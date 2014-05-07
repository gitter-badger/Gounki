//
//  Grille.c
//  Gounki
//
//  Created by Etienne Toussaint on 23/03/2004.
//  Copyright (c) 2004 Etienne Toussaint. All rights reserved.
//

#import "Grille.h"

pion ** initGrille(){
    pion** grille = malloc(sizeof(pion *)*8);
    int x = 0,y=0;
    for (x=0; x<8; x++) {
        *(grille+x) = malloc(sizeof(pion)*8);
        for (y=0; y<8; y++) {
            if(y<2 && (x+y)%2==0) *(*(grille+x)+y) = initCarre(x,y,'A');
            else if (y<2 && (x+y)%2==0) *(*(grille+x)+y) = initRond(x,y,'A');
            else if(y>5 && (x+y)%2==0) *(*(grille+x)+y) = initCarre(x,y,'B');
            else if (y>5 && (x+y)%2==0) *(*(grille+x)+y) = initRond(x,y,'B');
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
    result[0]=(char)(y+97);
    result[1]=(char)(x+49);
    return result;
}

coup* checkDeplacement(pion pionDepart,pion pionCible,char joueur,coup* coupPossible,pion ** grille){
    return coupPossible;
}

coup* victoire(pion pionDepart,char joueur,coup* coupPossible,pion ** grille){
    
    return coupPossible;
}


coup* checkDeploiementCompose(pion pionDepart,char* how,pion pion2,char joueur,coup* coupPossible,pion ** grilleActuelle, char * proto){
    if(pion2.joueur == 0 || (pion2.joueur == joueur && (pion2.type<5 || pion2.type == 7))){
        int x = pion2.x;
        int y = pion2.y;
        coup * coupSuivant = coupPossible;
        if (strcmp(how, "+")) {
            switch (pionDepart.type) {
                case 7:
                    if(x < 7 && y < 7 && joueur == 'A')coupSuivant = checkDeploiementCompose(pionDepart,"+*",grilleActuelle[x+1][y+1],joueur,coupSuivant,grilleActuelle,concat(concat(proto, "+"),convertit(x, y)));
                    if(y < 7 && x > 0 && joueur == 'A')coupSuivant = checkDeploiementCompose(pionDepart,"+*",grilleActuelle[x-1][y+1],joueur,coupSuivant,grilleActuelle,concat(concat(proto, "+"),convertit(x, y)));
                    if(x > 0 && y > 0 && joueur == 'B')coupSuivant = checkDeploiementCompose(pionDepart,"+*",grilleActuelle[x-1][y-1],joueur,coupSuivant,grilleActuelle,concat(concat(proto, "+"),convertit(x, y)));
                    if(y > 0 && x < 7 && joueur == 'B')coupSuivant = checkDeploiementCompose(pionDepart,"+*",grilleActuelle[x+1][y-1],joueur,coupSuivant,grilleActuelle,concat(concat(proto, "+"),convertit(x, y)));
                case 9:
                    if(x < 6 && y < 6 && joueur == 'A')coupSuivant = checkDeploiementCompose(pionDepart,"+**",grilleActuelle[x+2][y+2],joueur,coupSuivant,grilleActuelle,concat(concat(concat(concat(proto, "*"),convertit(x+1, y+1)),"-"),convertit(x+2, y+2)));
                    if(y < 6 && x > 1 && joueur == 'A')coupSuivant = checkDeploiementCompose(pionDepart,"+**",grilleActuelle[x+2][y+2],joueur,coupSuivant,grilleActuelle,concat(concat(concat(concat(proto, "*"),convertit(x-1, y+1)),"-"),convertit(x-2, y+2)));
                    if(x > 1 && y > 1 && joueur == 'B')coupSuivant = checkDeploiementCompose(pionDepart,"+**",grilleActuelle[x+2][y+2],joueur,coupSuivant,grilleActuelle,concat(concat(concat(concat(proto, "*"),convertit(x-1, y-1)),"-"),convertit(x-2, y-2)));
                    if(y > 1 && x < 6 && joueur == 'B')coupSuivant = checkDeploiementCompose(pionDepart,"+**",grilleActuelle[x+2][y+2],joueur,coupSuivant,grilleActuelle,concat(concat(concat(concat(proto, "*"),convertit(x+1, y-1)),"-"),convertit(x+2, y-2)));
                    if(x == 6 && y < 6 && joueur == 'A')coupSuivant = checkDeploiementCompose(pionDepart,"+**",grilleActuelle[x+2][y+2],joueur,coupSuivant,grilleActuelle,concat(concat(concat(concat(proto, "*"),convertit(x+1, y+1)),"-"),convertit(x+1, y+2)));
                    if(y < 6 && x == 1 && joueur == 'A')coupSuivant = checkDeploiementCompose(pionDepart,"+**",grilleActuelle[x+2][y+2],joueur,coupSuivant,grilleActuelle,concat(concat(concat(concat(proto, "*"),convertit(x-1, y+1)),"-"),convertit(x-1, y+2)));
                    if(x == 1 && y > 1 && joueur == 'B')checkDeploiementCompose(pionDepart,"+**",grilleActuelle[x+2][y+2],joueur,coupSuivant,grilleActuelle,concat(concat(concat(concat(proto, "*"),convertit(x-1, y-1)),"-"),convertit(x-1, y-2)));
                    if(y > 1 && x == 6 && joueur == 'B')checkDeploiementCompose(pionDepart,"+**",grilleActuelle[x+2][y+2],joueur,coupSuivant,grilleActuelle,concat(concat(concat(concat(proto, "*"),convertit(x+1, y-1)),"-"),convertit(x+1, y-2)));
                    break;
                }
        }
        else if(strcmp(how, "*")){
            switch (pionDepart.type) {
                case 7:
                    if(joueur == 'A' && y < 7) coupSuivant = checkDeploiementCompose(pionDepart,"*+",grilleActuelle[x][y+1],joueur,coupSuivant,grilleActuelle,concat(concat(proto, "*"),convertit(x, y)));
                    if(joueur == 'B' && y > 0) coupSuivant = checkDeploiementCompose(pionDepart,"*+",grilleActuelle[x][y-1],joueur,coupSuivant,grilleActuelle,concat(concat(proto, "*"),convertit(x, y)));
                    if(x < 7)coupSuivant = checkDeploiementCompose(pionDepart,"*+",grilleActuelle[x+1][y],joueur,coupSuivant,grilleActuelle,concat(concat(proto, "*"),convertit(x, y)));
                    if(x > 0)coupSuivant = checkDeploiementCompose(pionDepart,"*+",grilleActuelle[x-1][y],joueur,coupSuivant,grilleActuelle,concat(concat(proto, "*"),convertit(x, y)));
                case 8:
                    break;
            }
        }
        else if(strcmp(how, "++")){
            //Type 8
            if(x < 7 && y < 7 && joueur == 'A')coupSuivant = checkDeploiementCompose(pionDepart,"++*",grilleActuelle[x+1][y+1],joueur,coupSuivant,grilleActuelle,concat(concat(proto, "+"),convertit(x, y)));
            if(y < 7 && x > 0 && joueur == 'A')coupSuivant = checkDeploiementCompose(pionDepart,"++*",grilleActuelle[x-1][y+1],joueur,coupSuivant,grilleActuelle,concat(concat(proto, "+"),convertit(x, y)));
            if(x > 0 && y > 0 && joueur == 'B')coupSuivant = checkDeploiementCompose(pionDepart,"++*",grilleActuelle[x-1][y-1],joueur,coupSuivant,grilleActuelle,concat(concat(proto, "+"),convertit(x, y)));
            if(y > 0 && x < 7 && joueur == 'B')coupSuivant = checkDeploiementCompose(pionDepart,"++*",grilleActuelle[x+1][y-1],joueur,coupSuivant,grilleActuelle,concat(concat(proto, "+"),convertit(x, y)));
        }
        else if(strcmp(how, "**")){
            //Type 9
            if(joueur == 'A' && y < 7) coupSuivant = checkDeploiementCompose(pionDepart,"**+",grilleActuelle[x][y+1],joueur,coupSuivant,grilleActuelle,concat(concat(proto, "*"),convertit(x, y)));
            if(joueur == 'B' && y > 0) coupSuivant = checkDeploiementCompose(pionDepart,"**+",grilleActuelle[x][y-1],joueur,coupSuivant,grilleActuelle,concat(concat(proto, "*"),convertit(x, y)));
            if(x < 7)coupSuivant = checkDeploiementCompose(pionDepart,"**+",grilleActuelle[x+1][y],joueur,coupSuivant,grilleActuelle,concat(concat(proto, "*"),convertit(x, y)));
            if(x > 0)coupSuivant = checkDeploiementCompose(pionDepart,"**+",grilleActuelle[x-1][y],joueur,coupSuivant,grilleActuelle,concat(concat(proto, "*"),convertit(x, y)));
        }
        else if (strcmp(how, "+*")) {
            coup *newCoup;
            newCoup = malloc(sizeof(coup));
            coupSuivant->coupSuivant = newCoup;
            coupSuivant->proto = concat(concat(proto, "*"),convertit(x, y));
            return newCoup;
            
        }
        else if (strcmp(how, "*+")) {
            coup *newCoup;
            newCoup = malloc(sizeof(coup));
            coupSuivant->coupSuivant = newCoup;
            coupSuivant->proto = concat(concat(proto, "+"),convertit(x, y));
            return newCoup;
            }
        
        else if (strcmp(how, "*++")) {
            coup *newCoup;
            newCoup = malloc(sizeof(coup));
            coupSuivant->coupSuivant = newCoup;
            coupSuivant->proto = concat(concat(proto, "+"),convertit(x, y));
            return newCoup;
        }
        else if (strcmp(how, "++*")) {
            coup *newCoup;
            newCoup = malloc(sizeof(coup));
            coupSuivant->coupSuivant = newCoup;
            coupSuivant->proto = concat(concat(proto, "*"),convertit(x, y));
            return newCoup;
        }
        else if (strcmp(how, "**+")) {
            coup *newCoup;
            newCoup = malloc(sizeof(coup));
            coupSuivant->coupSuivant = newCoup;
            coupSuivant->proto = concat(concat(proto, "+"),convertit(x, y));
            return newCoup;
        }
        else if (strcmp(how, "+**")) {
            coup *newCoup;
            newCoup = malloc(sizeof(coup));
            coupSuivant->coupSuivant = newCoup;
            coupSuivant->proto = concat(concat(proto, "*"),convertit(x, y));
            return newCoup;
        }
        

    }
    return coupPossible;
}


coup* checkDeploiement2(pion pionDepart,pion pion1,pion pion2,char joueur,coup* coupPossible,pion ** grilleActuelle){
    return coupPossible;
}

coup* checkDeploiement3(pion pionDepart,pion pion1,pion pion2,pion pion3,char joueur,coup* coupPossible,pion ** grilleActuelle){
    return coupPossible;
}

coup* coupsPossibles(pion** grilleActuelle,char joueur){
    coup * coupPremier;
    coupPremier = malloc(sizeof(coup *));
    coup * coupSuivant = coupPremier;
    int x = 0,y=0;
    for (x=0; x<8; x++) {
        for (y=8; y<8; x++) {
            if ((*(*(grilleActuelle+x)+y)).joueur == joueur) {
                switch ((*(*(grilleActuelle+x)+y)).type)
                {
                    case 1:
                        //Victoire
                        if(joueur == 'A' && y == 7) coupSuivant = victoire(grilleActuelle[x][y], joueur, coupSuivant,grilleActuelle);
                        if(joueur == 'B' && y == 0) coupSuivant = victoire(grilleActuelle[x][y], joueur, coupSuivant,grilleActuelle);
                        //Deplacement
                        if(joueur == 'A' && y < 7) coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x][y+1],joueur,coupSuivant,grilleActuelle);
                        if(joueur == 'B' && y > 0) coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x][y-1],joueur,coupSuivant,grilleActuelle);
                        if(x < 7)coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x+1][y],joueur,coupSuivant,grilleActuelle);
                        if(x > 0)coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x-1][y],joueur,coupSuivant,grilleActuelle);
                        break;
                    case 2:
                        //Victoire
                        if(y == 7 && joueur == 'A') coupSuivant = victoire(grilleActuelle[x][y], joueur, coupSuivant,grilleActuelle);
                        if(y == 0 && joueur == 'B') coupSuivant = victoire(grilleActuelle[x][y], joueur, coupSuivant,grilleActuelle);
                        //Déplacement
                        if(x < 7 && y < 7 && joueur == 'A')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x+1][y+1],joueur,coupSuivant,grilleActuelle);
                        if(y < 7 && x > 0 && joueur == 'A')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x-1][y+1],joueur,coupSuivant,grilleActuelle);
                        if(x > 0 && y > 0 && joueur == 'B')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x-1][y-1],joueur,coupSuivant,grilleActuelle);
                        if(y > 0 && x < 7 && joueur == 'B')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x+1][y-1],joueur,coupSuivant,grilleActuelle);
                        break;
                    case 3:
                        //Victoire
                        if(joueur == 'A' && y >= 6)coupSuivant = victoire(grilleActuelle[x][y], joueur, coupSuivant,grilleActuelle);
                        if(joueur == 'B' && y <= 1)coupSuivant = victoire(grilleActuelle[x][y], joueur, coupSuivant,grilleActuelle);
                        //Déplacement
                        if(joueur == 'A' && y < 7)coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x][y+1],joueur,coupSuivant,grilleActuelle);
                        if(joueur == 'A' && y < 6)coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x][y+2],joueur,coupSuivant,grilleActuelle);
                        if(joueur == 'B' && y > 0)coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x][y-1],joueur,coupSuivant,grilleActuelle);
                        if(joueur == 'B' && y > 1)coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x][y-2],joueur,coupSuivant,grilleActuelle);
                        if(x < 7)coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x+1][y],joueur,coupSuivant,grilleActuelle);
                        if(x > 0)coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x-1][y],joueur,coupSuivant,grilleActuelle);
                        if(x < 6)coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x+2][y],joueur,coupSuivant,grilleActuelle);
                        if(x > 1)coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x-2][y],joueur,coupSuivant,grilleActuelle);
                        //Déploiement
                        if(x == 6)coupSuivant = checkDeploiement2(grilleActuelle[x][y],grilleActuelle[x+1][y],grilleActuelle[x+1][y],joueur,coupSuivant,grilleActuelle);
                        if(x < 6)coupSuivant = checkDeploiement2(grilleActuelle[x][y],grilleActuelle[x+1][y],grilleActuelle[x+2][y],joueur,coupSuivant,grilleActuelle);
                        if(x == 1)coupSuivant = checkDeploiement2(grilleActuelle[x][y],grilleActuelle[x-1][y],grilleActuelle[x-1][y],joueur,coupSuivant,grilleActuelle);
                        if(x > 1)coupSuivant = checkDeploiement2(grilleActuelle[x][y],grilleActuelle[x-1][y],grilleActuelle[x-2][y],joueur,coupSuivant,grilleActuelle);
                        if(y < 6 && joueur == 'A' )coupSuivant = checkDeploiement2(grilleActuelle[x][y],grilleActuelle[x][y+1],grilleActuelle[x][y+2],joueur,coupSuivant,grilleActuelle);
                        if(y > 2 && joueur == 'B' )coupSuivant = checkDeploiement2(grilleActuelle[x][y],grilleActuelle[x][y-1],grilleActuelle[x][y-2],joueur,coupSuivant,grilleActuelle);
                        break;
                    case 4:
                        //Victoire
                        if(y >= 6 && joueur == 'A') coupSuivant = victoire(grilleActuelle[x][y], joueur, coupSuivant,grilleActuelle);
                        if(y <= 1 && joueur == 'B') coupSuivant = victoire(grilleActuelle[x][y], joueur, coupSuivant,grilleActuelle);
                        //Déplacement
                        if(x < 7 && y < 7 && joueur == 'A')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x+1][y+1],joueur,coupSuivant,grilleActuelle);
                        if(y < 7 && x > 0 && joueur == 'A')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x-1][y+1],joueur,coupSuivant,grilleActuelle);
                        if(x > 0 && y > 0 && joueur == 'B')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x-1][y-1],joueur,coupSuivant,grilleActuelle);
                        if(y > 0 && x < 7 && joueur == 'B')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x+1][y-1],joueur,coupSuivant,grilleActuelle);
                        if(x < 6 && y < 6 && joueur == 'A')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x+2][y+2],joueur,coupSuivant,grilleActuelle);
                        if(y < 6 && x > 1 && joueur == 'A')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x-2][y+2],joueur,coupSuivant,grilleActuelle);
                        if(x > 1 && y > 1 && joueur == 'B')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x-2][y-2],joueur,coupSuivant,grilleActuelle);
                        if(y > 1 && x < 6 && joueur == 'B')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x+2][y-2],joueur,coupSuivant,grilleActuelle);
                        if(x == 6 && y < 6 && joueur == 'A')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x+1][y+2],joueur,coupSuivant,grilleActuelle);
                        if(y < 6 && x == 1 && joueur == 'A')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x-1][y+2],joueur,coupSuivant,grilleActuelle);
                        if(x == 1 && y > 1 && joueur == 'B')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x-1][y-2],joueur,coupSuivant,grilleActuelle);
                        if(y > 1 && x == 6 && joueur == 'B')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x+1][y-2],joueur,coupSuivant,grilleActuelle);
                        //Déploiement
                        if(x < 6 && y < 6 && joueur == 'A')coupSuivant = checkDeploiement2(grilleActuelle[x][y],grilleActuelle[x+1][y+1],grilleActuelle[x+2][y+2],joueur,coupSuivant,grilleActuelle);
                        if(y < 6 && x > 1 && joueur == 'A')coupSuivant = checkDeploiement2(grilleActuelle[x][y],grilleActuelle[x-1][y+2],grilleActuelle[x-2][y+2],joueur,coupSuivant,grilleActuelle);
                        if(x > 1 && y > 1 && joueur == 'B')coupSuivant = checkDeploiement2(grilleActuelle[x][y],grilleActuelle[x-1][y-1],grilleActuelle[x-2][y-2],joueur,coupSuivant,grilleActuelle);
                        if(y > 1 && x < 6 && joueur == 'B')coupSuivant = checkDeploiement2(grilleActuelle[x][y],grilleActuelle[x+1][y-1],grilleActuelle[x+2][y-2],joueur,coupSuivant,grilleActuelle);
                        if(x == 6 && y < 6 && joueur == 'A')coupSuivant = checkDeploiement2(grilleActuelle[x][y],grilleActuelle[x+1][y+1],grilleActuelle[x+1][y+2],joueur,coupSuivant,grilleActuelle);
                        if(y < 6 && x == 1 && joueur == 'A')coupSuivant = checkDeploiement2(grilleActuelle[x][y],grilleActuelle[x-1][y+1],grilleActuelle[x-1][y+2],joueur,coupSuivant,grilleActuelle);
                        if(x == 1 && y > 1 && joueur == 'B')coupSuivant = checkDeploiement2(grilleActuelle[x][y],grilleActuelle[x-1][y-1],grilleActuelle[x-1][y-2],joueur,coupSuivant,grilleActuelle);
                        if(y > 1 && x == 6 && joueur == 'B')coupSuivant = checkDeploiement2(grilleActuelle[x][y],grilleActuelle[x+1][y-1],grilleActuelle[x+1][y-2],joueur,coupSuivant,grilleActuelle);
                        break;
                    case 5:
                        //Victoire
                        if(joueur == 'A' && y >= 5)coupSuivant = victoire(grilleActuelle[x][y], joueur, coupSuivant,grilleActuelle);
                        if(joueur == 'B' && y <= 2)coupSuivant = victoire(grilleActuelle[x][y], joueur, coupSuivant,grilleActuelle);
                        //Déplacement
                        if(joueur == 'A' && y < 7)coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x][y+1],joueur,coupSuivant,grilleActuelle);
                        if(joueur == 'A' && y < 6)coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x][y+2],joueur,coupSuivant,grilleActuelle);
                        if(joueur == 'A' && y < 5)coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x][y+3],joueur,coupSuivant,grilleActuelle);
                        if(joueur == 'B' && y > 0)coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x][y-1],joueur,coupSuivant,grilleActuelle);
                        if(joueur == 'B' && y > 1)coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x][y-2],joueur,coupSuivant,grilleActuelle);
                        if(joueur == 'B' && y > 2)coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x][y-3],joueur,coupSuivant,grilleActuelle);
                        if(x < 7)coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x+1][y],joueur,coupSuivant,grilleActuelle);
                        if(x > 0)coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x-1][y],joueur,coupSuivant,grilleActuelle);
                        if(x < 6)coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x+2][y],joueur,coupSuivant,grilleActuelle);
                        if(x > 1)coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x-2][y],joueur,coupSuivant,grilleActuelle);
                        if(x < 5)coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x+3][y],joueur,coupSuivant,grilleActuelle);
                        if(x > 2)coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x-3][y],joueur,coupSuivant,grilleActuelle);
                        if(x == 6)coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x][y],joueur,coupSuivant,grilleActuelle);
                        if(x == 1)coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x][y],joueur,coupSuivant,grilleActuelle);
                        //Déploiement
                        if(joueur == 'A' && y < 5)coupSuivant = checkDeploiement3(grilleActuelle[x][y],grilleActuelle[x][y+1],grilleActuelle[x][y+2],grilleActuelle[x][y+3],joueur,coupSuivant,grilleActuelle);
                        if(joueur == 'B' && y > 2)coupSuivant = checkDeploiement3(grilleActuelle[x][y],grilleActuelle[x][y-1],grilleActuelle[x][y-2],grilleActuelle[x][y-3],joueur,coupSuivant,grilleActuelle);
                        if(x == 6)coupSuivant = checkDeploiement3(grilleActuelle[x][y],grilleActuelle[x+1][y],grilleActuelle[x+1][y],grilleActuelle[x][y],joueur,coupSuivant,grilleActuelle);
                        if(x == 1)coupSuivant = checkDeploiement3(grilleActuelle[x][y],grilleActuelle[x-1][y],grilleActuelle[x-1][y],grilleActuelle[x][y],joueur,coupSuivant,grilleActuelle);
                        if(x == 5)coupSuivant = checkDeploiement3(grilleActuelle[x][y],grilleActuelle[x+1][y],grilleActuelle[x+2][y],grilleActuelle[x+2][y],joueur,coupSuivant,grilleActuelle);
                        if(x == 2)coupSuivant = checkDeploiement3(grilleActuelle[x-1][y],grilleActuelle[x-2][y],grilleActuelle[x][y],grilleActuelle[x-2][y],joueur,coupSuivant,grilleActuelle);
                        if(x < 5)coupSuivant = checkDeploiement3(grilleActuelle[x][y],grilleActuelle[x+1][y],grilleActuelle[x+2][y],grilleActuelle[x+3][y],joueur,coupSuivant,grilleActuelle);
                        if(x > 2)coupSuivant = checkDeploiement3(grilleActuelle[x][y],grilleActuelle[x-1][y],grilleActuelle[x-2][y],grilleActuelle[x-3][y],joueur,coupSuivant,grilleActuelle);
                        break;
                    case 6:
                        //Victoire
                        if(joueur == 'A' && y >= 5)coupSuivant = victoire(grilleActuelle[x][y], joueur, coupSuivant,grilleActuelle);
                        if(joueur == 'B' && y <= 2)coupSuivant = victoire(grilleActuelle[x][y], joueur, coupSuivant,grilleActuelle);
                        //Déplacement
                        if(x < 7 && y < 7 && joueur == 'A')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x+1][y+1],joueur,coupSuivant,grilleActuelle);
                        if(y < 7 && x > 0 && joueur == 'A')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x-1][y+1],joueur,coupSuivant,grilleActuelle);
                        if(x > 0 && y > 0 && joueur == 'B')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x-1][y-1],joueur,coupSuivant,grilleActuelle);
                        if(y > 0 && x < 7 && joueur == 'B')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x+1][y-1],joueur,coupSuivant,grilleActuelle);
                        if(x < 6 && y < 6 && joueur == 'A')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x+2][y+2],joueur,coupSuivant,grilleActuelle);
                        if(y < 6 && x > 1 && joueur == 'A')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x-2][y+2],joueur,coupSuivant,grilleActuelle);
                        if(x > 1 && y > 1 && joueur == 'B')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x-2][y-2],joueur,coupSuivant,grilleActuelle);
                        if(y > 1 && x < 6 && joueur == 'B')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x+2][y-2],joueur,coupSuivant,grilleActuelle);
                        if(x < 5 && y < 5 && joueur == 'A')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x+3][y+3],joueur,coupSuivant,grilleActuelle);
                        if(y < 5 && x > 2 && joueur == 'A')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x-3][y+3],joueur,coupSuivant,grilleActuelle);
                        if(x > 2 && y > 2 && joueur == 'B')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x-3][y-3],joueur,coupSuivant,grilleActuelle);
                        if(y > 2 && x < 5 && joueur == 'B')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x+3][y-3],joueur,coupSuivant,grilleActuelle);
                        //Rebond
                        if(x == 6 && y < 6 && joueur == 'A')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x+1][y+2],joueur,coupSuivant,grilleActuelle);
                        if(y < 6 && x == 1 && joueur == 'A')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x-1][y+2],joueur,coupSuivant,grilleActuelle);
                        if(x == 6 && y < 5 && joueur == 'A')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x][y+3],joueur,coupSuivant,grilleActuelle);
                        if(y < 5 && x == 1 && joueur == 'A')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x][y+3],joueur,coupSuivant,grilleActuelle);
                        if(x == 5 && y < 5 && joueur == 'A')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x+2][y+3],joueur,coupSuivant,grilleActuelle);
                        if(y < 5 && x == 2 && joueur == 'A')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x-2][y+3],joueur,coupSuivant,grilleActuelle);
                        if(x == 1 && y > 1 && joueur == 'B')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x+1][y-2],joueur,coupSuivant,grilleActuelle);
                        if(y > 1 && x == 6 && joueur == 'B')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x-1][y-2],joueur,coupSuivant,grilleActuelle);
                        if(x == 1 && y > 2 && joueur == 'B')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x][y-3],joueur,coupSuivant,grilleActuelle);
                        if(y > 2 && x == 6 && joueur == 'B')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x][y-3],joueur,coupSuivant,grilleActuelle);
                        if(x == 2 && y > 2 && joueur == 'B')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x-2][y-3],joueur,coupSuivant,grilleActuelle);
                        if(y > 2 && x == 5 && joueur == 'B')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x+2][y-3],joueur,coupSuivant,grilleActuelle);
                        //Déploiement
                        if(x < 5 && y < 5 && joueur == 'A')coupSuivant = checkDeploiement3(grilleActuelle[x][y],grilleActuelle[x+1][y+1],grilleActuelle[x+2][y+2],grilleActuelle[x+3][y+3],joueur,coupSuivant,grilleActuelle);
                        if(y < 5 && x > 2 && joueur == 'A')coupSuivant = checkDeploiement3(grilleActuelle[x][y],grilleActuelle[x-1][y+2],grilleActuelle[x-2][y+2],grilleActuelle[x-3][y+3],joueur,coupSuivant,grilleActuelle);
                        if(x > 2 && y > 2 && joueur == 'B')coupSuivant = checkDeploiement3(grilleActuelle[x][y],grilleActuelle[x-1][y-1],grilleActuelle[x-2][y-2],grilleActuelle[x-3][y-3],joueur,coupSuivant,grilleActuelle);
                        if(y > 2 && x < 5 && joueur == 'B')coupSuivant = checkDeploiement3(grilleActuelle[x][y],grilleActuelle[x+1][y-1],grilleActuelle[x+2][y-2],grilleActuelle[x+3][y-3],joueur,coupSuivant,grilleActuelle);
                        //Déploiement avec Rebond
                        if(x == 6 && y < 5 && joueur == 'A')coupSuivant = checkDeploiement3(grilleActuelle[x][y],grilleActuelle[x+1][y+1],grilleActuelle[x+1][y+2],grilleActuelle[x][y+3],joueur,coupSuivant,grilleActuelle);
                        if(y < 5 && x == 1 && joueur == 'A')coupSuivant = checkDeploiement3(grilleActuelle[x][y],grilleActuelle[x-1][y+1],grilleActuelle[x-1][y+2],grilleActuelle[x][y+3],joueur,coupSuivant,grilleActuelle);
                        if(x == 5 && y < 5 && joueur == 'A')coupSuivant = checkDeploiement3(grilleActuelle[x][y],grilleActuelle[x+1][y+1],grilleActuelle[x+2][y+2],grilleActuelle[x+2][y+3],joueur,coupSuivant,grilleActuelle);
                        if(y < 5 && x == 2 && joueur == 'A')coupSuivant = checkDeploiement3(grilleActuelle[x][y],grilleActuelle[x-1][y+1],grilleActuelle[x-2][y+2],grilleActuelle[x-2][y+3],joueur,coupSuivant,grilleActuelle);
                        if(x == 1 && y > 2 && joueur == 'B')coupSuivant = checkDeploiement3(grilleActuelle[x][y],grilleActuelle[x-1][y-1],grilleActuelle[x-1][y-2],grilleActuelle[x][y-3],joueur,coupSuivant,grilleActuelle);
                        if(y > 2 && x == 6 && joueur == 'B')coupSuivant = checkDeploiement3(grilleActuelle[x][y],grilleActuelle[x+1][y-1],grilleActuelle[x+1][y-2],grilleActuelle[x][y-3],joueur,coupSuivant,grilleActuelle);
                        if(x == 2 && y > 2 && joueur == 'B')coupSuivant = checkDeploiement3(grilleActuelle[x][y],grilleActuelle[x-1][y-1],grilleActuelle[x-2][y-2],grilleActuelle[x-2][y-3],joueur,coupSuivant,grilleActuelle);
                        if(y > 2 && x == 5 && joueur == 'B')coupSuivant = checkDeploiement3(grilleActuelle[x][y],grilleActuelle[x+1][y-1],grilleActuelle[x+2][y-2],grilleActuelle[x+2][y-3],joueur,coupSuivant,grilleActuelle);
                        break;
                    case 7:
                        //Victoire
                        if(joueur == 'A' && y == 6) coupSuivant = victoire(grilleActuelle[x][y], joueur, coupSuivant,grilleActuelle);
                        if(joueur == 'B' && y == 1) coupSuivant = victoire(grilleActuelle[x][y], joueur, coupSuivant,grilleActuelle);
                        //Déplacement Carré
                        if(joueur == 'A' && y < 7) coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x][y+1],joueur,coupSuivant,grilleActuelle);
                        if(joueur == 'B' && y > 0) coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x][y-1],joueur,coupSuivant,grilleActuelle);
                        if(x < 7)coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x+1][y],joueur,coupSuivant,grilleActuelle);
                        if(x > 0)coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x-1][y],joueur,coupSuivant,grilleActuelle);
                        //Déplacement Rond
                        if(x < 7 && y < 7 && joueur == 'A')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x+1][y+1],joueur,coupSuivant,grilleActuelle);
                        if(y < 7 && x > 0 && joueur == 'A')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x-1][y+1],joueur,coupSuivant,grilleActuelle);
                        if(x > 0 && y > 0 && joueur == 'B')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x-1][y-1],joueur,coupSuivant,grilleActuelle);
                        if(y > 0 && x < 7 && joueur == 'B')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x+1][y-1],joueur,coupSuivant,grilleActuelle);
                        //Déplacement Composé
                        if(x < 6 && y < 7 && joueur == 'A')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x+2][y+1],joueur,coupSuivant,grilleActuelle);
                        if(x > 1 && y < 7 && joueur == 'A')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x-2][y+1],joueur,coupSuivant,grilleActuelle);
                        if(x > 0 && y < 6 && joueur == 'A')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x-1][y+2],joueur,coupSuivant,grilleActuelle);
                        if(x < 7 && y < 6 && joueur == 'A')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x+1][y+2],joueur,coupSuivant,grilleActuelle);
                        if(x < 6 && y > 0 && joueur == 'B')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x+2][y-1],joueur,coupSuivant,grilleActuelle);
                        if(x > 1 && y > 0 && joueur == 'B')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x-2][y-1],joueur,coupSuivant,grilleActuelle);
                        if(x > 0 && y > 1 && joueur == 'B')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x-1][y-2],joueur,coupSuivant,grilleActuelle);
                        if(x < 7 && y > 1 && joueur == 'B')coupSuivant = checkDeplacement(grilleActuelle[x][y],grilleActuelle[x+1][y-2],joueur,coupSuivant,grilleActuelle);
                        //Déploiement
                        if(joueur == 'A' && y < 7) coupSuivant = checkDeploiementCompose(grilleActuelle[x][y],"+",grilleActuelle[x][y+1],joueur,coupSuivant,grilleActuelle,convertit(x, y));
                        if(joueur == 'B' && y > 0) coupSuivant = checkDeploiementCompose(grilleActuelle[x][y],"+",grilleActuelle[x][y-1],joueur,coupSuivant,grilleActuelle,convertit(x, y));
                        if(x < 7)coupSuivant = checkDeploiementCompose(grilleActuelle[x][y],"+",grilleActuelle[x+1][y],joueur,coupSuivant,grilleActuelle,convertit(x, y));
                        if(x > 0)coupSuivant = checkDeploiementCompose(grilleActuelle[x][y],"+",grilleActuelle[x-1][y],joueur,coupSuivant,grilleActuelle,convertit(x, y));
                        if(x < 7 && y < 7 && joueur == 'A')coupSuivant = checkDeploiementCompose(grilleActuelle[x][y],"*",grilleActuelle[x+1][y+1],joueur,coupSuivant,grilleActuelle,convertit(x, y));
                        if(y < 7 && x > 0 && joueur == 'A')coupSuivant = checkDeploiementCompose(grilleActuelle[x][y],"*",grilleActuelle[x-1][y+1],joueur,coupSuivant,grilleActuelle,convertit(x, y));
                        if(x > 0 && y > 0 && joueur == 'B')coupSuivant = checkDeploiementCompose(grilleActuelle[x][y],"*",grilleActuelle[x-1][y-1],joueur,coupSuivant,grilleActuelle,convertit(x, y));
                        if(y > 0 && x < 7 && joueur == 'B')coupSuivant = checkDeploiementCompose(grilleActuelle[x][y],"*",grilleActuelle[x+1][y-1],joueur,coupSuivant,grilleActuelle,convertit(x, y));
                        
                        //Déploiement Rebond
                        break;
                    case 8:
                        
                        break;
                    case 9:
                        
                        break;
                }
            }
        }
    }
    return coupPremier;
}
