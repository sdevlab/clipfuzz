import sys
sys.path.append('/graphfuzz/Little-CMS/gfuzz/src')

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
    data_len = len(data)
    padding = bytes(1048576-data_len)
    total_len = 1048576

    create_graph(graph, 0, 1, 0,   None, [(6,0)], data+padding+total_len.to_bytes(4,'little')) #sP
    create_graph(graph, 1, 0, 0,   None, [(6,1)], None) #dP
    create_graph(graph, 2, 15, 0,  None, [(6,2)], None) #sC
    create_graph(graph, 3, 10, 0,   None, [(8,5)], None) #T
    create_graph(graph, 4, 17, 0,  None, [(7,1)], None) #nU
    create_graph(graph, 5, 17, 0,  None, [(8,4)], None) #sU

    create_graph(graph, 6, 2, 1, [(0,0),(1,0),(2,0)], [(8,0),(8,1),(7,0)], None) #sP dP sC
    create_graph(graph, 7, 3, 1, [(6,2),(4,0)], [(8,2),(8,3)], None) #sC nU

    create_graph(graph, 8, 4, 1, [(6,0),(6,1),(7,0), (7,1), (5,0),(3,0)], \
                                    [(9,0),(10,0),(12,0),(11,1) ,(11,2),(11,0)], None) #sP dP sC nU sU T

    create_graph(graph, 9, 5, 2, [(8,0)], None, None)
    create_graph(graph, 10, 6,2,  [(8,1)], None, None) ## error
    create_graph(graph, 11, 7,1,  [(8,5),(8,3),(8,4)], [(15,0),(13,0),(14,0)], (1).to_bytes(4,'little')+(1).to_bytes(4,'little'))
    create_graph(graph, 12, 16,2,  [(8,2)], None, None)
    create_graph(graph, 13, 18,2,  [(11,1)], None, None)
    create_graph(graph, 14, 18,2,  [(11,2)], None, None)
    create_graph(graph, 15, 11,2,  [(11,0)], None, None)


    with open(out_name, 'wb') as file:
        file.write(graph.SerializeToString())

if __name__ == "__main__":
    main()
