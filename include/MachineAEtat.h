#ifndef MACHINE_A_ETAT_H
#define MACHINE_A_ETAT_H

//include 
    //nos fichiers
        #include <Define.h>
//

//fonctions
    Etat_t Next_State(Etat_t CurrentState);             //fonction servant a faire les test de transitions entre les etats
    void Current_State(Etat_t etat_courant);            //fonction faisant les actions des etats
// 

#endif // !MACHINE_A_ETAT_H
