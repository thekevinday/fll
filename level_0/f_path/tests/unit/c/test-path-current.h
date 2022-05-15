/**
 * FLL - Level 0
 *
 * Project: Path
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the path project.
 */
#ifndef _TEST__F_path_current_h
#define _TEST__F_path_current_h

/**
 * Test that function fails.
 *
 * @see f_path_current()
 */
extern void test__f_path_current__fails(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_path_current()
 */
#ifndef _di_level_0_parameter_checking_
  extern void test__f_path_current__parameter_checking(void **state);
#endif // _di_level_0_parameter_checking_

/**
 * Test that function works.
 *
 * @see f_path_current()
 */
extern void test__f_path_current__works(void **state);

#endif // _TEST__F_path_current_h
