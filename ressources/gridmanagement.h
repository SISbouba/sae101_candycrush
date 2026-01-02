#ifndef GRIDMANAGEMENT_H
#define GRIDMANAGEMENT_H

#include "type.h"

// Déclaration des fonctions
void couleur (const unsigned & coul);
void clearScreen ();
void couleur_KNbCandies(const unsigned & candy);    
void initGrid (mat & grid, const size_t & size);
void displayGrid (const mat & grid);
void displayGridWithChanges (const mat & grid, const maPosition & pos1, const maPosition & pos2);
void gridSwap (mat & Grid, const maPosition & PosStart, const maPosition & PosEnd);


#endif // GRIDMANAGEMENT_H