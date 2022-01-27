#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define uint8_t unsigned char
#define uint32_t unsigned long

typedef struct {
    uint8_t pos1;
    uint8_t pos2;
    uint8_t pos3;
    uint8_t pos4;
}code_t;
code_t code;
code_t possibilites[1024];


int main(){
    uint32_t i;
    /* g�n�ration du code al�atoire */
    srand( time(NULL));
    code.pos1 = rand() % 5;
    code.pos2 = rand() % 5;
    code.pos3 = rand() % 5;
    code.pos4 = rand() % 5;
    /* fin */

    /* etape 1 */
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
                    } else {
                        possibilites[i].pos4 += 1;
                    }
                } else {
                    possibilites[i].pos3 += 1;
                }
            } else {
                possibilites[i].pos2 += 1;
            }
        } else {
            possibilites[i].pos1 += 1;
        }
        printf("possibilite %lu = %d;%d;%d;%d\n",i,possibilites[i].pos1,possibilites[i].pos2,possibilites[i].pos3,possibilites[i].pos4);
    }
    /* fin */

    /* etape 3 */
    /*  tester 1122 puis selon les resultat obtenue tester tout les autres codes et verifier qu'ils donnerait
    *   ce resultat si ils etait le code :
    *   ex Pour 1122 si le resultat obtenue est : R,B,*,*
    *   alors il est impossible que le code soit 1111 car le resultat obtenue serait R,R,*,*
    */
    /* fin */

    /* suite */
}
