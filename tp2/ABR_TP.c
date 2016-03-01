/**
 * @file ABR_TP.c
 * @brief Contient les fonctions de définitions de l'arbre de recherche
 * @author Gwladys Auffret / Benjamin Houx TP1 PROMO2018
 * @date 02/2016
 */


#include <stdio.h>
#include "./file.h"
#include <stdlib.h>

typedef int element;

/*****************************************************************************/
NOEUD *arbre_vide() {return NULL; }
/*****************************************************************************/
NOEUD *insere(NOEUD *p, element x)
{
    if (p == NULL) 
    {
        p = (NOEUD *)malloc(sizeof(NOEUD));
        p->valeur = x;p->gauche = NULL;p->droit = NULL;
    }
    else if (x == p->valeur) printf("%d est deja dans l'arbre\n",x);
    else if (x < p->valeur)  p->gauche = insere(p->gauche,x);
    else p->droit  = insere(p->droit,x);

    return(p);        
}
/*****************************************************************************/
void affiche_arbre(NOEUD *p, int col)
{
    int i;
    if (p)
    {
        affiche_arbre(p->droit,col+1);
        for (i=0;i<col;i++) printf("   ");
            printf("%d\n",p->valeur);
        affiche_arbre(p->gauche,col+1);
    }   
}

/* Retourne le nombre de feuilles de l'arbre */
int nombre_feuilles(NOEUD * p)
{
    if (p == NULL)
        return 1;
    else
        return nombre_feuilles(p->gauche) + nombre_feuilles(p->droit);
}

/* Affiche l'arbre en largeur */
void parcours_largeur(NOEUD * rac)
{
    file * f = creer_file();
    enfiler(f, rac);
        
    NOEUD * p;
    while (! file_estVide(f))
    {
        p = defiler(f);
        printf("%d ", p->valeur);
        if (p->gauche) enfiler(f, p->gauche);
        if (p->droit) enfiler(f, p->droit);
    }
    printf("\n");
}
/*
int main()
{
    NOEUD *a[3]; 
    /* on peut travailler sur 3 arbres  *//*
    char c;
    int i, j;
    element x;
    char nom_fich[20];
    FILE *fich;

  NOEUD *a[3]; /* on peut travailler sur 3 arbres *//*
  char c;
  int i, j;
  element x;
  char nom_fich[20];
  FILE *fich;

    do {
        printf("Commande ? "); c = getchar();
        switch(c)
        {
            case 'v' : scanf("%d",&i); a[i] = arbre_vide(); break;     
            case 'i' : scanf("%d %d",&x,&i); a[i] = insere(a[i],x); break;    
            case 'a' : scanf("%d",&i); affiche_arbre(a[i],1); break;           
            case 'n' : scanf("%d",&i); nombre_feuilles(a[i]); break;
            case 'p' : scanf("%d",&i); parcours_largeur(a[i]); break;
            case 'q' : exit(0); 
        }
        printf("\n"); c = getchar();
    }
    while (1);
}*/
/****************************************************************************/  


