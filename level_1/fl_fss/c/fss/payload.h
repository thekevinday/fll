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

#ifdef __cplusplus
extern "C" {
#endif

/**
 * An internal structure for the fss_payload_header_write() passed to callbacks.
 *
 * Properties:
 *   - step:        The current step.
 *   - i:           A counter used for the "headers" and "signatures" outer arrays.
 *   - j:           A counter used for the inner loop or for pre-allocation counting.
 *   - conversion:  The conversion data.
 *   - destination: The destination string being written to.
 *   - original:    The original destination used length.
 */
#ifndef _di_f_fss_payload_header_write_internal_t_
  typedef struct {
    uint16_t step;
    f_number_unsigned_t i;
    f_number_unsigned_t j;
    f_string_range_t range;
    f_conversion_data_t conversion;

    f_string_dynamic_t * const destination;
    const f_number_unsigned_t original;
  } f_fss_payload_header_write_internal_t;

  #define f_fss_payload_header_write_internal_t_initialize { \
    0, \
    0, \
    0, \
    f_string_range_t_initialize, \
    f_conversion_data_base_10_c, \
    0, \
    0, \
  }

  #define macro_f_fss_payload_header_write_internal_t_initialize_1(step, i, j, range, conversion, destination, original) { \
    step, \
    i, \
    j, \
    range, \
    conversion, \
    destination, \
    original, \
  }

  #define macro_f_fss_payload_header_write_internal_t_initialize_2(destination, original) { \
    0, \
    0, \
    0, \
    f_string_range_t_initialize, \
    f_conversion_data_base_10_c, \
    destination, \
    original, \
  }
#endif // _di_f_fss_payload_header_write_internal_t_

/**
 * A state structure for passing data to fss_payload_header_write().
 *
 * Properties:
 *   - conversion: The conversion data.
 *   - cache:      A string cache to use (generally required to be not NULL).
 */
#ifndef _di_f_fss_payload_header_write_state_t_
  typedef struct {
    f_conversion_data_t conversion;

    f_string_dynamic_t *cache;
  } f_fss_payload_header_write_state_t;

  #define f_fss_payload_header_write_state_t_initialize { \
    f_conversion_data_base_10_c, \
    0, \
  }

  #define macro_f_fss_payload_header_write_state_t_initialize_1(conversion, destination) { \
    conversion, \
    destination, \
  }

  #define macro_f_fss_payload_header_write_state_t_initialize_2(destination) { \
    f_conversion_data_base_10_c, \
    destination, \
  }
#endif // _di_f_fss_payload_header_write_state_t_

// @todo fl_fss_payload_header_read() to build an array of f_abstruse for the headers?

/**
 * Write standard header of the FSS-000E (Payload).
 *
 * This implementation does not handle the following f_abstruse_*_e:
 *   - none.
 *   - strings.
 *   - void.
 *   - voids.
 *
 * @param headers
 *   An abstruse map representing individual headers.
 *   Ultimately, all headers are cast to a string or a binary representation (depending on implementation).
 * @param signatures
 *   (optional) An abstruse map representing individual signature headers.
 *   Ultimately, all headers are cast to a string or a binary representation (depending on implementation).
 *   Set to NULL to not use.
 * @param destination
 *   The string in which the resulting header is appended to.
 *   Must not be NULL.
 * @param state
 *   A state for providing flags and handling interrupts during long running operations.
 *   The state.handle() is optionally allowed.
 *   There is no "callbacks" structure.
 *   The data is required and set to f_fss_payload_header_write_state_t.
 *   The data.cache must not be NULL.
 *
 *   The optional state->handle() is called on error and the handler may alter the status to not have an error bit step to prevent returning except for when there is an invalid parameter passed to this function.
 *   The second parameter is a f_fss_payload_header_write_internal_t.
 *   The second parameter to state->handle() is NULL on invalid paramter passed to this function.
 *
 *   When state.interrupt() returns, only F_interrupt and F_interrupt_not are processed.
 *   Error bit designates an error but must be passed along with F_interrupt.
 *   All other statuses are ignored.
 *   The second parameter is a f_fss_payload_header_write_internal_t.
 *
 *   Must not be NULL.
 *
 *   This alters state.status:
 *     F_okay on success.
 *     F_okay_eos on success after reaching the end of the buffer.
 *     F_okay_stop on success after reaching the range stop.
 *     F_data_not if object is empty (object.used is 0).
 *     F_data_not_eos no data to write due start location being greater than or equal to buffer size.
 *     F_data_not_stop no data to write due start location being greater than stop location.
 *
 *     F_interrupt (with error bit) if stopping due to an interrupt.
 *     F_okay_eol (with error bit) after reaching an EOL, which is not supported by the standard.
 *     F_parameter (with error bit) if a parameter is invalid.
 *
 *     Errors (with error bit) from: f_memory_array_increase().
 *     Errors (with error bit) from: f_memory_array_increase_by().
 *
 * @see f_memory_array_increase()
 * @see f_memory_array_increase_by()
 */
#ifndef _di_fl_fss_payload_header_write_
  extern void fl_fss_payload_header_write(const f_abstruse_maps_t headers, const f_abstruse_maps_t * const signatures, f_string_dynamic_t * const destination, f_state_t * const state);
#endif // _di_fl_fss_payload_header_write_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_fss_payload_h
