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
    #data = read_file_to_bytes("/mnt/curl_corpus/ossfuzz_max/oss-fuzz-gen-c5ad923ce92551a488992eeb4bf0717d5a894fd9")
    out_name = sys.argv[1]
    origin_seed = sys.argv[2]
    data = read_file_to_bytes(origin_seed)
    data_len = len(data)
    padding = bytes(1048576-data_len)
    total_len = 1048576

    create_graph(graph, 0, 0, 0, None, [(1,0)], data+padding+data_len.to_bytes(4,'little'))
    create_graph(graph, 1, 1, 1, [(0,0)], [(2,0)], None)
    create_graph(graph, 2, 2, 1, [(1,0)], [(3,0)], None)
    create_graph(graph, 3, 3, 2, [(2,0)], None, None)

    with open(out_name, 'wb') as file:
        file.write(graph.SerializeToString())

if __name__ == "__main__":
    main()
