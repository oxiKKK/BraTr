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
#include "CDialogManager.h"

void CDialogManager::display_error(const std::string& text)
{
	display_generic(text, CTranslation::Get<TRED_MSG_ERROR>(), MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
	CConsole::get().output_error(text);
	__debugbreak();
}

void CDialogManager::display_fatal_error(const std::string& text)
{
	display_generic(text, CTranslation::Get<TRED_MSG_ERROR>(), MB_OK | MB_ICONERROR | MB_DEFBUTTON1);
	__debugbreak();
	ExitProcess(1);
}

void CDialogManager::display_info(const std::string& text)
{
	display_generic(text, CTranslation::Get<TRED_MSG_INFO>(), MB_OK | MB_ICONINFORMATION | MB_DEFBUTTON1);
	CConsole::get().output_info(text);
}

void CDialogManager::display_generic(const std::string& text, const std::string& title, uint32_t dialog_type)
{
	uint32_t text_length = text.length() + 1;
	wchar_t *wtext = new wchar_t[text_length];
	MultiByteToWideChar(CP_UTF8, NULL, text.c_str(), text_length, wtext, text_length);

	uint32_t title_length = title.length() + 1;
	wchar_t *wtitle = new wchar_t[title_length];
	MultiByteToWideChar(CP_UTF8, NULL, title.c_str(), title_length, wtitle, title_length);
	
	MessageBoxW(NULL, wtext, wtitle, dialog_type);

	delete[] wtext;
	delete[] wtitle;
}
