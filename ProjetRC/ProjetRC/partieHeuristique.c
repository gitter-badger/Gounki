//
//  partieHeuristique.c
//  ProjetRC
//
//  Created by Etienne Toussaint on 15/04/2014.
//  Copyright (c) 2014 Etienne Toussaint. All rights reserved.
//

#include "partieHeuristique.h"

void viderBufferc()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}


int partiH()
{
    
    int typeA = -1;
    int typeB = -1;
    printf("Choisiser l'IA de A \n0 pour l'IA standa\n1 pour l'IA aggresive\n2 pour l'IA defence\n3 pour l'IA bizzare\n");
    while (typeA<0||typeA>4) {
        scanf("%d", &typeA);
        viderBufferc();
    }
    printf("Choisiser l'IA de B \n0 pour l'IA standa\n1 pour l'IA aggresive\n2 pour l'IA defence\n3 pour l'IA bizzare\n");
    while (typeB<0||typeB>4) {
        scanf("%d", &typeB);
        viderBufferc();
    }
    
    srand(time(NULL));
    
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
                pere = calloc(1,sizeof(coup));
                pere->proto = NULL;
                pere->coupSuivant = NULL;
                pere = coupsPossibles(grille, 'A',pere);
                coup * coupPossible = pere;
                int n = 0;
                int i = 0;
                int max = calculHeuristiqueCoups(pere, grille,'A',typeA);
                
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
                    //printf("efef");
                    a++;
                    victoire = 1;
                    break;
                    //printf("a");
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
                int max = calculHeuristiqueCoups(pere, grille,'B',typeB);
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
                    //printf("b");
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
        //printf("%d",t);
        freeGrille(grille);
        freeMap();
        
    }
    printf("a=%d,b=%d\n",a,b);
    return 0;
}

int jouerCoupIA(pion ** grille, char joueur,int  difficulter,int testIA, int ad,int type){
    coup * pere;
    pere = calloc(1,sizeof(coup));
    pere->proto = NULL;
    pere->coupSuivant = NULL;
    pere = coupsPossibles(grille, joueur,pere);
    coup * coupPossible = pere;
    int n = 0;
    int i = 0;
    int max;
    if(difficulter == 0)max = calculHeuristiqueCoups(pere, grille,joueur,type);
    else max = calculHeuristiqueCoupsMultiples(pere, grille,joueur,difficulter,type);
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
    if(ad)setAdvice(coupPossible->proto);
    if(!testIA)printf("\n%s\n",coupPossible->proto);
    if(action(grille, coupPossible->proto, pere,1)==1)return 1;
    
    freeCoup(pere,1);
    freeCoup(coupHeuri,0);
    //updateMap(grille);
    //affiche();
    return 0;
}
