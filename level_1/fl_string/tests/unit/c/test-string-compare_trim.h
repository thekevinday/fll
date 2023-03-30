/**
 * FLL - Level 1
 *
 * Project: String
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the string project.
 */
#ifndef _TEST__FL_string_compare_trim_h
#define _TEST__FL_string_compare_trim_h

// fl_string_compare_trim() only returns memory failures.

/**
 * Test that function trims.
 *
 * @see fl_string_compare_trim()
 */
extern void test__fl_string_compare_trim__trims(void **state);

/**
 * Test that function doesn't match empty string to a non-empty string.
 *
 * @see fl_string_compare_trim()
 */
extern void test__fl_string_compare_trim__something_misses_nothing(void **state);

/**
 * Test that function works.
 *
 * @see fl_string_compare_trim()
 */
extern void test__fl_string_compare_trim__works(void **state);

#endif // _TEST__FL_string_compare_trim_h
