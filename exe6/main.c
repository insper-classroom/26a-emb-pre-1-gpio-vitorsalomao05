#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

static const uint FIRST_GPIO = 2;
static const uint BTN_PIN_G = 28;
static const uint32_t DEBOUNCE_MS = 40;

static volatile uint8_t counter = 0;
static volatile bool counter_changed = false;
static volatile uint32_t last_press_ms = 0;

// This array converts a number 0-9 to a bit pattern to send to the GPIOs
static const uint8_t bits[10] = {
    0x3f,  // 0
    0x06,  // 1
    0x5b,  // 2
    0x4f,  // 3
    0x66,  // 4
    0x6d,  // 5
    0x7d,  // 6
    0x07,  // 7
    0x7f,  // 8
    0x67   // 9
};

static void seven_seg_init(void) {
    for (int gpio = FIRST_GPIO; gpio < FIRST_GPIO + 7; gpio++) {
        gpio_init(gpio);
        gpio_set_dir(gpio, GPIO_OUT);
    }
}

static void seven_seg_display(uint8_t value_index) {
    uint8_t value = bits[value_index];

    for (int i = 0; i < 7; i++) {
        int gpio = FIRST_GPIO + i;
        int bit = (value >> i) & 1u;
        gpio_put(gpio, bit);
    }
}

static void on_button_press(uint gpio, uint32_t events) {
    (void)gpio;

    if ((events & GPIO_IRQ_EDGE_FALL) == 0u) {
        return;
    }

    uint32_t now_ms = to_ms_since_boot(get_absolute_time());
    if ((now_ms - last_press_ms) < DEBOUNCE_MS) {
        return;
    }

    last_press_ms = now_ms;
    counter = (uint8_t)((counter + 1u) % 10u);
    counter_changed = true;
}

int main(void) {
    stdio_init_all();

    gpio_init(BTN_PIN_G);
    gpio_set_dir(BTN_PIN_G, GPIO_IN);
    gpio_pull_up(BTN_PIN_G);

    seven_seg_init();
    seven_seg_display(counter);
    gpio_set_irq_enabled_with_callback(BTN_PIN_G, GPIO_IRQ_EDGE_FALL, true, &on_button_press);

    while (true) {
        if (counter_changed) {
            counter_changed = false;
            seven_seg_display(counter);
            printf("cnt: %u\n", (unsigned int)counter);
        }

        sleep_ms(10);
    }
}
