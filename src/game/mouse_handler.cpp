#include "mouse_handler.h"

bool is_piece_being_dragged = false;
SDL_Texture* selected_piece_tex = nullptr;
ChessPiece selected_piece = EMPTY;
float m_x, m_y;
bool left_held = false;
bool right_held = false;
int old_x, old_y;

SDL_Texture* GetTextureFromPiece(TextureArray& textures, ChessPiece& piece)
{
	int index = static_cast<int>(piece) - 1;
	return textures[index];
}

void MouseHandler::Handle(TextureArray& textures, ChessBoard &board, int cell_size) {

	Uint32 buttons = SDL_GetMouseState(&m_x, &m_y);
	left_held = (buttons & SDL_BUTTON_LMASK);
	right_held = (buttons & SDL_BUTTON_RMASK);

	auto is_in_bounds = [](int x, int y) {
		return (x >= 0 && x < 8 && y >= 0 && y < 8);
	};

	auto reset_selected_piece_to_old_pos = [&]() {
		board[old_y][old_x] = selected_piece;

		// Reset selected piece data
		selected_piece_tex = nullptr;
		is_piece_being_dragged = false;
	};


	if (left_held && !is_piece_being_dragged) {
		int board_x = m_x / cell_size;
		int board_y = m_y / cell_size;

		if (!is_in_bounds(board_x, board_y)) return;

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
		int board_x = m_x / cell_size;
		int board_y = m_y / cell_size;

		if (!is_in_bounds(board_x, board_y)) {
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
	}
	else if (right_held && !is_piece_being_dragged) {
		int board_x = m_x / cell_size;
		int board_y = m_y / cell_size;

		if (!is_in_bounds(board_x, board_y)) return;

		board[board_y][board_x] = EMPTY;
	}
}

void MouseHandler::Render(SDL_Renderer *renderer, int cell_size) {
	if (is_piece_being_dragged && selected_piece_tex != nullptr) {
		const SDL_FRect dest = { m_x - cell_size / 2, m_y - cell_size / 2, cell_size, cell_size };
		SDL_RenderTexture(renderer, selected_piece_tex, NULL, &dest);
	}
}