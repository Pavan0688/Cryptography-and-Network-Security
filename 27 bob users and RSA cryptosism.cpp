#include <stdio.h>

void frequency_analysis(const int encrypted[], int length) {
    int frequency[26] = {0};

    for (int i = 0; i < length; ++i) {
        frequency[encrypted[i]]++;
    }

    printf("Frequency Analysis:\n");
    for (int i = 0; i < 26; ++i) {
        printf("%c: %d\n", 'A' + i, frequency[i]);
    }
}

int main() {
    
    int encrypted_message[] = {2, 15, 4, 0, 7, 8, 4, 13, 0, 25, 0, 2, 15, 17};

    int message_length = sizeof(encrypted_message) / sizeof(encrypted_message[0]);

    frequency_analysis(encrypted_message, message_length);

    return 0;
}

