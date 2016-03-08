typedef struct noeud
{
	char lettre;
	struct noeud* frere;
	struct noeud* fils;
}noeud;

noeud* creeDico ();

int recherche (char* clef, noeud* d,int taille, int index);

noeud* insertion(noeud * dico, char * mot, int taille, int index);

void chargement(noeud * arbre, char * chemin);

void afficheD (noeud* d, int tab);

