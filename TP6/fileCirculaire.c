/**
 * @file fileCirculaire.c
 * @brief Définition de la structure file
 * @author Gwladys Auffret / Benjamin Houx TP1 PROMO2018
 * @date 02/2016
 */

#include <stdio.h>
#include <stdlib.h>
#include "mpm.h"

struct cellule{
	int valeur;
	Cellule* suivant;

};



/*créer une file vide, 
tester si la file est vide, 
enfiler un élément (ie. l'ajouter en queue de file), 
défiler (ie. supprimer l'élément se trouvant en tête de file), 
concaténer 2 files (ie. les mettre bout à bout), 
afficher le contenu de la file. */

fileC* creer_fileC(){
	fileC * f = malloc(sizeof(fileC));
	f->queue = NULL;
	return f;
}

int fileC_vide(fileC* f){
	if (f->queue == NULL)
		return 1;
	return 0;
}

void enfilerC (fileC* f, int e){
	Cellule* cel = malloc(sizeof(Cellule));
	Cellule* tmp;
	cel->valeur = e;
	if (fileC_vide(f)){
		cel->suivant = cel;
	}else{
		cel->suivant = (f->queue)->suivant;
		tmp = cel->suivant;
		while(tmp->suivant != cel->suivant){
			tmp = tmp->suivant;
		}
		tmp->suivant = cel;
	}
	f->queue = cel;
}

int defiler (fileC* f){
	int ret = -1;
	Cellule* tmp;

	if(fileC_vide(f)){
		printf("Il n'y a rien a defiler dans une liste vide !\n");
	}else{
		if(f->queue == (f->queue)->suivant){
			ret=f->queue->valeur;
			free(f->queue);
			f->queue = NULL;
		}else{
			tmp = (f->queue)->suivant;
			(f->queue)->suivant = tmp->suivant;
			ret = tmp->valeur;
			free(tmp);
		}
	}
	return ret;
}

void concatC (fileC* f1, fileC* f2){
	Cellule * tmp;

	if (!(fileC_vide(f1))){
		if (fileC_vide(f2)){
			f1=f2;
		}else{

			tmp = (f1->queue)->suivant;
			(f1->queue)->suivant = (f2->queue)->suivant;
			(f2->queue)->suivant = tmp;
		}
	}
}

void afficheFC (fileC* f){
	if(fileC_vide(f)){
		printf("La liste est vide !\n");
	}else{
		Cellule * tmp = f->queue;
		do{
			tmp=tmp->suivant;
			printf("%d -> ",tmp->valeur);
			

		}while(tmp!=f->queue);
		printf("\n\n");
	}
}

