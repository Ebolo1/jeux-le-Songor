
#include <stdio.h>
#include <stdlib.h>
#include "songo.h"

// Formate la demande d'un nombre entre a et b
//****************************
int return_valeur(int a,int b)
//****************************
{
    int choix;
    printf("\n\nVotre choix : ");
  	scanf("%d",&choix);
    while ((choix<a)||(choix>b))
    {
  	    printf("Entre %d et %d : ",a,b);
  	    scanf("%c",&choix);
    }
    return choix;
}


// Crée un songo conforme et le renvoie
//**********************************
void initialiser(songo* a,int total)
//**********************************
{
    int i;
    for (i=0;i<6;i++)
    {
        a->case_moi[i]=4;
        a->case_cpu[i]=4;
    }
    a->score_moi=0;
    a->score_cpu=0;
    a->tour_jeu=1;
    a->fini=0;
    if (total==0) return; // On sort et n'initialise pas la suite
    strcpy(a->nom1,"joueur 1");
    strcpy(a->nom2,"joueur 2 / CPU");
    a->difficulte=1;

}


// Affiche l'songo a l'ecran suivant le paramètre def dans songo.h
//********************
void afficher(songo a)
//********************
{
    if (affichage_beau==1)
        afficher_beau(a);
    else
        afficher_commun(a);
}


// Affiche l'songo avec un cadre autour en ascii
//*************************
void afficher_beau(songo a)
//*************************
{
	printf("\n\n\nTour de jeu : %s\n\n",(a.tour_jeu==1?a.nom1:a.nom2));
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);
	printf("%c%2d%c%2d%c%2d%c%2d%c%2d%c%2d%c    score : %d\n",186,a.case_cpu[5],179,a.case_cpu[4],179,a.case_cpu[3],179,a.case_cpu[2],179,a.case_cpu[1],179,a.case_cpu[0],186,a.score_cpu);
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",186,196,196,197,196,196,197,196,196,197,196,196,197,196,196,197,196,196,186);
	printf("%c%2d%c%2d%c%2d%c%2d%c%2d%c%2d%c    score : %d\n",186,a.case_moi[0],179,a.case_moi[1],179,a.case_moi[2],179,a.case_moi[3],179,a.case_moi[4],179,a.case_moi[5],186,a.score_moi);
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);
}


// Affiche l'songo sans cadre, reste commun mais compatible avec tous les ascii
//***************************
void afficher_commun(songo a)
//***************************
{
	printf("\n\n\nTour de jeu : %s\n\n",(a.tour_jeu==1?a.nom1:a.nom2));
	printf("%3d %3d %3d %3d %3d %3d     score : %d\n\n\n",a.case_cpu[5],a.case_cpu[4],a.case_cpu[3],a.case_cpu[2],a.case_cpu[1],a.case_cpu[0],a.score_cpu);
	printf("%3d %3d %3d %3d %3d %3d     score : %d\n\n",a.case_moi[0],a.case_moi[1],a.case_moi[2],a.case_moi[3],a.case_moi[4],a.case_moi[5],a.score_moi);
}


// Le joueur joue un coup entre 0 et 5
// Déplace les pions, change le score
// En paramètre, le plateau de jeu et la case à jouer
//*****************************************
void joueur_joue(songo* a,int case_choisie)
//*****************************************
{
	int case_gene=case_choisie;
	int nb_graine=a->case_moi[case_choisie]; // Nombre de graines dans la case à jouer
	int case_bis=11; // Servira pour la règle : enlève tt enlève rien
	int enleve=0;


	a->case_moi[case_choisie]=0; // Case à jouer remise à 0

	//Dépose les graines
	while(nb_graine!=0)
	{
		case_gene++;
		if (case_gene==12) case_gene=0;
  		if (case_gene==case_choisie) case_gene++; // On est dans la case à jouer, on passe à la suivante
		if (case_gene>5)
			a->case_cpu[case_gene-6]++;
		else
			a->case_moi[case_gene]++;
		nb_graine--;
	}

	// Vérifie la règle : enlève tt enlève rien
	if ((case_gene>5)&&((a->case_cpu[case_gene-6]==2)||(a->case_cpu[case_gene-6]==3)))
	{
		while ((case_bis!=case_gene)&&(enleve==0))
		{
			if (a->case_cpu[case_bis-6]!=0) enleve=1;
			case_bis--;
		}
		case_bis--;
		while ((case_bis>5)&&(enleve==0))
		{
			if ((a->case_cpu[case_bis-6]!=2)&&(a->case_cpu[case_bis-6]!=3)) enleve=1;
			case_bis--;
		}
		// si enleve==1, alors on peut enlever les graines gagnées
		if (enleve==1)
			while ((case_gene>5)&&((a->case_cpu[case_gene-6]==2)||(a->case_cpu[case_gene-6]==3)))
			{
				a->score_moi+=a->case_cpu[case_gene-6];
				a->case_cpu[case_gene-6]=0;
				case_gene--;
			}
	}
	a->tour_jeu=2; // C'est au tour de l'autre
}


