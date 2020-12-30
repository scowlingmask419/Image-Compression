#include "includes/quadtree.h"
#include "includes/colorlist.h"
#include "includes/err.h"

/*
 * Fonction permettant de savoir s'il sagit d'un sous arbre
 * Param a quadtree
 * Param b quadtree
*/ 
t_qt *is_subtree(t_qt *a, t_qt *b){
	if (!b){
		return (NULL);
	}
	else if (a == b){
		return (a);
	}
	else{
		if (is_subtree(a, b->no)){
			return (a);
		}
		if (is_subtree(a, b->ne)){
			return (a);
		}
		if (is_subtree(a, b->se)){
			return (a);
		}
		if (is_subtree(a, b->so)){
			return (a);
		}
		return (NULL);
	}
}

/*
 * Fonction permettant d'afficher les noeuds
 * Param a quadtree
 * Param b quadtree
*/ 
t_qt *test_search(t_qt *a, t_qt *b){
	if (!b){
		return (NULL);
	}
	else if (a == b){
		if (a->par){
			printf("parent : %d\n", a->par->n_node);
			if (a->par->no){
				printf("parent->no : %d\n", a->par->no->n_node);
			}
			if (a->par->ne){
				printf("parent->ne : %d\n", a->par->ne->n_node);
			}
			if (a->par->se){
				printf("parent->se : %d\n", a->par->se->n_node);
			}
			if (a->par->so){
				printf("parent->so : %d\n", a->par->so->n_node);
			}
		}
		printf("node ; %d\n", b->n_node);
		return (a);
	}
	else{
		if (test_search(a, b->no)){
			return (a);
		}
		if (test_search(a, b->ne)){
			return (a);
		}
		if (test_search(a, b->se)){
			return (a);
		}
		if (test_search(a, b->so)){
			return (a);
		}
		return (NULL);
	}
}

/*
 * Fonction permettant de chercher un noeud dans l'arbre
 * Param node noeud a chercher
 * Param b quadtree
*/ 
t_qt *test_search_nb(unsigned int node, t_qt *b){
	if (!b){
		return (NULL);
	}
	else if (node == b->n_node){
		if (b->par){
			printf("parent : (%d) => node ; %d\n", b->par->n_node, b->n_node);
		}
		if (b->par->no){
			printf("parent->no : %d\n", b->par->no->n_node);
		}
		if (b->par->ne){
			printf("parent->ne : %d\n", b->par->ne->n_node);
		}
		if (b->par->se){
			printf("parent->se : %d\n", b->par->se->n_node);
		}
		if (b->par->so){
			printf("parent->so : %d\n", b->par->so->n_node);
		}
		return (b);
	}
	else{
		if (test_search_nb(node, b->no)){
			return (b);
		}
		if (test_search_nb(node, b->ne)){
			return (b);
		}
		if (test_search_nb(node, b->se)){
			return (b);
		}
		if (test_search_nb(node, b->so)){
			return (b);
		}
		return (NULL);
	}
}

/*
 * Fonction permettant de savoir s'il sagit d'un enfant
 * Param a quadtree
 * Param b quadtree
*/ 
int	is_child(t_qt *a, t_qt *b){
	if (a && (a->no == b || a->ne ==b || a->se == b || a->so == b)){
		return (1);
	}
	return (0);
}

