IoP Core integration/staging tree
=====================================

[![Build Status](https://travis-ci.org/IoP/IoP.svg?branch=master)](https://travis-ci.org/IoP/IoP)

https://IoPcore.org

What is IoP?
----------------

IoP is an experimental digital currency that enables instant payments to
anyone, anywhere in the world. IoP uses peer-to-peer technology to operate
with no central authority: managing transactions and issuing money are carried
out collectively by the network. IoP Core is the name of open source
software which enables the use of this currency.

For more information, as well as an immediately useable, binary version of
the IoP Core software, see https://IoP.org/en/download, or read the
[original whitepaper](https://IoPcore.org/IoP.pdf).

License
-------

IoP Core is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.

Development Process
-------------------

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/IoP/IoP/tags) are created
regularly to indicate new official, stable release versions of IoP Core.

The contribution workflow is described in [CONTRIBUTING.md](CONTRIBUTING.md).

The developer [mailing list](https://lists.linuxfoundation.org/mailman/listinfo/IoP-dev)
should be used to discuss complicated or controversial changes before working
on a patch set.

Developer IRC can be found on Freenode at #IoP-core-dev.

Testing
-------

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test on short notice. Please be patient and help out by testing
other people's pull requests, and remember this is a security-critical project where any mistake might cost people
lots of money.

### Automated Testing

Developers are strongly encouraged to write [unit tests](/doc/unit-tests.md) for new code, and to
submit new unit tests for old code. Unit tests can be compiled and run
(assuming they weren't disabled in configure) with: `make check`

There are also [regression and integration tests](/qa) of the RPC interface, written
in Python, that are run automatically on the build server.
These tests can be run (if the [test dependencies](/qa) are installed) with: `qa/pull-tester/rpc-tests.py`

The Travis CI system makes sure that every pull request is built for Windows, Linux, and OS X, and that unit/sanity tests are run automatically.

### Manual Quality Assurance (QA) Testing

Changes should be tested by somebody other than the developer who wrote the
code. This is especially important for large or high-risk changes. It is useful
to add a test plan to the pull request description if testing the changes is
not straightforward.

Translations
------------

Changes to translations as well as new translations can be submitted to
[IoP Core's Transifex page](https://www.transifex.com/projects/p/IoP/).

Translations are periodically pulled from Transifex and merged into the git repository. See the
[translation process](doc/translation_process.md) for details on how this works.

**Important**: We do not accept translation changes as GitHub pull requests because the next
pull from Transifex would automatically overwrite them again.

Translators should also subscribe to the [mailing list](https://groups.google.com/forum/#!forum/IoP-translators).

# Installing

## Ubuntu Packages

To install IoP the first time, add new repository to /etc/apt/sources.list.d/IoP.list with your editor (here "nano"):

sudo nano /etc/apt/sources.list.d/IoP.list
In the editor:
for Ubuntu 14.04:
`deb [arch=amd64] http://repo.fermat.community/ 14.04 main`

for Ubuntu 16.04:
`deb [arch=amd64] http://repo.fermat.community/ 16.04 main`

Save and exit editor.

Import the key that is used to sign the packages:

`gpg --keyserver keys.gnupg.net --recv-keys 0CC9EB6DA69C84F4
gpg -a --export A69C84F4 | sudo apt-key add -`

After that you can install IoP tools as any other software package:

`sudo apt-get update
sudo apt-get install iop-blockchain`

After installation is complete, start the IoP wallet by running IoP-qt from the command line.

IoP-qt ... and have fun! :-)

If you have already installed and want to upgrade to the latest, please follow this way:

`sudo apt-get update
sudo apt-get upgrade`

If you run into problems with the package versions, then you could try following:
`sudo apt-get remove iop-blockchain
sudo rm -fr /var/cache/apt/archives/*
sudo apt-get clean
sudo apt-get update
sudo apt-get install iop-blockchain`

** if you are in trouble you always should backup your wallet.dat file!**
After that empty the .IoP folder despite the wallet.dat - then start the IoP-qt again.
