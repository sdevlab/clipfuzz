import sys

def gen_seq_driver_from_origin_driver(org_driver,outfile):
    lines = read_file(org_driver)
    new_lines = []
    inside_for_loop = False

    idx = 0
    for i in range(len(lines)):
        l = lines[i]
        if 'for (' in l and 'serialized_bytes.api_block_call_seq_size()' in l:
            inside_for_loop = True

        elif '}' in lines[i-1] and '}' in l:
            inside_for_loop = False

        if inside_for_loop and 'call_api_block' in l:
            new_lines.append('\tprintf("%d ",'+str(idx)+');\n')
            idx = idx+1
        
        else:
            new_lines.append(l)
            
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
