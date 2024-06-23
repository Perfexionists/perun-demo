#!/bin/bash

. cpython_vars.sh

echo "[-] Prepare the ctypes CPython benchmark."
cd ./cmodule
python setup.py build
# Find the built cmodule library, move it to the benchmark dir and rename it
cmodule_path=`find . -name "cmodule.cpython*"`
mv $cmodule_path ../${benchmark_dir}/cmodule-ctypes.so
rm -rf ./build
cd ..