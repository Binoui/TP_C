#include <stdio.h>
#include <stdlib.h>

typedef struct Cellule Cellule;
typedef struct pile pile;

pile * creer_pile();

int pile_estVide(pile * f);

void enpiler(pile * f, int val);

int depiler(pile * f);

void afficher_pile(pile * f);

void concatener_piles(pile * f1, pile * f2);

void destruction(pile * f);