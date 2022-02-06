/**
 * FLL - Level 0
 *
 * Project: Color
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the color project.
 */
#ifndef _TEST__F_color__delete
#define _TEST__F_color__delete

/**
 * Test that deallocation works.
 *
 * @see f_color_context_delete()
 */
extern void test__f_color_context_delete__frees_memory(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_color_context_delete()
 */
#ifndef _di_level_0_parameter_checking_
  extern void test__f_color_context_delete__parameter_checking(void **state);
#endif // _di_level_0_parameter_checking_

#endif // _TEST__F_color__delete
