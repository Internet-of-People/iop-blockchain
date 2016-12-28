/*
 * votingSystem.h
 *
 *  Created on: Nov 14, 2016
 *      Author: rodrigo
 */

#ifndef VOTINGSYSTEM_H_
#define VOTINGSYSTEM_H_

#include "utilstrencodings.h"
#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>

#include "base58.h"
#include "clientversion.h"
#include "chain.h"
#include "chainparams.h"
#include "main.h"
#include "primitives/block.h"
#include "primitives/transaction.h"

#include "streams.h"
#include "stdio.h"
#include <fstream>
#include <iostream>
#include <string>

#include <rpc/blockchain.cpp>
#include <minerCap.cpp>

#include "votingSystem.h"

#include "util.h"
#include "uint256.h"
#include "utilstrencodings.h"



#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>

class CCBeneficiary {
private:
	CIoPAddress address;
	CAmount amount;
public:
	// constructs a new contribution contract
	CCBeneficiary(CIoPAddress address, CAmount amount){
		this->address = address;
		this->amount = amount;
	}

	CAmount getAmount(){
		return this->amount;
	}

	CIoPAddress getAddress(){
		return this->address;
	}
};


class ContributionContract {
private:
	boost::filesystem::path pathContributionContract;

public:
	int blockStart;
	std::string version;
	int blockEnd;
	int genesisBlockHeight;
	CTransaction genesisTx;
	uint256 genesisTxHash;
	std::vector<int> votes;

	// possible ContributionContract states
	enum CCState {
		SUBMITTED, 				// Transaction confirmed on blockchain. No votes yet.
		APPROVED, 				// YES > NO. Current height  < (BlockStart + 1000 blocks).
		NOT_APPROVED, 			// NO > YES. Current height  < (BlockStart + 1000 blocks).
		QUEUED_FOR_EXECUTION,	// YES > NO. Current height  < (BlockStart + 1000 blocks).
		IN_EXECUTION,			// YES > NO. Current height  > BlockStart  and Current height  < BlockEnd
		EXECUTION_CANCELLED, 	// NO > YES. Current height  > BlockStart  and Current height  < BlockEnd
		EXECUTED,				// YES > NO. Current height  > BlockEnd
		UNKNOWN};				// initial state

	std::vector<CCBeneficiary> beneficiaries;
	CAmount blockReward;
	CCState state;
	// constructs a new contribution contract
	ContributionContract(){
		this->blockStart = 0;
		this->blockEnd = 0;
		this->state = UNKNOWN;
	}

	static std::string getState(CCState state){
		switch (state){
		case SUBMITTED: return "SUBMITTED";
		case APPROVED: return "APPROVED";
		case NOT_APPROVED: return "NOT_APPROVED";
		case QUEUED_FOR_EXECUTION: return "QUEUED_FOR_EXECUTION";
		case IN_EXECUTION: return "IN_EXECUTION";
		case EXECUTION_CANCELLED: return "EXECUTION_CANCELLED";
		case EXECUTED: return "EXECUTED";
		default: return "UNKNOWN";
		}
	}

	/**
	 * Validates if the passed script is from a contribution contract.
	 */
	static bool isContributionContract(const CScript scriptPubKey){
		// 1st condition must be op_return
		if (scriptPubKey[0] != OP_RETURN)
			return false;

		// 2nd condition, first 2 bytes must be 0x4343
		CScript::const_iterator pc = scriptPubKey.begin();
		opcodetype opcode;
		std::vector<unsigned char> value;

		while (pc < scriptPubKey.end()){
			scriptPubKey.GetOp(pc, opcode, value);
		}

		// we get the OP_Return data into the string and validate is CC for Contribution Contract
		std::string opreturn = HexStr(value);

		if (opreturn.size() > 2){
			if (opreturn.substr(0, 4).compare("4343") == 0){
				return true;
			}

		}
		// not a valid CC
		return false;
	}

