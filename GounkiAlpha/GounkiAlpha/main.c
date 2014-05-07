//
//  main.c
//  GounkiAlpha
//
//  Created by Etienne Toussaint on 26/03/2014.
//  Copyright (c) 2014 Etienne Toussaint. All rights reserved.
//

#include <stdio.h>
#include "Pion.h"
#include "Grille.h"

int main(int argc, const char * argv[])
{
    pion ** grille=initGrille();
    int y0 = grille[0][0].type;
    int x0= coupValide(grille, "a1-b7-c4",'A');
    printf("%d",y0);
    return 0;
}

