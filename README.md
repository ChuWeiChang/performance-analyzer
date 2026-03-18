# Performance Analyzer

This repository contains C microbenchmarks for comparing algorithm and CPU behavior under different code patterns.

## Benchmarks

### 1) Linked List Middle Finder

File: `single_pointer_vs_fast_slow_pointer.c`

Compares two ways to find the middle of a singly linked list:

- Two-pass approach (count first, then walk again)
- One-pass approach (slow/fast pointers)

The program builds a linked list of the requested length, shuffles node memory locations to increase cache pressure, and runs the selected algorithm repeatedly.

#### Compile

    gcc -O2 -o test single_pointer_vs_fast_slow_pointer.c

#### Run

    sudo perf stat -e instructions,cycles,L1-dcache-loads,L1-dcache-misses ./test <mode> <length>

Arguments:

- `<mode>`:
  - `0` = two-pass
  - `1` = one-pass (slow/fast)
- `<length>`: number of nodes (for example `2500`, `100000`)

Example:

    ./test 1 2500

### 2) Branching vs Branchless Sum

File: `branch_vs_branchless.c`

Compares two ways to compute the sum of absolute values over a large integer array:

- Branching version: `if (x < 0) ...`
- Branchless version: bitwise sign-mask transform

The dataset is filled with random positive/negative values to make branch outcomes hard to predict.

#### Compile

    gcc -O2 -o bench branch_vs_branchless.c

#### Run

    ./bench <mode>

Arguments:

- `<mode>`:
  - `b` = branching
  - `l` = branchless

Examples:

    ./bench b
    ./bench l

Measure branch behavior with `perf`:

    sudo perf stat -e branches,branch-misses,cycles,instructions ./bench b