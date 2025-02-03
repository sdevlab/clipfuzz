import api_block_pb2

import struct
import sys

def add_default_pool_values(integ_bytes, pool_size, bps):
    pool_init_vals = integ_bytes.pool_init_values

    for i in range(bps):
        pool_init_vals.buf_unsigned_char_p.add().val = b'' # extended
        pool_init_vals.buf_opus_int16_p.add().val = b''
        pool_init_vals.buf_uint8_t_p.add().val = b''

    for i in range(pool_size):
        pool_init_vals._uint32_t.add().val = 0
        pool_init_vals._opus_int32.add().val = 0
        pool_init_vals._int.add().val = 0
        pool_init_vals._bool.add().val = False

    return pool_init_vals

def add_default_apib_input(integ_bytes):
    api_block_call = integ_bytes.api_block_call_seq.add()
    api_block_call.api_block_call_num = 0

    api_block_call_input = api_block_call.api_block_call_input

    #api_block_call_input.in_idx__opus_int32_0 = 0
    api_block_call_input.in_idx_OpusMSEncoder_p_0 = 0
    api_block_call_input.out_idx_OpusMSEncoder_p_0 = 0
    api_block_call_input.in_idx__uint32_t_0 = 0
    api_block_call_input.in_idx__uint32_t_1 = 0
    api_block_call_input.in_idx__uint32_t_2 = 0
    api_block_call_input.in_idx__uint32_t_3 = 0
    api_block_call_input.in_idx__uint32_t_4 = 0
    api_block_call_input.in_idx__uint32_t_5 = 0
    api_block_call_input.in_idx__uint32_t_6 = 0
    api_block_call_input.in_idx__uint32_t_7 = 0
    api_block_call_input.out_idx__uint32_t_0 = 0
    api_block_call_input.out_idx__uint32_t_1 = 0
    api_block_call_input.out_idx__uint32_t_2 = 0
    api_block_call_input.out_idx__uint32_t_3 = 0
    api_block_call_input.out_idx__uint32_t_4 = 0
    api_block_call_input.out_idx__uint32_t_5 = 0
    api_block_call_input.out_idx__uint32_t_6 = 0
    api_block_call_input.out_idx__uint32_t_7 = 0
    api_block_call_input.in_idx_buf_opus_int16_p_0 = 0
    api_block_call_input.out_idx_buf_opus_int16_p_0 = 0
    api_block_call_input.in_idx_buf_uint8_t_p_0 = 0
    api_block_call_input.in_idx__int_0 = 0
    api_block_call_input.in_idx__int_1 = 0
    api_block_call_input.in_idx__int_2 = 0
    api_block_call_input.in_idx__int_3 = 0
    api_block_call_input.in_idx__int_4 = 0
    api_block_call_input.in_idx__int_5 = 0
    api_block_call_input.out_idx__int_0 = 0
    api_block_call_input.out_idx__int_1 = 0
    api_block_call_input.out_idx__int_2 = 0
    api_block_call_input.out_idx__int_3 = 0
    api_block_call_input.out_idx__int_4 = 0
    api_block_call_input.out_idx__int_5 = 0
    api_block_call_input.in_idx__opus_int32_0 = 0
    api_block_call_input.in_idx__opus_int32_1 = 0
    api_block_call_input.out_idx__opus_int32_0 = 0
    api_block_call_input.out_idx__opus_int32_1 = 0
    api_block_call_input.in_idx_buf_unsigned_char_p_0 = 0
    api_block_call_input.out_idx_buf_unsigned_char_p_0 = 0
    api_block_call_input.in_idx__bool_0 = 0
    api_block_call_input.out_idx__bool_0 = 0


    return api_block_call

