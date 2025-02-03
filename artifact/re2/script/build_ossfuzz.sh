#!/bin/bash

rm ossfuzz_driver
CXX="clang++-12"
CXXFLAGS="-fno-omit-frame-pointer -gline-tables-only -DFUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION -fsanitize=address -fsanitize-address-use-after-scope -fsanitize=fuzzer-no-link"

$CXX $CXXFLAGS -I.. ./src/ossfuzz_driver.cpp -o ossfuzz -fsanitize=address,fuzzer ../obj/libre2.a $(pkg-config re2 --libs | sed -e 's/-lre2//')
