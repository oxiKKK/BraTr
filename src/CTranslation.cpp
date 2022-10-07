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

// Add /Zc:char8_t- to avoid errors with u8
std::array<translation_t, TRED_COUNT> CTranslation::m_translated_quotes =
{
	{
		// Errors

		{ TRED_ERR_APP_FAIL, "Failed to start application", u8"Nepodařilo se spustit program" },
		{ TRED_ERR_GLFW_INIT, "Failed to init glfw", u8"Nepodařilo se initializovat glfw" },
		{ TRED_ERR_GLFW_CREATE_WINDOW, "Failed to create glfw window", u8"Nepodařilo se otevřít okno glfw" },
		{ TRED_ERR_IMGUI_CONTEXT, "Failed to create imgui context", u8"Nepodařilo se vytvořit kontext imgui" },
		{ TRED_ERR_IMGUI_GLFW, "Failed to init glfw opengl for imgui", u8"Nepodařilo se initializovat glfw pro imgui" },
		{ TRED_ERR_IMGUI_OPGL2, "Failed to init opengl for imgui", u8"Nepodařilo se initializovat opengl pro imgui" },
		{ TRED_ERR_WINDOW_ICON, "Failed to set window icon", u8"Nepodařilo se nastavit ikonu okna" },
		{ TRED_ERR_FONT_NOT_FOUND, "Font not found", u8"Nepodařilo se najít písmo" },
		{ TRED_ERR_ICON_FILE_NOT_FOUND, "Icon file not found", u8"Nepodařilo se najít soubor pro ikonu programu" },
		{ TRED_ERR_COULDNT_CREATE_DIR, "Couldn't create directory", u8"Nepodařilo se vytvořit podsložku" },
		{ TRED_ERR_COULDNT_READ_FILE, "Couldn't read file contents", u8"Nepodařilo se číst ze souboru" },
		{ TRED_ERR_CHARACTER_WITHOUT_TRANSLATION, "This character doesn't have translation support", u8"Toto písmeno ještě nemá podporovaný překlad v braillově písmu" },
		{ TRED_ERR_PREVIOUS_INPUT_FILE_NOT_FOUND, "Couldn't locate previously saved file. Please, open new file.", u8"Nepodařilo se najít napoředy uložený soubor. Prosím, otevřete nový." },
		{ TRED_ERR_COULDNT_OPEN_FILE, "Couldn't open file", u8"Nepodařilo se otevřít soubor" },
		{ TRED_ERR_DESKTOP_RESOLUTION, "Couldn't get desktop resolution", u8"Nepodařilo se zíkat rozlišení plochy" },

		// Miscellaneous

		{ TRED_MSG_FATAL_ERROR, "Fatal error", u8"Fatální chyba" },
		{ TRED_MSG_ERROR, "Error", u8"Chyba" },
		{ TRED_MSG_INFO, "Info", u8"Informace" },

		{ TRED_TITLE, "Braille translator", u8"Braillův překladač" },

		// GUI

		{ TRED_GUI_FILE, "File", u8"Soubor" },
		{ TRED_GUI_OPEN, "Open", u8"Otevřít" },
		{ TRED_GUI_CLOSE, "Close", u8"Zavřít" },
		{ TRED_GUI_PREFERENCES, "Preferences", u8"Možnosti" },

		{ TRED_GUI_HIDE_LEFT_SIDE, "Hide left side", u8"Schovat levou stranu" },
		{ TRED_GUI_RENDER_HOVER_TOOLTIP, "Render character code", u8"Zobrazovat kód znaku" },
		{ TRED_GUI_SHOW_INPUT_FILE_NEXT_TIME, "Remember this file", u8"Zapamatovat soubor" },

		{ TRED_GUI_FONT_SIZE, "Font size", u8"Velikost písma" },
		{ TRED_GUI_FONT_SIZE_SMALL, "Small", u8"Malé" },
		{ TRED_GUI_FONT_SIZE_MEDIUM, "Medium", u8"Střední" },
		{ TRED_GUI_FONT_SIZE_BIG, "Big", u8"Velké" },

		{ TRED_GUI_SPECIAL_PREFIXES, "Special prefixes", u8"Speciální prefixy" },
		{ TRED_GUI_RENDER_SPECIAL_PREFIXES, "Render special prefixes", u8"Vykreslovat speciální prefixy" },
		{ TRED_GUI_RENDER_NUMBERS_PREFIX, "Numbers", u8"Čísla" },
		{ TRED_GUI_RENDER_SMALL_LETTER_PREFIX, "Small letters", u8"Malé písmena" },
		{ TRED_GUI_RENDER_CAPITAL_LETTERS_PREFIX, "Capital letters", u8"Velké písmena" },
		{ TRED_GUI_RENDER_CAPITAL_LETTERS_GROUP_PREFIX, "Capital letter groups", u8"Skupiny velkých písmen" },
		{ TRED_GUI_RENDER_SMALL_GREEK_LETTER_PREFIX, "Small greek letters", u8"Malá řecká písmena" },
		{ TRED_GUI_RENDER_CAPITAL_GREEK_LETTER_PREFIX, "Capital greek letters", u8"Velká řecká písmena" },

		{ TRED_GUI_ABOUT, "About", u8"O programu" },
		{ TRED_GUI_ABOUT_COMPILED_AT, "Compiled at", u8"Kompilováno dne" },

		// Others

		{ TRED_GUI_LANGUAGE, "Language", u8"Jazyk" },
		{ TRED_GUI_LANGUAGE_ENGLISH, "English", u8"Angličtina" },
		{ TRED_GUI_LANGUAGE_CZECH, "Czech", u8"Čeština" },
	}
};