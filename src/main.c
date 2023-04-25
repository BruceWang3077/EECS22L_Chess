#include "structures.h"
#include <time.h>
#define MAXMOVES 300

void endgame()
{
    printf("end game\n");
}
bool isGameOver(struct Board *board)
{
    printf("run isGameOver()\n");
    return false;
}

// above for the test
int main()
{
    int i, j;
    srand(time(NULL));
    struct Board *my_board = (struct Board *)malloc(sizeof(struct Board));
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            my_board->board[i][j] = (struct Piece *)malloc(sizeof(struct Piece));
            //my_board->board[i][j]->name[0] = (char *)malloc(4 * sizeof(char));
        }
    }
    initialize(my_board);

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

    // Allocate memory for struct Moves
    struct Moves *p_list = (struct Moves *)malloc(sizeof(struct Moves));
    p_list->size = 0; // Set initial size of moveList to 0
    for (i = 0; i < MAXMOVES; i++)
    {
        p_list->moveList[i].location_src = (struct Location *)malloc(sizeof(struct Location));
        p_list->moveList[i].location_dest = (struct Location *)malloc(sizeof(struct Location));
        p_list->moveList[i].captured_piece = (struct Piece *)malloc(sizeof(struct Piece));
    }
    FILE *log_file = fopen("bin/log/chess_game.txt", "w");
    if (log_file == NULL)
    {
        printf("Error: failed to create log file.\n");
        exit(1);
    }
 //test
    int count=0;
    // Game loop
    while (!is_game_over)
    {
        draw(my_board);
        // Human player's turn
        if (human_player == curr_player)
        {

            generatemoves(my_board, p_list, human_player);
            //print_moves(p_list, my_board);
            if (p_list->size == 0)
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
                is_move_legal = isLegal(&move, p_list);
                if (!is_move_legal)
                {
                    printf("Illegal move. Try again.\n");
                }
            }
            move_piece(&move, my_board);
            recordMove(&move, human_player, log_file);
            curr_player = computer_player;
        }
        // Computer's turn
        else
        {
            struct Move *computer_move;
            generatemoves(my_board, p_list, computer_player);
            int random_int;
            random_int = rand() % (p_list->size);
            computer_move=&(p_list->moveList[random_int]);
            move_piece(computer_move,my_board);
            recordMove(computer_move, computer_player, log_file);
            curr_player = human_player;
        }
        count++;
        // Check if game is over
        if (isGameOver(my_board) || count==10)
        {
            is_game_over = true;
            endgame();
            break;
        }
    }

    fclose(log_file);
    return 0;
}
