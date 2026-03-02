#ifndef KNOBS_H
#define KNOBS_H

#ifdef __cplusplus
extern "C" {
#endif

void get_knobs(int *knob, unsigned char **mem_base, int *rk, int *gk, int *bk) {
  //getting knobs values
  *knob = *(volatile uint32_t*)(*mem_base + SPILED_REG_KNOBS_8BIT_o);
  *rk = (*knob>>16) & 0xFF;
  *gk = (*knob>>8) & 0xFF;
  *bk = (*knob) & 0xFF;
}

bool buttons_action(int *knob, volatile unsigned int** led_stripe, bool *menu, unsigned short map[][320 + max_square_size], bool *is_drawing, volatile unsigned int **led1, struct timespec *loop_delay, bool *salaam, bool *change_size) {
  if ((*knob >> 26) & (*knob >> 24) & 1) { // Red and Blue buttons action
    return false;
  }
  else if ((*knob >> 26) & 1) { // Red button action
    **led_stripe = 0xFFFFFFFF;
    if (*menu) {
      for (int j=0; j<320; j++) {
        for (int i=0; i<480; i++) {
          map[i][j] = 0;
        }
      }
    } else {
      *is_drawing = true;
      **led1 = 0x0000FF00;
    }
  }
  else if ((*knob >> 25) & 1) { // Green button action
    clock_nanosleep(CLOCK_MONOTONIC, 0, loop_delay, NULL);
    **led_stripe = 0xFFFFFFFF;
    *menu = !*menu;
    *change_size = false;
    *is_drawing = false;
    *salaam = false;
    **led1 = 0x00FF0000;
  }
  else if ((*knob >> 24) & 1) { // Blue button action
    **led_stripe = 0xFFFFFFFF;
    *is_drawing = false;
    *change_size = !*change_size;
    **led1 = 0x00FF0000;
  }
  return true;
}

#ifdef __cplusplus
} /* extern "C"*/
#endif

#endif  /*KNOBS_H*/
