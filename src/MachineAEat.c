//include
    //natif au C
        #include <stdlib.h>
        #include <time.h>
    //nos fichiers 
        #include <MachineAEtat.h>
        #include <Fonctions.h>
        #include <Define.h>
        #include <Affichage.h>
//

code_t possibilites[625];                                                                                           //tableau sauvegardant toutes les possibilite lors de la resolution automatique
code_t tour_passe[12];                                                                                              //stockage des differents tours
unsigned char resol, getter, NumeroTour, flag_bon, retry, bool_victoire, etape_affichage, Automatique, gen;
unsigned char flag_tour[12], tour[4], code[4];                                                                      //stockage des drapeaux, stockage du tour actuel, stockage du code de la partie

Etat_t Next_State(Etat_t CurrentState){
    Etat_t Next_State = CurrentState;                                                                               //sauvegarde de l'etat precedent au cas ou
    switch(CurrentState){
        //etat precedent = Init
        case Init:
            if(resol) Next_State = Tour;                                                                            //on regarde le type de resolution (man ou auto) puis on va dans l'etat correspondant
            else Next_State = Resolution_Manuelle;
            break;

        //etat precedent = Resolution_Manuelle
        case Resolution_Manuelle:
            if(flag_bon){                                                                                           //en premier on regarde si le joueur a gagner
                Next_State = Fin;
                bool_victoire = 1;                                                                                  //cette variable sert a dire si le jeux est fini par une victoire ou une defaite
            }else if (NumeroTour == 12){                                                                            //ensuite on regarde si le joueur a perdue (+ de 12 tour)
                Next_State = Fin;
                bool_victoire = 0;                                                                                  //on stock le fait que le jeu soit finis par une defaite du joueur 
            }else{                                                                                                  //enfin le jeu n'etant donc pas fini on retourne dans Resolution_Manuelle
                Next_State = Resolution_Manuelle;                                           
            }
            break;

        //etat precedent = Tour
        case Tour:
            if(flag_bon){                                                                                           //on verifie la fin de partie de la meme maniere que dans resolution manuelle
                Next_State = Fin;
                bool_victoire = 1;
            }else if (NumeroTour == 12){
                Next_State = Fin;
                bool_victoire = 0;
            }else{
                do{                                                                                                 //on bloque tant que le joueur na pas appuiez sur espace
                    affichage();
                    SDL_Printf("tour suivant : tapez espace ...",1);
                    getter = RecupTouche_B_SDL();
                    if (getter == chargement) return etat_courant;
                }while((getter != t_espace)&&(getter != appuie));
                Next_State = Correspondance;                                                                        //on envoie sur l'etape de verification de la correspondance des possibilites
            }
            break;

        //etat precedent = Correspondance
        case Correspondance:
            Next_State = Tour;                                                                                      //apres cette etat la seul possibilite est d'aller dans l'etat tour
            break;

        case Fin:
            if(retry){                                                                                              //on verifie si le joueur veut rejouer 
                Next_State = Init;
            }else{
                ExitSDL();                                                                                          //on ferme la SDL et libere la memoire
                exit(EXIT_SUCCESS);                                                                                 //on quit le programme
            }
            break;
    }
    return Next_State;
}

