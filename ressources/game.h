/**
 * @headerfile game.h
 * @author DURAN Kalvin - SISE Aboubakar
 * @brief Déclaration des fonctions de gestion du jeu.
 * @details 
 * Ce fichier contient les déclarations des fonctions utilisées pour gérer la logique du jeu, y compris les mouvements des  
 * bonbons, la détection des alignements, et l'affichage des modes de jeu.
 */

#ifndef GAME_H
#define GAME_H


#include "type.h"
#include <cctype>
#include <iostream>

using namespace std;

//! Déclaration des fonctions de gestion du jeu
void MakeAMove (mat & Grid, const maPosition & Pos, char Direction);
bool isValidMove(const mat& grid, const maPosition& Pos, char Direction);
maPosition getTargetPosition(const maPosition& Pos, char Direction);
bool atLeastThreeInAColumn (const mat & grid, maPosition & pos, unsigned & howMany);
bool atLeastThreeInARow (const mat & grid, maPosition & pos, unsigned & howMany);
void gridSwap (mat & grid, const maPosition & pos1, const maPosition & pos2);
void removalInRow (mat & grid, const maPosition & pos, unsigned  howMany);
void removalInColumn (mat & grid, const maPosition & pos, unsigned  howMany);
bool traitementDeAlignement(mat& grid, unsigned& score, unsigned& combo, Gamemode mode);
void afficherMode(Gamemode mode);
void game ();

#endif // GAME_H