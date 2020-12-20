#ifndef COLORLIST_H
# define COLORLIST_H

# include "quadtree_struct.h"

typedef struct s_colorlist{
	struct s_quadtree **qt;
	int deleted;
	struct s_colorlist *next;
	struct s_colorlist *prev;
	struct s_colorlist_container *container;
}t_cl;

typedef struct s_colorlist_index{
	struct s_colorlist_container *index;
	struct s_colorlist_index *next;
}t_ci;

typedef struct s_colorlist_container{
	struct s_colorlist *first;
	struct s_colorlist *last;
}t_clc;

/*
 * Fonction permettant de vider le quadtree ainsi que la liste de couleur
 * Param qt quadtree a vider
*/ 
void delete_tree_and_colorlist(t_qt **qt);

/*
 * Fonction permettant de supprimer un élément de la liste de couleur
 * Param c liste de couleur
 * Param del indice de l'élément a supprimer
*/ 
t_cl *delete_any_colorlist(t_clc **c, t_cl *del);

/*
 * Fonction permettant de réajouter un élément supprimer dans la liste de couleur
 * Param c liste de couleur
 * Param qt quadtree
*/ 
void addback_colorlist(t_clc **c, t_qt **qt);

/*
 * Fonction permettant d'ajouter un élément en tête de liste
 * Param c liste de couleur
 * Param qt quadtree
*/ 
void addfront_colorindex(t_ci **c, t_qt **qt);

/*
 * Fontion permettant la mise à jour des index des éléments si ajout d'un nouvelle
 * élément
 * Param ci liste de couleur
 * Param qt quadtree
*/ 
void update_colorlist(t_ci **ci, t_qt **qt);

/*
 * Fonction permettant de compter le nombre de couleur sur une ligne
 * Param c liste de couleur
*/ 
int	count_color_line(t_clc *c);

/*Fonction permettant le nombre de couleur
 * Param c liste de couleur
*/ 
int	count_color(t_ci *c);

/*
 * Fonction permettant la récupération des blocs de mémoire non utilisé
 * Param c liste de couleur
 * Param garbage_collector utilisé pour la récupération des blocs de mémoire non 
 * utilisé
*/ 
void minimize2(t_ci **c, t_qt ***garbage_collector);

/*
 * Fonction permettant de vider la liste de couleur
 * Param ci liste de couleur
*/ 
void delete_colorlist(t_ci **ci);

/*
 * Fonction permettant d'afficher la liste de couleur
 * Param clc liste de couleur
*/ 
void display_colorlist(t_clc *clc);

/*
 * Fonction permettant d'afficher en inverse la liste de couleur
 * Param clc liste de couleur
*/ 
void display_colorlist_otherway(t_clc *clc);

/*Fonction test pour la liste de couleur, son affichage
 * Param ci liste de couleur
*/ 
void test_colorlist(t_ci *ci);

/*
 * Fonction permettant de chercher un noeud dans l'arbre
 * Param node noeud a chercher
 * Param b quadtree
*/ 
t_qt *test_search_nb(unsigned int node, t_qt *b);

#endif
