<!-- #Installing IoP Core on OS X

Download the binary file from 
```
http://link.here
```
and extract. Move the .app file to your Applications folder. Your wallet and all data will be stored in `~/Library/Application Support/IoP/`. To backup your wallet, copy 
`~/Library/Application Support/IoP/wallet.dat` to a secure location. -->

#Building IoP Core on Mac

* Install the latest XCode Package from the Mac App Store (Command Line Tools are not sufficient).

* Install homebrew (http://brew.sh) via the command prompt with
```
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```
* Install dependencies with
```
brew install automake berkeley-db4 libtool boost --c++11 miniupnpc openssl pkg-config homebrew/versions/protobuf260 --c++11 libevent qt5
``` 
This will take a while. WARNING: For macOS 10.12 users, see below.
* Use the command line to clone the git repository to your favorite location with 
```
git clone https://github.com/Fermat-ORG/iop-blockchain.git /path/to/favorite/location
```
e.g. 
```
git clone https://github.com/Fermat-ORG/iop-blockchain.git ~/GitHub/iop-blockchain
```
* Change to this location using `cd ~/GitHub/iop-blockchain` or equivalent.

* Run `./autogen.sh`

* Run `./configure`. Ignore the warnings about deprecated functions for now.

* Run `make && make deploy`

* Move the .app to your Applications Folder with `mv ./IoP-Qt.app /Applications/`

* Your wallet and all data will be stored in `~/Library/Application Support/IoP/`. To backup your wallet, copy 
`~/Library/Application Support/IoP/wallet.dat` to a secure location. 

# WARNING
If you are on macOS 10.12, qt5 is broken and will not `brew install`. To work around this, open `/usr/local/Homebrew/Library/Taps/homebrew/homebrew-core/Formula/qt5.rb` and add 

```
-skip qtconnectivity
-skip qtwebengine
-skip qtwebview
```

to the end of the lists of arguments here (should be line 80-96)

```
def install
    args = %W[
      -verbose
      -prefix #{prefix}
      -release
      -opensource -confirm-license
      -system-zlib
      -qt-libpng
      -qt-libjpeg
      -qt-freetype
      -qt-pcre
      -nomake tests
      -no-rpath
      ]
```

Then save and close. Continue as normal.
