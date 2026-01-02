#include <iostream>
#include "ressources/game.h"
#include "ressources/gridmanagement.h"

using namespace std;

int main()
{
    mat grid;
    size_t taille = 8;
    initGrid(grid, taille);

    gameLoop(grid);
    displayGrid(grid);
    cout << "----------------" << endl;
    MakeAMove(grid, {3,4}, 'z');
    displayGridWithChanges(grid, {4,4}, {3,4});
    // cout << "----------------" << endl;
    // MakeAMove(grid, {1,1}, 's');
    // displayGridWithChanges(grid, {0,0}, {1,0});
    // cout << "----------------" << endl;
    // MakeAMove(grid, {4,4}, 'q');
    // displayGrid(grid);
    // cout << "----------------" << endl;
    // MakeAMove(grid, {4,4}, 'd');
    // displayGrid(grid);


    // maPosition pos = {1,2};
    // unsigned howMany = 3;

    // while (true)
    // {
    //     MakeAMove(grid, pos, 'd');
    //     displayGrid(grid);
    //     cout << "----------------" << endl;
    //     if(atLeastThreeInAColumn(grid, pos, howMany)){
    //         removalInColumn(grid,pos,howMany);
    //         displayGrid(grid);
    //     }
    //     cout << "----------------" << endl;
    //     if(atLeastThreeInARow(grid, pos, howMany)){
    //         removalInRow(grid, pos, howMany);
    //         displayGrid(grid);
    //     }
    // }
    
    return 0;
}
