#ifndef CHESS_GAME_H
#define CHESS_GAME_H

// Define the different piece types
enum PieceType {
  KING,
  QUEEN,
  ROOK,
  BISHOP,
  KNIGHT,
  PAWN,
  EMPTY
};

// Define the different players
enum Player {
  BLACK,
  WHITE,
  EMPTY
};

// Define a struct to represent a chess piece
struct Piece {
  char *name3[3];
  PieceType t_piece;
  Player player;
  bool moved;
  bool captured;
};

// Define a struct to represent a chess move
struct Move {
  Location location_src;
  Location location_dest;
  Piece captured_piece;
};

//Define a struct to store a list of moves
struct Moves {
  int size;
  Move moveList[];
};

// Define a struct to represent a chess board location
struct Location {
  int rank;
  int file;
};

// Define the chess board as an 8x8 array of Piece structs
struct Board{
    Piece* board[8][8];
    bool whiteHasCastled;
    bool blackHasCastled;
}


#endif // CHESS_GAME_H