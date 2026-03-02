#define _POSIX_C_SOURCE 200112L

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
 
#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"
#include "font_types.h"

#include "text_draw.h"

#define _POSIX_C_SOURCE 200112L 
#define M_PI 3.1415

int scale=6;
 
unsigned int hsv2rgb_lcd(int hue, int saturation, int value) {
  hue = (hue%360);    
  float f = ((hue%60)/60.0);
  int p = (value*(255-saturation))/255;
  int q = (value*(255-(saturation*f)))/255;
  int t = (value*(255-(saturation*(1.0-f))))/255;
  unsigned int r,g,b;
  if (hue < 60){
    r = value; g = t; b = p;
  } else if (hue < 120) {
    r = q; g = value; b = p;
  } else if (hue < 180) {
    r = p; g = value; b = t;
  } else if (hue < 240) {
    r = p; g = q; b = value;
  } else if (hue < 300) {
    r = t; g = p; b = value;
  } else {
    r = value; g = p; b = q;
  }
  r>>=3;
  g>>=2;
  b>>=3;
  return (((r&0x1f)<<11)|((g&0x3f)<<5)|(b&0x1f));
}
 
void draw_pixel(unsigned short display[], font_descriptor_t *fdes, int x, int y, unsigned short color) {
  if (x>=0 && x<480 && y>=0 && y<320) {
    display[x+480*y] = color;
  }
}
 
void draw_pixel_big(unsigned short display[], font_descriptor_t *fdes, int x, int y, unsigned short color) {
  int i,j;
  for (i=0; i<scale; i++) {
    for (j=0; j<scale; j++) {
      draw_pixel(display, fdes, x+i, y+j, color);
    }
  }
}
 
int char_width(font_descriptor_t *fdes, int ch) {
  int width;
  if (!fdes->width) {
    width = fdes->maxwidth;
  } else {
    width = fdes->width[ch-fdes->firstchar];
  }
  return width;
}

void draw_char(unsigned short display[], font_descriptor_t *fdes, int x, int y, char ch, unsigned short color) {
  int w = char_width(fdes, ch);
  const font_bits_t *ptr;
  if ((ch >= fdes->firstchar) && (ch-fdes->firstchar < fdes->size)) {
    if (fdes->offset) {
      ptr = &fdes->bits[fdes->offset[ch-fdes->firstchar]];
    } else {
      int bw = (fdes->maxwidth+15)/16;
      ptr = &fdes->bits[(ch-fdes->firstchar)*bw*fdes->height];
    }
    int i, j;
    for (i=0; i<fdes->height; i++) {
      font_bits_t val = *ptr;
      for (j=0; j<w; j++) {
        if ((val&0x8000)!=0) {
          draw_pixel_big(display, fdes, x+scale*j, y+scale*i, color);
        }
        val<<=1;
      }
      ptr++;
    }
  }
}

void draw_text(unsigned short display[], font_descriptor_t *fdes, int x, int y, char text[], unsigned short color) {
  for (int i = 0; text[i] != '\0'; i++) {
    draw_char(display, fdes, x, y, text[i], color);
    x += char_width(fdes, text[i]) * scale;
  }
}
 