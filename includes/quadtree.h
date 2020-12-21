#ifndef QUADTREE_H
# define QUADTREE_H

# define OP 65536 /*2¹⁶*/
# define OP_MINI 10000
# define DISPLAY 0
# define TRUE 1

# include "libinclude.h"
# include "quadtree_struct.h"

enum{
	WHAT, 
	FILE_ISSUE, 
	IMG_NOT_FOUND, 
	COLOR, 
	NOCOLOR
};

typedef struct s_color{
	int	red;
	int	green;
	int	blue;
	int	alpha;
}t_color;

/*
 * Fonction permettant de dupliquer une chaine de caractere
 * Param s1 chaine de caractere a dupliquer
*/ 
char *ft_strdup(const char *s1);

/*
 * Fontion permettant de calculer la distance entre px et moy
 * Param px couleur de la somme des pixels
 * Param moy moyenne des couleur de la zone
*/ 
double dist(t_color px, t_color moy);

/*
 * Fonction qui renvoie un pointeur sur un noeud d'arbre quadtree allouer, une
 * variable statique nous permet d'incrementer le numero du noeud a chaqua fois
 * qu'on rentre dans la fonction
 * Param reset utiliser pour mettre le numero des noeuds a 0
*/ 
t_qt *create_tree(int reset);

/*
 * Fonction permettant de convertir MLV_Color a t_color
 * Param x couleur a convertir en t_color
 * Param x_c contient la nouvelle couleur convertie
*/ 
void MLV_Color_to_color(MLV_Color x, t_color *x_c);

/*
 * Fonction permeant de compter le nombre de noeuds d'un quadtree
 * Param qt quadtree
*/ 
int	count_node(t_qt *qt);

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
void quadtree_maker2(t_lc **l, MLV_Image *img, t_qt **qt, int operations);

/*
 * Fonction permettant de supprimer tous les noeuds d'un quadtree
 * Param qt quadtree
*/ 
void delete_tree(t_qt **qt);

/*
 * Fonction qui retourne la moyenne de la zone d'une image basé sur les pixels de
 * x1 a x2 et y1 a y2
 * Param img l'image
 * Param x1 coordonné du coin superieur gauche de la zone
 * Param x2 coordonné du coin inferieur droit de la zone
 * Param y1 coordonné du coin superieur gauche de la zone
 * Param y2 coordonné du coin inferieur gauche de la zone
*/ 
MLV_Color get_average_color_from_image(MLV_Image *img, int x1, int x2, int y1, int y2);

/*
 * Fonction qui retourne la moyenne de la zone d'une image basé sur les pixels de
 * x1 a x2 et y1 a y2
 * Param img l'image
 * Param x1 coordonné du coin superieur gauche de la zone
 * Param x2 coordonné du coin inferieur droit de la zone
 * Param y1 coordonné du coin superieur gauche de la zone
 * Param y2 coordonné du coin inferieur gauche de la zone
*/
t_color get_average_rgba_from_image(MLV_Image *img, int x1, int x2, int y1, int y2);

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
void draw_quadtree(t_qt *qt, int x1, int x2, int y1, int y2);

/*
 * Fonction permettant de comparer deux couleur avec une tolerance threshold
 * Param x premiere couleur a comparer
 * Param y deuxieme couleur a comparer
 * Param perte le seuil, threshold
*/ 
int	color_equal(MLV_Color x, MLV_Color y, int perte);

/*
 * Fonction qui retourne la difference entre deux couleurs
 * Param x premiere couleur a comparer
 * Param y deuxieme couleur a comparer
*/ 
int	color_diff(MLV_Color x, MLV_Color y);

/*
 * Fonction qui retourne la distance entre deux quadtrees
 * Param a premier quadtree a comparer
 * Param b deuxieme quadtree a comparer
*/ 
double get_dist_final(t_qt **a, t_qt **b);

/*
 * Fonction permettant de verifier si il s'agit bien d'une feuille
 * Param qt quadtree a verifier
*/ 
int	is_leaf(t_qt *qt);

