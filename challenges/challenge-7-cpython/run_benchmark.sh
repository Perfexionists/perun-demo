#!/bin/bash

. cpython_vars.sh

# ==============================================================================
echo "[-] Run the ctypes benchmark in CPython v3.10.4."
${pybin310} ${benchmark}

# ==============================================================================
echo "[-] Run the ctypes benchmark in CPython v3.11.0a7."
${pybin311} ${benchmark}