	/**
	 * Extracts and return the opreturn string from the scriptPubKey
	 */
	static bool getOPReturn(CScript scriptPubKey, std::string &out){
		// 1st condition must be op_return
			if (scriptPubKey[0] != OP_RETURN)
				return false;

			CScript::const_iterator pc = scriptPubKey.begin();
			opcodetype opcode;
			std::vector<unsigned char> value;

			while (pc < scriptPubKey.end()){
				scriptPubKey.GetOp(pc, opcode, value);
			}

			// we get the OP_Return data into the string
			out = HexStr(value);
			return true;
	}

	static int HexToInt(std::string hexstr){
		 int x;
		std::stringstream ss;
		ss << std::hex << hexstr;
		ss >> x;
		return x;
	}

	// gets a contribution contract from the passed Transaction
	static  bool getContributionContract(CTransaction genesisTx, ContributionContract &out){
		ContributionContract cc;

		// parse the op_return and return it.
		std::string value = "";

		CScript ccScript;
		int outputIndex = 0;
		for (unsigned int i = 0; i < genesisTx.vout.size(); i++){
			if (isContributionContract(genesisTx.vout[i].scriptPubKey)){
				getOPReturn(genesisTx.vout[i].scriptPubKey, value);
				outputIndex = i;
			}
		}

		if (value.size() == 0)
			return false;

		// get the version
		std::string textVersion(value.substr(4,4));


		cc.version = textVersion;

		// get the block start height
		std::string strBlockStart = value.substr(8,6);
		cc.blockStart = HexToInt(strBlockStart);


		// get the block end height
		std::string strBlockend = value.substr(14,4);
		cc.blockEnd = HexToInt(strBlockend);


		// get the block reward
		std::string strReward = value.substr(18,6);
		cc.blockReward= HexToInt(strReward);

		// the hash of the genesis transaction
		cc.genesisTxHash = genesisTx.GetHash();
		cc.genesisTx = genesisTx;

		//let's get the beneficiaries of this contract
		for (unsigned int x = outputIndex+1; x < genesisTx.vout.size(); x++){
			CScript redeemScript = genesisTx.vout[x].scriptPubKey;
			CTxDestination destinationAddress;
			ExtractDestination(redeemScript, destinationAddress);
			CIoPAddress address(destinationAddress);
			CCBeneficiary beneficiary = CCBeneficiary(address,genesisTx.vout[x].nValue);
			cc.beneficiaries.push_back(beneficiary);
		}

		out = cc;
		return true;
	}

	static bool getActiveContracts(int currentHeight, std::vector<ContributionContract>& ccOut){
		std::vector<std::string> ccPointers;
		ccPointers = loadCCPointers();

		bool found = false;

		for (auto i : ccPointers){
			std::vector<std::string> strs;
			boost::split(strs, i, boost::is_any_of(","));

			CTransaction ccGenesisTx;
			ccGenesisTx = loadCCGenesisTransaction(atoi(strs[0]), uint256S(strs[1]));
			if (ccGenesisTx.vin.size() > 0){
				BOOST_FOREACH(const CTxOut& out, ccGenesisTx.vout) {
					if (isContributionContract(out.scriptPubKey)){
						ContributionContract cc;
						if (getContributionContract(ccGenesisTx, cc)){
							cc.genesisBlockHeight = atoi(strs[0]); //I set the block height
							if (cc.isValid()){
								if (cc.isActive(currentHeight)){
									cc.state = IN_EXECUTION;
									found = true;
									ccOut.push_back(cc);
								}

							}
						}
					}
				}
			}
		}

		return found;
	}


	// stores this contribution contract to disk.
	bool persist(int blockHeight, uint256 genesisTxHash){
		pathContributionContract = GetDataDir() / "cc.dat";

		std::vector<std::string> cc;
		std::string height = std::to_string(blockHeight);
		cc.push_back(height + "," + genesisTxHash.ToString());

		try{
			//delete duplicates before storing
			std::ofstream file(pathContributionContract.string().c_str());
			for (unsigned int i=0; i < cc.size();i++){
				file << cc[i] << std::endl;
			}
			file.close();
			return true;
		} catch (const std::exception& e){
			return error("%s: Serialize or I/O error - %s", __func__, e.what());
		}
	}

