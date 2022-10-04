/*
 *       Copyright (c) 2022, oxiKKK
 *
 *   This program is licensed under the MIT license. By downloading, copying, or
 *    modifying, installing or using this software you agree to this license.
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

bool CApplication::run()
{
#ifdef _DEBUG
	static const int32_t con_size = 1024;
	if (!CConsole::get().create(con_size))
		return false;
#endif

	CFileSystem::get().init();

	CSettings::get().load_settings();

	if (!invoke_window())
	{
		CConsole::get().output_error("Failed to create glfw window");
		return false;
	}

	if (!CGUI::get().startup(m_glfw_window))
	{
		CConsole::get().output_error("Failed to initialize GUI");
		return false;
	}

	while (on_frame()) {}

	CGUI::get().shutdown();

	destroy_window();

	CSettings::get().write_settings();

#ifdef _DEBUG
	CConsole::get().destroy();
#endif

	return true;
}

bool CApplication::invoke_window()
{
	if (!glfwInit())
	{
		CDialogManager::get().display_fatal_error(CTranslation::Get<TRED_ERR_GLFW_INIT>());
		return false;
	}

	m_app_title = std::format("BraTr -- {}", CTranslation::Get<TRED_TITLE>());
	m_app_width = 860;
	m_app_height = 720;

	m_glfw_window = glfwCreateWindow(
		m_app_width, m_app_height,
		m_app_title.c_str(),
		nullptr, nullptr);

	if (!m_glfw_window)
	{
		CDialogManager::get().display_fatal_error(CTranslation::Get<TRED_ERR_GLFW_CREATE_WINDOW>());
		return false;
	}

	CConsole::get().output_message(std::format("Initialized window with dimensions {} {}", m_app_width, m_app_height));

	glfwMakeContextCurrent(m_glfw_window);

	GLFWimage icon;
	icon.pixels = SOIL_load_image_from_memory(s_icon_file_png_bin_data, sizeof(s_icon_file_png_bin_data), &icon.width, &icon.height, NULL, SOIL_LOAD_RGBA);
	glfwSetWindowIcon(m_glfw_window, 1, &icon);

	// Enable vsync
	glfwSwapInterval(1);

	return true;
}

void CApplication::destroy_window()
{
	glfwDestroyWindow(m_glfw_window);
	glfwTerminate();

	m_glfw_window = nullptr;

	CConsole::get().output_message("Destroyed window");
}

bool CApplication::on_frame()
{
	// User has requested a window close or the window just
	// has to be closed now.
	if (glfwWindowShouldClose(m_glfw_window))
		return false;

#ifdef _DEBUG
	CConsole::get().update();
#endif

	glfwPollEvents();

	// Update the dims if user resized the window
	update_app_dims();

	if (!CBrailleParser::get().update())
		return false;

	// Render ImGUI
	CGUI::get().run_frame(m_app_width, m_app_height);

	if (CGUI::get().get_input_file().empty())
		change_window_title(std::format("BraTr -- {}", CTranslation::Get<TRED_TITLE>()));
	else
		change_window_title(std::format("BraTr -- {} | {}", CTranslation::Get<TRED_TITLE>(), CGUI::get().get_input_file().filename().string()));

	glfwMakeContextCurrent(m_glfw_window);
	glfwSwapBuffers(m_glfw_window);

	return true;
}

void CApplication::update_app_dims()
{
	glfwGetFramebufferSize(m_glfw_window, &m_app_width, &m_app_height);
}

void CApplication::change_window_title(const std::string& title)
{
	glfwSetWindowTitle(m_glfw_window, title.c_str());
}

void CApplication::get_app_dims(int32_t* width_out, int32_t* height_out)
{
	*width_out = m_app_width;
	*height_out = m_app_height;
}
