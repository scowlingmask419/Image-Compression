#include "includes/quadtree.h"
#include "includes/err.h"

/*
 * Fonction permattant de creer le fichier .qtc
 * Param qt quadtree
 * Param filename nom du fichier
 * Param text nom du fichier a remplacer
*/ 
static void create_qtc(t_qt **qt, char **filename, char *text){
	FILE *fp;
	free(*filename);
	*filename = text;
	*qt = NULL;
	fp = fopen(text, "rb");
	if (!fp){
		err_what(FILE_ISSUE);
	}
	decode_bin(qt, fp);
	fclose(fp);
}

/*
 * Fonction permattant de creer le fichier .gmc
 * Param qt quadtree
 * Param filename nom du fichier
 * Param text nom du fichier a remplacer
*/ 
static void create_gmc(t_qt **qt, char **filename, char *text){
	free(*filename);
	*filename = text;
	*qt = NULL;
	hub_decode_graph(*filename, qt, COLOR);
}

/*
 * Fonction permattant de creer le fichier .qtn
 * Param qt quadtree
 * Param filename nom du fichier
 * Param text nom du fichier a remplacer
*/ 
static void create_qtn(t_qt **qt, char **filename, char *text){
	FILE *fp;
	free(*filename);
	*filename = text;
	*qt = NULL;
	fp = fopen(text, "rb");
	if (!fp){
		err_what(FILE_ISSUE);
	}
	decode_bin_nocolor(qt, fp);
	fclose(fp);
}

/*
 * Fonction permattant de creer le fichier .gmn
 * Param qt quadtree
 * Param filename nom du fichier
 * Param text nom du fichier a remplacer
*/ 
static void create_gmn(t_qt **qt, char **filename, char *text){
	free(*filename);
	*filename = text;
	*qt = NULL;
	hub_decode_graph(*filename, qt, NOCOLOR);
}

/*
 * Fonction permattant de creer l'image a partir du quadtree
 * Param qt quadtree
 * Param filename nom du fichier
 * Param text nom du fichier a remplacer
 * Param img l'image
*/ 
static void create_img(t_qt **qt, char **filename, char *text, MLV_Image **img){
	t_list *l;
	t_lc *lc;
	if (*img){
		MLV_free_image(*img);
	}
	free(*filename);
	*filename = text;
	*qt = NULL;
	l = NULL;
	lc = create_list_container(l);
	*img = MLV_load_image(text);
	if (!*img){
		err_what(IMG_NOT_FOUND);
	}
	create_tree(0);
	quadtree_maker2(&lc, *img, qt, OP);
	MLV_clear_window(MLV_COLOR_BLACK);
}

/*
 * Fonction permettant d'ouvir une image ou fichier si demander
 * Param qt quadtree a charger, creer
 * Param filename nom du fichier a ouvrir
 * Param mini permet de savoir s'il faut ouvrir image ou fichier
 * Param img image ou charger
*/
void open_img(t_qt **qt, char **filename, int *mini, MLV_Image **img){
	char *text;
	struct stat	sb;
	text = NULL;
	if (*qt){
		delete_tree(qt);
	}
	*qt = NULL;
	MLV_wait_input_box(TAILLE_X / 6, TAILLE_Y - TAILLE_Y / 3, TAILLE_X - TAILLE_X / 5, 100,
		MLV_COLOR_BLACK, MLV_COLOR_BLACK, MLV_COLOR_GREY,
		"Tapez le chemin de votre image : ", &text);
	if (stat(text, &sb) != -1){
		*mini = 1;
		if (is_img(text)){
			*mini = 0;
			create_img(qt, filename, text, img);
		}
		else if (is_qtn(text)){
			create_qtn(qt, filename, text);
		}
		else if (is_gmn(text)){
			create_gmn(qt, filename, text);
		}
		else if (is_gmc(text)){
			create_gmc(qt, filename, text);
		}
		else if (is_qtc(text)){
			create_qtc(qt, filename, text);
		}
	}
	MLV_clear_window(MLV_COLOR_BLACK);
	create_interface(*qt);
}

/*
 * Fonction permettant de creer l'interface avec le quadtree dessiner
 * Param qt quadtree a dessiner
*/ 
void create_interface(t_qt *qt){
	MLV_Font *font;
	font = MLV_load_font("resources/panforte.ttf", 10);
	if (!font){
		err_what(FILE_ISSUE);
	}
	draw_quadtree(qt, 0, TAILLE_X, 0, TAILLE_Y);
	draw_interface(font);
	MLV_actualise_window();
}
