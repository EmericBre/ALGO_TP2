#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "a234.h"
#include "pile.h"
#include "file.h"

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
  pfile_t file = creer_file();
  enfiler(file, a);
  Arbre234 current;
  while(file_vide(file) != 1) {
    current = defiler(file);
    if (current->t != 0) {
      if (current->t == 3 || current->t == 4) {
        enfiler(file, current->fils[0]);
      }
      enfiler(file, current->fils[1]);
      enfiler(file, current->fils[2]);
      if (current->t == 4) {
        enfiler(file, current->fils[3]);
      }
      
      if (current->t == 2) {
        printf("%d ", current->cles[1]);
      }
      else if (current->t == 3) {
        printf("%d %d ", current->cles[0], current->cles[1]);
      }
      else {
        printf("%d %d %d ", current->cles[0], current->cles[1], current->cles[2]);
      }
    }
  }

  return ;
}

void Affichage_Cles_Triees_Recursive (Arbre234 a)
{
  if (a!=NULL) {
    if (a->t == 2) {
      Affichage_Cles_Triees_Recursive(a->fils[1]);
      printf("%d ", a->cles[1]);
      Affichage_Cles_Triees_Recursive(a->fils[2]);
    }
    if (a->t == 3) {
      Affichage_Cles_Triees_Recursive(a->fils[0]);
      printf("%d ", a->cles[0]);
      Affichage_Cles_Triees_Recursive(a->fils[1]);
      printf("%d ", a->cles[1]);
      Affichage_Cles_Triees_Recursive(a->fils[2]);
    }
    if (a->t == 4) {
      Affichage_Cles_Triees_Recursive(a->fils[0]);
      printf("%d ", a->cles[0]);
      Affichage_Cles_Triees_Recursive(a->fils[1]);
      printf("%d ", a->cles[1]);
      Affichage_Cles_Triees_Recursive(a->fils[2]);
      printf("%d ", a->cles[2]);
      Affichage_Cles_Triees_Recursive(a->fils[3]);
    }
  }
     
}

int estFeuille(Arbre234 a) {
  if (a == NULL) {
    return 1;
  }
  else {
    if (a->fils[1]->t == 0 && a->fils[2]->t == 0) {
      return 1;
    }
    else {
      return 0;
    }
  }
}

int dejaTraite(Arbre234 a, Arbre234* traites, int length) {
  if (estFeuille(a) == 1) {
    return -2;
  }
  for (int i = 0; i < length; i++) {
    if (a==traites[i]) {
      return i;
    }
  }
  return -1;
}

void Affichage_Cles_Triees_NonRecursive (Arbre234 a)
{
  Arbre234* clestraitees = malloc(sizeof(Arbre234)*4);
  int* apparitions = malloc(sizeof(int)*4);
  ppile_t pile = creer_pile();
  empiler(pile, a);
  Arbre234 current;
  int i = 0;
  int result;

  while (pile_vide(pile) != 1) {
    current = depiler(pile);
    result = dejaTraite(current, clestraitees, 4);
    if (result == -1) {
      if (current->t == 2) {
        empiler(pile, current->fils[2]);
        empiler(pile, current);
        empiler(pile, current->fils[1]);
      }
      else {
        if (current->t == 4) {
          empiler(pile, current->fils[3]);
        }
        empiler(pile, current->fils[2]);
        empiler(pile, current->fils[1]);
        empiler(pile, current);
        empiler(pile, current->fils[0]);
      }
      clestraitees[i] = current;
      apparitions[i] = 1;
      i++;
    } 
    else if (result != -2) {
      if (current->t == 2) {
        printf("%d ", current->cles[1]);
      }
      else if (current->t == 3) {
        printf("%d ", current->cles[apparitions[result]-1]);
        Arbre234 save = depiler(pile);
        if (apparitions[result] != 2) {
          empiler(pile, current);
        }
        empiler(pile, save);
        apparitions[result]++;
      }
      else {
        printf("%d ", current->cles[apparitions[result]-1]);
        Arbre234 save = depiler(pile);
        if (apparitions[result] != 3) {
          empiler(pile, current);
        }
        empiler(pile, save);
        apparitions[result]++;
      }
    }
    else {
      if (current->t == 2) {
        printf("%d ", current->cles[1]);
      }
      else if (current->t == 3) {
        printf("%d %d ", current->cles[0], current->cles[1]);
      }
      else {
        printf("%d %d %d ", current->cles[0], current->cles[1], current->cles[2]);
      }
    }
  }
}


