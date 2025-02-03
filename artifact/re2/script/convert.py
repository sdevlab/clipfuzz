import sys
sys.path.append('/graphfuzz/re2/gfuzz/src')

import graph_pb2
import struct

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
    create_graph(graph, 0, 0, 0, None, [(1,0)], None)
    create_graph(graph, 1, 3, 1, [(0,0)], [(2,0)], bytes([0]))
    create_graph(graph, 2, 4, 1, [(1,0)], [(3,0)], bytes([0]))    
    create_graph(graph, 3, 5, 1, [(2,0)], [(4,0)], bytes([0]))
    create_graph(graph, 4, 6, 1, [(3,0)], [(5,0)], bytes([0]))
    create_graph(graph, 5, 7, 1, [(4,0)], [(6,0)], bytes([0]))
    create_graph(graph, 6, 8, 1, [(5,0)], [(7,0)], bytes([0]))
    create_graph(graph, 7, 9, 1, [(6,0)], [(8,0)], bytes([0]))
    create_graph(graph, 8, 10, 1, [(7,0)], [(9,0)], bytes([0]))
    create_graph(graph, 9, 11, 1, [(8,0)], [(10,0)], bytes([0]))
    create_graph(graph, 10, 12, 1, [(9,0)], [(12,1)], bytes([0]))

    create_graph(graph, 11, 13, 1, None, [(12,0)], None)
    create_graph(graph, 12, 15, 1, [(11,0),(10,0)], [(13,0),(14,0)], struct.pack('I', 64)+bytes(64))
    create_graph(graph, 13, 14, 1, [(12,0)], None, None)
    create_graph(graph, 14, 1, 1, [(13,0)], None, None)

    with open('output_graph.bin', 'wb') as file:
        file.write(graph.SerializeToString())
    print("Graph has been serialized and saved to 'output_graph.bin'.")

if __name__ == "__main__":
    main()
