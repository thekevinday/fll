/**
 * FLL - Level 0
 *
 * Project: Console
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the console project.
 */
#ifndef _TEST__F_console_environment_process_h
#define _TEST__F_console_environment_process_h

// f_console_environment_process() only returns memory failures.

/**
 * Test that the function returns F_data_not when there are no environment variables.
 *
 * @see test__f_console_environment_process__data_not()
 */
extern void test__f_console_environment_process__data_not(void **state);

/**
 * Test that parameter checking works as expected.
 *
 * @see f_console_environment_process()
 */
extern void test__f_console_environment_process__parameter_checking(void **state);

/**
 * Test that function works.
 *
 * @see f_console_environment_process()
 */
extern void test__f_console_environment_process__works(void **state);

#endif // _TEST__F_console_environment_process_h
