/**
 * FLL - Level 0
 *
 * Project: Memory
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the memory project.
 */
#ifndef _TEST__F_memory__new_aligned
#define _TEST__F_memory__new_aligned

/**
 * Test that parameter checking works as expected.
 *
 * @see f_memory_new_aligned()
 */
#ifndef _di_level_0_parameter_checking_
  extern void test__f_memory_new_aligned__parameter_checking(void **state);
#endif // _di_level_0_parameter_checking_

/**
 * Test that allocation works.
 *
 * @see f_memory_new_aligned()
 */
extern void test__f_memory_new_aligned__works(void **state);

#endif // _TEST__F_memory__new_aligned