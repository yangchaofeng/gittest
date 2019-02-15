#include <sys/types.h>
#include <functional>
#include <string>
#include <vector>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory>

#include <sys/stat.h>
#include <fcntl.h>

#include "font_10x18.h"


#include "yang.h"

static GRFont* gr_font = NULL;

#define SURFACE_DATA_ALIGNMENT 8


static int overscan_percent = 0;

static int overscan_offset_x = 0;
static int overscan_offset_y = 0;

static uint32_t gr_current = ~0;
static  uint32_t alpha_mask = 0xff000000;

static GRSurface* gr_draw = NULL;
static GRRotation rotation = ROTATION_NONE;

static bool outside(int x, int y) {
  return x < 0 || x >= (rotation % 2 ? gr_draw->height : gr_draw->width) || y < 0 ||
         y >= (rotation % 2 ? gr_draw->width : gr_draw->height);
}

static inline uint32_t pixel_blend(uint8_t alpha, uint32_t pix) {
  
  if (alpha == 255) return gr_current;
  if (alpha == 0) return pix;
  uint32_t pix_r = pix & 0xff;
  uint32_t pix_g = pix & 0xff00;
  uint32_t pix_b = pix & 0xff0000;
  uint32_t cur_r = gr_current & 0xff;
  uint32_t cur_g = gr_current & 0xff00;
  uint32_t cur_b = gr_current & 0xff0000;

  uint32_t out_r = (pix_r * (255 - alpha) + cur_r * alpha) / 255;
  uint32_t out_g = (pix_g * (255 - alpha) + cur_g * alpha) / 255;
  uint32_t out_b = (pix_b * (255 - alpha) + cur_b * alpha) / 255;
  
  return (out_r & 0xff) | (out_g & 0xff00) | (out_b & 0xff0000) | (gr_current & 0xff000000);
}

// increments pixel pointer right, with current rotation.
static void incr_x(uint32_t** p, int row_pixels) {
  if (rotation % 2) {
    *p = *p + (rotation == 1 ? 1 : -1) * row_pixels;
  } else {
    *p = *p + (rotation ? -1 : 1);
  }
}

// increments pixel pointer down, with current rotation.
static void incr_y(uint32_t** p, int row_pixels) {
  if (rotation % 2) {
    *p = *p + (rotation == 1 ? -1 : 1);
  } else {
    *p = *p + (rotation ? -1 : 1) * row_pixels;
  }
}

// returns pixel pointer at given coordinates with rotation adjustment.
static uint32_t* pixel_at(GRSurface* surf, int x, int y, int row_pixels) {
  switch (rotation) {
    case ROTATION_NONE:
      return reinterpret_cast<uint32_t*>(surf->data) + y * row_pixels + x;
    case ROTATION_RIGHT:
      return reinterpret_cast<uint32_t*>(surf->data) + x * row_pixels + (surf->width - y);
    case ROTATION_DOWN:
      return reinterpret_cast<uint32_t*>(surf->data) + (surf->height - 1 - y) * row_pixels +
             (surf->width - 1 - x);
    case ROTATION_LEFT:
      return reinterpret_cast<uint32_t*>(surf->data) + (surf->height - 1 - x) * row_pixels + y;
    default:
      printf("invalid rotation %d", rotation);
  }
  return NULL;
}

static void text_blend(uint8_t* src_p, int src_row_bytes, uint32_t* dst_p, int dst_row_pixels,
                       int width, int height) {
  uint8_t alpha_current = static_cast<uint8_t>((alpha_mask & gr_current) >> 24);
  for (int j = 0; j < height; ++j) {
    uint8_t* sx = src_p;
    uint32_t* px = dst_p;
    for (int i = 0; i < width; ++i, incr_x(&px, dst_row_pixels)) {
      uint8_t a = *sx++;
      if (alpha_current < 255) a = (static_cast<uint32_t>(a) * alpha_current) / 255;
      *px = pixel_blend(a, *px);

	if(1) {
			if(gr_current  == *px) /* == means this pixel should be change*/
				printf("*");
			else
				printf(" ");

		       //printf("0x%x 0x%x 0x%x\n",a, gr_current, *px);
			if(i==width-1)
				printf("\n");
    	}
    }
    src_p += src_row_bytes;
    incr_y(&dst_p, dst_row_pixels);
  }
}