// Le cpu joue un coup entre 0 et 5
// Déplace les pions, change le score
// En paramètre le plateau de jeu et la case à jouer
//**************************************
void cpu_joue(songo* a,int case_choisie)
//**************************************
{
	int case_gene=case_choisie;
	int nb_graine=a->case_cpu[case_choisie];
	int case_bis=11; // Servira pour la règle : enlève tt enlève rien
	int enleve=0;


	a->case_cpu[case_choisie]=0;

	//Dépose les graines
	while(nb_graine!=0)
	{
		case_gene++;
		if (case_gene==12) case_gene=0;
		if (case_gene==case_choisie) case_gene++;
		if (case_gene>5)
			a->case_moi[case_gene-6]++;
		else
			a->case_cpu[case_gene]++;
		nb_graine--;
	}

	//Enlève celles gagnées et augmente le score
		// Vérifie la règle : enlève tt enlève rien
	if ((case_gene>5)&&((a->case_moi[case_gene-6]==2)||(a->case_moi[case_gene-6]==3)))
	{
		while ((case_bis!=case_gene)&&(enleve==0))
		{
			if (a->case_moi[case_bis-6]!=0) enleve=1;
			case_bis--;
		}
		case_bis--;
		while ((case_bis>5)&&(enleve==0))
		{
			if ((a->case_moi[case_bis-6]!=2)&&(a->case_moi[case_bis-6]!=3)) enleve=1;
			case_bis--;
		}
		// si enleve==1, alors on peut enlever les graines gagnèes
		if (enleve==1)
			while ((case_gene>5)&&((a->case_moi[case_gene-6]==2)||(a->case_moi[case_gene-6]==3)))
			{
				a->score_cpu+=a->case_moi[case_gene-6];
				a->case_moi[case_gene-6]=0;
				case_gene--;
			}
	}
	a->tour_jeu=1; // Au tour de l'autre
}


// Demande au joueur quel coup il veut jouer
// Joue le coup choisi
//***************************
void demande_joueur(songo* a)
//***************************
{
	int i=0;
	int coup;

	// Vérifie si le jeu n'est pas fini
	if (a->case_cpu[0]+a->case_cpu[1]+a->case_cpu[2]+a->case_cpu[3]+a->case_cpu[4]+a->case_cpu[5]==0)
	{
		while ((i+a->case_moi[i]<6)&&(i<6)) i++; // Vérifie si on peut donner des graines
		if (i==6)
		{
			a->fini=1;
			return; // Jeu fini
		}
	}

	printf("Quel case : ");
	scanf("%d",&coup);

	// Coup entre 1 et 6
	while ((coup<1)||(coup>6))
	{
		printf("Il faut entre 1 et 6 : ");
		scanf("%d",&coup);
	}

	// Joue une case non vide
	while (a->case_moi[coup-1]==0)
	{
		printf("Il faut jouer une case non vide : ");
		scanf("%d",&coup);
	}

	// Vérifie si l'adversaire n'a pas de graine
	if (a->case_cpu[0]+a->case_cpu[1]+a->case_cpu[2]+a->case_cpu[3]+a->case_cpu[4]+a->case_cpu[5]==0)
		while (coup+a->case_moi[coup-1] < 7)
		{
			printf("Il faut donner des graines ! (radin) : ");
			scanf("%d",&coup);
		}

	joueur_joue(a,coup-1);
}


// Demande au cpu quel coup il veut jouer
// Joue le coup
// Mode 2 joueurs
//************************
void demande_cpu(songo* a)
//************************
{
	int i;
	int coup;

	// Vérifie si le jeu n'est pas fini
	if (a->case_moi[0]+a->case_moi[1]+a->case_moi[2]+a->case_moi[3]+a->case_moi[4]+a->case_moi[5]==0)
	{
		while ((i+a->case_cpu[i]<6)&&(i<6)) i++; // Vérifie si on peut donner des graines
		if (i==6)
		{
			a->fini=1;
			return; // Jeu fini
		}
	}

	printf("Quel coup : ");
	scanf("%d",&coup);

	// Coup entre 1 et 6
	while ((coup<1)||(coup>6))
	{
		printf("Il faut entre 1 et 6 : ");
		scanf("%d",&coup);
	}

	// Joue une case non vide
	while (a->case_cpu[coup-1]==0)
	{
		printf("Il faut jouer une case non vide : ");
		scanf("%d",&coup);
	}

	// Vérifie si l'adversaire n'a pas de graine
	if (a->case_moi[0]+a->case_moi[1]+a->case_moi[2]+a->case_moi[3]+a->case_moi[4]+a->case_moi[5]==0)
		while (coup-1+a->case_cpu[coup-1]<6)
		{
			printf("Il faut donner des graines ! (radin) :");
			scanf("%d",&coup);
		}

	cpu_joue(a,coup-1);
}


