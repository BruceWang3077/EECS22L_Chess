#include "structures.h"


void gentlemoves(int srcrank, int srcfile, int destrank, int destfile, struct Moves *p_list)
{
	p_list->moveList[p_list->size].location_src->rank = srcrank;
	p_list->moveList[p_list->size].location_src->file = srcfile;
	p_list->moveList[p_list->size].location_dest->rank = destrank;
	p_list->moveList[p_list->size].location_dest->file = destfile;
	p_list->size++;
}

void attackmoves(int srcrank, int srcfile, int destrank, int destfile, struct Moves *p_list, struct Board *position)
{
	p_list->moveList[p_list->size].location_src->rank = srcrank;
	p_list->moveList[p_list->size].location_src->file = srcfile;
	p_list->moveList[p_list->size].location_dest->rank = destrank;
	p_list->moveList[p_list->size].location_dest->file = destfile;
	p_list->moveList[p_list->size].captured_piece->player = position->board[destrank][destfile]->player;
	p_list->moveList[p_list->size].captured_piece->t_piece = position->board[destrank][destfile]->t_piece;
	p_list->size++;
}

void castlingmoves(int srcrank, int srcfile, int destrank, int destfile, struct Moves *p_list, struct Board *position)
{
	p_list->moveList[p_list->size].location_src->rank = srcrank;
	p_list->moveList[p_list->size].location_src->file = srcfile;
	p_list->moveList[p_list->size].location_dest->rank = destrank;
	p_list->moveList[p_list->size].location_dest->file = destfile;
	p_list->moveList[p_list->size].castling = true;
	p_list->size++;
}

