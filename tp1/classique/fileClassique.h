#include <stdio.h>
#include <stdlib.h>

typedef struct Cellule Cellule;
typedef struct file file;

file * creer_file();

int file_estVide(file * f);

void enfiler(file * f, int val);

int defiler(file * f);

void afficher_file(file * f);

void concatener_files(file * f1, file * f2);

void destruction(file * f);