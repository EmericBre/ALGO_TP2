#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "a234.h"
#include "detruire_cle.h" 

void fusion(Arbre234 *a, int indice) {
    Arbre234 G;
    Arbre234 D;
    Arbre234 A = *a;

    if (A->t == 2) {
        G = A->fils[indice];
        D = A->fils[indice+1];
        A->cles[0] = G->cles[1];
        A->cles[1] = A->cles[indice];
        A->cles[2] = D->cles[1];
        A->fils[0] = G->fils[1];
        A->fils[1] = G->fils[2];
        A->fils[2] = D->fils[1];
        A->fils[3] = D->fils[2];
        A->t = 4;
        free(G);
        free(D);
    }
    else {
        G = A->fils[indice];
        D = A->fils[indice+1];
        G->cles[0] = G->cles[1];
        G->cles[1] = A->cles[indice];
        G->cles[2] = D->cles[1];
        G->fils[0] = G->fils[1];
        G->fils[1] = G->fils[2];
        G->fils[2] = D->fils[1];
        G->fils[3] = D->fils[2];
        G->t = 4;
        free(D);
        if (A->t == 3) {
            if (indice == 0) {
                A->fils[1] = A->fils[0];
                A->fils[1]->t = A->fils[0]->t;
            }
            else if (indice == 1) {
                A->cles[1] = A->cles[0];
                A->fils[2] = A->fils[1];
                A->fils[2]->t = A->fils[1]->t;
                A->fils[1] = A->fils[0];
                A->fils[1]->t = A->fils[0]->t;
            }
            A->fils[0] = NULL;
            A->cles[0] = 0;
            A->t--;
        }
        else if (A->t == 4) {
            if (indice == 1) {
                A->cles[1] = A->cles[2];
                A->fils[2] = A->fils[3];
                A->fils[2]->t = A->fils[3]->t;
            }
            else if (indice == 0) {
                A->fils[1] = A->fils[2];
                A->fils[1]->t = A->fils[2]->t;
                A->fils[2] = A->fils[3];
                A->fils[2]->t = A->fils[3]->t;
                A->cles[0] = A->cles[1];
                A->cles[1] = A->cles[2];
            }
            A->cles[2] = 0;
            A->fils[3] = NULL;
            A->t--;
        }
    }
}

void verifFusion(Arbre234 *a) {
    Arbre234 tmp = *a;
    if (tmp != NULL && tmp->t != 0) {
        verifFusion(&tmp->fils[0]);
        verifFusion(&tmp->fils[1]);
        verifFusion(&tmp->fils[2]);
        verifFusion(&tmp->fils[3]);
        if (tmp->t == 2 && tmp->fils[1]->t == 2 && tmp->fils[2]->t == 2) {
            fusion(a, 1);
        }
        else if (tmp->t > 2) {
            for (int i = 0; i < tmp->t-1; i++) {
                if (tmp->fils[i]->t == 2 && tmp->fils[i+1]->t == 2) {
                    fusion(a, i);
                }
            }
        }
    }
}

void rd_gen(Arbre234 *a, int indice) {
    int j;
    Arbre234 G;
    Arbre234 D;
    Arbre234 A = *a;

    G = A->fils[indice-1];

    D = A->fils[indice];

    for (j = D->t; j>1; j--) {
        D->cles[j] = D->cles[j-1];
        D->fils[j+1] = D->fils[j];
    }
    D->fils[1] = D->fils[0];
    D->cles[0] = A->cles[indice-1];
    D->t = D->t+1;

    A->cles[indice-1] = G->cles[G->t];
    D->fils[0] = G->fils[G->t+1];
    G->t = G->t-1;
}

