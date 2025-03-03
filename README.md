# Pin Tool for Flush/Fence Tracking

This project implements a Pin Tool to track `CLFLUSH`, `MFENCE`, `LFENCE`, and `SFENCE` instructions in a target program.

## Files
- `mytool.cpp`: The Pin Tool source code.
- `flush_test.cpp`: A test program to validate the tool.

## How to Use
1. Compile the Pin Tool:
   ```bash
   make obj-intel64/mytool.so TARGET=intel64
