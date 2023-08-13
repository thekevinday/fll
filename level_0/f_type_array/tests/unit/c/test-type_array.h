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
#include <fll/level_0/type_file.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/type_array.h>
#include <fll/level_0/type_array_file.h>

// Test includes.
#include "test-type_array-cells_destroy_callback.h"
#include "test-type_array-cells_delete_callback.h"
#include "test-type_array-files_destroy_callback.h"
#include "test-type_array-files_delete_callback.h"
#include "test-type_array-fll_ids_destroy_callback.h"
#include "test-type_array-fll_ids_delete_callback.h"
#include "test-type_array-int8s_destroy_callback.h"
#include "test-type_array-int8s_delete_callback.h"
#include "test-type_array-int16s_destroy_callback.h"
#include "test-type_array-int16s_delete_callback.h"
#include "test-type_array-int32s_destroy_callback.h"
#include "test-type_array-int32s_delete_callback.h"
#include "test-type_array-int64s_destroy_callback.h"
#include "test-type_array-int64s_delete_callback.h"
#include "test-type_array-int128s_destroy_callback.h"
#include "test-type_array-int128s_delete_callback.h"
#include "test-type_array-number_unsigneds_destroy_callback.h"
#include "test-type_array-number_unsigneds_delete_callback.h"
#include "test-type_array-polls_destroy_callback.h"
#include "test-type_array-polls_delete_callback.h"
#include "test-type_array-states_destroy_callback.h"
#include "test-type_array-states_delete_callback.h"
#include "test-type_array-statuss_destroy_callback.h"
#include "test-type_array-statuss_delete_callback.h"
#include "test-type_array-uint8s_destroy_callback.h"
#include "test-type_array-uint8s_delete_callback.h"
#include "test-type_array-uint16s_destroy_callback.h"
#include "test-type_array-uint16s_delete_callback.h"
#include "test-type_array-uint32s_destroy_callback.h"
#include "test-type_array-uint32s_delete_callback.h"
#include "test-type_array-uint64s_destroy_callback.h"
#include "test-type_array-uint64s_delete_callback.h"
#include "test-type_array-uint128s_destroy_callback.h"
#include "test-type_array-uint128s_delete_callback.h"

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
