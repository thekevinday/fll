/**
 * FLL - Level 0
 *
 * Project: Memory
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test set quote resize in the fss project.
 */
#ifndef _TEST__F_memory__array_append
#define _TEST__F_memory__array_append

/**
 * Test that the function correctly fails on invalid parameter.
 *
 * @see f_memory_array_append()
 */
extern void test__f_memory_array_append__parameter_checking(void **state);

/**
 * Test that the function returns F_array_too_large.
 *
 * @see f_memory_array_append()
 */
extern void test__f_memory_array_append__returns_array_too_large(void **state);

/**
 * Test that the function works.
 *
 * @see f_memory_array_append()
 */
extern void test__f_memory_array_append__works(void **state);

#endif // _TEST__F_memory__array_append
