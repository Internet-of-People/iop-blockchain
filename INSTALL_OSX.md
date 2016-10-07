# Installing IoP Core on Mac OS X

Download the .dmg file from [here](http://) and mount it. Move the .app file to your Applications folder.

At the moment, the GUI does not show or generate QR Codes.

Your wallet and all data will be stored in `~/Library/Application Support/IoP/`. To backup your wallet, copy `~/Library/Application Support/IoP/wallet.dat` to a secure location.

# Building IoP Core on Mac OS X

- Install the latest XCode Package from the Mac App Store (Command Line Tools are not sufficient) and run it. Accept the License Agreement and let it install components.

- Install homebrew (<http://brew.sh>) via the command prompt with

  ```
  /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
  ```

- Install dependencies with

  ```
  brew install automake berkeley-db4 libtool boost --c++11 miniupnpc openssl pkg-config homebrew/versions/protobuf260 --c++11 libevent qt5
  ```

  This will take a while. WARNING: macOS 10.12 users, see below.
- Use the command line to clone the git repository to your favorite location with 

  ```
  git clone https://github.com/Fermat-ORG/iop-blockchain.git /path/to/favorite/location
  ```

  e.g. 

  ```
  git clone https://github.com/Fermat-ORG/iop-blockchain.git ~/GitHub/iop-blockchain
  ```

- Change to this location using `cd ~/GitHub/iop-blockchain` or equivalent.

- Run `./autogen.sh`

- Run `./configure`

- Run `make && make deploy`. On macOS 10.12 you will get some warnings about deprecated functions. Ignore them for now. If everything goes well, you will now have two options. The binary `IoP-Qt.app` is linked to external libraries and will only run on macs with the same build environment. The `IoP-Qt.dmg` file contains another version of the application, which contains all necessary libraries and should be usable on all your Macs. The daemon and other tools are available at `src/IoPd`.


## Problems with macOS 10.12

If you are on macOS 10.12, homebrews qt5 (v5.6.1) is broken and at the moment (2016/10/7) will not `brew install`. Upstream should release a fixed version soon and the brew team will then update the formula.

For now, to get qt5 to compile, open `/usr/local/Homebrew/Library/Taps/homebrew/homebrew-core/Formula/qt5.rb` with your favorite editor and add

```
-skip qtconnectivity
-skip qtwebengine
-skip qtwebview
```

to the end of the lists of arguments here (should be line 80-96)

```
...
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
...
```

Save, close and continue as normal. Thanks for this solution to user [UdjinM6](https://github.com/UdjinM6), who posted it [here](https://github.com/Homebrew/homebrew-core/issues/4841#issuecomment-249177609).
