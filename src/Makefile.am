DIST_SUBDIRS = secp256k1 univalue

AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS) $(HARDENED_LDFLAGS)
AM_CXXFLAGS = $(HARDENED_CXXFLAGS)
AM_CPPFLAGS = $(HARDENED_CPPFLAGS)
EXTRA_LIBRARIES =

if EMBEDDED_UNIVALUE
LIBUNIVALUE = univalue/libunivalue.la

$(LIBUNIVALUE): $(wildcard univalue/lib/*) $(wildcard univalue/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)
else
LIBUNIVALUE = $(UNIVALUE_LIBS)
endif

IoP_CONFIG_INCLUDES=-I$(builddir)/config
IoP_INCLUDES=-I$(builddir) -I$(builddir)/obj $(BDB_CPPFLAGS) $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)

IoP_INCLUDES += -I$(srcdir)/secp256k1/include
IoP_INCLUDES += $(UNIVALUE_CFLAGS)

LIBIoP_SERVER=libIoP_server.a
LIBIoP_COMMON=libIoP_common.a
LIBIoP_CONSENSUS=libIoP_consensus.a
LIBIoP_CLI=libIoP_cli.a
LIBIoP_UTIL=libIoP_util.a
LIBIoP_CRYPTO=crypto/libIoP_crypto.a
LIBIoPQT=qt/libIoPqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la

if ENABLE_ZMQ
LIBIoP_ZMQ=libIoP_zmq.a
endif
if BUILD_IoP_LIBS
LIBIoPCONSENSUS=libIoPconsensus.la
endif
if ENABLE_WALLET
LIBIoP_WALLET=libIoP_wallet.a
endif

$(LIBSECP256K1): $(wildcard secp256k1/src/*) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES += \
  $(LIBIoP_CRYPTO) \
  $(LIBIoP_UTIL) \
  $(LIBIoP_COMMON) \
  $(LIBIoP_CONSENSUS) \
  $(LIBIoP_SERVER) \
  $(LIBIoP_CLI) \
  $(LIBIoP_WALLET) \
  $(LIBIoP_ZMQ)

lib_LTLIBRARIES = $(LIBIoPCONSENSUS)

bin_PROGRAMS =
TESTS =
BENCHMARKS =

if BUILD_IoPD
  bin_PROGRAMS += IoPd
endif

if BUILD_IoP_UTILS
  bin_PROGRAMS += IoP-cli IoP-tx
endif

.PHONY: FORCE check-symbols check-security
# IoP core #
IoP_CORE_H = \
  addrman.h \
  base58.h \
  bloom.h \
  blockencodings.h \
  chain.h \
  chainparams.h \
  chainparamsbase.h \
  chainparamsseeds.h \
  checkpoints.h \
  checkqueue.h \
  clientversion.h \
  coincontrol.h \
  coins.h \
  compat.h \
  compat/byteswap.h \
  compat/endian.h \
  compat/sanity.h \
  compressor.h \
  consensus/consensus.h \
  core_io.h \
  core_memusage.h \
  httprpc.h \
  httpserver.h \
  indirectmap.h \
  init.h \
  key.h \
  keystore.h \
  dbwrapper.h \
  limitedmap.h \
  main.h \
  memusage.h \
  merkleblock.h \
  miner.h \
  net.h \
  netbase.h \
  noui.h \
  policy/fees.h \
  policy/policy.h \
  policy/rbf.h \
  pow.h \
  protocol.h \
  random.h \
  reverselock.h \
  rpc/client.h \
  rpc/protocol.h \
  rpc/server.h \
  rpc/register.h \
  scheduler.h \
  script/sigcache.h \
  script/sign.h \
  script/standard.h \
  script/ismine.h \
  streams.h \
  support/allocators/secure.h \
  support/allocators/zeroafterfree.h \
  support/cleanse.h \
  support/pagelocker.h \
  sync.h \
  threadsafety.h \
  timedata.h \
  torcontrol.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  undo.h \
  util.h \
  utilmoneystr.h \
  utiltime.h \
  validationinterface.h \
  versionbits.h \
  wallet/crypter.h \
  wallet/db.h \
  wallet/rpcwallet.h \
  wallet/wallet.h \
  wallet/walletdb.h \
  zmq/zmqabstractnotifier.h \
  zmq/zmqconfig.h\
  zmq/zmqnotificationinterface.h \
  zmq/zmqpublishnotifier.h


obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
libIoP_util_a-clientversion.$(OBJEXT): obj/build.h

# server: shared between IoPd and IoP-qt
libIoP_server_a_CPPFLAGS = $(AM_CPPFLAGS) $(IoP_INCLUDES) $(MINIUPNPC_CPPFLAGS) $(EVENT_CFLAGS) $(EVENT_PTHREADS_CFLAGS)
libIoP_server_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libIoP_server_a_SOURCES = \
  addrman.cpp \
  bloom.cpp \
  blockencodings.cpp \
  chain.cpp \
  checkpoints.cpp \
  httprpc.cpp \
  httpserver.cpp \
  init.cpp \
  dbwrapper.cpp \
  main.cpp \
  merkleblock.cpp \
  miner.cpp \
  net.cpp \
  noui.cpp \
  policy/fees.cpp \
  policy/policy.cpp \
  pow.cpp \
  rest.cpp \
  rpc/blockchain.cpp \
  rpc/mining.cpp \
  rpc/misc.cpp \
  rpc/net.cpp \
  rpc/rawtransaction.cpp \
  rpc/server.cpp \
  script/sigcache.cpp \
  script/ismine.cpp \
  timedata.cpp \
  torcontrol.cpp \
  txdb.cpp \
  txmempool.cpp \
  ui_interface.cpp \
  validationinterface.cpp \
  versionbits.cpp \
  $(IoP_CORE_H)

if ENABLE_ZMQ
libIoP_zmq_a_CPPFLAGS = $(IoP_INCLUDES) $(ZMQ_CFLAGS)
libIoP_zmq_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libIoP_zmq_a_SOURCES = \
  zmq/zmqabstractnotifier.cpp \
  zmq/zmqnotificationinterface.cpp \
  zmq/zmqpublishnotifier.cpp
endif


# wallet: shared between IoPd and IoP-qt, but only linked
# when wallet enabled
libIoP_wallet_a_CPPFLAGS = $(AM_CPPFLAGS) $(IoP_INCLUDES)
libIoP_wallet_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libIoP_wallet_a_SOURCES = \
  wallet/crypter.cpp \
  wallet/db.cpp \
  wallet/rpcdump.cpp \
  wallet/rpcwallet.cpp \
  wallet/wallet.cpp \
  wallet/walletdb.cpp \
  policy/rbf.cpp \
  $(IoP_CORE_H)

# crypto primitives library
crypto_libIoP_crypto_a_CPPFLAGS = $(AM_CPPFLAGS) $(IoP_CONFIG_INCLUDES)
crypto_libIoP_crypto_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libIoP_crypto_a_SOURCES = \
  crypto/aes.cpp \
  crypto/aes.h \
  crypto/common.h \
  crypto/hmac_sha256.cpp \
  crypto/hmac_sha256.h \
  crypto/hmac_sha512.cpp \
  crypto/hmac_sha512.h \
  crypto/ripemd160.cpp \
  crypto/ripemd160.h \
  crypto/sha1.cpp \
  crypto/sha1.h \
  crypto/sha256.cpp \
  crypto/sha256.h \
  crypto/sha512.cpp \
  crypto/sha512.h

# consensus: shared between all executables that validate any consensus rules.
libIoP_consensus_a_CPPFLAGS = $(AM_CPPFLAGS) $(IoP_INCLUDES)
libIoP_consensus_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libIoP_consensus_a_SOURCES = \
  amount.h \
  arith_uint256.cpp \
  arith_uint256.h \
  consensus/merkle.cpp \
  consensus/merkle.h \
  consensus/params.h \
  consensus/validation.h \
  hash.cpp \
  hash.h \
  prevector.h \
  primitives/block.cpp \
  primitives/block.h \
  primitives/transaction.cpp \
  primitives/transaction.h \
  pubkey.cpp \
  pubkey.h \
  script/IoPconsensus.cpp \
  script/interpreter.cpp \
  script/interpreter.h \
  script/script.cpp \
  script/script.h \
  script/script_error.cpp \
  script/script_error.h \
  serialize.h \
  tinyformat.h \
  uint256.cpp \
  uint256.h \
  utilstrencodings.cpp \
  utilstrencodings.h \
  version.h

# common: shared between IoPd, and IoP-qt and non-server tools
libIoP_common_a_CPPFLAGS = $(AM_CPPFLAGS) $(IoP_INCLUDES)
libIoP_common_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libIoP_common_a_SOURCES = \
  amount.cpp \
  base58.cpp \
  chainparams.cpp \
  coins.cpp \
  compressor.cpp \
  core_read.cpp \
  core_write.cpp \
  key.cpp \
  keystore.cpp \
  netbase.cpp \
  protocol.cpp \
  scheduler.cpp \
  script/sign.cpp \
  script/standard.cpp \
  $(IoP_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libIoP_util_a_CPPFLAGS = $(AM_CPPFLAGS) $(IoP_INCLUDES)
libIoP_util_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libIoP_util_a_SOURCES = \
  support/pagelocker.cpp \
  chainparamsbase.cpp \
  clientversion.cpp \
  compat/glibc_sanity.cpp \
  compat/glibcxx_sanity.cpp \
  compat/strnlen.cpp \
  random.cpp \
  rpc/protocol.cpp \
  support/cleanse.cpp \
  sync.cpp \
  util.cpp \
  utilmoneystr.cpp \
  utilstrencodings.cpp \
  utiltime.cpp \
  $(IoP_CORE_H)

if GLIBC_BACK_COMPAT
libIoP_util_a_SOURCES += compat/glibc_compat.cpp
endif

# cli: shared between IoP-cli and IoP-qt
libIoP_cli_a_CPPFLAGS = $(AM_CPPFLAGS) $(IoP_INCLUDES)
libIoP_cli_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libIoP_cli_a_SOURCES = \
  rpc/client.cpp \
  $(IoP_CORE_H)

nodist_libIoP_util_a_SOURCES = $(srcdir)/obj/build.h
#

# IoPd binary #
IoPd_SOURCES = IoPd.cpp
IoPd_CPPFLAGS = $(AM_CPPFLAGS) $(IoP_INCLUDES)
IoPd_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
IoPd_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
IoPd_SOURCES += IoPd-res.rc
endif

IoPd_LDADD = \
  $(LIBIoP_SERVER) \
  $(LIBIoP_COMMON) \
  $(LIBUNIVALUE) \
  $(LIBIoP_UTIL) \
  $(LIBIoP_WALLET) \
  $(LIBIoP_ZMQ) \
  $(LIBIoP_CONSENSUS) \
  $(LIBIoP_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

IoPd_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(MINIUPNPC_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS) $(ZMQ_LIBS)

# IoP-cli binary #
IoP_cli_SOURCES = IoP-cli.cpp
IoP_cli_CPPFLAGS = $(AM_CPPFLAGS) $(IoP_INCLUDES) $(EVENT_CFLAGS)
IoP_cli_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
IoP_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
IoP_cli_SOURCES += IoP-cli-res.rc
endif

IoP_cli_LDADD = \
  $(LIBIoP_CLI) \
  $(LIBUNIVALUE) \
  $(LIBIoP_UTIL) \
  $(LIBIoP_CRYPTO)

IoP_cli_LDADD += $(BOOST_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(EVENT_LIBS)
#

# IoP-tx binary #
IoP_tx_SOURCES = IoP-tx.cpp
IoP_tx_CPPFLAGS = $(AM_CPPFLAGS) $(IoP_INCLUDES)
IoP_tx_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
IoP_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
IoP_tx_SOURCES += IoP-tx-res.rc
endif

IoP_tx_LDADD = \
  $(LIBUNIVALUE) \
  $(LIBIoP_COMMON) \
  $(LIBIoP_UTIL) \
  $(LIBIoP_CONSENSUS) \
  $(LIBIoP_CRYPTO) \
  $(LIBSECP256K1)

IoP_tx_LDADD += $(BOOST_LIBS) $(CRYPTO_LIBS)
#

# IoPconsensus library #
if BUILD_IoP_LIBS
include_HEADERS = script/IoPconsensus.h
libIoPconsensus_la_SOURCES = $(crypto_libIoP_crypto_a_SOURCES) $(libIoP_consensus_a_SOURCES)

if GLIBC_BACK_COMPAT
  libIoPconsensus_la_SOURCES += compat/glibc_compat.cpp
endif

libIoPconsensus_la_LDFLAGS = $(AM_LDFLAGS) -no-undefined $(RELDFLAGS)
libIoPconsensus_la_LIBADD = $(LIBSECP256K1)
libIoPconsensus_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(builddir)/obj -I$(srcdir)/secp256k1/include -DBUILD_IoP_INTERNAL
libIoPconsensus_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)

endif
#

CTAES_DIST =  crypto/ctaes/bench.c
CTAES_DIST += crypto/ctaes/ctaes.c
CTAES_DIST += crypto/ctaes/ctaes.h
CTAES_DIST += crypto/ctaes/README.md
CTAES_DIST += crypto/ctaes/test.c

CLEANFILES = $(EXTRA_LIBRARIES)

CLEANFILES += *.gcda *.gcno
CLEANFILES += compat/*.gcda compat/*.gcno
CLEANFILES += consensus/*.gcda consensus/*.gcno
CLEANFILES += crypto/*.gcda crypto/*.gcno
CLEANFILES += policy/*.gcda policy/*.gcno
CLEANFILES += primitives/*.gcda primitives/*.gcno
CLEANFILES += script/*.gcda script/*.gcno
CLEANFILES += support/*.gcda support/*.gcno
CLEANFILES += univalue/*.gcda univalue/*.gcno
CLEANFILES += wallet/*.gcda wallet/*.gcno
CLEANFILES += wallet/test/*.gcda wallet/test/*.gcno
CLEANFILES += zmq/*.gcda zmq/*.gcno

DISTCLEANFILES = obj/build.h

EXTRA_DIST = $(CTAES_DIST)

clean-local:
	-$(MAKE) -C secp256k1 clean
	-$(MAKE) -C univalue clean
	-rm -f leveldb/*/*.gcda leveldb/*/*.gcno leveldb/helpers/memenv/*.gcda leveldb/helpers/memenv/*.gcno
	-rm -f config.h
	-rm -rf test/__pycache__

.rc.o:
	@test -f $(WINDRES)
	## FIXME: How to get the appropriate modulename_CPPFLAGS in here?
	$(AM_V_GEN) $(WINDRES) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(CPPFLAGS) -DWINDRES_PREPROC -i $< -o $@

.mm.o:
	$(AM_V_CXX) $(OBJCXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	  $(CPPFLAGS) $(AM_CXXFLAGS) $(QT_INCLUDES) $(AM_CXXFLAGS) $(PIE_FLAGS) $(CXXFLAGS) -c -o $@ $<

check-symbols: $(bin_PROGRAMS)
if GLIBC_BACK_COMPAT
	@echo "Checking glibc back compat..."
	$(AM_V_at) READELF=$(READELF) CPPFILT=$(CPPFILT) $(top_srcdir)/contrib/devtools/symbol-check.py < $(bin_PROGRAMS)
endif

check-security: $(bin_PROGRAMS)
if HARDEN
	@echo "Checking binary security..."
	$(AM_V_at) READELF=$(READELF) OBJDUMP=$(OBJDUMP) $(top_srcdir)/contrib/devtools/security-check.py < $(bin_PROGRAMS)
endif

%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(<D) $<

if EMBEDDED_LEVELDB
include Makefile.leveldb.include
endif

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_BENCH
include Makefile.bench.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
