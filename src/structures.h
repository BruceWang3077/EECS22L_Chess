
#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <time.h>

enum PieceType
{
    KING,
    QUEEN,
    ROOK,
    BISHOP,
    KNIGHT,
    PAWN,
    EMPTY_Piece
};

// Define the different players
enum Player
{
    BLACK,
    WHITE,
    EMPTY_Player
};

// Define a struct to represent a chess piece
struct Piece
{
    char name[3];
    enum PieceType t_piece;
    enum Player player;
    bool moved;
    bool captured;
    bool enpass;
};

// Define a struct to represent a chess move
struct Move
{
    struct Location *location_src;
    struct Location *location_dest;
    struct Piece *captured_piece;
    bool castling;
};

// Define a struct to store a list of moves
struct Moves
{
    int size;
    struct Move moveList[300];
};

// define a struct to represent chessboard location
struct Location
{
    int rank;
    int file;
};

// Define the chess board as an 8x8 array of Piece structs
struct Board
{
    struct Piece *board[8][8];
    enum Player current_player;
    bool whiteHasCastled;
    bool blackHasCastled;
};

extern void initialize(struct Board *board);
extern void print_moves(struct Moves *moves, struct Board *position);
extern bool isGameOver(struct Board *board);
extern int inCheck(struct Board *board, enum Player playerColor, struct Moves *moves);
extern void generatemoves(struct Board *position, struct Moves *p_list, enum Player playerturn);
extern int straight_moves_count(struct Board *position, int dir, int rank, int file);
extern void move_piece(struct Move *move, struct Board *board);
extern void draw(struct Board *board);
extern bool isLegal(struct Move *move, struct Moves *moves);
extern void recordMove(struct Move *move, enum Player curr_player, FILE *fp);
extern int get_user_move(struct Move *move);
extern int reload(FILE *log, struct Board *board);
extern void print_move(struct Move* move);
extern int print_files()
#endif // CHESS_GAME_H