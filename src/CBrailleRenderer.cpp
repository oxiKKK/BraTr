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

/*********************************************************************************
* Style Constants
*/

float CBrailleRenderer::StyleConstants::k_letter_spacing_x = 0.f;
float CBrailleRenderer::StyleConstants::k_letter_spacing_y = 2.f;

float CBrailleRenderer::StyleConstants::k_dot_size_modifier = 1.f / 12.f;
float CBrailleRenderer::StyleConstants::k_dot_invards_shift_modifier = 3.f;

float CBrailleRenderer::StyleConstants::k_letter_ratio_x = 4.f;
float CBrailleRenderer::StyleConstants::k_letter_ratio_y = 2.5f;

/*********************************************************************************/

void CBrailleRenderer::render_side_region(bool regular_characters)
{
	render_strips();

	// Render individual characters
	render_characters(regular_characters);
}

void CBrailleRenderer::handle_keyboard_events()
{
	// Shift to left (-)
	handle_selection_shift_on_key_press(
		ImGuiKey_LeftArrow, [&]()
		{
			m_selected_letter_idx.shift_left();
		});

	// Shift to right (+)
	handle_selection_shift_on_key_press(
		ImGuiKey_RightArrow, [&]()
		{
			m_selected_letter_idx.shift_right();
		});

	// Shift upwards (negative *)
	handle_selection_shift_on_key_press(
		ImGuiKey_UpArrow, [&]()
		{
			m_selected_letter_idx.shift_up(get_num_of_chars_per_line());
		});

	// Shift downwards (positive *)
	handle_selection_shift_on_key_press(
		ImGuiKey_DownArrow, [&]()
		{
			m_selected_letter_idx.shift_down(get_num_of_chars_per_line());
		});
}

void CBrailleRenderer::render_strips()
{
	const auto drawlist = ImGui::GetWindowDrawList();
	const auto window_size = ImGui::GetWindowSize();
	
	// m_max_avail_content_scroll_y is used only when we exceed the renderable region. Otherwise, 
	// regular window size is used.
	ImVec2 total_size = { window_size.x, (m_max_avail_content_scroll_y < m_max_avail_content.y) ? window_size.y : m_max_avail_content_scroll_y } ;

	auto& style = ImGui::GetStyle();
	const auto window_pad = style.WindowPadding;

	const auto letter_size = get_letter_size();

	ImVec2 cursor_pos = { ImGui::GetCursorScreenPos().x - window_pad.x, ImGui::GetCursorScreenPos().y - window_pad.y };

	const float letter_size_with_spacing = letter_size.y + StyleConstants::k_letter_spacing_y;

	uint32_t n_strip = 0;
	for (float off = 0.f;
		 off + letter_size_with_spacing < total_size.y;
		 off += letter_size_with_spacing)
	{
		auto cur_pos = cursor_pos;

		cur_pos.x += window_pad.x;
		cur_pos.y += window_pad.y + off;

		ImColor color;

		if (n_strip & 1)
			color = ImColor(70, 70, 70, 100);
		else
			color = ImColor(30, 30, 30, 130);

		drawlist->AddQuadFilled({ cur_pos.x, cur_pos.y },
								{ cur_pos.x + total_size.x - window_pad.x * 2.f, cur_pos.y },
								{ cur_pos.x + total_size.x - window_pad.x * 2.f, cur_pos.y + letter_size.y },
								{ cur_pos.x, cur_pos.y + letter_size.y },
								color);

		n_strip++;
	}
}

