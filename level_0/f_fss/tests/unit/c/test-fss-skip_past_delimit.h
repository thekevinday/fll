/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test skip past delimit in the fss project.
 */
#ifndef _TEST__F_fss__skip_past_delimit
#define _TEST__F_fss__skip_past_delimit

/**
 * Test that the function correctly fails on invalid parameter.
 *
 * @see f_fss_skip_past_delimit()
 */
extern void test__f_fss_skip_past_delimit__parameter_checking(void **state);

/**
 * Test that the function returns F_data_not.
 *
 * @see f_fss_skip_past_delimit()
 */
extern void test__f_fss_skip_past_delimit__returns_data_not(void **state);

/**
 * Test that the function works.
 *
 * @see f_fss_skip_past_delimit()
 */
extern void test__f_fss_skip_past_delimit__works(void **state);

#endif // _TEST__F_fss__skip_past_delimit
