// -*- C++ -*-
/*!
 *
 * THIS FILE IS GENERATED AUTOMATICALLY!! DO NOT EDIT!!
 *
 * @file imProcessPortSkel.h 
 * @brief imProcessPort server skeleton header wrapper code
 * @date Wed May 24 17:23:35 2017 
 *
 */

#ifndef _IMPROCESSPORTSKEL_H
#define _IMPROCESSPORTSKEL_H



#include <rtm/config_rtc.h>
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION

#if   defined ORB_IS_TAO
#  include "imProcessPortC.h"
#  include "imProcessPortS.h"
#elif defined ORB_IS_OMNIORB
#  if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#    undef USE_stub_in_nt_dll
#  endif
#  include "imProcessPort.hh"
#elif defined ORB_IS_MICO
#  include "imProcessPort.h"
#elif defined ORB_IS_ORBIT2
#  include "/imProcessPort-cpp-stubs.h"
#  include "/imProcessPort-cpp-skels.h"
#elif defined ORB_IS_RTORB
#  include "imProcessPort.h"
#else
#  error "NO ORB defined"
#endif

#endif // _IMPROCESSPORTSKEL_H
