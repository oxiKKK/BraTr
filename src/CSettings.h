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
#ifndef BRATR_C_SETTINGS_H
#define BRATR_C_SETTINGS_H

#pragma once

enum ESettingsFont
{
	SETTINGS_FONT_SMALL, 
	SETTINGS_FONT_MEDIUM, 
	SETTINGS_FONT_BIG, 
};

class CSettings
{
public:
	static inline auto& get()
	{
		static CSettings settings;
		return settings;
	}

public:
	void load_settings();
	void write_settings();

private:
	std::string read_string(const std::string& section, const std::string& key) const;
	int32_t read_value(const std::string& section, const std::string& key) const;
	void write_value(std::ofstream& ofs, const std::string& key, uint32_t value) const;
	void write_string(std::ofstream& ofs, const std::string& key, const std::string& szvalue) const;
	void write_section(std::ofstream& ofs, const std::string& section) const;

	std::string get_settings_filepath() const;

public:
	bool m_hide_left_side = false;

	bool m_render_prefixes = true;

	bool m_render_number_prefix = true;
	bool m_render_small_letter_prefix = false;
	bool m_render_capital_letters_prefix = true;
	bool m_render_capital_letter_groups_prefix = true;
	bool m_render_small_greek_letters_prefix = true;
	bool m_render_capital_greek_letters_prefix = true;

	bool m_render_hover_unciode_offset_tooltip = false;

	bool m_open_same_input_file = false;
	std::string m_input_file; // Empty when the setting is off.

	ESettingsFont m_font_size = SETTINGS_FONT_BIG;

	ELanguage m_language = LANGUAGE_CZECH;

	static inline constexpr auto k_previously_opened_files_n = 5;
	std::deque<std::string> m_previously_opened_files;

private:
	static inline const char* k_settings_section_name = "root";
};

#endif