//include 
    //SDL
        #include <SDL/SDL.h>
        #include <SDL/SDL_ttf.h>
        #include <string.h>
    //nos headers
        #include <Define.h>
        #include <Affichage.h>
        #include <GestionFichiers.h>
//

//initialisations globales
    //fenetre
        SDL_Window *fenetre = NULL;
    //rendue
        SDL_Renderer *rendue = NULL;
    //surface (seras liberer juste apres avoire creer la texture correpondante)
        SDL_Surface *image = NULL;
    //textures
        //cercles
            SDL_Texture *cercleB = NULL;
            SDL_Texture *cercleG = NULL;
            SDL_Texture *cercleJ = NULL;
            SDL_Texture *cercleN = NULL;
            SDL_Texture *cercleV = NULL;
        //flags
            SDL_Texture *Flag_R = NULL;
            SDL_Texture *Flag_W = NULL;
        //fond
            SDL_Texture *Fond = NULL;
    //rectangles pour textures
        SDL_Rect Rect_Fond;
        SDL_Rect Rect_cercleDeplacement;
        SDL_Rect Rect_Code[4];
        SDL_Rect Rect_Flag[4];
        SDL_Rect Rect_Tour[4];
    //tableaux pour les positions des lignes et colonnes
        uint16_t lignes[12];
        uint16_t colonnes[9];
    //event
        SDL_Event event;
//

void InitSDL(void){
    //initialisation de SDL_Video et de TTF si une erreur survient on sort du programme avec ExitErreurSDL()
    if (SDL_Init(SDL_INIT_VIDEO) != 0) ExitErreurSDL("Init");
    if (TTF_Init() != 0) ExitErreurSDL("Init texte");
    fenetre = SDL_CreateWindow("Jeux du MasterMind", 2, 30, WINDOW_WIDTH, WINDOW_HEIGHT, 0);                    //creation d'une fenetre
    if (!fenetre) ExitErreurSDL("creation de fenetre");                                                         //si la fenetre ne c'est pas creer on sort
    rendue = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);                                         //creation du rendue
    if (!rendue) ExitErreurSDL("creation rendue");                                                              //si pas de rendue on sort  
    SDL_RenderPresent(rendue);                                                                                  //on affiche le rendue
    CreationTexture();                                                                                          //on creer toutes les textures a partir des images
    SetUpPositions();                                                                                           //on initialise les positions des differentes images
    SetUpRectangles();                                                                                          //on creer les rectangle permettant la mise dans le rendue des textures
    affichage();                                                                                                //on affiche ce qu'il y a a afficher
}

void ExitSDL(void){
    SDL_DestroyRenderer(rendue);                                                                                //rendue
    SDL_DestroyWindow(fenetre);                                                                                 //fenetre
    SDL_Quit();                                                                                                 //la SDL en elle meme
}

void ExitErreurSDL(const char* location){
    SDL_Log("ERREUR :%s > %s\n", location, SDL_GetError());                                                     //affichage erreur et localisation
    ExitSDL();                                                                                                  //fermeture de la SDL
    exit(EXIT_FAILURE);
}

