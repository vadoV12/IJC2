# Makefile
# Řešení IJC-DU2, příklad a),b) 5.4.2025
# Autor: Andrej Vadovsky,xvadova00,FIT
CC=gcc 
CFLAGS=-std=c11 -pedantic -Wall -Wextra -O2 -fPIC 
DFLAGS=-g
LDFLAGS=-lm	

HTAB:=htab_erase.o htab_find.o htab_for_each.o htab_hash.o \
htab_lookup_add.o htab_free.o htab_init.o htab_size.o

.PHONY: all run debug clean zip 

all: tail libhtab.a libhtab.so maxwordcount maxwordcount-dynamic

tail: tail.o 
	$(CC) $(CFLAGS) -o $@ $^ $(DFLAGS) $(LDFLAGS)

libhtab.a: $(HTAB)
	ar r $@ $^

libhtab.so: $(HTAB)
	$(CC) -shared -o $@ $^

maxwordcount: maxwordcount.o libhtab.a
	$(CC) $(CFLAGS) -o $@ $^ $(DFLAGS) $(LDFLAGS)

maxwordcount-dynamic: maxwordcount.o libhtab.so
	$(CC) $(CFLAGS) -o $@ $^ $(DFLAGS) $(LDFLAGS)

tail.o: tail.c
	$(CC) $(CFLAGS) -c tail.c -o tail.o $(DFLAGS) $(LDFLAGS)

htab.o: htab.c
	$(CC) $(CFLAGS) -c htab.c -o htab.o $(DFLAGS) $(LDFLAGS)

maxwordcount.o: maxwordcount.c
	$(CC) $(CFLAGS) -c $< -o $@ $(DFLAGS) $(LDFLAGS)

check:
	$(MAKE)
	./tail <seznam.txt && LD_LIBRARY_PATH=. ./maxwordcount-dynamic < seznam.txt


debug: DFLAGS+=-DDEBUG -g
debug: tail maxwordcount maxwordcount-dynamic

clean:
	rm -f tail maxwordcount maxwordcount-dynamic *.o libhtab.a libhtab.so

zip:
	zip -r xvadova00.zip *.c *.cc *.h Makefile seznam.txt
