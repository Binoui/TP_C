
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

