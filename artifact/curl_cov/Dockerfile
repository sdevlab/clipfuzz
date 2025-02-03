FROM graphfuzz_base:latest

# Install CURL
ENV SRC=/src \
    WORK=/work \
    OUT=/out \
    FUZZER_LIB=-fsanitize=fuzzer \
    LIB_FUZZING_ENGINE=-fsanitize=fuzzer \
    FUZZING_ENGINE="libfuzzer" \
    LIB_FUZZING_ENGINE_DEPRECATED=/usr/lib/libFuzzer.a \
    ARCHITECTURE="x86_64r-scope -fsanitize=fuzzer-no-link -fprofile-instr-generate -fcoverage-mapping" \
    CC="clang" \
    CXX="clang++" \
    CCC="clang++" \
    CFLAGS="-O1 -fno-omit-frame-pointer -gline-tables-only -DFUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION -fsanitize=address -fsanitize-address-use-after-scope -fsanitize=fuzzer-no-link -fprofile-instr-generate -fcoverage-mapping" \
    CXXFLAGS="-O1 -fno-omit-frame-pointer -gline-tables-only -DFUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION -fsanitize=address -fsanitize-address-use-after-scope -fsanitize=fuzzer-no-link -fprofile-instr-generate -fcoverage-mapping" \
    CXXFLAGS_EXTRA="" \
    SANITIZER="address" \
    SANITIZER_FLAGS_introspector="-O0 -flto -fno-inline-functions -fuse-ld=gold -Wno-unused-command-line-argument" \
    SANITIZER_FLAGS_address="-fsanitize=address -fsanitize-address-use-after-scope" \
    SANITIZER_FLAGS_memory="-fsanitize=memory -fsanitize-memory-track-origins" \
    UBSAN_OPTIONS="silence_unsigned_overflow=1" \
    SANITIZER_FLAGS_thread="-fsanitize=thread" \
    COVERAGE_FLAGS="-fsanitize=fuzzer-no-link -fprofile-instr-generate -fcoverage-mapping" \
    SANITIZER_FLAGS_undefined="-fsanitize=array-bounds,bool,builtin,enum,float-divide-by-zero,function,integer-divide-by-zero,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,unsigned-integer-overflow,unreachable,vla-bound,vptr -fno-sanitize-recover=array-bounds,bool,builtin,enum,float-divide-by-zero,function,integer-divide-by-zero,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,unreachable,vla-bound,vptr" \
    COVERAGE_FLAGS_coverage="-fprofile-instr-generate -fcoverage-mapping -pthread -Wl,--no-as-needed -Wl,-ldl -Wl,-lm -Wno-unused-command-line-argument" \
    SANITIZER_FLAGS_undefined_aarch64="-fsanitize=array-bounds,bool,builtin,enum,float-divide-by-zero,integer-divide-by-zero,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,unsigned-integer-overflow,unreachable,vla-bound,vptr -fno-sanitize-recover=array-bounds,bool,builtin,enum,float-divide-by-zero,integer-divide-by-zero,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,unreachable,vla-bound,vptr" \
    FUZZER_LDFLAGS="" \
    HWASAN_OPTIONS="random_tags=0" \
    SANITIZER_FLAGS_coverage="" \
    SANITIZER_FLAGS_hwaddress="-fsanitize=hwaddress -fuse-ld=lld -Wno-unused-command-line-argument" \
    DFSAN_OPTIONS="warn_unimplemented=0"

RUN apt-get install -y zip libgnutls28-dev nettle-dev --fix-missing

COPY submodule/curl /src/curl
COPY submodule/curl-fuzzer /src/curl-fuzzer
WORKDIR /src/curl-fuzzer
RUN scripts/ossfuzzdeps.sh && \
    ./ossfuzz.sh

ENV FUZZER_LIB= \
    LIB_FUZZING_ENGINE= \
    FUZZING_ENGINE= \
    LIB_FUZZING_ENGINE_DEPRECATED= \
    ARCHITECTURE= \
    CC= \
    CXX= \
    CCC= \
    CFLAGS= \
    CXXFLAGS= \
    CXXFLAGS_EXTRA= \
    SANITIZER= \
    SANITIZER_FLAGS_introspector= \
    SANITIZER_FLAGS_address= \
    SANITIZER_FLAGS_memory= \
    UBSAN_OPTIONS= \
    SANITIZER_FLAGS_thread= \
    COVERAGE_FLAGS= \
    SANITIZER_FLAGS_undefined= \
    COVERAGE_FLAGS_coverage= \
    SANITIZER_FLAGS_undefined_aarch64= \
    FUZZER_LDFLAGS= \
    HWASAN_OPTIONS= \
    SANITIZER_FLAGS_coverage= \
    SANITIZER_FLAGS_hwaddress= \
    DFSAN_OPTIONS=

# Set-up
WORKDIR /graphfuzz/gfuzz

COPY artifact/curl_cov/header /graphfuzz/gfuzz/header
COPY artifact/curl_cov/script /graphfuzz/gfuzz/script

COPY artifact/curl_cov/src /graphfuzz/gfuzz/src
RUN pip install protobuf==3.20.0 && \
    protoc --python_out=. src/graph.proto

RUN /graphfuzz/gfuzz/script/build_ossfuzz.sh


COPY artifact/curl_cov/integrated /graphfuzz/integrated
RUN mv /libprotobuf-mutator /graphfuzz/integrated/libprotobuf-mutator

RUN apt-get install -y screen
RUN nohup ./script/cleanup.sh &
RUN cd /graphfuzz/integrated && \
    nohup /graphfuzz/gfuzz/script/cleanup.sh &