void affichage(void){
    extern unsigned char etape_affichage, NumeroTour, Automatique;                                              //on recupere l'etape du programme, le numero du tour actuel, ainsi que l'affichage du code
    extern code_t tour_passe[12];                                                                               //on recupere les tour precedent
    extern unsigned char flag_tour[12], tour[4], code[4];                                                       //on recupere les flags total dans le jeu, le tour actuel, le code
    SDL_RenderCopy(rendue, Fond, NULL, &Rect_Fond);                                                             //on met le fond dans le rendue (permet de suprimmer tout element SDL ajouter en externe de cette fonction)
    if((etape_affichage > 0) && (Automatique)){                                                                 //on verifie que l'etape d'affichage est bien passer a au moins 1 et qu'il faille afficher le code
        for(char i=0;i<4;i++){                                                                                  //on affiche le code
            switch (code[i]){
                case 0:
                    SDL_RenderCopy(rendue, cercleB, NULL, &Rect_Code[i]);
                    break;
                case 1:
                    SDL_RenderCopy(rendue, cercleG, NULL, &Rect_Code[i]);
                    break;
                case 2:
                    SDL_RenderCopy(rendue, cercleJ, NULL, &Rect_Code[i]);
                    break;
                case 3:
                    SDL_RenderCopy(rendue, cercleN, NULL, &Rect_Code[i]);
                    break;
                case 4:
                    SDL_RenderCopy(rendue, cercleV, NULL, &Rect_Code[i]);
                    break;
            }
        }
    }
    if(etape_affichage > 1){                                                                                    //on verifie que l'etape d'affichage est au moins a 2
        for(unsigned char i=0; i<(NumeroTour-1); i++){                                                          //on affiche les different tour et leurs flags
            Rect_Tour[0].y = lignes[i];
            switch(tour_passe[i].pos1){                                                                         //pos1
                case 0:
                    SDL_RenderCopy(rendue, cercleB, NULL, &Rect_Tour[0]);                                       
                    break;
                case 1:
                    SDL_RenderCopy(rendue, cercleG, NULL, &Rect_Tour[0]);
                    break;
                case 2:
                    SDL_RenderCopy(rendue, cercleJ, NULL, &Rect_Tour[0]);
                    break;
                case 3:
                    SDL_RenderCopy(rendue, cercleN, NULL, &Rect_Tour[0]);
                    break;
                case 4:
                    SDL_RenderCopy(rendue, cercleV, NULL, &Rect_Tour[0]);
                    break;
            }
            Rect_Tour[1].y = lignes[i];
            switch(tour_passe[i].pos2){                                                                         //pos2
                case 0:
                    SDL_RenderCopy(rendue, cercleB, NULL, &Rect_Tour[1]);
                    break;
                case 1:
                    SDL_RenderCopy(rendue, cercleG, NULL, &Rect_Tour[1]);
                    break;
                case 2:
                    SDL_RenderCopy(rendue, cercleJ, NULL, &Rect_Tour[1]);
                    break;
                case 3:
                    SDL_RenderCopy(rendue, cercleN, NULL, &Rect_Tour[1]);
                    break;
                case 4:
                    SDL_RenderCopy(rendue, cercleV, NULL, &Rect_Tour[1]);
                    break;
            }
            Rect_Tour[2].y = lignes[i];
            switch(tour_passe[i].pos3){                                                                         //pos3
                case 0:
                    SDL_RenderCopy(rendue, cercleB, NULL, &Rect_Tour[2]);
                    break;
                case 1:
                    SDL_RenderCopy(rendue, cercleG, NULL, &Rect_Tour[2]);
                    break;
                case 2:
                    SDL_RenderCopy(rendue, cercleJ, NULL, &Rect_Tour[2]);
                    break;
                case 3:
                    SDL_RenderCopy(rendue, cercleN, NULL, &Rect_Tour[2]);
                    break;
                case 4:
                    SDL_RenderCopy(rendue, cercleV, NULL, &Rect_Tour[2]);
                    break;
            }
            Rect_Tour[3].y = lignes[i];
            switch(tour_passe[i].pos4){                                                                         //pos4
                case 0:
                    SDL_RenderCopy(rendue, cercleB, NULL, &Rect_Tour[3]);
                    break;
                case 1:
                    SDL_RenderCopy(rendue, cercleG, NULL, &Rect_Tour[3]);
                    break;
                case 2:
                    SDL_RenderCopy(rendue, cercleJ, NULL, &Rect_Tour[3]);
                    break;
                case 3:
                    SDL_RenderCopy(rendue, cercleN, NULL, &Rect_Tour[3]);
                    break;
                case 4:
                    SDL_RenderCopy(rendue, cercleV, NULL, &Rect_Tour[3]);
                    break;
            }
            for(char j=0;j<(flag_tour[i] & 0x0F);j++){                                                          //flags rouge
                Rect_Flag[j].y = lignes[i];
                SDL_RenderCopy(rendue, Flag_R, NULL, &Rect_Flag[j]);
            } for(char j=(flag_tour[i] & 0x0F);j<((flag_tour[i] & 0x0F)+(flag_tour[i] >> 4));j++){              //flags blanc
                Rect_Flag[j].y = lignes[i];
                SDL_RenderCopy(rendue, Flag_W, NULL, &Rect_Flag[j]);
            }
        }
        for(char i=0;i<4;i++){                                                                                  //on affiche aussi l'etat actuel du tour
            Rect_Tour[i].y = lignes[NumeroTour-1];
            switch(tour[i]){
                case 0:
                    SDL_RenderCopy(rendue, cercleB, NULL, &Rect_Tour[i]);
                    break;
                case 1:
                    SDL_RenderCopy(rendue, cercleG, NULL, &Rect_Tour[i]);
                    break;
                case 2:
                    SDL_RenderCopy(rendue, cercleJ, NULL, &Rect_Tour[i]);
                    break;
                case 3:
                    SDL_RenderCopy(rendue, cercleN, NULL, &Rect_Tour[i]);
                    break;
                case 4:
                    SDL_RenderCopy(rendue, cercleV, NULL, &Rect_Tour[i]);
                    break;
            }
        }
        for(char i=0;i<(flag_tour[NumeroTour-1] & 0x0F);i++){                                                   //ainsi que ses flags rouge 
            Rect_Flag[i].y = lignes[NumeroTour-1];
            SDL_RenderCopy(rendue, Flag_R, NULL, &Rect_Flag[i]);
        } for(char i=(flag_tour[NumeroTour-1] & 0x0F);i<((flag_tour[NumeroTour-1] & 0x0F)+(flag_tour[NumeroTour-1] >> 4));i++){ //et blanc
            Rect_Flag[i].y = lignes[NumeroTour-1];
            SDL_RenderCopy(rendue, Flag_W, NULL, &Rect_Flag[i]);
        }
        
    }
    SDL_RenderPresent(rendue);                                                                                  //on affiche le rendue apres avoir copier dedans ce qu'ont voulait
}

