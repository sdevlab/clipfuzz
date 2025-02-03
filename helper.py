CONFIG_FILE = "benchmarks.yaml"

import re
from collections import Counter
import argparse
import os
import sys
import subprocess
from typing import List
from pathlib import Path
import shutil
from datetime import datetime
import pandas as pd
import yaml

def load_yaml(file_path):
    with open(file_path, 'r') as file:
        data = yaml.safe_load(file)
    return data


def parse_arguments():
    parser = argparse.ArgumentParser(description="Helper script for various tasks.")

    subparsers = parser.add_subparsers(dest="command", required=True, help="Sub-command help")

    # Sub-command: build
    build_parser = subparsers.add_parser("build", help="Select target project.")
    build_parser.add_argument("project", help="The name of the project to build.")

    # Sub-command: activate
    activate_parser = subparsers.add_parser("activate", help="Activate the docker container.")
    activate_parser.add_argument("project", help="The name of the project to activate.")
    activate_parser.add_argument("--coverage_mode", action="store_true", help="Activate container to enable coverage measurement")
    activate_parser.add_argument("--run", action="store_true", help="Exit existing container")

    # Sub-command: convert_ossfuzz_seed
    convert_parser = subparsers.add_parser(
        "convert_ossfuzz_seed", help="Convert OSSFuzz seed.")
    convert_parser.add_argument("project", help="The name of the project to activate.")
    convert_parser.add_argument("--seed_path", required=False, help="Path to the OSS-Fuzz seed file.")
    convert_parser.add_argument("--fuzzer", required=True, help="Select among [ossfuzz, gfuzz, clfuzz].")
    convert_parser.add_argument("--out_dir_path", required=True, help="Output directory path.")
    convert_parser.add_argument("--coverage", action="store_true", help="Save llvm-cov coverage result.")
    convert_parser.add_argument("--buffer_n", required=False, type=int, help="Set pool_size of BUFFER for CLIPFuzz.")
    convert_parser.add_argument("--pool_size", required=False, type=int, help="Set primtivie pool_size for CLIPFuzz.")

    # Sub-command: fuzzing
    fuzzing_parser = subparsers.add_parser("fuzzing", help="Run fuzzing on a project.")
    fuzzing_parser.add_argument("project", help="The name of the project to fuzz.")
    fuzzing_parser.add_argument("--fuzzer", required=True, help="The fuzzer to use [ossfuzz, gfuzz, clfuzz].")
    fuzzing_parser.add_argument("--init_corpus", required=True, help="Path to the seed directory.")
    fuzzing_parser.add_argument("--session", required=True, type=int, help="Number of repeat times for the session.")
    fuzzing_parser.add_argument('--time', type=int, required=False, help='Total time for fuzzing in seconds (for GraphFuzz, OSS-Fuzz).')
    fuzzing_parser.add_argument("--interval", nargs="+", type=int, required=False,
                                help="[MAX_API_LEN_0, TIME_0, ...] (e.g., 10 600 20 600) only for CLIPFuzz.")
    fuzzing_parser.add_argument('--buffer_n', type=int, required=False, help='Size of pool of buffers (Only for CLIPFuzz)')
    fuzzing_parser.add_argument("--pool_size", required=False, type=int, help="Set pool_size (Only for CLIPFuzz).")

    # Sub-command: coverage
    coverage_parser = subparsers.add_parser("coverage", help="Measure coverage for a project.")
    coverage_parser.add_argument("project", help="The name of the project.")
    coverage_parser.add_argument("--fuzzer", required=True, help="The fuzzer to use [ossfuzz, gfuzz, clfuzz].")
    coverage_parser.add_argument("--input", required=True, help="Path of the root directory of the out directories.")
    coverage_parser.add_argument("--print", action="store_true", help="Print coverage of each seed corpus.")

    # Validity check
    args = parser.parse_args()
    config = load_yaml(CONFIG_FILE)

    if args.command != 'convert_ossfuzz_seed' and args.project not in config.keys():
        print(f"Invalid Project {args.project}: select in", config.keys())
        return


    if args.command == 'fuzzing':
        if args.fuzzer == 'clfuzz' \
                        and (args.interval == None or args.buffer_n == None):
            print('clipfuzz requires --interval and --buffer_n')
            return

        elif args.fuzzer != 'clfuzz' \
                        and args.time == None:
            print('ossfuzz and gfuzz require --time')
            return

        elif args.fuzzer == 'clfuzz' \
                        and args.interval != None and args.time != None:
            print('clipfuzz requires --interval, and other fuzzers require --time')
            return

        elif args.fuzzer == 'clfuzz':
            min_api_len = config[args.project].get('environment')['clipfuzz']['seed_gen']['min_api_uc_len']
            for i in range(0, len(args.interval), 2):
                api_len = args.interval[i]
                if api_len < min_api_len:
                    print(f"Invalid Interval: unsatisfied api_seq_len({api_len})  > {min_api_len}")
                    return


    if args.command == 'fuzzing' or args.command == 'coverage' or args.command == 'convert_ossfuzz_seed':
        if args.fuzzer != 'ossfuzz' \
                and args.fuzzer != 'gfuzz' \
                and args.fuzzer != 'clfuzz':
            print('Select fuzzer in [ossfuzz, gfuzz, clfuzz]')
            return

    if args.command == 'convert_ossfuzz_seed' and args.fuzzer == 'ossfuzz':
        print('Invalid fuzzer')
        return

    if args.command == 'convert_ossfuzz_seed' and args.fuzzer == 'clfuzz':
        min_buffer_n = config[args.project].get('environment')['clipfuzz']['seed_gen']['min_buffer_n']
        if args.buffer_n < min_buffer_n:
            print(f"Must be: --buffer_n >= {min_buffer_n}")
            return

        min_prim_pool_size = config[args.project].get('environment')['clipfuzz']['seed_gen']['min_pool_size']
        if args.pool_size < min_prim_pool_size:
            print(f"Must be: --pool_size >= {min_prim_pool_size}")
            return

    # Main logic
    if args.command == 'build':
        build_image(config[args.project].get('environment'))
    elif args.command == 'activate':
        activate_container(config[args.project].get('environment'), args.coverage_mode, args.run)
    elif args.command == 'fuzzing':
        do_fuzzing(config[args.project].get('environment'), args.fuzzer, args.init_corpus, args.time, args.interval, args.buffer_n, args.pool_size, args.session)
    elif args.command == 'convert_ossfuzz_seed':
        convert_ossfuzz_seed(config[args.project].get('environment'), args.seed_path, args.fuzzer, args.out_dir_path, args.coverage, args.buffer_n, args.pool_size)
    elif args.command == 'coverage':
        measure_coverage(config[args.project].get('environment'), args.project, args.fuzzer, args.input, args.print)