	// ToString override.
	std::string ToString(){
		std::string output = "\nVersion: " + this->version + "\n";
		output = output  + "Block start: " + std::to_string(this->blockStart) + "\n";
		output = output  + "Block end: " + std::to_string(this->blockEnd) + "\n";
		output = output  + "CC Start height: " + std::to_string(this->blockStart + this->genesisBlockHeight + Params().GetConsensus().ccBlockStartAdditionalHeight) + "\n";
		output = output  + "CC End height: " + std::to_string(this->blockEnd + this->blockStart + this->genesisBlockHeight+Params().GetConsensus().ccBlockStartAdditionalHeight) + "\n";
		output = output  + "Block Reward: " + std::to_string(this->blockReward) + "\n";
		output = output  + "Genesis Tx: " + this->genesisTxHash.ToString() + "\n";
		output = output  + "Genesis block height: " + std::to_string(this->genesisBlockHeight) + "\n";
		for (CCBeneficiary ccb : this->beneficiaries){
			output = output  + " Beneficiary : " + ccb.getAddress().ToString() + " - " + std::to_string(ccb.getAmount()) + "\n";
		}
		return output;
	}

	static std::vector<std::string> loadCCPointers(){
		//sets the directory where the file will be saved.
		boost::filesystem::path pathContributionContract = GetDataDir() / "cc.dat";
		std::vector<std::string> cc;
				try{
					std::ifstream file(pathContributionContract.string().c_str());

					std::string pkey;
					while (file >> pkey) {
						cc.push_back(pkey);
					}

					file.close();
				} catch (const std::exception& e){
					//return error("%s: Serialize or I/O error - %s", __func__, e.what());
				}
				return cc;
	}

	// gets true if the contract is valid in all the rules.
		bool isValid(){
			// valid version is 0
			if (this->version.compare("0001") != 0)
				return false;

			// we validate that this transaction freezes at least 1000 IoP
			if (this->genesisTx.vout[0].nValue < COIN * 1000)
				return false;

			// can't pay more than 0.1 IoP
			if (this->blockReward > COIN * 0.1)
				return false;

			// Block start is defined as current Height + 1000 + n, and can't be more than 6 months, or 11960 blocks.
			if (this->blockStart > 11960)
				return false;

			// block end is defined as EndBlock = StartBlock + n. and can't be more than 4 weeks, or 20160 blocks.
			if (this->blockEnd > 20160)
				return false;

			// sum of beneficiaries amount, must be equal to block reward.
			CAmount totalAmount = 0;
			BOOST_FOREACH(CCBeneficiary beneficiary, this->beneficiaries){
				totalAmount = totalAmount + beneficiary.getAmount();
			}
			if (totalAmount != this->blockReward)
				return false;


			// at this point the Contribution contract is valid.
			return true;

		}


		static bool getContributionContracts(int currentHeight, std::vector<ContributionContract>& ccOut){
				std::vector<std::string> ccPointers;
				ccPointers = loadCCPointers();

				bool found = false;

				for (auto i : ccPointers){
					std::vector<std::string> strs;
					boost::split(strs, i, boost::is_any_of(","));

					CTransaction ccGenesisTx;
					ccGenesisTx = loadCCGenesisTransaction(atoi(strs[0]), uint256S(strs[1]));
					if (ccGenesisTx.vin.size() > 0){
						BOOST_FOREACH(const CTxOut& out, ccGenesisTx.vout) {
							if (isContributionContract(out.scriptPubKey)){
								ContributionContract cc;
								if (getContributionContract(ccGenesisTx, cc)){
									cc.genesisBlockHeight = atoi(strs[0]); //I set the block height
									if (cc.isValid()){
											cc.votes = cc.getCCVotes(currentHeight);
											cc.state = cc.getCCState(currentHeight);
											found = true;
											ccOut.push_back(cc);
									}
								}
							}
						}
					}
				}

				return found;
			}

