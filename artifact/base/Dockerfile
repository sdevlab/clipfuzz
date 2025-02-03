FROM ubuntu:20.04
ENV TERM xterm-256color
ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update && \
    apt-get -y upgrade && \
    apt-get -y install \
    clang-12 make cmake git wget curl tar gdb vim clang-tools-12 \
    python3 python3-pip libprotobuf-dev protobuf-compiler

# Set-up OSS-Fuzz docker image 
RUN ln -sf /usr/bin/clang-12 /usr/bin/clang
RUN ln -sf /usr/bin/clang++-12 /usr/bin/clang++

ENV CC="clang" \
    CXX="clang++"

## Install libFuzzer.a
COPY submodule/llvm-project /llvm-project
RUN apt-get install -y libc++-12-dev libc++abi-12-dev
WORKDIR /llvm-project/compiler-rt/lib/fuzzer
RUN (for f in *.cpp; do clang++ -stdlib=libc++ -fPIC -O2 -std=c++11 $f -c & done && wait) && \
    ar r libFuzzer.a *.o && \
    cp libFuzzer.a /usr/lib

RUN mkdir /src /work /out

# Install GraphFuzz
RUN python3 -m pip install poetry

WORKDIR /graphfuzz
COPY submodule/GraphFuzz/cli /graphfuzz/cli
COPY submodule/GraphFuzz/core /graphfuzz/core
COPY submodule/GraphFuzz/CMakeLists.txt /graphfuzz/CMakeLists.txt

RUN cd /graphfuzz && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make && \
    make install

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

# Install Protobuf
COPY submodule/libprotobuf-mutator /libprotobuf-mutator
WORKDIR /libprotobuf-mutator

ENV CC="clang" \
    CXX="clang++" \
    CCC="clang++" \
    CFLAGS="-O1 -fno-omit-frame-pointer -gline-tables-only -DFUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION -fsanitize=address -fsanitize-address-use-after-scope -fsanitize=fuzzer-no-link" \
    CXXFLAGS="-O1 -fno-omit-frame-pointer -gline-tables-only -DFUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION -fsanitize=address -fsanitize-address-use-after-scope -fsanitize=fuzzer-no-link -stdlib=libc++"

RUN mkdir build && \
    cd build && \
    cmake .. \
         -DCMAKE_C_COMPILER=/usr/bin/clang-12 \
         -DCMAKE_CXX_COMPILER=/usr/bin/clang++-12 \
         -DCMAKE_BUILD_TYPE=Debug -DLIB_PROTO_MUTATOR_DOWNLOAD_PROTOBUF=ON \
         -DCMAKE_VERBOSE_MAKEFILE=ON -DLIBLZMA_INCLUDE_DIR=/usr/include -DLIBLZMA_LIBRARY=/usr/lib/x86_64-linux-gnu/liblzma.so.5 && \
    cd examples/libfuzzer && \
    make all -j12

RUN apt-get install -y screen