void rg_gen(Arbre234 *a, int indice) {
    Arbre234 G;
    Arbre234 D;
    Arbre234 A = *a;

    G = A->fils[indice];
    D = A->fils[indice+1];
    G->t = G->t+1;
    if (G->t == 3) {
        G->cles[0] = G->cles[1];
        G->cles[1] = A->cles[indice];
        G->fils[0] = G->fils[1];
        G->fils[1] = G->fils[2];
        G->fils[2] = D->fils[0];
    }
    else {
        G->cles[2] = A->cles[indice];
        G->fils[3] = D->fils[0];
    }
    A->cles[indice] = D->cles[0];

    D->t = D->t-1;

    if (D->t == 2) {
        D->cles[0] = 0;
        D->fils[0] = NULL;
    }
    else {
        D->cles[0] = D->cles[1];
        D->cles[1] = D->cles[2];
        D->fils[0] = D->fils[1];
        D->fils[0]->t = D->fils[1]->t;
        D->fils[1] = D->fils[2];
        D->fils[1]->t = D->fils[2]->t;
        D->fils[2] = D->fils[3];
        D->fils[2]->t = D->fils[3]->t;
    }
}

void Detruire_Cle_Rec(int cle, Arbre234 *A) {
    Arbre234 a = *A;
    int indice = 0;

    if (a->t == 2) { // On r??cup??re l'indice de l'??l??ment ??gal ?? la cl??, ou du premier ??l??ment sup??rieur ?? la cl??
        if (cle <= a->cles[1]) {
            indice = 1;
        }
        else {
            indice = 2;
        }
    }
    else {
        for (int i = 0; i < a->t-1; i++) {
            if (cle > a->cles[i]) {
                indice++;
            }
        }
    }

    if (estFeuille(a)==0) { // Noeud interne
        if (a->cles[indice] == cle) { // On a trouv?? la cl??
            if (a->fils[indice]->t > a->fils[indice+1]->t) { // fils gauche plus petit que fils droit
                a->cles[indice] = CleMax(a->fils[indice]); // On r??cup??re la cl?? max du fils gauche et on la supprime de ce fils
                Detruire_Cle_Rec(a->cles[indice], &a->fils[indice]);
            }
            else {
                if (a->fils[indice+1]->t > 2) { // Si le fils droit a plus d'une cl??
                    a->cles[indice] = CleMin(a->fils[indice+1]); // On r??cup??re la cl?? min du fils droit et on la supprime de ce fils
                    Detruire_Cle_Rec(a->cles[indice], &a->fils[indice+1]);
                }
                else {
                    fusion(A, indice); // Si le fils droit a une cl?? et que le fils gauche n'est pas plus grand (a une cl?? aussi), on fusionne
                    Detruire_Cle_Rec(cle, &a->fils[indice]);
                }
            }
        }
        else { // On n'a pas trouv?? la cl??
            if (a->fils[indice]->t == 2) { // Le fils n'a qu'une cl??
                if (indice > 0 && a->fils[indice-1]->t > 2) { // Le fils ?? sa gauche a plus d'une cl??
                    rd_gen(A, indice); // On fait une rotation droite
                }
                else { // Le fils ?? sa gauche n'a qu'une cl??
                    if (((a->t == 2 && indice == 1) || (a->t > 2 && indice < a->t-1)) && (a->fils[indice+1]->t > 2)) { // Si le fils ?? sa droite ?? plus d'une cl??
                        rg_gen(A, indice); // On fait une rotation gauche
                    }
                    else { // Les deux fils n'ont qu'une cl??, on les fusionne
                        if (indice > 0 && a->t > 2) {
                            indice--;
                        }
                        fusion(A, indice);
                        Detruire_Cle_Rec(cle, &a->fils[indice+1]);
                        return;
                    }
                }
            }
            Detruire_Cle_Rec(cle, &a->fils[indice]);
        }
        return;
    }
    else { // Noeud est une feuille
        if (a->t == 3) {
            if (indice == 1) {
                a->cles[1] = a->cles[0];
            }
        }
        else if (a->t == 4) {
            if (indice == 1) {
                a->cles[1] = a->cles[2];
            }
            else if (indice == 0) {
                a->cles[0] = a->cles[1];
                a->cles[1] = a->cles[2];
            }
        }
        else if (a->t == 2) {
            a->t = 1;
        }
        a->t--;
        return;
    }
}
