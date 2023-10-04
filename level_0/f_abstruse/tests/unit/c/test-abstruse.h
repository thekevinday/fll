/**
 * FLL - Level 0
 *
 * Project: Abstruse
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the abstruse project.
 */
#ifndef _TEST__F_abstruse_h
#define _TEST__F_abstruse_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/abstruse.h>

// Mock includes.
#include "mock-abstruse.h"

// Test includes.
#include "test-abstruse-maps_delete_callback.h"
#include "test-abstruse-maps_destroy_callback.h"
#include "test-abstruse-mapss_delete_callback.h"
#include "test-abstruse-mapss_destroy_callback.h"
#include "test-abstruse-s_delete_callback.h"
#include "test-abstruse-s_destroy_callback.h"
#include "test-abstruse-ss_delete_callback.h"
#include "test-abstruse-ss_destroy_callback.h"

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

#endif // _TEST__F_abstruse_h
