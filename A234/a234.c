#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "a234.h"

#define max(a,b) ((a)>(b)?(a):(b))


int hauteur (Arbre234 a)
{
  int h0, h1, h2, h3 ;
  
  if (a == NULL)
    return 0 ;

  if (a->t == 0)
    return 0 ;

  h0 = hauteur (a->fils [0]) ;
  h1 = hauteur (a->fils [1]) ;
  h2 = hauteur (a->fils [2]) ;
  h3 = hauteur (a->fils [3]) ;

  return 1 + max (max (h0,h1),max (h2,h3)) ;
} 

int NombreCles (Arbre234 a)
{  
  if (a == NULL) {
    return 0 ;
  }
  if (a->t == 0) {
    return 0;
  }

  return a->t-1 + NombreCles(a->fils[0]) + NombreCles(a->fils[1]) + NombreCles(a->fils[2]) + NombreCles(a->fils[3]) ;
}

int CleMax (Arbre234 a)
{
  if (a==NULL) {
    return 0;
  }
  if (a->t == 0) {
    return -1;
  }
  else if (a->t == 2 || a->t == 3) {
    return max(CleMax(a->fils[2]), a->cles[1]);
  }
  else {
    return max(CleMax(a->fils[3]), a->cles[2]);
  }
}

int CleMin (Arbre234 a)
{
  int verif;
  if (a==NULL) {
    return 0;
  }
  if (a->t == 0) {
    return -1;
  }
  else if (a->t == 2) {
    verif = CleMin(a->fils[1]);
    if (verif == -1) {
      return a->cles[1];
    }
    else {
      return verif;
    }
  }
  else {
    verif = CleMin(a->fils[0]);
    if (verif == -1) {
      return a->cles[0];
    }
    else {
      return verif;
    }
  }
}

Arbre234 RechercherCle (Arbre234 a, int cle)
{
  if (a==NULL) {
    printf("L'arbre n'existe pas.\n");
    return NULL;
  }
  if (a->t == 0) {
    printf("La clé demandée n'a pas été trouvée dans l'arbre.\n");
    return NULL;
  }
  if (a->t == 2) {
    if (cle == a->cles[1]) {
      return a;
    }
    else if (cle < a->cles[1]) {
      return RechercherCle(a->fils[1], cle);
    }
    else {
      return RechercherCle(a->fils[2], cle);
    }
  }
  else if (a->t == 3) {
    if (cle == a->cles[0] || cle == a->cles[1]) {
      return a;
    }
    else if (cle < a->cles[0]) {
      return RechercherCle(a->fils[0], cle);
    }
    else if (cle > a->cles[0] && cle < a->cles[1]) {
      return RechercherCle(a->fils[1], cle);
    }
    else {
      return RechercherCle(a->fils[2], cle);
    }
  }
  else {
    if (cle == a->cles[0] || cle == a->cles[1] || cle == a->cles[2]) {
      return a;
    }
    else if (cle < a->cles[0]) {
      return RechercherCle(a->fils[0], cle);
    }
    else if (cle > a->cles[0] && cle < a->cles[1]) {
      return RechercherCle(a->fils[1], cle);
    }
    else if (cle > a->cles[1] && cle < a->cles[2]) {
      return RechercherCle(a->fils[2], cle);
    }
    else {
      return RechercherCle(a->fils[3], cle);
    }
  }
}

void AnalyseStructureArbre (Arbre234 a, int *feuilles, int *noeud2, int *noeud3, int *noeud4)
{
  if (a!=NULL) {
    if (a->t == 0) {
      *feuilles += 1;
    }
    else if (a->t == 2) {
      *noeud2 += 1;
    }
    else if (a->t == 3) {
      *noeud3 += 1;
    }
    else {
      *noeud4 += 1;
    }
    AnalyseStructureArbre(a->fils[0], feuilles, noeud2, noeud3, noeud4);
    AnalyseStructureArbre(a->fils[1], feuilles, noeud2, noeud3, noeud4);
    AnalyseStructureArbre(a->fils[2], feuilles, noeud2, noeud3, noeud4);
    AnalyseStructureArbre(a->fils[3], feuilles, noeud2, noeud3, noeud4);
  }

}

