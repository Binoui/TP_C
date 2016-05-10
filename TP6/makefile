CC=gcc
CFLAGS= -W -Wall -ansi -g

exe: L_ADJ.o fileCirculaire.o mpm.o
	$(CC) $^ -o $@

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o exe

