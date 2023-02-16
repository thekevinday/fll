/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _fake_fake_path_generate_h
#define _fake_fake_path_generate_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Generate all appropriate paths based on runtime information.
 *
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_path_generate_
  extern f_status_t fake_path_generate(fake_data_t * const data);
#endif // _di_fake_path_generate_

/**
 * Generate all appropriate paths based on runtime information from dynamic strings.
 *
 * The given source is applied to each destination.
 *
 * @param daa
 *   The program data.
 * @param source
 *   The string to copy from.
 * @param destination
 *   An array of pointers to the strings to append onto.
 * @param length
 *   The size of the values.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_path_generate_string_dynamic_
  extern f_status_t fake_path_generate_string_dynamic(fake_data_t * const data, const f_string_dynamic_t source, f_string_dynamic_t *destination[], const uint8_t size);
#endif // _di_fake_path_generate_string_dynamic_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_fake_path_generate_h
