/*
    *@file : type.h
    *@author : DURAN Kelvin - SISE Aboubakar
    *@brief : Définition des types utilisés dans le jeu.
*/

#ifndef TYPE_H
#define TYPE_H

#include <vector>
#include <string>

using namespace std;

typedef vector <unsigned> line; // un type représentant une ligne de la grille
typedef vector <line> mat; // un type représentant la grille
typedef struct {
    unsigned abs;
    unsigned ord;
} maPosition;// une position dans la girlle

typedef enum {
    MODE_SCORE,
    MODE_CLEAR,
    MODE_1v1
} Gamemode;

// Déclaration des constantes
//Couleurs pour l'affichage 
const unsigned KImpossible (0); // valeur représentant une case vide*
const unsigned KReset   (0);
const unsigned KCandies (5);
const unsigned KRouge   (31);
const unsigned KVert    (32);
const unsigned KJaune   (33);
const unsigned KBleu    (34);
const unsigned KMAgenta (35);
const unsigned KCyan (36);

// Constantes pour le score
const unsigned KScorePerCandy= 10;
const unsigned KComboMultiplier = 2;
const unsigned KTargetScore = 1000;

#endif // TYPE_H