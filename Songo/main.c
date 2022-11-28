#include <stdio.h>
#include <stdlib.h>
#include "songo.h"

int main(int argc, char *argv[])
{
    int choix=1;
    char nom1[25];
    char nom2[25];
    songo a;

    initialiser(&a,1);

    while(choix!=0)
    {
  	    printf("\n\n******************************SONGO TRADITIONNELLE*********************************\n\n");
  	    printf("\n\n**********************************Menu principal***********************************\n\n");
  	    printf("1. 1 joueur\n");
  	    printf("2. 2 joueurs\n");
  	    printf("3. Changer les noms (%s), (%s)\n",a.nom1,a.nom2);
  	    printf("\n0. Quitte\n");
  	    choix=return_valeur(0,3);

        switch(choix)
        {
                case 0 :
                break;
                case 1 : lance_jeu_1joueur(&a);
                initialiser(&a,0);
                break;
                case 2 : lance_jeu_2joueurs(&a);
                initialiser(&a,0);
                break;
                case 3 : changer_noms(&a);
                break;
        }
    }
    system("PAUSE");
    return 0;
}
