#!/bin/bash -ex
# Copyright 2020 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


export SRC=/src
export WORK=/work
export OUT=/out

export FUZZER_LIB=-fsanitize=fuzzer
export LIB_FUZZING_ENGINE=-fsanitize=fuzzer
export FUZZING_ENGINE="libfuzzer"
export LIB_FUZZING_ENGINE_DEPRECATED=/usr/lib/libFuzzer.a
export ARCHITECTURE="x86_64r-scope -fsanitize=fuzzer-no-link -stdlib=libc++ -fprofile-instr-generate -fcoverage-mapping"

export CC="clang"
export CXX="clang++"
export CCC="clang++"
export CFLAGS="-O1 -fno-omit-frame-pointer -gline-tables-only -DFUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION -fsanitize=address -fsanitize-address-use-after-scope -fsanitize=fuzzer-no-link -fprofile-instr-generate -fcoverage-mapping"
export CXXFLAGS="-O1 -fno-omit-frame-pointer -gline-tables-only -DFUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION -fsanitize=address -fsanitize-address-use-after-scope -fsanitize=fuzzer-no-link -fprofile-instr-generate -fcoverage-mapping -I/usr/lib/llvm-12/include/c++/v1 -stdlib=libc++"
export CXXFLAGS_EXTRA="-stdlib=libc++"
export SANITIZER="address"
export SANITIZER_FLAGS_introspector="-O0 -flto -fno-inline-functions -fuse-ld=gold -Wno-unused-command-line-argument"
export SANITIZER_FLAGS_address="-fsanitize=address -fsanitize-address-use-after-scope"
export SANITIZER_FLAGS_memory="-fsanitize=memory -fsanitize-memory-track-origins"
export UBSAN_OPTIONS="silence_unsigned_overflow=1"
export SANITIZER_FLAGS_thread="-fsanitize=thread"
export COVERAGE_FLAGS="-fsanitize=fuzzer-no-link -fprofile-instr-generate -fcoverage-mapping"
export SANITIZER_FLAGS_undefined="-fsanitize=array-bounds,bool,builtin,enum,float-divide-by-zero,function,integer-divide-by-zero,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,unsigned-integer-overflow,unreachable,vla-bound,vptr -fno-sanitize-recover=array-bounds,bool,builtin,enum,float-divide-by-zero,function,integer-divide-by-zero,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,unreachable,vla-bound,vptr"
export COVERAGE_FLAGS_coverage="-fprofile-instr-generate -fcoverage-mapping -pthread -Wl,--no-as-needed -Wl,-ldl -Wl,-lm -Wno-unused-command-line-argument"
export SANITIZER_FLAGS_undefined_aarch64="-fsanitize=array-bounds,bool,builtin,enum,float-divide-by-zero,integer-divide-by-zero,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,unsigned-integer-overflow,unreachable,vla-bound,vptr -fno-sanitize-recover=array-bounds,bool,builtin,enum,float-divide-by-zero,integer-divide-by-zero,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,unreachable,vla-bound,vptr"
export FUZZER_LDFLAGS=""
export HWASAN_OPTIONS="random_tags=0"
export SANITIZER_FLAGS_coverage=""
export SANITIZER_FLAGS_hwaddress="-fsanitize=hwaddress -fuse-ld=lld -Wno-unused-command-line-argument"
export DFSAN_OPTIONS="warn_unimplemented=0"


# Do this here because the original python3.8 gets clobbered.
apt-get update && apt-get install python3 python3-pip -y

# This library can end up being linked to the fuzzer but it is not in the
# runner Dockerfile.
apt-get remove -y libfreetype6

python3.8 -m pip install ninja meson==0.56.0

# Disable:
# 1. UBSan vptr since target built with -fno-rtti.
export CFLAGS="$CFLAGS -fno-sanitize=vptr -DHB_NO_VISIBILITY"
export CXXFLAGS="$CXXFLAGS -fno-sanitize=vptr -DHB_NO_VISIBILITY"

# setup
build=$WORK/build_cov

# cleanup
rm -rf $build
mkdir -p $build

# Build the library.
meson --default-library=static --wrap-mode=nodownload \
      -Dexperimental_api=true \
      -Dfuzzer_ldflags="$(echo $LIB_FUZZING_ENGINE)" \
      $build \
  || (cat build/meson-logs/meson-log.txt && false)

# Build the fuzzers.
ninja -v -j$(nproc) -C $build test/fuzzing/hb-shape-fuzzer
mv $build/test/fuzzing/hb-shape-fuzzer $OUT/hb-shape-fuzzer_cov

# Archive and copy to $OUT seed corpus if the build succeeded.
#mkdir all-fonts
#for d in \
    #test/shape/data/in-house/fonts \
    #test/shape/data/aots/fonts \
    #test/shape/data/text-rendering-tests/fonts \
    #test/api/fonts \
    #test/fuzzing/fonts \
    #perf/fonts \
    #; do
    #cp $d/* all-fonts/
#done

#mkdir $OUT/seeds
#cp all-fonts/* $OUT/seeds/
