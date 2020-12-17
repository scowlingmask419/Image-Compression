#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 32

/*
 * Fonction permettant de lire les data dans buffer
 * Param fd descripteur de fichier
 * Param line correspond a la ligne
*/ 
int get_next_line(int const fd, char **line);

/*
 * Fonction permettant l'allocation du type size_t
 * Param size correspond au maximum de blocs pouvant être allouer
*/ 
void *ft_memalloc(size_t size);

typedef struct s_struct{
	char *b1;
	char *b2;
	int fd;
	struct s_struct *next;
	struct s_struct *prev;
}t_struct;

#endif
