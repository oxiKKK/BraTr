/*
 *       Copyright (c) 2022, oxiKKK
 *
 *   This program is licensed under the MIT license. By downloading, copying, or
 *    modifying, installing or using this software you agree to this license.
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
#ifndef BRATR_PCH_H
#define BRATR_PCH_H

#pragma once

#ifdef _DEBUG
#	define BUILD_MODE_STR	"debug"
#else
#	define BUILD_MODE_STR	"release"
#endif

#include "Versioning.h"

// for swprintf
#define _CRT_NON_CONFORMING_SWPRINTFS

#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

enum ELanguage
{
	LANGUAGE_ENGLISH,
	LANGUAGE_CZECH,
};

#include <Windows.h>
#include <filesystem>
#include <array>
#include <iostream>
#include <fstream>
#include <chrono>
#include <functional>
#include <deque>
#include <codecvt> // for std::codecvt_utf8
#include <locale>  // for std::wstring_convert

// A cross-platform library for file dialogs
#include <portable-file-dialogs/portable-file-dialogs.h>

// Rendering library
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl2.h>

// GLFW
#include <GLFW/glfw3.h>

// SOIL
#include <SOIL/SOIL.h>

// Translated strings into czech/english
#include "TranslationStrings.h"

// Character atlas where we define translations for each character
#include "BrailleCharacterAtlas.h"

// Our project files
#include "CUtils.h"
#include "CSettings.h"
#include "CTranslation.h"
#include "CConsole.h"
#include "CDialogManager.h"
#include "CGUI.h"
#include "CGUIFontManager.h"
#include "CBrailleParser.h"
#include "CFileSystem.h"
#include "CBrailleRenderer.h"
#include "CEventListener.h"
#include "CApplication.h"

// Compressed fonts
extern const unsigned int arial_font_compressed_size;
extern const unsigned int arial_font_compressed_data[707164 / 4];

// Icon PNG raw file data
extern const unsigned char s_icon_file_png_bin_data[820];

#endif