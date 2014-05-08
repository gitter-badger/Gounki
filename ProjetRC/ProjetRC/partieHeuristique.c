//
//  partieHeuristique.c
//  ProjetRC
//
//  Created by Etienne Toussaint on 15/04/2014.
//  Copyright (c) 2014 Etienne Toussaint. All rights reserved.
//

#include "partieHeuristique.h"



int partiH()
{
    srand(time(NULL));
    
    FILE * fichier = fopen("/Users/Toussaint/Documents/Cours/LC4/test.txt", "w");
    int victoire = 0;
    int t = 0;
    int a=0;
    int b = 0;
    
    for (t=0; t<2000; t++) {
        
        victoire = 0;
        initMap();
        pion ** grille = initGrille();
        //affiche();
        
        
        while (!victoire) {
            
            {
                static int f =0;
                f ++;
                coup * pere;
                pere = malloc(sizeof(coup));
                pere->proto = NULL;
                pere->coupSuivant = NULL;
                pere = coupsPossibles(grille, 'A',pere);
                coup * coupPossible = pere;
                int n = 0;
                int i = 0;
                int max = -100000;
                while (coupPossible != NULL) {
                    coupPossible->heuristique = heuristiques(grille, coupPossible, 'A');
                    if(coupPossible->heuristique > max) max = coupPossible->heuristique;
                    //printf("%s|%d\n",coupPossible->proto,coupPossible->heuristique);
                    coupPossible = coupPossible->coupSuivant;
                }
                
                
                coupPossible = pere;
                coup *coupHeuri = malloc(sizeof(coup));
                coupHeuri->proto = NULL;
                coupHeuri->coupSuivant = NULL;
                coup *coupActuelle = coupHeuri;
                while (coupPossible != NULL){
                    if(coupPossible->heuristique == max){
                        n++;
                        coup * coupSuivant = malloc(sizeof(coup)); coupSuivant->proto = NULL;coupSuivant->coupSuivant= NULL;
                        coupActuelle->proto = coupPossible->proto;
                        coupActuelle->heuristique =coupPossible->heuristique;
                        coupActuelle->coupSuivant = coupSuivant;
                        coupActuelle = coupSuivant;
                    }
                    coupPossible = coupPossible->coupSuivant;
                }
                
                
                int choix = (rand()%n);
                //i = 0;
                coupPossible = coupHeuri;
                
                for (i=0; i<choix; i++) {
                    coupPossible = coupPossible->coupSuivant;
                }
                
                
                
                //printf("\n%s\n",coupPossible->proto);
                if(action(grille, coupPossible->proto, pere)==1){
                    printf("efef");
                    a++;
                    victoire = 1;
                    break;
                }
                
                freeCoup(pere,1);
                freeCoup(coupHeuri,0);
                updateMap(grille);
                //affiche();
            }
            {
                coup * pere;
                pere = malloc(sizeof(coup));
                pere->proto = NULL;
                pere->coupSuivant = NULL;
                pere = coupsPossibles(grille, 'B',pere);
                coup * coupPossible = pere;
                int n = 0;
                int i = 0;
                int max = -1000000;
                while (coupPossible != NULL) {
                    coupPossible->heuristique = heuristiques(grille, coupPossible, 'B');
                    if(coupPossible->heuristique > max) max = coupPossible->heuristique;
                    //printf("%s|%d\n",coupPossible->proto,coupPossible->heuristique);
                    coupPossible = coupPossible->coupSuivant;
                }
                coupPossible = pere;
                coup *coupHeuri = malloc(sizeof(coup));
                coupHeuri->proto = NULL;
                coupHeuri->coupSuivant = NULL;
                coup *coupActuelle = coupHeuri;
                while (coupPossible != NULL){
                    if(coupPossible->heuristique == max){
                        n++;
                        coup * coupSuivant = malloc(sizeof(coup)); coupSuivant->proto = NULL;coupSuivant->coupSuivant= NULL;
                        coupActuelle->proto = coupPossible->proto;
                        coupActuelle->heuristique =coupPossible->heuristique;
                        coupActuelle->coupSuivant = coupSuivant;
                        coupActuelle = coupSuivant;
                    }
                        coupPossible = coupPossible->coupSuivant;
                }
                int choix = (rand()%n);
                i = 0;
                coupPossible = coupHeuri;
                
                for (i=0; i<choix; i++) {
                    coupPossible = coupPossible->coupSuivant;
                }
                
                //printf("\n%s\n",coupPossible->proto);
                if(action(grille, coupPossible->proto, pere)==1){
                    printf("efef");
                    b++;
                    victoire = 1;
                    break;
                }
                
                freeCoup(pere,1);
                freeCoup(coupHeuri,0);
                updateMap(grille);
                //affiche();
            }
            
        }
        printf("%d",t);
        freeGrille(grille);
        freeMap();
        
    }
    fprintf(fichier,"a=%d,b=%d",a,b);
    fclose(fichier);
    return 0;
}

void jouerCoupIA(pion ** grille, char joueur){
    coup * pere;
    pere = malloc(sizeof(coup));
    pere->proto = NULL;
    pere->coupSuivant = NULL;
    pere = coupsPossibles(grille, joueur,pere);
    coup * coupPossible = pere;
    int n = 0;
    int i = 0;
    int max = -1000000;
    while (coupPossible != NULL) {
        coupPossible->heuristique = heuristiques(grille, coupPossible, joueur);
        if(coupPossible->heuristique > max) max = coupPossible->heuristique;
        //printf("%s|%d\n",coupPossible->proto,coupPossible->heuristique);
        coupPossible = coupPossible->coupSuivant;
    }
    coupPossible = pere;
    coup *coupHeuri = malloc(sizeof(coup));
    coupHeuri->proto = NULL;
    coupHeuri->coupSuivant = NULL;
    coup *coupActuelle = coupHeuri;
    while (coupPossible != NULL){
        if(coupPossible->heuristique == max){
            n++;
            coup * coupSuivant = malloc(sizeof(coup)); coupSuivant->proto = NULL;coupSuivant->coupSuivant= NULL;
            coupActuelle->proto = coupPossible->proto;
            coupActuelle->heuristique =coupPossible->heuristique;
            coupActuelle->coupSuivant = coupSuivant;
            coupActuelle = coupSuivant;
        }
        coupPossible = coupPossible->coupSuivant;
    }
    int choix = (rand()%n);
    i = 0;
    coupPossible = coupHeuri;
    
    for (i=0; i<choix; i++) {
        coupPossible = coupPossible->coupSuivant;
    }
    
    printf("\n%s\n",coupPossible->proto);
    action(grille, coupPossible->proto, pere);
    
    freeCoup(pere,1);
    freeCoup(coupHeuri,0);
    //updateMap(grille);
    //affiche();
}
