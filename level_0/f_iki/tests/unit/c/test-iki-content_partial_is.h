/**
 * FLL - Level 0
 *
 * Project: IKI
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Test the iki project.
 */
#ifndef _TEST__F_iki_content_partial_is_h
#define _TEST__F_iki_content_partial_is_h

/**
 * Test that function returns F_false.
 *
 * @see f_iki_content_partial_is()
 */
extern void test__f_iki_content_partial_is__returns_false(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_iki_content_partial_is()
 */
extern void test__f_iki_content_partial_is__parameter_checking(void **state);

/**
 * Test that function returns F_data_not.
 *
 * @see f_iki_content_partial_is()
 */
extern void test__f_iki_content_partial_is__returns_data_not(void **state);

/**
 * Test that function returns F_data_not_eos.
 *
 * @see f_iki_content_partial_is()
 */
extern void test__f_iki_content_partial_is__returns_data_not_eos(void **state);

/**
 * Test that function returns F_data_not_stop.
 *
 * @see f_iki_content_partial_is()
 */
extern void test__f_iki_content_partial_is__returns_data_not_stop(void **state);

/**
 * Test that function returns F_true.
 *
 * @see f_iki_content_partial_is()
 */
extern void test__f_iki_content_partial_is__returns_true(void **state);

#endif // _TEST__F_iki_content_partial_is_h
