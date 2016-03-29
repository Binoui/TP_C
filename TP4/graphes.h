typedef struct {
 int nbsom;
 int nbarc;
 float **matrice; /* matrice d'adjacence */
} graphe;

typedef struct {	
  int *pere;
  int nbelements;
  int nbclasses; } t_ens;	 


void init_graphe(int nbs, int nba, graphe *g);

void cree_graphe_oriente_value(char *nom_fich, int nbs, int nba);

void cree_graphe_oriente_non_value(char *nom_fich, int nbs, int nba);

void cree_graphe_non_oriente_value(char *nom_fich, int nbs, int nba);

void cree_graphe_non_oriente_non_value(char *nom_fich, int nbs, int nba);

void cree_graphe_topo_value(char *nom_fich, int nbs, int nba);

void cree_graphe_topo_non_value(char *nom_fich, int nbs, int nba);

void init_ens(int dim, t_ens *ens);

int trouver(int x, t_ens *ens);

void reunir(int r1, int r2, t_ens *ens);

void cree_graphe_connexe_non_value(char *nom_fich, int nbs, int nba);

void cree_graphe_connexe_value(char *nom_fich, int nbs, int nba);


