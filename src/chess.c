#include "structures.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int reload(FILE *log, struct Board* board){
    char start_char;
    char f1,r1,f2,r2;
    log = fopen("bin/log/chess_game.txt", "a+"); // Open file in read mode
    // Check if file exists
    if (log == NULL)
    {
        printf("File does not exist.\n");
        return 0;
    }

    // Read and print all lines
    struct Move *move = malloc(sizeof(struct Move));
    move->location_dest = malloc(sizeof(struct Location));
    move->location_src = malloc(sizeof(struct Location));
    if (move == NULL || move->location_dest == NULL || move->location_src == NULL)
    {
        printf("Error: failed to create move .\n");
        exit(1);
    }
    while (fscanf(log, "%c %c%c%c%c\n", &start_char, &r1, &f1, &r2, &f2) == 5)
    {
        move->location_src->file = f1-'0';
        move->location_src->rank = r1-'0';
        move->location_dest->file = f2-'0';
        move->location_dest->rank = r2 -'0';
        move_piece(move,board);
        // printf("reload: ");
        // print_move(move)
    }
    enum Player next=(start_char=='B')?WHITE:BLACK;
    board->current_player=next;

    fclose(log); // Close file
    return 0;
}
void sighandler(int signum)
{
    printf("time's up!\n");
    //exit(1);
}
int get_user_move(struct Move *move)
{   signal(SIGALRM,sighandler);
    printf("Enter your move (e.g. e2e4): ");
    alarm(60);
    char input[10];
    printf("You have 1 minute to input your move:\n");
    scanf("%s",input);

    int src_file = input[0] - 'a';
    int src_rank = input[1] - '1';
    int dest_file = input[2] - 'a';
    int dest_rank = input[3] - '1';
    move->location_src = malloc(sizeof(struct Location));
    move->location_dest = malloc(sizeof(struct Location));
    move->location_src->file = src_file;
    move->location_src->rank = src_rank;
    move->location_dest->file = dest_file;
    move->location_dest->rank = dest_rank;
    return 0;
}

