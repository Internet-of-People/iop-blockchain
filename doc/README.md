IoP Core 0.13.0
=====================

Setup
---------------------
[IoP Core](http://IoP.org/en/download) is the original IoP client and it builds the backbone of the network. However, it downloads and stores the entire history of IoP transactions (which is currently several GBs); depending on the speed of your computer and network connection, the synchronization process can take anywhere from a few hours to a day or more.

Running
---------------------
The following are some helpful notes on how to run IoP on your native platform.

### Unix

Unpack the files into a directory and run:

- `bin/IoP-qt` (GUI) or
- `bin/IoPd` (headless)

### Windows

Unpack the files into a directory, and then run IoP-qt.exe.

### OS X

Drag IoP-Core to your applications folder, and then run IoP-Core.

### Need Help?

* See the documentation at the [IoP Wiki](https://en.IoP.it/wiki/Main_Page)
for help and more information.
* Ask for help on [#IoP](http://webchat.freenode.net?channels=IoP) on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net?channels=IoP).
* Ask for help on the [IoPTalk](https://IoPtalk.org/) forums, in the [Technical Support board](https://IoPtalk.org/index.php?board=4.0).

Building
---------------------
The following are developer notes on how to build IoP on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [OS X Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)
- [Windows Build Notes](build-windows.md)
- [OpenBSD Build Notes](build-openbsd.md)
- [Gitian Building Guide](gitian-building.md)

Development
---------------------
The IoP repo's [root README](/README.md) contains relevant information on the development process and automated testing.

- [Developer Notes](developer-notes.md)
- [Multiwallet Qt Development](multiwallet-qt.md)
- [Release Notes](release-notes.md)
- [Release Process](release-process.md)
- [Source Code Documentation (External Link)](https://dev.visucore.com/IoP/doxygen/)
- [Translation Process](translation_process.md)
- [Translation Strings Policy](translation_strings_policy.md)
- [Unit Tests](unit-tests.md)
- [Unauthenticated REST Interface](REST-interface.md)
- [Shared Libraries](shared-libraries.md)
- [BIPS](bips.md)
- [Dnsseed Policy](dnsseed-policy.md)
- [Benchmarking](benchmarking.md)

### Resources
* Discuss on the [IoPTalk](https://IoPtalk.org/) forums, in the [Development & Technical Discussion board](https://IoPtalk.org/index.php?board=6.0).
* Discuss project-specific development on #IoP-core-dev on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net/?channels=IoP-core-dev).
* Discuss general IoP development on #IoP-dev on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net/?channels=IoP-dev).

### Miscellaneous
- [Assets Attribution](assets-attribution.md)
- [Files](files.md)
- [Tor Support](tor.md)
- [Init Scripts (systemd/upstart/openrc)](init.md)

License
---------------------
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
This product includes software developed by the OpenSSL Project for use in the [OpenSSL Toolkit](https://www.openssl.org/). This product includes
cryptographic software written by Eric Young ([eay@cryptsoft.com](mailto:eay@cryptsoft.com)), and UPnP software written by Thomas Bernard.
