/**
 * FLL - Level 0
 *
 * Project: Memory
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test set quote resize in the fss project.
 */
#ifndef _TEST__F_memory__array_append_all
#define _TEST__F_memory__array_append_all

/**
 * Test that the function correctly fails on invalid parameter.
 *
 * @see f_memory_array_append_all()
 */
extern void test__f_memory_array_append_all__parameter_checking(void **state);

/**
 * Test that the function returns F_array_too_large.
 *
 * @see f_memory_array_append_all()
 */
extern void test__f_memory_array_append_all__returns_array_too_large(void **state);

/**
 * Test that the function returns F_data_not.
 *
 * @see f_memory_array_append_all()
 */
extern void test__f_memory_array_append_all__returns_data_not(void **state);

/**
 * Test that the function works.
 *
 * @see f_memory_array_append_all()
 */
extern void test__f_memory_array_append_all__works(void **state);

#endif // _TEST__F_memory__array_append_all
