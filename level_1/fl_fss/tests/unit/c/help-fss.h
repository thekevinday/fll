/**
 * FLL - Level 1
 *
 * Project: FSS
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Helper for the fss project tests.
 */
#ifndef _HELP__FL_fss_h
#define _HELP__FL_fss_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Load the content lines from the given file.
 *
 * This first loads the content line total followed by each content line according to that total.
 *
 * The content read is treated each as a single, separate, map value.
 *
 * @param file
 *   The file to use.
 *   Must not be NULL.
 * @param contents
 *   The array of contents to use.
 *   Must not be NULL.
 *
 * @return
 *   F_true if there is no content left to read in the file.
 *   F_false otherwise.
 */
uint8_t help__read_line_contents__single(FILE *file, f_string_dynamics_t * const contents);

/**
 * Load the expect lines from the given file.
 *
 * This first loads the expect line total followed by each expect line according to that total.
 *
 * The expect read is treated each as a single, separate, map value.
 *
 * @param file
 *   The file to use.
 *   Must not be NULL.
 * @param object
 *   The object name to associate with each expected content.
 * @param expects
 *   The array of expects to use.
 *   Must not be NULL.
 *
 * @return
 *   F_true if there is no expect left to read in the file.
 *   F_false otherwise.
 */
uint8_t help__read_line_expects__single(FILE *file, const f_string_static_t object, f_string_maps_t * const expects);

/**
 * Load the object line from the given file.
 *
 * The object line is required to exist in the file.
 *
 * @param file
 *   The file to use.
 *   Must not be NULL.
 * @param object
 *   The string to use.
 *   The used is set to the size of the string read, without the EOL.
 *   Must not be NULL.
 *
 * @return
 *   F_true if there is no object left to read in the file.
 *   F_false otherwise.
 */
uint8_t help__read_line_object(FILE *file, f_string_dynamic_t * const object);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _HELP__FL_fss_h
