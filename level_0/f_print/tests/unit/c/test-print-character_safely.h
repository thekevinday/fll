/**
 * FLL - Level 0
 *
 * Project: Print
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the print project.
 */
#ifndef _TEST__F_print_character_safely_h
#define _TEST__F_print_character_safely_h

/**
 * Test that function fails.
 *
 * @see f_print_character_safely()
 */
extern void test__f_print_character_safely__fails(void **state);

/**
 * Test that function works but returns F_stream_not.
 *
 * @see f_print_character_safely()
 */
extern void test__f_print_character_safely__returns_stream_not(void **state);

/**
 * Test that function works but returns F_utf.
 *
 * @see f_print_character_safely()
 */
extern void test__f_print_character_safely__returns_utf(void **state);

/**
 * Test that function works.
 *
 * @see f_print_character_safely()
 */
extern void test__f_print_character_safely__works(void **state);

#endif // _TEST__F_print_character_safely_h
