#include "thread.h"
#include "private-thread.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_thread_attributes_decrease_) || !defined(_di_f_thread_attributes_decrease_by_) || !defined(_di_f_thread_attributes_delete_)
  f_return_status private_f_thread_attributes_delete(f_thread_attributes_t *attributes) {
    f_status_t status = F_none;

    f_macro_thread_attributes_t_delete(status, (*attributes));

    return status;
  }
#endif // !defined(_di_f_thread_attributes_decrease_) || !defined(_di_f_thread_attributes_decrease_by_) || !defined(_di_f_thread_attributes_delete_)

#if !defined(_di_f_thread_attributes_decrease_) || !defined(_di_f_thread_attributes_decrease_by_) || !defined(_di_f_thread_attributes_increase_) || !defined(_di_f_thread_attributes_increase_by_)
  f_return_status private_f_thread_attributes_resize(const f_array_length_t length, f_thread_attributes_t *attributes) {
    f_status_t status = F_none;

    f_macro_thread_attributes_t_resize(status, (*attributes), length);

    return status;
  }
#endif // !defined(_di_f_thread_attributes_decrease_) || !defined(_di_f_thread_attributes_decrease_by_) || !defined(_di_f_thread_attributes_increase_) || !defined(_di_f_thread_attributes_increase_by_)

#if !defined(_di_f_thread_conditions_decrease_) || !defined(_di_f_thread_conditions_decrease_by_) || !defined(_di_f_thread_conditions_delete_)
  f_return_status private_f_thread_conditions_delete(f_thread_conditions_t *conditions) {
    f_status_t status = F_none;

    f_macro_thread_conditions_t_delete(status, (*conditions));

    return status;
  }
#endif // !defined(_di_f_thread_conditions_decrease_) || !defined(_di_f_thread_conditions_decrease_by_) || !defined(_di_f_thread_conditions_delete_)

#if !defined(_di_f_thread_conditions_decrease_) || !defined(_di_f_thread_conditions_decrease_by_) || !defined(_di_f_thread_conditions_increase_) || !defined(_di_f_thread_conditions_increase_by_)
  f_return_status private_f_thread_conditions_resize(const f_array_length_t length, f_thread_conditions_t *conditions) {
    f_status_t status = F_none;

    f_macro_thread_conditions_t_resize(status, (*conditions), length);

    return status;
  }
#endif // !defined(_di_f_thread_conditions_decrease_) || !defined(_di_f_thread_conditions_decrease_by_) || !defined(_di_f_thread_conditions_increase_) || !defined(_di_f_thread_conditions_increase_by_)

#if !defined(_di_f_thread_ids_decrease_) || !defined(_di_f_thread_ids_decrease_by_) || !defined(_di_f_thread_ids_delete_)
  f_return_status private_f_thread_ids_delete(f_thread_ids_t *ids) {
    f_status_t status = F_none;

    f_macro_thread_ids_t_delete(status, (*ids));

    return status;
  }
#endif // !defined(_di_f_thread_ids_decrease_) || !defined(_di_f_thread_ids_decrease_by_) || !defined(_di_f_thread_ids_delete_)

#if !defined(_di_f_thread_ids_decrease_) || !defined(_di_f_thread_ids_decrease_by_) || !defined(_di_f_thread_ids_increase_) || !defined(_di_f_thread_ids_increase_by_)
  f_return_status private_f_thread_ids_resize(const f_array_length_t length, f_thread_ids_t *ids) {
    f_status_t status = F_none;

    f_macro_thread_ids_t_resize(status, (*ids), length);

    return status;
  }
#endif // !defined(_di_f_thread_ids_decrease_) || !defined(_di_f_thread_ids_decrease_by_) || !defined(_di_f_thread_ids_increase_) || !defined(_di_f_thread_ids_increase_by_)

#if !defined(_di_f_thread_keys_decrease_) || !defined(_di_f_thread_keys_decrease_by_) || !defined(_di_f_thread_keys_delete_)
  f_return_status private_f_thread_keys_delete(f_thread_keys_t *keys) {
    f_status_t status = F_none;

    f_macro_thread_keys_t_delete(status, (*keys));

    return status;
  }
#endif // !defined(_di_f_thread_keys_decrease_) || !defined(_di_f_thread_keys_decrease_by_) || !defined(_di_f_thread_keys_delete_)

#if !defined(_di_f_thread_keys_decrease_) || !defined(_di_f_thread_keys_decrease_by_) || !defined(_di_f_thread_keys_increase_) || !defined(_di_f_thread_keys_increase_by_)
  f_return_status private_f_thread_keys_resize(const f_array_length_t length, f_thread_keys_t *keys) {
    f_status_t status = F_none;

    f_macro_thread_keys_t_resize(status, (*keys), length);

    return status;
  }
#endif // !defined(_di_f_thread_keys_decrease_) || !defined(_di_f_thread_keys_decrease_by_) || !defined(_di_f_thread_keys_increase_) || !defined(_di_f_thread_keys_increase_by_)

#if !defined(_di_f_thread_locks_decrease_) || !defined(_di_f_thread_locks_decrease_by_) || !defined(_di_f_thread_locks_delete_)
  f_return_status private_f_thread_locks_delete(f_thread_locks_t *locks) {
    f_status_t status = F_none;

    f_macro_thread_locks_t_delete(status, (*locks));

    return status;
  }
#endif // !defined(_di_f_thread_locks_decrease_) || !defined(_di_f_thread_locks_decrease_by_) || !defined(_di_f_thread_locks_delete_)

#if !defined(_di_f_thread_locks_decrease_) || !defined(_di_f_thread_locks_decrease_by_) || !defined(_di_f_thread_locks_increase_) || !defined(_di_f_thread_locks_increase_by_)
  f_return_status private_f_thread_locks_resize(const f_array_length_t length, f_thread_locks_t *locks) {
    f_status_t status = F_none;

    f_macro_thread_locks_t_resize(status, (*locks), length);

    return status;
  }
