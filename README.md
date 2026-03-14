# Linked List Middle Finder

This program evaluates the performance of finding the middle node of a singly linked list using two different algorithms: a two-pass approach and a one-pass (slow/fast pointer) approach. 

The program generates a linked list of a specified length, randomly shuffles the node memory locations to simulate cache-miss scenarios, and runs the chosen algorithm 1000 times.

## Compilation

Compile the C file using standard GCC:

    gcc -O3 -o test single_pointer_vs_fast_slow_pointer.c 

## Usage

Run the compiled executable with two arguments: `mode` and `length`.

    sudo perf stat -e instructions,cycles,L1-dcache-loads,L1-dcache-misses ./test <mode> <length>

### Arguments

* `<mode>`: Determines the algorithm used to find the middle node.
    * `0`: Runs the Two-pass algorithm.
    * `1`: Runs the One-pass (slow/fast pointers) algorithm.
* `<length>`: The number of nodes in the generated linked list (e.g., 1000, 100000).

I set `<length>` = 2500 to better show the difference in cache misses, since my l1 cache is 32kb.

Set `<length>` > 5000 would drastically increase miss rate. At `<length>` around 30000, the miss rate hit an ceiling about 90 %.
### Example

To run the program using the one-pass algorithm on a linked list with 50,000 nodes:

    ./test 1 2500