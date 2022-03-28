#ifndef GESTIONFICHIERS_H
#define GESTIONFICHIERS_H

//include 
    //fichiers natif au C
        #include <stdio.h>
//


void LectureInstruction(char* nomSauvegarde);                               //fonctions qui va regarder un fichier de sauvegarde et charger la partie
void SauvegardePartie(char* nomSauvegarde);                                 //fonctions qui va sauvegarder une partie dans un fichiers qui a comme nom ce qu'ont lui rentre en parametre


#endif