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
#ifndef BRATR_C_BRAILLE_RENDERER_H
#define BRATR_C_BRAILLE_RENDERER_H

#pragma once

class CSelectionCursor
{
private:
	inline static constexpr int32_t INVALID_INDEX = -1;

public:
	static inline int32_t invalid_index() { return INVALID_INDEX; }

	// Shifting routines checking for an under/overflow.
	void shift_left();
	void shift_right();
	void shift_up(uint32_t nMaxLettersPerLine);
	void shift_down(uint32_t nMaxLettersPerLine);

	inline int32_t get_position() const { return m_letter_idx; }
	inline void update(int32_t new_idx) { m_letter_idx = new_idx; }

private:
	// Position of the letter that we've selected right now.
	int32_t m_letter_idx = invalid_index();
};

class CBrailleRenderer
{
public:
	// Returns an static instance of this particular class
	static inline CBrailleRenderer& get()
	{
		static CBrailleRenderer renderer;
		return renderer;
	}

public:
	// Render either normal-character side or the side where
	// braille characters are rendered.
	void render_side_region(bool regular_characters);

	// Keyboard events are handled outside rendering code
	void handle_keyboard_events();

public:
	// This function returns the amount of characters displayed including counted 
	// individual prefixes set inside the settings.
	inline uint32_t num_of_settingcared_chars() const { return m_settingcared_num_of_chars; };

private:
	void render_strips();

	// Renders the contents of the file. If regular_characters
	// is set to true, then this function takes care of rendering
	// regular characters. Otherwise, braille characters are 
	// rendered.
	void render_characters(bool regular_characters);

	// Renders individual characters at fixed position.
	void render_regular_char(const ImVec2& pos, const Character& character);
	void render_braille_char(const ImVec2& pos, const Character& character);
	void render_dot(const ImVec2& center_pos, float radius);
	void render_rotated_triangle(const ImVec2& center_pos, float size);

	// Used for when the character isn't inside the atlas
	void render_invalid_char_marker(const ImVec2& char_pos);

	void render_letter_selection_rect(const ImVec2& pos, const ImColor& color, bool is_filled);

	void synchronize_translation_childs_scrollbars(bool regular_characters);

	// Used to handle new lines and position for newly rendered characters.
	void increment_chraracter_pos(ImVec2& relative_pos);

	void handle_selection_shift_on_key_press(ImGuiKey key, const std::function<void()>& callback);

	bool approved_prefix(EBraillePrefix prefix);

	float get_letter_size() const { return CGUIFontManager::get().get_active_font()->FontSize; }
	float get_braille_dot_size() const { return CGUIFontManager::get().get_active_font()->FontSize / 12.f; }

	// How much is the dot shifted invards when rendered
	float get_braille_dot_invards_shift_mul() const { return CGUIFontManager::get().get_active_font()->FontSize / 15.f; }

	float get_num_of_chars_per_line() const { return m_max_avail_content.x / (get_letter_size() + StyleConstants::k_letter_spacing_x); }

public:
	// Class for holding style information about how are the braille elements rendered
	class StyleConstants
	{
	public:
		static inline constexpr float k_letter_spacing_x = 0.f;
		static inline constexpr float k_letter_spacing_y = 2.f;
	};

private:
	CSelectionCursor	m_selected_letter_idx;

	// Save this across frames for selection shift handling
	ImVec2				m_max_avail_content = {};

	// Takes in count the whole region, not only visible contents
	float				m_max_avail_content_scroll_y = {};

	uint32_t			m_settingcared_num_of_chars; // Chracters including prefixes if prefixes are enabled in settings.

	// Scroll for both sides -- 0 is for left, 1 is for right.
	float				m_translation_side_scroll[2];
};

#endif