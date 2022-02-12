/**
 * FLL - Level 0
 *
 * Project: Memory
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the memory project.
 */
#ifndef _TEST__F_memory__resize
#define _TEST__F_memory__resize

/**
 * Test that parameter checking works as expected.
 *
 * @see f_memory_resize()
 */
#ifndef _di_level_0_parameter_checking_
  extern void test__f_memory_resize__parameter_checking(void **state);
#endif // _di_level_0_parameter_checking_

/**
 * Test that reallocation works.
 *
 * @see f_memory_new()
 * @see f_memory_resize()
 */
extern void test__f_memory_resize__works(void **state);

#endif // _TEST__F_memory__resize