		CCState getCCState(int currentHeight){
			// possible states are SUBMITTED, APPROVED, NOT APPROVED depending on the votes count
			if (currentHeight < this->blockStart + this->genesisBlockHeight + Params().GetConsensus().ccBlockStartAdditionalHeight){
				std::vector<int> votes;
				votes.push_back(0);
				votes.push_back(0);

				votes = getCCVotes(currentHeight);
				if (votes[0] == 0 && votes[1] == 0){
					return SUBMITTED;
				}

				if (votes[0] > votes[1]){
					return APPROVED;
				}

				if (votes[0] < votes[1]){
					return NOT_APPROVED;
				}
			}


			// possible states are NOT_APPROVED and QUEUED_FOR_EXECUTION depending on the votes count
			if (currentHeight > this->blockStart + this->genesisBlockHeight  &&
					currentHeight < this->blockStart + this->genesisBlockHeight + Params().GetConsensus().ccBlockStartAdditionalHeight){
				std::vector<int> votes;
				votes.push_back(0);
				votes.push_back(0);

				votes = getCCVotes(currentHeight);
				if (votes[0] > votes[1]){
					return QUEUED_FOR_EXECUTION;
				}

				if (votes[0] < votes[1]){
					return NOT_APPROVED;
				}

			}

			// possible states are NOT_APPROVED, IN_EXECUTION and EXECUTION_CANCELLED depending on the votes count
			if (currentHeight > this->blockStart + this->genesisBlockHeight + Params().GetConsensus().ccBlockStartAdditionalHeight &&
					currentHeight < this->blockEnd + this->blockStart + this->genesisBlockHeight+Params().GetConsensus().ccBlockStartAdditionalHeight){
				std::vector<int> votes;
				votes.push_back(0);
				votes.push_back(0);

				votes = getCCVotes(currentHeight);
				LogPrint("VotingSystem", "Votes yes/no:%s/%s \n", votes[0], votes[1]);

				if (votes[0] == 0 && votes[1] == 0){
					return NOT_APPROVED;
				}


				if (votes[0] > votes[1]){
					return IN_EXECUTION;
				}

				if (votes[0] < votes[1]){
					return EXECUTION_CANCELLED;
				}

			}

			// possible states are EXECUTED  depending on the votes count
			if (currentHeight > this->blockEnd + this->blockStart + this->genesisBlockHeight+Params().GetConsensus().ccBlockStartAdditionalHeight){
				std::vector<int> votes;
				votes.push_back(0);
				votes.push_back(0);

				votes = getCCVotes(currentHeight);
				if (votes[0] > votes[1]){
					return EXECUTED;
				}
			}

			return UNKNOWN;
		}


		// a CC is Active if it is between the blocks period and the amount of YES votes is bigger than the NO votes.
		bool isActive(int currentHeight){
			// first condition to be active: current height must be greater that blockstart
			if (currentHeight < this->blockStart + this->genesisBlockHeight + Params().GetConsensus().ccBlockStartAdditionalHeight)
				return false;

			// if the current height is greater than blockend the cc is expired.
			if (currentHeight > this->blockEnd + this->blockStart + this->genesisBlockHeight+Params().GetConsensus().ccBlockStartAdditionalHeight)
				return false;

			// 1000 IoPs that where used to create the CC must still be locked, which means that there must
			// not be another transaction that uses that input in the Active period.
			UniValue utxo(UniValue::VOBJ);
			UniValue ret(UniValue::VOBJ);
			utxo.push_back(Pair("tx", this->genesisTxHash.ToString()));
			utxo.push_back(Pair("n", 0));
			ret = gettxout(utxo, false);
			// if I didn't get a result, then no utxo and the locked coins of the CC are already spent.

			if (ret.isNull())
				return false;


			// The amount of YES votes must be greater than NO votes.
			// I need to search all the Votes transaction since the genesis block.
			std::vector<int> votes;
			votes.push_back(0);
			votes.push_back(0);

			votes = getCCVotes(currentHeight);
			if (votes[0] > votes[1] || (votes[0] == 0 && votes[1] == 0)){
				return false;
			}

			return true;
		}


