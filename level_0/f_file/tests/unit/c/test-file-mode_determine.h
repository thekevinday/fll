/**
 * FLL - Level 0
 *
 * Project: File
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Test the file project.
 */
#ifndef _TEST__F_file_mode_determine_h
#define _TEST__F_file_mode_determine_h

/**
 * Test that parameter checking works as expected.
 *
 * @see f_file_mode_determine()
 */
extern void test__f_file_mode_determine__parameter_checking(void **state);

/**
 * Test that function works for basic combinations.
 *
 * @see f_file_mode_determine()
 */
extern void test__f_file_mode_determine__works_basic(void **state);

/**
 * Test that function works for basic combinations using replace.
 *
 * @see f_file_mode_determine()
 */
extern void test__f_file_mode_determine__works_basic_replace(void **state);

#endif // _TEST__F_file_mode_determine_h
