/**
 * FLL - Level 2
 *
 * Project: FSS
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Test the fl_fss project.
 */
#ifndef _TEST__FL_fss_basic_list_content_read_list_h
#define _TEST__FL_fss_basic_list_content_read_list_h

/**
 * Test that parameter checking works as expected.
 *
 * @see fl_fss_basic_list_content_read()
 */
extern void test__fl_fss_basic_list_content_read__parameter_checking(void **state);

/**
 * Test that the function returns F_data_not.
 *
 * @see fl_fss_basic_list_content_read()
 */
extern void test__fl_fss_basic_list_content_read__returns_data_not(void **state);

/**
 * Test that the function works.
 *
 * @see fl_fss_basic_list_content_read()
 */
extern void test__fl_fss_basic_list_content_read__works(void **state);

#endif // _TEST__FL_fss_basic_list_content_read_list_h
