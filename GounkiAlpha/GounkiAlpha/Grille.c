//
//  Grille.c
//  GounkiAlpha
//
//  Created by Etienne Toussaint on 26/03/2014.
//  Copyright (c) 2014 Etienne Toussaint. All rights reserved.
//

#include <stdio.h>
#include "Grille.h"
#include <stdlib.h>
#include "Conditions.h"

pion ** initGrille(){
    pion** grille = malloc(sizeof(pion *)*8);
    int x = 0,y=0;
    for (x=0; x<8; x++) {
        *(grille+x) = malloc(sizeof(pion)*8);
        for (y=0; y<8; y++) {
            if(y<2 && (x+y)%2==0) *(*(grille+x)+y) = initCarre(x,y,'A');
            else if (y<2 && (x+y)%2==0) *(*(grille+x)+y) = initRond(x,y,'A');
            else if(y>5 && (x+y)%2==0) *(*(grille+x)+y) = initCarre(x,y,'B');
            else if (y>5 && (x+y)%2==0) *(*(grille+x)+y) = initRond(x,y,'B');
            else *(*(grille+x)+y) = initPion(x,y);
        }
    }
    return grille;
}
int testBorne(int x,int y){
    if(x>7)return 0;
    if(y>7)return 0;
    if(x<0)return 0;
    if(y<0)return 0;
    return 1;
}

int accepteDeplacement(pion p,char joueur){
    if (p.joueur != joueur)return 1;
    if (p.type < 5 || p.type == 7)return 1;
    return 0;
}

int appartientPasConstGeo(int test[2], pion p){
    int type = p.type;
    int n = constGéographique[2]
    return 0;
}

int convertitX(char x){
    return (int)(x-97);
}
int convertitY(char y){
    return (int)(y-48);
}


int coupValide(pion** grille,char * proto,char joueur){
    //Déplacement
    int x0 = 0;
    int y0 = 0;
    if (!testBorne(x0,y0))return 0;
    if(grille[x0][y0].joueur != joueur) return 0;
    int x1 = 0;
    int y1 = 0;
    if(!testBorne(x1,y1))return 0;
    if(!accepteDeplacement(grille[x1][y1],joueur))return 0;
    
    int test[2] = {x1-x0,y1-y0};
    if (appartientPasConstGeo(test,grille[x0][y0])) {
        
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    return 1;
}