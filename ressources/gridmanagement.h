/**
 * @headerfile gridmanagement.h
 * @author DURAN Kalvin - SISE Aboubakar
 * @brief Déclaration des fonctions de gestion de la grille de jeu.
 * @details 
 * Ce fichier contient les déclarations des fonctions utilisées pour gérer la grille de jeu, y compris l'affichage,
 * l'initialisation, la gravité, et le remplissage de la grille.
 */

#ifndef GRIDMANAGEMENT_H
#define GRIDMANAGEMENT_H

#include "type.h"
// Déclaration des fonctions de gestion de la grille
void couleur (const unsigned & coul);
void clearScreen ();
void couleur_KNbCandies(const unsigned & candy);
void initGrid (mat & grid, const size_t & size);
void displayGrid (const mat & grid, unsigned score, unsigned combo, int timeValue, Gamemode mode);
unsigned compterBonbonRestants(const mat& grid);
bool isGridEmpty(const mat& grid);
void gravité(mat& grid);
void remplirGrid(mat& grid, Gamemode mode);

#endif // GRIDMANAGEMENT_H