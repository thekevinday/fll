/**
 * FLL - Level 0
 *
 * Project: String
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines quantity string data.
 *
 * This is auto-included by string.h and should not need to be explicitly included.
 */
#ifndef _F_string_quantitys_h
#define _F_string_quantitys_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * An array of string quantitys.
 *
 * Properties:
 *   - array: The array of string quantitys.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_string_quantitys_t_
  typedef struct {
    f_string_quantity_t *array;

    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_string_quantitys_t;

  #define f_string_quantitys_t_initialize { 0, 0, 0 }

  #define macro_f_string_quantitys_t_initialize_1(array, size, used) { array, size, used }
  #define macro_f_string_quantitys_t_initialize_2(array, length) { array, length, length }

  #define macro_f_string_quantitys_t_clear(quantitys) \
    quantitys.array = 0; \
    quantitys.size = 0; \
    quantitys.used = 0;
#endif // _di_f_string_quantitys_t_

/**
 * Append the single source quantity onto the destination.
 *
 * @param source
 *   The source quantity to append.
 * @param destination
 *   The destination quantitys the source is appended onto.
 *
 * @return
 *   F_okay on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_quantitys_append_
  extern f_status_t f_string_quantitys_append(const f_string_quantity_t source, f_string_quantitys_t * const destination);
#endif // _di_f_string_quantitys_append_

/**
 * Append the source quantitys onto the destination.
 *
 * @param source
 *   The source quantitys to append.
 * @param destination
 *   The destination quantitys the source is appended onto.
 *
 * @return
 *   F_okay on success.
 *   F_data_not on success, but there is nothing to append (size == 0).
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_resize().
 */
#ifndef _di_f_string_quantitys_append_all_
  extern f_status_t f_string_quantitys_append_all(const f_string_quantitys_t source, f_string_quantitys_t * const destination);
#endif // _di_f_string_quantitys_append_all_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_string_quantitys_h