void initialize(struct Board *board)
{   board->current_player=WHITE;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            board->board[i][j] = (struct Piece *)malloc(sizeof(struct Piece));
            // my_board->board[i][j]->name[0] = (char *)malloc(4 * sizeof(char));
        }
    }
    // Initialize the pieces for the white player
    // for (int i = 0; i < 8; i++)
    // {
    //     for (int j = 0; j < 8; j++)
    //     {
    //         board->board[i][j] = (struct Piece *)malloc(sizeof(struct Piece));
    //         // board->board[i][j]->name = (char *)malloc(3 * sizeof(char));
    //     }
    // }
    struct Piece *piece = board->board[0][0];
    strncpy(piece->name, "wR", 3);
    piece->t_piece = ROOK;
    piece->player = WHITE;
    piece->moved = false;
    piece->captured = false;
    piece->enpass = false;

    piece = board->board[0][1];
    strncpy(piece->name, "wN", 3);
    piece->t_piece = KNIGHT;
    piece->player = WHITE;
    piece->moved = false;
    piece->captured = false;
    piece->enpass = false;

    piece = board->board[0][2];
    strncpy(piece->name, "wB", 3);
    piece->t_piece = BISHOP;
    piece->player = WHITE;
    piece->moved = false;
    piece->captured = false;
    piece->enpass = false;

    piece = board->board[0][3];
    strncpy(piece->name, "wQ", 3);
    piece->t_piece = QUEEN;
    piece->player = WHITE;
    piece->moved = false;
    piece->captured = false;
    piece->enpass = false;

    piece = board->board[0][4];
    strncpy(piece->name, "wK", 3);
    piece->t_piece = KING;
    piece->player = WHITE;
    piece->moved = false;
    piece->captured = false;
    piece->enpass = false;

    piece = board->board[0][5];
    strncpy(piece->name, "wB", 3);
    piece->t_piece = BISHOP;
    piece->player = WHITE;
    piece->moved = false;
    piece->captured = false;
    piece->enpass = false;

    piece = board->board[0][6];
    strncpy(piece->name, "wN", 3);
    piece->t_piece = KNIGHT;
    piece->player = WHITE;
    piece->moved = false;
    piece->captured = false;
    piece->enpass = false;

    piece = board->board[0][7];
    strncpy(piece->name, "wR", 3);
    piece->t_piece = ROOK;
    piece->player = WHITE;
    piece->moved = false;
    piece->captured = false;
    piece->enpass = false;

    // Initialize the pawns for the white player
    for (int i = 0; i < 8; i++)
    {
        piece = board->board[1][i];
        strncpy(piece->name, "wP", 3);
        piece->t_piece = PAWN;
        piece->player = WHITE;
        piece->moved = false;
        piece->captured = false;
        piece->enpass = false;
    }

    // Initialize the empty squares
    for (int i = 2; i < 6; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            piece = board->board[i][j];
            strncpy(piece->name, "  ", 3);
            piece->t_piece = EMPTY_Piece;
            piece->player = EMPTY_Player;
            piece->moved = false;
            piece->captured = false;
            piece->enpass = false;
        }
    }

    // Initialize the pawns for the black player
    for (int i = 0; i < 8; i++)
    {
        piece = board->board[6][i];
        strncpy(piece->name, "bP", 3);
        piece->t_piece = PAWN;
        piece->player = BLACK;
        piece->moved = false;
        piece->captured = false;
        piece->enpass = false;
    }

    // Initialize the pieces for the black player
    piece = board->board[7][0];
    strncpy(piece->name, "bR", 3);
    piece->t_piece = ROOK;
    piece->player = BLACK;
    piece->moved = false;
    piece->captured = false;
    piece->enpass = false;

    piece = board->board[7][1];
    strncpy(piece->name, "bN", 3);
    piece->t_piece = KNIGHT;
    piece->player = BLACK;
    piece->moved = false;
    piece->captured = false;
    piece->enpass = false;

    piece = board->board[7][2];
    strncpy(piece->name, "bB", 3);
    piece->t_piece = BISHOP;
    piece->player = BLACK;
    piece->moved = false;
    piece->captured = false;
    piece->enpass = false;

    piece = board->board[7][3];
    strncpy(piece->name, "bQ", 3);
    piece->t_piece = QUEEN;
    piece->player = BLACK;
    piece->moved = false;
    piece->captured = false;
    piece->enpass = false;

    piece = board->board[7][4];
    strncpy(piece->name, "bK", 3);
    piece->t_piece = KING;
    piece->player = BLACK;
    piece->moved = false;
    piece->captured = false;
    piece->enpass = false;

    piece = board->board[7][5];
    strncpy(piece->name, "bB", 3);
    piece->t_piece = BISHOP;
    piece->player = BLACK;
    piece->moved = false;
    piece->captured = false;
    piece->enpass = false;

    piece = board->board[7][6];
    strncpy(piece->name, "bN", 3);
    piece->t_piece = KNIGHT;
    piece->player = BLACK;
    piece->moved = false;
    piece->captured = false;
    piece->enpass = false;

    piece = board->board[7][7];
    strncpy(piece->name, "bR", 3);
    piece->t_piece = ROOK;
    piece->player = BLACK;
    piece->moved = false;
    piece->captured = false;
    piece->enpass = false;

    // Initialize castling flags
    board->whiteHasCastled = false;
    board->blackHasCastled = false;
}
void print_moves(struct Moves *moves, struct Board *position)
{
    const char *enum_names[] = {
        "KING",
        "QUEEN",
        "ROOK",
        "BISHOP",
        "KNIGHT",
        "PAWN",
        "ETYPE"};
    const char *enum_player[] = {
        "BLACK",
        "WHITE",
        "EMPTY"};
    printf("List of Moves:\n");
    for (int i = 0; i < moves->size; i++)
    {
        printf("Move %d:\n", i + 1);
        printf("Piece type: %s\n", enum_player[position->board[moves->moveList[i].location_src->rank][moves->moveList[i].location_src->file]->player]);
        printf("Piece type: %s\n", enum_names[position->board[moves->moveList[i].location_src->rank][moves->moveList[i].location_src->file]->t_piece]);
        printf("Source Location: Rank %d, File %d\n", moves->moveList[i].location_src->rank + 1, moves->moveList[i].location_src->file + 1);
        printf("Destination Location: Rank %d, File %d\n", moves->moveList[i].location_dest->rank + 1, moves->moveList[i].location_dest->file + 1);
        printf("-----------------------\n");
    }
}
void recordMove(struct Move *move, enum Player curr_player, FILE *fp)
{
    const char *str;
    if (curr_player == WHITE)
    {
        str = "W ";
    }
    else if (curr_player == BLACK)
    {
        str = "B ";
    }
    else
    {
        printf("incorrect player information!\n");
        // set str to a default value to avoid undefined behavior
        str = "";
    }
    fprintf(fp, "%s", str);
    int srcrank = move->location_src->rank;
    int srcfile = move->location_src->file;
    int destrank = move->location_dest->rank;
    int destfile = move->location_dest->file;
    fprintf(fp, "%d%d%d%d \n", srcrank, srcfile, destrank, destfile);
    //printf("move Recorded\n");
}