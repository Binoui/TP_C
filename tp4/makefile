CC=gcc
CFLAGS= -W -Wall -ansi -g

graphe: fonctionsGraphe.o pileClassique.o
	$(CC) $^ -o $@

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o graphe

