/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the type arrays in the project.
 */
#ifndef _TEST__F_type_array_h
#define _TEST__F_type_array_h

// libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// fll-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/type/file.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/type_array.h>
#include <fll/level_0/type_array_file.h>

// Mock includes.
#include "mock-type_array.h"

// Test includes.
#include "test-type_array-cellss_delete_callback.h"
#include "test-type_array-cellss_destroy_callback.h"
#include "test-type_array-filess_delete_callback.h"
#include "test-type_array-filess_destroy_callback.h"
#include "test-type_array-fll_idss_delete_callback.h"
#include "test-type_array-fll_idss_destroy_callback.h"
#include "test-type_array-int8ss_delete_callback.h"
#include "test-type_array-int8ss_destroy_callback.h"
#include "test-type_array-int16ss_delete_callback.h"
#include "test-type_array-int16ss_destroy_callback.h"
#include "test-type_array-int32ss_delete_callback.h"
#include "test-type_array-int32ss_destroy_callback.h"
#include "test-type_array-int64ss_delete_callback.h"
#include "test-type_array-int64ss_destroy_callback.h"
#include "test-type_array-int128ss_delete_callback.h"
#include "test-type_array-int128ss_destroy_callback.h"
#include "test-type_array-number_signedss_delete_callback.h"
#include "test-type_array-number_signedss_destroy_callback.h"
#include "test-type_array-number_unsignedss_delete_callback.h"
#include "test-type_array-number_unsignedss_destroy_callback.h"
#include "test-type_array-pollss_delete_callback.h"
#include "test-type_array-pollss_destroy_callback.h"
#include "test-type_array-statess_delete_callback.h"
#include "test-type_array-statess_destroy_callback.h"
#include "test-type_array-statusss_delete_callback.h"
#include "test-type_array-statusss_destroy_callback.h"
#include "test-type_array-uint8ss_delete_callback.h"
#include "test-type_array-uint8ss_destroy_callback.h"
#include "test-type_array-uint16ss_delete_callback.h"
#include "test-type_array-uint16ss_destroy_callback.h"
#include "test-type_array-uint32ss_delete_callback.h"
#include "test-type_array-uint32ss_destroy_callback.h"
#include "test-type_array-uint64ss_delete_callback.h"
#include "test-type_array-uint64ss_destroy_callback.h"
#include "test-type_array-uint128ss_delete_callback.h"
#include "test-type_array-uint128ss_destroy_callback.h"

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

#endif // _TEST__F_type_array_h
