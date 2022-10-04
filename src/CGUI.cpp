/*
 *       Copyright (c) 2022, oxiKKK
 *
 *   This program is licensed under the MIT license. By downloading, copying,
 *    installing or using this software you agree to this license.
 *
 *       License Agreement
 *
 *   Permission is hereby granted, free of charge, to any person obtaining a
 *    copy of this software and associated documentation files (the "Software"),
 *    to deal in the Software without restriction, including without limitation
 *    the rights to use, copy, modify, merge, publish, distribute, sublicense,
 *    and/or sell copies of the Software, and to permit persons to whom the
 *    Software is furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included
 *    in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 *    OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 *    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 *    IN THE SOFTWARE.
*/
#include "bratr_pch.h"

bool CGUI::startup(GLFWwindow* window)
{
	// Setup Dear ImGui context
	if (!ImGui::CreateContext())
	{
		CDialogManager::get().display_fatal_error(CTranslation::Get<TRED_ERR_IMGUI_CONTEXT>());
		return false;
	}

	ImGuiIO& io = ImGui::GetIO();

	// Disable generating imgui.ini
	io.IniFilename = io.LogFilename = nullptr;

	// Try to load fonts for us
	if (!CGUIFontManager::get().precache_fonts(io))
	{
		CConsole::get().output_error("Failed to precache fonts");
		return false;
	}

	imgui_set_style();


	// Setup Platform/Renderer backends
	if (!ImGui_ImplGlfw_InitForOpenGL(window, true))
	{
		CDialogManager::get().display_fatal_error(CTranslation::Get<TRED_ERR_IMGUI_GLFW>());
		return false;
	}

	if (!ImGui_ImplOpenGL2_Init())
	{
		CDialogManager::get().display_fatal_error(CTranslation::Get<TRED_ERR_IMGUI_OPGL2>());
		return false;
	}

	CEventListener::get().register_listener();

	if (CSettings::get().m_open_same_input_file)
	{
		m_input_filepath = CSettings::get().m_input_file;

		if (m_input_filepath.empty() || !std::filesystem::exists(m_input_filepath))
			CDialogManager::get().display_error(CTranslation::Get<TRED_ERR_PREVIOUS_INPUT_FILE_NOT_FOUND>());
	}

	CConsole::get().output_message("Initialized GUI");

	return true;
}

void CGUI::shutdown()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplGlfw_Shutdown();

	CConsole::get().output_message("GUI Shutdown\n");
}

void CGUI::run_frame(uint32_t app_width, uint32_t app_height)
{
	//const auto clear_clr = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// Update font used by settings
	CGUIFontManager::get().update_active_font();

	CEventListener::get().listen();

	// Can't open same input file next time when there's isn't any
	if (m_input_filepath.empty())
		CSettings::get().m_open_same_input_file = false;

	render_contents();

	//ImGui::ShowDemoWindow();

	ImGui::Render();

	glViewport(0, 0, app_width, app_height);
	glClearColor(0.f, 0.f, 0.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT);

	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}

void CGUI::render_contents()
{
	// Get the dims affected by resizing and such
	int32_t app_width, app_height;
	CApplication::get().get_app_dims(&app_width, &app_height);

	ImGui::SetNextWindowSize({ (float)app_width, (float)app_height }, ImGuiCond_Always);
	ImGui::SetNextWindowPos({ 0, 0 }, ImGuiCond_Always);

	ImGuiIO& io = ImGui::GetIO();

	static constexpr auto wnd_flags =
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoScrollWithMouse |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_MenuBar |
		ImGuiWindowFlags_NoCollapse;

	ImGui::Begin("##MainWindow", NULL, wnd_flags);
	{		
		if (ImGui::BeginMenuBar())
		{
			render_menu_bar();

			render_menu_bar_decorations();

			ImGui::EndMenuBar();
		}

		// Hack Hack -- we need to call this twice, because imgui clips the rect when outside of menubar.
		render_menu_bar_decorations();

		render_translation_contents();
	}
	ImGui::End();
}

void CGUI::render_menu_bar_decorations()
{
	auto& Style = ImGui::GetStyle();
	
	ImGui::GetWindowDrawList()->AddRect({ -20, -20 },
										{ 230, 25 },
										ImGui::ColorConvertFloat4ToU32(Style.Colors[ImGuiCol_Border]),
										12.f);
}

