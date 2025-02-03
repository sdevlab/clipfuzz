import sys
sys.path.append('/graphfuzz/Little-CMS/gfuzz/src')

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
    if len(sys.argv) < 2:
        print("python3 ./convert.py BYTE_FILE")
        sys.exit(0)
    seed_fp = open(sys.argv[1], 'rb')
    node_idx = 0
    graph = graph_pb2.Graph()
    data = seed_fp.read()

    TEST_INPUT_MAX_SIZE = 10000
    data_len = len(data)
    plus = bytes(0)
    if data_len < TEST_INPUT_MAX_SIZE:
        plus = bytes(TEST_INPUT_MAX_SIZE-data_len)
    create_graph(graph, 0, 0, 0, None, [(3,1)], data_len.to_bytes(4,'little')+data+plus) #cmsOpenProfileFromMem
    create_graph(graph, 1, 1, 0, None, [(3,2)], None) 
    create_graph(graph, 2, 3, 0, None, [(3,0)], None)
    create_graph(graph, 3, 5, 1, [(2,0),(0,0),(1,0)], [(6,0),(4,0),(5,0)], None) #line_29_to_57
    create_graph(graph, 4, 2, 2, [(3,1)], None, None)
    create_graph(graph, 5, 2, 2, [(3,2)], None, None)
    create_graph(graph, 6, 4, 2, [(3,0)], None, None)

    with open('output_graph.bin', 'wb') as file:
        file.write(graph.SerializeToString())
    #print("Graph has been serialized and saved to 'output_graph.bin'.")

if __name__ == "__main__":
    main()
