/**
 * FLL - Level 0
 *
 * Project: IKI
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Test the iki project.
 */
#ifndef _TEST__F_iki_h
#define _TEST__F_iki_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/iki.h>

// Mock includes.
//#include "mock-iki.h"

// Test includes.
#include "test-iki-content_is.h"
#include "test-iki-content_partial_is.h"
#include "test-iki-datas_adjust.h"
#include "test-iki-datas_append.h"
#include "test-iki-datas_append_all.h"
#include "test-iki-datas_decimate_by.h"
#include "test-iki-datas_decrease_by.h"
#include "test-iki-datas_increase.h"
#include "test-iki-datas_increase_by.h"
#include "test-iki-datas_resize.h"
#include "test-iki-datass_adjust.h"
#include "test-iki-datass_append.h"
#include "test-iki-datass_append_all.h"
#include "test-iki-datass_decimate_by.h"
#include "test-iki-datass_decrease_by.h"
#include "test-iki-datass_increase.h"
#include "test-iki-datass_increase_by.h"
#include "test-iki-datass_resize.h"
#include "test-iki-object_is.h"
#include "test-iki-object_partial_is.h"
#include "test-iki-read.h"

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

#endif // _TEST__F_iki_h
