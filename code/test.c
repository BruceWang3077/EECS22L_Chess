#include "struct.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "chess.c"

int main(){
    struct Board* board=(struct Board*)malloc(sizeof(struct Board));
    initializeBoard(board);
    for(int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            printf("%s ",board->board[i][j]->name);
        }
        printf("\n");
    }
    free(board);
}