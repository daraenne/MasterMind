#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define uint8_t unsigned char
#define uint32_t unsigned long

uint8_t test_valid(uint8_t tour[], uint8_t code[]);
void test_correspondance(uint8_t flags, uint8_t code[]);

typedef struct {
    uint8_t pos1;
    uint8_t pos2;
    uint8_t pos3;
    uint8_t pos4;
}code_t;
code_t possibilites[625];
uint32_t possibilites_restante;

int main(){
    /* initialisations */
    uint32_t i;
    uint8_t tour[4], code[4], flag_tour[12];
    /* generation du code aleatoire */
    srand(time(NULL));
    for(i=0;i<4;i++){
        code[i] = rand()%5;
    }
    /* fin */






    /* etape 1 */
    /*
    *   mise de toutes les differentes valeurs possibles dans un tableau
    */
        possibilites[0].pos1=0;
        possibilites[0].pos2=0;
        possibilites[0].pos3=0;
        possibilites[0].pos4=0;
    for (i=1;i<625;i++){
        possibilites[i] = possibilites[i-1];
        if (possibilites[i].pos1 == 4){
            possibilites[i].pos1 = 0;

            if (possibilites[i].pos2 == 4){
                possibilites[i].pos2 = 0;

                if (possibilites[i].pos3 == 4){
                    possibilites[i].pos3 = 0;

                    if (possibilites[i].pos4 == 4){
                        break;
                    } else {possibilites[i].pos4 ++;}
                } else {possibilites[i].pos3 ++;}
            } else {possibilites[i].pos2 ++;}
        } else {possibilites[i].pos1 ++;}
    }
    printf("\n");
    /* fin */






    /* etape 2 */
    /*
    *   on test 1122 comme valeur
    */
    tour[0] = 1; tour[1] = 1; tour[2] = 2; tour[3] = 2;
    flag_tour[0] = test_valid(tour, code);

    /* affichage resultat etape 2 */
    printf("code :");
    for(i=0;i<4;i++){printf("%d",code[i]);}
    printf("\n");

    printf("tour :");
    for(i=0;i<4;i++){printf("%d",tour[i]);}
    printf("\nflags :%.2x pour le tour 1\n",flag_tour[0]);
    /* fin */






    /* etape 3 */
    /*
    *   on test toute les possibilites en tant que code valide
    *   si les flags changent par rapport au vrai
    *   alors cette possibilites ne peut pas etre le vrai code
    */
    test_correspondance(flag_tour[0],tour);
    printf("possibilites_restante = %d\n",possibilites_restante);
    /* fin */



    /* etape 4 */
    /* 
    *   calcul du prochain code 
    *   a optimiser plus tard pour trouver le code qui elimineras le plus de possibilite
    */
    i=0;
    while (1){
        if (possibilites[i].pos1 != 0xFF){
            tour[0] = possibilites[i].pos1;
            tour[1] = possibilites[i].pos2;
            tour[2] = possibilites[i].pos3;
            tour[3] = possibilites[i].pos4;
            break;
        }
        i++;
    }
    printf("\nle prochain code seras :");
    for(i=0;i<4;i++){printf("%d",tour[i]);}
    printf("\n");
    /*
    *   il ne reste plus qu'a boucler sur l'etape 2 avec le code obtenue 
    *   puis detecter la fin de partie
    */
    /* fin */
}


uint8_t test_valid(uint8_t tour[], uint8_t code[]){
    uint8_t flags, code_val[4], tour_val[4], r_flag = 0, w_flag = 0;
    uint8_t i, j;
    for (i=0;i<4;i++){code_val[i] = code[i];}
    for (i=0;i<4;i++){tour_val[i] = tour[i];}

    /* calcul flag rouge (bonne couleur bonne position) */
    for (i=0;i<4;i++){
        if (tour_val[i] == code_val[i]){
            tour_val[i] = 0xFF;
            code_val[i] = 0xAA;
            r_flag++;
        }
    }
    /* calcul flag blanc */
    for (i=0;i<4;i++){
        for (j=0;j<4;j++){
            if (tour_val[i] == code_val[j]){
                tour_val[i] = 0xFF;
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


void test_correspondance(uint8_t flags, uint8_t tour[]){
    uint32_t i,j;
    uint8_t code_simule[4], tour_val[4];
    for (i=0;i<4;i++){
        tour_val[i] = tour[i];
    }
    possibilites_restante = 0;
    for (i=0;i<625;i++){
        code_simule[0] = possibilites[i].pos1;
        code_simule[1] = possibilites[i].pos2;
        code_simule[2] = possibilites[i].pos3;
        code_simule[3] = possibilites[i].pos4;
        if ((flags == test_valid(tour_val, code_simule)) && (possibilites[i].pos1!=0xFF)){
            printf("possibilite %lu = %d;%d;%d;%d\n",i,possibilites[i].pos1,possibilites[i].pos2,possibilites[i].pos3,possibilites[i].pos4);
            possibilites_restante++;
        } else {
            possibilites[i].pos1 = 0xFF;
            possibilites[i].pos2 = 0xFF;
            possibilites[i].pos3 = 0xFF;
            possibilites[i].pos4 = 0xFF;
        }
    }
}
