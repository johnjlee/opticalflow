CC=gcc
CFLAGS=-Wall -Wstrict-prototypes
OFILES=file.o gfx.o subsample.o vector_field.o derivatives.o optical_flow.o needles.o foe.o

all: test

gfx.o: gfx.c gfx.h
file.o: file.h file.c gfx.h
subsample.o: gfx.c gfx.h subsample.c subsample.h
vector_field.o: vector_field.c vector_field.h
derivatives.o: derivatives.h derivatives.c gfx.o
optical_flow.o: optical_flow.c vector_field.o gfx.o
needles.o: needles.c needles.h gfx.o vector_field.o
foe.o: foe.c foe.h gfx.o vector_field.o

test: $(OFILES) test.c
	$(CC) $(CFLAGS) -lm $(OFILES) test.c -o test

clean:
	rm -rf *.o
	rm -f *~
	rm -f test