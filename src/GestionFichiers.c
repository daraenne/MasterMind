//include 
    //fichiers natif au C
        #include <stdio.h>
        #include <stdlib.h>
        #include <string.h>
        #include <time.h>
    //nos fichiers
        #include <GestionFichiers.h>
        #include <Define.h>
//

FILE *fichier = NULL;                                                                                       //fichiers à ouvrire pour l'ecriture ou la sauvegarde
//on recupere les variables importantes du programme
extern unsigned char NumeroTour, flag_tour[12], tour[4], code[4];
extern code_t tour_passe[12];   
extern Etat_t etat_courant;
char buff[10][255];

void LectureInstruction(char* nomSauvegarde){
    //ajout du chemin relatif pour les sauvegardes : Sauvegardes/
    char fd[255] = "Sauvegardes/";
    strncat(fd,nomSauvegarde,40);
    fichier = fopen(fd,"r");                                                                                //on ouvre le fichier en lecture seul
    fichier = fopen("ChoixDuJoueur.txt","r");

    char STRFichier[100];                                                                                   //string qui prendras les differentes lignes
    //date/heure
    fgets(STRFichier,100,fichier);
    printf("%s\n",STRFichier);
    //donnee utile
    fgets(STRFichier,100,fichier);
    printf("%s\n",STRFichier);
    //code
    fgets(STRFichier,100,fichier);
    printf("%s\n",STRFichier);
    fscanf(fichier,"%1d%1d%1d%1d",&code[0],&code[1],&code[2],&code[3]);
    printf("%1d%1d%1d%1d",code[0],code[1],code[2],code[3]);
    // for (char i=1; i<=NumeroTour; i++){
    //     if(i==NumeroTour) fscanf(fichier,"%d%d%d%d %02x\n",tour[0],tour[1],tour[2],tour[3],flag_tour[NumeroTour-1]);
    //     else fscanf(fichier,"%d%d%d%d %02x\n",tour_passe[i].pos1,tour_passe[i].pos2,tour_passe[i].pos3,tour_passe[i].pos4,flag_tour[NumeroTour-1]);
    // }
    fclose(fichier);
}

void SauvegardePartie(char* nomSauvegarde){
    //ajout du chemin relatif pour les sauvegardes : Sauvegardes/
    char fd[255] = "Sauvegardes/";
    strncat(fd,nomSauvegarde,40);
    fichier = fopen(fd,"w");                                                                                //on ouvre le fichier en ecritures seul (et on le creer si il n'existe pas)

    //ecriture dans le fichier
    //ecriture date
    time_t now;
    time(&now);                                                                                             //Renvoie l'heure actuelle
    struct tm *date = localtime(&now);                                                                      //Convertir au format heure locale
    fprintf(fichier,"partie sauvegardée le : %02d/%02d/%02d à %02d:%02d:%02d\n", date->tm_mday, date->tm_mon+1, date->tm_year+1900, date->tm_hour, date->tm_min, date->tm_sec);
    fprintf(fichier,"donnée utile :\n");
    //sauvegarde du code
    fprintf(fichier,"code : \n%d%d%d%d\n",code[0],code[1],code[2],code[3]);
    //sauvegarde du numero du tour
    fprintf(fichier,"numero du tour : \n%d\n",NumeroTour);
    //sauvegarde de l'etat
    switch(etat_courant){
        case Init :
            fprintf(fichier,"etat : \nInit\n");
            break;
        case Tour : 
            fprintf(fichier,"etat : \nTour\n");
            break;
        case Correspondance :
            fprintf(fichier,"etat : \nCorrespondance\n");
            break;
        case Fin :
            fprintf(fichier,"etat : \nFin\n");
            break;
        case Resolution_Manuelle :
            fprintf(fichier,"etat : \nResolution_Manuelle\n");
            break;
    }
    //ecriture partie
    fprintf(fichier,"partie :\n");
    for (char i=1; i<=NumeroTour; i++){
        if(i==NumeroTour) fprintf(fichier,"%d%d%d%d %02x\n",tour[0],tour[1],tour[2],tour[3],flag_tour[NumeroTour-1]);
        else fprintf(fichier,"%d%d%d%d %02x\n",tour_passe[i].pos1,tour_passe[i].pos2,tour_passe[i].pos3,tour_passe[i].pos4,flag_tour[NumeroTour-1]);
    }
    fclose(fichier);
}