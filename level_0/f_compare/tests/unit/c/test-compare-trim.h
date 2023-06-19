/**
 * FLL - Level 0
 *
 * Project: Compare
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the compare project.
 */
#ifndef _TEST__F_compare_trim_h
#define _TEST__F_compare_trim_h

// f_compare_trim() only returns memory failures.

/**
 * Test that function trims.
 *
 * @see f_compare_trim()
 */
extern void test__f_compare_trim__trims(void **state);

/**
 * Test that function doesn't match empty string to a non-empty string.
 *
 * @see f_compare_trim()
 */
extern void test__f_compare_trim__something_misses_nothing(void **state);

/**
 * Test that function works.
 *
 * @see f_compare_trim()
 */
extern void test__f_compare_trim__works(void **state);

#endif // _TEST__F_compare_trim_h