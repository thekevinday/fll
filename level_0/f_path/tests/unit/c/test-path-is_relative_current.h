/**
 * FLL - Level 0
 *
 * Project: Path
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the path project.
 */
#ifndef _TEST__F_path_is_relative_current_h
#define _TEST__F_path_is_relative_current_h

/**
 * Test that function returns F_false.
 *
 * @see f_path_is_relative_current()
 */
extern void test__f_path_is_relative_current__returns_false(void **state);

/**
 * Test that function returns F_data_not.
 *
 * @see f_path_is_relative_current()
 */
extern void test__f_path_is_relative_current__returns_data_not(void **state);

/**
 * Test that function returns F_true.
 *
 * @see f_path_is_relative_current()
 */
extern void test__f_path_is_relative_current__returns_true(void **state);

#endif // _TEST__F_path_is_relative_current_h