void SDL_Printf(const char* message, unsigned char ligne){
    SDL_Color C_Black;C_Black.a = 255;C_Black.r = 0;C_Black.g = 0;C_Black.b = 0;                                //on creer une couleur pour le texte (ici noir)
    SDL_Rect Rect_Text;                                                                                         //on initialise un rectangle pour placer le texte
    SDL_Texture *Texte=NULL;                                                                                    //on initialise une texture
    TTF_Font *police=NULL;                                                                                      //on initialise une police
    switch(ligne){                                                                                              //on verifie dans quelle ligne il faut ecrire
        //ecrire dans la ligne 1
        case 1:
            police = TTF_OpenFont("Polices/arial.ttf",20);                                                      //mise de la police voulue pour cette ligne (arial)
            if(!police) ExitErreurSDL("erreur creation police");                                                //si la police n'a pas ete creer on sort en erreur
            image = TTF_RenderText_Solid(police, message, C_Black);                                             //on creer une surface a partir du message voule et de la police
            if (!image) ExitErreurSDL("creation de Surtexte");                                                  //si pas de surface on sort
            Texte = SDL_CreateTextureFromSurface(rendue, image);                                                //on creer une texture a partir de cette surface et du rendue 
            if (!Texte) ExitErreurSDL("creation de Texte");                                                     //si pas de texture on sort
            SDL_FreeSurface(image);                                                                             //on libere en memoire la surface
            SDL_QueryTexture(Texte,NULL,NULL,&Rect_Text.w,&Rect_Text.h);                                        //on recupere cette texture et on creer son rectangle (weidth et heigth)
            /*
            *   centrage du texte dans la zone correspondante explication avec un exemple du calcul :
            *   on veut centrer l'image cercle dans l'image fond
            *   on recupere comme coordonnee pour le cercle :
            *   fond.x + ((fond.w-cercle.w)/2)      --->        coordonnee X
            *   fond.y + ((fond.h-cercle.h)/2)      --->        coordonnee Y
            */
            Rect_Text.x = 275 + ((455-Rect_Text.w)/2);
            Rect_Text.y = 516 + ((39-Rect_Text.h)/2);
            SDL_RenderCopy(rendue,Texte,NULL,&Rect_Text);                                                       //on copie la texture dans le rendue avec son rectangle donnant les coordonnee
            SDL_RenderPresent(rendue);                                                                          //on affiche le rendue
            break;  
        //ecrire dans la ligne 2
        case 2:
            police = TTF_OpenFont("Polices/BabySchoolItalic.ttf",20);                                           //mise de la police voulue pour cette ligne (BabySchoolItalic car elle est plus propre pour mettre en gras que de mettre la police arial en gras)      
            if(!police) ExitErreurSDL("erreur creation police");                                                //si pas de police on sort
            TTF_SetFontStyle(police, TTF_STYLE_UNDERLINE);                                                      //on souligne le texte
            image = TTF_RenderText_Solid(police, message, C_Black);                                             //la suite est comme la ligne 1
            if (!image) ExitErreurSDL("creation de Surtexte");
            Texte = SDL_CreateTextureFromSurface(rendue, image);
            if (!Texte) ExitErreurSDL("creation de Texte");
            SDL_FreeSurface(image);
            SDL_QueryTexture(Texte,NULL,NULL,&Rect_Text.w,&Rect_Text.h);
            Rect_Text.x = 275 + ((455-Rect_Text.w)/2);
            Rect_Text.y = 555 + ((39-Rect_Text.h)/2);
            SDL_RenderCopy(rendue,Texte,NULL,&Rect_Text);
            SDL_RenderPresent(rendue);
            break;
    }
}

