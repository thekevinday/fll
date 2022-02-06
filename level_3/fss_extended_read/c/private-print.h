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
#ifndef _di_fss_extended_read_print_at_
  extern void fss_extended_read_print_at(fll_program_data_t * const main, const f_array_length_t at, const f_fss_delimits_t delimits_object, const f_fss_delimits_t delimits_content, fss_extended_read_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_read_print_at_

/**
 * Print total count at the specified Object/Content position.
 *
 * @param main
 *   The main program data.
 * @param at
 *   The Object/Content position.
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success but nothig was matched (and total was printed).
 *   F_success on success and something was matched (and total was printed).
 */
#ifndef _di_fss_extended_read_print_at_total_
  extern f_status_t fss_extended_read_print_at_total(fll_program_data_t * const main, const f_array_length_t at, fss_extended_read_data_t *data) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_read_print_at_total_

/**
 * Print the end of a Content.
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_fss_extended_read_print_content_end_
  extern void fss_extended_read_print_content_end(fll_program_data_t * const main) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_read_print_content_end_

/**
 * Print the end of an Object (which is essentially the start of Content).
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_fss_extended_read_print_object_end_
  extern void fss_extended_read_print_object_end(fll_program_data_t * const main) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_read_print_object_end_

/**
 * Print the number one and a newline.
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_fss_extended_read_print_one_
  extern void fss_extended_read_print_one(fll_program_data_t * const main) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_read_print_one_

/**
 * Print the end of an Object/Content set.
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_fss_extended_read_print_set_end_
  extern void fss_extended_read_print_set_end(fll_program_data_t * const main) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_read_print_set_end_

/**
 * Print the number zero and a newline.
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_fss_extended_read_print_zero_
  extern void fss_extended_read_print_zero(fll_program_data_t * const main) F_attribute_visibility_internal_d;
#endif // _di_fss_extended_read_print_zero_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_print_h
