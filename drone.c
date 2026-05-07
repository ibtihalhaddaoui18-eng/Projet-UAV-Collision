#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "drone.h"

float distanceCarree(Drone *a, Drone *b)
{
    float dx;
    float dy;
    float dz;

    dx = a->x - b->x;
    dy = a->y - b->y;
    dz = a->z - b->z;

    return dx * dx + dy * dy + dz * dz;
}

float calculerDistance(Drone *a, Drone *b)
{
    return sqrt(distanceCarree(a, b));
}

void initialiserDrones(Drone *essaim, int nombre)
{
    Drone *p;
    int i;

    p = essaim;

    for (i = 0; i < nombre; i++)
    {
        (p + i)->id = i + 1;
        (p + i)->x = (float)(rand() % 10000);
        (p + i)->y = (float)(rand() % 10000);
        (p + i)->z = (float)(rand() % 10000);
    }
}

void afficherDrones(Drone *essaim, int nombre)
{
    Drone *p;
    int i;

    p = essaim;

    for (i = 0; i < nombre; i++)
    {
        printf("Drone %d : X = %.2f | Y = %.2f | Z = %.2f\n",
               (p + i)->id,
               (p + i)->x,
               (p + i)->y,
               (p + i)->z);
    }
}

int comparerSelonX(const void *a, const void *b)
{
    Drone *d1;
    Drone *d2;

    d1 = (Drone *)a;
    d2 = (Drone *)b;

    if (d1->x < d2->x)
    {
        return -1;
    }

    if (d1->x > d2->x)
    {
        return 1;
    }

    return 0;
}

int comparerPointeursSelonY(const void *a, const void *b)
{
    Drone *d1;
    Drone *d2;

    d1 = *(Drone **)a;
    d2 = *(Drone **)b;

    if (d1->y < d2->y)
    {
        return -1;
    }

    if (d1->y > d2->y)
    {
        return 1;
    }

    return 0;
}

ResultatCollision resultatVide()
{
    ResultatCollision r;

    r.drone1 = NULL;
    r.drone2 = NULL;
    r.distance = 0.0f;

    return r;
}

ResultatCollision meilleurResultat(ResultatCollision r1, ResultatCollision r2)
{
    if (r1.drone1 == NULL)
    {
        return r2;
    }

    if (r2.drone1 == NULL)
    {
        return r1;
    }

    if (r1.distance < r2.distance)
    {
        return r1;
    }

    return r2;
}

ResultatCollision rechercheBruteLocale(Drone *debut, int nombre)
{
    Drone *a;
    Drone *b;

    ResultatCollision meilleur;
    float distanceActuelle;
    int premierCalcul;

    meilleur = resultatVide();
    premierCalcul = 1;

    for (a = debut; a < debut + nombre; a++)
    {
        for (b = a + 1; b < debut + nombre; b++)
        {
            distanceActuelle = calculerDistance(a, b);

            if (premierCalcul || distanceActuelle < meilleur.distance)
            {
                meilleur.drone1 = a;
                meilleur.drone2 = b;
                meilleur.distance = distanceActuelle;
                premierCalcul = 0;
            }
        }
    }

    return meilleur;
}

ResultatCollision rechercheRecursive(Drone *debut, int nombre)
{
    int milieu;
    int i;
    int j;
    int tailleBande;

    float xMilieu;
    float ecartX;
    float ecartY;
    float ecartZ;
    float distanceActuelle;

    Drone **bande;

    ResultatCollision gauche;
    ResultatCollision droite;
    ResultatCollision meilleur;

    if (nombre < 2)
    {
        return resultatVide();
    }

    if (nombre <= 3)
    {
        return rechercheBruteLocale(debut, nombre);
    }

    milieu = nombre / 2;
    xMilieu = (debut + milieu)->x;

    gauche = rechercheRecursive(debut, milieu);
    droite = rechercheRecursive(debut + milieu, nombre - milieu);

    meilleur = meilleurResultat(gauche, droite);

    bande = (Drone **)malloc(nombre * sizeof(Drone *));

    if (bande == NULL)
    {
        return meilleur;
    }

    tailleBande = 0;

    for (i = 0; i < nombre; i++)
    {
        ecartX = fabs((debut + i)->x - xMilieu);

        if (ecartX < meilleur.distance)
        {
            *(bande + tailleBande) = debut + i;
            tailleBande++;
        }
    }

    qsort(bande, tailleBande, sizeof(Drone *), comparerPointeursSelonY);

    for (i = 0; i < tailleBande; i++)
    {
        j = i + 1;

        while (j < tailleBande)
        {
            ecartY = fabs((*(bande + j))->y - (*(bande + i))->y);

            if (ecartY >= meilleur.distance)
            {
                break;
            }

            ecartZ = fabs((*(bande + j))->z - (*(bande + i))->z);

            if (ecartZ < meilleur.distance)
            {
                distanceActuelle = calculerDistance(*(bande + i), *(bande + j));

                if (distanceActuelle < meilleur.distance)
                {
                    meilleur.drone1 = *(bande + i);
                    meilleur.drone2 = *(bande + j);
                    meilleur.distance = distanceActuelle;
                }
            }

            j++;
        }
    }

    free(bande);

    return meilleur;
}

ResultatCollision trouverDronesPlusProches(Drone *essaim, int nombre)
{
    qsort(essaim, nombre, sizeof(Drone), comparerSelonX);

    return rechercheRecursive(essaim, nombre);
}
