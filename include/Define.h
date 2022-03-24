#ifndef Define_H
#define Define_H

//retours de la fonction RecupTouche_B_SDL()
    //Valeurs des retour pour chaques touche
        #define t_entree            0x0
        #define t_gauche            0x1
        #define t_droite            0x2
        #define t_espace            0x3
    //Click souris
        #define appuie_code1        0xA0
        #define appuie_code2        0xA1
        #define appuie_code3        0xA2
        #define appuie_code4        0xA3
        #define appuie_Tour1        0xA4
        #define appuie_Tour2        0xA5
        #define appuie_Tour3        0xA6
        #define appuie_Tour4        0xA7
        #define appuie              0xA8
//

typedef enum Etat{Init, Tour, Correspondance, Fin, Resolution_Manuelle}Etat_t;                              //enum pour les etats                
typedef struct {unsigned char pos1; unsigned char pos2; unsigned char pos3; unsigned char pos4;}code_t;     //structure pour les codes

#endif // !Define_H
