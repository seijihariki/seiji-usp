CC:=gcc
CFLAGS:=-Wall -pedantic -g -ansi

ep3: tresReversao.o cvector.o stack.o 
	$(CC) $(CFLAGS) -o $@ $^

# General formulas (for making objects)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<


clean:
	rm -f *.o

upload: clean
	git add --all
	git commit
	git push
