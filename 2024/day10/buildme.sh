

cmake -S . -B build && \
    cmake --build build && \
    #echo -e "\n\n--------\nSTARTING TESTS\n--------\n" && \
    #ctest --test-dir ./build && \
    echo -e "\n\n--------\nRUNNING CODE\n--------\n" && \
    ./build/main


