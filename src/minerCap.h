/*
 * minerCap.h
 *
 *  Created on: Oct 11, 2016
 *      Author: rodrigo
 */

#ifndef MINERCAP_H_
#define MINERCAP_H_

#include "pubkey.h"
#include <boost/filesystem/path.hpp>
#include <tr1/unordered_map>

class CMinerCap {
private:
	typedef std::tr1::unordered_map <std::string, uint32_t> minerCapMap;
public:
	CMinerCap();

	// enables the miner cap. The passed factor is used to set the mining cap
	void enable(std::string factor);

	// disables miner cap
	void disable();

	// returns true if enabled.
	bool isEnabled();

	// gets the total amount of active miners.
	int getAvgBlocksPerMiner();

	// calculates when the monitoring window starts
	int getWindowStart(int currentHeight);

	// we are allowing miners to mine minerMultiplier times the average blocks / miner
	int getMinerMultiplier();

};

#endif /* MINERCAP_H_ */
