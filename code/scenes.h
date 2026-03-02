#ifndef SCENES_H
#define SCENES_H

#ifdef __cplusplus
extern "C" {
#endif

int max_square_size = 70;

void fill_square(int *square_size, int *xx, int *yy, unsigned short display[], unsigned short map[][320 + max_square_size], font_descriptor_t *fdes, bool *is_drawing, unsigned short *color) {
  // Fill square with choosen color
  for (int j=0; j<*square_size; j++) {
    for (int i=0; i<*square_size; i++) {
      // printf("%d x, %d y, %d\n", *xx, *yy, *is_drawing);
      if(*is_drawing){
        map[i + *xx][j + *yy] = *color;
      }
      draw_pixel(display, fdes, i + *xx, j + *yy, *color);
    }
  }
}

void paint_scene(int *square_size, int *gk, int *xx, int *yy, int *knob, unsigned short display[], unsigned short map[][320 + max_square_size], font_descriptor_t *fdes, bool *is_drawing, unsigned short *color) {
  // Square left top corner coordinate
  *xx = ((*knob&0xff)*480)/256; 
  *yy = (((*knob>>16)&0xff)*320)/256;

  // Redraw dispaly according to pixel map
  for (int j=0; j<320; j++) {
    for (int i=0; i<480; i++) {
      draw_pixel(display, fdes, i, j, map[i][j]);
    }
  }

  fill_square(square_size, xx, yy, display, map, fdes, is_drawing, color);
}

void menu_scene(unsigned short display[], font_descriptor_t *fdes, int *square_size, bool *salaam, bool *change_size, unsigned int *col, volatile unsigned int **led2, uint32_t *rgb_knobs_value, int *knob, unsigned short *color, int *ri, int *gk, int *gi, int *bi) {
  struct timespec loop_delay;
  loop_delay.tv_sec = 0;
  loop_delay.tv_nsec = 100 * 1000 * 1000;

  draw_white_background(display, fdes);

  if (*salaam) {
    draw_greetings(display, fdes, 80, 20, *col);
    **led2 = 0x00FFFFFF;

  } else if (*change_size) {
    *square_size = *gk % 40 + 30; // Change square size according to Green knob position
    draw_color_sample(display, fdes, *color, *change_size, *square_size);

  } else {

    *rgb_knobs_value = *knob;
    *color = get_color(*ri / 8, *gi / 4, *bi / 8);
    **led2 = get_led_color(*ri, *gi, *bi);
    
    draw_menu(display, fdes, *col, *ri ,*gi ,*bi);
    draw_color_sample(display, fdes, *color, *change_size, *square_size);
    clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
  }
}

#ifdef __cplusplus
} /* extern "C"*/
#endif

#endif  /*SCENES_H*/
