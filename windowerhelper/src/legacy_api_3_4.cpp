/*
 * legacy_api_3_4.cpp
 * 
 * Copyright © 2012 Windower Team
 */

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

#ifndef WINDOWER_64_BIT

#include "shift_jis.hpp"
#include "unicode.hpp"
#include "windowerhelper_impl.hpp"

#include <boost/scoped_array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/spirit/include/qi.hpp>
#include <cstdlib>
#include <map>
#include <string>
#include <sstream>
#include <vector>

#include <iostream>

namespace
{
	namespace qi = boost::spirit::qi;

	class impl
	{
	public:
		typedef boost::shared_ptr<impl> ptr;

		static ptr get_instance(std::string const& name)
		{
			int process = 0;
			std::string::size_type pos = name.find_last_of('_');
			if (pos != std::string::npos)
			{
				std::stringstream s;
				s << name.substr(pos + 1);
				s >> process;
			}

			ptr result;

			boost::mutex::scoped_lock(mutex);
			std::map<int, boost::weak_ptr<impl>>::const_iterator it = instances.find(process);
			if (it != instances.end())
			{
				result = it->second.lock();
			}
			
			if (!result)
			{
				result.reset(new impl(process));
				instances[process] = result;
			}

			return result;
		}

		~impl()
		{
			::windower_delete(m_handle);

			boost::mutex::scoped_lock(mutex);
			for(std::map<int, boost::weak_ptr<impl>>::const_iterator i = instances.begin();i != instances.end();)
			{
				if (i->second.expired())
				{
					instances.erase(i++);
				}
				else
				{
					++i;
				}
			}
		}

		void SendString(char const* string)
		{
			std::string temp;
			shift_jis::decode(std::string(string), temp);
			::windower_send_string(m_handle, temp.c_str());
		}

		void SetKey(unsigned char key, bool down)
		{
			::windower_set_key_state(m_handle, key, down);
		}

		void BlockInput(bool block)
		{
			if (block)
			{
				::windower_block(m_handle, WINDOWER_INPUT_TYPE_KEYBOARD);
			}
			else
			{
				::windower_unblock(m_handle, WINDOWER_INPUT_TYPE_KEYBOARD);
			}
		}

		void UpdateCommand()
		{
			m_command_args.clear();

			windower_command command_handle = 0;
			if (::windower_next_command(m_handle, &command_handle) || !command_handle)
			{
				return;
			}

			size_t length;
			char const* string;

			::windower_command_length(command_handle, &length);
			::windower_command_string(command_handle, &string);

			char const* begin = string;
			char const* end = begin + length;

			m_command_raw.assign(begin, end);

			m_command_args.clear();

			std::cout << m_command_raw.size() << std::endl;
			std::cout << "starting..." << std::endl;
			qi::phrase_parse(begin, end, args_parser, qi::ascii::space, m_command_args);
			std::cout << "done..." << std::endl;

			std::cout << m_command_args.size() << std::endl;
			for (std::vector<std::string>::iterator i = m_command_args.begin(); i != m_command_args.end(); ++i)
			{
				std::cout << *i << std::endl;
			}

			::windower_command_delete(command_handle);

			++m_command_index;
		}

		unsigned int GetCommandID()
		{
			return m_command_index;
		}

		unsigned int GetRawCommand(char* buffer, int size)
		{
			if (size < 0)
			{
				return 0;
			}

			std::string command;
			shift_jis::encode(m_command_raw, command);
			std::size_t length = command.size();
			if (length > std::size_t(size))
			{
				length = size;
			}
			std::memcpy(buffer, command.data(), length);
			buffer[length] = 0;
			return length;
		}

		int GetArgCount()
		{
			std::vector<std::string>::size_type count = m_command_args.size();
			return count > 8 ? 8 : count;
		}

		void GetArg(unsigned int index, char* buffer)
		{
			if (index < m_command_args.size() && index < 8)
			{
				std::string arg;
				shift_jis::encode(m_command_args[index], arg);
				arg = arg.substr(0, command_arg_size - 1);
				std::memcpy(buffer, arg.data(), arg.size());
				buffer[arg.size()] = 0;
			}
			else
			{
				buffer[0] = 0;
			}
		}

