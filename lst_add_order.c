#include "includes/quadtree.h"
#include "includes/err.h"

/*
 * Fonction permettant de creer une liste qui va contenir la liste des distances
 * Param l_dist liste distance
*/ 
t_lc *create_list_container(t_list *l_dist){
	t_lc *new;
	new = (t_lc*)malloc(sizeof(t_lc));
	if (!new){
		malloc_handling();
	}
	new->first = l_dist;
	new->last = l_dist;
	return (new);
}

/*
 * Fonction permettant de creer une liste qui va contenir les distances d'une
 * zone
 * Param ptr pointeur quadtree
 * Param dist distance
 * Param zone a etudier
*/ 
t_list *ft_lstnew(t_qt *ptr, double dist, t_zone zone){
	t_list *new;
	new = (t_list*)malloc(sizeof(t_list));
	if (new){
		new->ptr = ptr;
		new->dist = dist;
		new->next = NULL;
		new->prev = NULL;
		fill_zone(&(new->zone), zone.x1, zone.x2, zone.y1, zone.y2);
		return (new);
	}
	return (NULL);
}

/*
 * Fonction permettant de reajouter un element a liste
 * Param lst liste
 * Param ptr pointeur quadtree
 * Param dist distance
 * Param zone a etudier
*/ 
int	ft_lstadd_back(t_list **lst, t_qt *ptr, double dist, t_zone zone){
	t_list *tmp;
	t_list *elem;
	if ((*lst) == NULL){
		if (!((*lst) = ft_lstnew(ptr, dist, zone))){
			return (-1);
		}
		return (1);
	}
	tmp = (*lst);
	while (tmp->next != NULL){
		tmp = tmp->next;
	}
	if (!(elem = ft_lstnew(ptr, dist, zone))){
		return (-1);
	}
	tmp->next = elem;
	return (1);
}

/*
 * Fonction permettant d'ajouter un élément en tête de liste
 * Param l liste
 * Param ptr pointeur quadtree
 * Param dist distance
 * Param zone a etudier
*/ 
int add_front_recur(t_list **l, t_qt *ptr, double dist, t_zone zone){
	t_list *tmp;
	tmp = NULL;
	if (!((tmp) = ft_lstnew(ptr, dist, zone))){
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
 * Param ptr pointeur quadtree
 * Param dist distance
 * Param zone a etudier
*/
int add_end_recur(t_list **l, t_qt *ptr, double dist, t_zone zone){
	t_list *tmp;
	tmp = NULL;
	if (!(tmp = ft_lstnew(ptr, dist, zone))){
		return (-1);
	}
	(*l)->next = tmp;
	return (1);
}

/*
 * Fonction permettant d'ajouter un élément dans la liste dans l'ordre
 * Param l liste
 * Param ptr pointeur quadtree
 * Param dist distance
 * Param zone a etudier
*/
int	add_order_any_recur(t_list **l, t_qt *ptr, double dist, t_zone zone){
	t_list *tmp;
	t_list *save;
	save = NULL;
	tmp = *l;
	while (tmp->prev != NULL){
		if (tmp->prev->dist >= dist){
			if (!(save = ft_lstnew(ptr, dist, zone))){
				return (-1);
			}
			save->next = tmp;
			save->prev = tmp->prev;
			save->prev->next = save;
			tmp->prev = save;
			tmp->prev->next = tmp;
			return (1);
		}
		tmp = tmp->prev;
	}
	return (1);
}

/*
 * Fonction permettant d'ajouter un élément dans la liste dans l'ordre
 * Param l liste
 * Param l dernier element liste
 * Param ptr pointeur quadtree
 * Param dist distance
 * Param zone a etudier
*/
int add_order(t_list **l, t_list **last, t_qt *ptr, double dist, t_zone zone){
	t_list *prev;
	if (*l == NULL){
		*l = ft_lstnew(ptr, dist, zone);
		*last = *l;
		(*last)->prev = NULL;
		(*l)->prev = NULL;
	}
	else if (dist >= (*l)->dist){
		return (add_front_recur(l, ptr, dist, zone));
	}
	else if (*last && dist <= (*last)->dist){
		add_end_recur(last, ptr, dist, zone);
		prev = *last;
		*last = (*last)->next;
		(*last)->prev = prev;
	}
	else{
		add_order_any_recur(last, ptr, dist, zone);
	}
	return (1);
}

/*
 * Fonction permettant d'afficher le contenu de la liste
 * Param l liste a afficher
 * Param last correspondant au dernier element de la liste
*/ 
void display_list(t_list *l, t_list *last){
	t_list *tmp;
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
	if (last){
		printf("Last = %f\n", last->dist);
		if (last->prev){
			printf("Last prev = %f\n", last->prev->dist);
		}
	}
}
