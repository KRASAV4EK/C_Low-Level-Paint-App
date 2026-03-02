#ifndef TEXT_DRAW_H
#define TEXT_DRAW_H

#ifdef __cplusplus
extern "C" {
#endif

unsigned int hsv2rgb_lcd(int hue, int saturation, int value);

void draw_pixel(unsigned short display[], font_descriptor_t *fdes, int x, int y, unsigned short color);
 
void draw_pixel_big(unsigned short display[], font_descriptor_t *fdes, int x, int y, unsigned short color);
 
int char_width(font_descriptor_t *fdes, int ch);

void draw_char(unsigned short display[], font_descriptor_t *fdes, int x, int y, char ch, unsigned short color);

void draw_text(unsigned short display[], font_descriptor_t *fdes, int x, int y, char text[], unsigned short color);

#ifdef __cplusplus
} /* extern "C"*/
#endif

#endif  /*TEXT_DRAW_H*/
