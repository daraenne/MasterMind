//fichiers generaux
#include <stdio.h>
//mes fichiers
#include <SDL/SDL.h>
#include <Define.h>
#include <Affichage.h>

//fenetre
SDL_Window *fenetre = NULL;
SDL_Texture *screenshot = NULL;
//rendue
SDL_Renderer *rendue = NULL;
SDL_Renderer *rendueDeplacement = NULL;
//surface
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
//textes
SDL_Texture *T_continuer = NULL;
SDL_Texture *T_gen_man_EnCour = NULL;
SDL_Texture *T_gen_man = NULL;
SDL_Texture *T_gen_rand_Non = NULL;
SDL_Texture *T_gen_rand_Oui = NULL;
SDL_Texture *T_gen_rand = NULL;
SDL_Texture *T_quitter = NULL;
SDL_Texture *T_rejouer = NULL;

//rectangles pour textures
SDL_Rect Rect_Fond;
SDL_Rect Rect_Texte;
SDL_Rect Rect_cercleDeplacement;
SDL_Rect Rect_Screenshot;
SDL_Rect Rect_Code[4];
SDL_Rect Rect_Flag[4];
SDL_Rect Rect_Tour[4];
//tableaux pour les positions des lignes et colonnes
uint16_t lignes[12];
uint16_t colonnes[9];
//event
SDL_Event event;

void InitSDL(void){
    printf("init SDL\n");
    if (SDL_Init(SDL_INIT_VIDEO) != 0) ExitErreurSDL("Init");
    printf("crea window\n")
    fenetre = SDL_CreateWindow("Jeux du MasterMind", 2, 30, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!fenetre) ExitErreurSDL("creation de fenetre");
    printf("crea rendue\n");
    rendue = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
    if (!rendue) ExitErreurSDL("creation rendue");
    SDL_RenderPresent(rendue);
    CreationTexture();
    SetUpPositions();
    SetUpRectangles();
    affichage();
}

void ExitSDL(void){
    printf("exit SDL\n");
    SDL_RenderClear(rendue);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
}

void ExitErreurSDL(const char* location){
    printf("erreur SDL\n");
    SDL_Log("ERREUR :%s > %s\n", location, SDL_GetError());
    ExitSDL();
    exit(EXIT_FAILURE);
}

void affichage(void){
    printf("affichage\n");
    SDL_RenderCopy(rendue, Fond, NULL, &Rect_Fond);
    SDL_RenderPresent(rendue);
}

