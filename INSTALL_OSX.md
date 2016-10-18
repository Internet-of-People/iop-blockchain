At the moment we only provide instructions to build your own copy of IoP Core. If you have absolutely no idea about programming, please follow the Laymen's Guide. If you know your way around the terminal and want to control exactly where files are placed, follow the second guide.

You will need Apple's **XCode** (Command Line Tools are not sufficient). For Mac OS X 10.11.5 or higher, it is provided for free via the Mac App Store. If you are on a lower Version of Mac OS X, you need to manually download Xcode from the developer homepage. For this you need to register for a free Apple developer account on <http://developer.apple.com>

# Building IoP Core on Mac OS X for Laymen

- Update you Mac to the newest version available (at least 10.11.5)
- Install the latest XCode Package from the Mac App Store and run it. Accept the License Agreement and let it install components. 

- Open the Application **Terminal** and paste the following lines one by one, pressing the return key after each one and then waiting until you are prompted for input again.

  ```/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"```

  ```brew install automake berkeley-db4 libtool boost --c++11 miniupnpc openssl pkg-config homebrew/versions/protobuf260 --c++11 libevent qt5```
  This will take a while.
  
  ```git clone https://github.com/Fermat-ORG/iop-blockchain.git ~/Documents/iop-blockchain```
  
  ```cd ~/Documents/iop-blockchain```
  
  ```git checkout beta-1.0.0```
  
  ```./autogen.sh && ./configure```
  
  ```make && make deploy```

If everything goes well, you can find the application `IoP Core.app` in your Documents Folder under iop-blockchain. Drag this to your Applications Folder.

# Building IoP Core on Mac OS X 

- Install XCode and run it. Accept the License Agreement and let it install components. 

- Install [homebrew](http://brew.sh) via the terminal (**Terminal.app**) with

  ```
  /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
  ```

- Install dependencies with

  ```
  brew install automake berkeley-db4 libtool boost --c++11 miniupnpc openssl pkg-config homebrew/versions/protobuf260 --c++11 libevent qt5
  ```

  This will take a while.

  
- Use the terminal to clone the git repository to your favorite location with e.g.

  ```
  git clone https://github.com/Fermat-ORG/iop-blockchain.git ~/GitHub/iop-blockchain
  ```

- Change to this location using `cd ~/GitHub/iop-blockchain` or equivalent.

- Run `./autogen.sh`

- Run `./configure`

- Run `make && make deploy`. You might get some warnings about deprecated functions. Ignore them. If everything goes well, you can find the application `IoP Core.app` in `~/GitHub/iop-blockchain`. Drag this to your Applications Folder.

## Some Notes

At the moment, the GUI does not show or generate QR Codes.

Your wallet and all data will be stored in `~/Library/Application Support/IoP/`. To backup your wallet, copy `~/Library/Application Support/IoP/wallet.dat` to a secure location. Although there seem to be no problems, you should use this wallet file only with the Mac OS X version of IoP Core, as the Mac version is compiled against Berkeley DB 4 instead of Berkeley DB 5 and data files might be incompatible. To migrate your wallet between Operating Systems, we recommend using `dumpprivkey`.


## A note for experienced users

You can use  `berkeley-db` (v6.1.26 as of 2016/10/08) instead of `berkeley-db4` to compile IoP Core, but data files might not be fully compatible between different versions of BDB, so it is recommended to migrate wallets between versions and/or operating systems via `dumpprivkey`. You also need to `configure` with `./configure CPPFLAGS="-I/usr/local/Cellar/berkeley-db/6.1.26/include -O2" LDFLAGS="-L/usr/local/Cellar/berkeley-db/6.1.26/lib" --with-incompatible-bdb`