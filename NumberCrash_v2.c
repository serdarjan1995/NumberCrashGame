#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100

void generateNew(int (*)[],int,int);  /// fill empty blocks with random numbers
void pullDown(int (*)[],int,int); /// pull non empty blocks down
void checkForCrash(int (*)[],int ,int ,int ,int *,int, int , int , int);  /// check 4-connectivity for crashing items
int traverseMatrix(int (*)[],int ,int ,int *);  /// traverse matrix items
void exchange(int (*)[],int , int ,int ,int ,int ,int ); /// exchange 2 items
void matrixShow(int (*)[],int , int , int);  /// display matrix

void main()
{
    system("COLOR F0");
    srand(time(NULL));
    int N;
    int M;
    int i;
    int j;
    int crashed=0;
    int moved=0;
    int lives=1;
    int table[SIZE][SIZE];
    int score,row_1,column_1,row_2,column_2;
    char again,quit;
    srand(time(NULL));


        /*Entering the size of matrix*/
        printf("Enter the size of table ( N*M, N>5, M>5 )");
        printf("\n\tN: ");
        scanf("%d",&N);
        while(N<4 || N>SIZE){
            printf("\n**Please check your input and enter again**\n\tN: ");
            scanf("%d",&N);
        }
        printf("\tM: ");
        scanf("%d",&M);
        while(M<4 || M>SIZE){
            printf("\n**Please check your input and enter again**\n\tM: ");
            scanf("%d",&M);
        }
//        N=6;
//        M=5;
        printf("\n\tNumber Crash\n");
    do{
/** Initializing board **/
    /*setting random numbers on the board*/
    for(i=0;i<N;i++){
        for(j=0;j<M;j++){
            table[i][j]=rand()%10;
        }
    }
//    table[0][0] = 5;
//    table[0][1] = 5;
//    table[1][0] = 5;
//    table[1][1] = 5;
//        table[2][2] = 2;
//        table[3][2] = 2;
//        table[3][3] = 2;
//        table[3][4] = 2;
//        table[4][3] = 2;
/** GAME BEGINS HERE! **/
    moved = 0;
    while(lives>0){
        matrixShow(table,N,M,0);
        crashed = traverseMatrix(table,N,M,&score);
        if(moved && !crashed){
            printf("\nOoops! No crashed, live -1\n");
            lives--;
            //printf("\nLives: %d\n",lives);
        }
        if(!crashed){
            printf("\nLives: %d\n",lives);
            printf("\nChange: ");
            scanf("%d %d %d %d",&row_1,&column_1,&row_2,&column_2);
            exchange(table,N,M,row_1,column_1,row_2,column_2);
            moved=1;
        }
    } /*While looping ends here*/
    printf("Your Score: %d",score);
    lives=3;
    score=0;
    printf("\nWant to play again? (y/n) ");
    scanf(" %c",&again);
    }while(again=='y' || again=='Y');
    printf("Game terminated");
    system("pause");
}

/**
function of displaying the board.
@param N                    row size of matrix
@param M                    column size of matrix
@param doDelay              1 - delay for a bit, then continue, 0 - user should press key to continue
@param table[SIZE][SIZE]    board with numbers
*/
void matrixShow(int table[SIZE][SIZE],int N, int M, int doDelay){
    int i,j;
    /*printing column indexes of matrix (x-axis) to make easy understand which number we have chosen*/
    printf("\n\t   ");
    for(i=0;i<M;i++){
        printf("%2d",i);
    }
    printf("\n\t   ");
    for(i=0;i<M;i++){
        printf("--");
    }
    printf("\n"); /*columns finished*/
    for(i=0;i<N;i++){
        printf("\t%2d|",i);/* printing row indexes */
        for(j=0;j<M;j++){/*start to printing matrix's elements*/
            if(table[i][j]>=0){
//                switch(table[i][j]){
//                    case 0:  printf("\033[1;30m %2d",table[i][j]); break;
//                    case 1:  printf("\033[1;31m %2d",table[i][j]); break;
//                    case 2:  printf("\033[1;32m %2d",table[i][j]); break;
//                    case 3:  printf("\033[1;33m %2d",table[i][j]); break;
//                    case 4:  printf("\033[1;34m %2d",table[i][j]); break;
//                    case 5:  printf("\033[1;35m %2d",table[i][j]); break;
//                    case 6:  printf("\033[1;36m %2d",table[i][j]); break;
//                    case 7:  printf("\033[1;37m %2d",table[i][j]); break;
//                    case 8:  printf("\033[1;38m %2d",table[i][j]); break;
//                    case 9:  printf("\033[1;39m %2d",table[i][j]); break;
//                }
                printf("%2d",table[i][j]);
            }
            else{
                printf("%2c",table[i][j]);
            }
        }
    printf("\n");
    }
    printf("\n");
    if(doDelay){
        for (i = 0; i <= 32767; i++)
            for (j = 0; j <= 12767; j++)
                {}
    }
    else{
        system("pause");
    }
}


/**
function of exchanging two values of matrix.
@param N                    row size of matrix
@param M                    column size of matrix
@param table[SIZE][SIZE]    board with numbers
*/
void exchange(int table[SIZE][SIZE],int N, int M,int row_1,int column_1,int row_2,int column_2){
int temp;
if((row_1<0 || row_1>=N) || (row_2<0 || row_2>=N)){
    printf("\n Out of bounds \n"); return;
}

if((column_1<0 || column_1>=M) || (column_2<0 || column_2>=M)){
    printf("\n Out of bounds \n"); return;
}

temp=table[row_1][column_1];
table[row_1][column_1]=table[row_2][column_2];
table[row_2][column_2]=temp;

}


