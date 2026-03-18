#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100000000
#define ITER 10

long long sum_branching(int *data) {
    long long sum = 0;
    for (int i = 0; i < SIZE; i++) {
        if (data[i] < 0) {
            sum += -data[i];
        } else {
            sum += data[i];
        }
    }
    return sum;
}

long long sum_branchless(int *data) {
    long long sum = 0;
    for (int i = 0; i < SIZE; i++) {
        int x = data[i];
        int mask = x >> 31;
        sum += (x ^ mask) - mask;
    }
    return sum;
}

int main(int argc, char **argv) {
    int *data = malloc(SIZE * sizeof(int));
    srand(time(NULL));

    // disable branch prediction by shuffling the data
    for (int i = 0; i < SIZE; i++) {
        data[i] = (rand() % 2000) - 1000;
    }

    if (argc < 2) return 1;
    char mode = argv[1][0];

    long long result = 0;
    for (int i = 0; i < ITER; i++) {
        if (mode == 'b') { // branching
            result += sum_branching(data);
        } else {           // branchless
            result += sum_branchless(data);
        }
    }

    printf("Result: %lld\n", result);
    free(data);
    return 0;
}