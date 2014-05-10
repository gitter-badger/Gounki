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
    
    for (t=0; t<200; t++) {
        
        victoire = 0;
        initMap();
        pion ** grille = initGrille();
        //affiche();
        
        
        while (!victoire) {
            
            {
                static int f =0;
                f ++;
                coup * pere;
                pere = calloc(1,sizeof(coup));
                pere->proto = NULL;
                pere->coupSuivant = NULL;
                pere = coupsPossibles(grille, 'A',pere);
                coup * coupPossible = pere;
                int n = 0;
                int i = 0;
                int max = calculHeuristiqueCoupsMultiples(pere, grille,'A',1);
                
                coupPossible = pere;
                coup *coupHeuri = calloc(1,sizeof(coup));
                coupHeuri->proto = NULL;
                coupHeuri->coupSuivant = NULL;
                coup *coupActuelle = coupHeuri;
                while (coupPossible != NULL){
                    if(coupPossible->heuristique == max){
                        n++;
                        coup * coupSuivant = calloc(1,sizeof(coup)); coupSuivant->proto = NULL;coupSuivant->coupSuivant= NULL;
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
                if(action(grille, coupPossible->proto, pere,1)==1){
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
                pere = calloc(1,sizeof(coup));
                pere->proto = NULL;
                pere->coupSuivant = NULL;
                pere = coupsPossibles(grille, 'B',pere);
                coup * coupPossible = pere;
                int n = 0;
                int i = 0;
                int max = calculHeuristiqueCoups(pere, grille,'B');
                coupPossible = pere;
                coup *coupHeuri = calloc(1,sizeof(coup));
                coupHeuri->proto = NULL;
                coupHeuri->coupSuivant = NULL;
                coup *coupActuelle = coupHeuri;
                while (coupPossible != NULL){
                    if(coupPossible->heuristique == max){
                        n++;
                        coup * coupSuivant = calloc(1,sizeof(coup)); coupSuivant->proto = NULL;coupSuivant->coupSuivant= NULL;
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
                if(action(grille, coupPossible->proto, pere,1)==1){
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

int jouerCoupIA(pion ** grille, char joueur,int  difficulter,int testIA){
    coup * pere;
    pere = calloc(1,sizeof(coup));
    pere->proto = NULL;
    pere->coupSuivant = NULL;
    pere = coupsPossibles(grille, joueur,pere);
    coup * coupPossible = pere;
    int n = 0;
    int i = 0;
    int max;
    if(difficulter == 0)max = calculHeuristiqueCoups(pere, grille,joueur);
    else max = calculHeuristiqueCoupsMultiples(pere, grille,joueur,difficulter);
    coupPossible = pere;
    coup *coupHeuri = calloc(1,sizeof(coup));
    coupHeuri->proto = NULL;
    coupHeuri->coupSuivant = NULL;
    coup *coupActuelle = coupHeuri;
    while (coupPossible != NULL){
        if(coupPossible->heuristique == max){
            n++;
            coup * coupSuivant = calloc(1,sizeof(coup)); coupSuivant->proto = NULL;coupSuivant->coupSuivant= NULL;
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
    //setAdvice(coupPossible->proto);
    if(!testIA)printf("\n%s\n",coupPossible->proto);
    if(action(grille, coupPossible->proto, pere,1)==1)return 1;
    
    freeCoup(pere,1);
    freeCoup(coupHeuri,0);
    //updateMap(grille);
    //affiche();
    return 0;
}
