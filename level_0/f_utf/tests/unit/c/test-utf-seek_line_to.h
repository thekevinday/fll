/**
 * FLL - Level 0
 *
 * Project: UTF
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the data types in the utf project.
 */
#ifndef _TEST__F_utf_seek_line_to_h
#define _TEST__F_utf_seek_line_to_h

/**
 * Test that the function works where seek target is after a newline.
 *
 * @see f_utf_string_seek_line_to()
 */
extern void test__f_utf_seek_line_to__after_newline(void **state);

/**
 * Test that the function works where seek target is before a newline.
 *
 * @see f_utf_string_seek_line_to()
 */
extern void test__f_utf_seek_line_to__before_newline(void **state);

/**
 * Test that the function returns F_data_not_stop because range is an empty range (range.start > range.stop).
 *
 * @see f_utf_string_seek_line_to()
 */
extern void test__f_utf_seek_line_to__returns_data_not_stop(void **state);

/**
 * Test that the function returns F_none_stop stopped after end of range because no newline is found.
 *
 * @see f_utf_string_seek_line_to()
 */
extern void test__f_utf_seek_line_to__returns_none_stop(void **state);

/**
 * Test that the function correctly fails on invalid parameter.
 *
 * @see f_utf_string_seek_line_to()
 */
extern void test__f_utf_seek_line_to__parameter_checking(void **state);

#endif // _TEST__F_utf_seek_line_to_h
