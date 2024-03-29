/**
 * FLL - Level 1
 *
 * Project: Conversion
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Defines common data to be used for/by project conversion.
 *
 * This is auto-included by conversion.h and should not need to be explicitly included.
 */
#ifndef _FL_conversion_common_h
#define _FL_conversion_common_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Provide a structure for customizing conversion settings for a conversion function to use.
 *
 * base: The base unit the number is to be represented as, only the numbers 2 through 16 are supported as a base.
 * flag: Store flags from fl_conversion_data_flag_*.
 */
#ifndef _di_fl_conversion_data_t_
  typedef struct {
    uint8_t base;
    uint16_t flag;
  } fl_conversion_data_t;

  #define fl_conversion_data_t_initialize { 10, 0 }

  #define macro_fl_conversion_data_t_initialize(base, flag) { base, flag }

  #define macro_fl_conversion_data_t_clear(data) \
    data.base = 0; \
    data.flag = 0;
#endif // _di_fl_conversion_data_t_

/**
 * The defines for conversion data.
 *
 * fl_conversion_data_*:
 *   - base_2:        Basic base-2 conversion structure.
 *   - base_8:        Basic base-8 conversion structure.
 *   - base_10:       Basic base-10 conversion structure.
 *   - base_12:       Basic base-12 conversion structure.
 *   - base_16:       Basic base-16 conversion structure.
 *   - endian_big:    Basic base-10 conversion with big-endian flag.
 *   - endian_little: Basic base-10 conversion with little-endian flag.
 *   - shift_left:    Basic base-10 conversion with shift left flag.
 */
#ifndef _di_fl_conversion_data_t_defines_
  extern const fl_conversion_data_t fl_conversion_data_base_2_c;
  extern const fl_conversion_data_t fl_conversion_data_base_8_c;
  extern const fl_conversion_data_t fl_conversion_data_base_10_c;
  extern const fl_conversion_data_t fl_conversion_data_base_12_c;
  extern const fl_conversion_data_t fl_conversion_data_base_16_c;
  extern const fl_conversion_data_t fl_conversion_data_endian_big_c;
  extern const fl_conversion_data_t fl_conversion_data_endian_little_c;
  extern const fl_conversion_data_t fl_conversion_data_shift_left_c;
#endif // _di_fl_conversion_data_t_defines_

/**
 * Define flags used by fl_conversion_data_t.
 *
 * fl_conversion_data_flag_*:
 *   - endian_big:    Use big-endian rather than host byte order or little-endian when converting.
 *   - endian_little: Use little-endian rather than host byte order or big-endian when converting.
 *   - negative:      Treat the string as a negative number.
 */
#ifndef _di_fl_conversion_data_flag_
  #define FL_conversion_data_flag_endian_big_d    0x1
  #define FL_conversion_data_flag_endian_little_d 0x2
  #define FL_conversion_data_flag_negative_d      0x4
#endif // _di_fl_conversion_data_flag_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FL_conversion_common_h
