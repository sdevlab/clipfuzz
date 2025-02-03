sudo rm -r fuzzing/grapfuzz_corpus/re2/
sudo rm -r test_coverage
sudo rm -r 2025-*

python3 helper.py build re2
python3 helper.py convert_ossfuzz_seed re2 --fuzzer gfuzz --out_dir_path fuzzing/grapfuzz_corpus/re2 --coverage

sudo rm -r 2025-01*
python3 helper.py fuzzing re2 --fuzzer gfuzz --init_corpus fuzzing/grapfuzz_corpus/re2 --session 2 --time 3

sleep 10
python3 helper.py coverage re2 --fuzzer gfuzz --input 2025-*  --print
