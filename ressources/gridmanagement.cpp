/**
 * @file gridmanagement.cpp
 * @author DURAN Kalvin - SISE Aboubakar
 * @brief Fonctions de gestion de la grille de jeu.
 * @details 
 * Ce fichier contient les définitions des fonctions utilisées pour gérer la grille de jeu, y compris l'affichage,
 * l'initialisation, la gravité, et le remplissage de la grille.
 */

#include <iostream>
#include "gridmanagement.h"
#include "type.h" 

using namespace std;

//! Change la couleur du texte dans la console
void couleur (const unsigned & coul) {
    cout << "\033[" << coul <<"m";
}

//! Efface l'écran
void clearScreen () {
    cout << "\033[H\033[2J";
}

//! Change la couleur en fonction du type de bonbon
void couleur_KNbCandies(const unsigned & candy){
    switch (candy) {
    case 1:
        couleur(KRouge);
        break;
    case 2:
        couleur(KVert);
        break;
    case 3:
        couleur(KBleu);
        break;
    case 4:
        couleur(KJaune);
        break;
    }
}

/**
 * @brief Initialisation de la grille
 * 
 * @param grid 
 * @param size
 * @details
 * Initialise une grille de taille spécifiée avec des valeurs aléatoires représentant différents types de bonbons.
 * Évite les alignements initiaux de trois bonbons identiques.
 */
void initGrid (mat & grid, const size_t & size)
{
    srand(time(NULL));
    grid.resize(size);
    for (size_t i = 0; i < size; ++i) {
        grid[i].resize(size);
        for (size_t j = 0; j < size; ++j) {
            // Génération aléatoire d'une valeur de bonbon en évitant les alignements initiaux
            bool estValide;
            unsigned bonbon;

            //! Boucle jusqu'à obtenir une valeur valide
            do {
                estValide = true;
                bonbon = 1 + rand() % (KCandies - 1);
                // Vérifier l'alignement horizontal (2 à gauche)
                if (j >= 2 && grid[i][j-1] == bonbon && grid[i][j-2] == bonbon) {
                    estValide = false;
                }
                // Vérifier l'alignement vertical (2 au-dessus)
                if (i >= 2 && grid[i-1][j] == bonbon && grid[i-2][j] == bonbon) {
                    estValide = false;
                }
            } while (!estValide);
            
            grid[i][j] = bonbon;
        }
    }
}

/**
 * @brief Affichage de la grille
 * 
 * @param grid 
 * @param score 
 * @param combo 
 * @param timeValue 
 * @param mode
 * @details
 * Affiche la grille de jeu dans la console avec des informations supplémentaires telles que le score, le combo,
 * le temps restant et le mode de jeu.
 */
void  displayGrid (const mat & grid, unsigned score, unsigned combo, int timeValue, Gamemode mode)
{
    clearScreen();
    switch(mode) {
        case MODE_SCORE:
            couleur(KCyan);
            cout << "Mode de jeu: SCORE " << endl;
            cout << "Score: " << score << " | Combo: x" << combo << " | Temps: " << timeValue << "s" << endl;
            cout << "Objectif: " << KTargetScore << " points en 120s" << endl;
            couleur(KReset);
            break;
            
        case MODE_CLEAR:
            couleur(KCyan);
            cout << "Mode de jeu: CLEAR " << endl;
            cout << "Bonbons restants: " << compterBonbonRestants(grid) << " | Combo: x" << combo << " | Temps: " << timeValue << "s" << endl;
            cout << "Objectif: Vider la grille le plus vite possible." << endl;
            couleur(KReset);
            break;
            
        // case MODE_1v1:
        //     couleur(KCyan);
        //     cout << "Mode de jeu: 1v1 " << endl;
        //     cout << "Score Joueur 1: " << score << " | Combo: x" << combo << endl;
        //     cout << "Score Joueur 2: " << score << " | Combo: x" << combo << endl;
        //     cout << "Temps restant: " << timeValue << "s" << endl;
        //     cout << "Objectif: Avoir le score le plus élevé en 120s" << endl;
        //     couleur(KReset);
        //     break;
    }

    cout << "    ";
    for (size_t line = 0; line < grid.size(); ++line) {
        cout << line << " ";
    }
    cout << endl;

    for (size_t i = 0; i < grid.size(); ++i) {
        cout << i << " | ";
        for (const unsigned & j : grid[i]) {
            if(j >= 1 && j <= KCandies){
                couleur_KNbCandies(j);
                cout << j << " ";
            }
            else {
                couleur_KNbCandies(j);
                cout << ' ';
            }
        }
        couleur(KReset);
        cout << "|" << endl;
    }
    cout << endl;
}

