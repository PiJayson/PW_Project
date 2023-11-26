#!/bin/bash

# Compilation settings
CPP_IMPL_FILE="./sources/Matrix_threads.cpp"    # Path to your C++ source file
BASE_OUTPUT_DIR="./../tests/output/threads"  # Base directory to store test output files
BASE_TIME_DIR="./../tests/time/threads"   # Base directory to store execution times

# Array of thread counts
THREAD_COUNTS=(1 4 8 16 32 64)

# Iterate over the thread counts
for N_THREADS in "${THREAD_COUNTS[@]}"; do
    echo "Compiling for ${N_THREADS} threads..."

    # Adjust directories for the current number of threads
    OUTPUT_DIR="${BASE_OUTPUT_DIR}/${N_THREADS}"
    TIME_DIR="${BASE_TIME_DIR}/${N_THREADS}"

    # Create directories if they don't exist
    mkdir -p "${OUTPUT_DIR}"
    mkdir -p "${TIME_DIR}"

    # Compile Matrix.cpp with thread support
    g++ -pthread -DN_THREADS=${N_THREADS} -c sources/Matrix.cpp -o obj/Matrix.o

    # Compile Matrix_threads.cpp with thread support
    g++ -pthread -DN_THREADS=${N_THREADS} -c sources/Matrix_threads.cpp -o obj/Matrix_threads.o

    # Compile main.cpp
    g++ -c sources/main.cpp -o obj/main.o

    # Link the object files to create the executable
    g++ -pthread obj/Matrix.o obj/Matrix_threads.o obj/main.o -o my_program

    # Run tests for this number of threads
    ./run_all_tests.sh $OUTPUT_DIR $TIME_DIR

    echo "Tests completed for ${N_THREADS} threads."
done
