/**
 * @file fileClassique.c
 * @brief Définition de la structure file
 * @author Gwladys Auffret / Benjamin Houx TP1 PROMO2018
 * @date 02/2016
 */

 #include "./fileClassique.h"

struct Cellule
{
	int valeur;
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

void enfiler(file * f, int val)
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

int defiler(file * f)
{
	int ret = -1;

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
		printf("| %d ", c->valeur);
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

int main(int argc, char *argv[])
{
	
	file * f1 = creer_file();

	printf("Création file 1\n");
	afficher_file(f1);

	enfiler(f1, 50);
	enfiler(f1, 25);
	enfiler(f1, 2);
	enfiler(f1, 7);

	printf("Affichage file 1\n");
	afficher_file(f1);

	printf("Défile file 1\n");
	defiler(f1);

	afficher_file(f1);

	enfiler(f1, 7);
	printf("Enfile file 1\n");
	afficher_file(f1);

	file * f2 = creer_file();

	enfiler(f2, 3);
	enfiler(f2, 4);
	enfiler(f2, 5);

	printf("Création file 2\n");
	afficher_file(f2);

	printf("Concaténation file 1 et 2\n");
	concatener_files(f1, f2);

	afficher_file(f1);
	defiler(f1);
	defiler(f1);
	defiler(f1);
	defiler(f1);
	defiler(f1);
	defiler(f1);

	printf("Défiler file 1\n");
	afficher_file(f1);

	printf("File 1 est vide : ");
	printf("%d\n", file_estVide(f2));

	destruction(f2);

	destruction(f1);

	return 0;
}