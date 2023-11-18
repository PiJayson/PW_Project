#!/bin/bash

# Compilation settings
CPP_IMPL_FILE="./sources/Matrix_no_threads.cpp"    # Path to your C++ source file
OUTPUT_DIR="./../tests/output/no_threads"  # Directory to store test output files
TIME_DIR="./../tests/time/no_threads"   # File to store execution times

# Compile the C++ code (adjust the compilation command as needed)
# Compile Matrix.cpp
g++ -c sources/Matrix.cpp -o obj/Matrix.o

# Compile Matrix_no_threads.cpp
g++ -c "$CPP_IMPL_FILE" -o obj/Matrix_impl.o

# Compile main.cpp
g++ -c sources/main.cpp -o obj/main.o

# Link the object files to create the executable
g++ obj/Matrix.o obj/Matrix_impl.o obj/main.o -o my_program

./run_all_tests.sh $OUTPUT_DIR $TIME_DIR
