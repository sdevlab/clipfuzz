import sys

def gen_seq_driver_from_schema(yaml_file, outfile):
        
    with open(yaml_file, 'r') as file:
        yaml_content = file.read()

    parsed_data = yaml.safe_load(yaml_content)
    api_b_n = 0
    for key, value in parsed_data.items():
        if 'methods' in value:
            n = len(value['methods'])
            api_b_n = api_b_n+n
    
    postfix = ''
    for i in range(api_b_n):

        snippet=f'''
extern "C" void shim_{i}(void **in_ref, void **out_ref, const char *context) {{
    std::cout << \"{i} \";
}}
    \n'''
        postfix += (snippet)

    postfix+='void __attribute__((visibility ("default"))) (*FUZZER_SHIMS[])(void **, void **, const char *) = {\n'

    for i in range(api_b_n):
        postfix += f'    &shim_{i},\n'

    postfix+='};'

    prefix='''
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

}\n
'''
    f = open(outfile, "w")
    f.write(prefix+postfix)
    f.close()

import yaml
        
if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 seq_integ.py <schema>")
        sys.exit(1)
        
    yaml_file = sys.argv[1]
    
    gen_seq_driver_from_schema(yaml_file , "fuzz_seq.cpp")
