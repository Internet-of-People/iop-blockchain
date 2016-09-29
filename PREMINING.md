#IoP Blockchain

## Wallet Instalation
In order to install the IoP Wallet that will allow you to send and recieve IoPs you need to follow this procedure:

### For Ubuntu users
Follow the instructions to install here http://repo.fermat.community/index.html

After installation is complete, start the IoP wallet by running **IoP-qt** from the command line.

```
$ IoP-qt
```



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

Securing your address, funds and wallet must be a priority. In case of computer damage, reinstall or loss you must be able to get your tokens back.

### Wallet backup
You can create a backup of your wallet and all your keys by selecting *Backup Wallet* from the *File* menu in your wallet. 

The file you specify, will be used in case you need to restore your wallet.

### Private Key backup
During this initial phase, new IoP Wallet version will be launched regularly, so you will need to reinstall the wallet often.
You can just backup the address you generated for the premine stage, by exporting the private key.

In order to export the private key, follow these steps:

* Open your wallet.
* Go to *Help* and *Debug Window*
* In the new window that was opened, swtich to *Console* tab.
* White the following command replacing address with the one you want to export:

```
dumpprivkey [address]
```
* The result will be a string that you must keep secure. Write it down and keep it safe.

You can restore this private key in another wallet by following the same procedure, but executing the following command and replacing the privKeyString with the real private key you exported before:

```
importprivkey [privKeyString]
```

** You will only need to import your private key if you delete and uninstall the IoP wallet.**


### Time locked funds

Certain amount of shares will be send using a time constrained transaction. meaning that those **IoPs** won't be available to be spent after certain date.

The time constrains that are applied on the *Fermat Token* spreadsheet are:

* 6 months
* 1 year
* 2 years
* 4 years
* 5 years

---

** Important: The constraint start from the date the distribution was executed, and it is up to the IoP owner to claim these funds after that date. **

---

You can **Wath-only** this IoP coins in your wallet by importing a IoP address that was automatically generated during the execution of the distribution.

You can view your addresses for each date in the [PreMining Distribution Output](https://docs.google.com/spreadsheets/d/1NafNFjKbBl-RCeh7wLoDGeZqSGnAFvIPciGbEdmmSZk/edit?usp=sharing) 


In order to import your address, do the following:

* Open your wallet.
* Go to *Help* menu and *Debug Window*
* Go to *Console* tab and execute the following command

```
importaddress [address from Columm B] [Label from column D]
```

For example, for this row:

|Name|Address|IoPs|TimeConstraint|RedeemScript|
|---|---|---|---|---|
|Rodrigo Acosta |2DHTYYgTDRWnKgEYZfJ4twBbxQeLNZ1rTY1|1465,930962|1 year|0800000157768bdce6b17576a914460eb1ec408c4c3a204eb04841cd9f86f1936f4c88ac|
|Rodrigo Acosta |2DB9f5vMS4Eu8dJPEoy55nCZtmxRbrUoXjk|1465,930962|2 years|080000015776c2cb66b17576a914460eb1ec408c4c3a204eb04841cd9f86f1936f4c88ac|

The commands to execute would be:

```
importaddress 2DHTYYgTDRWnKgEYZfJ4twBbxQeLNZ1rTY1 "1 year"
importaddress 2DB9f5vMS4Eu8dJPEoy55nCZtmxRbrUoXjk "2 years"
```

(The RedeemScript will be discussed later.)
