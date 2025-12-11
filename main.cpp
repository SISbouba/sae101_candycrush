#include <iostream>
#include <vector>
#include <time.h>
#include <cstdlib>

using namespace std;

typedef vector <unsigned> line; // un type représentant une ligne de la grille
typedef vector <line> mat; // un type représentant la grille
typedef struct {
    unsigned abs;
    unsigned ord;
} maPosition; // une position dans la girlle

// Déclaration des constantes
const unsigned KCandies (5);
const unsigned KImpossible (0);
const unsigned KReset   (0);
const unsigned KNoir    (30);
const unsigned KRouge   (31);
const unsigned KVert    (32);
const unsigned KJaune   (33);
const unsigned KBleu    (34);
const unsigned KMAgenta (35);
const unsigned KCyan    (36);

// Déclaration des signatures
void clearScreen();
void couleur(const unsigned & coul);
void couleur_KNbCandies(const unsigned & candy);



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


//Déplacement des éléments de la grille
void gridSwap (mat & Grid, const maPosition & PosStart, const maPosition & PosEnd)
{
    swap(Grid[PosStart.abs][PosStart.ord], Grid[PosEnd.abs][PosEnd.ord]);
}

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

int main()
{
    mat grid;
    size_t taille = 8;
    initGrid(grid, taille);
    displayGrid(grid);

    maPosition pos ;
    unsigned howMany;

    // if(atLeastThreeInAColumn(grid, pos, howMany)){
    //     removalInColumn(grid,pos,howMany);
    //     displayGrid(grid);
    // }

    // if(atLeastThreeInARow(grid, pos, howMany)){
    //     removalInRow(grid, pos, howMany);
    //     displayGrid(grid);
    // }

    return 0;
}
