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
#ifndef BRATR_C_FILESYSTEM_H
#define BRATR_C_FILESYSTEM_H

#pragma once

class CFileSystem
{
public:
	// Returns an static instance of this particular class
	static inline CFileSystem& get()
	{
		static CFileSystem fs;
		return fs;
	}

public:
	// Creates subdirectories...
	void init();

	const std::filesystem::path& get_specific_dir(const std::string& dir);
	std::filesystem::path get_file_inside_dir(const std::string& dir, const std::string& filename);
	const std::filesystem::path& get_base_dir();

private:
	// Takes our saved directories and creates them if they don't exist
	void validate_dirs();

private:
	std::map<std::string, std::filesystem::path> m_dirs;
};

#endif