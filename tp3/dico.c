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
	noeud * nouveau;
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
			if (dico->lettre > mot[index])
			{
				/* on regarde les frères pour chercher la lettre*/
				if (dico->frere != NULL && (dico->frere)->lettre > mot[index+1])
				{
					nouveau = malloc(sizeof(noeud));
					nouveau->lettre = mot[index+1];
					nouveau->frere = dico->frere;
					dico->frere = nouveau;
				}

				insertion(dico->fils, mot, taille, index+1);
				dico->fils = insertion(dico->fils, mot, taille, index+1);
			}
			else 
			{
				if (dico->lettre < mot[index])
				{
					nouveau = malloc(sizeof(noeud));
					nouveau->lettre = mot[index];
					nouveau->frere = dico->fils;
					dico->fils = nouveau;
				}

				dico->fils = insertion(dico->fils, mot, taille, index+1);
			}
		}
	}
	return dico;
}

/*void chargement(noeud * arbre, char * chemin)
{
	int tailleDico, i, j;
	char[100] buffer;
	FILE * fich = fopen(chemin, "r");
	
	if (fich == NULL)
		printf("Erreur fichier\n");
	else
	{
		fprintf(fich, "%d\n", &tailleDico);

		for (i = 0; i < tailleDico; i++)
		{
			for (j = 0; cara != '\0'; j++)
			{
				fprintf(fich, "%c", buffer);
			}*/

void afficheD(noeud* d, int tab)
{
	int i;
	printf("%c -> ", d->lettre);

	if((d->fils)||(d->frere)){
		if(d->fils){
			afficheD(d->fils, tab+1);
			printf("Fin\n");

		}
		if (d->frere){
			printf("\n");
			for (i=0;i<tab;i++){
				printf("\t");
			}
			printf("-> ");
			afficheD(d->frere, tab);
		}
	}
}

int main(int argc, char *argv[])
{
	noeud * arbre = creeDico();

	arbre = insertion(arbre, "arbre\0", 6, 0);
	afficheD(arbre,0);
	arbre = insertion(arbre, "arbuste\0", 8, 0);
	afficheD(arbre,0);
	printf("\n");
	return 0;

}

