//
//  heuristique.c
//  ProjetRC
//
//  Created by Etienne Toussaint on 15/04/2014.
//  Copyright (c) 2014 Etienne Toussaint. All rights reserved.
//

#include <stdio.h>
#include "heuristique.h"
#include <string.h>

#define HEURISTIQUE_TEST 0.5;
#define HEURISTIQUE_ARMEE 3;
#define HEURISTIQUE_PERCEE 0.5;
#define HEURISTIQUE_DEFENSE 1;
#define min(a, b)       ((a) < (b) ? (a) : (b))
#define max(a, b)       ((a) < (b) ? (b) : (a))

int heuristiques (pion** grille,coup* coup,char joueur){
    int maxY=0;
    int minY=7;
    int resultat = 0;
    
    pion** grilleCpy = malloc(sizeof(pion *)*8);
    int x = 0,y=0;
    for (x=0; x<8; x++) {
        *(grilleCpy+x) = malloc(sizeof(pion)*8);
        for (y=0; y<8; y++) {
            *(*(grilleCpy+x)+y) = grille[x][y];
        }
    }
    if (coup->proto == NULL) {
        freeGrille(grilleCpy);
        return -9999;
    }
    if ( coup->proto!=  NULL && coup->proto[2]=='#') {
        freeGrille(grilleCpy);
        return 9999;
    }
    else if (coup->proto != NULL && coup->proto != 0 )  action(grilleCpy, coup->proto,coup);
    x =0,y=0;
    for (x=0; x<8; x++) {
        for (y=0; y<8; y++) {
            if(grilleCpy[x][y].joueur == 'A')maxY= max(maxY,y);
            else if(grilleCpy[x][y].joueur == 'B') minY=min(minY,y);
            if(joueur == 'A')resultat += (grilleCpy[x][y].joueur == joueur ? grilleCpy[x][y].type : -grilleCpy[x][y].type)*HEURISTIQUE_ARMEE;
            if(joueur == 'B')resultat += (grilleCpy[x][y].joueur == joueur ? grilleCpy[x][y].type : -grilleCpy[x][y].type)*HEURISTIQUE_ARMEE;
            
        }
    }
    if(joueur == 'A')resultat+=maxY*HEURISTIQUE_TEST;
    if(joueur == 'B')resultat+=(7-minY)*HEURISTIQUE_PERCEE;
    if(joueur == 'A')resultat-=(7-minY)*HEURISTIQUE_DEFENSE;
    if(joueur == 'B')resultat-=(maxY)*HEURISTIQUE_DEFENSE;
    
    freeGrille(grilleCpy);
    return resultat;
}
