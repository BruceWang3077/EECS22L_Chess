#include "structures.h"

int straight_moves_count(struct Board *position, int dir, int rank, int file)
{
	int count = 0;
	int i;
	if (dir == 0)
	{ // direction goes forward
		for (i = 1; i <= 7; i++)
		{
			if ((rank + i) < 8)
			{
				if (position->board[rank + i][file]->player == EMPTY_Player)
				{
					count++;
				}
				else
				{
					break; // exit loop if a non-empty square is encountered
				}
			}
			else
			{
				break; // exit loop if outside the bounds of the chessboard
			}
		}
	}
	if (dir == 1)
	{ // direction goes backward
		for (i = 1; i <= 7; i++)
		{
			if ((rank - i) >= 0)
			{
				if (position->board[rank - i][file]->player == EMPTY_Player)
				{
					count++;
				}
				else
				{
					break; // exit loop if a non-empty square is encountered
				}
			}
			else
			{
				break; // exit loop if outside the bounds of the chessboard
			}
		}
	}

	if (dir == 2)
	{ // direction goes left
		for (i = 1; i <= 7; i++)
		{
			if ((file - i) >= 0)
			{
				if (position->board[rank][file - i]->player == EMPTY_Player)
				{
					count++;
				}
				else
				{
					break; // exit loop if a non-empty square is encountered
				}
			}
			else
			{
				break; // exit loop if outside the bounds of the chessboard
			}
		}
	}
	if (dir == 3)
	{ // direction goes right
		for (i = 1; i <= 7; i++)
		{
			if ((file + i) < 8)
			{
				if (position->board[rank][file + i]->player == EMPTY_Player)
				{
					count++;
				}
				else
				{
					break; // exit loop if a non-empty square is encountered
				}
			}
			else
			{
				break; // exit loop if outside the bounds of the chessboard
			}
		}
	}
	return count;
}

