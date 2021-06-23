#ifndef GESTIONNAIRE_TACHE_H_INCLUDED
#define GESTIONNAIRE_TACHE_H_INCLUDED

/**
 * \brief cette fonction demande à l'utilisateur si il veut rentrer une nouvelle commande ou pas.
 */
void choix_utilisateur();

/**
 * \brief cette fonction demande à l'utilisateur de rentrer le path, la commande, le délai, 
 * ainsi que le nombre d'itérations.
 */
void entrees_utilisateur();

/**
 * \brief cette fonction stock les différents paramètres dans un tableau.
 */
void stockage_commande();

/**
 * \brief cette fonction execute la commande au moment voulu.
 */
void execution();

#endif // GESTIONNAIRE_TACHE_H_INCLUDED