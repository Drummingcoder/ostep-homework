#!/bin/bash

# Compile tlb.c with flags to prevent aggressive optimization
gcc -O0 -fno-optimize-sibling-calls -o tlb tlb.c

# Start with 1 page, go up to 8192 pages, doubling each time
pages=1
while [ $pages -le 8192 ]; do
    echo "Running with $pages pages"
    ./tlb $pages 5000  # Run with 5 trials for each page count
    echo "-----------------------------------"
    pages=$((pages * 2))
done