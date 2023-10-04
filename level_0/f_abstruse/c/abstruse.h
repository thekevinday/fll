/**
 * FLL - Level 0
 *
 * Project: Abstruse
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides abstruse type definitions.
 *
 * An abstruse type is intended to act as a variable that can be passed and then later cast to the appropriate type.
 * This produces behavior similar to an object-oriented design in a non-object-oriented language like C.
 *
 * This is not intended to handle all possible types but instead handle a set of common and core FLL types.
 */
#ifndef _F_abstruse_h
#define _F_abstruse_h

// Include pre-requirements.
#ifndef _GNU_SOURCE
  #define _GNU_SOURCE
#endif // _GNU_SOURCE

// Libc includes.
#include <stdbool.h>
#include <stdint.h>
#include <sys/stat.h>
#include <unistd.h>

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/type_array.h>
#include <fll/level_0/string.h>

// FLL-0 type includes.
#include <fll/level_0/abstruse/enum.h>
#include <fll/level_0/abstruse/type.h>
#include <fll/level_0/abstruse/abstruse.h>
#include <fll/level_0/abstruse/map.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_abstruse_h
