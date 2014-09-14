CFLAGS += -g
LFLAGS +=

all: oop.o object.o string.o array.o tree.o

clean:
	rm -rf *.o

dep:
	$(CC) $(CFLAGS) -M *.c *.h > .depend

.c.o:
	$(CC) $(CFLAGS) -c $< 

include .depend
