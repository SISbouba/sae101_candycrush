/**
 * @file main.cpp
 * @author DURAN Kalvin - SISE Aboubakar
 * @brief Point d'entrée principal du programme de jeu.
 * @details 
 * Ce fichier contient la fonction main qui initialise et lance le jeu en appelant la fonction game().
 */

#include <iostream>
#include <cstdlib>

#include "ressources/game.h"
#include "ressources/gridmanagement.h"
#include "ressources/type.h"

using namespace std;



int main()
{
    //! Lancer le jeu
    game();
    return 0;
}
