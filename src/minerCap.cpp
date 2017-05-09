/*
 * minerCap.cpp
 *
 *  Created on: Oct 11, 2016
 *      Author: rodrigo
 */


#include <boost/algorithm/string.hpp>
#include "main.h"
#include "minerwhitelist.h"
#include "minerCap.h"
#include <string>




// String used to identify the enabled status.
const std::string ENABLED = "enabled:";


/* constructor  */
CMinerCap::CMinerCap() {

}

// utility function that translate into text from hexadecimal string.
std::string HexText(const std::string in){
	int len = in.length();
	std::string newString;
	for(int i=0; i< len; i+=2)
	{
	    std::string byte = in.substr(i,2);
	    char chr = (char) (int)strtol(byte.c_str(), NULL, 16);
	    newString.push_back(chr);
	}
	return newString;
}

// enables the miner cap
void CMinerCap::enable(std::string factor){
	CMinerWhiteList minerWhiteList;
	minerwhitelist_v minerVector = minerWhiteList.Read();
	std::string enabled = ENABLED + HexText(factor);
	minerVector.push_back(enabled);

	minerWhiteList.Write(minerVector);
}

// disables miner cap
void CMinerCap::disable(){
	CMinerWhiteList minerWhiteList;
	minerwhitelist_v minerVector = minerWhiteList.Read();

	std::string enabled = ENABLED + std::to_string(getMinerMultiplier());
	minerVector.erase(std::remove(minerVector.begin(), minerVector.end(), enabled), minerVector.end());

	minerWhiteList.Write(minerVector);
}

// returns true if enabled.
bool CMinerCap::isEnabled(){
	CMinerWhiteList minerWhiteList;
	minerwhitelist_v minerVector = minerWhiteList.Read();

	std::string enabled = ENABLED + std::to_string(getMinerMultiplier());
	return (std::find(minerVector.begin(), minerVector.end(), enabled) != minerVector.end());
}

// gets the average blocks per miner (2016 / amount of miners)
int CMinerCap::getAvgBlocksPerMiner(){
	CMinerWhiteList minerWhiteList;
	minerwhitelist_v minerVector = minerWhiteList.Read();

	return (2016 / (minerVector.size() -1)); // removing the enable line from the size
}

int CMinerCap::getCap(){
	CMinerWhiteList minerWhiteList;
	minerwhitelist_v minerVector = minerWhiteList.Read();
	
	int fac = getMinerMultiplier();
	return (fac * 2016 / (minerVector.size() -1)); // removing the enable line from the size
}

// gets the start of the cap window.
int CMinerCap::getWindowStart(int currentHeight){
	if (currentHeight < 2017)
		return 1;
	
	if (currentHeight < Params().GetConsensus().minerCapSystemChangeHeight) {
		for (int i = currentHeight; i>1; i--){ 
    if (i % 2016 == 0) 
      return i; 
    }
		return 0;
	}
	return currentHeight - 2016 + 1; // We want 2016 Blocks INCLUDING the current block.
}

int CMinerCap::getMinerMultiplier(){
	CMinerWhiteList minerWhiteList;
	minerwhitelist_v minerVector = minerWhiteList.Read();
	minerwhitelist_v::iterator it;

	for (it = minerVector.begin(); it < minerVector.end(); it++){
		std::vector<std::string> strs;
		boost::split(strs, *it, boost::is_any_of(":"));
		// I have found the enable:n string
		if (strs.size() > 1){
			return  atoi(strs[1].c_str());
		}
	}
	return 0;
}

int CMinerCap::getWhiteListedMiners(){
	CMinerWhiteList minerWhiteList;
	minerwhitelist_v minerVector = minerWhiteList.Read();
	return (minerVector.size() -1); // removing the enable line from the size
}