#endif // !defined(_di_f_thread_locks_decrease_) || !defined(_di_f_thread_locks_decrease_by_) || !defined(_di_f_thread_locks_increase_) || !defined(_di_f_thread_locks_increase_by_)

#if !defined(_di_f_thread_mutexs_decrease_) || !defined(_di_f_thread_mutexs_decrease_by_) || !defined(_di_f_thread_mutexs_delete_)
  f_return_status private_f_thread_mutexs_delete(f_thread_mutexs_t *mutexs) {
    f_status_t status = F_none;

    f_macro_thread_mutexs_t_delete(status, (*mutexs));

    return status;
  }
#endif // !defined(_di_f_thread_mutexs_decrease_) || !defined(_di_f_thread_mutexs_decrease_by_) || !defined(_di_f_thread_mutexs_delete_)

#if !defined(_di_f_thread_mutexs_decrease_) || !defined(_di_f_thread_mutexs_decrease_by_) || !defined(_di_f_thread_mutexs_increase_) || !defined(_di_f_thread_mutexs_increase_by_)
  f_return_status private_f_thread_mutexs_resize(const f_array_length_t length, f_thread_mutexs_t *mutexs) {
    f_status_t status = F_none;

    f_macro_thread_mutexs_t_resize(status, (*mutexs), length);

    return status;
  }
#endif // !defined(_di_f_thread_mutexs_decrease_) || !defined(_di_f_thread_mutexs_decrease_by_) || !defined(_di_f_thread_mutexs_increase_) || !defined(_di_f_thread_mutexs_increase_by_)

#if !defined(_di_f_thread_mutex_attributes_decrease_) || !defined(_di_f_thread_mutex_attributes_decrease_by_) || !defined(_di_f_thread_mutex_attributes_delete_)
  f_return_status private_f_thread_mutex_attributes_delete(f_thread_mutex_attributes_t *mutex_attributes) {
    f_status_t status = F_none;

    f_macro_thread_mutex_attributes_t_delete(status, (*mutex_attributes));

    return status;
  }
#endif // !defined(_di_f_thread_mutex_attributes_decrease_) || !defined(_di_f_thread_mutex_attributes_decrease_by_) || !defined(_di_f_thread_mutex_attributes_delete_)

#if !defined(_di_f_thread_mutex_attributes_decrease_) || !defined(_di_f_thread_mutex_attributes_decrease_by_) || !defined(_di_f_thread_mutex_attributes_increase_) || !defined(_di_f_thread_mutex_attributes_increase_by_)
  f_return_status private_f_thread_mutex_attributes_resize(const f_array_length_t length, f_thread_mutex_attributes_t *mutex_attributes) {
    f_status_t status = F_none;

    f_macro_thread_mutex_attributes_t_resize(status, (*mutex_attributes), length);

    return status;
  }
#endif // !defined(_di_f_thread_mutex_attributes_decrease_) || !defined(_di_f_thread_mutex_attributes_decrease_by_) || !defined(_di_f_thread_mutex_attributes_increase_) || !defined(_di_f_thread_mutex_attributes_increase_by_)

#if !defined(_di_f_thread_onces_decrease_) || !defined(_di_f_thread_onces_decrease_by_) || !defined(_di_f_thread_onces_delete_)
  f_return_status private_f_thread_onces_delete(f_thread_onces_t *onces) {
    f_status_t status = F_none;

    f_macro_thread_onces_t_delete(status, (*onces));

    return status;
  }
#endif // !defined(_di_f_thread_onces_decrease_) || !defined(_di_f_thread_onces_decrease_by_) || !defined(_di_f_thread_onces_delete_)

#if !defined(_di_f_thread_onces_decrease_) || !defined(_di_f_thread_onces_decrease_by_) || !defined(_di_f_thread_onces_increase_) || !defined(_di_f_thread_onces_increase_by_)
  f_return_status private_f_thread_onces_resize(const f_array_length_t length, f_thread_onces_t *onces) {
    f_status_t status = F_none;

    f_macro_thread_onces_t_resize(status, (*onces), length);

    return status;
  }
#endif // !defined(_di_f_thread_onces_decrease_) || !defined(_di_f_thread_onces_decrease_by_) || !defined(_di_f_thread_onces_increase_) || !defined(_di_f_thread_onces_increase_by_)

#if !defined(_di_f_thread_sets_decrease_) || !defined(_di_f_thread_sets_decrease_by_) || !defined(_di_f_thread_sets_delete_)
  f_return_status private_f_thread_sets_delete(f_thread_sets_t *sets) {
    f_status_t status = F_none;

    f_macro_thread_sets_t_delete(status, (*sets));

    return status;
  }
#endif // !defined(_di_f_thread_sets_decrease_) || !defined(_di_f_thread_sets_decrease_by_) || !defined(_di_f_thread_sets_delete_)

#if !defined(_di_f_thread_sets_decrease_) || !defined(_di_f_thread_sets_decrease_by_) || !defined(_di_f_thread_sets_increase_) || !defined(_di_f_thread_sets_increase_by_)
  f_return_status private_f_thread_sets_resize(const f_array_length_t length, f_thread_sets_t *sets) {
    f_status_t status = F_none;

    f_macro_thread_sets_t_resize(status, (*sets), length);

    return status;
  }
#endif // !defined(_di_f_thread_sets_decrease_) || !defined(_di_f_thread_sets_decrease_by_) || !defined(_di_f_thread_sets_increase_) || !defined(_di_f_thread_sets_increase_by_)

#ifdef __cplusplus
} // extern "C"
#endif
