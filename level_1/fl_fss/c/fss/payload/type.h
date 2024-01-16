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
 * An internal structure for the FSS Payload header functions passed to callbacks.
 *
 * This is intended to be used by functions such as fl_fss_payload_header_map().
 *
 * Properties:
 *   - quote:        The quote being used in all cases.
 *   - step:         The current step.
 *   - i:            A counter used for the "headers" outer arrays.
 *   - j:            A counter used for the inner loop or for pre-allocation counting.
 *   - k:            A number used for converting values but also made available for use as a counter if need be.
 *   - l:            A counter used for more complex use cases such as with multi-maps.
 *   - range:        Used for passing a given string range to the FSS write functions.
 *   - conversion:   The conversion data.
 *   - destinations: The destinations map being appended to.
 *   - original:     The original destination used length.
 */
#ifndef _di_f_fss_payload_header_internal_t_
  typedef struct {
    uint8_t quote;
    uint16_t step;
    f_number_unsigned_t i;
    f_number_unsigned_t j;
    f_number_unsigned_t k;
    f_number_unsigned_t l;
    f_range_t range;
    f_conversion_data_t conversion;

    f_string_maps_t * const destinations;
    const f_number_unsigned_t original;
  } f_fss_payload_header_internal_t;

  #define f_fss_payload_header_internal_t_initialize { \
    0, \
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

  #define macro_f_fss_payload_header_internal_t_initialize_1(quote, step, i, j, k, l, range, conversion, destinations, original) { \
    quote, \
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

  #define macro_f_fss_payload_header_internal_t_initialize_2(destinations, original) { \
    0, \
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
#endif // _di_f_fss_payload_header_internal_t_

/**
 * A state structure for passing data to FSS Payload header functions.
 *
 * This is intended to be used by functions such as fl_fss_payload_header_map().
 *
 * Properties:
 *   - flag:       A set of flags for the function to use.
 *   - conversion: The conversion data.
 *   - cache:      A string cache to use reduce re-allocations on the destination strings (generally required to not be NULL).
 */
#ifndef _di_f_fss_payload_header_state_t_
  typedef struct {
    uint64_t flag;
    f_conversion_data_t conversion;

    f_string_dynamic_t *cache;
  } f_fss_payload_header_state_t;

  #define f_fss_payload_header_state_t_initialize { \
    0, \
    f_conversion_data_base_10_c, \
    0, \
  }

  #define macro_f_fss_payload_header_state_t_initialize_1(flag, conversion, cache) { \
    0, \
    conversion, \
    cache, \
  }

  #define macro_f_fss_payload_header_state_t_initialize_2(flag, cache) { \
    flag, \
    f_conversion_data_base_10_c, \
    cache, \
  }

  #define macro_f_fss_payload_header_state_t_initialize_3(cache) { \
    0, \
    f_conversion_data_base_10_c, \
    cache, \
  }
#endif // _di_f_fss_payload_header_state_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_fss_payload_type_h
