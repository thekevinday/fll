/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides path generate functionality.
 *
 * This is auto-included and should not need to be explicitly included.
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
 *   This alters data.main->setting.state.status:
 *     F_none on success.
 *
 *     Errors (with error bit) from: f_string_dynamic_append_nulless().
 *     Errors (with error bit) from: fake_path_generate_string_dynamic().
 *
 * @see f_string_dynamic_append_nulless()
 *
 * @see fake_path_generate_string_dynamic()
 */
#ifndef _di_fake_path_generate_
  extern void fake_path_generate(fake_data_t * const data);
#endif // _di_fake_path_generate_

/**
 * Generate all appropriate paths based on runtime information from dynamic strings.
 *
 * The given source is applied to each destination.
 *
 * @param data
 *   The program data.
 *
 *   This alters data.main->setting.state.status:
 *     F_none on success.
 *
 *     Errors (with error bit) from: f_string_dynamic_append_nulless().
 *
 * @param source
 *   The string to copy from.
 * @param destination
 *   An array of pointers to the strings to append onto.
 * @param length
 *   The size of the values.
 *
 * @see f_string_dynamic_append_nulless()
 */
#ifndef _di_fake_path_generate_string_dynamic_
  extern void fake_path_generate_string_dynamic(fake_data_t * const data, const f_string_dynamic_t source, f_string_dynamic_t *destination[], const uint8_t size);
#endif // _di_fake_path_generate_string_dynamic_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_fake_path_generate_h