void CGUI::render_menu_bar()
{
	if (ImGui::BeginMenu(CTranslation::Get<TRED_GUI_FILE>()))
	{
		if (ImGui::MenuItem(CTranslation::Get<TRED_GUI_OPEN>()))
		{
			auto Sel = pfd::open_file::open_file(
				"Select a text file", ".",
				{ "Text Files (.txt", "*.txt" },
				pfd::opt::none);

			try_to_open_input_file(Sel.result()[0]);
		}

		ImGui::BeginDisabled(m_input_filepath.empty());

		if (ImGui::MenuItem(CTranslation::Get<TRED_GUI_CLOSE>()))
		{
			m_input_filepath = "";
		}

		ImGui::EndDisabled();

		// Previously opened files
		const auto& prev_opened = CSettings::get().m_previously_opened_files;

		if (!prev_opened.empty())
			ImGui::Separator();

		for (uint32_t i = 0; i < prev_opened.size(); i++)
		{
			if (ImGui::Selectable(prev_opened[i].c_str()))
			{
				try_to_open_input_file(prev_opened[i]);
			}
		}

		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu(CTranslation::Get<TRED_GUI_PREFERENCES>()))
	{
		ImGui::MenuItem(CTranslation::Get<TRED_GUI_HIDE_LEFT_SIDE>(), nullptr, &CSettings::get().m_hide_left_side);
		if (ImGui::MenuItem(CTranslation::Get<TRED_GUI_SHOW_INPUT_FILE_NEXT_TIME>(), nullptr, &CSettings::get().m_open_same_input_file, !m_input_filepath.empty()))
		{
			CSettings::get().m_input_file = m_input_filepath.string();
		}
		ImGui::MenuItem(CTranslation::Get<TRED_GUI_RENDER_HOVER_TOOLTIP>(), nullptr, &CSettings::get().m_render_hover_unciode_offset_tooltip);

		ImGui::Separator();

		if (ImGui::BeginMenu(CTranslation::Get<TRED_GUI_LANGUAGE>()))
		{
			static bool selected_1 = false, selected_2 = false;

			selected_1 = CSettings::get().m_language == LANGUAGE_ENGLISH;
			selected_2 = CSettings::get().m_language == LANGUAGE_CZECH;

			if (ImGui::MenuItem(CTranslation::Get<TRED_GUI_LANGUAGE_ENGLISH>(), nullptr, &selected_1))
				CSettings::get().m_language = LANGUAGE_ENGLISH;
			else if (ImGui::MenuItem(CTranslation::Get<TRED_GUI_LANGUAGE_CZECH>(), nullptr, selected_2))
				CSettings::get().m_language = LANGUAGE_CZECH;

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu(CTranslation::Get<TRED_GUI_FONT_SIZE>()))
		{
			static bool selected_1 = false, selected_2 = false, selected_3 = false;

			selected_1 = CSettings::get().m_font_size == SETTINGS_FONT_SMALL;
			selected_2 = CSettings::get().m_font_size == SETTINGS_FONT_MEDIUM;
			selected_3 = CSettings::get().m_font_size == SETTINGS_FONT_BIG;

			if (ImGui::MenuItem(CTranslation::Get<TRED_GUI_FONT_SIZE_SMALL>(), nullptr, &selected_1))
				CSettings::get().m_font_size = SETTINGS_FONT_SMALL;
			else if (ImGui::MenuItem(CTranslation::Get<TRED_GUI_FONT_SIZE_MEDIUM>(), nullptr, selected_2))
				CSettings::get().m_font_size = SETTINGS_FONT_MEDIUM;
			else if (ImGui::MenuItem(CTranslation::Get<TRED_GUI_FONT_SIZE_BIG>(), nullptr, selected_3))
				CSettings::get().m_font_size = SETTINGS_FONT_BIG;

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu(CTranslation::Get<TRED_GUI_SPECIAL_PREFIXES>()))
		{
			ImGui::MenuItem(CTranslation::Get<TRED_GUI_RENDER_SPECIAL_PREFIXES>(), nullptr, &CSettings::get().m_render_prefixes, true);

			ImGui::Separator();

			bool are_prefixes_eanbled = CSettings::get().m_render_prefixes;

			ImGui::MenuItem(CTranslation::Get<TRED_GUI_RENDER_NUMBERS_PREFIX>(), nullptr, &CSettings::get().m_render_number_prefix, are_prefixes_eanbled);
			ImGui::MenuItem(CTranslation::Get<TRED_GUI_RENDER_SMALL_LETTER_PREFIX>(), nullptr, &CSettings::get().m_render_small_letter_prefix, are_prefixes_eanbled);
			ImGui::MenuItem(CTranslation::Get<TRED_GUI_RENDER_CAPITAL_LETTERS_PREFIX>(), nullptr, &CSettings::get().m_render_capital_letters_prefix, are_prefixes_eanbled);
			ImGui::MenuItem(CTranslation::Get<TRED_GUI_RENDER_CAPITAL_LETTERS_GROUP_PREFIX>(), nullptr, &CSettings::get().m_render_capital_letter_groups_prefix, are_prefixes_eanbled);
			ImGui::MenuItem(CTranslation::Get<TRED_GUI_RENDER_SMALL_GREEK_LETTER_PREFIX>(), nullptr, &CSettings::get().m_render_small_greek_letters_prefix, are_prefixes_eanbled);
			ImGui::MenuItem(CTranslation::Get<TRED_GUI_RENDER_CAPITAL_GREEK_LETTER_PREFIX>(), nullptr, &CSettings::get().m_render_capital_greek_letters_prefix, are_prefixes_eanbled);

			ImGui::EndMenu();
		}

		ImGui::EndMenu();
	}

	if (ImGui::MenuItem(CTranslation::Get<TRED_GUI_ABOUT>()))
	{
		ImGui::OpenPopup(CTranslation::Get<TRED_GUI_ABOUT>());
	}

	// Always center this window when appearing
	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetNextWindowPos(center, ImGuiCond_Always, ImVec2(0.5f, 0.5f));

	if (ImGui::BeginPopupModal(CTranslation::Get<TRED_GUI_ABOUT>(), NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("%s v%s", CTranslation::Get<TRED_TITLE>(), BRATR_VERSION);
		ImGui::Text("%s %s %s (%s build)", CTranslation::Get<TRED_GUI_ABOUT_COMPILED_AT>(), __DATE__, __TIME__, BUILD_MODE_STR);
		ImGui::Separator();

		if (ImGui::Button("OK", ImVec2(120, 0)))
			ImGui::CloseCurrentPopup();

		ImGui::SetItemDefaultFocus();

		ImGui::EndPopup();
	}
}

void CGUI::render_translation_contents()
{
	// We have to handle this due to selectioning. This cannot be 
	// done inside the rendering code, because it is rendered twice, 
	// for left&right side. This'd result in twice execution of the 
	// handler code - bugs.
	CBrailleRenderer::get().handle_keyboard_events();

	if (ImGui::BeginTable("Translation contents table", 2))
	{
		ImGui::TableSetupColumn("1");
		ImGui::TableSetupColumn("2");

		ImGui::TableNextColumn();

		// Render left side
		ImGui::BeginChild("##MainChildLeft", { 0, 0 }, true);
		{
			CBrailleRenderer::get().render_side_region(true);
		}
		ImGui::EndChild();

		ImGui::TableNextColumn();

		// Render right side
		ImGui::BeginChild("##MainChildRight", { 0, 0 }, true);
		{
			CBrailleRenderer::get().render_side_region(false);
		}
		ImGui::EndChild();

		ImGui::EndTable();
	}
}

void CGUI::add_double_entry(const std::string& label_left, const std::function<void()>& callback)
{
	ImGui::TableNextColumn();
	ImGui::Text(label_left.c_str());
	ImGui::TableNextColumn();

	// Inside this callback user renders whatever he wants
	callback();
}

void CGUI::imgui_set_style()
{
	// Our style is based on the dark one.
	ImGui::StyleColorsDark();

	auto& style = ImGui::GetStyle();

	style.ChildRounding = 6.f;
	style.Colors[ImGuiCol_MenuBarBg] = style.Colors[ImGuiCol_WindowBg];
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
	style.Colors[ImGuiCol_TitleBgActive] = ImColor(50, 50, 60, 255);
	style.Colors[ImGuiCol_Button] = ImColor(100, 110, 130, 100);
	style.Colors[ImGuiCol_ButtonHovered] = ImColor(85, 85, 85, 255);
	style.Colors[ImGuiCol_ButtonActive] = ImColor(126, 126, 126, 255);
	style.Colors[ImGuiCol_Tab] = style.Colors[ImGuiCol_Button];
	style.Colors[ImGuiCol_TabHovered] = style.Colors[ImGuiCol_ButtonHovered];
	style.Colors[ImGuiCol_TabActive] = style.Colors[ImGuiCol_ButtonActive];
	style.Colors[ImGuiCol_Header] = style.Colors[ImGuiCol_Button];
	style.Colors[ImGuiCol_HeaderHovered] = style.Colors[ImGuiCol_ButtonHovered];
	style.Colors[ImGuiCol_HeaderActive] = style.Colors[ImGuiCol_ButtonActive];

	CConsole::get().output_message("Setuped basic imgui theme");
}

void CGUI::try_to_open_input_file(const std::filesystem::path& filepath)
{
	// Found the file
	if (filepath.empty())
	{
		CDialogManager::get().display_error(std::format("{} ({})", CTranslation::Get<TRED_ERR_COULDNT_OPEN_FILE>(), filepath.string()));

		return;
	}

	// Add the file to the remember queue
	auto& prev_opened_files = CSettings::get().m_previously_opened_files;

	if (prev_opened_files.size() > CSettings::get().k_previously_opened_files_n)
		prev_opened_files.pop_front();

	// Scan if we've already added it to the list before.
	// If not, add it to the list.
	bool added_already = false;
	for (const auto& file : prev_opened_files)
	{
		if (file == filepath)
		{
			added_already = true;
			break;
		}
	}

	if (!added_already)
		prev_opened_files.push_back(filepath.string());

	CConsole::get().output_info(std::format("Opened new input file {}", filepath.string()));

	m_input_filepath = filepath;
}
