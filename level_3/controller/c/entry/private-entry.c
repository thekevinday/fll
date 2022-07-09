#include "../controller.h"
#include "../common/private-common.h"
#include "../controller/private-controller.h"
#include "../controller/private-controller_print.h"
#include "../entry/private-entry.h"
#include "../entry/private-entry_print.h"
#include "../lock/private-lock.h"
#include "../lock/private-lock_print.h"
#include "../rule/private-rule.h"
#include "../thread/private-thread.h"
#include "../thread/private-thread_process.h"
#include "../thread/private-thread_signal.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_entry_action_type_is_rule_
  f_status_t controller_entry_action_type_is_rule(uint8_t type) {

    switch (type) {
      case controller_entry_action_type_freeze_e:
      case controller_entry_action_type_kill_e:
      case controller_entry_action_type_pause_e:
      case controller_entry_action_type_reload_e:
      case controller_entry_action_type_restart_e:
      case controller_entry_action_type_resume_e:
      case controller_entry_action_type_start_e:
      case controller_entry_action_type_stop_e:
      case controller_entry_action_type_thaw_e:
        return F_true;
    }

    return F_false;
  }
#endif // _di_controller_entry_action_type_is_rule_

#ifndef _di_controller_entry_action_type_to_rule_action_type_
  uint8_t controller_entry_action_type_to_rule_action_type(uint8_t type) {

    switch (type) {
      case controller_entry_action_type_freeze_e:
        return controller_rule_action_type_freeze_e;

      case controller_entry_action_type_kill_e:
        return controller_rule_action_type_kill_e;

      case controller_entry_action_type_pause_e:
        return controller_rule_action_type_pause_e;

      case controller_entry_action_type_reload_e:
        return controller_rule_action_type_reload_e;

      case controller_entry_action_type_restart_e:
        return controller_rule_action_type_restart_e;

      case controller_entry_action_type_resume_e:
        return controller_rule_action_type_resume_e;

      case controller_entry_action_type_start_e:
        return controller_rule_action_type_start_e;

      case controller_entry_action_type_stop_e:
        return controller_rule_action_type_stop_e;

      case controller_entry_action_type_thaw_e:
        return controller_rule_action_type_thaw_e;
    }

    return 0;
  }
#endif // _di_controller_entry_action_type_to_rule_action_type_