void CBrailleRenderer::render_characters(bool regular_characters)
{
	const auto& precached_chars = CBrailleParser::get().get_precached_chars();

	const auto window_size = ImGui::GetWindowSize();

	auto& style = ImGui::GetStyle();
	const auto window_pad = style.WindowPadding;

	const ImVec2 letter_size = get_letter_size();

	// Apply scrollbar size however, only if it's present.
	float scrollbar_size_x = style.ScrollbarSize;
	if (m_max_avail_content_scroll_y < window_size.y)
		scrollbar_size_x = 0.f;

	ImVec2 cursor_pos = { ImGui::GetCursorScreenPos().x - window_pad.x, ImGui::GetCursorScreenPos().y - window_pad.y };

	// Start pos is the position of the top left corner
	ImVec2 start_pos = { cursor_pos.x + window_pad.x, cursor_pos.y + window_pad.y };

	// End position is only important for calculating the max avail contents
	ImVec2 end_pos = { start_pos.x + window_size.x - window_pad.x - scrollbar_size_x, start_pos.y + window_size.y - window_pad.y };

	// The maximum available space we can use to render characters
	m_max_avail_content = { end_pos.x - start_pos.x, end_pos.y - start_pos.y };

	// Relative pos is the position of character from the top left corner
	ImVec2 relative_pos;

	// Setting-cared index cares about which prefixes user requested to render
	// Both index includes both, normal as well as braille prefix chars.
	uint32_t n_settingcared_idx = 0, n_both_idx = 0;
	while (n_both_idx < precached_chars.size())
	{
		const auto& cur_char = precached_chars[n_both_idx];

		// Current position of a character
		ImVec2 cur_pos = { start_pos.x + relative_pos.x, start_pos.y + relative_pos.y };

		if (cur_char.has_prefix())
		{
			// We've explicitly disabled showing this prefix
			if (!approved_prefix(cur_char.m_prefix_type))
			{
				n_both_idx++;
				continue;
			}
		}

		// Render this character and increment the position afterwards

		if (!cur_char.m_not_found_in_atlas)
		{
			if (regular_characters)
			{
				ImVec2 char_center =
				{
					cur_pos.x + letter_size.x / 2.f,
					cur_pos.y + letter_size.y / 2.f
				};

				// If it's a prefix character, render a dot representing it
				if (cur_char.m_unicode_character == '-')
				{
					const float rect_size = get_braille_dot_size();
					render_rotated_triangle(char_center, rect_size);
				}
				else
				{
					float imgui_font_size = CGUIFontManager::get().get_active_font()->FontSize;

					// We have to also take in count the ratio of a letter size in
					// order to position the character to the center.
					ImVec2 char_ratio_off_pos =
					{
						cur_pos.x + letter_size.x / 2.f - imgui_font_size / 2.f,
						cur_pos.y + letter_size.y / 2.f - imgui_font_size / 2.f
					};

					render_regular_char(char_ratio_off_pos, cur_char);
				}
			}
			else
				render_braille_char(cur_pos, cur_char);
		}
		else
		{
			render_invalid_char_marker(cur_pos);
		}

		// Mouse movement
		if (CUtils::is_rect_hovered(cur_pos, letter_size))
		{
			if (CEventListener::get().is_mouse_button_pressed(ImGuiMouseButton_Left))
			{
				if (m_selected_letter_idx.get_position() != n_settingcared_idx)
				{
					CConsole::get().output_message(std::format("Selected {}", n_settingcared_idx));
					m_selected_letter_idx.update(n_settingcared_idx); // Select
				}
				else
				{
					CConsole::get().output_message(std::format("Unselected {}", n_settingcared_idx));
					m_selected_letter_idx.update(CSelectionCursor::invalid_index()); // Already selected, unsellect
				}
			}
			else
			{
				if (m_selected_letter_idx.get_position() != n_settingcared_idx) // If this is selected, don't apply hover
					render_letter_selection_rect(cur_pos, ImColor(230, 230, 230, 120), false);
			}

			if (cur_char.m_not_found_in_atlas || CSettings::get().m_render_hover_unciode_offset_tooltip)
			{
				ImGui::SetNextWindowSize({ 80.f, 0.f }, ImGuiCond_Always);
				ImGui::BeginTooltip();

				ImGui::Text("U+%06X", (uint32_t)cur_char.m_unicode_character);

				ImGui::EndTooltip();
			}
		}

		if (m_selected_letter_idx.get_position() == n_settingcared_idx)
			render_letter_selection_rect(cur_pos, ImColor(230, 230, 230, 70), true);

		// Take care of another position and newlines.
		increment_chraracter_pos(relative_pos);

		n_settingcared_idx++;
		n_both_idx++;
	}

	m_settingcared_num_of_chars = n_settingcared_idx;

	// The maximum available contents for scrolling + one extra line as a reserve.
	m_max_avail_content_scroll_y = relative_pos.y + (letter_size.y * StyleConstants::k_letter_spacing_y);

	ImGui::SetCursorPosY(m_max_avail_content_scroll_y);

	synchronize_translation_childs_scrollbars(regular_characters);
}

void CBrailleRenderer::render_regular_char(const ImVec2& pos, const Character& character)
{
	wchar_t buf[4];

	wchar_t char_to_render = character.m_unicode_character;
	ImColor char_clr = { 255, 255, 255, 255 };

	if (CSettings::get().m_hide_left_side)
	{
		char_to_render = L'?';
		char_clr = { 255, 255, 255, 50 };
	}

	swprintf(buf, L"%c%ws", char_to_render, char_to_render == L'%' ? L"%" : L"");
	CGUIFontManager::get().render_text_u16(pos, char_clr, buf);
}

