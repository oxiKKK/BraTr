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
#ifndef BRATR_ERROR_CODES_H
#define BRATR_ERROR_CODES_H

#pragma once

enum ETranslationQuotes
{
	// Errors

	TRED_ERR_APP_FAIL,
	TRED_ERR_GLFW_INIT,
	TRED_ERR_GLFW_CREATE_WINDOW,
	TRED_ERR_IMGUI_CONTEXT,
	TRED_ERR_IMGUI_GLFW,
	TRED_ERR_IMGUI_OPGL2,
	TRED_ERR_WINDOW_ICON,
	TRED_ERR_FONT_NOT_FOUND,
	TRED_ERR_ICON_FILE_NOT_FOUND,
	TRED_ERR_COULDNT_CREATE_DIR,
	TRED_ERR_COULDNT_READ_FILE,
	TRED_ERR_CHARACTER_WITHOUT_TRANSLATION,
	TRED_ERR_COULDNT_OPEN_FILE,
	TRED_ERR_DESKTOP_RESOLUTION,

	// Miscellaneous

	TRED_MSG_FATAL_ERROR,
	TRED_MSG_ERROR,
	TRED_MSG_INFO,

	TRED_TITLE,

	// GUI

	TRED_GUI_FILE,
	TRED_GUI_OPEN,
	TRED_GUI_CLOSE,
	TRED_GUI_PREFERENCES,

	TRED_GUI_HIDE_LEFT_SIDE,
	TRED_GUI_RENDER_HOVER_TOOLTIP,

	TRED_GUI_FONT_SIZE,
	TRED_GUI_FONT_SIZE_SMALL,
	TRED_GUI_FONT_SIZE_MEDIUM,
	TRED_GUI_FONT_SIZE_BIG,

	TRED_GUI_SPECIAL_PREFIXES,
	TRED_GUI_RENDER_SPECIAL_PREFIXES,
	TRED_GUI_RENDER_NUMBERS_PREFIX,
	TRED_GUI_RENDER_SMALL_LETTER_PREFIX,
	TRED_GUI_RENDER_CAPITAL_LETTERS_PREFIX,
	TRED_GUI_RENDER_CAPITAL_LETTERS_GROUP_PREFIX,
	TRED_GUI_RENDER_SMALL_GREEK_LETTER_PREFIX,
	TRED_GUI_RENDER_CAPITAL_GREEK_LETTER_PREFIX,

	TRED_GUI_ABOUT,
	TRED_GUI_ABOUT_COMPILED_AT,

	// Others

	TRED_GUI_LANGUAGE,
	TRED_GUI_LANGUAGE_ENGLISH,
	TRED_GUI_LANGUAGE_CZECH,

	TRED_COUNT
};

#endif
