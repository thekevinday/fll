/**
 * FLL - Level 1
 *
 * Project: FSS
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * This is the fss-000e implementation.
 */
#ifndef _FL_fss_payload_h
#define _FL_fss_payload_h

// Libc includes.
#include <ctype.h>
#include <string.h>

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>
#include <fll/level_0/abstruse.h>
#include <fll/level_0/conversion.h>
#include <fll/level_0/fss.h>

// FLL-1 includes.
#include <fll/level_1/fss.h>

// FLL-1 FSS Payload includes.
#include <fll/level_1/fss/payload/define.h>
#include <fll/level_1/fss/payload/type.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Write standard header of the FSS-000E (Payload).
 *
 * This implementation does not handle the following f_abstruse_*_e:
 *   - none.
 *   - void.
 *   - voids.
 *
 * Any f_abstruse_strings_e must be NULL terminated.
 *
 * For dynamic string data, such as f_abstruse_dynamic_e and f_abstruse_map_e, an empty quoted string is printed if the ".used" is 0.
 *
 * @param headers
 *   An abstruse map representing individual headers.
 *   Ultimately, all headers are cast to a string or a binary representation (depending on implementation).
 * @param destinations
 *   A map of strings representing the header names and values after being safely converted into the valid payload header format.
 *   This built header names and values are appended onto this.
 *
 *   Must not be NULL.
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
 *   The state.handle() is optionally allowed.
 *   There is no "callbacks" structure.
 *   The data is required and set to f_fss_payload_header_state_t.
 *   The data.cache must not be NULL.
 *
 *   The optional state->handle() is called on error and the handler may alter the status to not have an error bit step to prevent returning except for when there is an invalid parameter passed to this function.
 *   The second parameter is a f_fss_payload_header_internal_t.
 *   The second parameter to state->handle() is NULL on invalid paramter passed to this function.
 *
 *   When state.interrupt() returns, only F_interrupt and F_interrupt_not are processed.
 *   Error bit designates an error but must be passed along with F_interrupt.
 *   All other statuses are ignored.
 *   The second parameter is a f_fss_payload_header_internal_t.
 *
 *   Must not be NULL.
 *
 *   This alters state.status:
 *     F_okay on success.
 *     F_data_not if headers is empty (headers.used is 0).
 *
 *     F_interrupt (with error bit) if stopping due to an interrupt.
 *     F_parameter (with error bit) if a parameter is invalid.
 *
 *     Errors (with error bit) from: f_memory_array_increase().
 *     Errors (with error bit) from: f_memory_array_increase_by().
 *     Errors (with error bit) from: f_string_dynamic_append_nulless().
 *     Errors (with error bit) from: f_string_dynamic_strip_null().
 *     Errors (with error bit) from: f_string_dynamic_strip_null_range().
 *
 * @see f_memory_array_increase()
 * @see f_memory_array_increase_by()
 * @see f_string_dynamic_append_nulless()
 * @see f_string_dynamic_strip_null()
 * @see f_string_dynamic_strip_null_range()
 */
#ifndef _di_fl_fss_payload_header_map_
  extern void fl_fss_payload_header_map(const f_abstruse_maps_t headers, f_string_maps_t * const destinations, f_state_t * const state);
#endif // _di_fl_fss_payload_header_map_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_fss_payload_h
