Installing IoP Client
==========================

At this early stage we don't provide other packages than for Ubuntu Linux.
But you can find other community packages on the [community repositories](http://repo.fermat.community)

For a little help building IoP Core on OSX see [INSTALL_OSX.md](https://github.com/Fermat-ORG/iop-blockchain/blob/beta-1.0.0/INSTALL_OSX.md)

We will provide Windows, MacOSX and other Packages after the beta phase, please be patient.

# Installing Ubuntu Packages

To install IoP the first time on Ubuntu, add new repository to `/etc/apt/sources.list.d/IoP.list` with your editor (here "nano"):

`sudo nano /etc/apt/sources.list.d/IoP.list`

In the editor you do this

for Ubuntu 14.04:

`deb [arch=amd64] http://repo.fermat.community/ 14.04 main`

for Ubuntu 16.04:

`deb [arch=amd64] http://repo.fermat.community/ 16.04 main`

Save and exit editor.

Import the key that is used to sign the packages:

`gpg --keyserver keys.gnupg.net --recv-keys 0CC9EB6DA69C84F4`

`gpg -a --export A69C84F4 | sudo apt-key add -`

After that you can install IoP tools as any other software package:

`sudo apt-get update`

`sudo apt-get install iop-blockchain`

After installation is complete, start the IoP wallet by running IoP-qt from the command line.

`IoP-qt` 
... and have fun! :-)

Now you should have a working IoP blockchain deployment.

# Upgrading Ubuntu

If you have already installed and want to upgrade to the latest, please follow this way:

`sudo apt-get update`

`sudo apt-get upgrade`

# Troubleshooting in case of IoP Package error

If you run into problems with the package versions, then you could try following:

`sudo apt-get remove iop-blockchain`

`sudo rm -fr /var/cache/apt/archives/*`

`sudo apt-get clean`

`sudo apt-get update`

`sudo apt-get install iop-blockchain`

** if you are in trouble you should always backup your wallet.dat file!**
After that empty the .IoP folder despite the wallet.dat - then start the IoP-qt again.


Windows, MacOSX and Other Packages
========================
We don't support offically other packages (yet).
Nevertheless, there are [unsopported community build packages](http://repo.fermat.community) where you can even find Windows packages.

Using the blockchain tool
=========================

Until we have official documentation you can follow the Fermat IoP Wallet Guide:

[English](http://repo.fermat.community/Fermat_Wallet_Tutorial/FermatWalletTutorialEN.html)

[Spanish](https://docs.google.com/document/d/1_RkGVSKEz42Sh9NgGdt9WKrKcvi6jhdhtlxxHqgpZxA)

Compiling from source
=====================

First you have to grab the source code, you can just clone our GitHub repository. Assuming you work on Ubuntu and don't have git installed yet, you can have our initial release (tagged version beta-1.0.0) with:

`sudo apt-get install git`

`git clone https://github.com/Fermat-ORG/iop-blockchain.git`

`cd iop-blockchain`

`git checkout beta`


Now comes the hard part, you will have to install the whole build environment which means an awful lot of tools, libraries and headers.

sudo apt-get install g++ make automake pkg-config libtool libboost-all-dev libssl-dev libevent-dev libqrencode-dev libprotobuf-dev protobuf-compiler libqt5gui5 qttools5-dev qttools5-dev-tools

We still need the BerkeleyDB library to support wallets. The code assumes wallets built with 4.8 by default, but this version is now outdated and not accessible from the default repositories. If you insist on using backwards-compatible wallets, you have to get the library from a custom archive repository as described here https://github.com/bitcoin/bitcoin/blob/master/doc/build-unix.md (look for add-apt-repository). We simply suggest using a recent libdb version instead.

`sudo apt-get install libdb++-dev`

Now you have to generate the build configurator files.

`./autogen.sh`

Now you have to generate makefiles that fit your environment. This will take a lot of time. If you are using backwards-compatible wallets with libdb4.8, you can remove the option from the following command:

`./configure --with-incompatible-bdb`

Finally, you can compile everything. This will take a very, very long time. Note that if you have a lot of CPU cores in your computer, you should use the -j option to compile with multiple threads, e.g. -j8 for eight compiler threads.

`make`

If you want to run the compiled binaries directly, you can find them in directory src, e.g. src/IoPd or src/qt/IoP-qt. Otherwise, you can deploy them as usual with

`make install`

