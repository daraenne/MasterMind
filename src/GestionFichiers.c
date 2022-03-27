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


void LectureInstruction(void){
    fichier = fopen("ChoixDuJoueur.txt","r");
    if (fichier == NULL) {
        printf("Probleme ouverture fichier pour lecture");
        exit(EXIT_FAILURE);
    }

    fclose(fichier);
}

void SauvegardePartie(char* nomSauvegarde){
    //ajout du chemin relatif pour les sauvegardes : Sauvegardes/
    char fd[255] = "Sauvegardes/";
    strncat(fd,nomSauvegarde,40);
    fichier = fopen(fd,"w");                                                                                //on ouvre le fichier (et on le creer si il n'existe pas)

    //ecriture dans le fichier
    //ecriture date
    time_t now;
    time(&now);                                                                                             //Renvoie l'heure actuelle
    struct tm *date = localtime(&now);                                                                      //Convertir au format heure locale
    fprintf(fichier,"partie sauvegardée le : %02d/%02d/%02d à %02d:%02d:%02d\n", date->tm_mday, date->tm_mon+1, date->tm_year+1900, date->tm_hour, date->tm_min, date->tm_sec);
    //ecriture partie
    fprintf(fichier,"partie :\n");
    for (char i=1; i<=NumeroTour; i++){
        if(i==NumeroTour) fprintf(fichier,"%d%d%d%d %02x\n",tour[0],tour[1],tour[2],tour[3],flag_tour[NumeroTour-1]);
        else fprintf(fichier,"%d%d%d%d %02x\n",tour_passe[i].pos1,tour_passe[i].pos2,tour_passe[i].pos3,tour_passe[i].pos4,flag_tour[NumeroTour-1]);
    }
    fprintf(fichier,"\ndonnée utile :\n");
    //sauvegarde du code
    fprintf(fichier,"code : %d%d%d%d\n",code[0],code[1],code[2],code[3]);
    //sauvegarde du numero du tour
    fprintf(fichier,"numero du tour : %d\n",NumeroTour);
    //sauvegarde de l'etat
    switch(etat_courant){
        case Init :
            fprintf(fichier,"etat : Init\n");
            break;
        case Tour : 
            fprintf(fichier,"etat : Tour\n");
            break;
        case Correspondance :
            fprintf(fichier,"etat : Correspondance\n");
            break;
        case Fin :
            fprintf(fichier,"etat : Fin\n");
            break;
        case Resolution_Manuelle :
            fprintf(fichier,"etat : Resolution_Manuelle\n");
            break;
    }
    fclose(fichier);
}