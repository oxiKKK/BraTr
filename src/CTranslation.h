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
#ifndef BRATR_C_TRANSLATION_H
#define BRATR_C_TRANSLATION_H

#pragma once

struct translation_t
{
	ETranslationQuotes	m_idx;
	std::string			m_english;
	std::string			m_czech;
};

class CTranslation
{
public:
	template <uint32_t N> requires (N >= 0 && N < TRED_COUNT)
	static inline const char* Get()
	{
		switch (CSettings::get().m_language)
		{
			case LANGUAGE_ENGLISH:
				return m_translated_quotes[N].m_english.c_str();
			case LANGUAGE_CZECH:
				return m_translated_quotes[N].m_czech.c_str();
		}

		// Return english by default
		return m_translated_quotes[N].m_english.c_str();
	}

private:
	static std::array<translation_t, TRED_COUNT> m_translated_quotes;
};

#endif