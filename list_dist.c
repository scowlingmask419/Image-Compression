#include "includes/quadtree.h"
#include "includes/err.h"

/*
 * Fonction permettant de creer une liste qui va contenir la liste des distances
 * Param l_dist liste distance
*/ 
t_ldc *create_list_dist_container(t_ld *l_dist){
	t_ldc	*new;
	new = (t_ldc*)malloc(sizeof(t_ldc));
	if (!new){
		malloc_handling();
	}
	new->first = l_dist;
	new->last = l_dist;
	return (new);
}

/*
 * Fonction permettant de creer une liste qui va contenir les distances
 * Param a quadtree
 * Param b quadtree
 * Param dist distance
*/ 
static t_ld	*create_ld(t_qt **a, t_qt **b, double dist){
	t_ld *new;
	new = (t_ld*)malloc(sizeof(t_ld));
	if (new){
		new->a = a;
		new->b = b;
		new->dist = dist;
		new->next = NULL;
		new->prev = NULL;
		return (new);
	}
	return (NULL);
}

/*
 * Fonction permettant d'ajouter un élément en tête de liste
 * Param l liste
 * Param a quadtree
 * Param b quadtree
 * Param dist distance
*/  
static int add_front_recur(t_ld **l, t_qt **a, t_qt **b, double dist){
	t_ld *tmp;
	tmp = NULL;
	if (!((tmp) = create_ld(a, b, dist))){
		return (-1);
	}
	tmp->next = *l;
	*l = tmp;
	(*l)->prev = NULL;
	if ((*l)->next){
		(*l)->next->prev = (*l);
	}
	return (1);
}

/*
 * Fonction permettant d'ajouter un élément a la fin de liste
 * Param l liste
 * Param a quadtree
 * Param b quadtree
 * Param dist distance
*/ 
static int add_end_recur(t_ld **l, t_qt **a, t_qt **b, double dist){
	t_ld *tmp;
	tmp = NULL;
	if (!(tmp = create_ld(a, b, dist))){
		return (-1);
	}
	(*l)->next = tmp;
	return (1);
}

/*
 * Fonction permettant d'ajouter un élément dans la liste dans l'ordre
 * Param l liste
 * Param a quadtree
 * Param b quadtree
 * Param dist distance
*/ 
static int add_order_any_recur(t_ld **l, t_qt **a, t_qt **b, double dist){
	t_ld *tmp;
	t_ld *save;
	save = NULL;
	tmp = *l;
	while (tmp->prev != NULL){
		if (*(tmp->b) == *b){
			printf("%p vs %p\n", (void*)*(tmp->b), (void*)*b);
			return (1);
		}
		if (tmp->prev->dist >= dist){
			if (!(save = create_ld(a, b, dist))){
				return (-1);
			}
			save->next = tmp;
			save->prev = tmp->prev;
			save->prev->next = save;
			tmp->prev = save;
			tmp->prev->next = tmp;
			return (1);
		}
		g_nb_op_creation++;
		tmp = tmp->prev;
	}
	return (1);
}

/*
 * Fonction permettant d'ajouter un élément dans la liste dans l'ordre
 * Param l liste
 * Param a quadtree
 * Param b quadtree
 * Param dist distance
*/
int	add_order_ld(t_ld **l, t_ld **last, t_qt **a, t_qt **b, double dist){
	t_ld *prev;
	if (*l == NULL){
		*l = create_ld(a, b, dist);
		*last = *l;
		(*last)->prev = NULL;
		(*l)->prev = NULL;
	}
	else if (*l && !(*l)->prev){
		if (dist >= (*l)->dist){
			return (add_front_recur(l, a, b, dist));
		}
		else if (*last && dist <= (*last)->dist){
			add_end_recur(last, a, b, dist);
			prev = *last;
			*last = (*last)->next;
			(*last)->prev = prev;
		}
	}
	else{
		add_order_any_recur(last, a, b, dist);
	}
	return (1);
}

/*
 * Fonction permettant de vider la liste des distances
 * Param l liste
*/ 
void delete_list_dist(t_ldc **l){
	t_ld *tmp;
	t_ld *prev;
	if (!l || !*l){
		return ;
	}
	tmp = (*l)->first;
	if (!tmp){
		free((*l));
		return ;
	}
	prev = NULL;
	while (tmp){
		if (prev){
			free(prev);
			prev = NULL;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	free(prev);
	prev = NULL;
	free(*l);
}

/*
 * Fonction permettant d'afficher la liste des distances
 * Param l liste
*/ 
void display_list_dist(t_ld *l){
	t_ld *tmp;
	int	i;
	i = 0;
	tmp = l;
	if (!tmp){
		return ;
	}
	while (tmp){
		printf("%f\n", tmp->dist);
		if (tmp->prev){
			printf("\tprev = %f\n", tmp->prev->dist);
		}
		tmp = tmp->next;
		i++;
	}
}
