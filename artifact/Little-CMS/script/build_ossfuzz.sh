CXX="clang++-12"
CXXFLAGS="-fno-omit-frame-pointer -gline-tables-only -DFUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION -fsanitize=address -fsanitize-address-use-after-scope -fsanitize=fuzzer-no-link"

$CXX $CFLAGS \
	-I../include \
	./src/ossfuzz_driver.cpp \
	-fsanitize=address,fuzzer \
	../src/.libs/liblcms2.a \
	-o ossfuzz
