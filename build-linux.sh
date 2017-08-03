#!/usr/bin/env bash
set -u -e

export NODE_VERSION="6"

export CXXFLAGS="${CXXFLAGS:-""} -D_GLIBCXX_USE_CXX11_ABI=0"

git clone --depth 1 --branch v0.3.0 https://github.com/mapbox/mason.git ./.mason;
export PATH=$(pwd)/.mason:${PATH};
mason install clang 3.8.0;
export PATH=$(mason prefix clang 3.8.0)/bin:${PATH};
export CXX=clang++-3.8;
export CC=clang-3.8;
export PATH=./node_modules/.bin/:$PATH

./scripts/build_against_sdk.sh

node-pre-gyp package testpackage
npm test
