sudo checkinstall \
    --install=no \
    --fstrans=yes \
    --type=debian \
    --nodoc \
    --maintainer="$USER\\<$USER@$HOSTNAME\\>" \
    --pkgsource="https://github.com/Fermat-ORG/iop-blockchain" \
    --pkglicense=GPLv3 \
    --pkggroup=net \
    --pkgname=iop-blockchain \
    --pkgversion=0.1 \
    --pkgrelease=beta1 \
    --pkgarch=$(dpkg \
        --print-architecture) \
    --requires="libqt5gui5,libdb5.3++,libqrencode3,libprotobuf9v5,libssl1.0.0,libevent-2.0-5,libevent-pthreads-2.0-5,libboost-program-options1.58.0,libboost-thread1.58.0,libboost-chrono1.58.0" \

