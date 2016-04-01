#include <stdlib.h>
#include <stdio.h>

typedef struct
{
	int nbsom;
	int nbarc;
	int **matrice; /* matrice d'adjacence */
} graphe;

typedef struct 
{	
	int *pere;
	int nbelements;
	int nbclasses; 
} t_ens;	


void init_graphe(int nbs, int nba, graphe *g)
{ 
	int i;

	g->nbsom = nbs; 
	g->nbarc = nba;
	g->matrice = (int **)calloc(g->nbsom,sizeof(int*));

	for (i=0;i<g->nbsom;i++)
	{ 
		g->matrice[i] = (int *)calloc(g->nbsom,sizeof(int));
    	/* for (j=0; j<g->nbsom; j++) g->matrice[i][j] = 0.; 
		inutile avec calloc */
	}
}

/* format du fichier : 
nbsommets nbaretes
aretes sous forme de triplets origine extremité                           */
graphe cree_graphe_non_oriente_non_value(char *nom_fich)
{
	FILE *fich; 
	graphe g;
	int nbs, nba, som1, som2;
	int iare;

	fich = fopen(nom_fich, "r");

	fscanf(fich,"%d %d", &nbs, &nba);

	init_graphe(nbs,nba,&g);    

	for (iare = 0; iare < nba ; iare++)
	{
		fscanf(fich, "%d %d", &som1, &som2);

		g.matrice[som1][som2] = g.matrice[som2][som1] = 1;
	} 

	fclose(fich);
	return g;
}	

void visite_profondeur(int * coul, graphe g, int numSom)
{
	coul[numSom] = 1;

	int i;
	for (i = 0; i < g.nbsom; i++)
	{       
		    /* Successeur */
		if (g.matrice[numSom][i] && ! coul[numSom])
		{
			printf("\r%d ", i);
			visite_profondeur(coul, g, i); 
		}
	}

	coul[numSom] = 2;
}

void parcours_profondeur(graphe g)
{
	int i;
	/* 0 pour blanc (pas encore traité)
	   1 pour gris (en cours de traitement) 
	   2 pour noir (traité) */
	int * couleur = malloc(sizeof(int) * g.nbsom);
	
	for (i = 0; i < g.nbsom; i++)
	{
		couleur[i] = 0;
	}

	for (i = 0; i < g.nbsom; i++)
	{
		if (! couleur[i])
		{
			printf("\n%d -> \n", i);
			visite_profondeur(couleur, g, i);
		}	
	}

	printf("\n");
}

int main(void)
{
	graphe g = cree_graphe_non_oriente_non_value("graphe.data");

	parcours_profondeur(g);


	return 0;
}