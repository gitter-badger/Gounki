//
//  heuristique.h
//  ProjetRC
//
//  Created by Etienne Toussaint on 15/04/2014.
//  Copyright (c) 2014 Etienne Toussaint. All rights reserved.
//

#ifndef ProjetRC_heuristique_h
#define ProjetRC_heuristique_h
#include "grille.h"
#include "pion.h"
#include "partieHeuristique.h"

//int heuristiques (pion** grille,coup* coup,char joueur);
int calculHeuristiqueCoups(coup * pere, pion ** grille, char joueur);
int calculHeuristiqueCoupsMultiples(coup * pere, pion ** grille, char joueur,int profondeur);

#endif
