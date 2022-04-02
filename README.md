# MOProc_2022_G01_Mastermind
## Infos
***
Ce projet est un MasterMind qui est soit jouable par un vrai joueur <br>
soit automatiquement résolue par l'ordinateur <br>
## Compilation/lancement
***
Pour l'installation et le lancement :
```
$ git clone https://forge.univ-lyon1.fr/mo-progc/moproc_2022_g01_mastermind.git
$ cd ../path/to/the/file
$ ./bin/MasterMind
```
***
1. Pour compiler le programme il faut en premier lieu installer GCC : <br>
voici un lien pour installer MINGW32 si vous n'avez pas GCC, cela vous installera en prime G++ et GDB. <br>
<a href="https://winlibs.com/"> winlibs <br> </a>

2. Puis il faudra le mettre en variable PATH (les deux autres s'y mettront aussi automatiquement) :<br>
décompressez MINGW puis mettez le la ou vous voulez. <br>

> En général, si vous êtes sous Windows, on préfère mettre les programmes 64bit dans ```c:/Programmes\ (x86)/``` et les 32bit dans ```c:/Programmes/``` <br>

3. Sous Windows il faudra chercher dans le menu Windows ```modifier les variable d'environement``` <br>
4. puis cliquez sur ```variables d'environement``` <br>
5. puis double-cliquez sur ```Path``` <br>
6. et y ajouter le chemin vers le dossier bin de MINGW. <br>

Pour compiler il suffira enfin de faire :
```
$ cd ../path/to/the/file
$ gcc src/*.c -o bin/MasterMind -I include -L lib/SDL -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf
```
> ou si vous ne voulez pas garder le terminal occupé durant l'exécution du programme
```
$ gcc src/*.c -o bin/MasterMind -I include -L lib/SDL -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -mwindows
```
## Auteurs
***
BOLLIAND Thomas <br>
LACOSTE Gabriel <br>
## Fonctionnalités
Comme dit plus haut ce programme lance un jeu du MasterMind. <br>
Lors du lancement, vous aurez plusieurs choix à faire : <br>
* Le mode de résolution (par l'ordinateur ou par un joueur).
* La méthode de génération du code (pareille au mode de résolution).
* Puis le jeux se lancera selon ce que votre choix.
