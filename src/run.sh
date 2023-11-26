#!/bin/bash

./generate_test_results.sh
./run_all_tests_no_threads.sh
./run_all_tests_openmp.sh
./run_all_tests_threads.sh