void SetUpRectangles(void){
    //fond
    if (SDL_QueryTexture(Fond, NULL, NULL, &Rect_Fond.w, &Rect_Fond.h) != 0) ExitErreurSDL("Chargement fond");
    Rect_Fond.x = 0;
    Rect_Fond.y = 0;
    for(char i=0;i<4;i++){
        //code
        if (SDL_QueryTexture(cercleB, NULL, NULL, &Rect_Code[i].w, &Rect_Code[i].h) != 0) ExitErreurSDL("Chargement Rectangle de code");
        Rect_Code[i].x = colonnes[0];
        Rect_Code[i].y = lignes[i];
        //flag
        if (SDL_QueryTexture(Flag_R, NULL, NULL, &Rect_Flag[i].w, &Rect_Flag[i].h) != 0) ExitErreurSDL("Chargement Rectangle de flag");
        Rect_Flag[i].x = colonnes[5+i];
        //cercle
        if (SDL_QueryTexture(cercleB, NULL, NULL, &Rect_Tour[i].w, &Rect_Tour[i].h) != 0) ExitErreurSDL("Chargement Rectangle de cercle");
        Rect_Tour[i].x = colonnes[1+i];
    }
    if (SDL_QueryTexture(cercleB, NULL, NULL, &Rect_cercleDeplacement.w, &Rect_cercleDeplacement.h) != 0) ExitErreurSDL("Chargement Rectangle de cercle");
}

