CC=gcc
CFLAGS= -W -Wall -ansi -g

abr: ABR_TP.o file.o fonctionsABR.o
	$(CC) $^ -o $@

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o abr

