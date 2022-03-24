//fichiers generaux
#include <stdio.h>
//mes fichiers
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <Define.h>
#include <Affichage.h>

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

void InitSDL(void){
    if (SDL_Init(SDL_INIT_VIDEO) != 0) ExitErreurSDL("Init");
    if (TTF_Init() != 0) ExitErreurSDL("Init texte");

    fenetre = SDL_CreateWindow("Jeux du MasterMind", 2, 30, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!fenetre) ExitErreurSDL("creation de fenetre");
    rendue = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
    if (!rendue) ExitErreurSDL("creation rendue");
    SDL_RenderPresent(rendue);
    CreationTexture();
    SetUpPositions();
    SetUpRectangles();
    affichage();
}

void ExitSDL(void){
    SDL_DestroyRenderer(rendue);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
}

void ExitErreurSDL(const char* location){
    SDL_Log("ERREUR :%s > %s\n", location, SDL_GetError());
    ExitSDL();
    exit(EXIT_FAILURE);
}

void affichage(void){
    extern unsigned char etape_affichage, NumeroTour, Automatique;
    extern code_t tour_passe[12];
    extern unsigned char flag_tour[12], tour[4], code[4];
    unsigned char k;
    SDL_RenderCopy(rendue, Fond, NULL, &Rect_Fond);
    if((etape_affichage > 0) && (Automatique)){
        for(char i=0;i<4;i++){
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
    if(etape_affichage > 1){
        for(unsigned char i=0; i<(NumeroTour-1); i++){
            Rect_Tour[0].y = lignes[i];
            switch(tour_passe[i].pos1){
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
            switch(tour_passe[i].pos2){
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
            switch(tour_passe[i].pos3){
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
            switch(tour_passe[i].pos4){
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
            for(char j=0;j<(flag_tour[i] & 0x0F);j++){
                Rect_Flag[j].y = lignes[i];
                SDL_RenderCopy(rendue, Flag_R, NULL, &Rect_Flag[j]);
            } for(char j=(flag_tour[i] & 0x0F);j<((flag_tour[i] & 0x0F)+(flag_tour[i] >> 4));j++){
                Rect_Flag[j].y = lignes[i];
                SDL_RenderCopy(rendue, Flag_W, NULL, &Rect_Flag[j]);
            }
        }
        for(char i=0;i<4;i++){
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
        for(char i=0;i<(flag_tour[NumeroTour-1] & 0x0F);i++){
            Rect_Flag[i].y = lignes[NumeroTour-1];
            SDL_RenderCopy(rendue, Flag_R, NULL, &Rect_Flag[i]);
        } for(char i=(flag_tour[NumeroTour-1] & 0x0F);i<((flag_tour[NumeroTour-1] & 0x0F)+(flag_tour[NumeroTour-1] >> 4));i++){
            Rect_Flag[i].y = lignes[NumeroTour-1];
            SDL_RenderCopy(rendue, Flag_W, NULL, &Rect_Flag[i]);
        }
        
    }
    SDL_RenderPresent(rendue);
}

void SDL_Printf(const char* message,unsigned char ligne){
    SDL_Color C_Black;C_Black.a = 255;C_Black.r = 0;C_Black.g = 0;C_Black.b = 0;
    SDL_Rect Rect_Text;
    SDL_Surface *SurTexte=NULL;
    SDL_Texture *Texte=NULL;
    TTF_Font *police=NULL;
    switch(ligne){
        case 1:
            police = TTF_OpenFont("Polices/arial.ttf",20);
            if(!police) ExitErreurSDL("erreur creation police");
            printf("%s\n",message);
            SurTexte = TTF_RenderText_Solid(police, message, C_Black);
            if (!SurTexte) ExitErreurSDL("creation de Surtexte");
            Texte = SDL_CreateTextureFromSurface(rendue, SurTexte);
            if (!Texte) ExitErreurSDL("creation de Texte");
            SDL_FreeSurface(SurTexte);
            SDL_QueryTexture(Texte,NULL,NULL,&Rect_Text.w,&Rect_Text.h);
            Rect_Text.x = 275 + ((455-Rect_Text.w)/2);
            Rect_Text.y = 516 + ((39-Rect_Text.h)/2);
            SDL_RenderCopy(rendue,Texte,NULL,&Rect_Text);
            SDL_RenderPresent(rendue);
            break;
        case 2:
            police = TTF_OpenFont("Polices/BabySchoolItalic.ttf",20);
            if(!police) ExitErreurSDL("erreur creation police");
            printf("%s\n",message);
            TTF_SetFontStyle(police, TTF_STYLE_UNDERLINE);
            SurTexte = TTF_RenderText_Solid(police, message, C_Black);
            if (!SurTexte) ExitErreurSDL("creation de Surtexte");
            Texte = SDL_CreateTextureFromSurface(rendue, SurTexte);
            if (!Texte) ExitErreurSDL("creation de Texte");
            SDL_FreeSurface(SurTexte);
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
    extern unsigned char NumeroTour;
    while(SDL_WaitEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                ExitSDL();
                exit(EXIT_SUCCESS);
                break;
            case SDL_KEYDOWN:
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
                if((event.button.x >= colonnes[0])&&(event.button.y >= lignes[0])&&(event.button.x <= (colonnes[0] + Rect_Code[0].w))&&(event.button.y <= (lignes[0] + Rect_Code[0].h))) return appuie_code1;
                else if((event.button.x >= colonnes[0])&&(event.button.y >= lignes[1])&&(event.button.x <= (colonnes[0] + Rect_Code[1].w))&&(event.button.y <= (lignes[1] + Rect_Code[1].h))) return appuie_code2;
                else if((event.button.x >= colonnes[0])&&(event.button.y >= lignes[2])&&(event.button.x <= (colonnes[0] + Rect_Code[2].w))&&(event.button.y <= (lignes[2] + Rect_Code[2].h))) return appuie_code3;
                else if((event.button.x >= colonnes[0])&&(event.button.y >= lignes[3])&&(event.button.x <= (colonnes[0] + Rect_Code[3].w))&&(event.button.y <= (lignes[3] + Rect_Code[3].h))) return appuie_code4;
                else if((event.button.x >= 733)&&(event.button.y >= 532)&&(event.button.x <= 834)&&(event.button.y <= 586)) return t_entree;
                else if((event.button.x >= colonnes[1])&&(event.button.y >= lignes[NumeroTour-1])&&(event.button.x <= (colonnes[1] + Rect_Code[0].w))&&(event.button.y <= (lignes[NumeroTour-1] + Rect_Code[0].h))) return appuie_Tour1;
                else if((event.button.x >= colonnes[2])&&(event.button.y >= lignes[NumeroTour-1])&&(event.button.x <= (colonnes[2] + Rect_Code[1].w))&&(event.button.y <= (lignes[NumeroTour-1] + Rect_Code[1].h))) return appuie_Tour2;
                else if((event.button.x >= colonnes[3])&&(event.button.y >= lignes[NumeroTour-1])&&(event.button.x <= (colonnes[3] + Rect_Code[2].w))&&(event.button.y <= (lignes[NumeroTour-1] + Rect_Code[2].h))) return appuie_Tour3;
                else if((event.button.x >= colonnes[4])&&(event.button.y >= lignes[NumeroTour-1])&&(event.button.x <= (colonnes[4] + Rect_Code[3].w))&&(event.button.y <= (lignes[NumeroTour-1] + Rect_Code[3].h))) return appuie_Tour4;
                else return appuie;
                break;
            case SDL_MOUSEMOTION:
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
}