def build_image (config):
    parrent_name = config['parrent_image']
    project_name = config['fuzzing_image']
    coverage_name = config['coverage_image']

    image_name = parrent_name.lower()
    docker_file = f"artifact/{parrent_name}/Dockerfile"
    subprocess.run(['docker', 'kill', f'clipfuzz_{image_name}'])
    subprocess.run(['docker', 'rm', f'clipfuzz_{image_name}'])
    subprocess.run(['docker', 'build', '.', '-f', docker_file, '-t', f'clipfuzz_{image_name}'])

    image_name = project_name.lower()
    docker_file = f"artifact/{project_name}/Dockerfile"
    subprocess.run(['docker', 'kill', f'clipfuzz_{image_name}'])
    subprocess.run(['docker', 'rm', f'clipfuzz_{image_name}'])
    subprocess.run(['docker', 'build', '.', '-f', docker_file, '-t', f'clipfuzz_{image_name}'])

    image_name = coverage_name.lower()
    docker_file = f"artifact/{coverage_name}/Dockerfile"
    subprocess.run(['docker', 'kill', f'clipfuzz_{image_name}'])
    subprocess.run(['docker', 'rm', f'clipfuzz_{image_name}'])
    subprocess.run(['docker', 'build', '.', '-f', docker_file, '-t', f'clipfuzz_{image_name}'])


