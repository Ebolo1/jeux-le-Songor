
// Si 1, avec ascii anglais  (beau)
// Si 0, avec ascii francais (commun)
#define affichage_beau 0

// Définiton du tableau donnant la profondeur de recherche suivant la difficulte
int tab_profondeur[2][6];

//Définition de la structure du songo
typedef struct
{
    char nom1[25];
    char nom2[25];
	int case_moi[6];
	int case_cpu[6];
	int score_moi;
	int score_cpu;
	int tour_jeu;  // Ne sert que dans l'affichage
	int difficulte;// Hernadez Ebolo 473
	int fini;     //  1 si le jeu est terminé
} songo;


// Définition de la structure de la case à retourner avec le gain de score
typedef struct
{
	int case_meilleure;
	int gain_score;
} case_retour;

// pour les commentaires des fonctions cf. songo.c


int return_valeur(int a,int b); // Demande une valeur entre a et b et la retourne

void initialiser(songo* a,int total); // si total==1, initialise les noms et dif
void afficher(songo a);
void afficher_beau(songo a);
void afficher_commun(songo a);
void joueur_joue(songo* a,int case_choisie);
void cpu_joue(songo* a,int case_choisie);
void demande_joueur(songo* a);
void demande_cpu(songo* a);
void terminer_jeu(songo* a);
case_retour meilleure_case_cpu(songo a,int nbre_recursif);
case_retour meilleure_case_joueur(songo a,int nbre_recursif);
void afficher_gagnant_1joueur(songo a);
void afficher_gagnant_2joueurs(songo a);
void lance_jeu_1joueur(songo* a);
void lance_jeu_2joueurs(songo* a);
void changer_noms(songo * a);