int sommeNoeud(Arbre234 a) {
  if (a==NULL || a->t == 0) {
    return 0;
  }
  else {
    return a->cles[0] + a->cles[1] + a->cles[2];
  }
}

Arbre234 noeud_max (Arbre234 a)
{
  if (a==NULL || a->t == 0) {
    return NULL;
  }
  Arbre234* fils = malloc(sizeof(Arbre234)*4);
  fils[0] = noeud_max(a->fils[0]);
  fils[1] = noeud_max(a->fils[1]);
  fils[2] = noeud_max(a->fils[2]);
  fils[3] = noeud_max(a->fils[3]);

  int max = sommeNoeud(a);
  int maxfils = 4;
  for (int i = 0; i < 4; i++) {
    if (max < sommeNoeud(fils[i])) {
      max = sommeNoeud(fils[i]);
      maxfils = i;
    }
  }
  if (maxfils == 4) {
    free(fils);
    return a;
  }
  else {
    Arbre234 retour = fils[maxfils];
    free(fils);
    return retour;
  }
}


void Afficher_Cles_Largeur (Arbre234 a)
{
  /*
    Afficher le cles de l'arbre a avec
    un parcours en largeur
  */

  return ;
}

void Affichage_Cles_Triees_Recursive (Arbre234 a)
{
  /* 
     Afficher les cles en ordre croissant
     Cette fonction sera recursive
  */
     
}

void Affichage_Cles_Triees_NonRecursive (Arbre234 a)
{
    /* 
     Afficher les cles en ordre croissant
     Cette fonction ne sera pas recursive
     Utiliser une pile
  */

}


void Detruire_Cle (Arbre234 *a, int cle)
{
  /*
    retirer la cle de l'arbre a
  */

  return ;
}




int main (int argc, char **argv)
{
  Arbre234 a ;

  if (argc != 2)
    {
      fprintf (stderr, "il manque le parametre nom de fichier\n") ;
      exit (-1) ;
    }

  a = lire_arbre (argv [1]) ;

  printf ("==== Afficher arbre ====\n") ;
  
  afficher_arbre (a, 0) ;

  printf ("==== Nombre Clés arbre ====\n") ;
  
  printf("Nombre de clés de l'arbre : %d\n", NombreCles (a)) ;

  printf ("==== Clé Max arbre ====\n") ;
  
  printf("Clé max de l'arbre : %d\n", CleMax (a)) ;

  printf ("==== Clé Min arbre ====\n") ;
  
  printf("Clé min de l'arbre : %d\n", CleMin (a)) ;

  printf ("==== Rechercher Clé arbre ====\n") ;
  
  printf("Rechercher la clé 50 dans l'arbre : \n"); 
  afficher_arbre (RechercherCle(a, 50), 0) ;
  printf("\nRechercher la clé 12 dans l'arbre : \n\n"); 
  afficher_arbre (RechercherCle(a, 12), 0) ;
  printf("\nRechercher la clé 15 dans l'arbre : \n"); 
  afficher_arbre (RechercherCle(a, 15), 0) ;
  printf("\nRechercher la clé 11 dans l'arbre : \n\n"); 
  afficher_arbre (RechercherCle(a, 11), 0) ;
  printf("\nRechercher la clé 3 dans l'arbre : \n"); 
  afficher_arbre (RechercherCle(a, 3), 0) ;
  printf("\nRechercher la clé 9 dans l'arbre : \n"); 
  afficher_arbre (RechercherCle(a, 9), 0) ;

  printf ("==== Analyse Structure arbre ====\n") ;

  int feuilles = 0;
  int noeud2 = 0;
  int noeud3 = 0;
  int noeud4 = 0;

  AnalyseStructureArbre(a, &feuilles, &noeud2, &noeud3, &noeud4);
  
  printf("Analyse de la structure de l'arbre : %d, %d, %d, %d\n", feuilles, noeud2, noeud3, noeud4);

  printf ("==== Max noeud arbre ====\n") ;
  
  printf("Noeud maximum de l'arbre : \n");
  afficher_arbre (noeud_max(a), 0) ;

}
