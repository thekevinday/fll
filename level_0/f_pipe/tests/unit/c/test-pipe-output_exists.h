/**
 * FLL - Level 0
 *
 * Project: Pipe
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the pipe project.
 */
#ifndef _TEST__F_pipe_output_exists_h
#define _TEST__F_pipe_output_exists_h

/**
 * Test that function fails.
 *
 * @see f_pipe_output_exists()
 */
extern void test__f_pipe_output_exists__fails(void **state);

/**
 * Test that function returns F_false.
 *
 * @see f_pipe_output_exists()
 */
extern void test__f_pipe_output_exists__returns_false(void **state);

/**
 * Test that function returns F_true.
 *
 * @see f_pipe_output_exists()
 */
extern void test__f_pipe_output_exists__returns_true(void **state);

#endif // _TEST__F_pipe_output_exists_h
