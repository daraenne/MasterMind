// compilation :
// gcc src/*.c -o bin/prog -I include -L lib/SDL -lmingw32 -lSDL2main -lSDL2
//fichiers generaux
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
//mes fichiers
#include <SDL/SDL.h>
#include <Define.h>
#include <MachineAEtat.h>
#include <Affichage.h>


int main(int argc,char **argv){
    InitSDL();
    Etat_t etat_courant = Init;

    while(1){
        Current_State(etat_courant);
        etat_courant = Next_State(etat_courant);
    }

    return EXIT_SUCCESS;
}
