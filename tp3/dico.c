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
