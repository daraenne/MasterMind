#include <stdio.h>
#include <stdlib.h>

uint8_t N;

int main()
{
    printf("Hello world!\n");
    return 0;
}

typedef enum ETAT{
    INIT;
    TOUR_N;
    TOUR_CHECK;
    FIN_JEU;
}ETAT_T;


ETAT_T Next_State(ETAT_T CurrentState)           //Transition between the states
{
    ETAT_T Next_State = Current_State;
    switch(CurrentState){
        case INIT:
            Next_State = TOUR_N;
            break;
        case TOUR_N:
            if (N>12){
                Next_State = TOUR_CHECK;
            }
            else{
                Next_State = FIN_JEU;
            }
            break;
        case TOUR_CHECK:
            if(Combinaison == Code){
                Next_State = FIN_JEU;
            }
            else{
                Next_State = TOUR_N;
            }
            break;
        case FIN_JEU:
            if(Retry != 0){
                Next_State = INIT;
            }
            break;
        default:
            break;
    }
    return Next_State;
}

void Current_State(ETAT_T )
