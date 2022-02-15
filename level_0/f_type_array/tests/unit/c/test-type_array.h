/**
 * FLL - Level 0
 *
 * Project: Type
 * API Version: 0.5
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
#include <fll/level_0/memory.h>
#include <fll/level_0/type_array.h>

// test includes.
#include "test-type_array-array_lengths_adjust.h"
#include "test-type_array-array_lengths_append.h"
#include "test-type_array-array_lengths_decimate_by.h"
#include "test-type_array-array_lengths_decrease_by.h"
#include "test-type_array-array_lengths_increase.h"
#include "test-type_array-array_lengths_increase_by.h"
#include "test-type_array-array_lengths_resize.h"
#include "test-type_array-array_lengthss_adjust.h"
#include "test-type_array-array_lengthss_append.h"
#include "test-type_array-array_lengthss_decimate_by.h"
#include "test-type_array-array_lengthss_decrease_by.h"
#include "test-type_array-array_lengthss_increase.h"
#include "test-type_array-array_lengthss_increase_by.h"
#include "test-type_array-array_lengthss_resize.h"
#include "test-type_array-cells_adjust.h"
#include "test-type_array-cells_append.h"
#include "test-type_array-cells_decimate_by.h"
#include "test-type_array-cells_decrease_by.h"
#include "test-type_array-cells_increase.h"
#include "test-type_array-cells_increase_by.h"
#include "test-type_array-cells_resize.h"
#include "test-type_array-cellss_adjust.h"
#include "test-type_array-cellss_append.h"
#include "test-type_array-cellss_decimate_by.h"
#include "test-type_array-cellss_decrease_by.h"
#include "test-type_array-cellss_increase.h"
#include "test-type_array-cellss_increase_by.h"
#include "test-type_array-cellss_resize.h"
#include "test-type_array-fll_ids_adjust.h"
#include "test-type_array-fll_ids_append.h"
#include "test-type_array-fll_ids_decimate_by.h"
#include "test-type_array-fll_ids_decrease_by.h"
#include "test-type_array-fll_ids_increase.h"
#include "test-type_array-fll_ids_increase_by.h"
#include "test-type_array-fll_ids_resize.h"
#include "test-type_array-fll_idss_adjust.h"
#include "test-type_array-fll_idss_append.h"
#include "test-type_array-fll_idss_decimate_by.h"
#include "test-type_array-fll_idss_decrease_by.h"
#include "test-type_array-fll_idss_increase.h"
#include "test-type_array-fll_idss_increase_by.h"
#include "test-type_array-fll_idss_resize.h"
#include "test-type_array-int8s_adjust.h"
#include "test-type_array-int8s_append.h"
#include "test-type_array-int8s_decimate_by.h"
#include "test-type_array-int8s_decrease_by.h"
#include "test-type_array-int8s_increase.h"
#include "test-type_array-int8s_increase_by.h"
#include "test-type_array-int8s_resize.h"
#include "test-type_array-int8ss_adjust.h"
#include "test-type_array-int8ss_append.h"
#include "test-type_array-int8ss_decimate_by.h"
#include "test-type_array-int8ss_decrease_by.h"
#include "test-type_array-int8ss_increase.h"
#include "test-type_array-int8ss_increase_by.h"
#include "test-type_array-int8ss_resize.h"
#include "test-type_array-int16s_adjust.h"
#include "test-type_array-int16s_append.h"
#include "test-type_array-int16s_decimate_by.h"
#include "test-type_array-int16s_decrease_by.h"
#include "test-type_array-int16s_increase.h"
#include "test-type_array-int16s_increase_by.h"
#include "test-type_array-int16s_resize.h"
#include "test-type_array-int16ss_adjust.h"
#include "test-type_array-int16ss_append.h"
#include "test-type_array-int16ss_decimate_by.h"
#include "test-type_array-int16ss_decrease_by.h"
#include "test-type_array-int16ss_increase.h"
#include "test-type_array-int16ss_increase_by.h"
#include "test-type_array-int16ss_resize.h"
#include "test-type_array-int32s_adjust.h"
#include "test-type_array-int32s_append.h"
#include "test-type_array-int32s_decimate_by.h"
#include "test-type_array-int32s_decrease_by.h"
#include "test-type_array-int32s_increase.h"
#include "test-type_array-int32s_increase_by.h"
#include "test-type_array-int32s_resize.h"
#include "test-type_array-int32ss_adjust.h"
#include "test-type_array-int32ss_append.h"
#include "test-type_array-int32ss_decimate_by.h"
#include "test-type_array-int32ss_decrease_by.h"
#include "test-type_array-int32ss_increase.h"
#include "test-type_array-int32ss_increase_by.h"
#include "test-type_array-int32ss_resize.h"
#include "test-type_array-int64s_adjust.h"
#include "test-type_array-int64s_append.h"
#include "test-type_array-int64s_decimate_by.h"
#include "test-type_array-int64s_decrease_by.h"
#include "test-type_array-int64s_increase.h"
#include "test-type_array-int64s_increase_by.h"
#include "test-type_array-int64s_resize.h"
#include "test-type_array-int64ss_adjust.h"
#include "test-type_array-int64ss_append.h"
#include "test-type_array-int64ss_decimate_by.h"
#include "test-type_array-int64ss_decrease_by.h"
#include "test-type_array-int64ss_increase.h"
#include "test-type_array-int64ss_increase_by.h"
#include "test-type_array-int64ss_resize.h"
#include "test-type_array-int128s_adjust.h"
#include "test-type_array-int128s_append.h"
#include "test-type_array-int128s_decimate_by.h"
#include "test-type_array-int128s_decrease_by.h"
#include "test-type_array-int128s_increase.h"
#include "test-type_array-int128s_increase_by.h"
#include "test-type_array-int128s_resize.h"
#include "test-type_array-int128ss_adjust.h"
#include "test-type_array-int128ss_append.h"
#include "test-type_array-int128ss_decimate_by.h"
#include "test-type_array-int128ss_decrease_by.h"
#include "test-type_array-int128ss_increase.h"
#include "test-type_array-int128ss_increase_by.h"
#include "test-type_array-int128ss_resize.h"
#include "test-type_array-states_adjust.h"
#include "test-type_array-states_append.h"
#include "test-type_array-states_decimate_by.h"
#include "test-type_array-states_decrease_by.h"
#include "test-type_array-states_increase.h"
#include "test-type_array-states_increase_by.h"
#include "test-type_array-states_resize.h"
#include "test-type_array-statess_adjust.h"
#include "test-type_array-statess_append.h"
#include "test-type_array-statess_decimate_by.h"
#include "test-type_array-statess_decrease_by.h"
#include "test-type_array-statess_increase.h"
#include "test-type_array-statess_increase_by.h"
#include "test-type_array-statess_resize.h"
#include "test-type_array-statuss_adjust.h"
#include "test-type_array-statuss_append.h"
#include "test-type_array-statuss_decimate_by.h"
#include "test-type_array-statuss_decrease_by.h"
#include "test-type_array-statuss_increase.h"
#include "test-type_array-statuss_increase_by.h"
#include "test-type_array-statuss_resize.h"
#include "test-type_array-statusss_adjust.h"
#include "test-type_array-statusss_append.h"
#include "test-type_array-statusss_decimate_by.h"
#include "test-type_array-statusss_decrease_by.h"
#include "test-type_array-statusss_increase.h"
#include "test-type_array-statusss_increase_by.h"
#include "test-type_array-statusss_resize.h"
#include "test-type_array-uint8s_adjust.h"
#include "test-type_array-uint8s_append.h"
#include "test-type_array-uint8s_decimate_by.h"
#include "test-type_array-uint8s_decrease_by.h"
#include "test-type_array-uint8s_increase.h"
#include "test-type_array-uint8s_increase_by.h"
#include "test-type_array-uint8s_resize.h"
#include "test-type_array-uint8ss_adjust.h"
#include "test-type_array-uint8ss_append.h"
#include "test-type_array-uint8ss_decimate_by.h"
#include "test-type_array-uint8ss_decrease_by.h"
#include "test-type_array-uint8ss_increase.h"
#include "test-type_array-uint8ss_increase_by.h"
#include "test-type_array-uint8ss_resize.h"
#include "test-type_array-uint16s_adjust.h"
#include "test-type_array-uint16s_append.h"
#include "test-type_array-uint16s_decimate_by.h"
#include "test-type_array-uint16s_decrease_by.h"
#include "test-type_array-uint16s_increase.h"
#include "test-type_array-uint16s_increase_by.h"
#include "test-type_array-uint16s_resize.h"
#include "test-type_array-uint16ss_adjust.h"
#include "test-type_array-uint16ss_append.h"
#include "test-type_array-uint16ss_decimate_by.h"
#include "test-type_array-uint16ss_decrease_by.h"
#include "test-type_array-uint16ss_increase.h"
#include "test-type_array-uint16ss_increase_by.h"
#include "test-type_array-uint16ss_resize.h"
#include "test-type_array-uint32s_adjust.h"
#include "test-type_array-uint32s_append.h"
#include "test-type_array-uint32s_decimate_by.h"
#include "test-type_array-uint32s_decrease_by.h"
#include "test-type_array-uint32s_increase.h"
#include "test-type_array-uint32s_increase_by.h"
#include "test-type_array-uint32s_resize.h"
#include "test-type_array-uint32ss_adjust.h"
#include "test-type_array-uint32ss_append.h"
#include "test-type_array-uint32ss_decimate_by.h"
#include "test-type_array-uint32ss_decrease_by.h"
#include "test-type_array-uint32ss_increase.h"
#include "test-type_array-uint32ss_increase_by.h"
#include "test-type_array-uint32ss_resize.h"
#include "test-type_array-uint64s_adjust.h"
#include "test-type_array-uint64s_append.h"
#include "test-type_array-uint64s_decimate_by.h"
#include "test-type_array-uint64s_decrease_by.h"
#include "test-type_array-uint64s_increase.h"
#include "test-type_array-uint64s_increase_by.h"
#include "test-type_array-uint64s_resize.h"
#include "test-type_array-uint64ss_adjust.h"
#include "test-type_array-uint64ss_append.h"
#include "test-type_array-uint64ss_decimate_by.h"
#include "test-type_array-uint64ss_decrease_by.h"
#include "test-type_array-uint64ss_increase.h"
#include "test-type_array-uint64ss_increase_by.h"
#include "test-type_array-uint64ss_resize.h"
#include "test-type_array-uint128s_adjust.h"
#include "test-type_array-uint128s_append.h"
#include "test-type_array-uint128s_decimate_by.h"
#include "test-type_array-uint128s_decrease_by.h"
#include "test-type_array-uint128s_increase.h"
#include "test-type_array-uint128s_increase_by.h"
#include "test-type_array-uint128s_resize.h"
#include "test-type_array-uint128ss_adjust.h"
#include "test-type_array-uint128ss_append.h"
#include "test-type_array-uint128ss_decimate_by.h"
#include "test-type_array-uint128ss_decrease_by.h"
#include "test-type_array-uint128ss_increase.h"
#include "test-type_array-uint128ss_increase_by.h"
#include "test-type_array-uint128ss_resize.h"

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
