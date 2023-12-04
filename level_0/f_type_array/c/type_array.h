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
#ifndef _F_type_array_h
#define _F_type_array_h

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/memory.h>

// FLL-0 type_array includes.
#include <fll/level_0/type_array/common.h>
#include <fll/level_0/type_array/cell.h>
#include <fll/level_0/type_array/fll_id.h>
#include <fll/level_0/type_array/int8.h>
#include <fll/level_0/type_array/int16.h>
#include <fll/level_0/type_array/int32.h>
#include <fll/level_0/type_array/int64.h>
#include <fll/level_0/type_array/int128.h>
#include <fll/level_0/type_array/number_signed.h>
#include <fll/level_0/type_array/number_unsigned.h>
#include <fll/level_0/type_array/range.h>
#include <fll/level_0/type_array/ranges.h>
#include <fll/level_0/type_array/rangess.h>
#include <fll/level_0/type_array/range_double.h>
#include <fll/level_0/type_array/range_doubles.h>
#include <fll/level_0/type_array/range_doubless.h>
#include <fll/level_0/type_array/state.h>
#include <fll/level_0/type_array/status.h>
#include <fll/level_0/type_array/uint8.h>
#include <fll/level_0/type_array/uint16.h>
#include <fll/level_0/type_array/uint32.h>
#include <fll/level_0/type_array/uint64.h>
#include <fll/level_0/type_array/uint128.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_type_array_h
