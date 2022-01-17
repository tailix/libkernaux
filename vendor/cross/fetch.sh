#!/bin/sh

set -e

REPO="$(realpath "$(dirname "$(realpath "$0")")")"

cd "$REPO"

wget -nc -i 'wget.txt'
sha256sum -c 'sha256sums.txt'

tar -xf 'binutils-2.37.tar.xz'
tar -xf 'gcc-11.2.0.tar.xz'
