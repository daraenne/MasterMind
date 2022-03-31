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
//variable de resolution de probleme temporaires
unsigned char bufferTour[4], bufferFlag;

void LectureInstruction(char* nomSauvegarde){
    char etat_tour = 0;
    //ajout du chemin relatif pour les sauvegardes : Sauvegardes/
    char fd[255] = "Sauvegardes/";
    strncat(fd,nomSauvegarde,40);
    fichier = fopen(fd,"r");                                                                                //on ouvre le fichier en lecture seul
    char STRFichier[100];                                                                                   //string qui prendras les differentes lignes
    //date/heure
    fgets(STRFichier,100,fichier);
    //donnee utile
    fgets(STRFichier,100,fichier);
    //code
    fgets(STRFichier,100,fichier);
    fscanf(fichier,"%1d%1d%1d%1d\n",&code[0],&code[1],&code[2],&code[3]);
    //numero du tour
    fgets(STRFichier,100,fichier);
    fscanf(fichier,"%02d\n",&NumeroTour);
    //recuperation de l'etat forcement resolution manuelle car on ne sauvegarde pas de partie automatique
    etat_courant = Resolution_Manuelle;
    //recuperation partie si entame
    fgets(STRFichier,100,fichier);
    for (char i=0; i<NumeroTour; i++){
        if(i == (NumeroTour-1)) {
            fscanf(fichier,"%1d%1d%1d%1d %02x\n",&bufferTour[0],&bufferTour[1],&bufferTour[2],&bufferTour[3],&bufferFlag);
            for(char j=0;j<4;j++) tour[j]=bufferTour[j];
            flag_tour[i] = bufferFlag;
        } else {
            fscanf(fichier,"%1d%1d%1d%1d %02x\n",&tour_passe[i].pos1,&tour_passe[i].pos2,&tour_passe[i].pos3,&tour_passe[i].pos4,&flag_tour[i]);
        }
    }
    fclose(fichier);
    NumeroTour--;                                                                                           //pour eviter de sauter un tour car la sauvegarde se passant lors du tour : NumeroTour; lorsqu'ont revient au debut de l'etat resolution... on augment NumeroTour de 1
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
    //ecriture partie
    fprintf(fichier,"partie :\n");
    for (char i=1; i<=NumeroTour; i++){
        if(i==NumeroTour) fprintf(fichier,"%1d%1d%1d%1d %02x\n",tour[0],tour[1],tour[2],tour[3],flag_tour[i-1]);
        else fprintf(fichier,"%1d%1d%1d%1d %02x\n",tour_passe[i-1].pos1,tour_passe[i-1].pos2,tour_passe[i-1].pos3,tour_passe[i-1].pos4,flag_tour[i-1]);
    }
    fclose(fichier);
}
