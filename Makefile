CC=gcc
CFLAGS=-ansi -pedantic -Wall -lMLV -lm
OBJ = Main.o Tree.o Image.o


ImageCompression : $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

Image.o : Image.c Image.h Tree.h

Tree.o : Tree.c Tree.h

%.o: %.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o

mrproper: clean
	rm -f EXEC
