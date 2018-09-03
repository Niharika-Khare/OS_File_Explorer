CC=g++
CFLAGS=-I
DEPS= list.h commandMod.h termSet.h

%o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

kakashi: kakashi.o
	$(CC) -o kakashi kakashi.o