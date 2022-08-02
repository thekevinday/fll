/**
 * FLL - Level 0
 *
 * Project: Console
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the console project.
 */
#ifndef _TEST__F_console_h
#define _TEST__F_console_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/console.h>

// Test includes.
#include "test-console-identify.h"
#include "test-console-environment_process.h"
#include "test-console-parameter_prioritize_left.h"
#include "test-console-parameter_prioritize_right.h"
#include "test-console-parameter_process.h"
#include "test-console-parameters_delete.h"
#include "test-console-parameters_destroy.h"

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

#endif // _TEST__F_console_h
