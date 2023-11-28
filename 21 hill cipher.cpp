#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_SIZE 10

void getKey(int keyMatrix[MAX_SIZE][MAX_SIZE], int keySize) {
    printf("Enter the key matrix (size %d x %d):\n", keySize, keySize);

    for (int i = 0; i < keySize; ++i) {
        for (int j = 0; j < keySize; ++j) {
            scanf("%d", &keyMatrix[i][j]);
        }
    }
}

void encrypt(char message[], int keyMatrix[MAX_SIZE][MAX_SIZE], int keySize) {
    int messageVector[MAX_SIZE];
    int resultVector[MAX_SIZE];

    int len = strlen(message);

    while (len % keySize != 0) {
        message[len++] = 'X';
    }

    for (int i = 0; i < len; i += keySize) {
       
        for (int j = 0; j < keySize; ++j) {
            messageVector[j] = message[i + j] - 'A';
        }

        for (int j = 0; j < keySize; ++j) {
            resultVector[j] = 0;
            for (int k = 0; k < keySize; ++k) {
                resultVector[j] += keyMatrix[j][k] * messageVector[k];
            }
            resultVector[j] %= 26;  
        }

        for (int j = 0; j < keySize; ++j) {
            printf("%c", resultVector[j] + 'A');
        }
    }

    printf("\n");
}

int main() {
    int keyMatrix[MAX_SIZE][MAX_SIZE];
    int keySize;

    printf("Enter the size of the key matrix: ");
    scanf("%d", &keySize);

    if (keySize > MAX_SIZE) {
        printf("Error: Maximum key size is %d\n", MAX_SIZE);
        return 1;
    }

    getKey(keyMatrix, keySize);

    char message[100];
    printf("Enter the message to be encrypted (uppercase only): ");
    scanf("%s", message);

    encrypt(message, keyMatrix, keySize);

    return 0;
}