void Detruire_Cle (Arbre234 *a, int cle)
{
  Arbre234 tmp = *a;

  if (tmp!= NULL) {
    Detruire_Cle_Rec(cle, a);
    // if (tmp->t == 0) {
    //   tmp = tmp->fils[0];
    // }
  }

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

  printf ("\n==== Nombre Clés arbre ====\n") ;
  
  printf("Nombre de clés de l'arbre : %d\n", NombreCles (a)) ;

  printf ("\n==== Clé Max arbre ====\n") ;
  
  printf("Clé max de l'arbre : %d\n", CleMax (a)) ;

  printf ("\n==== Clé Min arbre ====\n") ;
  
  printf("Clé min de l'arbre : %d\n", CleMin (a)) ;

  printf ("\n==== Rechercher Clé arbre ====\n") ;
  
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

  printf ("\n==== Analyse Structure arbre ====\n") ;

  int feuilles = 0;
  int noeud2 = 0;
  int noeud3 = 0;
  int noeud4 = 0;

  AnalyseStructureArbre(a, &feuilles, &noeud2, &noeud3, &noeud4);
  
  printf("Analyse de la structure de l'arbre : %d feuilles, %d 2-noeud, %d 3-noeud, %d 4-noeud\n", feuilles, noeud2, noeud3, noeud4);

  printf ("\n==== Max noeud arbre ====\n") ;
  
  printf("Noeud maximum de l'arbre : \n");
  afficher_arbre (noeud_max(a), 0) ;

  printf ("\n==== Liste clé largeur arbre ====\n") ;
  
  printf("Parcours en largeur de l'arbre : \n");
  Afficher_Cles_Largeur (a) ; printf("\n");

  printf ("\n==== Liste clé triée récursive arbre ====\n") ;
  
  printf("Liste des clés triées récursivement de l'arbre : \n");
  Affichage_Cles_Triees_Recursive (a) ; printf("\n");

  printf ("\n==== Liste clé triée non-récursive arbre ====\n") ;
  
  printf("Liste des clés triées non-récursivement de l'arbre : \n");
  Affichage_Cles_Triees_NonRecursive (a) ; printf("\n");

  printf ("\n==== Détruire Clé arbre ====\n") ;
  
  printf("Détruire la clé 1 dans l'arbre : \n"); 
  Detruire_Cle(&a, 1);
  afficher_arbre (a, 0) ;
  printf("Détruire la clé 7 dans l'arbre : \n"); 
  Detruire_Cle(&a, 7);
  afficher_arbre (a, 0) ;
  printf("Détruire la clé 8 dans l'arbre : \n"); 
  Detruire_Cle(&a, 8);
  afficher_arbre (a, 0) ;
  // printf("\nDétruire la clé 12 dans l'arbre : \n\n"); 
  // Detruire_Cle(&a, 12);
  // afficher_arbre (a, 0) ;
  // printf("\nDétruire la clé 15 dans l'arbre : \n"); 
  // Detruire_Cle(&a, 15);
  // afficher_arbre (a, 0) ;
  // printf("\nDétruire la clé 11 dans l'arbre : \n\n"); 
  // Detruire_Cle(&a, 11);
  // afficher_arbre (a, 0) ;
  // printf("\nDétruire la clé 3 dans l'arbre : \n"); 
  // Detruire_Cle(&a, 3);
  // afficher_arbre (a, 0) ;
  // printf("\nDétruire la clé 9 dans l'arbre : \n"); 
  // Detruire_Cle(&a, 9);
  // afficher_arbre (a, 0) ;

}
