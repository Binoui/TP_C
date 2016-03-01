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

void insertion(noeud * dico, char * mot, int taille, int index)
{
	noeud * nouveau;
	printf("index = %d\n",index);
	if (index < taille)
	{
		if (dico == NULL)
		{
			printf("Yo\n ");
			dico = malloc(sizeof(noeud));
			dico->lettre = mot[index];

			insertion(dico->fils, mot, taille, index+1);
		}
		else
		{	
			if (dico->lettre > mot[index])
			{

				printf("Yeah\n");
				if (dico->frere != NULL && (dico->frere)->lettre > mot[index+1])
				{
					printf("yOLO\n");
					nouveau = malloc(sizeof(noeud));
					nouveau->lettre = mot[index+1];
					nouveau->frere = dico->frere;
					dico->frere = nouveau;
				}	

				insertion(dico->fils, mot, taille, index+1);
			}
			else
			{
				printf("suite\n");
				insertion(dico->fils, mot, taille, index+1);
			}
		}
	}
}


void afficheD(noeud* d, int tab){
	int i;
	printf("%c ->", d->lettre);

	//if((d->fils)||(d->frere)){
		if(d->fils){
			afficheD(d->fils, tab+1);
		}
		else{
			printf("Fin");
		}
		if (d->frere){
			printf("\n");
			for (i=0;i<tab;i++){
				printf("\t");
			}
			printf("-> ");
			afficheD(d->frere, tab);
		}

	//}

}

int main(int argc, char *argv[])
{
	noeud * arbre = creeDico();

	insertion(arbre, "arbre\0", 6, 0);
	insertion(arbre, "prout\0", 6, 0);
	insertion(arbre, "test\0", 5, 0);

	afficheD(arbre,0);
	return 0;

}

