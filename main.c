#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <memory.h>
#include "stdlib.h"

#define N 21

int cursorX = 0, cursorY = 0;

#define ERR_TOL_L 1
#define ERR_TOL_M 0
#define ERR_TOL_Q 3
#define ERR_TOL_H 2

char codes[255];

void fillCodes()
{
    for(char i = 0; i < 10; i++){
        codes[48+i] = i;
    }
    for (char i = 0; i < 26; i++){
        codes['A' + i] = 10 + i;
    }
    codes[' '] = 36;
    codes['$'] = 37;
    codes['%'] = 38;
    codes['*'] = 39;
    codes['+'] = 40;
    codes['-'] = 41;
    codes['.'] = 42;
    codes['/'] = 43;
    codes[':'] = 44;
}

int main() {
//    fillCodes();
//    char str[25];
//    scanf("%s", str);
//    int counter;
//    int checksum[1024];
//    for (int i = 0; i < strlen(str); i++){
//        if(i + 1 < strlen(str)){
//            printf("%c = %i\n", str[i], codes[str[i]]);
//            printf("%c = %i\n", str[i+1], codes[str[i+1]]);
//            checksum[counter++] = codes[str[i]] * 45 + codes[str[i + 1]];
//            i++;
//        }else{
//            printf("%c = %i\n", str[i], codes[str[i]]);
//            checksum[counter++] = codes[str[i]];
//        }
//        printf("%i\n",checksum[counter - 1]);
//    }
    

    char bitmatrix[N][N];
    char matrix[N][N];
    char buff[N];
    int origin;
    origin = open("./pic.txt", O_RDONLY);
    ssize_t readed = 0;
    for (int i = 0; i < N; i++){
        readed = read(origin, buff, N);
        if(readed == 0) break;
        strcpy(matrix[i], buff);
        read(origin, buff, 1);
    }
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++) {
            if (matrix[i][j] == '#') bitmatrix[i][j] = 1;
            else bitmatrix[i][j] = 0;
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
    int errtolerance = ((bitmatrix[8][0] << 1) | bitmatrix[8][1]) ^ 2;
    int codetype = ((bitmatrix[8][2] << 2) | (bitmatrix[8][3] << 1) | bitmatrix[8][4]) ^ 5;
    printf("errtolerance = %i\ncodetype = %i\n", errtolerance, codetype);
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (i < 8 && j < 8) continue;
            if (i >= N - 8 && j < N - 8) continue;
            if (i < N - 8 && j >= N - 8) continue;
            if (i % 3 == 0 && j == 6) continue;
            if (j % 3 == 0 && i == 6) continue;


            if ((i + j) % 3 == 0){
                bitmatrix[i][j] = !bitmatrix[i][j];
            }
        }
    }
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++) {
            if (bitmatrix[i][j])
                printf("# ");
            else
                printf("_ ");
        }
        printf("\n");
    }
    int codedType = bitmatrix[N-2][N-2] << 3 | bitmatrix[N-1][N-2] << 2 | bitmatrix[N-2][N-1] << 1 | bitmatrix[N-1][N-1];
    printf("coded t = %i\n", codedType);
    return 0;
}