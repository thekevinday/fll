/**
 * FLL - Level 3
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_print_h
#define _PRIVATE_print_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Print the Object and Content at the given position.
 *
 * Only what is requested to print (Object, Content, both, or neither) will be printed, if there is something to print.
 *
 * @param main
 *   The main program data.
 * @param at
 *   The index in the Objects and Contents to print.
 * @param delimits_object
 *   The delimits to be applied to an Object.
 * @param delimits_content
 *   The delimits to be applied to Content.
 * @param data
 *   The program data.
 */
#ifndef _di_fss_basic_read_print_at_
  extern void fss_basic_read_print_at(fss_basic_read_main_t * const main, const f_array_length_t at, const f_fss_delimits_t delimits_object, const f_fss_delimits_t delimits_content, fss_basic_read_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_fss_basic_read_print_at_

/**
 * Print the end of an Object (which is essentially the start of Content).
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_fss_basic_read_print_object_end_
  extern void fss_basic_read_print_object_end(fss_basic_read_main_t * const main) F_attribute_visibility_internal_d;
#endif // _di_fss_basic_read_print_object_end_

/**
 * Print the number one and a newline.
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_fss_basic_read_print_one_
  extern void fss_basic_read_print_one(fss_basic_read_main_t * const main) F_attribute_visibility_internal_d;
#endif // _di_fss_basic_read_print_one_

/**
 * Print the end of an Object/Content set.
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_fss_basic_read_print_set_end_
  extern void fss_basic_read_print_set_end(fss_basic_read_main_t * const main) F_attribute_visibility_internal_d;
#endif // _di_fss_basic_read_print_set_end_

/**
 * Print the number zero and a newline.
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_fss_basic_read_print_zero_
  extern void fss_basic_read_print_zero(fss_basic_read_main_t * const main) F_attribute_visibility_internal_d;
#endif // _di_fss_basic_read_print_zero_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_print_h
