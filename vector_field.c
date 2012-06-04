#include <stdlib.h>
#include "vector_field.h"


// coord system: origin at bottom left of image
// s[i][j] goes i units right and j units up
struct vector_field *new_vector_field(int xres, int yres)
{
   int i;
   struct vector_field *new = (struct vector_field *)malloc(sizeof(struct vector_field));
   new->xres = xres;
   new->yres = yres;
   new->s = (struct vec3 **)malloc(new->xres*sizeof(struct vec3 *));
   for(i=0; i < new->xres; i++)
   {
      new->s[i] = (struct vec3 *)calloc((new->yres), sizeof(struct vec3));
   }
   return new;
}


void free_vector_field(struct vector_field *s)
{
   int i;

   for(i=0; i < s->xres; i++)
   {
      free(s->s[i]);
   }

   free(s->s);
   free(s);
}
