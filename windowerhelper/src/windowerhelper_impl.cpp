/*
 * windower_helper_impl.c
 * 
 * Copyright © 2012 Windower Team
 */

#include "windowerhelper_impl.hpp"

#include <zmq.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>
#include <boost/scoped_ptr.hpp>
#include <cstdlib>
#include <exception>
#include <new>

namespace
{
	unsigned short int const port_first	= 49980;
	unsigned short int const port_last	= 49999;

	class error : public std::exception
	{
	public:
		error(unsigned int error_code) : m_error_code(error_code) { }

		unsigned int error_code() const
		{
			return m_error_code;
		}

	private:
		unsigned int m_error_code;
	};

	unsigned int get_error_code(std::exception const& exception)
	{
		if (dynamic_cast<std::bad_alloc const*>(&exception))
		{
			return WINDOWER_ERROR_OUT_OF_MEMORY;
		}
		else if (dynamic_cast<std::invalid_argument const*>(&exception) || dynamic_cast<std::domain_error const*>(&exception))
		{
			return WINDOWER_ERROR_INVALID_ARGUMENT;
		}
		else if (dynamic_cast<std::out_of_range const*>(&exception))
		{
			return WINDOWER_ERROR_OUT_OF_RANGE;
		}
		else if (error const* e = dynamic_cast<error const*>(&exception))
		{
			return e->error_code();
		}
		else if (zmq::error_t const* e = dynamic_cast<zmq::error_t const*>(&exception))
		{
			switch (e->num())
			{
			case EINTR:		return WINDOWER_ERROR_INTERRUPT;
			case EAGAIN:	return WINDOWER_ERROR_TIME_OUT;
			case ENOMEM:	return WINDOWER_ERROR_OUT_OF_MEMORY;
			case ETERM:		return WINDOWER_ERROR_CONNECTION_CLOSED;
			}
			return WINDOWER_ERROR_CONNECTION_FAULT;
		}
		return WINDOWER_ERROR_UNKNOWN;
	}
}

struct windower_instance_type
{
public:
	windower_instance_type(char const* domain, unsigned int process)
		: m_version(0), m_command_index(0), m_command_initialized(false)
	{
		if (!domain) { throw error(WINDOWER_ERROR_INVALID_ARGUMENT); }

		m_context.reset(new zmq::context_t(1));

		for (unsigned short int i = port_first; i <= port_last && !m_socket; ++i)
		{
			boost::scoped_ptr<zmq::socket_t> temp(new zmq::socket_t(*m_context, ZMQ_REQ));

			int timeout = 200;
			temp->setsockopt(ZMQ_RCVTIMEO, &timeout, sizeof timeout);
			timeout = 0;
			temp->setsockopt(ZMQ_SNDTIMEO, &timeout, sizeof timeout);
			temp->setsockopt(ZMQ_LINGER, &timeout, sizeof timeout);

			try
			{
				temp->connect((boost::format("tcp://%1%:%2%") % domain % i).str().c_str());
				std::string reply = request(temp, "HELPERMSG INIT");
				std::string::size_type delim = reply.find(' ');
				if (boost::lexical_cast<unsigned int>(reply.substr(0, delim)) == process)
				{
					m_socket.swap(temp);

					unsigned int major = 0;
					unsigned int minor = 0;
					std::string::size_type point = reply.find('.', delim);
					major = boost::lexical_cast<unsigned int>(reply.substr(delim + 1, point - delim - 1));
					if (point != std::string::npos)
					{
						minor = boost::lexical_cast<unsigned int>(reply.substr(point + 1));
					}
					m_version = WINDOWER_VERSION(major, minor);
				}
			}
			catch (boost::bad_lexical_cast const&) { }
			catch (error const&) { }
		}

		if (!m_socket) { throw error(WINDOWER_ERROR_NOT_FOUND); }

		int timeout = 1000;
		m_socket->setsockopt(ZMQ_RCVTIMEO, &timeout, sizeof timeout);
		timeout = 1000;
		m_socket->setsockopt(ZMQ_LINGER, &timeout, sizeof timeout);
	}

	unsigned int get_version()
	{
		return m_version;
	}

	void send_string(char const* string)
	{
		request((boost::format("HELPERMSG SENDSTRING %1%") % string).str());
	}

	void set_key_state(unsigned int key, unsigned int state)
	{
		if (state != WINDOWER_KEY_STATE_UP)
		{
			state = WINDOWER_KEY_STATE_DOWN;
		}
		request((boost::format("HELPERMSG SETKEY %1% %2%") % key % state).str());
	}

