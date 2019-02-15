#include <stdio.h>
#include <stdlib.h>

#include "font.h"
//#include "include/font_10x18.h"
#include "include/font_6x10.h"
//#include "include/font_6x11.h"
//#include "include/font_7x14.h"
//#include "include/font_8x16.h"
//#include "include/font_8x8.h"
//#include "include/font_acorn_8x8.h"
//#include "include/font_mini_4x6.h"
//#include "include/font_pearl_8x8.h"
//#include "include/font_sun12x22.h"
//#include "include/font_sun8x16.h"

#define false 0
#define true 1
typedef int bool;
typedef unsigned int uint;
typedef unsigned int       uint32_t;


typedef enum {
	GFX_FORMAT_RGB_565,
	GFX_FORMAT_ARGB_8888,
	GFX_FORMAT_RGB_x888,

	GFX_FORMAT_MAX
} gfx_format;

#define MAX_ALPHA 255

#define TEXT_COLOR 0xffffffff

typedef struct gfx_surface {
	void *ptr;
	bool free_on_destroy;
	gfx_format format;
	uint width;
	uint height;
	uint stride;
	uint pixelsize;
	size_t len;
	uint alpha;

	// function pointers
	void (*copyrect)(struct gfx_surface *, uint x, uint y, uint width, uint height, uint x2, uint y2);
	void (*fillrect)(struct gfx_surface *, uint x, uint y, uint width, uint height, uint color);
	void (*putpixel)(struct gfx_surface *, uint x, uint y, uint color);
	void (*flush)(uint starty, uint endy);
} gfx_surface;




static void copyrect32(gfx_surface *surface, uint x, uint y, uint width, uint height, uint x2, uint y2)
{
	// copy
	const uint32_t *src = &((const uint32_t *)surface->ptr)[x + y * surface->stride];
	uint32_t *dest = &((uint32_t *)surface->ptr)[x2 + y2 * surface->stride];
	uint stride_diff = surface->stride - width;

	if (dest < src) {
		uint i, j;
		for (i=0; i < height; i++) {
			for (j=0; j < width; j++) {
				*dest = *src;
				dest++;
				src++;
			}
			dest += stride_diff;
			src += stride_diff;
		}
	} else {
		// copy backwards
		src += height * surface->stride + width;
		dest += height * surface->stride + width;

		uint i, j;
		for (i=0; i < height; i++) {
			for (j=0; j < width; j++) {
				*dest = *src;
				dest--;
				src--;
			}
			dest -= stride_diff;
			src -= stride_diff;
		}
	}
}

static void fillrect32(gfx_surface *surface, uint x, uint y, uint width, uint height, uint color)
{
	uint32_t *dest = &((uint32_t *)surface->ptr)[x + y * surface->stride];
	uint stride_diff = surface->stride - width;
	
	uint i, j;
	for (i=0; i < height; i++) {
		for (j=0; j < width; j++) {
			*dest = color;
			dest++;
		}
		dest += stride_diff;
	}
}

static void putpixel32(gfx_surface *surface, uint x, uint y, uint color)
{
	uint32_t *dest = &((uint32_t *)surface->ptr)[x + y * surface->stride];

	*dest = color;
}

void gfx_putpixel(gfx_surface *surface, uint x, uint y, uint color)
{
	if (y >= surface->height)
		return;

	surface->putpixel(surface, x, y, color);
}

void gfx_flush_rows(struct gfx_surface *surface, uint start, uint end)
{
	if (start > end) {
		uint temp = start;
		start = end;
		end = temp;
	}

	if (start >= surface->height)
		return;
	if (end >= surface->height)
		end = surface->height - 1;


	if (surface->flush)
		surface->flush(start, end);

}
extern const unsigned char fontdata_10x18[9216];//
extern const unsigned char fontdata_6x10[];//
extern const unsigned char fontdata_6x11[11*256];//
extern const unsigned char fontdata_7x14[3584];//
extern const unsigned char fontdata_8x16[4096];//
extern const unsigned char fontdata_8x8[2048];//
extern const unsigned char acorndata_8x8[];//
extern const unsigned char fontdata_mini_4x6[1536];//
extern const unsigned char fontdata_pearl8x8[2048];//
extern const unsigned char fontdata_sun12x22[11264] ;//
extern const unsigned char fontdata_sun8x16[4096] ;//

#define FONT_X	6
#define FONT_Y	10
void font_draw_char(gfx_surface *surface, unsigned char c, int x, int y, uint32_t color)
{
	uint i,j;
	uint line;

	// draw this char into a buffer
	for (i = 0; i < FONT_Y; i++) {
		//line = FONT[c * FONT_Y + i];
		//line = fontdata_10x18[c * FONT_Y + i]; //X
		//line = fontdata_6x10[c * FONT_Y + i];//OK
		//line = fontdata_6x11[c * FONT_Y + i];//OK
		//line = fontdata_7x14[c * FONT_Y + i];//OK
		//line = fontdata_8x16[c * FONT_Y + i];//OK
		//line = fontdata_8x8[c * FONT_Y + i];//OK
		//line = acorndata_8x8[c * FONT_Y + i];//OK
		//line = fontdata_mini_4x6[c * FONT_Y + i];//OK
		//line = fontdata_pearl8x8[c * FONT_Y + i];//OK
		//line = fontdata_sun12x22[c * FONT_Y + i];//X
		//line = fontdata_sun8x16[c * FONT_Y + i];
		line = fontdata_6x10[c * FONT_Y + i];
		for (j = 0; j < FONT_X; j++) {
			if (line & 0x1) {
				printf("*");		
				//gfx_putpixel(surface, x + j, y + i, color);
			}else{
				printf(" ");
			}
			if(j==FONT_X-1)
				printf("\n");
			line = line >> 1;
		}
	}
	//gfx_flush_rows(surface, y, y + FONT_Y);
}


void yang_font_draw_char(gfx_surface *surface, unsigned char c, int x, int y, uint32_t color)
{
	uint i,j;
	uint line;

	printf("\n");
	// draw this char into a buffer
	for (i = 0; i < FONT_Y; i++) {
		line = FONT[c * FONT_Y + i];
		for (j = 0; j < FONT_X; j++) {
			if (line & 0x1) {
				printf("*");		
				//gfx_putpixel(surface, x + j, y + i, color);
			}else{
				printf("*");
			}
			if(j==FONT_X-1)
				printf("\n");
			line = line >> 1;
		}
	}
	//gfx_flush_rows(surface, y, y + FONT_Y);
}
