#!/usr/bin/env bash
set -u -e

export NODE_VERSION="6"

# Whether this is needed may somehow depend on the linux platform
#export CXXFLAGS="${CXXFLAGS:-""} -D_GLIBCXX_USE_CXX11_ABI=0"

# Start with a clean path
export PATH=$(getconf PATH)

git clone --depth 1 https://github.com/mapbox/mason.git ./.mason;
export PATH=$(pwd)/.mason:${PATH};
mason install clang++ 3.9.1;
export PATH=$(mason prefix clang++ 3.9.1)/bin:${PATH};
export CXX=clang++-3.9;
export CC=clang-3.9;
export PATH=./node_modules/.bin/:$PATH

# Useful info for debugging
env
$CXX --version
$CC --version

./scripts/build_against_sdk.sh

node-pre-gyp package testpackage
npm test
