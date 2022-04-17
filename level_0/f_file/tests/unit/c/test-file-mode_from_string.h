/**
 * FLL - Level 0
 *
 * Project: File
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the file project.
 */
#ifndef _TEST__F_file_mode_from_string_h
#define _TEST__F_file_mode_from_string_h

/**
 * Test that function fails for basic strings.
 *
 * @see f_file_mode_from_string()
 */
extern void test__f_file_mode_from_string__fails_basic(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_file_mode_from_string()
 */
#ifndef _di_level_0_parameter_checking_
  extern void test__f_file_mode_from_string__parameter_checking(void **state);
#endif // _di_level_0_parameter_checking_

/**
 * Test that function works but the path is empty.
 *
 * @see f_file_mode_from_string()
 */
extern void test__f_file_mode_from_string__returns_data_not(void **state);

/**
 * Test that function works for basic codes using alphabetic characters.
 *
 * @see f_file_mode_from_string()
 */
extern void test__f_file_mode_from_string__works_basic_alphabet(void **state);

/**
 * Test that function works for basic codes using digit characters.
 *
 * @see f_file_mode_from_string()
 */
extern void test__f_file_mode_from_string__works_basic_digit(void **state);

#endif // _TEST__F_file_mode_from_string_h
