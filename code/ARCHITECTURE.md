# APO Project Architecture
Here you can find files and functions description, what they do, arguments.


# colors.h
Makes all of operations with colors.

### get_color
```
unsigned short get_color (int ri, int gi, int bi)
```
Takes current color indexes, converts them into RGB565 and returns resulting color.

### get_led_color
```
unsigned int get_led_color (int ri, int gi, int bi)
```
Takes current color indexes, converts them into RGB and returns resulting color.

### change_color
```
void change_color (int* knob_pos, int* knob_pos_old, int* color_idx)
```
Changes color index according to knob position.

### change_colors
```
void change_colors (int* rk, int* rk_old, int* ri, int* gk, 
                    int* gk_old, int* gi, int* bk, int* bk_old, int* bi)
```
Simple function that takes knob positions and convert them to color indexes using change_color.



# draw_display.h
Draw some scene parts on the display.

### draw_greetings
```
void draw_greetings (unsigned short display[], font_descriptor_t *fdes, int x,
                     int y, unsigned short col)
```
Takes greeting position and draws it on the display.

### draw_menu
```
void draw_menu (unsigned short display[], font_descriptor_t *fdes, unsigned short col, 
                unsigned short rk, unsigned short gk, unsigned short bk)
```
Takes knobs positions and draws menu on the display.

### draw_white_background
```
void draw_white_background (unsigned short display[], font_descriptor_t *fdes)
```
Fills display with white color for menu scene.

### draw_color_sample
```
void draw_color_sample (unsigned short display[], font_descriptor_t *fdes, 
                        unsigned short color, bool change_size, int square_size)
```
Takes brush size and draws sample on the display.



# fill_display.h
Fill desk display with black or some needed colors.

### fill_display_black
```
void fill_display_black (unsigned char *parlcd_mem_base) 
```
Fill display with black color.

### fill_display_rgb
```
void fill_display_rgb (unsigned char *parlcd_mem_base, unsigned short display[])
```
Fill display with needed colors according to pixel map.



# knobs.h
Do everything that is related to knobs.

### get_knobs
```
void get_knobs (int *knob, unsigned char **mem_base, int *rk, int *gk, int *bk)
```
Writes knob values by taking them from the desk.

### buttons_action
```
bool buttons_action (int *knob, volatile unsigned int** led_stripe, bool *menu, 
                     unsigned short map[][320 + max_square_size], bool *is_drawing, 
                     volatile unsigned int **led1, struct timespec *loop_delay, 
                     bool *salaam, bool *change_size)
```
Change actions according to knobs presses.



# scenes.h
Menu and paint scenes.

### fill_square
```
void fill_square (int *square_size, int *xx, int *yy, unsigned short display[], 
                  unsigned short map[][320 + max_square_size], font_descriptor_t *fdes, 
                  bool *is_drawing, unsigned short *color)
```
Redraws paint scene according to brush size and position.

### paint_scene
```
void paint_scene (int *square_size, int *gk, int *xx, int *yy, int *knob, 
                  unsigned short display[], unsigned short map[][320 + max_square_size], 
                  font_descriptor_t *fdes, bool *is_drawing, unsigned short *color)
```
Takes brush position according to knobs position and redraws itself according to pixel map.

### menu_scene
```
void menu_scene (unsigned short display[], font_descriptor_t *fdes, int *square_size, 
                 bool *salaam, bool *change_size, unsigned int *col, 
                 volatile unsigned int **led2, uint32_t *rgb_knobs_value, int *knob, 
                 unsigned short *color, int *ri, int *gk, int *gi, int *bi)
```
Takes boolean arguments from main and according to them enters to needed scenes.



# text_draw.h
Draw some text or chars on the mzAPO desk display.

### draw_pixel
```
void draw_pixel (unsigned short display[], font_descriptor_t *fdes, int x, int y, 
                 unsigned short color)
```
Takes pixel position and draw on the display.

### draw_pixel_big
```
void draw_pixel_big (unsigned short display[], font_descriptor_t *fdes, int x, int y, 
                     unsigned short color)
```
Takes pixel position and draw on the display, according to scale.

### char_width
```
int char_width (font_descriptor_t *fdes, int ch)
```
Takes char as integer, calculates and returns chars width.

### draw_char
```
void draw_char (unsigned short display[], font_descriptor_t *fdes, int x, int y, 
                char ch, unsigned short color)
```
Takes char, char position, char color, draw it on the display.

### draw_text
```
void draw_text (unsigned short display[], font_descriptor_t *fdes, int x, int y, 
                char text[], unsigned short color)
```
Takes text, text position, chars color, draw string on the display.



# update_led_line.h
Controls led stripe.

### update_led_line
```
void update_led_line (volatile unsigned int** led_stripe, uint32_t *lighting_leds, 
                      unsigned short *k, bool *left)
```
Forses leds on stripe go forward and backward.

### turn_off_leds
```
void turn_off_leds (volatile unsigned int* led1, volatile unsigned int* led2, 
                    volatile unsigned int* led_stripe)
```
Turns off leds as program finished working.