void affichageImage(choixImage_t choix, unsigned char tab[], unsigned char NumeroTour){
    printf("affichage image\n");
    unsigned char i=0, flagR=(tab[NumeroTour-1] & 0x0F), flagW=(tab[NumeroTour-1] >> 4);
    switch(choix){
        case AF_code:
            printf("affichage code\n");
            for(i=0;i<4;i++){
                switch (tab[i]){
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
            break;
        case flag:
            printf("affichage flag\n");
            i=0;
            for(char j=0;j<flagR;j++){
                Rect_Flag[i].y = lignes[NumeroTour-1];
                SDL_RenderCopy(rendue, Flag_R, NULL, &Rect_Flag[i]);
                i++;
            } for(char j=0;j<flagW;j++){
                Rect_Flag[i].y = lignes[NumeroTour-1];
                SDL_RenderCopy(rendue, Flag_W, NULL, &Rect_Flag[i]);
                i++;
            }
            break;
        case AF_tour:
            printf("affichage jeu\n");
            for(i=0;i<4;i++){
                Rect_Tour[i].y = lignes[NumeroTour-1];
                switch(tab[i]){
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
            break;
        case texte:
            printf("affichage texte\n");
            switch(tab[0]){
                case txt_continuer:
                    SDL_RenderCopy(rendue, T_continuer, NULL, &Rect_Texte);
                    break;
                case txt_gen_man:
                    SDL_RenderCopy(rendue, T_gen_man, NULL, &Rect_Texte);
                    break;
                case txt_gen_man_EnCour:
                    SDL_RenderCopy(rendue, T_gen_man_EnCour, NULL, &Rect_Texte);
                    break;
                case txt_gen_rand:
                    SDL_RenderCopy(rendue, T_gen_rand, NULL, &Rect_Texte);
                    break;
                case txt_gen_rand_Non:
                    SDL_RenderCopy(rendue, T_gen_rand_Non, NULL, &Rect_Texte);
                    break;
                case txt_gen_rand_Oui:
                    SDL_RenderCopy(rendue, T_gen_rand_Oui, NULL, &Rect_Texte);
                    break;
                case txt_quitter:
                    SDL_RenderCopy(rendue, T_quitter, NULL, &Rect_Texte);
                    break;
                case txt_rejouer:
                    SDL_RenderCopy(rendue, T_rejouer, NULL, &Rect_Texte);
                    break;
            }
            break;
    }
    SDL_RenderPresent(rendue);
}

void SetUpRectangles(void){
    printf("setup rectangles\n");
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
    //texte
    if (SDL_QueryTexture(T_continuer, NULL, NULL, &Rect_Texte.w, &Rect_Texte.h) != 0) ExitErreurSDL("Chargement Rectangle de texte");
    Rect_Texte.y = TextY;
    Rect_Texte.x = TextX;
}

unsigned char RecupTouche_B_SDL(void){
    printf("recup touche\n");
    while(SDL_WaitEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                printf("SDL quit\n");
                ExitSDL();
                exit(EXIT_SUCCESS);
                break;
            case SDL_KEYDOWN:
                printf("appuie touche\n");
                switch(event.key.keysym.sym){
                    case SDLK_RIGHT:
                        return t_droite;
                        break;
                    case SDLK_LEFT:
                        return t_gauche;
                        break;
                    case SDLK_RETURN:
                        return t_entree;
                        break;
                    case SDLK_SPACE:
                        return t_espace;
                        break;                  
                    default:
                        return 0;
                        break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                printf("appuie souris\n");
                if((event.button.x >= 350)&&(event.button.y >= 550)&&(event.button.x <= 480)&&(event.button.y <= 580)) return appuie_texteG;
                else if((event.button.x >= 530)&&(event.button.y >= 550)&&(event.button.x <= 650)&&(event.button.y <= 580)) return appuie_texteD;
                else if((event.button.x >= colonnes[0])&&(event.button.y >= lignes[0])&&(event.button.x <= (colonnes[0] + Rect_Code[0].w))&&(event.button.y <= (lignes[0] + Rect_Code[0].h))) return appuie_code1;
                else if((event.button.x >= colonnes[0])&&(event.button.y >= lignes[1])&&(event.button.x <= (colonnes[0] + Rect_Code[1].w))&&(event.button.y <= (lignes[1] + Rect_Code[1].h))) return appuie_code2;
                else if((event.button.x >= colonnes[0])&&(event.button.y >= lignes[2])&&(event.button.x <= (colonnes[0] + Rect_Code[2].w))&&(event.button.y <= (lignes[2] + Rect_Code[2].h))) return appuie_code3;
                else if((event.button.x >= colonnes[0])&&(event.button.y >= lignes[3])&&(event.button.x <= (colonnes[0] + Rect_Code[3].w))&&(event.button.y <= (lignes[3] + Rect_Code[3].h))) return appuie_code4;
                else if((event.button.x >= 733)&&(event.button.y >= 532)&&(event.button.x <= 834)&&(event.button.y <= 586)) return t_entree;
                else {
                    rendueDeplacement = SDL_GetRenderer(fenetre);
                    Rect_cercleDeplacement.x = event.motion.x - (Rect_cercleDeplacement.w / 2);
                    Rect_cercleDeplacement.y = event.motion.y - (Rect_cercleDeplacement.h / 2);
                    SDL_RenderCopy(rendueDeplacement, cercleB, NULL, &Rect_cercleDeplacement);
                    SDL_RenderPresent(rendueDeplacement);
                    SDL_RenderClear(rendueDeplacement);
                    SDL_RenderPresent(rendue);




                    /*
                    SDL_SaveBMP(SDL_GetWindowSurface(fenetre), "img/save/screenshot.bmp");
                    Rect_cercleDeplacement.x = event.motion.x - (Rect_cercleDeplacement.w / 2);
                    Rect_cercleDeplacement.y = event.motion.y - (Rect_cercleDeplacement.h / 2);
                    SDL_RenderCopy(rendue, cercleB, NULL, &Rect_cercleDeplacement);
                    SDL_RenderPresent(rendue);
                    image = SDL_LoadBMP("img/save/screenshot.bmp");
                    if (!image) ExitErreurSDL("recup de screenshot.bmp");
                    screenshot = SDL_CreateTextureFromSurface(rendue, image);
                    SDL_FreeSurface(image);
                    if (SDL_QueryTexture(screenshot, NULL, NULL, &Rect_Screenshot.w, &Rect_Screenshot.h) != 0) ExitErreurSDL("Chargement Rectangle du screenshot");
                    Rect_Screenshot.y = 0;
                    Rect_Screenshot.x = 0;
                    SDL_RenderCopy(rendue, screenshot, NULL, &Rect_Screenshot);
                    SDL_RenderPresent(rendue);*/
                    return appuie;
                }
                break;
            default:
                break;
        }
    }
}

void SetUpPositions(void){
    printf("setup positions\n");
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
    printf("crea texture\n");
    //cercles
    image = SDL_LoadBMP("img/Cercles/Cercle_Couleur_B.bmp");
    if (!image) ExitErreurSDL("creation de Cercle_Couleur_B");
    cercleB = SDL_CreateTextureFromSurface(rendue,image);
    SDL_FreeSurface(image);
    if (!cercleB) ExitErreurSDL("creation de la texture Cercle_Couleur_B");
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

    //Textes
    image = SDL_LoadBMP("img/Textes/continuer.bmp");
    if (!image) ExitErreurSDL("creation de T_continuer");
    T_continuer = SDL_CreateTextureFromSurface(rendue,image);
    SDL_FreeSurface(image);
    if (!T_continuer) ExitErreurSDL("creation de la texture T_continuer");
    image = SDL_LoadBMP("img/Textes/gen_man_EnCour.bmp");
    if (!image) ExitErreurSDL("creation de T_gen_man_EnCour");
    T_gen_man_EnCour = SDL_CreateTextureFromSurface(rendue,image);
    SDL_FreeSurface(image);
    if (!T_gen_man_EnCour) ExitErreurSDL("creation de la texture T_gen_man_EnCour");
    image = SDL_LoadBMP("img/Textes/gen_man.bmp");
    if (!image) ExitErreurSDL("creation de T_gen_man");
    T_gen_man = SDL_CreateTextureFromSurface(rendue,image);
    SDL_FreeSurface(image);
    if (!T_gen_man) ExitErreurSDL("creation de la texture T_gen_man");
    image = SDL_LoadBMP("img/Textes/gen_rand_Non.bmp");
    if (!image) ExitErreurSDL("creation de T_gen_rand_Non");
    T_gen_rand_Non = SDL_CreateTextureFromSurface(rendue,image);
    SDL_FreeSurface(image);
    if (!T_gen_rand_Non) ExitErreurSDL("creation de la texture T_gen_rand_Non");
    image = SDL_LoadBMP("img/Textes/gen_rand_Oui.bmp");
    if (!image) ExitErreurSDL("creation de T_gen_rand_Oui");
    T_gen_rand_Oui = SDL_CreateTextureFromSurface(rendue,image);
    SDL_FreeSurface(image);
    if (!T_gen_rand_Oui) ExitErreurSDL("creation de la texture T_gen_rand_Oui");
    image = SDL_LoadBMP("img/Textes/gen_rand.bmp");
    if (!image) ExitErreurSDL("creation de T_gen_rand");
    T_gen_rand = SDL_CreateTextureFromSurface(rendue,image);
    SDL_FreeSurface(image);
    if (!T_gen_rand) ExitErreurSDL("creation de la texture T_gen_rand");
    image = SDL_LoadBMP("img/Textes/quitter.bmp");
    if (!image) ExitErreurSDL("creation de T_quitter");
    T_quitter = SDL_CreateTextureFromSurface(rendue,image);
    SDL_FreeSurface(image);
    if (!T_quitter) ExitErreurSDL("creation de la texture T_quitter");
    image = SDL_LoadBMP("img/Textes/rejouer.bmp");
    if (!image) ExitErreurSDL("creation de T_rejouer");
    T_rejouer = SDL_CreateTextureFromSurface(rendue,image);
    SDL_FreeSurface(image);
    if (!T_rejouer) ExitErreurSDL("creation de la texture T_rejouer");
}
