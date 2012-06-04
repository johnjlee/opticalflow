#ifndef _FOE_H
#define _FOE_H

#include "gfx.h"
#include "vector_field.h"

// renders a dot at min(uv) onto "big". "small" is the subsampled image,
// big is the non-subsampled image.
void render_foe(struct image *small, struct image *big, 
                struct vector_field *uv);

#endif