/**
 * @brief Déplacement des éléments de la grille
 * 
 * @param Grid 
 * @param PosStart 
 * @param PosEnd 
 * @details
 * Échange les éléments à deux positions spécifiées dans la grille.
 */
void gridSwap (mat & Grid, const maPosition & PosStart, const maPosition & PosEnd)
{
    swap(Grid[PosStart.abs][PosStart.ord], Grid[PosEnd.abs][PosEnd.ord]);
}

/**
 * @brief Compte le nombre de bonbons restants dans la grille
 * 
 * @param grid 
 * @return unsigned 
 * @details
 * Parcourt la grille et compte le nombre de cases qui ne sont pas vides (différentes de KImpossible).
 */
unsigned compterBonbonRestants(const mat& grid) {
    unsigned compteur = 0;
    for (size_t i = 0; i < grid.size(); ++i) {
        for (size_t j = 0; j < grid[i].size(); ++j) {
            if (grid[i][j] != KImpossible) {
                compteur = compteur + 1;
            }
        }
    }
    return compteur;
}

/**
 * @brief Vérifie si la grille est vide
 * 
 * @param grid 
 * @return true 
 * @return false
 * @details
 * Parcourt la grille pour vérifier si toutes les cases sont vides (égales à KImpossible). 
 */
bool isGridEmpty(const mat& grid) {
    for (size_t i = 0; i < grid.size(); ++i) {
        for (size_t j = 0; j < grid[i].size(); ++j) {
            if (grid[i][j] != KImpossible) {
                return false;
            }
        }
    }
    return true;
}

/**
 * @brief Applique la gravité sur la grille
 * @details *
 * Parcourt chaque colonne de la grille et fait "tomber" les bonbons vers le bas pour remplir les cases vides (KImpossible).
 */
void gravité(mat& grid) {
    size_t taille = grid.size();
    
    for (size_t col = 0; col < taille; col = col + 1) {
        // Partir du bas et remonter
        int pos = taille - 1; // Position où on écrit le prochain bonbon
        
        // Parcourir de bas en haut
        for (int row = taille - 1; row >= 0; row = row - 1) {
            if (grid[row][col] != KImpossible) {
                // Si on a trouvé un bonbon, le placer à la position d'écriture
                if (row != pos) {
                    grid[pos][col] = grid[row][col];
                    grid[row][col] = KImpossible;
                }
                pos = pos - 1;
            }
        }
    }
}

/**
 * @brief Remplit les cases vides de la grille avec de nouveaux bonbons
 * 
 * @param grid 
 * @param mode 
 * @details
 * Parcourt la grille et remplit les cases vides (KImpossible) avec de nouveaux bonbons aléatoires uniquement si le mode de jeu est MODE_SCORE.
 */
void remplirGrid(mat& grid, Gamemode mode) {
    if (mode == MODE_SCORE) {
        size_t taille = grid.size();
        srand(time(NULL));
        
        for (size_t col = 0; col < taille; col = col + 1) {
            for (size_t row = 0; row < taille; row = row + 1) {
                if (grid[row][col] == KImpossible) {
                    // Générer un nouveau bonbon aléatoire
                    grid[row][col] = 1 + rand() % (KCandies - 1);
                }
            }
        }
    }
}
