/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test set quote adjust in the fss project.
 */
#ifndef _TEST__F_fss__set_quotes_adjust
#define _TEST__F_fss__set_quotes_adjust

/**
 * Test that the function correctly fails on invalid parameter.
 *
 * @see f_fss_set_quotes_adjust()
 */
extern void test__f_fss_set_quotes_adjust__parameter_checking(void **state);

/**
 * Test that the function works.
 *
 * @see f_fss_set_quotes_adjust()
 */
extern void test__f_fss_set_quotes_adjust__works(void **state);

#endif // _TEST__F_fss__set_quotes_adjust
