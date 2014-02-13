/** \file config.hpp
 *   General configuration and definitions for Agency project.
 *
 * \date 2010.12.20
 * \version 1.0.0    Prelimnary version, first Release
 * \author amir zamani
 */

#ifndef _CONFIG_HPP_
#define _CONFIG_HPP_
///////////////////////////////////////////////////////////////////////////////
#include "config.h"
#ifdef __GNUC__
#   include <syslog.h>
#endif

#include <QtCore/QString>
///////////////////////////////////////////////////////////////////////////////
typedef wchar_t         *wchars;
typedef const wchar_t   *cwchars;
typedef char            *chars;
typedef const char      *cchars;
typedef uint8_t         *uchars;
typedef const uint8_t   *cuchars;

///////////////////////////////////////////////////////////////////////////////
#ifndef qTimeStamp
#   define qTimeStamp  QDateTime::currentDateTime().toString("yyyyMMdd-hhmmss")
#endif // qTimeStamp

#ifndef qTimeTick
#   define qTimeTick   QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz")
#endif // qTimeTick
///////////////////////////////////////////////////////////////////////////////


#endif /* _CONFIG_HPP_ */
