//fichiers generaux
#include <stdio.h>
//mes fichiers
#include <Fonctions.h>
#include <Define.h>

unsigned char test_valid(unsigned char test[], unsigned char code[]){
    unsigned char flags, code_val[4], test_val[4], r_flag = 0, w_flag = 0;
    //stockage des tableaux dans des variables locals pour eviter de reecrire dessus
    for (unsigned char i=0;i<4;i++)
        code_val[i] = code[i];
    for (unsigned char i=0;i<4;i++)
        test_val[i] = test[i];

    //calcul flag rouge (bonne couleur bonne position)
    for (unsigned char i=0;i<4;i++){
        if (test_val[i] == code_val[i]){
            test_val[i] = 0xFF;
            code_val[i] = 0xAA;
            r_flag++;
        }
    }

    //calcul flag blanc (bonne couleur mais mauvaise position)
    for (unsigned char i=0;i<4;i++){
        for (unsigned char j=0;j<4;j++){
            if (test_val[i] == code_val[j]){
                test_val[i] = 0xFF;
                code_val[j] = 0xAA;
                w_flag++;
            }
        }
    }
    /*
    *   on retourne les flags sur un seul octet
    *   les 4 LSB pour les flags rouges
    *   les 4 MSB pour les flags blancs
    */
    flags = r_flag | (w_flag<<4);
    return flags;
}


void test_correspondance(unsigned char flags, unsigned char tour[], code_t possibilites[]){
    unsigned char code_simule[4], tour_val[4];
    for (unsigned char i=0;i<4;i++) tour_val[i] = tour[i];                                          //stockage du tableau en local pour eviter un probleme de reecriture au cas ou
    for (unsigned long i=0;i<625;i++){
        //on met les possibilite dans un tableau (car tes_valid() prend des tableau en parametre et pas la structure code_t)
        code_simule[0] = possibilites[i].pos1;
        code_simule[1] = possibilites[i].pos2;
        code_simule[2] = possibilites[i].pos3;
        code_simule[3] = possibilites[i].pos4;
        if ((flags != test_valid(tour_val, code_simule)) || (possibilites[i].pos1 > 4)){            //on test pour chaque possibilite encore valide (possibilite invalide = 0xFF pour chaque .pos on verifie donc si un des .pos .pos1 est superieur a 4) si elle sont toujours
            possibilites[i].pos1 = 0xFF;
            possibilites[i].pos2 = 0xFF;
            possibilites[i].pos3 = 0xFF;
            possibilites[i].pos4 = 0xFF;
        }
    }
}

