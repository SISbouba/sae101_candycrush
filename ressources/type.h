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

// Déclaration des constantes
const unsigned KImpossible (0); // valeur représentant une case vide*
const unsigned KReset   (0);
const unsigned KCandies (5);
const unsigned KRouge   (31);
const unsigned KVert    (32);
const unsigned KJaune   (33);
const unsigned KBleu    (34);
const unsigned KMAgenta (35);

#endif // TYPE_H