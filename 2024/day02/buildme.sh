

cmake -S . -B build     # Generate makefile (only re-run if CMakeLists changes)
cmake --build build     # Build the binary / library

echo -e "\n\n--------\nSTARTING TESTS\n--------\n"
ctest --test-dir ./build/tests && \
    echo -e "\n\n--------\nRUNNING CODE\n--------\n" && \
    ./build/src/day02



