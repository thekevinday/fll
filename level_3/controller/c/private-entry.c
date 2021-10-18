#include "controller.h"
#include "private-common.h"
#include "private-controller.h"
#include "private-entry.h"
#include "private-thread.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_entry_action_parameters_print_
  void controller_entry_action_parameters_print(FILE * const stream, const controller_entry_action_t action) {

    for (f_array_length_t index = 0; ;) {

      f_print_dynamic_safely(action.parameters.array[index], stream);

      ++index;

      if (index == action.parameters.used) break;

      f_print_terminated(f_string_space_s, stream);
    } // for
  }
#endif // _di_controller_entry_action_parameters_print_

#ifndef _di_controller_entry_action_type_is_rule_
  f_status_t controller_entry_action_type_is_rule(uint8_t type) {

    switch (type) {
      case controller_entry_action_type_freeze:
      case controller_entry_action_type_kill:
      case controller_entry_action_type_pause:
      case controller_entry_action_type_reload:
      case controller_entry_action_type_restart:
      case controller_entry_action_type_resume:
      case controller_entry_action_type_start:
      case controller_entry_action_type_stop:
      case controller_entry_action_type_thaw:
        return F_true;
    }

    return F_false;
  }
#endif // _di_controller_entry_action_type_is_rule_

#ifndef _di_controller_entry_action_type_name_
  f_string_static_t controller_entry_action_type_name(const uint8_t type) {

    f_string_static_t buffer = f_string_static_t_initialize;

    switch (type) {
      case controller_entry_action_type_consider:
        buffer.string = controller_consider_s;
        buffer.used = controller_consider_s_length;
        break;

      case controller_entry_action_type_execute:
        buffer.string = controller_execute_s;
        buffer.used = controller_execute_s_length;
        break;

      case controller_entry_action_type_failsafe:
        buffer.string = controller_failsafe_s;
        buffer.used = controller_failsafe_s_length;
        break;

      case controller_entry_action_type_freeze:
        buffer.string = controller_freeze_s;
        buffer.used = controller_freeze_s_length;
        break;

      case controller_entry_action_type_item:
        buffer.string = controller_item_s;
        buffer.used = controller_item_s_length;
        break;

      case controller_entry_action_type_kill:
        buffer.string = controller_kill_s;
        buffer.used = controller_kill_s_length;
        break;

      case controller_entry_action_type_pause:
        buffer.string = controller_pause_s;
        buffer.used = controller_pause_s_length;
        break;

      case controller_entry_action_type_ready:
        buffer.string = controller_ready_s;
        buffer.used = controller_ready_s_length;
        break;

      case controller_entry_action_type_reload:
        buffer.string = controller_reload_s;
        buffer.used = controller_reload_s_length;
        break;

      case controller_entry_action_type_restart:
        buffer.string = controller_restart_s;
        buffer.used = controller_restart_s_length;
        break;

      case controller_entry_action_type_resume:
        buffer.string = controller_resume_s;
        buffer.used = controller_resume_s_length;
        break;

      case controller_entry_action_type_start:
        buffer.string = controller_start_s;
        buffer.used = controller_start_s_length;
        break;

      case controller_entry_action_type_stop:
        buffer.string = controller_stop_s;
        buffer.used = controller_stop_s_length;
        break;

      case controller_entry_action_type_thaw:
        buffer.string = controller_thaw_s;
        buffer.used = controller_thaw_s_length;
        break;

      case controller_entry_action_type_timeout:
        buffer.string = controller_timeout_s;
        buffer.used = controller_timeout_s_length;
        break;
    }

    buffer.size = buffer.used;

    return buffer;
  }
#endif // _di_controller_entry_action_type_name_

#ifndef _di_controller_entry_action_type_to_rule_action_type_
  uint8_t controller_entry_action_type_to_rule_action_type(uint8_t type) {

    switch (type) {
      case controller_entry_action_type_freeze:
        return controller_rule_action_type_freeze;

      case controller_entry_action_type_kill:
        return controller_rule_action_type_kill;

      case controller_entry_action_type_pause:
        return controller_rule_action_type_pause;

      case controller_entry_action_type_reload:
        return controller_rule_action_type_reload;

      case controller_entry_action_type_restart:
        return controller_rule_action_type_restart;

      case controller_entry_action_type_resume:
        return controller_rule_action_type_resume;

      case controller_entry_action_type_start:
        return controller_rule_action_type_start;

      case controller_entry_action_type_stop:
        return controller_rule_action_type_stop;

      case controller_entry_action_type_thaw:
        return controller_rule_action_type_thaw;
    }

    return 0;
  }
#endif // _di_controller_entry_action_type_to_rule_action_type_

