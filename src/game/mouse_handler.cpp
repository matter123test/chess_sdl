#include "mouse_handler.h"
#include "moves.h"

bool is_piece_being_dragged = false;
SDL_Texture* selected_piece_tex = nullptr;
ChessPiece selected_piece = EMPTY;
float m_x, m_y;
bool left_held = false;
bool right_held = false;
int old_x, old_y;
int board_x, board_y;

SDL_Texture* GetTextureFromPiece(TextureArray& textures, ChessPiece& piece)
{
	int index = static_cast<int>(piece) - 1;
	return textures[index];
}

bool IsInBounds(int x, int y) {
	return (x >= 0 && x < 8 && y >= 0 && y < 8);
};

void MouseHandler::Handle(TextureArray& textures, ChessBoard& board, int& cell_size) {
	Uint32 buttons = SDL_GetMouseState(&m_x, &m_y);
	left_held = (buttons & SDL_BUTTON_LMASK);
	right_held = (buttons & SDL_BUTTON_RMASK);

	auto reset_selected_piece_to_old_pos = [&]() {
		board[old_y][old_x] = selected_piece;

		// Reset selected piece data
		selected_piece_tex = nullptr;
		is_piece_being_dragged = false;
		};

	auto calc_piece_positions = [&]() {
		board_x = m_x / cell_size;
		board_y = m_y / cell_size;
	};

	if (left_held && !is_piece_being_dragged) {
		calc_piece_positions();

		if (!IsInBounds(board_x, board_y)) return;

		selected_piece = board[board_y][board_x];
		if (selected_piece == EMPTY) return;

		old_x = board_x;
		old_y = board_y;

		// Get piece texture
		selected_piece_tex = GetTextureFromPiece(textures, board[board_y][board_x]);
		is_piece_being_dragged = true;

		// Remove the selected texture piece from the board
		board[board_y][board_x] = EMPTY;
	}
	else if (!left_held && is_piece_being_dragged) {
		calc_piece_positions();

		if (!IsInBounds(board_x, board_y)) {
			reset_selected_piece_to_old_pos();
			return;
		};

		// Check the if the selected piece is colliding
		ChessPiece piece = board[board_y][board_x];
		if (piece != EMPTY) {
			reset_selected_piece_to_old_pos();
			return;
		}

		board[board_y][board_x] = selected_piece;

		// Reset selected piece data
		selected_piece_tex = nullptr;
		is_piece_being_dragged = false;
		selected_piece = EMPTY;
	}
	else if (right_held && !is_piece_being_dragged) {
		calc_piece_positions();

		if (!IsInBounds(board_x, board_y)) return;

		board[board_y][board_x] = EMPTY;
	}
}

static void RenderMoves(SDL_Renderer* renderer, std::vector<Move>& moves, int& cell_size, int* color_c) {
	for (auto& m : moves) {
		SDL_SetRenderDrawColor(renderer, color_c[0], color_c[1], color_c[2], 255);
		int n_x = (old_x + m.x);
		int n_y = (old_y + m.y);
		
		if (!IsInBounds(n_x, n_y)) continue;

		const SDL_FRect rec = { 
			n_x * cell_size, 
			n_y * cell_size, 
			cell_size, cell_size };

		SDL_RenderFillRect(renderer, &rec);
	}
}

void MouseHandler::Render(SDL_Renderer* renderer, int& cell_size, const bool &show_moves, ChessBoard& board, int* color_c) {
	if (show_moves) {
		auto moves = GetMovesForPiece(selected_piece);
		RenderMoves(renderer, moves, cell_size, color_c);
	}
}

void MouseHandler::RenderSelectedPiece(SDL_Renderer* renderer, int& cell_size)
{
	if (is_piece_being_dragged && selected_piece_tex != nullptr) {
		const SDL_FRect dest = { m_x - cell_size / 2, m_y - cell_size / 2, cell_size, cell_size };
		SDL_RenderTexture(renderer, selected_piece_tex, NULL, &dest);
	}
}
