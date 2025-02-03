import sys

api_block_n = int(sys.argv[1])

prefix_str='''
#include <string.h>
#include <string>
#include <iostream>

unsigned long CURR_ID = 0;

extern "C" void __attribute__((visibility ("default"))) global_init(int *argc, char ***argv) {
    char **new_argv = (char **)malloc((*argc + 2) * sizeof(char *));
    memcpy(new_argv, *argv, sizeof(*new_argv) * *argc);
    new_argv[*argc] = (char *)"-detect_leaks=0";
    new_argv[*argc + 1] = 0;
    (*argc)++;
    *argv = new_argv;
}

extern "C" void __attribute__((visibility ("default"))) shim_init() {

}
extern "C" void __attribute__((visibility ("default"))) shim_finalize() {

}
'''

block_f='''
extern "C" void shim_{N} (void **in_ref, void **out_ref, const char *context) {{
    std::cout << "{N} ";
}}
'''

print(prefix_str)
for i in range(api_block_n):
	print(block_f.format(N=str(i)))


print('void __attribute__((visibility ("default"))) (*FUZZER_SHIMS[])(void **, void **, const char *) = {')
for i in range(api_block_n):
	print("    &shim_{N},".format(N=str(i)))
print('};')
