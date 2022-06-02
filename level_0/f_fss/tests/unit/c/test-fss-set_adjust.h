/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test set adjust in the fss project.
 */
#ifndef _TEST__F_fss__set_adjust
#define _TEST__F_fss__set_adjust

/**
 * Test that the function correctly fails on invalid parameter.
 *
 * @see f_fss_set_adjust()
 */
extern void test__f_fss_set_adjust__parameter_checking(void **state);

/**
 * Test that the function works.
 *
 * @see f_fss_set_adjust()
 */
extern void test__f_fss_set_adjust__works(void **state);

#endif // _TEST__F_fss__set_adjust
