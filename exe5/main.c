#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

const int BTN_PIN_1 = 26;
const int BTN_PIN_2 = 7;
const uint32_t DEBOUNCE_MS = 50;

int main() {
    stdio_init_all();

    gpio_init(BTN_PIN_1);
    gpio_set_dir(BTN_PIN_1, GPIO_IN);
    gpio_pull_up(BTN_PIN_1);

    gpio_init(BTN_PIN_2);
    gpio_set_dir(BTN_PIN_2, GPIO_IN);
    gpio_pull_up(BTN_PIN_2);

    int cnt_1 = 0;
    int cnt_2 = 0;
    bool last_btn_1 = true;
    bool last_btn_2 = true;
    uint32_t last_press_1_ms = 0;
    uint32_t last_press_2_ms = 0;

    while (true) {
        const uint32_t now_ms = to_ms_since_boot(get_absolute_time());
        const bool btn_1 = gpio_get(BTN_PIN_1);
        const bool btn_2 = gpio_get(BTN_PIN_2);

        if (last_btn_1 && !btn_1 && (now_ms - last_press_1_ms >= DEBOUNCE_MS)) {
            cnt_1++;
            printf("Botao 1: %d\n", cnt_1);
            last_press_1_ms = now_ms;
        }

        if (last_btn_2 && !btn_2 && (now_ms - last_press_2_ms >= DEBOUNCE_MS)) {
            cnt_2++;
            printf("Botao 2: %d\n", cnt_2);
            last_press_2_ms = now_ms;
        }

        last_btn_1 = btn_1;
        last_btn_2 = btn_2;
        sleep_ms(1);
    }
}
