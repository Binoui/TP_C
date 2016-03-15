#include <stdio.h>
#include <stdlib.h>
#include "dico.h"



noeud* creeDico(){
	return NULL;
}

int recherche(char* clef, noeud* d,int taille, int index){
	int trouve = 0;
	if (d ==NULL)
		return 0;

	if (d->lettre != clef[index]) 
		trouve = recherche (clef, d->frere, taille, index);
	else{
		index ++;
		if (index == taille)
			trouve = 1;
		else
			trouve = recherche (clef, d->fils, taille, index);
	}
	return trouve;
} 

noeud* insertion(noeud * dico, char * mot, int taille, int index)
{
	noeud * nouveau, * ptr;

	if (index < taille)
	{
		/* nouvelle lettre, on crée un noeud */
		if (dico == NULL)
		{
			dico = malloc(sizeof(noeud));
			dico->lettre = mot[index];
			dico->fils = insertion(dico->fils, mot, taille, index+1);
		}
		/* il y a une lettre */
		else
		{	
			/* si la lettre à placer est plus grande, on va dans les frères*/
			if (mot[index] > dico->lettre)
			{
				ptr = dico;
				if (dico->frere == NULL)
				{
					nouveau = malloc(sizeof(noeud));
					nouveau->lettre = mot[index];
					ptr->frere = nouveau;
					ptr = nouveau;
				}
				else
				{
					while (ptr->frere != NULL && mot[index] > ptr->frere->lettre)
						ptr = ptr->frere;

					nouveau = malloc(sizeof(noeud));
					nouveau->lettre = mot[index];
					nouveau->frere = ptr->frere;
					ptr->frere = nouveau;
				}

				ptr->fils = insertion(ptr->fils, mot, taille, index+1);
			}
			else 
			{
				/* lettre plus petite, on décale les fils */
				if (mot[index] < dico->lettre)
				{
					nouveau = malloc(sizeof(noeud));
					nouveau->lettre = dico->lettre;
					nouveau->fils = dico->fils;
					nouveau->frere = dico->frere;
					dico->lettre = mot[index];
					dico->frere = nouveau;
					dico->fils = NULL;
				}
				dico->fils = insertion(dico->fils, mot, taille, index+1);
			}
		}
	}
	else
	{
		dico = malloc(sizeof(noeud));
		dico->lettre = '\0';
		dico->fils = NULL;
		dico->frere = NULL;
	}

	return dico;
}

noeud * chargement(noeud * arbre, char * chemin)
{
	int tailleDico, tailleMot, i, j;
	char buffer[100];
	FILE * fich = fopen(chemin, "r");
	
	if (fich == NULL)
		printf("Erreur fichier\n");
	else
	{
		fgets(buffer, 100, fich);
		tailleDico = atoi(buffer);

		for (i = 0; i < tailleDico; i++)
		{

			fscanf(fich, "%s%n", buffer, &tailleMot);
			printf("%s %d\n", buffer, tailleMot);
			arbre = insertion(arbre, buffer, tailleMot, 0);
		}
	}

	return arbre;
}

void afficheD(noeud* d, int tab)
{
	int i;
	if (d == NULL)
	{
		printf("Arbre vide\n");
	}
	else
	{
		printf(" %c ->", d->lettre);
		
		if(d->fils){
			afficheD(d->fils, tab+1);
		}
		else
			printf(" Fin\n");

		if (d->frere){
			printf("\n");
			for (i=0;i<tab;i++){
				printf("    ");
			}
			printf("->");
			afficheD(d->frere, tab);
		}
	}

}

int main(int argc, char *argv[])
{
	noeud * arbre = creeDico();

/*	arbre = insertion(arbre, "arbre", 5, 0);
	afficheD(arbre,0);
	printf("\n deuxième affichage \n");
	arbre = insertion(arbre, "arbuste", 7, 0);
	afficheD(arbre,0);
	printf("\n troisième affichage \n");
	arbre = insertion(arbre, "arrivee", 7, 0);
	afficheD(arbre,0);
	printf("\n quatrième affichage \n");
	arbre = insertion(arbre, "abreuvoir", 9, 0);
	afficheD(arbre,0);
	printf("\n cinquième affichage \n");
	arbre = insertion(arbre, "ablation", 8, 0);
	afficheD(arbre,0);
*/

	arbre = chargement(arbre, "./dico.fr");
	afficheD(arbre,0);


	printf("\n");
	return 0;

}