/*
 * Fonction permettant de comparer des listes de couleurs
 * Param a liste couleur
 * Param b liste couleur
 * Param g_c quadtree garbage collector
*/
t_cl *compare_colorlist(t_cl *a, t_cl **b, t_qt **g_c){
	double dist;
	t_cl *ret;
	t_qt *qt;
	int	dir;
	static int test = 0;
	qt = NULL;
	dir = 0;
	ret = NULL;
	if (!a || !*b || a == *b || !(*b)->qt || !(*(*b)->qt)
	|| *(a->qt) == *((*b)->qt) || (*b)->deleted == 1 || (*(*b)->qt)->deleted == 1 || (*(*b)->qt)->n_node == 0){
		return (ret);
	}
	if (a && a->qt && (*(a->qt)) && b && (*b) && (*b)->qt){
		if ((*(*b)->qt)->par != (*(a->qt)) && is_subtree((*(*b)->qt), *(a->qt))){
			return (ret);
		}
		dist = get_dist_final(a->qt, (*b)->qt);
		if (dist < 15){
			test++;
			qt = (*(*b)->qt)->par;
			if (qt && qt->no == (*(*b)->qt)){
				dir = 0;
			}
			else if (qt && qt->ne == (*(*b)->qt)){
				dir = 1;
			}
			else if (qt && qt->se == (*(*b)->qt)){
				dir = 2;
			}
			else if (qt && qt->so == (*(*b)->qt)){
				dir = 3;
			}
			if ((*(*b)->qt)->par == (*(a->qt))){
				if ((*b)->prev){
					ret = (*b)->prev;
				}
				else{
					ret = NULL;
				}
				if ((*(*b)->qt)->no){
					g_c[(*(*b)->qt)->no->n_node] = (*(*b)->qt)->no;
				}
				if ((*(*b)->qt)->ne){
					g_c[(*(*b)->qt)->ne->n_node] = (*(*b)->qt)->ne;
				}
				if ((*(*b)->qt)->se){
					g_c[(*(*b)->qt)->se->n_node] = (*(*b)->qt)->se;
				}
				if ((*(*b)->qt)->so){
					g_c[(*(*b)->qt)->so->n_node] = (*(*b)->qt)->so;
				}
				(*(*b)->qt)->no = NULL;
				(*(*b)->qt)->ne = NULL;
				(*(*b)->qt)->se = NULL;
				(*(*b)->qt)->so = NULL;
				return (ret);
			}
			(*b)->deleted = 1;
			if ((*b)->prev){
				ret = (*b)->prev;
			}
			else{
				ret = NULL;
			}
			g_c[(*(*b)->qt)->n_node] = (*(*b)->qt);
			(*(*b)->qt) = NULL;
			(*b)->qt = NULL;
			*b = NULL;
			if (dir == 0){
				qt->no = *(a->qt);
			}
			if (dir == 1){
				qt->ne = *(a->qt);
			}
			if (dir == 2){
				qt->se = *(a->qt);
			}
			if (dir == 3){
				qt->so = *(a->qt);
			}
			if (qt){
				qt->deleted = 1;
			}
			return (ret);
		}
	}
	return (ret);
}

/*
 * Fonction permettant de minimiser la liste de couleur
 * Param c liste de couleur
 * Param g_c quadtree garbage collector
*/ 
void minimize_colorlist(t_clc **c, t_qt **g_c){
	t_cl *cmp;
	t_cl *last;
	if (!(*c) || !(*c)->last || (*c)->last == (*c)->first){
		return ;
	}
	last = (*c)->last;
	cmp = (*c)->last->prev;
	while (last){
		while (cmp && cmp != last){
			cmp = compare_colorlist(last, &cmp, g_c);
		}
		if ((*c) && (*c)->last){
			cmp = (*c)->last->prev;
		}
		last = last->prev;
	}
}

/*
 * Fonction permettant la récupération des blocs de mémoire non utilisé
 * Param c liste de couleur
 * Param garbage_collector utilisé pour la récupération des blocs de mémoire non 
 * utilisé
*/
void minimize2(t_ci **c, t_qt ***garbage_collector){
	t_ci *tmp;
	int	i;
	i = 0;
	tmp = *c;
	while (i < OP_MINI * 4 + 1){
		(*garbage_collector)[i++] = NULL;
	}
	while (tmp){
		minimize_colorlist(&(tmp->index), *garbage_collector);
		tmp = tmp->next;
	}
}
