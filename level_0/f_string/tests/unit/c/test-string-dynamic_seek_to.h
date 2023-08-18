/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the array types in the type project.
 */
#ifndef _TEST__F_string_dynamic_seek_to_h
#define _TEST__F_string_dynamic_seek_to_h

/**
 * Test that the function returns F_data_not_stop because range is an empty range (range.start > range.stop).
 *
 * @see f_string_dynamic_seek_to()
 */
extern void test__f_string_dynamic_seek_to__returns_data_not_stop(void **state);

/**
 * Test that the function returns F_okay_eos stopped after end of string because no newline is found.
 *
 * @see f_string_dynamic_seek_to()
 */
extern void test__f_string_dynamic_seek_to__returns_none_eos(void **state);

/**
 * Test that the function returns F_okay_stop stopped after end of range because no newline is found.
 *
 * @see f_string_dynamic_seek_to()
 */
extern void test__f_string_dynamic_seek_to__returns_none_stop(void **state);

/**
 * Test that the function works.
 *
 * @see f_string_dynamic_seek_to()
 */
extern void test__f_string_dynamic_seek_to__works(void **state);

/**
 * Test that the function correctly fails on invalid parameter.
 *
 * @see f_string_dynamic_seek_to()
 */
extern void test__f_string_dynamic_seek_to__parameter_checking(void **state);

#endif // _TEST__F_string_dynamic_seek_to_h
