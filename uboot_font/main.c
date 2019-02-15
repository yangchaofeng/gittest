#include <stdio.h>
#include <stdlib.h>


/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#include <fcntl.h>
#include "my.h"



int main(int argc, char *argv[]) {
	
	
	int i = 0;
	
	
	gfx_surface *surface = malloc(sizeof(gfx_surface));
	
	surface->free_on_destroy = false;
	surface->format = GFX_FORMAT_RGB_x888;
	surface->width = 240;
	surface->height = 320;
	surface->stride = 240;
	surface->alpha = MAX_ALPHA;
	
			surface->copyrect = &copyrect32;
			surface->fillrect = &fillrect32;
			surface->putpixel = &putpixel32;
			surface->pixelsize = 4;
			surface->len = surface->height * surface->stride * surface->pixelsize;
	
	surface->ptr = malloc(surface->len);
	surface->free_on_destroy = true;
	 unsigned char c[] = "234567";
	
	for (i = 0; i< 2; i++) {
		
		font_draw_char(surface, c[i], 0, 0, TEXT_COLOR);
		//printf("we will display %c in 3 second\n", c[i]);
		sleep(1);
	}
	yang_font_draw_char(surface, c[0], 0, 0, TEXT_COLOR);
	
	free(surface);
	
	printf("yangchaofeng add for test end\n");
	return 0;
}
