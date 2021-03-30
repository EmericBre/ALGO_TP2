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
            if (indice == 1) {
                A->cles[1] = A->cles[0];
            }
            else if (indice == A->t-2) {
                A->cles[indice] = 0;
            }
            A->t--;
            A->fils[indice+1] = A->fils[indice];
        }
        else if (A->t == 4) {
            if (indice == 1) {
                A->cles[1] = A->cles[2];
            }
            else if (indice == A->t-2) {
                A->cles[indice] = 0;
            }
            else if (indice == 0) {
                A->cles[0] = A->cles[1];
                A->cles[1] = A->cles[2];
                printf("\n");
                A->fils[1] = A->fils[2];
                A->fils[2] = A->fils[3];
            }
            printf("\n");
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
    int j;
    Arbre234 G;
    Arbre234 D;
    Arbre234 A = *a;

    G = A->fils[indice];
    D = A->fils[indice+1];
    G->cles[G->t+1] = A->cles[indice];
    G->t = G->t+1;
    if (G->t == 3) {
        G->cles[0] = G->cles[1];
        G->cles[1] = A->cles[indice];
        G->fils[0] = G->fils[1];
        G->fils[1] = G->fils[2];
        G->fils[2] = D->fils[indice];
    }
    else {
        G->cles[2] = A->cles[indice];
        G->fils[3] = D->fils[indice];
    }
    A->cles[indice] = D->cles[indice];

    for (j = 1; j < D->t; j++) {
        D->cles[j] = D->cles[j+1];
    }
    if (D->fils[0] != NULL) {
        for (j = 1; j < D->t-1; j++) {
            D->fils[j] = D->fils[j+1];
        }
    }
    D->t = D->t-1;
}

void Detruire_Cle_Rec(int cle, Arbre234 *A) {
    printf("\t");
    Arbre234 a = *A;
    int indice = 0;

    if (a->t == 2) { // On récupère l'indice de l'élément égal à la clé, ou du premier élément supérieur à la clé
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

    if (a->fils[1] != NULL && a->fils[1]->t != 0) { // Noeud interne
        if (a->cles[indice] == cle) { // On a trouvé la clé
            if (a->fils[indice]->t > a->fils[indice+1]->t) { // fils gauche plus petit que fils droit
                a->cles[indice] = CleMax(a->fils[indice]); // On récupère la clé max du fils gauche et on la supprime de ce fils
                Detruire_Cle_Rec(a->cles[indice], &a->fils[indice]);
            }
            else {
                if (a->fils[indice+1]->t > 2) { // Si le fils droit a plus d'une clé
                    a->cles[indice] = CleMin(a->fils[indice+1]); // On récupère la clé min du fils droit et on la supprime de ce fils
                    Detruire_Cle_Rec(a->cles[indice], &a->fils[indice+1]);
                }
                else {
                    fusion(A, indice); // Si le fils droit a une clé et que le fils gauche n'est pas plus grand (a une clé aussi), on fusionne
                    Detruire_Cle_Rec(cle, &a->fils[indice]);
                }
            }
        }
        else { // On n'a pas trouvé la clé
            if (a->fils[indice]->t == 2) { // Le fils n'a qu'une clé
                if (indice > 0 && a->fils[indice-1]->t > 2) { // Le fils à sa gauche a plus d'une clé
                    rd_gen(A, indice); // On fait une rotation droite
                }
                else { // Le fils à sa gauche n'a qu'une clé
                    if (((a->t == 2 && indice == 1) || (a->t > 2 && indice < a->t-1)) && (a->fils[indice+1]->t > 2)) { // Si le fils à sa droite à plus d'une clé
                        rg_gen(A, indice); // On fait une rotation gauche
                    }
                    else { // Les deux fils n'ont qu'une clé, on les fusionne
                        if (indice > 0) {
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
        a->t--;
        return;
    }
}
