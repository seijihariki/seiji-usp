CC:=gcc
CFLAGS:=-Wall -pedantic -g
#-O2 -ansi
DEPS:= str.o linkedlist.o tabelaSimbolo_AB.o tabelaSimbolo_LD.o tabelaSimbolo_LO.o tabelaSimbolo_VD.o tabelaSimbolo_VO.o

tabelaSimbolo: tabelaSimbolo.o $(DEPS)
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
