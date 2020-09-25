#include <iostream>
#include "Matrice.h"
#include <thread>


using namespace std;

//Création de la Matrice avec son nombre de ligne et colonne et instanciation de son contenu à 0.
Matrice::Matrice(const int l) {
    this->ligne = l;
    this->colonne = l;
    this->values[l][l];
    for(int i = 0; i < l; i++)
    {
        for(int j = 0; j <l; j++)
        {
            this->values[i][j] = 0;
        }
    }
}

Matrice::~Matrice() {}

//Affichage de la matrice
void Matrice::Display() {
    for(int i = 0; i < this->ligne; i++) {
        for(int j = 0; j < this->colonne; j++) {
            if(j == this->colonne-1) cout << this->values[i][j];
            else cout << this->values[i][j] << " - ";
        }
        cout << endl;
    }
    cout << endl;
}

//Remplissage de la matrice
void Matrice::FillMatrice() {
    for(int i = 0; i < this->ligne; i++) {
        for(int j = 0; j < this->colonne; j++) {
            this->values[i][j] = rand()%5+1; //Donne un nombre random entre 1 et 5
        }
    }
}

Matrice Matrice::ProduitBloc(Matrice &A, Matrice &B, Matrice &P, int start, int end) {
    for(int i = start; i < end ; i++) {
        for(int j = 0; j < B.colonne; j++) {
            for(int k = 0; k < A.colonne; k++) {
                P.values[i][j] += A.values[i][k] * B.values[k][j];
            }
        }
    }
    return P;
}

int main(int ac, char** av) {

    const int length = 4;
    Matrice A = Matrice(length);
    A.FillMatrice();
    A.Display();
    Matrice B = Matrice(length);
    B.FillMatrice();
    B.Display();
    Matrice P = Matrice(length);

    //Calcul de la matrice P ligne par ligne
    thread a(&Matrice::ProduitBloc, &P, ref(A), ref(B), ref(P), 0, 1);
    thread b(&Matrice::ProduitBloc, &P, ref(A), ref(B), ref(P), 1, 2);
    thread c(&Matrice::ProduitBloc, &P, ref(A), ref(B), ref(P), 2, 3);
    thread d(&Matrice::ProduitBloc, &P, ref(A), ref(B), ref(P), 3, 4);
    a.join();
    b.join();
    c.join();
    d.join();
    P.Display();
}
