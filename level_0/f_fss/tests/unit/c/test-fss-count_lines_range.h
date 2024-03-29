/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Test count lines range in the fss project.
 */
#ifndef _TEST__F_fss__count_lines_range
#define _TEST__F_fss__count_lines_range

/**
 * Test that the function correctly fails on invalid parameter.
 *
 * @see f_fss_count_lines_range()
 */
extern void test__f_fss_count_lines_range__parameter_checking(void **state);

/**
 * Test that the function returns F_data_not.
 *
 * @see f_fss_count_lines_range()
 */
extern void test__f_fss_count_lines_range__returns_data_not(void **state);

/**
 * Test that the function works.
 *
 * @see f_fss_count_lines_range()
 */
extern void test__f_fss_count_lines_range__works(void **state);

#endif // _TEST__F_fss__count_lines_range
