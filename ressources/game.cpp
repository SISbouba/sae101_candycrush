/*
    *@file : game.cpp
    *@author : DURAN Kelvin - SISE Aboubakar
    *@brief : Fonctions de gestion du jeu.
*/

#include <iostream>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <chrono>

#include "game.h"
#include "gridmanagement.h"
#include "score.h"

using namespace std;
using namespace std::chrono;

void MakeAMove (mat & Grid, const maPosition & Pos, char Direction)
{
    size_t Sgrid = Grid.size();
    switch (tolower(Direction)) {
    case 'z':
        if (Pos.ord > 0)
            gridSwap(Grid, Pos, { Pos.ord - 1, Pos.abs });
        break;
    case 'q':
        if (Pos.abs > 0)
        gridSwap(Grid, Pos, { Pos.ord, Pos.abs - 1 });
        break;
    case 's':
        if (Pos.ord + 1 < Sgrid)
        gridSwap(Grid, Pos, { Pos.ord + 1, Pos.abs });
        break;
    case 'd':
        if (Pos.abs + 1 < Sgrid)
            gridSwap(Grid, Pos, { Pos.ord, Pos.abs + 1 });
        break;
    default :
        cout << "Erreur : rentre une touche valide";
    }
}


// Vérifie s'il y a au moins trois bonbons alignés verticalement
bool atLeastThreeInAColumn (const mat & grid, maPosition & pos, unsigned & howMany){
    size_t taille = grid.size();

    for (size_t col = 0; col < taille; ++col) {
        for (size_t row = 0; row < taille - 2; ++row) {

            if (grid[row][col] == grid[row+1][col] && grid[row][col] == grid[row+2][col]) {
                pos.ord = row;
                pos.abs = col;
                howMany = 3;
                return true;
            }
        }
    }
    return false;
}

// Vérifie s'il y a au moins trois bonbons alignés horizontalement
bool atLeastThreeInARow (const mat & grid, maPosition & pos, unsigned & howMany){
    size_t taille = grid.size();

    for (size_t row = 0; row < taille; ++row) {
        for (size_t col = 0; col < taille - 2; ++col) {

            if (grid[row][col] == grid[row][col+1] && grid[row][col] == grid[row][col+2]) {
                pos.ord = row;
                pos.abs = col;
                howMany = 3;
                return true;
            }
        }
    }
    return false;
}

// Supprime les bonbons atLeastThreeInAColumn
void removalInColumn (mat & grid, const maPosition & pos, unsigned  howMany){
    size_t col = pos.abs;
    size_t row = pos.ord;
    size_t taille = grid.size();

    for (size_t i = row; i + howMany < taille; ++i) {
        grid[i][col] = grid[i + howMany][col];
    }

    for (size_t i = taille - howMany; i < taille; ++i) {
        grid[i][col] = KImpossible;
    }
}

// Supprime les bonbons atLeastThreeInARow
void removalInRow (mat & grid, const maPosition & pos, unsigned  howMany){
    size_t col = pos.abs;
    size_t row = pos.ord;
    size_t taille = grid.size();

    for (size_t i = col; i + howMany < taille; ++i) {
        grid[row][i] = grid[row][i + howMany];
    }

    for (size_t i = taille - howMany; i < taille; ++i) {
        grid[row][i] = KImpossible;
    }
}

void afficherMode(Gamemode mode){
    mat grid;
    size_t taille = 8;
    unsigned score = 0;
    unsigned combo = 1;
    
    initGrid(grid, taille);
    auto startTime = steady_clock::now();
    switch (mode)
    {
    case MODE_SCORE:
        cout << "Mode de jeu: SCORE " << endl;
        cout << "Objectif: " << KTargetScore << " points en 120s" << endl;
        break;
    case MODE_CLEAR:
        cout << "Mode de jeu: CLEAR " << endl;
        cout << "Objectif: Vider la grille le plus vite possible." << endl;
        break;
    case MODE_1v1:
        cout << "Mode de jeu: 1v1 " << endl;
        cout << "Objectif: Obtenir le plus de points possible avant la fin du temps imparti." << endl;
        break;
    default:
        break;
    }
}



void testGame(){
    mat grid;
    size_t taille = 8;
    maPosition pos ;
    unsigned howMany;

    cout << "Bienvenue dans Number Crush" << endl;
    initGrid(grid, taille);

    cout << "Grille initiale :" << endl;
    displayGrid(grid, 0, 0, 120, MODE_1v1);
    MakeAMove(grid, {3,3}, 'd');
    cout << "Après le déplacement :" << endl;
    //displayGridWithChanges(grid, {3,3}, {3,4});
    displayGrid(grid, 0, 0, 120, MODE_1v1);
}


void game(){
    size_t taille;
    int choix;

    cout << "Bienvenue dans Number Crush" << endl;

    cout << "Veuillez choisir votre mode de jeu :" << endl;
    cout << "1. Mode Score" << endl;
    cout << "2. Mode Clear" << endl;
    cout << "3. Mode 1v1" << endl;
    cout << "4. Quitter" << endl;

    cout << "Votre choix : ";
    cin >> choix;
    
    switch (choix)
    {
    case 1:
        //afficherMode(MODE_SCORE);
        return;
    case 2:
        //afficherMode(MODE_CLEAR);
        return;
    case 3:
        //afficherMode(MODE_1v1);
        return;
    case 4:
        couleur(KCyan);
        cout << "Merci d'avoir joué ! Au revoir !" << endl;
        couleur(KReset);
        exit(0);
    default:
        couleur(KRouge);
        cout << "Mode de jeu invalide, veuillez recommencer en appuyant sur Entrée." << endl;
        couleur(KReset);
        cin.get();
        return;
    }
}