#!/bin/bash

# If any commands fail, fail the script immediately.
set -ex

# Exit if the build root has not been defined.
[[ -d ${BUILD_ROOT} ]] || exit 1

# Parse the options.
OPTIND=1
CODE_COVERAGE_OPTION=""

while getopts "c" opt
do
        case "$opt" in
                c) CODE_COVERAGE_OPTION="--enable-code-coverage"
           ;;
    esac
done
shift $((OPTIND-1))

# Check that the installation directory exists.
export INSTALLDIR=$1
[[ -d ${INSTALLDIR} ]] || exit 1

# Build the fuzzers.
${BUILD_ROOT}/buildconf || exit 2
make clean
CC=clang-12 CXX=clang++-12 CFLAGS="-fprofile-instr-generate -fcoverage-mapping" CXXFLAGS="-fprofile-instr-generate -fcoverage-mapping" ${BUILD_ROOT}/configure ${CODE_COVERAGE_OPTION} || exit 3
CC=clang-12 CXX=clang++-12 CFLAGS="-fprofile-instr-generate -fcoverage-mapping" CXXFLAGS="-fprofile-instr-generate -fcoverage-mapping" make libstandaloneengine.a -j12

CC=clang-12 CXX=clang++-12 CFLAGS="-fprofile-instr-generate -fcoverage-mapping" CXXFLAGS="-fprofile-instr-generate -fcoverage-mapping" make curl_fuzzer_http-curl_fuzzer.o
CC=clang-12 CXX=clang++-12 CFLAGS="-fprofile-instr-generate -fcoverage-mapping" CXXFLAGS="-fprofile-instr-generate -fcoverage-mapping" make curl_fuzzer_http-curl_fuzzer_tlv.o
CC=clang-12 CXX=clang++-12 CFLAGS="-fprofile-instr-generate -fcoverage-mapping" CXXFLAGS="-fprofile-instr-generate -fcoverage-mapping" make curl_fuzzer_http-curl_fuzzer_callback.o
