#include "includes/quadtree.h"

/*
 * Fonction permettant de convertir MLV_Color a t_color
 * Param x couleur a convertir en t_color
 * Param x_c contient la nouvelle couleur convertie
*/
void MLV_Color_to_color(MLV_Color x, t_color *x_c){
	uint8_t x_r, x_g, x_b, x_a;
	MLV_convert_color_to_rgba(x, &x_r, &x_g, &x_b, &x_a);
	(*x_c).red = x_r;
	(*x_c).green = x_g;
	(*x_c).blue = x_b;
	(*x_c).alpha = x_a;
}

/*
 * Fonction permettant d'initialiser les couleur
 * Param ret structure representant les couleurs
*/ 
void init_color(t_color *ret){
	(*ret).red = 0;
	(*ret).green = 0;
	(*ret).blue = 0;
	(*ret).alpha = 0;
}

/*
 * Fonction permettant de comparer les couleurs 
 * Param a couleur sous forme uint8_t
 * Param b couleur sous forme uint8_t
 * Param perte correspondant a la perte d'information
*/ 
int	c_cmp(uint8_t a, uint8_t b, int perte){
	if (a == b || (a > b - perte && a < b + perte) || (a < b + perte && a > b - perte)){
		return (1);
	}
	return (0);
}

/*
 * Fonction permettant de comparer deux couleur avec une tolerance threshold
 * Param x premiere couleur a comparer
 * Param y deuxieme couleur a comparer
 * Param perte le seuil, threshold
*/
int	color_equal(MLV_Color x, MLV_Color y, int perte){
	uint8_t x_r, x_g, x_b, x_a;
	uint8_t y_r, y_g, y_b, y_a;
	MLV_convert_color_to_rgba(x, &x_r, &x_g, &x_b, &x_a);
	MLV_convert_color_to_rgba(y, &y_r, &y_g, &y_b, &y_a);
	if (c_cmp(x_r, y_r, perte) && c_cmp(x_g, y_g, perte) && c_cmp(x_b, y_b, perte) && c_cmp(x_a, y_a, perte)){
		return (1);
	}
	return (0);
}

/*
 * Fonction qui retourne la difference entre deux couleurs
 * Param x premiere couleur a comparer
 * Param y deuxieme couleur a comparer
*/ 
int	color_diff(MLV_Color x, MLV_Color y){
	uint8_t x_r, x_g, x_b, x_a;
	uint8_t y_r, y_g, y_b, y_a;
	MLV_convert_color_to_rgba(x, &x_r, &x_g, &x_b, &x_a);
	MLV_convert_color_to_rgba(y, &y_r, &y_g, &y_b, &y_a);
	return (abs(x_r - y_r + x_g - y_g + x_b - y_b + x_a - y_a));
}

/*
 * Fonction permettant d'afficher la couleur en fonction des autres couleurs
 * Param x correspondant a la couleur
*/
void print_color(MLV_Color x){
	uint8_t x_r, x_g, x_b, x_a;
	MLV_convert_color_to_rgba(x, &x_r, &x_g, &x_b, &x_a);
	printf("rgb(%d, %d, %d)\n", x_r, x_g, x_b);
}

