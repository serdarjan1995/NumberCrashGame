/**
@file
BBG2 2014-2015 spring semester, semester project.
NumberCrash game.
@author
Name: Sardor Hazratov
Student no: 14011901
Date: 08/06/2015
E-Mail: serdarjan1995@gmail.com
Compiler used: GCC
IDE: CodeBlocks
Operating System Windows 8.1
*/

#include <stdio.h>
#include <stdlib.h>

/**
function of pulling numbers down after detecting any structure ( recursive ).
Generates numbers on empty cells;
@param n                size of matrix
@param numbers          range of numbers (2<x<10)
@param table[100][100]  board with numbers
*/
void pullDown(int table[100][100],int n,int numbers){
int i,j,k,temp;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(table[i][j]==0 && i==0){ /*if there are any empty cell on the first row, fill it with new random number*/
                table[i][j]=rand()%(numbers-1)+2;
            }
            else if (table[i][j]==0 && i>0){ /*if there are any empty cells, push them up.*/
                for(k=i;k>0;k--){
                       temp=table[k][j];
                       table[k][j]=table[k-1][j];
                       table[k-1][j]=temp;
                }
                pullDown(table,n,numbers); /*After pushing the empty cell, start function again with changed matrix*/
        }
    }

}
}

/**
function of exchanging position of two numbers.
@param row              row where exchanging number is plant (y-axis).
@param column           column where exchanging number is plant (x-axis).
@param direction        direction of exchanging. (8-up; 6-right; 4-left; 2-down;)
@param table[100][100]  board with numbers
*/
void exchange(int table[100][100],int row,int column,int direction){
int temp;
switch(direction){
case 8/*up*/    : temp=table[row][column];
                  table[row][column]=table[row-1][column];
                  table[row-1][column]=temp; break;
case 6/*right*/:  temp=table[row][column];
                  table[row][column]=table[row][column+1];
                  table[row][column+1]=temp; break;
case 2/*down*/:   temp=table[row][column];
                  table[row][column]=table[row+1][column];
                  table[row+1][column]=temp; break;
case 4/*left*/:   temp=table[row][column];
                  table[row][column]=table[row][column-1];
                  table[row][column-1]=temp; break;
}
}
/**
function of displaying the board.
@param N                size of matrix
@param table[100][100]  board with numbers
*/
void matrixShow(int table[100][100],int N){
    int i,j;
    /*printing column indexes of matrix (x-axis) to make easy understand which number we have chosen*/
    printf("\n   ");
    for(i=0;i<N;i++){
        printf("%2d",i);
    }
    printf("\n  ");
    for(i=0;i<N;i++){
        printf("--");
    }
    printf("\n"); /*columns finished*/
    for(i=0;i<N;i++){
        printf("%2d|",i);/* printing row indexes */
        for(j=0;j<N;j++){/*start to printing matrix's elements*/
            if(table[i][j]){
                printf("%2d",table[i][j]);
            }
            else{
                printf("%2c",table[i][j]);
            }
        }
    printf("\n");
}
printf("\n");
}

/**
****** STRUCTURE I ******
@param n                size of matrix
@param *score           game score
@param numbers          range of numbers (2<x<10)  (required by pullDown function)
@param table[100][100]  board with numbers
______________________________________________________
!!!!!!! In the function used pullDown function;!!!!!!!
*/
int strI(int table[100][100],int n,int *score,int numbers){
    int i,j,temp,found=0;
    for(i=0;i<n-2;i++){
        for(j=0;j<n-2;j++){
            if(table[i][j]==table[i+1][j] && table[i][j]==table[i+2][j]){
                found++;
                temp=table[i][j]+table[i+1][j]+table[i+2][j];
                *score+=temp;
                table[i][j]=NULL;
                table[i+1][j]=NULL;
                table[i+2][j]=NULL;
                matrixShow(table,n);
                pullDown(table,n,numbers); /*send the condition to pullDown function*/
                printf("\nYou hit I structure +%d points.\nscore: %d\n",temp,*score);
                matrixShow(table,n);
            }

        }
    }
    return found;
}

