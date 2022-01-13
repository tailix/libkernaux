#!/bin/sh

set -e

ARCH='riscv64'
TARGET="$ARCH-elf"
REPO="$(pwd)"
PREFIX="$REPO/vendor/cross"
PATH="$PREFIX/bin:$PATH"

if [ -z "$J" ]; then J='1'; fi

cd "$REPO/vendor/cross/build/$ARCH/binutils"
../../../../binutils-2.37/configure --target="$TARGET" --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make -j"$J"
make install

cd "$REPO/vendor/cross/build/$ARCH/gcc"
../../../../gcc-11.2.0/configure --target="$TARGET" --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make -j"$J" all-gcc all-target-libgcc
make install-gcc install-target-libgcc