		void CreateTextObject(char const* name)
		{
			windower_text text_handle;
			::windower_text_create(m_handle, &text_handle, name);
			if (text_handle)
			{
				m_text_handles[name] = text_handle;
			}
		}

		void DeleteTextObject(char const* name)
		{
			std::map<std::string, windower_text>::iterator it = m_text_handles.find(name);
			if (it != m_text_handles.end())
			{
				windower_text text_handle = it->second;
				::windower_text_delete(text_handle);
			}
		}

		void SetText(char const* name, char const* text)
		{
			std::map<std::string, windower_text>::iterator it = m_text_handles.find(name);
			if (it != m_text_handles.end())
			{
				windower_text text_handle = it->second;
				::windower_text_set_text(text_handle, text);
			}
		}

		void SetVisibility(char const* name, bool visible)
		{
			std::map<std::string, windower_text>::iterator it = m_text_handles.find(name);
			if (it != m_text_handles.end())
			{
				windower_text text_handle = it->second;
				if (visible)
				{
					::windower_text_show(text_handle);
				}
				else
				{
					::windower_text_hide(text_handle);
				}
			}
		}

		void SetLocation(char const* name, float x, float y)
		{
			std::map<std::string, windower_text>::iterator it = m_text_handles.find(name);
			if (it != m_text_handles.end())
			{
				windower_text text_handle = it->second;
				::windower_text_set_location(text_handle, int(x), int(y));
			}
		}

		void SetColor(char const* name, unsigned char a, unsigned char r, unsigned char g, unsigned char b)
		{
			std::map<std::string, windower_text>::iterator it = m_text_handles.find(name);
			if (it != m_text_handles.end())
			{
				windower_text text_handle = it->second;
				::windower_text_set_foreground(text_handle, r, g, b, a);
			}
		}

		void SetBGColor(char const* name, unsigned char a, unsigned char r, unsigned char g, unsigned char b)
		{
			std::map<std::string, windower_text>::iterator it = m_text_handles.find(name);
			if (it != m_text_handles.end())
			{
				windower_text text_handle = it->second;
				::windower_text_set_background(text_handle, r, g, b, a);
			}
		}

		void SetBGVisibility(char const* name, bool visible)
		{
			std::map<std::string, windower_text>::iterator it = m_text_handles.find(name);
			if (it != m_text_handles.end())
			{
				windower_text text_handle = it->second;
				if (visible)
				{
					::windower_text_show_background(text_handle);
				}
				else
				{
					::windower_text_hide_background(text_handle);
				}
			}
		}

		void SetFont(char const* name, char const* typeface, int size)
		{
			std::map<std::string, windower_text>::iterator it = m_text_handles.find(name);
			if (it != m_text_handles.end())
			{
				windower_text text_handle = it->second;
				::windower_text_set_font(text_handle, typeface, float(size));
			}
		}

		void SetBold(char const* name, bool bold)
		{
			std::map<std::string, windower_text>::iterator it = m_text_handles.find(name);
			if (it != m_text_handles.end())
			{
				windower_text text_handle = it->second;
				if (bold)
				{
					::windower_text_set_weight(text_handle, WINDOWER_TEXT_FONT_WEIGHT_BOLD);
				}
				else
				{
					::windower_text_set_weight(text_handle, WINDOWER_TEXT_FONT_WEIGHT_NORMAL);
				}
			}
		}

		void SetItalic(char const* name, bool italic)
		{
			std::map<std::string, windower_text>::iterator it = m_text_handles.find(name);
			if (it != m_text_handles.end())
			{
				windower_text text_handle = it->second;
				if (italic)
				{
					::windower_text_set_style(text_handle, WINDOWER_TEXT_FONT_STYLE_ITALIC);
				}
				else
				{
					::windower_text_set_style(text_handle, WINDOWER_TEXT_FONT_STYLE_NONE);
				}
			}
		}

		void SetBGBorderSize(char const* name, float pixels)
		{
			std::map<std::string, windower_text>::iterator it = m_text_handles.find(name);
			if (it != m_text_handles.end())
			{
				windower_text text_handle = it->second;
				::windower_text_set_padding(text_handle, pixels);
			}
		}

