#ifndef WINDOWERHELPER_3_4_H
#define WINDOWERHELPER_3_4_H

/*
 * windower_helper_3_4.h
 * 
 * Copyright © 2012 Windower Team
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#pragma once

#if _MSC_VER < 1700
#	ifdef _M_X64 
#		define WINDOWER_64_BIT
#	endif
#else
#	include <stdint.h>
#	if UINTPTR_MAX == 0xFFFFFFFF
#		define WINDOWER_64_BIT
#	endif
#endif

#ifdef WINDOWER_64_BIT
#	error "Windower Helper 3.4 API not supported on 64-bit platforms"
#else

#ifndef WINDOWER_HELPER_API
#ifdef WINDOWER_HELPER_STAIC
#	define WINDOWER_HELPER_API
#else
#	define WINDOWER_HELPER_API __declspec(dllimport)
#endif
#endif

#if defined(_MSC_VER)
#	define WINDOWER_HELPER_DEPRECATED __declspec(deprecated)
#elif defined(__GNUC__)
#	define WINDOWER_HELPER_DEPRECATED __attribute__((deprecated))
#else
#	define WINDOWER_HELPER_DEPRECATED
#endif

// C API
#ifdef __cplusplus
extern "C"
{
#endif
	WINDOWER_HELPER_DEPRECATED WINDOWER_HELPER_API unsigned int __stdcall GetWHVersion();

	WINDOWER_HELPER_DEPRECATED WINDOWER_HELPER_API void* __stdcall CreateKeyboardHelper(char*);
	WINDOWER_HELPER_DEPRECATED WINDOWER_HELPER_API void __stdcall DeleteKeyboardHelper(void*);
	WINDOWER_HELPER_DEPRECATED WINDOWER_HELPER_API void __stdcall CKHSendString(void*, char*);
	WINDOWER_HELPER_DEPRECATED WINDOWER_HELPER_API void __stdcall CKHSetKey(void*, unsigned char, char);
	WINDOWER_HELPER_DEPRECATED WINDOWER_HELPER_API void __stdcall CKHBlockInput(void*, char);

	WINDOWER_HELPER_DEPRECATED WINDOWER_HELPER_API void* __stdcall CreateConsoleHelper(char*);
	WINDOWER_HELPER_DEPRECATED WINDOWER_HELPER_API void __stdcall DeleteConsoleHelper(void*);
	WINDOWER_HELPER_DEPRECATED WINDOWER_HELPER_API unsigned int __stdcall CCHGetCommandID(void*);
	WINDOWER_HELPER_DEPRECATED WINDOWER_HELPER_API char __stdcall CCHIsNewCommand(void*);
	WINDOWER_HELPER_DEPRECATED WINDOWER_HELPER_API unsigned int __stdcall CCHGetRawCommand(void*, char*, int);
	WINDOWER_HELPER_DEPRECATED WINDOWER_HELPER_API int __stdcall CCHGetArgCount(void*);
	WINDOWER_HELPER_DEPRECATED WINDOWER_HELPER_API void __stdcall CCHGetArg(void*, int, char*);

	WINDOWER_HELPER_DEPRECATED WINDOWER_HELPER_API void* __stdcall CreateTextHelper(char*);
	WINDOWER_HELPER_DEPRECATED WINDOWER_HELPER_API void __stdcall DeleteTextHelper(void*);
	WINDOWER_HELPER_DEPRECATED WINDOWER_HELPER_API void __stdcall CTHCreateTextObject(void*, char*);
	WINDOWER_HELPER_DEPRECATED WINDOWER_HELPER_API void __stdcall CTHDeleteTextObject(void*, char*);
	WINDOWER_HELPER_DEPRECATED WINDOWER_HELPER_API void __stdcall CTHSetText(void*, char*, char*);
	WINDOWER_HELPER_DEPRECATED WINDOWER_HELPER_API void __stdcall CTHSetVisibility(void*, char*, char);
	WINDOWER_HELPER_DEPRECATED WINDOWER_HELPER_API void __stdcall CTHSetLocation(void*, char*, float x, float y);
	WINDOWER_HELPER_DEPRECATED WINDOWER_HELPER_API void __stdcall CTHSetColor(void*, char*, unsigned char, unsigned char, unsigned char, unsigned char);
	WINDOWER_HELPER_DEPRECATED WINDOWER_HELPER_API void __stdcall CTHSetBGColor(void*, char*, unsigned char, unsigned char, unsigned char, unsigned char);
	WINDOWER_HELPER_DEPRECATED WINDOWER_HELPER_API void __stdcall CTHSetBGVisibility(void*, char*, char);
	WINDOWER_HELPER_DEPRECATED WINDOWER_HELPER_API void __stdcall CTHSetFont(void*, char*, char*, int);
	WINDOWER_HELPER_DEPRECATED WINDOWER_HELPER_API void __stdcall CTHSetBold(void*, char*, char);
	WINDOWER_HELPER_DEPRECATED WINDOWER_HELPER_API void __stdcall CTHSetItalic(void*, char*, char);
	WINDOWER_HELPER_DEPRECATED WINDOWER_HELPER_API void __stdcall CTHSetBGBorderSize(void*, char*, float);
	WINDOWER_HELPER_DEPRECATED WINDOWER_HELPER_API void __stdcall CTHSetRightJustified(void*, char*, char);
	WINDOWER_HELPER_DEPRECATED WINDOWER_HELPER_API void __stdcall CTHFlushCommands(void*);

	struct WINDOWER_HELPER_DEPRECATED MMFTextCommand
	{
		unsigned long Command;
		char Alias[256];
		char Param1[256];
		char Param2[256];
		char Param3[256];
		char Param4[256];
		char Text[2048];
	};

	struct WINDOWER_HELPER_DEPRECATED MMFTextControlMapping
	{
		unsigned long NumberOfCommands;
		char Handled;
		struct MMFTextCommand Commands[32];
	};

	struct WINDOWER_HELPER_DEPRECATED MMFKeyboardCommand
	{
		unsigned long Command;
		char Param1[8];
		char Param2[8];
		char Param3[8];
		char Param4[8];
		char Text[2048];
	};

	struct WINDOWER_HELPER_DEPRECATED MMFKeyboardControlMapping
	{
		unsigned long NumberOfCommands;
		char Handled;
		struct MMFKeyboardCommand Commands[32];
	};

	struct WINDOWER_HELPER_DEPRECATED MMFConsoleArg
	{
		char Value[2048];
	};

	struct WINDOWER_HELPER_DEPRECATED MMFConsoleCommand
	{
		int ArgCount;
		struct MMFConsoleArg Args[8];
	};

	struct WINDOWER_HELPER_DEPRECATED MMFConsoleControlMapping
	{
		unsigned long LastUpdate;
		struct MMFConsoleCommand Command;
	};
#ifdef __cplusplus
}
#endif

// C++ API
#ifdef __cplusplus

class WINDOWER_HELPER_DEPRECATED CTextHelper {
public:
	WINDOWER_HELPER_API CTextHelper();
	WINDOWER_HELPER_API CTextHelper(char*);
	WINDOWER_HELPER_API CTextHelper(CTextHelper const&);
	WINDOWER_HELPER_API virtual ~CTextHelper();
	WINDOWER_HELPER_API void OpenMap(char*);
	WINDOWER_HELPER_API void CloseMap();
	WINDOWER_HELPER_API void CreateTextObject(char*);
	WINDOWER_HELPER_API void DeleteTextObject(char*);
	WINDOWER_HELPER_API void SetText(char*, char*);
	WINDOWER_HELPER_API void SetVisibility(char*, bool);
	WINDOWER_HELPER_API void SetFont(char*, char*, int);
	WINDOWER_HELPER_API void SetColor(char*, unsigned char, unsigned char, unsigned char, unsigned char);
	WINDOWER_HELPER_API void SetLocation(char*, float x, float y);
	WINDOWER_HELPER_API void SetBold(char*, bool bold);
	WINDOWER_HELPER_API void SetItalic(char*, bool italic);
	WINDOWER_HELPER_API void SetBGColor(char*, unsigned char, unsigned char, unsigned char, unsigned char);
	WINDOWER_HELPER_API void SetBGBorderSize(char*, float);
	WINDOWER_HELPER_API void SetBGVisibility(char*, bool);        
	WINDOWER_HELPER_API void SetRightJustified(char*, bool);
	WINDOWER_HELPER_API void FlushCommands();

private:
	void* impl;
};
 
class WINDOWER_HELPER_DEPRECATED CKeyboardHelper
{
public:
	WINDOWER_HELPER_API CKeyboardHelper();
	WINDOWER_HELPER_API CKeyboardHelper(char*);
	WINDOWER_HELPER_API CKeyboardHelper(CKeyboardHelper const&);
	WINDOWER_HELPER_API virtual ~CKeyboardHelper();
	WINDOWER_HELPER_API void OpenMap(char*);
	WINDOWER_HELPER_API void CloseMap();
	WINDOWER_HELPER_API void SetKey(unsigned char, bool);
	WINDOWER_HELPER_API void BlockInput(bool);
	WINDOWER_HELPER_API void SendString(char*);

private:
	void* impl;
};
 
class WINDOWER_HELPER_DEPRECATED CConsoleHelper
{
public:
	WINDOWER_HELPER_API CConsoleHelper();
	WINDOWER_HELPER_API CConsoleHelper(char* name);
	WINDOWER_HELPER_API CConsoleHelper(CConsoleHelper const&);
	WINDOWER_HELPER_API virtual ~CConsoleHelper();
	WINDOWER_HELPER_API void OpenMap(char*);
	WINDOWER_HELPER_API void CloseMap();
	WINDOWER_HELPER_API unsigned int GetCommandID();
	WINDOWER_HELPER_API bool IsNewCommand();
	WINDOWER_HELPER_API unsigned int GetRawCommand(char*, int);
	WINDOWER_HELPER_API int GetArgCount();
	WINDOWER_HELPER_API void GetArg(int, char*);

private:
	void* impl;
};

#endif

#endif

#endif
