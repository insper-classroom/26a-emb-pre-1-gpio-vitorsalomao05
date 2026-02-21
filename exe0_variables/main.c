#include <stdbool.h>

static int increment(int value) {
    return value + 1;
}

int main(void) {
    int a = 0;
    bool threshold_reached = false;

    while (!threshold_reached) {
        a = increment(a);

        if (a > 5) {
            threshold_reached = true;
        }
    }

    return 0;
}
