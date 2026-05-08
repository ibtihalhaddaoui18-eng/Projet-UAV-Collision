#include "drone.h"

void initialiserDrones(Drone *essaim, int n)
{
    Drone *curseur;
    int i;

    curseur = essaim;

    for (i = 0; i < n; i++)
    {
        curseur->id = i + 1;
        curseur->x = (float)(rand() % 10000);
        curseur->y = (float)(rand() % 10000);
        curseur->z = (float)(rand() % 10000);

        curseur++;
    }
}

void afficherDrones(Drone *essaim, int n)
{
    Drone *curseur;
    int i;

    curseur = essaim;

    for (i = 0; i < n; i++)
    {
        printf("Drone %d : X = %.2f | Y = %.2f | Z = %.2f\n",
               curseur->id,
               curseur->x,
               curseur->y,
               curseur->z);

        curseur++;
    }
}

float distanceDrone(Drone *a, Drone *b)
{
    float dx;
    float dy;
    float dz;

    dx = a->x - b->x;
    dy = a->y - b->y;
    dz = a->z - b->z;

    return sqrt(dx * dx + dy * dy + dz * dz);
}

int comparerX(const void *a, const void *b)
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

int comparerPointeursY(const void *a, const void *b)
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

ResultatCollision creerResultatVide()
{
    ResultatCollision r;

    r.drone1 = NULL;
    r.drone2 = NULL;
    r.distance = FLT_MAX;

    return r;
}

ResultatCollision meilleurResultat(ResultatCollision r1, ResultatCollision r2)
{
    if (r1.distance < r2.distance)
    {
        return r1;
    }

    return r2;
}

ResultatCollision rechercheNaiveLocale(Drone *debut, int n)
{
    Drone *a;
    Drone *b;
    ResultatCollision meilleur;
    float d;

    meilleur = creerResultatVide();

    for (a = debut; a < debut + n; a++)
    {
        for (b = a + 1; b < debut + n; b++)
        {
            d = distanceDrone(a, b);

            if (d < meilleur.distance)
            {
                meilleur.drone1 = a;
                meilleur.drone2 = b;
                meilleur.distance = d;
            }
        }
    }

    return meilleur;
}

ResultatCollision rechercheRecursive(Drone *debut, int n)
{
    int milieu;
    int i;
    int j;
    int tailleBande;

    float xMilieu;
    float ecartX;
    float ecartY;
    float distanceActuelle;

    Drone **bande;

    ResultatCollision gauche;
    ResultatCollision droite;
    ResultatCollision meilleur;

    if (n <= 3)
    {
        return rechercheNaiveLocale(debut, n);
    }

    milieu = n / 2;
    xMilieu = (debut + milieu)->x;

    gauche = rechercheRecursive(debut, milieu);
    droite = rechercheRecursive(debut + milieu, n - milieu);

    meilleur = meilleurResultat(gauche, droite);

    bande = (Drone **)malloc(n * sizeof(Drone *));

    if (bande == NULL)
    {
        printf("Erreur : allocation de la bande centrale impossible.\n");
        exit(1);
    }

    tailleBande = 0;

    for (i = 0; i < n; i++)
    {
        ecartX = fabs((debut + i)->x - xMilieu);

        if (ecartX < meilleur.distance)
        {
            *(bande + tailleBande) = debut + i;
            tailleBande++;
        }
    }

    qsort(bande, tailleBande, sizeof(Drone *), comparerPointeursY);

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

            distanceActuelle = distanceDrone(*(bande + i), *(bande + j));

            if (distanceActuelle < meilleur.distance)
            {
                meilleur.drone1 = *(bande + i);
                meilleur.drone2 = *(bande + j);
                meilleur.distance = distanceActuelle;
            }

            j++;
        }
    }

    free(bande);

    return meilleur;
}

ResultatCollision chercherPlusProches(Drone *essaim, int n)
{
    qsort(essaim, n, sizeof(Drone), comparerX);

    return rechercheRecursive(essaim, n);
}

