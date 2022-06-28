#include "test-thread.h"

#ifdef __cplusplus
extern "C" {
#endif

int setup(void **state) {

  return 0;
}

int setdown(void **state) {

  errno = 0;

  return 0;
}

int main(void) {

  const struct CMUnitTest tests[] = {
    cmocka_unit_test(test__f_thread_attributes_decimate_by__returns_data_not),
    cmocka_unit_test(test__f_thread_attributes_decrease_by__returns_data_not),
    cmocka_unit_test(test__f_thread_attributes_increase__returns_data_not),
    cmocka_unit_test(test__f_thread_attributes_increase_by__returns_data_not),

    cmocka_unit_test(test__f_thread_attributes_adjust__works),
    cmocka_unit_test(test__f_thread_attributes_decimate_by__works),
    cmocka_unit_test(test__f_thread_attributes_decrease_by__works),
    cmocka_unit_test(test__f_thread_attributes_increase__works),
    cmocka_unit_test(test__f_thread_attributes_increase_by__works),
    cmocka_unit_test(test__f_thread_attributes_resize__works),

    cmocka_unit_test(test__f_thread_barrier_attributes_decimate_by__returns_data_not),
    cmocka_unit_test(test__f_thread_barrier_attributes_decrease_by__returns_data_not),
    cmocka_unit_test(test__f_thread_barrier_attributes_increase__returns_data_not),
    cmocka_unit_test(test__f_thread_barrier_attributes_increase_by__returns_data_not),

    cmocka_unit_test(test__f_thread_barrier_attributes_adjust__works),
    cmocka_unit_test(test__f_thread_barrier_attributes_decimate_by__works),
    cmocka_unit_test(test__f_thread_barrier_attributes_decrease_by__works),
    cmocka_unit_test(test__f_thread_barrier_attributes_increase__works),
    cmocka_unit_test(test__f_thread_barrier_attributes_increase_by__works),
    cmocka_unit_test(test__f_thread_barrier_attributes_resize__works),

    cmocka_unit_test(test__f_thread_barriers_decimate_by__returns_data_not),
    cmocka_unit_test(test__f_thread_barriers_decrease_by__returns_data_not),
    cmocka_unit_test(test__f_thread_barriers_increase__returns_data_not),
    cmocka_unit_test(test__f_thread_barriers_increase_by__returns_data_not),

    cmocka_unit_test(test__f_thread_barriers_adjust__works),
    cmocka_unit_test(test__f_thread_barriers_decimate_by__works),
    cmocka_unit_test(test__f_thread_barriers_decrease_by__works),
    cmocka_unit_test(test__f_thread_barriers_increase__works),
    cmocka_unit_test(test__f_thread_barriers_increase_by__works),
    cmocka_unit_test(test__f_thread_barriers_resize__works),

    cmocka_unit_test(test__f_thread_condition_attributes_decimate_by__returns_data_not),
    cmocka_unit_test(test__f_thread_condition_attributes_decrease_by__returns_data_not),
    cmocka_unit_test(test__f_thread_condition_attributes_increase__returns_data_not),
    cmocka_unit_test(test__f_thread_condition_attributes_increase_by__returns_data_not),

    cmocka_unit_test(test__f_thread_condition_attributes_adjust__works),
    cmocka_unit_test(test__f_thread_condition_attributes_decimate_by__works),
    cmocka_unit_test(test__f_thread_condition_attributes_decrease_by__works),
    cmocka_unit_test(test__f_thread_condition_attributes_increase__works),
    cmocka_unit_test(test__f_thread_condition_attributes_increase_by__works),
    cmocka_unit_test(test__f_thread_condition_attributes_resize__works),

    cmocka_unit_test(test__f_thread_conditions_decimate_by__returns_data_not),
    cmocka_unit_test(test__f_thread_conditions_decrease_by__returns_data_not),
    cmocka_unit_test(test__f_thread_conditions_increase__returns_data_not),
    cmocka_unit_test(test__f_thread_conditions_increase_by__returns_data_not),

    cmocka_unit_test(test__f_thread_conditions_adjust__works),
    cmocka_unit_test(test__f_thread_conditions_decimate_by__works),
    cmocka_unit_test(test__f_thread_conditions_decrease_by__works),
    cmocka_unit_test(test__f_thread_conditions_increase__works),
    cmocka_unit_test(test__f_thread_conditions_increase_by__works),
    cmocka_unit_test(test__f_thread_conditions_resize__works),

    cmocka_unit_test(test__f_thread_ids_decimate_by__returns_data_not),
    cmocka_unit_test(test__f_thread_ids_decrease_by__returns_data_not),
    cmocka_unit_test(test__f_thread_ids_increase__returns_data_not),
    cmocka_unit_test(test__f_thread_ids_increase_by__returns_data_not),

    cmocka_unit_test(test__f_thread_ids_adjust__works),
    cmocka_unit_test(test__f_thread_ids_decimate_by__works),
    cmocka_unit_test(test__f_thread_ids_decrease_by__works),
    cmocka_unit_test(test__f_thread_ids_increase__works),
    cmocka_unit_test(test__f_thread_ids_increase_by__works),
    cmocka_unit_test(test__f_thread_ids_resize__works),

    cmocka_unit_test(test__f_thread_keys_decimate_by__returns_data_not),
    cmocka_unit_test(test__f_thread_keys_decrease_by__returns_data_not),
    cmocka_unit_test(test__f_thread_keys_increase__returns_data_not),
    cmocka_unit_test(test__f_thread_keys_increase_by__returns_data_not),

    cmocka_unit_test(test__f_thread_keys_adjust__works),
    cmocka_unit_test(test__f_thread_keys_decimate_by__works),
    cmocka_unit_test(test__f_thread_keys_decrease_by__works),
    cmocka_unit_test(test__f_thread_keys_increase__works),
    cmocka_unit_test(test__f_thread_keys_increase_by__works),
    cmocka_unit_test(test__f_thread_keys_resize__works),

    cmocka_unit_test(test__f_thread_lock_attributes_decimate_by__returns_data_not),
    cmocka_unit_test(test__f_thread_lock_attributes_decrease_by__returns_data_not),
    cmocka_unit_test(test__f_thread_lock_attributes_increase__returns_data_not),
    cmocka_unit_test(test__f_thread_lock_attributes_increase_by__returns_data_not),

    cmocka_unit_test(test__f_thread_lock_attributes_adjust__works),
    cmocka_unit_test(test__f_thread_lock_attributes_decimate_by__works),
    cmocka_unit_test(test__f_thread_lock_attributes_decrease_by__works),
    cmocka_unit_test(test__f_thread_lock_attributes_increase__works),
    cmocka_unit_test(test__f_thread_lock_attributes_increase_by__works),
    cmocka_unit_test(test__f_thread_lock_attributes_resize__works),

    cmocka_unit_test(test__f_thread_locks_decimate_by__returns_data_not),
    cmocka_unit_test(test__f_thread_locks_decrease_by__returns_data_not),
    cmocka_unit_test(test__f_thread_locks_increase__returns_data_not),
    cmocka_unit_test(test__f_thread_locks_increase_by__returns_data_not),

    cmocka_unit_test(test__f_thread_locks_adjust__works),
    cmocka_unit_test(test__f_thread_locks_decimate_by__works),
    cmocka_unit_test(test__f_thread_locks_decrease_by__works),
    cmocka_unit_test(test__f_thread_locks_increase__works),
    cmocka_unit_test(test__f_thread_locks_increase_by__works),
    cmocka_unit_test(test__f_thread_locks_resize__works),

    cmocka_unit_test(test__f_thread_mutex_attributes_decimate_by__returns_data_not),
    cmocka_unit_test(test__f_thread_mutex_attributes_decrease_by__returns_data_not),
    cmocka_unit_test(test__f_thread_mutex_attributes_increase__returns_data_not),
    cmocka_unit_test(test__f_thread_mutex_attributes_increase_by__returns_data_not),

    cmocka_unit_test(test__f_thread_mutex_attributes_adjust__works),
    cmocka_unit_test(test__f_thread_mutex_attributes_decimate_by__works),
    cmocka_unit_test(test__f_thread_mutex_attributes_decrease_by__works),
    cmocka_unit_test(test__f_thread_mutex_attributes_increase__works),
    cmocka_unit_test(test__f_thread_mutex_attributes_increase_by__works),
    cmocka_unit_test(test__f_thread_mutex_attributes_resize__works),

    cmocka_unit_test(test__f_thread_mutexs_decimate_by__returns_data_not),
    cmocka_unit_test(test__f_thread_mutexs_decrease_by__returns_data_not),
    cmocka_unit_test(test__f_thread_mutexs_increase__returns_data_not),
    cmocka_unit_test(test__f_thread_mutexs_increase_by__returns_data_not),

    cmocka_unit_test(test__f_thread_mutexs_adjust__works),
    cmocka_unit_test(test__f_thread_mutexs_decimate_by__works),
    cmocka_unit_test(test__f_thread_mutexs_decrease_by__works),
    cmocka_unit_test(test__f_thread_mutexs_increase__works),
    cmocka_unit_test(test__f_thread_mutexs_increase_by__works),
    cmocka_unit_test(test__f_thread_mutexs_resize__works),

    cmocka_unit_test(test__f_thread_onces_decimate_by__returns_data_not),
    cmocka_unit_test(test__f_thread_onces_decrease_by__returns_data_not),
    cmocka_unit_test(test__f_thread_onces_increase__returns_data_not),
    cmocka_unit_test(test__f_thread_onces_increase_by__returns_data_not),

    cmocka_unit_test(test__f_thread_onces_adjust__works),
    cmocka_unit_test(test__f_thread_onces_decimate_by__works),
    cmocka_unit_test(test__f_thread_onces_decrease_by__works),
    cmocka_unit_test(test__f_thread_onces_increase__works),
    cmocka_unit_test(test__f_thread_onces_increase_by__works),
    cmocka_unit_test(test__f_thread_onces_resize__works),

    cmocka_unit_test(test__f_thread_semaphores_decimate_by__returns_data_not),
    cmocka_unit_test(test__f_thread_semaphores_decrease_by__returns_data_not),
    cmocka_unit_test(test__f_thread_semaphores_increase__returns_data_not),
    cmocka_unit_test(test__f_thread_semaphores_increase_by__returns_data_not),

    cmocka_unit_test(test__f_thread_semaphores_adjust__works),
    cmocka_unit_test(test__f_thread_semaphores_decimate_by__works),
    cmocka_unit_test(test__f_thread_semaphores_decrease_by__works),
    cmocka_unit_test(test__f_thread_semaphores_increase__works),
    cmocka_unit_test(test__f_thread_semaphores_increase_by__works),
    cmocka_unit_test(test__f_thread_semaphores_resize__works),

    cmocka_unit_test(test__f_thread_sets_decimate_by__returns_data_not),
    cmocka_unit_test(test__f_thread_sets_decrease_by__returns_data_not),
    cmocka_unit_test(test__f_thread_sets_increase__returns_data_not),
    cmocka_unit_test(test__f_thread_sets_increase_by__returns_data_not),

    cmocka_unit_test(test__f_thread_sets_adjust__works),
    cmocka_unit_test(test__f_thread_sets_decimate_by__works),
    cmocka_unit_test(test__f_thread_sets_decrease_by__works),
    cmocka_unit_test(test__f_thread_sets_increase__works),
    cmocka_unit_test(test__f_thread_sets_increase_by__works),
    cmocka_unit_test(test__f_thread_sets_resize__works),

    cmocka_unit_test(test__f_thread_spins_decimate_by__returns_data_not),
    cmocka_unit_test(test__f_thread_spins_decrease_by__returns_data_not),
    cmocka_unit_test(test__f_thread_spins_increase__returns_data_not),
    cmocka_unit_test(test__f_thread_spins_increase_by__returns_data_not),

    cmocka_unit_test(test__f_thread_spins_adjust__works),
    cmocka_unit_test(test__f_thread_spins_decimate_by__works),
    cmocka_unit_test(test__f_thread_spins_decrease_by__works),
    cmocka_unit_test(test__f_thread_spins_increase__works),
    cmocka_unit_test(test__f_thread_spins_increase_by__works),
    cmocka_unit_test(test__f_thread_spins_resize__works),

    cmocka_unit_test(test__f_thread_at_fork__fails),
    cmocka_unit_test(test__f_thread_at_fork__works),

    cmocka_unit_test(test__f_thread_attribute_affinity_get__fails),
    cmocka_unit_test(test__f_thread_attribute_affinity_get__works),

    cmocka_unit_test(test__f_thread_attribute_affinity_set__fails),
    cmocka_unit_test(test__f_thread_attribute_affinity_set__works),

    cmocka_unit_test(test__f_thread_attribute_condition_clock_get__fails),
    cmocka_unit_test(test__f_thread_attribute_condition_clock_get__works),

    cmocka_unit_test(test__f_thread_attribute_condition_clock_set__fails),
    cmocka_unit_test(test__f_thread_attribute_condition_clock_set__works),

    cmocka_unit_test(test__f_thread_attribute_condition_shared_get__fails),
    cmocka_unit_test(test__f_thread_attribute_condition_shared_get__works),

    cmocka_unit_test(test__f_thread_attribute_condition_shared_set__fails),
    cmocka_unit_test(test__f_thread_attribute_condition_shared_set__works),

    cmocka_unit_test(test__f_thread_attribute_create__fails),
    cmocka_unit_test(test__f_thread_attribute_create__works),

    cmocka_unit_test(test__f_thread_attribute_default_get__fails),
    cmocka_unit_test(test__f_thread_attribute_default_get__works),

    cmocka_unit_test(test__f_thread_attribute_default_set__fails),
    cmocka_unit_test(test__f_thread_attribute_default_set__works),

    cmocka_unit_test(test__f_thread_attribute_delete__fails),
    cmocka_unit_test(test__f_thread_attribute_delete__works),

    cmocka_unit_test(test__f_thread_attribute_detach_get__fails),
    cmocka_unit_test(test__f_thread_attribute_detach_get__works),

    cmocka_unit_test(test__f_thread_attribute_detach_set__fails),
    cmocka_unit_test(test__f_thread_attribute_detach_set__works),

    cmocka_unit_test(test__f_thread_attribute_guard_get__fails),
    cmocka_unit_test(test__f_thread_attribute_guard_get__works),

    cmocka_unit_test(test__f_thread_attribute_guard_set__fails),
    cmocka_unit_test(test__f_thread_attribute_guard_set__works),

    cmocka_unit_test(test__f_thread_attribute_scheduler_inherit_get__fails),
    cmocka_unit_test(test__f_thread_attribute_scheduler_inherit_get__works),

    cmocka_unit_test(test__f_thread_attribute_scheduler_inherit_set__fails),
    cmocka_unit_test(test__f_thread_attribute_scheduler_inherit_set__works),

    cmocka_unit_test(test__f_thread_attribute_scheduler_parameter_get__fails),
    cmocka_unit_test(test__f_thread_attribute_scheduler_parameter_get__works),

    cmocka_unit_test(test__f_thread_attribute_scheduler_parameter_set__fails),
    cmocka_unit_test(test__f_thread_attribute_scheduler_parameter_set__works),

    cmocka_unit_test(test__f_thread_attribute_scheduler_policy_get__fails),
    cmocka_unit_test(test__f_thread_attribute_scheduler_policy_get__works),

    cmocka_unit_test(test__f_thread_attribute_scheduler_policy_set__fails),
    cmocka_unit_test(test__f_thread_attribute_scheduler_policy_set__works),

    cmocka_unit_test(test__f_thread_attribute_scope_get__fails),
    cmocka_unit_test(test__f_thread_attribute_scope_get__works),

    cmocka_unit_test(test__f_thread_attribute_scope_set__fails),
    cmocka_unit_test(test__f_thread_attribute_scope_set__works),

    cmocka_unit_test(test__f_thread_attribute_stack_get__fails),
    cmocka_unit_test(test__f_thread_attribute_stack_get__works),

    cmocka_unit_test(test__f_thread_attribute_stack_set__fails),
    cmocka_unit_test(test__f_thread_attribute_stack_set__works),

    cmocka_unit_test(test__f_thread_attribute_stack_size_get__fails),
    cmocka_unit_test(test__f_thread_attribute_stack_size_get__works),

    cmocka_unit_test(test__f_thread_attribute_stack_size_set__fails),
    cmocka_unit_test(test__f_thread_attribute_stack_size_set__works),

    cmocka_unit_test(test__f_thread_barrier_attribute_create__fails),
    cmocka_unit_test(test__f_thread_barrier_attribute_create__works),

    cmocka_unit_test(test__f_thread_barrier_attribute_delete__fails),
    cmocka_unit_test(test__f_thread_barrier_attribute_delete__works),

    cmocka_unit_test(test__f_thread_barrier_attribute_shared_get__fails),
    cmocka_unit_test(test__f_thread_barrier_attribute_shared_get__works),

    cmocka_unit_test(test__f_thread_barrier_attribute_shared_set__fails),
    cmocka_unit_test(test__f_thread_barrier_attribute_shared_set__works),

    cmocka_unit_test(test__f_thread_barrier_create__fails),
    cmocka_unit_test(test__f_thread_barrier_create__works),

    cmocka_unit_test(test__f_thread_barrier_delete__fails),
    cmocka_unit_test(test__f_thread_barrier_delete__works),

    cmocka_unit_test(test__f_thread_barrier_wait__works),

    #ifndef _di_level_0_parameter_checking_
      cmocka_unit_test(test__f_thread_attributes_adjust__parameter_checking),
      cmocka_unit_test(test__f_thread_attributes_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_thread_attributes_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_thread_attributes_increase__parameter_checking),
      cmocka_unit_test(test__f_thread_attributes_increase_by__parameter_checking),
      cmocka_unit_test(test__f_thread_attributes_resize__parameter_checking),

      cmocka_unit_test(test__f_thread_barrier_attributes_adjust__parameter_checking),
      cmocka_unit_test(test__f_thread_barrier_attributes_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_thread_barrier_attributes_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_thread_barrier_attributes_increase__parameter_checking),
      cmocka_unit_test(test__f_thread_barrier_attributes_increase_by__parameter_checking),
      cmocka_unit_test(test__f_thread_barrier_attributes_resize__parameter_checking),

      cmocka_unit_test(test__f_thread_barriers_adjust__parameter_checking),
      cmocka_unit_test(test__f_thread_barriers_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_thread_barriers_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_thread_barriers_increase__parameter_checking),
      cmocka_unit_test(test__f_thread_barriers_increase_by__parameter_checking),
      cmocka_unit_test(test__f_thread_barriers_resize__parameter_checking),

      cmocka_unit_test(test__f_thread_condition_attributes_adjust__parameter_checking),
      cmocka_unit_test(test__f_thread_condition_attributes_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_thread_condition_attributes_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_thread_condition_attributes_increase__parameter_checking),
      cmocka_unit_test(test__f_thread_condition_attributes_increase_by__parameter_checking),
      cmocka_unit_test(test__f_thread_condition_attributes_resize__parameter_checking),

      cmocka_unit_test(test__f_thread_conditions_adjust__parameter_checking),
      cmocka_unit_test(test__f_thread_conditions_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_thread_conditions_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_thread_conditions_increase__parameter_checking),
      cmocka_unit_test(test__f_thread_conditions_increase_by__parameter_checking),
      cmocka_unit_test(test__f_thread_conditions_resize__parameter_checking),

      cmocka_unit_test(test__f_thread_ids_adjust__parameter_checking),
      cmocka_unit_test(test__f_thread_ids_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_thread_ids_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_thread_ids_increase__parameter_checking),
      cmocka_unit_test(test__f_thread_ids_increase_by__parameter_checking),
      cmocka_unit_test(test__f_thread_ids_resize__parameter_checking),

      cmocka_unit_test(test__f_thread_keys_adjust__parameter_checking),
      cmocka_unit_test(test__f_thread_keys_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_thread_keys_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_thread_keys_increase__parameter_checking),
      cmocka_unit_test(test__f_thread_keys_increase_by__parameter_checking),
      cmocka_unit_test(test__f_thread_keys_resize__parameter_checking),

      cmocka_unit_test(test__f_thread_lock_attributes_adjust__parameter_checking),
      cmocka_unit_test(test__f_thread_lock_attributes_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_thread_lock_attributes_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_thread_lock_attributes_increase__parameter_checking),
      cmocka_unit_test(test__f_thread_lock_attributes_increase_by__parameter_checking),
      cmocka_unit_test(test__f_thread_lock_attributes_resize__parameter_checking),

      cmocka_unit_test(test__f_thread_locks_adjust__parameter_checking),
      cmocka_unit_test(test__f_thread_locks_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_thread_locks_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_thread_locks_increase__parameter_checking),
      cmocka_unit_test(test__f_thread_locks_increase_by__parameter_checking),
      cmocka_unit_test(test__f_thread_locks_resize__parameter_checking),

      cmocka_unit_test(test__f_thread_mutex_attributes_adjust__parameter_checking),
      cmocka_unit_test(test__f_thread_mutex_attributes_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_thread_mutex_attributes_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_thread_mutex_attributes_increase__parameter_checking),
      cmocka_unit_test(test__f_thread_mutex_attributes_increase_by__parameter_checking),
      cmocka_unit_test(test__f_thread_mutex_attributes_resize__parameter_checking),

      cmocka_unit_test(test__f_thread_mutexs_adjust__parameter_checking),
      cmocka_unit_test(test__f_thread_mutexs_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_thread_mutexs_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_thread_mutexs_increase__parameter_checking),
      cmocka_unit_test(test__f_thread_mutexs_increase_by__parameter_checking),
      cmocka_unit_test(test__f_thread_mutexs_resize__parameter_checking),

      cmocka_unit_test(test__f_thread_onces_adjust__parameter_checking),
      cmocka_unit_test(test__f_thread_onces_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_thread_onces_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_thread_onces_increase__parameter_checking),
      cmocka_unit_test(test__f_thread_onces_increase_by__parameter_checking),
      cmocka_unit_test(test__f_thread_onces_resize__parameter_checking),

      cmocka_unit_test(test__f_thread_semaphores_adjust__parameter_checking),
      cmocka_unit_test(test__f_thread_semaphores_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_thread_semaphores_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_thread_semaphores_increase__parameter_checking),
      cmocka_unit_test(test__f_thread_semaphores_increase_by__parameter_checking),
      cmocka_unit_test(test__f_thread_semaphores_resize__parameter_checking),

      cmocka_unit_test(test__f_thread_sets_adjust__parameter_checking),
      cmocka_unit_test(test__f_thread_sets_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_thread_sets_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_thread_sets_increase__parameter_checking),
      cmocka_unit_test(test__f_thread_sets_increase_by__parameter_checking),
      cmocka_unit_test(test__f_thread_sets_resize__parameter_checking),

      cmocka_unit_test(test__f_thread_spins_adjust__parameter_checking),
      cmocka_unit_test(test__f_thread_spins_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_thread_spins_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_thread_spins_increase__parameter_checking),
      cmocka_unit_test(test__f_thread_spins_increase_by__parameter_checking),
      cmocka_unit_test(test__f_thread_spins_resize__parameter_checking),

      cmocka_unit_test(test__f_thread_at_fork__parameter_checking),

      cmocka_unit_test(test__f_thread_attribute_affinity_get__parameter_checking),
      cmocka_unit_test(test__f_thread_attribute_affinity_set__parameter_checking),

      cmocka_unit_test(test__f_thread_attribute_condition_clock_get__parameter_checking),
      cmocka_unit_test(test__f_thread_attribute_condition_clock_set__parameter_checking),

      cmocka_unit_test(test__f_thread_attribute_condition_shared_get__parameter_checking),
      cmocka_unit_test(test__f_thread_attribute_condition_shared_set__parameter_checking),

      cmocka_unit_test(test__f_thread_attribute_create__parameter_checking),

      cmocka_unit_test(test__f_thread_attribute_default_get__parameter_checking),
      cmocka_unit_test(test__f_thread_attribute_default_set__parameter_checking),

      cmocka_unit_test(test__f_thread_attribute_delete__parameter_checking),

      cmocka_unit_test(test__f_thread_attribute_detach_get__parameter_checking),
      cmocka_unit_test(test__f_thread_attribute_detach_set__parameter_checking),

      cmocka_unit_test(test__f_thread_attribute_guard_get__parameter_checking),
      cmocka_unit_test(test__f_thread_attribute_guard_set__parameter_checking),

      cmocka_unit_test(test__f_thread_attribute_scheduler_inherit_get__parameter_checking),
      cmocka_unit_test(test__f_thread_attribute_scheduler_inherit_set__parameter_checking),

      cmocka_unit_test(test__f_thread_attribute_scheduler_parameter_get__parameter_checking),
      cmocka_unit_test(test__f_thread_attribute_scheduler_parameter_set__parameter_checking),

      cmocka_unit_test(test__f_thread_attribute_scheduler_policy_get__parameter_checking),
      cmocka_unit_test(test__f_thread_attribute_scheduler_policy_set__parameter_checking),

      cmocka_unit_test(test__f_thread_attribute_scope_get__parameter_checking),
      cmocka_unit_test(test__f_thread_attribute_scope_set__parameter_checking),

      cmocka_unit_test(test__f_thread_attribute_stack_get__parameter_checking),
      cmocka_unit_test(test__f_thread_attribute_stack_set__parameter_checking),

      cmocka_unit_test(test__f_thread_attribute_stack_size_get__parameter_checking),
      cmocka_unit_test(test__f_thread_attribute_stack_size_set__parameter_checking),

      cmocka_unit_test(test__f_thread_barrier_attribute_create__parameter_checking),

      cmocka_unit_test(test__f_thread_barrier_attribute_delete__parameter_checking),

      cmocka_unit_test(test__f_thread_barrier_attribute_shared_get__parameter_checking),

      cmocka_unit_test(test__f_thread_barrier_attribute_shared_set__parameter_checking),

      cmocka_unit_test(test__f_thread_barrier_create__parameter_checking),

      cmocka_unit_test(test__f_thread_barrier_delete__parameter_checking),

      cmocka_unit_test(test__f_thread_barrier_wait__parameter_checking),
    #endif // _di_level_0_parameter_checking_

    // f_thread_user_set() doesn't use parameter checking.
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif
