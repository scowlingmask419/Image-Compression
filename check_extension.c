#include "includes/quadtree.h"

/*
 * Fonction permettant de connaitre l'extention de fin du fichier si c'est qtn
 * Param str nom du fichier
*/ 
int	is_qtn(const char *str){
	int	len;
	if (!str){
		return (0);
	}
	len = strlen(str);
	if (len - 4 > 1 && strcmp(str + (len - 4), ".qtn") == 0){
		return (1);
	}
	return (0);
}

/*
 * Fonction permettant de connaitre l'extention de fin du fichier si c'est gmn
 * Param str nom du fichier
*/ 
int	is_gmn(const char *str){
	int	len;
	if (!str){
		return (0);
	}
	len = strlen(str);
	if (len - 4 > 1 && strcmp(str + (len - 4), ".gmn") == 0){
		return (1);
	}
	return (0);
}

/*
 * Fonction permettant de connaitre l'extention de fin du fichier si c'est gmc
 * Param str nom du fichier
*/ 
int	is_gmc(const char *str){
	int	len;
	if (!str){
		return (0);
	}
	len = strlen(str);
	if (len - 4 > 1 && strcmp(str + (len - 4), ".gmc") == 0){
		return (1);
	}
	return (0);
}

/*
 * Fonction permettant de connaitre l'extention de fin du fichier si c'est qtc
 * Param str nom du fichier
*/ 
int	is_qtc(const char *str){
	int	len;
	if (!str){
		return (0);
	}
	len = strlen(str);
	if (len - 4 > 1 && strcmp(str + (len - 4), ".qtc") == 0){
		return (1);
	}
	return (0);
}

/*
 * Fonction permettant de connaitre l'extention de fin du fichier si c'est cur,
 * gif, png, tga, ico, bmp, jpg, pcx, jpeg, tiff
 * Param str nom du fichier
*/ 
int	is_img(char *str){
	int	len;
	if (!str){
		return (0);
	}
	len = strlen(str);
	if (len - 4 > 1 && (strcmp(str + (len - 4), ".ico") == 0 || strcmp(str + (len - 4), ".cur") == 0
	|| strcmp(str + (len - 4), ".bmp") == 0 || strcmp(str + (len - 4), ".gif") == 0
	|| strcmp(str + (len - 4), ".jpg") == 0 || strcmp(str + (len - 4), ".png") == 0
	|| strcmp(str + (len - 4), ".pcx") == 0 || strcmp(str + (len - 4), ".tga") == 0)){
		return (1);
	}
	if (len - 5 > 1 && (strcmp(str + (len - 5), ".jpeg") == 0 || strcmp(str + (len - 5), ".tiff") == 0)){
		return (1);
	}
	return (0);
}
