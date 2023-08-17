/**
 * FLL - Level 0
 *
 * Project: Memory
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the memory project.
 */
#ifndef _TEST__F_memory_h
#define _TEST__F_memory_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/memory.h>

// Test includes.
#include "test-memory-adjust.h"
#include "test-memory-array_adjust.h"
#include "test-memory-array_append.h"
#include "test-memory-array_append_all.h"
#include "test-memory-array_decimate_by.h"
#include "test-memory-array_decrease_by.h"
#include "test-memory-array_increase.h"
#include "test-memory-array_increase_by.h"
#include "test-memory-array_resize.h"
#include "test-memory-arrays_adjust.h"
#include "test-memory-arrays_resize.h"
#include "test-memory-delete.h"
#include "test-memory-destroy.h"
#include "test-memory-new.h"
#include "test-memory-new_aligned.h"
#include "test-memory-resize.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A structure used for testing the memory array functions.
 */
typedef struct {
  int *array;
  f_number_unsigned_t used;
  f_number_unsigned_t size;
} test_memory_array_t;

#define test_memory_array_t_initialize { 0, 0, 0 }

/**
 * A structure used for testing the memory arrays functions.
 */
typedef struct {
  test_memory_array_t *array;
  f_number_unsigned_t used;
  f_number_unsigned_t size;
} test_memory_arrays_t;

#define test_memory_arrays_t_initialize { 0, 0, 0 }

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

/**
 * Callback for passing to f_memory_arrays functions.
 */
extern f_status_t test_memory_array_callback(const f_number_unsigned_t start, const f_number_unsigned_t size, void * const array);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _TEST__F_memory_h
