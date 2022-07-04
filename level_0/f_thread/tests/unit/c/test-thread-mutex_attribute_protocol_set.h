/**
 * FLL - Level 0
 *
 * Project: Thread
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Test the thread project.
 */
#ifndef _TEST__F_thread__mutex_attribute_protocol_set_h
#define _TEST__F_thread__mutex_attribute_protocol_set_h

/**
 * Test that function fails.
 *
 * @see f_thread_mutex_attribute_protocol_set()
 */
extern void test__f_thread_mutex_attribute_protocol_set__fails(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_thread_mutex_attribute_protocol_set()
 */
extern void test__f_thread_mutex_attribute_protocol_set__parameter_checking(void **state);

/**
 * Test that function works.
 *
 * @see f_thread_mutex_attribute_protocol_set()
 */
extern void test__f_thread_mutex_attribute_protocol_set__works(void **state);

#endif // _TEST__F_thread__mutex_attribute_protocol_set_h
