sudo rm -r 2025-*

python3 helper.py build re2
python3 helper.py fuzzing re2 --fuzzer ossfuzz --init_corpus fuzzing/ossfuzz_seed/re2 --session 2 --time 3

sleep 10
python3 helper.py coverage re2 --fuzzer ossfuzz --input 2025-*  --print
