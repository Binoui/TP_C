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
	graphe g = fich2Graf("test.txt");
	pLargeur(g);

	printf("bicolore ? %d\n",bicolore(g));

	return 0;
}