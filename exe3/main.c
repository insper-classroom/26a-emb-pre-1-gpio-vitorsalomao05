#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdbool.h>
#include <stdio.h>

const int LED_PIN_R = 4;
const int LED_PIN_G = 6;
const int BTN_PIN_G = 26;
const int BTN_PIN_R = 28;

int main() {
  stdio_init_all();

  gpio_init(LED_PIN_R);
  gpio_set_dir(LED_PIN_R, GPIO_OUT);
  gpio_put(LED_PIN_R, 0);

  gpio_init(LED_PIN_G);
  gpio_set_dir(LED_PIN_G, GPIO_OUT);
  gpio_put(LED_PIN_G, 0);

  gpio_init(BTN_PIN_G);
  gpio_set_dir(BTN_PIN_G, GPIO_IN);
  gpio_pull_up(BTN_PIN_G);

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  bool led_r_on = false;
  bool led_g_on = false;
  int last_btn_g = 1;
  int last_btn_r = 1;

  while (true) {
    int btn_g = gpio_get(BTN_PIN_G);
    int btn_r = gpio_get(BTN_PIN_R);

    if (last_btn_g == 1 && btn_g == 0) {
      led_g_on = !led_g_on;
      gpio_put(LED_PIN_G, led_g_on);
    }

    if (last_btn_r == 1 && btn_r == 0) {
      led_r_on = !led_r_on;
      gpio_put(LED_PIN_R, led_r_on);
    }

    last_btn_g = btn_g;
    last_btn_r = btn_r;
    sleep_ms(1);
  }
}
