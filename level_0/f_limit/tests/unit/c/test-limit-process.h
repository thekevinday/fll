/**
 * FLL - Level 0
 *
 * Project: Limit
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Test the limit project.
 */
#ifndef _TEST__F_limit_process_h
#define _TEST__F_limit_process_h

/**
 * Test that function fails.
 *
 * @see f_limit_process()
 */
extern void test__f_limit_process__fails(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_limit_process()
 */
extern void test__f_limit_process__parameter_checking(void **state);

/**
 * Test that function works.
 *
 * @see f_limit_process()
 */
extern void test__f_limit_process__works(void **state);

#endif // _TEST__F_limit_process_h
