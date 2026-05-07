#ifndef DRONE_H
#define DRONE_H

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

void initialiserDrones(Drone *essaim, int nombre);
void afficherDrones(Drone *essaim, int nombre);
float calculerDistance(Drone *a, Drone *b);
ResultatCollision trouverDronesPlusProches(Drone *essaim, int nombre);

#endif
