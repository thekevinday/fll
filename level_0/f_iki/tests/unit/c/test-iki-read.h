/**
 * FLL - Level 0
 *
 * Project: IKI
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the iki project.
 */
#ifndef _TEST__F_iki_read_h
#define _TEST__F_iki_read_h

/**
 * Test that parameter checking works as expected.
 *
 * @see f_iki_read()
 */
#ifndef _di_level_0_parameter_checking_
  extern void test__f_iki_read__parameter_checking(void **state);
#endif // _di_level_0_parameter_checking_

/**
 * Test that function returns F_data_not.
 *
 * @see f_iki_read()
 */
extern void test__f_iki_read__returns_data_not(void **state);

/**
 * Test that function returns F_data_not_eos.
 *
 * @see f_iki_read()
 */
extern void test__f_iki_read__returns_data_not_eos(void **state);

/**
 * Test that function returns F_data_not_stop.
 *
 * @see f_iki_read()
 */
extern void test__f_iki_read__returns_data_not_stop(void **state);

/**
 * Test that function works.
 *
 * @see f_iki_read()
 */
extern void test__f_iki_read__works(void **state);

#endif // _TEST__F_iki_read_h
