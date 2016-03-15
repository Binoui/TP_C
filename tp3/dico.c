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
				printf(" > : %c - %c\n",mot[index], dico->lettre );
				ptr = dico;
				if (dico->frere == NULL)
				{
					printf("Pas frere\n");
					nouveau = malloc(sizeof(noeud));
					nouveau->lettre = mot[index];
					dico->frere = nouveau;
					ptr = nouveau;

				}
				else
				{
					printf("frere = %c\n ", ptr->frere->lettre );

					while (ptr->frere != NULL && mot[index] >= ptr->frere->lettre){
						ptr = ptr->frere;
						printf("freres : %c - %c\n",mot[index], ptr->lettre );
					}
					if (ptr->lettre != mot[index]){
						nouveau = malloc(sizeof(noeud));
						nouveau->lettre = mot[index];
						nouveau->frere = ptr->frere;
						ptr->frere = nouveau;
						ptr = nouveau;
					}
				}

				ptr->fils = insertion(ptr->fils, mot, taille, index+1);
			}
			else 
			{
				printf(" <= : %c - %c\n",mot[index], dico->lettre );

				/* lettre plus petite, on décale les fils */
				if (mot[index] < dico->lettre)
				{
					printf("< : %c - %c\n",mot[index], dico->lettre );
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
		printf("%d\n", tailleDico);

		for (i = 0; i < tailleDico; i++)
		{

			fscanf(fich, "%s%n", buffer, &tailleMot);
			//printf("%s %d\n", buffer, tailleMot);
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
	printf("\n sixième affichage \n");
	arbre = insertion(arbre, "ablation", 8, 0);
	afficheD(arbre,0);

	printf("Est ce que le mot arbre appartient a notre arbre : %d (1 oui, 0 non)\n",recherche("arbre", arbre,5, 0));
	printf("Est ce que le mot arbuisseau appartient a notre arbre : %d (1 oui, 0 non)\n",recherche("arbuisseau", arbre,10, 0));

*/

	//arbre = chargement(arbre, "./dico.ang");
	
	arbre = insertion(arbre, "zinc", 4, 0);
	arbre = insertion(arbre, "zion", 4, 0);
	arbre = insertion(arbre, "zionism", 8, 0);
/*	arbre = insertion(arbre, "zionist", 8, 0);
	arbre = insertion(arbre, "zionists", 9, 0);
	arbre = insertion(arbre, "zions", 5, 0);
	arbre = insertion(arbre, "zodiac", 6, 0);
	arbre = insertion(arbre, "zoe", 3, 0);
	arbre = insertion(arbre, "zomba", 5, 0);
	arbre = insertion(arbre, "zonal", 5, 0);
	arbre = insertion(arbre, "zonally", 7, 0);
	arbre = insertion(arbre, "zone", 4, 0);
	arbre = insertion(arbre, "zoned", 5, 0);
	arbre = insertion(arbre, "zones", 4, 0);
	arbre = insertion(arbre, "zoning", 6, 0);
	arbre = insertion(arbre, "zoo", 3, 0);
	arbre = insertion(arbre, "zoological", 10, 0);
	arbre = insertion(arbre, "zoologically", 12, 0);
	arbre = insertion(arbre, "zoom", 4, 0);
	arbre = insertion(arbre, "zooms", 5, 0);
	arbre = insertion(arbre, "zoos", 4, 0);
	arbre = insertion(arbre, "zorn", 4, 0);
	arbre = insertion(arbre, "zoroaster", 9, 0);
	arbre = insertion(arbre, "zoroastrian", 11, 0);
	arbre = insertion(arbre, "zulu", 4, 0);
	arbre = insertion(arbre, "zulus", 5, 0);*/


	afficheD(arbre,0);
	printf("\n");
	return 0;

}
