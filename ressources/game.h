#ifndef GAME_H
#define GAME_H

// Déclaration des fonctions
void MakeAMove (mat & Grid, const maPosition & Pos, char Direction);
bool atLeastThreeInAColumn (const mat & grid, maPosition & pos, unsigned & howMany);
bool atLeastThreeInARow (const mat & grid, maPosition & pos, unsigned & howMany);
void removalInColumn (mat & grid, const maPosition & pos, const unsigned & howMany);
void removalInRow (mat & grid, const maPosition & pos, const unsigned & howMany);
//void gameLoop(mat & grid);


#endif // GAME_H