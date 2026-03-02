#ifndef UPDATE_LED_LINE_H
#define UPDATE_LED_LINE_H

#ifdef __cplusplus
extern "C" {
#endif

void update_led_line(volatile unsigned int** led_stripe, uint32_t *lighting_leds, unsigned short *k, bool *left) {
    // LED
  **led_stripe = *lighting_leds;

  if (*k == 7) // Check if achieved left edge
    *left = false;
  else if (*k == 0) // Check if achieved right edge
    *left = true;
  if (*left == true){ // Go left
    *lighting_leds<<=1;
    *k += 1;
  } else { // Go right
    *lighting_leds>>=1;
    *k -= 1;
  }
}

void turn_off_leds(volatile unsigned int* led1, volatile unsigned int* led2, volatile unsigned int* led_stripe) {
  *led_stripe = 0x0;
  *led2 = 0x0;
  *led1 = 0x0;
}

#ifdef __cplusplus
} /* extern "C"*/
#endif

#endif  /*UPDATE_LED_LINE_H*/
