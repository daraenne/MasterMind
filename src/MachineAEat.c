//fichiers generaux
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
//mes fichiers
#include <MachineAEtat.h>
#include <Fonctions.h>
#include <Define.h>
#include <Affichage.h>

code_t possibilites[625];
code_t tour_passe[12];
unsigned char resol, getter, NumeroTour, flag_bon, retry, bool_victoire, etape_affichage, Automatique;
unsigned char flag_tour[12], tour[4], code[4];

Etat_t Next_State(Etat_t CurrentState){
    Etat_t Next_State = CurrentState;
    switch(CurrentState){
        case Init:
            if(resol) Next_State = Tour;
            else Next_State = Resolution_Manuelle;
            break;

        case Resolution_Manuelle:
            if(flag_bon){
                Next_State = Fin;
                bool_victoire = 1;
            }else if (NumeroTour == 12){
                Next_State = Fin;
                bool_victoire = 0;
            }else{
                Next_State = Resolution_Manuelle;
            }
            break;

        case Tour:
            if(flag_bon){
                Next_State = Fin;
                bool_victoire = 1;
            }else if (NumeroTour == 12){
                Next_State = Fin;
                bool_victoire = 0;
            }else{
                affichage();
                SDL_Printf("tour suivant : tapez espace ...",1);
                do{
                    getter = 0;
                    getter = RecupTouche_B_SDL();
                }while((getter != t_espace)&&(getter != appuie));
                Next_State = Correspondance;
            }
            break;

        case Correspondance:
            Next_State = Tour;
            break;

        case Fin:
            if(retry){
                Next_State = Init;
            }else{
                ExitSDL();
                exit(EXIT_SUCCESS);
            }
            break;
    }
    return Next_State;
}

