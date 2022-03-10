#ifndef AFFICHAGE_H
#define AFFICHAGE_H

//define
#define WINDOW_HEIGHT 720
#define WINDOW_WIDTH 980
//position du texte
#define TextX 276
#define TextY 517

//mes fichiers
#include <SDL/SDL.h>

//fonxtions
void InitSDL(void);
void ExitSDL(void);
void ExitErreurSDL(const char* location);
void affichage(void);
void SDL_Printf(char* message, unsigned char ligne);
void affichageImage(choixImage_t choix, unsigned char tab[], unsigned char NumeroTour);
void CreationTexture(void);
void SetUpRectangles(void);
void SetUpPositions(void);
unsigned char RecupTouche_B_SDL(void);

#endif // !AFFICHAGE_H