def activate_container (config, coverage_mode, exit_existing):
    project_name = config['fuzzing_image']
    coverage_name = config['coverage_image']

    if coverage_mode:
        image_name = f"clipfuzz_{coverage_name.lower()}"
    else:
        image_name = f"clipfuzz_{project_name.lower()}"

    docker_name = f"{image_name}_act"

    if exit_existing:
        command = f"docker stop {docker_name}"
        subprocess.run(command, shell=True)
        command = f"docker rm {docker_name}"
        subprocess.run(command, shell=True)

    command = f"docker run -t -d --name {docker_name} -v {os.getcwd()}:/mnt {image_name} /bin/bash"
    subprocess.run(command, shell=True)

    gfuzz_driver_dir = os.path.dirname(config['graphfuzz']['schema_path'])
    integ_driver_dir = os.path.dirname(config['clipfuzz']['driver_path'])

    gfuzz_work_dir = config['graphfuzz']['work_dir_path_in_container']
    integ_work_dir = config['clipfuzz']['work_dir_path_in_container']

    bring_schema(docker_name, gfuzz_driver_dir, gfuzz_work_dir)
    bring_proto(docker_name, integ_driver_dir, integ_work_dir)

    subprocess.run(['docker', 'exec', '-it', f'{docker_name}', '/bin/bash'])


def convert_ossfuzz_seed (config, ossfuzz_seed, fuzzer, out_dir_path, save_result, buffer_n, pool_size):

    if fuzzer == 'clfuzz' and (buffer_n == None or pool_size == None):
        print("CLIPFuzz requires --api_uc_len and --buffer_n, --pool_size")
        return

    if os.path.exists(out_dir_path):
        print(f"Wrong options: --out_dir={out_dir_path} already exists")
        return

    image_name = f"clipfuzz_{config['coverage_image'].lower()}"
    if fuzzer == 'gfuzz':
        work_dir = config['graphfuzz']['work_dir_path_in_container']
    elif fuzzer == 'clfuzz':
        work_dir = config['clipfuzz']['work_dir_path_in_container']

    docker_name = f"{image_name}_seed"


    # Run container
    command = f"docker stop {docker_name}"
    subprocess.run(command, shell=True)
    command = f"docker rm {docker_name}"
    subprocess.run(command, shell=True)
    command = f"docker run -t -d --name {docker_name} -v {os.getcwd()}:/mnt {image_name} /bin/bash"
    subprocess.run(command, shell=True)


    # Option values
    ossfuzz_seed = "/mnt/"+config['ossfuzz']['initial_seed_path']
    min_api_uc_len = config['clipfuzz']['seed_gen']['min_api_uc_len']
    min_buffer_n = config['clipfuzz']['seed_gen']['min_buffer_n']
    min_pool_size = config['clipfuzz']['seed_gen']['min_pool_size']


    # Bring driver in container
    gfuzz_driver_dir = os.path.dirname(config['graphfuzz']['schema_path'])
    integ_driver_dir = os.path.dirname(config['clipfuzz']['driver_path'])

    gfuzz_work_dir = config['graphfuzz']['work_dir_path_in_container']
    integ_work_dir = config['clipfuzz']['work_dir_path_in_container']

    # Convert a seed
    if fuzzer == 'clfuzz':
        bring_proto(docker_name, integ_driver_dir, integ_work_dir, pool_size=pool_size, buffer_n=buffer_n, to_build=False)

        convert_script = "/mnt/"+config['clipfuzz']['seed_gen']['script_path']

        CMD = './libprotobuf-mutator/build/external.protobuf/bin/protoc --python_out=. api_block.proto'
        command = f"docker exec -w {work_dir} {docker_name} /bin/bash -c \"{CMD}\""
        subprocess.run(command, shell=True)

        out_seed = f"/mnt/{out_dir_path}/buffer_n_{buffer_n}_pool_size_{pool_size}.bin"

    elif fuzzer == 'gfuzz':
        convert_script = "/mnt/"+config['graphfuzz']['seed_gen']['script_path']

        bring_schema(docker_name, gfuzz_driver_dir, gfuzz_work_dir, to_build=True)
        out_seed = f"/mnt/{out_dir_path}/{os.path.basename(ossfuzz_seed)}_graph.bin"

    os.makedirs(out_dir_path)

    convert_script_name = os.path.basename(convert_script)

    CMD = f"cp {convert_script} ."
    command = f"docker exec -w {work_dir} {docker_name} /bin/bash -c \"{CMD}\""
    subprocess.run(command, shell=True)

    CMD = f"python3 {convert_script_name} {out_seed} {ossfuzz_seed} {pool_size} {buffer_n}"
    command = f"docker exec -w {work_dir} {docker_name} /bin/bash -c \"{CMD}\""
    subprocess.run(command, shell=True)

    print(f"Success to generate seed for {fuzzer}:", out_seed.replace("/mnt/",""))

    if save_result:
        coverage_dir = f"test_coverage/{out_dir_path.replace('/mnt/','')}"
        run_cov_script_with_seed_corpus(docker_name, work_dir, fuzzer, out_dir_path, [100, 100])
        bring_from_container_to_local(docker_name, work_dir, "result", coverage_dir.replace("/mnt/",""))
        print(f"Saved coverage of {out_seed.replace('/mnt/','')} into:", coverage_dir)

        gfuzz_work_dir = config['graphfuzz']['work_dir_path_in_container']
        parse_export = gfuzz_work_dir+"/script/export_branch.py"
        
        docker_command = f"python3 {parse_export} /mnt/{coverage_dir}/result/result.export"
        command = f"echo -n 'Branch coverage of {coverage_dir}/result/result.export: '&& docker exec -w {gfuzz_work_dir} {docker_name} /bin/bash -c \"{docker_command}\""
        subprocess.run(command, shell=True)
    