void Current_State(Etat_t etat_courant){
    unsigned char while_bool = 1, gen;
    switch(etat_courant){
        case Init:
            //initialisation variables
            flag_bon = 0;
            Automatique = 1;
            etape_affichage = 0;
            NumeroTour = 0;
            for(char i=0;i<12;i++)flag_tour[i] = 0;
            for(char i=0;i<4;i++)tour[i] = 0;
            for(char i=0;i<4;i++)code[i] = 0;

            // choix resolution manuelle ou automatique

            affichage();
            SDL_Printf("resolution manuelle <> automatique ",1);
            SDL_Printf("automatique",2);
            resol = 1;

            while(while_bool){
                getter = RecupTouche_B_SDL();
                switch(getter){
                    case t_entree:
                        while_bool = 0;
                        break;
                    case t_droite :
                        affichage();
                        SDL_Printf("resolution manuelle <> automatique ",1);
                        SDL_Printf("automatique",2);
                        resol = 1;
                        break;
                    case t_gauche :
                        affichage();
                        SDL_Printf("resolution manuelle <> automatique ",1);
                        SDL_Printf("manuelle",2);
                        resol = 0;
                        break;
                    default:
                        break;
                }
            }while_bool = 1;

            // choix entre generation a la main ou random
            affichage();
            SDL_Printf("generation du code : manuelle <> aleatoire",1);
            SDL_Printf("manuelle",2);
            gen = 1;
            while(while_bool){
                getter = RecupTouche_B_SDL();
                switch (getter){
                    case t_entree:
                        while_bool = 0;
                        break;
                    case t_droite:
                        affichage();
                        SDL_Printf("generation du code : manuelle <> aleatoire",1);
                        SDL_Printf("aleatoire",2);
                        gen = 0;
                        break;
                    case t_gauche:
                        affichage();
                        SDL_Printf("generation du code : manuelle <> aleatoire",1);
                        SDL_Printf("manuelle",2);
                        gen = 1;
                        break;
                }
            } while_bool = 1;
            // generation du code
            if(gen){
                //on s'assure que le code soit initialiser correctement
                for(char i=0;i<4;i++) code[i] = 0;
                etape_affichage = 1;
                affichage();
                SDL_Printf("selectionnez le code puis validez",1);
                do{
                    // generation du code
                    getter = RecupTouche_B_SDL();
                    switch(getter){
                        case appuie_code1:
                            code[0]++;
                            if(code[0]==5) code[0] = 0;
                            affichage();
                            SDL_Printf("selectionnez le code puis validez",1);
                            break;
                        case appuie_code2:
                            code[1]++;
                            if(code[1]==5) code[1] = 0;
                            affichage();
                            SDL_Printf("selectionnez le code puis validez",1);
                            break;
                        case appuie_code3:
                            code[2]++;
                            if(code[2]==5) code[2] = 0;
                            affichage();
                            SDL_Printf("selectionnez le code puis validez",1);
                            break;
                        case appuie_code4:
                            code[3]++;
                            if(code[3]==5) code[3] = 0;
                            affichage();
                            SDL_Printf("selectionnez le code puis validez",1);
                            break;
                    }
                }while(getter != t_entree);
            }else{
                while(while_bool){
                    // generation random
                    srand(time(NULL));
                    for(unsigned char i=0;i<4;i++)code[i] = rand()%5;
                    etape_affichage = 1;
                    while_bool = 0;
                    affichage();
                    SDL_Printf("regenerer le code : oui <> non",1);
                    SDL_Printf("non",2);
                    while(1){
                        getter = RecupTouche_B_SDL();
                        if(getter == t_droite){
                            while_bool = 0;
                            affichage();
                            SDL_Printf("regenerer le code : oui <> non",1);
                            SDL_Printf("non",2);
                        }
                        if(getter == t_gauche){
                            while_bool = 1;
                            affichage();
                            SDL_Printf("regenerer le code : oui <> non",1);
                            SDL_Printf("oui",2);
                        }
                        if(getter == t_entree) break;
                    }
                }while_bool = 1;
            }
            if(resol){
                // generation d'un tableau vide (clear d'une possible partie precedente)
                possibilites[0].pos1=0;
                possibilites[0].pos2=0;
                possibilites[0].pos3=0;
                possibilites[0].pos4=0;
                // mise de toutes les differentes valeurs possibles dans le tableau
                for (unsigned long i=1;i<625;i++){
                    possibilites[i] = possibilites[i-1];
                    if (possibilites[i].pos1 == 4){
                        possibilites[i].pos1 = 0;

                        if (possibilites[i].pos2 == 4){
                            possibilites[i].pos2 = 0;

                            if (possibilites[i].pos3 == 4){
                                possibilites[i].pos3 = 0;

                                if (possibilites[i].pos4 == 4) break;
                                else possibilites[i].pos4 ++;
                            } else possibilites[i].pos3 ++;
                        } else possibilites[i].pos2 ++;
                    } else possibilites[i].pos1 ++;
                }
            }
            break;

        case Resolution_Manuelle:
            Automatique = 0;
            NumeroTour++;
            etape_affichage = 2;
            do{
                // selection du code pour le tour
                affichage();
                SDL_Printf("selectionnez le code pour le tour puis validez",1);
                getter = RecupTouche_B_SDL();
                switch(getter){
                    case appuie_Tour1:
                        tour[0]++;
                        if(tour[0]==5) tour[0] = 0;
                        affichage();
                        SDL_Printf("selectionnez le code puis validez",1);
                        break;
                    case appuie_Tour2:
                        tour[1]++;
                        if(tour[1]==5) tour[1] = 0;
                        affichage();
                        SDL_Printf("selectionnez le code puis validez",1);
                        break;
                    case appuie_Tour3:
                        tour[2]++;
                        if(tour[2]==5) tour[2] = 0;
                        affichage();
                        SDL_Printf("selectionnez le code puis validez",1);
                        break;
                    case appuie_Tour4:
                        tour[3]++;
                        if(tour[3]==5) tour[3] = 0;
                        affichage();
                        SDL_Printf("selectionnez le code puis validez",1);
                        break;
                }
            }while(getter != t_entree);

            tour_passe[NumeroTour-1].pos1 = tour[0];
            tour_passe[NumeroTour-1].pos2 = tour[1];
            tour_passe[NumeroTour-1].pos3 = tour[2];
            tour_passe[NumeroTour-1].pos4 = tour[3];

            flag_tour[NumeroTour-1] = test_valid(tour, code);
            if(flag_tour[NumeroTour-1] == 0x04) flag_bon = 1;
            Automatique = 1;
            break;
    
        case Tour:
            NumeroTour++;
            if (NumeroTour == 1){
                // on test 1122 comme valeur
                tour[0] = 1; tour[1] = 1; tour[2] = 2; tour[3] = 2;
                // sauvegarde du tour
                tour_passe[NumeroTour-1].pos1 = tour[0];
                tour_passe[NumeroTour-1].pos2 = tour[1];
                tour_passe[NumeroTour-1].pos3 = tour[2];
                tour_passe[NumeroTour-1].pos4 = tour[3];
                flag_tour[NumeroTour-1] = test_valid(tour, code);
                if(flag_tour[NumeroTour-1] == 0x04) flag_bon = 1;
                else flag_bon = 0;
                etape_affichage = 2;
            }else{
                flag_tour[NumeroTour-1] = test_valid(tour, code);
                if(flag_tour[NumeroTour-1] == 0x04) flag_bon = 1;
                else {
                    flag_bon = 0;
                    tour_passe[NumeroTour-1].pos1 = tour[0];
                    tour_passe[NumeroTour-1].pos2 = tour[1];
                    tour_passe[NumeroTour-1].pos3 = tour[2];
                    tour_passe[NumeroTour-1].pos4 = tour[3];
                }
                
            }
            break;

        case Correspondance:
            test_correspondance(flag_tour[NumeroTour-1], tour, possibilites);
            // calcul du prochain code
            // a optimiser plus tard pour trouver le code qui elimineras le plus de possibilite
            for(unsigned long i=0; i<625; i++){
                if (possibilites[i].pos1 != 0xFF){
                    tour[0] = possibilites[i].pos1;
                    tour[1] = possibilites[i].pos2;
                    tour[2] = possibilites[i].pos3;
                    tour[3] = possibilites[i].pos4;
                    break;
                }
            }
            break;

        case Fin:
            // affichage fin de partie victoire ou defaite
            if(!bool_victoire){
                SDL_Printf("vous avez depasse 12 tours",1);
            }
            // menu pour quiter ou recommencer
            affichage();
            SDL_Printf("replay <> quit :",1);
            SDL_Printf("replay",2);
            retry = 1;
            while(while_bool){
                getter = RecupTouche_B_SDL();
                switch (getter){
                    case t_entree:
                        while_bool = 0;
                        break;
                    case t_droite:
                        affichage();
                        SDL_Printf("replay <> quit :",1);
                        SDL_Printf("quit",2);
                        retry = 0;
                        break;
                    case t_gauche:
                        affichage();
                        SDL_Printf("replay <> quit :",1);
                        SDL_Printf("replay",2);
                        retry = 1;
                        break;
                }
            } while_bool = 1;
            break;
    }
}
