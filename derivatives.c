#include <assert.h>
#include <stdlib.h>
#include "gfx.h"
#include "vector_field.h"

struct vector_field * compute_derivatives(struct image *e1, struct image *e2)
{
   assert(e1 != NULL);
   assert(e2 != NULL);
   assert(e1->xres == e2->xres);
   assert(e1->yres == e2->yres);

   struct vector_field *de = new_vector_field(e1->xres, e1->yres);
//   printf("de xres is %d\n", de->xres);
   int i,j;

   for(i=0; i < e1->xres-1; i++)
   {
      for(j=0; j < e1->yres-1; j++)
      {
         // compute local gradient
         de->s[i][j].x = (1/4.0) * (
            (e1->s[i+1][j] + e2->s[i+1][j] + e1->s[i+1][j+1] + e2->s[i+1][j+1])
            - (e1->s[i][j] + e2->s[i][j] + e1->s[i][j+1] + e2->s[i][j+1])
            );
         
         de->s[i][j].y = (1/4.0) * (
            (e1->s[i][j+1] + e2->s[i][j+1] + e1->s[i+1][j+1] + e2->s[i+1][j+1])
            - (e1->s[i][j] + e2->s[i][j] + e1->s[i+1][j] + e2->s[i+1][j])
            );

         de->s[i][j].t = (1/4.0) * (
            (e2->s[i][j] + e2->s[i][j+1] + e2->s[i+1][j] + e2->s[i+1][j+1])
            - (e1->s[i][j] + e1->s[i][j+1] + e1->s[i+1][j] + e1->s[i+1][j+1])
            );
      }
   }

   de->s[e1->xres-1][e1->yres-1].x = 0;
   de->s[e1->xres-1][e1->yres-1].y = 0;
   de->s[e1->xres-1][e1->yres-1].y = 0;
   return de;
}
