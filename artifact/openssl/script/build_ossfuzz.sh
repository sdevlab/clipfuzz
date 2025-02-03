export CXXFLAGS="-O1 -fno-omit-frame-pointer -gline-tables-only -DFUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION -fsanitize=address -fsanitize-address-use-after-scope -fsanitize=fuzzer-no-link -stdlib=libc++"

clang++ ${CXXFLAGS} \
    -I/src/openssl/include  \
    -fno-sanitize=alignment \
    /src/openssl/fuzz/x509-bin-driver.o \
    /src/openssl/fuzz/x509-bin-x509.o \
    -fsanitize=address,fuzzer \
    -stdlib=libc++ \
    -o ossfuzz \
    /src/openssl/libssl.a \
    /src/openssl/libcrypto.a \
    -pthread
