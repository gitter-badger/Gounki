//
//  Grille.c
//  Projet
//
//  Created by Etienne Toussaint on 26/03/2014.
//  Copyright (c) 2014 Etienne Toussaint. All rights reserved.
//

//Victoire + deploiement
//rebond

#include "Grille.h"
#include "Pion.h"

pion ** initGrille(){
    pion** grille = malloc(sizeof(pion *)*8);
    int x = 0,y=0;
    for (x=0; x<8; x++) {
        *(grille+x) = malloc(sizeof(pion)*8);
        for (y=0; y<8; y++) {
            if(y<2 && (x+y)%2==0) *(*(grille+x)+y) = initCarre(x,y,'A');
            else if (y<2 && (x+y)%2==1) *(*(grille+x)+y) = initRond(x,y,'A');
            else if(y>5 && (x+y)%2==0) *(*(grille+x)+y) = initCarre(x,y,'B');
            else if (y>5 && (x+y)%2==1) *(*(grille+x)+y) = initRond(x,y,'B');
            else *(*(grille+x)+y) = initPion(x,y);
        }
    }
    
    return grille;
}



char * concat(char * string1,char * string2){
    char * result = malloc(sizeof(char)*(strlen(string1)+strlen(string2)));
    result = strcat(strcpy(result,string1), string2);
    return result;
}

char * convertit(int x,int y){
    char *result = malloc(2*sizeof(char));
    result[0]=(char)(x+97);
    result[1]=(char)(y+49);
    return result;
}

int recupX(char x){
    return (int)(x-97);
}
int recupY(char y){
    return (int)(y-49);
}

pion ** deplacer(pion ** grille,int xDepart, int yDepart,int xArrive, int yArrive){
    if (grille[xArrive][yArrive].joueur != grille[xDepart][yDepart].joueur){
        grille[xArrive][yArrive] = grille[xDepart][yDepart];
        grille[xArrive][yArrive].x = xArrive;
        grille[xArrive][yArrive].y = yArrive;
        grille[xDepart][yDepart].joueur = 'V';
        grille[xDepart][yDepart].type = 0;
        
    }
    return grille;
}

pion** action(pion ** grille ,char * proto){
    switch (strlen(proto)) {
        case 5:
            if (proto[2] == '-') {
                grille = deplacer(grille,recupX(proto[0]), recupY(proto[1]),recupX(proto[3]), recupY(proto[4]));
            }
            break;
        case 8:
            break;
    }
    return grille;
}


coup* deployComposeRond (char *begin, pion pionEnCours, coup * coupActuelle, pion ** grille, char joueur){
    int x = pionEnCours.x;
    int y = pionEnCours.y;
    
    if(x < 7 && y < 7 && joueur == 'A'){
        if(deployment(grille[x+1][y+1],joueur)){
            coup * coupSuivant = malloc(sizeof(coup));
            char * proto = concat(concat(begin, "+"),convertit(x, y));
            coupActuelle->proto=concat(concat(proto,"-"),convertit(x+1,y+1));
            coupActuelle->coupSuivant = coupSuivant;
            coupActuelle = coupSuivant;
        }
    }
    if(x == 7 && y < 7 && joueur == 'A'){
        if(deployment(grille[x+1][y+1],joueur)){
            coup * coupSuivant = malloc(sizeof(coup));
            char * proto = concat(concat(begin, "+"),convertit(x, y));
            coupActuelle->proto=concat(concat(proto,"-"),convertit(x,y+2));
            coupActuelle->coupSuivant = coupSuivant;
            coupActuelle = coupSuivant;
        }
    }
    if(y < 7 && x > 0 && joueur == 'A'){
        if(deployment(grille[x-1][y+1],joueur)){
            coup * coupSuivant = malloc(sizeof(coup));
            char * proto = concat(concat(begin, "+"),convertit(x, y));
            coupActuelle->proto=concat(concat(proto,"-"),convertit(x-1,y+1));
            coupActuelle->coupSuivant = coupSuivant;
            coupActuelle = coupSuivant;
        }
    }
    if(y < 7 && x == 0 && joueur == 'A'){
        if(deployment(grille[x-1][y+1],joueur)){
            coup * coupSuivant = malloc(sizeof(coup));
            char * proto = concat(concat(begin, "+"),convertit(x, y));
            coupActuelle->proto=concat(concat(proto,"-"),convertit(x,y+2));
            coupActuelle->coupSuivant = coupSuivant;
            coupActuelle = coupSuivant;
        }
    }
    if(x > 0 && y > 0 && joueur == 'B'){
        if(deployment(grille[x-1][y-1],joueur)){
            coup * coupSuivant = malloc(sizeof(coup));
            char * proto = concat(concat(begin, "+"),convertit(x, y));
            coupActuelle->proto=concat(concat(proto,"-"),convertit(x-1,y-1));
            coupActuelle->coupSuivant = coupSuivant;
            coupActuelle = coupSuivant;
        }
    }
    if(x == 0 && y > 0 && joueur == 'B'){
        if(deployment(grille[x-1][y-1],joueur)){
            coup * coupSuivant = malloc(sizeof(coup));
            char * proto = concat(concat(begin, "+"),convertit(x, y));
            coupActuelle->proto=concat(concat(proto,"-"),convertit(x,y-2));
            coupActuelle->coupSuivant = coupSuivant;
            coupActuelle = coupSuivant;
        }
    }
    if(y > 0 && x < 7 && joueur == 'B'){
        if(deployment(grille[x+1][y-1],joueur)){
            coup * coupSuivant = malloc(sizeof(coup));
            char * proto = concat(concat(begin, "+"),convertit(x, y));
            coupActuelle->proto=concat(concat(proto,"-"),convertit(x+1,y-1));
            coupActuelle->coupSuivant = coupSuivant;
            coupActuelle = coupSuivant;
        }
    }
    if(y > 0 && x == 7 && joueur == 'B'){
        if(deployment(grille[x+1][y-1],joueur)){
            coup * coupSuivant = malloc(sizeof(coup));
            char * proto = concat(concat(begin, "+"),convertit(x, y));
            coupActuelle->proto=concat(concat(proto,"-"),convertit(x,y-2));
            coupActuelle->coupSuivant = coupSuivant;
            coupActuelle = coupSuivant;
        }
    }
    return coupActuelle;
}

