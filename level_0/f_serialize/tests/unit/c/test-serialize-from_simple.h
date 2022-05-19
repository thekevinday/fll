/**
 * FLL - Level 0
 *
 * Project: Serialize
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the serialize project.
 */
#ifndef _TEST__F_serialize_from_simple_h
#define _TEST__F_serialize_from_simple_h

/**
 * Test that parameter checking works as expected.
 *
 * @see f_serialize_from_simple()
 */
extern void test__f_serialize_from_simple__parameter_checking(void **state);

/**
 * Test that function works but returns F_data_not.
 *
 * @see f_serialize_from_simple()
 */
extern void test__f_serialize_from_simple__returns_data_not(void **state);

/**
 * Test that function works.
 *
 * @see f_serialize_from_simple()
 */
extern void test__f_serialize_from_simple__works(void **state);

#endif // _TEST__F_serialize_from_simple_h