#ifndef _di_controller_entry_actions_increase_by_
  f_status_t controller_entry_actions_increase_by(const f_array_length_t amount, controller_entry_actions_t *actions) {

    if (actions->used + amount > actions->size) {
      if (actions->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      const f_status_t status = f_memory_resize(actions->size, actions->used + amount, sizeof(controller_entry_action_t), (void **) & actions->array);

      if (F_status_is_error_not(status)) {
        actions->size = actions->used + amount;
      }

      return status;
    }

    return F_data_not;
  }
#endif // _di_controller_entry_actions_increase_by_

#ifndef _di_controller_entry_actions_read_
  f_status_t controller_entry_actions_read(const bool is_entry, const f_string_range_t content_range, controller_global_t global, controller_cache_t *cache, controller_entry_actions_t *actions) {
    f_status_t status = F_none;
    f_status_t status_action = F_none;

    actions->used = 0;

    cache->object_actions.used = cache->object_actions.size;

    while (cache->object_actions.used) {

      cache->object_actions.array[--cache->object_actions.used].start = 1;
      cache->object_actions.array[cache->object_actions.used].stop = 0;
    } // while

    cache->content_actions.used = cache->content_actions.size;

    while (cache->content_actions.used) {
      cache->content_actions.array[--cache->content_actions.used].used = 0;
    } // while

    {
      controller_state_interrupt_t custom = macro_controller_state_interrupt_t_initialize(is_entry, global.thread);
      f_state_t state = macro_f_state_t_initialize(controller_common_allocation_large_d, controller_common_allocation_small_d, 0, &controller_thread_signal_state_fss, 0, (void *) &custom, 0);
      f_string_range_t range = content_range;

      status = fll_fss_extended_read(cache->buffer_file, state, &range, &cache->object_actions, &cache->content_actions, 0, 0, &cache->delimits, 0);
    }

    if (F_status_is_error(status)) {
      controller_entry_error_print(is_entry, global.main->error, cache->action, F_status_set_fine(status), "fll_fss_extended_read", F_true, global.thread);

      return status;
    }

    status = fl_fss_apply_delimit(cache->delimits, &cache->buffer_file);

    if (F_status_is_error(status)) {
      controller_entry_error_print(is_entry, global.main->error, cache->action, F_status_set_fine(status), "fl_fss_apply_delimit", F_true, global.thread);

      return status;
    }

    cache->delimits.used = 0;

    status = controller_entry_actions_increase_by(cache->object_actions.used, actions);

    if (F_status_is_error(status)) {
      controller_entry_error_print(is_entry, global.main->error, cache->action, F_status_set_fine(status), "controller_entry_actions_increase_by", F_true, global.thread);

      return status;
    }

    controller_entry_action_t *action = 0;

    f_array_length_t allocate = 0;
    f_array_length_t at_least = 0;
    f_array_length_t at_most = 0;

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    for (; i < cache->object_actions.used; ++i) {

      cache->action.line_action = 0;
      cache->action.name_action.used = 0;

      action = &actions->array[actions->used];
      action->type = 0;
      action->code = 0;
      action->line = 0;
      action->number = 0;
      action->status = F_known_not;
      action->parameters.used = 0;

      status = f_fss_count_lines(cache->buffer_file, cache->object_actions.array[i].start, &cache->action.line_action);

      if (F_status_is_error(status)) {
        controller_entry_error_print(is_entry, global.main->error, cache->action, F_status_set_fine(status), "f_fss_count_lines", F_true, global.thread);
        break;
      }

      action->line = ++cache->action.line_action;

      status = controller_dynamic_rip_nulless_terminated(cache->buffer_file, cache->object_actions.array[i], &cache->action.name_action);

      if (F_status_is_error(status)) {
        controller_entry_error_print(is_entry, global.main->error, cache->action, F_status_set_fine(status), "controller_dynamic_rip_nulless_terminated", F_true, global.thread);
        break;
      }

      if (fl_string_dynamic_compare_string(controller_consider_s, cache->action.name_action, controller_consider_s_length) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_consider;
      }
      else if (fl_string_dynamic_compare_string(controller_execute_s, cache->action.name_action, controller_execute_s_length) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_execute;
      }
      else if (fl_string_dynamic_compare_string(controller_failsafe_s, cache->action.name_action, controller_failsafe_s_length) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_failsafe;
      }
      else if (fl_string_dynamic_compare_string(controller_freeze_s, cache->action.name_action, controller_freeze_s_length) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_freeze;
      }
      else if (fl_string_dynamic_compare_string(controller_item_s, cache->action.name_action, controller_item_s_length) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_item;
      }
      else if (fl_string_dynamic_compare_string(controller_kill_s, cache->action.name_action, controller_kill_s_length) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_kill;
      }
      else if (fl_string_dynamic_compare_string(controller_pause_s, cache->action.name_action, controller_pause_s_length) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_pause;
      }
      else if (fl_string_dynamic_compare_string(controller_ready_s, cache->action.name_action, controller_ready_s_length) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_ready;
      }
      else if (fl_string_dynamic_compare_string(controller_reload_s, cache->action.name_action, controller_reload_s_length) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_reload;
      }
      else if (fl_string_dynamic_compare_string(controller_restart_s, cache->action.name_action, controller_restart_s_length) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_restart;
      }
      else if (fl_string_dynamic_compare_string(controller_resume_s, cache->action.name_action, controller_resume_s_length) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_resume;
      }
      else if (fl_string_dynamic_compare_string(controller_start_s, cache->action.name_action, controller_start_s_length) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_start;
      }
      else if (fl_string_dynamic_compare_string(controller_stop_s, cache->action.name_action, controller_stop_s_length) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_stop;
      }
      else if (fl_string_dynamic_compare_string(controller_thaw_s, cache->action.name_action, controller_thaw_s_length) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_thaw;
      }
      else if (fl_string_dynamic_compare_string(controller_timeout_s, cache->action.name_action, controller_timeout_s_length) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_timeout;
      }
      else {
        if (global.main->warning.verbosity == f_console_verbosity_debug) {
          controller_print_lock(global.main->warning.to, global.thread);

          fl_print_format("%c%[%SUnknown %s item action '%]", global.main->warning.to.stream, f_string_eol_s[0], global.main->warning.context, global.main->warning.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->warning.context);
          fl_print_format("%[%S%]", global.main->warning.to.stream, global.main->warning.notable, cache->action.name_action, global.main->warning.notable);
          fl_print_format("%['.%]%c", global.main->warning.to.stream, global.main->warning.context, global.main->warning.context, f_string_eol_s[0]);

          controller_entry_error_print_cache(is_entry, global.main->warning, cache->action);

          controller_print_unlock_flush(global.main->warning.to, global.thread);
        }

        continue;
      }

      if (action->type == controller_entry_action_type_consider || controller_entry_action_type_is_rule(action->type)) {
        allocate = cache->content_actions.array[i].used;
        at_least = 2;
        at_most = allocate;
      }
      else if (action->type == controller_entry_action_type_execute) {
        allocate = cache->content_actions.array[i].used;
        at_least = 1;
        at_most = allocate;
      }
      else if (action->type == controller_entry_action_type_failsafe || action->type == controller_entry_action_type_item) {
        allocate = 1;
        at_least = 1;
        at_most = 1;
      }
      else if (action->type == controller_entry_action_type_timeout) {
        allocate = 2;
        at_least = 2;
        at_most = 2;
      }
      else if (action->type == controller_entry_action_type_ready) {
        allocate = 1;
        at_least = 0;
        at_most = 1;
      }

      if (cache->content_actions.array[i].used < at_least || cache->content_actions.array[i].used > at_most) {
        action->status = F_status_set_error(F_parameter);

        if (global.main->error.verbosity != f_console_verbosity_quiet) {
          f_thread_mutex_lock(&global.thread->lock.print);

          flockfile(global.main->error.to.stream);

          fl_print_format("%c%[%SThe %s item action '%]", global.main->error.to.stream, f_string_eol_s[0], global.main->error.context, global.main->error.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->error.context);
          fl_print_format("%[%Q%]", global.main->error.to.stream, global.main->error.notable, cache->action.name_action, global.main->error.notable);
          fl_print_format("%[' requires ", global.main->error.to.stream, global.main->error.context);

          if (at_least == at_most) {
            f_print_terminated("exactly ", global.main->error.to.stream);
          }

          fl_print_format("%]%[%un%]", global.main->error.to.stream, global.main->error.context, global.main->error.notable, at_least, global.main->error.notable);

          if (action->type == controller_entry_action_type_consider || controller_entry_action_type_is_rule(action->type)) {
            fl_print_format("%[ or more parameters.%]%c", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s[0]);
          }
          else {
            if (at_least == at_most) {
              fl_print_format("%[ parameters.%]%c", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s[0]);
            }
            else {
              fl_print_format("%[ to %]", global.main->error.to.stream, global.main->error.context, global.main->error.context);
              fl_print_format("%[%un%]", global.main->error.to.stream, global.main->error.notable, at_most, global.main->error.notable);
              fl_print_format("%[ parameters.%]%c", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s[0]);
            }
          }

          funlockfile(global.main->error.to.stream);

          f_thread_mutex_unlock(&global.thread->lock.print);
        }
      }
      else {
        action->status = F_none;
      }

      if (F_status_is_error(action->status)) {
        if (F_status_is_error_not(status_action)) {
          status_action = action->status;
        }

        continue;
      }

      if (allocate) {
        status = f_string_dynamics_increase_by(allocate, &action->parameters);

        if (F_status_is_error(status)) {
          controller_entry_error_print(is_entry, global.main->error, cache->action, F_status_set_fine(status), "f_string_dynamics_increase_by", F_true, global.thread);

          action->status = status;

          if (F_status_is_error_not(status_action)) {
            status_action = status;
          }

          break;
        }

        for (j = 0; j < allocate && j < cache->content_actions.array[i].used; ++j) {

          action->parameters.array[j].used = 0;

          status = f_string_dynamic_partial_append_nulless(cache->buffer_file, cache->content_actions.array[i].array[j], &action->parameters.array[j]);

          if (F_status_is_error(status)) {
            controller_entry_error_print(is_entry, global.main->error, cache->action, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, global.thread);

            action->status = status;

            if (F_status_is_error_not(status_action)) {
              status_action = status;
            }

            break;
          }

          ++action->parameters.used;
        } // for

        if (F_status_is_error_not(action->status)) {
          if (action->type == controller_entry_action_type_consider || controller_entry_action_type_is_rule(action->type)) {
            if (action->parameters.array[0].used) {

              // force the path to be canonical (removing all '../' parts).
              status = fll_path_canonical(action->parameters.array[0].string, &cache->buffer_path);

              if (F_status_is_error(status)) {
                controller_entry_error_print(is_entry, global.main->error, cache->action, F_status_set_fine(status), "fll_path_canonical", F_true, global.thread);

                action->status = status;

                if (F_status_set_fine(status) == F_memory_not) {
                  status_action = status;
                  break;
                }

                if (F_status_is_error_not(status_action)) {
                  status_action = status;
                }
              }
            }
            else {
              action->status = F_status_set_error(F_parameter);

              if (F_status_is_error_not(status_action)) {
                status_action = action->status;
              }

              if (global.main->error.verbosity != f_console_verbosity_quiet) {
                fll_print_format("%c%[%SThe %s item action must not have an empty string for a path (the first parameter).%]%c", global.main->error.to.stream, f_string_eol_s[0], global.main->error.context, global.main->error.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->error.context, f_string_eol_s[0]);
              }
            }

            if (action->parameters.array[1].used) {
              cache->buffer_path.used = 0;

              status = f_file_name_base(action->parameters.array[1].string, action->parameters.array[1].used, &cache->buffer_path);

              if (F_status_is_error(status)) {
                controller_entry_error_print(is_entry, global.main->error, cache->action, F_status_set_fine(status), "f_file_name_base", F_true, global.thread);

                if (F_status_set_fine(status) == F_memory_not) {
                  status_action = status;
                  break;
                }

                action->status = status;

                if (F_status_is_error_not(status_action)) {
                  status_action = status;
                }
              }
              else {
                if (fl_string_dynamic_compare(action->parameters.array[1], cache->buffer_path) == F_equal_to_not) {

                  if (global.main->error.verbosity != f_console_verbosity_quiet) {
                    status = f_string_dynamic_terminate_after(&cache->buffer_path);

                    if (F_status_is_error(status)) {
                      controller_entry_error_print(is_entry, global.main->error, cache->action, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true, global.thread);

                      action->status = status;

                      if (F_status_set_fine(status) == F_memory_not) {
                        status_action = status;
                      }

                      break;
                    }

                    flockfile(global.main->error.to.stream);

                    fl_print_format("%c%[%SThe %s item action second parameter '%]", global.main->error.to.stream, f_string_eol_s[0], global.main->error.context, global.main->error.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->error.context);
                    fl_print_format("%[%Q%]", global.main->error.to.stream, global.main->error.notable, action->parameters.array[1], global.main->error.notable);
                    fl_print_format("%[' must be a base path name, such as '%]", global.main->error.to.stream, global.main->error.context, global.main->error.context);
                    fl_print_format("%[%Q%]", global.main->error.to.stream, global.main->error.notable, cache->buffer_path, global.main->error.notable);
                    fl_print_format("%['.%]", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s[0]);

                    funlockfile(global.main->error.to.stream);
                  }

                  action->status = F_status_set_error(F_parameter);

                  if (F_status_is_error_not(status_action)) {
                    status_action = action->status;
                  }
                }
              }
            }
            else {
              action->status = F_status_set_error(F_parameter);

              if (F_status_is_error_not(status_action)) {
                status_action = action->status;
              }

              if (global.main->error.verbosity != f_console_verbosity_quiet) {
                fll_print_format("%c%[%SThe %s item action must not have an empty string for a rule name (the second parameter).%]", global.main->error.to.stream, f_string_eol_s[0], global.main->error.context, global.main->error.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->error.context, f_string_eol_s[0]);
              }
            }

            for (j = 2; j < action->parameters.used; ++j) {

              if (fl_string_dynamic_compare_string(controller_asynchronous_s, action->parameters.array[j], controller_asynchronous_s_length) == F_equal_to) {
                action->code |= controller_entry_rule_code_asynchronous_d;
              }
              else if (fl_string_dynamic_compare_string(controller_require_s, action->parameters.array[j], controller_require_s_length) == F_equal_to) {
                action->code |= controller_entry_rule_code_require_d;
              }
              else if (fl_string_dynamic_compare_string(controller_wait_s, action->parameters.array[j], controller_wait_s_length) == F_equal_to) {
                action->code |= controller_entry_rule_code_wait_d;
              }
              else {
                if (action->status == F_none) {
                  action->status = F_status_set_error(F_supported_not);

                  if (F_status_is_error_not(status_action)) {
                    status_action = action->status;
                  }
                }

                if (global.main->error.verbosity != f_console_verbosity_quiet) {
                  flockfile(global.main->error.to.stream);

                  fl_print_format("%c%[%SThe %s item action third parameter (and beyond) must be one of '%]", global.main->error.to.stream, f_string_eol_s[0], global.main->error.context, global.main->error.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->error.context);
                  fl_print_format("%[%s%]", global.main->error.to.stream, global.main->error.notable, controller_asynchronous_s, global.main->error.notable);
                  fl_print_format("%[', '%]", global.main->error.to.stream, global.main->error.context, global.main->error.context);
                  fl_print_format("%[%s%]", global.main->error.to.stream, global.main->error.notable, controller_require_s, global.main->error.notable);
                  fl_print_format("%[', or '%]", global.main->error.to.stream, global.main->error.context, global.main->error.context);
                  fl_print_format("%[%s%]", global.main->error.to.stream, global.main->error.notable, controller_wait_s, global.main->error.notable);
                  fl_print_format("%[' but instead has '%]", global.main->error.to.stream, global.main->error.context, global.main->error.context);
                  fl_print_format("%[%Q%]", global.main->error.to.stream, global.main->error.notable, action->parameters.array[j], global.main->error.notable);
                  fl_print_format("%['.%]", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s[0]);

                  funlockfile(global.main->error.to.stream);
                }
              }
            } // for
          }
          else if (action->type == controller_entry_action_type_failsafe || action->type == controller_entry_action_type_item) {
            if (fl_string_dynamic_compare_string(controller_main_s, action->parameters.array[0], controller_main_s_length) == F_equal_to) {
              action->status = F_status_set_error(F_supported_not);

              if (F_status_is_error_not(status_action)) {
                status_action = action->status;
              }

              if (global.main->error.verbosity != f_console_verbosity_quiet) {
                flockfile(global.main->error.to.stream);

                fl_print_format("%c%[%SThe %s item action may not specify the reserved item '%]", global.main->error.to.stream, f_string_eol_s[0], global.main->error.context, global.main->error.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->error.context);
                fl_print_format("%[%s%]", global.main->error.to.stream, global.main->error.notable, controller_main_s, global.main->error.notable);
                fl_print_format("%['.%]", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s[0]);

                funlockfile(global.main->error.to.stream);
              }
            }
          }
          else if (action->type == controller_entry_action_type_timeout) {

            if (fl_string_dynamic_compare_string(controller_kill_s, action->parameters.array[0], controller_kill_s_length) == F_equal_to) {
              action->code = controller_entry_timeout_code_kill_d;
            }
            else if (fl_string_dynamic_compare_string(controller_start_s, action->parameters.array[0], controller_start_s_length) == F_equal_to) {
              action->code = controller_entry_timeout_code_start_d;
            }
            else if (fl_string_dynamic_compare_string(controller_stop_s, action->parameters.array[0], controller_stop_s_length) == F_equal_to) {
              action->code = controller_entry_timeout_code_stop_d;
            }
            else {
              action->status = F_status_set_error(F_supported_not);

              if (F_status_is_error_not(status_action)) {
                status_action = action->status;
              }

              if (global.main->error.verbosity != f_console_verbosity_quiet) {
                flockfile(global.main->error.to.stream);

                fl_print_format("%c%[%SThe %s item action must have one of '%]", global.main->error.to.stream, f_string_eol_s[0], global.main->error.context, global.main->error.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->error.context);
                fl_print_format("%[%s%]", global.main->error.to.stream, global.main->error.notable, controller_kill_s, global.main->error.notable);
                fl_print_format("%[', '%]", global.main->error.to.stream, global.main->error.context, global.main->error.context);
                fl_print_format("%[%s%]", global.main->error.to.stream, global.main->error.notable, controller_start_s, global.main->error.notable);
                fl_print_format("%[', or '%]", global.main->error.to.stream, global.main->error.context, global.main->error.context);
                fl_print_format("%[%s%]", global.main->error.to.stream, global.main->error.notable, controller_stop_s, global.main->error.notable);
                fl_print_format("%[' but instead has '%]", global.main->error.to.stream, global.main->error.context, global.main->error.context);
                fl_print_format("%[%Q%]", global.main->error.to.stream, global.main->error.notable, action->parameters.array[0], global.main->error.notable);
                fl_print_format("%['.%]", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s[0]);

                funlockfile(global.main->error.to.stream);
              }
            }

            if (action->status == F_none) {
              const f_string_range_t range = macro_f_string_range_t_initialize(action->parameters.array[1].used);

              status = fl_conversion_string_to_number_unsigned(action->parameters.array[1].string, range, &action->number);

              if (F_status_is_error(status) || status == F_data_not) {
                action->number = 0;

                if (status == F_data_not) {
                  action->status = F_status_set_error(F_number);
                }
                else {
                  action->status = controller_status_simplify_error(F_status_set_fine(status));
                }

                if (F_status_set_fine(status) == F_memory_not) {
                  controller_entry_error_print(is_entry, global.main->error, cache->action, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, global.thread);

                  status_action = status;
                  break;
                }

                if (global.main->error.verbosity != f_console_verbosity_quiet) {
                  flockfile(global.main->error.to.stream);

                  fl_print_format("%c%[%SThe %s item action parameter '%]", global.main->error.to.stream, f_string_eol_s[0], global.main->error.context, global.main->error.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->error.context);
                  fl_print_format("%[%Q%]", global.main->error.to.stream, global.main->error.notable, action->parameters.array[1], global.main->error.notable);
                  fl_print_format("%[' is not a valid supported number.%]", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s[0]);

                  funlockfile(global.main->error.to.stream);
                }
              }
            }
          }
          else if (action->type == controller_entry_action_type_ready) {
            if (action->parameters.used) {
              if (fl_string_dynamic_compare_string(controller_wait_s, action->parameters.array[0], controller_wait_s_length) == F_equal_to) {
                action->code |= controller_entry_rule_code_wait_d;
              }
              else {
                action->status = F_status_set_error(F_supported_not);

                if (global.main->error.verbosity != f_console_verbosity_quiet) {
                  flockfile(global.main->error.to.stream);

                  fl_print_format("%c%[%SThe %s item action may only have '%]", global.main->error.to.stream, f_string_eol_s[0], global.main->error.context, global.main->error.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->error.context);
                  fl_print_format("%[%s%]", global.main->error.to.stream, global.main->error.notable, controller_wait_s, global.main->error.notable);
                  fl_print_format("%[' but instead has '%]", global.main->error.to.stream, global.main->error.context, global.main->error.context);
                  fl_print_format("%[%Q%]", global.main->error.to.stream, global.main->error.notable, action->parameters.array[0], global.main->error.notable);
                  fl_print_format("%['.%]", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s[0]);

                  funlockfile(global.main->error.to.stream);
                }
              }
            }
          }
        }
      }

      ++actions->used;
    } // for

    if (F_status_is_error(status_action)) {
      return status_action;
    }

    return status;
  }
#endif // _di_controller_entry_actions_read_

#ifndef _di_controller_entry_error_print_
  void controller_entry_error_print(const bool is_entry, const fl_print_t print, const controller_cache_action_t cache, const f_status_t status, const f_string_t function, const bool fallback, controller_thread_t *thread) {

    if (print.verbosity == f_console_verbosity_quiet) return;
    if (status == F_interrupt) return;

    // fll_error_print() automatically locks, so manually handle only the mutex locking and flushing rather than calling controller_print_lock().
    f_thread_mutex_lock(&thread->lock.print);

    fll_error_print(print, status, function, fallback);

    flockfile(print.to.stream);

    controller_entry_error_print_cache(is_entry, print, cache);

    controller_print_unlock_flush(print.to, thread);
  }
#endif // _di_controller_entry_error_print_

#ifndef _di_controller_entry_error_print_cache_
  void controller_entry_error_print_cache(const bool is_entry, const fl_print_t output, const controller_cache_action_t cache) {

    fl_print_format("%c%[%SWhile processing ", output.to.stream, f_string_eol_s[0], output.context, output.prefix);

    if (cache.name_action.used) {
      fl_print_format("action '%]", output.to.stream, output.context);
      fl_print_format("%[%Q%]", output.to.stream, output.notable, cache.name_action, output.notable);
      fl_print_format("%[' on line%] ", output.to.stream, output.context, output.context);
      fl_print_format("%[%un%]", output.to.stream, output.notable, cache.line_action, output.notable);
      fl_print_format("%[ for ", output.to.stream, output.context);
    }

    if (cache.name_item.used) {
      fl_print_format("%s item '%]", output.to.stream, is_entry ? controller_entry_s : controller_exit_s, output.context);
      fl_print_format("%[%Q%]", output.to.stream, output.notable, cache.name_item, output.notable);
      fl_print_format("%[' on line%] ", output.to.stream, output.context, output.context);
      fl_print_format("%[%un%]", output.to.stream, output.notable, cache.line_item, output.notable);
      fl_print_format("%[ for ", output.to.stream, output.context);
    }

    if (cache.name_file.used) {
      fl_print_format("%s file '%]", output.to.stream, is_entry ? controller_entry_s : controller_exit_s, output.context);
      fl_print_format("%[%Q%]%['", output.to.stream, output.notable, cache.name_file, output.notable, output.context);
    }

    fl_print_format(".%]%c", output.to.stream, output.context, f_string_eol_s[0]);
  }
#endif // _di_controller_entry_error_print_cache_

#ifndef _di_controller_entry_items_increase_by_
  f_status_t controller_entry_items_increase_by(const f_array_length_t amount, controller_entry_items_t *items) {

    if (items->used + amount > items->size) {
      if (items->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      const f_status_t status = f_memory_resize(items->size, items->used + amount, sizeof(controller_entry_item_t), (void **) & items->array);

      if (F_status_is_error_not(status)) {
        items->size = items->used + amount;
      }

      return status;
    }

    return F_data_not;
  }
#endif // _di_controller_entry_items_increase_by_

#ifndef _di_controller_entry_read_
  f_status_t controller_entry_read(const bool is_entry, controller_global_t global, controller_cache_t *cache) {

    f_status_t status = F_none;

    controller_entry_t *entry = is_entry ? &global.setting->entry : &global.setting->exit;

    entry->status = F_known_not;
    entry->items.used = 0;

    cache->action.line_action = 0;
    cache->action.line_item = 0;

    macro_f_time_spec_t_clear(cache->timestamp);

    cache->comments.used = 0;
    cache->delimits.used = 0;

    cache->content_action.used = 0;

    {
      f_array_length_t i = 0;

      for (; i < cache->content_actions.used; ++i) {
        cache->content_actions.array[i].used = 0;
      } // for

      for (i = 0; i < cache->content_items.used; ++i) {
        cache->content_items.array[i].used = 0;
      } // for
    }

    cache->content_actions.used = 0;
    cache->content_items.used = 0;

    cache->object_actions.used = 0;
    cache->object_items.used = 0;

    cache->buffer_file.used = 0;
    cache->buffer_path.used = 0;

    cache->action.name_file.used = 0;
    cache->action.name_action.used = 0;
    cache->action.name_item.used = 0;

    if (is_entry) {
      status = controller_file_load(F_true, controller_entries_s, global.setting->name_entry, controller_entry_s, controller_entries_s_length, controller_entry_s_length, global, cache);
    }
    else {
      status = controller_file_load(F_false, controller_exits_s, global.setting->name_entry, controller_exit_s, controller_exits_s_length, controller_exit_s_length, global, cache);

      if (status == F_file_found_not) {
        return F_file_found_not;
      }
    }

    if (F_status_is_error_not(status)) {
      if (cache->buffer_file.used) {
        controller_state_interrupt_t custom = macro_controller_state_interrupt_t_initialize(is_entry, global.thread);
        f_state_t state = macro_f_state_t_initialize(controller_common_allocation_large_d, controller_common_allocation_small_d, 0, &controller_thread_signal_state_fss, 0, (void *) &custom, 0);
        f_string_range_t range = macro_f_string_range_t_initialize(cache->buffer_file.used);

        status = fll_fss_basic_list_read(cache->buffer_file, state, &range, &cache->object_items, &cache->content_items, &cache->delimits, 0, &cache->comments);

        if (F_status_is_error(status)) {
          controller_error_print(global.main->error, F_status_set_fine(status), "fll_fss_basic_list_read", F_true, global.thread);
        }
        else {
          status = fl_fss_apply_delimit(cache->delimits, &cache->buffer_file);

          if (F_status_is_error(status)) {
            controller_entry_error_print(is_entry, global.main->error, cache->action, F_status_set_fine(status), "fl_fss_apply_delimit", F_true, global.thread);
          }
        }
      }
      else {
        if (global.main->error.verbosity != f_console_verbosity_quiet) {
          controller_print_lock(global.main->error.to, global.thread);

          fll_print_format("%c%[%SThe %s file is empty.%]%c", global.main->error.to.stream, f_string_eol_s[0], global.main->error.context, global.main->error.prefix, is_entry ? controller_entry_s : is_entry ? controller_entry_s : controller_exit_s, global.main->error.context, f_string_eol_s[0]);

          controller_print_unlock_flush(global.main->error.to, global.thread);
        }

        status = F_status_set_error(F_data_not);
      }
    }

    if (F_status_is_error_not(status) && cache->object_items.used) {
      status = controller_entry_items_increase_by(cache->object_items.used, &entry->items);

      if (F_status_is_error(status)) {
        controller_entry_error_print(is_entry, global.main->error, cache->action, F_status_set_fine(status), "controller_entry_items_increase_by", F_true, global.thread);
      }
      else {

        // 0x1 = main found, 0x2 = found existing.
        uint8_t code = 0;

        f_string_range_t *range = 0;

        f_array_length_t at = 0;
        f_array_length_t i = 0;
        f_array_length_t j = 0;

        for (; i < cache->object_items.used && controller_thread_is_enabled(is_entry, global.thread); ++i) {

          if (code & 0x2) {
            code -= 0x2;
          }

          at = 0;
          range = 0;

          cache->action.line_action = 0;
          cache->action.line_item = 0;

          cache->comments.used = 0;
          cache->delimits.used = 0;

          cache->content_action.used = 0;
          cache->content_actions.used = 0;

          cache->object_actions.used = 0;

          cache->buffer_path.used = 0;

          cache->action.name_action.used = 0;
          cache->action.name_item.used = 0;

          status = controller_entry_items_increase_by(controller_common_allocation_small_d, &entry->items);

          if (F_status_is_error(status)) {
            controller_entry_error_print(is_entry, global.main->error, cache->action, F_status_set_fine(status), "controller_entry_items_increase_by", F_true, global.thread);
            break;
          }

          status = controller_dynamic_partial_append_terminated(cache->buffer_file, cache->object_items.array[i], &cache->action.name_item);

          if (F_status_is_error(status)) {
            controller_entry_error_print(is_entry, global.main->error, cache->action, F_status_set_fine(status), "controller_dynamic_partial_append_terminated", F_true, global.thread);
            break;
          }

          status = f_fss_count_lines(cache->buffer_file, cache->object_items.array[i].start, &cache->action.line_item);

          if (F_status_is_error(status)) {
            controller_entry_error_print(is_entry, global.main->error, cache->action, F_status_set_fine(status), "f_fss_count_lines", F_true, global.thread);
            break;
          }

          ++cache->action.line_item;

          for (j = (code & 0x1) ? 1 : 0; j < entry->items.used; ++j) {

            if (fl_string_dynamic_compare(entry->items.array[j].name, cache->action.name_item) == F_equal_to) {
              if (global.main->warning.verbosity == f_console_verbosity_debug) {
                controller_print_lock(global.main->warning.to, global.thread);

                fl_print_format("%c%[%SIgnoring duplicate %s item '%]", global.main->warning.to.stream, f_string_eol_s[0], global.main->warning.context, global.main->warning.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->warning.context);
                fl_print_format("%[%Q%]", global.main->warning.to.stream, global.main->warning.notable, cache->action.name_file, global.main->warning.notable);
                fl_print_format("%['.%]%c", global.main->warning.to.stream, global.main->warning.context, global.main->warning.context, f_string_eol_s[0]);

                controller_entry_error_print_cache(is_entry, global.main->warning, cache->action);

                controller_print_unlock_flush(global.main->warning.to, global.thread);
              }

              code |= 0x2;
              break;
            }
          } // for

          if (code & 0x2) continue;

          range = &cache->content_items.array[i].array[0];

          if (fl_string_dynamic_compare_string(controller_main_s, cache->action.name_item, controller_main_s_length) == F_equal_to) {
            code |= 0x1;

            at = 0;

            if (!entry->items.used) {
              entry->items.used = 1;
            }
          }
          else if (fl_string_dynamic_compare_string(controller_setting_s, cache->action.name_item, controller_setting_s_length) == F_equal_to) {
            status = controller_entry_settings_read(is_entry, *range, global, cache);

            continue;
          }
          else if (entry->items.used) {
            at = entry->items.used++;
          }
          else {

            // skip position 0, which is reserved for "main".
            entry->items.array[0].name.used = 0;

            at = 1;
            entry->items.used = 2;
          }

          entry->items.array[at].line = cache->action.line_item;

          status = controller_dynamic_append_terminated(cache->action.name_item, &entry->items.array[at].name);

          if (F_status_is_error(status)) {
            controller_error_print(global.main->error, F_status_set_fine(status), "controller_dynamic_append_terminated", F_true, global.thread);

            break;
          }

          status = controller_entry_actions_read(is_entry, *range, global, cache, &entry->items.array[at].actions);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) != F_interrupt) {
              controller_print_lock(global.main->error.to, global.thread);

              controller_entry_error_print_cache(is_entry, global.main->error, cache->action);

              controller_print_unlock_flush(global.main->error.to, global.thread);
            }

            if (F_status_set_fine(status) == F_memory_not) {
              break;
            }
          }
        } // for

        if (is_entry && status == F_signal) {
          return F_signal;
        }

        if (F_status_is_error_not(status)) {
          cache->action.name_action.used = 0;
          cache->action.name_item.used = 0;

          if (!(code & 0x1)) {
            if (global.main->error.verbosity != f_console_verbosity_quiet) {
              controller_print_lock(global.main->error.to, global.thread);

              fl_print_format("%c%[%SThe required %s item '%]", global.main->error.to.stream, f_string_eol_s[0], global.main->error.context, global.main->error.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->error.context);
              fl_print_format("%[%s%]", global.main->error.to.stream, global.main->error.notable, controller_main_s, global.main->error.notable);
              fl_print_format("%[' was not found.%]%c", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s[0]);

              controller_print_unlock_flush(global.main->error.to, global.thread);
            }

            status = F_status_set_error(F_found_not);
          }

          if (F_status_is_error_not(status)) {
            controller_entry_action_t *action = 0;

            f_array_length_t k = 0;

            // 0x1 = missing or not, 0x2 = one or more missing.
            uint8_t missing = 0;

            for (i = 0; i < entry->items.used; ++i) {

              for (j = 0; j < entry->items.array[i].actions.used; ++j) {

                if (!controller_thread_is_enabled(is_entry, global.thread)) {
                  return F_signal;
                }

                action = &entry->items.array[i].actions.array[j];

                // only process actions that don't already have an error.
                if (F_status_is_error(action->status)) continue;

                if (action->type == controller_entry_action_type_failsafe || action->type == controller_entry_action_type_item) {
                  missing |= 0x1;

                  for (k = 0; k < entry->items.used; ++k) {

                    if (fl_string_dynamic_compare(action->parameters.array[0], entry->items.array[k].name) == F_equal_to) {
                      if (missing & 0x1) {
                        missing -= 0x1;
                      }

                      break;
                    }
                  } // for

                  if (missing & 0x1) {
                    missing |= 0x2;

                    cache->action.line_action = action->line;
                    cache->action.line_item = entry->items.array[i].line;

                    status = controller_dynamic_append_terminated(entry->items.array[i].name, &cache->action.name_item);

                    if (F_status_is_error(status)) {
                      controller_error_print(global.main->error, F_status_set_fine(status), "controller_dynamic_append_terminated", F_true, global.thread);
                      break;
                    }

                    if (global.main->error.verbosity != f_console_verbosity_quiet) {
                      controller_print_lock(global.main->error.to, global.thread);

                      fl_print_format("%c%[%SThe required %s item '%]", global.main->error.to.stream, f_string_eol_s[0], global.main->error.context, global.main->error.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->error.context);
                      fl_print_format("%[%Q%]", global.main->error.to.stream, global.main->error.notable, action->parameters.array[0], global.main->error.notable);
                      fl_print_format("%[' does not exist.%]%c", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s[0]);

                      controller_entry_error_print_cache(is_entry, global.main->error, cache->action);

                      controller_print_unlock_flush(global.main->error.to, global.thread);
                    }

                    action->number = 0;
                    action->status = controller_status_simplify_error(F_found_not);

                    cache->action.name_action.used = 0;
                    cache->action.name_item.used = 0;
                  }
                  else {
                    action->number = k;
                  }
                }
              } // for
            } // for
          }
        }
      }
    }

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) != F_interrupt) {
        controller_entry_error_print_cache(is_entry, global.main->error, cache->action);
      }

      entry->status = controller_status_simplify_error(F_status_set_fine(status));
    }
    else {
      entry->status = F_none;
    }

    return entry->status;
  }
