#ifndef FILL_DISPLAY_H
#define FILL_DISPLAY_H

#ifdef __cplusplus
extern "C" {
#endif

void fill_display_black(unsigned char *parlcd_mem_base) {
  // Fill up display with black color
  parlcd_write_cmd(parlcd_mem_base, 0x2c);
  for (int ptr = 0; ptr < 480*320 ; ptr++) 
    parlcd_write_data(parlcd_mem_base, 0);
}

void fill_display_rgb(unsigned char *parlcd_mem_base, unsigned short display[]) {
  // Fill up display with some color
  parlcd_write_cmd(parlcd_mem_base, 0x2c);
  for (int ptr = 0; ptr < 480*320 ; ptr++) 
      parlcd_write_data(parlcd_mem_base, display[ptr]);
}

#ifdef __cplusplus
} /* extern "C"*/
#endif

#endif  /*FILL_DISPLAY_H*/
