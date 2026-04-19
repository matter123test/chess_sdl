#include "ui.h"
#include <imgui_stdlib.h>

UI::UI(SDL_Window* window, SDL_Renderer* renderer)
	:m_window(window), m_renderer(renderer)
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io{ ImGui::GetIO() };

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	// Setup Platform/Renderer backends
	ImGui_ImplSDL3_InitForSDLRenderer(
		m_window,
		m_renderer
	);
	ImGui_ImplSDLRenderer3_Init(
		m_renderer
	);
}

void UI::Update(SDL_Event* event)
{
	ImGui_ImplSDL3_ProcessEvent(event);
}

void UI::Build(ChessBoard& board)
{
	// Start the Dear ImGui frame
	ImGui_ImplSDL3_NewFrame();
	ImGui_ImplSDLRenderer3_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Test");

	if (ImGui::ArrowButton("in", ImGuiDir_Left)) { ClearBoard(board); FENToBoard(input_FEN_str, board); }
	ImGui::SameLine();
	ImGui::InputText("FEN IN", input_FEN_str, sizeof(input_FEN_str));

	if (ImGui::ArrowButton("out", ImGuiDir_Right)) { output_FEN_str = BoardToFEN(board); };
	ImGui::SameLine();
	ImGui::InputText("FEN OUT", &output_FEN_str);

	if (ImGui::Button("RESET")) { ResetBoard(board); }

	ImGui::ColorEdit3("A", color_a);
	ImGui::ColorEdit3("B", color_b);

	ImGui::End();

	ImGui::Render();
}

void UI::Render()
{
	ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), m_renderer);
}

void UI::HandleColors(int(&color_a)[3], int(&color_b)[3])
{
	color_a[0] = this->color_a[0] * 255;
	color_a[1] = this->color_a[1] * 255;
	color_a[2] = this->color_a[2] * 255;

	color_b[0] = this->color_b[0] * 255;
	color_b[1] = this->color_b[1] * 255;
	color_b[2] = this->color_b[2] * 255;
}
