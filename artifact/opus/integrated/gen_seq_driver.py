import sys

def gen_seq_driver_from_origin_driver(org_driver,outfile):
    content='''
#include "api_block.pb.h"
#include "libprotobuf-mutator/src/libfuzzer/libfuzzer_macro.h"
#include "port/protobuf.h"
#include "src/libfuzzer/libfuzzer_macro.h"

DEFINE_PROTO_FUZZER_IMPL(true, const FUZZER_BYTES& fuzzer_bytes) {
  FUZZER_BYTES serialized_bytes = (FUZZER_BYTES)fuzzer_bytes;\n
'''

    lines = read_file(org_driver)
    new_lines = []
    inside_for_loop = False

    new_lines.append(content)

    idx = 0
    for i in range(len(lines)):
        l = lines[i]
        if 'for (' in l and 'serialized_bytes.api_block_call_seq_size()' in l:
            inside_for_loop = True
            new_lines.append(l)

        elif inside_for_loop and '};' in lines[i-1] and '}' in l:
            inside_for_loop = False
            new_lines.append(l)

        elif inside_for_loop and 'call_api_block' in l:
            new_lines.append('\tprintf("%d ",'+str(idx)+');\n')
            idx = idx+1
        
        elif inside_for_loop:
            new_lines.append(l)

    new_lines.append('}\n')
            
    #print(''.join(new_lines))
    f = open(outfile, "w")
    f.write(''.join(new_lines))
    f.close()

def read_file(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()
    return lines

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 seq_integ.py <schema>")
        sys.exit(1)
    
    org_driver = sys.argv[1]
    gen_seq_driver_from_origin_driver(org_driver, "seq_driver.cpp")
