/**
 * FLL - Level 2
 *
 * Project: Status
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the status_string project.
 */
#ifndef _TEST__FLL_status_string_from_h
#define _TEST__FLL_status_string_from_h

/**
 * Test that function fails.
 *
 * @see fll_status_string_from()
 */
extern void test__fll_status_string_from__fails(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see fll_status_string_from()
 */
extern void test__fll_status_string_from__parameter_checking(void **state);

/**
 * Test that function returns F_data_not.
 *
 * @see fll_status_string_from()
 */
extern void test__fll_status_string_from__returns_data_not(void **state);

/**
 * Test that function works.
 *
 * @see fll_status_string_from()
 */
extern void test__fll_status_string_from__works(void **state);

#endif // _TEST__FLL_status_string_from_h
