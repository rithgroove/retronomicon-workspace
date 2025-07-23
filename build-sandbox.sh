# rm -rf build retronomicon_build
cmake -S . -B build
cmake --build build

cp -r ./asset ./build/sandbox
# mkdir -p build && cd build
# cmake ..
# make
# ./sandbox/math-sandbox