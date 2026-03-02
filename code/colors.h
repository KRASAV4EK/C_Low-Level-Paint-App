#ifndef COLORS_H
#define COLORS_H

#ifdef __cplusplus
extern "C" {
#endif

unsigned short get_color (int ri, int gi, int bi) {
  unsigned short val = 0;
  val |= ri;
  val <<= 6;
  val |= gi;
  val <<= 5;
  val |= bi;
  return val;
}

unsigned int get_led_color (int ri, int gi, int bi) {
  unsigned int val = 0;
  val |= 0;
  val <<= 8;
  val |= ri;
  val <<= 8;
  val |= gi;
  val <<= 8;
  val |= bi;
  return val;
}

void change_color (int* knob_pos, int* knob_pos_old, int* color_idx){
  if (*knob_pos - *knob_pos_old > 128)
    *knob_pos_old = 255 + *knob_pos_old;
  else if (*knob_pos_old - *knob_pos > 128)
    *knob_pos_old = -255 + *knob_pos_old;
  if (abs(*knob_pos - *knob_pos_old) > 3)
    *color_idx += (*knob_pos - *knob_pos_old) / 4;
  if (*color_idx > 255)
    *color_idx = 255;
  else if (*color_idx < 0)
    *color_idx = 0;
  *knob_pos_old = *knob_pos;
}

void change_colors (int* rk, int* rk_old, int* ri, int* gk, int* gk_old, int* gi, int* bk, int* bk_old, int* bi) {
  change_color(rk, rk_old, ri);
  change_color(gk, gk_old, gi);
  change_color(bk, bk_old, bi);
}

#ifdef __cplusplus
} /* extern "C"*/
#endif

#endif  /*COLORS_H*/