/**
****** STRUCTURE T ******
@param n                size of matrix
@param *score           game score
@param numbers          range of numbers (2<x<10)  (required by pullDown function)
@param table[100][100]  board with numbers
______________________________________________________
!!!!!!! In the function used pullDown function;!!!!!!!
*/
int strT(int table[100][100],int n,int *score,int numbers){
    int i,j,temp,found=0;
    for(i=0;i<n-2;i++){
        for(j=0;j<n-2;j++){
            if(table[i][j]==table[i][j+1] && table[i][j]==table[i][j+2] && table[i][j]==table[i+1][j+1] && table[i][j]==table[i+2][j+1]){
                found++;
                temp=table[i][j]+table[i][j+1]+table[i][j+2]+table[i+1][j+1]+table[i+2][j+1];
                *score+=temp;
                table[i][j]=NULL;
                table[i][j+1]=NULL;
                table[i][j+2]=NULL;
                table[i+1][j+1]=NULL;
                table[i+2][j+1]=NULL;
                matrixShow(table,n);
                pullDown(table,n,numbers);/*send the condition to pullDown function*/
                printf("\nYou hit T structure +%d points.\nscore: %d\n",temp,*score);
                matrixShow(table,n);
            }

        }
    }
    return found;
}

/**
****** STRUCTURE L ******
@param n                size of matrix
@param *score           game score
@param numbers          range of numbers (2<x<10)  (required by pullDown function)
@param table[100][100]  board with numbers
______________________________________________________
!!!!!!! In the function used pullDown function;!!!!!!!
*/
int strL(int table[100][100],int n,int *score,int numbers){
    int i,j,temp,found=0;
    for(i=0;i<n-2;i++){
        for(j=0;j<n-2;j++){
            if(table[i][j]==table[i+1][j] && table[i][j]==table[i+2][j] && table[i][j]==table[i+2][j+1] && table[i][j]==table[i+2][j+2]){
                found++;
                temp=table[i][j]+table[i+1][j]+table[i+2][j]+table[i+2][j+1]+table[i+2][j+2];
                *score+=temp;
                table[i][j]=NULL;
                table[i+1][j]=NULL;
                table[i+2][j]=NULL;
                table[i+2][j+1]=NULL;
                table[i+2][j+2]=NULL;
                matrixShow(table,n);
                pullDown(table,n,numbers);/*send the condition to pullDown function*/
                printf("\nYou hit L structure +%d points.\nscore: %d\n",temp,*score);
                matrixShow(table,n);
            }

        }
    }
    return found;
}

/**
****** STRUCTURE C ******
@param n                size of matrix
@param *score           game score
@param numbers          range of numbers (2<x<10)  (required by pullDown function)
@param table[100][100]  board with numbers
______________________________________________________
!!!!!!! In the function used pullDown function;!!!!!!!
*/
int strC(int table[100][100],int n,int *score,int numbers){
    int i,j,temp,found=0;
    for(i=0;i<n-2;i++){
        for(j=0;j<n-2;j++){
            if(table[i][j]==table[i+1][j] && table[i][j]==table[i+2][j] && table[i][j]==table[i+2][j+1]
                && table[i][j]==table[i+2][j+2] && table[i][j]==table[i][j+1] && table[i][j]==table[i][j+2]){
                found++;
                temp=table[i][j]+table[i+1][j]+table[i+2][j]+table[i+2][j+1]+table[i+2][j+2]+table[i][j+1]+table[i][j+2];
                *score+=temp;
                table[i][j]=NULL;
                table[i+1][j]=NULL;
                table[i+2][j]=NULL;
                table[i+2][j+1]=NULL;
                table[i+2][j+2]=NULL;
                table[i][j+1]=NULL;
                table[i][j+2]=NULL;
                matrixShow(table,n);
                pullDown(table,n,numbers);/*send the condition to pullDown function*/
                printf("\nYou hit C structure +%d points.\nscore: %d\n",temp,*score);
                matrixShow(table,n);
            }

        }
    }
    return found;
}

/**
****** STRUCTURE U ******
@param n                size of matrix
@param *score           game score
@param numbers          range of numbers (2<x<10)  (required by pullDown function)
@param table[100][100]  board with numbers
______________________________________________________
!!!!!!! In the function used pullDown function;!!!!!!!
*/
int strU(int table[100][100],int n,int *score,int numbers){
    int i,j,temp,found=0;
    for(i=0;i<n-2;i++){
        for(j=0;j<n-2;j++){
            if(table[i][j]==table[i+1][j] && table[i][j]==table[i+2][j] && table[i][j]==table[i+2][j+1]
                && table[i][j]==table[i+2][j+2] && table[i][j]==table[i+1][j+2] && table[i][j]==table[i][j+2]){
                found++;
                temp=table[i][j]+table[i+1][j]+table[i+2][j]+table[i+2][j+1]+table[i+2][j+2]+table[i+1][j+2]+table[i][j+2];
                *score+=temp;
                table[i][j]=NULL;
                table[i+1][j]=NULL;
                table[i+2][j]=NULL;
                table[i+2][j+1]=NULL;
                table[i+2][j+2]=NULL;
                table[i+1][j+2]=NULL;
                table[i][j+2]=NULL;
                matrixShow(table,n);
                pullDown(table,n,numbers);/*send the condition to pullDown function*/
                printf("\nYou hit U structure +%d points.\nscore: %d\n",temp,*score);
                matrixShow(table,n);
            }

        }
    }
    return found;
}

