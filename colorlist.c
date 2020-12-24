#include "includes/colorlist.h"
#include "includes/err.h"

/*
 * Fonction permettant de creer la liste de couleur
 * Param qt quadtree
 * Param c liste de couleur
*/ 
static t_cl	*create_colorlist(t_qt **qt, t_clc **c){
	t_cl *newcl;
	newcl = (t_cl*)malloc(sizeof(t_cl));
	if (!newcl){
		malloc_handling();
	}
	newcl->qt = qt;
	newcl->deleted = 0;
	newcl->next = NULL;
	newcl->prev = NULL;
	newcl->container = *c;
	if (qt && *qt){
		(*qt)->cl = newcl;
	}
	return (newcl);
}

/*
 * Fonction qui va permettre de creer un contenaire qui va contenir la liste
 * Param qt quadtree
*/ 
static t_clc *create_colorlist_container(t_qt **qt){
	t_clc *newclc;
	newclc = (t_clc*)malloc(sizeof(t_clc));
	if (!newclc){
		malloc_handling();
	}
	newclc->first = create_colorlist(qt, &newclc);
	newclc->last = newclc->first;
	return (newclc);
}

/*
 * Fonction permettant d'indexer le container de la liste de couleur
 * Param qt quadtree
*/ 
static t_ci	*create_colorlist_index(t_qt **qt){
	t_ci *newci;
	newci = (t_ci*)malloc(sizeof(t_ci));
	if (!newci){
		malloc_handling();
	}
	newci->index = create_colorlist_container(qt);
	newci->next = NULL;
	return (newci);
}

/*
 * Fonction permettant de vider le quadtree ainsi que la liste de couleur
 * Param qt quadtree a vider
*/ 
void delete_tree_and_colorlist(t_qt **qt){
	if (!qt || !*qt){
		return ;
	}
	delete_tree_and_colorlist(&(*qt)->no);
	delete_tree_and_colorlist(&(*qt)->ne);
	delete_tree_and_colorlist(&(*qt)->se);
	delete_tree_and_colorlist(&(*qt)->so);
	if (qt && *qt && (*qt)->cl && (*qt)->cl->container && (*qt)->deleted == 0){
		delete_any_colorlist(&(*qt)->cl->container, (*qt)->cl);
		(*qt)->deleted = 1;
		(*qt)->no = NULL;
		(*qt)->ne = NULL;
		(*qt)->se = NULL;
		(*qt)->so = NULL;
		if ((*qt)->par && (*qt)->par->no == *qt){
			(*qt)->par->no = NULL;
			free(*qt);
		}
		else if ((*qt)->par && (*qt)->par->ne == *qt){
			(*qt)->par->ne = NULL;
			free(*qt);
		}
		else if ((*qt)->par && (*qt)->par->se == *qt){
			(*qt)->par->se = NULL;
			free(*qt);
		}
		else if ((*qt)->par && (*qt)->par->so == *qt){
			(*qt)->par->so = NULL;
			free(*qt);
		}
		*qt = NULL;
	}
}

/*
 * Fonction permettant de supprimer un élément de la liste de couleur
 * Param c liste de couleur
 * Param del indice de l'élément a supprimer
*/ 
t_cl *delete_any_colorlist(t_clc **c, t_cl *del){
	t_cl *tmp;
	t_cl *aux;
	if (!c || !(*c) || !del){
		return (del);
	}
	aux = NULL;
	tmp = (*c)->last;
	while (tmp){
		if (tmp == del && tmp){
			if (tmp && (*c)->first == tmp){
				(*c)->first = (*c)->first->next;
			}
			if (tmp && (*c)->last == tmp){
				(*c)->last = (*c)->last->prev;
			}
			if (!tmp->prev){
				aux = tmp;
				tmp = tmp->next;
				free(aux);
				aux = NULL;
				if (tmp){
					tmp->prev = NULL;
				}
				return (tmp);
			}
			if (tmp){
				aux = tmp->prev;
			}
			if (tmp->prev){
				tmp->prev->next = tmp->next;
			}
			if (tmp->next){
				tmp->next->prev = tmp->prev;
			}
			free(tmp);
			tmp = NULL;
			return (aux);
		}
		tmp = tmp->prev;
	}
	return (del);
}

/*
 * Fonction permettant de réajouter un élément supprimer dans la liste de couleur
 * Param c liste de couleur
 * Param qt quadtree
*/ 
void addback_colorlist(t_clc **c, t_qt **qt){
	t_cl *prev;
	if (!*c){
		return ;
	}
	if (!(*c)->last){
		(*c)->first = create_colorlist(qt, c);
		(*c)->last = (*c)->first;
		return ;
	}
	prev = (*c)->last;
	(*c)->last->next = create_colorlist(qt, c);
	(*c)->last = (*c)->last->next;
	(*c)->last->prev = prev;
}

/*
 * Fonction permettant d'ajouter un élément en tête de liste
 * Param c liste de couleur
 * Param qt quadtree
*/ 
void addfront_colorindex(t_ci **c, t_qt **qt){
	t_ci *newci;
	if (!*c){
		*c = create_colorlist_index(qt);
		return ;
	}
	newci = create_colorlist_index(qt);
	newci->next = *c;
	*c = newci;
}

/*
 * Fonction permettant de vider la liste de couleur
 * Param c container de la liste de couleur
*/ 
void delete_all_colorlist(t_clc **c){
	t_cl *tmp;
	t_cl *prev;
	prev = NULL;
	if (!c || !*c){
		return ;
	}
	tmp = (*c)->first;
	while (tmp){
		if (prev){
			free(prev);
			prev = NULL;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	(*c)->first = NULL;
	(*c)->last = NULL;
	free(*c);
}

/*
 * Fonction permettant de vider la liste de couleur
 * Param ci liste de couleur
*/ 
void delete_colorlist(t_ci **c){
	t_ci *tmp;
	t_ci *prev;
	prev = NULL;
	tmp = *c;
	if (!*c){
		return ;
	}
	while (tmp){
		if (prev){
			prev->index = NULL;
			free(prev);
			prev = NULL;
		}
		delete_all_colorlist(&(tmp->index));
		prev = tmp;
		tmp = tmp->next;
	}
	if (prev){
		prev->index = NULL;
		free(prev);
		prev = NULL;
	}
}
