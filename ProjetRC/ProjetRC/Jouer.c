//
//  Jouer.c
//  Gounki
//
//  Created by andres quiroz on 30/04/2014.
//  Copyright (c) 2014 andres quiroz. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "Jouer.h"
//1=48,8=56
//a=97,h=104

int victoire = 0;

void setVictoire(int v){
    victoire = v;
}

void interaction(char * coup , pion ** grille , char joueur , int mode){
    fgets(coup, 13, stdin);
    int len = strlen(coup);
    coup[len-1]=0;
    if(!strcmp(coup, "save")){
        save(grille, joueur, mode);
    }
    else if(!strcmp(coup, "exit")){
        exit(1);
    }
    else if(!strcmp(coup, "help")){
        printf("Pour faire un déplacment : c2-d3\nPour faire un déploiement simple : c2+b2 pour les carrés\nPour faire un déploiement simple : c2*b3 pour les rond\nPour les deploiement composées c2*b3-b4 pour ce commencé par rond\nPour les deploiement composées c2+c3-b4 pour ce commencé par rond\n");
    }
}

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}
void jouer(){
    
    initMap();
    char joueur='A';
    int i;
    pion ** grille = initGrille();
    char *coup=malloc(sizeof(char)*13);
    for(i=0;i<13;i++){
        coup[i]=0;
    }
    
    int mode=0;
    printf("Bienvenue A Gounki\n");
    printf("Pour initier une nouvelle partie taper 1\nPour charger une partie taper 2 \n");
    while (mode==0) {
        scanf("%d", &mode);
        viderBuffer();
    }
    if(mode == 2){
        char * chargement = charger();
        mode = charToInt(chargement[0]);
        joueur = chargement[1];
        grille = grilleString(grille,chargement);
        free(chargement);
    }
    else mode = 0;
    
    if(mode == 0)printf("Pour jouer a deux taper 1\nPour jouer Contre l'IA taper 2 \nPour faire jouer deux IA taper 3\n");
    while (mode==0) {
        scanf("%d", &mode);
        viderBuffer();
    }
    if (mode==1) {
        //2 joueurs.
        //while (fonction victoir.)
        while (!victoire) {
            updateMap(grille);
            affiche();
            
            struct coup * pere;
            pere = malloc(sizeof(struct coup));
            pere->proto = NULL;
            pere->coupSuivant = NULL;
            
            
            pere = coupsPossibles(grille, joueur,pere);
            do {
                if(joueur == 'A'){
                    printf("\nJoueurs 1\n");
                }
                else{
                    printf("\nJoueurs 2\n");
                }
                interaction(coup,grille,joueur,mode);
            }
            while (action(grille, coup, pere)==-1);
            
            freeCoup(pere,1);
            
            if(joueur == 'A')joueur = 'B';
            else joueur = 'A';
        }
    }
    else if (mode==2) {
        int difficulter = -1;
        printf("Taper un nombre de 0 à 4 pour la difficulter \n");
        while (difficulter<0||difficulter>4) {
            scanf("%d", &difficulter);
            viderBuffer();
        }
        //Appelle fonction joueurs contre IA
            while (!victoire) {
                //while (fonction victoir.)
                if(joueur == 'A'){
                updateMap(grille);
                affiche();
                
                struct coup * pere;
                pere = malloc(sizeof(struct coup));
                pere->proto = NULL;
                pere->coupSuivant = NULL;
                pere = coupsPossibles(grille, 'A',pere);
                do {
                    printf("Joueurs 1\n");
                    interaction(coup, grille, joueur, mode);
                }
                while (action(grille, coup, pere)==-1);
                freeCoup(pere,1);
                    joueur = 'B';
                }
                if(joueur == 'B'){
                updateMap(grille);
                affiche();
                
                    if(!victoire){
                printf("Coup IA\n");//appelle IA.
                jouerCoupIA(grille, 'B',difficulter,0);
                    joueur = 'A';
                    }
                }
            }
        
    
        }
    else{
        //Appelle fonction faire jouer 2 IA
            printf("IA VS IA\n");
    }
}
