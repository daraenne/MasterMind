// compilation :
// gcc src/*.c -o bin/MasterMind -I include -L lib/SDL -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -mwindows (-mwindows pour qu'il n'y est pas de terminal)
//fichiers generaux
#include <stdlib.h>
//mes fichiers
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
