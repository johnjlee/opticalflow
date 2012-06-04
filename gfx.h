#ifndef _GFX_H
#define _GFX_H

#define MAXGRAY 255

struct image
{
   int **s;
   int xres, yres;
};

struct image *new_image(int xres, int yres);
void free_image(struct image *s);

#endif
