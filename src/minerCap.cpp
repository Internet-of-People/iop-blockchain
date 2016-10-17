/*
 * minerCap.cpp
 *
 *  Created on: Oct 11, 2016
 *      Author: rodrigo
 */


#include "main.h"
#include "minerwhitelist.h"
#include "minerCap.h"



// String used to identify the enabled status.
const std::string ENABLED = "enabled";
// the miner is allowed to mine this times the average
const int capMultiplier = 3;

/* constructor with directory to save the file */
CMinerCap::CMinerCap() {

}

// enables the miner cap
void CMinerCap::enable(){
	CMinerWhiteList minerWhiteList;
	minerwhitelist_v minerVector = minerWhiteList.Read();

	if (std::find(minerVector.begin(), minerVector.end(), ENABLED) == minerVector.end())
		minerVector.push_back(ENABLED);

	minerWhiteList.Write(minerVector);
}

// disables miner cap
void CMinerCap::disable(){
	CMinerWhiteList minerWhiteList;
	minerwhitelist_v minerVector = minerWhiteList.Read();

	minerVector.erase(std::remove(minerVector.begin(), minerVector.end(), ENABLED), minerVector.end());

	minerWhiteList.Write(minerVector);
}

// returns true if enabled.
bool CMinerCap::isEnabled(){
	CMinerWhiteList minerWhiteList;
	minerwhitelist_v minerVector = minerWhiteList.Read();

	return (std::find(minerVector.begin(), minerVector.end(), ENABLED) != minerVector.end());
}

// gets the average blocks per miner (2016 / amount of miners)
int CMinerCap::getAvgBlocksPerMiner(){
	CMinerWhiteList minerWhiteList;
	minerwhitelist_v minerVector = minerWhiteList.Read();

	return (2016 / (minerVector.size() -1)); // removing the enable line from the size
}

// gets the start of the cap window.
int CMinerCap::getWindowStart(int currentHeight){
	if (currentHeight < 2017)
		return 1;

	for (int i = currentHeight; i>1; i--){
		if (i % 2016 == 0)
			return i;
	}

	return 0;
}

int CMinerCap::getMinerMultiplier(){
	return capMultiplier;
}

