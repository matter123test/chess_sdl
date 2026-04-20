#include "moves.h"

const std::array<Move, 2> W_PAWN_MOVES = {
	Move{-1, -1}, // Top left
	Move{ 1, -1}  // Top right
};

const std::array<Move, 2> B_PAWN_MOVES = {
	Move{-1, 1}, // Bottom left
	Move{ 1, 1}  // Bottom right
};

const std::array<Move, 8> KING_MOVES = {
	Move{-1, -1}, // Top left
	Move{ 0, -1}, // Top center
	Move{ 1, -1}, // Top right
	Move{-1,  0}, // Middle left
	//Move{ 0,  0}, // Middle
	Move{ 1,  0}, // Middle right
	Move{-1,  1}, // Bottom left
	Move{ 0,  1}, // Bottom center
	Move{ 1,  1}, // Bttom right

};

const std::array<Move, 8> KNIGHT_MOVES = {
	// Top
	Move{-1, -2},
	Move{ 1, -2},

	// Bottom
	Move{-1,  2},
	Move{ 1,  2},

	// Left
	Move{-2, -1},
	Move{-2,  1},

	// Right
	Move{ 2, -1},
	Move{ 2,  1}
};

template<size_t N>
void AddToMoves(std::vector<Move>& moves, std::array<Move, N> moveset) {
	for (auto& m : moveset) moves.push_back(m);
}
void AddToMoves(std::vector<Move>& moves, std::vector<Move> moveset) {
	for (auto& m : moveset) moves.push_back(m);
}

static void CreateMovesFromDir(const int& dir_x, const int& dir_y, std::vector<Move>& moves) {
	int t_x = 0;
	int t_y = 0;

	for (int i = 0; i < 8; i++) {
		t_x += dir_x;
		t_y += dir_y;
		moves.emplace_back(t_x, t_y);
	}
}

std::vector<Move> GetBishopMoves() {
	std::vector<Move> moves{};

	CreateMovesFromDir(-1, -1, moves); // Top left
	CreateMovesFromDir( 1, -1, moves); // Top right
	CreateMovesFromDir(-1,  1, moves); // Bottom left
	CreateMovesFromDir( 1,  1, moves); // Bottom right

	return moves;
}

std::vector<Move> GetRookMoves() {
	std::vector<Move> moves{};

	CreateMovesFromDir( 0,  1, moves); // Top
	CreateMovesFromDir( 0, -1, moves); // Bottom
	CreateMovesFromDir( 1,  0, moves); // Left 
	CreateMovesFromDir(-1,  0, moves); // Right

	return moves;
}

std::vector<Move> GetQueenMoves() {
	auto bishop_moves = GetBishopMoves();
	auto rook_moves = GetRookMoves();

	std::vector<Move> moves{};
	moves.reserve(bishop_moves.size() + rook_moves.size() + KING_MOVES.size());

	for (const auto& move : bishop_moves) {
		moves.push_back(move);
	}

	for (const auto& move : rook_moves) {
		moves.push_back(move);
	}

	for (const auto& move : KING_MOVES) {
		moves.push_back(move);
	}

	return moves;
}

std::vector<Move> GetMovesForPiece(const ChessPiece& piece)
{
	std::vector<Move> moves{};

	switch (piece) {
	case W_PAWN:
		AddToMoves(moves, W_PAWN_MOVES);
		break;
	case B_PAWN:
		AddToMoves(moves, B_PAWN_MOVES);
		break;
	case W_KING: case B_KING:
		AddToMoves(moves, KING_MOVES);
		break;
	case W_KNIGHT: case B_KNIGHT:
		AddToMoves(moves, KNIGHT_MOVES);
		break;
	case W_BISHOP: case B_BISHOP:
		AddToMoves(moves, GetBishopMoves());
		break;
	case W_ROOK: case B_ROOK:
		AddToMoves(moves, GetRookMoves());
		break;
	case W_QUEEN: case B_QUEEN:
		AddToMoves(moves, GetQueenMoves());
		break;
	default:
		break;
	}

	return moves;
}
