sudo rm -r fuzzing/clipfuzz_corpus/re2/
sudo rm -r test_coverage
sudo rm -r 2025-*

python3 helper.py build re2
python3 helper.py convert_ossfuzz_seed re2 --fuzzer clfuzz --out_dir_path fuzzing/clipfuzz_corpus/re2 --coverage --buffer_n 2 --pool_size 2

sudo rm -r 2025-01*
python3 helper.py fuzzing re2 --fuzzer clfuzz --init_corpus fuzzing/clipfuzz_corpus/re2 --session 2 --interval 20 2 40 2 --buffer_n 2 --pool_size 2

sleep 10
python3 helper.py coverage re2 --fuzzer clfuzz --input 2025-*  --print
