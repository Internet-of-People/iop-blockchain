#!/usr/bin/env python2 
# Copyright (c) 2015 The Bitcoin Core developers 
 
# This program is free software: you can redistribute it and/or modify\n# it under the terms of the GNU General Public License as published by\n# the Free Software Foundation, either version 3 of the License, or\n# (at your option) any later version.\n\n# This program is distributed in the hope that it will be useful,\n# but WITHOUT ANY WARRANTY; without even the implied warranty of\n# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the \n# GNU General Public License for more details.\n\n# You should have received a copy of the GNU General Public License\n# along with this program. If not, see <http:#www.gnu.org/licenses/>.#

import hashlib
import sys
import os
from random import SystemRandom
import base64
import hmac

if len(sys.argv) < 2:
    sys.stderr.write('Please include username as an argument.\n')
    sys.exit(0)

username = sys.argv[1]

#This uses os.urandom() underneath
cryptogen = SystemRandom()

#Create 16 byte hex salt
salt_sequence = [cryptogen.randrange(256) for i in range(16)]
hexseq = list(map(hex, salt_sequence))
salt = "".join([x[2:] for x in hexseq])

#Create 32 byte b64 password
password = base64.urlsafe_b64encode(os.urandom(32))

digestmod = hashlib.sha256

if sys.version_info.major >= 3:
    password = password.decode('utf-8')
    digestmod = 'SHA256'
 
m = hmac.new(bytearray(salt, 'utf-8'), bytearray(password, 'utf-8'), digestmod)
result = m.hexdigest()

print("String to be appended to IoP.conf:")
print("rpcauth="+username+":"+salt+"$"+result)
print("Your password:\n"+password)
