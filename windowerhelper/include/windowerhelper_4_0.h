#ifndef WINDOWERHELPER_4_0_H
#define WINDOWERHELPER_4_0_H

/*
 * windower_helper_4_0.h
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

#include <stddef.h>

#ifdef __cplusplus
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#endif

#define WINDOWER_VERSION(major, minor) ((major) * 1000 + (minor))
#define WINDOWER_GET_MAJOR(version) ((version) / 1000)
#define WINDOWER_GET_MINOR(version) ((version) % 1000)

#define WINDOWER_HELPER_VERSION_MAJOR	4
#define WINDOWER_HELPER_VERSION_MINOR	0
#define WINDOWER_HELPER_VERSION			WINDOWER_VERSION(WINDOWER_HELPER_VERSION_MAJOR, WINDOWER_HELPER_VERSION_MINOR)

#ifndef WINDOWER_HELPER_API
#ifdef WINDOWER_HELPER_STATIC
#	define WINDOWER_HELPER_API
#else
#	define WINDOWER_HELPER_API __declspec(dllimport)
#endif
#endif

// C API
#define WINDOWER_ERROR_NONE					0x00
#define WINDOWER_ERROR_UNKNOWN				0x01
#define WINDOWER_ERROR_OUT_OF_MEMORY		0x02
#define WINDOWER_ERROR_INVALID_ARGUMENT		0x03
#define WINDOWER_ERROR_OUT_OF_RANGE			0x04
#define WINDOWER_ERROR_INVALID_HANDLE		0x05
#define WINDOWER_ERROR_CONNECTION_FAULT		0x06
#define WINDOWER_ERROR_CONNECTION_CLOSED	0x07
#define WINDOWER_ERROR_TIME_OUT				0x08
#define WINDOWER_ERROR_INTERRUPT			0x09
#define WINDOWER_ERROR_INVALID_REPLY		0x0A
#define WINDOWER_ERROR_NOT_FOUND			0x0B
#define WINDOWER_ERROR_ENCODING				0x0C

#define WINDOWER_KEY_ESCAPE					0x01
#define WINDOWER_KEY_ENTER					0x1C
#define WINDOWER_KEY_INSERT					0xD2
#define WINDOWER_KEY_DELETE					0xD3
#define WINDOWER_KEY_HOME					0xC7
#define WINDOWER_KEY_END					0xCF
#define WINDOWER_KEY_PAGE_UP				0xC9
#define WINDOWER_KEY_PAGE_DOWN				0xD1
#define WINDOWER_KEY_LEFT_CONTROL			0x1D
#define WINDOWER_KEY_LEFT_ALT				0x38
#define WINDOWER_KEY_LEFT_SHIFT				0x2A
#define WINDOWER_KEY_RIGHT_CONTROL			0x9D
#define WINDOWER_KEY_RIGHT_ALT				0xB8
#define WINDOWER_KEY_RIGHT_SHIFT			0x36
#define WINDOWER_KEY_LEFT_WINDOWS			0xDB
#define WINDOWER_KEY_RIGHT_WINDOWS			0xDC
#define WINDOWER_KEY_APP_MENU				0xDD
#define WINDOWER_KEY_F1						0x3B
#define WINDOWER_KEY_F2						0x3C
#define WINDOWER_KEY_F3						0x3D
#define WINDOWER_KEY_F4						0x3E
#define WINDOWER_KEY_F5						0x3F
#define WINDOWER_KEY_F6						0x40
#define WINDOWER_KEY_F7						0x41
#define WINDOWER_KEY_F8						0x42
#define WINDOWER_KEY_F9						0x43
#define WINDOWER_KEY_F10					0x44
#define WINDOWER_KEY_F11					0x57
#define WINDOWER_KEY_F12					0x58
#define WINDOWER_KEY_F13					0x64
#define WINDOWER_KEY_F14					0x65
#define WINDOWER_KEY_F15					0x66
#define WINDOWER_KEY_PRINT_SCREEN			0xB7
#define WINDOWER_KEY_SCROLL_LOCK			0x46
#define WINDOWER_KEY_BREAK					0xC5
#define WINDOWER_KEY_UP						0xC8
#define WINDOWER_KEY_DOWN					0xD0
#define WINDOWER_KEY_LEFT					0xCB
#define WINDOWER_KEY_RIGHT					0xCD
#define WINDOWER_KEY_NUM_LOCK				0x45
#define WINDOWER_KEY_NUM_PAD_0				0x52
#define WINDOWER_KEY_NUM_PAD_1				0x4F
#define WINDOWER_KEY_NUM_PAD_2				0x50
#define WINDOWER_KEY_NUM_PAD_3				0x51
#define WINDOWER_KEY_NUM_PAD_4				0x4B
#define WINDOWER_KEY_NUM_PAD_5				0x4C
#define WINDOWER_KEY_NUM_PAD_6				0x4D
#define WINDOWER_KEY_NUM_PAD_7				0x47
#define WINDOWER_KEY_NUM_PAD_8				0x48
#define WINDOWER_KEY_NUM_PAD_9				0x49
#define WINDOWER_KEY_NUM_PAD_ENTER			0x9C
#define WINDOWER_KEY_NUM_PAD_MINUS			0x4A
#define WINDOWER_KEY_NUM_PAD_PLUS			0x4E
#define WINDOWER_KEY_NUM_PAD_MULTIPLY		0x37
#define WINDOWER_KEY_NUM_PAD_DIVIDE			0xB5
#define WINDOWER_KEY_NUM_PAD_PPERIOD		0x53
#define WINDOWER_KEY_TAB					0x0F
#define WINDOWER_KEY_BACKSPACE				0x0E
#define WINDOWER_KEY_SPACE					0x39
#define WINDOWER_KEY_A						0x1E
#define WINDOWER_KEY_B						0x30
#define WINDOWER_KEY_C						0x2E
#define WINDOWER_KEY_D						0x20
#define WINDOWER_KEY_E						0x12
#define WINDOWER_KEY_F						0x21
#define WINDOWER_KEY_G						0x22
#define WINDOWER_KEY_H						0x23
#define WINDOWER_KEY_I						0x17
#define WINDOWER_KEY_J						0x24
#define WINDOWER_KEY_K						0x25
#define WINDOWER_KEY_L						0x26
#define WINDOWER_KEY_M						0x32
#define WINDOWER_KEY_N						0x31
#define WINDOWER_KEY_O						0x18
#define WINDOWER_KEY_P						0x19
#define WINDOWER_KEY_Q						0x10
#define WINDOWER_KEY_R						0x13
#define WINDOWER_KEY_S						0x1F
#define WINDOWER_KEY_T						0x14
#define WINDOWER_KEY_U						0x16
#define WINDOWER_KEY_V						0x2F
#define WINDOWER_KEY_W						0x11
#define WINDOWER_KEY_X						0x2D
#define WINDOWER_KEY_Y						0x15
#define WINDOWER_KEY_Z						0x2C
#define WINDOWER_KEY_GRAVE					0x29
#define WINDOWER_KEY_1						0x02
#define WINDOWER_KEY_2						0x03
#define WINDOWER_KEY_3						0x04
#define WINDOWER_KEY_4						0x05
#define WINDOWER_KEY_5						0x06
#define WINDOWER_KEY_6						0x07
#define WINDOWER_KEY_7						0x08
#define WINDOWER_KEY_8						0x09
#define WINDOWER_KEY_9						0x0A
#define WINDOWER_KEY_0						0x0B
#define WINDOWER_KEY_MINUS					0x0C
#define WINDOWER_KEY_EQUALS					0x0D
#define WINDOWER_KEY_LEFT_BRACKET			0x1A
#define WINDOWER_KEY_RIGHT_BRACKET			0x1B
#define WINDOWER_KEY_BACKSLASH				0x2B
#define WINDOWER_KEY_SEMICOLON				0x27
#define WINDOWER_KEY_APOSTROPHE				0x28
#define WINDOWER_KEY_COMMA					0x33
#define WINDOWER_KEY_PERIOD					0x34
#define WINDOWER_KEY_SLASH					0x35
#define WINDOWER_KEY_CAPS_LOCK				0x3A
#define WINDOWER_KEY_PLAY_PAUSE				0xA2
#define WINDOWER_KEY_STOP					0xA4
#define WINDOWER_KEY_NEXT_TRACK				0x99
#define WINDOWER_KEY_PREVIOUS_TRACK			0x90
#define WINDOWER_KEY_VOLUME_UP				0xB0
#define WINDOWER_KEY_VOLUME_DOWN			0xAE
#define WINDOWER_KEY_MUTE					0xA0
#define WINDOWER_KEY_MEDIA_SELECT			0xED
#define WINDOWER_KEY_POWER					0xDE
#define WINDOWER_KEY_SLEEP					0xDF
#define WINDOWER_KEY_WAKE					0xE3
#define WINDOWER_KEY_WEB_BACK				0xEA
#define WINDOWER_KEY_WEB_FORWARD			0xE9
#define WINDOWER_KEY_WEB_STOP				0xE8
#define WINDOWER_KEY_WEB_REFRESH			0xE7
#define WINDOWER_KEY_WEB_HOME				0xB2
#define WINDOWER_KEY_WEB_SEARCH				0xE5
#define WINDOWER_KEY_WEB_BOOKMARKS			0xE6
#define WINDOWER_KEY_MAIL					0xEC
#define WINDOWER_KEY_MY_COMPUTER			0xEB
#define WINDOWER_KEY_CALCULATOR				0xA1
#define WINDOWER_KEY_YEN					0x7D
#define WINDOWER_KEY_KANA					0x70
#define WINDOWER_KEY_KANJI					0x94
#define WINDOWER_KEY_CONVERT				0x79
#define WINDOWER_KEY_NO_CONVERT				0x7B
#define WINDOWER_KEY_CIRCUMFLEX				0x90

#define WINDOWER_KEY_STATE_UP				0
#define WINDOWER_KEY_STATE_DOWN				1

#define WINDOWER_INPUT_TYPE_NONE			0
#define WINDOWER_INPUT_TYPE_KEYBOARD		1
#define WINDOWER_INPUT_TYPE_MOUSE			2
#define WINDOWER_INPUT_TYPE_ALL				(WINDOWER_INPUT_TYPE_KEYBOARD | WINDOWER_INPUT_TYPE_MOUSE)

#define WINDOWER_TEXT_FONT_STYLE_NONE		0
#define WINDOWER_TEXT_FONT_STYLE_ITALIC		1

#define WINDOWER_TEXT_FONT_WEIGHT_DEFAULT	0
#define WINDOWER_TEXT_FONT_WEIGHT_NORMAL	400
#define WINDOWER_TEXT_FONT_WEIGHT_BOLD		700

#define WINDOWER_TEXT_ALIGN_LEFT			0
#define WINDOWER_TEXT_ALIGN_RIGHT			1

#ifdef __cplusplus
extern "C"
{
#endif
	typedef struct windower_instance_type* windower_instance;
	typedef struct windower_command_type* windower_command;
	typedef struct windower_text_type* windower_text;

	WINDOWER_HELPER_API unsigned int windower_create(windower_instance* result, unsigned int process);
	WINDOWER_HELPER_API unsigned int windower_create_remote(windower_instance* result, char const* domain, unsigned int process);
	WINDOWER_HELPER_API unsigned int windower_delete(windower_instance handle);

	WINDOWER_HELPER_API unsigned int windower_get_version(windower_instance handle, unsigned int* result);
	WINDOWER_HELPER_API unsigned int windower_send_string(windower_instance handle, char const* string);
	WINDOWER_HELPER_API unsigned int windower_set_key_state(windower_instance handle, unsigned int key, unsigned int state);
	WINDOWER_HELPER_API unsigned int windower_block(windower_instance handle, unsigned int input_kind);
	WINDOWER_HELPER_API unsigned int windower_unblock(windower_instance handle, unsigned int input_kind);

	WINDOWER_HELPER_API unsigned int windower_next_command(windower_instance handle, windower_command* result);
	WINDOWER_HELPER_API unsigned int windower_command_delete(windower_command handle);
	WINDOWER_HELPER_API unsigned int windower_command_length(windower_command handle, unsigned int* result);
	WINDOWER_HELPER_API unsigned int windower_command_string(windower_command handle, char const** result);

	WINDOWER_HELPER_API unsigned int windower_text_create(windower_instance handle, windower_text* result, char const* name);
	WINDOWER_HELPER_API unsigned int windower_text_delete(windower_text handle);
	WINDOWER_HELPER_API unsigned int windower_text_set_text(windower_text handle, char const* text);
	WINDOWER_HELPER_API unsigned int windower_text_show(windower_text handle);
	WINDOWER_HELPER_API unsigned int windower_text_hide(windower_text handle);
	WINDOWER_HELPER_API unsigned int windower_text_set_location(windower_text handle, int x, int y);
	WINDOWER_HELPER_API unsigned int windower_text_set_foreground(windower_text handle, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
	WINDOWER_HELPER_API unsigned int windower_text_set_background(windower_text handle, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
	WINDOWER_HELPER_API unsigned int windower_text_show_background(windower_text handle);
	WINDOWER_HELPER_API unsigned int windower_text_hide_background(windower_text handle);
	WINDOWER_HELPER_API unsigned int windower_text_set_font(windower_text handle, char const* typeface, float size);
	WINDOWER_HELPER_API unsigned int windower_text_set_weight(windower_text handle, unsigned int weight);
	WINDOWER_HELPER_API unsigned int windower_text_set_style(windower_text handle, unsigned int style);
	WINDOWER_HELPER_API unsigned int windower_text_set_alignment(windower_text handle, unsigned int alignment);
	WINDOWER_HELPER_API unsigned int windower_text_set_padding(windower_text handle, float pixels);
#ifdef __cplusplus
}
#endif

#if defined(__cplusplus) && !defined(WINDOWER_HELPER_NO_CLASSES)

// C++ API
namespace windower
{
	namespace error_code
	{
		enum type
		{
			none							= WINDOWER_ERROR_NONE,
			unknown							= WINDOWER_ERROR_UNKNOWN,
			out_of_memory					= WINDOWER_ERROR_OUT_OF_MEMORY,
			invalid_argument				= WINDOWER_ERROR_INVALID_ARGUMENT,
			out_of_range					= WINDOWER_ERROR_OUT_OF_RANGE,
			invalid_handle					= WINDOWER_ERROR_INVALID_HANDLE,
			connection_fault				= WINDOWER_ERROR_CONNECTION_FAULT,
			connection_closed				= WINDOWER_ERROR_CONNECTION_CLOSED,
			interrupt						= WINDOWER_ERROR_INTERRUPT,
			invalid_reply					= WINDOWER_ERROR_INVALID_REPLY,
			not_found						= WINDOWER_ERROR_NOT_FOUND,
			encoding						= WINDOWER_ERROR_ENCODING,
		};
	}

	namespace key
	{
		enum type
		{
			esc								= WINDOWER_KEY_ESCAPE,
			enter							= WINDOWER_KEY_ENTER,
			ins								= WINDOWER_KEY_INSERT,
			del								= WINDOWER_KEY_DELETE,
			home							= WINDOWER_KEY_HOME,
			end								= WINDOWER_KEY_END,
			page_up							= WINDOWER_KEY_PAGE_UP,
			page_down						= WINDOWER_KEY_PAGE_DOWN,
			left_ctrl						= WINDOWER_KEY_LEFT_CONTROL,
			left_alt						= WINDOWER_KEY_LEFT_ALT,
			left_shift						= WINDOWER_KEY_LEFT_SHIFT,
			right_ctrl						= WINDOWER_KEY_RIGHT_CONTROL,
			right_alt						= WINDOWER_KEY_RIGHT_ALT,
			right_shift						= WINDOWER_KEY_RIGHT_SHIFT,
			left_windows					= WINDOWER_KEY_LEFT_WINDOWS,
			right_windows					= WINDOWER_KEY_RIGHT_WINDOWS,
			app_menu						= WINDOWER_KEY_APP_MENU,
			f1								= WINDOWER_KEY_F1,
			f2								= WINDOWER_KEY_F2,
			f3								= WINDOWER_KEY_F3,
			f4								= WINDOWER_KEY_F4,
			f5								= WINDOWER_KEY_F5,
			f6								= WINDOWER_KEY_F6,
			f7								= WINDOWER_KEY_F7,
			f8								= WINDOWER_KEY_F8,
			f9								= WINDOWER_KEY_F9,
			f10								= WINDOWER_KEY_F10,
			f11								= WINDOWER_KEY_F11,
			f12								= WINDOWER_KEY_F12,
			f13								= WINDOWER_KEY_F13,
			f14								= WINDOWER_KEY_F14,
			f15								= WINDOWER_KEY_F15,
			print_screen					= WINDOWER_KEY_PRINT_SCREEN,
			scroll_lock						= WINDOWER_KEY_SCROLL_LOCK,
			pause_break						= WINDOWER_KEY_BREAK,
			up								= WINDOWER_KEY_UP,
			down							= WINDOWER_KEY_DOWN,
			left							= WINDOWER_KEY_LEFT,
			right							= WINDOWER_KEY_RIGHT,
			num_lock						= WINDOWER_KEY_NUM_LOCK,
			num_pad_0						= WINDOWER_KEY_NUM_PAD_0,
			num_pad_1						= WINDOWER_KEY_NUM_PAD_1,
			num_pad_2						= WINDOWER_KEY_NUM_PAD_2,
			num_pad_3						= WINDOWER_KEY_NUM_PAD_3,
			num_pad_4						= WINDOWER_KEY_NUM_PAD_4,
			num_pad_5						= WINDOWER_KEY_NUM_PAD_5,
			num_pad_6						= WINDOWER_KEY_NUM_PAD_6,
			num_pad_7						= WINDOWER_KEY_NUM_PAD_7,
			num_pad_8						= WINDOWER_KEY_NUM_PAD_8,
			num_pad_9						= WINDOWER_KEY_NUM_PAD_9,
			num_pad_enter					= WINDOWER_KEY_NUM_PAD_ENTER,
			num_pad_minus					= WINDOWER_KEY_NUM_PAD_MINUS,
			num_pad_plus					= WINDOWER_KEY_NUM_PAD_PLUS,
			num_pad_multiply				= WINDOWER_KEY_NUM_PAD_MULTIPLY,
			num_pad_divide					= WINDOWER_KEY_NUM_PAD_DIVIDE,
			num_pad_period					= WINDOWER_KEY_NUM_PAD_PPERIOD,
			tab								= WINDOWER_KEY_TAB,
			backspace						= WINDOWER_KEY_BACKSPACE,
			space							= WINDOWER_KEY_SPACE,
			a								= WINDOWER_KEY_A,
			b								= WINDOWER_KEY_B,
			c								= WINDOWER_KEY_C,
			d								= WINDOWER_KEY_D,
			e								= WINDOWER_KEY_E,
			f								= WINDOWER_KEY_F,
			g								= WINDOWER_KEY_G,
			h								= WINDOWER_KEY_H,
			i								= WINDOWER_KEY_I,
			j								= WINDOWER_KEY_J,
			k								= WINDOWER_KEY_K,
			l								= WINDOWER_KEY_L,
			m								= WINDOWER_KEY_M,
			n								= WINDOWER_KEY_N,
			o								= WINDOWER_KEY_O,
			p								= WINDOWER_KEY_P,
			q								= WINDOWER_KEY_Q,
			r								= WINDOWER_KEY_R,
			s								= WINDOWER_KEY_S,
			t								= WINDOWER_KEY_T,
			u								= WINDOWER_KEY_U,
			v								= WINDOWER_KEY_V,
			w								= WINDOWER_KEY_W,
			x								= WINDOWER_KEY_X,
			y								= WINDOWER_KEY_Y,
			z								= WINDOWER_KEY_Z,
			grave							= WINDOWER_KEY_GRAVE,
			number_1						= WINDOWER_KEY_1,
			number_2						= WINDOWER_KEY_2,
			number_3						= WINDOWER_KEY_3,
			number_4						= WINDOWER_KEY_4,
			number_5						= WINDOWER_KEY_5,
			number_6						= WINDOWER_KEY_6,
			number_7						= WINDOWER_KEY_7,
			number_8						= WINDOWER_KEY_8,
			number_9						= WINDOWER_KEY_9,
			number_0						= WINDOWER_KEY_0,
			minus							= WINDOWER_KEY_MINUS,
			equals							= WINDOWER_KEY_EQUALS,
			left_bracket					= WINDOWER_KEY_LEFT_BRACKET,
			right_bracket					= WINDOWER_KEY_RIGHT_BRACKET,
			backslash						= WINDOWER_KEY_BACKSLASH,
			semicolon						= WINDOWER_KEY_SEMICOLON,
			apostrophe						= WINDOWER_KEY_APOSTROPHE,
			comma							= WINDOWER_KEY_COMMA,
			period							= WINDOWER_KEY_PERIOD,
			slash							= WINDOWER_KEY_SLASH,
			caps_lock						= WINDOWER_KEY_CAPS_LOCK,
			play_pause						= WINDOWER_KEY_PLAY_PAUSE,
			stop							= WINDOWER_KEY_STOP,
			next_track						= WINDOWER_KEY_NEXT_TRACK,
			previous_track					= WINDOWER_KEY_PREVIOUS_TRACK,
			volume_up						= WINDOWER_KEY_VOLUME_UP,
			volume_down						= WINDOWER_KEY_VOLUME_DOWN,
			mute							= WINDOWER_KEY_MUTE,
			media_select					= WINDOWER_KEY_MEDIA_SELECT,
			power							= WINDOWER_KEY_POWER,
			sleep							= WINDOWER_KEY_SLEEP,
			wake							= WINDOWER_KEY_WAKE,
			web_back						= WINDOWER_KEY_WEB_BACK,
			web_forward						= WINDOWER_KEY_WEB_FORWARD,
			web_stop						= WINDOWER_KEY_WEB_STOP,
			web_refresh						= WINDOWER_KEY_WEB_REFRESH,
			web_home						= WINDOWER_KEY_WEB_HOME,
			web_search						= WINDOWER_KEY_WEB_SEARCH,
			web_bookmarks					= WINDOWER_KEY_WEB_BOOKMARKS,
			mail							= WINDOWER_KEY_MAIL,
			my_computer						= WINDOWER_KEY_MY_COMPUTER,
			calculator						= WINDOWER_KEY_CALCULATOR,
			yen								= WINDOWER_KEY_YEN,
			kana							= WINDOWER_KEY_KANA,
			kanji							= WINDOWER_KEY_KANJI,
			convert							= WINDOWER_KEY_CONVERT,
			no_convert						= WINDOWER_KEY_NO_CONVERT,
			circumflex						= WINDOWER_KEY_CIRCUMFLEX,
		};
	}

	namespace key_state
	{
		enum type
		{
			up								= WINDOWER_KEY_STATE_UP,
			down							= WINDOWER_KEY_STATE_DOWN,
		};
	}

	namespace input_kind
	{
		enum type
		{
			none							= WINDOWER_INPUT_TYPE_NONE,
			keyboard						= WINDOWER_INPUT_TYPE_KEYBOARD,
			mouse							= WINDOWER_INPUT_TYPE_MOUSE,
			all								= WINDOWER_INPUT_TYPE_ALL,
		};
	}

	namespace font_weight
	{
		enum type
		{
			default							= WINDOWER_TEXT_FONT_WEIGHT_DEFAULT,
			normal							= WINDOWER_TEXT_FONT_WEIGHT_NORMAL,
			bold							= WINDOWER_TEXT_FONT_WEIGHT_BOLD,
		};
	}

	namespace font_style
	{
		enum type
		{
			none							= WINDOWER_TEXT_FONT_STYLE_NONE,
			italic							= WINDOWER_TEXT_FONT_STYLE_ITALIC,
		};
	}

	namespace text_alignment
	{
		enum type
		{
			left							= WINDOWER_TEXT_ALIGN_LEFT,
			right							= WINDOWER_TEXT_ALIGN_RIGHT,
		};
	}

	class error : public std::runtime_error
	{
	public:
		error(unsigned int e) : std::runtime_error(error_string(error_code::type(e))), m_error_code(error_code::type(e)) { }

		error_code::type error_code()
		{
			return m_error_code;
		}

	private:
		static std::string error_string(error_code::type e)
		{
			switch(e)
			{
			default: return "unknown error";
			case error_code::none: return "no error";
			case error_code::out_of_memory: return "out of memory";
			case error_code::invalid_argument: return "invalid argument";
			case error_code::out_of_range: return "out of range";
			case error_code::invalid_handle: return "invalid handle";
			case error_code::connection_fault: return "connection fault";
			case error_code::connection_closed: return "connection closed";
			case error_code::interrupt: return "interrupt";
			case error_code::invalid_reply: return "invalid reply";
			case error_code::not_found: return "not found";
			case error_code::encoding: return "encoding error";
			}
		}

		error_code::type m_error_code;
	};

	class version
	{
	public:
		version(unsigned int major, unsigned int minor)
		{
			m_version = WINDOWER_VERSION(major, minor);
		}

		unsigned int major() const
		{
			return WINDOWER_GET_MAJOR(m_version);
		}

		unsigned int minor() const
		{
			return WINDOWER_GET_MINOR(m_version);
		}

		bool operator ==(version const& rhs) const
		{
			return m_version == rhs.m_version;
		}

		bool operator !=(version const& rhs) const
		{
			return m_version != rhs.m_version;
		}

		bool operator <=(version const& rhs) const
		{
			return m_version <= rhs.m_version;
		}

		bool operator <(version const& rhs) const
		{
			return m_version < rhs.m_version;
		}

		bool operator >=(version const& rhs) const
		{
			return m_version >= rhs.m_version;
		}

		bool operator >(version const& rhs) const
		{
			return m_version > rhs.m_version;
		}

	private:
		version(unsigned int version) : m_version(version) { }

		unsigned int m_version;

		friend class instance;
	};

	template<typename T>
	std::basic_ostream<T>& operator <<(std::basic_ostream<T>& lhs, version const& rhs)
	{
		return lhs << rhs.major() << T('.') << rhs.minor();
	}

	class instance
	{
	public:
		instance(unsigned int process)
		{
			if (unsigned int e = ::windower_create(&m_handle, process))
			{
				throw error(e);
			}
		}

		instance(std::string domain, unsigned int process)
		{
			if (unsigned int e = ::windower_create_remote(&m_handle, domain.c_str(), process))
			{
				throw error(e);
			}
		}

		~instance()
		{
			if (m_handle)
			{
				::windower_delete(m_handle);
				m_handle = 0;
			}
		}

		void dispose()
		{
			if (m_handle)
			{
				unsigned int e = ::windower_delete(m_handle);
				m_handle = 0;
				if (e)
				{
					throw error(e);
				}
			}
		}

		version version()
		{
			unsigned int v;
			if (unsigned int e = ::windower_get_version(m_handle, &v))
			{
				throw error(e);
			}
			return v;
		}


		void send(std::string string)
		{
			if (unsigned int e = ::windower_send_string(m_handle, string.c_str()))
			{
				throw error(e);
			}
		}

		void key_state(key::type key, key_state::type state)
		{
			if (unsigned int e = ::windower_set_key_state(m_handle, key, state))
			{
				throw error(e);
			}
		}

		void block(input_kind::type input_kind)
		{
			if (unsigned int e = ::windower_block(m_handle, input_kind))
			{
				throw error(e);
			}
		}

		void unblock(input_kind::type input_kind)
		{
			if (unsigned int e = ::windower_unblock(m_handle, input_kind))
			{
				throw error(e);
			}
		}

		bool next_command(std::string& command)
		{
			bool result = false;

			windower_command command_handle;
			unsigned int e = ::windower_next_command(m_handle, &command_handle);
			if (!e && command_handle)
			{
				size_t length;
				e = ::windower_command_length(command_handle, &length);
				if (!e)
				{
					char const* string;
					e = ::windower_command_string(command_handle, &string);
					if (!e)
					{
						command.assign(string, string + length);
						result = true;
					}
				}
				unsigned int temp = ::windower_command_delete(command_handle);
				e = !temp ? temp : e;
			}
			else if (!e)
			{
				throw error(e);
			}

			return result;
		}

	private:
		windower_instance m_handle;

		friend class text;
	};

	class text
	{
	public:
		text(instance const& instance, std::string const& name)
		{
			if (unsigned int e = ::windower_text_create(instance.m_handle, &m_handle, name.c_str()))
			{
				throw error(e);
			}
		}

		~text()
		{
			if (m_handle)
			{
				::windower_text_delete(m_handle);
				m_handle = 0;
			}
		}

		void dispose()
		{
			if (m_handle)
			{
				unsigned int e = ::windower_text_delete(m_handle);
				m_handle = 0;
				if (e)
				{
					throw error(e);
				}
			}
		}

		void string(std::string const& text)
		{
			if (unsigned int e = ::windower_text_set_text(m_handle, text.c_str()))
			{
				throw error(e);
			}
		}

		void show()
		{
			if (unsigned int e = ::windower_text_show(m_handle))
			{
				throw error(e);
			}
		}

		void hide()
		{
			if (unsigned int e = ::windower_text_hide(m_handle))
			{
				throw error(e);
			}
		}

		void location(int x, int y)
		{
			if (unsigned int e = ::windower_text_set_location(m_handle, x, y))
			{
				throw error(e);
			}
		}

		void foreground(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255)
		{
			if (unsigned int e = ::windower_text_set_foreground(m_handle, r, g, b, a))
			{
				throw error(e);
			}
		}

		void background(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255)
		{
			if (unsigned int e = ::windower_text_set_background(m_handle, r, g, b, a))
			{
				throw error(e);
			}
		}

		void show_background()
		{
			if (unsigned int e = ::windower_text_show_background(m_handle))
			{
				throw error(e);
			}
		}

		void hide_background()
		{
			if (unsigned int e = ::windower_text_hide_background(m_handle))
			{
				throw error(e);
			}
		}

		void font(std::string typeface, float size)
		{
			if (unsigned int e = ::windower_text_set_font(m_handle, typeface.c_str(), size))
			{
				throw error(e);
			}
		}

		void weight(font_weight::type weight)
		{
			if (unsigned int e = ::windower_text_set_weight(m_handle, weight))
			{
				throw error(e);
			}
		}

		void style(font_style::type style)
		{
			if (unsigned int e = ::windower_text_set_style(m_handle, style))
			{
				throw error(e);
			}
		}

		void alignment(text_alignment::type alignment)
		{
			if (unsigned int e = ::windower_text_set_alignment(m_handle, alignment))
			{
				throw error(e);
			}
		}

		void padding(float pixels)
		{
			if (unsigned int e = ::windower_text_set_padding(m_handle, pixels))
			{
				throw error(e);
			}
		}

	private:
		windower_text m_handle;
	};
}

#endif

#endif
