//
//  main.c
//  Gounki
//
//  Created by Etienne Toussaint on 19/03/2014.
//  Copyright (c) 2014 Etienne Toussaint. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "Grille.h"

int main(int argc, const char * argv[])
{
    pion ** grille;
    grille =  initGrille();
    coup * test = malloc(sizeof(coup));
    test = coupsPossibles(grille,'A');
    printf("%s",test->coupSuivant->proto);
    
    return 0;
}

