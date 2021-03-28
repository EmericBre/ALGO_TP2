#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "a234.h"

int verifCleFils(Arbre234 a, int cle) {
    if (a!=NULL && a->t != 0) {
        for (int i = 0; i < 4; i++) {
            if (a->fils[i]->t == 2) {
                if (a->fils[i]->cles[1] == cle) {
                    return i;
                }
            }
            else if (a->fils[i]->t == 3) {
                if (a->fils[i]->cles[0] == cle || a->fils[i]->cles[1] == cle) {
                    return i;
                }
            }
            else if (a->fils[i]->t == 4) {
                if (a->fils[i]->cles[0] == cle || a->fils[i]->cles[1] == cle || a->fils[i]->cles[2] == cle) {
                    return i;
                }
            }
        }
    }
    return 0;
}

void fusion(Arbre234 *a) {
    Arbre234 G;
    Arbre234 D;
    Arbre234 A = *a;

    G = A->fils[1];
    D = A->fils[2];
    A->cles[0] = G->cles[1];
    A->cles[1] = A->cles[1];
    A->cles[2] = D->cles[1];
    A->t = 4;
    A->fils[0] = G->fils[1];
    A->fils[1] = G->fils[2];
    A->fils[2] = D->fils[1];
    A->fils[3] = D->fils[2];
    free(D);
    free(G);
    // for (j=indice; j < A->t; j++) {
    //     A->cles[j] = A->cles[j+1];
    //     A->fils[j+1] = A->fils[j+2];
    // }
    // A->t = A->t-1;*
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
    A->cles[indice] = D->cles[indice];
    G->fils[G->t+1] = D->fils[indice];

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
    Arbre234 a = *A;
    if (a == NULL || (estFeuille(a)==1)) {
        printf("La clé demandée n'existe pas dans l'arbre.\n");
        return;
    }

    if (verifCleFils(a, cle) != 0) {
        Arbre234 find = RechercherCle(a, cle);
        if (estFeuille(find) == 1) {
            if (find->t == 3) {
                if (find->cles[1] == cle) {
                    find->cles[1] = find->cles[0];
                }
                find->cles[0] = 0;
                find->t--;
            }
            else if (find->t == 4) {
                if (find->cles[1] == cle) {
                    find->cles[1] = find->cles[2];
                }
                else if (find->cles[0] == cle) {
                    find->cles[0] = find->cles[1];
                    find->cles[1] = find->cles[2];
                }
                find->cles[2] = 0;
                find->t--;
            }
            else {
                if (a->t == 2 && a->fils[1]->t == 2 && a->fils[2]->t == 2) {
                    fusion(&a);
                    if (a->cles[0] == cle) {
                        a->cles[0] = a->cles[1];
                        a->cles[1] = a->cles[2];
                    }
                    else if (a->cles[1] == cle) {
                        a->cles[1] = a->cles[2];
                    }
                    a->cles[2] = 0;
                    a->t--;
                }
                else if (a->t == 2) {
                    if (verifCleFils(a, cle) == 1) {
                        find->cles[1] = a->cles[1];
                        a->cles[1] = a->fils[2]->cles[0];
                        if (a->fils[2]->t == 4) {
                            a->fils[2]->cles[0] = a->fils[2]->cles[1]; 
                            a->fils[2]->cles[1] = a->fils[2]->cles[2]; 
                        }
                        a->fils[2]->t--;
                    }
                    else {
                        find->cles[1] = a->cles[1];
                        if (a->t == 4) {
                            a->cles[1] = a->fils[1]->cles[2];
                        }
                        else {
                            a->cles[1] = a->fils[1]->cles[1];
                            a->fils[1]->cles[1] = a->fils[1]->cles[0];
                        }
                        a->fils[1]->t--;
                    }
                }
            }
        }
    }
    else {
        if (a->t == 2) {
            if (cle < a->cles[1]) {
                Detruire_Cle_Rec(cle, &a->fils[1]);
            }
            else {
                Detruire_Cle_Rec(cle, &a->fils[2]);
            }
        }
        else if (a->t == 3) {
            if (cle < a->cles[0]) {
                Detruire_Cle_Rec(cle, &a->fils[0]);
            }
            else if (cle > a->cles[1]) {
                Detruire_Cle_Rec(cle, &a->fils[2]);
            }
            else {
                Detruire_Cle_Rec(cle, &a->fils[1]);
            }
        }
        else {
            if (cle < a->cles[0]) {
                Detruire_Cle_Rec(cle, &a->fils[0]);
            }
            else if (cle > a->cles[2]) {
                Detruire_Cle_Rec(cle, &a->fils[3]);
            }
            else if (cle > a->cles[0] && cle < a->cles[1]) {
                Detruire_Cle_Rec(cle, &a->fils[1]);
            }
            else {
                Detruire_Cle_Rec(cle, &a->fils[2]);
            }
        }
    }
    // int i = 0;
    // Arbre234 a = *A;
    // while (i < a->t-1 && cle > a->cles[i]) {
    //     printf("test\n");
    //     i = i+1;
    // }

    // if (a->fils[0] != NULL) {
    //     printf("test2\n");
    //     if (i < a->t && a->cles[i]==cle) {
    //         if (a->fils[i]->t > a->fils[i+1]->t) {
    //             a->cles[i] = CleMax(a->fils[i]);
    //             Detruire_Cle_Rec(a->cles[i], &a->fils[i]);
    //         }
    //         else {
    //             if (a->fils[i+1]->t > 1) {
    //                 a->cles[i] = CleMin(a->fils[i+1]);
    //                 Detruire_Cle_Rec(a->cles[i], &a->fils[i]);
    //             }
    //             else {
    //                 fusion (A, i);
    //                 Detruire_Cle_Rec(cle, &a->fils[i]);
    //             }
    //         }
    //     }
    //     else {
    //         printf("test3\n");
    //         if (a->fils[i]->t == 2) {
    //             printf("test4\n");
    //             if (i>1 && a->fils[i-1]->t > 1) {
    //                 printf("test5\n");
    //                 rd_gen(A, i);
    //             }
    //             else {
    //                 if (i <= a->t && a->fils[i+1]->t > 1) {
    //                     rg_gen(A, i);
    //                 }
    //                 else {
    //                     if (i > 1) {
    //                         i = i-1;
    //                     }
    //                     fusion(A, i);
    //                 }
    //             }
    //         }
    //         Detruire_Cle_Rec(cle, &a->fils[i]);
    //     }
    // }
    // else {
    //     if (i <= a->t && a->cles[i] == cle) {
    //         for (int j = 1; j < a->t; j++) {
    //             a->cles[j] = a->cles[j+1];
    //         }
    //         a->t = a->t-1;
    //     }
    // }
}
