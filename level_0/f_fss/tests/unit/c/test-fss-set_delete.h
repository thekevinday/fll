/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the array types in the type project.
 */
#ifndef _TEST__F_fss__set_delete
#define _TEST__F_fss__set_delete

/**
 * Test that the function fails.
 *
 * @see f_fss_set_delete()
 */
extern void test__f_fss_set_delete__fails(void **state);

/**
 * Test that the function correctly fails on invalid parameter.
 *
 * @see f_fss_set_delete()
 */
extern void test__f_fss_set_delete__parameter_checking(void **state);

/**
 * Test that the function works.
 *
 * @see f_fss_set_delete()
 */
extern void test__f_fss_set_delete__works(void **state);

#endif // _TEST__F_fss__set_delete
