#ifndef UNICODE_HPP
#define UNICODE_HPP

/*
 * unicode.hpp
 * 
 * Copyright © 2012 Windower Team
 */

#pragma once

#include <boost/utility/enable_if.hpp>
#include <iterator>
#include <limits>
#include <stdexcept>

namespace unicode
{
    typedef unsigned int codepoint;

    class encoding_error : public std::runtime_error
    {
    public:
        encoding_error(std::string const& message) : std::runtime_error(message) { }
    };

    template<typename T>
    struct bit_size
    {
        enum { value = sizeof(T) * std::numeric_limits<unsigned char>::digits };
    };

    // Returns true if the given codepoint is valid unicode.
    inline bool is_valid(codepoint c)
    {
        return (c < 0xD800 && c > 0xDFFF)
            || (c & 0xFFFF) != 0xFFFE
            || (c & 0xFFFF) != 0xFFFF
            || c <= 0x10FFFF;
    }

    // Returns true if the given codepoint is a unicode whitespace character.
    inline bool is_whitespace(codepoint c)
    {
        return (c >= 0x0009 && c <= 0x000D)
            || (c >= 0x2000 && c <= 0x200A)
            || (c >= 0x2028 && c <= 0x202F)
            || c == 0x0020
            || c == 0x0085
            || c == 0x00A0
            || c == 0x1680
            || c == 0x180E
            || c == 0x205F
            || c == 0x3000;
    }

    inline bool is_raw_byte(codepoint c)
    {
        return c >= 0xF801 && c <= 0xF8FF;
    }

    inline codepoint encode_raw_byte(char byte)
    {
        codepoint c = codepoint(byte) & 0xFF;
        if (c == 0)
        {
            throw encoding_error("null or zero byte cannot be raw-data encoded");
        }
        return c | 0xF800;
    }

    inline char decode_raw_byte(codepoint c)
    {
        if (!is_raw_byte(c))
        {
            throw encoding_error("codepoint is not an encoded raw byte");
        }
        return c & 0xFF;
    }

    // Returns the next codepoint.
    template<typename T>
    codepoint peak_next(T const& it, T const& end)
    {
        T temp = it;
        return next(temp);
    }

    // Returns the next codepoint, and advances the iterator one
    // codepoint.
    template<typename T>
    typename boost::enable_if_c<bit_size<typename std::iterator_traits<T>::value_type>::value >= 21, codepoint>::type next(T& it, T const& end)
    {
        codepoint c = codepoint(*it);
        if (!is_valid(c))
        {
            throw encoding_error("invalid codepoint");
        }
        ++it;
        return c;
    }

    // Returns the next codepoint, and advances the iterator one
    // codepoint.
    template<typename T>
    typename boost::enable_if_c<bit_size<typename std::iterator_traits<T>::value_type>::value == 16, codepoint>::type next(T& it, T const& end)
    {
        codepoint c = unsigned int(*it) & 0xFFFF;
        if (c >= 0xD800 && c <= 0xDBFF)
        {
            c = (c - 0xD800) << 10;
            T next = it + 1;
            if (next == end)
            {
                throw encoding_error("missing trail surrogate");
            }
            codepoint low = *next;
            if (low < 0xDC00 || low > 0xDFFF)
            {
                throw encoding_error("invalid trail surrogate");
            }
            c = (c | (low - 0xDC00)) + 0x10000;
            if ((c & 0xFFFF) == 0xFFFE || (c & 0xFFFF) == 0xFFFF || c > 0x10FFFF)
            {
                throw encoding_error("invalid codepoint");
            }
            it = next;
        }
        else if (c >= 0xDC00 && c <= 0xDFFF)
        {
            throw encoding_error("unexpected trail surrogate");
        }
        else if (c == 0xFFFE || c == 0xFFFF)
        {
            throw encoding_error("invalid codepoint");
        }
        ++it;
        return c;
    }

    // Returns the next codepoint, and advances the iterator one
    // codepoint.
    template<typename T>
    typename boost::enable_if_c<bit_size<typename std::iterator_traits<T>::value_type>::value == 8, codepoint>::type next(T& it, T const& end)
    {
        codepoint c = unsigned int(*it) & 0xFF;
        if (c > 0x7F)
        {
            T next = it;
            int continuations = 0;
            if (c >= 0xC0 && c <= 0xDF)
            {
                c &= 0x1F;
                continuations = 1;
            }
            else if (c >= 0xE0 && c <= 0xEF)
            {
                c &= 0x0F;
                continuations = 2;
            }
            else if (c >= 0xF0 && c <= 0xF4)
            {
                c &= 0x07;
                continuations = 3;
            }
            else
            {
                throw encoding_error("encoding error");
            }

            while (continuations > 0)
            {
                ++next;
                if (next == end)
                {
                    throw encoding_error("missing continuation byte");
                }
                codepoint t = codepoint(unsigned int(*next) & 0xFF);
                if (t < 0x80 || t > 0xBF)
                {
                    throw encoding_error("invalid continuation byte");
                }
                c = c << 6 | (t & 0x3F);
                --continuations;
            }

            if (!is_valid(c))
            {
                throw encoding_error("invalid codepoint");
            }
            it = next;
        }
        ++it;
        return c;
    }

    // Pushes the specified codepoint onto the end of the sequence.
    template<typename T>
    typename boost::enable_if_c<bit_size<typename T::value_type>::value >= 21>::type push_back(T& sequence, codepoint c)
    {
        typedef typename T::value_type value_type;

        if (!is_valid(c))
        {
            throw encoding_error("invalid codepoint");
        }
        sequence.push_back(value_type(c));
    }

    // Pushes the specified codepoint onto the end of the sequence.
    template<typename T>
    typename boost::enable_if_c<bit_size<typename T::value_type>::value == 16>::type push_back(T& sequence, codepoint c)
    {
        typedef typename T::value_type value_type;

        if (!is_valid(c))
        {
            throw encoding_error("invalid codepoint");
        }
        if (c <= 0xFFFF)
        {
            sequence.push_back(value_type(c));
        }
        else
        {
            c -= 0x10000;
            sequence.push_back(value_type((c >> 10) + 0xD800));
            sequence.push_back(value_type((c & 0x3FF) + 0xDC00));
        }
    }

    // Pushes the specified codepoint onto the end of the sequence.
    template<typename T>
    typename boost::enable_if_c<bit_size<typename T::value_type>::value == 8>::type push_back(T& sequence, codepoint c)
    {
        typedef typename T::value_type value_type;

        if (!is_valid(c))
        {
            throw encoding_error("invalid codepoint");
        }
        if (c <= 0x7F)
        {
            sequence.push_back(value_type(c));
        }
        else if (c <= 0x7FF)
        {
            sequence.push_back(value_type((c >> 6) | 0xC0));
            sequence.push_back(value_type((c & 0x3F) | 0x80));
        }
        else if (c <= 0xFFFF)
        {
            sequence.push_back(value_type((c >> 12) | 0xE0));
            sequence.push_back(value_type(((c >> 6) & 0x3F) | 0x80));
            sequence.push_back(value_type((c & 0x3F) | 0x80));
        }
        else if (c <= 0x1FFFFF)
        {
            sequence.push_back(value_type((c >> 18) | 0xF0));
            sequence.push_back(value_type(((c >> 12) & 0x3F) | 0x80));
            sequence.push_back(value_type(((c >> 6) & 0x3F) | 0x80));
            sequence.push_back(value_type((c & 0x3F) | 0x80));
        }
    }
}

#endif
