/******************************************************************************/
/* C. PORQUET                    L_ADJ.c                            Mars 2004 */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "file.h"


typedef struct t_cellule 
	{int extremite;
	 int valuation;
	 struct t_cellule *suivant;
  } T_CELLULE;

typedef struct t_ladj	/* listes d'adjacence */
	{int nbsom, nbar;
   int* nbPred;
	 T_CELLULE **tab;
	} T_LADJ;
/*----------------------------------------------------------------------------*/	
T_CELLULE *creer_cellule(int extr, int val, T_CELLULE *suiv)
{T_CELLULE *p;
 
 p = (T_CELLULE *)malloc(sizeof(T_CELLULE));
 if (p == NULL) exit(-1);
 p->extremite = extr;p->valuation = val; p->suivant = suiv;
 return p;}
/*----------------------------------------------------------------------------*/	
void affiche_liste(T_CELLULE *p)
{while (p) 
       {printf("<%d-%d>\t",p->extremite,p->valuation);
        p = p->suivant; };
 printf("\n"); }
/*----------------------------------------------------------------------------*/		
T_LADJ init_ladj(int nsom, int nar) /* allocation dynamique et initialisation */
{T_LADJ g;
 
 g.nbsom = nsom; g.nbar = nar;
 g.tab = (T_CELLULE **)calloc(nsom,sizeof(T_CELLULE *));
 g.nbPred = (int*)calloc(nsom,sizeof(int));
 if (g.tab == NULL) exit(-1);
 return g;}
/*----------------------------------------------------------------------------*/
void affiche_graphe(T_LADJ g)
{int i;

 for (i=0;i<g.nbsom;i++) 
     {if (g.tab[i]) {printf("Successeurs de %d : ",i);
                     affiche_liste(g.tab[i]); } }
 printf("\n"); }
/*----------------------------------------------------------------------------*/	
T_LADJ charge_graphe(char *nom_fichier)
{T_LADJ g;              
 int nsom, nar;
 FILE *fp;
 int i, ori, ext, val;
 T_CELLULE *p;
 
 fp = fopen(nom_fichier,"rt");
 if (fp == NULL) exit(-1);
 fscanf(fp,"%d %d",&nsom,&nar);
 g = init_ladj(nsom,nar);
 for (i=0;i<nar;i++)
     {fscanf(fp,"%d %d %d",&ori,&ext,&val);
      g.nbPred[ext]++;
      p = creer_cellule(ext,val,g.tab[ori]);     
      g.tab[ori] = p;  /* on empile */
     }  
 fclose(fp);
 return g; }
/*----------------------------------------------------------------------------*/ 
T_LADJ inverse(T_LADJ g)
{T_LADJ g_inverse;
 int i;
 T_CELLULE *p, *q;
 
 g_inverse = init_ladj(g.nbsom,g.nbar);
 for (i=0; i<g.nbsom; i++)
     {p = g.tab[i];
      while (p)
            {q = creer_cellule(i,p->valuation,g_inverse.tab[p->extremite]);     
             g_inverse.tab[p->extremite] = q; /* on empile */
	           p = p->suivant;
             g_inverse.nbPred[i]++;
            }
     } 
 return g_inverse; } 
/******************************************************************************/
void affiche_pred(T_LADJ g)
{int i;

 for (i=0;i<g.nbsom;i++) 
     {if (g.tab[i]) {printf("Predecesseurs de %d : ",i);
                     affiche_liste(g.tab[i]); } }
 printf("\n"); }


int marquageTopo(T_LADJ g){
  int i,nbSomTrait=0,indexMarque=0;
  int marquage[g.nbsom];
  T_CELLULE* cel;
  fileC* attente = creer_fileC();

  for(i=0;i<g.nbsom;i++){
    if(g.nbPred[i]==0){
      enfilerC (attente,i);
      nbSomTrait++;
    }
  }


  while(!fileC_vide(attente) || nbSomTrait != g.nbsom){
    if(fileC_vide(attente)){
      return 0;
    }

    marquage[indexMarque]=defiler(attente);
    cel = g.tab[marquage[indexMarque]];
    while (cel) {
      g.nbPred[cel->extremite]--;
            if(g.nbPred[cel->extremite]==0){
        enfilerC(attente,cel->extremite);
        nbSomTrait++;
      }
      cel = cel->suivant; 
    }

    indexMarque++;

  }


  return 1;
}





void main(int argc, char **argv)
{T_LADJ  g, g_inverse;
 
 if (argc!=2) exit(-1);
 
 g = charge_graphe(argv[1]);
 affiche_graphe(g);
 
 g_inverse = inverse(g);
 affiche_pred(g_inverse);


 printf("Marquage topologique sens originel : %d\n",marquageTopo(g));
 printf("Marquage topologique sens inverse : %d\n",marquageTopo(g_inverse));

}