# --time: gfuzz, OSS-Fuzz
# --interval: clipfuzz
def do_fuzzing (config, fuzzer, seed_corpus, time, interval, buffer_n, pool_size, repeat_n):

    proj = config['fuzzing_image']
    image_name = f"clipfuzz_{proj.lower()}"
    docker_name = f"{image_name}_fuzzing"

    subprocess.run(['docker', 'stop', f'{docker_name}'])
    subprocess.run(['docker', 'rm', f'{docker_name}'])
    command = f"docker run -t -d --name {docker_name} -v {os.getcwd()}:/mnt {image_name} /bin/bash"
    subprocess.run(command, shell=True)

    if fuzzer == 'gfuzz':
        work_dir = config['graphfuzz']['work_dir_path_in_container']
        cov_script = f"{work_dir}/script/gfuzz_cov.sh"
        driver_name = "fuzz_exec_cov"
        gfuzz_driver_dir = os.path.dirname(config['graphfuzz']['schema_path'])
        bring_schema(docker_name, gfuzz_driver_dir, work_dir, to_build=True)

    elif fuzzer == 'ossfuzz':
        work_dir = config['ossfuzz']['work_dir_path_in_container']
        cov_script = f"{work_dir}/script/ossfuzz_cov.sh"
        driver_name = "runner"
        CMD = f"./script/build_ossfuzz.sh"
        command = f"docker exec -w {work_dir} {docker_name} /bin/bash -c \"{CMD}\""
        subprocess.run(command, shell=True)

    elif fuzzer == 'clfuzz':
        work_dir = config['clipfuzz']['work_dir_path_in_container']
        cov_script = f"{work_dir}/cov_integ.sh"
        driver_name = "fuzz_driver_cov"
        integ_driver_dir = os.path.dirname(config['clipfuzz']['driver_path'])
        bring_proto(docker_name, integ_driver_dir, work_dir, pool_size=pool_size, buffer_n=buffer_n, to_build=True)


    if 'dictionary_path' in config['ossfuzz'].keys():
        dictionary = f"-dict=/mnt/{config['ossfuzz']['dictionary_path']}"
    else:
        dictionary = ""

    out_root_dir = f'{datetime.now().strftime("%Y-%m-%d_%H-%M")}_{proj}_{fuzzer}'

    if time is not None:
        cur_time = datetime.now().strftime("%Y-%m-%d_%H-%M")
        out_dir_name_lst = []

        for session in range(repeat_n):
            out_dir_name_lst.append(f"{cur_time}_{proj}_{fuzzer}_{session}")

        for session in range(repeat_n):
            out_dir_name = out_dir_name_lst[session]
            inter_time = session*1

            if seed_corpus != "":
                CMD1 = (
                    f'mkdir -p {out_dir_name} && '
                    f'mkdir -p {out_dir_name}/interesting {out_dir_name}/artifact && '
                    f'cp -a /mnt/{seed_corpus} {out_dir_name}'
                )
            else:
                CMD1 = (
                    f'mkdir -p {out_dir_name} && '
                    f'mkdir -p {out_dir_name}/interesting {out_dir_name}/artifact'
                )

            command = f"docker exec -w {work_dir} {docker_name} /bin/bash -c \"{CMD1}\""
            subprocess.run(command, shell=True)

            if fuzzer == 'gfuzz':

                CMD = "cp schema.yaml {out_dir_name}"
                command = f"docker exec -w {work_dir} {docker_name} /bin/bash -c \"{CMD}\""
                subprocess.run(command, shell=True)

                CMD2 = (
                    f"echo 'ASAN_OPTIONS=detect_leaks=0 ./fuzz_exec {out_dir_name}/interesting {out_dir_name}/{os.path.basename(seed_corpus)} "
                    f'-artifact_prefix={out_dir_name}/artifact/ {dictionary} '
                    f'--graphfuzz_max_nodes=0 -timeout=1 -max_len=2097152 '
                    f"-fork=1 -ignore_crashes=1 -max_total_time={time} > {out_dir_name}/fuzz_log.txt 2>&1' > {out_dir_name}/run.sh && "
                    f"echo 'rm -r {out_dir_name}/artifact' >> {out_dir_name}/run.sh && "
                    f"echo 'sleep {inter_time}' >> {out_dir_name}/run.sh && "
                    f"echo 'mv {out_dir_name} /mnt/{out_root_dir}' >> {out_dir_name}/run.sh && "
                    f'chmod +x {out_dir_name}/run.sh'
                )
            elif fuzzer == 'ossfuzz':
                CMD2 = (
                    f"echo 'ASAN_OPTIONS=detect_leaks=0 ./ossfuzz {out_dir_name}/interesting {out_dir_name}/{os.path.basename(seed_corpus)} "
                    f'-timeout=1 -max_len=1048576 -artifact_prefix={out_dir_name}/artifact/ {dictionary} '
                    f"-max_total_time={time} > {out_dir_name}/fuzz_log.txt 2>&1' > {out_dir_name}/run.sh && "
                    f"echo 'sleep {inter_time}' >> {out_dir_name}/run.sh && "
                    f"echo 'rm -r {out_dir_name}/artifact' >> {out_dir_name}/run.sh && "
                    f"echo 'mv {out_dir_name} /mnt/{out_root_dir}' >> {out_dir_name}/run.sh && "
                    f'chmod +x {out_dir_name}/run.sh'
                )

            command = f"docker exec -w {work_dir} {docker_name} /bin/bash -c \"{CMD2}\""
            subprocess.run(command, shell=True)

        os.makedirs(out_root_dir)

        for session in range(repeat_n):
            out_dir_name = out_dir_name_lst[session]
            screen_name = f"fuzz_{session}"
    
            CMD3 = (
                f'screen -S fuzz_session_{session} -dm ./{out_dir_name}/run.sh'
            )
            screen_command = f"docker exec -w {work_dir} {docker_name} /bin/bash -c \"{CMD3}\""
            subprocess.run(screen_command, shell=True)


    elif interval is not None:
        cur_time = datetime.now().strftime("%Y-%m-%d_%H-%M")
        out_dir_name_lst = []

        for session in range(repeat_n):
            out_dir_name_lst.append(f"{cur_time}_{proj}_{fuzzer}_{session}")

        for session in range(repeat_n):
            out_dir_name = out_dir_name_lst[session]
            inter_time = session*1

            if seed_corpus != "":
                CMD1 = (
                    f'mkdir -p {out_dir_name} && '
                    f'mkdir -p {out_dir_name}/interesting {out_dir_name}/artifact && '
                    f'cp integrated_driver.cpp api_block.proto {out_dir_name} &&'
                    f'cp -a /mnt/{seed_corpus} {out_dir_name}'
                )
            else:
                CMD1 = (
                    f'mkdir -p {out_dir_name} && '
                    f'mkdir -p {out_dir_name}/interesting {out_dir_name}/artifact'
                )

            command = f"docker exec -w {work_dir} {docker_name} /bin/bash -c \"{CMD1}\""
            subprocess.run(command, shell=True)

            script_gen_runnig_driver_0 = f"echo 'ASAN_OPTIONS=detect_leaks=0 MAX_API_SEQ_LEN={{}} " \
                    + f"./fuzz_driver {out_dir_name}/interesting {out_dir_name}/{os.path.basename(seed_corpus)} " \
                    + f'-artifact_prefix={out_dir_name}/artifact/ {dictionary} ' \
                    + f'-timeout=1 -max_len=2097152 -detect_leaks=0 ' \
                    + f"-fork=1 -ignore_crashes=1 -max_total_time={{}} > {out_dir_name}/fuzz_log.txt 2>&1'" \
                    + f" > {out_dir_name}/run.sh && \\\n"
    
            script_gen_runnig_driver_1 = f"echo 'ASAN_OPTIONS=detect_leaks=0 MAX_API_SEQ_LEN={{}} " \
                    + f"./fuzz_driver {out_dir_name}/interesting " \
                    + f'-artifact_prefix={out_dir_name}/artifact/ {dictionary} ' \
                    + f'-timeout=1 -max_len=2097152 -detect_leaks=0 ' \
                    + f"-fork=1 -ignore_crashes=1 -max_total_time={{}} >> {out_dir_name}/fuzz_log.txt 2>&1'" \
                    + f" >> {out_dir_name}/run.sh && \\\n"
    
            script_list = []
            script_list.append(script_gen_runnig_driver_0.format(interval[0], interval[1]))
    
            for i in range(2, len(interval), 2):
                max_api_len = interval[i]
                time = interval[i+1]
                script_list.append(script_gen_runnig_driver_1.format(max_api_len, time))
    
            CMD2 = (
                f"{''.join(script_list)}"
                f"echo 'rm -r {out_dir_name}/artifact' >> {out_dir_name}/run.sh && "
                f"echo 'sleep {inter_time}' >> {out_dir_name}/run.sh && "
                f"echo 'mv {out_dir_name} /mnt/{out_root_dir}' >> {out_dir_name}/run.sh && "
                f'chmod +x {out_dir_name}/run.sh'
            )

            command = f"docker exec -w {work_dir} {docker_name} /bin/bash -c \"{CMD2}\""
            subprocess.run(command, shell=True)

        os.makedirs(out_root_dir)

        for session in range(repeat_n):
            out_dir_name = out_dir_name_lst[session]
            screen_name = f"fuzz_{session}"

            CMD3 = (
                f'screen -S fuzz_session_{session} -dm ./{out_dir_name}/run.sh'
            )
            screen_command = f"docker exec -w {work_dir} {docker_name} /bin/bash -c \"{CMD3}\""
            subprocess.run(screen_command, shell=True)


    
