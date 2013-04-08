#ifndef WINDOWERHELPER_IMPL_H
#define WINDOWERHELPER_IMPL_H

/*
 * windower_helper_impl.h
 * 
 * Copyright © 2012 Windower Team
 */

#pragma once

#ifdef WINDOWER_HELPER_STATIC
#   define WINDOWER_HELPER_API
#else
#   define WINDOWER_HELPER_API __declspec(dllexport)
#endif

#define WINDOWER_HELPER_NO_CLASSES

#include <windowerhelper.h>

#endif
