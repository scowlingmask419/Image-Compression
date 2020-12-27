#include "includes/quadtree.h"

/*
 * Fonction gérant les erreurs lié au malloc
*/ 
void malloc_handling(void){
	fprintf(stderr, "Erreur dans l'allocation\n");
	exit(EXIT_FAILURE);
}

/*
 * Fonction gérant les erreurs lié a la lecture de fichier ou image
 * Param err correspond au type de l'erreur fichier ou image
*/
void err_what(int err){
	switch (err){
		case 0:
		fprintf(stderr, "How did you even ... ?\n");
		break;
		case 1:
		fprintf(stderr, "Impossible de creer ou de modifier le fichier.\n");
		case 2:
		fprintf(stderr, "Image inaccessible\n");
		break;
	}
	exit(EXIT_FAILURE);
}
