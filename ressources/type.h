#ifndef TYPE_H
#define TYPE_H

#include <vector>

using namespace std;

typedef vector <unsigned> line; // un type représentant une ligne de la grille
typedef vector <line> mat; // un type représentant la grille
typedef struct {
    unsigned abs;
    unsigned ord;
} maPosition; // une position dans la girlle



#endif // TYPE_H