coup* deployComposeRondDouble (char *begin, pion pionEnCours, coup * coupActuelle, pion ** grille, char joueur){
    int x = pionEnCours.x;
    int y = pionEnCours.y;
    
    if(x < 6 && y < 6 && joueur == 'A'){
        if(deployment(grille[x+1][y+1],joueur)&&deployment(grille[x+2][y+2],joueur)){
            coup * coupSuivant = malloc(sizeof(coup));
            char * proto = concat(concat(begin, "+"),convertit(x, y));
            coupActuelle->proto=concat(concat(proto,"-"),convertit(x+2,y+2));
            coupActuelle->coupSuivant = coupSuivant;
            coupActuelle = coupSuivant;
        }
    }
    
    if(x == 6 && y < 6 && joueur == 'A'){
        if(deployment(grille[x+1][y+1],joueur)&&deployment(grille[x+1][y+3],joueur)){
            coup * coupSuivant = malloc(sizeof(coup));
            char * proto = concat(concat(begin, "+"),convertit(x, y));
            coupActuelle->proto=concat(concat(proto,"-"),convertit(x+1,y+2));
            coupActuelle->coupSuivant = coupSuivant;
            coupActuelle = coupSuivant;
        }
    }
    
    if(x == 7 && y < 6 && joueur == 'A'){
        if(deployment(grille[x][y+2],joueur)&&deployment(grille[x-1][y+3],joueur)){
            coup * coupSuivant = malloc(sizeof(coup));
            char * proto = concat(concat(begin, "+"),convertit(x, y));
            coupActuelle->proto=concat(concat(proto,"-"),convertit(x+1,y+2));
            coupActuelle->coupSuivant = coupSuivant;
            coupActuelle = coupSuivant;
        }
    }
    
    if(y < 6 && x > 1 && joueur == 'A'){
        if(deployment(grille[x-1][y+1],joueur)&&deployment(grille[x-2][y+2],joueur)){
            coup * coupSuivant = malloc(sizeof(coup));
            char * proto = concat(concat(begin, "+"),convertit(x, y));
            coupActuelle->proto=concat(concat(proto,"-"),convertit(x-2,y+2));
            coupActuelle->coupSuivant = coupSuivant;
            coupActuelle = coupSuivant;
        }
    }
    if(x > 1 && y > 1 && joueur == 'B'){
        if(deployment(grille[x-1][y-1],joueur)&&deployment(grille[x-2][y-2],joueur)){
            coup * coupSuivant = malloc(sizeof(coup));
            char * proto = concat(concat(begin, "+"),convertit(x, y));
            coupActuelle->proto=concat(concat(proto,"-"),convertit(x-2,y-2));
            coupActuelle->coupSuivant = coupSuivant;
            coupActuelle = coupSuivant;
        }
    }
    if(y > 1 && x < 6 && joueur == 'B'){
        if(deployment(grille[x+1][y-1],joueur)&&deployment(grille[x+2][y-2],joueur)){
            coup * coupSuivant = malloc(sizeof(coup));
            char * proto = concat(concat(begin, "+"),convertit(x, y));
            coupActuelle->proto=concat(concat(proto,"-"),convertit(x+2,y-2));
            coupActuelle->coupSuivant = coupSuivant;
            coupActuelle = coupSuivant;
        }
    }
    return coupActuelle;
}

coup* deployComposeCarreDouble (char *begin, pion pionEnCours, coup * coupActuelle, pion ** grille, char joueur){
    int x = pionEnCours.x;
    int y = pionEnCours.y;
    
    if(joueur == 'A' && y < 6) {
        if(deployment(grille[x][y+2],joueur) && deployment(grille[x][y+1],joueur)){
            coup * coupSuivant = malloc(sizeof(coup));
            char * proto = concat(concat(begin, "*"),convertit(x, y));
            coupActuelle->proto=concat(concat(proto,"-"),convertit(x,y+2));
            coupActuelle->coupSuivant = coupSuivant;
            coupActuelle = coupSuivant;
        }
    }
    if(joueur == 'B' && y > 1) {
        if(deployment(grille[x][y-2],joueur) && deployment(grille[x][y-1],joueur)){
            coup * coupSuivant = malloc(sizeof(coup));
            char * proto = concat(concat(begin, "*"),convertit(x, y));
            coupActuelle->proto=concat(concat(proto,"-"),convertit(x,y-2));
            coupActuelle->coupSuivant = coupSuivant;
            coupActuelle = coupSuivant;
        }
    }
    if(x < 6){
        if(deployment(grille[x+2][y],joueur) && deployment(grille[x+1][y],joueur)){
            coup * coupSuivant = malloc(sizeof(coup));
            char * proto = concat(concat(begin, "*"),convertit(x, y));
            coupActuelle->proto=concat(concat(proto,"-"),convertit(x+2,y));
            coupActuelle->coupSuivant = coupSuivant;
            coupActuelle = coupSuivant;
        }
    }
    if(x > 1){
        if(deployment(grille[x-2][y],joueur) && deployment(grille[x-2][y+1],joueur)){
            coup * coupSuivant = malloc(sizeof(coup));
            char * proto = concat(concat(begin, "*"),convertit(x, y));
            coupActuelle->proto=concat(concat(proto,"-"),convertit(x-2,y));
            coupActuelle->coupSuivant = coupSuivant;
            coupActuelle = coupSuivant;
        }
    }
    return coupActuelle;
}