// Affecte les dernieres graines quand le jeu est fini
//*************************
void terminer_jeu(songo* a)
//*************************
{
	int i;
	a->score_moi+=a->case_moi[0]+a->case_moi[1]+a->case_moi[2]+a->case_moi[3]+a->case_moi[4]+a->case_moi[5];
	a->score_cpu+=a->case_cpu[0]+a->case_cpu[1]+a->case_cpu[2]+a->case_cpu[3]+a->case_cpu[4]+a->case_cpu[5];
	for (i=0;i<6;i++)
	{
		a->case_moi[i]=0;
		a->case_cpu[i]=0;
	}
}


// Cherche le meilleur coup du CPU de façon recursive
// Renvoie la case donnant le meilleur coup et le gain de score
//*******************************************************
case_retour meilleure_case_cpu(songo a,int nbre_recursif)
//*******************************************************
{
	int i;
	case_retour sortie={0,0}; // On retourne la meilleure case avec le gain
	songo song[6];
	int case_retenue=-1;
	int gain_retenu=-36;
	int gain_actuel;
	int donne[6]={0,0,0,0,0,0}; // Marquera les cases qui ne donnent pas de graine

	// Vérifie si l'adversaire est sans graines et marque les cases qui ne donnent pas
	if (a.case_moi[0]+a.case_moi[1]+a.case_moi[2]+a.case_moi[3]+a.case_moi[4]+a.case_moi[5]==0)
	{
		for(i=0;i<6;i++)
			if (i+a.case_cpu[i] < 6)
				donne[i]=1;
		if (donne[0]+donne[1]+donne[2]+donne[3]+donne[4]+donne[5]==6) // Jeu fini car adversaire sans graine et on peut pas donner
		{
			sortie.gain_score=a.score_moi-a.score_cpu;
			terminer_jeu(&a);
			sortie.case_meilleure=-1;
			sortie.gain_score+=a.score_cpu-a.score_moi;
			return sortie;
		}
	}

	// Le jeu n'est pas fini
	for (i=0;i<6;i++)
		if ((a.case_cpu[i]!=0)&&(donne[i]==0)) // donne[i]=1 si adversaire sans graine et cette case ne donne pas
		{
			song[i]=a;
			cpu_joue(&song[i],i);
			if (nbre_recursif==0)
				gain_actuel=a.score_moi-a.score_cpu+song[i].score_cpu-song[i].score_moi;
			else
			{
				sortie=meilleure_case_joueur(song[i],nbre_recursif-1); // Lance la fonction récursive complémentaire
				gain_actuel=a.score_moi-a.score_cpu+song[i].score_cpu-song[i].score_moi-sortie.gain_score;
			}
			if (gain_actuel>gain_retenu)
			{
				gain_retenu=gain_actuel;
				case_retenue=i;
			}
		}

	sortie.case_meilleure=case_retenue;
	sortie.gain_score=gain_retenu;

	return sortie;
}


