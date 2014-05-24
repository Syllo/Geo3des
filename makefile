SRCPATH = src/
INCPATH = include/
OBJPATH = obj/
BINPATH = bin/
CC      = gcc -std=c99
CFLAGS = -O0 -I/usr/X11R6/include -IGL -Wall -I$(INCPATH)
LDFLAGS = -L/usr/X11R6/lib -lglut -lGL -lGLU -lm
DEBUGFLAGS = -g

vpath %.c $(SRCPATH)
vpath %.o $(OBJPATH)
vpath %.h $(INCPATH)

%.o : | $(OBJPATH)
	$(CC) -o $@ -c $< $(CFLAGS) $(DEBUGFLAGS)
	mv $@ $(OBJPATH)

Perlin.o : Perlin.c Perlin.h Vector.h
Vector.o : Vector.c Vector.h
Polygon.o : Polygon.c Polygon.h Vector.h

$(OBJPATH) :
	mkdir $(OBJPATH)

$(BINPATH) :
	mkdir $(BINPATH)

clean:
	@echo Removing obj and bin directory ...;\
		rm -r $(OBJPATH) $(BINPATH) 2>/dev/null;\
		echo Done.
