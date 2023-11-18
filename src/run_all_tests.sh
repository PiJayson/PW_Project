#!/bin/bash

# Compilation settings
OUTPUT_DIR="$1"  # Directory to store test output files
TIME_DIR="$2"   # File to store execution times

# Check if compilation was successful
if [ $? -ne 0 ]; then
  echo "Compilation failed. Exiting."
  exit 1
fi

mkdir "$OUTPUT_DIR"
mkdir "$TIME_DIR"

rm -f "$OUTPUT_DIR"/*
rm -f "$TIME_DIR"/*

# Run tests in the 'tests/' directory and measure execution time
for test_file in ./../tests/input/*.in; do
  test_name="$(basename "${test_file%.in}")"
  output_file="$OUTPUT_DIR/${test_name}.out"
  time_file="$TIME_DIR/${test_name}_time.txt"

  # Measure execution time and capture the output
  { time ./my_program < "$test_file" > "$output_file"; } 2>> "$time_file"

  # Check the test result
  if [ $? -eq 0 ]; then
    echo "Test $test_name: PASSED"
  else
    echo "Test $test_name: FAILED"
  fi
done

# Clean up by removing the compiled program
rm my_program

echo "All tests completed. Output files are stored in $OUTPUT_DIR."
echo "Execution times are logged in $TIME_DIR."