// Cherche le meilleur coup du joueur de facon recursive
// Renvoie la case donnant le meilleur coup et le gain de score
// Fonction complémentaire à meilleure_case_cpu(...)
//**********************************************************
case_retour meilleure_case_joueur(songo a,int nbre_recursif)
//**********************************************************
{
	int i;
	case_retour sortie={0,0};
	songo song[6];
	int case_retenue=-1;
	int gain_retenu=-36;
	int gain_actuel;
	int donne[6]={0,0,0,0,0,0}; // Marque les cases qui ne donnent pas de graine

	// Vérifie si l'adversaire est sans graines et marque les cases qui ne donnent pas
	if (a.case_cpu[0]+a.case_cpu[1]+a.case_cpu[2]+a.case_cpu[3]+a.case_cpu[4]+a.case_cpu[5]==0)
	{
		for(i=0;i<6;i++)
			if (i+a.case_moi[i] < 6)
				donne[i]=1;
		if (donne[0]+donne[1]+donne[2]+donne[3]+donne[4]+donne[5]==6) // Jeu fini
		{
			sortie.gain_score=a.score_cpu-a.score_moi;
			terminer_jeu(&a);
			sortie.case_meilleure=-1;
			sortie.gain_score+=a.score_moi-a.score_cpu;
			return sortie;
		}
	}

	for(i=0;i<6;i++)
		if ((a.case_moi[i]!=0)&&(donne[i]==0))
		{
			song[i]=a;
			joueur_joue(&song[i],i);
			if (nbre_recursif==0)
			{
				gain_actuel=a.score_cpu-a.score_moi+song[i].score_moi-song[i].score_cpu;
			}
			else
			{
				sortie=meilleure_case_cpu(song[i],nbre_recursif-1);
				gain_actuel=a.score_cpu-a.score_moi+song[i].score_moi-song[i].score_cpu-sortie.gain_score;
			}
			if (gain_actuel>gain_retenu)
			{
				gain_retenu=gain_actuel;
				case_retenue=i;
			}
		}

	sortie.case_meilleure=case_retenue;
	sortie.gain_score=gain_retenu;

	return sortie;
}


// Affiche le gagnant pour jeu 1 joueur
//************************************
void afficher_gagnant_1joueur(songo a)
//************************************
{
	if (a.score_moi > a.score_cpu)
		printf("Le gagnant est %s !\n Félicitations.\n\n",a.nom1);
	else
		if (a.score_moi < a.score_cpu)
			printf("Le gagnant est l'ordinateur !\n Entraines-toi encore.\n\n");
		else
			printf("Match nul !\n Pas mal du tout.\n\n");
}


// Affiche le gagnant pour le jeu à 2 joueurs
//*************************************
void afficher_gagnant_2joueurs(songo a)
//*************************************
{
	if (a.score_moi > a.score_cpu)
		printf("Le gagnant est %s !\n Félicitations\n\n",a.nom1);
	else
		if (a.score_moi < a.score_cpu)
			printf("Le gagnant est %s !\n Félicitations.\n\n",a.nom2);
		else
			printf("Match nul !\n Pas mal du tout aux deux.\n\n");
}


// Fait tourner le jeu, une fois le joueur, une fois le CPU
//******************************
void lance_jeu_1joueur(songo* a)
//******************************
{
	int i;
	int nbre_graine;
	int profondeur;
	case_retour choix_cpu;

	afficher(*a);
	while (a->fini==0)
	{
		demande_joueur(a); // demande et joue
		afficher(*a);
		if (a->fini==0)
		{
			// Calcule le nbre d'itérations en fonction du nbre total de graines
			// Hernadez Ebolo
			// Moins il y a de graines et plus il va loin dans la recherche
			nbre_graine=a->case_moi[0]+a->case_moi[1]+a->case_moi[2]+a->case_moi[3]+a->case_moi[4]+a->case_moi[5]+a->case_cpu[0]+a->case_cpu[1]+a->case_cpu[2]+a->case_cpu[3]+a->case_cpu[4]+a->case_cpu[5];
			profondeur=tab_profondeur[a->difficulte][0];
			if (nbre_graine<24) profondeur=tab_profondeur[a->difficulte][1];
   			if (nbre_graine<18) profondeur=tab_profondeur[a->difficulte][2];
			if (nbre_graine<12) profondeur=tab_profondeur[a->difficulte][3];
			if (nbre_graine<6)  profondeur=tab_profondeur[a->difficulte][4];
			if (nbre_graine<4)  profondeur=tab_profondeur[a->difficulte][5];

			choix_cpu=meilleure_case_cpu(*a,profondeur);
			if (choix_cpu.case_meilleure!=-1)
			{
				cpu_joue(a,choix_cpu.case_meilleure);
				afficher(*a);
			}
			else a->fini=1;
		}
	}
	terminer_jeu(a);
	afficher(*a);
	afficher_gagnant_1joueur(*a);
}

// Fait tourner le jeu à 2 joueurs, le joueur joue pour lui et le cpu
//*******************************
void lance_jeu_2joueurs(songo* a)
//*******************************
{
	int i;

	afficher(*a);
	while (a->fini==0)
	{
		demande_joueur(a);
		afficher(*a);
		if (a->fini==0)
		{
			demande_cpu(a);
			afficher(*a);
		}
	}
	terminer_jeu(a);
	afficher_gagnant_2joueurs(*a);
}

//*************************
void changer_noms(songo* a)
//*************************
{
    printf("\n\nLe nom du premier joueur : ");
    scanf("%s",a->nom1);
    printf("Le nom du deuxieme joueur : ");
    scanf("%s",a->nom2);
}