	void block(unsigned int input_kind)
	{
		input_kind &= WINDOWER_INPUT_TYPE_ALL;
		request((boost::format("HELPERMSG BLOCK %1%") % input_kind).str());
	}

	void unblock(unsigned int input_kind)
	{
		input_kind &= WINDOWER_INPUT_TYPE_ALL;
		request((boost::format("HELPERMSG UNBLOCK %1%") % input_kind).str());
	}

private:
	static std::string request(boost::scoped_ptr<zmq::socket_t> const& socket, std::string const& string)
	{
		boost::mutex::scoped_lock(m_mutex);

		zmq::message_t message(string.size());
		std::memcpy(message.data(), string.data(), string.size());
		socket->send(message);
		message.rebuild();
		socket->recv(&message);
		char const* begin = reinterpret_cast<char const*>(message.data());
		char const* end = begin + message.size();
		std::string reply(begin, end);
		if (reply == "OK")
		{
			return "";
		}
		else if (boost::starts_with(reply, "OK "))
		{
			return reply.substr(3);
		}
		else if (boost::starts_with(reply, "ERROR "))
		{
			try
			{
				switch (boost::lexical_cast<unsigned int>(reply.substr(6)))
				{
				default: throw error(WINDOWER_ERROR_UNKNOWN);
				case 1:
				case 7:
				case 9: throw error(WINDOWER_ERROR_INVALID_ARGUMENT);
				case 4: throw error(WINDOWER_ERROR_OUT_OF_RANGE);
				case 5: throw error(WINDOWER_ERROR_ENCODING);
				case 8: throw error(WINDOWER_ERROR_NOT_FOUND);
				}
			}
			catch (boost::bad_lexical_cast const&) { }
		}
		throw error(WINDOWER_ERROR_INVALID_REPLY);
	}

	boost::mutex m_mutex;
	boost::scoped_ptr<zmq::context_t> m_context;
	boost::scoped_ptr<zmq::socket_t> m_socket;
	unsigned int m_version;
	unsigned int m_command_index;
	bool m_command_initialized;

	std::string request(std::string const& string)
	{
		return request(m_socket, string);
	}

	friend struct windower_command_type;
	friend struct windower_text_type;
};

struct windower_command_type
{
public:
	windower_command_type(windower_instance handle)
	{
		if (!handle->m_command_initialized)
		{
			try
			{
				handle->m_command_index = boost::lexical_cast<unsigned int>(handle->request("HELPERMSG GETCOMMANDINDEX"));
				handle->m_command_initialized = true;
			}
			catch (boost::bad_lexical_cast const&)
			{
				throw error(WINDOWER_ERROR_INVALID_REPLY);
			}
		}
		m_command = handle->request((boost::format("HELPERMSG GETCOMMAND %1%") % handle->m_command_index).str());
		++handle->m_command_index;
	}

	unsigned int length()
	{
		size_t length = m_command.size();
		return length > 0x7FFFFFFF ? 0x7FFFFFFF : unsigned int(length);
	}

	char const* string()
	{
		return m_command.c_str();
	}

private:
	std::string m_command;
};

struct windower_text_type
{
public:
	windower_text_type(windower_instance handle, const char* name)
		: m_instance(handle), m_name(name)
	{
		for (char const* c = name; *c != 0; ++c)
		{
			if (*c < 0x21 || *c > 0x7E)
			{
				throw error(WINDOWER_ERROR_ENCODING);
			}
		}
		m_instance->request((boost::format("HELPERMSG CREATETEXT %1%") % m_name).str());
	}

	~windower_text_type()
	{
		m_instance->request((boost::format("HELPERMSG DELETETEXT %1%") % m_name).str());
	}

	void set_text(char const* text)
	{
		m_instance->request((boost::format("HELPERMSG TEXTSETTEXT %1% %2%") % m_name % text).str());
	}

	void show()
	{
		m_instance->request((boost::format("HELPERMSG TEXTSETVISIBLE %1% 1") % m_name).str());
	}

	void hide()
	{
		m_instance->request((boost::format("HELPERMSG TEXTSETVISIBLE %1% 0") % m_name).str());
	}

	void set_location(int x, int y)
	{
		m_instance->request((boost::format("HELPERMSG TEXTSETLOCATION %1% %2% %3%") % m_name % x % y).str());
	}

