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
#ifndef BRATR_C_PARSER_H
#define BRATR_C_PARSER_H

#pragma once

class Character
{
public:
	Character(wchar_t unicode_char, uint32_t idx, uint8_t braille_bits,
			  uint8_t braille_prefix_bits, EBraillePrefix prefix_type, bool not_found_in_atlas) :
		m_braille_bits(braille_bits),
		m_braille_prefix_bits(braille_prefix_bits),
		m_unicode_character(unicode_char),
		m_prefix_type(prefix_type),
		m_index(idx),
		m_not_found_in_atlas(not_found_in_atlas)
	{}

public:
	inline bool has_prefix() const
	{
		return m_braille_prefix_bits != 0 && m_prefix_type != EBraillePrefix::None;
	}

public:
	uint8_t			m_braille_bits = 0b00000000;
	uint8_t			m_braille_prefix_bits = 0b00000000;
	wchar_t			m_unicode_character = 0;
	EBraillePrefix	m_prefix_type = EBraillePrefix::None;
	uint32_t		m_index = 0;
	bool			m_not_found_in_atlas = false;
};

class CBrailleParser
{
private:
	using timepoint_t = std::chrono::high_resolution_clock::time_point;

public:
	// Returns an static instance of this particular class
	static inline CBrailleParser& get()
	{
		static CBrailleParser parser;
		return parser;
	}

public:
	bool update();

	inline const auto& get_precached_chars() const { return m_precached_chars; }

	inline uint32_t get_num_of_non_precached_chars() const { return m_num_of_non_prefix_characters; };

private:
	bool reload_file_contents();
	void read_file_contents(const std::filesystem::path& filepath);

	void process_characters();

private:
	std::vector<Character>		m_precached_chars;
	std::wstring				m_file_buffer;
	timepoint_t					m_load_time = std::chrono::high_resolution_clock::now();
	uint32_t					m_num_of_non_prefix_characters;
};

#endif