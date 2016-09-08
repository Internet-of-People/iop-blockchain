Shared Libraries
================

## IoPconsensus

The purpose of this library is to make the verification functionality that is critical to IoP's consensus available to other applications, e.g. to language bindings.

### API

The interface is defined in the C header `IoPconsensus.h` located in  `src/script/IoPconsensus.h`.

#### Version

`IoPconsensus_version` returns an `unsigned int` with the API version *(currently at an experimental `0`)*.

#### Script Validation

`IoPconsensus_verify_script` returns an `int` with the status of the verification. It will be `1` if the input script correctly spends the previous output `scriptPubKey`.

##### Parameters
- `const unsigned char *scriptPubKey` - The previous output script that encumbers spending.
- `unsigned int scriptPubKeyLen` - The number of bytes for the `scriptPubKey`.
- `const unsigned char *txTo` - The transaction with the input that is spending the previous output.
- `unsigned int txToLen` - The number of bytes for the `txTo`.
- `unsigned int nIn` - The index of the input in `txTo` that spends the `scriptPubKey`.
- `unsigned int flags` - The script validation flags *(see below)*.
- `IoPconsensus_error* err` - Will have the error/success code for the operation *(see below)*.

##### Script Flags
- `IoPconsensus_SCRIPT_FLAGS_VERIFY_NONE`
- `IoPconsensus_SCRIPT_FLAGS_VERIFY_P2SH` - Evaluate P2SH ([BIP16](https://github.com/IoP/bips/blob/master/bip-0016.mediawiki)) subscripts
- `IoPconsensus_SCRIPT_FLAGS_VERIFY_DERSIG` - Enforce strict DER ([BIP66](https://github.com/IoP/bips/blob/master/bip-0066.mediawiki)) compliance

##### Errors
- `IoPconsensus_ERR_OK` - No errors with input parameters *(see the return value of `IoPconsensus_verify_script` for the verification status)*
- `IoPconsensus_ERR_TX_INDEX` - An invalid index for `txTo`
- `IoPconsensus_ERR_TX_SIZE_MISMATCH` - `txToLen` did not match with the size of `txTo`
- `IoPconsensus_ERR_DESERIALIZE` - An error deserializing `txTo`

### Example Implementations
- [NIoP](https://github.com/NicolasDorier/NIoP/blob/master/NIoP/Script.cs#L814) (.NET Bindings)
- [node-libIoPconsensus](https://github.com/bitpay/node-libIoPconsensus) (Node.js Bindings)
- [java-libIoPconsensus](https://github.com/dexX7/java-libIoPconsensus) (Java Bindings)
- [IoPconsensus-php](https://github.com/Bit-Wasp/IoPconsensus-php) (PHP Bindings)
