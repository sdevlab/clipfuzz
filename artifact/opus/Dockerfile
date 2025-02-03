FROM clipfuzz_base:latest

RUN apt-get update && apt-get install -y make autoconf automake libtool wget
RUN apt-get install -y zip

ENV SRC=/src \
    WORK=/work \
    OUT=/out \
    FUZZER_LIB=-fsanitize=fuzzer \
    LIB_FUZZING_ENGINE=-fsanitize=fuzzer \
    FUZZING_ENGINE="libfuzzer" \
    LIB_FUZZING_ENGINE_DEPRECATED=/usr/lib/libFuzzer.a \
    ARCHITECTURE="x86_64r-scope -fsanitize=fuzzer-no-link" \
    CC="clang" \
    CXX="clang++" \
    CCC="clang++" \
    CFLAGS="-O1 -fno-omit-frame-pointer -gline-tables-only -DFUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION -fsanitize=address -fsanitize-address-use-after-scope -fsanitize=fuzzer-no-link" \
    CXXFLAGS="-O1 -fno-omit-frame-pointer -gline-tables-only -DFUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION -fsanitize=address -fsanitize-address-use-after-scope -fsanitize=fuzzer-no-link" \
    CXXFLAGS_EXTRA="" \
    SANITIZER="address" \
    SANITIZER_FLAGS_introspector="-O0 -flto -fno-inline-functions -fuse-ld=gold -Wno-unused-command-line-argument" \
    SANITIZER_FLAGS_address="-fsanitize=address -fsanitize-address-use-after-scope" \
    SANITIZER_FLAGS_memory="-fsanitize=memory -fsanitize-memory-track-origins" \
    UBSAN_OPTIONS="silence_unsigned_overflow=1" \
    SANITIZER_FLAGS_thread="-fsanitize=thread" \
    COVERAGE_FLAGS="-fsanitize=fuzzer-no-link" \
    SANITIZER_FLAGS_undefined="-fsanitize=array-bounds,bool,builtin,enum,float-divide-by-zero,function,integer-divide-by-zero,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,unsigned-integer-overflow,unreachable,vla-bound,vptr -fno-sanitize-recover=array-bounds,bool,builtin,enum,float-divide-by-zero,function,integer-divide-by-zero,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,unreachable,vla-bound,vptr" \
    COVERAGE_FLAGS_coverage="-fprofile-instr-generate -fcoverage-mapping -pthread -Wl,--no-as-needed -Wl,-ldl -Wl,-lm -Wno-unused-command-line-argument" \
    SANITIZER_FLAGS_undefined_aarch64="-fsanitize=array-bounds,bool,builtin,enum,float-divide-by-zero,integer-divide-by-zero,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,unsigned-integer-overflow,unreachable,vla-bound,vptr -fno-sanitize-recover=array-bounds,bool,builtin,enum,float-divide-by-zero,integer-divide-by-zero,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,unreachable,vla-bound,vptr" \
    FUZZER_LDFLAGS="" \
    HWASAN_OPTIONS="random_tags=0" \
    SANITIZER_FLAGS_coverage="" \
    SANITIZER_FLAGS_hwaddress="-fsanitize=hwaddress -fuse-ld=lld -Wno-unused-command-line-argument" \
    DFSAN_OPTIONS="warn_unimplemented=0"

COPY submodule/opus /src/opus
WORKDIR /src/opus
COPY artifact/opus/build.sh /src/build.sh
COPY artifact/opus/opus_encode_fuzzer.cc /src/opus/tests/
COPY artifact/opus/opus_multistream_decode_fuzzer.cc /src/opus/tests/
COPY artifact/opus/opus_multistream_encode_fuzzer.cc /src/opus/tests/
COPY artifact/opus/opus_projection_decoder_fuzzer.cc /src/opus/tests/
COPY artifact/opus/opus_projection_encoder_fuzzer.cc /src/opus/tests/
COPY artifact/opus/opus_repacketizer_fuzzer.cc /src/opus/tests/
RUN /src/build.sh

RUN cp -a /src/opus /src/opus_cov
COPY artifact/opus/build_cov.sh /src/build_cov.sh
WORKDIR /src/opus_cov
RUN /src/build_cov.sh

##

WORKDIR /graphfuzz/gfuzz
COPY artifact/opus/header /graphfuzz/gfuzz/header
COPY artifact/opus/script /graphfuzz/gfuzz/script
COPY artifact/opus/src /graphfuzz/gfuzz/src
#COPY artifact/opus/schema.yaml /graphfuzz/gfuzz/schema.yaml

RUN pip install protobuf==3.20.0 && \
    protoc --python_out=. src/graph.proto

COPY artifact/opus/integrated /graphfuzz/integrated
#RUN /graphfuzz/opus/gfuzz/script/build.sh

RUN mv /libprotobuf-mutator /graphfuzz/integrated/libprotobuf-mutator
