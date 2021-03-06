//
//  Pion.c
//  GounkiAlpha
//
//  Created by Etienne Toussaint on 26/03/2014.
//  Copyright (c) 2014 Etienne Toussaint. All rights reserved.
//

#include <stdio.h>
#include "Pion.h"

int deplacement(pion p, char joueur){
    return (p.joueur != joueur || p.type<5 || p.type ==7)?1:0;
}

int deployment(pion p, char joueur){
    return ((p.joueur == joueur && (p.type<5 || p.type ==7))|| p.joueur == 'V')?1:0;
}

pion initPion(int x, int y){
    pion newPion;
    newPion.x = x;
    newPion.y=y;
    newPion.joueur='V';
    newPion.type=0;
    return newPion;
}

pion initRond(int x, int y,char joueur){
    pion newPion;
    newPion.x = x;
    newPion.y=y;
    newPion.joueur=joueur;
    newPion.type=2;
    return newPion;
}

pion initCarre(int x, int y,char joueur){
    pion newPion;
    newPion.x = x;
    newPion.y=y;
    newPion.joueur=joueur;
    newPion.type=1;
    return newPion;
}

