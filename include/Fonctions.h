#ifndef FONCTIONS_H
#define FONCTIONS_H

//include
    //nos fichiers
        #include <Define.h>
//

//fonctions
    unsigned char test_valid(unsigned char tour[], unsigned char code[]);                                   //fonction testant la validite d'un tour selon le code les deux etant founis en parametre et renvoie les drapeaux
    void test_correspondance(unsigned char flags, unsigned char code[], code_t possibilites[]);             //fonction regardant la correspondance entre les flags du tour passe le code joue (equivalent de tour de la fonction precedent) et les possibilite totales de la partie
//

#endif // !FONCTIONS_H