def bring_from_container_to_local(docker_name, work_dir, container_file, local_dir):
    command = f"mkdir -p {local_dir}"
    subprocess.run(command, shell=True)

    docker_command = f"mv {container_file} /mnt/{local_dir}"
    command = f"docker exec -w {work_dir} {docker_name} /bin/bash -c \"{docker_command}\""
    subprocess.run(command, shell=True)


def measure_coverage (config, project, fuzzer, input_dir, print_mode):
    image_name = f"clipfuzz_{config['coverage_image'].lower()}"
    docker_name = f"{image_name}_cov"

    subprocess.run(['docker', 'stop', f'{docker_name}'])
    subprocess.run(['docker', 'rm', f'{docker_name}'])
    command = f"docker run -t -d --name {docker_name} -v {os.getcwd()}:/mnt {image_name} /bin/bash"
    subprocess.run(command, shell=True)

    gfuzz_driver_dir = os.path.dirname(config['graphfuzz']['schema_path'])
    integ_driver_dir = os.path.dirname(config['clipfuzz']['driver_path'])

    if fuzzer == 'ossfuzz':
        work_dir = config['ossfuzz']['work_dir_path_in_container']

    elif fuzzer == 'gfuzz':
        work_dir = config['graphfuzz']['work_dir_path_in_container']
        driver_name = "fuzz_exec_cov"
        bring_schema(docker_name, gfuzz_driver_dir, work_dir, to_build=True)

    elif fuzzer == 'clfuzz':
        work_dir = config['clipfuzz']['work_dir_path_in_container']
        driver_name = "fuzz_driver_cov"

    input_dir = input_dir if input_dir[-1] != '/' else input_dir[:-1]
    interesting_dirs = []

    
    for dirpath, dirnames, filenames in os.walk(input_dir):
        if 'interesting' in dirnames:
            interesting_path = os.path.join(dirpath, 'interesting')
            interesting_dirs.append(interesting_path)


    if len(interesting_dirs) < 1:
        print("There is no 'interesting' directory")
        return

    interesting_dirs = sorted(interesting_dirs)
    result_dirs = []

    for interesting_dir in interesting_dirs:
        out_dir = os.path.dirname(interesting_dir)
        result_dir = out_dir+"/result"
        result_dirs.append(result_dir)

        if os.path.isdir(result_dir):
            continue

        if fuzzer == 'clfuzz':
            run_sh = out_dir + "/run.sh"
            interval = parse_run_script(run_sh)

            pool_size, buffer_n = parse_clfuzz_driver(os.path.dirname(interesting_dir)+'/integrated_driver.cpp')
            bring_proto(docker_name, integ_driver_dir, work_dir, pool_size=pool_size, buffer_n=buffer_n, to_build=False)
        else:
            run_sh = out_dir + "/run.sh"
            interval = parse_run_script(run_sh)
            time = interval[0]
            interval = [0, time]

        run_cov_script_with_seed_corpus(docker_name, work_dir, fuzzer, interesting_dir, interval)
        bring_from_container_to_local(docker_name, work_dir, "result", out_dir)

    print("Results of llvm-cov are saved in: ", '\n\t'.join(result_dirs))

    if print_mode:
        for result_dir in result_dirs:
            gfuzz_work_dir = config['graphfuzz']['work_dir_path_in_container']
            parse_export = gfuzz_work_dir+"/script/export_branch.py"
        
            docker_command = f"python3 {parse_export} /mnt/{result_dir}/result.export"
            command = f"echo -n 'Branch coverage of {result_dir}/result.export: '&& docker exec -w {gfuzz_work_dir} {docker_name} /bin/bash -c \"{docker_command}\""
            subprocess.run(command, shell=True)
    

