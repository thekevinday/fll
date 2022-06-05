/**
 * FLL - Level 0
 *
 * Project: Status
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the status project.
 */
#ifndef _TEST__F_status_h
#define _TEST__F_status_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/status.h>

// Test includes.
#include "test-status-macro-is_error.h"
#include "test-status-macro-is_error_not.h"
#include "test-status-macro-is_fine.h"
#include "test-status-macro-is_fine_not.h"
#include "test-status-macro-is_problem.h"
#include "test-status-macro-is_problem_not.h"
#include "test-status-macro-is_signal.h"
#include "test-status-macro-is_signal_not.h"
#include "test-status-macro-is_warning.h"
#include "test-status-macro-is_warning_not.h"
#include "test-status-macro-set_error.h"
#include "test-status-macro-set_fine.h"
#include "test-status-macro-set_signal.h"
#include "test-status-macro-set_warning.h"

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

#endif // _TEST__F_status_h
