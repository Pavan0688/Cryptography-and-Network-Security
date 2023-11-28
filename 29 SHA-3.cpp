#include <stdio.h>
#include <stdint.h>

#define STATE_SIZE 1600 

void printState(uint64_t state[STATE_SIZE]) {
    for (int i = 0; i < STATE_SIZE; ++i) {
        printf("%016llx ", state[i]);
        if ((i + 1) % 5 == 0) {
            printf("\n");
        }
    }
}

void initializeState(uint64_t state[STATE_SIZE]) {
  
    for (int i = 0; i < STATE_SIZE; ++i) {
        state[i] = 0;
    }
}

int main() {
    uint64_t state[STATE_SIZE];

    initializeState(state);

    printf("Initial State Matrix:\n");
    printState(state);

    return 0;
}

