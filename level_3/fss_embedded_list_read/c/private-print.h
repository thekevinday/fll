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
 * Print the ignore character for content.
 *
 * This is only used in pipe output mode.
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_fss_embedded_list_read_print_content_ignore_
  extern void fss_embedded_list_read_print_content_ignore(fss_embedded_list_read_main_t * const main) F_attribute_visibility_internal_d;
#endif // _di_fss_embedded_list_read_print_content_ignore_

/**
 * Print the end of an object (which is essentially the start of a content).
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_fss_embedded_list_read_print_object_end_
  extern void fss_embedded_list_read_print_object_end(fss_embedded_list_read_main_t * const main) F_attribute_visibility_internal_d;
#endif // _di_fss_embedded_list_read_print_object_end_

/**
 * Print the end of an object/content set.
 *
 * @param main
 *   The main program data.
 */
#ifndef _di_fss_embedded_list_read_print_set_end_
  extern void fss_embedded_list_read_print_set_end(fss_embedded_list_read_main_t * const main) F_attribute_visibility_internal_d;
#endif // _di_fss_embedded_list_read_print_set_end_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_print_h
