#ifndef DRONE_H
#define DRONE_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <time.h>
#define NOMBRE_DRONES 10000
/* Structure representant un drone dans l'espace 3D */
typedef struct
{
    int id;
    float x;
    float y;
    float z;
} Drone;
/* Structure contenant le resultat de la detection de collision */
typedef struct
{
    Drone *drone1;
    Drone *drone2;
    float distance;
} ResultatCollision;
/* Fonctions principales */
void initialiserDrones(Drone *essaim, int n);
void afficherDrones(Drone *essaim, int n);
float distanceDrone(Drone *a, Drone *b);
ResultatCollision chercherPlusProches(Drone *essaim, int n);
/* Fonctions internes utilisees par l'algorithme */
int comparerX(const void *a, const void *b);
int comparerPointeursY(const void *a, const void *b);
ResultatCollision creerResultatVide(void);
ResultatCollision meilleurResultat(ResultatCollision r1, ResultatCollision r2);
ResultatCollision rechercheNaiveLocale(Drone *debut, int n);
ResultatCollision rechercheRecursive(Drone *debut, int n);
#endif
