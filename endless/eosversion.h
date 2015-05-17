/* Copyright 2013-2015 Endless Mobile, Inc. */

#ifndef API_VERSION_H
#define API_VERSION_H

#if !(defined(_EOS_SDK_INSIDE_ENDLESS_H) || defined(COMPILING_EOS_SDK))
#error "Please do not include this header file directly."
#endif

#include <glib.h>

#ifdef EOS_SDK_DISABLE_DEPRECATION_WARNINGS
#define EOS_SDK_DEPRECATED
#define EOS_SDK_DEPRECATED_FOR(f)
#define EOS_SDK_UNAVAILABLE(maj,min)
#else
#define EOS_SDK_DEPRECATED G_DEPRECATED
#define EOS_SDK_DEPRECATED_FOR(f) G_DEPRECATED_FOR(f)
#define EOS_SDK_UNAVAILABLE(maj,min) G_UNAVAILABLE(maj,min)
#endif

/* Each new stable series should add a new version symbol here. If necessary,
define EOS_SDK_VERSION_MIN_REQUIRED and EOS_SDK_VERSION_MAX_ALLOWED to one of
these macros. */
#define EOS_SDK_VERSION_0_0 (G_ENCODE_VERSION (0, 0))
#define EOS_SDK_VERSION_0_2 (G_ENCODE_VERSION (0, 2))

#if (EOS_SDK_MINOR_VERSION == 99)
#define EOS_SDK_VERSION_CUR_STABLE (G_ENCODE_VERSION (EOS_SDK_MAJOR_VERSION + 1, 0))
#elif (EOS_SDK_MINOR_VERSION % 2)
#define EOS_SDK_VERSION_CUR_STABLE (G_ENCODE_VERSION (EOS_SDK_MAJOR_VERSION, EOS_SDK_MINOR_VERSION + 1))
#else
#define EOS_SDK_VERSION_CUR_STABLE (G_ENCODE_VERSION (EOS_SDK_MAJOR_VERSION, EOS_SDK_MINOR_VERSION))
#endif

/* evaluates to the previous stable version */
#if (EOS_SDK_MINOR_VERSION == 99)
#define EOS_SDK_VERSION_PREV_STABLE (G_ENCODE_VERSION (EOS_SDK_MAJOR_VERSION + 1, 0))
#elif (EOS_SDK_MINOR_VERSION % 2)
#define EOS_SDK_VERSION_PREV_STABLE (G_ENCODE_VERSION (EOS_SDK_MAJOR_VERSION, EOS_SDK_MINOR_VERSION - 1))
#else
#define EOS_SDK_VERSION_PREV_STABLE (G_ENCODE_VERSION (EOS_SDK_MAJOR_VERSION, EOS_SDK_MINOR_VERSION - 2))
#endif

#ifndef EOS_SDK_VERSION_MIN_REQUIRED
# define EOS_SDK_VERSION_MIN_REQUIRED (EOS_SDK_VERSION_CUR_STABLE)
#endif

#ifndef EOS_SDK_VERSION_MAX_ALLOWED
# if EOS_SDK_VERSION_MIN_REQUIRED > EOS_SDK_VERSION_PREV_STABLE
#  define EOS_SDK_VERSION_MAX_ALLOWED (EOS_SDK_VERSION_MIN_REQUIRED)
# else
#  define EOS_SDK_VERSION_MAX_ALLOWED (EOS_SDK_VERSION_CUR_STABLE)
# endif
#endif

/* sanity checks */
#if EOS_SDK_VERSION_MAX_ALLOWED < EOS_SDK_VERSION_MIN_REQUIRED
#error "EOS_SDK_VERSION_MAX_ALLOWED must be >= EOS_SDK_VERSION_MIN_REQUIRED"
#endif
#if EOS_SDK_VERSION_MIN_REQUIRED < EOS_SDK_VERSION_0_0
#error "EOS_SDK_VERSION_MIN_REQUIRED must be >= EOS_SDK_VERSION_0_0"
#endif

/* Every new stable minor release should add a set of macros here */

#if EOS_SDK_VERSION_MIN_REQUIRED >= EOS_SDK_VERSION_0_0
# define EOS_SDK_DEPRECATED_IN_0_0        EOS_SDK_DEPRECATED
# define EOS_SDK_DEPRECATED_IN_0_0_FOR(f) EOS_SDK_DEPRECATED_FOR(f)
#else
# define EOS_SDK_DEPRECATED_IN_0_0
# define EOS_SDK_DEPRECATED_IN_0_0_FOR(f)
#endif

#if EOS_SDK_VERSION_MAX_ALLOWED < EOS_SDK_VERSION_0_0
# define EOS_SDK_AVAILABLE_IN_0_0 EOS_SDK_UNAVAILABLE(0, 0)
#else
# define EOS_SDK_AVAILABLE_IN_0_0
#endif

#if EOS_SDK_VERSION_MIN_REQUIRED >= EOS_SDK_VERSION_0_2
# define EOS_SDK_DEPRECATED_IN_0_2        EOS_SDK_DEPRECATED
# define EOS_SDK_DEPRECATED_IN_0_2_FOR(f) EOS_SDK_DEPRECATED_FOR(f)
#else
# define EOS_SDK_DEPRECATED_IN_0_2
# define EOS_SDK_DEPRECATED_IN_0_2_FOR(f)
#endif

#if EOS_SDK_VERSION_MAX_ALLOWED < EOS_SDK_VERSION_0_2
# define EOS_SDK_AVAILABLE_IN_0_2 EOS_SDK_UNAVAILABLE(0, 2)
#else
# define EOS_SDK_AVAILABLE_IN_0_2
#endif

#endif /* API_VERSION_H */
