/**
 * FLL - Level 0
 *
 * Project: FSS
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test fail utf in the fss project.
 */
#ifndef _TEST__F_fss__fail_utf
#define _TEST__F_fss__fail_utf

/**
 * Test that the function works for when error bit is set.
 *
 * @see f_fss_fail_utf()
 */
extern void test__f_fss_fail_utf__works_for_error(void **state);

/**
 * Test that the function works for when no error bit is set.
 *
 * @see f_fss_fail_utf()
 */
extern void test__f_fss_fail_utf__works_for_no_error(void **state);

#endif // _TEST__F_fss__fail_utf
