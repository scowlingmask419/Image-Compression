#ifndef ERR_FNT_H
# define ERR_FNT_H

/*
 * Fonction gérant les erreurs lié au malloc
*/ 
void malloc_handling();

/*
 * Fonction gérant les erreurs lié a la lecture de fichier ou image
 * Param err correspond au type de l'erreur fichier ou image
*/ 
void err_what(int err);

#endif
