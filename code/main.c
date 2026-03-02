#define _POSIX_C_SOURCE 200112L
 
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
 
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
 
#include "font_types.h"

#include "colors.h"
#include "text_draw.h"
#include "fill_display.h"
#include "draw_display.h"
#include "update_led_line.h"
#include "scenes.h"
#include "knobs.h"

#define M_PI 3.1415

int main(int argc, char *argv[]) {
  // Display 
  unsigned short display[320*480*2];
  font_descriptor_t *fdes;
  
  // Text
  fdes = &font_winFreeSystem14x16;
  unsigned int col = hsv2rgb_lcd(255,0,0);
  bool menu = true;
  bool salaam = true;
  bool change_size = false;

  // Colors
  bool is_drawing = false; // Flag for drawing method
  unsigned short color = 0xFFFF;
  uint32_t rgb_knobs_value;
  int rk, gk, bk;
  int rk_old = 0, gk_old = 0, bk_old = 0;
  int ri = 255, gi = 0, bi = 0;

  // Memory & Coordinates
  unsigned char *parlcd_mem_base, *mem_base;
  int knob;

  // Square & Size
  int square_size = 50; // Paint size
  unsigned short map[480 + max_square_size][320 + max_square_size]; // Map with colors

  // LED Stripe
  unsigned short k = 0; // Current led offset 
  bool left = true; // If true then light goes left
  uint32_t lighting_leds = 16843009;

  printf("Hello master\n");
 
  parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
  if (parlcd_mem_base == NULL)
    exit(1);
 
  mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
  if (mem_base == NULL)
    exit(1);
 
  parlcd_hx8357_init(parlcd_mem_base);
  fill_display_black(parlcd_mem_base);

  // RGB LEDs and LED STRIPE
  volatile unsigned int* led1 = (volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB1_o);
  volatile unsigned int* led2 = (volatile uint32_t*)(mem_base + SPILED_REG_LED_RGB2_o);
  volatile unsigned int* led_stripe = (volatile uint32_t*)(mem_base + SPILED_REG_LED_LINE_o);

  struct timespec loop_delay;
  loop_delay.tv_sec = 0;
  loop_delay.tv_nsec = 50 * 1000 * 1000;
  int xx = 0, yy = 0;

  while (1) {
    update_led_line(&led_stripe, &lighting_leds, &k, &left);

    get_knobs(&knob, &mem_base, &rk, &gk, &bk);

    if (!buttons_action(&knob, &led_stripe, &menu, map, &is_drawing, &led1, &loop_delay, &salaam, &change_size))
      break;
    
    // PAINT
    if (!menu) {
      paint_scene(&square_size, &gk, &xx, &yy, &knob, display, map, fdes, &is_drawing, &color);
    } 
    // MENU OR GREETINGS
    else {
      change_colors(&rk, &rk_old, &ri, &gk, &gk_old, &gi, &bk, &bk_old, &bi);
      menu_scene(display, fdes, &square_size, &salaam, &change_size, &col, &led2, &rgb_knobs_value, &knob, &color, &ri, &gk, &gi, &bi);
    }

    fill_display_rgb(parlcd_mem_base, display);
    clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
  }

  turn_off_leds(led1, led2, led_stripe);

  fill_display_black(parlcd_mem_base);
  printf("Goodbye master\n");
  return 0;
}
