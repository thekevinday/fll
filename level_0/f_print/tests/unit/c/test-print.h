/**
 * FLL - Level 0
 *
 * Project: Print
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the print project.
 */
#ifndef _TEST__F_print_h
#define _TEST__F_print_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/print.h>

// Mock includes.
#include "mock-print.h"

// Test includes.
#include "test-print-.h"
#include "test-print-character.h"
#include "test-print-character_safely.h"
#include "test-print-character_safely_get.h"
#include "test-print-dynamic.h"
#include "test-print-dynamic_partial.h"
#include "test-print-dynamic_partial_raw.h"
#include "test-print-dynamic_partial_raw_safely.h"
#include "test-print-dynamic_partial_safely.h"
#include "test-print-dynamic_raw.h"
#include "test-print-dynamic_raw_safely.h"
#include "test-print-dynamic_safely.h"
#include "test-print-except.h"
#include "test-print-except_dynamic.h"
#include "test-print-except_dynamic_partial.h"
#include "test-print-except_dynamic_partial_raw.h"
#include "test-print-except_dynamic_partial_raw_safely.h"
#include "test-print-except_dynamic_partial_safely.h"
#include "test-print-except_dynamic_raw.h"
#include "test-print-except_dynamic_raw_safely.h"
#include "test-print-except_dynamic_safely.h"
#include "test-print-except_in.h"
#include "test-print-except_in_dynamic.h"
#include "test-print-except_in_dynamic_partial.h"
#include "test-print-except_in_dynamic_partial_raw.h"
#include "test-print-except_in_dynamic_partial_raw_safely.h"
#include "test-print-except_in_dynamic_partial_safely.h"
#include "test-print-except_in_dynamic_raw.h"
#include "test-print-except_in_dynamic_raw_safely.h"
#include "test-print-except_in_dynamic_safely.h"
#include "test-print-except_in_raw.h"
#include "test-print-except_in_raw_safely.h"
#include "test-print-except_in_safely.h"
#include "test-print-except_raw.h"
#include "test-print-except_raw_safely.h"
#include "test-print-except_safely.h"
#include "test-print-raw.h"
#include "test-print-raw_safely.h"
#include "test-print-raw_terminated.h"
#include "test-print-safely.h"
#include "test-print-safely_get.h"
#include "test-print-safely_terminated.h"
#include "test-print-terminated.h"
#include "test-print-to.h"
#include "test-print-to_character.h"
#include "test-print-to_character_safely.h"
#include "test-print-to_dynamic.h"
#include "test-print-to_dynamic_partial.h"
#include "test-print-to_dynamic_partial_raw.h"
#include "test-print-to_dynamic_partial_raw_safely.h"
#include "test-print-to_dynamic_partial_safely.h"
#include "test-print-to_dynamic_raw.h"
#include "test-print-to_dynamic_raw_safely.h"
#include "test-print-to_dynamic_safely.h"
#include "test-print-to_except.h"
#include "test-print-to_except_dynamic.h"
#include "test-print-to_except_dynamic_partial.h"
#include "test-print-to_except_dynamic_partial_raw.h"
#include "test-print-to_except_dynamic_partial_raw_safely.h"
#include "test-print-to_except_dynamic_partial_safely.h"
#include "test-print-to_except_dynamic_raw.h"
#include "test-print-to_except_dynamic_raw_safely.h"
#include "test-print-to_except_dynamic_safely.h"
#include "test-print-to_except_in.h"
#include "test-print-to_except_in_dynamic.h"
#include "test-print-to_except_in_dynamic_partial.h"
#include "test-print-to_except_in_dynamic_partial_raw.h"
#include "test-print-to_except_in_dynamic_partial_raw_safely.h"
#include "test-print-to_except_in_dynamic_partial_safely.h"
#include "test-print-to_except_in_dynamic_raw.h"
#include "test-print-to_except_in_dynamic_raw_safely.h"
#include "test-print-to_except_in_dynamic_safely.h"
#include "test-print-to_except_in_raw.h"
#include "test-print-to_except_in_raw_safely.h"
#include "test-print-to_except_in_safely.h"
#include "test-print-to_except_raw.h"
#include "test-print-to_except_raw_safely.h"
#include "test-print-to_except_safely.h"
#include "test-print-to_raw.h"
#include "test-print-to_raw_safely.h"
#include "test-print-to_raw_terminated.h"
#include "test-print-to_safely.h"
#include "test-print-to_safely_terminated.h"
#include "test-print-to_terminated.h"

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

#endif // _TEST__F_print_h
