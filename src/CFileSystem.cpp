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

void CFileSystem::init()
{
	// Retrieves the '%appdata%Roaming\\BraTr' path
	PWSTR w_appdata_roaming_data[MAX_PATH];
	::SHGetKnownFolderPath(FOLDERID_RoamingAppData, KF_FLAG_DEFAULT, NULL, w_appdata_roaming_data);

	std::filesystem::path base_dir = std::wstring(*w_appdata_roaming_data) + L"\\BraTr";

	CConsole::get().output_message(std::format("Base filystem directory is: {}", base_dir.string()));

	m_dirs["Base"] = base_dir;
	m_dirs["Settings"] = base_dir.string() + "\\Settings";

	// Create directories if they don't exist
	validate_dirs();

	CConsole::get().output_message("Initialized file system");
}

const std::filesystem::path& CFileSystem::get_specific_dir(const std::string& dir)
{
	try
	{
		return m_dirs.at(dir);
	}
	catch (...)
	{
		CDialogManager::get().display_fatal_error("Directory name not inside the list");
	}

	// In case we fail, return base directory
	return m_dirs.at("Base");
}

std::filesystem::path CFileSystem::get_file_inside_dir(const std::string& dir, const std::string& filename)
{
	return get_specific_dir(dir).string() + '\\' + filename;
}

const std::filesystem::path& CFileSystem::get_base_dir()
{
	return m_dirs.at("Base");
}

void CFileSystem::validate_dirs()
{
	// Go through all the directories and create them if they don't exist
	for (const auto& [Key, Dir] : m_dirs)
	{
		if (std::filesystem::exists(Dir))
			continue;

		// Try to create the directory
		if (!std::filesystem::create_directory(Dir))
			CDialogManager::get().display_fatal_error(std::format("{} ({})", CTranslation::Get<TRED_ERR_COULDNT_CREATE_DIR>(), Dir.string().c_str()));

		CConsole::get().output_message(std::format("Creating directory {}", Dir.string().c_str()));
	}
}