void gr_text(const GRFont* font, int x, int y, const char* s, bool bold) {
  if (!font || !font->texture || (gr_current & alpha_mask) == 0) return;

  if (font->texture->pixel_bytes != 1) {
    printf("gr_text: font has wrong format\n");
    return;
  }

  bold = bold && (font->texture->height != font->char_height);

  x += overscan_offset_x;
  y += overscan_offset_y;

  unsigned char ch;
  while ((ch = *s++)) {
    if (outside(x, y) || outside(x + font->char_width - 1, y + font->char_height - 1)) break;

    if (ch < ' ' || ch > '~') {
      ch = '?';
    }

    int row_pixels = gr_draw->row_bytes / gr_draw->pixel_bytes;
    uint8_t* src_p = font->texture->data + ((ch - ' ') * font->char_width) +
                     (bold ? font->char_height * font->texture->row_bytes : 0);
    uint32_t* dst_p = pixel_at(gr_draw, x, y, row_pixels);

	if (1) {
			for (int j = 0; j < font->char_height; ++j) {
				uint8_t* sx = src_p;
				for (int i = 0; i < font->char_width; ++i) {
					uint8_t a = *sx++;

					printf("%2x ",a);
					if(i==font->char_width-1)
						printf("\n");
				}
				src_p += font->texture->row_bytes;
			}
			src_p = font->texture->data + ((ch - ' ') * font->char_width) +
		                     (bold ? font->char_height * font->texture->row_bytes : 0);
		}

    text_blend(src_p, font->texture->row_bytes, dst_p, row_pixels, font->char_width,
               font->char_height);

    x += font->char_width;
  }
}


void gr_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
  uint32_t r32 = r, g32 = g, b32 = b, a32 = a;
#if defined(RECOVERY_ABGR) || defined(RECOVERY_BGRA)
  gr_current = (a32 << 24) | (r32 << 16) | (g32 << 8) | b32;
#else
  gr_current = (a32 << 24) | (b32 << 16) | (g32 << 8) | r32;
#endif
}

void gr_fill(int x1, int y1, int x2, int y2) {
  x1 += overscan_offset_x;
  y1 += overscan_offset_y;

  x2 += overscan_offset_x;
  y2 += overscan_offset_y;

  if (outside(x1, y1) || outside(x2 - 1, y2 - 1)) return;

  int row_pixels = gr_draw->row_bytes / gr_draw->pixel_bytes;
  uint32_t* p = pixel_at(gr_draw, x1, y1, row_pixels);
  uint8_t alpha = static_cast<uint8_t>(((gr_current & alpha_mask) >> 24));
  if (alpha > 0) {
    for (int y = y1; y < y2; ++y) {
      uint32_t* px = p;
      for (int x = x1; x < x2; ++x) {
        *px = pixel_blend(alpha, *px);
        incr_x(&px, row_pixels);
      }
      incr_y(&p, row_pixels);
    }
  }
}


static void gr_init_font(void) {
  gr_font = static_cast<GRFont*>(calloc(1, sizeof(*gr_font)));
  gr_font->texture = static_cast<GRSurface*>(malloc(sizeof(*gr_font->texture)));
  gr_font->texture->width = font.width;
  gr_font->texture->height = font.height;
  gr_font->texture->row_bytes = font.width;
  gr_font->texture->pixel_bytes = 1;

  unsigned char* bits = static_cast<unsigned char*>(malloc(font.width * font.height));
  gr_font->texture->data = bits;

  unsigned char data;
  unsigned char* in = font.rundata;
  while ((data = *in++)) {
    memset(bits, (data & 0x80) ? 255 : 0, data & 0x7f);
    bits += (data & 0x7f);
  }

  gr_font->char_width = font.char_width;
  gr_font->char_height = font.char_height;
}

#define DISPLAY_X	100
#define DISPLAY_Y	18
#define PIXEL_FORMAT 3 // 2 rgb565 3 rgb888

int main(void)
{
	/* 1: init gr_font */
	gr_init_font();
	printf("yang add %s:%d ----\n", __func__, __LINE__);

	/* 2: init gr_draw */
	gr_draw = static_cast<GRSurface*>(malloc(sizeof(GRSurface)));
	gr_draw->width = DISPLAY_X;
	gr_draw->height = DISPLAY_Y;
	gr_draw->row_bytes = DISPLAY_X*PIXEL_FORMAT;
	gr_draw->pixel_bytes = PIXEL_FORMAT;
	gr_draw->data = static_cast<unsigned char*>(malloc(gr_draw->height * gr_draw->row_bytes));

	memset(gr_draw->data, 0, gr_draw->height * gr_draw->row_bytes);

	overscan_offset_x = gr_draw->width * overscan_percent / 100;
	overscan_offset_y = gr_draw->height * overscan_percent / 100;

	/* 3: draw a char to gr_draw */
	gr_color(0x11, 0x22, 0x33, 255);
	gr_fill(0, 0, DISPLAY_X, DISPLAY_Y);

	gr_color(0x77, 0x88, 0x99, 255);
	char line[]="yang";
	gr_text(gr_font, 0, 0, line, 1);


	/* 4: wirte gr_draw->data to file */
	int fd = open("data.raw",O_WRONLY | O_CREAT);
	write(fd,gr_draw->data, DISPLAY_X*DISPLAY_Y*PIXEL_FORMAT);
	close(fd);

	sleep(1);

	free(gr_draw);
	printf("yang add %s:%d ----\n", __func__, __LINE__);
	return 0;
}
