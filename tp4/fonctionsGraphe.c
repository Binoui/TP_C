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

graphe fich2Graf (char* fichier){
	graphe g;
	int nbA, nbS, i,ori, ext;


	FILE* f = fopen(fichier,"r");
	if(f==NULL){
		printf("Erreur : mauvais fichier.");
		init_graphe(0,0,&g);
	}else{
		fscanf(f,"%d %d",&nbS,&nbA);

		init_graphe(nbS,nbA,&g);

		for(i=0; i <= nbA; i++){
			fscanf(f,"%d %d", &ori, &ext);

			g.matrice[ori][ext] = g.matrice[ext][ori] = 1;
		}
		fclose(f);
	}
	return g;
}

int pLargeur(graphe g){

	int nbS=g.nbsom, i,ori=0, courant,nbSommet = 0, nscc, booleen =1, ncc=0,j=0;
	file* liste = creer_file();
	int* coule= (int*)calloc(nbS,sizeof(int*));


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
		printf("La %deme composante connexe contient %d sommet(s). Nous avons actuellement %d/%d sommets\n",ncc, nscc, nbSommet,nbS);
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
	}


	free(coule);
	free(liste);
	return booleen;
}


int bicolore(graphe g){
	char* coule = (char*)calloc(g.nbsom,sizeof(char*));
	file* liste = creer_file();
	int ori, nbSommet,courant,nbS=g.nbsom,i,j;
	ori =0;

	for(i=0;i<nbS;i++){
		coule[i]='N';
	}

	enfiler(liste,ori);
	nbSommet++;
	coule[ori] ='B';

	while(nbSommet<nbS){
		while(!(file_estVide(liste))){
			courant = defiler(liste);
			printf("Sommet %d, couleur : %c\n", courant, coule[courant]);
			for(i=0;i<nbS;i++){
				if(g.matrice[courant][i]==1){
					if(coule[i]!=coule[courant]){
						if(coule[i]=='N'){
							if(coule[courant]=='B'){
								coule[i]='J';
							}else{
								coule[i]='B';
							}
							enfiler(liste,i);
							nbSommet++;
						}
					}else{
						return 0;
					}
				}
			}
			coule[courant]=2;
		}
		if(nbSommet!=nbS){
			while(coule[j]!=0){
				j++;
			}
			enfiler(liste,j);
			nbSommet++;
			coule[j]='B';
		}

	}

	free(coule);
	free(liste);
	return 1;
}

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

void visite_profondeur_prefixe(int * coul, graphe g, int numSom)
{
	coul[numSom] = 1;

	int i;
	printf("  %d ", numSom);
	
	for (i = 0; i < g.nbsom; i++)
	{       
		    /* Successeur */
		if (g.matrice[numSom][i] == 1  && coul[i] == 0)
		{
			visite_profondeur_prefixe(coul, g, i); 
		}
	}

	coul[numSom] = 2;
}

void visite_profondeur_affi_double(int * coul, graphe g, int numSom, int * tab, int * index)
{
	coul[numSom] = 1;

	int i;
	tab[(*index)++] = numSom;
	
	for (i = 0; i < g.nbsom; i++)
	{       
		    /* Successeur */
		if (g.matrice[numSom][i] == 1  && coul[i] == 0)
		{
			visite_profondeur_affi_double(coul, g, i, tab, index); 
		}
	}

	printf(" %d ", numSom);

	coul[numSom] = 2;
}

void parcours_profondeur(graphe g)
{
	int i;
	/* 0 pour blanc (pas encore traité)
	   1 pour gris (en cours de traitement) 
	   2 pour noir (traité) */
	int * couleur = malloc(sizeof(int) * g.nbsom);
	int * tab = malloc(sizeof(int) * g.nbsom);
	int a = 0;
	int * index = &a;

	for (i = 0; i < g.nbsom; i++)
	{
		couleur[i] = 0;
	}

	printf("Affichage Prefixe\n");
	for (i = 0; i < g.nbsom; i++)
	{
		if (! couleur[i])
		{
			printf("\n%d -> \n", i);
			
			/*visite_profondeur_prefixe(couleur, g, i);*/

			visite_profondeur_affi_double(couleur, g, i, tab, index);
		}	
	}

	printf("\nAffichage Suffixe\n");
	for (i = 0; i < a; i++)
	{
		printf(" %d \n", tab[i]);
	}

	printf("\n");
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

int main(void)
{
/*		graphe g = fich2Graf("graphe.data");*/
		graphe g = cree_graphe_non_oriente_non_value("test.txt");
/*		pLargeur(g);
		printf("bicolore ? %d\n",bicolore(g));
*/

		parcours_profondeur(g);

		return 0;
}