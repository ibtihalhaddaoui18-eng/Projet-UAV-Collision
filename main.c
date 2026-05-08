#include "drone.h"
int main()
{
    Drone *essaim;
    ResultatCollision resultat;
    clock_t debut;
    clock_t fin;
    double temps;
    srand((unsigned int)time(NULL));
    /* Allocation dynamique du tableau de drones */
    essaim = (Drone *)malloc(NOMBRE_DRONES * sizeof(Drone));
    if (essaim == NULL)
    {
        printf("Erreur : allocation memoire impossible.\n");
        return 1;
    }
    initialiserDrones(essaim, NOMBRE_DRONES);
    printf("=== SYSTEME DE DETECTION DE COLLISION UAV ===\n\n");
    printf("Nombre total de drones : %d\n\n", NOMBRE_DRONES);
    printf("Apercu des 5 premiers drones :\n");
    afficherDrones(essaim, 5);
    debut = clock();
    resultat = chercherPlusProches(essaim, NOMBRE_DRONES);
    fin = clock();
    temps = ((double)(fin - debut)) / CLOCKS_PER_SEC;
    printf("\n=== RESULTAT DE DETECTION ===\n");
    if (resultat.drone1 != NULL && resultat.drone2 != NULL)
    {
        printf("Drone 1 : ID %d | X = %.2f | Y = %.2f | Z = %.2f\n",
               resultat.drone1->id,
               resultat.drone1->x,
               resultat.drone1->y,
               resultat.drone1->z);
        printf("Drone 2 : ID %d | X = %.2f | Y = %.2f | Z = %.2f\n",
               resultat.drone2->id,
               resultat.drone2->x,
               resultat.drone2->y,
               resultat.drone2->z);
        printf("\nDistance minimale : %.4f\n", resultat.distance);
        printf("Temps d'execution : %.6f secondes\n", temps);
    }
    else
    {
        printf("Aucun resultat trouve.\n");
    }
    /* Liberation de la memoire et remise du pointeur a NULL */
    free(essaim);
    essaim = NULL;
    printf("\nAppuyez sur Entree pour fermer...");
    getchar();
    return 0;  
}