void Current_State(Etat_t etat_courant){
    unsigned char while_bool = 1;                                                                                   //while bool permet de sortir de certain while selon certaine condition, gen sert a determiner si la generation du code est manuelle ou aleatoire
    switch(etat_courant){
        //etat Init
        case Init:
            //initialisation variables
            flag_bon = 0;
            Automatique = 1;
            etape_affichage = 0;
            NumeroTour = 0;
            for(char i=0;i<12;i++)flag_tour[i] = 0;
            for(char i=0;i<4;i++)tour[i] = 0;
            for(char i=0;i<4;i++)code[i] = 0;
            affichage();
            SDL_Printf("resolution manuelle <> automatique ",1);
            SDL_Printf("automatique",2);
            resol = 1;
            while(while_bool){                                                                                      //choix resolution manuelle ou automatique (choix par defaut : automatique)
                getter = RecupTouche_B_SDL();
                if (getter == chargement) return;
                switch(getter){
                    case t_entree:                                                                                  //si le joueur appuie sur entree ou valider le choix est finis et on sort de la boucle
                        while_bool = 0;
                        break;
                    case t_droite :                                                                                 //si le joueur appuie sur la fleche droite du clavier on affiche son choix et selectionne resolution automatique
                        affichage();
                        SDL_Printf("resolution manuelle <> automatique ",1);
                        SDL_Printf("automatique",2);
                        resol = 1;
                        break;
                    case t_gauche :                                                                                 //si le joueur appuie sur la fleche gauche du clavier on affiche son choix et selectionne resolution manuelle
                        affichage();
                        SDL_Printf("resolution manuelle <> automatique ",1);
                        SDL_Printf("manuelle",2);
                        resol = 0;
                        break;
                }
            }while_bool = 1;

            affichage();
            SDL_Printf("generation du code : manuelle <> aleatoire",1);
            SDL_Printf("manuelle",2);
            gen = 1;
            while(while_bool){                                                                                      //choix entre generation a la main ou random
                getter = RecupTouche_B_SDL();
                if (getter == chargement) return;                
                switch (getter){
                    case t_entree:                                                                                  //si le joueur appuie sur entree ou valider le choix est finis et on sort de la boucle
                        while_bool = 0;
                        break;
                    case t_droite:                                                                                  //si le joueur appuie sur la fleche droite du clavier on affiche son choix et selectionne generation aleatoire
                        affichage();
                        SDL_Printf("generation du code : manuelle <> aleatoire",1);
                        SDL_Printf("aleatoire",2);
                        gen = 0;
                        break;
                    case t_gauche:                                                                                  //si le joueur appuie sur la fleche gauche du clavier on affiche son choix et selectionne generation aleatoire
                        affichage();
                        SDL_Printf("generation du code : manuelle <> aleatoire",1);
                        SDL_Printf("manuelle",2);
                        gen = 1;
                        break;
                }
            } while_bool = 1;

            if(gen){                                                                                                //on regarde si la generation du code est aleatoire ou manuelle (1 = manuelle)
                for(char i=0;i<4;i++) code[i] = 0;                                                                  //on s'assure que le code soit initialiser correctement
                etape_affichage = 1;
                do{
                    affichage();
                    SDL_Printf("selectionnez le code puis validez",1);
                    getter = RecupTouche_B_SDL();
                    if (getter == chargement) return;
                    switch(getter){
                        //le joueur appuie sur la case 1 du code
                        case appuie_code1:
                            code[0]++;                                                                              //modification de la valeur du code (un appuie = +1 et si le code depasse la valeur max on remet a 0)
                            if(code[0]==5) code[0] = 0;
                            break;
                        //le joueur appuie sur la case 2 du code
                        case appuie_code2:
                            code[1]++;
                            if(code[1]==5) code[1] = 0;
                            break;
                        //le joueur appuie sur la case 3 du code
                        case appuie_code3:
                            code[2]++;
                            if(code[2]==5) code[2] = 0;
                            break;
                        //le joueur appuie sur la case 4 du code
                        case appuie_code4:
                            code[3]++;
                            if(code[3]==5) code[3] = 0;
                            break;
                    }
                }while(getter != t_entree);
            }else{                                                                                                  //generation du code aleatoire (gen=0)
                while(while_bool){
                    srand(time(NULL));                                                                              //lancement du timer pour rand() (voir time.h)
                    for(unsigned char i=0;i<4;i++)code[i] = rand()%5;                                               //mise d'une valeur aleatoire entre 0 et 5 pour chaque valeur du code
                    etape_affichage = 1;                                                                            
                    while_bool = 0;
                    affichage();
                    SDL_Printf("regenerer le code : oui <> non",1);
                    SDL_Printf("non",2);
                    while(1){                                                                                       //on laisse au joueur la possibilite de regenerer ou non le code
                        getter = RecupTouche_B_SDL();
                        if (getter == chargement) return;
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
            if(resol){                                                                                              //si on est en resolution automatique
                // generation d'un tableau vide (clear d'une possible partie precedente)
                possibilites[0].pos1=0;
                possibilites[0].pos2=0;
                possibilites[0].pos3=0;
                possibilites[0].pos4=0;
                // mise de toutes les differentes valeurs possibles dans le tableau possibilite
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

        //etat Resolution_Manuelle
        case Resolution_Manuelle:
            Automatique = 0;                                                                                        //on remet Automatique a 0 car il permet d'afficher le code 
            NumeroTour++;                                                                                           //on augmente le numero du tour (initialiser a 0)
            etape_affichage = 2;
            do{
                affichage();
                SDL_Printf("selectionnez le code pour le tour puis validez",1);
                getter = RecupTouche_B_SDL();
                if (getter == chargement) return;
                switch(getter){                                                                                     //selection du tour la selection marche de la meme maniere que la genration manuelle du code
                    case appuie_Tour1:
                        tour[0]++;
                        if(tour[0]==5) tour[0] = 0;
                        break;
                    case appuie_Tour2:
                        tour[1]++;
                        if(tour[1]==5) tour[1] = 0;
                        break;
                    case appuie_Tour3:
                        tour[2]++;
                        if(tour[2]==5) tour[2] = 0;
                        break;
                    case appuie_Tour4:
                        tour[3]++;
                        if(tour[3]==5) tour[3] = 0;
                        break;
                }
            }while(getter != t_entree);

            //sauvegarde des tours
            tour_passe[NumeroTour-1].pos1 = tour[0];
            tour_passe[NumeroTour-1].pos2 = tour[1];
            tour_passe[NumeroTour-1].pos3 = tour[2];
            tour_passe[NumeroTour-1].pos4 = tour[3];

            flag_tour[NumeroTour-1] = test_valid(tour, code);                                                       //verification de la validite du code et stockage des flags dans flag_tour
            if(flag_tour[NumeroTour-1] == 0x04) flag_bon = 1;                                                       //si les flags sont egaux a 4 rouges (0x04) on le stock pour la transition des etats
            Automatique = 1;
            break;
    
        //etat Tour
        case Tour:
            NumeroTour++;                                                                                           //on augmente le numero du tour (initialiser a 0)
            if (NumeroTour == 1){                                                                                   //si c'est le premier tour on test 1122 comme valeur car c'est la valeur la plus optimise (au mme stade que certaine autre comme 1133, 2244, ...)
                tour[0] = 1; tour[1] = 1; tour[2] = 2; tour[3] = 2;

                //sauvegarde du tour
                tour_passe[NumeroTour-1].pos1 = tour[0];
                tour_passe[NumeroTour-1].pos2 = tour[1];
                tour_passe[NumeroTour-1].pos3 = tour[2];
                tour_passe[NumeroTour-1].pos4 = tour[3];

                //pour le reste du tour tout ce passe de la meme maniere que dans la resolution manuelle (valide, stockage flags, verif flags bon)
                flag_tour[NumeroTour-1] = test_valid(tour, code);
                if(flag_tour[NumeroTour-1] == 0x04) flag_bon = 1;
                else flag_bon = 0;
                etape_affichage = 2;
            }else{                                                                                                  //si c'est un autre tour que le premier le code du tour auras deja ete choisie dans l'etat Correspondance (etat suivant)
                //puis on poursuit le tour comme d'habitude
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

        //etat Correspondance 
        case Correspondance:
            test_correspondance(flag_tour[NumeroTour-1], tour, possibilites);                                       //on regarde si les possibilite restantes sont possible en tant que code ou non
            // calcul du prochain code
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
            //affichage fin de partie victoire ou defaite
            if(!bool_victoire){
                do{                                                                                                 //on bloque tant que le joueur na pas appuiez sur espace
                    affichage();
                    SDL_Printf("vous avez depasse 12 tours (pressez espace)",1);
                    getter = RecupTouche_B_SDL();
                    if (getter == chargement) return;
                }while(getter != t_espace);
            }
            //menu pour quiter ou recommencer
            affichage();
            SDL_Printf("replay <> quit :",1);
            SDL_Printf("replay",2);
            retry = 1;
            while(while_bool){
                getter = RecupTouche_B_SDL();
                if (getter == chargement) return;
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
