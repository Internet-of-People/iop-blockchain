#!/usr/bin/env python3
# Copyright (c) 2014-2016 The Bitcoin Core developers

# This program is free software: you can redistribute it and/or modify\n# it under the terms of the GNU General Public License as published by\n# the Free Software Foundation, either version 3 of the License, or\n# (at your option) any later version.\n\n# This program is distributed in the hope that it will be useful,\n# but WITHOUT ANY WARRANTY; without even the implied warranty of\n# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the \n# GNU General Public License for more details.\n\n# You should have received a copy of the GNU General Public License\n# along with this program. If not, see <http:#www.gnu.org/licenses/>.#

#
# Test -reindex and -reindex-chainstate with CheckBlockIndex
#
from test_framework.test_framework import IoPTestFramework
from test_framework.util import *
import time

class ReindexTest(IoPTestFramework):

    def __init__(self):
        super().__init__()
        self.setup_clean_chain = True
        self.num_nodes = 1

    def setup_network(self):
        self.nodes = []
        self.is_network_split = False
        self.nodes.append(start_node(0, self.options.tmpdir))

    def reindex(self, justchainstate=False):
        self.nodes[0].generate(3)
        blockcount = self.nodes[0].getblockcount()
        stop_node(self.nodes[0], 0)
        wait_IoPds()
        self.nodes[0]=start_node(0, self.options.tmpdir, ["-debug", "-reindex-chainstate" if justchainstate else "-reindex", "-checkblockindex=1"])
        while self.nodes[0].getblockcount() < blockcount:
            time.sleep(0.1)
        assert_equal(self.nodes[0].getblockcount(), blockcount)
        print("Success")

    def run_test(self):
        self.reindex(False)
        self.reindex(True)
        self.reindex(False)
        self.reindex(True)

if __name__ == '__main__':
    ReindexTest().main()
