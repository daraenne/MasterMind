#ifndef Define_H
#define Define_H

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
//choix du texte
#define txt_continuer       0x0
#define txt_gen_man_EnCour  0x1
#define txt_gen_man         0x2
#define txt_gen_rand        0x3
#define txt_gen_rand_Non    0x4
#define txt_gen_rand_Oui    0x5
#define txt_quitter         0x6
#define txt_rejouer         0x7

typedef enum Etat{Init, Tour, Correspondance, Fin, Resolution_Manuelle}Etat_t;
typedef struct {unsigned char pos1; unsigned char pos2; unsigned char pos3; unsigned char pos4;}code_t;
#endif // !Define_H
