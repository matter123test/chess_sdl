#include "ui.h"

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

void UI::Build()
{
	// Start the Dear ImGui frame
	ImGui_ImplSDL3_NewFrame();
	ImGui_ImplSDLRenderer3_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Test");
	ImGui::End();

	ImGui::Render();
}

void UI::Render()
{
	ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), m_renderer);
}