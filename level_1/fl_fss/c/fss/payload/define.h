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
 *   Handle error return status, calling handle and reset destination.used.
 *
 *   Parameters:
 *     - destination: The destination passed directly from the f_fss_payload_header_write() parameters.
 *     - state:       The state passed directly from the f_fss_payload_header_write() parameters.
 *     - internal:    The internal state, f_fss_payload_header_write_internal_t, created inside of f_fss_payload_header_write().
 *
 * macro_f_fss_payload_header_write_process_signed_numbers_d:
 *   Process the numbers array, converting it to a string.
 *   The data->cache_1 is appended to.
 *   The data->cache_2 is reset and used.
 *   This requires private_inline_f_payload_header_write_number_signed() from payload.c.
 *
 *   Parameters:
 *     - data:       The f_fss_payload_header_write_state_t pointer. The data->cache_2.used is set to 0 and then appended onto. The resulting data->cache_2 is then appended onto data->cache_1 on success.
 *     - state:      The state passed directly from the f_fss_payload_header_write() parameters.
 *     - internal:   The internal state, f_fss_payload_header_write_internal_t, created inside of f_fss_payload_header_write().
 *     - numbers:    The is.a representing the array of signed numbers.
 *     - signatures: (optional) An array whose indexes must match each index in the headers, where each value if set to F_true will result in the generation of a signature. Set to NULL to not use.
 *
 * macro_f_fss_payload_header_write_process_unsigned_numbers_d:
 *   The same as the macro_f_fss_payload_header_write_process_signed_numbers_d() macro documentation above except for unsigned rather than signed.
 */
#ifndef _di_f_fss_payload_header_write_d_
  #define macro_f_fss_payload_header_write_handle_error_d(destination, state, internal) \
    if (F_status_is_error(state->status)) { \
      if (state->handle) { \
        state->handle((void * const) state, (void * const) &internal); \
        \
        if (F_status_is_error(state->status)) { \
          destination->used = internal.original; \
          \
          return; \
        } \
      } \
      else { \
        destination->used = internal.original; \
        \
        return; \
      } \
    }

  #define macro_f_fss_payload_header_write_process_signed_numbers_d(data, state, internal, numbers, signatures) \
    data->cache_2->used = 0; \
    \
    for (internal.j = 0; internal.j < numbers.used; ++internal.j) { \
      \
      if (state->interrupt) { \
        state->interrupt((void * const) state, (void * const) &internal); \
        if (F_status_set_fine(state->status) == F_interrupt) break; \
      } \
      \
      if (private_inline_f_payload_header_write_number_signed(data, state, &internal, (f_number_signed_t) numbers.array[internal.j])) break; \
      \
      if (internal.j + 1 < numbers.used) { \
        state->status = f_string_dynamic_append(f_fss_extended_open_s, data->cache_2); \
        if (F_status_is_error(state->status)) break; \
      } \
    } /* for */ \
    \
    if (F_status_is_error_not(state->status) && signatures && signatures->array[internal.i]) { \
      /* @todo build signature (against data->cache_2), use a callback for this so that the caller can provide an appropriate algorithm. */ \
    } \
    \
    if (F_status_is_error_not(state->status) && data->cache_2->used) { \
      state->status = f_string_dynamic_append(*data->cache_2, data->cache_1); \
    }

  #define macro_f_fss_payload_header_write_process_unsigned_numbers_d(data, state, internal, numbers, signatures) \
    data->cache_2->used = 0; \
    \
    for (internal.j = 0; internal.j < numbers.used; ++internal.j) { \
      \
      if (state->interrupt) { \
        state->interrupt((void * const) state, (void * const) &internal); \
        if (F_status_set_fine(state->status) == F_interrupt) break; \
      } \
      \
      if (private_inline_f_payload_header_write_number_unsigned(data, state, &internal, (f_number_unsigned_t) numbers.array[internal.j])) break; \
      \
      if (internal.j + 1 < numbers.used) { \
        state->status = f_string_dynamic_append(f_fss_extended_open_s, data->cache_2); \
        if (F_status_is_error(state->status)) break; \
      } \
    } /* for */ \
    \
    if (F_status_is_error_not(state->status) && signatures && signatures->array[internal.i]) { \
      /* @todo build signature (against data->cache_2), use a callback for this so that the caller can provide an appropriate algorithm. */ \
    } \
    \
    if (F_status_is_error_not(state->status) && data->cache_2->used) { \
      state->status = f_string_dynamic_append(*data->cache_2, data->cache_1); \
    }

  #define macro_f_fss_payload_header_write_process_dynamic_d(data, state, internal, dynamic) \
    if (dynamic.used) { \
      internal.range.start = 0; \
      internal.range.stop = dynamic.used - 1; \
      \
      private_fl_fss_basic_write(F_false, dynamic, 0, &internal.range, data->cache_2, state, (void * const) &internal); \
    } \
    else { \
      data->cache_2->string[data->cache_2->used++] = f_string_ascii_quote_double_s.string[0]; \
      data->cache_2->string[data->cache_2->used++] = f_string_ascii_quote_double_s.string[0]; \
    } \
    \
    data->cache_2->string[data->cache_2->used++] = f_fss_extended_open_s.string[0];
#endif // _di_f_fss_payload_header_write_d_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_fss_payload_define_h
