#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gfx.h"
#include "file.h"
#include "subsample.h"
#include "derivatives.h"
#include "optical_flow.h"
#include "needles.h"
#include "foe.h"


#define WIDTH 640
#define HEIGHT 480
#define SUBSAMPLE_X 80
#define SUBSAMPLE_Y 60
#define LAMBDA 50
#define NUMITERS 100

void usage(void)
{
   printf("Usage: ./test output_basename <pgmfilenames>\n");
   printf("Must use at least two files.\n");
}

int main(int argc, char** argv)
{

   int i,j,m;
   if(argc < 4)
   {
      usage();
      return 0;
   }
   
   struct image *first, *sub1;
   struct image *second, *sub2;
   
   // initial image
   FILE *f = fopen(argv[2], "r");
   first = read_pgm(f);
   fclose(f);
   sub1 = subsample(first, SUBSAMPLE_X, SUBSAMPLE_Y);
   

   for(m=3; m < argc-1; m++)
   {
      // open argv[m] and argv[m+1]
      // compute flow
      // save output in file m
      
      printf("second image is %s %d\n", argv[m], m);
      FILE *g = fopen(argv[m], "r");
      second = read_pgm(g);
      fclose(g);

      sub2 = subsample(second, SUBSAMPLE_X, SUBSAMPLE_Y);

      struct vector_field *derivs = compute_derivatives(sub1, sub2);
      struct vector_field *uv2 = compute_optical_flow(sub1, derivs, LAMBDA, NUMITERS);


   // scale
      float xmax=0, ymax=0;
      for(i=0; i < uv2->xres; i++)
      {
         for(j=0; j < uv2->yres; j++)
         {
            if(fabsf(uv2->s[i][j].x) > xmax)
            xmax = fabsf(uv2->s[i][j].x);
            
            if(fabsf(uv2->s[i][j].y) > ymax)
               ymax = fabsf(uv2->s[i][j].y);
         }
      }
      
      printf("%f %f\n", xmax, ymax);
      if(xmax == 0 && ymax == 0)
      {
         printf("error\n");
         continue;
      }
      // what do we want the max needle length to be?
      // for now, let the max (in one dimension) to be min(xwidth, ywidth)
      float xwidth = (WIDTH/SUBSAMPLE_X);
      float ywidth = (HEIGHT/SUBSAMPLE_Y);
      
      float width = xwidth < ywidth ? xwidth : ywidth;
      
      for(i=0; i < uv2->xres; i++)
      {
         for(j=0; j < uv2->yres; j++)
         {
            uv2->s[i][j].x *= (float)width/xmax;
            uv2->s[i][j].y *= (float)width/ymax;
         }
      }

      render_needles(sub1, first, uv2);
//      render_foe(sub1, first, uv2);

      char filename[512];
      sprintf(filename, "%s%.6d.pgm", argv[1], m-2);
      g = fopen(filename, "w");
      write_pgm(first, g);
      fclose(g);


      free_image(first);
      free_image(sub1);
      free_vector_field(derivs);
      free_vector_field(uv2);
      sub1 = sub2;
      first = second;

   }

   return 0;
}