/*
 * Fonction permettant d'ouvrir un FILE, creer filemname avec l'extension et
 * lance l'encodage binaire
 * Param qt quadtree contenant l'image
 * Param filename nom du fichier a creer sansl'extension
 * Param color egale a COLOR ou NOCOLOR, specifie si on doit encoder en couleur
 * ou noir et blanc
*/
void encode_bin(t_qt *qt, const char *filename, int color);

/*
 * Fonction permettant d'ajouter une extension au fichier
 * Param file le nom complet d'un fichier avec une extension a remplacer par ext
 * Param ext extension voulu
*/ 
char *add_ext_to_filename(const char *file, const char *ext);

/*
 * Fonction ouvrant FILE, creer filename avec l'extension et lance l'encodage
 * Param qt quadtree contenant l'image
 * Param name nom du fichier sans l'extension qui contient l'encodage du quadtree
 * Param color egale a COLOR ou NOCOLOR, specifie si on doit encoder en couleur
 * ou noir et blanc
*/
void hub_encode_graph(t_qt *qt, const char *name, int color);

/*
 * Fonction permettant l'encodage avec la methode graphique en f basé sur qt, un
 * noeud est traduit en hexadecimal par son numero n_node prealablement defini
 * dans la structure, ensuite ses enfants seraient egalement representer par des
 * valeurs hexadecimales correspondant a leur nombre n_node, les feuilles
 * commencent par '=' et tous les 2 caracteres representent une valeur rgba
 * Param qt quadtree contenant l'image
 * Param f pointeur sur la position actuelle du fichier
*/
void encode_graph(t_qt *qt, FILE *f);

/*
 * Fonction ouvrant un fichier nommer filename et decode le contenu en qt, en
 * noir et blanc ou couleur
 * Param filename nom du fichier a ouvrir et decoder
 * Param qt quadtree a remplir
 * Param color egale a COLOR ou NOCOLOR, specifie si on doit decoder en couleur
 * ou noir et blanc
*/ 
void hub_decode_graph(const char *filename, t_qt **qt, int color);

/*
 * Fonction permettant de decoder sans couleur le fichier fp en qt
 * Param qt permettant de contenir le decodage
 * Param fp pointeur sur la position actuelle du fichier
*/ 
void decode_bin_nocolor(t_qt **qt, FILE *fp);

/*
 * Fonction permettant de decoder en couleur le fichier fp en qt, en utilisant
 * tab pour decoder le fichier
 * Param qt permettant de contenir le decodage
 * Param fd pointeur sur la position actuelle du fichier
 * Param tab tableau permettant d'ajouter et de chercher
*/ 
void decode_graph(t_qt **qt, int fd, t_qt **tab);

/*
 * Fonction permettant de decoder sans couleur le fichier fp en qt, en utilisant
 * tab pour decoder le fichier
 * Param qt permettant de contenir le decodage
 * Param fd pointeur sur la position actuelle du fichier
 * Param tab tableau permettant d'ajouter et de chercher
*/ 
void decode_graph_nocolor(t_qt **qt, int fd, t_qt **tab);

/*
 * Fonction ouvrant File, creer filename avec l'extension et lance l'encodage
 * binaire
 * Param qt permettant de contenir le encodage
 * Param fp pointeur sur la position actuelle du fichier
*/
void encode(t_qt *qt, FILE *fp);

/*
 * Fonction permettant l'encodage avec la methode graphique en f basé sur qt, un
 * noeud est traduit en hexadecimal par son numero n_node prealablement defini
 * dans la structure, ensuite ses enfants seraient egalement representer par des
 * valeurs hexadecimales correspondant a leur nombre n_node, les feuilles
 * commencent par '=' et egale a 0 ou 1 si le feuille est blanc ou noir
 * Param qt quadtree contenant l'image
 * Param fp pointeur sur la position actuelle du fichier
*/
void encode_graph_nocolor(t_qt *qt, FILE *fp);

