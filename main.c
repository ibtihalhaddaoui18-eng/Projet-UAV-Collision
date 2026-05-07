#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "drone.h"

#define NOMBRE_DRONES 10000

int main()
{
    Drone *essaim;
    ResultatCollision resultat;

    srand((unsigned int)time(NULL));

    essaim = (Drone *)malloc(NOMBRE_DRONES * sizeof(Drone));

    if (essaim == NULL)
    {
        printf("Erreur : allocation memoire impossible.\n");
        return 1;
    }

    initialiserDrones(essaim, NOMBRE_DRONES);

    printf("Systeme UAV initialise avec succes.\n");
    printf("Nombre total de drones : %d\n\n", NOMBRE_DRONES);

    printf("Affichage des 5 premiers drones :\n");
    afficherDrones(essaim, 5);

    resultat = trouverDronesPlusProches(essaim, NOMBRE_DRONES);

    printf("\nResultat de detection :\n");

    if (resultat.drone1 != NULL && resultat.drone2 != NULL)
    {
        printf("Drone 1 : ID %d\n", resultat.drone1->id);
        printf("Drone 2 : ID %d\n", resultat.drone2->id);
        printf("Distance minimale : %.4f\n", resultat.distance);
    }
    else
    {
        printf("Detection impossible.\n");
    }

    free(essaim);

    printf("\nAppuyez sur Entree pour fermer...");
    getchar();

    return 0;
}
