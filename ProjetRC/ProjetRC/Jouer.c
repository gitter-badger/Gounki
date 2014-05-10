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

char * advice;
int victoire = 0;
pion ** grilleCancel;
pion ** grilleReDo;

char * correrction(pion ** grille,char * proto,coup* pere){
  if(proto[2] == '*' || proto[2] == '+')
  {
    pion ** grilleCpy = copieGrille(grille);
    char * protoA = calloc(5, sizeof(char));
    char * protoB = calloc(8, sizeof(char));
    int i =0;
    switch (strlen(proto)) {
      case 8:
      if(action(grilleCpy, proto, pere, 0)!=-1){
        break;
      }
      for (i=0; i<5; i++) {
        protoA[i]= proto[i];
      }

      if(action(grilleCpy, protoA, pere, 0)!=-1){
        proto[5]=0;
        break;
      }

      for (i=3; i<5; i++) {
        protoA[i]= proto[i+3];
      }

      if(action(grilleCpy, protoA, pere, 0)!=-1){
        for (i=0; i<5; i++) {
          proto[i]= protoA[i];
        }
        proto[5]=0;
        break;
      }
      break;
      case 11:
      for (i=0; i<5; i++) {
        protoA[i]= proto[i];
      }

      if(action(grilleCpy, protoA, pere, 0)!=-1){
        proto[5]=0;
        break;
      }

      for (i=3; i<5; i++) {
        protoA[i]= proto[i+3];
      }

      if(action(grilleCpy, protoA, pere, 0)!=-1){
        for (i=0; i<5; i++) {
          proto[i]= protoA[i];
        }
        proto[5]=0;
        break;
      }

      for (i=3; i<5; i++) {
        protoA[i]= proto[i+6];
      }

      if(action(grilleCpy, protoA, pere, 0)!=-1){
        for (i=0; i<5; i++) {
          proto[i]= protoA[i];
        }
        proto[5]=0;
        break;
      }

      for (i=0; i<8; i++) {
        protoB[i]= proto[i];
      }
      if(action(grilleCpy, protoB, pere, 0)!=-1){
        proto[8]=0;
        break;
      }

      for (i=5; i<8; i++) {
        protoB[i]= proto[i+3];
      }
      if(action(grilleCpy, protoB, pere, 0)!=-1){
        for (i=0; i<8; i++) {
          proto[i]= protoB[i];
        }
        proto[8]=0;
        break;
      }


      for (i=3; i<8; i++) {
        protoB[i]= proto[i+3];
      }

      if(action(grilleCpy, protoB, pere, 0)!=-1){
        for (i=0; i<8; i++) {
          proto[i]= protoB[i];
        }
        proto[8]=0;
        break;
      }
      break;
    }
      free(protoA);protoA=NULL;
      free(protoB);protoB = NULL;
    freeGrille(grilleCpy);
  }
  return proto;
}

void setVictoire(int v){
  victoire = v;
}

void setAdvice(char * ad){
  int i = 0;
  for (i=0;i<strlen(ad);i++)advice[i] = ad[i];
}

/*void setGrilleCancel(pion ** grille){
  static int f = 0;
  if(f)freeGrille(grilleCancel);
  grilleCancel = grille;
  f=1;
}

void setGrilleReDo(pion ** grille){
  static int f = 0;
  if(f)freeGrille(grilleReDo);
  grilleReDo = grille;
  f=1;
}
*/

void viderBuffer()
{
  int c = 0;
  while (c != '\n' && c != EOF)
  {
    c = getchar();
  }
}

void interaction(char * coup , pion ** grille , char* joueur , int mode, struct coup * pere){
  fgets(coup, 13, stdin);
  int len = strlen(coup);
  coup[len-1]=0;
  if(!strcmp(coup, "save")){
    save(grille, *joueur, mode);
  }
  else if(!strcmp(coup, "exit")){
    freeGrille(grille);
    free(advice);
    exit(1);
  }
  else if(!strcmp(coup, "help")){
    printf("Pour faire un déplacment : c2-d3\nPour faire un déploiement simple : c2+b2 pour les carrés\nPour faire un déploiement simple : c2*b3 pour les rond\nPour les deploiement composées c2*b3-b4 pour ce commencé par rond\nPour les deploiement composées c2+c3-b4 pour ce commencé par rond\nTaper help pour afficher ce menu\nTaper save pour sauvegarder\nTaper exit pour quitter le jeu\nTaper advice pour un conseil\nTaper cancel pour annuler le dernier coup jouer\n Taper redo pour refaire le coup annuler\n");
  }
  else if(!strcmp(coup, "advice")){
    int difficulter = -1;
    printf("Taper un nombre de 0 à 4 pour la qualite \n");
    while (difficulter<0||difficulter>4) {
      scanf("%d", &difficulter);
      viderBuffer();
    }
    pion ** grilleCpy = copieGrille(grille);
    jouerCoupIA(grilleCpy, *joueur, difficulter, 1);
    freeGrille(grilleCpy);
    printf("advice : %s \n", advice);
  }
  /*    else if(!strcmp(coup, "cancel")){
  if(mode == 1){
  if(*joueur == 'A')*joueur = 'B';
  else *joueur = 'A';
}
setGrilleReDo(grille);
grille = grilleCancel;
freeCoup(pere, 1);
pere = malloc(sizeof(struct coup));
pere->proto = NULL;
pere->coupSuivant = NULL;
pere = coupsPossibles(grille, *joueur,pere);
updateMap(grille);
affiche();
}
else if(!strcmp(coup, "redo")){
if(*joueur == 'A')*joueur = 'B';
else *joueur = 'A';
}
*/
else{
  coup = correrction(grille, coup, pere);
  printf("%s\n",coup);
}
}


void jouer(){
  advice = calloc(16,sizeof(char));
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
    if(chargement [0] == '#'){
      mode = charToInt(chargement[1]);
      joueur = chargement[2];
      grille = grilleString(grille,chargement+4);
        free(chargement);chargement = NULL;
    }
    else {
      mode = 0;
      grille = grilleString(grille,chargement);
        free(chargement);chargement = NULL;
    }
  }
  else mode = 0;

  if(mode == 0)printf("Pour jouer a deux taper 1\nPour jouer Contre l'IA taper 2 \nPour faire jouer deux IA taper 3\n");
  while (mode==0) {
    scanf("%d", &mode);
    viderBuffer();
  }
  printf("Vous pouvez taper help a tout moment dans le jeu pour avoir accée a differente option \n");
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
        interaction(coup,grille,&joueur,mode,pere);
      }
      while (action(grille, coup, pere,1)==-1);

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
          interaction(coup, grille, &joueur, mode,pere);
        }
        while (action(grille, coup, pere,1)==-1);
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
