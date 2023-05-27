//grid verifying pour qu'il n y ait pas 3 matching cells au départ

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define minGridSize 5
#define maxGridSize 26


#define minSymbols 4
#define maxSymbols 6

#define EMPTY_CELL ' '
#define BUFFER_SIZE 4096

// Structure représentant une cellule du plateau
typedef struct {
    char symbol;
    int color;
    int validMatches;
} Cell;

char  letters[] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z', };
 
 char symbols[] = { 'A', 'B', 'C', 'D', 'E', 'F' };
 
int pNumberOfSymbols =5;

int pGridLines =8;

int pGridColumns =8;

Cell board[maxGridSize][maxGridSize];


int score =0;

int validsSwaps =0;


// Couleurs des lettres
#define COLOR_RED    "\x1b[31m"
#define COLOR_GREEN  "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE   "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN   "\x1b[36m"
#define COLOR_RESET  "\x1b[0m"


// Générer la matrice
void fillBoard() 
{
   
    for (int i = 0; i < pGridLines; i++) {
        for (int j = 0; j < pGridColumns; j++) 
        {
          
            int index = rand() % pNumberOfSymbols;

                board[i][j].symbol = symbols[index];
                board[i][j].color = index;
                board[i][j].validMatches = 0;

            // s'assurer que la matrice générée, ne contient pas des cellules de type match-3 sur une même ligne
            if ((j>=2 &&    board[i][j-1].symbol==symbols[index] &&    board[i][j-2].symbol==symbols[index]  )
               ||
               (j==pGridColumns-1 &&    board[i][j-1].symbol==symbols[index] &&    board[i][0].symbol==symbols[index]  )
               ||
               (j==pGridColumns-1 &&    board[i][1].symbol==symbols[index] &&    board[i][0].symbol==symbols[index]  )
             

                 ) 
            {
                    char  varBadLeftSymbol= symbols[index];

                    while (varBadLeftSymbol == symbols[index])
                     {
                            index = rand() % pNumberOfSymbols;
                           
                      }
                
                 board[i][j].symbol = symbols[index];
                 board[i][j].color = index;
                 board[i][j].validMatches = 0;

            }
            // s'assurer que la matrice générée, ne contient pas des cellules de type match-3 sur une même colonne
            if ( (i>=2 &&    board[i-1][j].symbol==symbols[index] &&    board[i-2][j].symbol==symbols[index]  )

            ||
               (i==pGridLines-1 &&    board[i-1][j].symbol==symbols[index] &&    board[0][j].symbol==symbols[index]  )
            ||
               (i==pGridLines-1 &&    board[1][j].symbol==symbols[index] &&    board[0][j].symbol==symbols[index]  )
              )
            {
                    char  varBadUpSymbol= symbols[index];

                    while (varBadUpSymbol == symbols[index] || varBadUpSymbol == symbols[index] )
                     {
                            index = rand() % pNumberOfSymbols;
                           
                      }
                
                 board[i][j].symbol = symbols[index];
                 board[i][j].color = index;
                 board[i][j].validMatches = 0;

            }



        }
    }
}

// pour se déplacer en horizontale au sein de la matrice
// MvtH(i,1) permet de faire un déplacement horizontale d'une case vers la droite pour une celllule qui se trouve au niveau de la colonne i. 
// MvtH(i,1) permet de faire un déplacement horizontale d'une case vers la gauche pour une celllule qui se trouve au niveau de la colonne i.
// Exemple : Pour une matrice de 8 lignes et 8 colonnes : MvtH(7,1)=0 ==> la colonne suivante à la colonne 7 est la colonne 0
//                                                      : MvtH(5,1)=6 ==> la colonne suivante à la colonne 5 est la colonne 6
//                                                      : MvtH(0,-1)=7 ==> la colonne précédente à la colonne 0 est la colonne 7
int MvtH(int varIndex, int varNumber)
{

   int result =  (varIndex + varNumber )% pGridColumns;
   if (result<0) result=pGridColumns+result;
   return result;


}


