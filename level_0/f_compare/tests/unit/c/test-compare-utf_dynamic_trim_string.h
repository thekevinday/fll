/**
 * FLL - Level 0
 *
 * Project: Compare
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the compare project.
 */
#ifndef _TEST__F_compare_utf_dynamic_trim_string_h
#define _TEST__F_compare_utf_dynamic_trim_string_h

// f_compare_utf_dynamic_trim_string() only returns memory failures.

/**
 * Test that function trims.
 *
 * @see f_compare_utf_dynamic_trim_string()
 */
extern void test__f_compare_utf_dynamic_trim_string__trims(void **state);

/**
 * Test that function doesn't match empty string to a non-empty string.
 *
 * @see f_compare_utf_dynamic_trim_string()
 */
extern void test__f_compare_utf_dynamic_trim_string__something_misses_nothing(void **state);

/**
 * Test that function works.
 *
 * @see f_compare_utf_dynamic_trim_string()
 */
extern void test__f_compare_utf_dynamic_trim_string__works(void **state);

#endif // _TEST__F_compare_utf_dynamic_trim_string_h