#endif // _di_controller_entry_read_

#ifndef _di_controller_entry_settings_read_
  f_status_t controller_entry_settings_read(const bool is_entry, const f_string_range_t content_range, controller_global_t global, controller_cache_t *cache) {

    f_status_t status = F_none;

    {
      controller_state_interrupt_t custom = macro_controller_state_interrupt_t_initialize(is_entry, global.thread);
      f_state_t state = macro_f_state_t_initialize(controller_common_allocation_large_d, controller_common_allocation_small_d, 0, &controller_thread_signal_state_fss, 0, (void *) &custom, 0);
      f_string_range_t range = content_range;

      status = fll_fss_extended_read(cache->buffer_file, state, &range, &cache->object_actions, &cache->content_actions, 0, 0, &cache->delimits, 0);
    }

    if (F_status_is_error(status)) {
      controller_entry_error_print(is_entry, global.main->error, cache->action, F_status_set_fine(status), "fll_fss_extended_read", F_true, global.thread);

      return status;
    }

    status = fl_fss_apply_delimit(cache->delimits, &cache->buffer_file);

    if (F_status_is_error(status)) {
      controller_entry_error_print(is_entry, global.main->error, cache->action, F_status_set_fine(status), "fl_fss_apply_delimit", F_true, global.thread);

      return status;
    }

    cache->delimits.used = 0;

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t line = 0;

    controller_entry_t *entry = is_entry ? &global.setting->entry : &global.setting->exit;

    for (; i < cache->object_actions.used; ++i) {

      status = f_fss_count_lines(cache->buffer_file, cache->object_actions.array[i].start, &cache->action.line_action);

      if (F_status_is_error(status)) {
        controller_entry_error_print(is_entry, global.main->error, cache->action, F_status_set_fine(status), "f_fss_count_lines", F_true, global.thread);
        break;
      }

      line = ++cache->action.line_action;
      cache->action.name_action.used = 0;

      status = controller_dynamic_rip_nulless_terminated(cache->buffer_file, cache->object_actions.array[i], &cache->action.name_action);

      if (F_status_is_error(status)) {
        controller_entry_error_print(is_entry, global.main->error, cache->action, F_status_set_fine(status), "controller_dynamic_rip_nulless_terminated", F_true, global.thread);
        break;
      }

      if (is_entry && fl_string_dynamic_compare_string(controller_mode_s, cache->action.name_action, controller_mode_s_length) == F_equal_to) {
        if (cache->content_actions.array[i].used < 0 || cache->content_actions.array[i].used > 1) {
          controller_entry_settings_read_print_setting_requires_exactly(is_entry, global, *cache, 1);

          continue;
        }

        if (fl_string_dynamic_partial_compare_string(controller_service_s, cache->buffer_file, controller_service_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          global.setting->mode = controller_setting_mode_service;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_program_s, cache->buffer_file, controller_program_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          global.setting->mode = controller_setting_mode_program;
        }
        else {
          controller_entry_settings_read_print_setting_unknown_action_value(is_entry, global, *cache, i);

          continue;
        }
      }
      else if (fl_string_dynamic_compare_string(controller_pid_s, cache->action.name_action, controller_pid_s_length) == F_equal_to) {
        if (cache->content_actions.array[i].used < 0 || cache->content_actions.array[i].used > 1) {
          controller_entry_settings_read_print_setting_requires_exactly(is_entry, global, *cache, 1);

          continue;
        }

        if (fl_string_dynamic_partial_compare_string(controller_disable_s, cache->buffer_file, controller_disable_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          entry->pid = controller_entry_pid_disable;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_ready_s, cache->buffer_file, controller_ready_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          entry->pid = controller_entry_pid_ready;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_require_s, cache->buffer_file, controller_require_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          entry->pid = controller_entry_pid_require;
        }
        else {
          controller_entry_settings_read_print_setting_unknown_action_value(is_entry, global, *cache, i);

          continue;
        }
      }
      else if (fl_string_dynamic_compare_string(controller_show_s, cache->action.name_action, controller_show_s_length) == F_equal_to) {
        if (cache->content_actions.array[i].used < 0 || cache->content_actions.array[i].used > 1) {
          controller_entry_settings_read_print_setting_requires_exactly(is_entry, global, *cache, 1);

          continue;
        }

        if (fl_string_dynamic_partial_compare_string(controller_normal_s, cache->buffer_file, controller_normal_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          entry->show = controller_entry_show_normal;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_init_s, cache->buffer_file, controller_init_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          entry->show = controller_entry_show_init;
        }
        else {
          controller_entry_settings_read_print_setting_unknown_action_value(is_entry, global, *cache, i);

          continue;
        }
      }
      else {
        if (global.main->warning.verbosity == f_console_verbosity_debug) {
          controller_entry_settings_read_print_setting_unknown_action(is_entry, global, *cache);
        }

        continue;
      }
    } // for
  }
#endif // _di_controller_entry_settings_read_

#ifndef _di_controller_entry_settings_read_print_setting_requires_exactly_
  void controller_entry_settings_read_print_setting_requires_exactly(const bool is_entry, const controller_global_t global, const controller_cache_t cache, const f_number_unsigned_t total) {

    if (global.main->error.verbosity == f_console_verbosity_quiet) return;

    controller_print_lock(global.main->error.to, global.thread);

    fl_print_format("%c%[%SThe %s item setting '%]", global.main->error.to.stream, f_string_eol_s[0], global.main->error.context, global.main->error.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->error.context);
    fl_print_format("%[%Q%]", global.main->error.to.stream, global.main->error.notable, cache.action.name_action, global.main->error.notable);
    fl_print_format("%[' requires exactly %]", global.main->error.to.stream, global.main->error.context, global.main->error.context);
    fl_print_format("%[%un%]", global.main->error.to.stream, global.main->error.notable, total, global.main->error.notable);
    fl_print_format("%[' %s.%]%c", global.main->error.to.stream, global.main->error.context, total > 1 ? controller_parameters_s : controller_parameter_s, global.main->error.context, f_string_eol_s[0]);

    controller_entry_error_print_cache(is_entry, global.main->error, cache.action);

    controller_print_unlock_flush(global.main->error.to, global.thread);
  }
#endif // _di_controller_entry_settings_read_print_setting_requires_exactly_

#ifndef _di_controller_entry_settings_read_print_setting_unknown_action_
  void controller_entry_settings_read_print_setting_unknown_action(const bool is_entry, const controller_global_t global, const controller_cache_t cache) {

    if (global.main->warning.verbosity != f_console_verbosity_debug) return;

    controller_print_lock(global.main->warning.to, global.thread);

    fl_print_format("%c%[%SUnknown %s item setting '%]", global.main->warning.to.stream, f_string_eol_s[0], global.main->warning.context, global.main->warning.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->warning.context);
    fl_print_format("%[%Q%]", global.main->warning.to.stream, global.main->warning.notable, cache.action.name_action, global.main->warning.notable);
    fl_print_format("%['.%]%c", global.main->warning.to.stream, global.main->warning.context, global.main->warning.context, f_string_eol_s[0]);

    controller_entry_error_print_cache(is_entry, global.main->warning, cache.action);

    controller_print_unlock_flush(global.main->warning.to, global.thread);
  }
#endif // _di_controller_entry_settings_read_print_setting_unknown_action_

#ifndef _di_controller_entry_settings_read_print_setting_unknown_action_value_
  void controller_entry_settings_read_print_setting_unknown_action_value(const bool is_entry, const controller_global_t global, const controller_cache_t cache, const f_array_length_t index) {

    if (global.main->warning.verbosity != f_console_verbosity_debug) return;

    controller_print_lock(global.main->warning.to, global.thread);

    fl_print_format("%c%[%SThe %s item setting '%]", global.main->warning.to.stream, f_string_eol_s[0], global.main->warning.context, global.main->warning.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->warning.context);
    fl_print_format("%[%Q%]", global.main->warning.to.stream, global.main->warning.notable, cache.action.name_action, global.main->warning.notable);
    fl_print_format("%[' has an unknown value '%]", global.main->warning.to.stream, f_string_eol_s[0], global.main->warning.context, global.main->warning.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->warning.context);
    fl_print_format("%[%Q%]", global.main->warning.to.stream, global.main->warning.notable, cache.content_actions.array[index].array[0], global.main->warning.notable);
    fl_print_format("%['.%]%c", global.main->warning.to.stream, global.main->warning.context, global.main->warning.context, f_string_eol_s[0]);

    controller_entry_error_print_cache(is_entry, global.main->warning, cache.action);

    controller_print_unlock_flush(global.main->warning.to, global.thread);
  }
#endif // _di_controller_entry_settings_read_print_setting_unknown_action_value_

#ifdef __cplusplus
} // extern "C"
#endif
