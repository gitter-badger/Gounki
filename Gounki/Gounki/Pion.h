//
//  Pion.h
//  Gounki
//
//  Created by Etienne Toussaint on 22/03/2014.
//  Copyright (c) 2014 Etienne Toussaint. All rights reserved.
//

#ifndef Gounki_Pion_h
#include <stdio.h>
#include <stdlib.h>
#define Gounki_Pion_h


typedef struct pion {
    int x;
    int y;
    char joueur;
    int type;
}pion;

pion initPion(int x,int y);
pion initRond(int x,int y,char joueur);
pion initCarre(int x,int y,char joueur);



#endif
