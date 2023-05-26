//grid verifying pour qu'il n y ait pas 3 matching cells au départ

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>

#define maxGridSize 26
#define EMPTY_CELL ' '

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



void fillBoard() 
{
   
    for (int i = 0; i < pGridLines; i++) {
        for (int j = 0; j < pGridColumns; j++) 
        {
          
            int index = rand() % pNumberOfSymbols;

                board[i][j].symbol = symbols[index];
                board[i][j].color = index;
                board[i][j].validMatches = 0;

            // verifier à gauche
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
            // verifier en dessus
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


int MvtH(int varIndex, int varNumber)
{

   int result =  (varIndex + varNumber )% pGridColumns;
   if (result<0) result=pGridColumns+result;
   return result;


}


int MvtV(int varIndex, int varNumber)
{

   int result =  (varIndex + varNumber )% pGridLines;
   if (result<0) result=pGridLines+result;
   return result;


}





// Fonction d'affichage du plateau
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

void printBoardWithMaches()
{
    
    printf("   ");
    for (int i = 0; i < pGridLines; i++)
        printf("%d ", i + 1);
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
              
            printf("%s%d%s ", colorCode, board[i][j].validMatches  , COLOR_RESET);
        }
        printf("\n");
    }
}

   




 
//gravity

 void applyGravity(int i, int j )

  {

                board[i][j].symbol= EMPTY_CELL;
                board[i][j].color= 10;
                board[i][j].validMatches= 0;

                score++;

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
  
 

// Vérifie si le plateau contient un groupe d'au moins trois éléments identiques
int hasMatchingCells() {
    // Vérification des lignes
    for (int i = 0; i < pGridLines; i++) {
        int count = 1;
        for (int j = 0; j < pGridColumns; j++) {
            if (board[i][j].symbol != EMPTY_CELL && board[i][j].symbol == board[i][MvtH(j,+1)].symbol)
               count++;
            else
                count = 1;

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

         (  board[row2][MvtH(col2,-1)].symbol==varSymbol  && board[row2][MvtH(col2,+1)].symbol==varSymbol )
          ||
        (  board[row2][MvtH(col2,+1)].symbol==varSymbol  && board[row2][MvtH(col2,+2)].symbol==varSymbol )
          ||
        (  board[row2][MvtH(col2,-1)].symbol==varSymbol  && board[row2][MvtH(col2,-2)].symbol==varSymbol )

          ||

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


int isMaching(int row1, int col1)  {
   
    // Horizontal
    char varSymbol= board[row1][col1].symbol;

     if (varSymbol==EMPTY_CELL) return 0;

    if (
         (  board[row1][MvtH(col1,-1)].symbol==varSymbol  && board[row1][MvtH(col1,+1)].symbol==varSymbol )
          ||
        (  board[row1][MvtH(col1,+1)].symbol==varSymbol  && board[row1][MvtH(col1,+2)].symbol==varSymbol )
          ||
        (  board[row1][MvtH(col1,-1)].symbol==varSymbol  && board[row1][MvtH(col1,-2)].symbol==varSymbol )

            ||

         (  board[MvtV(row1,-1)][col1].symbol==varSymbol  && board[MvtV(row1,+1)][col1].symbol==varSymbol )
          ||
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

// Supprime les groupes d'éléments identiques du plateau
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

void removeMatches() 
 {
  

        // Marquer les celllules à supprimer
        for (int i = 0; i < pGridLines; i++) 
        {
            
            for (int j = 0; j < pGridColumns; j++) 
            {

             
                if ( board[i][j].validMatches)     applyGravity(i,j); 
                                                      
            }
        }

 

    }

    int getNumCol(char  lettreCol)
    {
         int numCol ;
         lettreCol =toupper(lettreCol)-'A';
         numCol=lettreCol;
         numCol++;
         return numCol;
    }
 

int main() {

      /* 130 = é
          133 = à
          138 = è
          135 = ç
          136 = ê  */


         
    time_t startTime;
    char bufferStartTime[80];

    time(&startTime);

    struct tm *pStartTime = localtime( &startTime );
    strftime( bufferStartTime, 80, "%d/%m/%Y %H:%M:%S", pStartTime );
    printf( "Heure de d%cbut : %s\n",130, bufferStartTime );

  //  printf("\nThis program has been writeen at (date and time): %s", ctime(&startTime));

   


    
    int row1, col1, row2, col2;
    char   letterCol1, letterCol2;
   
          int  attenteValeurs =1;

         printf("Indiquer Nombre de lignes et colonnes de la matrice (Exemple : 10 8) : ");
         while (attenteValeurs)
            {
                
                scanf("%d %d", &pGridLines, &pGridColumns);
                if( pGridLines>=8 && pGridLines<=26 && pGridColumns>=8 && pGridColumns<=26  )
                            attenteValeurs=0;
                else {      
                            printf("%s", COLOR_RED);
                            printf("le nombre de lignes doit %ctre entre 8 et 26\n",136);
                            printf("le nombre de colonnes doit %ctre %cgalement 8 et 26\n",136,130);
                              printf("%s ", COLOR_RESET);
                            printf("Merci d'indiquer le nombre de lignes et colonnes de la matrice (Exemple : 8 8) : ");
                   }

            }

            attenteValeurs =1;

            printf("Indiquer le nombre de symboles (4 %c 6) : ",133);
            while (attenteValeurs)
                {

                   
                    scanf("%d", &pNumberOfSymbols);

                    if( pNumberOfSymbols>=4 && pNumberOfSymbols<=6   )
                                attenteValeurs=0;
                    else {     
                                 printf("%s", COLOR_RED);
                                printf("Le nombre de symboles doit %ctre entre 4 et 6\n",136);
                                 printf("%s ", COLOR_RESET);
                                printf("Merci d'indiquer le nombre de symboles (4 %c 6) : ",133);
                            }
                }

        fillBoard();
    
         printBoard();
         

    while (hasMatchingCells()) 
     { 
        
         attenteValeurs =1;

          printf("S%clectionnez une cellule %c changer (ligne colonne) : ",130,133);
         while (attenteValeurs)
            {

               
                scanf("%d %c", &row1, &letterCol1);
                col1=getNumCol(letterCol1);
                        if( row1>=1 &&  row1 <= pGridLines  && col1>= 1 &&  col1 <= pGridColumns  )
                                attenteValeurs=0;
                         else {
                                 printf("%s", COLOR_RED);
                                printf("Le num%cro de la ligne doit %ctre un nombre entre 1 et %d\n",130,136, pGridLines);
                                printf("La colone doit %ctre indiqu%ce par une lettre de A %c %C\n",136,130,133, 'A' + pGridColumns-1);
                                   printf("%s", COLOR_RESET);
                                printf("Merci d'indiquer une cellule %c changer (ligne colonne) : " ,133);
                            }


              
            }



         attenteValeurs =1;
  
         printf("S%clectionnez une autre cellule %c changer (ligne colonne) : ",130,133);
            {

               
               scanf("%d %c", &row2, &letterCol2);
               col2=getNumCol(letterCol2);
                        if( row2>=1 &&  row2 <= pGridLines  && col2>= 1 &&  col2 <= pGridColumns  )
                                attenteValeurs=0;
                         else {
                                printf("%s ", COLOR_RED);
                                printf("Le num%cro de la ligne doit %ctre un nombre entre 1 et %d\n",130,136, pGridLines);
                                printf("La colone doit %ctre indiqu%ce par une lettre de A %c %C\n",136,130,133, 'A' + pGridColumns-1);
                                printf("%s ", COLOR_RESET);
                                printf("Merci d'indiquer une cellule %c changer (ligne colonne) : " ,133);
                            }
     
            }

        
        
       
      



        if (isValidMove(row1 - 1, col1 - 1, row2 - 1, col2 - 1))
         {                
              makeMove( row1 - 1, col1 - 1, row2 - 1, col2 - 1);
               
              printf("Matrice avec mouvement et avant suppression\n");
              printBoard();
                
               while   (markMatches())  {   removeMatches();  }

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
    printf( "Heure de fin : %s\n",130, bufferEndTime );

    int  seconds=difftime(endTime,startTime);
  printf("Temps en secondes  : %d\n",seconds);
    

    printf("Jeu termin%c. Aucun mouvement possible.\n",130);

    return 0;
}
 