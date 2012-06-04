#include <assert.h>
#include <stdlib.h>
#include "subsample.h"
#include "gfx.h"


struct image *subsample(struct image *s, int xres, int yres)
{
   assert(s != NULL);
   assert(s->xres >= xres);
   assert(s->yres >= yres);
   assert((s->xres % xres) == 0);
   assert((s->yres % yres) == 0);

   int i,j;
   int x,y;
   int xwidth = s->xres / xres;
   int ywidth = s->yres / yres;

   struct image *newimage = new_image(xres,yres);

   // sum over (xwidth x ywidth) regions of the original image
   for(i=0; i < s->xres; i++)
   {
      for(j=0; j < s->yres; j++)
      {
         x = (i / xwidth);
         y = (j / ywidth);
         newimage->s[x][y] += s->s[i][j];
      }
   }

   // normalize the subsampled image
   int area = xwidth*ywidth;
   for(i=0; i < xres; i++)
   {
      for(j=0; j < yres; j++)
      {
         newimage->s[i][j] /= area;
      }
   }

   return newimage;
      
}
