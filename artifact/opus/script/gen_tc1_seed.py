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
    create_graph(graph, 0, 63, 0, None, [(19,1)], None)
    create_graph(graph, 1, 16, 0, None, [(2,0)], None)
    create_graph(graph, 2, 17, 1, [(1,0)], [(3,0)], None)
    create_graph(graph, 3, 18, 1, [(2,0)], [(4,0)], None)
    create_graph(graph, 4, 19, 1, [(3,0)], [(5,0)], None)
    create_graph(graph, 5, 20, 1, [(4, 0)], [(6, 0)], None)
    create_graph(graph, 6, 21, 1, [(5, 0)], [(7, 0)], None)
    create_graph(graph, 7, 22, 1, [(6, 0)], [(8, 0)], None)
    create_graph(graph, 8, 23, 1, [(7, 0)], [(9, 0)], None)
    create_graph(graph, 9, 24, 1, [(8, 0)], [(10, 0)], None)
    create_graph(graph, 10, 25, 1, [(9, 0)], [(11, 0)], None)
    create_graph(graph, 11, 26, 1, [(10, 0)], [(12, 0)], None)
    create_graph(graph, 12, 27, 1, [(11, 0)], [(13, 0)], None)
    create_graph(graph, 13, 28, 1, [(12, 0)], [(14, 0)], None)
    create_graph(graph, 14, 29, 1, [(13, 0)], [(15, 0)], None)
    create_graph(graph, 15, 30, 1, [(14, 0),(0,0)], [(16, 0),(30,1)], None)
    
    create_graph(graph, 16, 17, 1, [(15, 0)], [(17, 0)], None)
    create_graph(graph, 17, 18, 1, [(16, 0)], [(18, 0)], None)
    create_graph(graph, 18, 31, 1, [(17, 0)], [(19, 0)], None)
    create_graph(graph, 19, 20, 1, [(18, 0)], [(20, 0)], None)
    create_graph(graph, 20, 21, 1, [(19, 0)], [(21, 0)], None)
    create_graph(graph, 21, 32, 1, [(20, 0)], [(22, 0)], None)
    create_graph(graph, 22, 33, 1, [(21, 0)], [(23, 0)], None)
    create_graph(graph, 23, 34, 1, [(22, 0)], [(24, 0)], None)
    create_graph(graph, 24, 35, 1, [(23, 0)], [(25, 0)], None)
    create_graph(graph, 25, 36, 1, [(24, 0)], [(26, 0)], None)
    create_graph(graph, 26, 37, 1, [(25, 0)], [(27, 0)], None)
    create_graph(graph, 27, 38, 1, [(26, 0)], [(28, 0)], None)
    create_graph(graph, 28, 39, 1, [(27, 0)], [(29, 0)], None)
    create_graph(graph, 29, 40, 1, [(28, 0),(15,1)], [(30, 0),(43,1)], None)

    create_graph(graph, 30, 17, 1, [(29, 0)], [(31, 0)], None)
    create_graph(graph, 31, 18, 1, [(30, 0)], [(32, 0)], None)
    create_graph(graph, 32, 31, 1, [(31, 0)], [(33, 0)], None)
    create_graph(graph, 33, 20, 1, [(32, 0)], [(34, 0)], None)
    create_graph(graph, 34, 21, 1, [(33, 0)], [(35, 0)], None)
    create_graph(graph, 35, 32, 1, [(34, 0)], [(36, 0)], None)
    create_graph(graph, 36, 33, 1, [(35, 0)], [(37, 0)], None)
    create_graph(graph, 37, 34, 1, [(36, 0)], [(38, 0)], None)
    create_graph(graph, 38, 35, 1, [(37, 0)], [(39, 0)], None)
    create_graph(graph, 39, 36, 1, [(38, 0)], [(40, 0)], None)
    create_graph(graph, 40, 37, 1, [(39, 0)], [(41, 0)], None)
    create_graph(graph, 41, 38, 1, [(40, 0)], [(42, 0)], None)
    create_graph(graph, 42, 39, 1, [(41, 0)], [(43, 0)], None)
    create_graph(graph, 43, 41, 1, [(42, 0),(29,1)], [(44, 0),(57,1)], None)

    create_graph(graph, 44, 17, 1, [(43, 0)], [(45, 0)], None)
    create_graph(graph, 45, 18, 1, [(44, 0)], [(46, 0)], None)
    create_graph(graph, 46, 31, 1, [(45, 0)], [(47, 0)], None)
    create_graph(graph, 47, 20, 1, [(46, 0)], [(48, 0)], None)
    create_graph(graph, 48, 21, 1, [(47, 0)], [(49, 0)], None)
    create_graph(graph, 49, 32, 1, [(48, 0)], [(50, 0)], None)
    create_graph(graph, 50, 33, 1, [(49, 0)], [(51, 0)], None)
    create_graph(graph, 51, 34, 1, [(50, 0)], [(52, 0)], None)
    create_graph(graph, 52, 35, 1, [(51, 0)], [(53, 0)], None)
    create_graph(graph, 53, 36, 1, [(52, 0)], [(54, 0)], None)
    create_graph(graph, 54, 37, 1, [(53, 0)], [(55, 0)], None)
    create_graph(graph, 55, 38, 1, [(54, 0)], [(56, 0)], None)
    create_graph(graph, 56, 39, 1, [(55, 0)], [(57, 0)], None)
    create_graph(graph, 57, 42, 1, [(56, 0),(43,1)], [(58, 0),(71,1)], None) 

    create_graph(graph, 58, 17, 1, [(57, 0)], [(59, 0)], None)
    create_graph(graph, 59, 18, 1, [(58, 0)], [(60, 0)], None)
    create_graph(graph, 60, 31, 1, [(59, 0)], [(61, 0)], None)
    create_graph(graph, 61, 20, 1, [(60, 0)], [(62, 0)], None)
    create_graph(graph, 62, 21, 1, [(61, 0)], [(63, 0)], None)
    create_graph(graph, 63, 32, 1, [(62, 0)], [(64, 0)], None)
    create_graph(graph, 64, 33, 1, [(63, 0)], [(65, 0)], None)
    create_graph(graph, 65, 34, 1, [(64, 0)], [(66, 0)], None)
    create_graph(graph, 66, 35, 1, [(65, 0)], [(67, 0)], None)
    create_graph(graph, 67, 36, 1, [(66, 0)], [(68, 0)], None)
    create_graph(graph, 68, 37, 1, [(67, 0)], [(69, 0)], None)
    create_graph(graph, 69, 38, 1, [(68, 0)], [(70, 0)], None)
    create_graph(graph, 70, 39, 1, [(69, 0)], [(71, 0)], None)
    create_graph(graph, 71, 43, 1, [(70, 0),(57,1)], [(72, 0),(85,1)], None)

    create_graph(graph, 72, 44, 1, [(71, 0)], [(73, 0)], None)
    create_graph(graph, 73, 18, 1, [(72, 0)], [(74, 0)], None)
    create_graph(graph, 74, 31, 1, [(73, 0)], [(75, 0)], None)
    create_graph(graph, 75, 20, 1, [(74, 0)], [(76, 0)], None)
    create_graph(graph, 76, 45, 1, [(75, 0)], [(77, 0)], None)
    create_graph(graph, 77, 32, 1, [(76, 0)], [(78, 0)], None)
    create_graph(graph, 78, 23, 1, [(77, 0)], [(79, 0)], None)
    create_graph(graph, 79, 24, 1, [(78, 0)], [(80, 0)], None)
    create_graph(graph, 80, 25, 1, [(79, 0)], [(81, 0)], None)
    create_graph(graph, 81, 46, 1, [(80, 0)], [(82, 0)], None)
    create_graph(graph, 82, 27, 1, [(81, 0)], [(83, 0)], None)
    create_graph(graph, 83, 47, 1, [(82, 0)], [(84, 0)], None)
    create_graph(graph, 84, 48, 1, [(83, 0)], [(85, 0)], None)
    create_graph(graph, 85, 49, 1, [(84, 0),(71,1)], [(86, 0),(87,0)], None)
    create_graph(graph, 86, 2, 1, [(85, 0)], None, None)
    create_graph(graph, 87, 64, 1, [(85, 1)], None, None)

    # Destructor: create_graph(graph, 0, 2, 2, (13,0), None, None)

    with open('tc1.graph', 'wb') as file:
        file.write(graph.SerializeToString())
    print("Graph has been serialized and saved to 'tc1.graph'.")

if __name__ == "__main__":
    main()
