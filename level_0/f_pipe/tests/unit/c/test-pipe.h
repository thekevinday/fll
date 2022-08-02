/**
 * FLL - Level 0
 *
 * Project: Pipe
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the pipe project.
 */
#ifndef _TEST__F_pipe_h
#define _TEST__F_pipe_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <string.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/pipe.h>

// Mock includes.
#include "mock-pipe.h"

// Test includes.
#include "test-pipe-debug_exists.h"
#include "test-pipe-error_exists.h"
#include "test-pipe-input_exists.h"
#include "test-pipe-warning_exists.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Perform any setup operations.
 *
 * @param state
 *   The test state.
 *
 * @return
 *   The status of this function, where 0 means success.
 */
extern int setup(void **state);

/**
 * Peform any setdown operations.
 *
 * @param state
 *   The test state.
 *
 * @return
 *   The status of this function, where 0 means success.
 */
extern int setdown(void **state);

/**
 * Run all tests.
 *
 * @return
 *   The final result of the tests.
 *
 * @see cmocka_run_group_tests()
 * @see cmocka_unit_test()
 */
extern int main(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _TEST__F_pipe_h