coup* deployComposeCarre (char *begin, pion pionEnCours, coup * coupActuelle, pion ** grille, char joueur){
    int x = pionEnCours.x;
    int y = pionEnCours.y;
    
    if(joueur == 'A' && y < 7) {
        if(deployment(grille[x][y+1],joueur)){
            coup * coupSuivant = malloc(sizeof(coup));
            char * proto = concat(concat(begin, "*"),convertit(x, y));
            coupActuelle->proto=concat(concat(proto,"-"),convertit(x,y+1));
            coupActuelle->coupSuivant = coupSuivant;
            coupActuelle = coupSuivant;
        }
    }
    if(joueur == 'B' && y > 0) {
        if(deployment(grille[x][y-1],joueur)){
            coup * coupSuivant = malloc(sizeof(coup));
            char * proto = concat(concat(begin, "*"),convertit(x, y));
            coupActuelle->proto=concat(concat(proto,"-"),convertit(x,y-1));
            coupActuelle->coupSuivant = coupSuivant;
            coupActuelle = coupSuivant;
        }
    }
    if(x < 7){
        if(deployment(grille[x+1][y],joueur)){
            coup * coupSuivant = malloc(sizeof(coup));
            char * proto = concat(concat(begin, "*"),convertit(x, y));
            coupActuelle->proto=concat(concat(proto,"-"),convertit(x+1,y));
            coupActuelle->coupSuivant = coupSuivant;
            coupActuelle = coupSuivant;
        }
    }
    if(x > 0){
        if(deployment(grille[x-1][y],joueur)){
            coup * coupSuivant = malloc(sizeof(coup));
            char * proto = concat(concat(begin, "*"),convertit(x, y));
            coupActuelle->proto=concat(concat(proto,"-"),convertit(x-1,y));
            coupActuelle->coupSuivant = coupSuivant;
            coupActuelle = coupSuivant;
        }
    }
    return coupActuelle;
}


