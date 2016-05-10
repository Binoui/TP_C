typedef struct{
	int numero;
	char* nom;
	int datePlusTot;
	int datePlusTard;
	int marge;
	int duree;
	int critique;
}Sommet;


typedef struct t_cellule {
	int extremite;
	int valuation;
	struct t_cellule *suivant;
} T_CELLULE;

typedef struct t_ladj{
int nbsom, nbar;
int* nbPred;
Sommet* sommet;
T_CELLULE **tab;
} T_LADJ;


typedef struct cellule Cellule;


typedef struct{
	Cellule* queue;

}fileC;

fileC* creer_fileC();

int fileC_vide(fileC* f);

void enfilerC (fileC* f, int e);

int defiler (fileC* f);

void concatC (fileC* f1, fileC* f2);

void afficheFC (fileC* f);

T_LADJ marquageTopo(T_LADJ g);

T_LADJ charge_graphe(char *nom_fichier);