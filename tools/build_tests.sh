#!/bin/sh
# This script is used by CI to build all test functions

SCRIPT_DIR=$(dirname "$0")
TEST_FUNCTIONS=$(cat src/test/test.c | grep -P '(?<=void )test_.+(?=\()' -o)
for test_function in $TEST_FUNCTIONS
do
    make TEST=$test_function
done