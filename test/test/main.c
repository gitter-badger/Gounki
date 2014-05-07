#include <stdlib.h>
#include <stdio.h>

int main(){
    int tab[3][3][3];
    int (*q0)[3],(*q1)[3][3],(**q2)[3];
    void * test = *q1;
    q2 = &q0;
    
}
