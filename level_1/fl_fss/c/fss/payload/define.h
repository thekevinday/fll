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
 * Defines for fl_fss_payload_header_map().
 *
 * macro_f_fss_payload_header_write_handle_error_d:
 *   Handle error return status, calling handle and reset destinations.used.
 *
 *   Parameters:
 *     - destinations: The destinations passed directly from the fl_fss_payload_header_map() parameters.
 *     - state:        The state passed directly from the fl_fss_payload_header_map() parameters.
 *     - internal:     The internal state, f_fss_payload_header_internal_t, created inside of fl_fss_payload_header_map().
 *
 * macro_f_fss_payload_header_write_process_numbers_d:
 *   Process the numbers array (either signed or unsigned), converting it to a string.
 *   The data->cache is reset and used (via private_fl_payload_header_map_number_signed()).
 *   The destinations->used is incremented on non-error.
 *   This requires private_fl_payload_header_map_number_signed() from payload.c.
 *
 *   Parameters:
 *     - data:        The f_fss_payload_header_state_t pointer.
 *     - state:       The state passed directly from the fl_fss_payload_header_map() parameters.
 *     - internal:    The internal state, f_fss_payload_header_internal_t, created inside of fl_fss_payload_header_map().
 *     - numbers:     The is.a representing the array of signed numbers.
 *     - destination: The destination string to append to.
 *     - function:    The private signed/unsigned function to call.
 *     - cast:        The signed/unsigned structure to cast to.
 *
 * macro_f_fss_payload_header_write_process_numbers_signed_d:
 *   This wraps macro_f_fss_payload_header_write_process_numbers_d, passing the signed function and cast.
 *
 * macro_f_fss_payload_header_write_process_numbers_unsigned_d:
 *   This wraps macro_f_fss_payload_header_write_process_numbers_d, passing the unsigned function and cast.
 *
 * macro_f_fss_payload_header_write_process_dynamic_d:
 *   This macro writes the given dynamic string into the cache.
 *   If the dynamic string is empty, then an empty quotes are written to the cache.
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

  #define macro_f_fss_payload_header_write_process_numbers_d(data, state, internal, numbers, destination, function, cast) \
    data->cache->used = 0; \
    \
    for (internal.j = 0; internal.j < numbers.used; ++internal.j) { \
      \
      if (state->interrupt) { \
        state->interrupt((void * const) state, (void * const) &internal); \
        if (F_status_set_fine(state->status) == F_interrupt) break; \
      } \
      \
      if (!(data->flag & f_fss_payload_header_map_flag_join_digits_e)) { \
        data->cache->used = 0; \
      } \
      \
      if (function(data, state, &internal, (cast) numbers.array[internal.j])) { \
        data->cache->used = 0; \
        \
        break; \
      } \
      \
      if (!(data->flag & f_fss_payload_header_map_flag_join_digits_e)) { \
        if (data->cache->used && internal.j + 1 < numbers.used) { \
          state->status = f_string_dynamic_append(f_fss_extended_open_s, &destination); \
          if (F_status_is_error(state->status)) break; \
        } \
        \
        ++destinations->used; \
      } \
    } /* for */ \
    \
    if (data->cache->used && (data->flag & f_fss_payload_header_map_flag_join_digits_e)) { \
      private_fl_payload_header_map_cache_write(data, state, &internal); \
      \
      if (F_status_is_error_not(state->status)) { \
        ++destinations->used; \
      } \
    }

  #define macro_f_fss_payload_header_write_process_numbers_signed_d(data, state, internal, numbers, destination) \
    macro_f_fss_payload_header_write_process_numbers_d(data, state, internal, numbers, destination, private_fl_payload_header_map_number_signed, f_number_signed_t)

  #define macro_f_fss_payload_header_write_process_numbers_unsigned_d(data, state, internal, numbers, destination) \
    macro_f_fss_payload_header_write_process_numbers_d(data, state, internal, numbers, destination, private_fl_payload_header_map_number_unsigned, f_number_unsigned_t)

  #define macro_f_fss_payload_header_write_process_dynamic_d(data, state, internal, dynamic) \
    if (dynamic.used || (data->flag & f_fss_payload_header_map_flag_null_dynamic_e)) { \
      if (dynamic.used) { \
        internal.range.start = 0; \
        internal.range.stop = dynamic.used - 1; \
        \
        private_fl_fss_basic_write(F_false, dynamic, internal.quote, &internal.range, data->cache, state, (void * const) &internal); \
      } \
      else { \
        state->status = f_string_dynamic_append(internal.quote_null, data->cache); \
      } \
      \
      if (F_status_is_error_not(state->status)) { \
        data->cache->string[data->cache->used++] = f_fss_extended_next_s.string[0]; \
      } \
    }
#endif // _di_f_fss_payload_header_write_d_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_fss_payload_define_h
