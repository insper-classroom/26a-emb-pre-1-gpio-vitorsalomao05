#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_1 = 7;
const int BTN_PIN_2 = 26;

int main() {
  stdio_init_all();

  gpio_init(BTN_PIN_1);
  gpio_set_dir(BTN_PIN_1, GPIO_IN);
  gpio_pull_up(BTN_PIN_1);

  gpio_init(BTN_PIN_2);
  gpio_set_dir(BTN_PIN_2, GPIO_IN);
  gpio_pull_up(BTN_PIN_2);

  while (true) {
    if (!gpio_get(BTN_PIN_1)) {
      printf("Botao 1\n");
      while (!gpio_get(BTN_PIN_1)) {
        sleep_ms(1);
      }
    }

    if (!gpio_get(BTN_PIN_2)) {
      printf("Botao 2\n");
      while (!gpio_get(BTN_PIN_2)) {
        sleep_ms(1);
      };
    }

    sleep_ms(1);
  }
}
