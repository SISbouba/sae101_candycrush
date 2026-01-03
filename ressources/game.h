#ifndef GAME_H
#define GAME_H


#include "type.h"
#include <cctype>
#include <iostream>

using namespace std;

// Déclaration des fonctions de gestion du jeu
void MakeAMove (mat & Grid, const maPosition & Pos, char Direction);
bool atLeastThreeInAColumn (const mat & grid, maPosition & pos, unsigned & howMany);
bool atLeastThreeInARow (const mat & grid, maPosition & pos, unsigned & howMany);
void gridSwap (mat & grid, const maPosition & pos1, const maPosition & pos2);
void removalInRow (mat & grid, const maPosition & pos, unsigned  howMany);
void removalInColumn (mat & grid, const maPosition & pos, unsigned  howMany);
void afficherMode(Gamemode mode);
void testGame ();
void game ();

#endif // GAME_H