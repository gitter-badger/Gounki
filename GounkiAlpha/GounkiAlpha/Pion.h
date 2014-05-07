//
//  Pion.h
//  GounkiAlpha
//
//  Created by Etienne Toussaint on 26/03/2014.
//  Copyright (c) 2014 Etienne Toussaint. All rights reserved.
//

#ifndef GounkiAlpha_Pion_h
#define GounkiAlpha_Pion_h

typedef struct pion {
    int x;
    int y;
    char joueur;
    int type;
}pion;

int deplacement(pion p, char joueur);
int deployment(pion p, char joueur);
pion initPion(int x,int y);
pion initRond(int x,int y,char joueur);
pion initCarre(int x,int y,char joueur);
#endif
