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

int heuristique_armee;
int heuristique_percee;
int heuristique_defense;

void setNormal(){
    heuristique_armee = 3;
    heuristique_percee = 0.5;
    heuristique_defense = 1;
}

void setRush(){
    heuristique_armee = 3;
    heuristique_percee = 2;
    heuristique_defense = 0.5;
}

void setBlock(){
    heuristique_armee = 3;
    heuristique_percee = 0.25;
    heuristique_defense = 2;
}

void setLoose(){
    heuristique_armee = 1;
    heuristique_percee = 1;
    heuristique_defense = 1;
}

int heuristiques (pion** grille,coup* coup,char joueur,int type){
    switch (type) {
        case 0:
            setNormal();
            break;
        case 1:
            setRush();
            break;
        case 2:
            setBlock();
            break;
        case 3:
            setLoose();
            break;
        default:
            setNormal();
            break;
    }
    
    int maxY=0;
    int minY=7;
    int resultat = 0;
    
    pion** grilleCpy = copieGrille(grille);
    
    if (coup->proto == NULL) {
        freeGrille(grilleCpy);
        return -9999;
    }
    if ( coup->proto!=  NULL && coup->proto[2]=='#') {
        freeGrille(grilleCpy);
        return 9999;
    }
    else if (coup->proto != NULL && coup->proto != 0 )  action(grilleCpy, coup->proto,coup,0);
    int x =0,y=0;
    for (x=0; x<8; x++) {
        for (y=0; y<8; y++) {
            if(grilleCpy[x][y].joueur == 'A')maxY= max(maxY,y);
            else if(grilleCpy[x][y].joueur == 'B') minY=min(minY,y);
            if(joueur == 'A')resultat += (grilleCpy[x][y].joueur == joueur ? grilleCpy[x][y].type : -grilleCpy[x][y].type)*heuristique_armee;
            if(joueur == 'B')resultat += (grilleCpy[x][y].joueur == joueur ? grilleCpy[x][y].type : -grilleCpy[x][y].type)*heuristique_armee;
            
        }
    }
    if(joueur == 'A')resultat+=maxY*heuristique_percee;
    if(joueur == 'B')resultat+=(7-minY)*heuristique_percee;
    if(joueur == 'A')resultat-=(7-minY)*heuristique_defense;
    if(joueur == 'B')resultat-=(maxY)*heuristique_defense;
    
    freeGrille(grilleCpy);
    return resultat;
}

int heuristiquesMultiple (pion** grille,coup* coup,char joueur,int profondeur,int type){
    profondeur --;
    pion** grilleCpy = copieGrille(grille);
    if (coup->proto == NULL) {
        freeGrille(grilleCpy);
        return -9999;
    }
    if ( coup->proto!=  NULL && coup->proto[2]=='#') {
        freeGrille(grilleCpy);
        return 9999;
    }
    else if (coup->proto != NULL && coup->proto != 0 )  action(grilleCpy, coup->proto,coup,0);
    
    
    char joueurTemp = joueur;
    if(joueurTemp == 'A')joueurTemp = 'B';
    else joueurTemp = 'A';
    
    if(jouerCoupIA(grilleCpy, joueurTemp,0,1,0,0)){
        freeGrille(grilleCpy);
        return -9998;
    }
    
    if(joueurTemp == 'A')joueurTemp = 'B';
    else joueurTemp = 'A';
    
    struct coup * pere;
    pere = calloc(1,sizeof(struct coup));
    pere->proto = NULL;
    pere->coupSuivant = NULL;
    pere = coupsPossibles(grilleCpy, joueurTemp,pere);
    int max = -9999;
    if(profondeur>0)max = calculHeuristiqueCoupsMultiples(pere, grilleCpy,joueurTemp,profondeur,type);
    else max = calculHeuristiqueCoups(pere, grilleCpy,joueurTemp,type);
    freeCoup(pere,1);
    freeGrille(grilleCpy);
    return max;
}

int calculHeuristiqueCoups(coup * pere, pion ** grille, char joueur,int type){
    int max = -1000000;
    coup * coupPossible = pere;
    while (coupPossible != NULL) {
        coupPossible->heuristique = heuristiques(grille, coupPossible, joueur,type);
        if(coupPossible->heuristique > max) max = coupPossible->heuristique;
        //printf("%s|%d\n",coupPossible->proto,coupPossible->heuristique);
        coupPossible = coupPossible->coupSuivant;
    }
    return max;
}
int calculHeuristiqueCoupsMultiples(coup * pere, pion ** grille, char joueur,int prodondeur,int type){
    int max = -1000000;
    coup * coupPossible = pere;
    while (coupPossible != NULL) {
        coupPossible->heuristique = heuristiquesMultiple(grille, coupPossible, joueur,prodondeur,type);
        if(coupPossible->heuristique > max) max = coupPossible->heuristique;
        //printf("%s|%d\n",coupPossible->proto,coupPossible->heuristique);
        coupPossible = coupPossible->coupSuivant;
    }
    return max;
}
