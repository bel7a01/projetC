#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Candidat {
    char nom[50];
    int id;
    int votes; 
};


struct Electeur {
    char nom[50];
    int id;
    int aVote; // 1 si l'électeur a voté, 0 sinon
};


struct Election {
    char titre[50];
    int id;
    struct Candidat candidats[10];  
    struct Electeur electeurs[100]; 
    int nombreCandidats;
    int nombreElecteurs;
};


struct Admin {
    char nom_utilisateur[50];
    char mot_de_passe[50];
};

// Variables globales 
struct Election elections[10]; 
struct Candidat candidats[50]; 
struct Electeur electeurs[100]; 
struct Admin administrateurs[10]; 

int nombreElections = 0;
int nombreCandidats = 0;
int nombreElecteurs = 0;
int nombreAdmins = 0;
int choixElection; // pour stocker le choix de l'élection

//a jouter un candidat à une élection
void ajouterCandidat(struct Election *election, const char *nomCandidat) {
    if (election->nombreCandidats < 10) {
        struct Candidat nouveauCandidat;
        strcpy(nouveauCandidat.nom, nomCandidat);
        nouveauCandidat.id = election->nombreCandidats + 1; // Identifiant unique
        nouveauCandidat.votes = 0; 

        election->candidats[election->nombreCandidats] = nouveauCandidat;
        election->nombreCandidats++;

        printf("Candidat ajout%c avec succ%cs!\n",130,130);
    } else {
        printf("Le nombre maximal de candidats a %ct%c atteint pour cette %clecction.\n", 130,130,130);
    }
}

// Créer une nouvelle élection avec la possibilité d'ajouter des candidats
void creerNouvelleElection() {
    if (nombreElections < 10) {
        struct Election nouvelleElection;
        printf("Entrez le titre de la nouvelle %clection : ",130);
        scanf("%s", nouvelleElection.titre);

        nouvelleElection.id = nombreElections + 1; // Identifiant unique
        nouvelleElection.nombreCandidats = 0; 
        nouvelleElection.nombreElecteurs = 0; 

        printf("Combien de candidats voulez-vous ajouter ? (max 10) : ");
        int nombreCandidatsAajouter;
        scanf("%d", &nombreCandidatsAajouter);
		int i;
        
		for (i = 0; i < nombreCandidatsAajouter; ++i) {
            printf("Entrez le nom du candidat %d : ", i + 1);
            char nomCandidat[50];
            scanf("%s", nomCandidat);
            ajouterCandidat(&nouvelleElection, nomCandidat);
        }

        elections[nombreElections] = nouvelleElection;
        nombreElections++;

        printf("Election cr%c%ce avec succ%cs!\n",130,130,130);
    } else {
        printf("Le nombre maximal d'%clections a %ct%c atteint.\n",130,130,130);
    }
}

// permettre à un électeur de voter
void voterPourCandidatDansElection(struct Election *election, struct Electeur *electeur) {
    if (!electeur->aVote) {
        printf("Liste des candidats pour l'%clection %s :\n",130, election->titre);
        int i;
		for (i = 0; i < election->nombreCandidats; ++i) {
            printf("%d. %s\n", election->candidats[i].id, election->candidats[i].nom);
        }

        int choixCandidat;
        printf("Choisissez le num%cro du candidat pour lequel vous voulez voter : ",130);
        scanf("%d", &choixCandidat);

        if (choixCandidat >= 1 && choixCandidat <= election->nombreCandidats) {
            struct Candidat *candidatChoisi = &election->candidats[choixCandidat - 1];
            candidatChoisi->votes++;
            electeur->aVote = 1;

            printf("Vote enregistr%c avec succ%cs!\n",130,130);
        } else {
            printf("Choix invalide.\n");
        }
    } else {
        printf("Vous avez deja vot%c dans cette %clection.\n",130,130);
    }
}

//afficher les élections
void afficherElections() {
    printf("\nListe des %clections :\n",130);
    
    int i;
	for (i = 0; i < nombreElections; ++i) {
        printf("%d) %s\n", elections[i].id, elections[i].titre);
    }
}

// Fonction pour afficher les résultats d'une élection
void afficherResultatElection(struct Election *election) {
    printf("\nR%csultats de l'%clection '%s' :\n",130,130, election->titre);
    int i;
	for (i = 0; i < election->nombreCandidats; ++i) {
        printf("%s : %d votes\n", election->candidats[i].nom, election->candidats[i].votes);
    }
}

// afficher la liste des votes
void afficherListeVotes() {
    printf("\nListe des votes :\n");
    int i;
	
	for (i = 0; i < nombreElecteurs; ++i) {
        if (electeurs[i].aVote) {
            printf("%s a vot%c\n",130, electeurs[i].nom);
        }
    }
}

// créer un compte administrateur
void creerCompteAdmin() {
    if (nombreAdmins < 10) {
        struct Admin nouveauAdmin;
        printf("Entrez le nom d'utilisateur : ");
        scanf("%s", nouveauAdmin.nom_utilisateur);
        printf("Entrez le mot de passe : ");
        scanf("%s", nouveauAdmin.mot_de_passe);

        administrateurs[nombreAdmins] = nouveauAdmin;
        nombreAdmins++;

        printf("Compte administrateur cr%ce avec succ%cs!\n",130,130);
    } else {
        printf("Le nombre maximal d'administrateurs a %ct%c atteint.\n",130,130);
    }
}

