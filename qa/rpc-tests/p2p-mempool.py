#!/usr/bin/env python3
# Copyright (c) 2015-2016 The Bitcoin Core developers

# This program is free software: you can redistribute it and/or modify\n# it under the terms of the GNU General Public License as published by\n# the Free Software Foundation, either version 3 of the License, or\n# (at your option) any later version.\n\n# This program is distributed in the hope that it will be useful,\n# but WITHOUT ANY WARRANTY; without even the implied warranty of\n# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the \n# GNU General Public License for more details.\n\n# You should have received a copy of the GNU General Public License\n# along with this program. If not, see <http://www.gnu.org/licenses/>.#

from test_framework.mininode import *
from test_framework.test_framework import IoPTestFramework
from test_framework.util import *
import time

class TestNode(NodeConnCB):
    def __init__(self):
        NodeConnCB.__init__(self)
        self.connection = None
        self.ping_counter = 1
        self.last_pong = msg_pong()
        self.block_receive_map = {}

    def add_connection(self, conn):
        self.connection = conn
        self.peer_disconnected = False

    def on_inv(self, conn, message):
        pass

    # Track the last getdata message we receive (used in the test)
    def on_getdata(self, conn, message):
        self.last_getdata = message

    def on_block(self, conn, message):
        message.block.calc_sha256()
        try:
            self.block_receive_map[message.block.sha256] += 1
        except KeyError as e:
            self.block_receive_map[message.block.sha256] = 1

    # Spin until verack message is received from the node.
    # We use this to signal that our test can begin. This
    # is called from the testing thread, so it needs to acquire
    # the global lock.
    def wait_for_verack(self):
        def veracked():
            return self.verack_received
        return wait_until(veracked, timeout=10)

    def wait_for_disconnect(self):
        def disconnected():
            return self.peer_disconnected
        return wait_until(disconnected, timeout=10)

    # Wrapper for the NodeConn's send_message function
    def send_message(self, message):
        self.connection.send_message(message)

    def on_pong(self, conn, message):
        self.last_pong = message

    def on_close(self, conn):
        self.peer_disconnected = True

    # Sync up with the node after delivery of a block
    def sync_with_ping(self, timeout=30):
        def received_pong():
            return (self.last_pong.nonce == self.ping_counter)
        self.connection.send_message(msg_ping(nonce=self.ping_counter))
        success = wait_until(received_pong, timeout)
        self.ping_counter += 1
        return success

    def send_mempool(self):
        self.lastInv = []
        self.send_message(msg_mempool())

class P2PMempoolTests(IoPTestFramework):
    def setup_chain(self):
        initialize_chain_clean(self.options.tmpdir, 2)

    def setup_network(self):
        # Start a node with maxuploadtarget of 200 MB (/24h)
        self.nodes = []
        self.nodes.append(start_node(0, self.options.tmpdir, ["-debug", "-peerbloomfilters=0"]))

    def run_test(self):
        #connect a mininode
        aTestNode = TestNode()
        node = NodeConn('127.0.0.1', p2p_port(0), self.nodes[0], aTestNode)
        aTestNode.add_connection(node)
        NetworkThread().start()
        aTestNode.wait_for_verack()

        #request mempool
        aTestNode.send_mempool()
        aTestNode.wait_for_disconnect()

        #mininode must be disconnected at this point
        assert_equal(len(self.nodes[0].getpeerinfo()), 0)

if __name__ == '__main__':
    P2PMempoolTests().main()
