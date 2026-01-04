/**
 * @headerfile type.h
 * @author DURAN Kalvin - SISE Aboubakar
 * @brief Définition des types utilisés dans le jeu.
 * @details
 * Ce fichier contient les définitions des types de données et des constantes utilisées dans le jeu,
 * y compris les types pour la grille de jeu, les positions, les modes de jeu, et les constantes de configuration.
 */


#ifndef TYPE_H
#define TYPE_H

#include <vector>
#include <string>

using namespace std;

/**
 * @brief Définition des types utilisés dans le jeu.
 * @var mat
 * @var line
 * @var maPosition
 */
typedef vector <unsigned> line; //! Type représentant une ligne de la grille
typedef vector <line> mat; //! Type représentant la grille
typedef struct {
    unsigned abs;
    unsigned ord;
} maPosition;//! Une position dans la grille

/**
 * @brief Enumération des modes de jeu disponibles.
 * @enum Gamemode
 */
typedef enum {
    MODE_SCORE, /**< Le but est d'atteindre le nombre de points définie dans un temps limité. */
    MODE_CLEAR, /**< Le but est de vider la grille le plus vite possible */
    MODE_1v1 /**< Le joueur qui la plus de points dans un temps donnée à gagner */
} Gamemode;

/**
 * @brief Constantes pour la grille de jeu
 * 
 */

 //! Valeur représentant une case vide
const unsigned KImpossible (0);
//! Réinitialisation de la couleur
const unsigned KReset   (0);
//! Nombre total de types de bonbons
const unsigned KCandies (5);
//! Couleur rouge
const unsigned KRouge   (31);
//! Couleur verte
const unsigned KVert    (32);
//! Couleur jaune
const unsigned KJaune   (33);
//! Couleur blue
const unsigned KBleu    (34);
//! Couleur magenta
const unsigned KMAgenta (35);
//! Couleur cyan
const unsigned KCyan (36);

/**
 * @brief Constantes pour le score
 * 
 */
//! Points par bonbon supprimé
const unsigned KScorePerCandy= 10;
//! Multiplicateur de combo 
const unsigned KComboMultiplier = 2;
//! Score cible pour gagner en mode SCORE
const unsigned KTargetScore = 1000;

#endif // TYPE_H