/*
 * Fonction permettant d'afficher toutes les couleurs egales
 * Param qt quadtree
 * Param tmp quadtree 
 * Param x couleur
 * Param nombre de couleur a comparer
*/ 
void	print_every_color_equal(t_qt **qt, t_qt **tmp, MLV_Color x, int *nb_color){
	if (!qt || !(*qt)){
		return ;
	}
	if (is_leaf(*qt) && x != (*qt)->color && color_equal(x, (*qt)->color, 6)){
		*nb_color -= 1;
		free(*qt);
		*qt = *tmp;
		return ;
	}
	print_every_color_equal(&((*qt)->no), tmp, x, nb_color);
	print_every_color_equal(&((*qt)->ne), tmp, x, nb_color);
	print_every_color_equal(&((*qt)->se), tmp, x, nb_color);
	print_every_color_equal(&((*qt)->so), tmp, x, nb_color);
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
 * Fonction permettant de dessiner le quaqtree sur la fenetre en utilisant des
 * feuilles de l'arbre, pour dessiner l'image entiere, qt doit etre a la racine
 * x1 doit etre a 0, x2 doit etre la largeur de la fenetre, y1 doit etre a 0, y2
 * doit etre la hauteur de l'ecran
 * Param qt quadtree
 * Param x1 coordonné du coin superieur gauche de la zone
 * Param x2 coordonné du coin inferieur droit de la zone
 * Param y1 coordonné du coin superieur gauche de la zone
 * Param y2 coordonné du coin inferieur gauche de la zone
*/ 
void draw_quadtree(t_qt *qt, int x1, int x2, int y1, int y2){
	if (!qt){
		return ;
	}
	if (qt && is_leaf(qt)){
		MLV_draw_filled_rectangle(x1, y1, x2 - x1, y2 - y1, qt->color);
		return ;
	}
	draw_quadtree(qt->no, x1, d(x1, x2), y1, d(y1, y2));
	draw_quadtree(qt->ne, d(x1, x2), x2, y1, d(y1, y2));
	draw_quadtree(qt->se, d(x1, x2), x2, d(y1, y2), y2);
	draw_quadtree(qt->so, x1, d(x1, x2), d(y1, y2), y2);
}

/*
 * Fonction qui retourne la moyenne de la zone d'une image basé sur les pixels de
 * x1 a x2 et y1 a y2
 * Param img l'image
 * Param x1 coordonné du coin superieur gauche de la zone
 * Param x2 coordonné du coin inferieur droit de la zone
 * Param y1 coordonné du coin superieur gauche de la zone
 * Param y2 coordonné du coin inferieur gauche de la zone
*/ 
MLV_Color get_average_color_from_image(MLV_Image *img, int x1, int x2, int y1, int y2){
	t_color	color;
	t_color	moy;
	int	save_x1;
	int	nb_px;
	nb_px = 0;
	save_x1 = x1;
	init_color(&color);
	init_color(&moy);
	if (x2 < x1 || y2 < y1 || x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0){
		return (MLV_COLOR_BLACK);
	}
	while (y1 < y2){
		while (x1 < x2){
			MLV_get_pixel_on_image(img, x1, y1, &(color.red), &(color.green),
				&(color.blue), &(color.alpha));
			moy.blue += color.blue;
			moy.red += color.red;
			moy.green += color.green;
			moy.alpha += color.alpha;
			x1++;
			nb_px++;
		}
		x1 = save_x1;
		y1++;
	}
	if (nb_px != 0){
		moy.red = moy.red/nb_px;
		moy.green = moy.green/nb_px;
		moy.blue = moy.blue/nb_px;
		moy.alpha = moy.alpha/nb_px;
	}
	else{
		MLV_get_pixel_on_image(img, x1, y1, &(moy.red), &(moy.green),
				&(moy.blue), &(moy.alpha));
	}
	return (MLV_convert_rgba_to_color(moy.red, moy.green, moy.blue, moy.alpha));
}

/*
 * Fonction qui retourne la moyenne de la zone d'une image basé sur les pixels de
 * x1 a x2 et y1 a y2
 * Param img l'image
 * Param x1 coordonné du coin superieur gauche de la zone
 * Param x2 coordonné du coin inferieur droit de la zone
 * Param y1 coordonné du coin superieur gauche de la zone
 * Param y2 coordonné du coin inferieur gauche de la zone
*/
t_color	get_average_rgba_from_image(MLV_Image *img, int x1, int x2, int y1, int y2){
	t_color	color;
	t_color	moy;
	int	save_x1;
	int	nb_px;
	nb_px = 0;
	save_x1 = x1;
	init_color(&color);
	init_color(&moy);
	if (x2 < x1 || y2 < y1 || x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0){
		return (moy);
	}
	while (y1 < y2){
		while (x1 < x2){
			MLV_get_pixel_on_image(img, x1, y1, &(color.red), &(color.green),
				&(color.blue), &(color.alpha));
			moy.blue += color.blue;
			moy.red += color.red;
			moy.green += color.green;
			moy.alpha += color.alpha;
			x1++;
			nb_px++;
		}
		x1 = save_x1;
		y1++;
	}
	if (nb_px != 0){
		moy.red = moy.red/nb_px;
		moy.green = moy.green/nb_px;
		moy.blue = moy.blue/nb_px;
		moy.alpha = moy.alpha/nb_px;
	}
	else{
		MLV_get_pixel_on_image(img, x1, y1, &(moy.red), &(moy.green),
				&(moy.blue), &(moy.alpha));
	}
	return (moy);
}