// pour se déplacer en verticale ale au sein de la matrice
// MvtV(i,1) permet de faire un déplacement verticale d'une case vers le bas  pour une celllule qui se trouve au niveau de la ligne i. 
// MvtV(i,1) permet de faire un déplacement verticale d'une case vers le haut pour une celllule qui se trouve au niveau de la ligne i.
// Exemple : Pour une matrice de 8 lignes et 8 colonnes : MvtV(7,1)=0 ==> la ligne suivante à la ligne 7 est la ligne 0
//                                                      : MvtV(5,1)=6 ==> la ligne suivante à la ligne 5 est la ligne 6
//                                                      : MvtV(0,-1)=7 ==> la ligne précédente à la ligne 0 est la ligne 7

int MvtV(int varIndex, int varNumber)
{

   int result =  (varIndex + varNumber )% pGridLines;
   if (result<0) result=pGridLines+result;
   return result;


}





// Fonction d'affichage de la matrice
void printBoard()
 {
    printf("   ");
    for (int i = 0; i < pGridColumns; i++)
        printf("%c ", letters[i]);
    printf("\n");

    for (int i = 0; i < pGridLines; i++) {
        printf("%2d ", i + 1);
        for (int j = 0; j < pGridColumns; j++) {
            int color = board[i][j].color;
            const char* colorCode;
            switch (color) {
                case 0:
                    colorCode = COLOR_MAGENTA;
                    break;
                case 1:
                    colorCode = COLOR_RED;
                    break;
                case 2:
                    colorCode = COLOR_GREEN;
                    break;
                case 3:
                    colorCode = COLOR_YELLOW;
                    break;
                case 4:
                    colorCode = COLOR_BLUE;
                    break;
                case 5:
                    colorCode = COLOR_MAGENTA;
                    break;
                
                    
                default:
                    colorCode = COLOR_RESET;
                    break;
            }
            printf("%s%c%s ", colorCode, board[i][j].symbol, COLOR_RESET);
        }
        printf("\n");
    }
}



   




 
//gravity vertical
// deplace la cellule (i-1, j) en dessus de (i,j) vers i,j et deplace la cellule (i-2,j )vers i-1,j juqu'à la cellule 0,0
 void applyGravity(int i, int j )

  {

                board[i][j].symbol= EMPTY_CELL;
                board[i][j].color= 10;
                board[i][j].validMatches= 0;
             

       if (i== 0)
        {
              // printf("Cell-0 i %d j %d \n",i,j);
                board[i][j].symbol= EMPTY_CELL;
                board[i][j].color= 10;
                board[i][j].validMatches= 0;
        }
        else 
            {    
                   for (int k = i; k >0 ; k--)  
                    { 
                        
                         if (board[k-1][j].symbol!=EMPTY_CELL)  
                         {
                             
                              board[k][j] = board[k-1][j] ; 
                         
                               board[k-1][j].symbol= EMPTY_CELL;
                               board[k-1][j].color= 10;
                               board[k-1][j].validMatches= 0;
                         
                         }

                     
                        //  if( j==7) printf("Cell i %d j %d - Mvts  k-1 %d j %d vers k %d j %d  \n",i,j,k-1,j,k,j);
                    }
                   
                    board[0][j].symbol= EMPTY_CELL;
                    board[0][j].color= 10;
                    board[0][j].validMatches= 0;

            }

   

  }



// Vérifie si un symbole exite au moins MinNumber
// Dans notre cas, MinNumber=3

int  ExistingSymbol( char symbol, int MinNumber) {

    int count = 0;
     for (int i = 0; i < pGridLines; i++) 
            {       
                for (int j = 0; j < pGridColumns; j++)
                    {
                        if (board[i][j].symbol == symbol) count++;
                        if (count==MinNumber) return 1;
                    }
            }
    return 0;
}
  
 

// Vérifie si la martice contient un groupe d'au moins trois éléments identiques qui puevent matcher avec un   mouvement valide
int hasMatchingCells() {
    // Vérification des lignes
    for (int i = 0; i < pGridLines; i++) {
        int count = 1;
        for (int j = 0; j < pGridColumns; j++) {
            if (board[i][j].symbol != EMPTY_CELL && board[i][j].symbol == board[i][MvtH(j,+1)].symbol)
               count++;
            else
                count = 1;
         // count>= 2 veut dire qu'il y'a au mois deux cellules cote à cote contenant le même symblole
         // On doit juste s'assurer qu'il y a une troisième cellule contenant  le même symbole
        if ((count >= 2) && ExistingSymbol(board[i][j].symbol,3)==1)
                return 1;
        }
    }

    // Vérification des colonnes
    for (int j = 0; j < pGridColumns; j++) {
        int count = 1;
        for (int i = 0; i < pGridLines; i++) {
            if (board[i][j].symbol != EMPTY_CELL && board[i][j].symbol == board[MvtV(i, +1)][j].symbol)
                count++;
            else
                count = 1;

            if ((count >= 2) && ExistingSymbol(board[i][j].symbol,3)==1)
                return 1;
        }
    }

    return 0;
}
 