def create_fuzzing_bytes (origin_seed, pool_size, bps):
    integ_bytes = api_block_pb2.FUZZING_BYTES()

    init_values = add_default_pool_values(integ_bytes, pool_size, bps)

    init_values._uint32_t[0].val = 117
    init_values._uint32_t[1].val = 1

    init_values._uint32_t[2].val = 37
    init_values._uint32_t[3].val = 7
    init_values._uint32_t[4].val = 2
    init_values._uint32_t[5].val = 2
    init_values._uint32_t[6].val = 4
    init_values._uint32_t[7].val = 2

    init_values._uint32_t[8].val = 2
    init_values._uint32_t[9].val = 4
    init_values._uint32_t[10].val = 12
    init_values._uint32_t[11].val = 8
    init_values._uint32_t[12].val = 2

    init_values._bool[0].val = True
    init_values._bool[1].val = False
    init_values._bool[2].val = True
    init_values._bool[3].val = False
    init_values._bool[4].val = False
    init_values._bool[5].val = True
    init_values._bool[6].val = False


    data = read_binary_file(origin_seed)
    #data = read_binary_file('/mnt/opus_corpus/ossfuzz_high/testvector01.bit')
    rd = data[::-1]
    nb_channels = 117
    mapping = rd[6:7+nb_channels]+bytes(255-nb_channels)

    pcm_size = 280800
    data_size= len(data)
    pcm = data[:pcm_size]
    for i in range(0, 42, 2):
        uint16_value = struct.unpack_from('<h', data, i)[0]
        #print(f'uint16_value[{i // 2}] = {uint16_value}')

    for i in range(pcm_size, pcm_size-40, -2):
        uint16_value = struct.unpack_from('<h', data, i)[0]
        #print(f'uint16_value[{i // 2}] = {uint16_value}')


    init_values.buf_unsigned_char_p[0].val = bytes(1500)
    init_values.buf_uint8_t_p[0].val = mapping
    init_values.buf_uint8_t_p[1].val = pcm

    apib_input = add_default_apib_input(integ_bytes)
    apib_input.api_block_call_num = 0 # driver_31_to_71

    apib_input.api_block_call_input.in_idx_buf_uint8_t_p_0 = 0

    apib_input.api_block_call_input.in_idx__uint32_t_0 = 0
    apib_input.api_block_call_input.out_idx__uint32_t_0 = 0
    apib_input.api_block_call_input.in_idx__uint32_t_1 = 1
    apib_input.api_block_call_input.out_idx__uint32_t_1 = 1
    apib_input.api_block_call_input.in_idx__uint32_t_2 = 2
    apib_input.api_block_call_input.out_idx__uint32_t_2 = 2
    apib_input.api_block_call_input.in_idx__uint32_t_3 = 3
    apib_input.api_block_call_input.out_idx__uint32_t_3 = 3
    apib_input.api_block_call_input.in_idx__uint32_t_4 = 4
    apib_input.api_block_call_input.out_idx__uint32_t_4 = 4
    apib_input.api_block_call_input.in_idx__uint32_t_5 = 5
    apib_input.api_block_call_input.out_idx__uint32_t_5 = 5
    apib_input.api_block_call_input.in_idx__uint32_t_6 = 6
    apib_input.api_block_call_input.out_idx__uint32_t_6 = 6
    apib_input.api_block_call_input.in_idx__uint32_t_7 = 7
    apib_input.api_block_call_input.out_idx__uint32_t_7 = 7

    apib_input.api_block_call_input.in_idx__bool_0 = 0
    apib_input.api_block_call_input.out_idx__bool_0 = 0

    apib_input.api_block_call_input.out_idx__opus_int32_0 = 0
    apib_input.api_block_call_input.out_idx__opus_int32_1 = 1

    apib_input.api_block_call_input.out_idx__int_0 = 0
    apib_input.api_block_call_input.out_idx__int_1 = 1
    apib_input.api_block_call_input.out_idx__int_2 = 2
    apib_input.api_block_call_input.out_idx__int_3 = 3
    apib_input.api_block_call_input.out_idx__int_4 = 4

    apib_input = add_default_apib_input(integ_bytes)
    apib_input.api_block_call_num = 1 # driver_72

    apib_input.api_block_call_input.in_idx__bool_0 = 1
    apib_input.api_block_call_input.out_idx__bool_0 = 1

    apib_input = add_default_apib_input(integ_bytes)
    apib_input.api_block_call_num = 2 # driver_73

    apib_input.api_block_call_input.in_idx__bool_0 = 2
    apib_input.api_block_call_input.out_idx__bool_0 = 2

    apib_input = add_default_apib_input(integ_bytes)
    apib_input.api_block_call_num = 3 # driver_74_to_75

    apib_input.api_block_call_input.in_idx__uint32_t_0 = 8
    apib_input.api_block_call_input.out_idx__uint32_t_0 = 8

    apib_input = add_default_apib_input(integ_bytes)
    apib_input.api_block_call_num = 4 # driver_76_to_80

    apib_input.api_block_call_input.in_idx__uint32_t_0 = 9
    apib_input.api_block_call_input.out_idx__uint32_t_0 = 9

    apib_input = add_default_apib_input(integ_bytes)
    apib_input.api_block_call_num = 5 # driver_81

    apib_input.api_block_call_input.in_idx__bool_0 = 3
    apib_input.api_block_call_input.out_idx__bool_0 = 3

    apib_input = add_default_apib_input(integ_bytes)
    apib_input.api_block_call_num = 6 # driver_82_to_83

    apib_input.api_block_call_input.in_idx__uint32_t_0 = 10
    apib_input.api_block_call_input.out_idx__uint32_t_0 = 10

    apib_input = add_default_apib_input(integ_bytes)
    apib_input.api_block_call_num = 7 # driver_84

    apib_input.api_block_call_input.in_idx__bool_0 = 4
    apib_input.api_block_call_input.out_idx__bool_0 = 4

    apib_input = add_default_apib_input(integ_bytes)
    apib_input.api_block_call_num = 8 # driver_85_to_86

    apib_input.api_block_call_input.in_idx__uint32_t_0 = 11
    apib_input.api_block_call_input.out_idx__uint32_t_0 = 11

    apib_input = add_default_apib_input(integ_bytes)
    apib_input.api_block_call_num = 9 # driver_87_to_88 # XXX

    apib_input.api_block_call_input.in_idx__bool_0 = 5
    apib_input.api_block_call_input.out_idx__bool_0 = 5

    apib_input = add_default_apib_input(integ_bytes)
    apib_input.api_block_call_num = 10 # driver_89_to_91

    apib_input.api_block_call_input.in_idx__uint32_t_0 = 12
    apib_input.api_block_call_input.out_idx__uint32_t_0 = 12

    apib_input = add_default_apib_input(integ_bytes)
    apib_input.api_block_call_num = 11 # driver_92_to_93

    apib_input.api_block_call_input.in_idx__bool_0 = 6
    apib_input.api_block_call_input.out_idx__bool_0 = 6

    apib_input = add_default_apib_input(integ_bytes)
    apib_input.api_block_call_num = 12 # driver_95_to_109

    apib_input.api_block_call_input.in_idx__int_0 = 3
    apib_input.api_block_call_input.out_idx__int_0 = 3

    apib_input.api_block_call_input.in_idx__opus_int32_0 = 0
    apib_input.api_block_call_input.out_idx__opus_int32_0 = 0

    apib_input.api_block_call_input.in_idx_buf_uint8_t_p_0 = 1

    apib_input = add_default_apib_input(integ_bytes)
    apib_input.api_block_call_num = 13 # driver_110

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
