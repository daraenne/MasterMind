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

    char STRFichier[100];                                                                                   //string qui prendras les differentes lignes
    //date/heure
    fgets(STRFichier,100,fichier);
    printf("%s",STRFichier);
    //donnee utile
    fgets(STRFichier,100,fichier);
    printf("%s",STRFichier);
    //code
    fgets(STRFichier,100,fichier);
    printf("%s",STRFichier);
    fscanf(fichier,"%1d%1d%1d%1d\n",&code[0],&code[1],&code[2],&code[3]);
    printf("code : %d %d %d %d\n",code[0],code[1],code[2],code[3]);
    //numero du tour
    fgets(STRFichier,100,fichier);
    printf("%s",STRFichier);
    fscanf(fichier,"%02d\n",&NumeroTour);
    printf("numero du tour : %d",NumeroTour);
    //recuperation de l'etat
    fgets(STRFichier,100,fichier);
    printf("%s",STRFichier);
    fgets(STRFichier,100,fichier);
    if(strcmp(STRFichier,"Init\n") == 0) etat_courant = Init;
    else if (strcmp(STRFichier,"Tour\n") == 0) etat_courant = Tour;
    else if (strcmp(STRFichier,"Correspondance\n") == 0) etat_courant = Correspondance;
    else if (strcmp(STRFichier,"Fin\n") == 0) etat_courant = Fin;
    else if (strcmp(STRFichier,"Resolution_Manuelle\n") == 0) etat_courant = Resolution_Manuelle;
    else {
        printf("erreur chargement  etat");
        exit(EXIT_FAILURE);
    }
    //recuperation partie si entame
    for (char i=1; i<=NumeroTour; i++){
        if(i==NumeroTour) fscanf(fichier,"%1d%1d%1d%1d %02x\n",&tour[0],&tour[1],&tour[2],&tour[3],&flag_tour[i-1]);
        else fscanf(fichier,"%1d%1d%1d%1d %02x\n",&tour_passe[i-1].pos1,&tour_passe[i-1].pos2,&tour_passe[i-1].pos3,&tour_passe[i-1].pos4,&flag_tour[i-1]);
    }
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
    fprintf(fichier,"code : \n%1d%1d%1d%1d\n",code[0],code[1],code[2],code[3]);
    //sauvegarde du numero du tour
    fprintf(fichier,"numero du tour : \n%02d\n",NumeroTour);
    //sauvegarde de l'etat
    switch(etat_courant){
        case Init :
            fprintf(fichier,"etat (mettre Tour pour resolution automatique sinon Resolution_Manuelle): \nInit\n");
            break;
        case Tour : 
            fprintf(fichier,"etat (mettre Tour pour resolution automatique sinon Resolution_Manuelle): \nTour\n");
            break;
        case Correspondance :
            fprintf(fichier,"etat (mettre Tour pour resolution automatique sinon Resolution_Manuelle): \nCorrespondance\n");
            break;
        case Fin :
            fprintf(fichier,"etat (mettre Tour pour resolution automatique sinon Resolution_Manuelle): \nFin\n");
            break;
        case Resolution_Manuelle :
            fprintf(fichier,"etat (mettre Tour pour resolution automatique sinon Resolution_Manuelle): \nResolution_Manuelle\n");
            break;
    }
    //ecriture partie
    fprintf(fichier,"partie :\n");
    for (char i=1; i<=NumeroTour; i++){
        if(i==NumeroTour) fprintf(fichier,"%1d%1d%1d%1d %02x\n",tour[0],tour[1],tour[2],tour[3],flag_tour[i-1]);
        else fprintf(fichier,"%1d%1d%1d%1d %02x\n",tour_passe[i-1].pos1,tour_passe[i-1].pos2,tour_passe[i-1].pos3,tour_passe[i-1].pos4,flag_tour[i-1]);
    }
    fclose(fichier);
}
