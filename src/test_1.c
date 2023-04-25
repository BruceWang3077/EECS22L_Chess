#include "structures.h"
#include <stdbool.h>

int main(){
    struct Board *my_board = (struct Board *)malloc(sizeof(struct Board));
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            my_board->board[i][j] = (struct Piece *)malloc(sizeof(struct Piece));
            //my_board->board[i][j]->name[0] = (char *)malloc(4 * sizeof(char));
        }
    }
    initialize(my_board);
    enum Player human_player=WHITE;
    struct Moves *p_list = (struct Moves *)malloc(sizeof(struct Moves));
    p_list->size = 0; // Set initial size of moveList to 0
    for (int i = 0; i < 300; i++)
    {
        p_list->moveList[i].location_src = (struct Location *)malloc(sizeof(struct Location));
        p_list->moveList[i].location_dest = (struct Location *)malloc(sizeof(struct Location));
        p_list->moveList[i].captured_piece = (struct Piece *)malloc(sizeof(struct Piece));
    }

    struct Moves *test_list = (struct Moves *)malloc(sizeof(struct Moves));
    p_list->size = 5; // Set initial size of moveList to 0
    for (int i = 0; i <5; i++)
    {
        test_list->moveList[i].location_src = (struct Location *)malloc(sizeof(struct Location));
        test_list->moveList[i].location_dest = (struct Location *)malloc(sizeof(struct Location));
        test_list->moveList[i].captured_piece = (struct Piece *)malloc(sizeof(struct Piece));
    }
    generatemoves(my_board, p_list, human_player);
    char test_move[4*5+1];
    strcat(test_move,"e2e4");//pawn moves 2 steps forward
    strcat(test_move, "e4e6");//can't move 2 steps forward twice
    strcat(test_move,"b1b3");//can't move a knight straight up
    strcat(test_move,"g1f3");//move a knight in L shape
    strcat(test_move,"d1d3");//can't move queen when there's one on the way
    for(int i=0;i<5;i++){
        int src_file = test_move[i * 4 + 0] - 'a';
        int src_rank = test_move[i * 4 + 1] - '1';
        int dest_file = test_move[i * 4 + 2] - 'a';
        int dest_rank = test_move[i * 4 + 3] - '1';
        test_list->moveList[i].location_src->file = src_file;
        test_list->moveList[i].location_src->rank = src_rank;
        test_list->moveList[i].location_dest->file = dest_file;
        test_list->moveList[i].location_dest->rank = dest_rank;
    }
    for(int i=0;i<5;i++){
        bool result = isLegal(&(test_list->moveList[i]), p_list);
        printf("%d\n", result);
        if(result){
            move_piece(&(test_list->moveList[i]),my_board);
        }

    }
}