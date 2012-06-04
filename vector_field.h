#ifndef _VECTOR_FIELD_H
#define _VECTOR_FIELD_H


struct vec3
{
   float x, y, t;
};


// a (x,y,t) triplet over a 2d grid
struct vector_field
{
   struct vec3 **s;
   int xres, yres;
};

struct vector_field *new_vector_field(int xres, int yres);
void free_vector_field(struct vector_field *s);


#endif