unsigned char RecupTouche_B_SDL(void){
    extern unsigned char NumeroTour;                            //on recupere le numero du tour pour la localisation des cercles du tour actuel
    while(SDL_WaitEvent(&event)){                               //tant qu'il n'y a pas d'event on boucle a l'infini
        switch(event.type){                                     //on regarde quelle event c'est passer
            //si on appuie sur la croix rouge
            case SDL_QUIT:
                ExitSDL();                                      //on ferme la SDL
                exit(EXIT_SUCCESS);
                break;
            //si on appuie sur le clavier on retourne la valeur correspondante
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    //touche fleche droite
                    case SDLK_RIGHT:    
                        return t_droite;
                        break;
                    //touche fleche gauche
                    case SDLK_LEFT:
                        return t_gauche;
                        break;
                    //touche entree
                    case SDLK_RETURN:
                        return t_entree;
                        break;
                    //touche espace
                    case SDLK_SPACE:
                        return t_espace;
                        break;                  
                    default:
                        return 0;
                        break;
                }
                break;
            //si on clique avec la souris on localise le clique et on renvoie ce a quoi ca correspond (on retourne appuie si on a pas cliquer sur quelquechose d'interactif dan le jeu)
            case SDL_MOUSEBUTTONDOWN:
                if((event.button.x >= colonnes[0])&&(event.button.y >= lignes[0])&&(event.button.x <= (colonnes[0] + Rect_Code[0].w))&&(event.button.y <= (lignes[0] + Rect_Code[0].h))) return appuie_code1;
                else if((event.button.x >= colonnes[0])&&(event.button.y >= lignes[1])&&(event.button.x <= (colonnes[0] + Rect_Code[1].w))&&(event.button.y <= (lignes[1] + Rect_Code[1].h))) return appuie_code2;
                else if((event.button.x >= colonnes[0])&&(event.button.y >= lignes[2])&&(event.button.x <= (colonnes[0] + Rect_Code[2].w))&&(event.button.y <= (lignes[2] + Rect_Code[2].h))) return appuie_code3;
                else if((event.button.x >= colonnes[0])&&(event.button.y >= lignes[3])&&(event.button.x <= (colonnes[0] + Rect_Code[3].w))&&(event.button.y <= (lignes[3] + Rect_Code[3].h))) return appuie_code4;
                else if((event.button.x >= 733)&&(event.button.y >= 532)&&(event.button.x <= 834)&&(event.button.y <= 586)) return t_entree;
                else if((event.button.x >= colonnes[1])&&(event.button.y >= lignes[NumeroTour-1])&&(event.button.x <= (colonnes[1] + Rect_Code[0].w))&&(event.button.y <= (lignes[NumeroTour-1] + Rect_Code[0].h))) return appuie_Tour1;
                else if((event.button.x >= colonnes[2])&&(event.button.y >= lignes[NumeroTour-1])&&(event.button.x <= (colonnes[2] + Rect_Code[1].w))&&(event.button.y <= (lignes[NumeroTour-1] + Rect_Code[1].h))) return appuie_Tour2;
                else if((event.button.x >= colonnes[3])&&(event.button.y >= lignes[NumeroTour-1])&&(event.button.x <= (colonnes[3] + Rect_Code[2].w))&&(event.button.y <= (lignes[NumeroTour-1] + Rect_Code[2].h))) return appuie_Tour3;
                else if((event.button.x >= colonnes[4])&&(event.button.y >= lignes[NumeroTour-1])&&(event.button.x <= (colonnes[4] + Rect_Code[3].w))&&(event.button.y <= (lignes[NumeroTour-1] + Rect_Code[3].h))) return appuie_Tour4;
                else if((event.button.x >= 197)&&(event.button.y >= 370)&&(event.button.x <= 334)&&(event.button.y <= 426)) {
                    //load
                    return appuie;
                } else if((event.button.x >= 197)&&(event.button.y >= 286)&&(event.button.x <= 334)&&(event.button.y <= 342)) {             //sauvegarde
                    char* nomFichier = "Sauvegarde1";                                                                                       //initialisation du nom du fichier de sauvegarde
                    char while_bool=1,choixNom=0;                                                                                           //creation d'une bool pour le while et de la variable de choix de nom
                    while(while_bool){                                                                                                      //tant qu'ont a pas choisie on boucle
                        if(SDL_WaitEvent(&event)){                                                                                      
                            //on affiche la demande
                            affichage();
                            SDL_Printf("emplacement de sauvegarde (5max) :",1);
                            SDL_Printf(nomFichier,2);
                            //on choisie le nom ()
                            switch(event.type){
                                case SDL_KEYDOWN :
                                    switch(event.key.keysym.sym){
                                    //touche fleche haut
                                    case SDLK_UP:
                                        choixNom++;
                                        if(choixNom == 5) choixNom=0;
                                        break;
                                    //touche fleche bas
                                    case SDLK_DOWN:
                                        choixNom--;
                                        if(choixNom == -1) choixNom=4;
                                        break;
                                    //touche entree
                                    case SDLK_RETURN:
                                        while_bool = 0;
                                        break;
                                    }
                                    break; 
                            }
                            //on remplie la variable pour le nom avec celui choisie
                            switch(choixNom){
                                case 0 :
                                    nomFichier = "Sauvegarde1";
                                    break;
                                case 1 :
                                    nomFichier = "Sauvegarde2";
                                    break;
                                case 2 :
                                    nomFichier = "Sauvegarde3";
                                    break;
                                case 3 :
                                    nomFichier = "Sauvegarde4";
                                    break;
                                case 4 :
                                    nomFichier = "Sauvegarde5";
                                    break;
                            } 
                        }
                    }
                    SauvegardePartie(nomFichier);                                                                                           //on sauvegarde dans le fichier choisie
                    return appuie;
                } else return appuie;
                break;
            default:
                break;
        }
    }
}

