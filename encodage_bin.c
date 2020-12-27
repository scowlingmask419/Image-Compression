#include "includes/quadtree.h"
#include "includes/err.h"

/*
 * Fonction permettant de convertir en binaire
 * Param c a convertir
 * Param fp pointer de la position actuelle dans le fichier
*/
static void convert_to_bin(uint8_t c, FILE *fp){
    int index;
	char b;
    index = 7;
    while (index >= 0){
		b = (c | (1u << index)) == c;
		fwrite(&b, 1, 1, fp);
        printf("%d", (c | (1u << index)) == c);
        index--;
    }
}

/*
 * Fonction permettant de savoir s'il s'agit de la couleur black ou white
 * Param color la couleur a analyser
*/ 
int black_or_white(MLV_Color color){
    if (color_equal(MLV_COLOR_WHITE, color, 10)){
        return (1);
    }
    return (0);
}

/*
 * Fonction permettant de convertir en binaire les couleurs
 * Param color la couleur
 * Param fp pointer de la position actuelle dans le fichier
*/ 
static void convert_to_bin_rgba(MLV_Color color, FILE *fp){
    t_color c;
    MLV_Color_to_color(color, &c);
    convert_to_bin(c.red, fp);
    printf("][");
    convert_to_bin(c.green, fp);
    printf("][");
    convert_to_bin(c.blue, fp);
    printf("][");
    convert_to_bin(c.alpha, fp);
}

/*
 * Fonction ouvrant File, creer filename avec l'extension et lance l'encodage
 * binaire
 * Param qt permettant de contenir le encodage
 * Param fp pointeur sur la position actuelle du fichier
*/
void encode(t_qt *qt, FILE *fp){
	char c;
    if (!qt){
        return ;
    }
    if (!is_leaf(qt)){
		c = 0;
		fwrite(&c, 1, 1, fp);
        printf("0");
    }
    else{
		c = 1;
		fwrite(&c, 1, 1, fp);
        printf("1[");
        convert_to_bin_rgba(qt->color, fp);
        printf("]\n");
    }
    encode(qt->no, fp);
    encode(qt->ne, fp);
    encode(qt->se, fp);
    encode(qt->so, fp);
}

/*
 * Fonction ouvrant File, creer filename avec l'extension et lance l'encodage
 * binaire sans couleur
 * Param qt permettant de contenir le encodage
 * Param fp pointeur sur la position actuelle du fichier
*/
void encode_nocolor(t_qt *qt, FILE *fp){
	char c;
    if (!qt){
        return ;
    }
    if (!is_leaf(qt)){
		c = 0;
		fwrite(&c, 1, 1, fp);
        printf("0");
    }
    else{
		c = 1;
		fwrite(&c, 1, 1, fp);
        printf("1[");
		if (color_equal(MLV_COLOR_BLACK, qt->color, 50)){
			c = 0;
			fwrite(&c, 1, 1, fp);
		}
		else{
			fwrite(&c, 1, 1, fp);
		}
        printf("]\n");
    }
    encode_nocolor(qt->no, fp);
    encode_nocolor(qt->ne, fp);
    encode_nocolor(qt->se, fp);
    encode_nocolor(qt->so, fp);
}

/*
 * Fonction permettant d'ajouter une extension au fichier
 * Param file le nom complet d'un fichier avec une extension a remplacer par ext
 * Param ext extension voulu
*/ 
char *add_ext_to_filename(const char *file, const char *ext){
	int	len;
	int	i;
	char *ret;
	i = 0;
	if (!file){
		return (ft_strdup("no_name"));
	}
	len = strlen(file);
	ret = (char*)malloc(sizeof(char) * (len + strlen(ext) + 1));
	if (!ret){
		malloc_handling();
	}
	while (len && file[len] != '.'){
		len--;
	}
	if (!len || !ext){
		exit(1);
	}
	while (file[i] && i < len){
		ret[i] = file[i];
		i++;
	}
	len = i;
	i = 0;
	while (ext[i]){
		ret[len + i] = ext[i];
		i++;
	}
	ret[len + i] = 0;
	return (ret);
}

/*
 * Fonction permettant d'ouvrir un FILE, creer filemname avec l'extension et
 * lance l'encodage binaire
 * Param qt quadtree contenant l'image
 * Param filename nom du fichier a creer sansl'extension
 * Param color egale a COLOR ou NOCOLOR, specifie si on doit encoder en couleur
 * ou noir et blanc
*/
void encode_bin(t_qt *qt, const char *filename, int color){
	char *out;
	FILE *fp;
	if (color == COLOR){
		out = add_ext_to_filename(filename, ".qtc");
	}
	else{
		out = add_ext_to_filename(filename, ".qtn");
	}
	fp = fopen(out, "wb");
	if (!fp){
		err_what(FILE_ISSUE);
	}
	if (color == COLOR){
		encode(qt, fp);
	}
	else{
		encode_nocolor(qt, fp);
	}
	free(out);
	fclose(fp);
}
