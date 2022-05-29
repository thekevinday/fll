/**
 * FLL - Level 0
 *
 * Project: Console
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the console project.
 */
#ifndef _TEST__F_console_parameter_process_h
#define _TEST__F_console_parameter_process_h

// f_console_parameter_process() only returns memory failures.

/**
 * Test that function works with no (argv) arguments (but does have program name).
 *
 * @see f_console_parameter_process()
 */
extern void test__f_console_parameter_process__no_arguments(void **state);

/**
 * Test that function works with no (argv) arguments and does not have program name.
 *
 * @see f_console_parameter_process()
 */
extern void test__f_console_parameter_process__no_arguments_no_program(void **state);

/**
 * Test that function works with (argv) arguments as a NULL pointer.
 *
 * @see f_console_parameter_process()
 */
extern void test__f_console_parameter_process__null_arguments(void **state);

/**
 * Test that function works with all (argv) arguments do not match any defined parameter.
 *
 * @see f_console_parameter_process()
 */
extern void test__f_console_parameter_process__only_remaining(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_console_parameter_process()
 */
extern void test__f_console_parameter_process__parameter_checking(void **state);

/**
 * Test that function works.
 *
 * @see f_console_parameter_process()
 */
extern void test__f_console_parameter_process__works(void **state);

#endif // _TEST__F_console_parameter_process_h
