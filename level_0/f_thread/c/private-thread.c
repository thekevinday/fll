#include "thread.h"
#include "private-thread.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_thread_sets_decrease_) || !defined(_di_f_thread_sets_decrease_by_) || !defined(_di_f_thread_sets_delete_)
  f_return_status private_f_thread_sets_delete(f_thread_sets_t *thread_sets) {
    f_status_t status = F_none;

    f_macro_thread_sets_t_delete(status, (*thread_sets));

    return status;
  }
#endif // !defined(_di_f_thread_sets_decrease_) || !defined(_di_f_thread_sets_decrease_by_) || !defined(_di_f_thread_sets_delete_)

#if !defined(_di_f_thread_sets_decrease_) || !defined(_di_f_thread_sets_decrease_by_) || !defined(_di_f_thread_sets_increase_) || !defined(_di_f_thread_sets_increase_by_)
  f_return_status private_f_thread_sets_resize(const f_array_length_t length, f_thread_sets_t *thread_sets) {
    f_status_t status = F_none;

    f_macro_thread_sets_t_resize(status, (*thread_sets), length);

    return status;
  }
#endif // !defined(_di_f_thread_sets_decrease_) || !defined(_di_f_thread_sets_decrease_by_) || !defined(_di_f_thread_sets_increase_) || !defined(_di_f_thread_sets_increase_by_)


#ifdef __cplusplus
} // extern "C"
#endif