		void SetRightJustified(char const* name, bool justified)
		{
			std::map<std::string, windower_text>::iterator it = m_text_handles.find(name);
			if (it != m_text_handles.end())
			{
				windower_text text_handle = it->second;
				if (justified)
				{
					::windower_text_set_alignment(text_handle, WINDOWER_TEXT_ALIGN_RIGHT);
				}
				else
				{
					::windower_text_set_alignment(text_handle, WINDOWER_TEXT_ALIGN_LEFT);
				}
			}
		}

	private:
		static int const command_arg_size = 2048;
		static int const command_size = command_arg_size * 24;

		static boost::mutex mutex;
		static std::map<int, boost::weak_ptr<impl>> instances;
		static qi::rule<char const*, std::string()> const arg_parser;
		static qi::rule<char const*, std::vector<std::string>(), qi::ascii::space_type> const args_parser;

		windower_instance m_handle;
		unsigned int m_command_index;
		std::string m_command_raw;
		std::vector<std::string> m_command_args;
		std::map<std::string, windower_text> m_text_handles;

		impl(int process)
			: m_command_index(0)
		{
			::windower_create(&m_handle, process);
		}
	};

	boost::mutex impl::mutex;

	std::map<int, boost::weak_ptr<impl>> impl::instances;

	qi::rule<char const*, std::string()> const impl::arg_parser = '"' >> *~qi::char_('"') >> -qi::lit('"') | +~qi::ascii::space;

	qi::rule<char const*, std::vector<std::string>(), qi::ascii::space_type> const impl::args_parser = *impl::arg_parser;
}

class WINDOWER_HELPER_API CKeyboardHelper
{
	public:
		CKeyboardHelper() : m_impl(new impl::ptr()) { }

		CKeyboardHelper(char* name) : m_impl(new impl::ptr(impl::get_instance(name))) { }

		CKeyboardHelper(CKeyboardHelper const& other) : m_impl(new impl::ptr(*other.m_impl)) { }

		virtual ~CKeyboardHelper()
		{
			delete m_impl;
		}

		void OpenMap(char* name)
		{
			*m_impl = impl::get_instance(name);
		}

		void CloseMap()
		{
			m_impl->reset();
		}

		void SendString(char* string)
		{
			(*m_impl)->SendString(string);
		}

		void SetKey(unsigned char key, bool down)
		{
			(*m_impl)->SetKey(key, down);
		}

		void BlockInput(bool block)
		{
			(*m_impl)->BlockInput(block);
		}

		CKeyboardHelper& operator =(CKeyboardHelper const& rhs)
		{
			*m_impl = *rhs.m_impl;
			return *this;
		}

	private:
		impl::ptr* m_impl;
};

class WINDOWER_HELPER_API CConsoleHelper
{
	public:
		CConsoleHelper() : m_impl(new impl::ptr()) { }

		CConsoleHelper(char* name) : m_impl(new impl::ptr(impl::get_instance(name))) { }

		CConsoleHelper(CConsoleHelper const& other) : m_impl(new impl::ptr(*other.m_impl)) { }

		virtual ~CConsoleHelper()
		{
			delete m_impl;
		}

		void OpenMap(char* name)
		{
			*m_impl = impl::get_instance(name);
		}

		void CloseMap()
		{
			m_impl->reset();
		}

		unsigned int GetCommandID()
		{
			(*m_impl)->UpdateCommand();
			return (*m_impl)->GetCommandID();
		}

		bool IsNewCommand()
		{
			(*m_impl)->UpdateCommand();
			return true;
		}

		unsigned int GetRawCommand(char* buffer, int size)
		{
			return (*m_impl)->GetRawCommand(buffer, size);
		}

		int GetArgCount()
		{
			return (*m_impl)->GetArgCount();
		}

		void GetArg(int index, char* buffer)
		{
			(*m_impl)->GetArg(index, buffer);
		}

		CConsoleHelper& operator =(CConsoleHelper const& rhs)
		{
			*m_impl = *rhs.m_impl;
			return *this;
		}

	private:
		impl::ptr* m_impl;
};

