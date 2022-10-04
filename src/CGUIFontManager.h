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
#ifndef BRATR_C_GUI_FONT_MANAGER_H
#define BRATR_C_GUI_FONT_MANAGER_H

#pragma once

class GlyphContainer
{
public:
	static const ImWchar s_czech[];
};

class CGUIFontManager
{
public:
	// Returns an static instance of this particular class
	static inline CGUIFontManager& get()
	{
		static CGUIFontManager fnt;
		return fnt;
	}

public:
	bool precache_fonts(ImGuiIO& io);

	ImFont* get_font(const std::string& font_name);
	ImFont* get_active_font();

	void update_active_font();

	void render_text_u8(const ImVec2& pos, ImColor clr, const char* text, ...);
	void render_text_u16(const ImVec2& pos, ImColor clr, const wchar_t* text, ...);
	void render_text_ex(const ImVec2& pos, ImColor clr, ImFont* font, const char* text);

	void unicode_to_utf8(const wchar_t* wbuf, char* sbuf, uint32_t buf_len);

private:
	ImFont* try_to_precache(ImGuiIO& io, const void* compressed_ttf_data, uint32_t compressed_size, 
						  float font_size, const ImWchar* glyph_ranges);

private:
	std::map<std::string, ImFont*> m_precached_fonts;

	// Font that is currently selected
	ImFont* m_active_font;
};

#endif