#/*== Stephanie Briere Americo ==*/

CFLAGS = -Wall -g -lSDL_gfx -lSDL -lSDL2

all: wireframe

clean:
	-rm *.o

purge: clean
	-rm wireframe

# ----

wireframe: wireframe.o objread.o
	gcc -o wireframe $(CFLAGS) *.o

# ----
wireframe.o: datatypes.h objread.h wireframe.c
	gcc -c wireframe.c $(CFLAGS)

objread.o: datatypes.h objread.h objread.c
	gcc -c objread.c $(CFLAGS)
