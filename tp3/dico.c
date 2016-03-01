typedef struct
{
	char lettre;
	noeud * frere;
	noeud * fils;
} noeud;

dico * insertion(noeud * dico, char * mot, int taille, int index)
{
	noeud * nouveau;

	if (index < taille)
	{
		if (dico == NULL)
		{
			dico = malloc(sizeof(noeud));
			dico->lettre = mot[index];

			insertion(dico->fils, mot, taille, index+1);
		}
		else
		{	
			if (dico->lettre > mot[index])
			{

				if (dico->frere != NULL && dico->frere->lettre > mot[index+1])
				{
					nouveau = malloc(sizeof(noeud));
					nouveau->lettre = mot[index+1];
					nouveau->frere = dico->frere;
					dico->frere = nouveau;
				}	

				insertion(dico->fils, mot, taille, index+1);)
			}
			else
			{
				insertion(dico->fils, mot, taille, index+1);
			}
		}
	}
	return dico;
}

void chargement(noeud * arbre, char * chemin)
{
	int i;
	char * 
	FILE * fich = fopen(chemin, "r");
	
	if (fich == NULL)
		printf("Erreur fichier\n");
	else
	{
		fprintf(chemin, "%d\n", &tailleDico);
		for (i = 0; i < taille; i++)
		{
			fprintf(stderr, "%s\n", );

		}
	}
}

int main(int argc, char *argv[])
{


	return 0;
}