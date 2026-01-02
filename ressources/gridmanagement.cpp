#include <iostream>
#include "gridmanagement.h"
#include "params.h"
#include "type.h" 

using namespace std;

void couleur (const unsigned & coul) {
    cout << "\033[" << coul <<"m";
}

void clearScreen () {
    cout << "\033[H\033[2J";
}

void couleur_KNbCandies(const unsigned & candy){
    switch (candy) {
    case 1:
        couleur(KRouge+10);
        break;
    case 2:
        couleur(KVert+10);
        break;
    case 3:
        couleur(KBleu+10);
        break;
    case 4:
        couleur(KJaune+10);
        break;
    }
}


void initGrid (mat & grid, const size_t & size)
{
    srand(time(NULL));
    grid.resize(size);
    for (size_t i = 0; i < size; ++i) {
        grid[i].resize(size);
        for (size_t j = 0; j < size; ++j) {
            grid[i][j] = 1 + rand() % (KCandies - 1);
        }
    }
}

// Affichage de la grille
void  displayGrid (const mat & grid)
{
    clearScreen();
    for (const line & i : grid) {
        for (const unsigned & j : i) {
            if(j >= 1 && j <= KCandies){
                couleur_KNbCandies(j);
                cout << j << " ";
            }
            else {
                couleur_KNbCandies(j);
                cout << ' ';
            }
        }
        cout << endl;
    }
    couleur(KReset);
}

// Affichage de la grille en coloriant les positions modifiées
void displayGridWithChanges (const mat & grid, const maPosition & PosStart, const maPosition & PosEnd)
{
    clearScreen();
    for (size_t row = 0; row < grid.size(); ++row) {
        for (size_t col = 0; col < grid[row].size(); ++col) {
            unsigned j = grid[row][col];
            // Colorie en Magenta les positions qui ont changé
            if ((row == PosStart.abs && col == PosStart.ord) || 
                (row == PosEnd.abs && col == PosEnd.ord)) {
                couleur(KMAgenta+10);
            } else {
                couleur_KNbCandies(j);
            }
            
            if(j >= 1 && j <= KCandies){
                cout << j << " ";
            }
            else {
                cout << ' ';
            }
        }
        cout << endl;
    }
    couleur(KReset);
}


//Déplacement des éléments de la grille
void gridSwap (mat & Grid, const maPosition & PosStart, const maPosition & PosEnd)
{
    swap(Grid[PosStart.abs][PosStart.ord], Grid[PosEnd.abs][PosEnd.ord]);
}