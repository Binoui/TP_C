typedef int element;

typedef struct noeud
{
    element valeur;
    struct noeud *gauche, *droit;
} NOEUD, *ABR;

NOEUD* arbre_vide();    

NOEUD* insere(NOEUD* p,element x);

void affiche_arbre(NOEUD* p,int col);         

void parcours_pref(NOEUD *p); 

void parcours_inf(NOEUD *p); 

void parcours_suf(NOEUD *p); 

void parcours_largeur(NOEUD * rac);