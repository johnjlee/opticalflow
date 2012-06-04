#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "gfx.h"


void write_pgm(struct image *s, FILE *f)
{
   assert(f != NULL);
   int numpoints=0;
   int j,i;
   fprintf(f,"P2\n%d %d\n%d\n", s->xres, s->yres, MAXGRAY);
   for(j=s->yres-1; j>=0; j--)
   {
      for(i=0; i<s->xres; i++)
      {
         numpoints++;
         if((numpoints % 17) == 0)
            fprintf(f, "\n");

         fprintf(f,"%d ",s->s[i][j]);
      }

   }
}


struct image *read_pgm(FILE *f)
{
   assert(f != NULL);
   
   void *temp=(void *)malloc(2*sizeof(char));
   int i,j;
   
   struct image *new = (struct image *)malloc(sizeof(struct image));
   
   fscanf(f, "%s", (char *)temp);                  // magic pnm number - ignore
   fscanf(f, "%d %d", &(new->xres), &(new->yres)); // xres, yres
   fscanf(f, "%f", (float *)temp);                 // maxcolors: assume 255
   
   free(temp);

   new->s = (int **)malloc(new->xres*sizeof(int *));
   
   for(i=0; i < new->xres; i++)
   {
      new->s[i] = (int *)malloc((new->yres)*sizeof(int));
   }
   
   for(i = new->yres-1; i >= 0; i--)
   {
      for(j = 0; j < new->xres; j++)
      {
         fscanf(f, "%d", 
                &(new->s[j][i]));
      }
   }
   return new;
}
