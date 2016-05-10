/******************************************************************************/
/* G.Auffret/ B.Houx                  MPM.c                          Mai 2016 */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "mpm.h"

void affichageSommet(T_LADJ g){
	int i;
	Sommet s;

	for(i=0;i<g.nbsom;i++){
		s = g.sommet[i];
		printf("Le sommet %s doit commencer au plus tot la %deme semaine et au plus tard la %deme semaine.\n\tElle a donc une marge de %d. Cette tache dur %d semaines.\n\tCette tache est elle critique ? %d\n\n",s.nom,s.datePlusTot, s.datePlusTard, s.marge,s.duree,s.critique);
	}

}



void main(int argc, char **argv){
	T_LADJ g;

	if (argc!=2) exit(-1);

	g = charge_graphe(argv[1]);

	g=marquageTopo(g);
	affichageSommet(g);


}