void CBrailleRenderer::render_braille_char(const ImVec2& pos, const Character& character)
{
	const auto drawlist = ImGui::GetWindowDrawList();

	const ImVec2 letter_size = get_letter_size();

	// Circle radius
	const float dot_size = get_braille_dot_size();

	// How much is the dot shifted invards when rendered
	const float dot_invards_shift_mul = get_braille_dot_invards_shift_mul();

	// How are the dots spaced out of each other
	const ImVec2 dot_spacing = { letter_size.x, letter_size.y / 2.f };

	// Bits which indicate which dots will be rendered
	uint8_t render_braille_bits = character.has_prefix() ? character.m_braille_prefix_bits : character.m_braille_bits;

	ImVec2 circle_center, off;

	for (uint32_t bit = 0; bit < 6; bit++)
	{
		// Offsets to the points so they're not out of bounds from the bounding box
		static const ImVec2 bit_offsets[6]
		{
			{ dot_size, dot_size },
			{ -dot_size, dot_size },
			{ dot_size, 0.f },
			{ -dot_size, 0.f },
			{ dot_size, -dot_size },
			{ -dot_size, -dot_size },
		};

		// Check if bit is set
		bool render_circle = render_braille_bits & (1 << bit);

		circle_center = {
			pos.x + off.x + bit_offsets[bit].x * dot_invards_shift_mul, 
			pos.y + off.y + bit_offsets[bit].y * dot_invards_shift_mul
		};

		// For points that aren't rendered render only small circle
		if (render_circle)
			drawlist->AddCircleFilled(circle_center, dot_size, ImColor(255, 255, 255, 255));

		if (bit & 1) // every second dot
		{
			off.y += dot_spacing.y;
			off.x = 0.f;
		}
		else
		{
			off.x += dot_spacing.x;
		}
	}	
}

void CBrailleRenderer::render_dot(const ImVec2& center_pos, float radius)
{
	const auto drawlist = ImGui::GetWindowDrawList();

	drawlist->AddCircleFilled(center_pos,
							  radius, ImColor(255, 255, 255, 150));
}

void CBrailleRenderer::render_rotated_triangle(const ImVec2& center_pos, float size)
{
	const auto drawlist = ImGui::GetWindowDrawList();

	ImVec2 positions[4] =
	{
		{ center_pos.x - size, center_pos.y },
		{ center_pos.x, center_pos.y - size },
		{ center_pos.x + size, center_pos.y },
		{ center_pos.x, center_pos.y + size },
	};

	drawlist->AddQuadFilled(positions[0], positions[1], positions[2], positions[3], ImColor(255, 255, 255, 150));
}

void CBrailleRenderer::render_invalid_char_marker(const ImVec2& char_pos)
{
	const auto drawlist = ImGui::GetWindowDrawList();

	const auto letter_size = get_letter_size();

	const float pad = 7.f;
	ImColor disabled_clr = ImColor(255, 255, 255, 75);

	drawlist->AddRect({ char_pos.x + pad, char_pos.y + pad },
					   { char_pos.x + letter_size.x - pad, char_pos.y + letter_size.y - pad },
					  disabled_clr,
					   2.f);

	const char* text = "?";
	const auto label_sz = ImGui::CalcTextSize(text);

	CGUIFontManager::get().render_text_ex(
		{
			char_pos.x + letter_size.x / 2.f - label_sz.x / 2.f,
			char_pos.y + letter_size.y / 2.f - label_sz.y / 2.f,
		},
		disabled_clr,
		CGUIFontManager::get().get_font("Default"),
		text);
}

void CBrailleRenderer::synchronize_translation_childs_scrollbars(bool regular_characters)
{
	// Scrollbar synchronization for both child windows. I didn't know how to implement this 
	// through valid imgui API, so i did this crap. It's a little bit sloppy however, it works.
	if (regular_characters) // Left side
	{
		if (m_translation_side_scroll[0] != ImGui::GetScrollY())
		{
			m_translation_side_scroll[0] = ImGui::GetScrollY();
		}
		else if (m_translation_side_scroll[0] != m_translation_side_scroll[1])
		{
			m_translation_side_scroll[0] = m_translation_side_scroll[1];
			ImGui::SetScrollY(m_translation_side_scroll[1]);
		}
	}
	else // Right side
	{
		if (m_translation_side_scroll[1] != ImGui::GetScrollY())
		{
			m_translation_side_scroll[1] = ImGui::GetScrollY();
		}
		else if (m_translation_side_scroll[1] != m_translation_side_scroll[0])
		{
			m_translation_side_scroll[1] = m_translation_side_scroll[0];
			ImGui::SetScrollY(m_translation_side_scroll[0]);
		}
	}
}

