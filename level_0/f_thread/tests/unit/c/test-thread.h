/**
 * FLL - Level 0
 *
 * Project: Thread
 * API Version: 0.6
 * Licenses: lgpl-2.1-or-later
 *
 * Test the thread project.
 */
#ifndef _TEST__F_thread_h
#define _TEST__F_thread_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <stdio.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/thread.h>

// Mock includes.
#include "mock-thread.h"

// Test includes.
#include "test-thread-attributes_adjust.h"
#include "test-thread-attributes_decimate_by.h"
#include "test-thread-attributes_decrease_by.h"
#include "test-thread-attributes_increase.h"
#include "test-thread-attributes_increase_by.h"
#include "test-thread-attributes_resize.h"
#include "test-thread-barriers_adjust.h"
#include "test-thread-barriers_decimate_by.h"
#include "test-thread-barriers_decrease_by.h"
#include "test-thread-barriers_increase.h"
#include "test-thread-barriers_increase_by.h"
#include "test-thread-barriers_resize.h"
#include "test-thread-barrier_attributes_adjust.h"
#include "test-thread-barrier_attributes_decimate_by.h"
#include "test-thread-barrier_attributes_decrease_by.h"
#include "test-thread-barrier_attributes_increase.h"
#include "test-thread-barrier_attributes_increase_by.h"
#include "test-thread-barrier_attributes_resize.h"
#include "test-thread-conditions_adjust.h"
#include "test-thread-conditions_decimate_by.h"
#include "test-thread-conditions_decrease_by.h"
#include "test-thread-conditions_increase.h"
#include "test-thread-conditions_increase_by.h"
#include "test-thread-conditions_resize.h"
#include "test-thread-condition_attributes_adjust.h"
#include "test-thread-condition_attributes_decimate_by.h"
#include "test-thread-condition_attributes_decrease_by.h"
#include "test-thread-condition_attributes_increase.h"
#include "test-thread-condition_attributes_increase_by.h"
#include "test-thread-condition_attributes_resize.h"
#include "test-thread-ids_adjust.h"
#include "test-thread-ids_decimate_by.h"
#include "test-thread-ids_decrease_by.h"
#include "test-thread-ids_increase.h"
#include "test-thread-ids_increase_by.h"
#include "test-thread-ids_resize.h"
#include "test-thread-keys_adjust.h"
#include "test-thread-keys_decimate_by.h"
#include "test-thread-keys_decrease_by.h"
#include "test-thread-keys_increase.h"
#include "test-thread-keys_increase_by.h"
#include "test-thread-keys_resize.h"
#include "test-thread-locks_adjust.h"
#include "test-thread-locks_decimate_by.h"
#include "test-thread-locks_decrease_by.h"
#include "test-thread-locks_increase.h"
#include "test-thread-locks_increase_by.h"
#include "test-thread-locks_resize.h"
#include "test-thread-lock_attributes_adjust.h"
#include "test-thread-lock_attributes_decimate_by.h"
#include "test-thread-lock_attributes_decrease_by.h"
#include "test-thread-lock_attributes_increase.h"
#include "test-thread-lock_attributes_increase_by.h"
#include "test-thread-lock_attributes_resize.h"
#include "test-thread-mutexs_adjust.h"
#include "test-thread-mutexs_decimate_by.h"
#include "test-thread-mutexs_decrease_by.h"
#include "test-thread-mutexs_increase.h"
#include "test-thread-mutexs_increase_by.h"
#include "test-thread-mutexs_resize.h"
#include "test-thread-mutex_attributes_adjust.h"
#include "test-thread-mutex_attributes_decimate_by.h"
#include "test-thread-mutex_attributes_decrease_by.h"
#include "test-thread-mutex_attributes_increase.h"
#include "test-thread-mutex_attributes_increase_by.h"
#include "test-thread-mutex_attributes_resize.h"
#include "test-thread-onces_adjust.h"
#include "test-thread-onces_decimate_by.h"
#include "test-thread-onces_decrease_by.h"
#include "test-thread-onces_increase.h"
#include "test-thread-onces_increase_by.h"
#include "test-thread-onces_resize.h"
#include "test-thread-semaphores_adjust.h"
#include "test-thread-semaphores_decimate_by.h"
#include "test-thread-semaphores_decrease_by.h"
#include "test-thread-semaphores_increase.h"
#include "test-thread-semaphores_increase_by.h"
#include "test-thread-semaphores_resize.h"
#include "test-thread-sets_adjust.h"
#include "test-thread-sets_decimate_by.h"
#include "test-thread-sets_decrease_by.h"
#include "test-thread-sets_increase.h"
#include "test-thread-sets_increase_by.h"
#include "test-thread-sets_resize.h"
#include "test-thread-spins_adjust.h"
#include "test-thread-spins_decimate_by.h"
#include "test-thread-spins_decrease_by.h"
#include "test-thread-spins_increase.h"
#include "test-thread-spins_increase_by.h"
#include "test-thread-spins_resize.h"

