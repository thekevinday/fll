/**
 * FLL - Level 0
 *
 * Project: Print
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the print project.
 */
#ifndef _TEST__F_print_character_safely_get_h
#define _TEST__F_print_character_safely_get_h

/**
 * Test that function works but returns a control character safe alternative.
 *
 * @see f_print_character_safely_get()
 */
extern void test__f_print_character_safely_get__returns_character_control(void **state);

/**
 * Test that function works but returns a delete character safe alternative.
 *
 * @see f_print_character_safely_get()
 */
extern void test__f_print_character_safely_get__returns_character_delete(void **state);

/**
 * Test that function works but returns a unknown character safe alternative.
 *
 * @see f_print_character_safely_get()
 */
extern void test__f_print_character_safely_get__returns_character_unknown(void **state);

/**
 * Test that function works but returns an empty string.
 *
 * @see f_print_character_safely_get()
 */
extern void test__f_print_character_safely_get__returns_empty(void **state);

#endif // _TEST__F_print_character_safely_get_h
