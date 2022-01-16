/**
 * FLL - Level 0
 *
 * Project: Memory
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the memory project.
 */
#ifndef _TEST__F_memory__adjust
#define _TEST__F_memory__adjust

/**
 * Test that parameter checking works as expected.
 *
 * @see f_memory_adjust()
 */
#ifndef _di_level_0_parameter_checking_
  extern void test__f_memory_adjust__parameter_checking(void **state);
#endif // _di_level_0_parameter_checking_

/**
 * Test that reallocation works.
 *
 * @see f_memory_new()
 * @see f_memory_adjust()
 */
extern void test__f_memory_adjust__works(void **state);

#endif // _TEST__F_memory__adjust
