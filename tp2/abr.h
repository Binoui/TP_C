
typedef int element;

typedef struct noeud {
	element valeur;
	struct noeud *gauche, *droit;
} NOEUD, *ABR;


NOEUD* arbre_vide();    

NOEUD* insere(NOEUD* p,element x);

void affiche_arbre(NOEUD* p,int col); 

int nombre_feuilles(NOEUD * p);        

void parcours_pref(NOEUD *p); 

void parcours_inf(NOEUD *p); 

void parcours_suf(NOEUD *p); 

int compteN(NOEUD *p);

int parcoursAffichage (NOEUD* p);