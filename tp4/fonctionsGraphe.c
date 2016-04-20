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

	int nbS=g.nbsom, i,ori=0, nbSommet, courant, nscc, booleen =1, ncc=0,j=0;
	file* liste = creer_file();
	int* coule= (int*)calloc(nbS,sizeof(int*));


	ori =0;

	enfiler(liste,ori);
	nbSommet = 0;
	nbSommet++;
	coule[ori] =1;

	while(nbSommet<nbS){
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
			if(nbS == nbSommet){
				printf("La %deme composante connexe contient %d sommet(s). Nous avons actuellement %d/%d sommets\n",ncc+1, 1, nbSommet,nbS);
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
	int ori, nbSommet = 0,courant,nbS=g.nbsom,i,j;
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
void cree_graphe_non_oriente_non_value(char *nom_fich, int nbs, int nba)
{ 
	FILE *fich; 
	graphe g;
	int ori, ext;
	int iare;

	fich = fopen(nom_fich,"w");

	fprintf(fich,"%d %d\n",nbs,nba);

	init_graphe(nbs,nba,&g);    

	for (iare = 1; iare <= nba ; iare++)
	{
		do 
		{
			ori = random()%nbs;
			ext = random()%nbs;
		} while ((ori == ext)||(g.matrice[ori][ext]));

		g.matrice[ori][ext] = g.matrice[ext][ori] = 1;
		fprintf(fich,"%d %d\n",ori,ext);
	} 

	fclose(fich);
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

void visite_profondeur_affi_double(int * coul, graphe g, int numSom, int * tab, int * index, int * nbSom)
{
	coul[numSom] = 1;

	int i;
	tab[(*index)++] = numSom;

	for (i = 0; i < g.nbsom; i++)
	{       
			/* Successeur */
		if (g.matrice[numSom][i] == 1  && coul[i] == 0)
		{
			(*nbSom)++;
			visite_profondeur_affi_double(coul, g, i, tab, index, nbSom); 
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
	int nbCompCon = 0;
	int nbSom = 1;

	for (i = 0; i < g.nbsom; i++)
	{
		couleur[i] = 0;
	}

	printf("Affichage Prefixe\n");
	for (i = 0; i < g.nbsom; i++)
	{
		if (! couleur[i])
		{
			/*visite_profondeur_prefixe(couleur, g, i);*/
			nbCompCon++;
			visite_profondeur_affi_double(couleur, g, i, tab, index, &nbSom);
			printf("\nComposante connexe numero %d contient %d sommets\n", nbCompCon, nbSom);
			nbSom = 1;
		}   
	}

	printf("\nAffichage Suffixe\n");
	for (i = 0; i < a; i++)
	{
		printf(" %d ", tab[i]);
	}

	printf("\n");
}

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

int main(void)
{
	cree_graphe_non_oriente_non_value("testGraphe.data", 250, 250);
	graphe g = fich2Graf("testGraphe.data"); 


	printf("\nPARCOURS PROFONDEUR\n");
	parcours_profondeur(g);
	
	printf("\nPARCOURS LARGEUR\n");
	pLargeur(g);
/*	printf("bicolore ? %d\n",bicolore(g));
*/
	return 0;
}