#ifndef _di_controller_entry_actions_read_
  f_status_t controller_entry_actions_read(const controller_global_t global, const bool is_entry, const f_string_range_t content_range, controller_cache_t * const cache, controller_entry_actions_t *actions) {

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
      f_state_t state = macro_f_state_t_initialize(controller_common_allocation_large_d, controller_common_allocation_small_d, 0, 0, &controller_thread_signal_state_fss, 0, (void *) &custom, 0);
      f_string_range_t range = content_range;

      status = fll_fss_extended_read(cache->buffer_file, state, &range, &cache->object_actions, &cache->content_actions, 0, 0, &cache->delimits, 0);
    }

    if (F_status_is_error(status)) {
      controller_entry_print_error(is_entry, global.main->error, cache->action, F_status_set_fine(status), "fll_fss_extended_read", F_true, global.thread);

      return status;
    }

    f_state_t state = f_state_t_initialize;

    status = f_fss_apply_delimit(state, cache->delimits, &cache->buffer_file);

    if (F_status_is_error(status)) {
      controller_entry_print_error(is_entry, global.main->error, cache->action, F_status_set_fine(status), "f_fss_apply_delimit", F_true, global.thread);

      return status;
    }

    cache->delimits.used = 0;

    status = controller_entry_actions_increase_by(cache->object_actions.used, actions);

    if (F_status_is_error(status)) {
      controller_entry_print_error(is_entry, global.main->error, cache->action, F_status_set_fine(status), "controller_entry_actions_increase_by", F_true, global.thread);

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

      status = f_fss_count_lines(state, cache->buffer_file, cache->object_actions.array[i].start, &cache->action.line_action);

      if (F_status_is_error(status)) {
        controller_entry_print_error(is_entry, global.main->error, cache->action, F_status_set_fine(status), "f_fss_count_lines", F_true, global.thread);

        break;
      }

      action->line = ++cache->action.line_action;

      status = fl_string_dynamic_partial_rip_nulless(cache->buffer_file, cache->object_actions.array[i], &cache->action.name_action);

      if (F_status_is_error(status)) {
        controller_entry_print_error(is_entry, global.main->error, cache->action, F_status_set_fine(status), "fl_string_dynamic_partial_rip_nulless", F_true, global.thread);

        break;
      }

      if (fl_string_dynamic_compare(controller_consider_s, cache->action.name_action) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_consider_e;
      }
      else if (fl_string_dynamic_compare(controller_execute_s, cache->action.name_action) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_execute_e;
      }
      else if (fl_string_dynamic_compare(controller_failsafe_s, cache->action.name_action) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_failsafe_e;
      }
      else if (fl_string_dynamic_compare(controller_freeze_s, cache->action.name_action) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_freeze_e;
      }
      else if (fl_string_dynamic_compare(controller_item_s, cache->action.name_action) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_item_e;
      }
      else if (fl_string_dynamic_compare(controller_kill_s, cache->action.name_action) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_kill_e;
      }
      else if (fl_string_dynamic_compare(controller_pause_s, cache->action.name_action) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_pause_e;
      }
      else if (fl_string_dynamic_compare(controller_ready_s, cache->action.name_action) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_ready_e;
      }
      else if (fl_string_dynamic_compare(controller_reload_s, cache->action.name_action) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_reload_e;
      }
      else if (fl_string_dynamic_compare(controller_restart_s, cache->action.name_action) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_restart_e;
      }
      else if (fl_string_dynamic_compare(controller_resume_s, cache->action.name_action) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_resume_e;
      }
      else if (fl_string_dynamic_compare(controller_start_s, cache->action.name_action) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_start_e;
      }
      else if (fl_string_dynamic_compare(controller_stop_s, cache->action.name_action) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_stop_e;
      }
      else if (fl_string_dynamic_compare(controller_thaw_s, cache->action.name_action) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_thaw_e;
      }
      else if (fl_string_dynamic_compare(controller_timeout_s, cache->action.name_action) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_timeout_e;
      }
      else {
        if (global.main->warning.verbosity == f_console_verbosity_debug_e) {
          controller_lock_print(global.main->warning.to, global.thread);

          fl_print_format("%r%[%QUnknown %r item action '%]", global.main->warning.to.stream, f_string_eol_s, global.main->warning.context, global.main->warning.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->warning.context);
          fl_print_format("%[%Q%]", global.main->warning.to.stream, global.main->warning.notable, cache->action.name_action, global.main->warning.notable);
          fl_print_format("%['.%]%r", global.main->warning.to.stream, global.main->warning.context, global.main->warning.context, f_string_eol_s);

          controller_entry_print_error_cache(is_entry, global.main->warning, cache->action);

          controller_unlock_print_flush(global.main->warning.to, global.thread);
        }

        continue;
      }

      if (action->type == controller_entry_action_type_consider_e || controller_entry_action_type_is_rule(action->type)) {
        allocate = cache->content_actions.array[i].used;
        at_least = 2;
        at_most = allocate;
      }
      else if (action->type == controller_entry_action_type_execute_e) {
        allocate = cache->content_actions.array[i].used;
        at_least = 1;
        at_most = allocate;
      }
      else if (action->type == controller_entry_action_type_failsafe_e || action->type == controller_entry_action_type_item_e) {
        allocate = 1;
        at_least = 1;
        at_most = 1;
      }
      else if (action->type == controller_entry_action_type_timeout_e) {
        allocate = 2;
        at_least = 2;
        at_most = 2;
      }
      else if (action->type == controller_entry_action_type_ready_e) {
        allocate = 1;
        at_least = 0;
        at_most = 1;
      }

      if (cache->content_actions.array[i].used < at_least || cache->content_actions.array[i].used > at_most) {
        action->status = F_status_set_error(F_parameter);

        if (global.main->error.verbosity != f_console_verbosity_quiet_e) {
          f_thread_mutex_lock(&global.thread->lock.print);

          flockfile(global.main->error.to.stream);

          fl_print_format("%r%[%QThe %r item action '%]", global.main->error.to.stream, f_string_eol_s, global.main->error.context, global.main->error.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->error.context);
          fl_print_format("%[%Q%]", global.main->error.to.stream, global.main->error.notable, cache->action.name_action, global.main->error.notable);
          fl_print_format("%[' requires ", global.main->error.to.stream, global.main->error.context);

          if (at_least == at_most) {
            f_print_terminated("exactly ", global.main->error.to.stream);
          }

          fl_print_format("%]%[%un%]", global.main->error.to.stream, global.main->error.context, global.main->error.notable, at_least, global.main->error.notable);

          if (action->type == controller_entry_action_type_consider_e || controller_entry_action_type_is_rule(action->type)) {
            fl_print_format("%[ or more parameters.%]%r", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s);
          }
          else {
            if (at_least == at_most) {
              fl_print_format("%[ parameters.%]%r", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s);
            }
            else {
              fl_print_format("%[ to %]", global.main->error.to.stream, global.main->error.context, global.main->error.context);
              fl_print_format("%[%un%]", global.main->error.to.stream, global.main->error.notable, at_most, global.main->error.notable);
              fl_print_format("%[ parameters.%]%r", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s);
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
          controller_entry_print_error(is_entry, global.main->error, cache->action, F_status_set_fine(status), "f_string_dynamics_increase_by", F_true, global.thread);

          action->status = status;

          if (F_status_is_error_not(status_action)) {
            status_action = status;
          }

          break;
        }

        for (j = 0; j < allocate && j < cache->content_actions.array[i].used; ++j) {

          action->parameters.array[j].used = 0;

          if (cache->content_actions.array[i].array[j].start > cache->content_actions.array[i].array[j].stop) continue;

          status = f_string_dynamic_increase_by((cache->content_actions.array[i].array[j].stop - cache->content_actions.array[i].array[j].start) + 1, &action->parameters.array[j]);

          if (F_status_is_error(status)) {
            controller_entry_print_error(is_entry, global.main->error, cache->action, F_status_set_fine(status), "f_string_dynamic_increase_by", F_true, global.thread);

            break;
          }

          status = f_string_dynamic_partial_append_nulless(cache->buffer_file, cache->content_actions.array[i].array[j], &action->parameters.array[j]);

          if (F_status_is_error(status)) {
            controller_entry_print_error(is_entry, global.main->error, cache->action, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, global.thread);

            break;
          }

          ++action->parameters.used;
        } // for

        if (F_status_is_error_not(action->status)) {
          if (action->type == controller_entry_action_type_consider_e || controller_entry_action_type_is_rule(action->type)) {
            if (action->parameters.array[0].used) {

              // Force the path to be canonical (removing all '../' parts).
              status = controller_path_canonical_relative(global.setting, action->parameters.array[0], &cache->buffer_path);

              if (F_status_is_error(status)) {
                controller_entry_print_error_file(is_entry, global.main->error, cache->action, F_status_set_fine(status), "controller_path_canonical_relative", F_true, cache->action.generic, f_file_operation_analyze_s, fll_error_file_type_path_e, global.thread);

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

              if (global.main->error.verbosity != f_console_verbosity_quiet_e) {
                fll_print_format("%r%[%QThe %r item action must not have an empty string for a path (the first parameter).%]%r", global.main->error.to.stream, f_string_eol_s, global.main->error.context, global.main->error.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->error.context, f_string_eol_s);
              }
            }

            if (action->parameters.array[1].used) {
              cache->buffer_path.used = 0;

              status = f_file_name_base(action->parameters.array[1], &cache->buffer_path);

              if (F_status_is_error(status)) {
                controller_entry_print_error(is_entry, global.main->error, cache->action, F_status_set_fine(status), "f_file_name_base", F_true, global.thread);

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
                  if (global.main->error.verbosity != f_console_verbosity_quiet_e) {
                    flockfile(global.main->error.to.stream);

                    fl_print_format("%r%[%QThe %r item action second parameter '%]", global.main->error.to.stream, f_string_eol_s, global.main->error.context, global.main->error.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->error.context);
                    fl_print_format("%[%Q%]", global.main->error.to.stream, global.main->error.notable, action->parameters.array[1], global.main->error.notable);
                    fl_print_format("%[' must be a base path name, such as '%]", global.main->error.to.stream, global.main->error.context, global.main->error.context);
                    fl_print_format("%[%Q%]", global.main->error.to.stream, global.main->error.notable, cache->buffer_path, global.main->error.notable);
                    fl_print_format("%['.%]", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s);

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

              if (global.main->error.verbosity != f_console_verbosity_quiet_e) {
                fll_print_format("%r%[%QThe %r item action must not have an empty string for a rule name (the second parameter).%]", global.main->error.to.stream, f_string_eol_s, global.main->error.context, global.main->error.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->error.context, f_string_eol_s);
              }
            }

            for (j = 2; j < action->parameters.used; ++j) {

              if (fl_string_dynamic_compare(controller_asynchronous_s, action->parameters.array[j]) == F_equal_to) {
                action->code |= controller_entry_rule_code_asynchronous_d;
              }
              else if (fl_string_dynamic_compare(controller_require_s, action->parameters.array[j]) == F_equal_to) {
                action->code |= controller_entry_rule_code_require_d;
              }
              else if (fl_string_dynamic_compare(controller_wait_s, action->parameters.array[j]) == F_equal_to) {
                action->code |= controller_entry_rule_code_wait_d;
              }
              else {
                if (action->status == F_none) {
                  action->status = F_status_set_error(F_supported_not);

                  if (F_status_is_error_not(status_action)) {
                    status_action = action->status;
                  }
                }

                if (global.main->error.verbosity != f_console_verbosity_quiet_e) {
                  flockfile(global.main->error.to.stream);

                  fl_print_format("%r%[%QThe %r item action third parameter (and beyond) must be one of '%]", global.main->error.to.stream, f_string_eol_s, global.main->error.context, global.main->error.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->error.context);
                  fl_print_format("%[%r%]", global.main->error.to.stream, global.main->error.notable, controller_asynchronous_s, global.main->error.notable);
                  fl_print_format("%[', '%]", global.main->error.to.stream, global.main->error.context, global.main->error.context);
                  fl_print_format("%[%r%]", global.main->error.to.stream, global.main->error.notable, controller_require_s, global.main->error.notable);
                  fl_print_format("%[', or '%]", global.main->error.to.stream, global.main->error.context, global.main->error.context);
                  fl_print_format("%[%r%]", global.main->error.to.stream, global.main->error.notable, controller_wait_s, global.main->error.notable);
                  fl_print_format("%[' but instead has '%]", global.main->error.to.stream, global.main->error.context, global.main->error.context);
                  fl_print_format("%[%Q%]", global.main->error.to.stream, global.main->error.notable, action->parameters.array[j], global.main->error.notable);
                  fl_print_format("%['.%]", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s);

                  funlockfile(global.main->error.to.stream);
                }
              }
            } // for
          }
          else if (action->type == controller_entry_action_type_failsafe_e || action->type == controller_entry_action_type_item_e) {
            if (fl_string_dynamic_compare(controller_main_s, action->parameters.array[0]) == F_equal_to) {
              action->status = F_status_set_error(F_supported_not);

              if (F_status_is_error_not(status_action)) {
                status_action = action->status;
              }

              if (global.main->error.verbosity != f_console_verbosity_quiet_e) {
                flockfile(global.main->error.to.stream);

                fl_print_format("%r%[%QThe %r item action may not specify the reserved item '%]", global.main->error.to.stream, f_string_eol_s, global.main->error.context, global.main->error.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->error.context);
                fl_print_format("%[%r%]", global.main->error.to.stream, global.main->error.notable, controller_main_s, global.main->error.notable);
                fl_print_format("%['.%]", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s);

                funlockfile(global.main->error.to.stream);
              }
            }
          }
          else if (action->type == controller_entry_action_type_timeout_e) {

            if (fl_string_dynamic_compare(controller_kill_s, action->parameters.array[0]) == F_equal_to) {
              action->code = controller_entry_timeout_code_kill_d;
            }
            else if (fl_string_dynamic_compare(controller_start_s, action->parameters.array[0]) == F_equal_to) {
              action->code = controller_entry_timeout_code_start_d;
            }
            else if (fl_string_dynamic_compare(controller_stop_s, action->parameters.array[0]) == F_equal_to) {
              action->code = controller_entry_timeout_code_stop_d;
            }
            else {
              action->status = F_status_set_error(F_supported_not);

              if (F_status_is_error_not(status_action)) {
                status_action = action->status;
              }

              if (global.main->error.verbosity != f_console_verbosity_quiet_e) {
                flockfile(global.main->error.to.stream);

                fl_print_format("%r%[%QThe %r item action must have one of '%]", global.main->error.to.stream, f_string_eol_s, global.main->error.context, global.main->error.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->error.context);
                fl_print_format("%[%r%]", global.main->error.to.stream, global.main->error.notable, controller_kill_s, global.main->error.notable);
                fl_print_format("%[', '%]", global.main->error.to.stream, global.main->error.context, global.main->error.context);
                fl_print_format("%[%r%]", global.main->error.to.stream, global.main->error.notable, controller_start_s, global.main->error.notable);
                fl_print_format("%[', or '%]", global.main->error.to.stream, global.main->error.context, global.main->error.context);
                fl_print_format("%[%r%]", global.main->error.to.stream, global.main->error.notable, controller_stop_s, global.main->error.notable);
                fl_print_format("%[' but instead has '%]", global.main->error.to.stream, global.main->error.context, global.main->error.context);
                fl_print_format("%[%Q%]", global.main->error.to.stream, global.main->error.notable, action->parameters.array[0], global.main->error.notable);
                fl_print_format("%['.%]", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s);

                funlockfile(global.main->error.to.stream);
              }
            }

            if (action->status == F_none) {
              status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, action->parameters.array[1], &action->number);

              if (F_status_is_error(status) || status == F_data_not) {
                action->number = 0;

                if (status == F_data_not) {
                  action->status = F_status_set_error(F_number);
                }
                else {
                  action->status = controller_status_simplify_error(F_status_set_fine(status));
                }

                if (F_status_set_fine(status) == F_memory_not) {
                  controller_entry_print_error(is_entry, global.main->error, cache->action, F_status_set_fine(status), "fl_conversion_dynamic_to_unsigned_detect", F_true, global.thread);

                  status_action = status;

                  break;
                }

                if (global.main->error.verbosity != f_console_verbosity_quiet_e) {
                  flockfile(global.main->error.to.stream);

                  fl_print_format("%r%[%QThe %r item action parameter '%]", global.main->error.to.stream, f_string_eol_s, global.main->error.context, global.main->error.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->error.context);
                  fl_print_format("%[%Q%]", global.main->error.to.stream, global.main->error.notable, action->parameters.array[1], global.main->error.notable);
                  fl_print_format("%[' is not a valid supported number.%]", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s);

                  funlockfile(global.main->error.to.stream);
                }
              }
            }
          }
          else if (action->type == controller_entry_action_type_ready_e) {
            if (action->parameters.used) {
              if (fl_string_dynamic_compare(controller_wait_s, action->parameters.array[0]) == F_equal_to) {
                action->code |= controller_entry_rule_code_wait_d;
              }
              else {
                action->status = F_status_set_error(F_supported_not);

                if (global.main->error.verbosity != f_console_verbosity_quiet_e) {
                  flockfile(global.main->error.to.stream);

                  fl_print_format("%r%[%QThe %r item action may only have '%]", global.main->error.to.stream, f_string_eol_s, global.main->error.context, global.main->error.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->error.context);
                  fl_print_format("%[%r%]", global.main->error.to.stream, global.main->error.notable, controller_wait_s, global.main->error.notable);
                  fl_print_format("%[' but instead has '%]", global.main->error.to.stream, global.main->error.context, global.main->error.context);
                  fl_print_format("%[%Q%]", global.main->error.to.stream, global.main->error.notable, action->parameters.array[0], global.main->error.notable);
                  fl_print_format("%['.%]", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s);

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

#ifndef _di_controller_entry_preprocess_
  f_status_t controller_entry_preprocess(const controller_global_t global, const bool is_entry, controller_cache_t * const cache) {

    f_status_t status = F_none;
    f_status_t status2 = F_none;

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    f_array_length_t at_i = 0;
    f_array_length_t at_j = 1;

    controller_entry_t *entry = is_entry ? &global.setting->entry : &global.setting->exit;
    controller_entry_actions_t *actions = 0;

    uint8_t error_has = F_false;

    // This effectively sets the read for an entry and resets the ready for an exit.
    global.setting->ready = controller_setting_ready_no_e;

    cache->ats.used = 0;

    cache->action.line_action = 0;
    cache->action.line_item = 0;
    cache->action.name_action.used = 0;
    cache->action.name_item.used = 0;

    macro_f_array_lengths_t_increase_by(status, cache->ats, controller_common_allocation_small_d)

    if (F_status_is_error(status)) {
      controller_entry_print_error(is_entry, global.main->error, cache->action, F_status_set_fine(status), "macro_f_array_lengths_t_increase_by", F_true, global.thread);

      return status;
    }

    // Utilize the ats cache as an item execution stack (at_i is for item index, and at_j (at_i + 1) is for action index).
    cache->ats.array[0] = 0;
    cache->ats.array[1] = 0;
    cache->ats.used = 2;

    cache->action.line_item = entry->items.array[0].line;
    cache->action.name_item.used = 0;

    status = f_string_dynamic_append_nulless(entry->items.array[0].name, &cache->action.name_item);

    if (F_status_is_error(status)) {
      controller_entry_print_error(is_entry, global.main->error, cache->action, F_status_set_fine(status), "f_string_dynamic_append_nulless", F_true, global.thread);

      return status;
    }

    while (controller_thread_is_enabled(is_entry, global.thread)) {

      actions = &entry->items.array[cache->ats.array[at_i]].actions;

      for (; cache->ats.array[at_j] < actions->used && controller_thread_is_enabled(is_entry, global.thread); ++cache->ats.array[at_j]) {

        cache->action.line_action = actions->array[cache->ats.array[at_j]].line;
        cache->action.name_action.used = 0;

        status2 = f_string_dynamic_append_nulless(controller_entry_action_type_name(actions->array[cache->ats.array[at_j]].type), &cache->action.name_action);

        if (F_status_is_error(status2)) {
          controller_entry_print_error(is_entry, global.main->error, cache->action, F_status_set_fine(status2), "f_string_dynamic_append_nulless", F_true, global.thread);

          return status2;
        }

        if (actions->array[cache->ats.array[at_j]].type == controller_entry_action_type_ready_e) {

          if (global.setting->ready == controller_setting_ready_wait_e) {
            if (global.main->warning.verbosity == f_console_verbosity_debug_e) {
              controller_lock_print(global.main->warning.to, global.thread);

              fl_print_format("%r%[%QMultiple '%]", global.main->warning.to.stream, f_string_eol_s, global.main->warning.context, global.main->warning.prefix, global.main->warning.context);
              fl_print_format("%[%r%]", global.main->warning.to.stream, global.main->warning.notable, controller_ready_s, global.main->warning.notable);
              fl_print_format("%[' %r item actions detected; only the first will be used.%]%r", global.main->warning.to.stream, global.main->warning.context, is_entry ? controller_entry_s : controller_exit_s, global.main->warning.context, f_string_eol_s);

              controller_entry_print_error_cache(is_entry, global.main->warning, cache->action);

              controller_unlock_print_flush(global.main->warning.to, global.thread);
            }
          }
          else {
            global.setting->ready = controller_setting_ready_wait_e;
          }
        }
        else if (actions->array[cache->ats.array[at_j]].type == controller_entry_action_type_item_e) {
          error_has = F_false;

          // "main" is not allowed to be used for an "item" and "setting" is not an executable "item".
          if (fl_string_dynamic_compare(controller_main_s, actions->array[cache->ats.array[at_j]].parameters.array[0]) == F_equal_to) {
            continue;
          }
          else if (fl_string_dynamic_compare(controller_setting_s, actions->array[cache->ats.array[at_j]].parameters.array[0]) == F_equal_to) {
            continue;
          }

          // Walk though each items and check to see if the item actually exists.
          for (i = 1; i < entry->items.used && controller_thread_is_enabled(is_entry, global.thread); ++i) {

            if (fl_string_dynamic_compare(entry->items.array[i].name, actions->array[cache->ats.array[at_j]].parameters.array[0]) == F_equal_to) {

              // Check to see if "i" is already in the stack (to prevent recursion) (skipping main).
              for (j = 2; j < cache->ats.used; j += 2) {

                if (cache->ats.array[j] == i) {
                  if (global.main->error.verbosity != f_console_verbosity_quiet_e) {
                    controller_lock_print(global.main->error.to, global.thread);

                    fl_print_format("%r%[%QThe %r item named '%]", global.main->error.to.stream, f_string_eol_s, global.main->error.context, is_entry ? controller_entry_s : controller_exit_s, global.main->error.prefix, global.main->error.context);
                    fl_print_format("%[%Q%]", global.main->error.to.stream, global.main->error.notable, entry->items.array[i].name, global.main->error.notable);
                    fl_print_format("%[' cannot be executed because recursion is not allowed.%]%r", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s);

                    controller_entry_print_error_cache(is_entry, global.main->error, cache->action);

                    controller_unlock_print_flush(global.main->error.to, global.thread);
                  }

                  if (F_status_is_error_not(status)) {
                    status = F_status_set_error(F_recurse);
                  }

                  error_has = F_true;
                  break;
                }
              } // for

              if (error_has) break;

              macro_f_array_lengths_t_increase_by(status2, cache->ats, controller_common_allocation_small_d)

              if (F_status_is_error(status2)) {
                controller_entry_print_error(is_entry, global.main->error, cache->action, F_status_set_fine(status2), "macro_f_array_lengths_t_increase_by", F_true, global.thread);

                return status2;
              }

              // Save the value so to avoid string comparison during normal operation.
              actions->array[cache->ats.array[at_j]].number = i;

              // Continue into the requested item.
              at_i = cache->ats.used;
              at_j = cache->ats.used + 1;

              cache->ats.array[at_i] = i;
              cache->ats.array[at_j] = 0;
              cache->ats.used += 2;

              cache->action.name_action.used = 0;
              cache->action.line_action = 0;

              cache->action.name_item.used = 0;
              cache->action.line_item = entry->items.array[i].line;

              status2 = f_string_dynamic_append_nulless(entry->items.array[i].name, &cache->action.name_item);

              if (F_status_is_error(status2)) {
                controller_entry_print_error(is_entry, global.main->error, cache->action, F_status_set_fine(status2), "f_string_dynamic_append_nulless", F_true, global.thread);

                return status2;
              }

              break;
            }
          } // for

          if (error_has || i >= entry->items.used) {
            if (i >= entry->items.used) {
              if (global.main->error.verbosity != f_console_verbosity_quiet_e) {
                controller_lock_print(global.main->error.to, global.thread);

                fl_print_format("%r%[%QThe %r item named '%]", global.main->error.to.stream, f_string_eol_s, global.main->error.context, is_entry ? controller_entry_s : controller_exit_s, global.main->error.prefix, global.main->error.context);
                fl_print_format("%[%Q%]", global.main->error.to.stream, global.main->error.notable, actions->array[cache->ats.array[at_j]].parameters.array[0], global.main->error.notable);
                fl_print_format("%[' does not exist.%]%r", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s);

                controller_entry_print_error_cache(is_entry, global.main->error, cache->action);

                controller_unlock_print_flush(global.main->error.to, global.thread);
              }

              if (F_status_is_error_not(status)) {
                status = F_status_set_error(F_valid_not);
              }
            }
          }
          else {
            break;
          }
        }
      } // for

      cache->action.line_action = 0;
      cache->action.name_action.used = 0;

      // End of actions found, so drop to previous loop in stack.
      if (cache->ats.array[at_j] == actions->used) {

        // All actions for "main" are processed so there is nothing left to do.
        if (at_i == 0) break;

        at_i -= 2;
        at_j -= 2;

        cache->ats.used -= 2;
        ++cache->ats.array[at_j];

        cache->action.line_item = entry->items.array[cache->ats.array[at_i]].line;
        cache->action.name_item.used = 0;

        status2 = f_string_dynamic_append_nulless(entry->items.array[cache->ats.array[at_i]].name, &cache->action.name_item);

        if (F_status_is_error(status2)) {
          controller_entry_print_error(is_entry, global.main->error, cache->action, F_status_set_fine(status2), "f_string_dynamic_append_nulless", F_true, global.thread);

          return status2;
        }
      }
    } // while

    if (!controller_thread_is_enabled(is_entry, global.thread)) {
      return F_status_set_error(F_interrupt);
    }

    // If ready was never found in the entry, then default to always ready.
    if (global.setting->ready == controller_setting_ready_no_e) {
      global.setting->ready = controller_setting_ready_yes_e;
    }

    return status;
  }
#endif // _di_controller_entry_preprocess_

#ifndef _di_controller_entry_process_
  f_status_t controller_entry_process(const controller_global_t * const global, controller_cache_t * const cache, const bool failsafe, const bool is_entry) {

    f_status_t status = F_none;
    f_status_t status_lock = F_none;

    f_array_length_t at_i = 0;
    f_array_length_t at_j = 1;

    uint8_t options_force = 0;
    uint8_t options_process = 0;

    controller_entry_t *entry = is_entry ? &global->setting->entry : &global->setting->exit;
    controller_entry_action_t *entry_action = 0;
    controller_entry_actions_t *entry_actions = 0;
    controller_process_t *process = 0;

    // An empty stack is used here because each rule here is the first rule run in the rule's scope.
    const f_array_lengths_t stack = f_array_lengths_t_initialize;

    cache->ats.used = 0;
    cache->stack.used = 0;

    cache->action.line_action = 0;
    cache->action.line_item = 0;
    cache->action.name_action.used = 0;
    cache->action.name_item.used = 0;

    macro_f_array_lengths_t_increase_by(status, cache->ats, controller_common_allocation_small_d)

    if (F_status_is_error(status)) {
      controller_entry_print_error(is_entry, global->main->error, cache->action, F_status_set_fine(status), "macro_f_array_lengths_t_increase_by", F_true, global->thread);

      return status;
    }

    // utilize the ats cache as an item execution stack (at_i is for item index, and at_j (at_i + 1) is for action index).
    cache->ats.array[0] = failsafe ? global->setting->failsafe_item_id : 0;
    cache->ats.array[1] = 0;
    cache->ats.used = 2;

    cache->action.line_item = entry->items.array[cache->ats.array[0]].line;
    cache->action.name_item.used = 0;

    status = f_string_dynamic_append_nulless(entry->items.array[cache->ats.array[0]].name, &cache->action.name_item);

    if (F_status_is_error(status)) {
      controller_entry_print_error(is_entry, global->main->error, cache->action, F_status_set_fine(status), "f_string_dynamic_append_nulless", F_true, global->thread);

      return status;
    }

    if (global->main->parameters.array[controller_parameter_simulate_e].result == f_console_result_found_e || global->main->error.verbosity == f_console_verbosity_verbose_e || global->main->error.verbosity == f_console_verbosity_debug_e) {
      if (global->main->error.verbosity != f_console_verbosity_quiet_e) {
        controller_lock_print(global->main->output.to, global->thread);

        fl_print_format("%rProcessing %r%r item '", global->main->output.to.stream, f_string_eol_s, failsafe ? controller_entry_print_failsafe_s : f_string_empty_s, is_entry ? controller_entry_s : controller_exit_s);
        fl_print_format("%[%Q%]'.%r", global->main->output.to.stream, global->main->context.set.notable, cache->action.name_item, global->main->context.set.notable, f_string_eol_s);

        controller_unlock_print_flush(global->main->output.to, global->thread);
      }
    }

    // The pre-process determines if ready is explicitly specified within the entry file and if it is not start as ready.
    if (global->setting->ready == controller_setting_ready_yes_e) {
      status = controller_perform_ready(global, cache, is_entry);
      if (F_status_is_error(status)) return status;
    }

    while (controller_thread_is_enabled(is_entry, global->thread)) {

      entry_actions = &entry->items.array[cache->ats.array[at_i]].actions;

      for (; cache->ats.array[at_j] < entry_actions->used && controller_thread_is_enabled(is_entry, global->thread); ++cache->ats.array[at_j]) {

        entry_action = &entry_actions->array[cache->ats.array[at_j]];

        cache->action.line_action = entry_action->line;
        cache->action.name_action.used = 0;

        status = f_string_dynamic_append_nulless(controller_entry_action_type_name(entry_action->type), &cache->action.name_action);

        if (F_status_is_error(status)) {
          controller_entry_print_error(is_entry, global->main->error, cache->action, F_status_set_fine(status), "f_string_dynamic_append_nulless", F_true, global->thread);

          return status;
        }

        if (F_status_is_error(entry_action->status)) {
          if (global->main->parameters.array[controller_parameter_simulate_e].result == f_console_result_found_e) {
            if (global->main->error.verbosity != f_console_verbosity_quiet_e) {
              controller_lock_print(global->main->output.to, global->thread);

              fl_print_format("%rThe %r item action '", global->main->output.to.stream, f_string_eol_s, is_entry ? controller_entry_s : controller_exit_s);
              fl_print_format("%[%Q%]", global->main->output.to.stream, global->main->context.set.title, cache->action.name_action, global->main->context.set.title);

              if (entry_action->parameters.used) {
                fl_print_format(" %[", global->main->output.to.stream, global->main->context.set.notable);

                controller_entry_action_parameters_print(global->main->output.to.stream, *entry_action);

                fl_print_format("%]", global->main->output.to.stream, global->main->context.set.notable);
              }

              fl_print_format("' is %[%r%] and is in a ", global->main->output.to.stream, global->main->context.set.notable, entry_action->code & controller_entry_rule_code_require_d ? "required" : "optional", global->main->context.set.notable);

              fl_print_format("%[failed%] state, skipping.%r", global->main->output.to.stream, global->main->context.set.notable, global->main->context.set.notable, global->main->context.set.notable, f_string_eol_s);

              controller_unlock_print_flush(global->main->output.to, global->thread);
            }
          }
          else {
            if ((entry_action->code & controller_entry_rule_code_require_d) && global->main->error.verbosity != f_console_verbosity_quiet_e || !(entry_action->code & controller_entry_rule_code_require_d) && (global->main->warning.verbosity == f_console_verbosity_verbose_e || global->main->warning.verbosity == f_console_verbosity_debug_e)) {
              fl_print_t *output = 0;

              if (entry_action->code & controller_entry_rule_code_require_d) {
                output = &global->main->error;
              }
              else {
                output = &global->main->warning;
              }

              controller_lock_print(output->to, global->thread);

              fl_print_format("%r%[%QThe %r item action '%]", output->to.stream, f_string_eol_s, output->context, output->prefix, is_entry ? controller_entry_s : controller_exit_s, output->context);
              fl_print_format("%[%Q%]", output->to.stream, output->notable, cache->action.name_action, output->notable);


              if (entry_action->parameters.used) {
                fl_print_format(" %[", output->to.stream, global->main->context.set.notable);

                controller_entry_action_parameters_print(output->to.stream, *entry_action);

                fl_print_format("%]", output->to.stream, global->main->context.set.notable);
              }

              if (entry_action->code & controller_entry_rule_code_require_d) {
                fl_print_format("%[' is%] %[required%]", output->to.stream, output->context, output->context, output->notable, output->notable);
              }
              else {
                fl_print_format("%[' is%] %[optional%]", output->to.stream, output->context, output->context, output->notable, output->notable);
              }

              fl_print_format(" %[and is in a%] %[failed%]", output->to.stream, output->context, output->context, output->notable, output->notable);

              if (entry_action->code & controller_entry_rule_code_require_d) {
                fl_print_format(" %[state, aborting.%]%r", output->to.stream, output->context, output->context, f_string_eol_s);
              }
              else {
                fl_print_format(" %[state, skipping.%]%r", output->to.stream, output->context, output->context, f_string_eol_s);
              }

              controller_entry_print_error_cache(is_entry, *output, cache->action);

              controller_unlock_print_flush(output->to, global->thread);
            }

            if (controller_entry_action_type_is_rule(entry_action->type) && entry_action->code & controller_entry_rule_code_require_d) {
              return F_status_is_error(F_require);
            }
          }

          continue;
        }

        if (entry_action->type == controller_entry_action_type_ready_e) {
          if ((entry_action->code & controller_entry_rule_code_wait_d) || global->setting->ready == controller_setting_ready_wait_e) {
            if (global->main->parameters.array[controller_parameter_simulate_e].result == f_console_result_found_e || global->main->error.verbosity == f_console_verbosity_verbose_e || global->main->error.verbosity == f_console_verbosity_debug_e || entry->show == controller_entry_show_init_e) {
              if (global->main->output.verbosity != f_console_verbosity_quiet_e) {
                controller_lock_print(global->main->output.to, global->thread);

                fl_print_format("%rWaiting before processing %r item action '", global->main->output.to.stream, f_string_eol_s, is_entry ? controller_entry_s : controller_exit_s);
                fl_print_format("%[%r%]", global->main->output.to.stream, global->main->context.set.title, controller_ready_s, global->main->context.set.title);
                fl_print_format("'.%r", global->main->output.to.stream, f_string_eol_s);

                controller_unlock_print_flush(global->main->output.to, global->thread);
              }
            }

            if (global->main->parameters.array[controller_parameter_validate_e].result == f_console_result_none_e) {
              status = controller_rule_wait_all(*global, is_entry, F_false, process);
              if (F_status_is_error(status)) return status;
            }
          }

          if (global->setting->ready == controller_setting_ready_yes_e) {
            if (global->main->parameters.array[controller_parameter_simulate_e].result == f_console_result_found_e || global->main->error.verbosity == f_console_verbosity_verbose_e || global->main->error.verbosity == f_console_verbosity_debug_e) {
              if (global->main->output.verbosity != f_console_verbosity_quiet_e) {
                controller_lock_print(global->main->output.to, global->thread);

                fl_print_format("%rIgnoring %r item action '", global->main->output.to.stream, f_string_eol_s, is_entry ? controller_entry_s : controller_exit_s);
                fl_print_format("%[%r%]", global->main->output.to.stream, global->main->context.set.title, controller_ready_s, global->main->context.set.title);
                fl_print_format("', state already is ready.%r", global->main->output.to.stream, f_string_eol_s);

                controller_unlock_print_flush(global->main->output.to, global->thread);
              }
            }
          }
          else {
            if (!failsafe && (global->main->error.verbosity == f_console_verbosity_verbose_e || entry->show == controller_entry_show_init_e) && global->main->parameters.array[controller_parameter_simulate_e].result == f_console_result_none_e) {
              fl_print_format("%rState is now '%[%r%]'.%r", global->main->output.to.stream, f_string_eol_s, global->main->context.set.notable, controller_ready_s, global->main->context.set.notable, f_string_eol_s);
            }

            status = controller_perform_ready(global, cache, is_entry);
            if (F_status_is_error(status)) return status;
          }
        }
        else if (entry_action->type == controller_entry_action_type_item_e) {
          if (entry_action->number == 0 || entry_action->number >= entry->items.used || failsafe && entry_action->number == global->setting->failsafe_item_id) {

            // This should not happen if the pre-process is working as intended, but in case it doesn't, return a critical error to prevent infinite recursion and similar errors.
            if (global->main->error.verbosity != f_console_verbosity_quiet_e) {
              controller_lock_print(global->main->error.to, global->thread);

              fl_print_format("%r%[Invalid %r item index '%]", global->main->error.to.stream, f_string_eol_s, global->main->error.context, is_entry ? controller_entry_s : controller_exit_s, global->main->error.context);
              fl_print_format("%[%un%]", global->main->error.to.stream, global->main->error.notable, entry_action->number, global->main->error.notable);
              fl_print_format("%[' detected.%]%r", global->main->error.to.stream, global->main->error.context, global->main->error.context, f_string_eol_s);

              controller_entry_print_error_cache(is_entry, global->main->error, cache->action);

              controller_unlock_print_flush(global->main->error.to, global->thread);
            }

            return F_status_is_error(F_critical);
          }

          macro_f_array_lengths_t_increase_by(status, cache->ats, controller_common_allocation_small_d)

          if (F_status_is_error(status)) {
            controller_entry_print_error(is_entry, global->main->error, cache->action, F_status_set_fine(status), "macro_f_array_lengths_t_increase_by", F_true, global->thread);

            return status;
          }

          // continue into the requested item.
          cache->ats.array[cache->ats.used] = entry_action->number;
          cache->ats.array[cache->ats.used + 1] = 0;

          at_i = cache->ats.used;
          at_j = cache->ats.used + 1;

          cache->ats.used += 2;

          cache->action.name_action.used = 0;
          cache->action.line_action = 0;

          cache->action.name_item.used = 0;
          cache->action.line_item = entry->items.array[cache->ats.array[at_i]].line;

          status = f_string_dynamic_append_nulless(entry->items.array[cache->ats.array[at_i]].name, &cache->action.name_item);

          if (F_status_is_error(status)) {
            controller_entry_print_error(is_entry, global->main->error, cache->action, F_status_set_fine(status), "f_string_dynamic_append_nulless", F_true, global->thread);

            return status;
          }

          if (global->main->parameters.array[controller_parameter_simulate_e].result == f_console_result_found_e || global->main->error.verbosity == f_console_verbosity_verbose_e || global->main->error.verbosity == f_console_verbosity_debug_e) {
            if (global->main->output.verbosity != f_console_verbosity_quiet_e) {
              controller_lock_print(global->main->output.to, global->thread);

              fl_print_format("%rProcessing %r item '", global->main->output.to.stream, f_string_eol_s, is_entry ? controller_entry_s : controller_exit_s);
              fl_print_format("%[%Q%]", global->main->output.to.stream, global->main->context.set.title, cache->action.name_item, global->main->context.set.title);
              fl_print_format("'.%r", global->main->output.to.stream, f_string_eol_s);

              controller_unlock_print_flush(global->main->output.to, global->thread);
            }
          }

          // Exit inner loop to force restarting and start processing the requested item.
          break;
        }
        else if (entry_action->type == controller_entry_action_type_consider_e || controller_entry_action_type_is_rule(entry_action->type)) {
          status_lock = controller_lock_write(is_entry, global->thread, &global->thread->lock.rule);

          if (F_status_is_error(status_lock)) {
            controller_lock_print_error_critical(global->main->error, F_status_set_fine(status_lock), F_false, global->thread);

            break;
          }

          status = controller_rules_increase(&global->setting->rules);

          f_thread_unlock(&global->thread->lock.rule);

          if (F_status_is_error(status)) {
            controller_entry_print_error(is_entry, global->main->error, cache->action, F_status_set_fine(status), "controller_rules_increase", F_true, global->thread);

            return status;
          }

          const f_array_length_t id_rule_length = entry_action->parameters.array[0].used + entry_action->parameters.array[1].used + 1;
          f_char_t id_rule_name[id_rule_length + 1];
          const f_string_static_t alias_rule = macro_f_string_static_t_initialize(id_rule_name, 0, id_rule_length);

          memcpy(id_rule_name, entry_action->parameters.array[0].string, sizeof(f_char_t) * entry_action->parameters.array[0].used);
          memcpy(id_rule_name + entry_action->parameters.array[0].used + 1, entry_action->parameters.array[1].string, sizeof(f_char_t) * entry_action->parameters.array[1].used);

          id_rule_name[entry_action->parameters.array[0].used] = f_path_separator_s.string[0];
          id_rule_name[id_rule_length] = 0;

          status_lock = controller_lock_read(is_entry, global->thread, &global->thread->lock.rule);

          if (F_status_is_error(status_lock)) {
            controller_lock_print_error_critical(global->main->error, F_status_set_fine(status_lock), F_true, global->thread);

            break;
          }

          status = controller_rule_find(alias_rule, global->setting->rules, 0);

          f_thread_unlock(&global->thread->lock.rule);

          if (global->main->parameters.array[controller_parameter_simulate_e].result == f_console_result_found_e || global->main->error.verbosity == f_console_verbosity_verbose_e || global->main->error.verbosity == f_console_verbosity_debug_e || (entry->show == controller_entry_show_init_e && entry_action->type != controller_entry_action_type_consider_e)) {
            if (global->main->output.verbosity != f_console_verbosity_quiet_e) {
              controller_lock_print(global->main->output.to, global->thread);

              fl_print_format("%r%r %r item rule ", global->main->output.to.stream, f_string_eol_s, entry_action->type == controller_entry_action_type_consider_e ? controller_entry_print_considering_s : controller_entry_print_processing_s, is_entry ? controller_entry_s : controller_exit_s);
              fl_print_format("'%[%Q%]'", global->main->output.to.stream, global->main->context.set.title, alias_rule, global->main->context.set.title);

              if (entry->show == controller_entry_show_init_e && global->main->parameters.array[controller_parameter_simulate_e].result == f_console_result_none_e) {
                fl_print_format(" [%[%r%]]", global->main->output.to.stream, global->main->context.set.notable, entry_action->code == controller_entry_rule_code_asynchronous_d ? controller_asynchronous_s : controller_synchronous_s, global->main->context.set.notable);

                if (entry_action->code == controller_entry_rule_code_wait_d) {
                  fl_print_format(" [%[%r%]]", global->main->output.to.stream, global->main->context.set.notable, controller_wait_s, global->main->context.set.notable);
                }

                if (entry_action->code == controller_entry_rule_code_require_d) {
                  fl_print_format(" [%[%r%]]", global->main->output.to.stream, global->main->context.set.notable, controller_required_s, global->main->context.set.notable);
                }
              }

              fl_print_format(".%r", global->main->output.to.stream, f_string_eol_s);

              controller_unlock_print_flush(global->main->output.to, global->thread);
            }
          }

          if (!controller_thread_is_enabled(is_entry, global->thread)) break;

          // The rule is not yet loaded, ensure that it is loaded.
          if (status != F_true) {

            // Rule execution will re-use the existing cache, so save the current cache.
            const f_array_length_t cache_line_action = cache->action.line_action;
            const f_array_length_t cache_line_item = cache->action.line_item;

            const f_array_length_t cache_name_action_used = cache->action.name_action.used;
            const f_array_length_t cache_name_item_used = cache->action.name_item.used;
            const f_array_length_t cache_name_file_used = cache->action.name_file.used;

            f_char_t cache_name_action[cache_name_action_used];
            f_char_t cache_name_item[cache_name_item_used];
            f_char_t cache_name_file[cache_name_file_used];

            memcpy(cache_name_action, cache->action.name_action.string, sizeof(f_char_t) * cache->action.name_action.used);
            memcpy(cache_name_item, cache->action.name_item.string, sizeof(f_char_t) * cache->action.name_item.used);
            memcpy(cache_name_file, cache->action.name_file.string, sizeof(f_char_t) * cache->action.name_file.used);

            status_lock = controller_lock_write(is_entry, global->thread, &global->thread->lock.rule);

            if (F_status_is_fine(status_lock)) {
              status = controller_rule_read(*global, is_entry, alias_rule, cache, entry, &global->setting->rules.array[global->setting->rules.used]);
            }

            // Restore cache.
            memcpy(cache->action.name_action.string, cache_name_action, sizeof(f_char_t) * cache_name_action_used);
            memcpy(cache->action.name_item.string, cache_name_item, sizeof(f_char_t) * cache_name_item_used);
            memcpy(cache->action.name_file.string, cache_name_file, sizeof(f_char_t) * cache_name_file_used);

            cache->action.name_action.string[cache_name_action_used] = 0;
            cache->action.name_item.string[cache_name_item_used] = 0;
            cache->action.name_file.string[cache_name_file_used] = 0;

            cache->action.name_action.used = cache_name_action_used;
            cache->action.name_item.used = cache_name_item_used;
            cache->action.name_file.used = cache_name_file_used;

            cache->action.line_action = cache_line_action;
            cache->action.line_item = cache_line_item;

            if (F_status_is_error(status_lock)) {
              controller_lock_print_error_critical(global->main->error, F_status_set_fine(status_lock), F_false, global->thread);

              break;
            }

            if (F_status_set_fine(status) == F_interrupt || !controller_thread_is_enabled(is_entry, global->thread)) {
              f_thread_unlock(&global->thread->lock.rule);

              break;
            }

            if (F_status_is_error(status)) {
              if (global->main->error.verbosity != f_console_verbosity_quiet_e) {
                controller_lock_print(global->main->error.to, global->thread);

                controller_entry_print_error_cache(is_entry, global->main->error, cache->action);

                controller_unlock_print_flush(global->main->error.to, global->thread);
              }

              // Designate the action as failed.
              entry_action->status = F_status_set_error(F_failure);

              if (global->main->parameters.array[controller_parameter_simulate_e].result == f_console_result_none_e) {
                f_thread_unlock(&global->thread->lock.rule);

                if (entry_action->code & controller_entry_rule_code_require_d) {
                  return F_status_set_error(F_require);
                }

                ++cache->ats.array[at_j];
                break;
              }
            }
            else {
              ++global->setting->rules.used;
            }

            f_thread_unlock(&global->thread->lock.rule);
          }

          if (F_status_is_error_not(status)) {
            options_force = 0;
            options_process = 0;

            if (global->main->parameters.array[controller_parameter_simulate_e].result == f_console_result_found_e) {
              options_process |= controller_process_option_simulate_d;
            }

            if (entry_action->code & controller_entry_rule_code_require_d) {
              options_process |= controller_process_option_require_d;
            }

            if (entry_action->code & controller_entry_rule_code_wait_d) {
              options_process |= controller_process_option_wait_d;
            }

            if (global->main->parameters.array[controller_parameter_validate_e].result == f_console_result_found_e) {
              options_process |= controller_process_option_validate_d;
            }

            if (entry_action->code & controller_entry_rule_code_asynchronous_d) {
              if (global->main->parameters.array[controller_parameter_validate_e].result == f_console_result_none_e) {
                options_force |= controller_process_option_asynchronous_d;
              }

              options_process |= controller_process_option_asynchronous_d;
            }

            status = controller_rule_process_begin(*global, options_force, alias_rule, controller_entry_action_type_to_rule_action_type(entry_action->type), options_process, is_entry ? controller_process_type_entry_e : controller_process_type_exit_e, stack, *cache);

            if (F_status_set_fine(status) == F_memory_not || status == F_child || F_status_set_fine(status) == F_interrupt) {
              break;
            }

            if (F_status_is_error(status) && global->main->parameters.array[controller_parameter_simulate_e].result == f_console_result_none_e && (entry_action->code & controller_entry_rule_code_require_d)) {
              return F_status_set_error(F_require);
            }
          }
        }
        else if (entry_action->type == controller_entry_action_type_execute_e) {
          if (global->main->parameters.array[controller_parameter_simulate_e].result == f_console_result_found_e || global->main->error.verbosity == f_console_verbosity_verbose_e || global->main->error.verbosity == f_console_verbosity_debug_e || entry->show == controller_entry_show_init_e) {
            if (global->main->output.verbosity != f_console_verbosity_quiet_e) {
              controller_lock_print(global->main->output.to, global->thread);

              fl_print_format("%r%Q is executing '", global->main->output.to.stream, f_string_eol_s, is_entry ? controller_entry_s : controller_exit_s);

              for (f_array_length_t k = 0; k < entry_action->parameters.used; ++k) {

                fl_print_format("%[%Q%]", global->main->output.to.stream, global->main->context.set.title, entry_action->parameters.array[k], global->main->context.set.title);

                if (k + 1 < entry_action->parameters.used) {
                  f_print_dynamic_raw(f_string_space_s, global->main->output.to.stream);
                }
              } // for

              fl_print_format("'.%r", global->main->output.to.stream, f_string_eol_s);

              controller_unlock_print_flush(global->main->output.to, global->thread);
            }
          }

          if (global->main->parameters.array[controller_parameter_simulate_e].result == f_console_result_found_e) {
            return F_execute;
          }

          controller_thread_process_cancel(*global, is_entry, is_entry ? controller_thread_cancel_execute_e : controller_thread_cancel_exit_execute_e, process);

          int result = 0;
          int option = FL_execute_parameter_option_path_d;

          if (entry->session == controller_entry_session_new_e) {
            option |= FL_execute_parameter_option_session_d;
          }

          status = fll_execute_into(f_string_empty_s, entry_action->parameters, option, 0, (void *) &result);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_file_found_not) {
              if (global->main->error.verbosity != f_console_verbosity_quiet_e) {
                controller_lock_print(global->main->error.to, global->thread);

                fl_print_format("%r%[%QExecution failed, unable to find program or script '%]", global->main->error.to.stream, f_string_eol_s, global->main->error.context, global->main->error.prefix, global->main->error.context);
                fl_print_format("%[%Q%]", global->main->error.to.stream, global->main->error.notable, entry_action->parameters.array[0], global->main->error.notable);
                fl_print_format("%['.%]%r", global->main->error.to.stream, global->main->error.context, global->main->error.context, f_string_eol_s);

                controller_entry_print_error_cache(is_entry, global->main->error, cache->action);

                controller_unlock_print_flush(global->main->error.to, global->thread);
              }
            }
            else {
              controller_entry_print_error(is_entry, global->main->error, cache->action, F_status_set_fine(status), "fll_execute_into", F_true, global->thread);
            }

            return F_status_set_error(F_execute);
          }
          else if (result != 0) {
            if (global->main->error.verbosity != f_console_verbosity_quiet_e) {
              controller_lock_print(global->main->error.to, global->thread);

              fl_print_format("%r%[%QExecution failed with return value of '%]", global->main->error.to.stream, f_string_eol_s, global->main->error.context, global->main->error.prefix, global->main->error.context);
              fl_print_format("%[%i%]", global->main->error.to.stream, global->main->error.notable, result, global->main->error.notable);
              fl_print_format("$['.%]%r", global->main->error.to.stream, global->main->error.context, global->main->error.context, f_string_eol_s);

              controller_entry_print_error_cache(is_entry, global->main->error, cache->action);

              controller_unlock_print_flush(global->main->error.to, global->thread);
            }

            return F_status_set_error(F_execute);
          }

          return F_execute;
        }
        else if (entry_action->type == controller_entry_action_type_timeout_e) {
          if (entry_action->code == controller_entry_timeout_code_kill_d) {
            entry->timeout_kill = entry_action->number;

            controller_entry_preprocess_print_simulate_setting_value(*global, is_entry, controller_timeout_s, controller_kill_s, entry->items.array[global->setting->failsafe_item_id].name, controller_entry_print_suffix_megatime_s);
          }
          else if (entry_action->code == controller_entry_timeout_code_start_d) {
            entry->timeout_start = entry_action->number;

            controller_entry_preprocess_print_simulate_setting_value(*global, is_entry, controller_timeout_s, controller_start_s, entry->items.array[global->setting->failsafe_item_id].name, controller_entry_print_suffix_megatime_s);
          }
          else if (entry_action->code == controller_entry_timeout_code_stop_d) {
            entry->timeout_stop = entry_action->number;

            controller_entry_preprocess_print_simulate_setting_value(*global, is_entry, controller_timeout_s, controller_stop_s, entry->items.array[global->setting->failsafe_item_id].name, controller_entry_print_suffix_megatime_s);
          }
        }
        else if (entry_action->type == controller_entry_action_type_failsafe_e) {

          if (failsafe) {
            if (global->main->warning.verbosity == f_console_verbosity_debug_e) {
              controller_lock_print(global->main->warning.to, global->thread);

              fl_print_format("%r%[%QFailsafe may not be specified when running in failsafe, ignoring.%]%r", global->main->warning.to.stream, f_string_eol_s, global->main->warning.context, global->main->warning.prefix, global->main->warning.context, f_string_eol_s);

              controller_entry_print_error_cache(is_entry, global->main->warning, cache->action);

              controller_unlock_print_flush(global->main->warning.to, global->thread);
            }
          }
          else {
            if (entry_action->number == 0 || entry_action->number >= entry->items.used) {

              // This should not happen if the pre-process is working as designed, but in case it doesn't, return a critical error to prevent infinite recursion and similar errors.
              if (global->main->error.verbosity != f_console_verbosity_quiet_e) {
                controller_lock_print(global->main->error.to, global->thread);

                fl_print_format("%r%[%QInvalid %r item index '%]", global->main->error.to.stream, f_string_eol_s, global->main->error.context, global->main->error.prefix, is_entry ? controller_entry_s : controller_exit_s, global->main->error.context);
                fl_print_format("%[%un%]", global->main->error.to.stream, global->main->error.notable, entry_action->number, global->main->error.notable);
                fl_print_format("%[' detected.%]%r", global->main->error.to.stream, global->main->error.context, global->main->error.context, f_string_eol_s);

                controller_entry_print_error_cache(is_entry, global->main->error, cache->action);

                controller_unlock_print_flush(global->main->error.to, global->thread);
              }

              return F_status_is_error(F_critical);
            }
            else {
              global->setting->flag |= controller_setting_flag_failsafe_e;
              global->setting->failsafe_item_id = entry_action->number;

              controller_entry_preprocess_print_simulate_setting_value(*global, is_entry, controller_failsafe_s, f_string_empty_s, entry->items.array[global->setting->failsafe_item_id].name, f_string_empty_s);
            }
          }
        }
      } // for

      if (status == F_child || F_status_set_fine(status) == F_interrupt) break;

      cache->action.line_action = 0;
      cache->action.name_action.used = 0;

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_memory_not || F_status_set_fine(status) == F_require) {
          break;
        }
      }

      // End of actions found, so drop to previous loop in stack.
      if (cache->ats.array[at_j] == entry_actions->used) {

        // All actions for "main" are processed so there is nothing left to do.
        if (at_i == 0) break;

        at_i -= 2;
        at_j -= 2;

        cache->ats.used -= 2;
        ++cache->ats.array[at_j];

        cache->action.line_item = entry->items.array[cache->ats.array[at_i]].line;
        cache->action.name_item.used = 0;

        status = f_string_dynamic_append_nulless(entry->items.array[cache->ats.array[at_i]].name, &cache->action.name_item);

        if (F_status_is_error(status)) {
          controller_entry_print_error(is_entry, global->main->error, cache->action, F_status_set_fine(status), "f_string_dynamic_append_nulless", F_true, global->thread);

          break;
        }
      }
    } // while

    if (!controller_thread_is_enabled(is_entry, global->thread)) {
      return F_status_set_error(F_interrupt);
    }

    if (status == F_child) {
      return status;
    }

    if (F_status_is_error(status_lock)) {
      return status_lock;
    }

    // Check to see if any required processes failed, but do not do this if already operating in failsafe.
    if (F_status_is_error_not(status) && !failsafe && global->main->parameters.array[controller_parameter_validate_e].result == f_console_result_none_e) {
      const f_status_t status_wait = controller_rule_wait_all(*global, is_entry, F_true, 0);

      if (F_status_is_error(status_wait)) {
        return status_wait;
      }

      if (status_wait == F_require) {
        return F_status_set_error(F_require);
      }
    }

    if ((global->main->parameters.array[controller_parameter_simulate_e].result == f_console_result_found_e && global->main->error.verbosity != f_console_verbosity_quiet_e) || global->main->error.verbosity == f_console_verbosity_verbose_e) {
      controller_lock_print(global->main->output.to, global->thread);

      fl_print_format("%rDone processing %r item '", global->main->output.to.stream, f_string_eol_s, is_entry ? controller_entry_s : controller_exit_s);
      fl_print_format("%[%r%]", global->main->output.to.stream, global->main->context.set.title, controller_main_s, global->main->context.set.title);
      fl_print_format("'.%r", global->main->output.to.stream, f_string_eol_s);

      // failsafe should not print the extra newline because the failure exit from controller_main should handle this.
      if (!failsafe) {
        f_print_dynamic_raw(f_string_eol_s, global->main->output.to.stream);
      }

      controller_unlock_print_flush(global->main->output.to, global->thread);
    }

    return status;
  }
#endif // _di_controller_entry_process_

#ifndef _di_controller_entry_read_
  f_status_t controller_entry_read(const controller_global_t global, const bool is_entry, controller_cache_t * const cache) {

    f_status_t status = F_none;

    controller_entry_t *entry = is_entry ? &global.setting->entry : &global.setting->exit;

    entry->status = F_known_not;
    entry->items.used = 0;

    if (global.main->as_init) {
      entry->session = controller_entry_session_new_e;
    }
    else {
      entry->session = controller_entry_session_same_e;
    }

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
      status = controller_file_load(global, F_true, controller_entries_s, global.setting->name_entry, controller_entry_s, cache);
    }
    else {
      status = controller_file_load(global, F_false, controller_exits_s, global.setting->name_entry, controller_exit_s, cache);

      if (status == F_file_found_not) {
        return F_file_found_not;
      }
    }

    if (F_status_is_error_not(status)) {
      if (cache->buffer_file.used) {
        controller_state_interrupt_t custom = macro_controller_state_interrupt_t_initialize(is_entry, global.thread);
        f_state_t state = macro_f_state_t_initialize(controller_common_allocation_large_d, controller_common_allocation_small_d, 0, 0, &controller_thread_signal_state_fss, 0, (void *) &custom, 0);
        f_string_range_t range = macro_f_string_range_t_initialize2(cache->buffer_file.used);

        status = fll_fss_basic_list_read(cache->buffer_file, state, &range, &cache->object_items, &cache->content_items, &cache->delimits, 0, &cache->comments);

        if (F_status_is_error(status)) {
          controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "fll_fss_basic_list_read", F_true);
        }
        else {
          status = f_fss_apply_delimit(state, cache->delimits, &cache->buffer_file);

          if (F_status_is_error(status)) {
            controller_entry_print_error(is_entry, global.main->error, cache->action, F_status_set_fine(status), "f_fss_apply_delimit", F_true, global.thread);
          }
        }
      }
      else {
        if (global.main->error.verbosity != f_console_verbosity_quiet_e) {
          controller_lock_print(global.main->error.to, global.thread);

          fll_print_format("%r%[%QThe %r file is empty.%]%r", global.main->error.to.stream, f_string_eol_s, global.main->error.context, global.main->error.prefix, is_entry ? controller_entry_s : is_entry ? controller_entry_s : controller_exit_s, global.main->error.context, f_string_eol_s);

          controller_unlock_print_flush(global.main->error.to, global.thread);
        }

        status = F_status_set_error(F_data_not);
      }
    }

    if (F_status_is_error_not(status) && cache->object_items.used) {
      status = controller_entry_items_increase_by(cache->object_items.used, &entry->items);

      if (F_status_is_error(status)) {
        controller_entry_print_error(is_entry, global.main->error, cache->action, F_status_set_fine(status), "controller_entry_items_increase_by", F_true, global.thread);
      }
      else {

        // 0x1 = main found, 0x2 = found existing.
        uint8_t code = 0;

        f_string_range_t *range = 0;

        f_array_length_t at = 0;
        f_array_length_t i = 0;
        f_array_length_t j = 0;

        f_state_t state = f_state_t_initialize;

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
            controller_entry_print_error(is_entry, global.main->error, cache->action, F_status_set_fine(status), "controller_entry_items_increase_by", F_true, global.thread);

            break;
          }

          status = f_string_dynamic_partial_append(cache->buffer_file, cache->object_items.array[i], &cache->action.name_item);

          if (F_status_is_error(status)) {
            controller_entry_print_error(is_entry, global.main->error, cache->action, F_status_set_fine(status), "f_string_dynamic_partial_append", F_true, global.thread);

            break;
          }

          status = f_fss_count_lines(state, cache->buffer_file, cache->object_items.array[i].start, &cache->action.line_item);

          if (F_status_is_error(status)) {
            controller_entry_print_error(is_entry, global.main->error, cache->action, F_status_set_fine(status), "f_fss_count_lines", F_true, global.thread);

            break;
          }

          ++cache->action.line_item;

          for (j = (code & 0x1) ? 1 : 0; j < entry->items.used; ++j) {

            if (fl_string_dynamic_compare(entry->items.array[j].name, cache->action.name_item) == F_equal_to) {
              if (global.main->warning.verbosity == f_console_verbosity_debug_e) {
                controller_lock_print(global.main->warning.to, global.thread);

                fl_print_format("%r%[%QIgnoring duplicate %r item '%]", global.main->warning.to.stream, f_string_eol_s, global.main->warning.context, global.main->warning.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->warning.context);
                fl_print_format("%[%Q%]", global.main->warning.to.stream, global.main->warning.notable, cache->action.name_file, global.main->warning.notable);
                fl_print_format("%['.%]%r", global.main->warning.to.stream, global.main->warning.context, global.main->warning.context, f_string_eol_s);

                controller_entry_print_error_cache(is_entry, global.main->warning, cache->action);

                controller_unlock_print_flush(global.main->warning.to, global.thread);
              }

              code |= 0x2;

              break;
            }
          } // for

          if (code & 0x2) continue;

          range = &cache->content_items.array[i].array[0];

          if (fl_string_dynamic_compare(controller_main_s, cache->action.name_item) == F_equal_to) {
            code |= 0x1;

            at = 0;

            if (!entry->items.used) {
              entry->items.used = 1;
            }
          }
          else if (fl_string_dynamic_compare(controller_setting_s, cache->action.name_item) == F_equal_to) {
            status = controller_entry_settings_read(global, is_entry, *range, cache);

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

          status = f_string_dynamic_append_nulless(cache->action.name_item, &entry->items.array[at].name);

          if (F_status_is_error(status)) {
            controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "f_string_dynamic_append_nulless", F_true);

            break;
          }

          status = controller_entry_actions_read(global, is_entry, *range, cache, &entry->items.array[at].actions);

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) != F_interrupt) {
              controller_lock_print(global.main->error.to, global.thread);

              controller_entry_print_error_cache(is_entry, global.main->error, cache->action);

              controller_unlock_print_flush(global.main->error.to, global.thread);
            }

            if (F_status_set_fine(status) == F_memory_not) {
              break;
            }
          }
        } // for

        if (is_entry && F_status_set_fine(status) == F_interrupt) {
          return status;
        }

        if (F_status_is_error_not(status)) {
          cache->action.name_action.used = 0;
          cache->action.name_item.used = 0;

          if (!(code & 0x1)) {
            if (global.main->error.verbosity != f_console_verbosity_quiet_e) {
              controller_lock_print(global.main->error.to, global.thread);

              fl_print_format("%r%[%QThe required %r item '%]", global.main->error.to.stream, f_string_eol_s, global.main->error.context, global.main->error.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->error.context);
              fl_print_format("%[%r%]", global.main->error.to.stream, global.main->error.notable, controller_main_s, global.main->error.notable);
              fl_print_format("%[' was not found.%]%r", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s);

              controller_unlock_print_flush(global.main->error.to, global.thread);
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
                  return F_status_set_error(F_interrupt);
                }

                action = &entry->items.array[i].actions.array[j];

                // Only process actions that don't already have an error.
                if (F_status_is_error(action->status)) continue;

                if (action->type == controller_entry_action_type_failsafe_e || action->type == controller_entry_action_type_item_e) {
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

                    status = f_string_dynamic_append_nulless(entry->items.array[i].name, &cache->action.name_item);

                    if (F_status_is_error(status)) {
                      controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "f_string_dynamic_append_nulless", F_true);

                      break;
                    }

                    if (global.main->error.verbosity != f_console_verbosity_quiet_e) {
                      controller_lock_print(global.main->error.to, global.thread);

                      fl_print_format("%r%[%QThe required %r item '%]", global.main->error.to.stream, f_string_eol_s, global.main->error.context, global.main->error.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->error.context);
                      fl_print_format("%[%Q%]", global.main->error.to.stream, global.main->error.notable, action->parameters.array[0], global.main->error.notable);
                      fl_print_format("%[' does not exist.%]%r", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s);

                      controller_entry_print_error_cache(is_entry, global.main->error, cache->action);

                      controller_unlock_print_flush(global.main->error.to, global.thread);
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
        controller_entry_print_error_cache(is_entry, global.main->error, cache->action);
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
  f_status_t controller_entry_settings_read(const controller_global_t global, const bool is_entry, const f_string_range_t content_range, controller_cache_t * const cache) {

    f_status_t status = F_none;

    {
      controller_state_interrupt_t custom = macro_controller_state_interrupt_t_initialize(is_entry, global.thread);
      f_state_t state = macro_f_state_t_initialize(controller_common_allocation_large_d, controller_common_allocation_small_d, 0, 0, &controller_thread_signal_state_fss, 0, (void *) &custom, 0);
      f_string_range_t range = content_range;

      status = fll_fss_extended_read(cache->buffer_file, state, &range, &cache->object_actions, &cache->content_actions, 0, 0, &cache->delimits, 0);
    }

    if (F_status_is_error(status)) {
      controller_entry_print_error(is_entry, global.main->error, cache->action, F_status_set_fine(status), "fll_fss_extended_read", F_true, global.thread);

      return status;
    }

    {
      f_state_t state = f_state_t_initialize;

      status = f_fss_apply_delimit(state, cache->delimits, &cache->buffer_file);
    }

    if (F_status_is_error(status)) {
      controller_entry_print_error(is_entry, global.main->error, cache->action, F_status_set_fine(status), "f_fss_apply_delimit", F_true, global.thread);

      return status;
    }

    cache->delimits.used = 0;

    f_array_length_t i = 0;
    f_array_length_t line = 0;

    controller_entry_t *entry = is_entry ? &global.setting->entry : &global.setting->exit;
    f_state_t state = f_state_t_initialize;

    for (; i < cache->object_actions.used; ++i) {

      status = f_fss_count_lines(state, cache->buffer_file, cache->object_actions.array[i].start, &cache->action.line_action);

      if (F_status_is_error(status)) {
        controller_entry_print_error(is_entry, global.main->error, cache->action, F_status_set_fine(status), "f_fss_count_lines", F_true, global.thread);

        break;
      }

      line = ++cache->action.line_action;
      cache->action.name_action.used = 0;

      status = fl_string_dynamic_partial_rip_nulless(cache->buffer_file, cache->object_actions.array[i], &cache->action.name_action);

      if (F_status_is_error(status)) {
        controller_entry_print_error(is_entry, global.main->error, cache->action, F_status_set_fine(status), "fl_string_dynamic_partial_rip_nulless", F_true, global.thread);

        break;
      }

      if (is_entry && fl_string_dynamic_compare(controller_control_s, cache->action.name_action) == F_equal_to) {
        if (cache->content_actions.array[i].used != 1) {
          controller_entry_settings_read_print_setting_requires_exactly(global, is_entry, *cache, 1);

          continue;
        }

        cache->action.generic.used = 0;
        global.setting->path_control.used = 0;

        status = fl_string_dynamic_partial_rip_nulless(cache->buffer_file, cache->content_actions.array[i].array[0], &cache->action.generic);

        if (F_status_is_error(status)) {
          controller_entry_print_error(is_entry, global.main->error, cache->action, F_status_set_fine(status), "fl_string_dynamic_partial_rip_nulless", F_true, global.thread);

          break;
        }

        status = controller_path_canonical_relative(global.setting, cache->action.generic, &global.setting->path_control);

        if (F_status_is_error(status)) {
          controller_entry_print_error_file(is_entry, global.main->error, cache->action, F_status_set_fine(status), "controller_path_canonical_relative", F_true, cache->action.generic, f_file_operation_analyze_s, fll_error_file_type_path_e, global.thread);

          global.setting->path_control.used = 0;

          continue;
        }
      }
      else if (is_entry && fl_string_dynamic_compare(controller_control_group_s, cache->action.name_action) == F_equal_to) {
        gid_t number = 0;

        status = controller_get_id_group(cache->buffer_file, cache->content_actions.array[i].array[0], cache, &number);

        if (F_status_is_error(status)) {
          status = F_status_set_fine(status);

          if (status == F_exist_not) {
            controller_entry_setting_read_print_error_with_range(is_entry, global.main->error, " has an invalid group", cache->content_actions.array[i].array[0], ", because no group was found by that name", global.thread, cache);
          }
          else if (status == F_number_too_large) {
            controller_entry_setting_read_print_error_with_range(is_entry, global.main->error, " has an invalid group", cache->content_actions.array[i].array[0], ", because the given ID is too large", global.thread, cache);
          }
          else if (status == F_number) {
            controller_entry_setting_read_print_error_with_range(is_entry, global.main->error, " has an invalid group", cache->content_actions.array[i].array[0], ", because the given ID is not a valid supported number", global.thread, cache);
          }
          else {
            controller_entry_print_error(is_entry, global.main->error, cache->action, F_status_set_fine(status), "controller_get_id_group", F_true, global.thread);
          }

          continue;
        }

        global.setting->control.group = number;
        global.setting->control.flag |= controller_control_flag_has_group_e;
      }
      else if (is_entry && fl_string_dynamic_compare(controller_control_mode_s, cache->action.name_action) == F_equal_to) {
        mode_t mode = 0;
        uint8_t replace = 0;
        f_file_mode_t mode_file = f_file_mode_t_initialize;

        cache->action.generic.used = 0;

        status = fl_string_dynamic_partial_rip_nulless(cache->buffer_file, cache->content_actions.array[i].array[0], &cache->action.generic);

        if (F_status_is_error(status)) {
          controller_entry_print_error(is_entry, global.main->error, cache->action, F_status_set_fine(status), "fl_string_dynamic_partial_rip_nulless", F_true, global.thread);

          break;
        }

        status = f_file_mode_from_string(cache->action.generic, global.main->umask, &mode_file, &replace);

        if (F_status_is_error(status)) {
          controller_entry_setting_read_print_error_with_range(is_entry, global.main->error, " has an unsupported mode", cache->content_actions.array[i].array[0], ", because the format is unknown or contains invalid data", global.thread, cache);

          continue;
        }

        status = f_file_mode_to_mode(mode_file, &mode);

        if (F_status_is_error(status)) {
          controller_entry_print_error(is_entry, global.main->error, cache->action, F_status_set_fine(status), "f_file_mode_to_mode", F_true, global.thread);

          continue;
        }

        global.setting->control.mode = mode;
        global.setting->control.flag |= controller_control_flag_has_mode_e;
      }
      else if (is_entry && fl_string_dynamic_compare(controller_control_user_s, cache->action.name_action) == F_equal_to) {
        uid_t number = 0;

        status = controller_get_id_user(cache->buffer_file, cache->content_actions.array[i].array[0], cache, &number);

        if (F_status_is_error(status)) {
          status = F_status_set_fine(status);

          if (status == F_exist_not) {
            controller_entry_setting_read_print_error_with_range(is_entry, global.main->error, " has an invalid user", cache->content_actions.array[i].array[0], ", because no user was found by that name", global.thread, cache);
          }
          else if (status == F_number_too_large) {
            controller_entry_setting_read_print_error_with_range(is_entry, global.main->error, " has an invalid user", cache->content_actions.array[i].array[0], ", because the given ID is too large", global.thread, cache);
          }
          else if (status == F_number) {
            controller_entry_setting_read_print_error_with_range(is_entry, global.main->error, " has an invalid user", cache->content_actions.array[i].array[0], ", because the given ID is not a valid supported number", global.thread, cache);
          }
          else {
            controller_entry_print_error(is_entry, global.main->error, cache->action, F_status_set_fine(status), "controller_get_id_user", F_true, global.thread);
          }

          continue;
        }

        global.setting->control.user = number;
        global.setting->control.flag |= controller_control_flag_has_user_e;
      }
      else if (fl_string_dynamic_compare(controller_define_s, cache->action.name_action) == F_equal_to) {
        if (cache->content_actions.array[i].used != 2) {
          controller_entry_settings_read_print_setting_requires_exactly(global, is_entry, *cache, 1);

          continue;
        }

        status = controller_entry_settings_read_map(cache->buffer_file, cache->content_actions.array[i], &entry->define);

        if (F_status_is_error(status)) {
          controller_entry_print_error(is_entry, global.main->error, cache->action, F_status_set_fine(status), "controller_entry_settings_read_map", F_true, global.thread);

          continue;
        }
      }
      else if (is_entry && fl_string_dynamic_compare(controller_mode_s, cache->action.name_action) == F_equal_to) {
        if (cache->content_actions.array[i].used != 1) {
          controller_entry_settings_read_print_setting_requires_exactly(global, is_entry, *cache, 1);

          continue;
        }

        if (fl_string_dynamic_partial_compare_string(controller_service_s.string, cache->buffer_file, controller_service_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          global.setting->mode = controller_setting_mode_service_e;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_program_s.string, cache->buffer_file, controller_program_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          global.setting->mode = controller_setting_mode_program_e;
        }
        else {
          controller_entry_settings_read_print_setting_unknown_action_value(global, is_entry, *cache, i);

          continue;
        }
      }
      else if (fl_string_dynamic_compare(controller_parameter_s, cache->action.name_action) == F_equal_to) {
        if (cache->content_actions.array[i].used != 2) {
          controller_entry_settings_read_print_setting_requires_exactly(global, is_entry, *cache, 1);

          continue;
        }

        status = controller_entry_settings_read_map(cache->buffer_file, cache->content_actions.array[i], &entry->parameter);

        if (F_status_is_error(status)) {
          controller_entry_print_error(is_entry, global.main->error, cache->action, F_status_set_fine(status), "controller_entry_settings_read_map", F_true, global.thread);

          continue;
        }
      }
      else if (fl_string_dynamic_compare(controller_pid_s, cache->action.name_action) == F_equal_to) {
        if (cache->content_actions.array[i].used != 1) {
          controller_entry_settings_read_print_setting_requires_exactly(global, is_entry, *cache, 1);

          continue;
        }

        if (fl_string_dynamic_partial_compare_string(controller_disable_s.string, cache->buffer_file, controller_disable_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          entry->pid = controller_entry_pid_disable_e;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_ready_s.string, cache->buffer_file, controller_ready_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          entry->pid = controller_entry_pid_ready_e;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_require_s.string, cache->buffer_file, controller_require_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          entry->pid = controller_entry_pid_require_e;
        }
        else {
          controller_entry_settings_read_print_setting_unknown_action_value(global, is_entry, *cache, i);

          continue;
        }
      }
      else if (is_entry && fl_string_dynamic_compare(controller_pid_file_s, cache->action.name_action) == F_equal_to) {
        if (cache->content_actions.array[i].used != 1) {
          controller_entry_settings_read_print_setting_requires_exactly(global, is_entry, *cache, 1);

          continue;
        }

        if (global.main->parameters.array[controller_parameter_pid_e].result == f_console_result_additional_e) {
          controller_entry_settings_read_print_setting_ignored(global, is_entry, *cache, i);
        }
        else {
          cache->action.generic.used = 0;

          status = fl_string_dynamic_partial_rip_nulless(cache->buffer_file, cache->content_actions.array[i].array[0], &cache->action.generic);

          if (F_status_is_error(status)) {
            controller_entry_print_error(is_entry, global.main->error, cache->action, F_status_set_fine(status), "fl_string_dynamic_partial_rip_nulless", F_true, global.thread);

            continue;
          }

          global.setting->path_pid.used = 0;

          status = controller_path_canonical_relative(global.setting, cache->action.generic, &global.setting->path_pid);

          if (F_status_is_error(status)) {
            controller_entry_print_error(is_entry, global.main->error, cache->action, F_status_set_fine(status), "controller_path_canonical_relative", F_true, global.thread);

            continue;
          }
        }
      }
      else if (fl_string_dynamic_compare(controller_session_s, cache->action.name_action) == F_equal_to) {
        if (cache->content_actions.array[i].used != 1) {
          controller_entry_settings_read_print_setting_requires_exactly(global, is_entry, *cache, 1);

          continue;
        }

        if (fl_string_dynamic_partial_compare_string(controller_new_s.string, cache->buffer_file, controller_new_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          entry->session = controller_entry_session_new_e;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_same_s.string, cache->buffer_file, controller_same_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          entry->session = controller_entry_session_same_e;
        }
        else {
          controller_entry_settings_read_print_setting_unknown_action_value(global, is_entry, *cache, i);

          continue;
        }
      }
      else if (fl_string_dynamic_compare(controller_show_s, cache->action.name_action) == F_equal_to) {
        if (cache->content_actions.array[i].used != 1) {
          controller_entry_settings_read_print_setting_requires_exactly(global, is_entry, *cache, 1);

          continue;
        }

        if (fl_string_dynamic_partial_compare_string(controller_normal_s.string, cache->buffer_file, controller_normal_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          entry->show = controller_entry_show_normal_e;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_init_s.string, cache->buffer_file, controller_init_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          entry->show = controller_entry_show_init_e;
        }
        else {
          controller_entry_settings_read_print_setting_unknown_action_value(global, is_entry, *cache, i);

          continue;
        }
      }
      else {
        if (global.main->warning.verbosity == f_console_verbosity_debug_e) {
          controller_entry_settings_read_print_setting_unknown_action(global, is_entry, *cache);
        }

        continue;
      }
    } // for

    return status;
  }
#endif // _di_controller_entry_settings_read_

#ifndef _di_controller_entry_settings_read_map_
  f_status_t controller_entry_settings_read_map(const f_string_static_t buffer, const f_string_ranges_t ranges, f_string_maps_t *setting_maps) {

    f_status_t status = f_string_maps_increase(controller_common_allocation_small_d, setting_maps);
    if (F_status_is_error(status)) return status;

    setting_maps->array[setting_maps->used].name.used = 0;
    setting_maps->array[setting_maps->used].value.used = 0;

    status = f_string_dynamic_partial_append_nulless(buffer, ranges.array[0], &setting_maps->array[setting_maps->used].name);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamic_partial_append_nulless(buffer, ranges.array[1], &setting_maps->array[setting_maps->used].value);
    if (F_status_is_error(status)) return status;

    ++setting_maps->used;
  }
#endif // _di_controller_entry_settings_read_map_

#ifdef __cplusplus
} // extern "C"
#endif
