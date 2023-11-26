#!/bin/bash

# Compilation settings
CPP_IMPL_FILE="./sources/Matrix_openmp.cpp"    # Path to your C++ source file
BASE_OUTPUT_DIR="./../tests/output/openmp"     # Base directory to store test output files
BASE_TIME_DIR="./../tests/time/openmp"         # Base directory to store execution times
THREAD_VALUES=(1 4 8 16 32 64)                 # Array of thread values

# Compile Matrix.cpp (this does not need to be inside the loop)
g++ -c sources/Matrix.cpp -o obj/Matrix.o

# Compile Matrix_openmp.cpp (this can be outside the loop as it's independent of thread count)
g++ -c "$CPP_IMPL_FILE" -fopenmp -o obj/Matrix_impl.o

# Compile main.cpp (also independent of thread count)
g++ -c sources/main.cpp -o obj/main.o

# Iterate over thread values
for NUM_THREADS in "${THREAD_VALUES[@]}"
do
    echo "Setting OMP_NUM_THREADS to $NUM_THREADS and running tests..."

    # Set the number of threads for OpenMP
    export OMP_NUM_THREADS=$NUM_THREADS

    # Create unique output and time directories for this thread count
    OUTPUT_DIR="${BASE_OUTPUT_DIR}/${NUM_THREADS}"
    TIME_DIR="${BASE_TIME_DIR}/${NUM_THREADS}"

    # Ensure the directories exist
    mkdir -p "$OUTPUT_DIR"
    mkdir -p "$TIME_DIR"

    # Link the object files to create the executable
    g++ obj/Matrix.o obj/Matrix_impl.o obj/main.o -fopenmp -o my_program

    # Run your tests
    ./run_all_tests.sh $OUTPUT_DIR $TIME_DIR
done
