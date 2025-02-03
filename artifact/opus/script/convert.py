import sys
sys.path.append('/graphfuzz/opus/gfuzz/src')

import graph_pb2

def consume_integral_in_range(data, _min, _max):
    return (int.from_bytes(data, 'little') % ((_max-_min)+1)) + _min

def create_graph(graph, node_idx, _type, _layer, _in_ref, _out_ref, _context):
    node_a = graph.nodes.add()
    node_a.index = node_idx
    node_a.type = _type
    node_a.layer = _layer
    if _in_ref is not None:
        node_a.in_ref.add(node_idx=_in_ref[0], conn_idx=_in_ref[1])
    if _out_ref is not None:
        node_a.out_ref.add(node_idx=_out_ref[0], conn_idx=_out_ref[1])
    if _context is not None:
        node_a.context = _context

def main():
    if len(sys.argv) < 2:
        print("python3 ./gen.py BYTE_FILE")
        sys.exit(0)
    seed_fp = open(sys.argv[1], 'rb')
    node_idx = 0
    graph = graph_pb2.Graph()
    data = seed_fp.read()
    rd = data[::-1]
    #for i in range(6,50):
        #print(f"ch[",i,"]:", rd[i])

    nb_channels = consume_integral_in_range(rd[0:1], 0, 255)
    #print("nb_channels:",nb_channels)
    frame_size_ms_x2 = consume_integral_in_range(rd[4:5], 0, 8)
    #print("frame_size_ms_x2:",frame_size_ms_x2)
    application = consume_integral_in_range(rd[5:6], 0, 2)
    #print("application:",application)
    BOOL = consume_integral_in_range(rd[nb_channels+6:nb_channels+7], 0, 1)
    #print("CONSUME_BOOL:", BOOL)
    if BOOL:
        map_f = consume_integral_in_range(rd[nb_channels+7:nb_channels+8], 0, 4)
        #print("map_f:", map_f)
        context_0 = rd[0:4]+rd[5:6+nb_channels]+bytes(255-nb_channels)+rd[nb_channels+7:nb_channels+8]
        create_graph(graph, 0, 1, 0, None, (1,0), context_0)
        idx = nb_channels+8
    else:
        context_0 = rd[0:4]+rd[5:6+nb_channels]+bytes(255-nb_channels)
        create_graph(graph, 0, 0, 0, None, (1,0), context_0)
        idx = nb_channels+7
    create_graph(graph, 1, 4, 1, (0,0), (2,0), rd[idx:idx+1]) #OPUS_SET_COMPLEXITY######
    #print("OPUS_SET_COMPLEXITY:", consume_integral_in_range(rd[idx:idx+1], 0, 10))
    idx = idx+1
    create_graph(graph, 2, 5, 1, (1,0), (3,0), rd[idx:idx+1]) #OPUS_SET_VBR
    #print("OPUS_SET_VBR:", consume_integral_in_range(rd[idx:idx+1], 0, 1))
    idx = idx+1
    create_graph(graph, 3, 6, 1, (2,0), (4,0), rd[idx:idx+1]) #OPUS_SET_VBR_CONSTRAINT
    #print("OPUS_SET_VBR_CONSTRAINT:", consume_integral_in_range(rd[idx:idx+1], 0, 1))
    idx = idx+1
    create_graph(graph, 4, 7, 1, (3,0), (5,0), rd[idx:idx+1]) #OPUS_SET_FORCE_CHANNELS
    #print("OPUS_SET_FORCE_CHANNELS:", consume_integral_in_range(rd[idx:idx+1], 0, 2))
    idx = idx+1
    create_graph(graph, 5, 8, 1, (4,0), (6,0), rd[idx:idx+1]) #OPUS_SET_MAX_BANDWIDTH
    #print("OPUS_SET_MAX_BANDWIDTH:", consume_integral_in_range(rd[idx:idx+1], 0, 4))
    idx = idx+1
    create_graph(graph, 6, 9, 1, (5,0), (7,0), rd[idx:idx+1]) #OPUS_SET_INBAND_FEC
    #print("OPUS_SET_INBAND_FEC:", consume_integral_in_range(rd[idx:idx+1], 0, 1))
    idx = idx+1
    create_graph(graph, 7, 10, 1, (6,0), (8,0), rd[idx:idx+1]) #OPUS_SET_PACKET_LOSS_PERC
    #print("OPUS_SET_PACKET_LOSS_PERC:", consume_integral_in_range(rd[idx:idx+1], 0, 100))
    idx = idx+1
    create_graph(graph, 8, 11, 1, (7,0), (9,0), rd[idx:idx+1]) #OPUS_SET_DTX
    #print("OPUS_SET_DTX:", consume_integral_in_range(rd[idx:idx+1], 0, 1))
    idx = idx+1
    create_graph(graph, 9, 12, 1, (8,0), (10,0), rd[idx:idx+1]) #OPUS_SET_LSB_DEPTH
    #print("OPUS_SET_LSB_DEPTH:", consume_integral_in_range(rd[idx:idx+1], 8, 24))
    idx = idx+1
    create_graph(graph, 10, 13, 1, (9,0), (11,0), rd[idx:idx+1]) #OPUS_SET_PREDICTION_DISABLED
    #print("OPUS_SET_PREDICTION_DISABLED:", consume_integral_in_range(rd[idx:idx+1], 0,1))
    idx = idx+1
    create_graph(graph, 11, 14, 1, (10,0), (12,0), rd[idx:idx+1]) #OPUS_SET_SIGNAL
    #print("OPUS_SET_SIGNAL:", consume_integral_in_range(rd[idx:idx+1], 0, 2))
    idx = idx+1
    create_graph(graph, 12, 15, 1, (11,0), (13,0), rd[idx:idx+1]) #OPUS_SET_PHASE_INVERSION_DISABLED
    #print("OPUS_SET_PHASE_INVERSION_DISABLED:", consume_integral_in_range(rd[idx:idx+1],0,1))
    idx = idx+1
    remain_n = len(data)-idx
    plus = bytes(0)
    TEST_INPUT_MAX_SIZE = 100000
    if remain_n < TEST_INPUT_MAX_SIZE:
        plus = bytes(TEST_INPUT_MAX_SIZE-remain_n)
    #print("TEST_INPUT_MAX_SIZE:", TEST_INPUT_MAX_SIZE);
    #print("remain_n:",remain_n,"plus:",len(plus))

    context_1 = rd[4:5]+remain_n.to_bytes(4,'little')+data[:remain_n]+plus
    #print("len(context_1):",len(context_1))

    create_graph(graph, 13, 3, 1, (12,0), (14,0), context_1)
    create_graph(graph, 14, 2, 2, (13,0), None, None)

    with open('output_graph.bin', 'wb') as file:
        file.write(graph.SerializeToString())
    #print("Graph has been serialized and saved to 'output_graph.bin'.")

if __name__ == "__main__":
    main()
