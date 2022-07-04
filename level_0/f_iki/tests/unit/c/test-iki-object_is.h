/**
 * FLL - Level 0
 *
 * Project: IKI
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Test the iki project.
 */
#ifndef _TEST__F_iki_object_is_h
#define _TEST__F_iki_object_is_h

/**
 * Test that function returns F_false.
 *
 * @see f_iki_object_is()
 */
extern void test__f_iki_object_is__returns_false(void **state);

// f_iki_object_is() doesn't use parameter checking.

/**
 * Test that function returns F_data_not.
 *
 * @see f_iki_object_is()
 */
extern void test__f_iki_object_is__returns_data_not(void **state);

/**
 * Test that function returns F_true.
 *
 * @see f_iki_object_is()
 */
extern void test__f_iki_object_is__returns_true(void **state);

#endif // _TEST__F_iki_object_is_h
