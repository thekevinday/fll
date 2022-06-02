/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test skip past space in the fss project.
 */
#ifndef _TEST__F_fss__skip_past_space
#define _TEST__F_fss__skip_past_space

/**
 * Test that the function correctly fails on invalid parameter.
 *
 * @see f_fss_skip_past_space()
 */
extern void test__f_fss_skip_past_space__parameter_checking(void **state);

/**
 * Test that the function returns F_data_not.
 *
 * @see f_fss_skip_past_space()
 */
extern void test__f_fss_skip_past_space__returns_data_not(void **state);

/**
 * Test that the function works.
 *
 * @see f_fss_skip_past_space()
 */
extern void test__f_fss_skip_past_space__works(void **state);

#endif // _TEST__F_fss__skip_past_space
