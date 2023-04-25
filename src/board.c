#include "structures.h"
#include <stdio.h>

void draw(struct Board *board) {
  printf(" +----+----+----+----+----+----+----+----+\n");
  for(int i = 7; i >= 0; i--) {
    printf("%d|", i+1);
    for(int j = 0; j < 8; j++) {
      struct Piece *p = board->board[i][j];
      if(p == NULL) {
        printf("    |");
      } else {
        printf(" %s |", p->name);
      }
    }
    printf("\n");
    printf(" +----+----+----+----+----+----+----+----+\n");
  }
  printf("    A    B    C    D    E    F    G    H  \n");
}

void move_piece(struct Move *move, struct Board *board) {
  struct Piece *src_piece = board->board[move->location_src->rank][move->location_src->file];
  struct Piece *dst_piece = board->board[move->location_dest->rank][move->location_dest->file];
  enum PieceType t1 = EMPTY_Piece;
  enum Player t2 = EMPTY_Player;
  if((dst_piece->t_piece != t1) && (dst_piece->player != t2)){
      strncpy(dst_piece->name, "  ", 3);
      dst_piece->t_piece = EMPTY_Piece; 
      dst_piece->player = EMPTY_Player;
      dst_piece->captured = true; 
      
      board->board[move->location_src->rank][move->location_src->file] = dst_piece;
      board->board[move->location_dest->rank][move->location_dest->file] = src_piece;
    }
    else{
      board->board[move->location_src->rank][move->location_src->file] = dst_piece;
      board->board[move->location_dest->rank][move->location_dest->file] = src_piece;

    }
  if (!src_piece->moved){
    src_piece->moved=true;
  }
}
 