void CBrailleRenderer::render_letter_selection_rect(const ImVec2& pos, const ImColor& clr, bool is_filled)
{
	auto drawlist = ImGui::GetWindowDrawList();

	const auto letter_size = get_letter_size();

	if (is_filled)
	{
		ImGui::GetWindowDrawList()->AddRectFilled({ pos.x, pos.y },
												  { pos.x + letter_size.x, pos.y + letter_size.y },
												  clr, 4.f);
	}
	else
	{
		ImGui::GetWindowDrawList()->AddRect({ pos.x, pos.y },
											{ pos.x + letter_size.x, pos.y + letter_size.y },
											clr, 4.f);
	}
}

void CBrailleRenderer::increment_chraracter_pos(ImVec2& relative_pos)
{
	const auto letter_size = get_letter_size();

	float spacing_x = letter_size.x + StyleConstants::k_letter_spacing_x;
	float spacing_y = letter_size.y + StyleConstants::k_letter_spacing_y;

	relative_pos.x += spacing_x;

	// Handle newline
	if (relative_pos.x > m_max_avail_content.x - spacing_x)
	{
		relative_pos.x = 0.f;
		relative_pos.y += spacing_y;

		// We don't handle max available rendering content since we're rendering all
		// of the characters anyways. Perhaps ImGui is somehow filtering out of bounds
		// rendering to optimize stuff? Idk
	}
}

void CBrailleRenderer::handle_selection_shift_on_key_press(ImGuiKey key, const std::function<void()>& callback)
{
	if (CEventListener::get().is_key_pressed(key))
	{
		if (m_selected_letter_idx.get_position() != CSelectionCursor::invalid_index())
		{
			callback();
		}
	}
}

bool CBrailleRenderer::approved_prefix(EBraillePrefix prefix)
{
	if (!CSettings::get().m_render_prefixes)
		return false;

	switch (prefix)
	{
		case EBraillePrefix::Number:
			if (!CSettings::get().m_render_number_prefix)
				return false;
			break;

		case EBraillePrefix::SmallLetter:
			if (!CSettings::get().m_render_small_letter_prefix)
				return false;
			break;

		case EBraillePrefix::CapitalLetter:
			if (!CSettings::get().m_render_capital_letters_prefix)
				return false;
			break;

		case EBraillePrefix::CapitalLetterGroup:
			if (!CSettings::get().m_render_capital_letter_groups_prefix)
				return false;
			break;

		case EBraillePrefix::SmallGreek:
			if (!CSettings::get().m_render_small_greek_letters_prefix)
				return false;
			break;

		case EBraillePrefix::CapitalGreek:
			if (!CSettings::get().m_render_capital_greek_letters_prefix)
				return false;
			break;
	}

	return true;
}

void CSelectionCursor::shift_left()
{
	m_letter_idx--;

	if (m_letter_idx < 0)
		m_letter_idx += CBrailleRenderer::get().num_of_settingcared_chars();

	CConsole::get().output_message(std::format("Shifted left to {}", m_letter_idx));
}

void CSelectionCursor::shift_right()
{
	m_letter_idx++;

	if (m_letter_idx >= CBrailleRenderer::get().num_of_settingcared_chars())
		m_letter_idx -= CBrailleRenderer::get().num_of_settingcared_chars();

	CConsole::get().output_message(std::format("Shifted right to {}", m_letter_idx));
}

void CSelectionCursor::shift_up(uint32_t max_letter_per_line)
{
	int32_t prev_pos = m_letter_idx;

	m_letter_idx -= max_letter_per_line;

	if (m_letter_idx < 0)
	{
		uint32_t nFullLines = CBrailleRenderer::get().num_of_settingcared_chars() / max_letter_per_line;

		m_letter_idx = (nFullLines * max_letter_per_line) + prev_pos;

		if (m_letter_idx >= CBrailleRenderer::get().num_of_settingcared_chars())
			m_letter_idx -= max_letter_per_line;
	}

	CConsole::get().output_message(std::format("Shifted upwards to {}", m_letter_idx));
}

void CSelectionCursor::shift_down(uint32_t max_letter_per_line)
{
	int32_t prev_pos = m_letter_idx;

	m_letter_idx += max_letter_per_line;

	if (m_letter_idx >= CBrailleRenderer::get().num_of_settingcared_chars())
	{
		m_letter_idx = prev_pos % max_letter_per_line;

		//if (m_letter_idx == 0) // We're on the first line
		//	m_letter_idx += prev_pos;
	}

	CConsole::get().output_message(std::format("Shifted downwards to {}", m_letter_idx));
}
