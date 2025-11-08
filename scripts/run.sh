#!/bin/bash
set -e
make
if [ -t 0 ]; then
  echo "Usage: echo 'let x = 1;' | ./build/compiler  OR  ./build/compiler < examples/hello.js"
  exit 0
fi
./build/compiler