#include "test-thread-at_fork.h"
#include "test-thread-attribute_affinity_get.h"
#include "test-thread-attribute_affinity_set.h"
#include "test-thread-attribute_concurrency_get.h"
#include "test-thread-attribute_concurrency_set.h"
#include "test-thread-attribute_create.h"
#include "test-thread-attribute_default_get.h"
#include "test-thread-attribute_default_set.h"
#include "test-thread-attribute_delete.h"
#include "test-thread-attribute_detach_get.h"
#include "test-thread-attribute_detach_set.h"
#include "test-thread-attribute_guard_get.h"
#include "test-thread-attribute_guard_set.h"
#include "test-thread-attribute_scheduler_inherit_get.h"
#include "test-thread-attribute_scheduler_inherit_set.h"
#include "test-thread-attribute_scheduler_parameter_get.h"
#include "test-thread-attribute_scheduler_parameter_set.h"
#include "test-thread-attribute_scheduler_policy_get.h"
#include "test-thread-attribute_scheduler_policy_set.h"
#include "test-thread-attribute_scope_get.h"
#include "test-thread-attribute_scope_set.h"
#include "test-thread-attribute_stack_get.h"
#include "test-thread-attribute_stack_set.h"
#include "test-thread-attribute_stack_size_get.h"
#include "test-thread-attribute_stack_size_set.h"
#include "test-thread-barrier_attribute_create.h"
#include "test-thread-barrier_attribute_delete.h"
#include "test-thread-barrier_attribute_shared_get.h"
#include "test-thread-barrier_attribute_shared_set.h"
#include "test-thread-barrier_create.h"
#include "test-thread-barrier_delete.h"
#include "test-thread-barrier_wait.h"
#include "test-thread-caller.h"
#include "test-thread-cancel.h"
#include "test-thread-cancel_state_set.h"
#include "test-thread-cancel_test.h"
#include "test-thread-cancel_type_set.h"
#include "test-thread-clock_get_id.h"
#include "test-thread-compare.h"
#include "test-thread-condition_attribute_clock_get.h"
#include "test-thread-condition_attribute_clock_set.h"
#include "test-thread-condition_attribute_create.h"
#include "test-thread-condition_attribute_delete.h"
#include "test-thread-condition_attribute_shared_get.h"
#include "test-thread-condition_attribute_shared_set.h"
#include "test-thread-condition_create.h"
#include "test-thread-condition_delete.h"
#include "test-thread-condition_signal.h"
#include "test-thread-condition_signal_all.h"
#include "test-thread-condition_wait.h"
#include "test-thread-condition_wait_timed.h"
#include "test-thread-create.h"
#include "test-thread-detach.h"
#include "test-thread-exit.h"
#include "test-thread-join.h"
#include "test-thread-join_try.h"
#include "test-thread-join_timed.h"
#include "test-thread-key_create.h"
#include "test-thread-key_delete.h"
#include "test-thread-key_get.h"
#include "test-thread-key_set.h"
#include "test-thread-lock_attribute_create.h"
#include "test-thread-lock_attribute_delete.h"
#include "test-thread-lock_attribute_shared_get.h"
#include "test-thread-lock_attribute_shared_set.h"
#include "test-thread-lock_create.h"
#include "test-thread-lock_delete.h"
#include "test-thread-lock_read.h"
#include "test-thread-lock_read_timed.h"
#include "test-thread-lock_read_try.h"
#include "test-thread-lock_write.h"
#include "test-thread-lock_write_timed.h"
#include "test-thread-lock_write_try.h"
#include "test-thread-mutex_attribute_create.h"
#include "test-thread-mutex_attribute_delete.h"
#include "test-thread-mutex_attribute_priority_ceiling_get.h"
#include "test-thread-mutex_attribute_priority_ceiling_set.h"
#include "test-thread-mutex_attribute_shared_get.h"
#include "test-thread-mutex_attribute_shared_set.h"
#include "test-thread-mutex_attribute_type_get.h"
#include "test-thread-mutex_attribute_type_set.h"
#include "test-thread-mutex_attribute_protocol_get.h"
#include "test-thread-mutex_attribute_protocol_set.h"
#include "test-thread-mutex_create.h"
#include "test-thread-mutex_delete.h"
#include "test-thread-mutex_lock.h"
#include "test-thread-mutex_lock_timed.h"
#include "test-thread-mutex_lock_try.h"
#include "test-thread-mutex_priority_ceiling_get.h"
#include "test-thread-mutex_priority_ceiling_set.h"
#include "test-thread-once.h"
#include "test-thread-scheduler_parameter_get.h"
#include "test-thread-scheduler_parameter_set.h"
#include "test-thread-scheduler_priority_set.h"
#include "test-thread-semaphore_create.h"
#include "test-thread-semaphore_delete.h"
#include "test-thread-semaphore_file_close.h"
#include "test-thread-semaphore_file_delete.h"
#include "test-thread-semaphore_file_open.h"
#include "test-thread-semaphore_lock.h"
#include "test-thread-semaphore_lock_timed.h"
#include "test-thread-semaphore_lock_try.h"
#include "test-thread-semaphore_unlock.h"
#include "test-thread-semaphore_value_get.h"
#include "test-thread-signal_mask.h"
#include "test-thread-signal_queue.h"
#include "test-thread-signal_write.h"
#include "test-thread-spin_create.h"
#include "test-thread-spin_delete.h"
#include "test-thread-spin_lock.h"
#include "test-thread-spin_lock_try.h"
#include "test-thread-spin_unlock.h"

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

#endif // _TEST__F_thread_h
