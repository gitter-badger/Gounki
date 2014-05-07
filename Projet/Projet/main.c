//
//  main.c
//  Projet
//
//  Created by Etienne Toussaint on 26/03/2014.
//  Copyright (c) 2014 Etienne Toussaint. All rights reserved.
//

#include <stdio.h>
#include "Grille.h"
#include "Pion.h"
#include "test.h"

int main(int argc, const char * argv[])
{
    initMap();
    affiche();
    pion ** grille = initGrille();
    grille[0][1].type = 9;
    coup * pere = coupsPossibles(grille, 'A');
    coup * coupPossible = pere;
    
    while (coupPossible != NULL) {
        printf("%s\n",coupPossible->proto);
        coupPossible = coupPossible->coupSuivant;
    }
    initMap();
    updateMap(grille);
    affiche();
    grille = action(grille, "a7-a6");
    updateMap(grille);
    affiche();
    printf("%d",grille[0][6].type);
    return 0;
}

