/**
 * FLL - Level 0
 *
 * Project: Conversion
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the conversion project.
 */
#ifndef _TEST__F_conversion_character_to_decimal_h
#define _TEST__F_conversion_character_to_decimal_h

/**
 * Test that function fails.
 *
 * @see f_conversion_character_to_decimal()
 */
extern void test__f_conversion_character_to_decimal__fails(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_conversion_character_to_decimal()
 */
#ifndef _di_level_0_parameter_checking_
  extern void test__f_conversion_character_to_decimal__parameter_checking(void **state);
#endif // _di_level_0_parameter_checking_

/**
 * Test that function works.
 *
 * @see f_conversion_character_to_decimal()
 */
extern void test__f_conversion_character_to_decimal__works(void **state);

#endif // _TEST__F_conversion_character_to_decimal_h
