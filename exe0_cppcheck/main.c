#include <stdio.h>

#define NUM_ELEMENTS 5

static int multiply_numbers(int x, int y) {
    return x * y;
}

int main(void) {
    int a = 2;
    int b = 5;
    int result = multiply_numbers(a, b);

    int arr[NUM_ELEMENTS];
    int sum = 0;

    for (int i = 0; i < NUM_ELEMENTS; i++) {
        arr[i] = i;
        sum += arr[i];
    }

    printf("result=%d sum=%d\n", result, sum);

    return 0;
}
