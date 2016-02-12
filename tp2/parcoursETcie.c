/*****************************************************************************/
/*   G.AUFFRET                      ABR_TP.c                     Fevrier 2016*/
/*                      Arbres binaires de recherche                         */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "abr.h"

void parcours_pref(NOEUD *p) 
{
	if (p){
		printf("%d - ",p->valeur); 
		parcours_pref(p->gauche); 
		parcours_pref(p->droit); 
	} 	 
} 


void parcours_inf(NOEUD *p) 
{
	if (p){ 
		parcours_inf(p->gauche); 
		printf("%d - ",p->valeur);
		parcours_inf(p->droit); 
	} 	 
}

void parcours_suf(NOEUD *p) 
{
	if (p){ 
		parcours_suf(p->gauche); 
		parcours_suf(p->droit); 
		printf("%d - ",p->valeur);
	} 	 
} 


void compteN(NOEUD *p){
	if (p){
		return 1+compteN(p->gauche)+compteN(p->droit);
    } 
    return 0;
}


int main (){

	NOEUD* p = arbre_vide();
	p = insere(p,25);
	p = insere(p,50);
	p = insere(p,15);
	p = insere(p,5);
	p = insere(p,6);
	p = insere(p,32);
	p = insere(p,45);
	p = insere(p,70);
	p = insere(p,20);
	
	affiche_arbre(p,1);
	
	parcours_pref(p);
	printf("\n");
	
	parcours_inf(p);
	printf("\n");
	
	parcours_suf(p);
	printf("\n");

	return 0;
}