/**
****** STRUCTURE O ******
@param n                size of matrix
@param *score           game score
@param numbers          range of numbers (2<x<10)  (required by pullDown function)
@param table[100][100]  board with numbers
______________________________________________________
!!!!!!! In the function used pullDown function;!!!!!!!
*/
int strO(int table[100][100],int n,int *score,int numbers){
    int i,j,temp,found=0;
    for(i=0;i<n-2;i++){
        for(j=0;j<n-2;j++){
            if(table[i][j]==table[i+1][j] && table[i][j]==table[i+2][j] && table[i][j]==table[i+2][j+1]
                && table[i][j]==table[i+2][j+2] && table[i][j]==table[i][j+1] && table[i][j]==table[i][j+2]
                && table[i][j]==table[i+1][j+2]){
                found++;
                temp=table[i][j]+table[i+1][j]+table[i+2][j]+table[i+2][j+1]+table[i+2][j+2]+table[i][j+1]+table[i][j+2]+table[i+1][j+2];
                *score+=temp;
                table[i][j]=NULL;
                table[i+1][j]=NULL;
                table[i+2][j]=NULL;
                table[i+2][j+1]=NULL;
                table[i+2][j+2]=NULL;
                table[i][j+1]=NULL;
                table[i][j+2]=NULL;
                table[i+1][j+2]=NULL;
                matrixShow(table,n);
                pullDown(table,n,numbers);/*send the condition to pullDown function*/
                printf("\nYou hit O structure +%d points.\nscore: %d\n",temp,*score);
                matrixShow(table,n);
            }

        }
    }
    return found;
}

/**
****** STRUCTURE E ******
@param n                size of matrix
@param *score           game score
@param numbers          range of numbers (2<x<10)  (required by pullDown function)
@param table[100][100]  board with numbers
______________________________________________________
!!!!!!! In the function used pullDown function;!!!!!!!
*/
int strE(int table[100][100],int n,int *score,int numbers){
    int i,j,temp,found=0;
    for(i=0;i<n-2;i++){
        for(j=0;j<n-2;j++){
            if(table[i][j]==table[i+1][j] && table[i][j]==table[i+2][j] && table[i][j]==table[i+2][j+1]
                && table[i][j]==table[i+2][j+2] && table[i][j]==table[i][j+1] && table[i][j]==table[i][j+2]
                && table[i][j]==table[i+1][j+1]){
                found++;
                temp=table[i][j]+table[i+1][j]+table[i+2][j]+table[i+2][j+1]+table[i+2][j+2]+table[i][j+1]+table[i][j+2]+table[i+1][j+1];
                *score+=temp;
                table[i][j]=NULL;
                table[i+1][j]=NULL;
                table[i+2][j]=NULL;
                table[i+2][j+1]=NULL;
                table[i+2][j+2]=NULL;
                table[i][j+1]=NULL;
                table[i][j+2]=NULL;
                table[i+1][j+1]=NULL;
                matrixShow(table,n);
                pullDown(table,n,numbers);/*send the condition to pullDown function*/
                printf("\nYou hit E structure +%d points.\nscore: %d\n",temp,*score);
                matrixShow(table,n);
            }

        }
    }
    return found;
}

/**
****** STRUCTURE F ******
@param n                size of matrix
@param *score           game score
@param numbers          range of numbers (2<x<10)  (required by pullDown function)
@param table[100][100]  board with numbers
______________________________________________________
!!!!!!! In the function used pullDown function;!!!!!!!
*/
int strF(int table[100][100],int n,int *score,int numbers){
    int i,j,temp,found=0;
    for(i=0;i<n-2;i++){
        for(j=0;j<n-2;j++){
            if(table[i][j]==table[i+1][j] && table[i][j]==table[i+2][j] && table[i][j]==table[i][j+1] && table[i][j]==table[i][j+2] && table[i][j]==table[i+1][j+1]){
                found++;
                temp=table[i][j]+table[i+1][j]+table[i+2][j]+table[i][j+1]+table[i][j+2]+table[i+1][j+1];
                *score+=temp;
                table[i][j]=NULL;
                table[i+1][j]=NULL;
                table[i+2][j]=NULL;
                table[i][j+1]=NULL;
                table[i][j+2]=NULL;
                table[i+1][j+1]=NULL;
                matrixShow(table,n);
                pullDown(table,n,numbers);/*send the condition to pullDown function*/
                printf("\nYou hit F structure +%d points.\nscore: %d\n",temp,*score);
                matrixShow(table,n);
            }

        }
    }
    return found;
}

