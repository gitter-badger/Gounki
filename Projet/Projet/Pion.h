//
//  Pion.h
//  Projet
//
//  Created by Etienne Toussaint on 26/03/2014.
//  Copyright (c) 2014 Etienne Toussaint. All rights reserved.
//

#ifndef Projet_Pion_h
#include <stdio.h>
#include <stdlib.h>
#define Projet_Pion_h

typedef struct pion {
    int x;
    int y;
    char joueur;
    int type;
}pion;

pion initPion(int x,int y);
pion initRond(int x,int y,char joueur);
pion initCarre(int x,int y,char joueur);
int deplacementSimple(pion p, char joueur);
int deplacementDouble(pion p, char joueur);
int deplacementTriple(pion p, char joueur);
int deployment(pion p, char joueur);


#endif
