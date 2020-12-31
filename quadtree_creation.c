#include "includes/quadtree.h"
#include "includes/err.h"

/*
 * Fonction qui renvoie un pointeur sur un noeud d'arbre quadtree allouer, une
 * variable statique nous permet d'incrementer le numero du noeud a chaqua fois
 * qu'on rentre dans la fonction
 * Param reset utiliser pour mettre le numero des noeuds a 0
*/ 
t_qt *create_tree(int reset){
	t_qt *new_qt;
	static unsigned int n_node = 0;
	if (reset == 0){
		n_node = 0;
		return (NULL);
	}
	new_qt = (t_qt*)malloc(sizeof(t_qt));
	if (!new_qt){
		malloc_handling();
	}
	new_qt->no = NULL;
	new_qt->ne = NULL;
	new_qt->se = NULL;
	new_qt->so = NULL;
	new_qt->dist = -1;
	new_qt->n_node = n_node;
	new_qt->color = MLV_COLOR_BLUE;
	new_qt->cl = NULL;
	new_qt->deleted = 0;
	n_node++;
	return (new_qt);
}

/*
 * Fonction permettant de supprimer tous les noeuds d'un quadtree
 * Param qt quadtree
*/
void delete_tree(t_qt **qt){
	if (!*qt || (*qt)->deleted == 1){
		return ;
	}
	delete_tree(&(*qt)->no);
	delete_tree(&(*qt)->ne);
	delete_tree(&(*qt)->se);
	delete_tree(&(*qt)->so);
	*qt = NULL;
}

/*
 * Fonction permettant de calculer distance entre 2 points
 * Param x1 premier nombre
 * Param x2 deuxieme nombre
*/ 
static int d(int x1, int x2){
	return (x2 - ((x2 - x1) / 2));
}

/*
 * Fonction permettant de recuperer la somme des distances entre color px et
 * color moyenne
 * Param img image
 * Param x1 coordonné du coin superieur gauche de la zone
 * Param x2 coordonné du coin inferieur droit de la zone
 * Param y1 coordonné du coin superieur gauche de la zone
 * Param y2 coordonné du coin inferieur gauche de la zone
 * Param qu quadtree
*/ 
static double get_error_dist(MLV_Image *img, int x1, int x2, int y1, int y2, t_qt **qt){
	t_color	moy;
	t_color	px;
	double	distance;
	int	save_x1;
	save_x1 = x1;
	distance = 0;
	moy = get_average_rgba_from_image(img, x1, x2, y1, y2);
	if (*qt){
		(*qt)->color = MLV_convert_rgba_to_color(moy.red, moy.green, moy.blue, moy.alpha);
	}
	while (y1 < y2){
		while (x1 < x2){
			MLV_get_pixel_on_image(img, x1, y1, &(px.red), &(px.green),
				&(px.blue), &(px.alpha));
			distance += dist(px, moy);
			x1++;
		}
		x1 = save_x1;
		y1++;
	}
	return (distance);
}

/*
 * Fonction permettant de remplir la zone avec les coordonees
 * Param zone a remplir
 * Param x1 coordonné du coin superieur gauche de la zone
 * Param x2 coordonné du coin inferieur droit de la zone
 * Param y1 coordonné du coin superieur gauche de la zone
 * Param y2 coordonné du coin inferieur gauche de la zone
*/
void fill_zone(t_zone *zone, int x1, int x2, int y1, int y2){
	(*zone).x1 = x1;
	(*zone).x2 = x2;
	(*zone).y1 = y1;
	(*zone).y2 = y2;
}

/*
 * Fonction permettant de creer la liste et l'arbre
 * Param parent noeud parent quadtree
 * Param qt quadtree
 * Param l liste container
 * Param img image
 * Param x1 coordonné du coin superieur gauche de la zone
 * Param x2 coordonné du coin inferieur droit de la zone
 * Param y1 coordonné du coin superieur gauche de la zone
 * Param y2 coordonné du coin inferieur gauche de la zone
*/
static void create_list_and_tree(t_qt **parent, t_qt **qt, t_lc **l, MLV_Image *img, int x1, int x2, int y1, int y2){
	t_zone zone;
	(*qt) = create_tree(1);
	(*qt)->par = *parent;
	(*qt)->dist = get_error_dist(img, x1, x2, y1, y2, qt);;
	if ((*qt)->dist <= 80.0 && (x2 - x1) > 1 && (y2 - y1) > 1){
		return ;
	}
	fill_zone(&zone, x1, x2, y1, y2);
	add_order(&(*l)->first, &(*l)->last, (*qt), (*qt)->dist, zone);
}

