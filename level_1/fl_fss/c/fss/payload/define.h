/**
 * FLL - Level 1
 *
 * Project: FSS
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * This is the fss-000e implementation.
 */
#ifndef _FL_fss_payload_define_h
#define _FL_fss_payload_define_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Defines for f_fss_payload_header_write().
 *
 * macro_f_fss_payload_header_write_handle_error_d:
 *   Handle error return status, calling handle and reset destinations.used.
 *
 *   Parameters:
 *     - destinations: The destinations passed directly from the f_fss_payload_header_write() parameters.
 *     - state:        The state passed directly from the f_fss_payload_header_write() parameters.
 *     - internal:     The internal state, f_fss_payload_header_write_internal_t, created inside of f_fss_payload_header_write().
 *
 * macro_f_fss_payload_header_write_process_signed_numbers_d:
 *   Process the numbers array, converting it to a string.
 *   The data->cache is reset and used (via private_inline_f_payload_header_write_number_signed()).
 *   The destinations->used is incremented on non-error.
 *   This requires private_inline_f_payload_header_write_number_signed() from payload.c.
 *
 *   Parameters:
 *     - data:        The f_fss_payload_header_write_state_t pointer.
 *     - state:       The state passed directly from the f_fss_payload_header_write() parameters.
 *     - internal:    The internal state, f_fss_payload_header_write_internal_t, created inside of f_fss_payload_header_write().
 *     - numbers:     The is.a representing the array of signed numbers.
 *     - destination: The destination string to append to.
 *
 * macro_f_fss_payload_header_write_process_unsigned_numbers_d:
 *   The same as the macro_f_fss_payload_header_write_process_signed_numbers_d() macro documentation above except for unsigned rather than signed.
 *
 * macro_f_fss_payload_header_write_process_dynamic_d:
 *   @todo document this.
 */
#ifndef _di_f_fss_payload_header_write_d_
  #define macro_f_fss_payload_header_write_handle_error_d(destinations, state, internal) \
    if (F_status_is_error(state->status)) { \
      if (state->handle) { \
        state->handle((void * const) state, (void * const) &internal); \
        \
        if (F_status_is_error(state->status)) { \
          destinations->used = internal.original; \
          \
          return; \
        } \
      } \
      else { \
        destinations->used = internal.original; \
        \
        return; \
      } \
    }

  #define macro_f_fss_payload_header_write_process_signed_numbers_d(data, state, internal, numbers, destination) \
    for (internal.j = 0; internal.j < numbers.used; ++internal.j) { \
      \
      if (state->interrupt) { \
        state->interrupt((void * const) state, (void * const) &internal); \
        if (F_status_set_fine(state->status) == F_interrupt) break; \
      } \
      \
      if (private_inline_f_payload_header_write_number_signed(data, state, &internal, (f_number_signed_t) numbers.array[internal.j])) break; \
      \
      if (data->cache->used && internal.j + 1 < numbers.used) { \
        state->status = f_string_dynamic_append(f_fss_extended_open_s, &destination); \
        if (F_status_is_error(state->status)) break; \
      } \
      if (F_status_is_error_not(state->status)) { \
        ++destinations->used; \
      } \
    } // for

  #define macro_f_fss_payload_header_write_process_unsigned_numbers_d(data, state, internal, numbers, destination) \
    for (internal.j = 0; internal.j < numbers.used; ++internal.j) { \
      \
      if (state->interrupt) { \
        state->interrupt((void * const) state, (void * const) &internal); \
        if (F_status_set_fine(state->status) == F_interrupt) break; \
      } \
      \
      if (private_inline_f_payload_header_write_number_unsigned(data, state, &internal, (f_number_unsigned_t) numbers.array[internal.j])) break; \
      \
      if (data->cache->used && internal.j + 1 < numbers.used) { \
        state->status = f_string_dynamic_append(f_fss_extended_open_s, &destination); \
        if (F_status_is_error(state->status)) break; \
      } \
      if (F_status_is_error_not(state->status)) { \
        ++destinations->used; \
      } \
    } // for

  #define macro_f_fss_payload_header_write_process_dynamic_d(data, state, internal, dynamic) \
    if (dynamic.used) { \
      internal.range.start = 0; \
      internal.range.stop = dynamic.used - 1; \
      \
      private_fl_fss_basic_write(F_false, dynamic, 0, &internal.range, data->cache, state, (void * const) &internal); \
    } \
    else { \
      data->cache->string[data->cache->used++] = f_string_ascii_quote_double_s.string[0]; \
      data->cache->string[data->cache->used++] = f_string_ascii_quote_double_s.string[0]; \
    } \
    \
    if (F_status_is_error_not(state->status)) { \
      data->cache->string[data->cache->used++] = f_fss_extended_next_s.string[0]; \
    }
#endif // _di_f_fss_payload_header_write_d_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_fss_payload_define_h
