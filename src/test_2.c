#include "structures.h"

void main(){
    int i,j;
    struct Board* my_board = (struct Board*)malloc(sizeof(struct Board));
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            my_board->board[i][j] = (struct Piece*)malloc(sizeof(struct Piece));
        }
    }
    struct Move move;
    char input[10]="e2e4";
    int src_file = input[0] - 'a';
    int src_rank = input[1] - '1';
    int dest_file = input[2] - 'a';
    int dest_rank = input[3] - '1';
    move.location_src = malloc(sizeof(struct Location));
    move.location_dest = malloc(sizeof(struct Location));
    move.location_src->file = src_file;
    move.location_src->rank = src_rank;
    move.location_dest->file = dest_file;
    move.location_dest->rank = dest_rank;
    initialize(my_board);
    move_piece(&move, my_board);

    draw(my_board);

    return 0;
}