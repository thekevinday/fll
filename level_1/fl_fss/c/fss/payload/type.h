/**
 * FLL - Level 1
 *
 * Project: FSS
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * This is the fss-000e implementation.
 */
#ifndef _FL_fss_payload_type_h
#define _FL_fss_payload_type_h

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
 *   - k:           A number used for converting values but also made available for use as a counter if need be.
 *   - conversion:  The conversion data.
 *   - destination: The destination string being written to.
 *   - original:    The original destination used length.
 */
#ifndef _di_f_fss_payload_header_write_internal_t_
  typedef struct {
    uint16_t step;
    f_number_unsigned_t i;
    f_number_unsigned_t j;
    f_number_unsigned_t k;
    f_string_range_t range;
    f_conversion_data_t conversion;

    f_string_dynamic_t * const destination;
    const f_number_unsigned_t original;
  } f_fss_payload_header_write_internal_t;

  #define f_fss_payload_header_write_internal_t_initialize { \
    0, \
    0, \
    0, \
    0, \
    f_string_range_t_initialize, \
    f_conversion_data_base_10_c, \
    0, \
    0, \
  }

  #define macro_f_fss_payload_header_write_internal_t_initialize_1(step, i, j, k, range, conversion, destination, original) { \
    step, \
    i, \
    j, \
    k, \
    range, \
    conversion, \
    destination, \
    original, \
  }

  #define macro_f_fss_payload_header_write_internal_t_initialize_2(destination, original) { \
    0, \
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
 *   - cache_1:    A string cache to use for building a complete header line (generally required to be not NULL).
 *   - cache_2:    A string cache to use for building small individual strings (generally required to be not NULL).
 *   - cache_3:    A string cache to use for building a complete signature of each header (generally required to be not NULL).
 */
#ifndef _di_f_fss_payload_header_write_state_t_
  typedef struct {
    f_conversion_data_t conversion;

    f_string_dynamic_t *cache_1;
    f_string_dynamic_t *cache_2;
    f_string_dynamic_t *cache_3;
  } f_fss_payload_header_write_state_t;

  #define f_fss_payload_header_write_state_t_initialize { \
    f_conversion_data_base_10_c, \
    0, \
    0, \
    0, \
  }

  #define macro_f_fss_payload_header_write_state_t_initialize_1(conversion, cache_1, cache_2, cache_3) { \
    conversion, \
    cache_1, \
    cache_2, \
    cache_3, \
  }

  #define macro_f_fss_payload_header_write_state_t_initialize_2(cache_1, cache_2, cache_3) { \
    f_conversion_data_base_10_c, \
    cache_1, \
    cache_2, \
    cache_3, \
  }
#endif // _di_f_fss_payload_header_write_state_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_fss_payload_type_h
