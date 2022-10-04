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

void CEventListener::register_listener()
{
	m_registered_keys.emplace_back(ImGuiKey_LeftArrow);
	m_registered_keys.emplace_back(ImGuiKey_RightArrow);
	m_registered_keys.emplace_back(ImGuiKey_UpArrow);
	m_registered_keys.emplace_back(ImGuiKey_DownArrow);

	m_registered_mouse_buttons.emplace_back(ImGuiMouseButton_Left);
	m_registered_mouse_buttons.emplace_back(ImGuiMouseButton_Right);

	CConsole::get().output_message("Registered all input events");
}

void CEventListener::listen()
{
	for (const auto& key : m_registered_keys)
	{
		m_key_pressed[key - ImGuiKey_NamedKey_BEGIN] = ImGui::IsKeyPressed(key);

		if (m_key_pressed[key - ImGuiKey_NamedKey_BEGIN])
			CConsole::get().output_message(std::format("Pressed key {}", ImGui::GetKeyName(key)));
	}

	for (const auto& mb : m_registered_mouse_buttons)
	{
		m_mouse_button_pressed[mb] = ImGui::IsMouseClicked(mb);

		if (m_mouse_button_pressed[mb])
			CConsole::get().output_message(std::format("Pressed mouse button {}", get_mbutton_name(mb)));
	}
}

std::string CEventListener::get_mbutton_name(ImGuiMouseButton MouseButton) const
{
	switch (MouseButton)
	{
		case ImGuiMouseButton_Left: return "Left Mouse Button";
		case ImGuiMouseButton_Right: return "Right Mouse Button";
		case ImGuiMouseButton_Middle: return "Middle Mouse Button";
	}

	return "Unknown";
}
