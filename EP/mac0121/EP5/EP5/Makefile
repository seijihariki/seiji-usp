CC:=gcc
CFLAGS:=-Wall -pedantic -ansi
RELEASE_FLAGS:=-O2
DEBUG_FLAGS:=-g -D __DEBUG__
DEPS:= player.o game.o

release: CFLAGS:= $(CFLAGS) $(RELEASE_FLAGS)
release: ep5

debug: CFLAGS:= $(CFLAGS) $(DEBUG_FLAGS)
debug: ep5

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
