//
//  Conditions.h
//  GounkiAlpha
//
//  Created by Etienne Toussaint on 26/03/2014.
//  Copyright (c) 2014 Etienne Toussaint. All rights reserved.
//

#ifndef GounkiAlpha_Conditions_h
#include "Grille.h";
#include "Pion.h";
#include <stdlib.h>
#define GounkiAlpha_Conditions_h

static int*** constGeographique;
constGéographique[0] = {{0,0}};
constGéographique[1] = {{-1,0},{1,0},{0,-1},{0,1}};
constGéographique[2] = {{-1,-1},{1,1},{1,-1},{-1,1}};
constGéographique[3] = {{-2,0},{2,0},{0,-2},{0,2}};
constGéographique[4] = {{-2,-2},{2,2},{2,-2},{-2,2}};
constGéographique[5] = {{-3,0},{3,0},{0,-3},{0,3}};
constGéographique[6] = {{-3,-3},{3,3},{3,-3},{-3,3}};
#endif