class WINDOWER_HELPER_API CTextHelper
{
	public:
		CTextHelper() : m_impl(new impl::ptr()) { }

		CTextHelper(char* name) : m_impl(new impl::ptr(impl::get_instance(name))) { }

		CTextHelper(CTextHelper const& other) : m_impl(new impl::ptr(*other.m_impl)) { }

		virtual ~CTextHelper()
		{
			delete m_impl;
		}
		
		void OpenMap(char* name)
		{
			*m_impl = impl::get_instance(name);
		}

		void CloseMap()
		{
			m_impl->reset();
		}

		void CreateTextObject(char* name)
		{
			(*m_impl)->CreateTextObject(name);
		}

		void DeleteTextObject(char* name)
		{
			(*m_impl)->DeleteTextObject(name);
		}

		void SetText(char* name, char* text)
		{
			(*m_impl)->SetText(name, text);
		}

		void SetVisibility(char* name, bool visible)
		{
			(*m_impl)->SetVisibility(name, visible);
		}

		void SetLocation(char* name, float x, float y)
		{
			(*m_impl)->SetLocation(name, x, y);
		}

		void SetColor(char* name, unsigned char a, unsigned char r, unsigned char g, unsigned char b)
		{
			(*m_impl)->SetColor(name, a, r, g, b);
		}

		void SetBGColor(char* name, unsigned char a, unsigned char r, unsigned char g, unsigned char b)
		{
			(*m_impl)->SetBGColor(name, a, r, g, b);
		}

		void SetBGVisibility(char* name, bool visible)
		{
			(*m_impl)->SetBGVisibility(name, visible);
		}

		void SetFont(char* name, char* font, int size)
		{
			(*m_impl)->SetFont(name, font, size);
		}

		void SetBold(char* name, bool bold)
		{
			(*m_impl)->SetBold(name, bold);
		}

		void SetItalic(char* name, bool italic)
		{
			(*m_impl)->SetItalic(name, italic);
		}

		void SetBGBorderSize(char* name, float pixels)
		{
			(*m_impl)->SetBGBorderSize(name, pixels);
		}

		void SetRightJustified(char* name, bool justified)
		{
			(*m_impl)->SetRightJustified(name, justified);
		}

		void FlushCommands() { }

		CTextHelper& operator =(CTextHelper const& rhs)
		{
			*m_impl = *rhs.m_impl;
			return *this;
		}

	private:
		impl::ptr* m_impl;
};

