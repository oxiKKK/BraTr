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

void CPlatform::get_desktop_resolution(int32_t& width, int32_t& height)
{
	RECT desktop;

	if (!::GetWindowRect(::GetDesktopWindow(), &desktop))
	{
		CDialogManager::get().display_fatal_error(std::format("{} (error {})", 
															  CTranslation::Get<TRED_ERR_DESKTOP_RESOLUTION>(), 
															  ::GetLastError()));
		return;
	}

	width = desktop.right;
	height = desktop.bottom;
}