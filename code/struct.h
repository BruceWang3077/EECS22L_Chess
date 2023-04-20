
#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



enum PieceType {
    KING,
    QUEEN,
    ROOK,
    BISHOP,
    KNIGHT,
    PAWN,
    EMPTY_Player
};

// Define the different players
enum Player {
    BLACK,
    WHITE,
    EMPTY_Piece
};

// Define a struct to represent a chess piece
struct Piece {
    char name[3];
    enum PieceType t_piece;
    enum Player player;
    bool moved;
    bool captured;
    bool enpass;
};

// Define a struct to represent a chess move
struct Move {
    struct Location* location_src;
    struct Location* location_dest;
    struct Piece captured_piece;
};

//Define a struct to store a list of moves
struct Moves {
    int size;
    struct Move moveList[300];
};

//define a struct to represent chessboard location
struct Location {
    int rank;
    int file;
};

// Define the chess board as an 8x8 array of Piece structs
struct Board {
    struct Piece* board[8][8];
    bool whiteHasCastled;
    bool blackHasCastled;
};

extern void initializeBoard(struct Board *board);



#endif // CHESS_GAME_H