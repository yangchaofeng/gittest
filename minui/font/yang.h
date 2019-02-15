#include <sys/types.h>

#include <functional>
#include <string>
#include <vector>


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <memory>


struct GRSurface {
  int width;
  int height;
  int row_bytes;
  int pixel_bytes;
  unsigned char* data;
};

struct GRFont {
  GRSurface* texture;
  int char_width;
  int char_height;
};

enum GRRotation {
  ROTATION_NONE = 0,
  ROTATION_RIGHT = 1,
  ROTATION_DOWN = 2,
  ROTATION_LEFT = 3,
};


GRSurface gr_framebuffer[2];
int gr_init();
void gr_exit();

int gr_fb_width();
int gr_fb_height();

void gr_flip();
void gr_fb_blank(bool blank);

void gr_clear();  // clear entire surface to current color
void gr_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
void gr_fill(int x1, int y1, int x2, int y2);

void gr_texticon(int x, int y, GRSurface* icon);

const GRFont* gr_sys_font();
int gr_init_font(const char* name, GRFont** dest);
void gr_text(const GRFont* font, int x, int y, const char* s, bool bold);
int gr_measure(const GRFont* font, const char* s);
void gr_font_size(const GRFont* font, int* x, int* y);

void gr_blit(GRSurface* source, int sx, int sy, int w, int h, int dx, int dy);
unsigned int gr_get_width(GRSurface* surface);
unsigned int gr_get_height(GRSurface* surface);


