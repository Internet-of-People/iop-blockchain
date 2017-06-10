// Copyright (c) 2015 The Bitcoin Core developers

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#ifndef IoP_ZMQ_ZMQABSTRACTNOTIFIER_H
#define IoP_ZMQ_ZMQABSTRACTNOTIFIER_H

#include "zmqconfig.h"

class CBlockIndex;
class CZMQAbstractNotifier;

typedef CZMQAbstractNotifier* (*CZMQNotifierFactory)();

class CZMQAbstractNotifier
{
public:
    CZMQAbstractNotifier() : psocket(0) { }
    virtual ~CZMQAbstractNotifier();

    template <typename T>
    static CZMQAbstractNotifier* Create()
    {
        return new T();
    }

    std::string GetType() const { return type; }
    void SetType(const std::string &t) { type = t; }
    std::string GetAddress() const { return address; }
    void SetAddress(const std::string &a) { address = a; }

    virtual bool Initialize(void *pcontext) = 0;
    virtual void Shutdown() = 0;

    virtual bool NotifyBlock(const CBlockIndex *pindex);
    virtual bool NotifyTransaction(const CTransaction &transaction);

protected:
    void *psocket;
    std::string type;
    std::string address;
};

#endif // IoP_ZMQ_ZMQABSTRACTNOTIFIER_H