//créer un compte candidat
void creerCompteCandidat() {
    if (nombreCandidats < 50) {
        struct Candidat nouveauCandidat;
        printf("Entrez le nom du candidat : ");
        scanf("%s", nouveauCandidat.nom);
        nouveauCandidat.id = nombreCandidats + 1; // Identifiant unique
        nouveauCandidat.votes = 0;

        candidats[nombreCandidats] = nouveauCandidat;
        nombreCandidats++;

        printf("Compte candidat cr%ce avec succ%cs!\n",130,130);
    } else {
        printf("Le nombre maximal de candidats a %ct%c atteint.\n",130,130);
    }
}

// créer un compte électeur
void creerCompteElecteur() {
    if (nombreElecteurs < 100) {
        struct Electeur nouveauElecteur;
        printf("Entrez le nom de l'%clecteur : ",130);
        scanf("%s", nouveauElecteur.nom);
        nouveauElecteur.id = nombreElecteurs + 1; // identifiant unique
        nouveauElecteur.aVote = 0; 

        electeurs[nombreElecteurs] = nouveauElecteur;
        nombreElecteurs++;

        printf("Compte %clecteur cr%ce avec succ%cs!\n",130,130,130);
    } else {
        printf("Le nombre maximal d'%clecteurs a %ct%c atteint.\n",130,130,130);
    }
}
// Fonction pour mettre à jour les informations d'un candidat
void mettreAJourCandidat() {
    printf("\nMettre %c jour les informations d'un candidat\n",133);
    printf("Liste des candidats :\n");
	int i;
    
	for (i = 0; i < nombreCandidats; ++i) {
        printf("%d. %s\n", candidats[i].id, candidats[i].nom);
    }

    int choixCandidat;
    printf("Choisissez le num%cro du candidat que vous voulez mettre %c jour : ",130,133);
    scanf("%d", &choixCandidat);

    if (choixCandidat >= 1 && choixCandidat <= nombreCandidats) {
        struct Candidat *candidatAUpdate = &candidats[choixCandidat - 1];

        printf("Entrez le nouveau nom du candidat : ");
        scanf("%s", candidatAUpdate->nom);

        printf("Informations du candidat mises %c jour avec succ%cs!\n",133,130);
    } else {
        printf("Choix invalide.\n");
    }
}


// Fonction du menu administrateur
void menuAdmin() {
    printf("\nMenu Administrateur\n");
    printf("1. Cr%cer un nouveau compte administrateur\n");
    printf("2. Cr%cer une nouvelle %clection\n",130);
    printf("3. Mettre %c jour les informations des candidats\n",133);
    printf("4. Afficher et g%crer les %clections\n",138,130);
    printf("5. Afficher le r%csultat\n",130);
    printf("6. Afficher la liste des votes\n");
    printf("7. Quitter\n");

    int choixAdmin;
    printf("Choisissez une option : ");
    scanf("%d", &choixAdmin);

    switch (choixAdmin) {
        case 1:
            creerCompteAdmin();
            break;
        case 2:
            creerNouvelleElection();
            break;
        case 3:
             mettreAJourCandidat();
            break;
        case 4:
            afficherElections();
            break;
        case 5:
            // choisir une élection
            printf("Choisissez le num%cro de l'%clection pour laquelle vous voulez afficher le r%csultat : ",130,130,130);
            scanf("%d", &choixElection);
            if (choixElection >= 1 && choixElection <= nombreElections) {
                afficherResultatElection(&elections[choixElection - 1]);
            } else {
                printf("Choix invalide.\n");
            }
            break;
        case 6:
            afficherListeVotes();
            break;
        case 7:
            printf("Au revoir!\n");
            exit(0);
        default:
            printf("Option invalide.\n");
    }
}

// Fonction du menu candidat
void menuCandidat() {
    printf("\nMenu Candidat\n");
    printf("1. Cr%cer un compte candidat\n");
    printf("2. Quitter\n");

    int choixCandidat;
    printf("Choisissez une option : ");
    scanf("%d", &choixCandidat);

    switch (choixCandidat) {
        case 1:
            creerCompteCandidat();
            break;
        case 2:
            printf("Au revoir!\n");
            exit(0);
        default:
            printf("Option invalide.\n");
    }
}

// Fonction du menu électeur
void menuElecteur() {
    printf("\nMenu Electeur\n");
    printf("1. Cr%cer un compte %clecteur\n",130,130);
    printf("2. Voter pour un candidat dans une %clection\n",130);
    printf("3. Quitter\n");

    int choixElecteur;
    printf("Choisissez une option : ");
    scanf("%d", &choixElecteur);

    switch (choixElecteur) {
        case 1:
        	//creer un compte electeur
            creerCompteElecteur();
            break;
        case 2:
            // choisir une élection
            printf("Choisissez le num%cro de l'%clection pour laquelle vous voulez voter : ",130,130);
            scanf("%d", &choixElection);
            if (choixElection >= 1 && choixElection <= nombreElections) {
                voterPourCandidatDansElection(&elections[choixElection - 1], &electeurs[choixElecteur - 1]);
            } else {
                printf("Choix invalide.\n");
            }
            break;
        case 3:
            printf("Au revoir!\n");
            exit(0);
        default:
            printf("Option invalide.\n");
    }
}


int main() {
    while (1) {
        int choixTypeUtilisateur;
        printf("\nChoisissez le type d'utilisateur : \n");
        printf("1. Administrateur\n");
        printf("2. Candidat\n");
        printf("3. Electeur\n");
        printf("4. Quitter\n");

        printf("Votre choix : ");
        scanf("%d", &choixTypeUtilisateur);

        switch (choixTypeUtilisateur) {
            case 1:
                menuAdmin();
                break;
            case 2:
                menuCandidat();
                break;
            case 3:
                menuElecteur();
                break;
            case 4:
                printf("Au revoir!\n");
                exit(0);
            default:
                printf("Option invalide.\n");
        }
    }

    return 0;
}
