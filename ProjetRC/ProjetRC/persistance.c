//
//  persistance.c
//  ProjetRC
//
//  Created by Etienne Toussaint on 08/05/2014.
//  Copyright (c) 2014 Etienne Toussaint. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "persistance.h"

void viderBufferb()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

char inToChar(int i){
    char result = 48+i;
    return result;
}

int charToInt(char c){
    int result = (int)c-48;
    return result;
}

void save(pion ** grille, char joueur, int mode){
    time_t result = time(NULL);
    char * date = asctime(localtime(&result));
    date[strlen(date)-1]=0;
    char * name = calloc(60,sizeof(char));
    strcat(name,"./Sauvegarde/");
    strcat(name,date);
    FILE * fichier = fopen((const char *)name, "w");
    char * sauvegarde = calloc(130,sizeof(char));
    sauvegarde[0]=inToChar(mode);
    sauvegarde[1]=joueur;
    int i = 2;
    for (i=0; i<64; i++) {
        sauvegarde[2*i+2]=inToChar(grille[i/8][i%8].type);
        sauvegarde[2*i+3]=grille[i/8][i%8].joueur;
    }
    fprintf(fichier,"%s",sauvegarde);
    //free(result);
    //free(date);
    free(name);
    free(sauvegarde);
    fclose(fichier);
}
char * charger(){
    struct dirent *lecture;
    DIR *rep;
    rep = opendir("./Sauvegarde/" );
    
    int i = 0;
    while ((lecture = readdir(rep))) {
        char * lec = lecture->d_name;
        if(lec[0]!='.') printf("Pour ouvrir : %s taper %d \n",lec,i+1);
        i++;
    }
    int choix = 0;
    while (choix==0) {
        scanf("%d", &choix);
        viderBufferb();
    }
    closedir(rep);
    rep = opendir("./Sauvegarde/" );
    for (i = 0; i<choix; i++){
        lecture = readdir(rep);
    }
    char * name = calloc(60,sizeof(char));
    strcat(name,"./Sauvegarde/");
    strcat(name,lecture->d_name);
    closedir(rep);
    
    FILE * fichier = fopen(name, "r");
    free(name);
    char * chargement = calloc(130,sizeof(char));
    fread( chargement , 130*sizeof(char) , 1 , fichier );
    fclose(fichier);
    
    return chargement;
}