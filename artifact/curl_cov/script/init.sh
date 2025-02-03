cd /graphfuzz/curl_fuzzer/
/graphfuzz/curl_fuzzer/scripts/ossfuzzdeps.sh

export LD_LIBRARY_PATH=/usr/lib/llvm-12/lib:$LD_LIBRARY_PATH

export BUILD_ROOT=/graphfuzz/curl_fuzzer
SCRIPTDIR=${BUILD_ROOT}/scripts

. ${SCRIPTDIR}/fuzz_targets

ZLIBDIR=/graphfuzz/zlib
OPENSSLDIR=/graphfuzz/openssl
NGHTTPDIR=/graphfuzz/nghttp2

export MAKEFLAGS="-j$(nproc)"

export INSTALLDIR=/graphfuzz/curl_install

${SCRIPTDIR}/handle_x.sh zlib ${ZLIBDIR} ${INSTALLDIR}
${SCRIPTDIR}/handle_x.sh nghttp2 ${NGHTTPDIR} ${INSTALLDIR}
${SCRIPTDIR}/install_curl.sh /graphfuzz/curl ${INSTALLDIR}

sed -i '/uint32_t to_u32/i\#INSERT_HERE_1' ${BUILD_ROOT}/curl_fuzzer.cc
sed -i '/extern "C" int LLVMFuzzerTestOneInput/,/#INSERT_HERE_1/!p;d' ${BUILD_ROOT}/curl_fuzzer.cc
sed -i'' -r '/make \|\|/i\make libstandaloneengine.a' ${SCRIPTDIR}/compile_fuzzer.sh

sed -i '30,31d' ${SCRIPTDIR}/compile_fuzzer.sh
${SCRIPTDIR}/compile_fuzzer.sh ${INSTALLDIR}
make curl_fuzzer_http-curl_fuzzer.o
make curl_fuzzer_http-curl_fuzzer_tlv.o
make curl_fuzzer_http-curl_fuzzer_callback.o
