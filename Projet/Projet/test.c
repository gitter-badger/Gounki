#include <stdio.h>
#include <stdlib.h>
#import "Pion.h"
#define clear()     printf("\033[H\033[2J")
#define fond1()     printf("\033[40m"); //fond noir
#define fond2()     printf("\033[47m"); //fond grise.
#define BLUE        "\033[1;34m"
#define BLACK       "\033[0;30m"

char ** map;
void initMap(){
    int i,j;
    char a;
    map=malloc(sizeof(char *)*17);
    for (i=0; i<17; i++) {
        map[i]=malloc(sizeof(char)*17);
    }
    for (i=0; i<17; i++) {
        for (j=0; j<17; j++) {
            map[i][j]=' ';
        }
    }
    a=49;
    for (i=1; i<16; i+=2) {
        map[0][i]=a;
        a++;
    }
    a=65;
    for (i=1; i<16; i+=2) {
        map[i][16]=a;
        a++;
    }
}
int joueurs(){
    return 0;
}
void affiche(){
    int i,j,a=0,b=0,c=1;//a,b,c me serve a alterner les cases noir et grise.
    for (j=16; j>=0; j--){
        for (i=0; i<17; i++){
            if (i>0 && j<16){
                if(b%2==0){
                    fond1();
                }
                else{
                    fond2();
                }
                a++;
                if(a==2){
                    b++;
                    a=0;
                }
            }
            
            if(i==0 && c==2){
                b++;
                c=0;
            }
            if (i==0 || j==16){
                printf ("\033[0m");
            }
            printf("%c",map[i][j]);
        }
        c++;
        printf("\n");
    }
    printf ("\033[0m");
    
}

void updateMap(pion ** grille){
    int x =0,y=0;
    for (x=0; x<8; x++) {
        for (y=0; y<8; y++) {
            switch (grille[x][y].type) {
                case 1:
                    map[x*2+1][y*2]=grille[x][y].joueur;
                    map[x*2+2][y*2]='C';
                    break;
                case 2:
                    map[x*2+1][y*2]=grille[x][y].joueur;
                    map[x*2+2][y*2]='R';
                    break;
                case 3:
                    map[x*2+1][y*2]=grille[x][y].joueur;
                    map[x*2+2][y*2]='C';
                    map[x*2+1][y*2+1]='C';
                    break;
                case 4:
                    map[x*2+1][y*2]=grille[x][y].joueur;
                    map[x*2+2][y*2]='R';
                    map[x*2+1][y*2+1]='R';
                    break;
                case 5:
                    map[x*2+1][y*2]=grille[x][y].joueur;
                    map[x*2+2][y*2]='C';
                    map[x*2+1][y*2+1]='C';
                    map[x*2+2][y*2+1]='C';
                    break;
                case 6:
                    map[x*2+1][y*2]=grille[x][y].joueur;
                    map[x*2+2][y*2]='R';
                    map[x*2+1][y*2+1]='R';
                    map[x*2+2][y*2+1]='R';
                    break;
                case 7:
                    map[x*2+1][y*2]=grille[x][y].joueur;
                    map[x*2+2][y*2]='C';
                    map[x*2+1][y*2+1]='R';
                    break;
                case 8:
                    map[x*2+1][y*2]=grille[x][y].joueur;
                    map[x*2+2][y*2]='C';
                    map[x*2+1][y*2+1]='C';
                    map[x*2+2][y*2+1]='R';
                    break;
                case 9:
                    map[x*2+1][y*2]=grille[x][y].joueur;
                    map[x*2+2][y*2]='C';
                    map[x*2+1][y*2+1]='R';
                    map[x*2+2][y*2+1]='R';
                    break;
                case 0:
                    map[x*2+1][y*2]=' ';
                    map[x*2+2][y*2]=' ';
                    map[x*2+1][y*2+1]=' ';
                    map[x*2+2][y*2+1]=' ';
                    break;
                    
            }
            
        }
    }

}