void SetUpPositions(void){
    lignes[0] = 114;
    lignes[1] = lignes[0]+32;
    lignes[2] = lignes[1]+32;
    lignes[3] = lignes[2]+32;
    lignes[4] = lignes[3]+33;
    lignes[5] = lignes[4]+32;
    lignes[6] = lignes[5]+34;
    lignes[7] = lignes[6]+32;
    lignes[8] = lignes[7]+33;
    lignes[9] = lignes[8]+32;
    lignes[10] = lignes[9]+33;
    lignes[11] = lignes[10]+32;
    colonnes[0] = 300;
    colonnes[1] = colonnes[0]+74;
    colonnes[2] = colonnes[1]+33;
    colonnes[3] = colonnes[2]+33;
    colonnes[4] = colonnes[3]+32;
    colonnes[5] = colonnes[4]+50;
    colonnes[6] = colonnes[5]+33;
    colonnes[7] = colonnes[6]+33;
    colonnes[8] = colonnes[7]+33;
}

void CreationTexture(void){
    //cercles
    image = SDL_LoadBMP("img/Cercles/Cercle_Couleur_B.bmp");                    //on charge l'image en tant que surface
    if (!image) ExitErreurSDL("creation de Cercle_Couleur_B");                  //si pas de surface creer (non NULL) on sort en erreurs
    cercleB = SDL_CreateTextureFromSurface(rendue,image);                       //on creer la texture via cette surface
    SDL_FreeSurface(image);                                                     //on libere en memoire la surface
    if (!cercleB) ExitErreurSDL("creation de la texture Cercle_Couleur_B");     //si la texture n'a pas ete creer on sort
                                                                                //la suite fonctionne de la meme maniere
    image = SDL_LoadBMP("img/Cercles/Cercle_Couleur_G.bmp");
    if (!image) ExitErreurSDL("creation de Cercle_Couleur_G");
    cercleG = SDL_CreateTextureFromSurface(rendue,image);
    SDL_FreeSurface(image);
    if (!cercleG) ExitErreurSDL("creation de la texture Cercle_Couleur_G");
    image = SDL_LoadBMP("img/Cercles/Cercle_Couleur_J.bmp");
    if (!image) ExitErreurSDL("creation de Cercle_Couleur_J");
    cercleJ = SDL_CreateTextureFromSurface(rendue,image);
    SDL_FreeSurface(image);
    if (!cercleJ) ExitErreurSDL("creation de la texture Cercle_Couleur_J");
    image = SDL_LoadBMP("img/Cercles/Cercle_Couleur_N.bmp");
    if (!image) ExitErreurSDL("creation de Cercle_Couleur_N");
    cercleN = SDL_CreateTextureFromSurface(rendue,image);
    SDL_FreeSurface(image);
    if (!cercleN) ExitErreurSDL("creation de la texture Cercle_Couleur_N");
    image = SDL_LoadBMP("img/Cercles/Cercle_Couleur_V.bmp");
    if (!image) ExitErreurSDL("creation de Cercle_Couleur_V");
    cercleV = SDL_CreateTextureFromSurface(rendue,image);
    SDL_FreeSurface(image);
    if (!cercleV) ExitErreurSDL("creation de la texture Cercle_Couleur_V");

    //flags
    image = SDL_LoadBMP("img/Flags/Flag_R.bmp");
    if (!image) ExitErreurSDL("creation de Flag_R");
    Flag_R = SDL_CreateTextureFromSurface(rendue,image);
    SDL_FreeSurface(image);
    if (!Flag_R) ExitErreurSDL("creation de la texture Flag_R");
    image = SDL_LoadBMP("img/Flags/Flag_W.bmp");
    if (!image) ExitErreurSDL("creation de Flag_W");
    Flag_W = SDL_CreateTextureFromSurface(rendue,image);
    SDL_FreeSurface(image);
    if (!Flag_W) ExitErreurSDL("creation de la texture Flag_W");

    //fond
    image = SDL_LoadBMP("img/Fond/Fond_mastermind.bmp");
    if (!image) ExitErreurSDL("creation de Fond_mastermind");
    Fond = SDL_CreateTextureFromSurface(rendue,image);
    SDL_FreeSurface(image);
    if (!Fond) ExitErreurSDL("creation de la texture Fond_mastermind");
}
