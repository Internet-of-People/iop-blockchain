#IoP Blockchain

## Wallet Installation
In order to install the IoP Wallet that will allow you to send and recieve IoPs you need to follow this procedure:

### For Ubuntu users
Follow the instructions to install here http://repo.fermat.community/index.html

To install IoP, add new repository to /etc/apt/sources.list.d/IoP.list with your editor (here "nano"):

    $ sudo nano /etc/apt/sources.list.d/IoP.list

In the editor:

*for Ubuntu 14.04:*

    $ deb http://repo.fermat.community/ 14.04 main  

*for Ubuntu 16.04:*  

    $ deb   http://repo.fermat.community/ 16.04 main  

Save and exit editor.  

Import the key that is used to sign the packages:  

    $ gpg --keyserver keys.gnupg.net --recv-keys 0CC9EB6DA69C84F4  
    $ gpg -a --export A69C84F4 | sudo apt-key add -

After that you can install IoP tools as any other software package:  

    $ apt-get update  
    $ apt-cache search iop  
    $ apt-get install iop-blockchain  
  
If you have Ubuntu 16.04 running, you might need to

    $ apt install libboost-filesystem1.58.0
as well.

After installation is complete, start the IoP wallet by running **IoP-qt** from the command line.

    $ IoP-qt

### For Windows users
Windows version will be available soon.

## Address Generation
In order to recevie tokens from the Premined stage, you need to generate an IoP address. Follow this simple steps:

* Open your IoP wallet.
* Go the the **Receive** Tab.
* In the **label** field specify what this address is going to be used for. For example: *PreMined Tokens*
* Click on the **Request Payment** button to generate the address.


Next you need to save this address on the **Fermat Tokens** spreadsheet on Google Drive, by posting a comment in the Token Tracking System tab in column *IM* labelled *IoP Wallet Address* in the row that corresponds to your name.

## Securing your wallet

Securing your address, funds and wallet is a must and priority. In case of computer damage, reinstall or loss you must be able to get your tokens back.

During this initial phase, new IoP Wallet versions will be launched regularly, so you will need to reinstall the wallet often.
Means, **after each new version you must** make a *Wallet Backup*.

### Wallet backup
You can create a backup of your wallet and all your keys by selecting *Backup Wallet* from the *File* menu in your wallet. 
The file you specify, will be used in case you need to restore your wallet.


To be on the safe site and really sure, we want you to make once in the beginning of the use of the IoP app a *Private Key Backup*. This you only need to do once.

### Private Key backup

You backup the initial address you generated for the premine stage, by exporting the private key and put it away.

In order to export the private key, follow these steps:

* Open your wallet.
* Go to *Help* and *Debug Window*
* In the new window that was opened, swtich to *Console* tab.
* White the following command replacing address with the one you want to export:

```
dumpprivkey [address]
```
* The result will be a string that you must keep secure. Write it down and keep it safe. We warn you. You must do this!

You can restore this private key in any other wallet by following the same procedure, but executing the following command and replacing the privKeyString with the real private key you exported before:

```
importprivkey [privKeyString]
```

*** You will only need to import your private key if you delete and uninstall the IoP wallet.***
