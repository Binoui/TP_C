#include "./file.h"

struct Cellule
{
	NOEUD * valeur;
	Cellule * suivant;
};

struct file
{
	Cellule * tete;
	Cellule * queue;
};

file * creer_file()
{
	file * f = malloc(sizeof(file));
	f->tete  = NULL;
	f->queue = NULL;

	return f;
}

int file_estVide(file * f)
{
	return f->tete == NULL ? 1 : 0;
}

void enfiler(file * f, NOEUD * val)
{
	Cellule * noeud = malloc(sizeof(Cellule));
	noeud->valeur = val;
	noeud->suivant = NULL;

	if (f->queue != NULL)
	{
		f->queue->suivant = noeud;
		f->queue = noeud;
	}
	else
		f->queue = noeud;

	if (f->tete == NULL)
		f->tete = noeud;
}

NOEUD * defiler(file * f)
{
	NOEUD * ret = NULL;

	if (f->tete != NULL)
	{
		Cellule * c;
		ret = f->tete->valeur;

		if (f->tete != f->queue)
		{
			c = f->tete;
			f->tete = c->suivant;
			c->suivant = NULL;
			free(c);
		}
		else
		{
			free(f->tete);
			f->tete = NULL;
		}
	}

	return ret;
}

void afficher_file(file * f)
{
	Cellule * c;
	for (c = f->tete; c != NULL; c = c->suivant)
	{
		printf("| %d ", c->valeur->valeur);
	}
	printf("|\n");
}

void concatener_files(file * f1, file * f2)
{
	if (f1 == NULL)
		f1 = f2;
	else
	{
		f1->queue->suivant = f2->tete;
		free(f2);
	}
}

void destruction(file * f)
{
	while (defiler(f) >= 0);
	free(f);
}