// Remplit le plateau avec des symboles aléatoires



// Vérifie si un mouvement est valide
int isValidMove(int row1, int col1, int row2, int col2) {
     
    char varSymbol= board[row1][col1].symbol;

    if (


            // Vérifie si le mouvement est valide avec les cellules voisins de la même ligne
         (  board[row2][MvtH(col2,-1)].symbol==varSymbol  && board[row2][MvtH(col2,+1)].symbol==varSymbol )
          ||
        (  board[row2][MvtH(col2,+1)].symbol==varSymbol  && board[row2][MvtH(col2,+2)].symbol==varSymbol )
          ||
        (  board[row2][MvtH(col2,-1)].symbol==varSymbol  && board[row2][MvtH(col2,-2)].symbol==varSymbol )

          ||
        // Vérifie si le mouvement est valide avec les cellules voisins de la même colonne
         (  board[MvtV(row2,-1)][col2].symbol==varSymbol  && board[MvtV(row2,+1)][col2].symbol==varSymbol )
          ||
        (  board[MvtV(row2,+1)][col2].symbol==varSymbol  && board[MvtV(row2,+2)][col2].symbol==varSymbol )
          ||
        (  board[MvtV(row2,-1)][col2].symbol==varSymbol  && board[MvtV(row2,-2)][col2].symbol==varSymbol )

       )
        return 1;
    else
        return 0;
}

// verifie si une cellule  match avec les cellules voisins
int isMaching(int row1, int col1)  {
   
   
    char varSymbol= board[row1][col1].symbol;

     if (varSymbol==EMPTY_CELL) return 0;

   
    if (

         // verifie si la cellule match avec la cellule à gauche et celle à droite
         (  board[row1][MvtH(col1,-1)].symbol==varSymbol  && board[row1][MvtH(col1,+1)].symbol==varSymbol )
          ||

            // verifie si la cellule match avec les deux cellules à droite ou  les deux à gauche
        (  board[row1][MvtH(col1,+1)].symbol==varSymbol  && board[row1][MvtH(col1,+2)].symbol==varSymbol )
          ||
        (  board[row1][MvtH(col1,-1)].symbol==varSymbol  && board[row1][MvtH(col1,-2)].symbol==varSymbol )

            ||

            // verifie si la cellule match avec la cellule en dessus  et celle en dessous
         (  board[MvtV(row1,-1)][col1].symbol==varSymbol  && board[MvtV(row1,+1)][col1].symbol==varSymbol )
          ||

           // verifie si la cellule match avec les deux cellules en dessus ou  les deux en dessous
        (  board[MvtV(row1,+1)][col1].symbol==varSymbol  && board[MvtV(row1,+2)][col1].symbol==varSymbol )
          ||
        (  board[MvtV(row1,-1)][col1].symbol==varSymbol  && board[MvtV(row1,-2)][col1].symbol==varSymbol )


       )
        return 1;
    else
        return 0;
}
// Effectue un mouvement en échangeant les cellules sélectionnées
void makeMove( int row1, int col1, int row2, int col2) {

 Cell temp = board[row1][col1];
 board[row1][col1]=board[row2][col2];
 board[row2][col2]=temp;

 validsSwaps++;

}

// Verifie tous les cellules de la matrice. Il met l'attribut validMatches à 1 pout chaque cellule qui contient le même symbole que deux autres cellules voisines (même ligne ou même colonne)
int markMatches() {
    int matchesFound = 0;

        // Marquer les celllules à supprimer
        for (int i = 0; i < pGridLines; i++) 
        {
            
            for (int j = 0; j < pGridColumns; j++) 
            {

                if (isMaching(i,j))  
                  { board[i][j].validMatches=1;
                     matchesFound=1;
                  }
     
            }
        }
  return matchesFound;
   
}

