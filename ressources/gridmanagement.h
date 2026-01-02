#ifndef GRIDMANAGEMENT_H
#define GRIDMANAGEMENT_H

#include "type.h"
// Déclaration des fonctions de gestion de la grille
void couleur (const unsigned & coul);
void clearScreen ();
void couleur_KNbCandies(const unsigned & candy);
void initGrid (mat & grid, const size_t & size);
void displayGrid (const mat & grid);
void displayGridWithChanges (const mat & grid, const maPosition & PosStart, const maPosition & PosEnd);

#endif // GRIDMANAGEMENT_H