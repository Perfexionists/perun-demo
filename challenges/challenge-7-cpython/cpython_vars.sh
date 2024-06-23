#!/bin/bash

prefix=`pwd`
pydir310="${prefix}/python3.10.4"
pybin310="${pydir310}/bin/python3.10"
pydir311="${prefix}/python3.11.0a7"
pybin311="${pydir311}/bin/python3.11"
benchmark_dir="bm_ctypes"
benchmark="${prefix}/${benchmark_dir}/ctypes_benchmark.py"