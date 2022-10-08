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

bool CUtils::is_rect_hovered(const ImVec2& rect, const ImVec2& size)
{
	return (ImGui::GetMousePos().x > rect.x && ImGui::GetMousePos().x < rect.x + size.x) &&
		(ImGui::GetMousePos().y > rect.y && ImGui::GetMousePos().y < rect.y + size.y);
}

bool CUtils::is_newline(const char c)
{ 
	return c == '\n'; 
}

bool CUtils::is_valid_ascii(const char c)
{ 
	return c >= ' ' && c <= '~'; 
}

std::string CUtils::get_current_module_path()
{
	char buf[MAX_PATH];
	GetModuleFileNameA(NULL, buf, sizeof(buf));

	return buf;
}