//  applique la fonction applyGravity pour toutes les cellules dont l'attribut validMatches == 1
// Cette attribut est mis à jour à l'aide de la fonction markMatches
void removeMatches() 
 {
  

        // Marquer les celllules à supprimer
        for (int i = 0; i < pGridLines; i++) 
        {
            
            for (int j = 0; j < pGridColumns; j++) 
            {

             
                if ( board[i][j].validMatches)  
                                         { 
                                                        // Pour chaque cellule qui sera supprimée, nous augmentons le score de 1
                                                        score++;
                                                         applyGravity(i,j); 
                                         }
                                                      
            }
        }

 

    }

// Il permet d'associer aux  lettres associé colonnes des index
// A ==>  0, B ==> 1 , C ==> 2 , ..
// Ainsi, quand l'utilisateur indique la colonne D par exemple, on doit accéder à la colonne 3 de la matrice
    int getNumCol(char  lettreCol)
    {
         int numCol ;
         lettreCol =toupper(lettreCol)-'A';
         numCol=lettreCol;
         numCol++;
         return numCol;
    }
 
 bool parse_int(char *string, int *integer)
{
 
  int i = 0;
  
  // Compter  le nombre des espaces au début 
  while (isspace(string[i])) i++;
  
  // Récupérer la longueur du texte
  int length = strlen(string);
  
  // si tout le texte ne contient que des espaces, on retourne false
  if (length == i) return false;
  
  // L'entier sdu texte sera stocké dans  integer_buffer
  char integer_buffer[BUFFER_SIZE];
  int integer_chars = 0;
  
  // si le nombre est négatif, il doit commencer par '-' 
  if (string[i] == '-')
  {
    // store the symbol into the buffer, and advance both indexes into the 
    // string and buffer
    integer_buffer[integer_chars] = '-';
    integer_chars++;
    i++;
    
    // si le texte ne contient pas des chiffres, on retourne false
    if (!isdigit(string[i])) return false;
  }
  
  //  boucle sur tous caractères du texte
  while (i < length && !isspace(string[i]))
  {
    // si nous trouvons des caractères autres que des chiffres, on retourne false
    if (!isdigit(string[i])) return false;
    
    // mettre le chiffre validée dans  integer_buffer
    integer_buffer[integer_chars] = string[i];
    integer_chars++;
    i++;
  }
  
  //mettre null à la fin de   integer_buffer, pour avoir un texte propre
  integer_buffer[integer_chars] = '\0';
  
  // Parcourir les espaces à lafin
  while (isspace(string[i])) i++;
  
  //  si on n'arrive pas à la fin du texte après les espaces, on retourne false. le texte n'est pas un entier
  if (string[i] != '\0') return false;
  
  // atoi  convertit integer_buffer à un entier 
  *integer = atoi(integer_buffer);
  
  // Si on arrive ici, cela veut dire qu'il s'agit un entier. Ainsi, on retourne true
  return true;
  

}

// Attendre retour à la ligne 
int clean_stdin()
{
    while (getchar() != '\n');
    return 1;
}

 /* 130 = é
          133 = à
          138 = è
          135 = ç
          136 = ê  */



