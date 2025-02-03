import sys
import struct

sys.path.append('/graphfuzz/gfuzz/src')
import graph_pb2

def consume_integral_in_range(data, _min, _max):
    return (int.from_bytes(data, 'little') % ((_max-_min)+1)) + _min

def create_graph(graph, node_idx, _type, _layer, _in_refs, _out_refs, _context):
    node_a = graph.nodes.add()
    node_a.index = node_idx
    node_a.type = _type
    node_a.layer = _layer
    if _in_refs is not None:
        for _in_ref in _in_refs:
            node_a.in_ref.add(node_idx=_in_ref[0], conn_idx=_in_ref[1])
    if _out_refs is not None:
        for _out_ref in _out_refs:
            node_a.out_ref.add(node_idx=_out_ref[0], conn_idx=_out_ref[1])
    if _context is not None:
        node_a.context = _context

def main():

    out_name = sys.argv[1]
    origin_seed = sys.argv[2]

    seed_fp = open(origin_seed, 'rb')
    #seed_fp = open('/mnt/opus_corpus/ossfuzz_high/testvector01.bit', 'rb')
    node_idx = 0
    graph = graph_pb2.Graph()
    data = seed_fp.read()
    rd = data[::-1]

    pcm_size = 280800
    buf = data[:pcm_size]
    remain = bytes(1048576 - pcm_size)

    nb_channels = 117
    frequency = 1
    streams = 37
    coupled_streams = 163
    frame_size_ms_x2 = 7
    application = 2

    mapping = rd[6:7+nb_channels]+bytes(255-nb_channels)

    t0 = 1
    mapping_family = 4
    OPUS_SET_COMPLEXITY = 2
    OPUS_SET_VBR = 0
    OPUS_SET_VBR_CONSTRAINT = 1
    OPUS_SET_FORCE_CHANNELS = 2
    OPUS_SET_MAX_BANDWIDTH = 4
    OPUS_SET_INBAND_FEC = 0

    OPUS_SET_PACKET_LOSS_PERC = 12
    OPUS_SET_DTX = 0
    OPUS_SET_LSB_DEPTH = 8
    OPUS_SET_PREDICTION_DISABLED = 1

    OPUS_SET_SIGNAL = 2
    OPUS_SET_PHASE_INVERSION_DISABLED = 0


    context_bytes = \
            struct.pack('B', nb_channels) + \
            struct.pack('B', frequency) + \
            struct.pack('B', streams) + \
            struct.pack('B', coupled_streams) + \
            struct.pack('B', frame_size_ms_x2) + \
            struct.pack('B', application) + \
            struct.pack('B', t0) + \
            struct.pack('B', mapping_family) + \
            struct.pack('B', OPUS_SET_COMPLEXITY)

    create_graph(graph, 0, 0, 0, None, [(5,0)], None) # Encoder
    create_graph(graph, 1, 23, 0, None, [(17,3)], buf+remain+len(buf).to_bytes(4,'little')) # Wrapper_data_0
    create_graph(graph, 2, 25, 0, None, [(5,3)], mapping+len(mapping).to_bytes(4,'little')) # Wrapper_data_1
    create_graph(graph, 3, 27, 0, None, [(5,1)], int(0).to_bytes(1,'little')) # Wrapper_int
    create_graph(graph, 4, 27, 0, None, [(5,2)], int(0).to_bytes(1,'little')) # Wrapper_int

    create_graph(graph, 5, 1, 1, [(0,0),(3,0),(4,0),(2,0)], [(6,0),(17,1),(17,2),(20,0)], context_bytes) # Encoder, Wrapper_int, Wrapper_int, Wrapper_data_1

    create_graph(graph, 6, 2, 1, [(5,0)], [(7,0)], OPUS_SET_VBR.to_bytes(1,'little'))
    create_graph(graph, 7, 3, 1, [(6,0)], [(8,0)], OPUS_SET_VBR_CONSTRAINT.to_bytes(1,'little'))
    create_graph(graph, 8, 4, 1, [(7,0)], [(9,0)], OPUS_SET_FORCE_CHANNELS.to_bytes(1,'little'))
    create_graph(graph, 9, 5, 1, [(8,0)], [(10,0)], OPUS_SET_MAX_BANDWIDTH.to_bytes(4,'little'))

    create_graph(graph, 10, 6, 1, [(9,0)], [(11,0)], OPUS_SET_INBAND_FEC.to_bytes(1,'little'))
    create_graph(graph, 11, 7, 1, [(10,0)], [(12,0)], OPUS_SET_PACKET_LOSS_PERC.to_bytes(4,'little'))
    create_graph(graph, 12, 8, 1, [(11,0)], [(13,0)], OPUS_SET_DTX.to_bytes(1,'little'))
    create_graph(graph, 13, 9, 1, [(12,0)], [(14,0)], OPUS_SET_LSB_DEPTH.to_bytes(4,'little'))

    create_graph(graph, 14, 10, 1, [(13,0)], [(15,0)], OPUS_SET_PREDICTION_DISABLED.to_bytes(1,'little'))
    create_graph(graph, 15, 11, 1, [(14,0)], [(16,0)], OPUS_SET_SIGNAL.to_bytes(4,'little'))
    create_graph(graph, 16, 12, 1, [(15,0)], [(17,0)], OPUS_SET_PHASE_INVERSION_DISABLED.to_bytes(1,'little'))

    create_graph(graph, 17, 13, 1, [(16,0),(5,1),(5,2),(1,0)], [(18,0),(21,0),(22,0),(19,0)], None) # Encoder, Wrapper_int, Wrapper_int, Wrapper_data_0


    create_graph(graph, 18, 14, 2, [(17,0)], None, None) # Encoder
    create_graph(graph, 19, 24, 2, [(17,3)], None, None) # Wrapper_data_0
    create_graph(graph, 20, 26, 2, [(5,3)], None, None) # Wrapper_data_1
    create_graph(graph, 21, 28, 2, [(17,1)], None, None) # Wrapper_int
    create_graph(graph, 22, 28, 2, [(17,2)], None, None) # Wrapper_int


    with open(out_name, 'wb') as file:
        file.write(graph.SerializeToString())

if __name__ == "__main__":
    main()
