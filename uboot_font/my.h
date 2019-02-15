#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#include "gfx.h"


#include "include/font.h"
#include "include/font_10x18.h"
#include "include/font_6x10.h"
#include "include/font_6x11.h"
#include "include/font_7x14.h"
#include "include/font_8x16.h"
#include "include/font_8x8.h"
#include "include/font_acorn_8x8.h"
#include "include/font_mini_4x6.h"
#include "include/font_pearl_8x8.h"
#include "include/font_sun12x22.h"
#include "include/font_sun8x16.h"
#include "include/font_cn.h"

typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;
typedef signed char int8_t;
typedef short     int16_t;
typedef int       int32_t;
typedef long long int64_t;

typedef unsigned int uint;

#define LOCAL_TRACE 0

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
static int gfx_draw_rgb_bars(gfx_surface *surface)
{
	uint x, y;
	int color;

	for (y = 50; y < surface->height; y++) {
		//R
		for (x = 0; x < surface->width/3; x++) {
			color = 0xffff0000;
			gfx_putpixel(surface, x, y, color);
		}
		//G
		for (;x < 2*(surface->width/3); x++) {
			color = 0xff00ff00;
			gfx_putpixel(surface, x, y, color );
		}
		//B
		for (;x < surface->width; x++) {
			color = 0xff0000ff;
			gfx_putpixel(surface, x, y, color);
		}
	}

	return 0;
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

extern const unsigned char fontcn_8x16[200] ;
extern const unsigned char fontcn_12x16[200] ;
extern const unsigned char fontcn_16x16[200] ;
extern const unsigned char fontcn_24x24[2000] ;
extern const unsigned char fontcn_32x32[2000] ;


#define FONT_X	8
#define FONT_Y	16
#define OFFSET_X ((FONT_X%8)? (FONT_X/8) : ((FONT_X/8)-1))
#define BYTE_X ((FONT_X%8)? (FONT_X/8 +1) : (FONT_X/8))
void font_draw_char(gfx_surface *surface, unsigned char c, int x, int y, uint32_t color)
{
	uint i = 0,j = 0;
	uint32_t line;

	//int offset_x = (FONT_X%8)? (FONT_X/8) : ((FONT_X/8)-1);
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

	// draw this char into a buffer
	for (i = 0; i < FONT_Y; i++) {
		if (OFFSET_X ==0){
			line = fontdata_8x16[c * FONT_Y + i];
		} else if (OFFSET_X ==1){
			line = fontcn_12x16[c * FONT_Y*BYTE_X +BYTE_X* i] << 8 | fontcn_12x16[c * FONT_Y*BYTE_X +BYTE_X* i +1] ;
		}else if (OFFSET_X ==2){
			line = fontcn_24x24[c * FONT_Y*BYTE_X +BYTE_X* i] << 16 | 
				 fontcn_24x24[c * FONT_Y*BYTE_X +BYTE_X* i +1] << 8 | fontcn_24x24[c * FONT_Y*BYTE_X +BYTE_X* i +2] ;
		}else if (OFFSET_X ==3){
			line = fontcn_32x32[c * FONT_Y*BYTE_X +BYTE_X* i] << 24 | fontcn_32x32[c * FONT_Y*BYTE_X +BYTE_X* i +1] << 16 |
				 fontcn_32x32[c * FONT_Y*BYTE_X +BYTE_X* i +2] << 8 | fontcn_32x32[c * FONT_Y*BYTE_X +BYTE_X* i +3] ;		
		}else {

		}
		//line = fontdata_6x10[c * FONT_Y + i];
		for (j = 0; j < FONT_X; j++) {
			if (line & (0x80) << (OFFSET_X *8)) {
				printf("*");		
				gfx_putpixel(surface, x + j, y + i, color);
			}else{
				printf(" ");
			}
			if(j==FONT_X-1)
				printf("\n");
			line = line << 1;
		}
	}
	gfx_flush_rows(surface, y, y + FONT_Y);
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
void gfx_surface_destroy(struct gfx_surface *surface)
{
	if (surface->free_on_destroy)
		free(surface->ptr);
	free(surface);
}