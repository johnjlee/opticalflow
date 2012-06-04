#include <assert.h>
#include <stdlib.h>
#include "needles.h"

void render_needles(struct image *small, struct image *big,
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
   
   for(i=0; i < uv->xres - 1; i++)
   {
      for(j=0; j < uv->yres - 1; j++)
      {
         int centerx = i*xwidth + (xwidth/2);
         int centery = j*ywidth + (ywidth/2);
         
         // draw a nice little dot
         big->s[centerx][centery] = DOT_COLOR;
         big->s[centerx][centery+1] = DOT_COLOR;
         big->s[centerx+1][centery] = DOT_COLOR;
         big->s[centerx+1][centery+1] = DOT_COLOR;

         draw_needle(big, centerx, centery, centerx + uv->s[i][j].x,
                     centery + uv->s[i][j].y);
      }
   }
}


// bresenham's line algorithm
void draw_needle(struct image *im, int Ax, int Ay, int Bx, int By)
{
   int dX = abs(Bx-Ax);
   int dY = abs(By-Ay);
   int Xincr, Yincr;
   
   if (Ax > Bx) { Xincr=-1; } else { Xincr=1; }
   if (Ay > By) { Yincr=-1; } else { Yincr=1; }
   
   if (dX >= dY)
   {           
      
      int dPr = dY<<1;
      int dPru = dPr - (dX<<1);
      int P = dPr - dX;
      
      
      for (; dX>=0; dX--)
      {
         if(Ax <= im->xres && Ay <= im->yres &&
            Ax >= 0 && Ay >= 0)
         {
            im->s[Ax][Ay] = DOT_COLOR;
         }
         if (P > 0)               // is the pixel going right AND up?
         { 
            Ax+=Xincr;               // increment independent variable
            Ay+=Yincr;         // increment dependent variable
            P+=dPru;           // increment decision (for up)
         }
         else                     // is the pixel just going right?
         {
            Ax+=Xincr;         // increment independent variable
            P+=dPr;            // increment decision (for right)
         }
      }               
   }
   else              // if Y is the independent variable
   {
      int dPr   = dX<<1;
      int dPru  = dPr - (dY<<1);
      int P = dPr - dY;
      
      for (; dY>=0; dY--)
      {
         //      printf("%d %d\n",Ax,Ay);
         if(Ax <= im->xres && Ay <= im->yres &&
            Ax >= 0 && Ay >= 0)
         {
            im->s[Ax][Ay] = DOT_COLOR;
         }
         if (P > 0)               // is the pixel going up AND right?
         { 
            Ax+=Xincr;         // increment dependent variable
            Ay+=Yincr;         // increment independent variable
            P+=dPru;           // increment decision (for up)
         }
         else                     // is the pixel just going up?
         {
            Ay+=Yincr;         // increment independent variable
            P+=dPr;            // increment decision (for right)
         }
      }               
   }  
}
