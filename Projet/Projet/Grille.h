//
//  Grille.h
//  Projet
//
//  Created by Etienne Toussaint on 26/03/2014.
//  Copyright (c) 2014 Etienne Toussaint. All rights reserved.
//

#ifndef Projet_Grille_h
#include <stdio.h>
#include <stdlib.h>
#import "pion.h"
#import <string.h>
#define Projet_Grille_h

typedef struct coup {
    char * proto;
    struct coup* coupSuivant;
}coup;

pion ** initGrille();
coup* coupsPossibles(pion** grilleActuelle,char joueur);
pion** action(pion ** grille ,char * proto);

#endif
