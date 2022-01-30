/**
 * FLL - Level 0
 *
 * Project: Conversion
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the conversion project.
 */
#ifndef _TEST__F_conversion_h
#define _TEST__F_conversion_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/conversion.h>

// mock includes.
#include "mock-conversion.h"

// test includes.
#include "test-conversion-character_is_binary.h"
#include "test-conversion-character_is_decimal.h"
#include "test-conversion-character_is_duodecimal.h"
#include "test-conversion-character_is_hexidecimal.h"
#include "test-conversion-character_is_octal.h"
#include "test-conversion-character_to_binary.h"
#include "test-conversion-character_to_decimal.h"
#include "test-conversion-character_to_duodecimal.h"
#include "test-conversion-character_to_hexidecimal.h"
#include "test-conversion-character_to_octal.h"
#include "test-conversion-number_signed_print.h"
#include "test-conversion-number_signed_to_string.h"
#include "test-conversion-number_unsigned_print.h"
#include "test-conversion-number_unsigned_to_string.h"

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

#endif // _TEST__F_conversion_h
