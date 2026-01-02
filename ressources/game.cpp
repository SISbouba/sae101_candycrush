#include <iostream>
#include <vector>
#include <time.h>
#include <cstdlib>

#include "game.h"
#include "params.h"
#include "gridmanagement.h"
#include "type.h"
#include "score.h"

//Déplacement des éléments de la grille
void MakeAMove (mat & Grid, const maPosition & Pos, char Direction)
{
    size_t Sgrid = Grid.size();
    switch (tolower(Direction)) {
    case 'z':
        if (Pos.ord > 0) {
            maPosition newPos = { Pos.ord - 1, Pos.abs };
            gridSwap(Grid, Pos, newPos);
            displayGridWithChanges(Grid, Pos, newPos);
        }
        break;
    case 'q':
        if (Pos.abs > 0) {
            maPosition newPos = { Pos.ord, Pos.abs - 1 };
            gridSwap(Grid, Pos, newPos);
            displayGridWithChanges(Grid, Pos, newPos);
        }
        break;
    case 's':
        if (Pos.ord + 1 < Sgrid) {
            maPosition newPos = { Pos.ord + 1, Pos.abs };
            gridSwap(Grid, Pos, newPos);
            displayGridWithChanges(Grid, Pos, newPos);
        }
        break;
    case 'd':
        if (Pos.abs + 1 < Sgrid) {
            maPosition newPos = { Pos.ord, Pos.abs + 1 };
            gridSwap(Grid, Pos, newPos);
            displayGridWithChanges(Grid, Pos, newPos);
        }
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

void gameLoop(mat & grid){
    unsigned int score = 0;
    maPosition pos;
    unsigned howMany;

    bool foundMatch = true;

    while (foundMatch) {
        foundMatch = false;

        while (atLeastThreeInAColumn(grid, pos, howMany)) {
            removalInColumn(grid, pos, howMany);
            updateScore(score, howMany);
            foundMatch = true;
        }

        while (atLeastThreeInARow(grid, pos, howMany)) {
            removalInRow(grid, pos, howMany);
            updateScore(score, howMany);
            foundMatch = true;
        }
    }

    // displayScore(score);
}