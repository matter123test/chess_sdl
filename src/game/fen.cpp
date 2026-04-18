#include "fen.h"
#include <optional>

enum class FENType {
	NUMBER,
	PIECE,
	SEPERATOR
};

FENType GetFENType(const char c) {
	if (c == '/') {
		return FENType::SEPERATOR;
	}
	else if (isdigit(c)) {
		return FENType::NUMBER;
	}
	else {
		return FENType::PIECE;
	}
}

ChessPiece GetChessPieceFromChar(const char c) {
	switch (c) {
	case 'r':
		return ChessPiece::B_ROOK;
		break;
	case 'n':
		return ChessPiece::B_KNIGHT;
		break;
	case 'b':
		return ChessPiece::B_BISHOP;
		break;
	case 'q':
		return ChessPiece::B_QUEEN;
		break;
	case 'p':
		return ChessPiece::B_PAWN;
		break;
	case 'k':
		return ChessPiece::B_KING;
		break;

	case 'R':
		return ChessPiece::W_ROOK;
		break;
	case 'N':
		return ChessPiece::W_KNIGHT;
		break;
	case 'B':
		return ChessPiece::W_BISHOP;
		break;
	case 'Q':
		return ChessPiece::W_QUEEN;
		break;
	case 'P':
		return ChessPiece::W_PAWN;
		break;
	case 'K':
		return ChessPiece::W_KING;
		break;

	default:
		return ChessPiece::EMPTY;
	}
}

std::optional<char> GetCharFromChessPiece(const ChessPiece& piece) {
	switch (piece) {
	case ChessPiece::B_ROOK:
		return 'r';
	case ChessPiece::B_KNIGHT:
		return 'n';
	case ChessPiece::B_BISHOP:
		return 'b';
	case ChessPiece::B_QUEEN:
		return 'q';
	case ChessPiece::B_PAWN:
		return 'p';
	case ChessPiece::B_KING:
		return 'k';

	case ChessPiece::W_ROOK:
		return 'R';
	case ChessPiece::W_KNIGHT:
		return 'N';
	case ChessPiece::W_BISHOP:
		return 'B';
	case ChessPiece::W_QUEEN:
		return 'Q';
	case ChessPiece::W_PAWN:
		return 'P';
	case ChessPiece::W_KING:
		return 'K';

	default:
		return std::nullopt;
	}
}


void FENToBoard(const std::string& FEN_string, ChessBoard& board)
{
	int x = 0; int y = 0;

	for (const char c : FEN_string) {

		FENType type = GetFENType(c);

		if (type == FENType::PIECE) {
			board[y][x] = GetChessPieceFromChar(c);
			x++;
		}
		else if (type == FENType::SEPERATOR) {
			x = 0;
			y++;
		}
		else if (type == FENType::NUMBER) {
			int jumps = c - '0';
			for (int jump = 0; jump < jumps; jump++) {
				x++;
			}
		}
	}
}

std::string BoardToFEN(ChessBoard& board)
{
	// TODO: implement
	return std::string();
}

void ClearBoard(ChessBoard& board)
{
	for (auto& row : board) for (ChessPiece& piece : row) piece = ChessPiece::EMPTY;
}

void ResetBoard(ChessBoard& board)
{
	ClearBoard(board);
	FENToBoard(STARTING_POS_STR, board);
}
