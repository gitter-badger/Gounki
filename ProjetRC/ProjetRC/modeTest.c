//
//  modeTest.c
//  ProjetRC
//
//  Created by Etienne Toussaint on 10/05/2014.
//  Copyright (c) 2014 Etienne Toussaint. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "modeTest.h"

void modeTest(char * name){
    //char * nameb = "test.txt";
    initMap();
    char joueur='A';
    int i;
    struct pion ** grille = initGrille();
    char *coup=malloc(sizeof(char)*13);
    FILE * fichier = fopen("test.txt", "r");
    coup = fgets(coup, 13, fichier);
    //coup[strlen(coup)-1]=0;
    
    do{
        if(coup[strlen(coup)-1]=='\n')coup[strlen(coup)-1]=0;
        updateMap(grille);
        affiche();
        struct coup * pere;
        pere = malloc(sizeof(struct coup));
        pere->proto = NULL;
        pere->coupSuivant = NULL;
        pere = coupsPossibles(grille, joueur,pere);
        coup = correrction(grille, coup, pere);
        printf("%s\n",coup);
        if(action(grille,coup,pere,1)==-1){
            printf("mauvais coup : %s\n" ,coup);
            free(coup);
            freeGrille(grille);
            freeCoup(pere, 1);
            exit(1);
        }
        if(joueur == 'A')joueur = 'B';
        else joueur = 'A';
        freeCoup(pere, 1);
    }while (fgets(coup, 13, fichier) != NULL);
    freeMap();
    updateMap(grille);
    affiche();
    free(coup);
    freeGrille(grille);
}