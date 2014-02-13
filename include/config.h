/*****************************************************************************/
/** \file config.h
 *   General configuration and definitions for agency project.
 *
 * \copyright (C) 2012, R&D\n
 *   All rights reserved.
 * \date 2011.05.30
 * \version 1.0.0    Prelimnary version, first Release
 * \author amir zamani
 */

#ifndef _CONFIG_H_
#define _CONFIG_H_
/*****************************************************************************/
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#if defined(__linux__) && defined(__GNUC__)
#   include <stdint-gcc.h>

#elif defined(WINCE)
   typedef signed char       int8_t;
   typedef signed short      int16_t;
   typedef signed int        int32_t;
   typedef unsigned char     uint8_t;
   typedef unsigned short    uint16_t;
   typedef unsigned int      uint32_t;

/* __unix__ or __APPLE__ or _WINDOWS */
#else
#   include <stdint.h>

#endif


#if defined     (_WINDOWS)
#   include <windows.h>
#   pragma warning(disable : 4996)
#   define snprintf     _snprintf
#   define snscanf      _snscanf
#   define snwprintf    _snwprintf

#elif defined   (__GNUC__)
#   define snwprintf    swprintf
#endif

/*****************************************************************************/
#endif /* _CONFIG_H_ */