extern "C"
{
	WINDOWER_HELPER_API unsigned int __stdcall GetWHVersion()
	{
		return 2;
	}

	WINDOWER_HELPER_API void* __stdcall CreateKeyboardHelper(char* name)
	{
		return new CKeyboardHelper(name);
	}

	WINDOWER_HELPER_API void __stdcall DeleteKeyboardHelper(void* handle)
	{
		delete reinterpret_cast<CKeyboardHelper*>(handle);
	}

	WINDOWER_HELPER_API void __stdcall CKHSendString(void* handle, char* string)
	{
		reinterpret_cast<CKeyboardHelper*>(handle)->SendString(string);
	}

	WINDOWER_HELPER_API void __stdcall CKHSetKey(void* handle, unsigned char key, bool down)
	{
		reinterpret_cast<CKeyboardHelper*>(handle)->SetKey(key, down);
	}

	WINDOWER_HELPER_API void __stdcall CKHBlockInput(void* handle, bool block)
	{
		reinterpret_cast<CKeyboardHelper*>(handle)->BlockInput(block);
	}

	WINDOWER_HELPER_API void* __stdcall CreateConsoleHelper(char* name)
	{
		return new CConsoleHelper(name);
	}

	WINDOWER_HELPER_API void __stdcall DeleteConsoleHelper(void* handle)
	{
		delete reinterpret_cast<CConsoleHelper*>(handle);
	}

	WINDOWER_HELPER_API unsigned int __stdcall CCHGetCommandID(void* handle)
	{
		return reinterpret_cast<CConsoleHelper*>(handle)->GetCommandID();
	}

	WINDOWER_HELPER_API bool __stdcall CCHIsNewCommand(void* handle)
	{
		return reinterpret_cast<CConsoleHelper*>(handle)->IsNewCommand();
	}

	WINDOWER_HELPER_API unsigned int __stdcall CCHGetRawCommand(void* handle, char* buffer, int size)
	{
		return reinterpret_cast<CConsoleHelper*>(handle)->GetRawCommand(buffer, size);
	}

	WINDOWER_HELPER_API int __stdcall CCHGetArgCount(void* handle)
	{
		return reinterpret_cast<CConsoleHelper*>(handle)->GetArgCount();
	}

	WINDOWER_HELPER_API void __stdcall CCHGetArg(void* handle, int index, char* buffer)
	{
		reinterpret_cast<CConsoleHelper*>(handle)->GetArg(index, buffer);
	}

	WINDOWER_HELPER_API void* __stdcall CreateTextHelper(char* name)
	{
		return new CTextHelper(name);
	}

	WINDOWER_HELPER_API void __stdcall DeleteTextHelper(void* handle)
	{
		delete reinterpret_cast<CTextHelper*>(handle);
	}

	WINDOWER_HELPER_API void __stdcall CTHCreateTextObject(void* handle, char* name)
	{
		reinterpret_cast<CTextHelper*>(handle)->CreateTextObject(name);
	}

	WINDOWER_HELPER_API void __stdcall CTHDeleteTextObject(void* handle, char* name)
	{
		reinterpret_cast<CTextHelper*>(handle)->DeleteTextObject(name);
	}

	WINDOWER_HELPER_API void __stdcall CTHSetText(void* handle, char* name, char* text)
	{
		reinterpret_cast<CTextHelper*>(handle)->SetText(name, text);
	}

	WINDOWER_HELPER_API void __stdcall CTHSetVisibility(void* handle, char* name, bool visible)
	{
		reinterpret_cast<CTextHelper*>(handle)->SetVisibility(name, visible);
	}

	WINDOWER_HELPER_API void __stdcall CTHSetLocation(void* handle, char* name, float x, float y)
	{
		reinterpret_cast<CTextHelper*>(handle)->SetLocation(name, x, y);
	}

	WINDOWER_HELPER_API void __stdcall CTHSetColor(void* handle, char* name, unsigned char a, unsigned char r, unsigned char g, unsigned char b)
	{
		reinterpret_cast<CTextHelper*>(handle)->SetColor(name, a, r, g, b);
	}

	WINDOWER_HELPER_API void __stdcall CTHSetBGColor(void* handle, char* name, unsigned char a, unsigned char r, unsigned char g, unsigned char b)
	{
		reinterpret_cast<CTextHelper*>(handle)->SetBGColor(name, a, r, g, b);
	}

	WINDOWER_HELPER_API void __stdcall CTHSetBGVisibility(void* handle, char* name, bool visible)
	{
		reinterpret_cast<CTextHelper*>(handle)->SetBGVisibility(name, visible);
	}

	WINDOWER_HELPER_API void __stdcall CTHSetFont(void* handle, char* name, char* font, int size)
	{
		reinterpret_cast<CTextHelper*>(handle)->SetFont(name, font, size);
	}

	WINDOWER_HELPER_API void __stdcall CTHSetBold(void* handle, char* name, bool bold)
	{
		reinterpret_cast<CTextHelper*>(handle)->SetBold(name, bold);
	}

	WINDOWER_HELPER_API void __stdcall CTHSetItalic(void* handle, char* name, bool italic)
	{
		reinterpret_cast<CTextHelper*>(handle)->SetBold(name, italic);
	}

	WINDOWER_HELPER_API void __stdcall CTHSetBGBorderSize(void* handle, char* name, float pixels)
	{
		reinterpret_cast<CTextHelper*>(handle)->SetBGBorderSize(name, pixels);
	}

	WINDOWER_HELPER_API void __stdcall CTHSetRightJustified(void* handle, char* name, bool justified)
	{
		reinterpret_cast<CTextHelper*>(handle)->SetRightJustified(name, justified);
	}

	WINDOWER_HELPER_API void __stdcall CTHFlushCommands(void* handle)
	{
		reinterpret_cast<CTextHelper*>(handle)->FlushCommands();
	}
}

#endif