int main() {

     
         
                                
                int row1, col1, row2, col2,  first_time_around ;
                char   letterCol1, letterCol2,charEndLine ;
                char buffer1, buffer2;
                bool parsed_correct ;



    // Nombre de ligne de la matrice

                        parsed_correct = true;
                        
                        // Demander à l'utilisateur le nombre de lignes de la matrice jusqu'à ce qu'il répond avec un entier compris entre minGridSize (8 default) et maxGridSize (26 default)
                        do
                        {
                            // Demander à l'utilisateur le nombre de lignes de la matrice
                            printf("Indiquer Nombre de lignes de la matrice : ");
                            
                            //  fget permet de récupéer  la ligne de texte saisie par l'utilisateur et la stocker au niveau de la variable buffer
                            char buffer[BUFFER_SIZE];
                            fgets(buffer, BUFFER_SIZE, stdin);
                            
                            // Valider la valeur saisie par l'utilisateur  et la stocker au niveau de pGridLines
                            // Il retourne true si la valeur est un entier et false si la valeur saisie ne correspond pas à un entier.
                            parsed_correct = parse_int(buffer, &pGridLines);
                            
                            
                            // Contrôle spécifique à nombre de ligne d'une matrice qui doit être compris entre minGridSize (8 default) et maxGridSize (26 default)
                                
                            if (parsed_correct && pGridLines >=minGridSize && pGridLines<=maxGridSize) parsed_correct= true;
                            else parsed_correct=false;

                                if (!parsed_correct)    printf("%sLe nombre de lignes doit %ctre un entier entre %d et %d%s\n",COLOR_RED,136,minGridSize,maxGridSize,COLOR_RESET);
                                
                        // Après la saisie d'un nombre entier valide, on sort de la boucle

                        } while (!parsed_correct);

                        // printf("Nombre de colonnes de la matrice : %d\n", pGridLines);
                        

    // Nombre de colonnes de la matrice

                                parsed_correct = true;
                            
                            // Demander à l'utilisateur le nombre de colonnes de la matrice jusqu'à ce qu'il répond avec un entier compris entre minGridSize (8 default) et maxGridSize (26 default)
                            do
                            {
                                // Demander à l'utilisateur le nombre de clonnes de la matrice
                                printf("Indiquer le nombre de colonnes de la matrice : ");
                                
                                //  fget per de récupéer  la ligne de texte saisie par l'utilisateur et la stocker au niveau de la variable buffer
                                char buffer[BUFFER_SIZE];
                                fgets(buffer, BUFFER_SIZE, stdin);
                                
                                // Valider la valeur saisie par l'utilisateur  et la stocke au niveau de pGridColumns
                                // Il retourne true si la valeur est un entier et false si la valeur saisie ne correspond pas à un entier.
                                parsed_correct = parse_int(buffer, &pGridColumns);
                                
                                
                                // Contrôle spécifique à nombre de ligne d'une matrice qui doit être compris entre minGridSize (8 default) et maxGridSize (26 default)
                                    
                                if (parsed_correct && pGridColumns >=minGridSize && pGridColumns<=maxGridSize) parsed_correct= true;
                                else parsed_correct=false;

                                    if (!parsed_correct)    printf("%sLe nombre de lignes doit %ctre un entier entre %d et %d%s\n",COLOR_RED,136,minGridSize,maxGridSize,COLOR_RESET);
                                    
                            // Après la saisie d'un nombre entier valide, on sort de la boucle

                            } while (!parsed_correct);

                            //   printf("Nombre de colonnes de la matrice : %d\n", pGridColumns);


// Nombre de symbole de la matrice
                    parsed_correct = true;
                    
                    // Demander à l'utilisateur le nombre de symboles à utiliser dans la matrice jusqu'à ce qu'il répond avec un entier compris entre minSymbols (4 default) et maxSymbols (6 default)
                            do
                            {
                                        // Demander à l'utilisateur le nombre de symboles de la matrice
                                        printf("Indiquer Nombre de symboles %c utiliser dans la matrice : ", 133);
                                        
                                        //  fget permet de récupérer  la ligne de texte saisie par l'utilisateur et la stocker au niveau de la variable buffer
                                        char buffer[BUFFER_SIZE];
                                        fgets(buffer, BUFFER_SIZE, stdin);
                                        
                                        // Valider la valeur saisie par l'utilisateur  et la stocker au niveau de pNumberOfSymbols
                                        // Il retourne true si la valeur est un entier et false si la valeur saisie ne correspond pas à un entier.
                                        parsed_correct = parse_int(buffer, &pNumberOfSymbols);
                                        
                                        
                                        // Contrôle spécifique à nombre de symboles qui doit être compris entre minSymbols (4 default) et maxSymbols (6 default)
                                            
                                        if   (parsed_correct && pNumberOfSymbols >=minSymbols && pNumberOfSymbols<=maxSymbols) parsed_correct= true;
                                        else parsed_correct=false;

                                        if (!parsed_correct)  printf("%sLe nombre de symbole doit %ctre un entier entre %d et %d%s\n",COLOR_RED,136,minSymbols,maxSymbols,COLOR_RESET);
                                            
                                    // Après la saisie d'un nombre entier valide, on sort de la boucle

                            } while (!parsed_correct);

                    //  printf("Nombre de symboles de la matrice : %d\n", pNumberOfSymbols);

 
// Générer la matrice

        fillBoard();

// Afficher la matrice généree
       printBoard();
         
// Marquer heure de début ddu jeu

                 time_t startTime;
                 char bufferStartTime[80];

                time(&startTime);


                struct tm *pStartTime = localtime( &startTime );
                strftime( bufferStartTime, 80, "%d/%m/%Y %H:%M:%S", pStartTime );
                

// Tanqu'il y a encore des mouvements valides possibles, ole jeux va continuer

            while (hasMatchingCells()) 
            { 
                






                        parsed_correct = true;
                        

                        // Demander à l'utilisateur le numéro de la ligne de la clulle jusqu'à ce qu'il répond avec un entier compris entre 1 et pGridLines (valeur saisie avant par l'utilisateur)
                        do
                        {
                                    // Demander à l'utilisateur le numéro de la ligne de la cellule
                                    printf("Indiquer le num%cro de la ligne de la premi%cre cellule %c changer : ",130,138,133);
                                    
                                    //  fget permet de récupérer  la ligne de texte saisie par l'utilisateur et la stocker au niveau de la variable buffer
                                    char buffer[BUFFER_SIZE];
                                    fgets(buffer, BUFFER_SIZE, stdin);
                                    
                                    // Valider la valeur saisie par l'utilisateur  et la stocker au niveau de row1
                                    // Il retourne true si la valeur est un entier et false si la valeur saisie ne correspond pas à un entier.
                                    parsed_correct = parse_int(buffer, &row1);
                                    
                                    
                                    // Contrôle spécifique au numéro de la ligne qui doit être compris entre 1 et  pGridLines
                                        
                                    if   (parsed_correct && row1 >=1 && row1<=pGridLines) parsed_correct= true;
                                    else parsed_correct=false;

                                    if (!parsed_correct)  printf("%sLe nombre de symbole doit %ctre un entier entre 1 et %d%s\n",COLOR_RED,136,pGridLines,COLOR_RESET);
                                        
                                // Après la saisie d'un nombre entier valide, on sort de la boucle

                        } while (!parsed_correct);

                        
                            // Demander à l'utilisateur le numéro de la colonne de la première cellulle jusqu'à ce qu'il répond avec une lettre valide
                     
                        first_time_around = 0;
                        
                            do
                            {  
                                
                                if (first_time_around == 0)
                                    first_time_around++;
                                else
                                    printf("%sLa colone doit %ctre indiqu%ce par une lettre de A %c %c%s\n",COLOR_RED,136,130,133, letters[pGridColumns-1],COLOR_RESET);

                                printf("Indiquer le code de la colonne de la premi%cre cellule: ",138);

                            }  while (      (   ( scanf("%c%c", &letterCol1, &charEndLine) != 2 || charEndLine != '\n' )  && clean_stdin() )
                                                || !isalpha(letterCol1) 
                                                || ( isalpha(letterCol1) && ( toupper(letterCol1) <'A'  || toupper(letterCol1) > letters[pGridColumns-1] ) )
                                            );
                        col1=getNumCol(letterCol1);
                        
                        //  printf("Numero colonne de la matrice : %c  %d\n", letterCol1,col1); 
                        
                            
                            
                        // deuxieme cellule


                        parsed_correct = true;
                        

                        // Demander à l'utilisateur le numéro de la lignes de la cellule jusqu'à ce qu'il répond avec un entier compre entre 1 et  pGridLines
                        do
                        {
                            // Demander à l'utilisateur le numéro de la ligne de la deuxième celle
                        
                            printf("Indiquer le num%cro de la ligne de la deuxi%cme cellule %c changer : ",130,138,133);
                            
                            //  fget permet de récupérer  la ligne de texte saisie par l'utilisateur et la stocker au niveau de la variable buffer
                            char buffer[BUFFER_SIZE];
                            fgets(buffer, BUFFER_SIZE, stdin);
                            
                            // Valider la valeur saisie par l'utilisateur  et la stocker au niveau de row2
                            // Il retourne true si la valeur est un entier et false si la valeur saisie ne correspond pas à un entier.
                            parsed_correct = parse_int(buffer, &row2);
                            
                            
                            // Contrôle spécifique à nombre de lsymboles qui doit être compris entre minSymbols (4 default) et maxSymbols (6 default)
                                
                            if   (parsed_correct && row2 >=1 && row2<=pGridLines) parsed_correct= true;
                            else parsed_correct=false;

                            if (!parsed_correct)  printf("%sLe num%cro de la lignee doit %ctre un entier entre 1 et %d%s\n",COLOR_RED,130,136,pGridLines,COLOR_RESET);
                                
                        // Après la saisie d'un nombre entier valide, on sort de la boucle

                        } while (!parsed_correct);

                        //  printf("Numero lige de la matrice : %d\n", row2);

                        

                                // Demander à l'utilisateur le numéro de la colonne de la deuxième cellule jusqu'à ce qu'il répond avec une lettre valide
                        first_time_around = 0;
                        
                            do
                            {  
                                
                                if (first_time_around == 0)
                                    first_time_around++;
                                else
                                    printf("%sLa colone doit %ctre indiqu%ce par une lettre de A %c %c%s\n",COLOR_RED,136,130,133, letters[pGridColumns-1],COLOR_RESET);

                                printf("Indiquer le code de la colonne de la deuxi%cme cellule %c changer : ",138,133);

                            }  while (      (   ( scanf("%c%c", &letterCol2, &charEndLine) != 2 || charEndLine != '\n' )  && clean_stdin() )
                                                || !isalpha(letterCol2) 
                                                || ( isalpha(letterCol2) && ( toupper(letterCol2) <'A'  || toupper(letterCol2) > letters[pGridColumns-1] ) )
                                            );
                        col2=getNumCol(letterCol2);
                        
                        //  printf("Numero colonne de la matrice : %c  %d\n", letterCol2,col2); 
                        



                                    //   Verifier si le mouvement est valide      
                                if (isValidMove(row1 - 1, col1 - 1, row2 - 1, col2 - 1))
                                {    

                                    //   effectuer le mouvement demandée par l'utlisateur             
                                    makeMove( row1 - 1, col1 - 1, row2 - 1, col2 - 1);

                                    // la matrice avec suppression est affichée juste pour contrôler la matrice après suppression qui sera affichée par la suite
                                     printf("Matrice avec mouvement et avant suppression\n");
                                    printBoard();

                                    // markMatches marque toutes les cellules qui seront supprimées  suite au dernier mouvemen 

                                    while   (markMatches())  { 
                                        
                                        // suppression et application de la gravité pour les cellules marqué par markMatches
                                             removeMatches(); 
                                              }

                                    printf("Matrice apr%cs suppresion\n",138);                     
                                    printBoard();   

                                    printf("Score : %d en %d Mouvements\n", score,validsSwaps);                           

                                }
                                else {
                                            printf("%s ", COLOR_RED);
                                            printf("Mouvement invalide. Veuillez r%cessayer.\n",130);
                                            printf("%s ", COLOR_RESET);
                                    }
                        
            }

  
  
     time_t endTime; 
     char bufferEndTime[80];

     time(&endTime);

    struct tm *pEndTime = localtime( &endTime );
    strftime( bufferEndTime, 80, "%d/%m/%Y %H:%M:%S", pEndTime );
 
    printf("%sJeu termin%c. Aucun mouvement possible. R%cultat : %s\n",COLOR_BLUE,130,130,COLOR_RESET);
    printf("%s---------------------------------------------------%s\n",COLOR_BLUE, COLOR_RESET);
    printf("%sScore finale : %d en %d Mouvements%s\n",COLOR_BLUE, score,validsSwaps,COLOR_RESET);    
     //  Affiche heure début et heure fin de la partie
    printf( "%sHeure de d%cbut : %s%s\n",COLOR_BLUE,130, bufferStartTime,COLOR_RESET );
    printf( "%sHeure de fin : %s%s\n",COLOR_BLUE, bufferEndTime,COLOR_RESET );

     // Caclule la durée de la partie
    int  seconds=difftime(endTime,startTime);
    printf("%sTemps en secondes  : %d%s\n",COLOR_BLUE,seconds,COLOR_RESET);
     printf("%s---------------------------------------------------%s\n",COLOR_BLUE, COLOR_RESET);

   

    return 0;
}
 