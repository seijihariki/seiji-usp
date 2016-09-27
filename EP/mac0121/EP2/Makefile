CC:=gcc
CFLAGS:=-Wall -pedantic -O2 -ansi

ep2: restaUm.o board.o stack.o 
	$(CC) $(CFLAGS) -o $@ $^

# General formulas (for making objects)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -f *.o
