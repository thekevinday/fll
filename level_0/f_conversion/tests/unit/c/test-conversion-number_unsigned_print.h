/**
 * FLL - Level 0
 *
 * Project: Conversion
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Test the conversion project.
 */
#ifndef _TEST__F_conversion_number_unsigned_print_h
#define _TEST__F_conversion_number_unsigned_print_h

/**
 * Test that function fails.
 *
 * @see f_conversion_number_unsigned_print()
 */
extern void test__f_conversion_number_unsigned_print__fails(void **state);

/**
 * Test that function fails when the prepend flag is used.
 *
 * @see f_conversion_number_unsigned_print()
 */
extern void test__f_conversion_number_unsigned_print__fails_for_prepend(void **state);

/**
 * Test that function fails for 0.
 *
 * @see f_conversion_number_unsigned_print()
 */
extern void test__f_conversion_number_unsigned_print__fails_for_zero(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_conversion_number_unsigned_print()
 */
extern void test__f_conversion_number_unsigned_print__parameter_checking(void **state);

/**
 * Test that function works.
 *
 * @see f_conversion_number_unsigned_print()
 */
extern void test__f_conversion_number_unsigned_print__works(void **state);

/**
 * Test that function works for 0.
 *
 * @see f_conversion_number_unsigned_print()
 */
extern void test__f_conversion_number_unsigned_print__works_for_zero(void **state);

/**
 * Test that function works for 0 when width is 0.
 *
 * @see f_conversion_number_unsigned_print()
 */
extern void test__f_conversion_number_unsigned_print__works_for_zero_with_width_zero(void **state);

#endif // _TEST__F_conversion_number_unsigned_print_h
