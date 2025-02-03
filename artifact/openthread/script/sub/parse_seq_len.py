import sys
import json

def count_elements_in_scopes(file_path):
    with open(file_path, 'r') as file:
        data = json.load(file)

    return len(data['scopes'])


target_file = sys.argv[1]
print(count_elements_in_scopes(target_file))
