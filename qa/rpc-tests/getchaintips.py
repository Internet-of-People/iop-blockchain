#!/usr/bin/env python3
# Copyright (c) 2014-2016 The Bitcoin Core developers

# This program is free software: you can redistribute it and/or modify\n# it under the terms of the GNU General Public License as published by\n# the Free Software Foundation, either version 3 of the License, or\n# (at your option) any later version.\n\n# This program is distributed in the hope that it will be useful,\n# but WITHOUT ANY WARRANTY; without even the implied warranty of\n# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the \n# GNU General Public License for more details.\n\n# You should have received a copy of the GNU General Public License\n# along with this program. If not, see <http:#www.gnu.org/licenses/>.#

# Exercise the getchaintips API.  We introduce a network split, work
# on chains of different lengths, and join the network together again.
# This gives us two tips, verify that it works.

from test_framework.test_framework import IoPTestFramework
from test_framework.util import assert_equal

class GetChainTipsTest (IoPTestFramework):
    def __init__(self):
        super().__init__()
        self.num_nodes = 4
        self.setup_clean_chain = False

    def run_test (self):

        tips = self.nodes[0].getchaintips ()
        assert_equal (len (tips), 1)
        assert_equal (tips[0]['branchlen'], 0)
        assert_equal (tips[0]['height'], 200)
        assert_equal (tips[0]['status'], 'active')

        # Split the network and build two chains of different lengths.
        self.split_network ()
        self.nodes[0].generate(10)
        self.nodes[2].generate(20)
        self.sync_all ()

        tips = self.nodes[1].getchaintips ()
        assert_equal (len (tips), 1)
        shortTip = tips[0]
        assert_equal (shortTip['branchlen'], 0)
        assert_equal (shortTip['height'], 210)
        assert_equal (tips[0]['status'], 'active')

        tips = self.nodes[3].getchaintips ()
        assert_equal (len (tips), 1)
        longTip = tips[0]
        assert_equal (longTip['branchlen'], 0)
        assert_equal (longTip['height'], 220)
        assert_equal (tips[0]['status'], 'active')

        # Join the network halves and check that we now have two tips
        # (at least at the nodes that previously had the short chain).
        self.join_network ()

        tips = self.nodes[0].getchaintips ()
        assert_equal (len (tips), 2)
        assert_equal (tips[0], longTip)

        assert_equal (tips[1]['branchlen'], 10)
        assert_equal (tips[1]['status'], 'valid-fork')
        tips[1]['branchlen'] = 0
        tips[1]['status'] = 'active'
        assert_equal (tips[1], shortTip)

if __name__ == '__main__':
    GetChainTipsTest ().main ()
