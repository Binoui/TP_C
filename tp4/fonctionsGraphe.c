#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "graphes.h"
#include "../tp1/classique/fileClassique.h"


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


int pLargeur(char* fichier){
	graphe g;
	int nbA, nbS, i,ori, ext,courant,nbSommet = 0, nscc, booleen =1, ncc=0,j=0;
	file* liste = creer_file();
	int* coule;


	FILE* f = fopen(fichier,"r");
	if(f==NULL){
		printf("Erreur : mauvais fichier.");
		return -1;
	}


	fscanf(f,"%d %d",&nbS,&nbA);

	init_graphe(nbS,nbA,&g);
	coule = (int*)calloc(nbS,sizeof(int*));


	for(i=0; i <= nbA; i++){
		fscanf(f,"%d %d", &ori, &ext);

		g.matrice[ori][ext] = g.matrice[ext][ori] = 1;
	}
	ori =0;

	enfiler(liste,ori);
	nbSommet++;
	coule[ori] =1;

	while(nbSommet!=nbS){
		ncc++;
		nscc=0;
		while(!(file_estVide(liste))){
			courant = defiler(liste);
			printf("Sommet %d\n", courant);
			for(i=0;i<nbS;i++){
				if(g.matrice[courant][i]==1){
					if(coule[i]==0){
						coule[i]=1;
						enfiler(liste,i);
						nbSommet++;
					}
				}
			}
			coule[courant]=2;
			nscc++;
		}
		if(nscc != nbS){
			booleen = 0;
			if(nbSommet!=nbS){
				while(coule[j]!=0){
					j++;
				}
				enfiler(liste,j);
				nbSommet++;
			}
		}
		printf("La %deme composante connexe contien %d sommet(s). Nous avons actullement %d/%d sommets\n",ncc, nscc, nbSommet,nbS);
	}


	free(coule);
	fclose(f);
	return booleen;
}



file * creer_file()
{
	file * f = malloc(sizeof(file));
	f->tete  = NULL;
	f->queue = NULL;
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

void init_graphe(int nbs, int nba, graphe *g)
  { int i,j;

    g->nbsom = nbs; g->nbarc = nba;
    g->matrice = (float **)calloc(g->nbsom,sizeof(float*));
    for (i=0;i<g->nbsom;i++)
      { g->matrice[i] = (float *)calloc(g->nbsom,sizeof(float));
        /* for (j=0; j<g->nbsom; j++) g->matrice[i][j] = 0.; 
	   inutile avec calloc */
      }
    }

int main(int argc, char *argv[])
{
	pLargeur("test.txt");


	return 0;
}