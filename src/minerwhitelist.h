/*
 * minerwhitelist.h
 *
 *  Created on: Aug 26, 2016
 *      Author: rodrigo
 */

#ifndef MINERWHITELIST_H_
#define MINERWHITELIST_H_


#include <boost/filesystem/path.hpp>
#include <boost/foreach.hpp>
#include <boost/signals2/signal.hpp>


typedef std::vector<std::string> minerwhitelist_v;

/** Access to the miner list minerWhiteList.dat */
class CMinerWhiteList {
private:
	boost::filesystem::path pathMinerWhiteList;
public:
	// possible actions enum
	enum WhiteListAction {ADD_MINER, REMOVE_MINER, ENABLE_CAP, DISABLE_CAP, NONE};

	CMinerWhiteList();
	bool Write(minerwhitelist_v minerwhitelist);
	minerwhitelist_v Read();
	bool Exist(std::string pkey);
};

#endif /* MINERWHITELIST_H_ */
