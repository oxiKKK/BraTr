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

const ImWchar GlyphContainer::s_czech[] =
{
	0x0020, 0x017F, // Basic Latin + Latin Supplement
	0x0100, 0x017F, // Latin Extended-A
	0,
};

bool CGUIFontManager::precache_fonts(ImGuiIO& io)
{
	// The first font precached is the font used by imgui by default
	m_precached_fonts["Default"] = try_to_precache(io, arial_font_compressed_data, arial_font_compressed_size, 15.f, GlyphContainer::s_czech);
	m_precached_fonts["Small"] = try_to_precache(io, arial_font_compressed_data, arial_font_compressed_size, 20.f, GlyphContainer::s_czech);
	m_precached_fonts["Medium"] = try_to_precache(io, arial_font_compressed_data, arial_font_compressed_size, 25.f, GlyphContainer::s_czech);
	m_precached_fonts["Big"] = try_to_precache(io, arial_font_compressed_data, arial_font_compressed_size, 35.f, GlyphContainer::s_czech);

	CConsole::get().output_message("Precached all GUI fonts");

	return true;
}

ImFont* CGUIFontManager::get_font(const std::string& font_name)
{
	try
	{
		return m_precached_fonts.at(font_name);
	}
	catch (...)
	{
		CDialogManager::get().display_fatal_error("Font name not inside the list");
	}

	return nullptr;
}

ImFont* CGUIFontManager::get_active_font()
{
	return m_active_font;
}

ImFont* CGUIFontManager::try_to_precache(ImGuiIO& io, const void* compressed_ttf_data,
										 uint32_t compressed_size, float font_size,
										 const ImWchar* glyph_ranges)
{
	ImFont* p_font = io.Fonts->AddFontFromMemoryCompressedTTF(
		compressed_ttf_data,
		compressed_size,
		font_size,
		nullptr,
		glyph_ranges);

	// Font most likely not found
	if (!p_font)
	{
		CDialogManager::get().display_fatal_error(CTranslation::get<TRED_ERR_FONT_NOT_FOUND>());
		return nullptr;
	}

	CConsole::get().output_message(std::format("Precached font of size: {} bytes", compressed_size));

	return p_font;
}

void CGUIFontManager::update_active_font()
{
	ImFont* p_font;

	switch (CSettings::get().m_font_size)
	{
		case SETTINGS_FONT_SMALL:
			p_font = get_font("Small");
			break;

			// If no font settings specified, apply medium by default
		default:
		case SETTINGS_FONT_MEDIUM:
			p_font = get_font("Medium");
			break;

		case SETTINGS_FONT_BIG:
			p_font = get_font("Big");
			break;
	}

	m_active_font = p_font;
}

void CGUIFontManager::render_text_u8(const ImVec2& pos, ImColor clr, const char* ptext, ...)
{
	const auto active_font = get_active_font();

	char buf[1024];
	va_list va_alist;
	va_start(va_alist, ptext);
	_vsnprintf_s(buf, sizeof(buf), ptext, va_alist);
	va_end(va_alist);

	const auto drawlist = ImGui::GetWindowDrawList();
	drawlist->AddText(active_font,
					  active_font->FontSize,
					  pos,
					  clr,
					  buf);
}

void CGUIFontManager::render_text_u16(const ImVec2& pos, ImColor clr, const wchar_t* ptext, ...)
{
	const auto active_font = get_active_font();

	// We need to first covert this unicode to utf-8
	char sztext[1024];
	unicode_to_utf8(ptext, sztext, sizeof(sztext));

	// Process variadic arguments
	char szbuf[1024];
	va_list va_alist;
	va_start(va_alist, sztext);
	_vsnprintf_s(szbuf, sizeof(szbuf), sztext, va_alist);
	va_end(va_alist);

	const auto drawlist = ImGui::GetWindowDrawList();
	drawlist->AddText(active_font,
					  active_font->FontSize,
					  pos,
					  clr,
					  szbuf);
}

void CGUIFontManager::render_text_ex(const ImVec2& pos, ImColor clr, ImFont* p_font, const char* ptext)
{
	// Process variadic arguments
	char buf[1024];
	va_list va_alist;
	va_start(va_alist, ptext);
	_vsnprintf_s(buf, sizeof(buf), ptext, va_alist);
	va_end(va_alist);

	const auto pDrawlist = ImGui::GetWindowDrawList();
	pDrawlist->AddText(p_font,
					   p_font->FontSize,
					   pos,
					   clr,
					   buf);
}

void CGUIFontManager::unicode_to_utf8(const wchar_t* wbuf, char* sbuf, uint32_t buf_len)
{
	WideCharToMultiByte(CP_UTF8, NULL, wbuf, buf_len, sbuf, buf_len, nullptr, nullptr);
}