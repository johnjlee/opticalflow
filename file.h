#ifndef _FILE_H
#define _FILE_H

#include "gfx.h"


struct image *read_pgm(FILE *f);
void write_pgm(struct image *s, FILE *f);

#endif
