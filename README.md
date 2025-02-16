# ClipFuzz

## Usage
```
git clone https://github.com/sdevlab/clipfuzz.git --recursive
cd clipfuzz
python3 helper.py --help
```

### Build
```
python3 helepr.py build re2
```

### Attach to the container
```
python3 helepr.py activate re2
```

### Convert an OSS-Fuzz seed to CLIPFuzz's seed
```
python3 helper.py convert_ossfuzz_seed re2 --fuzzer clfuzz --out_dir_path fuzzing/clipfuzz_corpus/re2 --coverage --buffer_n 2 --pool_size 2
```

### Fuzzing
```
python3 helper.py fuzzing re2 --fuzzer clfuzz --init_corpus fuzzing/clipfuzz_corpus/re2 --session 2 --interval 20 2 40 2 --buffer_n 2 --pool_size 2
```

### Coverage Measurement
```
python3 helper.py coverage re2 --fuzzer clfuzz --input 2025-mm-dd_hh_MM_clfuzz  --print
```

There are more examples in ```./example```.




## Change Mutation Strategy
 - There are three libprotobuf-mutator versions
   1) Original libprotobuf-mutator
   2) Multiple clone
   3) Multiple clone + 'Mutate' by 80%
 - Check current version: ```./clipfuzz/mutation_operator/convert_mutation_rool.sh --check```
 - Select specific version: ```./clipfuzz/mutation_operator/convert_mutation_rool.sh [1,3]```
