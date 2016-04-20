/**
 * @pile pileClassique.c
 * @brief Définition de la structure pile
 * @author Gwladys Auffret / Benjamin Houx TP1 PROMO2018
 * @date 02/2016
 */

 #include "./pileClassique.h"

struct Cellule
{
	int valeur;
	Cellule * suivant;
};

struct pile
{
	Cellule * tete;
	Cellule * queue;
};

pile * creer_pile()
{
	pile * f = malloc(sizeof(pile));
	f->tete  = NULL;
	f->queue = NULL;

	return f;
}

int pile_estVide(pile * f)
{
	return f->tete == NULL ? 1 : 0;
}

void enpiler(pile * f, int val)
{
	Cellule * noeud = malloc(sizeof(Cellule));
	noeud->valeur = val;
	noeud->suivant = NULL;

	if (f->tete == NULL)
		f->tete = noeud;

	noeud->suivant = f->tete;
	f->tete = noeud;
}

int depiler(pile * f)
{
	int ret = -1;
	
	if (f->tete != NULL)
	{
		Cellule * c = f->tete;
		ret = c->valeur;
		f->tete = c->suivant;
		free(c);
	}
	
	return ret;
}

void afficher_pile(pile * f)
{
	Cellule * c;
	for (c = f->tete; c != NULL; c = c->suivant)
	{
		printf("| %d ", c->valeur);
	}
	printf("|\n");
}

void concatener_piles(pile * f1, pile * f2)
{
	if (f1 == NULL)
		f1 = f2;
	else
	{
		f1->queue->suivant = f2->tete;
		free(f2);
	}
}

void destruction(pile * f)
{
	while (depiler(f) >= 0);
	free(f);
}