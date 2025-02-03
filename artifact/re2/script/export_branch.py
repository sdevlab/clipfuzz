import sys
import json
import os

def load_coverage_report(file_path):
    with open(file_path, 'r') as file:
        return json.load(file)

def extract_branch_coverage(data):
    branch_coverage_set = set()
    for f in data['data']:
        for file_data in f['files']:
            file_name = file_data['filename']
            file_name = os.path.basename(file_name)
            if 'fuzz_exec' in file_name or 'ossfuzz_driver' in file_name or 'integrated_driver' in file_name:
                continue
            for branch_data in file_data['branches']:
                is_covered_true = branch_data[4] > 0
                if is_covered_true:
                	branch_1 = (file_name, branch_data[0], branch_data[1], branch_data[2], branch_data[3], True)
                	branch_coverage_set.add(branch_1)
			
                is_covered_false = branch_data[5] > 0
                if is_covered_false:
                	branch_2 = (file_name, branch_data[0], branch_data[1], branch_data[2], branch_data[3], False)
                	branch_coverage_set.add(branch_2)
    return branch_coverage_set

if len(sys.argv) != 2:
    print("./export_branch.py EXPORTED_FILE")
    sys.exit(1)

coverage_1 = load_coverage_report(sys.argv[1])

branch_coverage_1 = extract_branch_coverage(coverage_1)

print(len(branch_coverage_1))
