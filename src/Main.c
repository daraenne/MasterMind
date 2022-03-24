// compilation :
// gcc src/*.c -o bin/MasterMind -I include -L lib/SDL -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -mwindows (-mwindows pour qu'il n'y est pas de terminal)
//fichiers generaux
#include <stdlib.h>
//mes fichiers
#include <Define.h>
#include <MachineAEtat.h>
#include <Affichage.h>

//main du programme (simople boucle infini sur la machine a etat)
int main(int argc,char **argv){
    InitSDL();                                          //initialisation de la SDL
    Etat_t etat_courant = Init;                         //initialisation de la machine a etat
    while(1){                                           //machine a etat
        Current_State(etat_courant);
        etat_courant = Next_State(etat_courant);
    }
    //ne seras jamais utiliser
    return EXIT_SUCCESS;
}
