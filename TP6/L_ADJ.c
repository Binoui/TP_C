/******************************************************************************/
/* C. PORQUET                    L_ADJ.c                            Mars 2004 */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "mpm.h"


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
 int i, ori, ext,num,temps;
 char* nom;
 T_CELLULE *p;
 
 fp = fopen(nom_fichier,"rt");
 if (fp == NULL) exit(-1);
 fscanf(fp,"%d %d",&nsom,&nar);
 g = init_ladj(nsom,nar);
 g.sommet = malloc(nsom*sizeof(Sommet));
 for (i=0;i<nar;i++)
     {fscanf(fp,"%d %d",&ori,&ext);
      g.nbPred[ext]++;
      p = creer_cellule(ext,1,g.tab[ori]);     
      g.tab[ori] = p;  /* on empile */
     }  
  for (i = 0; i < nsom; ++i)
  {
    fscanf(fp,"%d %d %s",&num,&temps,nom);
    g.sommet[num].numero = num;
    g.sommet[num].nom = nom;
    g.sommet[num].duree = temps;
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


T_LADJ marquageTopo(T_LADJ g){
  int i,nbSomTrait=0,indexMarque=0;
  int marquage[g.nbsom];
  T_CELLULE* cel;
  fileC* attente = creer_fileC();

  for(i=0;i<g.nbsom;i++){
    if(g.nbPred[i]==0){
      enfilerC (attente,i);
      nbSomTrait++;
      g.sommet[i].datePlusTot = 0;
    }
  }


  while(!fileC_vide(attente) || nbSomTrait != g.nbsom){
    if(fileC_vide(attente)){
      printf("Il y a un soucis : le graphe n'est pas topologique !\n");
      return g;
    }

    marquage[indexMarque]=defiler(attente);
    cel = g.tab[marquage[indexMarque]];
    while (cel) {
      g.nbPred[cel->extremite]--;
      if(g.nbPred[cel->extremite]==0){
        enfilerC(attente,cel->extremite);
        if(g.sommet[cel->extremite].datePlusTot < g.sommet[marquage[indexMarque]].datePlusTot+g.sommet[marquage[indexMarque]].duree){
          g.sommet[cel->extremite].datePlusTot = g.sommet[marquage[indexMarque]].datePlusTot+g.sommet[marquage[indexMarque]].duree;
        }
        nbSomTrait++;
      }
      cel = cel->suivant; 
    }

    indexMarque++;

  }

  g.sommet[marquage[indexMarque]].datePlusTard = g.sommet[marquage[indexMarque]].datePlusTot;
  g.sommet[marquage[indexMarque]].marge = 0;
  g.sommet[marquage[indexMarque]].critique =1;
  enfilerC(attente,marquage[indexMarque]);
  g = inverse(g);
  indexMarque =0;

  while(!fileC_vide(attente) || nbSomTrait != 0){
    if(fileC_vide(attente)){
      printf("Il y a un soucis : le graphe inverse n'est pas topologique !\n");
      return g;
    }

    marquage[indexMarque]=defiler(attente);
    cel = g.tab[marquage[indexMarque]];
    while (cel) {
      g.nbPred[cel->extremite]--;
      if(g.nbPred[cel->extremite]==0){
        enfilerC(attente,cel->extremite);
        if(g.sommet[cel->extremite].datePlusTard > g.sommet[marquage[indexMarque]].datePlusTard-g.sommet[cel->extremite].duree){
          g.sommet[cel->extremite].datePlusTard = g.sommet[marquage[indexMarque]].datePlusTard-g.sommet[cel->extremite].duree;
          g.sommet[cel->extremite].marge = g.sommet[cel->extremite].datePlusTard - g.sommet[cel->extremite].datePlusTot;
          if(g.sommet[cel->extremite].datePlusTard == g.sommet[cel->extremite].datePlusTot){
            g.sommet[cel->extremite].critique = 1;
          }else{
            g.sommet[cel->extremite].critique =0;
          }
        }
        nbSomTrait++;
      }
      cel = cel->suivant; 
    }

    indexMarque++;

  }


  free(cel);
  free(attente);

  return g;
}



/*

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

*/