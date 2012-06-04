#ifndef _SUBSAMPLE_H
#define _SUBSAMPLE_H

#include "gfx.h"

// allocates a new (smaller) image containing the samples
// s->xres must be a multiple of xres, and s->yres must be a 
// multiple of yres.
struct image *subsample(struct image *s, int xres, int yres);


#endif
