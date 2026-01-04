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
#include <thread>

#include "game.h"
#include "gridmanagement.h"

using namespace std;
using namespace std::chrono;


// Effectue un déplacement dans la grille
void MakeAMove (mat & grid, const maPosition & Pos, char Direction)
{
    size_t Sgrid = grid.size();
    // Touche du jouer 1
    switch (tolower(Direction)) {
    case 'z':
        if (Pos.ord > 0)
            gridSwap(grid, Pos, { Pos.ord - 1, Pos.abs });
        break;
    case 'q':
        if (Pos.abs > 0)
        gridSwap(grid, Pos, { Pos.ord, Pos.abs - 1 });
        break;
    case 's':
        if (Pos.ord + 1 < Sgrid)
        gridSwap(grid, Pos, { Pos.ord + 1, Pos.abs });
        break;
    case 'd':
        if (Pos.abs + 1 < Sgrid)
            gridSwap(grid, Pos, { Pos.ord, Pos.abs + 1 });
        break;
    default :
        cout << "Erreur : rentre une touche valide";
    }
}

// Vérifie si le mouvement est valide pour éviter les débordements
bool isValidMove(const mat& grid, const maPosition& Pos, char Direction) {
    size_t Sgrid = grid.size();
    switch (tolower(Direction)) {
        case 'z': 
            return Pos.ord > 0; // Vérifie que la position au-dessus est valide
        case 'q': 
            return Pos.abs > 0; // Vérifie que la position à gauche est valide
        case 's': 
            return Pos.ord + 1 < Sgrid; // Vérifie que la position en dessous est valide
        case 'd': 
            return Pos.abs + 1 < Sgrid; // Vérifie que la position à droite est valide
        default: 
            return false; // Touche invalide
    }
}

