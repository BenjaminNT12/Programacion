#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* solve(char* A) {
    int len = strlen(A);
    int i, j, k;

    // Reverse the entire string
    for (i = 0; i < len / 2; i++) {
        char temp = A[i];
        A[i] = A[len - i - 1];
        A[len - i - 1] = temp;
    }

    // Reverse each individual word
    int start = 0;
    for (i = 0; i < len; i++) {
        if (A[i] == ' ') {
            for (int j = start; j < (start + i) / 2; j++) {
                char temp = A[j];
                A[j] = A[start + i - j - 1];
                A[start + i - j - 1] = temp;
            }
            start = i + 1;
        }
    }
    for (j = start; j < (start + len) / 2; j++) {
        char temp = A[j];
        A[j] = A[start + len - j - 1];
        A[start + len - j - 1] = temp;
    }

    // Remove leading and trailing spaces
    i = 0, j = len - 1;
    while (A[i] == ' ') i++;
    while (A[j] == ' ') j--;
    for (int k = i; k <= j; k++) {
        A[k - i] = A[k];
    }
    A[j - i + 1] = '\0';

    // Replace consecutive spaces with a single space
    len = strlen(A);
    int pos = 0;
    for (i = 0; i < len; i++) {
        if (A[i] != ' ' || (i > 0 && A[i - 1] != ' ')) {
            A[pos++] = A[i];
        }
    }
    A[pos] = '\0';

    return A;
}

int main(void){
    char A[] = "the sky is blue";
    char* B;
    B = solve(A);
    // printf("%s\n", A);
    if (B == NULL) {
        printf("Error: Failed to allocate memory\n");
    } else {
        printf("%s\n", B);
    }
    return 0;
}