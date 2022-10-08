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
#ifndef BRATR_C_GUI_H
#define BRATR_C_GUI_H

#pragma once

class CGUI
{
public:
	// Returns an static instance of this particular class
	static inline CGUI& get()
	{
		static CGUI gui;
		return gui;
	}

public:
	bool startup(GLFWwindow* window);
	void shutdown();

	void run_frame(uint32_t app_width, uint32_t app_height);

	inline const std::filesystem::path& get_input_file() const 
	{
		return m_input_filepath;
	}

	void clear_input_file();

private:
	// Renders the contents of gui
	void render_contents();

	void render_menu_bar();
	void render_menu_bar_decorations();

	void render_translation_contents();

	void imgui_set_style();

	void try_to_open_input_file(const std::filesystem::path& filepath);

private:
	void add_double_entry(const std::string& label_left, const std::function<void()>& callback);

private:
	// File that we're reading from
	std::filesystem::path m_input_filepath;
};

#endif