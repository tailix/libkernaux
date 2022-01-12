#!/bin/sh

set -e

wget -nc -i 'vendor/wget.txt' -P 'vendor'
sha256sum -c 'vendor/sha256sums.txt'

tar -xf 'vendor/binutils-2.37.tar.xz' -C 'vendor'
tar -xf 'vendor/gcc-11.2.0.tar.xz'    -C 'vendor'
