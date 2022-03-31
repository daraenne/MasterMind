/*compilation :
*   gcc src/*.c -o bin/MasterMind -I include -L lib/SDL -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf
*   ajouter -mwindows a la fin pour qu'il n'y est pas d'utilisation du terminal
*/

//include
    //natif au C
        #include <stdlib.h>
    //nos fichiers
        #include <Define.h>
        #include <MachineAEtat.h>
        #include <Affichage.h>
//


//main du programme (simple boucle infini sur la machine a etat)
int main(int argc,char **argv){
    InitSDL();                                           //initialisation de la SDL
    etat_courant = Init;                                 //initialisation de la machine a etat
    while(1){                                            //machine a etat
        Current_State(etat_courant);
        etat_courant = Next_State(etat_courant);
    }
    
    //ne seras jamais utiliser
    return EXIT_SUCCESS;
}
