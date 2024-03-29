/**
 * FLL - Level 3
 *
 * Project: FSS
 * API Version: 0.6
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
 * @param is_payload
 *   If TRUE, then this is associated with a "payload" Object.
 * @param at
 *   The index in the Objects and Contents to print.
 * @param delimits_object
 *   The delimits to be applied to an Object.
 * @param delimits_content
 *   The delimits to be applied to Content.
 * @param data
 *   The program data.
 */
#ifndef _di_fss_payload_read_print_at_
  extern void fss_payload_read_print_at(fll_program_data_t * const main, const bool is_payload, const f_array_length_t at, const f_fss_delimits_t delimits_object, const f_fss_delimits_t delimits_content, fss_payload_read_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_fss_payload_read_print_at_

/**
 * Print the Object and Content at the given position for the FSS-0001 Extended Content at depth 1.
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
#ifndef _di_fss_payload_read_print_at_extended_
  extern void fss_payload_read_print_at_extended(fll_program_data_t * const main, const f_array_length_t at, const f_fss_delimits_t delimits_object, const f_fss_delimits_t delimits_content, fss_payload_read_data_t * const data) F_attribute_visibility_internal_d;
#endif // _di_fss_payload_read_print_at_extended_

/**
 * Explicitly print the Object at the given position.
 *
 * @param main
 *   The main program data.
 * @param data
 *   The program data.
 * @param at
 *   The index in the Objects and Contents to print.
 * @param delimits_object
 *   The delimits to be applied to an Object.
 */
#ifndef _di_fss_payload_read_print_at_object_
  extern void fss_payload_read_print_at_object(fll_program_data_t * const main, fss_payload_read_data_t * const data, const f_array_length_t at, const f_fss_delimits_t delimits_object) F_attribute_visibility_internal_d;
#endif // _di_fss_payload_read_print_at_object_

/**
 * Print total count at the specified Object/Content position for the FSS-0001 Extended Content at depth 1.
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
#ifndef _di_fss_payload_read_print_at_total_extended_
  extern f_status_t fss_payload_read_print_at_total_extended(fll_program_data_t * const main, const f_array_length_t at, fss_payload_read_data_t *data) F_attribute_visibility_internal_d;
#endif // _di_fss_payload_read_print_at_total_extended_

/**
 * Print the end of a Content for the FSS-0001 Extended Content at depth 1.
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_fss_payload_read_print_content_end_extended_
  extern void fss_payload_read_print_content_end_extended(fll_program_data_t * const main) F_attribute_visibility_internal_d;
#endif // _di_fss_payload_read_print_content_end_extended_

/**
 * Print the ignore character for Content.
 *
 * This is only used in pipe output mode.
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_fss_payload_read_print_content_ignore_
  extern void fss_payload_read_print_content_ignore(fll_program_data_t * const main) F_attribute_visibility_internal_d;
#endif // _di_fss_payload_read_print_content_ignore_

/**
 * Print the end of an Object (which is essentially the start of Content).
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_fss_payload_read_print_object_end_
  extern void fss_payload_read_print_object_end(fll_program_data_t * const main) F_attribute_visibility_internal_d;
#endif // _di_fss_payload_read_print_object_end_

/**
 * Print the end of an Object (which is essentially the start of Content) for the FSS-0001 Extended Content at depth 1.
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_fss_payload_read_print_object_end_extended_
  extern void fss_payload_read_print_object_end_extended(fll_program_data_t * const main) F_attribute_visibility_internal_d;
#endif // _di_fss_payload_read_print_object_end_extended_

/**
 * Print the number one and a newline.
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_fss_payload_read_print_one_
  extern void fss_payload_read_print_one(fll_program_data_t * const main) F_attribute_visibility_internal_d;
#endif // _di_fss_payload_read_print_one_

/**
 * Print the end of an Object/Content set.
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_fss_payload_read_print_set_end_
  extern void fss_payload_read_print_set_end(fll_program_data_t * const main) F_attribute_visibility_internal_d;
#endif // _di_fss_payload_read_print_set_end_

/**
 * Print the end of an Object/Content set for the FSS-0001 Extended Content at depth 1.
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_fss_payload_read_print_set_end_extended_
  extern void fss_payload_read_print_set_end_extended(fll_program_data_t * const main) F_attribute_visibility_internal_d;
#endif // _di_fss_payload_read_print_set_end_extended_

/**
 * Print the number zero and a newline.
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_fss_payload_read_print_zero_
  extern void fss_payload_read_print_zero(fll_program_data_t * const main) F_attribute_visibility_internal_d;
#endif // _di_fss_payload_read_print_zero_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_print_h
