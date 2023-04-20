#include "structures.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "chess.c"

int main()
{
    struct Board board;
    initializeBoard(&board);

    // Initialize the game
    bool is_game_over = false;
    enum Player human_player, computer_player;
    printf("Choose your side (B for Black, W for White): ");
    char side;
    scanf("%c", &side);
    if (side == 'B')
    {
        human_player = BLACK;
        computer_player = WHITE;
    }
    else
    {
        human_player = WHITE;
        computer_player = BLACK;
    }
    enum Player curr_player = WHITE;
    // FILE *log_file = fopen("chess_game.log", "w");
    // if (log_file == NULL)
    // {
    //     printf("Error: failed to create log file.\n");
    //     exit(1);
    // }

    // Game loop
    while (!is_game_over)
    {
        draw(&board);
        // Human player's turn
        if (human_player == curr_player)
        {
            struct Moves *moves = findAllMoves(human_player, &board);
            if (moves->size == 0)
            {
                printf("You have no legal moves left. Game over.\n");
                endgame();
                is_game_over = true;
                break;
            }
            struct Move move;
            bool is_move_legal = false;
            while (!is_move_legal)
            {
                printf("Enter your move (e.g. e2e4): ");
                char input[10];
                scanf("%s", input);
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
                is_move_legal = isLegal(&move, &board);
                if (!is_move_legal)
                {
                    printf("Illegal move. Try again.\n");
                }
            }
            move(&move);//CONSIDER CHANGING THE FUNCTION NAME!
            //recordMove(&move, human_player);
            curr_player=computer_player;
        }
        // Computer's turn
        else
        {
            struct Move *computer_move = getComputerMove(computer_player, &board);
            move(computer_move);
            //recordMove(computer_move, computer_player);
            curr_player=human_player;
        }

        // Check if game is over
        if (isGameOver(&board))
        {
            is_game_over = true;
            endgame();
        }
    }

    //fclose(log_file);
    return 0;
}
