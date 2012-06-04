#include <assert.h>
#include <stdlib.h>
#include "foe.h"

void render_foe(struct image *small, struct image *big,
                    struct vector_field *uv)
{
   assert(small != NULL);
   assert(big != NULL);
   assert(uv != NULL);
   assert(small->xres == uv->xres);
   assert(small->yres == uv->yres);
   assert((big->xres % small->xres) == 0);
   assert((big->yres % small->yres) == 0);
   
   int i,j;
   int xwidth = big->xres / small->xres;
   int ywidth = big->yres / small->yres;
   
   int besti=0, bestj=0;
   float minval = (uv->s[0][0].x)*(uv->s[0][0].x) +
      (uv->s[0][0].y)*(uv->s[0][0].y);

   for(i=3; i < uv->xres - 3; i++)
   {
      for(j=3; j < uv->yres - 3; j++)
      {
         float val = (uv->s[i][j].x)*(uv->s[i][j].x) +
            (uv->s[i][j].y)*(uv->s[i][j].y);

         if(val < minval)
         {
            minval = val;
            besti = i;
            bestj = j;
         }
      }
   }

   int centerx = besti*xwidth + (xwidth/2);
   int centery = bestj*ywidth + (ywidth/2);
   
   // draw a nice big dot

   for(i=centerx-2; i <= centerx+2; i++)
   {
      for(j=centery-2; j <= centery+2; j++)
      {
         big->s[i][j] = 255;
      }
   }

}
