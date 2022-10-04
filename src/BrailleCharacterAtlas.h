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
#ifndef BRATR_BRAILLE_CHARACTER_ATLAS_H
#define BRATR_BRAILLE_CHARACTER_ATLAS_H

enum class EBraillePrefix : uint32_t
{
	None, 
	Number, 
	SmallLetter,
	CapitalLetter,
	CapitalLetterGroup,
	SmallGreek,
	CapitalGreek,
};

// An element for the prefixes. This is used
// inside the prefix atlas.
struct BraillePrefixAtlasElement_t
{
	uint8_t bits; // Bits for this prefix
};

// An element for the regular characters. This
// is used inside the regular translation atlas.
struct BrailleAtlasElement_t
{
	BrailleAtlasElement_t(uint8_t _bits, EBraillePrefix _prefix = EBraillePrefix::None) :
		bits(_bits), 
		prefix(_prefix)
	{}

	BrailleAtlasElement_t() :
		bits(0b00000000), 
		prefix(EBraillePrefix::None)
	{}

	uint8_t			bits;	// Bits for this particular character
	EBraillePrefix	prefix;	// Braille prefix, if any
};

class BrailleAtlas
{
public:
	static const BrailleAtlasElement_t get_element(const wchar_t character, bool& not_found_in_atlas);
	static const BraillePrefixAtlasElement_t get_prefix_element(EBraillePrefix prefix);

	static const std::unordered_map<EBraillePrefix, BraillePrefixAtlasElement_t> s_braille_prefix_atlas;
	static const std::unordered_map<wchar_t, BrailleAtlasElement_t> s_braille_char_atlas;
};
#endif