/**
 * @file fonctionsABR.c
 * @brief Contient les fonctions sur les arbres de recherche
 * @author Gwladys Auffret / Benjamin Houx TP1 PROMO2018
 * @date 02/2016
 */

#include <stdio.h>
#include <stdlib.h>
#include "abr.h"
#include "../tp1/classique/fileClassique.h"


/*RGD*/
void parcours_pref(NOEUD *p) 
{
	if (p){
		printf("%d - ",p->valeur); 
		parcours_pref(p->gauche); 
		parcours_pref(p->droit); 
	} 	 
} 

/*GRD*/
void parcours_inf(NOEUD *p) 
{
	if (p){ 
		parcours_inf(p->gauche); 
		printf("%d - ",p->valeur);
		parcours_inf(p->droit); 
	} 	 
}

/*GDR*/
void parcours_suf(NOEUD *p) 
{
	if (p){ 
		parcours_suf(p->gauche); 
		parcours_suf(p->droit); 
		printf("%d - ",p->valeur);
	} 	 
} 

/* Renvoit le nombre de noeuds de l'arbre */
int compteN(NOEUD *p){
	if (p){
		return 1+compteN(p->gauche)+compteN(p->droit);
    } 
    return 0;
}

/* Parcourt l'arbre en infixe et suffixe en même temps */
int parcours_inf_sup(NOEUD * p)
{
	if (p)
	{
		printf("%d ", p->valeur);
		parcours_inf_sup(p->gauche);
		parcours_inf_sup(p->droit);
		printf("%d ", p->valeur);
	}
	return compteN(p);
}

/* Affiche l'arbre */
int parcoursAffichage(NOEUD *p){
  int nbn=0;
  if(p){
    printf("Parcours prefixe : %d\n",p->valeur);
    nbn+=parcoursAffichage(p->gauche);
    nbn+=parcoursAffichage(p->droit);
    printf("\tParcours suffixe : %d\n",p->valeur);
    nbn++;
  }
  return nbn;
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
	
	printf("Arbre : \n");
	affiche_arbre(p,1);
	

	printf("Parcours prefixe : ");
	parcours_pref(p);
	printf("\n");
	
	printf("Parcours infixe : ");
	parcours_inf(p);
	printf("\n");
	
	printf("Parcours suffixe : ");
	parcours_suf(p);
	printf("\n");
	
	printf("Il y a %d noeud(s)\n",compteN(p));

	printf("nb de noeuds : %d\n",parcoursAffichage(p));

	printf("Parcours en largeur : ");
	parcours_largeur(p);

	return 0;
}
