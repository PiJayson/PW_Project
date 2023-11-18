#!/bin/bash

# Compilation settings
CPP_FILE="./sources/main_no_threads.cpp"  # Path to your C++ source file\
OUTPUT_DIR="./../tests/ok"      # Directory to store test output files

# Compile the C++ code (adjust the compilation command as needed)
g++ -o my_program "$CPP_FILE"

# Check if compilation was successful
if [ $? -ne 0 ]; then
  echo "Compilation failed. Exiting."
  exit 1
fi

# Run tests in the 'tests/' directory
for test_file in ./../tests/input/*.in; do
  test_name="$(basename "${test_file%.in}")"
  output_file="$OUTPUT_DIR/${test_name}.ok"
  
  # Run the test and capture the output
  ./my_program < "$test_file" > "$output_file"

  # Check the test result
  if [ $? -eq 0 ]; then
    echo "Test $test_name: CREATED"
  else
    echo "Test $test_name: FAILED"
  fi
done

# Clean up by removing the compiled program
rm my_program