#include <stdio.h>
#include <stdlib.h>


/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#include <fcntl.h>
#include "my.h"

#define DISPLAY_X 720
#define DISPLAY_Y 1280
#define PIXEL_FORMAT 4// 2 rgb565 3 rgb888
#define TEXT_COLOR 0xffff0000 //0xffffffff //ARGB8888
int main(int argc, char *argv[]) {
	
	
	int i = 0, x = 0, y = 0;
	
	
	gfx_surface *surface = malloc(sizeof(gfx_surface));
	
	surface->free_on_destroy = false;
	surface->format = GFX_FORMAT_ARGB_8888;
	surface->width = DISPLAY_X;
	surface->height = DISPLAY_Y;
	surface->stride = DISPLAY_X;
	surface->alpha = MAX_ALPHA;
	
	surface->copyrect = &copyrect32;
	surface->fillrect = &fillrect32;
	surface->putpixel = &putpixel32;
	surface->pixelsize = PIXEL_FORMAT;
	surface->len = surface->height * surface->stride * surface->pixelsize;
	
	surface->ptr = malloc(surface->len);
	surface->free_on_destroy = true;
	unsigned char c[] = "yang1234567abcdef";
	//for cn test
	//unsigned char c[] = "yang1";
	
	for (i = 0; i< sizeof(c)-1; i++) {
		font_draw_char(surface, c[i], x, y, TEXT_COLOR);
		//for cn test
		//font_draw_char(surface, i, x, y, TEXT_COLOR);
		x += FONT_X +1;
		if (x + FONT_X > DISPLAY_X){
			x=0;
			y += FONT_Y +1;
		}	
	}

	gfx_draw_rgb_bars(surface);

	int fd = open("data.raw",O_WRONLY | O_CREAT);
	write(fd,surface->ptr, DISPLAY_X*DISPLAY_Y*PIXEL_FORMAT);
	close(fd);

	yang_font_draw_char(surface, c[0], 0, 0, TEXT_COLOR);
	
	gfx_surface_destroy(surface);
	
	printf("yang add for test end\n");
	return 0;
}