		// gets the total numbers of valid votes for the CC.
		// position 0 are YES votes, Position 1 are NO votes
		std::vector<int> getCCVotes(int currentHeight){
			std::vector<int> votes;
			votes.push_back(0);
			votes.push_back(0);

			for (int i = this->genesisBlockHeight; i<currentHeight; i++){
				CBlockIndex* blockIndex = chainActive[i];
				if (blockIndex == NULL)
					return votes;

				CBlock block;
				if (ReadBlockFromDisk(block, blockIndex, Params().GetConsensus())){
					std::string op_returnData = "";
					BOOST_FOREACH(CTransaction tx, block.vtx){
						if (i <= this->blockStart + this->genesisBlockHeight)
							getVote(tx, votes, true); // if the CC is not yet active, then count positive votes
						else
							getVote(tx, votes, false);
					}
				}
			}

			return votes;
		}



		bool getVote(CTransaction tx, std::vector<int> votes, bool includePositive){
			// can't be coinbase
			if (tx.IsCoinBase())
				return false;

			// first output is vote power
			CAmount amount = tx.vout[0].nValue;

			// transaction must have an op_return type output
			BOOST_FOREACH(CTxOut output, tx.vout){
				if (output.scriptPubKey[0] == OP_RETURN){
					CScript::const_iterator pc = output.scriptPubKey.begin();
					opcodetype opcode;
					std::vector<unsigned char> value;

					while (pc < output.scriptPubKey.end()){
						output.scriptPubKey.GetOp(pc, opcode, value);
					}

					std::string opreturn = HexStr(value);
					if (opreturn.size() == 72){ //string must be 36 bytes long
						// text in op_return output must be 0x564f54
						if (opreturn.substr(0, 6).compare("564f54") == 0){
							// vote power must be locked, meaning the output must in an utxo
							UniValue utxo(UniValue::VOBJ);
							UniValue ret(UniValue::VOBJ);
							utxo.push_back(Pair("tx", tx.GetHash().ToString()));
							utxo.push_back(Pair("n", 0));
							ret = gettxout(utxo, false);
							// if I didn't get a result, then no utxo and the locked coins of the Vote transaction are already spent.
							if (ret.isNull())
								return false;

							//referenced transaction must be the same as genesis hash
							if (opreturn.substr(8, 64).compare(this->genesisTxHash.ToString()) == 0){
								// we get the YES Votes
								if (opreturn.substr(6, 2).compare("01") == 0  && includePositive){
									votes[0] = amount;
									return true;
								}

								// we get the NO votes
								if (opreturn.substr(6, 2).compare("00") == 0){
									votes[1] = amount * 5; //negative votes weight x5
									return true;
								}


							}

						}
					}
				}
			}

			return false;
		}


		/**
		 * gets the genesis Transaction of the contribution Contract by getting the block at the specified id
		 * and iterating transaction within the block.
		 */
		static CTransaction loadCCGenesisTransaction(int blockHeight, uint256 txHash){
			CTransaction txOut;
			CBlockIndex* blockIndex = chainActive[blockHeight];
			// if the index passed is not valid, no CC genesis transaction available
			if (blockIndex == NULL)
				return txOut;


			CBlock block;
			if (ReadBlockFromDisk(block, blockIndex, Params().GetConsensus())){
				BOOST_FOREACH(const CTransaction& tx, block.vtx){
					if (tx.GetHash().Compare(txHash) == 0)
					return tx;
				}
			}
			// block or transaction does not exists.
			return txOut;
		}

};

#endif /* VOTINGSYSTEM_H_ */
