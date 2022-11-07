#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include <stdlib.h>

#include <ctype.h>

#include <string.h>



#include "dico.h"



int gagne(int lettreTrouvee[], long tailleMot);

int rechercheLettre(char lettre, char motSecret[], int lettreTrouvee[]);

char lireCaractere();



int main(int argc, char* argv[])

{

	char lettre = 0; // Stocke la lettre propos�e par l'utilisateur (retour du scanf)

	char motSecret[100] = { 0 }; // Ce sera le mot � trouver

	int *lettreTrouvee = NULL; // Un tableau de Chaque case correspond � une lettre du mot secret.

	long coupsRestants = 10; // Compteur de coups restants (0 = mort)

	long i = 0; // Une petite variable pour parcourir les tableaux

	long tailleMot = 0;



	printf("Bienvenue dans le Pendu !\n\n");



	if (!piocherMot(motSecret))

		exit(0);



	tailleMot = strlen(motSecret);



	lettreTrouvee = malloc(tailleMot * sizeof(int)); // On alloue dynamiquement le tableau lettreTrouvee

	if (lettreTrouvee == NULL)

		exit(0);



	for (i = 0; i < tailleMot; i++)

		lettreTrouvee[i] = 0;



	/* On continue a jouer tant qu'il reste au moins un coup a jouer  */

	while (coupsRestants > 0 && !gagne(lettreTrouvee, tailleMot))

	{

		printf("\n\nIl vous reste %ld coups a jouer", coupsRestants);

		printf("\nQuel est le mot secret ? ");



		/* On affiche le mot secret en masquant les lettres non trouvees */

		for (i = 0; i < tailleMot; i++)

		{

			if (lettreTrouvee[i]) // Si on a trouve la lettre n� i

				printf("%c", motSecret[i]); // On l'affiche

			else

				printf("*"); // Sinon, on affiche une �toile 

		}



		printf("\nProposez une lettre : ");

		lettre = lireCaractere();



		// Si ce n'etait PAS la bonne lettre

		if (!rechercheLettre(lettre, motSecret, lettreTrouvee))

		{

			coupsRestants--; // On enleve un coup

		}

	}



	if (gagne(lettreTrouvee, tailleMot))

		printf("\n\nGagne ! Le mot secret etait bien : %s", motSecret);

	else

		printf("\n\nPerdu ! Le mot secret etait : %s", motSecret);



	free(lettreTrouvee); // On libere la memoire 



	return 0;

}



char lireCaractere()

{

	char caractere = 0;



	caractere = getchar(); // On lit le premier caractere

	caractere = toupper(caractere); // On met la lettre en majuscule 



	// On lit les autres caracteres

	while (getchar() != '\n');



	return caractere; // On retourne le premier caractere 

}



int gagne(int lettreTrouvee[], long tailleMot)

{

	long i = 0;

	int joueurGagne = 1;



	for (i = 0; i < tailleMot; i++)

	{

		if (lettreTrouvee[i] == 0)

			joueurGagne = 0;

	}



	return joueurGagne;

}



int rechercheLettre(char lettre, char motSecret[], int lettreTrouvee[])

{

	long i = 0;

	int bonneLettre = 0;



	// On parcourt motSecret pour verifier 

	for (i = 0; motSecret[i] != '\0'; i++)

	{

		if (lettre == motSecret[i]) 

		{

			bonneLettre = 1; // On memorise que c'etait une bonne lettre

			lettreTrouvee[i] = 1; // On met a 1 la case du tableau correspondant ala lettre 

		}

	}



	return bonneLettre;

}