all: a234

OPTIONS_COMPIL=-Wall -g -c

a234: a234.o lire_affichage.o ajout_cle.o file.o pile.o
	gcc -o a234 a234.o lire_affichage.o ajout_cle.o file.o pile.o

a234.o: a234.c a234.h pile.h file.h
	gcc $(OPTIONS_COMPIL) a234.c

lire_affichage.o: lire_affichage.c a234.h
	gcc $(OPTIONS_COMPIL) lire_affichage.c

ajout_cle.o : ajout_cle.c a234.h
	gcc $(OPTIONS_COMPIL) ajout_cle.c

pile.o: pile.h pile.c
	gcc -g -Wall -c pile.c

file.o: file.h file.c
	gcc -g -Wall -c file.c

clean:
	rm -rf a234 *.o *~
