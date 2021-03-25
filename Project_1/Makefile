CC = gcc
CFLAGS = -Wall -o
objects = calc.o mcalc.o
default: calc
calc: $(objects)
	$(CC) -o $@ $^
calc.o: calc.c mcalc.h
mcalc.o: mcalc.c mcalc.h
%.o: %.c
	$(CC) -c $(CFLAGS) $@ $<
clean:
	rm -f $(objects)
