CC:=gcc
CFLAGS:=-Wall -pedantic -ansi -g -D __DEBUG__
#-O2
DEPS:= player.o game.o

ep5: main.o $(DEPS)
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
