#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;
const int LED_PIN_1 = 5;
const int LED_PIN_2 = 8;
const int LED_PIN_3 = 11;
const int LED_PIN_4 = 15;

static void turn_all_leds_off(void) {
  gpio_put(LED_PIN_1, 0);
  gpio_put(LED_PIN_2, 0);
  gpio_put(LED_PIN_3, 0);
  gpio_put(LED_PIN_4, 0);
}

static void light_only_led(int led_pin) {
  turn_all_leds_off();
  gpio_put(led_pin, 1);
}

int main() {
  stdio_init_all();

  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);

  gpio_init(LED_PIN_1);
  gpio_set_dir(LED_PIN_1, GPIO_OUT);
  gpio_init(LED_PIN_2);
  gpio_set_dir(LED_PIN_2, GPIO_OUT);
  gpio_init(LED_PIN_3);
  gpio_set_dir(LED_PIN_3, GPIO_OUT);
  gpio_init(LED_PIN_4);
  gpio_set_dir(LED_PIN_4, GPIO_OUT);
  turn_all_leds_off();

  const int sequence[] = {LED_PIN_1, LED_PIN_2, LED_PIN_3, LED_PIN_4};
  const int sequence_size = (int)(sizeof(sequence) / sizeof(sequence[0]));
  int last_btn_r = 1;

  while (true) {
    int btn_r = gpio_get(BTN_PIN_R);

    if (last_btn_r == 1 && btn_r == 0) {
      for (int i = 0; i < sequence_size; i++) {
        light_only_led(sequence[i]);
        sleep_ms(300);
      }
      turn_all_leds_off();
    }

    last_btn_r = btn_r;
    sleep_ms(1);
  }
}
