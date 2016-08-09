#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

#ifndef WIN32
    #include <sys/types.h>
    #define CLEAR "clear" 
    /* system("clear") pour UNIX */
#else
    #define CLEAR "cls" 
    /* system("cls") pour Windows */
#endif

int isDir(char* s)
{
    if ((strchr(s, '.')) == NULL) /* Si le nom du chemin n'a pas de point (une extension). */
        return 1;
    else
        return 0;
}

void lire(char* s)
{
    char *enter = NULL;
    char temp[100] = ""; /* Chaîne de caractères temporaire contenant la saisie de l'utilisateur. */

    fgets(temp, 99, stdin);

    enter = strchr(temp, '\n'); /* Voir le chapitre des saisies sécurisées. */
    if (enter != NULL)
        *enter = '\0';

    strcat(s, temp); /* On ajoute à la suite le nom du dossier
    pour obtenir quelque chose comme C:/nom/nom/ pour Win
    ou /nom/nom/ pour UNIX. */
}


void lireDossier(char* s, DIR* rep)
{
    struct dirent* ent = NULL;

    printf(" -- Lecture du dossier '%s' -- \n", s);

    while ((ent = readdir(rep)) != NULL) /* Lecture du dossier. */
        printf("%s\n", ent->d_name);

    printf("\n\n -- Que voulez-vous ouvrir -- ?\n");
}

void parcourirDossier(DIR* rep, char* chemin)
{
    lire(chemin); /* Lecture du nouveau chemin; */

    system(CLEAR); /* On efface l'écran. */

    if (!isDir(chemin))
    {
        printf("%s n'est pas un dossier", chemin);
        exit(-1);
    }

    rep = opendir(chemin);

    if (rep == NULL)
    {
        printf("Le dossier '%s' n'a pas pu etre ouvert", chemin);
        exit(-1);
    }

    lireDossier(chemin, rep); /* Lecture... */

    closedir(rep); /* Fermeture du répertoire. */

    parcourirDossier(rep, chemin); /* On rappelle la fonction parcourirDossier (récursivité). */
}

int main()
{
    DIR* rep = NULL;
    char chemin[500] = "";

    parcourirDossier(rep, chemin);

    closedir(rep);

    return 0;
}

