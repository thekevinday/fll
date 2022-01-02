#include "../controller.h"
#include "../private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_task_action_delete_simple_
  void controller_task_action_delete_simple(controller_task_action_t *action) {

    f_string_dynamic_resize(0, &action->help);
    f_string_dynamics_resize(0, &action->parameters);
  }
#endif // _di_controller_task_action_delete_simple_

#ifndef _di_controller_task_actions_delete_simple_
  void controller_task_actions_delete_simple(controller_task_actions_t *actions) {

    actions->used = actions->size;

    while (actions->used) {
      controller_task_action_delete_simple(&actions->array[--actions->used]);
    } // while

    f_memory_delete(actions->size, sizeof(controller_task_action_t), (void **) & actions->array);
    actions->size = 0;
  }
#endif // _di_controller_task_actions_delete_simple_

#ifndef _di_controller_task_actions_increase_by_
  f_status_t controller_task_actions_increase_by(const f_array_length_t amount, controller_task_actions_t *actions) {

    if (actions->used + amount > actions->size) {
      if (actions->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      const f_status_t status = f_memory_resize(actions->size, actions->used + amount, sizeof(controller_task_action_t), (void **) & actions->array);

      if (F_status_is_error_not(status)) {
        actions->size = actions->used + amount;
      }

      return status;
    }

    return F_data_not;
  }
#endif // _di_controller_task_actions_increase_by_

#ifndef _di_controller_task_delete_simple_
  void controller_task_delete_simple(controller_task_t * const task) {

    f_string_dynamic_resize(0, &task->alias);
    f_string_dynamic_resize(0, &task->help);
    f_string_dynamic_resize(0, &task->name);
    f_string_dynamic_resize(0, &task->path);
    f_string_dynamic_resize(0, &task->script);

    f_string_maps_resize(0, &task->arguments);
    f_string_maps_resize(0, &task->defines);
    f_string_maps_resize(0, &task->parameters);

    f_string_dynamics_resize(0, &task->environment);

    macro_f_int32s_t_delete_simple(task->affinity)
    macro_f_control_group_t_delete_simple(task->cgroup)
    macro_f_int32s_t_delete_simple(task->groups)
    macro_f_limit_sets_t_delete_simple(task->limits)

    if (task->capability) {
      f_capability_delete(&task->capability);
    }

    controller_task_actions_delete_simple(&task->actions);
  }
#endif // _di_controller_task_delete_simple_

#ifndef _di_controller_tasks_delete_simple_
  void controller_tasks_delete_simple(controller_tasks_t *tasks) {

    controller_tasks_resize(0, tasks);
  }
#endif // _di_controller_tasks_delete_simple_

#ifndef _di_controller_tasks_increase_
  f_status_t controller_tasks_increase(controller_tasks_t *tasks) {

    if (tasks->used + 1 > tasks->size) {
      f_array_length_t size = tasks->used + controller_common_allocation_small_d;

      if (size > F_array_length_t_size_d) {
        if (tasks->used + 1 > F_array_length_t_size_d) {
          return F_status_set_error(F_array_too_large);
        }

        size = F_array_length_t_size_d;
      }

      return controller_tasks_resize(size, tasks);
    }

    return F_data_not;
  }
#endif // _di_controller_tasks_increase_

#ifndef _di_controller_tasks_resize_
  f_status_t controller_tasks_resize(const f_array_length_t length, controller_tasks_t *tasks) {

    for (f_array_length_t i = length; i < tasks->size; ++i) {
      controller_task_delete_simple(&tasks->array[i]);
    } // for

    const f_status_t status = f_memory_resize(tasks->size, length, sizeof(controller_task_t), (void **) & tasks->array);

    if (F_status_is_error_not(status)) {
      tasks->size = length;

      if (tasks->used > tasks->size) {
        tasks->used = length;
      }
    }

    return status;
  }
#endif // _di_controller_tasks_resize_

#ifdef __cplusplus
} // extern "C"
#endif
