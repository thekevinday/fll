/**
 * FLL - Level 0
 *
 * Project: Signal
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the signal project.
 */
#ifndef _TEST__F_signal_h
#define _TEST__F_signal_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/signal.h>

// Mock includes.
#include "mock-signal.h"

// Test includes.
#include "test-signal-action.h"
#include "test-signal-close.h"
#include "test-signal-mask.h"
#include "test-signal-open.h"
#include "test-signal-pause.h"
#include "test-signal-queue.h"
#include "test-signal-read.h"
#include "test-signal-send.h"
#include "test-signal-set_add.h"
#include "test-signal-set_delete.h"
#include "test-signal-set_empty.h"
#include "test-signal-set_fill.h"
#include "test-signal-set_has.h"
#include "test-signal-suspend.h"
#include "test-signal-wait.h"
#include "test-signal-wait_until.h"

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

#endif // _TEST__F_signal_h