def parse_clfuzz_driver(clfuzz_driver):
    with open(clfuzz_driver, "r") as fp:
        pool_size = 0
        buffer_n = 0
        for line in fp.readlines():
            if pool_size == 0 and 'PRIMITIVE_POOL_SIZE' in line:
                pool_size = int(line[line.rindex('PRIMITIVE_POOL_SIZE ')+len('PRIMITIVE_POOL_SIZE '):])

            if buffer_n == 0 and 'BUFFER_POOL_SIZE' in line:
                buffer_n = int(line[line.rindex('BUFFER_POOL_SIZE ')+len('BUFFER_POOL_SIZE '):])

    return pool_size, buffer_n

    
def parse_run_script (run_script_path):
    #print("run_sh:", run_sh)

    with open(run_script_path, "r") as fp:
        content = fp.read()

    interval = []
    
    for word in content.split(' '):
        if 'MAX_API_SEQ_LEN' in word:
            max_api_len = int(word[len("MAX_API_SEQ_LEN="):])
            interval.append(max_api_len)

        elif 'max_total_time' in word:
            time = int(word[len("max_total_time=")+1:])
            interval.append(time)

    return interval


def bring_proto (docker_name, driver_dir, work_dir, pool_size=0, buffer_n=0, to_build=False):
    command = f"cp {driver_dir}/api_block.proto ."
    subprocess.run(command, shell=True)

    docker_command = f"mv /mnt/api_block.proto ."
    command = f"docker exec -w {work_dir} {docker_name} /bin/bash -c \"{docker_command}\""
    subprocess.run(command, shell=True)

    temp_driver_name = f"temp_{docker_name}.cpp"
    command = f"cp {driver_dir}/integrated_driver.cpp ./{temp_driver_name}"
    subprocess.run(command, shell=True)

    with open(f'./{temp_driver_name}', 'r+') as proto_file:
        content = proto_file.read()
        content = content.replace('#define OBJ_POOL_SIZE 0', f'#define OBJ_POOL_SIZE {pool_size}')
        content = content.replace('#define PRIMITIVE_POOL_SIZE 0', f'#define PRIMITIVE_POOL_SIZE {pool_size}')
        content = content.replace('#define BUFFER_POOL_SIZE 0', f'#define BUFFER_POOL_SIZE {buffer_n}')

        proto_file.seek(0)
        proto_file.write(content)
        proto_file.truncate()

    docker_command = f"mv /mnt/{temp_driver_name} ./integrated_driver.cpp"
    command = f"docker exec -w {work_dir} {docker_name} /bin/bash -c \"{docker_command}\""
    subprocess.run(command, shell=True)

    if to_build:
        docker_command = "./build.sh"
        command = f"docker exec -w {work_dir} {docker_name} /bin/bash -c \"{docker_command}\""
        subprocess.run(command, shell=True)


