#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	char lettre;
	noeud * frere;
	noeud * fils;
} noeud;

noeud* creeDico (){
	return NULL;
}

int recherche (char* clef, noeud* d,int taille, int index){
	int trouve = 0;
	if (d ==NULL)
		return 0;

	if (d->lettre != clef[index]) 
		trouve = recherche (clef, d->frere, taille, index)
	else{
		index ++;
		if (index == taille)
			trouve = 1;
		else
			trouve = recherche (clef, d->fils, taille, index);
	}
	return trouve;
} 

void insertion(noeud * dico, char * mot, int taille, int index)
{
	noeud * nouveau;

	if (index < taille)
	{
		if (dico == NULL)
		{
			dico = malloc(sizeof(noeud));
			dico->lettre = mot[index];

			insertion(dico->fils, mot, taille, index+1);
		}
		else
		{	
			if (dico->lettre > mot[index])
			{

				if (dico->frere != NULL && dico->frere->lettre > mot[index+1])
				{
					nouveau = malloc(sizeof(noeud));
					nouveau->lettre = mot[index+1];
					nouveau->frere = dico->frere;
					dico->frere = nouveau;
				}	

				insertion(dico->fils, mot, taille, index+1);
			}
			else
			{
				if (dico->fils != NULL && dico->fils->lettre > mot[index+1])
				{
					nouveau = malloc(sizeof(noeud));
					nouveau->lettre = mot[index+1];
					nouveau->fils = dico->fils;
					dico->fils = nouveau;
				}	

				insertion(dico->fils, mot, taille, index+1);
			}
		}
	}
}

void chargement(noeud * arbre, char * chemin)
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
			}

			insertion(arbre, buffer, j, 0);
		}
	}
}

int main(int argc, char *argv[])
{
	noeud * arbre = creeDico();

	insertion(arbre, "arbre", 6, 0);
	insertion(arbre, "prout", 6, 0);
	insertion(arbre, "test", 5, 0);



	return 0;
}

