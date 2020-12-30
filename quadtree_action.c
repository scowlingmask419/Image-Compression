#include "includes/quadtree.h"

/*
 * Fonction permettant de verifier si il s'agit bien d'une feuille
 * Param qt quadtree a verifier
*/
int	is_leaf(t_qt *qt){
	if (!(qt) || (!qt->no && !qt->ne && !qt->se && !qt->so)){
		return (1);
	}
	return (0);
}

/*
 * Fonction permeant de compter le nombre de noeuds d'un quadtree
 * Param qt quadtree
*/ 
int	count_node(t_qt *qt){
	if (!qt){
		return (0);
	}
	return (1 + count_node(qt->no) + count_node(qt->ne) + count_node(qt->se) + count_node(qt->so));
}
