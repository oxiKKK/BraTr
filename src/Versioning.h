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
#ifndef BRATR_VERSIONING_H
#define BRATR_VERSIONING_H

#pragma once

// Versioning of the BRATR program is based on Semantic Versioning 
// which can be found here:
//	https://semver.org
//
// In summary:
// -	The major version represend a big update, i.e. API changes or
//		 code architecture changes that are incompatible with the last
//		 version of the program.
// -	The minor version is versioning between major updates. Incre-
//		 ment this whether we're doing some changes to the program.
// -	The patch is for bugfixes in minor/major program releases.

#define BRATR_V_MAJOR_S "0"
#define BRATR_V_MINOR_S "1"
#define BRATR_V_PATCH_S "0"

#define BRATR_V_MAJOR   0
#define BRATR_V_MINOR   1
#define BRATR_V_PATCH   0

// Adds everything up in a syntax: major.minor.patch
#define BRATR_VERSION BRATR_V_MAJOR_S "." BRATR_V_MINOR_S "." BRATR_V_PATCH_S

#endif