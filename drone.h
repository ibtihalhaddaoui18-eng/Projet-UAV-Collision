#ifndef DRONE_H
#define DRONE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <time.h>

#define NOMBRE_DRONES 10000

typedef struct
{
    int id;
    float x;
    float y;
    float z;

} Drone;

typedef struct
{
    Drone *drone1;
    Drone *drone2;
    float distance;

} ResultatCollision;

void initialiserDrones(Drone *essaim, int n);
void afficherDrones(Drone *essaim, int n);
float distanceDrone(Drone *a, Drone *b);
ResultatCollision chercherPlusProches(Drone *essaim, int n);

#endif
