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

bool CBrailleParser::update()
{
	// Update file contents in our buffer
	if (!reload_file_contents())
		return false;
	
	return true;
}

bool CBrailleParser::reload_file_contents()
{
	// Run contents of this funtion every # ms
	if (std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::high_resolution_clock::now() - m_load_time).count() < 500)
		return true;

	m_precached_chars.clear();

	// Get the file path we've selected in our GUI
	const auto input_filepath = CGUI::get().get_input_file();

	// If the file is empty, perhaps we didn't select any
	if (!input_filepath.empty())
	{
		// Update the file contents
		read_file_contents(input_filepath);

		// Now take the file contents and process individual character
		process_characters();

		CConsole::get().output_message("Reloaded file");
	}

	m_load_time = std::chrono::high_resolution_clock::now();

	return true;
}

void CBrailleParser::read_file_contents(const std::filesystem::path& filepath)
{
	std::wifstream wifs(filepath, std::ios_base::in);

	// Clear the buffer first before another read operation.
	m_file_buffer.clear();

	// if the file's bad, just don't read it. This scenario can happen when user
	// opens some file and then renames or removes the original file on the disk.
	// Or also when the user opens a file from the previously opened files list
	// that no longer exists.
	if (!wifs.good())
	{
		CConsole::get().output_error(std::format("Couldn't read from a file: {}", filepath.string()));
		CGUI::get().clear_input_file();
		return;
	}

	wifs.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));

	// Read the entire contents of the file to this buffer
	std::wstringstream wss;
	wss << wifs.rdbuf();
	m_file_buffer = wss.str();

	wifs.close();
}

void CBrailleParser::process_characters()
{ 
	// Used to prevent infinite looping from happening
	bool prefix_already_added = false;

	// Real character indicates the position inside the file. It
	// doesn't count added prefixes, while n_char does.
	uint32_t n_char = 0, n_real_char = 0;
	while (n_real_char < m_file_buffer.size())
	{
		const wchar_t ch = m_file_buffer[n_real_char];

		bool not_found_in_atlas = false;

		// Get the braille character from our translation table
		const auto& character_element = BrailleAtlas::get_element(ch, not_found_in_atlas);

		// Process character with a prefix. If there's one, it'll be added
		// into the list as others, however with a blank character.
		if (character_element.prefix != EBraillePrefix::None && !prefix_already_added)
		{
			// Now return the prefix braille character
			const auto& character_prefix = BrailleAtlas::get_prefix_element(character_element.prefix);

			// Add it into the list with blank character but with prefix bits
			m_precached_chars.emplace_back(L'-', n_char, 0b00000000, character_prefix.bits, character_element.prefix, not_found_in_atlas);

			n_char++;
			prefix_already_added = true;
			continue;
		}

		// Add the actual character
		m_precached_chars.emplace_back(ch, n_char, character_element.bits, 0b00000000, EBraillePrefix::None, not_found_in_atlas);

		n_char++;
		n_real_char++;

		prefix_already_added = false;
	}

	m_num_of_non_prefix_characters = n_real_char;
}
