#ifndef _DERIVATIVES_H
#define _DERIVATIVES_H


#include "vector_field.h"
#include "gfx.h"
// given two images E1 and E2, where E2 is the frame after E1, it computes
// the vector fields Ex, Ey, and Et, returning it in a vector_field struct.

// the derivatives estimate an image at a time between E1 and E2, in pixel
// locations halfway between the ones in E1 and E2. The x and y dimensions
// of the returned vector fields are the same as E1 and E2 but the last row
// and last column contain meaningless values. in the end, you have to 
// shift the returned vector fields a half pixel in x and y.

// allocates new memory for the vector field. be careful for memory
// leaks.

struct vector_field *compute_derivatives(struct image *e1, struct image *e2);

#endif
