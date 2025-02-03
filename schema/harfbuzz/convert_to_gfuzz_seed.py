import sys
sys.path.append('/graphfuzz/gfuzz/src')

import graph_pb2

def read_file_to_bytes(filename):
    with open(filename, "rb") as f:
        return f.read()

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
    node_idx = 0
    graph = graph_pb2.Graph()

    out_name = sys.argv[1]
    origin_seed = sys.argv[2]
    data = read_file_to_bytes(origin_seed)
    #data = read_file_to_bytes("/mnt/harfbuzz_corpus/ossfuzz_high/SourceSansPro-Regular.otf")
    data_len = len(data)
    padding = bytes(1048576-data_len)
    total_len = 1048576

    create_graph(graph, 0, 0, 0, [], [(4, 0)], data+padding+data_len.to_bytes(4,'little'))
    create_graph(graph, 1, 3, 0, [], [(4, 1)], None)
    create_graph(graph, 2, 8, 0, [], [(5, 1)], None)
    create_graph(graph, 3, 12, 0, [], [(9, 0)], None)

    create_graph(graph, 4, 1, 1, [(0, 0), (1, 0)], [(16, 0), (5, 0)], None)
    create_graph(graph, 5, 4, 1, [(4, 1), (2, 0)], [(8, 0), (6, 0)], None)
    create_graph(graph, 6, 9, 1, [(5, 1)], [(7, 0)], None)

    context = int(12).to_bytes(4,'little')+int(12).to_bytes(4,'little')
    create_graph(graph, 7, 10, 1, [(6, 0)], [(8, 1)], context)

    num_coords = data[data_len-1]
    padding = bytes(255-num_coords)
    context = num_coords.to_bytes(1,'little') + data[data_len-num_coords-1 : data_len-1]+padding+data_len.to_bytes(4,'little')
    create_graph(graph, 8, 5, 1, [(5, 0), (7, 0)], [(15, 0), (9, 1)], context)

    context = (-1).to_bytes(4,'little', signed=True) \
            + int(0).to_bytes(4,'little') \
            + int(-1).to_bytes(4,'little', signed=True) \
            + int(0).to_bytes(4,'little') \
            + bytes('ABCDEXYZ123@_%&)*$!', 'utf-8') \
            + data[-(16*4):] \
            + int(6).to_bytes(1,'little')
    create_graph(graph, 9, 13, 1, [(3, 0), (8, 1)], [(10, 0), (12, 0)], context)

    context = data[-(16*4):]+int(0).to_bytes(4,'little')+int(-1).to_bytes(4,'little', signed=True)
    create_graph(graph, 10, 14, 1, [(9, 0)], [(11, 0)], context)

    create_graph(graph, 11, 15, 1, [(10, 0)], [(12, 1)], None)
    create_graph(graph, 12, 16, 1, [(9, 1), (11, 0)], [(14, 0), (13, 0)], None)

    create_graph(graph, 13, 17, 2, [(12, 1)], [], None)
    create_graph(graph, 14, 11, 2, [(12, 0)], [], None)
    create_graph(graph, 15, 6, 2, [(8, 0)], [], None)
    create_graph(graph, 16, 2, 2, [(4, 0)], [], None)

    with open(out_name, 'wb') as file:
        file.write(graph.SerializeToString())

if __name__ == "__main__":
    main()
