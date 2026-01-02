#include <iostream>
#include <vector>
#include <time.h>

#include "game.h"
#include "gridmanagement.h"
#include "score.h"
#include "params.h"

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

void testGame(){
    mat grid;
    size_t taille = 8;
    maPosition pos ;
    unsigned howMany;

    cout << "Bienvenue dans Number Crush" << endl;
    initGrid(grid, taille);

    cout << "Grille initiale :" << endl;
    displayGrid(grid);
    MakeAMove(grid, {3,3}, 'd');
    cout << "Après le déplacement :" << endl;
    displayGridWithChanges(grid, {3,3}, {3,4});

}