def bring_schema (docker_name, driver_dir, work_dir, to_build=False):
    command = f"cp {driver_dir}/schema.yaml ."
    subprocess.run(command, shell=True)

    docker_command = f"mv /mnt/schema.yaml ."
    command = f"docker exec -w {work_dir} {docker_name} /bin/bash -c \"{docker_command}\""
    subprocess.run(command, shell=True)

    if to_build:
        docker_command = "./script/build.sh"
        command = f"docker exec -w {work_dir} {docker_name} /bin/bash -c \"{docker_command}\""
        subprocess.run(command, shell=True)


def run_cov_script_with_seed_corpus (docker_name, work_dir, fuzzer, seed_corpus, interval):

    if fuzzer == 'gfuzz':
        cov_script = f"{work_dir}/script/gfuzz_cov.sh"
        driver_name = "fuzz_exec_cov"
    elif fuzzer == 'ossfuzz':
        cov_script = f"{work_dir}/script/ossfuzz_cov.sh"
        driver_name = "runner"
    elif fuzzer == 'clfuzz':
        cov_script = f"{work_dir}/cov_integ.sh"
        driver_name = "fuzz_driver_cov"
    
    out_dir = "result"

    # Collect *.profdraw
    out_raw_dir = f"{out_dir}/raw"
    cmd_create_raw = f"docker exec -w {work_dir} {docker_name} /bin/bash -c 'mkdir -p {out_raw_dir}'"
    subprocess.run(cmd_create_raw, shell=True)

    start_time = min(os.path.getmtime(os.path.join(seed_corpus, f)) for f in os.listdir(seed_corpus))

    n = 0
    time_list = []
    acc_time = 0

    container_from_input_dir = f"/mnt/{seed_corpus}"

    for i in range(0, len(interval), 2):
        #_max_api_len = interval[i]
        _time = interval[i+1]
        acc_time += _time
        time_list.append(acc_time)

    for input_file in sorted(os.listdir(seed_corpus), key=lambda f: os.path.getmtime(os.path.join(seed_corpus, f))):
        edit_time = os.path.getmtime(os.path.join(seed_corpus, input_file))
        input_name = os.path.basename(input_file)
        relative_start_time = int(edit_time - start_time)
        max_api_len = -1
        for (j, time) in enumerate(time_list):
            if relative_start_time <= time:
                max_api_len = interval[j*2]
                break

        if max_api_len == -1:
            print(f"WARNNING: generate time of {input_file} exceed total fuzzing time ({relative_start_time}) > time({time})")
            max_api_len = interval[len(interval)-2]

        n = n+1

        if n % 50 == 0:
            now = datetime.now()
            formatted_now = now.strftime("%Y-%m-%d %H:%M:%S")
            print("Progress: collect .profraw (", n, "/",len(os.listdir(seed_corpus)), ')', formatted_now)

        full_input_path = f"{container_from_input_dir}/{input_file}"
        cmd_run_script = f"docker exec -w {work_dir} {docker_name} /bin/bash -c 'MAX_API_SEQ_LEN={max_api_len} {cov_script} {full_input_path}'"
        subprocess.run(cmd_run_script, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)


    docker_command = f"mv *.profraw {out_raw_dir}"
    command = f"docker exec -w {work_dir} {docker_name} /bin/bash -c \"{docker_command}\""
    subprocess.run(command, shell=True)

    # Merge *.profdraw into merged.profdata
    out_data_dir = f"{out_dir}/merged"
    command = f"docker exec -w {work_dir} {docker_name} /bin/bash -c \"mkdir {out_data_dir}\""
    subprocess.run(command, shell=True)

    cmd_merge_profraw = f"llvm-profdata-12 merge -sparse {out_raw_dir}/*.profraw -o {out_data_dir}/merged.profdata"
    command = f"docker exec -w {work_dir} {docker_name} /bin/bash -c \"{cmd_merge_profraw}\""
    subprocess.run(command, shell=True)

    # Save result.show, result.report, result.export
    docker_command = f"llvm-cov-12 report {driver_name} -instr-profile={out_data_dir}/merged.profdata > {out_dir}/result.report"
    command = f"docker exec -w {work_dir} {docker_name} /bin/bash -c \"{docker_command}\""
    subprocess.run(command, shell=True)

    docker_command = f"llvm-cov-12 show {driver_name} -instr-profile={out_data_dir}/merged.profdata > {out_dir}/result.show"
    command = f"docker exec -w {work_dir} {docker_name} /bin/bash -c \"{docker_command}\""
    subprocess.run(command, shell=True)

    docker_command = f"llvm-cov-12 export {driver_name} -instr-profile={out_data_dir}/merged.profdata > {out_dir}/result.export"
    command = f"docker exec -w {work_dir} {docker_name} /bin/bash -c \"{docker_command}\""
    subprocess.run(command, shell=True)


if __name__ == "__main__":
    args = parse_arguments()
    #print(args)
