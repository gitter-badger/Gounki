//
//  Pion.c
//  Gounki
//
//  Created by Etienne Toussaint on 22/03/2014.
//  Copyright (c) 2014 Etienne Toussaint. All rights reserved.
//


#import "Grille.h"

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