coup* coupsPossibles(pion** grille,char joueur){
    coup* coupPere = malloc(sizeof(coup));
    coup* coupActuelle = coupPere;
    int x =0,y=0;
    for (x=0; x<8; x++) {
        for (y=0; y<8; y++) {
            if(grille[x][y].joueur == joueur){
                char * begin = convertit(x,y);
                switch (grille[x][y].type) {
                    case 1:
                        //Victoire
                        if(joueur == 'A' && y == 7){
                            coup * coupSuivant = malloc(sizeof(coup));
                            coupActuelle->proto=concat(begin,"#");
                            coupActuelle->coupSuivant = coupSuivant;
                            coupActuelle = coupSuivant;
                        }
                        if(joueur == 'B' && y == 0) {
                            coup * coupSuivant = malloc(sizeof(coup));
                            coupActuelle->proto=concat(begin,"#");
                            coupActuelle->coupSuivant = coupSuivant;
                            coupActuelle = coupSuivant;
                        }
                        //Deplacement
                        if(joueur == 'A' && y < 7) {
                            if(deplacementSimple(grille[x][y+1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x,y+1));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(joueur == 'B' && y > 0) {
                            if(deplacementSimple(grille[x][y-1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x,y-1));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x < 7){
                            if(deplacementSimple(grille[x+1][y],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x+1,y));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x > 0){
                            if(deplacementSimple(grille[x-1][y],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x-1,y));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        break;
                    case 2:
                        //Victoire
                        if(y == 7 && joueur == 'A'){
                            coup * coupSuivant = malloc(sizeof(coup));
                            coupActuelle->proto=concat(begin,"#");
                            coupActuelle->coupSuivant = coupSuivant;
                            coupActuelle = coupSuivant;
                        }
                        if(y == 0 && joueur == 'B'){
                            coup * coupSuivant = malloc(sizeof(coup));
                            coupActuelle->proto=concat(begin,"#");
                            coupActuelle->coupSuivant = coupSuivant;
                            coupActuelle = coupSuivant;
                        }
                        //Déplacement
                        if(x < 7 && y < 7 && joueur == 'A'){
                            if(deplacementSimple(grille[x+1][y+1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x+1,y+1));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(y < 7 && x > 0 && joueur == 'A'){
                            if(deplacementSimple(grille[x-1][y+1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x-1,y+1));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x > 0 && y > 0 && joueur == 'B'){
                            if(deplacementSimple(grille[x-1][y-1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x-1,y-1));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(y > 0 && x < 7 && joueur == 'B'){
                            if(deplacementSimple(grille[x+1][y-1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x+1,y-1));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        break;
                    case 3:
                        //Victoire
                        if(joueur == 'A' && y == 7){
                            coup * coupSuivant = malloc(sizeof(coup));
                            coupActuelle->proto=concat(begin,"#");
                            coupActuelle->coupSuivant = coupSuivant;
                            coupActuelle = coupSuivant;
                        }
                        if(joueur == 'B' && y == 0) {
                            coup * coupSuivant = malloc(sizeof(coup));
                            coupActuelle->proto=concat(begin,"#");
                            coupActuelle->coupSuivant = coupSuivant;
                            coupActuelle = coupSuivant;
                        }
                        if(joueur == 'A' && y == 6){
                            if(grille[x][y+1].joueur!='B'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(begin,"#");
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(joueur == 'B' && y == 1) {
                            if(grille[x][y-1].joueur!='A'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(begin,"#");
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        //Deplacement
                        if(joueur == 'A' && y < 7) {
                            if(deplacementDouble(grille[x][y+1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x,y+1));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(joueur == 'A' && y < 6) {
                            if(deplacementDouble(grille[x][y+2],joueur)&&grille[x][y+1].joueur == 'V'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x,y+2));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(joueur == 'B' && y > 0) {
                            if(deplacementDouble(grille[x][y-1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x,y-1));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(joueur == 'B' && y > 1) {
                            if(deplacementDouble(grille[x][y-2],joueur)&&grille[x][y-1].joueur == 'V'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x,y-2));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x < 7){
                            if(deplacementDouble(grille[x+1][y],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x+1,y));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x < 6){
                            if(deplacementDouble(grille[x+2][y],joueur)&&grille[x+1][y].joueur == 'V'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x+2,y));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x > 0){
                            if(deplacementDouble(grille[x-1][y],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x-1,y));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x > 1){
                            if(deplacementDouble(grille[x-2][y],joueur)&&grille[x-1][y].joueur == 'V'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x-2,y));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        //Déploiment.
                        
                        if(joueur == 'A' && y < 6) {
                            if(deployment(grille[x][y+2],joueur) && deployment(grille[x][y+1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"+"),convertit(x,y+2));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(joueur == 'B' && y > 1) {
                            if(deployment(grille[x][y-2],joueur) && deployment(grille[x][y-1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"+"),convertit(x,y-2));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x < 6){
                            if(deployment(grille[x+2][y],joueur) && deployment(grille[x+1][y],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"+"),convertit(x+2,y));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x > 1){
                            if(deployment(grille[x-2][y],joueur) && deployment(grille[x-2][y+1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"+"),convertit(x-2,y));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        
                        break;
                    case 4:
                        //Victoire
                        if(y == 7 && joueur == 'A'){
                            coup * coupSuivant = malloc(sizeof(coup));
                            coupActuelle->proto=concat(begin,"#");
                            coupActuelle->coupSuivant = coupSuivant;
                            coupActuelle = coupSuivant;
                        }
                        if(y == 6 && joueur == 'A'){
                            if (grille[x+1][y+1].joueur != 'A' || grille[x-1][y+1].joueur != 'A') {
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(begin,"#");
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(y == 0 && joueur == 'B'){
                            coup * coupSuivant = malloc(sizeof(coup));
                            coupActuelle->proto=concat(begin,"#");
                            coupActuelle->coupSuivant = coupSuivant;
                            coupActuelle = coupSuivant;
                        }
                        if(y == 1 && joueur == 'B'){
                            if (grille[x+1][y-1].joueur != 'B' || grille[x-1][y-1].joueur != 'B'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(begin,"#");
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        //Déplacement
                        if(x < 7 && y < 7 && joueur == 'A'){
                            if(deplacementDouble(grille[x+1][y+1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x+1,y+1));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x < 6 && y < 6 && joueur == 'A'){
                            if(deplacementDouble(grille[x+2][y+2],joueur)&&grille[x+1][y+1].joueur == 'V'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x+2,y+2));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(y < 7 && x > 0 && joueur == 'A'){
                            if(deplacementDouble(grille[x-1][y+1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x-1,y+1));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(y < 6 && x > 1 && joueur == 'A'){
                            if(deplacementDouble(grille[x-2][y+2],joueur)&&grille[x-1][y+1].joueur == 'V'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x-2,y+2));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x > 0 && y > 0 && joueur == 'B'){
                            if(deplacementDouble(grille[x-1][y-1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x-1,y-1));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x > 1 && y > 1 && joueur == 'B'){
                            if(deplacementDouble(grille[x-2][y-2],joueur)&&grille[x-1][y-1].joueur == 'V'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x-2,y-2));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(y > 0 && x < 7 && joueur == 'B'){
                            if(deplacementDouble(grille[x+1][y-1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x+1,y-1));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(y > 1 && x < 6 && joueur == 'B'){
                            if(deplacementDouble(grille[x+2][y-2],joueur)&&grille[x+1][y-1].joueur == 'V'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x+2,y-2));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        //Deploy
                        
                        
                        if(x < 6 && y < 6 && joueur == 'A'){
                            if(deployment(grille[x+1][y+1],joueur)&&deployment(grille[x+2][y+2],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"*"),convertit(x+2,y+2));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(y < 6 && x > 1 && joueur == 'A'){
                            if(deployment(grille[x-1][y+1],joueur)&&deployment(grille[x-2][y+2],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"*"),convertit(x-2,y+2));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x > 1 && y > 1 && joueur == 'B'){
                            if(deployment(grille[x-1][y-1],joueur)&&deployment(grille[x-2][y-2],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"*"),convertit(x-2,y-2));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(y > 1 && x < 6 && joueur == 'B'){
                            if(deployment(grille[x+1][y-1],joueur)&&deployment(grille[x+2][y-2],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"*"),convertit(x+2,y-2));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        
                        break;
                    case 5:
                        //Victoire
                        if(joueur == 'A' && y == 7){
                            coup * coupSuivant = malloc(sizeof(coup));
                            coupActuelle->proto=concat(begin,"#");
                            coupActuelle->coupSuivant = coupSuivant;
                            coupActuelle = coupSuivant;
                        }
                        if(joueur == 'B' && y == 0) {
                            coup * coupSuivant = malloc(sizeof(coup));
                            coupActuelle->proto=concat(begin,"#");
                            coupActuelle->coupSuivant = coupSuivant;
                            coupActuelle = coupSuivant;
                        }
                        if(joueur == 'A' && y == 6){
                            if(grille[x][y+1].joueur!='B'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(begin,"#");
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(joueur == 'B' && y == 1) {
                            if(grille[x][y-1].joueur!='A'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(begin,"#");
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(joueur == 'A' && y == 5){
                            if(grille[x][y+1].joueur!='B'&&grille[x][y+2].joueur!='B'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(begin,"#");
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(joueur == 'B' && y == 2) {
                            if(grille[x][y-1].joueur!='A'&&grille[x][y-2].joueur!='A'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(begin,"#");
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }

                        
                        //Deplacement
                        if(joueur == 'A' && y < 7) {
                            if(deplacementTriple(grille[x][y+1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x,y+1));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(joueur == 'A' && y < 6) {
                            if(deplacementTriple(grille[x][y+2],joueur)&&grille[x][y+1].joueur == 'V'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x,y+2));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(joueur == 'A' && y < 5) {
                            if(deplacementTriple(grille[x][y+3],joueur)&&grille[x][y+1].joueur == 'V'&&grille[x][y+2].joueur == 'V'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x,y+3));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }

                        if(joueur == 'B' && y > 0) {
                            if(deplacementTriple(grille[x][y-1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x,y-1));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(joueur == 'B' && y > 1) {
                            if(deplacementTriple(grille[x][y-2],joueur)&&grille[x][y-1].joueur == 'V'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x,y-2));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(joueur == 'B' && y > 2) {
                            if(deplacementTriple(grille[x][y-3],joueur)&&grille[x][y-1].joueur == 'V'&&grille[x][y-2].joueur == 'V'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x,y-3));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x < 7){
                            if(deplacementTriple(grille[x+1][y],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x+1,y));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x < 6){
                            if(deplacementTriple(grille[x+2][y],joueur)&&grille[x+1][y].joueur == 'V'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x+2,y));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x < 5){
                            if(deplacementTriple(grille[x+3][y],joueur)&&grille[x+1][y].joueur == 'V'&&grille[x+2][y].joueur == 'V'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x+3,y));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x > 0){
                            if(deplacementTriple(grille[x-1][y],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x-1,y));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x > 1){
                            if(deplacementTriple(grille[x-2][y],joueur)&&grille[x-1][y].joueur == 'V'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x-2,y));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x > 2){
                            if(deplacementTriple(grille[x-3][y],joueur)&&grille[x-1][y].joueur == 'V'&&grille[x-2][y].joueur == 'V'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x-3,y));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        
                        //deploy
                        
                        if(joueur == 'A' && y < 5) {
                            if(deployment(grille[x][y+2],joueur) && deployment(grille[x][y+1],joueur)&& deployment(grille[x][y+3],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"+"),convertit(x,y+3));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(joueur == 'B' && y > 2) {
                            if(deployment(grille[x][y-2],joueur) && deployment(grille[x][y-1],joueur)&& deployment(grille[x][y-3],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"+"),convertit(x,y-3));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x < 5){
                            if(deployment(grille[x+2][y],joueur) && deployment(grille[x+1][y],joueur)&& deployment(grille[x+3][y],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"+"),convertit(x+3,y));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x > 2){
                            if(deployment(grille[x-2][y],joueur) && deployment(grille[x-2][y+1],joueur)&& deployment(grille[x-3][y],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"+"),convertit(x-3,y));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }

                        
                        break;
                        
                    case 6:
                        //Victoire
                        if(y == 7 && joueur == 'A'){
                            coup * coupSuivant = malloc(sizeof(coup));
                            coupActuelle->proto=concat(begin,"#");
                            coupActuelle->coupSuivant = coupSuivant;
                            coupActuelle = coupSuivant;
                        }
                        if(y == 6 && joueur == 'A'){
                            if (grille[x+1][y+1].joueur != 'B' || grille[x-1][y+1].joueur != 'B') {
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(begin,"#");
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(y == 5 && joueur == 'A'){
                            if ((grille[x+1][y+1].joueur != 'B'&&grille[x+2][y+2].joueur != 'B') || (grille[x-1][y+1].joueur != 'A'&&grille[x-2][y+2].joueur != 'B')) {
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(begin,"#");
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(y == 0 && joueur == 'B'){
                            coup * coupSuivant = malloc(sizeof(coup));
                            coupActuelle->proto=concat(begin,"#");
                            coupActuelle->coupSuivant = coupSuivant;
                            coupActuelle = coupSuivant;
                        }
                        if(y == 1 && joueur == 'B'){
                            if (grille[x+1][y-1].joueur != 'A' || grille[x-1][y-1].joueur != 'A'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(begin,"#");
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(y == 2 && joueur == 'B'){
                            if ((grille[x+1][y-1].joueur != 'A'&&grille[x+2][y-2].joueur != 'A') || (grille[x-1][y-1].joueur != 'A'&&grille[x-2][y-2].joueur != 'A')){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(begin,"#");
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        //Déplacement
                        if(x < 7 && y < 7 && joueur == 'A'){
                            if(deplacementTriple(grille[x+1][y+1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x+1,y+1));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x < 6 && y < 6 && joueur == 'A'){
                            if(deplacementTriple(grille[x+2][y+2],joueur)&&grille[x+1][y+1].joueur == 'V'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x+2,y+2));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x < 5 && y < 5 && joueur == 'A'){
                            if(deplacementTriple(grille[x+3][y+3],joueur)&&grille[x+1][y+1].joueur == 'V'&&grille[x+2][y+2].joueur == 'V'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x+3,y+3));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(y < 7 && x > 0 && joueur == 'A'){
                            if(deplacementTriple(grille[x-1][y+1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x-1,y+1));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(y < 6 && x > 1 && joueur == 'A'){
                            if(deplacementTriple(grille[x-2][y+2],joueur)&&grille[x-1][y+1].joueur == 'V'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x-2,y+2));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(y < 5 && x > 2 && joueur == 'A'){
                            if(deplacementTriple(grille[x-3][y+3],joueur)&&grille[x-1][y+1].joueur == 'V'&&grille[x-2][y+2].joueur == 'V'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x-3,y+3));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x > 0 && y > 0 && joueur == 'B'){
                            if(deplacementTriple(grille[x-1][y-1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x-1,y-1));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x > 1 && y > 1 && joueur == 'B'){
                            if(deplacementTriple(grille[x-2][y-2],joueur)&&grille[x-1][y-1].joueur == 'V'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x-2,y-2));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x > 2 && y > 2 && joueur == 'B'){
                            if(deplacementTriple(grille[x-3][y-3],joueur)&&grille[x-1][y-1].joueur == 'V'&&grille[x-2][y-2].joueur == 'V'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x-3,y-3));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(y > 0 && x < 7 && joueur == 'B'){
                            if(deplacementTriple(grille[x+1][y-1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x+1,y-1));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(y > 1 && x < 6 && joueur == 'B'){
                            if(deplacementTriple(grille[x+2][y-2],joueur)&&grille[x+1][y-1].joueur == 'V'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x+2,y-2));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(y > 2 && x < 7 && joueur == 'B'){
                            if(deplacementTriple(grille[x+3][y-3],joueur)&&grille[x+1][y-1].joueur == 'V'&&grille[x+2][y-2].joueur == 'V'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x+3,y-3));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        //Deploy
                        
                        if(x < 5 && y < 5 && joueur == 'A'){
                            if(deployment(grille[x+1][y+1],joueur)&&deployment(grille[x+2][y+2],joueur)&&deployment(grille[x+3][y+3],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"*"),convertit(x+3,y+3));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(y < 5 && x > 2 && joueur == 'A'){
                            if(deployment(grille[x-1][y+1],joueur)&&deployment(grille[x-2][y+2],joueur)&&deployment(grille[x-3][y+3],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"*"),convertit(x-3,y+3));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x > 2 && y > 2 && joueur == 'B'){
                            if(deployment(grille[x-1][y-1],joueur)&&deployment(grille[x-2][y-2],joueur)&&deployment(grille[x-3][y-3],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"*"),convertit(x-3,y-3));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(y > 2 && x < 5 && joueur == 'B'){
                            if(deployment(grille[x+1][y-1],joueur)&&deployment(grille[x+2][y-2],joueur)&&deployment(grille[x+3][y-3],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"*"),convertit(x+3,y-3));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }

                        
                        
                        break;
                    case 7:
                        //Victoire
                        if(joueur == 'A' && y == 7){
                            coup * coupSuivant = malloc(sizeof(coup));
                            coupActuelle->proto=concat(begin,"#");
                            coupActuelle->coupSuivant = coupSuivant;
                            coupActuelle = coupSuivant;
                        }
                        if(joueur == 'B' && y == 0) {
                            coup * coupSuivant = malloc(sizeof(coup));
                            coupActuelle->proto=concat(begin,"#");
                            coupActuelle->coupSuivant = coupSuivant;
                            coupActuelle = coupSuivant;
                        }
                        //Deplacement
                        if(joueur == 'A' && y < 7) {
                            if(deplacementDouble(grille[x][y+1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x,y+1));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(joueur == 'B' && y > 0) {
                            if(deplacementDouble(grille[x][y-1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x,y-1));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x < 7){
                            if(deplacementDouble(grille[x+1][y],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x+1,y));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x > 0){
                            if(deplacementDouble(grille[x-1][y],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x-1,y));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        
                        //Victoire
                        if(y == 7 && joueur == 'A'){
                            coup * coupSuivant = malloc(sizeof(coup));
                            coupActuelle->proto=concat(begin,"#");
                            coupActuelle->coupSuivant = coupSuivant;
                            coupActuelle = coupSuivant;
                        }
                        if(y == 0 && joueur == 'B'){
                            coup * coupSuivant = malloc(sizeof(coup));
                            coupActuelle->proto=concat(begin,"#");
                            coupActuelle->coupSuivant = coupSuivant;
                            coupActuelle = coupSuivant;
                        }
                        //Déplacement
                        if(x < 7 && y < 7 && joueur == 'A'){
                            if(deplacementDouble(grille[x+1][y+1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x+1,y+1));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(y < 7 && x > 0 && joueur == 'A'){
                            if(deplacementDouble(grille[x-1][y+1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x-1,y+1));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x > 0 && y > 0 && joueur == 'B'){
                            if(deplacementDouble(grille[x-1][y-1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x-1,y-1));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(y > 0 && x < 7 && joueur == 'B'){
                            if(deplacementDouble(grille[x+1][y-1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x+1,y-1));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }

                        
                        // deploy
                        
                        if(x < 7 && y < 7 && joueur == 'A'){
                            if(deployment(grille[x+1][y+1],joueur)){
                                coupActuelle = deployComposeCarre(begin, grille[x+1][y+1], coupActuelle, grille, joueur);
                            }
                        }
                        if(y < 7 && x > 0 && joueur == 'A'){
                            if(deployment(grille[x-1][y+1],joueur)){
                                coupActuelle = deployComposeCarre(begin, grille[x-1][y+1], coupActuelle, grille, joueur);
                            }
                        }
                        if(x > 0 && y > 0 && joueur == 'B'){
                            if(deployment(grille[x-1][y-1],joueur)){
                                coupActuelle = deployComposeCarre(begin, grille[x-1][y-1], coupActuelle, grille, joueur);
                            }
                        }
                        if(y > 0 && x < 7 && joueur == 'B'){
                            if(deployment(grille[x+1][y-1],joueur)){
                                coupActuelle = deployComposeCarre(begin, grille[x+1][y-1], coupActuelle, grille, joueur);
                            }
                        }
                        
                        if(joueur == 'A' && y < 7) {
                            if(deployment(grille[x][y+1],joueur)){
                                coupActuelle = deployComposeRond(begin, grille[x][y+1], coupActuelle, grille, joueur);
                            }
                        }
                        if(joueur == 'B' && y > 0) {
                            if(deployment(grille[x][y-1],joueur)){
                                coupActuelle = deployComposeRond(begin, grille[x][y-1], coupActuelle, grille, joueur);
                            }
                        }
                        if(x < 7){
                            if(deployment(grille[x+1][y],joueur)){
                                coupActuelle = deployComposeRond(begin, grille[x+1][y], coupActuelle, grille, joueur);
                            }
                        }
                        if(x > 0){
                            if(deployment(grille[x-1][y],joueur)){
                                coupActuelle = deployComposeRond(begin, grille[x-1][y], coupActuelle, grille, joueur);
                            }
                        }

                        break;
                    case 8:
                        //Victoire
                        if(joueur == 'A' && y == 7){
                            coup * coupSuivant = malloc(sizeof(coup));
                            coupActuelle->proto=concat(begin,"#");
                            coupActuelle->coupSuivant = coupSuivant;
                            coupActuelle = coupSuivant;
                        }
                        if(joueur == 'B' && y == 0) {
                            coup * coupSuivant = malloc(sizeof(coup));
                            coupActuelle->proto=concat(begin,"#");
                            coupActuelle->coupSuivant = coupSuivant;
                            coupActuelle = coupSuivant;
                        }
                        if(joueur == 'A' && y == 6){
                            if(grille[x][y+1].joueur!='B'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(begin,"#");
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(joueur == 'B' && y == 1) {
                            if(grille[x][y-1].joueur!='A'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(begin,"#");
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        //Deplacement
                        if(joueur == 'A' && y < 7) {
                            if(deplacementTriple(grille[x][y+1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x,y+1));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(joueur == 'A' && y < 6) {
                            if(deplacementTriple(grille[x][y+2],joueur)&&grille[x][y+1].joueur == 'V'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x,y+2));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(joueur == 'B' && y > 0) {
                            if(deplacementTriple(grille[x][y-1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x,y-1));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(joueur == 'B' && y > 1) {
                            if(deplacementTriple(grille[x][y-2],joueur)&&grille[x][y-1].joueur == 'V'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x,y-2));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x < 7){
                            if(deplacementTriple(grille[x+1][y],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x+1,y));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x < 6){
                            if(deplacementTriple(grille[x+2][y],joueur)&&grille[x+1][y].joueur == 'V'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x+2,y));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x > 0){
                            if(deplacementTriple(grille[x-1][y],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x-1,y));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x > 1){
                            if(deplacementTriple(grille[x-2][y],joueur)&&grille[x-1][y].joueur == 'V'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x-2,y));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        
                        //Victoire
                        if(y == 7 && joueur == 'A'){
                            coup * coupSuivant = malloc(sizeof(coup));
                            coupActuelle->proto=concat(begin,"#");
                            coupActuelle->coupSuivant = coupSuivant;
                            coupActuelle = coupSuivant;
                        }
                        if(y == 0 && joueur == 'B'){
                            coup * coupSuivant = malloc(sizeof(coup));
                            coupActuelle->proto=concat(begin,"#");
                            coupActuelle->coupSuivant = coupSuivant;
                            coupActuelle = coupSuivant;
                        }
                        //Déplacement
                        if(x < 7 && y < 7 && joueur == 'A'){
                            if(deplacementTriple(grille[x+1][y+1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x+1,y+1));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(y < 7 && x > 0 && joueur == 'A'){
                            if(deplacementTriple(grille[x-1][y+1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x-1,y+1));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x > 0 && y > 0 && joueur == 'B'){
                            if(deplacementTriple(grille[x-1][y-1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x-1,y-1));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(y > 0 && x < 7 && joueur == 'B'){
                            if(deplacementTriple(grille[x+1][y-1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x+1,y-1));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        //deploy
                        
                        if(joueur == 'A' && y < 6) {
                            if(deployment(grille[x][y+2],joueur) && deployment(grille[x][y+1],joueur)){
                                coupActuelle = deployComposeRond(begin, grille[x][y+2], coupActuelle, grille, joueur);
                            }
                        }
                        if(joueur == 'B' && y > 1) {
                            if(deployment(grille[x][y-2],joueur) && deployment(grille[x][y-1],joueur)){
                                coupActuelle = deployComposeRond(begin, grille[x][y-2], coupActuelle, grille, joueur);
                            }
                        }
                        if(x < 6){
                            if(deployment(grille[x+2][y],joueur) && deployment(grille[x+1][y],joueur)){
                                coupActuelle = deployComposeRond(begin, grille[x+2][y], coupActuelle, grille, joueur);
                            }
                        }
                        if(x > 1){
                            if(deployment(grille[x-2][y],joueur) && deployment(grille[x-2][y+1],joueur)){
                                coupActuelle = deployComposeRond(begin, grille[x-2][y], coupActuelle, grille, joueur);
                            }
                        }
                        if(x < 7 && y < 7 && joueur == 'A'){
                            if(deployment(grille[x+1][y+1],joueur)){
                                coupActuelle = deployComposeCarreDouble(begin, grille[x+1][y+1], coupActuelle, grille, joueur);
                            }
                        }
                        if(y < 7 && x > 0 && joueur == 'A'){
                            if(deployment(grille[x-1][y+1],joueur)){
                                coupActuelle = deployComposeCarreDouble(begin, grille[x-1][y+1], coupActuelle, grille, joueur);
                            }
                        }
                        if(x > 0 && y > 0 && joueur == 'B'){
                            if(deployment(grille[x-1][y-1],joueur)){
                                coupActuelle = deployComposeCarreDouble(begin, grille[x-1][y-1], coupActuelle, grille, joueur);
                            }
                        }
                        if(y > 0 && x < 7 && joueur == 'B'){
                            if(deployment(grille[x+1][y-1],joueur)){
                                coupActuelle = deployComposeCarreDouble(begin, grille[x+1][y-1], coupActuelle, grille, joueur);
                            }
                        }

                        
                        break;
                    case 9:
                        //Victoire
                        if(joueur == 'A' && y == 7){
                            coup * coupSuivant = malloc(sizeof(coup));
                            coupActuelle->proto=concat(begin,"#");
                            coupActuelle->coupSuivant = coupSuivant;
                            coupActuelle = coupSuivant;
                        }
                        if(joueur == 'B' && y == 0) {
                            coup * coupSuivant = malloc(sizeof(coup));
                            coupActuelle->proto=concat(begin,"#");
                            coupActuelle->coupSuivant = coupSuivant;
                            coupActuelle = coupSuivant;
                        }
                        //Deplacement
                        if(joueur == 'A' && y < 7) {
                            if(deplacementTriple(grille[x][y+1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x,y+1));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(joueur == 'B' && y > 0) {
                            if(deplacementTriple(grille[x][y-1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x,y-1));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x < 7){
                            if(deplacementTriple(grille[x+1][y],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x+1,y));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x > 0){
                            if(deplacementTriple(grille[x-1][y],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x-1,y));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        //Victoire
                        if(y == 7 && joueur == 'A'){
                            coup * coupSuivant = malloc(sizeof(coup));
                            coupActuelle->proto=concat(begin,"#");
                            coupActuelle->coupSuivant = coupSuivant;
                            coupActuelle = coupSuivant;
                        }
                        if(y == 6 && joueur == 'A'){
                            if (grille[x+1][y+1].joueur != 'A' || grille[x-1][y+1].joueur != 'A') {
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(begin,"#");
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(y == 0 && joueur == 'B'){
                            coup * coupSuivant = malloc(sizeof(coup));
                            coupActuelle->proto=concat(begin,"#");
                            coupActuelle->coupSuivant = coupSuivant;
                            coupActuelle = coupSuivant;
                        }
                        if(y == 1 && joueur == 'B'){
                            if (grille[x+1][y-1].joueur != 'B' || grille[x-1][y-1].joueur != 'B'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(begin,"#");
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        //Déplacement
                        if(x < 7 && y < 7 && joueur == 'A'){
                            if(deplacementTriple(grille[x+1][y+1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x+1,y+1));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x < 6 && y < 6 && joueur == 'A'){
                            if(deplacementTriple(grille[x+2][y+2],joueur)&&grille[x+1][y+1].joueur == 'V'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x+2,y+2));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(y < 7 && x > 0 && joueur == 'A'){
                            if(deplacementTriple(grille[x-1][y+1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x-1,y+1));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(y < 6 && x > 1 && joueur == 'A'){
                            if(deplacementTriple(grille[x-2][y+2],joueur)&&grille[x-1][y+1].joueur == 'V'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x-2,y+2));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x > 0 && y > 0 && joueur == 'B'){
                            if(deplacementTriple(grille[x-1][y-1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x-1,y-1));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(x > 1 && y > 1 && joueur == 'B'){
                            if(deplacementTriple(grille[x-2][y-2],joueur)&&grille[x-1][y-1].joueur == 'V'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x-2,y-2));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(y > 0 && x < 7 && joueur == 'B'){
                            if(deplacementTriple(grille[x+1][y-1],joueur)){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x+1,y-1));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        if(y > 1 && x < 6 && joueur == 'B'){
                            if(deplacementTriple(grille[x+2][y-2],joueur)&&grille[x+1][y-1].joueur == 'V'){
                                coup * coupSuivant = malloc(sizeof(coup));
                                coupActuelle->proto=concat(concat(begin,"-"),convertit(x+2,y-2));
                                coupActuelle->coupSuivant = coupSuivant;
                                coupActuelle = coupSuivant;
                            }
                        }
                        
                        //deploy
                        if(x < 6 && y < 6 && joueur == 'A'){
                            if(deployment(grille[x+1][y+1],joueur)&&deployment(grille[x+2][y+2],joueur)){
                                coupActuelle = deployComposeCarre(begin, grille[x+2][y+2], coupActuelle, grille, joueur);
                            }
                        }
                        if(y < 6 && x > 1 && joueur == 'A'){
                            if(deployment(grille[x-1][y+1],joueur)&&deployment(grille[x-2][y+2],joueur)){
                                coupActuelle = deployComposeCarre(begin, grille[x-2][y+2], coupActuelle, grille, joueur);
                            }
                        }
                        if(x > 1 && y > 1 && joueur == 'B'){
                            if(deployment(grille[x-1][y-1],joueur)&&deployment(grille[x-2][y-2],joueur)){
                                coupActuelle = deployComposeCarre(begin, grille[x-2][y-2], coupActuelle, grille, joueur);
                            }
                        }
                        if(y > 1 && x < 6 && joueur == 'B'){
                            if(deployment(grille[x+1][y-1],joueur)&&deployment(grille[x+2][y-2],joueur)){
                                coupActuelle = deployComposeCarre(begin, grille[x+2][y-2], coupActuelle, grille, joueur);
                            }
                        }
                        
                        if(joueur == 'A' && y < 7) {
                            if(deployment(grille[x][y+1],joueur)){
                                coupActuelle = deployComposeRondDouble(begin, grille[x][y+1], coupActuelle, grille, joueur);
                            }
                        }
                        if(joueur == 'B' && y > 0) {
                            if(deployment(grille[x][y-1],joueur)){
                                coupActuelle = deployComposeRondDouble(begin, grille[x][y-1], coupActuelle, grille, joueur);
                            }
                        }
                        if(x < 7){
                            if(deployment(grille[x+1][y],joueur)){
                                coupActuelle = deployComposeRondDouble(begin, grille[x+1][y], coupActuelle, grille, joueur);
                            }
                        }
                        if(x > 0){
                            if(deployment(grille[x-1][y],joueur)){
                                coupActuelle = deployComposeRondDouble(begin, grille[x-1][y], coupActuelle, grille, joueur);
                            }
                        }


                        break;

                        
                }
            }
        }
    }
    return coupPere;
}