/**
Main function. Reads parameters and controls the game.
*/

int main(){
    int table[100][100],activeStructs[8];
    int k=3,control=0,lastControl=0,newControl=1;
    int i=0,j,N,numbers,score,row,column,direction,highScore=0;
    char again,quit,highScoreName[20],structs[8],defaultStructs[8]={'O','E','U','C','F','L','T','I','\0'};
    srand(time(NULL));
    do{
        for(i=0;i<9;i++){ /*Resetting matrix*/
            activeStructs[i]=0;
        }
        /*Entering the size of matrix*/
        printf("Enter the size of table ( N*N, N>5 ) N: ");
        scanf("%d",&N);
        while(N<6 || N>100){
            printf("\n**Please check your input and enter again**\nN: ");
            scanf("%d",&N);
        }
        /*Entering range of number*/
        printf("Enter the range of numbers ( 2<numbers<10 ) : ");
        scanf("%d",&numbers);
        while(numbers<3 || numbers>9){
            printf("\n**Please check your input and enter again**\nnumbers: ");
            scanf("%d",&numbers);
        }
        /*Entering the structures*/
        printf("Enter the structures ( O,E,U,C,F,L,T,I )\n=> ");
        scanf("%s",structs);
        i=0;
        while(structs[i]){
            for(j=0;j<8;j++){
                if(structs[i]==defaultStructs[j]){
                    activeStructs[j]=1;
                }
                else if((structs[i]+'A'-'a')==defaultStructs[j]){
                    activeStructs[j]=1;
                }
            }
            i++;
        }
        /*displaying active structures in binary model. 1-active; 0-off*/
        for(j=0;j<8;j++){
            printf("%d",activeStructs[j]);
        }
        printf("\n");
/** Initializing board **/
        /*setting random numbers on the board*/
        for(i=0;i<N;i++){
            for(j=0;j<N;j++){
                table[i][j]=rand()%(numbers-1)+2;
            }
        }
/** GAME BEGINS HERE! **/
    matrixShow(table,N);
    while(k>0){ /*k is the chances*/
        printf("\nChange ");
        scanf("%d %d %d",&row,&column,&direction);
        exchange(table,row,column,direction);
        newControl=1;
        lastControl=0;
            while(newControl!=lastControl){
                lastControl=newControl;
                /*check matrix as probabilities of structures*/
                /* control=0 if there are any structure */
                if(activeStructs[0]!=0) {control+=strO(table,N,&score,numbers);}
                if(activeStructs[1]!=0) {control+=strE(table,N,&score,numbers);}
                if(activeStructs[2]!=0) {control+=strU(table,N,&score,numbers);}
                if(activeStructs[3]!=0) {control+=strC(table,N,&score,numbers);}
                if(activeStructs[4]!=0) {control+=strF(table,N,&score,numbers);}
                if(activeStructs[5]!=0) {control+=strL(table,N,&score,numbers);}
                if(activeStructs[6]!=0) {control+=strT(table,N,&score,numbers);}
                if(activeStructs[7]!=0) {control+=strI(table,N,&score,numbers);}
                newControl=control;
            }
        if(control==0){ /*if control equals to 0, decline k(chances)*/
            k--;
            printf("\n**There was not any match\n");
        }
        matrixShow(table,N);/*display the table*/
        printf("\nLives: %d\n",k);
        control=0;
        } /*While looping ends here*/
    if(highScore<score){
        highScore=score;
        printf("\nScore: %d",score);
        printf("\nYou hit new high score!!! Enter the name: ");
        scanf("%s",&highScoreName);
    }
    k=3;
    score=0;
    newControl=1;
    lastControl=0;
    printf("\nHigh score:\t %d  played by %s",highScore,highScoreName);
    printf("\nWant to play again? (y/n) ");
    scanf(" %c",&again);
    }while(again=='y' || again=='Y');
    system("pause");

}
