#!/bin/bash

prefix=`pwd`
pyfixdir="${prefix}/python_hotfix"
pyfixbin="${pyfixdir}/bin/python3.11"

# Build and install custom CPython containing the fix
echo "[-] Build and install custom CPython version with a fix."
CFLAGS="${CFLAGS} -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer"
./configure --with-pydebug --prefix "${pyfixdir}"
make EXTRA_CFLAGS="$CFLAGS" -j
make EXTRA_CFLAGS="$CFLAGS" install
${pyfixbin} -m pip install pyperf