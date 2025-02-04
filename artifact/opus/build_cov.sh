make clean

export SRC=/src \
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



./configure $extra_args --enable-static --disable-shared --disable-doc \
    --enable-assertions
make -j$(nproc)

FUZZERS="opus_multistream_encode_fuzzer"

for fuzzer in $FUZZERS; do
  $CXX $CXXFLAGS -c -Iinclude \
    tests/$fuzzer.cc \
    -o $fuzzer.o

  $CXX $CXXFLAGS \
    $fuzzer.o \
    -o $OUT/${fuzzer}_cov \
    $LIB_FUZZING_ENGINE .libs/libopus.a
done
