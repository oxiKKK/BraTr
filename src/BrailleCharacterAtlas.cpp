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
#include "bratr_pch.h"

const BrailleAtlasElement_t BrailleAtlas::get_element(const wchar_t character, bool& not_found_in_atlas)
{
	not_found_in_atlas = false;
	
	try
	{
		return s_braille_char_atlas.at(character);
	}
	catch (...)
	{
		not_found_in_atlas = true;
	}

	// Return blank letter. We'll handle this inside the renderer by rendering
	// Invalid character for characters that aren't inside the atlas.
	static BrailleAtlasElement_t dummy;
	return dummy;
}

const BraillePrefixAtlasElement_t BrailleAtlas::get_prefix_element(EBraillePrefix prefix)
{
	try
	{
		return s_braille_prefix_atlas.at(prefix);
	}
	catch (...)
	{
		CDialogManager::get().display_fatal_error("Prefix not inside the list");
	}

	// Return something just to shut up compiler
	static BraillePrefixAtlasElement_t dummy;
	return dummy;
}

const std::unordered_map<EBraillePrefix, BraillePrefixAtlasElement_t> BrailleAtlas::s_braille_prefix_atlas =
{
	{
		{ EBraillePrefix::None,					{ 0b00000000 } }, 
		{ EBraillePrefix::Number,				{ 0b00111010 } },
		{ EBraillePrefix::SmallLetter,			{ 0b00001000 } },
		{ EBraillePrefix::CapitalLetter,		{ 0b00100000 } },
		{ EBraillePrefix::CapitalLetterGroup,	{ 0b00101000 } },
		{ EBraillePrefix::SmallGreek,			{ 0b00001010 } },
		{ EBraillePrefix::CapitalGreek,			{ 0b00100010 } },
	}
};

// Mark characters that are undefined. This is just for convience since
// invalid characters won't render anymore.
#define CHAR_UNDEF 0b00111111

