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

SRCDIR=$1
INSTALLDIR=$2

if [[ ! -d ${INSTALLDIR} ]]
then
  # Make an install target for curl.
  mkdir ${INSTALLDIR}
fi

if [[ -f ${INSTALLDIR}/lib/libssl.a ]]
then
  SSLOPTION=--with-ssl=${INSTALLDIR}
else
  SSLOPTION=--without-ssl
fi

if [[ -f ${INSTALLDIR}/lib/libnghttp2.a ]]
then
  NGHTTPOPTION=--with-nghttp2=${INSTALLDIR}
else
  NGHTTPOPTION=--without-nghttp2
fi

pushd ${SRCDIR}

# Build the library.
./buildconf
CC=clang-12 CXX=clang++-12 CFLAGS="-fprofile-instr-generate -fcoverage-mapping" CXXFLAGS="-fprofile-instr-generate -fcoverage-mapping" ./configure --prefix=${INSTALLDIR} \
            --disable-shared \
            --enable-debug \
            --enable-maintainer-mode \
            --disable-symbol-hiding \
            --enable-ipv6 \
            --enable-websockets \
            --without-libpsl \
            --with-random=/dev/null \
            ${SSLOPTION} \
            ${NGHTTPOPTION} \
            ${CODE_COVERAGE_OPTION}

CC=clang-12 CXX=clang++-12 CFLAGS="-fprofile-instr-generate -fcoverage-mapping" CXXFLAGS="-fprofile-instr-generate -fcoverage-mapping" make V=1 -j12
CC=clang-12 CXX=clang++-12 CFLAGS="-fprofile-instr-generate -fcoverage-mapping" CXXFLAGS="-fprofile-instr-generate -fcoverage-mapping" make install

# Make any explicit folders which are post install
UTFUZZDIR=${INSTALLDIR}/utfuzzer
mkdir -p ${UTFUZZDIR}

# Copy header files.
cp -v lib/curl_fnmatch.h ${UTFUZZDIR}
cp -v lib/bufq.h ${UTFUZZDIR}
touch ${UTFUZZDIR}/curl_setup.h

popd
