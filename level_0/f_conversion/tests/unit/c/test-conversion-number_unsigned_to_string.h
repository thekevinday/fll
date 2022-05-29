/**
 * FLL - Level 0
 *
 * Project: Conversion
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the conversion project.
 */
#ifndef _TEST__F_conversion_number_unsigned_to_string_h
#define _TEST__F_conversion_number_unsigned_to_string_h

// f_conversion_number_unsigned_to_string() only returns memory failures.

/**
 * Test that parameter checking works as expected.
 *
 * @see f_conversion_number_unsigned_to_string()
 */
extern void test__f_conversion_number_unsigned_to_string__parameter_checking(void **state);

/**
 * Test that function works.
 *
 * @see f_conversion_number_unsigned_to_string()
 */
extern void test__f_conversion_number_unsigned_to_string__works(void **state);

/**
 * Test that function works when the prepend flag is used.
 *
 * @see f_conversion_number_unsigned_to_string()
 */
extern void test__f_conversion_number_unsigned_to_string__works_for_prepend(void **state);

/**
 * Test that function works for 0.
 *
 * @see f_conversion_number_unsigned_to_string()
 */
extern void test__f_conversion_number_unsigned_to_string__works_for_zero(void **state);

#endif // _TEST__F_conversion_number_unsigned_to_string_h
