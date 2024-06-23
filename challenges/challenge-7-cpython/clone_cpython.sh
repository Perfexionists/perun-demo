#!/bin/bash

# ==============================================================================
# Get the current CPython source
echo "[-] Cloning the CPython repo in a treeless mode."
git clone --filter=tree:0 https://github.com/python/cpython.git