/*
 * Fonction permettant decodage binaire avec la methode graphique en f basé sur qt, un
 * noeud est traduit en hexadecimal par son numero n_node prealablement defini
 * dans la structure, ensuite ses enfants seraient egalement representer par des
 * valeurs hexadecimales correspondant a leur nombre n_node, les feuilles
 * commencent par '=' et egale a 0 ou 1 si le feuille est blanc ou noir
 * Param qt quadtree contenant l'image
 * Param fp pointeur sur la position actuelle du fichier
*/
void decode_bin(t_qt **qt, FILE *fp);

/*
 * Fonction permettant d'afficher le contenu de la liste
 * Param l liste a afficher
 * Param last correspondant au dernier element de la liste
*/ 
void display_list(t_list *l, t_list *last);

/*
 * Fonction permettant l'ajout dans l'ordre 
 * Param l liste
 * Param last dernier element 
 * Param ptr pointeur position dans le quadtree
 * Param dist correspondant a la distance 
 * Param zone correspondant a une zone
*/ 
int add_order(t_list **l, t_list **last, t_qt *ptr, double dist, t_zone zone);

/*
 * Fonction qui renvoie un pointeur sur le premier element la liste
 * Param l_dist utiliser pour creer la liste
*/ 
t_lc *create_list_container(t_list *l_dist);

/*
 * Fonction permettant de remplir la zone avec les coordonees
 * Param zone a remplir
 * Param x1 coordonné du coin superieur gauche de la zone
 * Param x2 coordonné du coin inferieur droit de la zone
 * Param y1 coordonné du coin superieur gauche de la zone
 * Param y2 coordonné du coin inferieur gauche de la zone
*/ 
void fill_zone(t_zone *zone, int x1, int x2, int y1, int y2);

/*
 * Fonction permettant d'afficher la zone
 * Param z zone a afficher
*/ 
void print_zone(t_zone z);

/*
 * Fonction permettant d'afficher la fenetre de depart
*/ 
char *start_screen(void);

/*
 * Fonction permettant de creer l'interface avec le quadtree dessiner
 * Param qt quadtree a dessiner
*/ 
void create_interface(t_qt *qt);

/*
 * Fonction permettant de dessiner l'interface avec les differents boutons de la
 * fenetre
 * Param font affichage du texte et des boites de dialogue
*/ 
void draw_interface(MLV_Font *font);

/*
 * Fonction permettant de gerer les clics des differentes options de la fenetre
 * Param qt quadtree a creer
 * Param filename nom du fichier dans lequel sauvegarder le quadtree
 * Param img image a analyser
*/ 
void click_interface(t_qt **qt, char *filename, MLV_Image *img);

/*
 * Fonction permettant d'ouvir une image ou fichier si demander
 * Param qt quadtree a charger, creer
 * Param filename nom du fichier a ouvrir
 * Param mini permet de savoir s'il faut ouvrir image ou fichier
 * Param img image ou charger
*/ 
void open_img(t_qt **qt, char **filename, int *mini, MLV_Image **img);

/*
 * Fonction permettant de connaitre l'extention de fin du fichier si c'est qtn
 * Param str nom du fichier
*/ 
int	is_qtn(const char *str);

/*
 * Fonction permettant de connaitre l'extention de fin du fichier si c'est qtc
 * Param str nom du fichier
*/ 
int	is_qtc(const char *str);

/*
 * Fonction permettant de connaitre l'extention de fin du fichier si c'est cur,
 * gif, png, tga, ico, bmp, jpg, pcx, jpeg, tiff
 * Param str nom du fichier
*/ 
int	is_img(char *str);

/*
 * Fonction permettant de connaitre l'extention de fin du fichier si c'est gmc
 * Param str nom du fichier
*/ 
int	is_gmc(const char *str);

/*
 * Fonction permettant de connaitre l'extention de fin du fichier si c'est gmn
 * Param str nom du fichier
*/ 
int	is_gmn(const char *str);

#endif