	void set_foreground(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	{
		m_instance->request((boost::format("HELPERMSG TEXTSETCOLOR %1% %5% %2% %3% %4%") % m_name % int(r) % int(g) % int(b) % int(a)).str());
	}

	void set_background(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	{
		m_instance->request((boost::format("HELPERMSG TEXTSETBGCOLOR %1% %5% %2% %3% %4%") % m_name % int(r) % int(g) % int(b) % int(a)).str());
	}

	void show_background()
	{
		m_instance->request((boost::format("HELPERMSG TEXTSETBGVISIBLE %1% 1") % m_name).str());
	}

	void hide_background()
	{
		m_instance->request((boost::format("HELPERMSG TEXTSETBGVISIBLE %1% 0") % m_name).str());
	}

	void set_font(char const* typeface, float size)
	{
		m_instance->request((boost::format("HELPERMSG TEXTSETFONT %1% %2% %3%") % m_name % int(size) % typeface).str());
	}

	void set_weight(unsigned int weight)
	{
		if (weight > 999)
		{
			throw error(WINDOWER_ERROR_OUT_OF_RANGE);
		}

		if (weight >= 700)
		{
			m_instance->request((boost::format("HELPERMSG TEXTSETBOLD %1% 1") % m_name).str());
		}
		else
		{
			m_instance->request((boost::format("HELPERMSG TEXTSETBOLD %1% 0") % m_name).str());
		}
	}

	void set_style(unsigned int style)
	{
		if (style & WINDOWER_TEXT_FONT_STYLE_ITALIC)
		{
			m_instance->request((boost::format("HELPERMSG TEXTSETITALIC %1% 1") % m_name).str());
		}
		else
		{
			m_instance->request((boost::format("HELPERMSG TEXTSETITALIC %1% 0") % m_name).str());
		}
	}

	void set_alignment(unsigned int alignment)
	{
		if (alignment != WINDOWER_TEXT_ALIGN_LEFT)
		{
			alignment = WINDOWER_TEXT_ALIGN_RIGHT;
		}
		m_instance->request((boost::format("HELPERMSG TEXTSETALIGNMENT %1% %2%") % m_name % alignment).str());
	}

	void set_padding(float pixels)
	{
		m_instance->request((boost::format("HELPERMSG TEXTSETBGBORDERSIZE %1% %2%") % m_name % pixels).str());
	}

private:
	windower_instance m_instance;
	std::string m_name;
};

extern "C"
{
	unsigned int windower_create(windower_instance* result, unsigned int process)
	{
		return ::windower_create_remote(result, "localhost", process);
	}

	unsigned int windower_create_remote(windower_instance* result, char const* domain, unsigned int process)
	{
		try
		{
			*result = new windower_instance_type(domain, process);
			return WINDOWER_ERROR_NONE;
		}
		catch (std::exception const& e) { return get_error_code(e); }
		catch (...) { return WINDOWER_ERROR_UNKNOWN; }
	}

	unsigned int windower_delete(windower_instance handle)
	{
		if (handle)
		{
			try
			{
				delete handle;
				return WINDOWER_ERROR_NONE;
			}
			catch (std::exception const& e) { return get_error_code(e); }
			catch (...) { return WINDOWER_ERROR_UNKNOWN; }
		}
		return WINDOWER_ERROR_INVALID_HANDLE;
	}

	unsigned int windower_get_version(windower_instance handle, unsigned int* result)
	{
		if (handle)
		{
			try
			{
				*result = handle->get_version();
				return WINDOWER_ERROR_NONE;
			}
			catch (std::exception const& e) { return get_error_code(e); }
			catch (...) { return WINDOWER_ERROR_UNKNOWN; }
		}
		return WINDOWER_ERROR_INVALID_HANDLE;
	}

	unsigned int windower_send_string(windower_instance handle, char const* string)
	{
		if (handle)
		{
			try
			{
				handle->send_string(string);
				return WINDOWER_ERROR_NONE;
			}
			catch (std::exception const& e) { return get_error_code(e); }
			catch (...) { return WINDOWER_ERROR_UNKNOWN; }
		}
		return WINDOWER_ERROR_INVALID_HANDLE;
	}

	unsigned int windower_set_key_state(windower_instance handle, unsigned int key, unsigned int state)
	{
		if (handle)
		{
			try
			{
				handle->set_key_state(key, state);
				return WINDOWER_ERROR_NONE;
			}
			catch (std::exception const& e) { return get_error_code(e); }
			catch (...) { return WINDOWER_ERROR_UNKNOWN; }
		}
		return WINDOWER_ERROR_INVALID_HANDLE;
	}

	unsigned int windower_block(windower_instance handle, unsigned int input_kind)
	{
		if (handle)
		{
			try
			{
				handle->block(input_kind);
				return WINDOWER_ERROR_NONE;
			}
			catch (std::exception const& e) { return get_error_code(e); }
			catch (...) { return WINDOWER_ERROR_UNKNOWN; }
		}
		return WINDOWER_ERROR_INVALID_HANDLE;
	}

	unsigned int windower_unblock(windower_instance handle, unsigned int input_kind)
	{
		if (handle)
		{
			try
			{
				handle->unblock(input_kind);
				return WINDOWER_ERROR_NONE;
			}
			catch (std::exception const& e) { return get_error_code(e); }
			catch (...) { return WINDOWER_ERROR_UNKNOWN; }
		}
		return WINDOWER_ERROR_INVALID_HANDLE;
	}

	unsigned int windower_next_command(windower_instance handle, windower_command* result)
	{
		if (handle)
		{
			try
			{
				*result = new windower_command_type(handle);
				return WINDOWER_ERROR_NONE;
			}
			catch (std::exception const& e) { return get_error_code(e); }
			catch (...) { return WINDOWER_ERROR_UNKNOWN; }
		}
		return WINDOWER_ERROR_INVALID_HANDLE;
	}

	unsigned int windower_command_delete(windower_command handle)
	{
		if (handle)
		{
			try
			{
				delete handle;
				return WINDOWER_ERROR_NONE;
			}
			catch (std::exception const& e) { return get_error_code(e); }
			catch (...) { return WINDOWER_ERROR_UNKNOWN; }
		}
		return WINDOWER_ERROR_INVALID_HANDLE;
	}

	unsigned int windower_command_length(windower_command handle, unsigned int* result)
	{
		if (handle)
		{
			try
			{
				*result = handle->length();
				return WINDOWER_ERROR_NONE;
			}
			catch (std::exception const& e) { return get_error_code(e); }
			catch (...) { return WINDOWER_ERROR_UNKNOWN; }
		}
		return WINDOWER_ERROR_INVALID_HANDLE;
	}

	unsigned int windower_command_string(windower_command handle, char const** result)
	{
		if (handle)
		{
			try
			{
				*result = handle->string();
				return WINDOWER_ERROR_NONE;
			}
			catch (std::exception const& e) { return get_error_code(e); }
			catch (...) { return WINDOWER_ERROR_UNKNOWN; }
		}
		return WINDOWER_ERROR_INVALID_HANDLE;
	}

	unsigned int windower_text_create(windower_instance handle, windower_text* result, char const* name)
	{
		if (handle)
		{
			try
			{
				*result = new windower_text_type(handle, name);
				return WINDOWER_ERROR_NONE;
			}
			catch (std::exception const& e) { return get_error_code(e); }
			catch (...) { return WINDOWER_ERROR_UNKNOWN; }
		}
		return WINDOWER_ERROR_INVALID_HANDLE;
	}

	unsigned int windower_text_delete(windower_text handle)
	{
		if (handle)
		{
			try
			{
				delete handle;
				return WINDOWER_ERROR_NONE;
			}
			catch (std::exception const& e) { return get_error_code(e); }
			catch (...) { return WINDOWER_ERROR_UNKNOWN; }
		}
		return WINDOWER_ERROR_INVALID_HANDLE;
	}

	unsigned int windower_text_set_text(windower_text handle, char const* text)
	{
		if (handle)
		{
			try
			{
				handle->set_text(text);
				return WINDOWER_ERROR_NONE;
			}
			catch (std::exception const& e) { return get_error_code(e); }
			catch (...) { return WINDOWER_ERROR_UNKNOWN; }
		}
		return WINDOWER_ERROR_INVALID_HANDLE;
	}

	unsigned int windower_text_show(windower_text handle)
	{
		if (handle)
		{
			try
			{
				handle->show();
				return WINDOWER_ERROR_NONE;
			}
			catch (std::exception const& e) { return get_error_code(e); }
			catch (...) { return WINDOWER_ERROR_UNKNOWN; }
		}
		return WINDOWER_ERROR_INVALID_HANDLE;
	}

	unsigned int windower_text_hide(windower_text handle)
	{
		if (handle)
		{
			try
			{
				handle->hide();
				return WINDOWER_ERROR_NONE;
			}
			catch (std::exception const& e) { return get_error_code(e); }
			catch (...) { return WINDOWER_ERROR_UNKNOWN; }
		}
		return WINDOWER_ERROR_INVALID_HANDLE;
	}

	unsigned int windower_text_set_location(windower_text handle, int x, int y)
	{
		if (handle)
		{
			try
			{
				handle->set_location(x, y);
				return WINDOWER_ERROR_NONE;
			}
			catch (std::exception const& e) { return get_error_code(e); }
			catch (...) { return WINDOWER_ERROR_UNKNOWN; }
		}
		return WINDOWER_ERROR_INVALID_HANDLE;
	}

	unsigned int windower_text_set_foreground(windower_text handle, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	{
		if (handle)
		{
			try
			{
				handle->set_foreground(r, g, b, a);
				return WINDOWER_ERROR_NONE;
			}
			catch (std::exception const& e) { return get_error_code(e); }
			catch (...) { return WINDOWER_ERROR_UNKNOWN; }
		}
		return WINDOWER_ERROR_INVALID_HANDLE;
	}

	unsigned int windower_text_set_background(windower_text handle, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	{
		if (handle)
		{
			try
			{
				handle->set_background(r, g, b, a);
				return WINDOWER_ERROR_NONE;
			}
			catch (std::exception const& e) { return get_error_code(e); }
			catch (...) { return WINDOWER_ERROR_UNKNOWN; }
		}
		return WINDOWER_ERROR_INVALID_HANDLE;
	}

	unsigned int windower_text_show_background(windower_text handle)
	{
		if (handle)
		{
			try
			{
				handle->show_background();
				return WINDOWER_ERROR_NONE;
			}
			catch (std::exception const& e) { return get_error_code(e); }
			catch (...) { return WINDOWER_ERROR_UNKNOWN; }
		}
		return WINDOWER_ERROR_INVALID_HANDLE;
	}

	unsigned int windower_text_hide_background(windower_text handle)
	{
		if (handle)
		{
			try
			{
				handle->hide_background();
				return WINDOWER_ERROR_NONE;
			}
			catch (std::exception const& e) { return get_error_code(e); }
			catch (...) { return WINDOWER_ERROR_UNKNOWN; }
		}
		return WINDOWER_ERROR_INVALID_HANDLE;
	}

	unsigned int windower_text_set_font(windower_text handle, char const* typeface, float size)
	{
		if (handle)
		{
			try
			{
				handle->set_font(typeface, size);
				return WINDOWER_ERROR_NONE;
			}
			catch (std::exception const& e) { return get_error_code(e); }
			catch (...) { return WINDOWER_ERROR_UNKNOWN; }
		}
		return WINDOWER_ERROR_INVALID_HANDLE;
	}

	unsigned int windower_text_set_weight(windower_text handle, unsigned int weight)
	{
		if (handle)
		{
			try
			{
				handle->set_weight(weight);
				return WINDOWER_ERROR_NONE;
			}
			catch (std::exception const& e) { return get_error_code(e); }
			catch (...) { return WINDOWER_ERROR_UNKNOWN; }
		}
		return WINDOWER_ERROR_INVALID_HANDLE;
	}

	unsigned int windower_text_set_style(windower_text handle, unsigned int style)
	{
		if (handle)
		{
			try
			{
				handle->set_style(style);
				return WINDOWER_ERROR_NONE;
			}
			catch (std::exception const& e) { return get_error_code(e); }
			catch (...) { return WINDOWER_ERROR_UNKNOWN; }
		}
		return WINDOWER_ERROR_INVALID_HANDLE;
	}

	unsigned int windower_text_set_alignment(windower_text handle, unsigned int alignment)
	{
		if (handle)
		{
			try
			{
				handle->set_alignment(alignment);
				return WINDOWER_ERROR_NONE;
			}
			catch (std::exception const& e) { return get_error_code(e); }
			catch (...) { return WINDOWER_ERROR_UNKNOWN; }
		}
		return WINDOWER_ERROR_INVALID_HANDLE;
	}

	unsigned int windower_text_set_padding(windower_text handle, float pixels)
	{
		if (handle)
		{
			try
			{
				handle->set_padding(pixels);
				return WINDOWER_ERROR_NONE;
			}
			catch (std::exception const& e) { return get_error_code(e); }
			catch (...) { return WINDOWER_ERROR_UNKNOWN; }
		}
		return WINDOWER_ERROR_INVALID_HANDLE;
	}
}