void generatemoves(struct Board *position, struct Moves *p_list, enum Player playerturn)
{

	p_list->size = 0;
	int movecount = 0;
	int i;
	int j;
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
								gentlemoves(rank, file, rank + 1, file, p_list);
								// for white pawn moving up twice, checks if second square is also empty
								if (piece->moved == false && (rank + 2) < 8)
								{
									if (position->board[rank + 2][file]->player == EMPTY_Player)
									{
										gentlemoves(rank, file, rank + 2, file, p_list);
									}
								}
							}
						}
						// for white pawn right diagonal capture move, also check is move is on board
						if ((file + 1) < 8 && (rank + 1) < 8)
						{
							if (position->board[rank + 1][file + 1]->player == BLACK)
							{
								attackmoves(rank, file, rank + 1, file + 1, p_list, position);
							}
						}
						// for white pawn left diagonal capture move, also check is move is on board
						if ((file - 1) >= 0 && (rank + 1) < 8)
						{
							if (position->board[rank + 1][file - 1]->player == BLACK)
							{
								attackmoves(rank, file, rank + 1, file - 1, p_list, position);
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

						// Checking all possible horizontal and vertical moves in the four directions: up, down, left, and right
						for (i = -1; i <= 1; i++)
						{ // i = -1 for up direction, i = 1 for down direction, i = 0 for horizontal direction
							for (j = -1; j <= 1; j++)
							{ // j = -1 for left direction, j = 1 for right direction, j = 0 for vertical direction
								if ((i != 0 && j != 0) || (i == 0 && j == 0))
								{ // Skip diagonal moves and the current position
									continue;
								}
								r = rank + i;
								f = file + j;
								while (r >= 0 && r < 8 && f >= 0 && f < 8)
								{ // Continue moving horizontally or vertically until the edge of the board is reached
									if (position->board[r][f]->player == EMPTY_Player)
									{ // If the square is empty
										// Add the move to the list of legal moves
										gentlemoves(rank, file, r, f, p_list);
									}
									else
									{
										// If there is a piece on the square, check if it's an opponent's piece and add the move if it is
										if (position->board[r][f]->player == BLACK)
										{
											attackmoves(rank, file, r, f, p_list, position);
										}
										// Stop checking further in this direction since the rook can't move through pieces
										break;
									}
									r += i;
									f += j;
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
										gentlemoves(rank, file, r, f, p_list);
									}
									else
									{
										// If there is a piece on the square, check if it's an opponent's piece and add the move if it is
										if (position->board[r][f]->player == BLACK)
										{
											attackmoves(rank, file, r, f, p_list, position);
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
									gentlemoves(rank, file, r, f, p_list);
								}
								else
								{
									// If there is a piece on the square, check if it's an opponent's piece and add the move if it is
									if (position->board[r][f]->player == BLACK)
									{
										attackmoves(rank, file, r, f, p_list, position);
									}
								}
							}
						}
					}
					// possible white queen moves
					if (piece->t_piece == QUEEN)
					{
						// Checking all possible horizontal and vertical moves in the four directions: up, down, left, and right
						for (i = -1; i <= 1; i++)
						{ // i = -1 for up direction, i = 1 for down direction, i = 0 for horizontal direction
							for (j = -1; j <= 1; j++)
							{ // j = -1 for left direction, j = 1 for right direction, j = 0 for vertical direction
								if ((i != 0 && j != 0) || (i == 0 && j == 0))
								{ // Skip diagonal moves and the current position
									continue;
								}
								r = rank + i;
								f = file + j;
								while (r >= 0 && r < 8 && f >= 0 && f < 8)
								{ // Continue moving horizontally or vertically until the edge of the board is reached
									if (position->board[r][f]->player == EMPTY_Player)
									{ // If the square is empty
										// Add the move to the list of legal moves
										gentlemoves(rank, file, r, f, p_list);
									}
									else
									{
										// If there is a piece on the square, check if it's an opponent's piece and add the move if it is
										if (position->board[r][f]->player == BLACK)
										{
											attackmoves(rank, file, r, f, p_list, position);
										}
										// Stop checking further in this direction since the rook can't move through pieces
										break;
									}
									r += i;
									f += j;
								}
							}
						}

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
										gentlemoves(rank, file, r, f, p_list);
									}
									else
									{
										// If there is a piece on the square, check if it's an opponent's piece and add the move if it is
										if (position->board[r][f]->player == BLACK)
										{
											attackmoves(rank, file, r, f, p_list, position);
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
										gentlemoves(rank, file, r, f, p_list);
									}
									if (position->board[r][f]->player == BLACK)
									{ // If the square contains opponents piece
										attackmoves(rank, file, r, f, p_list, position);
									}
								}
							}
						}
						if (piece->moved == false)
						{ // white castling right
							if ((position->board[rank][file + 2]->player == EMPTY_Player) && (position->board[rank][file + 1]->player == EMPTY_Player))
							{
								if ((position->board[rank][file + 3]->player != EMPTY_Player) && (position->board[rank][file + 3]->moved == false))
								{
									castlingmoves(rank, file, rank, file + 2, p_list, position);
								}
							} // white castling left
							if ((position->board[rank][file - 1]->player == EMPTY_Player) && (position->board[rank][file - 2]->player == EMPTY_Player))
							{
								if ((position->board[rank][file - 3]->player == EMPTY_Player) && position->board[rank][file - 4]->player != EMPTY_Player)
								{
									if (position->board[rank][file - 4]->moved == false)
									{
										castlingmoves(rank, file, rank, file - 2, p_list, position);
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
								gentlemoves(rank, file, rank - 1, file, p_list);
								// for black pawn moving down twice, checks if second square is also empty
								if (piece->moved == false && (rank - 2) >= 0)
								{
									if (position->board[rank - 2][file]->player == EMPTY_Player)
									{
										gentlemoves(rank, file, rank - 2, file, p_list);
									}
								}
							}
						}
						// for black pawn right diagonal capture move, also check if move is on board
						if ((file + 1) <= 7 && (rank - 1) >= 0)
						{
							if (position->board[rank - 1][file + 1]->player == WHITE)
							{
								attackmoves(rank, file, rank - 1, file + 1, p_list, position);
							}
						}
						// for black pawn left diagonal capture move, also check if move is on board
						if ((file - 1) >= 0 && (rank - 1) >= 0)
						{
							if (position->board[rank - 1][file - 1]->player == WHITE)
							{
								attackmoves(rank, file, rank - 1, file - 1, p_list, position);
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
						movecount = 0;

						// Checking all possible horizontal and vertical moves in the four directions: up, down, left, and right
						for (i = -1; i <= 1; i++)
						{ // i = -1 for up direction, i = 1 for down direction, i = 0 for horizontal direction
							for (j = -1; j <= 1; j++)
							{ // j = -1 for left direction, j = 1 for right direction, j = 0 for vertical direction
								if ((i != 0 && j != 0) || (i == 0 && j == 0))
								{ // Skip diagonal moves and the current position
									continue;
								}
								r = rank + i;
								f = file + j;
								while (r >= 0 && r < 8 && f >= 0 && f < 8)
								{ // Continue moving horizontally or vertically until the edge of the board is reached
									if (position->board[r][f]->player == EMPTY_Player)
									{ // If the square is empty
										// Add the move to the list of legal moves
										gentlemoves(rank, file, r, f, p_list);
									}
									else
									{
										// If there is a piece on the square, check if it's an opponent's piece and add the move if it is
										if (position->board[r][f]->player == WHITE)
										{
											attackmoves(rank, file, r, f, p_list, position);
										}
										// Stop checking further in this direction since the rook can't move through pieces
										break;
									}
									r += i;
									f += j;
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
										gentlemoves(rank, file, r, f, p_list);
									}
									else
									{
										// If there is a piece on the square, check if it's an opponent's piece and add the move if it is
										if (position->board[r][f]->player == WHITE)
										{
											attackmoves(rank, file, r, f, p_list, position);
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
									gentlemoves(rank, file, r, f, p_list);
								}
								else
								{
									// If there is a piece on the square, check if it's an opponent's piece and add the move if it is
									if (position->board[r][f]->player == WHITE)
									{
										attackmoves(rank, file, r, f, p_list, position);
									}
								}
							}
						}
					}
					// possible black queen moves
					if (piece->t_piece == QUEEN)
					{
						// Checking all possible horizontal and vertical moves in the four directions: up, down, left, and right
						for (i = -1; i <= 1; i++)
						{ // i = -1 for up direction, i = 1 for down direction, i = 0 for horizontal direction
							for (j = -1; j <= 1; j++)
							{ // j = -1 for left direction, j = 1 for right direction, j = 0 for vertical direction
								if ((i != 0 && j != 0) || (i == 0 && j == 0))
								{ // Skip diagonal moves and the current position
									continue;
								}
								r = rank + i;
								f = file + j;
								while (r >= 0 && r < 8 && f >= 0 && f < 8)
								{ // Continue moving horizontally or vertically until the edge of the board is reached
									if (position->board[r][f]->player == EMPTY_Player)
									{ // If the square is empty
										// Add the move to the list of legal moves
										gentlemoves(rank, file, r, f, p_list);
									}
									else
									{
										// If there is a piece on the square, check if it's an opponent's piece and add the move if it is
										if (position->board[r][f]->player == WHITE)
										{
											attackmoves(rank, file, r, f, p_list, position);
										}
										// Stop checking further in this direction since the rook can't move through pieces
										break;
									}
									r += i;
									f += j;
								}
							}
						}
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
										gentlemoves(rank, file, r, f, p_list);
									}
									else
									{
										// If there is a piece on the square, check if it's an opponent's piece and add the move if it is
										if (position->board[r][f]->player == WHITE)
										{
											attackmoves(rank, file, r, f, p_list, position);
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
										gentlemoves(rank, file, r, f, p_list);
									}
									if (position->board[r][f]->player == WHITE)
									{ // If the square contains opponents piece
										attackmoves(rank, file, r, f, p_list, position);
									}
								}
							}
						}
						if (piece->moved == false)
						{ // black castling right
							if ((rank >= 0) && (rank < 8) && ((file - 4) >= 0) && ((file + 3) < 8))
							{
								if ((position->board[rank][file + 2]->player == EMPTY_Player) && (position->board[rank][file + 1]->player == EMPTY_Player))
								{
									if ((position->board[rank][file + 3]->player != EMPTY_Player) && (position->board[rank][file + 3]->moved == false))
									{
										castlingmoves(rank, file, rank, file + 2, p_list, position);
									}
								} // black castling left
								if ((position->board[rank][file - 1]->player == EMPTY_Player) && (position->board[rank][file - 2]->player == EMPTY_Player))
								{
									if ((position->board[rank][file - 3]->player == EMPTY_Player) && position->board[rank][file - 4]->player != EMPTY_Player)
									{
										if (position->board[rank][file - 4]->moved == false)
										{
											castlingmoves(rank, file, rank, file - 2, p_list, position);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

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