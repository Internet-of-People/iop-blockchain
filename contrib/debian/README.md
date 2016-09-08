
Debian
====================
This directory contains files used to package IoPd/IoP-qt
for Debian-based Linux systems. If you compile IoPd/IoP-qt yourself, there are some useful files here.

## IoP: URI support ##


IoP-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install IoP-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your IoP-qt binary to `/usr/bin`
and the `../../share/pixmaps/IoP128.png` to `/usr/share/pixmaps`

IoP-qt.protocol (KDE)

