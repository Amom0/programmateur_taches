#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include "gestionnaire_tache.h"

char commande[100];
char path[50];
char** argv = NULL;
float delai;
int iteration;
int choix;
pid_t exec_le_programme;
pid_t exec_la_commande;
time_t time_now;
time_t time_end;   

void choix_utilisateur(){
    printf("\n1 - Entrez une nouvelle commande\n2 - Quitter\n");
    scanf("%d", &choix);
    getchar(); 

    if(choix == 1){  // Entrer une nouvelle commande :
        entrees_utilisateur();
    }else{  // Quitter
        printf("Bye");
    }
}

void entrees_utilisateur(){
    // Path de la commande
    printf("Entrez le path de la commande : ");
    scanf("%s", &path); 
    getchar(); 

    // Commande
    printf("Entrez une commande : ");
    fgets(commande, 100, stdin);
    commande[strlen(commande)-1]='\0';

    // Délai
    printf("Entrez un délai entre chaque execution (en min) : ");
    scanf("%f", &delai);  

    // Nombre d'itérations
    printf("Entrez un nombre d'itérations : ");
    scanf("%d", &iteration); 
    printf("\n");

    stockage_commande();
}

void stockage_commande(){
    int nbr_parametre = 0;
    int indice = 0;
    char cmd2[100];
    char cmd3[100];
    strcpy(cmd2, commande);
    strcpy(cmd3, commande);
    // Compte le nombre de parametre(s)
    char *str = strtok(cmd2, " ");
    while(str != NULL)
	{
		nbr_parametre += 1;
		str = strtok(NULL, " ");
	}
    // Alloue la mémoire pour le tableau
    argv = (char**) malloc((nbr_parametre+1)*sizeof(char*));
    // Incrémente le tableau des parametres
    char *ptr = strtok(cmd3, " ");
	while(ptr != NULL)
	{   
		argv[indice] = ptr;
		ptr = strtok(NULL, " ");
        indice += 1;
	}
    argv[nbr_parametre] = NULL;

    execution();
}

void execution(){
    exec_le_programme = fork();
    switch (exec_le_programme){
        case -1:
            perror("Erreur lors du lancement du programme\n");
            exit(errno);
        case 0:
            // Boucle itérations
            for(int i=0;i<iteration; i++){
                // Calcul du délai
                time(&time_now);
                time_end = time_now + (double)delai*60;
                while(time(NULL) < time_end){}
                // Execution de la commande
                exec_la_commande = fork();
                switch (exec_la_commande){
                    case -1:
                        perror("Erreur lors de l'execution de la commande\n");
                        exit(errno);
                    case 0:
                        execv(path, &(argv[0]));
                    default:
                        wait(NULL);
                        break;
                }
            }
        exit(-1);
    }
    choix_utilisateur();
}

int main(){    
    entrees_utilisateur();
    free(argv);
    return 0;
}