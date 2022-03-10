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
unsigned char resol, getter, NumeroTour, flag_bon, retry, bool_victoire, etape_affichage;
unsigned char flag_tour[12], tour[4], code[4], choix_text[1];

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
                break;
            }else if (NumeroTour <= 12){
                Next_State = Resolution_Manuelle;
            }else{
                Next_State = Fin;
                bool_victoire = 0;
            }
            break;

        case Tour:
            if(flag_bon){
                Next_State = Fin;
                bool_victoire = 1;
            }else if (NumeroTour <= 12){
                Next_State = Correspondance;
            }else{
                Next_State = Fin;
                bool_victoire = 0;
            }
            break;

        case Correspondance:
            Next_State = Tour;
            printf("tour suivant : tapez espace ...\n");
            choix_text[0] = txt_continuer;
            affichage();
            do{
                getter = 0;
                getter = RecupTouche_B_SDL();
            }while((getter != t_espace)&&(getter != appuie));
            break;

        case Fin:
            if(retry){
                affichage();
                Next_State = Init;
            }else{
                printf("fin ...");
                ExitSDL();
                exit(EXIT_SUCCESS);
            }
            break;
    }
    return Next_State;
}

void Current_State(Etat_t etat_courant){
    printf("current state\n");
    unsigned char while_bool = 1, gen;
    switch(etat_courant){
        case Init:
            printf("init\n");
            //init ecran
            etape_affichage = 0;
            affichage();
            // mise a 0 du nombre de tour
            NumeroTour = 0;

            // choix entre generation a la main ou random
            printf("generation du code : a la main <---> aleatoire\n");
            printf("a la main\r");
            SDL_Printf("generation du code : manuellement <> aleatoirement",0);
            SDL_Printf("manuellement",1);
            gen = 1;
            while(while_bool){
                getter = RecupTouche_B_SDL();
                switch (getter){
                    case t_entree:
                        while_bool = 0;
                        break;
                    case t_droite:
                        printf("aleatoire\r");
                        affichage();
                        SDL_Printf("generation du code : manuellement <> aleatoirement",0);
                        SDL_Printf("aleatoirement",1);
                        gen = 0;
                        break;
                    case appuie_texteD:
                        printf("aleatoire\r");
                        affichage();
                        SDL_Printf("generation du code : manuellement <> aleatoirement",0);
                        SDL_Printf("aleatoirement",1);
                        gen = 0;
                        break;
                    case t_gauche:
                        printf("a la main\r");
                        affichage();
                        SDL_Printf("generation du code : manuellement <> aleatoirement",0);
                        SDL_Printf("manuellement",1);
                        gen = 1;
                        break;
                    case appuie_texteG:
                        printf("a la main\r");
                        affichage();
                        SDL_Printf("generation du code : manuellement <> aleatoirement",0);
                        SDL_Printf("manuellement",1);
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
                do{
                    // generation du code
                    getter = RecupTouche_B_SDL();
                    switch(getter){
                        case appuie_code1:
                            code[0]++;
                            if(code[0]==5) code[0] = 0;
                            printf("pos 1 = %d\n", code[0]);
                            affichage();
                            break;
                        case appuie_code2:
                            code[1]++;
                            if(code[1]==5) code[1] = 0;
                            printf("pos 2 = %d\n", code[1]);
                            affichage();
                            break;
                        case appuie_code3:
                            code[2]++;
                            if(code[2]==5) code[2] = 0;
                            printf("pos 3 = %d\n", code[2]);
                            affichage();
                            break;
                        case appuie_code4:
                            code[3]++;
                            if(code[3]==5) code[3] = 0;
                            printf("pos 4 = %d\n", code[3]);
                            affichage();
                            break;
                    }
                }while(getter != t_entree);
                // affichage du code
                printf("code :");
                for(unsigned char i=0;i<4;i++)printf("%d",code[i]);
                printf("\n");
            }else{
                while(while_bool){
                    // generation random
                    srand(time(NULL));
                    for(unsigned char i=0;i<4;i++)code[i] = rand()%5;
                    // affichage du code
                    printf("code :");
                    affichage();
                    for(unsigned char i=0;i<4;i++)printf("%d",code[i]);
                    printf("\n");
                    printf("relancer ? (oui <-----> non)\n");
                    while_bool = 0;
                    printf("non\r");
                    affichage();
                    SDL_Printf("regenerer le code : oui <> non",0);
                    SDL_Printf("non",1);
                    while(1){
                        getter = RecupTouche_B_SDL();
                        if((getter == t_droite)||(getter == appuie_texteD)){
                            while_bool = 0;
                            printf("non\r");
                            affichage();
                            SDL_Printf("regenerer le code : oui <> non",0);
                            SDL_Printf("non",1);
                        }
                        if((getter == t_gauche)||(getter == appuie_texteG)){
                            while_bool = 1;
                            printf("oui\r");
                            affichage();
                            SDL_Printf("regenerer le code : oui <> non",0);
                            SDL_Printf("oui",1);
                        }
                        if(getter == t_entree) break;
                    }
                    printf("       \r");
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

                                if (possibilites[i].pos4 == 4){
                                    break;
                                } else {possibilites[i].pos4 ++;}
                            } else {possibilites[i].pos3 ++;}
                        } else {possibilites[i].pos2 ++;}
                    } else {possibilites[i].pos1 ++;}
                }
            }
            break;

        case Resolution_Manuelle:
            NumeroTour++;
            tour_passe[NumeroTour-1].pos1 = tour[0];
            tour_passe[NumeroTour-1].pos2 = tour[1];
            tour_passe[NumeroTour-1].pos3 = tour[2];
            tour_passe[NumeroTour-1].pos4 = tour[3];

            printf("\nSelection du code a soumettre\n");
            for(unsigned char i=0;i<4;i++) tour[i] = getch() - '0';

            flag_tour[NumeroTour-1] = test_valid(tour, code);
            if(flag_tour[NumeroTour-1] == 0x04) flag_bon = 1;

            // affichage resultat
            printf("tour %d:",NumeroTour);
            affichageImage(AF_tour, tour, NumeroTour);
            for(unsigned char i=0;i<4;i++) printf("%d",tour[i]);
            printf("\nflags :%.2x pour le tour %d\n",flag_tour[NumeroTour-1],NumeroTour);
            affichageImage(flag, flag_tour, NumeroTour);

            break;
    
        case Tour:
            NumeroTour += 1;
            flag_bon = 0;
            if (NumeroTour == 1){
                // on test 1122 comme valeur
                tour[0] = 1; tour[1] = 1; tour[2] = 2; tour[3] = 2;
                // sauvegarde du tour
                tour_passe[NumeroTour-1].pos1 = tour[0];
                tour_passe[NumeroTour-1].pos2 = tour[1];
                tour_passe[NumeroTour-1].pos3 = tour[2];
                tour_passe[NumeroTour-1].pos4 = tour[3];
                flag_tour[NumeroTour-1] = test_valid(tour, code);
                if(flag_tour[NumeroTour-1] == 0x40) flag_bon = 1; // 0x40 car on a 4 flag R et 0 flag B pour une bonne reponse
                // affichage resultat etape 2
                printf("tour %d:",NumeroTour);
                etape_affichage = 2;
                affichage();
                for(unsigned char i=0;i<4;i++) printf("%d",tour[i]);
                printf("\nflags :%.2x pour le tour 1\n",flag_tour[NumeroTour-1]);
                affichageImage(flag, flag_tour, NumeroTour);
            }else{
                tour_passe[NumeroTour-1].pos1 = tour[0];
                tour_passe[NumeroTour-1].pos2 = tour[1];
                tour_passe[NumeroTour-1].pos3 = tour[2];
                tour_passe[NumeroTour-1].pos4 = tour[3];
                flag_tour[NumeroTour-1] = test_valid(tour, code);
                if(flag_tour[NumeroTour-1] == 0x04) flag_bon = 1;
                // affichage resultat
                printf("tour %d:",NumeroTour);
                affichageImage(AF_tour, tour, NumeroTour);
                for(unsigned char i=0;i<4;i++) printf("%d",tour[i]);
                printf("\nflags :%.2x pour le tour %d\n",flag_tour[NumeroTour-1],NumeroTour);
                affichageImage(flag, flag_tour, NumeroTour);
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
            if(bool_victoire){
                printf("vous avez trouve le code en %d tour, et c'est :\n",NumeroTour);
                for(unsigned char i=0;i<4;i++) printf("%d",tour[i]);
                printf("\n");
            }else{
                printf("vous avez depasse 12 tours\n");
            }
            // menu pour quiter ou recommencer
            printf("replay <---> quit :\n");
            printf("replay\r");
            choix_text[0] = txt_rejouer;
            affichage();
            retry = 1;
            while(while_bool){
                getter = RecupTouche_B_SDL();
                switch (getter){
                    case t_entree:
                        while_bool = 0;
                        break;
                    case t_droite:
                        printf("quit  \r");
                        choix_text[0] = txt_quitter;
                        affichage();
                        retry = 0;
                        break;
                    case appuie_texteD:
                        printf("quit  \r");
                        choix_text[0] = txt_quitter;
                        affichage();
                        retry = 0;
                        break;
                    case t_gauche:
                        printf("replay\r");
                        choix_text[0] = txt_rejouer;
                        affichage();
                        retry = 1;
                        break;
                    case appuie_texteG:
                        printf("replay\r");
                        choix_text[0] = txt_rejouer;
                        affichage();
                        retry = 1;
                        break;
                }
            } while_bool = 1;
            break;
    }
}
