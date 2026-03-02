#ifndef DRAW_DISPLAY_H
#define DRAW_DISPLAY_H

#ifdef __cplusplus
extern "C" {
#endif

void draw_greetings(unsigned short display[], font_descriptor_t *fdes, int x, int y, unsigned short col) {
  draw_text(display, fdes, x, y, "Timofeev", col);
  draw_text(display, fdes, x, y + 80, "Zharkov", col);
  draw_text(display, fdes, x, y + 160, "Paint", col);
}

void draw_menu(unsigned short display[], font_descriptor_t *fdes, unsigned short col, unsigned short rk, unsigned short gk, unsigned short bk) {
  char value[6];

  // Red value
  draw_char(display, fdes, 100, 20, 'R', col);
  sprintf(value, "%d", rk);
  draw_text(display, fdes, 200, 20, value, col);

  // Green value
  draw_char(display, fdes, 100, 100, 'G', col);
  sprintf(value, "%d", gk);
  draw_text(display, fdes, 200, 100, value, col);

  // Blue value
  draw_char(display, fdes, 100, 180, 'B', col);
  sprintf(value, "%d", bk);
  draw_text(display, fdes, 200, 180, value, col);
}

void draw_white_background(unsigned short display[], font_descriptor_t *fdes) {
  for (int i = 10; i < 300 ; i++) 
    for (int j = 10; j < 460 ; j++) 
      draw_pixel(display, fdes, j, i, 0xFFFF);
}

void draw_color_sample(unsigned short display[], font_descriptor_t *fdes, unsigned short color, bool change_size, int square_size) {
  for (int j=0; j< square_size; j++) 
    for (int i=0; i< square_size; i++) {
      if (change_size)
        draw_pixel(display, fdes, 220 + i, 180 + j, color);     
      else
        draw_pixel(display, fdes, 380 + i, 220 + j, color);     
    }
}

#ifdef __cplusplus
} /* extern "C"*/
#endif

#endif  /*DRAW_DISPLAY_H*/
