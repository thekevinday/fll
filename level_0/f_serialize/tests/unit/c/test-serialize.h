/**
 * FLL - Level 0
 *
 * Project: Serialize
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Test the serialize project.
 */
#ifndef _TEST__F_serialize_h
#define _TEST__F_serialize_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/serialize.h>

// Mock includes.
//#include "mock-serialize.h"

// Test includes.
#include "test-serialize-from_simple.h"
#include "test-serialize-from_simple_get.h"
#include "test-serialize-from_simple_range.h"
#include "test-serialize-from_simple_select.h"
#include "test-serialize-to_simple.h"

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

#endif // _TEST__F_serialize_h
