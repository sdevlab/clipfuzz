import api_block_pb2

import struct
import sys

def add_default_pool_values(integ_bytes, pool_size, bps):
    pool_init_vals = integ_bytes.pool_init_values

    for i in range(bps):
        pool_init_vals.buf_uint8_t_p.add().val = b''
        pool_init_vals.buf_std__string.add().val = b''

    for i in range(pool_size):
        pool_init_vals._bool.add().val = False
        pool_init_vals._uint16_t.add().val = 0
        pool_init_vals.re2__options__encoding.append(api_block_pb2.RE2__OPTIONS__ENCODING.val_RE2__Options__EncodingUTF8)

    return pool_init_vals

def add_default_apib_input(integ_bytes):
    api_block_call = integ_bytes.api_block_call_seq.add()
    api_block_call.api_block_call_num = 0
	
    api_block_call_input = api_block_call.api_block_call_input

    api_block_call_input.in_idx_RE2_p_0 = 0
    api_block_call_input.out_idx_RE2_p_0 = 0
    api_block_call_input.in_idx__bool_0 = 0
    api_block_call_input.out_idx__bool_0 = 0
    api_block_call_input.in_idx_RE2__Options_0 = 0
    api_block_call_input.out_idx_RE2__Options_0 = 0
    api_block_call_input.in_idx__uint16_t_0 = 0
    api_block_call_input.out_idx__uint16_t_0 = 0
    api_block_call_input.in_idx_RE2__Options__Encoding_0 = 0
    api_block_call_input.out_idx_RE2__Options__Encoding_0 = 0
    api_block_call_input.in_idx__size_t_0 = 0
    api_block_call_input.out_idx__size_t_0 = 0
    api_block_call_input.in_idx_buf_uint8_t_p_0 = 0
    api_block_call_input.in_idx_buf_std__string_0 = 0
    api_block_call_input.out_idx_buf_std__string_0 = 0
	
    return api_block_call


def create_fuzzing_bytes (origin_seed, pool_size, bps):
    integ_bytes = api_block_pb2.FUZZING_BYTES()

    init_values = add_default_pool_values(integ_bytes, pool_size, bps)

    init_values.buf_uint8_t_p[0].val = read_binary_file(origin_seed)
    #init_values.buf_uint8_t_p[0].val = read_binary_file('/mnt/re2_corpus/ossfuzz_high/high.bin')


    apib_input = add_default_apib_input(integ_bytes)
    apib_input.api_block_call_num = 0 # driver_7_to_10

    apib_input = add_default_apib_input(integ_bytes)
    apib_input.api_block_call_num = 1

    apib_input = add_default_apib_input(integ_bytes)
    apib_input.api_block_call_num = 2

    apib_input = add_default_apib_input(integ_bytes)
    apib_input.api_block_call_num = 3

    apib_input = add_default_apib_input(integ_bytes)
    apib_input.api_block_call_num = 4

    apib_input = add_default_apib_input(integ_bytes)
    apib_input.api_block_call_num = 5

    apib_input = add_default_apib_input(integ_bytes)
    apib_input.api_block_call_num = 6

    apib_input = add_default_apib_input(integ_bytes)
    apib_input.api_block_call_num = 7

    apib_input = add_default_apib_input(integ_bytes)
    apib_input.api_block_call_num = 8

    apib_input = add_default_apib_input(integ_bytes)
    apib_input.api_block_call_num = 9

    apib_input = add_default_apib_input(integ_bytes)
    apib_input.api_block_call_num = 10

    apib_input = add_default_apib_input(integ_bytes)
    apib_input.api_block_call_num = 11

    apib_input = add_default_apib_input(integ_bytes)
    apib_input.api_block_call_num = 12


    return integ_bytes

def save_to_binary_file(message, filename):
    with open(filename, "wb") as f:
        f.write(message.SerializeToString())

def read_binary_file(filename):
    with open(filename, "rb") as f:
        data = f.read()
        return data

def parse_people_message(data):
    fuzzer_message = api_block_pb2.FUZZING_BYTES()
    fuzzer_message.ParseFromString(data)
    return fuzzer_message

if __name__ == "__main__":

    out_name = sys.argv[1]
    origin_seed = sys.argv[2]
    pool_size = int(sys.argv[3])
    buffer_pool_size = int(sys.argv[4])

    #pool_size = 4
    #buffer_pool_size = 1

    fuzzing_bytes = create_fuzzing_bytes(origin_seed, pool_size, buffer_pool_size)
    #out_name=f"v4_high_ps_{pool_size}_buffer_{buffer_pool_size}.bin"
    save_to_binary_file(fuzzing_bytes, out_name)

    # Read the message from the binary file and parse it
    binary_data = read_binary_file(out_name)
    parsed_message = parse_people_message(binary_data)

    for block in parsed_message.api_block_call_seq:
        break
