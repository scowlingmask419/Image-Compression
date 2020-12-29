#include "includes/quadtree.h"

/*
 * Fonction permettant de creer la liste encodage
 * Param n noeud
 * Param ptr pointeur quadtree
*/ 
static t_le	*create_le(unsigned int n, t_qt *ptr){
	t_le *new;
	new = (t_le*)malloc(sizeof(t_le));
	if (new){
		new->ptr = ptr;
		new->n_node = n;
		new->next = NULL;
		return (new);
	}
	return (NULL);
}

/*
 * Fonction permettant d'ajouter un noeud a la liste encodage
 * Param n noeud
 * Param l liste encodage
 * Param ptr pointeur quadtree
*/ 
int	add_node_to_le(unsigned int n, t_le **l, t_qt *ptr){
	t_le *tmp;
	tmp = *l;
	if (!tmp){
		*l = create_le(n, ptr);
		return (0);
	}
	while (tmp->next){
		tmp = tmp->next;
	}
	tmp->next = create_le(n, ptr);
	return (0);
}

/*
 * Fonction permettant de chercher un noeud
 * Param n noeud
 * Param l liste encodage
*/ 
t_qt *search_node(unsigned int n, t_le **l){
	t_le *tmp;
	tmp = *l;
	while (tmp){
		if (n == tmp->n_node){
			return (tmp->ptr);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