const std::unordered_map<wchar_t, BrailleAtlasElement_t> BrailleAtlas::s_braille_char_atlas =
{
	{
		{ L'\n', { 0b00000000 } },

		{ L' ',  { 0b00000000 } },
		{ L'!',  { 0b00011100 } },
		{ L'\"', { 0b00111100 } },
		{ L'#',  { CHAR_UNDEF } },
		{ L'$',  { CHAR_UNDEF } },
		{ L'%',  { CHAR_UNDEF } },
		{ L'&',  { CHAR_UNDEF } },
		{ L'\'', { 0b00000010 } },
		{ L'(',  { 0b00110100 } },
		{ L')',  { 0b00111000 } },
		{ L'*',  { 0b00011000 } },
		{ L'+',  { 0b00101100 } },
		{ L',',  { 0b00000100 } },
		{ L'-',  { 0b00110000 } },
		{ L'.',  { 0b00010000 } },
		{ L'/',  { 0b00101111 } },

		{ L'0',  { 0b00001110, EBraillePrefix::Number } },
		{ L'1',  { 0b00000001, EBraillePrefix::Number } },
		{ L'2',  { 0b00000101, EBraillePrefix::Number } },
		{ L'3',  { 0b00000011, EBraillePrefix::Number } },
		{ L'4',  { 0b00001011, EBraillePrefix::Number } },
		{ L'5',  { 0b00001001, EBraillePrefix::Number } },
		{ L'6',  { 0b00000111, EBraillePrefix::Number } },
		{ L'7',  { 0b00001111, EBraillePrefix::Number } },
		{ L'8',  { 0b00001101, EBraillePrefix::Number } },
		{ L'9',  { 0b00000110, EBraillePrefix::Number } },

		{ L':',  { 0b00001100 } },
		{ L';',  { 0b00010100 } },
		{ L'<',  { 0b00100101 } },
		{ L'=',  { 0b00111100 } },
		{ L'>',  { 0b00011010 } },
		{ L'?',  { 0b00101000 } },
		{ L'@',  { CHAR_UNDEF } },

		{ L'A',  { 0b00000001, EBraillePrefix::CapitalLetter } },
		{ L'B',  { 0b00000101, EBraillePrefix::CapitalLetter } },
		{ L'C',  { 0b00000011, EBraillePrefix::CapitalLetter } },
		{ L'D',  { 0b00001011, EBraillePrefix::CapitalLetter } },
		{ L'E',  { 0b00001001, EBraillePrefix::CapitalLetter } },
		{ L'F',  { 0b00000111, EBraillePrefix::CapitalLetter } },
		{ L'G',  { 0b00001111, EBraillePrefix::CapitalLetter } },
		{ L'H',  { 0b00001101, EBraillePrefix::CapitalLetter } },
		{ L'I',  { 0b00000110, EBraillePrefix::CapitalLetter } },
		{ L'J',  { 0b00001110, EBraillePrefix::CapitalLetter } },
		{ L'K',  { 0b00010001, EBraillePrefix::CapitalLetter } },
		{ L'L',  { 0b00010101, EBraillePrefix::CapitalLetter } },
		{ L'M',  { 0b00010011, EBraillePrefix::CapitalLetter } },
		{ L'N',  { 0b00011011, EBraillePrefix::CapitalLetter } },
		{ L'O',  { 0b00011001, EBraillePrefix::CapitalLetter } },
		{ L'P',  { 0b00010111, EBraillePrefix::CapitalLetter } },
		{ L'Q',  { 0b00011111, EBraillePrefix::CapitalLetter } },
		{ L'R',  { 0b00011101, EBraillePrefix::CapitalLetter } },
		{ L'S',  { 0b00010110, EBraillePrefix::CapitalLetter } },
		{ L'T',  { 0b00011110, EBraillePrefix::CapitalLetter } },
		{ L'U',  { 0b00110001, EBraillePrefix::CapitalLetter } },
		{ L'V',  { 0b00110101, EBraillePrefix::CapitalLetter } },
		{ L'W',  { 0b00111101, EBraillePrefix::CapitalLetter } },
		{ L'X',  { 0b00110011, EBraillePrefix::CapitalLetter } },
		{ L'Y',  { 0b00111011, EBraillePrefix::CapitalLetter } },
		{ L'Z',  { 0b00111001, EBraillePrefix::CapitalLetter } },

		{ L'[',  { CHAR_UNDEF } },
		{ L'\\', { CHAR_UNDEF } },
		{ L']',  { CHAR_UNDEF } },
		{ L'^',  { CHAR_UNDEF } },
		{ L'_',  { CHAR_UNDEF } },
		{ L'`',  { CHAR_UNDEF } },

		{ L'a',  { 0b00000001, EBraillePrefix::SmallLetter } },
		{ L'b',  { 0b00000101, EBraillePrefix::SmallLetter } },
		{ L'c',  { 0b00000011, EBraillePrefix::SmallLetter } },
		{ L'd',  { 0b00001011, EBraillePrefix::SmallLetter } },
		{ L'e',  { 0b00001001, EBraillePrefix::SmallLetter } },
		{ L'f',  { 0b00000111, EBraillePrefix::SmallLetter } },
		{ L'g',  { 0b00001111, EBraillePrefix::SmallLetter } },
		{ L'h',  { 0b00001101, EBraillePrefix::SmallLetter } },
		{ L'i',  { 0b00000110, EBraillePrefix::SmallLetter } },
		{ L'j',  { 0b00001110, EBraillePrefix::SmallLetter } },
		{ L'k',  { 0b00010001, EBraillePrefix::SmallLetter } },
		{ L'l',  { 0b00010101, EBraillePrefix::SmallLetter } },
		{ L'm',  { 0b00010011, EBraillePrefix::SmallLetter } },
		{ L'n',  { 0b00011011, EBraillePrefix::SmallLetter } },
		{ L'o',  { 0b00011001, EBraillePrefix::SmallLetter } },
		{ L'p',  { 0b00010111, EBraillePrefix::SmallLetter } },
		{ L'q',  { 0b00011111, EBraillePrefix::SmallLetter } },
		{ L'r',  { 0b00011101, EBraillePrefix::SmallLetter } },
		{ L's',  { 0b00010110, EBraillePrefix::SmallLetter } },
		{ L't',  { 0b00011110, EBraillePrefix::SmallLetter } },
		{ L'u',  { 0b00110001, EBraillePrefix::SmallLetter } },
		{ L'v',  { 0b00110101, EBraillePrefix::SmallLetter } },
		{ L'w',  { 0b00111101, EBraillePrefix::SmallLetter } },
		{ L'x',  { 0b00110011, EBraillePrefix::SmallLetter } },
		{ L'y',  { 0b00111011, EBraillePrefix::SmallLetter } },
		{ L'z',  { 0b00111001, EBraillePrefix::SmallLetter } },

		{ L'{',  { 0b00000000 } },
		{ L'|',  { 0b00101010 } },
		{ L'}',  { 0b00000000 } },
		{ L'~',  { 0b00000000 } },

		{ L'á',  { 0b00100001, EBraillePrefix::SmallLetter } },
		{ L'č',  { 0b00100011, EBraillePrefix::SmallLetter } },
		{ L'ď',  { 0b00101011, EBraillePrefix::SmallLetter } },
		{ L'é',  { 0b00011010, EBraillePrefix::SmallLetter } },
		{ L'ě',  { 0b00100101, EBraillePrefix::SmallLetter } },
		{ L'í',  { 0b00010010, EBraillePrefix::SmallLetter } },
		{ L'ň',  { 0b00100111, EBraillePrefix::SmallLetter } },
		{ L'ó',  { 0b00100110, EBraillePrefix::SmallLetter } },
		{ L'ř',  { 0b00101110, EBraillePrefix::SmallLetter } },
		{ L'š',  { 0b00101001, EBraillePrefix::SmallLetter } },
		{ L'ť',  { 0b00101101, EBraillePrefix::SmallLetter } },
		{ L'ú',  { 0b00110010, EBraillePrefix::SmallLetter } },
		{ L'ů',  { 0b00111110, EBraillePrefix::SmallLetter } },
		{ L'ý',  { 0b00110111, EBraillePrefix::SmallLetter } },
		{ L'ž',  { 0b00110110, EBraillePrefix::SmallLetter } },

		{ L'Á',  { 0b00100001, EBraillePrefix::CapitalLetter } },
		{ L'Č',  { 0b00100011, EBraillePrefix::CapitalLetter } },
		{ L'Ď',  { 0b00101011, EBraillePrefix::CapitalLetter } },
		{ L'É',  { 0b00011010, EBraillePrefix::CapitalLetter } },
		{ L'Ě',  { 0b00100101, EBraillePrefix::CapitalLetter } },
		{ L'Í',  { 0b00010010, EBraillePrefix::CapitalLetter } },
		{ L'Ň',  { 0b00100111, EBraillePrefix::CapitalLetter } },
		{ L'Ó',  { 0b00100110, EBraillePrefix::CapitalLetter } },
		{ L'Ř',  { 0b00101110, EBraillePrefix::CapitalLetter } },
		{ L'Š',  { 0b00101001, EBraillePrefix::CapitalLetter } },
		{ L'Ť',  { 0b00101101, EBraillePrefix::CapitalLetter } },
		{ L'Ú',  { 0b00110010, EBraillePrefix::CapitalLetter } },
		{ L'Ů',  { 0b00111110, EBraillePrefix::CapitalLetter } },
		{ L'Ý',  { 0b00110111, EBraillePrefix::CapitalLetter } },
		{ L'Ž',  { 0b00110110, EBraillePrefix::CapitalLetter } },
	}
};
