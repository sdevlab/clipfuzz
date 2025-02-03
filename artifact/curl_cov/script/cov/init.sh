cd /graphfuzz/curl_fuzzer/

export LD_LIBRARY_PATH=/usr/lib/llvm-12/lib:$LD_LIBRARY_PATH

export BUILD_ROOT=/src/curl_fuzzer
SCRIPTDIR=${BUILD_ROOT}/scripts

. ${SCRIPTDIR}/fuzz_targets

ZLIBDIR=/src/zlib
OPENSSLDIR=/src/openssl
NGHTTPDIR=/src/nghttp2

export MAKEFLAGS="-j$(nproc)"

export INSTALLDIR=/src/curl_install_cov

${SCRIPTDIR}/handle_x.sh zlib ${ZLIBDIR} ${INSTALLDIR}
${SCRIPTDIR}/handle_x.sh nghttp2 ${NGHTTPDIR} ${INSTALLDIR}
/graphfuzz/gfuzz/script/cov/install_curl.sh /src/curl ${INSTALLDIR}

/graphfuzz/gfuzz/script/cov/compile_fuzzer.sh ${INSTALLDIR}