void generatemoves(struct Board *position, struct Moves *p_list, enum Player playerturn)
{

	p_list->size = 0;
	int movecount = 0;
	int i;
	int j;
	int count;
	int rank;
	int file;
	int dir;
	int c;
	int r;
	int f;
	int dr;
	int df;
	int knight_moves[8][2] = {{-2, -1}, {-1, -2}, {1, -2}, {2, -1}, {-2, 1}, {-1, 2}, {1, 2}, {2, 1}};

	// square the piece is at, loops through all the pieces
	for (rank = 0; rank < 8; rank++)
	{
		for (file = 0; file < 8; file++)
		{
			struct Piece *piece = position->board[rank][file];

			if (playerturn == WHITE)
			{
				if (piece->player == WHITE)
				{
					// possible moves for white pawn
					if (piece->t_piece == PAWN)
					{
						// checks for white pawn move
						if ((rank + 1) < 8)
						{
							if (position->board[rank + 1][file]->player == EMPTY_Player)
							{
								p_list->moveList[p_list->size].location_src->rank = rank;
								p_list->moveList[p_list->size].location_src->file = file;
								p_list->moveList[p_list->size].location_dest->rank = rank + 1;
								p_list->moveList[p_list->size].location_dest->file = file;
								p_list->size++;

								// for white pawn moving up twice, checks if second square is also empty
								if (piece->moved == false && (rank + 2) < 8)
								{
									if (position->board[rank + 2][file]->player == EMPTY_Player)
									{
										p_list->moveList[p_list->size].location_src->rank = rank;
										p_list->moveList[p_list->size].location_src->file = file;
										p_list->moveList[p_list->size].location_dest->rank = rank + 2;
										p_list->moveList[p_list->size].location_dest->file = file;
										p_list->size++;
									}
								}
							}
						}
						// for white pawn right diagonal capture move, also check is move is on board
						if ((file + 1) < 8 && (rank + 1) < 8)
						{
							if (position->board[rank + 1][file + 1]->player == BLACK)
							{
								p_list->moveList[p_list->size].location_src->rank = rank;
								p_list->moveList[p_list->size].location_src->file = file;
								p_list->moveList[p_list->size].location_dest->rank = rank + 1;
								p_list->moveList[p_list->size].location_dest->file = file + 1;
								p_list->moveList[p_list->size].captured_piece->player = BLACK;
								p_list->moveList[p_list->size].captured_piece->t_piece = position->board[rank + 1][file + 1]->t_piece;
								p_list->size++;
							}
						}
						// for white pawn left diagonal capture move, also check is move is on board
						if ((file - 1) >= 0 && (rank + 1) < 8)
						{
							if (position->board[rank + 1][file - 1]->player == BLACK)
							{
								p_list->moveList[p_list->size].location_src->rank = rank;
								p_list->moveList[p_list->size].location_src->file = file;
								p_list->moveList[p_list->size].location_dest->rank = rank + 1;
								p_list->moveList[p_list->size].location_dest->file = file - 1;
								p_list->moveList[p_list->size].captured_piece->player = BLACK;
								p_list->moveList[p_list->size].captured_piece->t_piece = position->board[rank + 1][file - 1]->t_piece;
								p_list->size++;
							}
						}
						// checks for possible enpassant move right and left
						if (position->board[rank][file + 1]->enpass == true)
						{
							if ((file + 1) < 8 && (rank + 1) < 8)
							{
								if (position->board[rank + 1][file + 1]->player == EMPTY_Player)
								{
									p_list->moveList[p_list->size].location_src->rank = rank;
									p_list->moveList[p_list->size].location_src->file = file;
									p_list->moveList[p_list->size].location_dest->rank = rank + 1;
									p_list->moveList[p_list->size].location_dest->file = file + 1;
									p_list->moveList[p_list->size].captured_piece->player = BLACK;
									p_list->moveList[p_list->size].captured_piece->t_piece = position->board[rank][file + 1]->t_piece;
									p_list->size++;
								}
							}
						}
						if (position->board[rank][file - 1]->enpass == true)
						{
							if ((file - 1) >= 0 && (rank + 1) < 8)
							{
								if (position->board[rank + 1][file - 1]->player == EMPTY_Player)
								{
									p_list->moveList[p_list->size].location_src->rank = rank;
									p_list->moveList[p_list->size].location_src->file = file;
									p_list->moveList[p_list->size].location_dest->rank = rank + 1;
									p_list->moveList[p_list->size].location_dest->file = file - 1;
									p_list->moveList[p_list->size].captured_piece->player = BLACK;
									p_list->moveList[p_list->size].captured_piece->t_piece = position->board[rank][file - 1]->t_piece;
									p_list->size++;
								}
							}
						}
					}
					// possible moves for white rook
					if (piece->t_piece == ROOK)
					{ // possible moves for white rook no attack
						for (dir = 0; dir < 4; dir++)
						{
							movecount = straight_moves_count(position, dir, rank, file);
							for (c = 1; c <= movecount; c++)
							{
								p_list->moveList[p_list->size].location_src->rank = rank;
								p_list->moveList[p_list->size].location_src->file = file;

								switch (dir)
								{
								case 0:
									p_list->moveList[p_list->size].location_dest->rank = rank + c;
									p_list->moveList[p_list->size].location_dest->file = file;
									break;
								case 1:
									p_list->moveList[p_list->size].location_dest->rank = rank - c;
									p_list->moveList[p_list->size].location_dest->file = file;
									break;
								case 2:
									p_list->moveList[p_list->size].location_dest->rank = rank;
									p_list->moveList[p_list->size].location_dest->file = file - c;
									break;
								case 3:
									p_list->moveList[p_list->size].location_dest->rank = rank;
									p_list->moveList[p_list->size].location_dest->file = file + c;
									break;
								}

								p_list->size++;
							}
							if ((rank + movecount + 1) < 8)
							{ // Finds white rook forward attack move
								if (position->board[rank + movecount + 1][file]->player == BLACK)
								{
									p_list->moveList[p_list->size].location_src->rank = rank;
									p_list->moveList[p_list->size].location_src->file = file;
									p_list->moveList[p_list->size].location_dest->rank = rank + movecount + 1;
									p_list->moveList[p_list->size].location_dest->file = file;
									p_list->moveList[p_list->size].captured_piece->player = BLACK;
									p_list->moveList[p_list->size].captured_piece->t_piece = position->board[rank + movecount + 1][file]->t_piece;
									p_list->size++;
								}
							}
							if ((rank - (movecount + 1)) >= 0)
							{ // Finds white rook backward attack move
								if (position->board[rank - (movecount + 1)][file]->player == BLACK)
								{
									p_list->moveList[p_list->size].location_src->rank = rank;
									p_list->moveList[p_list->size].location_src->file = file;
									p_list->moveList[p_list->size].location_dest->rank = rank - (movecount + 1);
									p_list->moveList[p_list->size].location_dest->file = file;
									p_list->moveList[p_list->size].captured_piece->player = BLACK;
									p_list->moveList[p_list->size].captured_piece->t_piece = position->board[rank - (movecount + 1)][file]->t_piece;
									p_list->size++;
								}
							}
							if ((file - (movecount + 1)) >= 0)
							{ // Finds white rook left attack move
								if (position->board[rank][file - (movecount + 1)]->player == BLACK)
								{
									p_list->moveList[p_list->size].location_src->rank = rank;
									p_list->moveList[p_list->size].location_src->file = file;
									p_list->moveList[p_list->size].location_dest->rank = rank;
									p_list->moveList[p_list->size].location_dest->file = file - (movecount + 1);
									p_list->moveList[p_list->size].captured_piece->player = BLACK;
									p_list->moveList[p_list->size].captured_piece->t_piece = position->board[rank][file - (movecount + 1)]->t_piece;
									p_list->size++;
								}
							}
							if ((file + (movecount + 1)) < 8)
							{ // Finds white rook right attack move
								if (position->board[rank][file + movecount + 1]->player == BLACK)
								{
									p_list->moveList[p_list->size].location_src->rank = rank;
									p_list->moveList[p_list->size].location_src->file = file;
									p_list->moveList[p_list->size].location_dest->rank = rank;
									p_list->moveList[p_list->size].location_dest->file = file + movecount + 1;
									p_list->moveList[p_list->size].captured_piece->player = BLACK;
									p_list->moveList[p_list->size].captured_piece->t_piece = position->board[rank][file + movecount + 1]->t_piece;
									p_list->size++;
								}
							}
						}
					}
					// possible white bishop moves
					if (piece->t_piece == BISHOP)
					{
						movecount = 0;

						// Checking all possible diagonal moves in the four diagonal directions: top-left, top-right, bottom-left, bottom-right
						for (i = -1; i <= 1; i += 2)
						{ // i = -1 for top directions, i = 1 for bottom directions
							for (j = -1; j <= 1; j += 2)
							{ // j = -1 for left directions, j = 1 for right directions
								r = rank + i;
								f = file + j;
								while (r >= 0 && r < 8 && f >= 0 && f < 8)
								{ // Continue moving diagonally until the edge of the board is reached
									if (position->board[r][f]->player == EMPTY_Player)
									{ // If the square is empty
										// Add the move to the list of legal moves
										p_list->moveList[p_list->size].location_src->rank = rank;
										p_list->moveList[p_list->size].location_src->file = file;
										p_list->moveList[p_list->size].location_dest->rank = r;
										p_list->moveList[p_list->size].location_dest->file = f;
										p_list->size++;
									}
									else
									{
										// If there is a piece on the square, check if it's an opponent's piece and add the move if it is
										if (position->board[r][f]->player == BLACK)
										{
											p_list->moveList[p_list->size].location_src->rank = rank;
											p_list->moveList[p_list->size].location_src->file = file;
											p_list->moveList[p_list->size].location_dest->rank = r;
											p_list->moveList[p_list->size].location_dest->file = f;
											p_list->moveList[p_list->size].captured_piece->player = BLACK;
											p_list->moveList[p_list->size].captured_piece->t_piece = position->board[r][f]->t_piece;
											p_list->size++;
										}
										// Stop checking further in this direction since the bishop can't move through pieces
										break;
									}
									r += i;
									f += j;
								}
							}
						}
					}
					// possible white knight moves
					if (piece->t_piece == KNIGHT)
					{
						movecount = 0;
						// All possible knight moves from the current position
						for (i = 0; i < 8; i++)
						{
							r = rank + knight_moves[i][0];
							f = file + knight_moves[i][1];

							// Check if the move is within the board boundaries
							if (r >= 0 && r < 8 && f >= 0 && f < 8)
							{
								if (position->board[r][f]->player == EMPTY_Player)
								{ // If the square is empty
									// Add the move to the list of legal moves
									p_list->moveList[p_list->size].location_src->rank = rank;
									p_list->moveList[p_list->size].location_src->file = file;
									p_list->moveList[p_list->size].location_dest->rank = r;
									p_list->moveList[p_list->size].location_dest->file = f;
									p_list->size++;
								}
								else
								{
									// If there is a piece on the square, check if it's an opponent's piece and add the move if it is
									if (position->board[r][f]->player == BLACK)
									{
										p_list->moveList[p_list->size].location_src->rank = rank;
										p_list->moveList[p_list->size].location_src->file = file;
										p_list->moveList[p_list->size].location_dest->rank = r;
										p_list->moveList[p_list->size].location_dest->file = f;
										p_list->moveList[p_list->size].captured_piece->player = BLACK;
										p_list->moveList[p_list->size].captured_piece->t_piece = position->board[r][f]->t_piece;
										p_list->size++;
									}
								}
							}
						}
					}
					// possible white queen moves
					if (piece->t_piece == QUEEN)
					{
						// straight moves
						for (dir = 0; dir < 4; dir++)
						{
							movecount = straight_moves_count(position, dir, rank, file);
							for (c = 1; c <= movecount; c++)
							{
								p_list->moveList[p_list->size].location_src->rank = rank;
								p_list->moveList[p_list->size].location_src->file = file;

								switch (dir)
								{
								case 0:
									p_list->moveList[p_list->size].location_dest->rank = rank + c;
									p_list->moveList[p_list->size].location_dest->file = file;
									break;
								case 1:
									p_list->moveList[p_list->size].location_dest->rank = rank - c;
									p_list->moveList[p_list->size].location_dest->file = file;
									break;
								case 2:
									p_list->moveList[p_list->size].location_dest->rank = rank;
									p_list->moveList[p_list->size].location_dest->file = file - c;
									break;
								case 3:
									p_list->moveList[p_list->size].location_dest->rank = rank;
									p_list->moveList[p_list->size].location_dest->file = file + c;
									break;
								}

								p_list->size++;
							}
							if ((rank + movecount + 1) < 8)
							{ // Finds white queen forward attack move
								if (position->board[rank + movecount + 1][file]->player == BLACK)
								{
									p_list->moveList[p_list->size].location_src->rank = rank;
									p_list->moveList[p_list->size].location_src->file = file;
									p_list->moveList[p_list->size].location_dest->rank = rank + movecount + 1;
									p_list->moveList[p_list->size].location_dest->file = file;
									p_list->moveList[p_list->size].captured_piece->player = BLACK;
									p_list->moveList[p_list->size].captured_piece->t_piece = position->board[rank + movecount + 1][file]->t_piece;
									p_list->size++;
								}
							}
							if ((rank - (movecount + 1)) >= 0)
							{ // Finds white queen backward attack move
								if (position->board[rank - (movecount + 1)][file]->player == BLACK)
								{
									p_list->moveList[p_list->size].location_src->rank = rank;
									p_list->moveList[p_list->size].location_src->file = file;
									p_list->moveList[p_list->size].location_dest->rank = rank - (movecount + 1);
									p_list->moveList[p_list->size].location_dest->file = file;
									p_list->moveList[p_list->size].captured_piece->player = BLACK;
									p_list->moveList[p_list->size].captured_piece->t_piece = position->board[rank - (movecount + 1)][file]->t_piece;
									p_list->size++;
								}
							}
							if ((file - (movecount + 1)) >= 0)
							{ // Finds white queen left attack move
								if (position->board[rank][file - (movecount + 1)]->player == BLACK)
								{
									p_list->moveList[p_list->size].location_src->rank = rank;
									p_list->moveList[p_list->size].location_src->file = file;
									p_list->moveList[p_list->size].location_dest->rank = rank;
									p_list->moveList[p_list->size].location_dest->file = file - (movecount + 1);
									p_list->moveList[p_list->size].captured_piece->player = BLACK;
									p_list->moveList[p_list->size].captured_piece->t_piece = position->board[rank][file - (movecount + 1)]->t_piece;
									p_list->size++;
								}
							}
							if ((file + (movecount + 1)) < 8)
							{ // Finds white queen right attack move
								if (position->board[rank][file + movecount + 1]->player == BLACK)
								{
									p_list->moveList[p_list->size].location_src->rank = rank;
									p_list->moveList[p_list->size].location_src->file = file;
									p_list->moveList[p_list->size].location_dest->rank = rank;
									p_list->moveList[p_list->size].location_dest->file = file + movecount + 1;
									p_list->moveList[p_list->size].captured_piece->player = BLACK;
									p_list->moveList[p_list->size].captured_piece->t_piece = position->board[rank][file + movecount + 1]->t_piece;
									p_list->size++;
								}
							}
						}
						movecount = 0;
						// Checking all possible diagonal moves in the four diagonal directions: top-left, top-right, bottom-left, bottom-right
						for (i = -1; i <= 1; i += 2)
						{ // i = -1 for top directions, i = 1 for bottom directions
							for (j = -1; j <= 1; j += 2)
							{ // j = -1 for left directions, j = 1 for right directions
								r = rank + i;
								f = file + j;
								while (r >= 0 && r < 8 && f >= 0 && f < 8)
								{ // Continue moving diagonally until the edge of the board is reached
									if (position->board[r][f]->player == EMPTY_Player)
									{ // If the square is empty
										// Add the move to the list of legal moves
										p_list->moveList[p_list->size].location_src->rank = rank;
										p_list->moveList[p_list->size].location_src->file = file;
										p_list->moveList[p_list->size].location_dest->rank = r;
										p_list->moveList[p_list->size].location_dest->file = f;
										p_list->size++;
									}
									else
									{
										// If there is a piece on the square, check if it's an opponent's piece and add the move if it is
										if (position->board[r][f]->player == BLACK)
										{
											p_list->moveList[p_list->size].location_src->rank = rank;
											p_list->moveList[p_list->size].location_src->file = file;
											p_list->moveList[p_list->size].location_dest->rank = r;
											p_list->moveList[p_list->size].location_dest->file = f;
											p_list->moveList[p_list->size].captured_piece->player = BLACK;
											p_list->moveList[p_list->size].captured_piece->t_piece = position->board[r][f]->t_piece;
											p_list->size++;
										}
										// Stop checking further in this direction since the queen can't move through pieces
										break;
									}
									r += i;
									f += j;
								}
							}
						}
					}
					// all possible king moves
					if (piece->t_piece == KING)
					{
						// All possible king moves from the current position
						for (dr = -1; dr <= 1; dr++)
						{
							for (df = -1; df <= 1; df++)
							{
								// Skip the current position (no move)
								if (dr == 0 && df == 0)
									continue;

								r = rank + dr;
								f = file + df;
								// Check if the move is within the board boundaries
								if (r >= 0 && r < 8 && f >= 0 && f < 8)
								{
									if (position->board[r][f]->player == EMPTY_Player)
									{ // If the square is empty
										p_list->moveList[p_list->size].location_src->rank = rank;
										p_list->moveList[p_list->size].location_src->file = file;
										p_list->moveList[p_list->size].location_dest->rank = r;
										p_list->moveList[p_list->size].location_dest->file = f;
										p_list->size++;
									}
									if (position->board[r][f]->player == BLACK)
									{ // If the square contains opponents piece
										p_list->moveList[p_list->size].location_src->rank = rank;
										p_list->moveList[p_list->size].location_src->file = file;
										p_list->moveList[p_list->size].location_dest->rank = r;
										p_list->moveList[p_list->size].location_dest->file = f;
										p_list->moveList[p_list->size].captured_piece->player = BLACK;
										p_list->moveList[p_list->size].captured_piece->t_piece = position->board[r][f]->t_piece;
										p_list->size++;
									}
								}
							}
						}
					}
				}
			}
			if (playerturn == BLACK)
			{
				if (piece->player == BLACK)
				{
					// possible moves for black pawn
					if (piece->t_piece == PAWN)
					{
						// for black pawn moving once and twice
						if ((rank - 1) >= 0)
						{
							if (position->board[rank - 1][file]->player == EMPTY_Player)
							{
								p_list->moveList[p_list->size].location_src->rank = rank;
								p_list->moveList[p_list->size].location_src->file = file;
								p_list->moveList[p_list->size].location_dest->rank = rank - 1;
								p_list->moveList[p_list->size].location_dest->file = file;
								p_list->size++;

								// for black pawn moving down twice, checks if second square is also empty
								if (piece->moved == false && (rank - 2) >= 0)
								{
									if (position->board[rank - 2][file]->player == EMPTY_Player)
									{
										p_list->moveList[p_list->size].location_src->rank = rank;
										p_list->moveList[p_list->size].location_src->file = file;
										p_list->moveList[p_list->size].location_dest->rank = rank - 2;
										p_list->moveList[p_list->size].location_dest->file = file;
										p_list->size++;
									}
								}
							}
						}
						// for black pawn right diagonal capture move, also check if move is on board
						if ((file + 1) <= 7 && (rank - 1) >= 0)
						{
							if (position->board[rank - 1][file + 1]->player == WHITE)
							{
								p_list->moveList[p_list->size].location_src->rank = rank;
								p_list->moveList[p_list->size].location_src->file = file;
								p_list->moveList[p_list->size].location_dest->rank = rank - 1;
								p_list->moveList[p_list->size].location_dest->file = file + 1;
								p_list->moveList[p_list->size].captured_piece->player = WHITE;
								p_list->moveList[p_list->size].captured_piece->t_piece = position->board[rank - 1][file + 1]->t_piece;
								p_list->size++;
							}
						}
						// for black pawn left diagonal capture move, also check if move is on board
						if ((file - 1) >= 0 && (rank - 1) >= 0)
						{
							if (position->board[rank - 1][file - 1]->player == WHITE)
							{
								p_list->moveList[p_list->size].location_src->rank = rank;
								p_list->moveList[p_list->size].location_src->file = file;
								p_list->moveList[p_list->size].location_dest->rank = rank - 1;
								p_list->moveList[p_list->size].location_dest->file = file - 1;
								p_list->moveList[p_list->size].captured_piece->player = WHITE;
								p_list->moveList[p_list->size].captured_piece->t_piece = position->board[rank - 1][file - 1]->t_piece;
								p_list->size++;
							}
						}
						// checks for possible en passant move right and left
						if (position->board[rank][file + 1]->enpass == true)
						{
							if ((file + 1) <= 7 && (rank - 1) >= 0)
							{
								if (position->board[rank - 1][file + 1]->player == EMPTY_Player)
								{
									p_list->moveList[p_list->size].location_src->rank = rank;
									p_list->moveList[p_list->size].location_src->file = file;
									p_list->moveList[p_list->size].location_dest->rank = rank - 1;
									p_list->moveList[p_list->size].location_dest->file = file + 1;
									p_list->moveList[p_list->size].captured_piece->player = WHITE;
									p_list->moveList[p_list->size].captured_piece->t_piece = position->board[rank][file + 1]->t_piece;
									p_list->size++;
								}
							}
						}
						if (position->board[rank][file - 1]->enpass == true)
						{
							if ((file - 1) >= 0 && (rank - 1) >= 0)
							{
								if (position->board[rank - 1][file - 1]->player == EMPTY_Player)
								{
									p_list->moveList[p_list->size].location_src->rank = rank;
									p_list->moveList[p_list->size].location_src->file = file;
									p_list->moveList[p_list->size].location_dest->rank = rank - 1;
									p_list->moveList[p_list->size].location_dest->file = file - 1;
									p_list->moveList[p_list->size].captured_piece->player = WHITE;
									p_list->moveList[p_list->size].captured_piece->t_piece = position->board[rank][file - 1]->t_piece;
									p_list->size++;
								}
							}
						}
					}
					// possible moves for black rook
					if (piece->t_piece == ROOK)
					{
						for (dir = 0; dir < 4; dir++)
						{
							movecount = straight_moves_count(position, dir, rank, file);
							for (c = 1; c <= movecount; c++)
							{
								p_list->moveList[p_list->size].location_src->rank = rank;
								p_list->moveList[p_list->size].location_src->file = file;

								switch (dir)
								{
								case 0:
									p_list->moveList[p_list->size].location_dest->rank = rank - c;
									p_list->moveList[p_list->size].location_dest->file = file;
									break;
								case 1:
									p_list->moveList[p_list->size].location_dest->rank = rank + c;
									p_list->moveList[p_list->size].location_dest->file = file;
									break;
								case 2:
									p_list->moveList[p_list->size].location_dest->rank = rank;
									p_list->moveList[p_list->size].location_dest->file = file - c;
									break;
								case 3:
									p_list->moveList[p_list->size].location_dest->rank = rank;
									p_list->moveList[p_list->size].location_dest->file = file + c;
									break;
								}

								p_list->size++;
							}
							if ((rank - (movecount + 1)) >= 0)
							{ // Finds black rook forward attack move
								if (position->board[rank - (movecount + 1)][file]->player == WHITE)
								{
									p_list->moveList[p_list->size].location_src->rank = rank;
									p_list->moveList[p_list->size].location_src->file = file;
									p_list->moveList[p_list->size].location_dest->rank = rank - (movecount + 1);
									p_list->moveList[p_list->size].location_dest->file = file;
									p_list->moveList[p_list->size].captured_piece->player = WHITE;
									p_list->moveList[p_list->size].captured_piece->t_piece = position->board[rank - (movecount + 1)][file]->t_piece;
									p_list->size++;
								}
							}
							if ((rank + (movecount + 1)) < 8)
							{ // Finds black rook backward attack move
								if (position->board[rank + (movecount + 1)][file]->player == WHITE)
								{
									p_list->moveList[p_list->size].location_src->rank = rank;
									p_list->moveList[p_list->size].location_src->file = file;
									p_list->moveList[p_list->size].location_dest->rank = rank + (movecount + 1);
									p_list->moveList[p_list->size].location_dest->file = file;
									p_list->moveList[p_list->size].captured_piece->player = WHITE;
									p_list->moveList[p_list->size].captured_piece->t_piece = position->board[rank + (movecount + 1)][file]->t_piece;
									p_list->size++;
								}
							}
							if ((file - (movecount + 1)) >= 0)
							{ // Finds black rook left attack move
								if (position->board[rank][file - (movecount + 1)]->player == WHITE)
								{
									p_list->moveList[p_list->size].location_src->rank = rank;
									p_list->moveList[p_list->size].location_src->file = file;
									p_list->moveList[p_list->size].location_dest->rank = rank;
									p_list->moveList[p_list->size].location_dest->file = file - (movecount + 1);
									p_list->moveList[p_list->size].captured_piece->player = WHITE;
									p_list->moveList[p_list->size].captured_piece->t_piece = position->board[rank][file - (movecount + 1)]->t_piece;
									p_list->size++;
								}
							}
							if ((file + (movecount + 1)) < 8)
							{ // Finds black rook right attack move
								if (position->board[rank][file + (movecount + 1)]->player == WHITE)
								{
									p_list->moveList[p_list->size].location_src->rank = rank;
									p_list->moveList[p_list->size].location_src->file = file;
									p_list->moveList[p_list->size].location_dest->rank = rank;
									p_list->moveList[p_list->size].location_dest->file = file + (movecount + 1);
									p_list->moveList[p_list->size].captured_piece->player = WHITE;
									p_list->moveList[p_list->size].captured_piece->t_piece = position->board[rank][file + (movecount + 1)]->t_piece;
									p_list->size++;
								}
							}
						}
					}
					// possible black bishop moves
					if (piece->t_piece == BISHOP)
					{
						movecount = 0;

						// Checking all possible diagonal moves in the four diagonal directions: top-left, top-right, bottom-left, bottom-right
						for (i = -1; i <= 1; i += 2)
						{ // i = -1 for top directions, i = 1 for bottom directions
							for (j = -1; j <= 1; j += 2)
							{ // j = -1 for left directions, j = 1 for right directions
								r = rank + i;
								f = file + j;
								while (r >= 0 && r < 8 && f >= 0 && f < 8)
								{ // Continue moving diagonally until the edge of the board is reached
									if (position->board[r][f]->player == EMPTY_Player)
									{ // If the square is empty
										// Add the move to the list of legal moves
										p_list->moveList[p_list->size].location_src->rank = rank;
										p_list->moveList[p_list->size].location_src->file = file;
										p_list->moveList[p_list->size].location_dest->rank = r;
										p_list->moveList[p_list->size].location_dest->file = f;
										p_list->size++;
									}
									else
									{
										// If there is a piece on the square, check if it's an opponent's piece and add the move if it is
										if (position->board[r][f]->player == WHITE)
										{
											p_list->moveList[p_list->size].location_src->rank = rank;
											p_list->moveList[p_list->size].location_src->file = file;
											p_list->moveList[p_list->size].location_dest->rank = r;
											p_list->moveList[p_list->size].location_dest->file = f;
											p_list->moveList[p_list->size].captured_piece->player = WHITE;
											p_list->moveList[p_list->size].captured_piece->t_piece = position->board[r][f]->t_piece;
											p_list->size++;
										}
										// Stop checking further in this direction since the bishop can't move through pieces
										break;
									}
									r += i;
									f += j;
								}
							}
						}
					}
					// possible black knight moves
					if (piece->t_piece == KNIGHT)
					{
						movecount = 0;
						// All possible knight moves from the current position
						for (i = 0; i < 8; i++)
						{
							r = rank + knight_moves[i][0];
							f = file + knight_moves[i][1];

							// Check if the move is within the board boundaries
							if (r >= 0 && r < 8 && f >= 0 && f < 8)
							{
								if (position->board[r][f]->player == EMPTY_Player)
								{ // If the square is empty
									// Add the move to the list of legal moves
									p_list->moveList[p_list->size].location_src->rank = rank;
									p_list->moveList[p_list->size].location_src->file = file;
									p_list->moveList[p_list->size].location_dest->rank = r;
									p_list->moveList[p_list->size].location_dest->file = f;
									p_list->size++;
								}
								else
								{
									// If there is a piece on the square, check if it's an opponent's piece and add the move if it is
									if (position->board[r][f]->player == WHITE)
									{
										p_list->moveList[p_list->size].location_src->rank = rank;
										p_list->moveList[p_list->size].location_src->file = file;
										p_list->moveList[p_list->size].location_dest->rank = r;
										p_list->moveList[p_list->size].location_dest->file = f;
										p_list->moveList[p_list->size].captured_piece->player = WHITE;
										p_list->moveList[p_list->size].captured_piece->t_piece = position->board[r][f]->t_piece;
										p_list->size++;
									}
								}
							}
						}
					}
					// possible black queen moves
					if (piece->t_piece == QUEEN)
					{
						// checking straight moves
						for (dir = 0; dir < 4; dir++)
						{
							movecount = straight_moves_count(position, dir, rank, file);
							for (c = 1; c <= movecount; c++)
							{
								p_list->moveList[p_list->size].location_src->rank = rank;
								p_list->moveList[p_list->size].location_src->file = file;

								switch (dir)
								{
								case 0:
									p_list->moveList[p_list->size].location_dest->rank = rank - c;
									p_list->moveList[p_list->size].location_dest->file = file;
									break;
								case 1:
									p_list->moveList[p_list->size].location_dest->rank = rank + c;
									p_list->moveList[p_list->size].location_dest->file = file;
									break;
								case 2:
									p_list->moveList[p_list->size].location_dest->rank = rank;
									p_list->moveList[p_list->size].location_dest->file = file - c;
									break;
								case 3:
									p_list->moveList[p_list->size].location_dest->rank = rank;
									p_list->moveList[p_list->size].location_dest->file = file + c;
									break;
								}

								p_list->size++;
							}
							if ((rank - (movecount + 1)) >= 0)
							{ // Finds black rook forward attack move
								if (position->board[rank - (movecount + 1)][file]->player == WHITE)
								{
									p_list->moveList[p_list->size].location_src->rank = rank;
									p_list->moveList[p_list->size].location_src->file = file;
									p_list->moveList[p_list->size].location_dest->rank = rank - (movecount + 1);
									p_list->moveList[p_list->size].location_dest->file = file;
									p_list->moveList[p_list->size].captured_piece->player = WHITE;
									p_list->moveList[p_list->size].captured_piece->t_piece = position->board[rank - (movecount + 1)][file]->t_piece;
									p_list->size++;
								}
							}
							if ((rank + (movecount + 1)) < 8)
							{ // Finds black rook backward attack move
								if (position->board[rank + (movecount + 1)][file]->player == WHITE)
								{
									p_list->moveList[p_list->size].location_src->rank = rank;
									p_list->moveList[p_list->size].location_src->file = file;
									p_list->moveList[p_list->size].location_dest->rank = rank + (movecount + 1);
									p_list->moveList[p_list->size].location_dest->file = file;
									p_list->moveList[p_list->size].captured_piece->player = WHITE;
									p_list->moveList[p_list->size].captured_piece->t_piece = position->board[rank + (movecount + 1)][file]->t_piece;
									p_list->size++;
								}
							}
							if ((file - (movecount + 1)) >= 0)
							{ // Finds black rook left attack move
								if (position->board[rank][file - (movecount + 1)]->player == WHITE)
								{
									p_list->moveList[p_list->size].location_src->rank = rank;
									p_list->moveList[p_list->size].location_src->file = file;
									p_list->moveList[p_list->size].location_dest->rank = rank;
									p_list->moveList[p_list->size].location_dest->file = file - (movecount + 1);
									p_list->moveList[p_list->size].captured_piece->player = WHITE;
									p_list->moveList[p_list->size].captured_piece->t_piece = position->board[rank][file - (movecount + 1)]->t_piece;
									p_list->size++;
								}
							}
							if ((file + (movecount + 1)) < 8)
							{ // Finds white rook right attack move
								if (position->board[rank][file + (movecount + 1)]->player == WHITE)
								{
									p_list->moveList[p_list->size].location_src->rank = rank;
									p_list->moveList[p_list->size].location_src->file = file;
									p_list->moveList[p_list->size].location_dest->rank = rank;
									p_list->moveList[p_list->size].location_dest->file = file + (movecount + 1);
									p_list->moveList[p_list->size].captured_piece->player = WHITE;
									p_list->moveList[p_list->size].captured_piece->t_piece = position->board[rank][file + (movecount + 1)]->t_piece;
									p_list->size++;
								}
							}
						}
						movecount = 0;
						// Checking all possible diagonal moves in the four diagonal directions: top-left, top-right, bottom-left, bottom-right
						for (i = -1; i <= 1; i += 2)
						{ // i = -1 for top directions, i = 1 for bottom directions
							for (j = -1; j <= 1; j += 2)
							{ // j = -1 for left directions, j = 1 for right directions
								r = rank + i;
								f = file + j;
								while (r >= 0 && r < 8 && f >= 0 && f < 8)
								{ // Continue moving diagonally until the edge of the board is reached
									if (position->board[r][f]->player == EMPTY_Player)
									{ // If the square is empty
										// Add the move to the list of legal moves
										p_list->moveList[p_list->size].location_src->rank = rank;
										p_list->moveList[p_list->size].location_src->file = file;
										p_list->moveList[p_list->size].location_dest->rank = r;
										p_list->moveList[p_list->size].location_dest->file = f;
										p_list->size++;
									}
									else
									{
										// If there is a piece on the square, check if it's an opponent's piece and add the move if it is
										if (position->board[r][f]->player == WHITE)
										{
											p_list->moveList[p_list->size].location_src->rank = rank;
											p_list->moveList[p_list->size].location_src->file = file;
											p_list->moveList[p_list->size].location_dest->rank = r;
											p_list->moveList[p_list->size].location_dest->file = f;
											p_list->moveList[p_list->size].captured_piece->player = WHITE;
											p_list->moveList[p_list->size].captured_piece->t_piece = position->board[r][f]->t_piece;
											p_list->size++;
										}
										// Stop checking further in this direction since the bishop can't move through pieces
										break;
									}
									r += i;
									f += j;
								}
							}
						}
					}
					// possible black king moves
					if (piece->t_piece == KING)
					{
						// All possible king moves from the current position
						for (dr = -1; dr <= 1; dr++)
						{
							for (df = -1; df <= 1; df++)
							{
								// Skip the current position (no move)
								if (dr == 0 && df == 0)
									continue;

								r = rank + dr;
								f = file + df;
								// Check if the move is within the board boundaries
								if (r >= 0 && r < 8 && f >= 0 && f < 8)
								{
									if (position->board[r][f]->player == EMPTY_Player)
									{ // If the square is empty
										p_list->moveList[p_list->size].location_src->rank = rank;
										p_list->moveList[p_list->size].location_src->file = file;
										p_list->moveList[p_list->size].location_dest->rank = r;
										p_list->moveList[p_list->size].location_dest->file = f;
										p_list->size++;
									}
									if (position->board[r][f]->player == WHITE)
									{ // If the square contains opponents piece
										p_list->moveList[p_list->size].location_src->rank = rank;
										p_list->moveList[p_list->size].location_src->file = file;
										p_list->moveList[p_list->size].location_dest->rank = r;
										p_list->moveList[p_list->size].location_dest->file = f;
										p_list->moveList[p_list->size].captured_piece->player = WHITE;
										p_list->moveList[p_list->size].captured_piece->t_piece = position->board[r][f]->t_piece;
										p_list->size++;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	// position->board[0][0]->player = EMPTY;
	// p_list->moveList[p_list->size].location_src->rank = EMPTY;
}
#include "structures.h"

// takes in int rank and file from 0-7
bool isLegal(struct Move* move, struct Moves *moves)
{
	int srcrank=move->location_src->rank;
	int srcfile = move->location_src->file;
	int destrank=move->location_dest->rank;
	int destfile=move->location_dest->file;
	for (int i = 0; i < moves->size; i++)
	{
		if (moves->moveList[i].location_src->rank == srcrank &&
			moves->moveList[i].location_src->file == srcfile &&
			moves->moveList[i].location_dest->rank == destrank &&
			moves->moveList[i].location_dest->file == destfile)
		{
			return true;
		}
	}
	return false;
}