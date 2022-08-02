/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test seek to eol in the fss project.
 */
#ifndef _TEST__F_fss__seek_to_eol
#define _TEST__F_fss__seek_to_eol

/**
 * Test that the function correctly fails on invalid parameter.
 *
 * @see f_fss_seek_to_eol()
 */
extern void test__f_fss_seek_to_eol__parameter_checking(void **state);

/**
 * Test that the function returns F_data_not.
 *
 * @see f_fss_seek_to_eol()
 */
extern void test__f_fss_seek_to_eol__returns_data_not(void **state);

/**
 * Test that the function works.
 *
 * @see f_fss_seek_to_eol()
 */
extern void test__f_fss_seek_to_eol__works(void **state);

#endif // _TEST__F_fss__seek_to_eol