/**
****** Traverse matrix or crashing items ******
@param n                row size of matrix
@param m                column size of matrix
@param *score           game score
@param table[SIZE][SIZE]  board with numbers
______________________________________________________
*/
int traverseMatrix(int table[SIZE][SIZE],int n,int m,int *score){
    int i,j,temp,crashed=0,length;
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            length = 0;
            if(table[i][j]>=0){
                checkForCrash(table,n,m,table[i][j],&length,-1,-1,i,j);
                //printf("\n \t length: %d",length);
            }
            if(length){
                //matrixShow(table,n,m,1);
                crashed+=length;
                printf("\n \t crashed items: %d\t\t",crashed);
                system("pause");
            }
        }
    }
    if(crashed){
        *score = (*score) + (crashed*crashed);
        printf("\n \t Your Score: %d\t\t",*score);
        pullDown(table,n,m);
        matrixShow(table,n,m,0);
        generateNew(table,n,m);
        matrixShow(table,n,m,0);
    }
    return crashed;
}

/**
****** Crash items if possible ******
@param n                    row size of matrix
@param m                    column size of matrix
@param object               check neighbors for this item
@param *length              crashed item count
@param loc_x_prev           previous item location row
@param loc_y_prev           previous item location column
@param loc_x                current item location row
@param loc_y                current item location column
@param table[SIZE][SIZE]    board with numbers
______________________________________________________
!!!!!!! In the function used pullDown function;!!!!!!!
*/
void checkForCrash(int table[SIZE][SIZE],int n,int m, int object,int *length,
                  int loc_x_prev, int loc_y_prev,int loc_x, int loc_y){
    int selfCrash = 0;
    if((loc_x<0 || loc_x>=n) || (loc_y<0 || loc_y>=m) || (table[loc_x][loc_y]!=object) ){
        //printf(" loc %d %d returning 0",loc_x,loc_y);
        return ;
    }
    else{
        //printf("\n\tchecking [%d, %d]",loc_x,loc_y);
        if( table[loc_x][loc_y] != -1 && (loc_y_prev != loc_y+1) && loc_y+1 != m  && (table[loc_x][loc_y+1]==object) ){
            table[loc_x][loc_y] = -1;
            (*length)++;
            selfCrash = 1;
            printf("\t\t[%d, %d] %d crashed, going right",loc_x,loc_y,object);
            matrixShow(table,n,m,1);
            checkForCrash(table,n,m,object,length,loc_x,loc_y,loc_x,loc_y+1);
        }
        if( table[loc_x][loc_y] != -1 && (loc_y_prev != loc_y-1) && loc_y-1 != -1 && (table[loc_x][loc_y-1]==object) ){
            table[loc_x][loc_y] = -1;
            (*length)++;
            selfCrash = 1;
            printf("\t\t[%d, %d] %d crashed, going left",loc_x,loc_y,object);
            matrixShow(table,n,m,1);
            checkForCrash(table,n,m,object,length,loc_x,loc_y,loc_x,loc_y-1);
        }
        if( table[loc_x][loc_y] != -1 && (loc_x_prev != loc_x-1) && loc_x-1 != -1 &&(table[loc_x-1][loc_y]==object)){
            table[loc_x][loc_y] = -1;
            (*length)++;
            selfCrash = 1;
            printf("\t\t[%d, %d] %d crashed, going up",loc_x,loc_y,object);
            matrixShow(table,n,m,1);
            checkForCrash(table,n,m,object,length,loc_x,loc_y,loc_x-1,loc_y);
        }
        if( table[loc_x][loc_y] != -1 && (loc_x_prev != loc_x+1) && loc_x+1 != n && (table[loc_x+1][loc_y]==object)){
            table[loc_x][loc_y] = -1;
            (*length)++;
            printf("\t\t[%d, %d] %d crashed, going down",loc_x,loc_y,object);
            matrixShow(table,n,m,1);
            selfCrash = 1;
            checkForCrash(table,n,m,object,length,loc_x,loc_y,loc_x+1,loc_y);
        }
        if(table[loc_x][loc_y] != -1 && table[loc_x][loc_y]==object && *length!=0){
            table[loc_x][loc_y] = -1;
            printf("\t[%d, %d] crashed",loc_x,loc_y);
            matrixShow(table,n,m,1);
            (*length)++;
        }
        if(selfCrash){
            checkForCrash(table,n,m,object,length,loc_x,loc_y,loc_x,loc_y-1);
            checkForCrash(table,n,m,object,length,loc_x,loc_y,loc_x-1,loc_y);
            checkForCrash(table,n,m,object,length,loc_x,loc_y,loc_x+1,loc_y);
        }
    }
}


/**
function of pulling numbers down after detecting empty cells below.
@param n                row size of matrix
@param m                column size of matrix
@param table[100][100]  board with numbers
*/
void pullDown(int table[SIZE][SIZE],int n,int m){
    int i,j,k,temp;
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            if (table[i][j]==-1 && i>0){ /*if there are any empty cells, push them up.*/
                for(k=i;k>0;k--){
                       temp=table[k][j];
                       table[k][j]=table[k-1][j];
                       table[k-1][j]=temp;
                }
            }
        }
    }
}

/**
Generates numbers on empty cells;
@param n                row size of matrix
@param m                column size of matrix
@param table[100][100]  board with numbers
*/
void generateNew(int table[SIZE][SIZE],int n,int m){
    int i,j,k,temp;
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            if(table[i][j]==-1){
                table[i][j]=rand()%10;
            }
        }
    }
}
