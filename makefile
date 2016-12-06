#/*== Stephanie Briere Americo ==*/

CFLAGS = -Wall -g
SDLFLAGS = -lSDL -lSDL_gfx -lm

all: wireframe

clean:
	-rm *.o

purge: clean
	-rm wireframe

# ----

wireframe: wireframe.o objread.o perspect.o
	gcc -o wireframe *.o $(CFLAGS) $(SDLFLAGS) 

# ----
wireframe.o: datatypes.h objread.h wireframe.c
	gcc -c wireframe.c $(CFLAGS)

objread.o: datatypes.h objread.h objread.c
	gcc -c objread.c $(CFLAGS)

perspect.o: datatypes.h perspect.h perspect.c
	gcc -c perspect.c $(CFLAGS)
