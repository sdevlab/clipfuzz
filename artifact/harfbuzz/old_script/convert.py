import sys
sys.path.append('/graphfuzz/harfbuzz/gfuzz/src')

import graph_pb2

using_hb_ot_var_get_axis_count_map = {"ossfuzz_corpus/9d8c53cb64b8747abdd2b70755cce2ee0eb42ef7.ttf": 1,
"ossfuzz_corpus/AdobeVFPrototype-Subset.otf": 2,
"ossfuzz_corpus/AdobeVFPrototype_vsindex.otf": 2,
"ossfuzz_corpus/SourceSerifVariable-Roman-VVAR.ac.retaingids.ttf": 1,
"ossfuzz_corpus/SourceSerifVariable-Roman-VVAR.ac.ttf": 1,
"ossfuzz_corpus/TestAVAR.ttf": 1,
"ossfuzz_corpus/TestGVAR-Composite-Missing.ttf": 1,
"ossfuzz_corpus/TestGVARNine.ttf": 1,
"ossfuzz_corpus/TestHVARTwo.ttf": 2,
"ossfuzz_corpus/a232bb734d4c6c898a44506547d19768f0eba6a6.ttf": 1,
"ossfuzz_corpus/clusterfuzz-testcase-hb-subset-fuzzer-5508865908670464": 1,
"ossfuzz_corpus/clusterfuzz-testcase-minimized-hb-draw-fuzzer-5103082208493568": 1,
"ossfuzz_corpus/clusterfuzz-testcase-minimized-hb-draw-fuzzer-5641612227772416": 1,
"ossfuzz_corpus/clusterfuzz-testcase-minimized-hb-draw-fuzzer-5668491560747008": 1,
"ossfuzz_corpus/clusterfuzz-testcase-minimized-hb-draw-fuzzer-5681465586352128": 2,
"ossfuzz_corpus/clusterfuzz-testcase-minimized-hb-draw-fuzzer-5686960406659072": 2,
"ossfuzz_corpus/clusterfuzz-testcase-minimized-hb-draw-fuzzer-5703524300357632": 1,
"ossfuzz_corpus/clusterfuzz-testcase-minimized-hb-draw-fuzzer-5712313459146752": 2,
"ossfuzz_corpus/clusterfuzz-testcase-minimized-hb-draw-fuzzer-5750654771658752": 2,
"ossfuzz_corpus/clusterfuzz-testcase-minimized-hb-draw-fuzzer-6231698648596480": 1,
"ossfuzz_corpus/e8691822f6a705e3e9fb48a0405c645b1a036590.ttf": 3}


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
    create_graph(graph, 0, 0, 0, None, [(2,0)], data_len.to_bytes(4,'little')+data+plus) #hb_blob_create
    create_graph(graph, 1, 3, 0, None, [(2,1)], None)
    create_graph(graph, 2, 5, 0, [(0,0),(1,0)], [(22,0),(4,0)], None) #hb_face_create
    
    create_graph(graph, 3, 8, 0, None, [(4,1)], None)
    create_graph(graph, 4, 9, 0, [(2,0),(3,0)], [(7,1), (5,0)], None) #hb_font_create
    
    create_graph(graph, 5, 10, 1, [(4,1)], [(6,0)], None) #hb_ot_font_set_funcs
    create_graph(graph, 6, 11, 1, [(5,0)], [(7,0)], None) #hb_font_set_scale

    num_coords = 0
    if data_len > 0:
        num_coords = data[data_len-1]
    if sys.argv[1] in using_hb_ot_var_get_axis_count_map.keys():
        num_coords = using_hb_ot_var_get_axis_count_map[sys.argv[1]]

    plus = bytes(0)
    if data_len < 255:
        plus = bytes(255-data_len)
    create_graph(graph, 7, 13, 1, [(6,0),(4,0)], [(12,0),(20,0)], num_coords.to_bytes(1,'little')+data[data_len-256:data_len-1]+plus+data_len.to_bytes(4,'little')) #line_23_to_31 #TODO
    
    create_graph(graph, 8, 15, 1, None, [(9,0)], None) #hb_buffer_create
    create_graph(graph, 9, 17, 1, [(8,0)], [(10,0)], None) #hb_buffer_set_flags
    create_graph(graph, 10, 19, 1, [(9,0)], [(11,0)], None) #hb_buffer_add_utf8
    create_graph(graph, 11, 21, 1, [(10,0)], [(12,1)], None) #hb_buffer_guess_segment_properties
    create_graph(graph, 12, 22, 1, [(7,0),(11,0)], [(15,1), (13,0)], None) #hb_shape
    create_graph(graph, 13, 16, 1, [(12,0)], None, None) #hb_buffer_destroy
    
    create_graph(graph, 14, 15, 1, None, [(15,0)], None) #hb_buffer_create
    plus = bytes(0)
    if data_len < (4*16):
        plus = bytes((4*16)-data_len)
        create_graph(graph, 15, 24, 1, [(14,0),(12,0)], [(16,0),(17,0)], data+plus) #hb_buffer_add_utf32 #TODO
    else:
        create_graph(graph, 15, 24, 1, [(14,0),(12,0)], [(16,0),(17,0)], data[data_len-(4*16):]) #hb_buffer_add_utf32 #TODO
    #print("data_len:",data_len, "len(plus):",len(plus))
    
    create_graph(graph, 16, 21, 1, [(15,0)], [(17,1)], None) #hb_buffer_guess_segment_properties
    
    create_graph(graph, 17, 22, 1, [(15,1),(16,0)], [(19,0), (18,0)], None) #hb_shape
    create_graph(graph, 18, 16, 1, [(17,1)], None, None) #hb_buffer_destroy
    
    create_graph(graph, 19, 14, 2, [(17,0)], None, None) #hb_font_destroy
    create_graph(graph, 20, 7, 2, [(7,1)], [(21,0)], None) #hb_face_destroy
    create_graph(graph, 21, 4, 2, [(20,0)], None, None) #hb_face_destroy
    create_graph(graph, 22, 2, 2, [(2,0)], None, None) #hb_blob_destroy    

    with open('output_graph.bin', 'wb') as file:
        file.write(graph.SerializeToString())
    #print("Graph has been serialized and saved to 'output_graph.bin'.")

if __name__ == "__main__":
    main()
