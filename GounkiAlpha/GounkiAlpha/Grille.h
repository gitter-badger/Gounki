//
//  Grille.h
//  GounkiAlpha
//
//  Created by Etienne Toussaint on 26/03/2014.
//  Copyright (c) 2014 Etienne Toussaint. All rights reserved.
//

#ifndef GounkiAlpha_Grille_h
#include "Pion.h"
#define GounkiAlpha_Grille_h

typedef struct coup {
    char * proto;
    struct coup* coupSuivant;
}coup;

pion ** initGrille();
pion * coupsValides(pion** grille,char joueur);

#endif
