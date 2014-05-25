SRCPATH = src/
INCPATH = include/
OBJPATH = obj/
BINPATH = bin/
CC      = gcc -std=gnu99
CFLAGS = -O0 -I/usr/X11R6/include -IGL -Wall -I$(INCPATH)
LDFLAGS = -L/usr/X11R6/lib -lglut -lGL -lGLU -lm
DEBUGFLAGS = -g

vpath %.c $(SRCPATH)
vpath %.o $(OBJPATH)
vpath %.h $(INCPATH)
vpath extrusion $(BINPATH)

extrusion : main.o Mesh.o Perlin.o Vector.o Polygon.o | bin
	$(CC) -o $@ $(OBJPATH)main.o $(OBJPATH)Mesh.o $(OBJPATH)Perlin.o $(OBJPATH)Vector.o $(OBJPATH)Polygon.o $(LDFLAGS) $(DEBUGFLAGS)
	mv $@ $(BINPATH)

%.o : | $(OBJPATH)
	$(CC) -o $@ -c $< $(CFLAGS) $(DEBUGFLAGS)
	mv $@ $(OBJPATH)

Perlin.o : Perlin.c Perlin.h Vector.h
Vector.o : Vector.c Vector.h
Polygon.o : Polygon.c Polygon.h Vector.h
Mesh.o : Mesh.c Mesh.h Polygon.h Vector.h Perlin.h
main.o : main.c Mesh.h


$(OBJPATH) :
	mkdir $(OBJPATH)

$(BINPATH) :
	mkdir $(BINPATH)

clean:
	@echo Removing obj and bin directory ...;\
		rm -r $(OBJPATH) $(BINPATH) 2>/dev/null;\
		echo Done.
