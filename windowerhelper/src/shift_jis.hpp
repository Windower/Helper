#ifndef SHIFT_JIS_HPP
#define SHIFT_JIS_HPP

/*
 * shift_jis.hpp
 * 
 * Copyright © 2012 Windower Team
 */

#pragma once

#include "unicode.hpp"
#include "shift_jis_decode_lut.hpp"
#include "shift_jis_encode_lut.hpp"

#include <iterator>

namespace shift_jis
{
    template<typename T, typename U>
    void decode(T const& input, U& output)
    {
        T::const_iterator begin = input.begin();
        T::const_iterator end = input.end();
        for (T::const_iterator i = begin; i != end; ++i)
        {
            unsigned int index = unsigned int(*i) & 0xFF;
            if (index == 0) return;

            if (index == 0xFD)
            {
                unicode::push_back(output, 0xF7FD);
                unsigned int count = 4;
                while (count-- > 0 && ++i != end)
                {
                    unicode::push_back(output, unsigned int(*i) & 0xFF | 0xF800);
                }
                if (i != end && ++i != end)
                {
                    index = unsigned int(*i) & 0xFF;
                    if (index == 0) return;
                    unicode::push_back(output, 0xF7FD);
                }
            }
            else
            {
                unicode::codepoint c = impl_ns::decode_lut[index];
                if (c >= 0xD800 && c <= 0xDEFF)
                {
                    unicode::push_back(output, (c & 0xFF) | 0xF700);
                    unsigned int count = (c >> 8) - 0xD8;
                    while (count-- > 0 && ++i != end)
                    {
                        index = unsigned int(*i) & 0xFF;
                        if (index == 0) return;
                        unicode::push_back(output, (unsigned int(*i) & 0xFF) | 0xF800);
                    }
                }
                else if (c == 0xDF00) { /* skip */ }
                else if (c >= 0xDF01 && c <= 0xDFFF)
                {
                    ++i;
                    if (i != end)
                    {
                        index = unsigned int(*i) & 0xFF;
                        if (index == 0) return;

                        index = 32 + (c & 0xFF) * 224 + index - 0x1F;
                        if (index >= impl_ns::decode_lut_size)
                        {
                            unicode::push_back(output, 0xFFFD);
                        }
                        else
                        {
                            c = impl_ns::decode_lut[index];
                            unicode::push_back(output, c);
                        }
                    }
                }
                else
                {
                    unicode::push_back(output, c);
                }
            }
        }
    }

    template<typename T, typename U>
    void encode(T const& input, U& output)
    {
        typedef typename T::value_type value_type;

        T::const_iterator begin = input.begin();
        T::const_iterator end = input.end();
        for (T::const_iterator i = begin; i != end;)
        {
            unicode::codepoint c = unicode::next(i, end);
            if (c >= 0xFFFF)
            {
                c = 0x8541;
            }
            else if (c >= 0xF8FF)
            {
                c = impl_ns::encode_lut[c - 0x18FF];
            }
            else
            {
                c = impl_ns::encode_lut[c];
            }

            if (c >= 0xFF)
            {
                output.push_back(value_type((c >> 8) & 0xFF));
            }
            output.push_back(value_type(c & 0xFF));
        }
    }
}

#endif