/*
 * Fonction permettant de generer l'arbre
 * Param l liste container
 * Param img image
 * Param qt quadtree
 * Param zone a etudier
*/ 
static int gen_tree(t_lc **l, MLV_Image *img, t_qt **qt, t_zone zone){
	t_zone save;
	fill_zone(&save, zone.x1, zone.x2, zone.y1, zone.y2);
	if (!(*qt)){
		(*qt) = create_tree(1);
		(*qt)->dist = get_error_dist(img, zone.x1, zone.x2, zone.y1, zone.y2, qt);
		add_order(&(*l)->first, &(*l)->last,(*qt), (*qt)->dist, zone);
	}
	if (!(*qt)->no){
		create_list_and_tree(qt, &(*qt)->no, l, img, save.x1, d(save.x1, save.x2), save.y1, d(save.y1, save.y2));
	}
	if (!(*qt)->ne){
		create_list_and_tree(qt, &(*qt)->ne, l, img, d(save.x1, save.x2), save.x2, save.y1, d(save.y1, save.y2));
	}
	if (!(*qt)->se){
		create_list_and_tree(qt, &(*qt)->se, l, img, d(save.x1, save.x2), save.x2, d(save.y1, save.y2), save.y2);
	}
	if (!(*qt)->so){
		create_list_and_tree(qt, &(*qt)->so, l, img, save.x1, d(save.x1, save.x2), d(save.y1, save.y2), save.y2);
	}
	return (1);
}

/*
 * Fonction generant l'arbre
 * Param l liste container
 * Param img image
 * Param qt quadtree
 * Param zone a etudier
*/ 
static void	go_to_worst(t_lc **l, MLV_Image *img, t_qt **qt, t_zone zone){
	if (!(*qt)){
		return ;
	}
	gen_tree(l, img, qt, zone);
}

/*
 * Fonction permettant d'afficher la zone
 * Param z zone a afficher
*/ 
void print_zone(t_zone z){
	printf("(%d,%d) - (%d, %d)\n", z.x1, z.x2, z.y1, z.y2);
}

/*
 * Fonction permettant de creer un arbre quadtree basé sur img, calcule la
 * distance entre la couleur moyenne de la zone et chacun des pixels qui compose
 * l'image dans cette zone specifique, garde chaque distance dans une double
 * liste chainé trié contenue dans un list_container l, le premier noeud de la
 * liste est celui que nous devons divisé en 4
 * Param l liste container avec un pointeur sur le premier element de liste
 * utiliser pour avoir la pire distance
 * Param img image utiliser pour creer le quadtree
 * Param operations nombre d'operations
*/
void quadtree_maker2(t_lc **l, MLV_Image *img, t_qt **qt, int operations){
	int	i;
	int	pct;
	float pct_calc;
	t_zone zone;
	t_list *tmp;
	pct = 0;
	if (!*l){
		return ;
	}
	tmp = NULL;
	fill_zone(&zone, 0, TAILLE_X, 0, TAILLE_Y);
	i = 0;
	gen_tree(l, img, qt, zone);
	if (!*qt){
		err_what(0);
	}
	printf("Creation de l'arbre entier...\n");
	while (i < operations){
		if (!(*l)->first){
			printf("100%%\n");
			return ;
		}
		go_to_worst(l, img, &((*l)->first->ptr), (*l)->first->zone);
		if ((*l)->first){
			tmp = (*l)->first;
			(*l)->first = (*l)->first->next;
			free(tmp);
			tmp = NULL;
		}
		if (DISPLAY == TRUE){
			MLV_clear_window(MLV_COLOR_BLACK);
			draw_quadtree(*qt, 0, TAILLE_X, 0, TAILLE_Y);
			MLV_actualise_window();
		}
		pct_calc = ((float)i / (float)operations) * 100;
		if (operations != 0 && (int)pct_calc >= pct + 5){
			pct = (int)pct_calc;
			printf("%d%%\n", pct);
		}
		i++;
	}
	printf("100%%\n");
}
