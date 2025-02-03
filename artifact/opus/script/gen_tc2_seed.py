import sys
sys.path.append('/graphfuzz/opus/gfuzz/src')

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
    if len(sys.argv) != 1:
        print("python3 ./gen.py")
        sys.exit(0)
    graph = graph_pb2.Graph()
    #INIT
    create_graph(graph, 0, 65, 0, None, [(16,1)], None)
    create_graph(graph, 1, 55, 0, None, [(2,0)], None)
    
    create_graph(graph, 2, 44, 1, [(1,0)], [(3,0)], None)
    create_graph(graph, 3, 18, 1, [(2,0)], [(4,0)], None)
    create_graph(graph, 4, 19, 1, [(3,0)], [(5,0)], None)
    create_graph(graph, 5, 56, 1, [(4, 0)], [(6, 0)], None)
    create_graph(graph, 6, 57, 1, [(5, 0)], [(7, 0)], None)
    create_graph(graph, 7, 45, 1, [(6, 0)], [(8, 0)], None)
    create_graph(graph, 8, 32, 1, [(7, 0)], [(9, 0)], None)
    create_graph(graph, 9, 58, 1, [(8, 0)], [(10, 0)], None)
    create_graph(graph, 10, 24, 1, [(9, 0)], [(11, 0)], None)
    create_graph(graph, 11, 25, 1, [(10, 0)], [(12, 0)], None)
    create_graph(graph, 12, 59, 1, [(11, 0)], [(13, 0)], None)
    create_graph(graph, 13, 27, 1, [(12, 0)], [(14, 0)], None)
    create_graph(graph, 14, 60, 1, [(13, 0)], [(15, 0)], None)
    create_graph(graph, 15, 61, 1, [(14, 0)], [(16, 0)], None)
    
    create_graph(graph, 16, 62, 1, [(15, 0),(1,0)], [(17, 0),(18,0)], None) 
    
    #Final
    create_graph(graph, 17, 2, 1, [(16, 0)], None, None)
    create_graph(graph, 18, 66, 1, [(16, 1)], None, None)

    with open('tc2.graph', 'wb') as file:
        file.write(graph.SerializeToString())
    print("Graph has been serialized and saved to 'tc2.graph'.")

if __name__ == "__main__":
    main()
