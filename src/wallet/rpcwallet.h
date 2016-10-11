// Copyright (c) 2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef IoP_WALLET_RPCWALLET_H
#define IoP_WALLET_RPCWALLET_H

class CRPCTable;

void RegisterWalletRPCCommands(CRPCTable &tableRPC);

/* IoP beta change - we define this method to be able to see if the wallet is pass prhase locked or not from the miner */
bool IsWalletLocked();

#endif //IoP_WALLET_RPCWALLET_H
