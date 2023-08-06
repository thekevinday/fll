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
#include "test-type_array-cells_adjust_callback.h"
#include "test-type_array-cells_resize_callback.h"
#include "test-type_array-files_adjust_callback.h"
#include "test-type_array-files_resize_callback.h"
#include "test-type_array-fll_ids_adjust_callback.h"
#include "test-type_array-fll_ids_resize_callback.h"
#include "test-type_array-int8s_adjust_callback.h"
#include "test-type_array-int8s_resize_callback.h"
#include "test-type_array-int16s_adjust_callback.h"
#include "test-type_array-int16s_resize_callback.h"
#include "test-type_array-int32s_adjust_callback.h"
#include "test-type_array-int32s_resize_callback.h"
#include "test-type_array-int64s_adjust_callback.h"
#include "test-type_array-int64s_resize_callback.h"
#include "test-type_array-int128s_adjust_callback.h"
#include "test-type_array-int128s_resize_callback.h"
#include "test-type_array-number_unsigneds_adjust_callback.h"
#include "test-type_array-number_unsigneds_resize_callback.h"
#include "test-type_array-uint8s_adjust_callback.h"
#include "test-type_array-uint8s_resize_callback.h"
#include "test-type_array-uint16s_adjust_callback.h"
#include "test-type_array-uint16s_resize_callback.h"
#include "test-type_array-uint32s_adjust_callback.h"
#include "test-type_array-uint32s_resize_callback.h"
#include "test-type_array-uint64s_adjust_callback.h"
#include "test-type_array-uint64s_resize_callback.h"
#include "test-type_array-uint128s_adjust_callback.h"
#include "test-type_array-uint128s_resize_callback.h"

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
