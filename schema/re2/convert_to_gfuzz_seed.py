import sys
sys.path.append('/graphfuzz/re2/gfuzz/src')

import graph_pb2
import struct

def read_binary_file(filename):
    with open(filename, "rb") as f:
        data = f.read()
        return data

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
    graph = graph_pb2.Graph()
    out_name = sys.argv[1]
    origin_seed = sys.argv[2]

    data = read_binary_file(origin_seed)
    data_len = len(data)
    padding = bytes(1048576-data_len)

    create_graph(graph, 0, 22, 0, None, [(14,2)], data+padding+(data_len).to_bytes(4,'little')) # Wrapper_data
    create_graph(graph, 1, 0, 0, None, [(3,0)], data[:2]+(int(1).to_bytes(1,'little'))) # Options
    create_graph(graph, 2, 20, 0, None, [(14,0)], None) # RE2
    
    create_graph(graph, 3, 1, 1, [(1,0)], [(4,0)], None) # Options
    create_graph(graph, 4, 2, 1, [(3,0)], [(5,0)], None) # Options
    create_graph(graph, 5, 3, 1, [(4,0)], [(6,0)], None) # Options
    create_graph(graph, 6, 4, 1, [(5,0)], [(7,0)], None) # Options
    create_graph(graph, 7, 5, 1, [(6,0)], [(8,0)], None) # Options
    create_graph(graph, 8, 6, 1, [(7,0)], [(9,0)], None) # Options
    create_graph(graph, 9, 7, 1, [(8,0)], [(10,0)], None) # Options
    create_graph(graph, 10, 8, 1, [(9,0)], [(11,0)], None) # Options
    create_graph(graph, 11, 9, 1, [(10,0)], [(12,0)], None) # Options
    create_graph(graph, 12, 10, 1, [(11,0)], [(13,0)], None) # Options
    create_graph(graph, 13, 11, 1, [(12,0)], [(14,1)], None) # Options

    create_graph(graph, 14, 14, 1, [(2,0),(13,0),(0,0)], [(15,0),(16,0),(15,1)], None) # RE2, Option, Data
    create_graph(graph, 15, 15, 1, [(14,0),(14,2)], [(17,0),(18,0)], None) # RE2, Data

    create_graph(graph, 16, 12, 2, [(14,1)], None, None) # Option
    create_graph(graph, 17, 21, 2, [(15,0)], None, None) # RE2
    create_graph(graph, 18, 23, 2, [(15,1)], None, None) # Data
    
    with open(out_name, 'wb') as file:
        file.write(graph.SerializeToString())

if __name__ == "__main__":
    main()
