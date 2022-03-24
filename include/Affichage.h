#ifndef AFFICHAGE_H
#define AFFICHAGE_H

//define
    //taille fenetre
    #define WINDOW_HEIGHT 720
    #define WINDOW_WIDTH 980
    //position du texte
    #define TextX 276
    #define TextY 517
//

//fonctions
    //fonctions d'initialisation (appeler une seul fois en debut de programme)
        void InitSDL(void);                                         //fonction qui initialise tout ce dont on a besoin pour la SDL
        void SetUpRectangles(void);                                 //fonction qui initialise les different rectangle au possible
        void SetUpPositions(void);                                  //fonction qui simplifie la gestion des positions pour les cercles (ligne[0] = tour 1, colonne[0] = code)
        void CreationTexture(void);                                 //fonction qui creer les textures des differentes images
    //fonctions de sortie (qui permettent d'arreter le programme)
        void ExitSDL(void);                                         //fontions qui ferme tout ce qu'il faut pour quitter la SDL
        void ExitErreurSDL(const char* location);                   //fonction qui va faire quiter la SDL au programme afficher l'erreur qui est arriver ainsi que sa localisation (a mettre en parametre) puis fermer le programme
    //fonctions d'affichages
        void affichage(void);                                       //fonctions qui affiche tout ce qu'il faut celon ou l'ont se situe dans le programme
        void SDL_Printf(const char* message, unsigned char ligne);  //fonctions qui affiche dans la zone de texte le message qu'ont lui met en parametre a la ligne qu'ont lui met en 2eme parametre
    //fonction d'input    
        unsigned char RecupTouche_B_SDL(void);                      //fonction qui renvoie un code celon ce qui ce passe dans la fenetre de SDL
//

#endif // !AFFICHAGE_H
