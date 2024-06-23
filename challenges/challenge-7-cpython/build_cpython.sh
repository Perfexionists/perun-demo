#!/bin/bash

. cpython_vars.sh

cd cpython

# We install the Python versions in different directories to allow inspection
# of the results, built binaries, etc.
# The Perun performance management workflow would work just fine even if we
# overwrote the same directory with different Python versions.
# ==============================================================================
# Build and install CPython 3.10.4 with the pyperf module
echo "[-] Build and install CPython v3.10.4."
git checkout v3.10.4
CFLAGS="${CFLAGS} -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer"
./configure --with-pydebug --prefix "${pydir310}"
make EXTRA_CFLAGS="$CFLAGS" -j
make EXTRA_CFLAGS="$CFLAGS" install
${pybin310} -m pip install pyperf

# ==============================================================================
# Build and install CPython 3.11.0a7 with the pyperf module
echo "[-] Build and install CPython v3.11.0a7."
git checkout v3.11.0a7
./configure --with-pydebug --prefix "${pydir311}"
make EXTRA_CFLAGS="$CFLAGS" -j
make EXTRA_CFLAGS="$CFLAGS" install
${pybin311} -m pip install pyperf

# The clean is necessary as otherwise venv searches for python site-packages in
# the cpython directory and not in the venv
make clean

cd ..