// Obtient la position cible en fonction de la direction
maPosition getTargetPosition(const maPosition& Pos, char Direction) {
    maPosition target = Pos;
    switch (tolower(Direction)) {
        case 'z': 
            target.ord--; // Déplace vers le haut
            break;
        case 'q': 
            target.abs--; // Déplace vers la gauche
            break;
        case 's': 
            target.ord++; // Déplace vers le bas
            break;
        case 'd': 
            target.abs++; // Déplace vers la droite
            break;
    }
    return target;
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

// Traite les alignements et met à jour le score et le combo
bool traitementDeAlignement(mat& grid, unsigned& score, unsigned& combo, Gamemode mode) {
    maPosition pos;
    unsigned howMany;
    bool foundMatch = false;

    // Continue tant qu'il y a des alignements
    while (atLeastThreeInAColumn(grid, pos, howMany) || atLeastThreeInARow(grid, pos, howMany)) {
        foundMatch = true;
        
        // Supprime les bonbons alignés
        if (atLeastThreeInAColumn(grid, pos, howMany)) {
            removalInColumn(grid, pos, howMany);
        } else if (atLeastThreeInARow(grid, pos, howMany)) {
            removalInRow(grid, pos, howMany);
        }
        
        // Met à jour le score et le combo
        score += howMany * KScorePerCandy * combo;
        combo++;
        
        // Appliquer la gravité en mode CLEAR
        if (mode == MODE_CLEAR) {
            gravité(grid);
        }
        
        // Remplit la grille
        remplirGrid(grid, mode);
    }
    
    return foundMatch;
}

// Fonction d'affichage du mode de jeu
void afficherMode(Gamemode mode){
    mat grid;
    size_t taille = 8;
    unsigned score = 0;
    unsigned combo = 1;
    
    initGrid(grid, taille);
    auto startTime = steady_clock::now(); // Démarre le chronomètre
    int tempsLimite = 120; // Durée du temps en secondes

    switch (mode) {
        case MODE_SCORE:
            while(true){
                auto tempsActuel = steady_clock::now();
                int tempsPasser = duration_cast<seconds>(tempsActuel - startTime).count();
                int tempsRestant = tempsLimite - tempsPasser;

                // Affiche le message de fin si le temps est écoulé
                if (tempsRestant <= 0) {
                    couleur(KCyan);
                    cout << "Temps écoulé !" << endl;
                    this_thread::sleep_for(milliseconds(1000));
                    cout<< "Votre score final est : " << score << endl;
                    if (score >= KTargetScore) {
                        couleur(KVert);
                        cout << "VICTOIRE! Objectif atteint!" << endl;
                    } else {
                        couleur(KRouge);
                        cout << "Dommage... Objectif non atteint." << endl;
                    }
                    couleur(KReset);
                    break;
                }

                // Affiche le message de victoire si l'objectif est atteint
                if (score >= KTargetScore) {
                    clearScreen();
                    couleur(KVert);
                    cout << "VICTOIRE! Objectif atteint!" << endl;
                    couleur(KReset);
                    cout << "Score final: " << score << endl;
                    cout << "Temps restant: " << tempsRestant << "s" << endl;
                    break;
                }

                displayGrid(grid, score, combo, tempsRestant, mode);

                couleur(KCyan);
                cout << "Entrez la position (ligne colonne) et la direction (z/q/s/d) ou 'x' pour quitter:" << endl;
                cout << "Exemple: 3 4 d" << endl;
                couleur(KReset);
                
                string input;
                getline(cin, input);

                if (input == "x" || input == "X") break;
                    
                unsigned row, col;
                char direction;

                // Analyse l'entrée utilisateur
                if (sscanf(input.c_str(), "%u %u %c", &row, &col, &direction) == 3) { // Vérifie que trois valeurs ont été lues
                    if (row < taille && col < taille) { // Vérifie que les indices sont dans les limites de la grille
                        maPosition pos = {row, col};
                        
                        if (isValidMove(grid, pos, direction)) {
                            maPosition target = getTargetPosition(pos, direction); // Obtient la position cible
                            gridSwap(grid, pos, target);
                            
                            if (traitementDeAlignement(grid, score, combo, mode)) {
                                couleur(KJaune);
                                cout << "Bon coup! Combo x" << combo << endl;
                                couleur(KReset);
                            } else {
                                gridSwap(grid, pos, target);
                                combo = 1;
                                couleur(KRouge);
                                cout << "Aucune combinaison trouvée. Mouvement annulé." << endl;
                                couleur(KReset);
                            }
                            
                            this_thread::sleep_for(milliseconds(1000));
                        } else {
                            cout << "Mouvement invalide." << endl;
                            this_thread::sleep_for(milliseconds(1000));
                        }
                    }
                }
            }
            break;

        case MODE_CLEAR:
            while (true){
                auto tempsActuel = steady_clock::now();
                int tempsPasser = duration_cast<seconds>(tempsActuel - startTime).count();

                // Affiche le message de fin si le temps est écoulé
                if (isGridEmpty(grid) ) {
                    clearScreen();
                    couleur(KVert);
                    cout << "VICTOIRE! La grille est vide." << endl;
                    couleur(KCyan);
                    cout << "Temps écoulé: " << tempsPasser << " secondes" << endl;
                    cout << "Score final: " << score << " points" << endl;
                    cout << "Combo maximum: x" << combo << endl;
                    break;
                }

                // Affiche l'interface du jeu et l'information de la partie en cours
                displayGrid(grid, score, combo, tempsPasser, mode);

                couleur(KCyan);
                cout << "Entrez la position (ligne colonne) et la direction (z/q/s/d) ou 'x' pour quitter:" << endl;
                cout << "Exemple: 3 4 d" << endl;
                couleur(KReset);
                
                string input;
                getline(cin, input);

                // Sort de la boucle si l'utilisateur entre 'x'
                if (input == "x" || input == "X") break;
                    
                unsigned row, col;
                char direction;

                // Analyse l'entrée utilisateur
                if (sscanf(input.c_str(), "%u %u %c", &row, &col, &direction) == 3) { // Vérifie que trois valeurs ont été lues
                    if (row < taille && col < taille) {
                        maPosition pos = {row, col};
                        
                        if (isValidMove(grid, pos, direction)) {
                            maPosition target = getTargetPosition(pos, direction);
                            gridSwap(grid, pos, target);
                            
                            if (traitementDeAlignement(grid, score, combo, mode)) {
                                couleur(KJaune);
                                cout << "Bon coup! Combo x" << combo << endl;
                                couleur(KReset);
                            } else {
                                gridSwap(grid, pos, target);
                                combo = 1;
                                couleur(KRouge);
                                cout << "Aucune combinaison trouvée. Mouvement annulé." << endl;
                                couleur(KReset);
                            }
                            
                            this_thread::sleep_for(milliseconds(1000)); // Pause pour permettre au joueur de voir le résultat
                        } else {
                            cout << "Mouvement invalide." << endl;
                            this_thread::sleep_for(milliseconds(1000));
                        }
                    }
                }
            }
            break;

        case MODE_1v1:
            cout << "Mode de jeu: 1v1 " << endl;
            cout << "Objectif: Obtenir le plus de points possible avant la fin du temps imparti." << endl;
            break;

        default:
            couleur(KRouge);
            cout << "Mode de jeu invalide, veuillez réessayer en appuyant sur Entrée." << endl;
            couleur(KReset);
            break;
    }

    cout << "\nAppuyez sur Entrée pour continuer..." << endl;
    cin.ignore();
    cin.get();
}

void game(){
    size_t taille;
    int choix;

    couleur(KCyan);
    cout << "Bienvenue dans Number Crush" << endl;

    cout << "Veuillez choisir votre mode de jeu :" << endl;
    cout << "1. Mode Score" << endl;
    cout << "2. Mode Clear" << endl;
    cout << "3. Mode 1v1" << endl;
    cout << "4. Quitter" << endl;

    cout << "Votre choix : ";
    couleur(KReset);
    cin >> choix;

    // Affiche la sélection choisie
    switch (choix) {
    case 1:
        afficherMode(MODE_SCORE);
        break;
    case 2:
        afficherMode(MODE_CLEAR);
        break;
    case 3:
        afficherMode(MODE_1v1);
        break;
    case 4: // Quitter le jeu
        couleur(KCyan);
        cout << "Merci d'avoir joué ! Au revoir !" << endl;
        couleur(KReset);
        exit(0);
        break;
    default:
        couleur(KRouge);
        cout << "Mode de jeu invalide, veuillez recommencer." << endl;
        couleur(KReset);
        break;
    }
}