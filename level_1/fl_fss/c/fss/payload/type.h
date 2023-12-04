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
 *   - step:         The current step.
 *   - i:            A counter used for the "headers" outer arrays.
 *   - j:            A counter used for the inner loop or for pre-allocation counting.
 *   - k:            A number used for converting values but also made available for use as a counter if need be.
 *   - l:            @todo
 *   - range:        @todo
 *   - conversion:   The conversion data.
 *   - destinations: The destinations map being appended to.
 *   - original:     The original destination used length.
 */
#ifndef _di_f_fss_payload_header_write_internal_t_
  typedef struct {
    uint16_t step;
    f_number_unsigned_t i;
    f_number_unsigned_t j;
    f_number_unsigned_t k;
    f_number_unsigned_t l;
    f_range_t range;
    f_conversion_data_t conversion;

    f_string_maps_t * const destinations;
    const f_number_unsigned_t original;
  } f_fss_payload_header_write_internal_t;

  #define f_fss_payload_header_write_internal_t_initialize { \
    0, \
    0, \
    0, \
    0, \
    0, \
    f_range_t_initialize, \
    f_conversion_data_base_10_c, \
    0, \
    0, \
  }

  #define macro_f_fss_payload_header_write_internal_t_initialize_1(step, i, j, k, l, range, conversion, destinations, original) { \
    step, \
    i, \
    j, \
    k, \
    l, \
    range, \
    conversion, \
    destinations, \
    original, \
  }

  #define macro_f_fss_payload_header_write_internal_t_initialize_2(destinations, original) { \
    0, \
    0, \
    0, \
    0, \
    0, \
    f_range_t_initialize, \
    f_conversion_data_base_10_c, \
    destinations, \
    original, \
  }
#endif // _di_f_fss_payload_header_write_internal_t_

/**
 * A state structure for passing data to fss_payload_header_write().
 *
 * Properties:
 *   - conversion: The conversion data.
 *   - cache:      A string cache to use reduce re-allocations on the destination strings (generally required to not be NULL).
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

  #define macro_f_fss_payload_header_write_state_t_initialize_1(conversion, cache) { \
    conversion, \
    cache, \
  }

  #define macro_f_fss_payload_header_write_state_t_initialize_2(cache) { \
    f_conversion_data_base_10_c, \
    cache, \
  }
#endif // _di_f_fss_payload_header_write_state_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_fss_payload_type_h
