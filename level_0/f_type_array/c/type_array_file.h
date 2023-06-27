/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides an extension to the Type project (f_type) that depends on f_memory (linking to the f_memory library).
 *
 * As an exceptional case, this is an extension to f_type to avoid circular dependency issues with f_memory.
 * The functions and macros in this project therefore are prefixed with 'f_type_' instead of 'f_type_array_'.
 */
#ifndef _F_type_array_file_h
#define _F_type_array_file_h

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/type_file.h>
#include <fll/level_0/memory.h>

// FLL-0 type_array includes.
#include <fll/level_0/type_array/file.h>
#include <fll/level_0/type_array/poll.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_array_file_h
