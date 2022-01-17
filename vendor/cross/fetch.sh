#!/bin/sh

set -e

REPO="$(realpath "$(dirname "$(realpath "$0")")")"

cd "$REPO"

SRC="$REPO/src"

wget -nc -i 'wget.txt' -P "$SRC"
sha256sum -c 'sha256sums.txt'

tar -xf "$SRC/binutils-2.37.tar.xz" -C "$SRC"
tar -xf "$SRC/gcc-11.2.0.tar.xz"    -C "$SRC"
