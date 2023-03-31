/**
 * FLL - Level 1
 *
 * Project: Status
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the status_string project.
 */
#ifndef _TEST__FL_status_string_from_h
#define _TEST__FL_status_string_from_h

/**
 * Test that function fails.
 *
 * @see fl_status_string_from()
 */
extern void test__fl_status_string_from__fails(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see fl_status_string_from()
 */
extern void test__fl_status_string_from__parameter_checking(void **state);

/**
 * Test that function returns F_data_not.
 *
 * @see fl_status_string_from()
 */
extern void test__fl_status_string_from__returns_data_not(void **state);

/**
 * Test that function works.
 *
 * @see fl_status_string_from()
 */
extern void test__fl_status_string_from__works(void **state);

#endif // _TEST__FL_status_string_from_h
