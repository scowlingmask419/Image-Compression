#ifndef TEST_H
# define TEST_H

#include "quadtree_struct.h"
#include "colorlist.h"

/*
 * Fonction permettant de tester la fonction average color
*/ 
void test_color(void);

/*
 * Fonction permettantd de tester le decodage binaire
*/ 
void test_decode(void);

/*
 * Fonction permettant de tester l'encdage
 * Param qt quadtree a tester
*/ 
void test_encode(t_qt *qt);

/*
 * Fonction permettant de tester la fonciton add order
 * Param l_dist liste
 * Param last dernier element
*/ 
void test_lstorder(t_list *l_dist, t_list *last);

/*
 * Fonction permettant de parcourir l'arbre et l'afficher test
 * Param qt quadtree a tester
*/ 
void parcours_test(t_qt *qt);

/*
 * Fonction permettant de tester l decodage d'un graphe
 * Param filename fichier a decoder
*/ 
void test_decode_encode_graph(const char *filename);

/*
 * Fontion permettant de tester la liste couleur son contenu
 * Param ci liste couleur
*/ 
void test_colorlist(t_ci *ci);

#endif
