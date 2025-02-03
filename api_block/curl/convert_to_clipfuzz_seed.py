import api_block_pb2

import struct
import sys

def add_default_pool_values(integ_bytes, pool_size, bps):
    pool_init_vals = integ_bytes.pool_init_values

    for i in range(bps):
        pool_init_vals.buf_uint8_t_p.add().val = b''

    for i in range(pool_size):
        pool_init_vals._int.add().val = False
        pool_init_vals.curloption.append(api_block_pb2.CURLOPTION.val_CURLOPT_HTTPHEADER)

    return pool_init_vals

def add_default_apib_input(integ_bytes):
    api_block_call = integ_bytes.api_block_call_seq.add()
    api_block_call.api_block_call_num = 0
	
    api_block_call_input = api_block_call.api_block_call_input

    api_block_call_input.in_idx__size_t_0 = 0
    api_block_call_input.out_idx__size_t_0 = 0
    api_block_call_input.in_idx_buf_uint8_t_p_0 = 0
    api_block_call_input.in_idx__int_0 = 0
    api_block_call_input.in_idx__int_1 = 0
    api_block_call_input.out_idx__int_0 = 0
    api_block_call_input.out_idx__int_1 = 0
    api_block_call_input.in_idx_FUZZ_DATA_0 = 0
    api_block_call_input.out_idx_FUZZ_DATA_0 = 0
    api_block_call_input.in_idx_CURLoption_0 = 0
    api_block_call_input.in_idx_CURLoption_1 = 0
    api_block_call_input.in_idx_CURLoption_2 = 0
    api_block_call_input.in_idx_CURLoption_3 = 0
    api_block_call_input.out_idx_CURLoption_0 = 0
    api_block_call_input.out_idx_CURLoption_1 = 0
    api_block_call_input.out_idx_CURLoption_2 = 0
    api_block_call_input.out_idx_CURLoption_3 = 0
    api_block_call_input.in_idx_TLV_0 = 0
    api_block_call_input.out_idx_TLV_0 = 0
    
    return api_block_call


def create_fuzzing_bytes(origin_seed, pool_size, bps):
    integ_bytes = api_block_pb2.FUZZING_BYTES()

    init_values = add_default_pool_values(integ_bytes, pool_size, bps)

    init_values.buf_uint8_t_p[0].val = read_binary_file(origin_seed)
    #init_values.buf_uint8_t_p[0].val = read_binary_file('/mnt/curl_corpus/ossfuzz_max/oss-fuzz-gen-c5ad923ce92551a488992eeb4bf0717d5a894fd9')
    init_values.curloption[0] = api_block_pb2.CURLOPTION.val_CURLOPT_HTTPHEADER
    init_values.curloption[1] = api_block_pb2.CURLOPTION.val_CURLOPT_MAIL_RCPT
    init_values.curloption[2] = api_block_pb2.CURLOPTION.val_CURLOPT_MIMEPOST
    init_values.curloption[3] = api_block_pb2.CURLOPTION.val_CURLOPT_HTTPPOST

    apib_input = add_default_apib_input(integ_bytes)
    apib_input.api_block_call_num = 0

    apib_input = add_default_apib_input(integ_bytes)
    apib_input.api_block_call_num = 1

    apib_input = add_default_apib_input(integ_bytes)
    apib_input.api_block_call_num = 2
    apib_input.api_block_call_input.in_idx_CURLoption_0 = 0
    apib_input.api_block_call_input.in_idx_CURLoption_1 = 1
    apib_input.api_block_call_input.in_idx_CURLoption_2 = 2
    apib_input.api_block_call_input.in_idx_CURLoption_3 = 3

    apib_input = add_default_apib_input(integ_bytes)
    apib_input.api_block_call_num = 3

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
        #print("block:", block)

