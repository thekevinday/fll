/**
 * FLL - Level 0
 *
 * Project: String
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the array types in the type project.
 */
#ifndef _TEST__F_dynamic_strip_null_range_h
#define _TEST__F_dynamic_strip_null_range_h

/**
 * Test that the function returns F_data_not because the buffer is empty.
 *
 * @see f_string_dynamic_strip_null_range()
 */
extern void test__f_string_dynamic_strip_null_range__returns_data_not(void **state);

/**
 * Test that the function returns F_data_not_eos because range stops after buffer ends (range.stop >= buffer.used).
 *
 * @see f_string_dynamic_strip_null_range()
 */
extern void test__f_string_dynamic_strip_null_range__returns_data_not_eos(void **state);

/**
 * Test that the function returns F_data_not_stop because range is an empty range (range.start > range.stop).
 *
 * @see f_string_dynamic_strip_null_range()
 */
extern void test__f_string_dynamic_strip_null_range__returns_data_not_stop(void **state);

/**
 * Test that the function works.
 *
 * @see f_string_dynamic_strip_null_range()
 */
extern void test__f_string_dynamic_strip_null_range__works(void **state);

/**
 * Test that the function correctly fails on invalid parameter.
 *
 * @see f_string_dynamic_strip_null_range()
 */
extern void test__f_string_dynamic_strip_null_range__parameter_checking(void **state);

#endif // _TEST__F_dynamic_strip_null_range_h