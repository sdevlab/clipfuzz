FROM ubuntu:20.04
ENV TERM=xterm-256color
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get -y upgrade && \
    apt-get -y install \
    clang-12 make cmake git wget curl tar gdb vim clang-tools-12 \
    python3 python3-pip libprotobuf-dev protobuf-compiler

RUN ln -sf /usr/bin/clang-12 /usr/bin/clang
RUN ln -sf /usr/bin/clang++-12 /usr/bin/clang++

# Install poetry
RUN python3 -m pip install poetry

WORKDIR /graphfuzz
COPY submodule/GraphFuzz/cli /graphfuzz/cli
COPY submodule/GraphFuzz/core /graphfuzz/core
COPY submodule/GraphFuzz/CMakeLists.txt /graphfuzz/CMakeLists.txt

# Build and install libgraphfuzz
RUN cd /graphfuzz && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make && \
    make install

# Install gfuzz python tool
RUN cd /graphfuzz/cli && \
    poetry build && \
    poetry export > dist/requirements.txt && \
    python3 -m pip install -r dist/requirements.txt && \
    python3 -m pip install ./dist/gfuzz-*.whl

COPY submodule/abseil-cpp /graphfuzz/abseil-cpp
WORKDIR /graphfuzz/abseil-cpp
RUN mkdir build && cd build && \
    cmake -DCMAKE_POSITION_INDEPENDENT_CODE=ON .. && make -j$(nproc) && make install && \
    ldconfig

RUN apt-get install -y pkg-config libgtest-dev

COPY artifact/re2/integrated /graphfuzz/re2/integrated
COPY submodule/libprotobuf-mutator /graphfuzz/re2/integrated/libprotobuf-mutator
WORKDIR /graphfuzz/re2/integrated

RUN cd libprotobuf-mutator && \
    mkdir build && \
    cd build && \
    cmake .. -DCMAKE_C_COMPILER=/usr/bin/clang-12 \
         -DCMAKE_CXX_COMPILER=/usr/bin/clang++-12 \
         -DCMAKE_BUILD_TYPE=Debug -DLIB_PROTO_MUTATOR_DOWNLOAD_PROTOBUF=ON \
         -DCMAKE_VERBOSE_MAKEFILE=ON -DLIBLZMA_INCLUDE_DIR=/usr/include -DLIBLZMA_LIBRARY=/usr/lib/x86_64-linux-gnu/liblzma.so.5 && \
    cd examples/libfuzzer && \
    make all -j12

COPY submodule/re2 /graphfuzz/re2

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
    CXXFLAGS_EXTRA="-stdlib=libc++" \
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

WORKDIR /graphfuzz/re2
RUN make -j$(nproc) && \
    make -j$(nproc) test || true && \
    make -j$(nproc) obj/libre2.a && make common-install

ENV SRC=/src \
    WORK= \
    OUT= \
    FUZZER_LIB= \
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

COPY submodule/re2 /graphfuzz/re2_cov

WORKDIR /graphfuzz/re2_cov
RUN CC=clang-12 CXX=clang++-12 CFLAGS="-g -fprofile-instr-generate -fcoverage-mapping" CXXFLAGS="-g -fprofile-instr-generate -fcoverage-mapping" make -j$(nproc) obj/libre2.a

WORKDIR /graphfuzz/re2
RUN mkdir gfuzz
COPY artifact/re2/header /graphfuzz/re2/gfuzz/header
COPY artifact/re2/script /graphfuzz/re2/gfuzz/script
COPY artifact/re2/src /graphfuzz/re2/gfuzz/src
#COPY artifact/re2/schema.yaml /graphfuzz/re2/gfuzz/schema.yaml

WORKDIR /graphfuzz/re2/gfuzz
RUN pip install protobuf==3.20.0 && \
    protoc --python_out=. src/graph.proto

#RUN ./script/build.sh
RUN ./script/build_ossfuzz.sh

RUN apt-get install -y screen

#RUN cd /graphfuzz/re2/integrated && \
#    ./build.sh

RUN nohup ./script/cleanup.sh &

RUN cd /graphfuzz/re2/integrated && \
    nohup ../gfuzz/script/cleanup.sh &
