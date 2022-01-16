#include "../controller/controller.h"
#include "../common/private-common.h"
#include "../controller/private-controller.h"
#include "../controller/private-controller_print.h"
#include "../lock/private-lock.h"
#include "../lock/private-lock_print.h"
#include "../process/private-process.h"
#include "../rule/private-rule.h"
#include "../rule/private-rule_print.h"
#include "../thread/private-thread.h"
#include "../thread/private-thread_process.h"
#include "../thread/private-thread_signal.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_rule_action_method_name_
  f_string_static_t controller_rule_action_method_name(const uint8_t type) {

    f_string_static_t buffer = f_string_static_t_initialize;

    switch (type) {
      case controller_rule_action_method_extended_e:
        buffer.string = controller_rule_action_method_string_extended_s;
        buffer.used = controller_rule_action_method_string_extended_s_length;
        break;

      case controller_rule_action_method_extended_list_e:
        buffer.string = controller_rule_action_method_string_extended_list_s;
        buffer.used = controller_rule_action_method_string_extended_list_s_length;
        break;
    }

    buffer.size = buffer.used;

    return buffer;
  }
#endif // _di_controller_rule_action_method_name_

#ifndef _di_controller_rule_find_
  f_status_t controller_rule_find(const f_string_static_t alias, const controller_rules_t rules, f_array_length_t *at) {

    if (!alias.used) return F_none;
    if (!rules.used) return F_false;

    for (f_array_length_t i = 0; i < rules.used; ++i) {

      if (fl_string_dynamic_compare(alias, rules.array[i].alias) == F_equal_to) {
        if (at) *at = i;

        return F_true;
      }
    } // for

    return F_false;
  }
#endif // _di_controller_rule_find_

#ifndef _di_controller_rule_parameters_read_
  f_status_t controller_rule_parameters_read(const controller_global_t global, const f_string_static_t buffer, f_fss_object_t *object, f_fss_content_t *content, f_string_dynamics_t *parameters) {

    f_status_t status = F_none;

    parameters->used = 0;

    if (object && object->start <= object->start) {

      status = f_string_dynamics_increase(controller_common_allocation_small_d, parameters);

      if (F_status_is_error(status)) {
        controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "f_string_dynamics_increase", F_true);

        return status;
      }

      parameters->array[parameters->used].used = 0;

      status = f_string_dynamic_partial_append_nulless(buffer, *object, &parameters->array[0]);

      if (F_status_is_error(status)) {
        controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true);

        return status;
      }

      status = f_string_dynamic_terminate_after(&parameters->array[0]);

      if (F_status_is_error(status)) {
        controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);

        return status;
      }

      ++parameters->used;
    }

    if (content && content->used) {

      for (f_array_length_t i = 0; i < content->used; ++i) {

        if (content->array[i].start > content->array[i].start) continue;

        status = f_string_dynamics_increase(controller_common_allocation_small_d, parameters);

        if (F_status_is_error(status)) {
          controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "f_string_dynamics_increase", F_true);

          return status;
        }

        parameters->array[parameters->used].used = 0;

        status = f_string_dynamic_partial_append_nulless(buffer, content->array[i], &parameters->array[parameters->used]);

        if (F_status_is_error(status)) {
          controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true);

          return status;
        }

        status = f_string_dynamic_terminate_after(&parameters->array[parameters->used]);

        if (F_status_is_error(status)) {
          controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);

          return status;
        }

        ++parameters->used;
      } // for
    }

    return F_none;
  }
#endif // _di_controller_rule_parameters_read_

#ifndef _di_controller_rule_action_type_to_action_execute_type_
  uint8_t controller_rule_action_type_to_action_execute_type(const uint8_t type) {

    if (type == controller_rule_action_type_freeze_e) {
      return controller_rule_action_type_execute_freeze_e;
    }

    if (type == controller_rule_action_type_kill_e) {
      return controller_rule_action_type_execute_kill_e;
    }

    if (type == controller_rule_action_type_pause_e) {
      return controller_rule_action_type_execute_pause_e;
    }

    if (type == controller_rule_action_type_reload_e) {
      return controller_rule_action_type_execute_reload_e;
    }

    if (type == controller_rule_action_type_restart_e) {
      return controller_rule_action_type_execute_restart_e;
    }

    if (type == controller_rule_action_type_resume_e) {
      return controller_rule_action_type_execute_resume_e;
    }

    if (type == controller_rule_action_type_start_e) {
      return controller_rule_action_type_execute_start_e;
    }

    if (type == controller_rule_action_type_stop_e) {
      return controller_rule_action_type_execute_stop_e;
    }

    if (type == controller_rule_action_type_thaw_e) {
      return controller_rule_action_type_execute_thaw_e;
    }

    return controller_rule_action_type_execute__enum_size_e;
  }
#endif // _di_controller_rule_action_type_to_action_execute_type_

#ifndef _di_controller_rule_action_type_name_
  f_string_static_t controller_rule_action_type_name(const uint8_t type) {

    f_string_static_t buffer = f_string_static_t_initialize;

    switch (type) {
      case controller_rule_action_type_freeze_e:
        buffer.string = controller_freeze_s;
        buffer.used = controller_freeze_s_length;
        break;

      case controller_rule_action_type_group_e:
        buffer.string = controller_group_s;
        buffer.used = controller_group_s_length;
        break;

      case controller_rule_action_type_kill_e:
        buffer.string = controller_kill_s;
        buffer.used = controller_kill_s_length;
        break;

      case controller_rule_action_type_pause_e:
        buffer.string = controller_pause_s;
        buffer.used = controller_pause_s_length;
        break;

      case controller_rule_action_type_pid_file_e:
        buffer.string = controller_pid_file_s;
        buffer.used = controller_pid_file_s_length;
        break;

      case controller_rule_action_type_rerun_e:
        buffer.string = controller_rerun_s;
        buffer.used = controller_rerun_s_length;
        break;

      case controller_rule_action_type_reload_e:
        buffer.string = controller_reload_s;
        buffer.used = controller_reload_s_length;
        break;

      case controller_rule_action_type_restart_e:
        buffer.string = controller_restart_s;
        buffer.used = controller_restart_s_length;
        break;

      case controller_rule_action_type_resume_e:
        buffer.string = controller_resume_s;
        buffer.used = controller_resume_s_length;
        break;

      case controller_rule_action_type_start_e:
        buffer.string = controller_start_s;
        buffer.used = controller_start_s_length;
        break;

      case controller_rule_action_type_stop_e:
        buffer.string = controller_stop_s;
        buffer.used = controller_stop_s_length;
        break;

      case controller_rule_action_type_thaw_e:
        buffer.string = controller_thaw_s;
        buffer.used = controller_thaw_s_length;
        break;

      case controller_rule_action_type_user_e:
        buffer.string = controller_user_s;
        buffer.used = controller_user_s_length;
        break;

      case controller_rule_action_type_with_e:
        buffer.string = controller_with_s;
        buffer.used = controller_with_s_length;
        break;
    }

    buffer.size = buffer.used;

    return buffer;
  }
#endif // _di_controller_rule_action_type_name_

#ifndef _di_controller_rule_action_type_execute_name_
  f_string_static_t controller_rule_action_type_execute_name(const uint8_t type) {

    f_string_static_t buffer = f_string_static_t_initialize;

    switch (type) {
      case controller_rule_action_type_execute_freeze_e:
        buffer.string = controller_freeze_s;
        buffer.used = controller_freeze_s_length;
        break;

      case controller_rule_action_type_execute_kill_e:
        buffer.string = controller_kill_s;
        buffer.used = controller_kill_s_length;
        break;

      case controller_rule_action_type_execute_pause_e:
        buffer.string = controller_pause_s;
        buffer.used = controller_pause_s_length;
        break;

      case controller_rule_action_type_execute_reload_e:
        buffer.string = controller_reload_s;
        buffer.used = controller_reload_s_length;
        break;

      case controller_rule_action_type_execute_restart_e:
        buffer.string = controller_restart_s;
        buffer.used = controller_restart_s_length;
        break;

      case controller_rule_action_type_execute_resume_e:
        buffer.string = controller_resume_s;
        buffer.used = controller_resume_s_length;
        break;

      case controller_rule_action_type_execute_start_e:
        buffer.string = controller_start_s;
        buffer.used = controller_start_s_length;
        break;

      case controller_rule_action_type_execute_stop_e:
        buffer.string = controller_stop_s;
        buffer.used = controller_stop_s_length;
        break;

      case controller_rule_action_type_execute_thaw_e:
        buffer.string = controller_thaw_s;
        buffer.used = controller_thaw_s_length;
        break;
    }

    buffer.size = buffer.used;

    return buffer;
  }
#endif // _di_controller_rule_action_type_execute_name_

#ifndef _di_controller_rule_action_read_
  f_status_t controller_rule_action_read(const controller_global_t global, const bool is_normal, const uint8_t type, const uint8_t method, controller_cache_t * const cache, controller_rule_item_t *item, controller_rule_actions_t *actions, f_string_range_t *range) {

    f_status_t status = F_none;

    if (method == controller_rule_action_method_extended_list_e) {
      cache->comments.used = 0;
      cache->delimits.used = 0;
      cache->content_action.used = 0;
      cache->content_actions.used = 0;
      cache->object_actions.used = 0;

      if (actions->size) {
        actions->array[actions->used].parameters.used = 0;
      }

      {
        controller_state_interrupt_t custom = macro_controller_state_interrupt_t_initialize(is_normal, global.thread);
        f_state_t state = macro_f_state_t_initialize(controller_common_allocation_large_d, controller_common_allocation_small_d, 0, &controller_thread_signal_state_fss, 0, (void *) &custom, 0);

        status = fl_fss_extended_list_content_read(cache->buffer_item, state, range, &cache->content_action, &cache->delimits, &cache->comments);
      }

      if (F_status_is_error(status)) {
        controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "fl_fss_extended_list_content_read", F_true);
      }
      else if (status == F_fss_found_content) {
        status = fl_fss_apply_delimit(cache->delimits, &cache->buffer_item);

        if (F_status_is_error(status)) {
          controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "fl_fss_apply_delimit", F_true);
        }
        else {

          // "script" and "utility" types use the entire content and can be directly passed through.
          if (item->type == controller_rule_item_type_script_e || item->type == controller_rule_item_type_utility_e) {
            actions->array[actions->used].parameters.used = 0;

            status = f_string_dynamics_increase(controller_common_allocation_small_d, &actions->array[actions->used].parameters);

            if (F_status_is_error(status)) {
              controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "f_string_dynamics_increase", F_true);
            }
            else {
              actions->array[actions->used].type = type;
              actions->array[actions->used].line = cache->action.line_action;
              actions->array[actions->used].parameters.used = 0;
              actions->array[actions->used].status = F_known_not;

              status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_action.array[0], &actions->array[actions->used].parameters.array[0]);

              if (F_status_is_error(status)) {
                controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "f_string_dynamic_append_nulless", F_true);
              }

              status = f_string_dynamic_terminate_after(&actions->array[actions->used].parameters.array[0]);

              if (F_status_is_error(status)) {
                controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);
              }
              else {
                actions->array[actions->used++].parameters.used = 1;
              }
            }

            return status;
          }

          {
            controller_state_interrupt_t custom = macro_controller_state_interrupt_t_initialize(is_normal, global.thread);
            f_state_t state = macro_f_state_t_initialize(controller_common_allocation_large_d, controller_common_allocation_small_d, 0, &controller_thread_signal_state_fss, 0, (void *) &custom, 0);

            cache->delimits.used = 0;

            // the object_actions and content_actions caches are being used for the purposes of getting the parameters a given the action.
            status = fll_fss_extended_read(cache->buffer_item, state, &cache->content_action.array[0], &cache->object_actions, &cache->content_actions, 0, 0, &cache->delimits, 0);
          }

          if (F_status_is_error(status)) {
            controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "fll_fss_extended_read", F_true);
          }
          else {
            status = fl_fss_apply_delimit(cache->delimits, &cache->buffer_item);

            if (F_status_is_error(status)) {
              controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "fl_fss_apply_delimit", F_true);
            }
            else {
              f_array_length_t i = 0;
              f_array_length_t j = 0;

              for (; i < cache->object_actions.used; ++i) {
                status = controller_rule_actions_increase_by(controller_common_allocation_small_d, actions);

                if (F_status_is_error(status)) {
                  controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "controller_rule_actions_increase_by", F_true);

                  break;
                }

                status = f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &actions->array[actions->used].line);

                if (F_status_is_error(status)) {
                  controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "f_fss_count_lines", F_true);

                  break;
                }

                actions->array[actions->used].type = type;
                actions->array[actions->used].line += ++item->line;
                actions->array[actions->used].parameters.used = 0;
                actions->array[actions->used].status = F_known_not;

                status = f_string_dynamics_increase(controller_common_allocation_small_d, &actions->array[actions->used].parameters);

                if (F_status_is_error(status)) {
                  controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "f_string_dynamics_increase", F_true);

                  actions->array[actions->used].status = controller_status_simplify_error(F_status_set_fine(status));

                  break;
                }

                status = controller_rule_parameters_read(global, cache->buffer_item, &cache->object_actions.array[i], &cache->content_actions.array[i], &actions->array[actions->used].parameters);

                actions->array[actions->used++].status = controller_status_simplify_error(F_status_set_fine(status));
              } // for

              range->start = cache->content_action.array[0].start;
            }
          }
        }
      }
      else {
        status = F_data_not;
      }
    }
    else {
      cache->content_action.used = 0;
      cache->delimits.used = 0;

      {
        controller_state_interrupt_t custom = macro_controller_state_interrupt_t_initialize(is_normal, global.thread);
        f_state_t state = macro_f_state_t_initialize(controller_common_allocation_large_d, controller_common_allocation_small_d, 0, &controller_thread_signal_state_fss, 0, (void *) &custom, 0);

        status = fl_fss_extended_content_read(cache->buffer_item, state, range, &cache->content_action, 0, &cache->delimits);
      }

      if (F_status_is_error(status)) {
        controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "fll_fss_extended_content_read", F_true);
      }
      else if (status == F_fss_found_content) {
        status = fl_fss_apply_delimit(cache->delimits, &cache->buffer_item);

        if (F_status_is_error(status)) {
          controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "fl_fss_apply_delimit", F_true);
        }
        else if (type == controller_rule_action_type_pid_file_e) {
          item->pid_file.used = 0;

          status = fl_string_dynamic_rip(cache->buffer_item, cache->content_action.array[0], &item->pid_file);

          if (F_status_is_error(status)) {
            controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "fl_string_dynamic_rip", F_true);
          }
          else {
            status = f_string_dynamic_terminate_after(&item->pid_file);

            if (F_status_is_error(status)) {
              controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);
            }
          }
        }
        else if (type == controller_rule_action_type_rerun_e) {
          uint8_t type_rerun = 0;

          if (cache->content_action.used) {
            if (fl_string_dynamic_partial_compare_string(controller_freeze_s, cache->buffer_item, controller_freeze_s_length, cache->content_action.array[0]) == F_equal_to) {
              type_rerun = controller_rule_action_type_execute_freeze_e;
            }
            if (fl_string_dynamic_partial_compare_string(controller_kill_s, cache->buffer_item, controller_kill_s_length, cache->content_action.array[0]) == F_equal_to) {
              type_rerun = controller_rule_action_type_execute_kill_e;
            }
            else if (fl_string_dynamic_partial_compare_string(controller_pause_s, cache->buffer_item, controller_pause_s_length, cache->content_action.array[0]) == F_equal_to) {
              type_rerun = controller_rule_action_type_execute_pause_e;
            }
            else if (fl_string_dynamic_partial_compare_string(controller_reload_s, cache->buffer_item, controller_reload_s_length, cache->content_action.array[0]) == F_equal_to) {
              type_rerun = controller_rule_action_type_execute_reload_e;
            }
            else if (fl_string_dynamic_partial_compare_string(controller_restart_s, cache->buffer_item, controller_restart_s_length, cache->content_action.array[0]) == F_equal_to) {
              type_rerun = controller_rule_action_type_execute_restart_e;
            }
            else if (fl_string_dynamic_partial_compare_string(controller_resume_s, cache->buffer_item, controller_resume_s_length, cache->content_action.array[0]) == F_equal_to) {
              type_rerun = controller_rule_action_type_execute_resume_e;
            }
            else if (fl_string_dynamic_partial_compare_string(controller_start_s, cache->buffer_item, controller_start_s_length, cache->content_action.array[0]) == F_equal_to) {
              type_rerun = controller_rule_action_type_execute_start_e;
            }
            else if (fl_string_dynamic_partial_compare_string(controller_stop_s, cache->buffer_item, controller_stop_s_length, cache->content_action.array[0]) == F_equal_to) {
              type_rerun = controller_rule_action_type_execute_stop_e;
            }
            else if (fl_string_dynamic_partial_compare_string(controller_thaw_s, cache->buffer_item, controller_thaw_s_length, cache->content_action.array[0]) == F_equal_to) {
              type_rerun = controller_rule_action_type_execute_thaw_e;
            }
          }

          if (!type_rerun) {
            if (global.main->error.verbosity != f_console_verbosity_quiet_e) {
              controller_lock_print(global.main->error.to, global.thread);

              fl_print_format("%c%[%SRule item action '%]", global.main->error.to.stream, f_string_eol_s[0], global.main->error.context, global.main->error.prefix, global.main->error.context);
              fl_print_format("%[%s%]", global.main->error.to.stream, global.main->error.notable, controller_rerun_s, global.main->error.notable);
              fl_print_format("%[' has '%]", global.main->error.to.stream, global.main->error.context, global.main->error.context);
              fl_print_format("%[%/Q%]", global.main->error.to.stream, global.main->error.notable, cache->buffer_item, cache->content_action.array[0], global.main->error.notable);
              fl_print_format("%[' as the first value, only the following are allowed: '%]", global.main->error.to.stream, global.main->error.context, global.main->error.context);
              fl_print_format("%[%s%]%[', '%]", global.main->error.to.stream, global.main->error.notable, controller_freeze_s, global.main->error.notable, global.main->error.context, global.main->error.context);
              fl_print_format("%[%s%]%[', '%]", global.main->error.to.stream, global.main->error.notable, controller_kill_s, global.main->error.notable, global.main->error.context, global.main->error.context);
              fl_print_format("%[%s%]%[', '%]", global.main->error.to.stream, global.main->error.notable, controller_pause_s, global.main->error.notable, global.main->error.context, global.main->error.context);
              fl_print_format("%[%s%]%[', '%]", global.main->error.to.stream, global.main->error.notable, controller_reload_s, global.main->error.notable, global.main->error.context, global.main->error.context);
              fl_print_format("%[%s%]%[', '%]", global.main->error.to.stream, global.main->error.notable, controller_restart_s, global.main->error.notable, global.main->error.context, global.main->error.context);
              fl_print_format("%[%s%]%[', '%]", global.main->error.to.stream, global.main->error.notable, controller_resume_s, global.main->error.notable, global.main->error.context, global.main->error.context);
              fl_print_format("%[%s%]%[', '%]", global.main->error.to.stream, global.main->error.notable, controller_start_s, global.main->error.notable, global.main->error.context, global.main->error.context);
              fl_print_format("%[%s%]%[', or '%]", global.main->error.to.stream, global.main->error.notable, controller_stop_s, global.main->error.notable, global.main->error.context, global.main->error.context);
              fl_print_format("%[%s%]", global.main->error.to.stream, global.main->error.notable, controller_thaw_s, global.main->error.notable, global.main->error.context);
              fl_print_format("%['.%]%c", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s[0]);

              controller_rule_print_error_cache(global.main->error, cache->action, F_true);

              controller_unlock_print_flush(global.main->error.to, global.thread);
            }

            return F_status_set_error(F_valid_not);
          }

          controller_rule_rerun_item_t *rerun_item = 0;

          if (cache->content_action.used > 1) {
            if (fl_string_dynamic_partial_compare_string(controller_failure_s, cache->buffer_item, controller_failure_s_length, cache->content_action.array[1]) == F_equal_to) {
              rerun_item = &item->reruns[type_rerun].failure;
              item->reruns[type_rerun].is |= controller_rule_rerun_is_failure_d;
            }
            else if (fl_string_dynamic_partial_compare_string(controller_success_s, cache->buffer_item, controller_success_s_length, cache->content_action.array[1]) == F_equal_to) {
              rerun_item = &item->reruns[type_rerun].success;
              item->reruns[type_rerun].is |= controller_rule_rerun_is_success_d;
            }
          }
          else {
            if (global.main->error.verbosity != f_console_verbosity_quiet_e) {
              controller_lock_print(global.main->error.to, global.thread);

              fl_print_format("%c%[%SRule item action '%]", global.main->error.to.stream, f_string_eol_s[0], global.main->error.context, global.main->error.prefix, global.main->error.context);
              fl_print_format("%[%s%]", global.main->error.to.stream, global.main->error.notable, controller_rerun_s, global.main->error.notable);
              fl_print_format("%[' has '%]", global.main->error.to.stream, global.main->error.context, global.main->error.context);
              fl_print_format("%[%/Q%]", global.main->error.to.stream, global.main->error.notable, cache->buffer_item, cache->content_action.array[1], global.main->error.notable);
              fl_print_format("%[' as the second value, only the following are allowed: '%]", global.main->error.to.stream, global.main->error.context, global.main->error.context);
              fl_print_format("%[%s%]%[' or '%]", global.main->error.to.stream, global.main->error.notable, controller_stop_s, global.main->error.notable, global.main->error.context, global.main->error.context);
              fl_print_format("%[%s%]", global.main->error.to.stream, global.main->error.notable, controller_thaw_s, global.main->error.notable, global.main->error.context);
              fl_print_format("%['.%]%c", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s[0]);

              controller_rule_print_error_cache(global.main->error, cache->action, F_true);

              controller_unlock_print_flush(global.main->error.to, global.thread);
            }

            return F_status_set_error(F_valid_not);
          }

          for (f_array_length_t i = 2; i < cache->content_action.used; ++i) {

            if (fl_string_dynamic_partial_compare_string(controller_delay_s, cache->buffer_item, controller_delay_s_length, cache->content_action.array[i]) == F_equal_to) {
              status = controller_rule_action_read_rerun_number(global, controller_delay_s, cache, &i, &rerun_item->delay);
            }
            else if (fl_string_dynamic_partial_compare_string(controller_max_s, cache->buffer_item, controller_max_s_length, cache->content_action.array[i]) == F_equal_to) {
              status = controller_rule_action_read_rerun_number(global, controller_max_s, cache, &i, &rerun_item->max);
            }
            else if (fl_string_dynamic_partial_compare_string(controller_reset_s, cache->buffer_item, controller_reset_s_length, cache->content_action.array[i]) == F_equal_to) {
              item->reruns[type_rerun].is |= rerun_item == &item->reruns[type_rerun].failure ? controller_rule_rerun_is_failure_reset_d : controller_rule_rerun_is_success_reset_d;
            }
            else {
              if (global.main->error.verbosity != f_console_verbosity_quiet_e) {
                controller_lock_print(global.main->error.to, global.thread);

                fl_print_format("%c%[%SRule item action '%]", global.main->error.to.stream, f_string_eol_s[0], global.main->error.context, global.main->error.prefix, global.main->error.context);
                fl_print_format("%[%s%]", global.main->error.to.stream, global.main->error.notable, controller_rerun_s, global.main->error.notable);
                fl_print_format("%[' has an unknown value '%]", global.main->error.to.stream, global.main->error.context, global.main->error.context);
                fl_print_format("%[%/Q%]", global.main->error.to.stream, global.main->error.notable, cache->buffer_item, cache->content_action.array[i], global.main->error.notable);
                fl_print_format("%['.%]%c", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s[0]);

                controller_rule_print_error_cache(global.main->error, cache->action, F_true);

                controller_unlock_print_flush(global.main->error.to, global.thread);
              }

              return F_status_set_error(F_valid_not);
            }
          } // for
        }
        else if (type == controller_rule_action_type_with_e) {

          for (f_array_length_t i = 0; i < cache->content_action.used; ++i) {

            if (fl_string_dynamic_partial_compare_string(controller_full_path_s, cache->buffer_item, controller_full_path_s_length, cache->content_action.array[i]) == F_equal_to) {
              item->with |= controller_with_full_path_d;
            }
            else if (fl_string_dynamic_partial_compare_string(controller_session_new_s, cache->buffer_item, controller_session_new_s_length, cache->content_action.array[i]) == F_equal_to) {
              item->with |= controller_with_session_new_d;

              // "session_new" and "session_same" are mutually exclusive.
              if (item->with & controller_with_session_same_d) {
                item->with -= controller_with_session_same_d;
              }
            }
            else if (fl_string_dynamic_partial_compare_string(controller_session_same_s, cache->buffer_item, controller_session_same_s_length, cache->content_action.array[i]) == F_equal_to) {
              item->with |= controller_with_session_same_d;

              // "session_new" and "session_same" are mutually exclusive.
              if (item->with & controller_with_session_new_d) {
                item->with -= controller_with_session_new_d;
              }
            }
            else {
              if (global.main->error.verbosity != f_console_verbosity_quiet_e) {
                controller_lock_print(global.main->error.to, global.thread);

                fl_print_format("%c%[%SUnknown value '%]", global.main->error.to.stream, f_string_eol_s[0], global.main->error.context, global.main->error.prefix, global.main->error.context);
                fl_print_format("%[%/Q%]", global.main->error.to.stream, global.main->error.notable, cache->buffer_item, cache->content_action.array[i], global.main->error.notable);
                fl_print_format("%[' for rule item action '%]%[%s%]", global.main->error.to.stream, global.main->error.context, global.main->error.context, global.main->error.notable, controller_with_s, global.main->error.notable);
                fl_print_format("%['.%]%c", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s[0]);

                controller_rule_print_error_cache(global.main->error, cache->action, F_true);

                controller_unlock_print_flush(global.main->error.to, global.thread);
              }

              status = F_status_set_error(F_valid_not);
              break;
            }
          } // for
        }
        else if (item->type == controller_rule_item_type_script_e || item->type == controller_rule_item_type_utility_e) {
          status = f_string_dynamics_increase(controller_common_allocation_small_d, &actions->array[actions->used].parameters);

          if (F_status_is_error(status)) {
            controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "f_string_dynamics_increase", F_true);
          }
          else {

            // "script" types use the entire content as a single string piped to the script, so merge all arguments together.
            actions->array[actions->used].type = type;
            actions->array[actions->used].line = cache->action.line_action;
            actions->array[actions->used].parameters.used = 0;
            actions->array[actions->used].status = F_known_not;

            for (f_array_length_t i = 0; i < cache->content_action.used; ++i) {

              status = f_string_dynamic_partial_mash_nulless(f_string_space_s, F_string_space_s_length, cache->buffer_item, cache->content_action.array[i], &actions->array[actions->used].parameters.array[0]);
              if (F_status_is_error(status)) break;
            } // for

            if (F_status_is_error(status)) {
              controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "f_string_dynamic_partial_mash_nulless", F_true);
            }
            else {
              status = f_string_dynamic_terminate_after(&actions->array[actions->used].parameters.array[0]);

              if (F_status_is_error(status)) {
                controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);
              }
              else {
                actions->array[actions->used++].parameters.used = 1;
              }
            }
          }
        }
        else {
          status = f_fss_count_lines(cache->buffer_item, range->start, &actions->array[actions->used].line);

          if (F_status_is_error(status)) {
            controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "f_fss_count_lines", F_true);
          }
          else {
            actions->array[actions->used].type = type;
            actions->array[actions->used].line += ++item->line;
            actions->array[actions->used].parameters.used = 0;
            actions->array[actions->used].status = F_known_not;

            status = controller_rule_parameters_read(global, cache->buffer_item, 0, &cache->content_action, &actions->array[actions->used].parameters);

            if (F_status_is_error(status)) {
              controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "controller_rule_parameters_read", F_true);

              actions->array[actions->used++].status = controller_status_simplify_error(F_status_set_fine(status));
            }
            else {
              actions->array[actions->used++].status = status;
            }
          }
        }
      }
      else {
        status = F_data_not;
      }
    }

    if (F_status_is_error_not(status) && status == F_data_not) {
      if (global.main->warning.verbosity == f_console_verbosity_debug_e) {
        controller_lock_print(global.main->warning.to, global.thread);

        fl_print_format("%c%[%SAction is empty, nothing to do.%]%c", global.main->warning.to.stream, f_string_eol_s[0], global.main->warning.context, global.main->warning.prefix, global.main->warning.context, f_string_eol_s[0]);

        controller_rule_print_error_cache(global.main->warning, cache->action, F_true);

        controller_unlock_print_flush(global.main->warning.to, global.thread);
      }
    }

    return status;
  }
#endif // _di_controller_rule_action_read_

#ifndef _di_controller_rule_action_read_rerun_number_
  f_status_t controller_rule_action_read_rerun_number(const controller_global_t global, const f_string_t name, controller_cache_t * const cache, f_array_length_t * const index, f_number_unsigned_t * const number) {

    f_status_t status = F_none;
    f_number_unsigned_t parsed = 0;

    if (*index + 1 == cache->content_action.used) {
      status = F_status_set_error(F_valid_not);
    }
    else {
      status = fl_conversion_string_to_number_signed(cache->buffer_item.string, cache->content_action.array[++(*index)], &parsed);

      if (F_status_set_fine(status) == F_number_positive) {
        status = fl_conversion_string_to_number_signed(cache->buffer_item.string, controller_range_after_number_sign(cache->buffer_item, cache->content_action.array[*index]), &parsed);
      }

      if (status == F_data_not) {
        status = F_status_set_error(F_valid_not);
      }
    }

    if (F_status_is_error(status)) {
      if (global.main->error.verbosity != f_console_verbosity_quiet_e) {
        status = F_status_set_fine(status);

        if (status != F_valid_not && status != F_number && status != F_number_decimal && status != F_number_overflow && status != F_number_underflow && status != F_number_negative) {
          controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "f_string_dynamics_increase", F_true);
        }
        else {
          controller_lock_print(global.main->error.to, global.thread);

          fl_print_format("%c%[%SRule item action '%]", global.main->error.to.stream, f_string_eol_s[0], global.main->error.context, global.main->error.prefix, global.main->error.context);
          fl_print_format("%[%s%]", global.main->error.to.stream, global.main->error.notable, controller_rerun_s, global.main->error.notable);
          fl_print_format("%[' requires a positive whole number or 0 for the '%]", global.main->error.to.stream, global.main->error.context, global.main->error.context);
          fl_print_format("%[%S%]", global.main->error.to.stream, global.main->error.notable, name, global.main->error.notable);
          fl_print_format("%[' value", global.main->error.to.stream, global.main->error.context, global.main->error.context);

          if (*index + 1 == cache->content_action.used) {
            fl_print_format(", but none were given.%]%c", global.main->error.to.stream, global.main->error.context, f_string_eol_s[0]);
          }
          else {
            fl_print_format(", but '%]%[%/Q%]", global.main->error.to.stream, global.main->error.context, global.main->error.notable, cache->buffer_item, cache->content_action.array[*index], global.main->error.notable);

            if (status == F_number || status == F_number_decimal) {
              fl_print_format("%[' was given.%]%c", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s[0]);
            }
            else if (status == F_number_overflow) {
              fl_print_format("%[' is too large.%]%c", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s[0]);
            }
            else {
              fl_print_format("%[' is negative.%]%c", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s[0]);
            }
          }

          controller_rule_print_error_cache(global.main->error, cache->action, F_true);

          controller_unlock_print_flush(global.main->error.to, global.thread);
        }
      }

      return status;
    }

    *number = parsed;

    return F_none;
  }
#endif // _di_controller_rule_action_read_rerun_number_

#ifndef _di_controller_rule_copy_
  f_status_t controller_rule_copy(const controller_rule_t source, controller_rule_t *destination) {

    f_status_t status = F_none;

    // Delete the third party structures.
    macro_f_control_group_t_delete_simple(destination->cgroup)
    f_capability_delete(&destination->capability);

    for (f_array_length_t i = 0; i < controller_rule_action_type__enum_size_e; ++i) {
      destination->status[i] = source.status[i];
    } // for

    destination->timeout_kill = source.timeout_kill;
    destination->timeout_start = source.timeout_start;
    destination->timeout_stop = source.timeout_stop;

    destination->has = source.has;
    destination->nice = source.nice;
    destination->user = source.user;
    destination->group = source.group;

    destination->timestamp.seconds = source.timestamp.seconds;
    destination->timestamp.nanoseconds = source.timestamp.nanoseconds;

    destination->alias.used = 0;
    destination->name.used = 0;
    destination->path.used = 0;
    destination->script.used = 0;

    destination->define.used = 0;
    destination->parameter.used = 0;
    destination->environment.used = 0;

    destination->affinity.used = 0;
    destination->groups.used = 0;
    destination->limits.used = 0;
    destination->scheduler.policy = source.scheduler.policy;
    destination->scheduler.priority = source.scheduler.priority;

    for (f_array_length_t i = 0; i < destination->ons.size; ++i) {

      destination->ons.array[i].action = 0;
      destination->ons.array[i].need.used = 0;
      destination->ons.array[i].want.used = 0;
      destination->ons.array[i].wish.used = 0;
    } // for

    destination->ons.used = 0;
    destination->items.used = 0;

    if (source.alias.used) {
      status = f_string_dynamic_append(source.alias, &destination->alias);
      if (F_status_is_error(status)) return status;
    }

    if (source.name.used) {
      status = f_string_dynamic_append(source.name, &destination->name);
      if (F_status_is_error(status)) return status;
    }

    if (source.path.used) {
      status = f_string_dynamic_append(source.path, &destination->path);
      if (F_status_is_error(status)) return status;
    }

    if (source.script.used) {
      status = f_string_dynamic_append(source.script, &destination->script);
      if (F_status_is_error(status)) return status;
    }

    if (source.define.used) {
      status = f_string_maps_append(source.define, &destination->define);
      if (F_status_is_error(status)) return status;
    }

    if (source.parameter.used) {
      status = f_string_maps_append(source.parameter, &destination->parameter);
      if (F_status_is_error(status)) return status;
    }

    if (source.environment.used) {
      status = f_string_dynamics_append(source.environment, &destination->environment);
      if (F_status_is_error(status)) return status;
    }

    if (source.ons.used) {
      if (destination->ons.used < source.ons.used) {
        status = controller_rule_ons_resize(source.ons.used, &destination->ons);
        if (F_status_is_error(status)) return status;
      }

      for (f_array_length_t i = 0; i < source.ons.used; ++i) {

        destination->ons.array[i].action = source.ons.array[i].action;

        if (source.ons.array[i].need.used) {
          destination->ons.array[i].need.used = 0;

          status = f_string_dynamics_append(source.ons.array[i].need, &destination->ons.array[i].need);
          if (F_status_is_error(status)) return status;
        }

        if (source.ons.array[i].want.used) {
          destination->ons.array[i].want.used = 0;

          status = f_string_dynamics_append(source.ons.array[i].want, &destination->ons.array[i].want);
          if (F_status_is_error(status)) return status;
        }

        if (source.ons.array[i].wish.used) {
          destination->ons.array[i].wish.used = 0;

          status = f_string_dynamics_append(source.ons.array[i].wish, &destination->ons.array[i].wish);
          if (F_status_is_error(status)) return status;
        }
      } // for

      destination->ons.used = source.ons.used;
    }

    if (source.affinity.used) {
      status = f_type_int32s_append(source.affinity, &destination->affinity);
      if (F_status_is_error(status)) return status;
    }

    if (source.capability) {
      status = f_capability_copy(source.capability, &destination->capability);
      if (F_status_is_error(status)) return status;
    }

    status = f_control_group_copy(source.cgroup, &destination->cgroup);
    if (F_status_is_error(status)) return status;

    if (source.groups.used) {
      status = f_type_int32s_append(source.groups, &destination->groups);
      if (F_status_is_error(status)) return status;
    }

    if (source.limits.used) {
      status = f_limit_sets_copy(source.limits, &destination->limits);
      if (F_status_is_error(status)) return status;
    }

    if (source.items.used) {
      controller_rule_item_t *item_source = 0;
      controller_rule_item_t *item_destination = 0;

      controller_rule_action_t *action_source = 0;
      controller_rule_action_t *action_destination = 0;

      if (source.items.used > destination->items.size) {
        status = controller_rule_items_increase_by(source.items.used - destination->items.size, &destination->items);
        if (F_status_is_error(status)) return status;
      }

      f_array_length_t i = 0;
      f_array_length_t j = 0;

      for (; i < source.items.used; ++i) {

        item_source = &source.items.array[i];
        item_destination = &destination->items.array[i];

        if (item_source->actions.used > item_destination->actions.size) {
          status = controller_rule_actions_increase_by(item_source->actions.used - item_destination->actions.size, &item_destination->actions);
          if (F_status_is_error(status)) return status;
        }

        item_destination->type = item_source->type;
        item_destination->with = item_source->with;
        item_destination->line = item_source->line;
        item_destination->pid_file.used = 0;

        status = f_string_dynamic_append(item_source->pid_file, &item_destination->pid_file);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamic_terminate_after(&item_destination->pid_file);
        if (F_status_is_error(status)) return status;

        for (j = 0; j < controller_rule_action_type_execute__enum_size_e; ++j) {
          item_destination->reruns[j].is = item_source->reruns[j].is;
          item_destination->reruns[j].failure.count = item_source->reruns[j].failure.count;
          item_destination->reruns[j].failure.delay = item_source->reruns[j].failure.delay;
          item_destination->reruns[j].failure.max = item_source->reruns[j].failure.max;
          item_destination->reruns[j].success.count = item_source->reruns[j].success.count;
          item_destination->reruns[j].success.delay = item_source->reruns[j].success.delay;
          item_destination->reruns[j].success.max = item_source->reruns[j].success.max;
        } // for

        for (j = 0; j < item_source->actions.used; ++j) {

          action_source = &item_source->actions.array[j];
          action_destination = &item_destination->actions.array[j];

          action_destination->type = action_source->type;
          action_destination->line = action_source->line;
          action_destination->status = action_source->status;

          action_destination->parameters.used = 0;

          status = f_string_dynamics_append(action_source->parameters, &action_destination->parameters);
          if (F_status_is_error(status)) return status;
        } // for

        item_destination->actions.used = item_source->actions.used;
      } // for

      destination->items.used = source.items.used;
    }

    return status;
  }
#endif // _di_controller_rule_copy_

#ifndef _di_controller_rule_execute_
  f_status_t controller_rule_execute(const controller_global_t global, const uint8_t action, const uint8_t options, controller_process_t * const process) {

    f_status_t status = F_none;
    f_status_t success = F_false;

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t k = 0;

    // Child processes should receive all signals and handle the signals as they see fit.
    f_signal_how_t signals = f_signal_how_t_initialize;
    f_signal_set_empty(&signals.block);
    f_signal_set_fill(&signals.block_not);

    f_string_maps_t environment = f_string_maps_t_initialize;

    const f_string_dynamics_t arguments_none = f_string_dynamics_t_initialize;

    controller_execute_set_t execute_set = macro_controller_execute_set_t_initialize(0, 0, process->rule.has & controller_rule_has_environment_d ? &environment : 0, &signals, 0, fl_execute_as_t_initialize);

    if (process->rule.affinity.used) {
      execute_set.as.affinity = &process->rule.affinity;
    }

    if (process->rule.capability) {
      execute_set.as.capability = process->rule.capability;
    }

    if (process->rule.has & controller_rule_has_cgroup_d) {
      execute_set.as.control_group = &process->rule.cgroup;

      // Make sure all required cgroup directories exist.
      if (controller_rule_status_is_available(action, process->rule)) {
        status = fll_control_group_prepare(process->rule.cgroup);

        if (F_status_is_error(status)) {
          controller_print_error_file(global.thread, global.main->error, F_status_set_fine(status), "fll_control_group_prepare", F_true, process->rule.cgroup.path.string, "prepare control groups for", fll_error_file_type_directory_e);

          return status;
        }
      }
    }

    if (process->rule.has & controller_rule_has_group_d) {
      execute_set.as.id_group = &process->rule.group;

      if (process->rule.groups.used) {
        execute_set.as.id_groups = &process->rule.groups;
      }
    }

    if (process->rule.limits.used) {
      execute_set.as.limits = &process->rule.limits;
    }

    if (process->rule.has & controller_rule_has_scheduler_d) {
      execute_set.as.scheduler = &process->rule.scheduler;
    }

    if (process->rule.has & controller_rule_has_nice_d) {
      execute_set.as.nice = &process->rule.nice;
    }

    if (process->rule.has & controller_rule_has_user_d) {
      execute_set.as.id_user = &process->rule.user;
    }

    status = fl_environment_load_names(process->rule.environment, &environment);

    if (F_status_is_error(status)) {
      controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "fl_environment_load_names", F_true);

      return status;
    }

    for (i = 0; i < process->rule.items.used && controller_thread_is_enabled_process(process, global.thread); ++i) {

      if (process->rule.items.array[i].type == controller_rule_item_type_setting_e) continue;

      for (j = 0; j < process->rule.items.array[i].actions.used; ++j) {

        if (!controller_thread_is_enabled_process(process, global.thread)) {
          status = F_status_set_error(F_interrupt);

          break;
        }

        if (process->rule.items.array[i].actions.array[j].type != action) continue;

        execute_set.parameter.data = 0;
        execute_set.parameter.option = FL_execute_parameter_option_threadsafe_d | FL_execute_parameter_option_return_d;

        if (process->rule.items.array[i].with & controller_with_full_path_d) {
          execute_set.parameter.option |= FL_execute_parameter_option_path_d;
        }

        if (process->rule.items.array[i].with & controller_with_session_new_d) {
          execute_set.parameter.option |= FL_execute_parameter_option_session_d;
        }

        if (process->rule.items.array[i].type == controller_rule_item_type_command_e) {
          for (;;) {

            status = controller_rule_execute_foreground(process->rule.items.array[i].type, 0, process->rule.items.array[i].actions.array[j].parameters, options, &execute_set, process);

            if (status == F_child || F_status_set_fine(status) == F_interrupt || F_status_set_fine(status) == F_lock) break;
            if (F_status_is_error(status) && F_status_set_fine(status) != F_failure) break;

            if (controller_rule_execute_rerun(controller_rule_action_type_to_action_execute_type(action), process, &process->rule.items.array[i]) > 0) {
              continue;
            }

            break;
          } // for

          if (status == F_child || F_status_set_fine(status) == F_interrupt || F_status_set_fine(status) == F_lock) break;

          if (F_status_is_error(status)) {
            process->rule.items.array[i].actions.array[j].status = F_status_set_error(F_failure);

            if (!(options & controller_process_option_simulate_d)) break;

            success = F_status_set_error(F_failure);
          }
          else if (success == F_false || success == F_ignore) {
            success = F_true;
          }
        }
        else if (process->rule.items.array[i].type == controller_rule_item_type_script_e) {
          execute_set.parameter.data = &process->rule.items.array[i].actions.array[j].parameters.array[0];

          for (;;) {

            status = controller_rule_execute_foreground(process->rule.items.array[i].type, process->rule.script.used ? process->rule.script.string : controller_default_program_script_s, arguments_none, options, &execute_set, process);

            if (status == F_child || F_status_set_fine(status) == F_lock) break;
            if (F_status_is_error(status) && F_status_set_fine(status) != F_failure) break;

            if (controller_rule_execute_rerun(controller_rule_action_type_to_action_execute_type(action), process, &process->rule.items.array[i]) > 0) {
              continue;
            }

            break;
          } // for

          if (status == F_child || F_status_set_fine(status) == F_interrupt || F_status_set_fine(status) == F_lock) break;

          if (F_status_is_error(status)) {
            process->rule.items.array[i].actions.array[j].status = F_status_set_error(F_failure);

            if (!(options & controller_process_option_simulate_d)) break;

            success = F_status_set_error(F_failure);
          }
          else if (success == F_false || success == F_ignore) {
            success = F_true;
          }
        }
        else if (process->rule.items.array[i].type == controller_rule_item_type_service_e) {
          if (process->rule.items.array[i].pid_file.used) {
            for (;;) {

              status = controller_rule_execute_pid_with(process->rule.items.array[i].pid_file, process->rule.items.array[i].type, 0, process->rule.items.array[i].actions.array[j].parameters, options, process->rule.items.array[i].with, &execute_set, process);

              if (status == F_child || F_status_set_fine(status) == F_interrupt || F_status_set_fine(status) == F_lock) break;
              if (F_status_is_error(status) && F_status_set_fine(status) != F_failure) break;

              if (controller_rule_execute_rerun(controller_rule_action_type_to_action_execute_type(action), process, &process->rule.items.array[i]) > 0) {
                continue;
              }

              break;
            } // for

            if (status == F_child || F_status_set_fine(status) == F_interrupt || F_status_set_fine(status) == F_lock) break;

            if (F_status_is_error(status)) {
              process->rule.items.array[i].actions.array[j].status = F_status_set_error(F_failure);

              if (!(options & controller_process_option_simulate_d)) break;

              success = F_status_set_error(F_failure);
            }
            else if (success == F_false || success == F_ignore) {
              success = F_true;
            }
          }
          else {
            success = F_status_set_error(F_failure);

            // @todo make this more specific.
            controller_rule_action_print_error_missing_pid(global.main->error, process->rule.alias.string);
          }
        }
        else if (process->rule.items.array[i].type == controller_rule_item_type_utility_e) {
          if (process->rule.items.array[i].pid_file.used) {
            execute_set.parameter.data = &process->rule.items.array[i].actions.array[j].parameters.array[0];

            for (;;) {

              status = controller_rule_execute_pid_with(process->rule.items.array[i].pid_file, process->rule.items.array[i].type, process->rule.script.used ? process->rule.script.string : controller_default_program_script_s, arguments_none, options, process->rule.items.array[i].with, &execute_set, process);

              if (status == F_child || F_status_set_fine(status) == F_interrupt || F_status_set_fine(status) == F_lock) break;
              if (F_status_is_error(status) && F_status_set_fine(status) != F_failure) break;

              if (controller_rule_execute_rerun(controller_rule_action_type_to_action_execute_type(action), process, &process->rule.items.array[i]) > 0) {
                continue;
              }

              break;
            } // for

            if (status == F_child || F_status_set_fine(status) == F_interrupt || F_status_set_fine(status) == F_lock) break;

            if (F_status_is_error(status)) {
              process->rule.items.array[i].actions.array[j].status = F_status_set_error(F_failure);

              if (!(options & controller_process_option_simulate_d)) break;

              success = F_status_set_error(F_failure);
            }
            else if (success == F_false || success == F_ignore) {
              success = F_true;
            }
          }
          else {
            success = F_status_set_error(F_failure);

            // @todo make this more specific.
            controller_rule_action_print_error_missing_pid(global.main->error, process->rule.alias.string);
          }
        }
        else {
          if (global.main->warning.verbosity == f_console_verbosity_debug_e) {
            controller_lock_print(global.main->warning.to, global.thread);

            fl_print_format("%c%[%SAction type is unknown, ignoring.%]%c", global.main->warning.to.stream, f_string_eol_s[0], global.main->warning.context, global.main->warning.prefix, global.main->warning.context, f_string_eol_s[0]);

            controller_rule_print_error_cache(global.main->warning, process->cache.action, F_true);

            controller_unlock_print_flush(global.main->warning.to, global.thread);
          }

          if (success == F_false) {
            success = F_ignore;
          }

          continue;
        }
      } // for

      if (status == F_child || F_status_set_fine(status) == F_interrupt || F_status_is_error(status) && !(options & controller_process_option_simulate_d)) {
         break;
       }
    } // for

    macro_f_string_maps_t_delete_simple(environment);

    // Lock failed, attempt to re-establish lock before returning.
    if (F_status_set_fine(status) == F_lock) {
      status = controller_lock_read(process, global.thread, &process->lock);

      if (F_status_is_error(status)) {
        return F_status_set_error(F_lock);
      }

      success = F_false;
    }

    if (!controller_thread_is_enabled_process(process, global.thread)) {
      return F_status_set_error(F_interrupt);
    }

    if (status == F_child || F_status_is_error(status)) {
      return status;
    }

    if (success == F_false || success == F_failure) {
      return F_status_set_error(F_failure);
    }

    if (success == F_ignore) {
      return F_ignore;
    }

    return F_none;
  }
#endif // _di_controller_rule_execute_

#ifndef _di_controller_rule_execute_foreground_
  f_status_t controller_rule_execute_foreground(const uint8_t type, const f_string_t program, const f_string_statics_t arguments, const uint8_t options, controller_execute_set_t * const execute_set, controller_process_t * const process) {

    f_status_t status = F_none;
    f_status_t status_lock = F_none;

    f_string_dynamics_t arguments_none = f_string_dynamics_t_initialize;

    controller_main_t * const main = (controller_main_t *) process->main_data;
    controller_thread_t * const thread = (controller_thread_t *) process->main_thread;

    f_execute_result_t result = f_execute_result_t_initialize;

    status = controller_pids_increase(&process->childs);

    if (F_status_is_error(status)) {
      controller_print_error(thread, main->error, F_status_set_fine(status), "controller_pids_increase", F_true);

      return status;
    }

    pid_t *child = 0;
    f_string_dynamic_t *child_pid_file = 0;

    {
      f_array_length_t i = 0;

      while (i < process->childs.used && process->childs.array[i]) {
        ++i;
      } // while

      child = &process->childs.array[i];

      if (i == process->childs.used) {
        ++process->childs.used;
      }
    }

    if (options & controller_process_option_simulate_d) {
      if (main->output.verbosity != f_console_verbosity_quiet_e) {
        controller_lock_print(main->output.to, thread);

        fl_print_format("%cSimulating execution of '%[", main->output.to.stream, f_string_eol_s[0], main->context.set.title);

        if (program) {
          f_print_safely_terminated(program, main->output.to.stream);
        }
        else {
          f_print_dynamic_safely(arguments.array[0], main->output.to.stream);
        }

        fl_print_format("%]' with the arguments: '%[", main->output.to.stream, main->context.set.title, main->context.set.important);

        for (f_array_length_t i = program ? 0 : 1; i < arguments.used; ++i) {

          if (program && i || !program && i > 1) {
            f_print_terminated(f_string_space_s, main->output.to.stream);
          }

          f_print_dynamic_safely(arguments.array[i], main->output.to.stream);
        } // for

        fl_print_format("%]' from '", main->output.to.stream, main->context.set.important);
        fl_print_format("%[%Q%]'.%c", main->output.to.stream, main->context.set.notable, process->rule.name, main->context.set.notable, f_string_eol_s[0]);

        controller_unlock_print_flush(main->output.to, thread);
      }

      // Sleep for less than a second to better show simulation of synchronous vs asynchronous.
      {
        const struct timespec delay = controller_time_milliseconds(controller_thread_simulation_timeout_d);

        if (controller_time_sleep_nanoseconds(main, (controller_setting_t *) process->main_setting, delay) == -1) {
          status = F_status_set_error(F_interrupt);
        }
      }

      if (F_status_set_fine(status) != F_interrupt) {
        const f_string_static_t simulated_program = macro_f_string_static_t_initialize(f_string_empty_s, 0);
        const f_string_statics_t simulated_arguments = f_string_statics_t_initialize;
        fl_execute_parameter_t simulated_parameter = macro_fl_execute_parameter_t_initialize(execute_set->parameter.option, execute_set->parameter.wait, process->rule.has & controller_rule_has_environment_d ? execute_set->parameter.environment : 0, execute_set->parameter.signals, &simulated_program);

        status = fll_execute_program(controller_default_program_script_s, simulated_arguments, &simulated_parameter, &execute_set->as, (void *) &result);
      }
    }
    else {
      status = fll_execute_program(program, arguments, &execute_set->parameter, &execute_set->as, (void *) &result);
    }

    if (status == F_parent) {
      const pid_t id_child = result.pid;
      result.status = 0;

      f_thread_unlock(&process->lock);

      status_lock = controller_lock_write_process(process, thread, &process->lock);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(main->error, F_status_set_fine(status_lock), F_false, thread);

        if (F_status_set_fine(status_lock) != F_interrupt) {
          status = controller_lock_read_process(process, thread, &process->lock);

          if (status == F_none) {
            return status_lock;
          }
        }

        return F_status_set_error(F_lock);
      }

      // Assign the child process id to allow for the cancel process to send appropriate termination signals to the child process.
      *child = id_child;

      f_thread_unlock(&process->lock);

      status_lock = controller_lock_read_process(process, thread, &process->lock);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(main->error, F_status_set_fine(status_lock), F_true, thread);
      }

      if (F_status_set_fine(status_lock) != F_interrupt) {

        // Have the parent wait for the child process to finish.
        waitpid(id_child, &result.status, 0);
      }

      if (F_status_set_fine(status_lock) == F_interrupt || !controller_thread_is_enabled_process(process, thread)) {
        if (status_lock == F_none) {
          return F_status_set_error(F_interrupt);
        }

        return F_status_set_error(F_lock);
      }

      if (status_lock == F_none) {
        f_thread_unlock(&process->lock);
      }

      status_lock = controller_lock_write_process(process, thread, &process->lock);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(main->error, F_status_set_fine(status_lock), F_false, thread);

        if (F_status_set_fine(status_lock) != F_interrupt) {
          status = controller_lock_read_process(process, thread, &process->lock);

          if (status == F_none) {
            return status_lock;
          }
        }

        return F_status_set_error(F_lock);
      }

      process->result = result.status;

      // Remove the pid now that waidpid() has returned.
      *child = 0;

      f_thread_unlock(&process->lock);

      status_lock = controller_lock_read_process(process, thread, &process->lock);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(main->error, F_status_set_fine(status_lock), F_true, thread);

        return F_status_set_error(F_lock);
      }

      if (WIFEXITED(result.status) ? WEXITSTATUS(result.status) : 0) {
        status = F_status_set_error(F_failure);
      }
      else {
        status = F_none;
      }
    }
    else {
      main->child = result.status;

      if (!controller_thread_is_enabled_process(process, thread)) {
        return F_status_set_error(F_interrupt);
      }
    }

    if (F_status_is_error(status)) {
      status = F_status_set_fine(status);

      if (status == F_child || status == F_capability || status == F_group || status == F_nice || status == F_user) {
        status = F_child;
      }
      else {
        status = F_status_set_error(status);
      }
    }

    if (status == F_child || F_status_set_fine(status) == F_interrupt) {
      return status;
    }

    if (F_status_is_error(status)) {
      status = F_status_set_fine(status);

      if ((WIFEXITED(process->result) && WEXITSTATUS(process->result)) || status == F_control_group || status == F_failure || status == F_limit || status == F_processor || status == F_schedule) {
        controller_rule_item_print_error_execute(type == controller_rule_item_type_script_e, program ? program : arguments.used ? arguments.array[0].string : f_string_empty_s, status, process);
      }
      else {
        controller_print_error(thread, main->error, F_status_set_fine(status), "fll_execute_program", F_true);
      }

      status = F_status_set_error(status);
    }

    return status;
  }
#endif // _di_controller_rule_execute_foreground_

#ifndef _di_controller_rule_execute_pid_with_
  f_status_t controller_rule_execute_pid_with(const f_string_dynamic_t pid_file, const uint8_t type, const f_string_t program, const f_string_statics_t arguments, const uint8_t options, const uint8_t with, controller_execute_set_t * const execute_set, controller_process_t * const process) {

    f_status_t status = F_none;
    f_status_t status_lock = F_none;

    controller_main_t * const main = (controller_main_t *) process->main_data;
    controller_thread_t * const thread = (controller_thread_t *) process->main_thread;

    f_execute_result_t result = f_execute_result_t_initialize;

    status = controller_pids_increase(&process->childs);

    if (F_status_is_error(status)) {
      controller_print_error(thread, main->error, F_status_set_fine(status), "controller_pids_increase", F_true);

      return status;
    }

    status = f_string_dynamics_increase(controller_common_allocation_small_d, &process->path_pids);

    if (F_status_is_error(status)) {
      controller_print_error(thread, main->error, F_status_set_fine(status), "f_string_dynamics_increase", F_true);

      return status;
    }

    pid_t *child = 0;
    f_string_dynamic_t *child_pid_file = 0;

    {
      f_array_length_t i = 0;

      while (i < process->childs.used && process->childs.array[i]) {
        ++i;
      } // while

      child = &process->childs.array[i];

      if (i == process->childs.used) {
        ++process->childs.used;
      }

      for (i = 0; i < process->path_pids.used && process->path_pids.array[i].used; ++i) {
        // Do nothing.
      } // for

      child_pid_file = &process->path_pids.array[i];

      if (i == process->path_pids.used) {
        ++process->path_pids.used;
      }
    }

    status = f_file_exists(pid_file.string);

    if (F_status_is_error(status)) {
      controller_print_error_file(thread, main->error, F_status_set_fine(status), "f_file_exists", F_true, pid_file.string, "find", fll_error_file_type_file_e);

      return status;
    }

    if (status == F_true) {
      controller_print_error_file(thread, main->error, F_file_found, "f_file_exists", F_true, pid_file.string, "find", fll_error_file_type_file_e);

      return F_status_set_error(F_file_found);
    }

    status = controller_dynamic_append_terminated(pid_file, child_pid_file);

    if (F_status_is_error(status)) {
      controller_print_error(thread, main->error, F_status_set_fine(status), "controller_dynamic_append_terminated", F_true);

      return status;
    }

    if (options & controller_process_option_simulate_d) {
      if (main->error.verbosity != f_console_verbosity_quiet_e) {
        controller_lock_print(main->error.to, thread);

        fl_print_format("%cSimulating execution of '%[", main->error.to.stream, f_string_eol_s[0], main->context.set.title);

        if (program) {
          f_print_safely_terminated(program, main->error.to.stream);
        }
        else {
          f_print_dynamic_safely(arguments.array[0], main->error.to.stream);
        }

        fl_print_format("%]' with the arguments: '%[", main->error.to.stream, main->context.set.title, main->context.set.important);

        for (f_array_length_t i = program ? 0 : 1; i < arguments.used; ++i) {

          if (program && i || !program && i > 1) {
            f_print_terminated(f_string_space_s, main->error.to.stream);
          }

          f_print_dynamic_safely(arguments.array[i], main->error.to.stream);
        } // for

        fl_print_format("%]' from '", main->error.to.stream, main->context.set.important);
        fl_print_format("%[%Q%]'.%c", main->error.to.stream, main->context.set.notable, process->rule.name, main->context.set.notable, f_string_eol_s[0]);

        controller_unlock_print_flush(main->error.to, thread);
      }

      // Sleep for less than a second to better show simulation of synchronous vs asynchronous.
      {
        const struct timespec delay = controller_time_milliseconds(controller_thread_simulation_timeout_d);

        if (controller_time_sleep_nanoseconds(main, (controller_setting_t *) process->main_setting, delay) == -1) {
          status = F_status_set_error(F_interrupt);
        }
      }

      if (F_status_set_fine(status) != F_interrupt) {
        const f_string_static_t simulated_program = macro_f_string_static_t_initialize(f_string_empty_s, 0);
        const f_string_statics_t simulated_arguments = f_string_statics_t_initialize;
        fl_execute_parameter_t simulated_parameter = macro_fl_execute_parameter_t_initialize(execute_set->parameter.option, execute_set->parameter.wait, process->rule.has & controller_rule_has_environment_d ? execute_set->parameter.environment : 0, execute_set->parameter.signals, &simulated_program);

        status = fll_execute_program(controller_default_program_script_s, simulated_arguments, &simulated_parameter, &execute_set->as, (void *) &result);
      }
    }
    else {
      status = fll_execute_program(program, arguments, &execute_set->parameter, &execute_set->as, (void *) &result);
    }

    if (status == F_parent) {
      const pid_t id_child = result.pid;
      result.status = 0;

      f_thread_unlock(&process->lock);

      status_lock = controller_lock_write_process(process, thread, &process->lock);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(main->error, F_status_set_fine(status_lock), F_false, thread);

        if (F_status_set_fine(status_lock) != F_interrupt) {
          status = controller_lock_read_process(process, thread, &process->lock);

          if (status == F_none) {
            return status_lock;
          }
        }

        return F_status_set_error(F_lock);
      }

      // Assign the child process id to allow for the cancel process to send appropriate termination signals to the child process.
      *child = id_child;

      f_thread_unlock(&process->lock);

      status_lock = controller_lock_read_process(process, thread, &process->lock);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(main->error, F_status_set_fine(status_lock), F_true, thread);
      }

      if (F_status_set_fine(status_lock) != F_interrupt) {

        // The child process should perform the change into background, therefore it is safe to wait for the child to exit (another process is spawned).
        waitpid(id_child, &result.status, 0);
      }

      if (!controller_thread_is_enabled_process(process, thread)) {
        if (status_lock == F_none) {
          return F_status_set_error(F_interrupt);
        }

        return F_status_set_error(F_lock);
      }

      if (status_lock == F_none) {
        f_thread_unlock(&process->lock);
      }

      status_lock = controller_lock_write_process(process, thread, &process->lock);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(main->error, F_status_set_fine(status_lock), F_false, thread);

        if (F_status_set_fine(status_lock) != F_interrupt) {
          status = controller_lock_read_process(process, thread, &process->lock);

          if (status == F_none) {
            return status_lock;
          }
        }

        return F_status_set_error(F_lock);
      }

      process->result = result.status;

      // Remove the pid now that waidpid() has returned.
      *child = 0;

      f_thread_unlock(&process->lock);

      status_lock = controller_lock_read_process(process, thread, &process->lock);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(main->error, F_status_set_fine(status_lock), F_true, thread);

        return F_status_set_error(F_lock);
      }

      if (WIFEXITED(result.status) ? WEXITSTATUS(result.status) : 0) {
        status = F_status_set_error(F_failure);
      }
      else {
        status = F_none;
      }
    }
    else {
      main->child = result.status;

      if (!controller_thread_is_enabled_process(process, thread)) {
        return F_status_set_error(F_interrupt);
      }
    }

    if (F_status_is_error(status)) {
      status = F_status_set_fine(status);

      if (status == F_child || status == F_capability || status == F_group || status == F_nice || status == F_user) {
        status = F_child;
      }
      else {
        status = F_status_set_error(status);
      }
    }

    if (status == F_child || F_status_set_fine(status) == F_interrupt) {
      return status;
    }

    if (F_status_is_error(status)) {
      status = F_status_set_fine(status);

      if ((WIFEXITED(process->result) && WEXITSTATUS(process->result)) || status == F_control_group || status == F_failure || status == F_limit || status == F_processor || status == F_schedule) {
        controller_rule_item_print_error_execute(type == controller_rule_item_type_utility_e, program ? program : arguments.used ? arguments.array[0].string : f_string_empty_s, status, process);
      }
      else {
        controller_print_error(thread, main->error, F_status_set_fine(status), "fll_execute_program", F_true);
      }

      return F_status_set_error(status);
    }

    return status;
  }
#endif // _di_controller_rule_execute_pid_with_

#ifndef _di_controller_rule_execute_rerun_
  int8_t controller_rule_execute_rerun(const uint8_t action, controller_process_t * const process, controller_rule_item_t * const item) {

    const int result = WIFEXITED(process->result) ? WEXITSTATUS(process->result) : 0;

    if (item->reruns[action].is & (result ? controller_rule_rerun_is_failure_d : controller_rule_rerun_is_success_d)) {
      controller_main_t * const main = (controller_main_t *) process->main_data;
      controller_thread_t * const thread = (controller_thread_t *) process->main_thread;
      controller_rule_rerun_item_t *rerun_item = result ? &item->reruns[action].failure : &item->reruns[action].success;

      if (!controller_thread_is_enabled_process(process, thread)) return -2;

      if (!rerun_item->max || rerun_item->count < rerun_item->max) {
        if (main->error.verbosity == f_console_verbosity_debug_e) {
          controller_lock_print(main->output.to, thread);

          fl_print_format("%cRe-running '", main->output.to.stream, f_string_eol_s[0]);
          fl_print_format("%[%q%]", main->output.to.stream, main->context.set.title, process->rule.alias, main->context.set.title);
          f_print_terminated("' '", main->output.to.stream);
          fl_print_format("%[%q%]", main->output.to.stream, main->context.set.notable, controller_rule_action_type_execute_name(action), main->context.set.notable);
          f_print_terminated("' with a ", main->output.to.stream);
          fl_print_format("%[%s%]", main->output.to.stream, main->context.set.notable, controller_delay_s, main->context.set.notable);
          f_print_terminated(" of ", main->output.to.stream);
          fl_print_format("%[%ul%] MegaTime", main->output.to.stream, main->context.set.notable, rerun_item->delay, main->context.set.notable);

          if (rerun_item->max) {
            f_print_terminated(" for ", main->output.to.stream);
            fl_print_format("%[%ul%]", main->output.to.stream, main->context.set.notable, rerun_item->count, main->context.set.notable);
            f_print_terminated(" of ", main->output.to.stream);
            fl_print_format("%[%s%] ", main->output.to.stream, main->context.set.notable, controller_max_s, main->context.set.notable);
            fl_print_format("%[%ul%]", main->output.to.stream, main->context.set.notable, rerun_item->max, main->context.set.notable);
            fl_print_format(".%c", main->output.to.stream, f_string_eol_s[0]);
          }
          else {
            fl_print_format(" with no %[%s%].%c", main->output.to.stream, main->context.set.notable, controller_max_s, main->context.set.notable, f_string_eol_s[0]);
          }

          controller_unlock_print_flush(main->output.to, thread);
        }

        if (rerun_item->delay) {
          const struct timespec delay = controller_time_milliseconds(rerun_item->delay);

          if (controller_time_sleep_nanoseconds(main, (controller_setting_t *) process->main_setting, delay) == -1) {
            return -1;
          }

          if (!controller_thread_is_enabled_process(process, thread)) return -2;
        }

        if (item->reruns[action].is & (result ? controller_rule_rerun_is_failure_reset_d : controller_rule_rerun_is_success_reset_d)) {
          if (result) {
            item->reruns[action].success.count = 0;
          }
          else {
            item->reruns[action].failure.count = 0;
          }
        }

        if (rerun_item->max) {
          ++rerun_item->count;
        }

        return F_true;
      }
    }

    return F_false;
  }
#endif // _di_controller_rule_execute_rerun_

#ifndef _di_controller_rule_id_construct_
  f_status_t controller_rule_id_construct(const controller_global_t global, const f_string_static_t source, const f_string_range_t directory, const f_string_range_t basename, f_string_dynamic_t * const alias) {

    f_status_t status = F_none;

    alias->used = 0;

    status = f_string_dynamic_partial_append_nulless(source, directory, alias);

    if (F_status_is_error(status)) {
      controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true);

      return status;
    }

    status = f_string_append(f_path_separator_s, F_path_separator_s_length, alias);

    if (F_status_is_error(status)) {
      controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "f_string_append", F_true);

      return status;
    }

    status = f_string_dynamic_partial_append_nulless(source, basename, alias);

    if (F_status_is_error(status)) {
      controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true);

      return status;
    }

    status = f_string_dynamic_terminate_after(alias);

    if (F_status_is_error(status)) {
      controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);
    }

    return status;
  }
#endif // _di_controller_rule_id_construct_

#ifndef _di_controller_rule_status_is_available_
  f_status_t controller_rule_status_is_available(const uint8_t action, const controller_rule_t rule) {

    return F_status_is_error_not(rule.status[0]) && rule.status[action] == F_known_not;
  }
#endif // _di_controller_rule_status_is_available_

#ifndef _di_controller_rule_status_is_error_
  f_status_t controller_rule_status_is_error(const uint8_t action, const controller_rule_t rule) {

    return F_status_is_error(rule.status[0]) || F_status_is_error(rule.status[action]);
  }
#endif // _di_controller_rule_status_is_error_

#ifndef _di_controller_rule_item_read_
  f_status_t controller_rule_item_read(const controller_global_t global, const bool is_normal, controller_cache_t * const cache, controller_rule_item_t * const item) {

    f_status_t status = F_none;
    controller_state_interrupt_t custom = macro_controller_state_interrupt_t_initialize(is_normal, global.thread);
    f_state_t state = macro_f_state_t_initialize(controller_common_allocation_large_d, controller_common_allocation_small_d, 0, &controller_thread_signal_state_fss, 0, (void *) &custom, 0);
    f_string_range_t range = macro_f_string_range_t_initialize(cache->buffer_item.used);
    f_array_length_t last = 0;

    uint8_t type = 0;
    uint8_t method = 0;
    bool multiple = F_false;

    item->actions.used = 0;

    for (; range.start < cache->buffer_item.used && range.start <= range.stop; last = range.start, cache->delimits.used = 0, cache->comments.used = 0) {

      status = fl_fss_extended_list_object_read(cache->buffer_item, state, &range, &cache->range_action, &cache->delimits);

      if (F_status_is_error(status)) {
        controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "fl_fss_extended_list_object_read", F_true);

        break;
      }

      if (status == F_fss_found_object) {
        multiple = F_true;
      }
      else {
        range.start = last;
        multiple = F_false;
        cache->delimits.used = 0;

        // The current line is not an Extended List object, so the next possibility is a Basic List (and Extended List, both use the same Object structure).
        status = fl_fss_extended_object_read(cache->buffer_item, state, &range, &cache->range_action, 0, &cache->delimits);

        if (F_status_is_error(status)) {
          controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "fl_fss_extended_object_read", F_true);

          break;
        }

        // Nothing of importance here, so continue onto the next line.
        // @todo present an error if this line is anything but whitespace.
        if (status != F_fss_found_object) continue;
      }

      status = fl_fss_apply_delimit(cache->delimits, &cache->buffer_item);

      if (F_status_is_error(status)) {
        controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "fl_fss_apply_delimit", F_true);

        break;
      }

      status = f_fss_count_lines(cache->buffer_item, cache->range_action.start, &cache->action.line_action);

      if (F_status_is_error(status)) {
        controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "f_fss_count_lines", F_true);

        break;
      }

      cache->action.line_action += ++item->line;
      cache->action.name_action.used = 0;

      status = controller_dynamic_rip_nulless_terminated(cache->buffer_item, cache->range_action, &cache->action.name_action);

      if (F_status_is_error(status)) {
        controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "controller_dynamic_rip_nulless_terminated", F_true);

        break;
      }

      if (fl_string_dynamic_compare_string(controller_freeze_s, cache->action.name_action, controller_freeze_s_length) == F_equal_to) {
        type = controller_rule_action_type_freeze_e;
      }
      else if (fl_string_dynamic_compare_string(controller_group_s, cache->action.name_action, controller_group_s_length) == F_equal_to) {
        type = controller_rule_action_type_group_e;
      }
      else if (fl_string_dynamic_compare_string(controller_kill_s, cache->action.name_action, controller_kill_s_length) == F_equal_to) {
        type = controller_rule_action_type_kill_e;
      }
      else if (fl_string_dynamic_compare_string(controller_pause_s, cache->action.name_action, controller_pause_s_length) == F_equal_to) {
        type = controller_rule_action_type_pause_e;
      }
      else if (fl_string_dynamic_compare_string(controller_pid_file_s, cache->action.name_action, controller_pid_file_s_length) == F_equal_to) {
        type = controller_rule_action_type_pid_file_e;
      }
      else if (fl_string_dynamic_compare_string(controller_reload_s, cache->action.name_action, controller_reload_s_length) == F_equal_to) {
        type = controller_rule_action_type_reload_e;
      }
      else if (fl_string_dynamic_compare_string(controller_rerun_s, cache->action.name_action, controller_rerun_s_length) == F_equal_to) {
        type = controller_rule_action_type_rerun_e;
      }
      else if (fl_string_dynamic_compare_string(controller_restart_s, cache->action.name_action, controller_restart_s_length) == F_equal_to) {
        type = controller_rule_action_type_restart_e;
      }
      else if (fl_string_dynamic_compare_string(controller_resume_s, cache->action.name_action, controller_resume_s_length) == F_equal_to) {
        type = controller_rule_action_type_resume_e;
      }
      else if (fl_string_dynamic_compare_string(controller_start_s, cache->action.name_action, controller_start_s_length) == F_equal_to) {
        type = controller_rule_action_type_start_e;
      }
      else if (fl_string_dynamic_compare_string(controller_stop_s, cache->action.name_action, controller_stop_s_length) == F_equal_to) {
        type = controller_rule_action_type_stop_e;
      }
      else if (fl_string_dynamic_compare_string(controller_thaw_s, cache->action.name_action, controller_thaw_s_length) == F_equal_to) {
        type = controller_rule_action_type_thaw_e;
      }
      else if (fl_string_dynamic_compare_string(controller_user_s, cache->action.name_action, controller_user_s_length) == F_equal_to) {
        type = controller_rule_action_type_user_e;
      }
      else if (fl_string_dynamic_compare_string(controller_with_s, cache->action.name_action, controller_with_s_length) == F_equal_to) {
        type = controller_rule_action_type_with_e;
      }
      else {
        if (global.main->warning.verbosity == f_console_verbosity_debug_e) {
          controller_lock_print(global.main->warning.to, global.thread);

          fl_print_format("%c%[%SUnknown rule item action '%]", global.main->warning.to.stream, f_string_eol_s[0], global.main->warning.context, global.main->warning.prefix, global.main->warning.context);
          fl_print_format("%[%Q%]", global.main->warning.to.stream, global.main->warning.notable, cache->action.name_action, global.main->warning.notable);
          fl_print_format("%['.%]%c", global.main->warning.to.stream, global.main->warning.context, global.main->warning.context, f_string_eol_s[0]);

          controller_rule_print_error_cache(global.main->warning, cache->action, F_true);

          controller_unlock_print_flush(global.main->warning.to, global.thread);
        }

        continue;
      }

      if (multiple) {
        if (type == controller_rule_action_type_group_e || type == controller_rule_action_type_pid_file_e || type == controller_rule_action_type_user_e) {

          if (global.main->error.verbosity != f_console_verbosity_quiet_e) {
            controller_lock_print(global.main->error.to, global.thread);

            fl_print_format("%c%[%SFSS Extended List is not allowed for the rule item action '%]", global.main->error.to.stream, f_string_eol_s[0], global.main->error.context, global.main->error.prefix, global.main->error.context);
            fl_print_format("%[%Q%]", global.main->error.to.stream, global.main->error.notable, cache->action.name_action, global.main->error.notable);
            fl_print_format("%['.%]%c", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s[0]);

            controller_unlock_print_flush(global.main->error.to, global.thread);
          }

          status = F_status_set_error(F_supported_not);
          break;
        }

        method = controller_rule_action_method_extended_list_e;
      }
      else {
        method = controller_rule_action_method_extended_e;
      }

      status = controller_rule_actions_increase_by(controller_common_allocation_small_d, &item->actions);

      if (F_status_is_error(status)) {
        controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "controller_rule_actions_increase_by", F_true);

        break;
      }

      status = controller_rule_action_read(global, is_normal, type, method, cache, item, &item->actions, &range);
      if (F_status_is_error(status)) break;
    } // for

    return status;
  }
#endif // _di_controller_rule_item_read_

#ifndef _di_controller_rule_item_type_name_
  f_string_static_t controller_rule_item_type_name(const uint8_t type) {

    f_string_static_t buffer = f_string_static_t_initialize;

    switch (type) {
      case controller_rule_item_type_command_e:
        buffer.string = controller_command_s;
        buffer.used = controller_command_s_length;
        break;

      case controller_rule_item_type_script_e:
        buffer.string = controller_script_s;
        buffer.used = controller_script_s_length;
        break;

      case controller_rule_item_type_service_e:
        buffer.string = controller_service_s;
        buffer.used = controller_service_s_length;
        break;

      case controller_rule_item_type_setting_e:
        buffer.string = controller_setting_s;
        buffer.used = controller_setting_s_length;
        break;

      case controller_rule_item_type_utility_e:
        buffer.string = controller_utility_s;
        buffer.used = controller_utility_s_length;
        break;
    }

    buffer.size = buffer.used;

    return buffer;
  }
#endif // _di_controller_rule_item_type_name_

#ifndef _di_controller_rule_items_increase_by_
  f_status_t controller_rule_items_increase_by(const f_array_length_t amount, controller_rule_items_t * const items) {

    if (items->used + amount > items->size) {
      if (items->used + amount > F_array_length_t_size_d) {
        return F_status_set_error(F_array_too_large);
      }

      const f_status_t status = f_memory_resize(items->size, items->used + amount, sizeof(controller_rule_item_t), (void **) & items->array);

      if (F_status_is_error_not(status)) {
        items->size = items->used + amount;
      }

      return status;
    }

    return F_data_not;
  }
#endif // _di_controller_rule_items_increase_by_

#ifndef _di_controller_rule_setting_limit_type_name_
  f_string_static_t controller_rule_setting_limit_type_name(const uint8_t type) {

    f_string_static_t buffer = f_string_static_t_initialize;

    switch (type) {
      case controller_resource_limit_type_as_e:
        buffer.string = controller_as_s;
        buffer.used = controller_as_s_length;
        break;

      case controller_resource_limit_type_core_e:
        buffer.string = controller_core_s;
        buffer.used = controller_core_s_length;
        break;

      case controller_resource_limit_type_cpu_e:
        buffer.string = controller_cpu_s;
        buffer.used = controller_cpu_s_length;
        break;

      case controller_resource_limit_type_data_e:
        buffer.string = controller_data_s;
        buffer.used = controller_data_s_length;
        break;

      case controller_resource_limit_type_fsize_e:
        buffer.string = controller_fsize_s;
        buffer.used = controller_fsize_s_length;
        break;

      case controller_resource_limit_type_locks_e:
        buffer.string = controller_locks_s;
        buffer.used = controller_locks_s_length;
        break;

      case controller_resource_limit_type_memlock_e:
        buffer.string = controller_memlock_s;
        buffer.used = controller_memlock_s_length;
        break;

      case controller_resource_limit_type_msgqueue_e:
        buffer.string = controller_msgqueue_s;
        buffer.used = controller_msgqueue_s_length;
        break;

      case controller_resource_limit_type_nice_e:
        buffer.string = controller_nice_s;
        buffer.used = controller_nice_s_length;
        break;

      case controller_resource_limit_type_nofile_e:
        buffer.string = controller_nofile_s;
        buffer.used = controller_nofile_s_length;
        break;

      case controller_resource_limit_type_nproc_e:
        buffer.string = controller_nproc_s;
        buffer.used = controller_nproc_s_length;
        break;

      case controller_resource_limit_type_rss_e:
        buffer.string = controller_rss_s;
        buffer.used = controller_rss_s_length;
        break;

      case controller_resource_limit_type_rtprio_e:
        buffer.string = controller_rtprio_s;
        buffer.used = controller_rtprio_s_length;
        break;

      case controller_resource_limit_type_rttime_e:
        buffer.string = controller_rttime_s;
        buffer.used = controller_rttime_s_length;
        break;

      case controller_resource_limit_type_sigpending_e:
        buffer.string = controller_sigpending_s;
        buffer.used = controller_sigpending_s_length;
        break;

      case controller_resource_limit_type_stack_e:
        buffer.string = controller_stack_s;
        buffer.used = controller_stack_s_length;
        break;
    }

    buffer.size = buffer.used;

    return buffer;
  }
#endif // _di_controller_rule_setting_limit_type_name_

#ifndef _di_controller_rule_process_
  f_status_t controller_rule_process(const controller_global_t global, controller_process_t * const process) {

    switch (process->action) {
      case controller_rule_action_type_freeze_e:
      case controller_rule_action_type_kill_e:
      case controller_rule_action_type_pause_e:
      case controller_rule_action_type_reload_e:
      case controller_rule_action_type_restart_e:
      case controller_rule_action_type_resume_e:
      case controller_rule_action_type_start_e:
      case controller_rule_action_type_stop_e:
      case controller_rule_action_type_thaw_e:
        break;

      default:
        if (global.main->error.verbosity != f_console_verbosity_quiet_e) {
          controller_lock_print(global.main->error.to, global.thread);

          fl_print_format("%c%[%SUnsupported action type '%]", global.main->error.to.stream, f_string_eol_s[0], global.main->error.context, global.main->error.prefix, global.main->error.context);
          fl_print_format("%[%q%]", global.main->error.to.stream, global.main->error.notable, controller_rule_action_type_name(process->action), global.main->error.notable);
          fl_print_format("%[' while attempting to execute rule.%]%c", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s[0]);

          controller_rule_print_error_cache(global.main->error, process->cache.action, F_true);

          controller_unlock_print_flush(global.main->error.to, global.thread);
        }

        return F_status_set_error(F_parameter);
    }

    f_status_t status = F_none;
    f_status_t status_lock = F_none;

    process->cache.action.name_action.used = 0;
    process->cache.action.name_item.used = 0;
    process->cache.action.name_file.used = 0;

    status = f_string_append(controller_rules_s, controller_rules_s_length, &process->cache.action.name_file);

    if (F_status_is_error_not(status)) {
      status = f_string_append(f_path_separator_s, F_path_separator_s_length, &process->cache.action.name_file);
    }

    if (F_status_is_error(status)) {
      controller_rule_print_error(global.thread, global.main->error, process->cache.action, F_status_set_fine(status), "f_string_append", F_true, F_true);

      return status;
    }

    status = f_string_dynamic_append(process->rule.alias, &process->cache.action.name_file);

    if (F_status_is_error(status)) {
      controller_rule_print_error(global.thread, global.main->error, process->cache.action, F_status_set_fine(status), "f_string_dynamic_append", F_true, F_true);

      return status;
    }

    status = f_string_append(F_path_extension_separator_s, F_path_extension_separator_s_length, &process->cache.action.name_file);

    if (F_status_is_error_not(status)) {
      status = f_string_append(controller_rule_s, controller_rule_s_length, &process->cache.action.name_file);
    }

    if (F_status_is_error(status)) {
      controller_rule_print_error(global.thread, global.main->error, process->cache.action, F_status_set_fine(status), "f_string_append", F_true, F_true);

      return status;
    }

    status = f_string_dynamic_terminate_after(&process->cache.action.name_file);

    if (F_status_is_error(status)) {
      controller_rule_print_error(global.thread, global.main->error, process->cache.action, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true, F_true);

      return status;
    }

    if ((process->options & controller_process_option_simulate_d) && (process->options & controller_process_option_validate_d)) {
      controller_rule_validate(global, process->rule, process->action, process->options, &process->cache);
    }

    f_array_length_t i = 0;

    {
      f_array_length_t j = 0;
      f_array_length_t k = 0;
      f_array_length_t id_rule = 0;
      f_array_length_t id_dependency = 0;

      bool found = F_false;

      controller_process_t *dependency = 0;

      uint8_t options_process = 0;

      const f_string_t strings[3] = {
        "needed",
        "wanted",
        "wished for",
      };

      f_string_dynamics_t empty = f_string_dynamics_t_initialize;
      f_string_dynamics_t *dynamics[3] = { &empty, &empty, &empty };

      if (process->action) {

        for (i = 0; i < process->rule.ons.used; ++i) {

          if (process->rule.ons.array[i].action == process->action) {
            dynamics[0] = &process->rule.ons.array[i].need;
            dynamics[1] = &process->rule.ons.array[i].want;
            dynamics[2] = &process->rule.ons.array[i].wish;

            break;
          }
        } // for
      }

      // i==0 is need, i==1 is want, i==2 is wish.
      // loop through all dependencies: wait for depedency, execute dependency, fail due to missing required dependency, or skip unrequired missing dependencies.
      for (i = 0; i < 3 && controller_thread_is_enabled_process(process, global.thread); ++i) {

        for (j = 0; j < dynamics[i]->used && controller_thread_is_enabled_process(process, global.thread); ++j) {

          id_dependency = 0;
          dependency = 0;
          found = F_false;

          status_lock = controller_lock_read_process(process, global.thread, &global.thread->lock.process);

          if (F_status_is_error(status_lock)) {
            controller_lock_print_error_critical(global.main->error, F_status_set_fine(status_lock), F_true, global.thread);
          }
          else {
            status = controller_process_prepare_process_type(global, process->type, process->action, dynamics[i]->array[j], &id_dependency);

            if (F_status_is_error(status)) {
              if (F_status_set_fine(status) == F_lock) {
                if (!controller_thread_is_enabled_process_type(process->type, global.thread)) {
                  return F_status_set_error(F_interrupt);
                }
              }

              if (global.main->error.verbosity != f_console_verbosity_quiet_e) {
                controller_lock_print(global.main->error.to, global.thread);

                controller_rule_item_print_error_rule_not_loaded(global.main->error, dynamics[i]->array[j].string);
                controller_rule_print_error_cache(global.main->error, process->cache.action, F_false);

                controller_unlock_print_flush(global.main->error.to, global.thread);
              }

              return status;
            }

            status = F_true;
          }

          if (status == F_true) {
            found = F_true;

            dependency = global.thread->processs.array[id_dependency];

            status_lock = controller_lock_read_process(process, global.thread, &dependency->active);

            if (F_status_is_error(status_lock)) {
              controller_lock_print_error_critical(global.main->error, F_status_set_fine(status_lock), F_true, global.thread);

              status = F_false;
              dependency = 0;

              f_thread_unlock(&global.thread->lock.process);
            }
            else {
              f_thread_unlock(&global.thread->lock.process);

              status_lock = controller_lock_read_process(process, global.thread, &global.thread->lock.rule);

              if (F_status_is_error(status_lock)) {
                controller_lock_print_error_critical(global.main->error, F_status_set_fine(status_lock), F_true, global.thread);

                status = F_false;
              }
              else {
                status = controller_rule_find(dynamics[i]->array[j], global.setting->rules, &id_rule);

                f_thread_unlock(&global.thread->lock.rule);
              }
            }
          }
          else {
            f_thread_unlock(&global.thread->lock.process);
          }

          if (status != F_true) {
            found = F_false;
            id_rule = 0;

            if (i == 0) {
              controller_lock_print(global.main->error.to, global.thread);

              controller_rule_item_print_error_need_want_wish(global.main->error, strings[i], dynamics[i]->array[j].string, "was not found");
              controller_rule_print_error_cache(global.main->error, process->cache.action, F_true);

              controller_unlock_print_flush(global.main->error.to, global.thread);

              status = F_status_set_error(F_found_not);

              if (!(process->options & controller_process_option_simulate_d)) {
                if (dependency) {
                  f_thread_unlock(&dependency->active);
                }

                break;
              }
            }
            else {
              if (global.main->warning.verbosity == f_console_verbosity_debug_e) {
                controller_lock_print(global.main->warning.to, global.thread);

                controller_rule_item_print_error_need_want_wish(global.main->warning, strings[i], dynamics[i]->array[j].string, "was not found");

                controller_rule_print_error_cache(global.main->warning, process->cache.action, F_true);

                controller_unlock_print_flush(global.main->warning.to, global.thread);
              }
            }
          }
          else if (found) {
            status_lock = controller_lock_read_process(process, global.thread, &global.thread->lock.rule);

            if (F_status_is_error(status_lock)) {
              controller_lock_print_error_critical(global.main->error, F_status_set_fine(status_lock), F_true, global.thread);

              found = F_false;
              status = status_lock;
            }
          }

          if (found) {

            // the dependency may have write locks, which needs to be avoided, so copy the alias from the rule.
            char alias_other_buffer[global.setting->rules.array[id_rule].alias.used + 1];

            memcpy(alias_other_buffer, global.setting->rules.array[id_rule].alias.string, global.setting->rules.array[id_rule].alias.used);
            alias_other_buffer[global.setting->rules.array[id_rule].alias.used] = 0;

            const f_string_static_t alias_other = macro_f_string_static_t_initialize(alias_other_buffer, global.setting->rules.array[id_rule].alias.used);

            f_thread_unlock(&global.thread->lock.rule);

            status_lock = controller_lock_read_process(process, global.thread, &dependency->lock);

            if (F_status_is_error(status_lock)) {
              controller_lock_print_error_critical(global.main->error, F_status_set_fine(status_lock), F_true, global.thread);

              status = status_lock;
            }
            else if (dependency->state == controller_process_state_active_e || dependency->state == controller_process_state_busy_e) {
              f_thread_unlock(&dependency->lock);

              status = controller_process_wait(global, dependency);

              if (F_status_is_error(status) && !(process->options & controller_process_option_simulate_d)) break;

              status = dependency->rule.status[process->action];
            }
            else {
              status_lock = controller_lock_read_process(process, global.thread, &global.thread->lock.rule);

              if (F_status_is_error(status_lock)) {
                controller_lock_print_error_critical(global.main->error, F_status_set_fine(status_lock), F_true, global.thread);

                f_thread_unlock(&dependency->lock);

                status = status_lock;
              }
              else if (controller_rule_status_is_available(process->action, global.setting->rules.array[id_rule])) {
                f_thread_unlock(&global.thread->lock.rule);
                f_thread_unlock(&dependency->lock);

                options_process = 0;

                if (global.main->parameters[controller_parameter_simulate_e].result == f_console_result_found_e) {
                  options_process |= controller_process_option_simulate_d;
                }

                if (process->options & controller_process_option_validate_d) {
                  options_process |= controller_process_option_validate_d;
                }

                // Synchronously execute dependency.
                status = controller_rule_process_begin(global, 0, alias_other, process->action, options_process, process->type, process->stack, dependency->cache);

                if (status == F_child || F_status_set_fine(status) == F_interrupt) {
                  f_thread_unlock(&dependency->active);

                  break;
                }

                if (F_status_is_error(status)) {
                  if (i == 0 || i == 1 || F_status_set_fine(status) == F_memory_not) {
                    controller_lock_print(global.main->error.to, global.thread);

                    controller_rule_item_print_error_need_want_wish(global.main->error, strings[i], alias_other_buffer, "failed during execution");
                    controller_rule_print_error_cache(global.main->error, process->cache.action, F_true);

                    controller_unlock_print_flush(global.main->error.to, global.thread);

                    if (!(dependency->options & controller_process_option_simulate_d) || F_status_set_fine(status) == F_memory_not) {
                      f_thread_unlock(&dependency->active);

                      break;
                    }
                  }
                  else {
                    if (global.main->warning.verbosity == f_console_verbosity_debug_e) {
                      controller_lock_print(global.main->warning.to, global.thread);

                      controller_rule_item_print_error_need_want_wish(global.main->warning, strings[i], alias_other_buffer, "failed during execution");

                      controller_rule_print_error_cache(global.main->warning, process->cache.action, F_true);

                      controller_unlock_print_flush(global.main->warning.to, global.thread);
                    }
                  }
                }
              }
              else {
                status = global.setting->rules.array[id_rule].status[process->action];

                f_thread_unlock(&global.thread->lock.rule);
                f_thread_unlock(&dependency->lock);
              }
            }

            if (!controller_thread_is_enabled_process(process, global.thread)) {
              f_thread_unlock(&dependency->active);

              break;
            }

            if (F_status_is_error_not(status_lock)) {
              status_lock = controller_lock_read_process(process, global.thread, &global.thread->lock.rule);

              if (F_status_is_error(status_lock)) {
                controller_lock_print_error_critical(global.main->error, F_status_set_fine(status_lock), F_false, global.thread);
              }
            }

            if (F_status_is_error(status_lock)) {
              if (F_status_is_error(status_lock)) {
                controller_rule_item_print_error_need_want_wish(global.main->error, strings[i], alias_other_buffer, "due to lock failure");
              }

              status = status_lock;
            }
            else if (controller_rule_status_is_error(process->action, global.setting->rules.array[id_rule])) {
              f_thread_unlock(&global.thread->lock.rule);

              if (i == 0 || i == 1) {
                controller_lock_print(global.main->error.to, global.thread);

                controller_rule_item_print_error_need_want_wish(global.main->error, strings[i], alias_other_buffer, "is in a failed state");

                controller_rule_print_error_cache(global.main->error, process->cache.action, F_true);

                controller_unlock_print_flush(global.main->error.to, global.thread);

                status = F_status_set_error(F_found_not);

                if (!(dependency->options & controller_process_option_simulate_d)) {
                  f_thread_unlock(&dependency->active);

                  break;
                }
              }
              else {
                if (global.main->warning.verbosity == f_console_verbosity_debug_e) {
                  controller_lock_print(global.main->warning.to, global.thread);

                  controller_rule_item_print_error_need_want_wish(global.main->warning, strings[i], alias_other_buffer, "is in a failed state");

                  controller_rule_print_error_cache(global.main->warning, process->cache.action, F_true);

                  controller_unlock_print_flush(global.main->warning.to, global.thread);
                }
              }
            }
            else {
              f_thread_unlock(&global.thread->lock.rule);
            }
          }

          if (dependency) {
            f_thread_unlock(&dependency->active);
          }
        } // for

        if (status == F_child || F_status_set_fine(status) == F_interrupt) break;

        if (F_status_is_error(status) && !(process->options & controller_process_option_simulate_d)) break;
      } // for
    }

    if (status == F_child || F_status_set_fine(status) == F_interrupt) {
      return status;
    }

    if (!controller_thread_is_enabled_process(process, global.thread)) {
      return F_status_set_error(F_interrupt);
    }

    if ((process->options & controller_process_option_wait_d) && F_status_is_error_not(status) && (process->options & controller_process_option_validate_d)) {
      status_lock = controller_rule_wait_all_process_type(global, process->type, F_false, process);

      if (F_status_set_fine(status_lock) == F_interrupt) {
        return status_lock;
      }
    }

    if (!(process->options & controller_process_option_validate_d) && F_status_is_error_not(status)) {

      // find at least one of the requested action when the rule is required.
      if (process->options & controller_process_option_require_d) {
        bool missing = F_true;

        f_array_length_t j = 0;

        for (i = 0; i < process->rule.items.used; ++i) {

          for (j = 0; j < process->rule.items.array[i].actions.used; ++j) {

            if (process->rule.items.array[i].actions.array[j].type == process->action) {
              missing = F_false;
              break;
            }
          } // for
        } // for

        if (missing) {
          if (global.main->error.verbosity != f_console_verbosity_quiet_e) {
            controller_lock_print(global.main->error.to, global.thread);

            if (process->rule.items.used) {
              fl_print_format("%c%[%SThe rule '%]", global.main->error.to.stream, f_string_eol_s[0], global.main->error.context, global.main->error.prefix, global.main->error.context);
              fl_print_format("%[%Q%]", global.main->error.to.stream, global.main->error.notable, process->rule.name, global.main->error.notable);
              fl_print_format("%[' has no '%]", global.main->error.to.stream, global.main->error.context, global.main->error.context);
              fl_print_format("%[%q%]", global.main->error.to.stream, global.main->error.notable, controller_rule_action_type_name(process->action), global.main->error.notable);
              fl_print_format("%[' action to execute.%]%c", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s[0]);
            }
            else {
              fl_print_format("%c%[%SThe rule '%]", global.main->error.to.stream, f_string_eol_s[0], global.main->error.context, global.main->error.prefix, global.main->error.context);
              fl_print_format("%[%Q%]", global.main->error.to.stream, global.main->error.notable, process->rule.name, global.main->error.notable);
              fl_print_format("%[ has no known '%]", global.main->error.to.stream, global.main->error.context, global.main->error.context);
              fl_print_format("%[%s %s%]", global.main->error.to.stream, global.main->error.notable, controller_rule_s, controller_type_s, global.main->error.notable);
              fl_print_format("%[' (such as '%]", global.main->error.to.stream, global.main->error.context, global.main->error.context);
              fl_print_format("%[%s%]", global.main->error.to.stream, global.main->error.notable, controller_command_s, global.main->error.notable);
              fl_print_format("%[', '%]", global.main->error.to.stream, global.main->error.context, global.main->error.context);
              fl_print_format("%[%s%]", global.main->error.to.stream, global.main->error.notable, controller_service_s, global.main->error.notable);
              fl_print_format("%[', '%]", global.main->error.to.stream, global.main->error.context, global.main->error.context);
              fl_print_format("%[%s%]", global.main->error.to.stream, global.main->error.notable, controller_script_s, global.main->error.notable);
              fl_print_format("%[', or '%]", global.main->error.to.stream, global.main->error.context, global.main->error.context);
              fl_print_format("%[%s%]", global.main->error.to.stream, global.main->error.notable, controller_utility_s, global.main->error.notable);
              fl_print_format("%[') to execute.%]%c", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s[0]);
            }

            controller_rule_print_error_cache(global.main->error, process->cache.action, F_true);

            controller_unlock_print_flush(global.main->error.to, global.thread);
          }

          status = F_status_set_error(F_parameter);
        }
      }

      if (F_status_is_error_not(status)) {
        status = controller_rule_execute(global, process->action, process->options, process);

        if (status == F_child || F_status_set_fine(status) == F_interrupt || F_status_set_fine(status) == F_lock) {
          return status;
        }

        if (F_status_is_error(status)) {
          controller_rule_item_print_error(global.thread, global.main->error, process->cache.action, F_true, F_status_set_fine(status));
        }
      }
    }

    f_array_length_t id_rule = 0;

    f_thread_unlock(&process->lock);

    status_lock = controller_lock_write_process(process, global.thread, &process->lock);

    if (F_status_is_error(status_lock)) {
      controller_lock_print_error_critical(global.main->error, F_status_set_fine(status_lock), F_false, global.thread);

      if (F_status_set_fine(status) != F_interrupt) {
        status = controller_lock_read_process(process, global.thread, &process->lock);

        if (F_status_is_error_not(status)) {
          return status_lock;
        }
      }

      return F_status_set_error(F_lock);
    }

    if (F_status_is_error(status)) {
      process->rule.status[process->action] = controller_status_simplify_error(F_status_set_fine(status));
    }
    else {
      process->rule.status[process->action] = status;
    }

    status_lock = controller_lock_write_process(process, global.thread, &global.thread->lock.rule);

    if (F_status_is_error(status_lock)) {
      controller_lock_print_error_critical(global.main->error, F_status_set_fine(status_lock), F_false, global.thread);

      f_thread_unlock(&process->lock);

      status = controller_lock_read_process(process, global.thread, &process->lock);

      if (F_status_is_error_not(status)) {
        return status_lock;
      }

      return F_status_set_error(F_lock);
    }

    // Update the global rule status, which is stored separately from the rule status for this process.
    if (controller_rule_find(process->rule.alias, global.setting->rules, &id_rule) == F_true) {
      controller_rule_t *rule = &global.setting->rules.array[id_rule];

      rule->status[process->action] = process->rule.status[process->action];

      f_array_length_t j = 0;

      controller_rule_item_t *rule_item = 0;
      controller_rule_action_t *rule_action = 0;

      // @todo implement a "version" counter and detect if the rule version is different before attempting update.
      // Copy all rule item action statuses from the rule process to the rule.
      for (i = 0; i < rule->items.used; ++i) {

        rule_item = &rule->items.array[i];

        for (j = 0; j < rule_item->actions.used; ++j) {
          rule_item->actions.array[j].status = process->rule.items.array[i].actions.array[j].status;
        } // for
      } // for
    }

    f_thread_unlock(&global.thread->lock.rule);
    f_thread_unlock(&process->lock);

    status_lock = controller_lock_read_process(process, global.thread, &process->lock);

    if (F_status_is_error(status_lock)) {
      controller_lock_print_error_critical(global.main->error, F_status_set_fine(status_lock), F_true, global.thread);

      return F_status_set_error(F_lock);
    }

    return process->rule.status[process->action];
  }
#endif // _di_controller_rule_process_

#ifndef _di_controller_rule_process_begin_
  f_status_t controller_rule_process_begin(const controller_global_t global, const uint8_t options_force, const f_string_static_t alias_rule, const uint8_t action, const uint8_t options, const uint8_t type, const f_array_lengths_t stack, const controller_cache_t cache) {

    if (!controller_thread_is_enabled_process_type(type, global.thread)) {
      return F_status_set_error(F_interrupt);
    }

    f_status_t status = F_none;
    f_status_t status_lock = F_none;

    controller_process_t *process = 0;

    status = controller_lock_read_process_type(type, global.thread, &global.thread->lock.process);

    if (F_status_is_error(status)) {
      controller_lock_print_error_critical(global.main->error, F_status_set_fine(status), F_true, global.thread);

      return status;
    }

    {
      f_array_length_t at = 0;

      status = controller_process_prepare(global, type != controller_process_type_exit_e, action, alias_rule, &at);

      if (F_status_is_error(status)) {
        f_thread_unlock(&global.thread->lock.process);

        if (global.main->error.verbosity != f_console_verbosity_quiet_e) {
          controller_lock_print(global.main->error.to, global.thread);

          controller_rule_item_print_error_rule_not_loaded(global.main->error, alias_rule.string);
          controller_rule_print_error_cache(global.main->error, cache.action, F_false);

          controller_unlock_print_flush(global.main->error.to, global.thread);
        }

        return status;
      }

      process = global.thread->processs.array[at];

      status = controller_lock_read_process_type(type, global.thread, &process->active);

      if (F_status_is_error(status)) {
        controller_lock_print_error_critical(global.main->error, F_status_set_fine(status), F_true, global.thread);
        controller_rule_item_print_error(global.thread, global.main->error, cache.action, F_false, F_status_set_fine(status));

        f_thread_unlock(&global.thread->lock.process);

        return status;
      }

      status_lock = controller_lock_write_process(process, global.thread, &process->lock);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(global.main->error, F_status_set_fine(status_lock), F_false, global.thread);

        f_thread_unlock(&process->active);
        f_thread_unlock(&global.thread->lock.process);

        return status_lock;
      }

      // once a write lock on the process is achieved, it is safe to unlock the global process read lock.
      f_thread_unlock(&global.thread->lock.process);

      // if the process is already running, then there is nothing to do.
      if (process->state == controller_process_state_active_e || process->state == controller_process_state_busy_e) {
        f_thread_unlock(&process->lock);
        f_thread_unlock(&process->active);

        return F_busy;
      }

      // the thread is done, so close the thread.
      if (process->state == controller_process_state_done_e) {
        controller_thread_join(&process->id_thread);

        f_thread_mutex_lock(&process->wait_lock);
        f_thread_condition_signal_all(&process->wait);
        f_thread_mutex_unlock(&process->wait_lock);
      }

      process->id = at;
    }

    f_thread_unlock(&process->lock);

    status_lock = controller_lock_write_process(process, global.thread, &process->lock);

    if (F_status_is_error(status_lock)) {
      controller_lock_print_error_critical(global.main->error, F_status_set_fine(status_lock), F_false, global.thread);

      f_thread_unlock(&process->active);

      return status_lock;
    }

    process->state = controller_process_state_active_e;
    process->action = action;
    process->options = options;
    process->type = type;

    macro_f_time_spec_t_clear(process->cache.timestamp)
    macro_f_string_range_t_clear(process->cache.range_action)

    process->cache.ats.used = 0;
    process->cache.stack.used = 0;
    process->cache.comments.used = 0;
    process->cache.delimits.used = 0;
    process->cache.content_action.used = 0;
    process->cache.content_actions.used = 0;
    process->cache.content_items.used = 0;
    process->cache.object_actions.used = 0;
    process->cache.object_items.used = 0;
    process->cache.buffer_file.used = 0;
    process->cache.buffer_item.used = 0;
    process->cache.buffer_path.used = 0;
    process->cache.action.line_action = cache.action.line_action;
    process->cache.action.line_item = cache.action.line_item;
    process->cache.action.name_action.used = 0;
    process->cache.action.name_file.used = 0;
    process->cache.action.name_item.used = 0;
    process->cache.action.generic.used = 0;

    process->stack.used = 0;

    process->main_data = (void *) global.main;
    process->main_setting = (void *) global.setting;
    process->main_thread = (void *) global.thread;

    if (F_status_is_error_not(status) && stack.used) {
      if (process->stack.size < stack.used) {
        status = f_type_array_lengths_resize(stack.used, &process->stack);
      }

      if (F_status_is_error(status)) {
        controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "f_type_array_lengths_resize", F_true);
      }
      else {
        for (f_array_length_t i = 0; i < stack.used; ++i) {
          process->stack.array[i] = stack.array[i];
        } // for

        process->stack.used = stack.used;
      }
    }

    if (F_status_is_error_not(status)) {
      status = f_string_dynamic_append(cache.action.name_action, &process->cache.action.name_action);

      if (F_status_is_error_not(status)) {
        status = f_string_dynamic_append(cache.action.name_file, &process->cache.action.name_file);
      }

      if (F_status_is_error_not(status)) {
        status = f_string_dynamic_append(cache.action.name_item, &process->cache.action.name_item);
      }
      else {
        controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "f_string_dynamic_append", F_true);
      }
    }

    f_thread_unlock(&process->lock);

    if (F_status_is_error_not(status)) {
      if (process->action && (options_force & controller_process_option_asynchronous_d)) {
        if (process->type == controller_process_type_exit_e) {
          status = f_thread_create(0, &process->id_thread, controller_thread_process_other, (void *) process);
        }
        else {
          status = f_thread_create(0, &process->id_thread, controller_thread_process_normal, (void *) process);
        }

        if (F_status_is_error(status)) {
          controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "f_thread_create", F_true);
        }
      }
      else {
        status = controller_rule_process_do(options_force, process);

        if (status == F_child || F_status_set_fine(status) == F_interrupt) {
          f_thread_unlock(&process->active);

          return status;
        }
      }
    }

    if (!action || F_status_is_error(status) && (process->state == controller_process_state_active_e || process->state == controller_process_state_busy_e)) {
      {
        status_lock = controller_lock_write_process(process, global.thread, &process->lock);

        if (F_status_is_error(status_lock)) {
          controller_lock_print_error_critical(global.main->error, F_status_set_fine(status_lock), F_false, global.thread);

          f_thread_unlock(&process->active);

          return status_lock;
        }
      }

      if (!action || (options_force & controller_process_option_asynchronous_d)) {
        process->state = controller_process_state_done_e;
      }
      else {
        process->state = controller_process_state_idle_e;
      }

      f_thread_mutex_lock(&process->wait_lock);
      f_thread_condition_signal_all(&process->wait);
      f_thread_mutex_unlock(&process->wait_lock);

      f_thread_unlock(&process->lock);
    }

    f_thread_unlock(&process->active);

    if (F_status_is_error(status)) {
      return status;
    }

    return F_none;
  }
#endif // _di_controller_rule_process_begin_

#ifndef _di_controller_rule_process_do_
  f_status_t controller_rule_process_do(const uint8_t options_force, controller_process_t * const process) {

    f_status_t status_lock = F_none;

    controller_global_t global = macro_controller_global_t_initialize((controller_main_t *) process->main_data, (controller_setting_t *) process->main_setting, (controller_thread_t *) process->main_thread);

    // The process and active locks shall be held for the duration of this processing (aside from switching between read to/from write).
    if (options_force & controller_process_option_asynchronous_d) {
      status_lock = controller_lock_read_process(process, global.thread, &process->active);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(global.main->error, F_status_set_fine(status_lock), F_true, global.thread);

        return status_lock;
      }
    }

    status_lock = controller_lock_read_process(process, global.thread, &process->lock);

    if (F_status_is_error(status_lock)) {
      controller_lock_print_error_critical(global.main->error, F_status_set_fine(status_lock), F_true, global.thread);

      if (options_force & controller_process_option_asynchronous_d) {
        f_thread_unlock(&process->active);
      }

      return status_lock;
    }

    f_status_t status = F_none;

    f_array_length_t id_rule = 0;

    const f_array_length_t used_original_stack = process->stack.used;

    status_lock = controller_lock_read_process(process, global.thread, &global.thread->lock.rule);

    if (F_status_is_error(status_lock)) {
      controller_lock_print_error_critical(global.main->error, F_status_set_fine(status_lock), F_true, global.thread);

      f_thread_unlock(&process->lock);

      if (options_force & controller_process_option_asynchronous_d) {
        f_thread_unlock(&process->active);
      }

      return status_lock;
    }

    if (controller_rule_find(process->rule.alias, global.setting->rules, &id_rule) == F_true) {
      f_thread_unlock(&process->lock);

      status_lock = controller_lock_write_process(process, global.thread, &process->lock);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(global.main->error, F_status_set_fine(status_lock), F_false, global.thread);

        f_thread_unlock(&global.thread->lock.rule);

        if (options_force & controller_process_option_asynchronous_d) {
          f_thread_unlock(&process->active);
        }

        return status_lock;
      }

      controller_rule_delete_simple(&process->rule);

      status = controller_rule_copy(global.setting->rules.array[id_rule], &process->rule);

      f_thread_unlock(&process->lock);

      status_lock = controller_lock_read_process(process, global.thread, &process->lock);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(global.main->error, F_status_set_fine(status_lock), F_true, global.thread);

        f_thread_unlock(&global.thread->lock.rule);

        if (options_force & controller_process_option_asynchronous_d) {
          f_thread_unlock(&process->active);
        }

        return status_lock;
      }

      f_thread_unlock(&global.thread->lock.rule);

      if (F_status_is_error(status)) {
        controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "controller_rule_copy", F_true);
      }
      else if (!process->action) {

        // This is a "consider" Action, so do not actually execute the rule.
        f_thread_unlock(&process->lock);

        if (options_force & controller_process_option_asynchronous_d) {
          f_thread_unlock(&process->active);
        }

        return F_process_not;
      }
      else {
        for (f_array_length_t i = 0; i < process->stack.used && controller_thread_is_enabled_process(process, global.thread); ++i) {

          if (process->stack.array[i] == id_rule) {
            if (global.main->error.verbosity != f_console_verbosity_quiet_e) {
              controller_lock_print(global.main->error.to, global.thread);

              fl_print_format("%c%[%SThe rule '%]", global.main->error.to.stream, f_string_eol_s[0], global.main->error.context, global.main->error.prefix, global.main->error.context);
              fl_print_format("%[%Q%]", global.main->error.to.stream, global.main->error.notable, process->rule.alias, global.main->error.notable);
              fl_print_format("%[' is already on the execution dependency stack, this recursion is prohibited.%]%c", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s[0]);

              controller_rule_print_error_cache(global.main->error, process->cache.action, F_true);

              controller_unlock_print_flush(global.main->error.to, global.thread);
            }

            // Never continue on circular recursion errors even in simulate mode.
            status = F_status_set_error(F_recurse);

            break;
          }
        } // for

        if (!controller_thread_is_enabled_process(process, global.thread)) {
          f_thread_unlock(&process->lock);

          if (options_force & controller_process_option_asynchronous_d) {
            f_thread_unlock(&process->active);
          }

          return F_status_set_error(F_interrupt);
        }

        if (F_status_is_error_not(status)) {
          status = f_type_array_lengths_increase(controller_common_allocation_small_d, &process->stack);

          if (F_status_is_error(status)) {
            controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "f_type_array_lengths_increase", F_true);
          }
          else {
            f_thread_unlock(&process->lock);

            status_lock = controller_lock_write_process(process, global.thread, &process->lock);

            if (F_status_is_error(status_lock)) {
              controller_lock_print_error_critical(global.main->error, F_status_set_fine(status_lock), F_false, global.thread);

              if (options_force & controller_process_option_asynchronous_d) {
                f_thread_unlock(&process->active);
              }

              return status_lock;
            }

            process->stack.array[process->stack.used++] = id_rule;

            f_thread_unlock(&process->lock);

            status_lock = controller_lock_read_process(process, global.thread, &process->lock);

            if (F_status_is_error(status_lock)) {
              controller_lock_print_error_critical(global.main->error, F_status_set_fine(status_lock), F_true, global.thread);

              if (options_force & controller_process_option_asynchronous_d) {
                f_thread_unlock(&process->active);
              }

              return status_lock;
            }
          }
        }
      }

      if (F_status_is_error_not(status)) {
        status = controller_rule_process(global, process);
      }
    }
    else {
      f_thread_unlock(&global.thread->lock.rule);

      status = F_status_set_error(F_found_not);

      if (global.main->error.verbosity != f_console_verbosity_quiet_e) {
        controller_lock_print(global.main->error.to, global.thread);

        controller_rule_item_print_error_rule_not_loaded(global.main->error, process->rule.alias.string);
        controller_rule_print_error_cache(global.main->error, process->cache.action, F_false);

        controller_unlock_print_flush(global.main->error.to, global.thread);
      }
    }

    if (status == F_child) {
      f_thread_unlock(&process->lock);

      if (options_force & controller_process_option_asynchronous_d) {
        f_thread_unlock(&process->active);
      }

      return status;
    }

    status_lock = controller_lock_write_process(process, global.thread, &global.thread->lock.rule);

    if (F_status_is_error(status_lock)) {
      controller_lock_print_error_critical(global.main->error, F_status_set_fine(status_lock), F_false, global.thread);

      if (F_status_set_fine(status) != F_lock) {
        f_thread_unlock(&process->lock);
      }

      if (options_force & controller_process_option_asynchronous_d) {
        f_thread_unlock(&process->active);
      }

      return status_lock;
    }

    if (F_status_set_fine(status) == F_lock) {
      if (controller_rule_find(process->rule.alias, global.setting->rules, &id_rule) == F_true) {
        global.setting->rules.array[id_rule].status[process->action] = status;
      }
    }

    f_thread_unlock(&global.thread->lock.rule);

    if (F_status_set_fine(status) != F_lock) {
      f_thread_unlock(&process->lock);
    }

    if (F_status_set_fine(status) == F_interrupt || F_status_set_fine(status) == F_lock && !controller_thread_is_enabled_process(process, global.thread)) {
      if (options_force & controller_process_option_asynchronous_d) {
        f_thread_unlock(&process->active);
      }

      return F_status_set_error(F_interrupt);
    }

    status_lock = controller_lock_write_process(process, global.thread, &process->lock);

    if (F_status_is_error(status_lock)) {
      controller_lock_print_error_critical(global.main->error, F_status_set_fine(status_lock), F_false, global.thread);

      if (options_force & controller_process_option_asynchronous_d) {
        f_thread_unlock(&process->active);
      }

      return status_lock;
    }

    if (options_force & controller_process_option_asynchronous_d) {
      process->state = controller_process_state_done_e;
    }
    else {
      process->state = controller_process_state_idle_e;
    }

    process->stack.used = used_original_stack;

    // inform all things waiting that the process has finished running.
    f_thread_mutex_lock(&process->wait_lock);
    f_thread_condition_signal_all(&process->wait);
    f_thread_mutex_unlock(&process->wait_lock);

    f_thread_unlock(&process->lock);

    if (options_force & controller_process_option_asynchronous_d) {
      f_thread_unlock(&process->active);
    }

    if (controller_thread_is_enabled_process(process, global.thread)) {
      return status;
    }

    return F_status_set_error(F_interrupt);
  }
#endif // _di_controller_rule_process_do_

#ifndef _di_controller_rule_read_
  f_status_t controller_rule_read(const controller_global_t global, const bool is_normal, const f_string_static_t alias, controller_cache_t * const cache, controller_entry_t * const entry, controller_rule_t * const rule) {

    f_status_t status = F_none;

    bool for_item = F_true;

    for (f_array_length_t i = 0; i < controller_rule_action_type__enum_size_e; ++i) {
      rule->status[i] = F_known_not;
    } // for

    rule->timeout_kill = entry->timeout_kill ? entry->timeout_kill : 0;
    rule->timeout_start = entry->timeout_start ? entry->timeout_start : 0;
    rule->timeout_stop = entry->timeout_stop ? entry->timeout_stop : 0;

    rule->has = 0;
    rule->group = 0;
    rule->user = 0;
    rule->nice = 0;

    macro_f_time_spec_t_clear(rule->timestamp);

    rule->alias.used = 0;
    rule->name.used = 0;
    rule->path.used = 0;
    rule->script.used = 0;

    rule->define.used = 0;
    rule->parameter.used = 0;
    rule->environment.used = 0;

    rule->affinity.used = 0;

    if (rule->capability) {
      f_capability_delete(&rule->capability);
      rule->capability = 0;
    }

    for (f_array_length_t i = 0; i < rule->cgroup.groups.size; ++i) {
      rule->cgroup.groups.array[i].used = 0;
    } // for

    rule->cgroup.as_new = F_false;
    rule->cgroup.path.used = 0;
    rule->cgroup.groups.used = 0;

    macro_f_control_group_t_clear(rule->cgroup);

    rule->groups.used = 0;
    rule->limits.used = 0;

    rule->scheduler.policy = 0;
    rule->scheduler.priority = 0;

    for (f_array_length_t i = 0; i < rule->ons.size; ++i) {
      rule->ons.array[i].need.used = 0;
      rule->ons.array[i].want.used = 0;
      rule->ons.array[i].wish.used = 0;
    } // for

    rule->ons.used = 0;
    rule->items.used = 0;

    cache->action.line_item = 0;
    cache->action.line_action = 0;

    cache->range_action.start = 1;
    cache->range_action.stop = 0;

    cache->comments.used = 0;
    cache->delimits.used = 0;

    cache->buffer_file.used = 0;
    cache->buffer_item.used = 0;
    cache->buffer_path.used = 0;

    for (f_array_length_t i = 0; i < cache->content_items.used; ++i) {
      cache->content_items.array[i].used = 0;
    } // for

    cache->content_items.used = 0;
    cache->object_items.used = 0;

    cache->action.name_action.used = 0;
    cache->action.name_file.used = 0;
    cache->action.name_item.used = 0;

    status = f_string_dynamic_append_nulless(alias, &rule->alias);

    if (F_status_is_error(status)) {
      controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "f_string_dynamic_append_nulless", F_true);
    }
    else {
      status = f_string_dynamic_terminate_after(&rule->alias);

      if (F_status_is_error(status)) {
        controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);
      }
      else {
        status = controller_file_load(global, F_true, controller_rules_s, rule->alias, controller_rule_s, controller_rules_s_length, controller_rule_s_length, cache);
      }
    }

    if (F_status_is_error_not(status)) {
      rule->timestamp = cache->timestamp;

      if (cache->buffer_file.used) {
        controller_state_interrupt_t custom = macro_controller_state_interrupt_t_initialize(is_normal, global.thread);
        f_state_t state = macro_f_state_t_initialize(controller_common_allocation_large_d, controller_common_allocation_small_d, 0, &controller_thread_signal_state_fss, 0, (void *) &custom, 0);
        f_string_range_t range = macro_f_string_range_t_initialize(cache->buffer_file.used);

        status = fll_fss_basic_list_read(cache->buffer_file, state, &range, &cache->object_items, &cache->content_items, &cache->delimits, 0, &cache->comments);

        if (F_status_is_error(status)) {
          controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "fll_fss_basic_list_read", F_true);
        }
        else {
          status = fl_fss_apply_delimit(cache->delimits, &cache->buffer_file);

          if (F_status_is_error(status)) {
            controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "fl_fss_apply_delimit", F_true);
          }
        }
      }
    }

    if (F_status_is_error_not(status) && cache->object_items.used) {
      status = controller_rule_items_increase_by(cache->object_items.used, &rule->items);

      if (F_status_is_error(status)) {
        controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "controller_rule_items_increase_by", F_true);
      }
      else {
        f_array_length_t i = 0;
        f_array_length_t j = 0;

        for (; i < cache->object_items.used; ++i) {

          cache->action.line_item = 0;
          cache->action.line_action = 0;

          cache->range_action.start = 1;
          cache->range_action.stop = 0;

          cache->comments.used = 0;
          cache->delimits.used = 0;

          cache->content_action.used = 0;

          for (j = 0; j < cache->content_actions.used; ++j) {
            cache->content_actions.array[j].used = 0;
          } // for

          cache->content_actions.used = 0;
          cache->object_actions.used = 0;

          cache->buffer_item.used = 0;
          cache->buffer_path.used = 0;

          cache->action.name_action.used = 0;
          cache->action.name_item.used = 0;

          for_item = F_true;

          status = f_fss_count_lines(cache->buffer_file, cache->object_items.array[i].start, &cache->action.line_item);

          if (F_status_is_error(status)) {
            controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "f_fss_count_lines", F_true);

            break;
          }

          rule->items.array[rule->items.used].line = ++cache->action.line_item;

          status = controller_dynamic_rip_nulless_terminated(cache->buffer_file, cache->object_items.array[i], &cache->action.name_item);

          if (F_status_is_error(status)) {
            controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "controller_dynamic_rip_nulless_terminated", F_true);

            break;
          }

          if (fl_string_dynamic_compare_string(controller_setting_s, cache->action.name_item, controller_setting_s_length) == F_equal_to) {
            rule->items.array[rule->items.used].type = 0;
          }
          else if (fl_string_dynamic_compare_string(controller_command_s, cache->action.name_item, controller_command_s_length) == F_equal_to) {
            rule->items.array[rule->items.used].type = controller_rule_item_type_command_e;
          }
          else if (fl_string_dynamic_compare_string(controller_script_s, cache->action.name_item, controller_script_s_length) == F_equal_to) {
            rule->items.array[rule->items.used].type = controller_rule_item_type_script_e;
          }
          else if (fl_string_dynamic_compare_string(controller_service_s, cache->action.name_item, controller_service_s_length) == F_equal_to) {
            rule->items.array[rule->items.used].type = controller_rule_item_type_service_e;
          }
          else if (fl_string_dynamic_compare_string(controller_utility_s, cache->action.name_item, controller_utility_s_length) == F_equal_to) {
            rule->items.array[rule->items.used].type = controller_rule_item_type_utility_e;
          }
          else {
            if (global.main->warning.verbosity == f_console_verbosity_debug_e) {
              controller_lock_print(global.main->warning.to, global.thread);

              fl_print_format("%c%[%SUnknown rule item '%]", global.main->warning.to.stream, f_string_eol_s[0], global.main->warning.context, global.main->warning.prefix, global.main->warning.context);
              fl_print_format("%[%Q%]", global.main->warning.to.stream, global.main->warning.notable, cache->action.name_item, global.main->warning.notable);
              fl_print_format("%['.%]%c", global.main->warning.to.stream, global.main->warning.context, global.main->warning.context, f_string_eol_s[0]);

              controller_rule_print_error_cache(global.main->warning, cache->action, F_true);

              controller_unlock_print_flush(global.main->warning.to, global.thread);
            }

            continue;
          }

          status = f_string_dynamic_partial_append(cache->buffer_file, cache->content_items.array[i].array[0], &cache->buffer_item);

          if (F_status_is_error(status)) {
            controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "f_string_dynamic_partial_append", F_true);

            break;
          }

          status = f_string_dynamic_terminate_after(&cache->buffer_item);

          if (F_status_is_error(status)) {
            controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);

            break;
          }

          if (rule->items.array[rule->items.used].type) {

            // Initialize the item with settings.
            rule->items.array[rule->items.used].with = 0;

            if (entry->session == controller_entry_session_new_e) {
              rule->items.array[rule->items.used].with |= controller_with_session_new_d;
            }
            else {
              rule->items.array[rule->items.used].with |= controller_with_session_same_d;
            }

            status = controller_rule_item_read(global, is_normal, cache, &rule->items.array[rule->items.used]);
            if (F_status_is_error(status)) break;

            ++rule->items.used;
          }
          else {
            for_item = F_false;

            status = controller_rule_setting_read(global, is_normal, *global.setting, cache, rule);

            if (F_status_is_error(status)) {
              if (F_status_set_fine(status) == F_memory_not) {
                break;
              }
            }
          }
        } // for
      }
    }

    if (F_status_is_error(status)) {
      controller_rule_item_print_error(global.thread, global.main->error, cache->action, for_item, F_status_set_fine(status));

      rule->status[0] = controller_status_simplify_error(F_status_set_fine(status));

      return rule->status[0];
    }

    return F_none;
  }
#endif // _di_controller_rule_read_

#ifndef _di_controller_rule_setting_read_
  f_status_t controller_rule_setting_read(const controller_global_t global, const bool is_normal, const controller_setting_t setting, controller_cache_t * const cache, controller_rule_t * const rule) {

    f_status_t status = F_none;
    f_status_t status_return = F_none;

    f_string_range_t range = macro_f_string_range_t_initialize(cache->buffer_item.used);
    f_string_range_t range2 = f_string_range_t_initialize;

    {
      controller_state_interrupt_t custom = macro_controller_state_interrupt_t_initialize(is_normal, global.thread);
      f_state_t state = macro_f_state_t_initialize(controller_common_allocation_large_d, controller_common_allocation_small_d, 0, &controller_thread_signal_state_fss, 0, (void *) &custom, 0);

      status = fll_fss_extended_read(cache->buffer_item, state, &range, &cache->object_actions, &cache->content_actions, 0, 0, &cache->delimits, 0);
    }

    if (F_status_is_error(status)) {
      controller_rule_print_error(global.thread, global.main->error, cache->action, F_status_set_fine(status), "fll_fss_extended_read", F_true, F_false);

      return status;
    }

    f_array_length_t path_original_length = 0;
    f_string_dynamic_t *setting_value = 0;
    f_string_dynamics_t *setting_values = 0;
    f_string_maps_t *setting_maps = 0;

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    uint8_t type = 0;
    uint8_t action = 0;
    bool empty_disallow = F_true;

    // Save the current name item and line number to restore on return.
    const f_array_length_t line_item = cache->action.line_item;
    const f_array_length_t length_name_item = cache->action.name_item.used;

    char name_item[length_name_item];
    name_item[length_name_item] = 0;

    memcpy(name_item, cache->action.name_item.string, length_name_item);

    for (; i < cache->content_actions.used; ++i, type = 0) {

      // The name_action is used to store all setting values for a single setting.
      cache->action.name_action.used = 0;

      // The name_item is used to store the setting name.
      cache->action.name_item.used = 0;

      status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->object_actions.array[i], &cache->action.name_item);

      if (F_status_is_error(status)) {
        controller_rule_print_error(global.thread, global.main->error, cache->action, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, F_false);
      }
      else {
        status = f_string_dynamic_terminate_after(&cache->action.name_item);

        if (F_status_is_error(status)) {
          controller_rule_print_error(global.thread, global.main->error, cache->action, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true, F_false);
        }
      }

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_memory_not) {
          status_return = status;
          break;
        }

        if (F_status_is_error_not(status_return)) {
          status_return = status;
        }

        // Get the current line number within the settings item.
        cache->action.line_item = line_item;
        f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

        cache->action.line_action = ++cache->action.line_item;

        controller_rule_item_print_error(global.thread, global.main->error, cache->action, F_false, F_status_set_fine(status));

        continue;
      }

      empty_disallow = F_true;

      if (fl_string_dynamic_compare_string(controller_affinity_s, cache->action.name_item, controller_affinity_s_length) == F_equal_to) {
        type = controller_rule_setting_type_affinity_e;
      }
      else if (fl_string_dynamic_compare_string(controller_capability_s, cache->action.name_item, controller_capability_s_length) == F_equal_to) {
        type = controller_rule_setting_type_capability_e;
      }
      else if (fl_string_dynamic_compare_string(controller_cgroup_s, cache->action.name_item, controller_cgroup_s_length) == F_equal_to) {
        type = controller_rule_setting_type_cgroup_e;
      }
      else if (fl_string_dynamic_compare_string(controller_define_s, cache->action.name_item, controller_define_s_length) == F_equal_to) {
        type = controller_rule_setting_type_define_e;
      }
      else if (fl_string_dynamic_compare_string(controller_environment_s, cache->action.name_item, controller_environment_s_length) == F_equal_to) {
        type = controller_rule_setting_type_environment_e;
        empty_disallow = F_false;
      }
      else if (fl_string_dynamic_compare_string(controller_group_s, cache->action.name_item, controller_group_s_length) == F_equal_to) {
        type = controller_rule_setting_type_group_e;
      }
      else if (fl_string_dynamic_compare_string(controller_limit_s, cache->action.name_item, controller_limit_s_length) == F_equal_to) {
        type = controller_rule_setting_type_limit_e;
      }
      else if (fl_string_dynamic_compare_string(controller_name_s, cache->action.name_item, controller_name_s_length) == F_equal_to) {
        type = controller_rule_setting_type_name_e;
      }
      else if (fl_string_dynamic_compare_string(controller_nice_s, cache->action.name_item, controller_nice_s_length) == F_equal_to) {
        type = controller_rule_setting_type_nice_e;
      }
      else if (fl_string_dynamic_compare_string(controller_on_s, cache->action.name_item, controller_on_s_length) == F_equal_to) {
        type = controller_rule_setting_type_on_e;
      }
      else if (fl_string_dynamic_compare_string(controller_parameter_s, cache->action.name_item, controller_parameter_s_length) == F_equal_to) {
        type = controller_rule_setting_type_parameter_e;
      }
      else if (fl_string_dynamic_compare_string(controller_path_s, cache->action.name_item, controller_path_s_length) == F_equal_to) {
        type = controller_rule_setting_type_path_e;
      }
      else if (fl_string_dynamic_compare_string(controller_scheduler_s, cache->action.name_item, controller_scheduler_s_length) == F_equal_to) {
        type = controller_rule_setting_type_scheduler_e;
      }
      else if (fl_string_dynamic_compare_string(controller_script_s, cache->action.name_item, controller_script_s_length) == F_equal_to) {
        type = controller_rule_setting_type_script_e;
      }
      else if (fl_string_dynamic_compare_string(controller_timeout_s, cache->action.name_item, controller_timeout_s_length) == F_equal_to) {
        type = controller_rule_setting_type_timeout_e;
      }
      else if (fl_string_dynamic_compare_string(controller_user_s, cache->action.name_item, controller_user_s_length) == F_equal_to) {
        type = controller_rule_setting_type_user_e;
      }
      else {
        if (global.main->warning.verbosity == f_console_verbosity_debug_e) {

          // Get the current line number within the settings item.
          cache->action.line_item = line_item;
          f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

          cache->action.line_action = ++cache->action.line_item;

          controller_lock_print(global.main->warning.to, global.thread);

          fl_print_format("%c%[%SUnknown rule setting '%]", global.main->warning.to.stream, f_string_eol_s[0], global.main->warning.context, global.main->warning.prefix, global.main->warning.context);
          fl_print_format("%[%Q%]", global.main->warning.to.stream, global.main->warning.notable, cache->action.name_item, global.main->warning.notable);
          fl_print_format("%['.%]%c", global.main->warning.to.stream, global.main->warning.context, global.main->warning.context, f_string_eol_s[0]);

          controller_rule_print_error_cache(global.main->warning, cache->action, F_false);

          controller_unlock_print_flush(global.main->warning.to, global.thread);
        }

        continue;
      }

      if (cache->content_actions.array[i].used) {
        range2.start = cache->content_actions.array[i].array[0].start;
        range2.stop = cache->content_actions.array[i].array[cache->content_actions.array[i].used - 1].stop;

        status = f_string_dynamic_partial_append_nulless(cache->buffer_item, range2, &cache->action.name_action);

        if (F_status_is_error(status)) {
          controller_rule_print_error(global.thread, global.main->error, cache->action, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, F_false);
        }
        else {
          status = f_string_dynamic_terminate_after(&cache->action.name_action);

          if (F_status_is_error(status)) {
            controller_rule_print_error(global.thread, global.main->error, cache->action, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true, F_false);
          }
        }

        if (F_status_is_error(status)) {

          // Get the current line number within the settings item.
          cache->action.line_item = line_item;
          f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

          cache->action.line_action = ++cache->action.line_item;

          controller_rule_item_print_error(global.thread, global.main->error, cache->action, F_false, F_status_set_fine(status));

          if (F_status_set_fine(status) == F_memory_not) {
            status_return = status;
            break;
          }

          if (F_status_is_error_not(status_return)) {
            status_return = status;
          }

          continue;
        }
      }
      else {
        if (empty_disallow) {
          if (global.main->warning.verbosity == f_console_verbosity_debug_e) {

            // Get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

            cache->action.line_action = ++cache->action.line_item;

            controller_lock_print(global.main->warning.to, global.thread);

            fl_print_format("%c%[%SEmpty rule setting.%]%c", global.main->warning.to.stream, f_string_eol_s[0], global.main->warning.context, global.main->warning.prefix, global.main->warning.context, f_string_eol_s[0]);

            controller_rule_print_error_cache(global.main->warning, cache->action, F_false);

            controller_unlock_print_flush(global.main->warning.to, global.thread);
          }

          continue;
        }
      }

      if (type == controller_rule_setting_type_affinity_e) {
        // @todo use sched_getaffinity() to get the available cpus and do not add an invalid cpu to the affinity array.

        if (!cache->content_actions.array[i].used) {
          controller_rule_setting_read_print_error(global.main->error, "requires one or more Content", i, line_item, global.thread, cache);

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        rule->affinity.used = 0;

        f_number_signed_t number = 0;

        for (j = 0; j < cache->content_actions.array[i].used; ++j, number = 0) {

          // @todo this needs to be in a function such as f_int32s_increase().
          if (rule->affinity.used + 1 > rule->affinity.size) {
            f_array_length_t size = rule->affinity.used + controller_common_allocation_small_d;

            if (size > F_array_length_t_size_d) {
              if (rule->affinity.used + 1 > F_array_length_t_size_d) {
                status = F_status_set_error(F_array_too_large);
              }
              else {
                size = F_array_length_t_size_d;
              }
            }

            if (F_status_is_error_not(status)) {
              macro_f_int32s_t_resize(status, rule->affinity, size);
            }
          }

          if (F_status_is_error(status)) {
            controller_rule_print_error(global.thread, global.main->error, cache->action, F_status_set_fine(status), "macro_f_int32s_t_resize", F_true, F_false);
            break;
          }

          status = fl_conversion_string_to_number_signed(cache->buffer_item.string, cache->content_actions.array[i].array[j], &number);

          if (F_status_set_fine(status) == F_number_positive) {
            status = fl_conversion_string_to_number_signed(cache->buffer_item.string, controller_range_after_number_sign(cache->buffer_item, cache->content_actions.array[i].array[j]), &number);

            // Restore error on parameter problem.
            if (F_status_set_fine(status) == F_parameter) {
              status = F_status_set_error(F_number_positive);
            }
          }

          if (F_status_is_error(status)) {
            status = F_status_set_fine(status);

            if (status == F_data_not || status == F_number || status == F_number_overflow || status == F_number_underflow || status == F_number_negative || status == F_number_decimal) {
              if (status == F_number_underflow) {
                controller_rule_setting_read_print_error_with_range(global.main->error, " has an unsupported number", cache->content_actions.array[i].array[j], ", the number is too small for this system", i, line_item, global.thread, cache);
              }
              else if (status == F_number_overflow || status == F_number_positive) {
                controller_rule_setting_read_print_error_with_range(global.main->error, " has an unsupported number", cache->content_actions.array[i].array[j], ", the number is too large for this system", i, line_item, global.thread, cache);
              }
              else {
                controller_rule_setting_read_print_error_with_range(global.main->error, " has an invalid number", cache->content_actions.array[i].array[j], ", only whole numbers are allowed for an affinity value", i, line_item, global.thread, cache);
              }

              status = F_status_set_error(F_valid_not);

              if (F_status_is_error_not(status_return)) {
                status_return = status;
              }
            }
            else {
              controller_rule_print_error(global.thread, global.main->error, cache->action, F_status_set_fine(status), "fl_conversion_string_to_number_signed", F_true, F_false);

              status = F_status_set_error(status);

              if (F_status_is_error_not(status_return)) {
                status_return = status;
              }
            }

            continue;
          }

          rule->affinity.array[rule->affinity.used++] = number;
        } // for

        controller_rule_setting_read_print_values(global, controller_affinity_s, i, cache);

        continue;
      }

      if (type == controller_rule_setting_type_define_e || type == controller_rule_setting_type_parameter_e) {
        if (cache->content_actions.array[i].used != 2) {
          controller_rule_setting_read_print_error(global.main->error, "requires exactly two Content", i, line_item, global.thread, cache);

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        if (type == controller_rule_setting_type_define_e) {
          setting_maps = &rule->define;
        }
        else if (type == controller_rule_setting_type_parameter_e) {
          setting_maps = &rule->parameter;
        }

        status = f_string_maps_increase(controller_common_allocation_small_d, setting_maps);

        if (F_status_is_error(status)) {
          controller_rule_print_error(global.thread, global.main->error, cache->action, F_status_set_fine(status), "f_string_maps_increase", F_true, F_false);

          if (F_status_set_fine(status) == F_memory_not) {
            status_return = status;
            break;
          }

          if (F_status_is_error_not(status_return)) {
            status_return = status;
          }

          // Get the current line number within the settings item.
          cache->action.line_item = line_item;
          f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

          cache->action.line_action = ++cache->action.line_item;

          controller_rule_item_print_error(global.thread, global.main->error, cache->action, F_false, F_status_set_fine(status));

          continue;
        }

        setting_maps->array[setting_maps->used].name.used = 0;
        setting_maps->array[setting_maps->used].value.used = 0;

        status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[0], &setting_maps->array[setting_maps->used].name);

        if (F_status_is_error(status)) {
          controller_rule_print_error(global.thread, global.main->error, cache->action, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, F_false);

          if (F_status_set_fine(status) == F_memory_not) {
            status_return = status;
            break;
          }

          if (F_status_is_error_not(status_return)) {
            status_return = status;
          }

          // Get the current line number within the settings item.
          cache->action.line_item = line_item;
          f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

          cache->action.line_action = ++cache->action.line_item;

          controller_rule_item_print_error(global.thread, global.main->error, cache->action, F_false, F_status_set_fine(status));

          continue;
        }

        status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[1], &setting_maps->array[setting_maps->used].value);

        if (F_status_is_error(status)) {
          controller_rule_print_error(global.thread, global.main->error, cache->action, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, F_false);
        }
        else {
          status = f_string_dynamic_terminate_after(&setting_maps->array[setting_maps->used].value);

          if (F_status_is_error(status)) {
            controller_rule_print_error(global.thread, global.main->error, cache->action, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true, F_false);
          }
        }

        if (F_status_is_error(status)) {
          if (F_status_set_fine(status) == F_memory_not) {
            status_return = status;

            break;
          }

          if (F_status_is_error_not(status_return)) {
            status_return = status;
          }

          // Get the current line number within the settings item.
          cache->action.line_item = line_item;
          f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

          cache->action.line_action = ++cache->action.line_item;

          controller_rule_item_print_error(global.thread, global.main->error, cache->action, F_false, F_status_set_fine(status));

          continue;
        }

        controller_rule_setting_read_print_value(global, type == controller_rule_setting_type_define_e ? controller_define_s : controller_parameter_s, 0, setting_maps->array[setting_maps->used].name, 0);

        ++setting_maps->used;

        continue;
      }

      if (type == controller_rule_setting_type_cgroup_e) {
        if (cache->content_actions.array[i].used < 2 || rule->has & controller_rule_has_cgroup_d) {
          controller_rule_setting_read_print_error(global.main->error, "requires two or more Content", i, line_item, global.thread, cache);

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        if (fl_string_dynamic_partial_compare_string(controller_existing_s, cache->buffer_item, controller_existing_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          rule->cgroup.as_new = F_false;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_new_s, cache->buffer_item, controller_new_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          rule->cgroup.as_new = F_true;
        }
        else {
          controller_rule_setting_read_print_error_with_range(global.main->error, " has an unknown option", cache->content_actions.array[i].array[0], "", i, line_item, global.thread, cache);

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        rule->cgroup.path.used = 0;

        status = f_string_dynamic_append(global.setting->path_cgroup, &rule->cgroup.path);

        if (F_status_is_error(status)) {
          controller_rule_print_error(global.thread, global.main->error, cache->action, F_status_set_fine(status), "f_string_dynamic_append", F_true, F_false);
        }
        else {
          rule->cgroup.groups.used = 0;

          for (j = 1; j < cache->content_actions.array[i].used; ++j) {

            status = f_string_dynamics_increase(controller_common_allocation_small_d, &rule->cgroup.groups);

            if (F_status_is_error(status)) {
              controller_rule_print_error(global.thread, global.main->error, cache->action, F_status_set_fine(status), "f_string_dynamics_increase", F_true, F_false);
              break;
            }

            rule->cgroup.groups.array[rule->cgroup.groups.used].used = 0;

            status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[j], &rule->cgroup.groups.array[rule->cgroup.groups.used]);

            if (F_status_is_error(status)) {
              controller_rule_print_error(global.thread, global.main->error, cache->action, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, F_false);
              break;
            }

            ++rule->cgroup.groups.used;
          } // for
        }

        if (F_status_is_error(status)) {
          if (F_status_set_fine(status) == F_memory_not) {
            status_return = status;
            break;
          }

          rule->cgroup.path.used = 0;

          if (F_status_is_error_not(status_return)) {
            status_return = status;
          }

          // get the current line number within the settings item.
          cache->action.line_item = line_item;
          f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

          cache->action.line_action = ++cache->action.line_item;

          controller_rule_item_print_error(global.thread, global.main->error, cache->action, F_false, F_status_set_fine(status));

          continue;
        }

        rule->has |= controller_rule_has_cgroup_d;

        controller_rule_setting_read_print_values(global, controller_cgroup_s, i, cache);

        continue;
      }

      if (type == controller_rule_setting_type_limit_e) {
        if (cache->content_actions.array[i].used != 3) {
          controller_rule_setting_read_print_error(global.main->error, "requires three Content", i, line_item, global.thread, cache);

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        if (fl_string_dynamic_partial_compare_string(controller_as_s, cache->buffer_item, controller_as_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_as_e;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_core_s, cache->buffer_item, controller_core_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_core_e;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_cpu_s, cache->buffer_item, controller_cpu_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_cpu_e;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_data_s, cache->buffer_item, controller_data_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_data_e;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_fsize_s, cache->buffer_item, controller_fsize_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_fsize_e;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_locks_s, cache->buffer_item, controller_locks_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_locks_e;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_memlock_s, cache->buffer_item, controller_memlock_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_memlock_e;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_msgqueue_s, cache->buffer_item, controller_msgqueue_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_msgqueue_e;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_nice_s, cache->buffer_item, controller_nice_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_nice_e;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_nofile_s, cache->buffer_item, controller_nofile_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_nofile_e;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_nproc_s, cache->buffer_item, controller_nproc_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_nproc_e;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_rss_s, cache->buffer_item, controller_rss_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_rss_e;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_rtprio_s, cache->buffer_item, controller_rtprio_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_rtprio_e;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_rttime_s, cache->buffer_item, controller_rttime_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_rttime_e;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_sigpending_s, cache->buffer_item, controller_sigpending_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_sigpending_e;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_stack_s, cache->buffer_item, controller_stack_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_stack_e;
        }
        else {
          if (global.main->error.verbosity == f_console_verbosity_debug_e) {

            // Get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

            cache->action.line_action = ++cache->action.line_item;

            controller_lock_print(global.main->error.to, global.thread);

            fl_print_format("%c%[%SUnknown resource limit type '%]", global.main->error.to.stream, f_string_eol_s[0], global.main->error.context, global.main->error.prefix, global.main->error.context);
            fl_print_format("%[%Q%]", global.main->error.to.stream, global.main->error.notable, cache->action.name_action, global.main->error.notable);
            fl_print_format("%['.%]%c", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s[0]);

            controller_rule_print_error_cache(global.main->error, cache->action, F_true);

            controller_unlock_print_flush(global.main->error.to, global.thread);
          }

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        for (j = 0; j < rule->limits.used; ++j) {

          if (type == rule->limits.array[j].type) {
            if (global.main->error.verbosity != f_console_verbosity_quiet_e) {

              // get the current line number within the settings item.
              cache->action.line_item = line_item;
              f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

              cache->action.line_action = ++cache->action.line_item;

              controller_lock_print(global.main->error.to, global.thread);

              fl_print_format("%c%[%SThe resource limit type is already specified%]%c", global.main->error.to.stream, f_string_eol_s[0], global.main->error.context, global.main->error.context, f_string_eol_s[0]);

              controller_rule_print_error_cache(global.main->error, cache->action, F_false);

              controller_unlock_print_flush(global.main->error.to, global.thread);
            }

            status = F_status_set_error(F_valid_not);

            if (F_status_is_error_not(status_return)) {
              status_return = status;
            }
          }
        } // for

        if (F_status_is_error(status)) continue;

        macro_f_limit_sets_t_increase(status, controller_common_allocation_small_d, rule->limits);

        if (F_status_is_error(status)) {
          controller_rule_print_error(global.thread, global.main->error, cache->action, F_status_set_fine(status), "f_limit_sets_increase", F_true, F_false);

          if (F_status_set_fine(status) == F_memory_not) {
            status_return = status;
            break;
          }

          if (F_status_is_error_not(status_return)) {
            status_return = status;
          }

          // get the current line number within the settings item.
          cache->action.line_item = line_item;
          f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

          cache->action.line_action = ++cache->action.line_item;

          controller_rule_item_print_error(global.thread, global.main->error, cache->action, F_false, F_status_set_fine(status));

          continue;
        }

        f_number_signed_t number = 0;

        for (j = 1; j < 3; ++j, number = 0) {

          status = fl_conversion_string_to_number_signed(cache->buffer_item.string, cache->content_actions.array[i].array[j], &number);

          if (F_status_set_fine(status) == F_number_positive) {
            status = fl_conversion_string_to_number_signed(cache->buffer_item.string, controller_range_after_number_sign(cache->buffer_item, cache->content_actions.array[i].array[j]), &number);

            // Restore error on parameter problem.
            if (F_status_set_fine(status) == F_parameter) {
              status = F_status_set_error(F_number_positive);
            }
          }

          if (F_status_is_error(status)) {
            status = F_status_set_fine(status);

            if (status == F_data_not || status == F_number || status == F_number_overflow || status == F_number_underflow || status == F_number_negative || status == F_number_positive || status == F_number_decimal) {
              if (status == F_number_underflow) {
                controller_rule_setting_read_print_error_with_range(global.main->error, " has an unsupported number", cache->content_actions.array[i].array[j], ", the number is too small for this system", i, line_item, global.thread, cache);
              }
              else if (status == F_number_overflow) {
                controller_rule_setting_read_print_error_with_range(global.main->error, " has an unsupported number", cache->content_actions.array[i].array[j], ", the number is too large for this system", i, line_item, global.thread, cache);
              }
              else {
                controller_rule_setting_read_print_error_with_range(global.main->error, " has an unsupported number", cache->content_actions.array[i].array[j], ", only whole numbers are allowed for a resource limit value", i, line_item, global.thread, cache);
              }

              status = F_status_set_error(F_valid_not);

              if (F_status_is_error_not(status_return)) {
                status_return = status;
              }
            }
            else {
              controller_rule_print_error(global.thread, global.main->error, cache->action, F_status_set_fine(status), "fl_conversion_string_to_number_signed", F_true, F_false);

              status = F_status_set_error(status);

              if (F_status_is_error_not(status_return)) {
                status_return = status;
              }
            }

            break;
          }

          if (j == 1) {
            rule->limits.array[rule->limits.used].value.rlim_cur = number;
          }
          else {
            rule->limits.array[rule->limits.used].value.rlim_max = number;
          }
        } // for

        if (F_status_is_error(status)) continue;

        rule->limits.array[rule->limits.used++].type = type;

        controller_rule_setting_read_print_values(global, controller_limit_s, i, cache);

        continue;
      }

      if (type == controller_rule_setting_type_name_e || type == controller_rule_setting_type_path_e || type == controller_rule_setting_type_script_e) {

        if (type == controller_rule_setting_type_name_e) {
          setting_value = &rule->name;
        }
        else if (type == controller_rule_setting_type_path_e) {
          setting_value = &rule->path;
        }
        else if (type == controller_rule_setting_type_script_e) {
          setting_value = &rule->script;
        }

        if (setting_value->used || cache->content_actions.array[i].used != 1) {
          controller_rule_setting_read_print_error(global.main->error, "requires exactly one Content", i, line_item, global.thread, cache);

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        if (type == controller_rule_setting_type_name_e || type == controller_rule_setting_type_script_e) {
          status = controller_dynamic_rip_nulless_terminated(cache->buffer_item, cache->content_actions.array[i].array[0], setting_value);

          if (F_status_is_error(status)) {
            setting_value->used = 0;

            if (F_status_set_fine(status) == F_memory_not) {
              status_return = status;
              break;
            }

            if (F_status_is_error_not(status_return)) {
              status_return = status;
            }

            // get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

            cache->action.line_action = ++cache->action.line_item;

            controller_rule_item_print_error(global.thread, global.main->error, cache->action, F_false, F_status_set_fine(status));

            continue;
          }

          status = controller_validate_has_graph(*setting_value);

          if (status == F_false || F_status_set_fine(status) == F_complete_not_utf) {
            if (global.main->error.verbosity != f_console_verbosity_quiet_e) {

              // get the current line number within the settings item.
              cache->action.line_item = line_item;
              f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

              cache->action.line_action = ++cache->action.line_item;
            }

            if (status == F_false) {
              if (global.main->error.verbosity != f_console_verbosity_quiet_e) {
                controller_lock_print(global.main->error.to, global.thread);

                fl_print_format("%c%[%SRule setting has an invalid name '%]", global.main->error.to.stream, f_string_eol_s[0], global.main->error.context, global.main->error.prefix, global.main->error.context);
                fl_print_format("%[%Q%]", global.main->error.to.stream, global.main->error.notable, *setting_value, global.main->error.notable);
                fl_print_format("%[', there must be at least 1 graph character.%]%c", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s[0]);

                controller_rule_print_error_cache(global.main->error, cache->action, F_false);

                controller_unlock_print_flush(global.main->error.to, global.thread);
              }

              if (F_status_is_error_not(status_return)) {
                status_return = F_status_set_error(F_valid_not);
              }
            }
            else {

              // this function should only return F_complete_not_utf on error.
              controller_rule_print_error(global.thread, global.main->error, cache->action, F_complete_not_utf, "controller_validate_has_graph", F_true, F_false);

              if (F_status_is_error_not(status_return)) {
                status_return = status;
              }

              controller_rule_item_print_error(global.thread, global.main->error, cache->action, F_false, F_status_set_fine(status));
            }

            setting_value->used = 0;

            continue;
          }

          controller_rule_setting_read_print_value(global, type == controller_rule_setting_type_name_e ? controller_name_s : controller_script_s, 0, *setting_value, 0);
        }
        else if (type == controller_rule_setting_type_path_e) {
          status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[0], setting_value);

          if (F_status_is_error(status)) {
            controller_rule_print_error(global.thread, global.main->error, cache->action, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, F_false);
          }
          else {
            status = f_string_dynamic_terminate_after(setting_value);

            if (F_status_is_error(status)) {
              controller_rule_print_error(global.thread, global.main->error, cache->action, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true, F_false);
            }
          }

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_memory_not) {
              status_return = status;
              break;
            }

            if (F_status_is_error_not(status_return)) {
              status_return = status;
            }

            setting_value->used = 0;

            // get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

            cache->action.line_action = ++cache->action.line_item;

            controller_rule_item_print_error(global.thread, global.main->error, cache->action, F_false, F_status_set_fine(status));

            continue;
          }

          controller_rule_setting_read_print_value(global, controller_path_s, 0, *setting_value, 0);
        }

        continue;
      }

      if (type == controller_rule_setting_type_scheduler_e) {

        if (cache->content_actions.array[i].used < 1 || cache->content_actions.array[i].used > 2 || rule->has & controller_rule_has_scheduler_d) {
          controller_rule_setting_read_print_error(global.main->error, "requires either one or two Content", i, line_item, global.thread, cache);

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        if (fl_string_dynamic_partial_compare_string(controller_batch_s, cache->buffer_item, controller_batch_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          rule->scheduler.policy = SCHED_BATCH;
          rule->scheduler.priority = 0;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_deadline_s, cache->buffer_item, controller_deadline_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          rule->scheduler.policy = SCHED_DEADLINE;
          rule->scheduler.priority = 49;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_fifo_s, cache->buffer_item, controller_fifo_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          rule->scheduler.policy = SCHED_FIFO;
          rule->scheduler.priority = 49;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_idle_s, cache->buffer_item, controller_idle_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          rule->scheduler.policy = SCHED_IDLE;
          rule->scheduler.priority = 0;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_other_s, cache->buffer_item, controller_other_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          rule->scheduler.policy = SCHED_OTHER;
          rule->scheduler.priority = 0;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_round_robin_s, cache->buffer_item, controller_round_robin_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          rule->scheduler.policy = SCHED_RR;
          rule->scheduler.priority = 49;
        }
        else {
          controller_rule_setting_read_print_error_with_range(global.main->error, " has an unknown scheduler", cache->content_actions.array[i].array[0], "", i, line_item, global.thread, cache);

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        if (cache->content_actions.array[i].used > 1) {
          const bool zero_only = rule->scheduler.policy == SCHED_BATCH || rule->scheduler.policy == SCHED_IDLE || rule->scheduler.policy == SCHED_OTHER;

          f_number_signed_t number = 0;

          status = fl_conversion_string_to_number_signed(cache->buffer_item.string, cache->content_actions.array[i].array[1], &number);

          if (F_status_set_fine(status) == F_number_positive) {
            status = fl_conversion_string_to_number_signed(cache->buffer_item.string, controller_range_after_number_sign(cache->buffer_item, cache->content_actions.array[i].array[1]), &number);

            // Restore error on parameter problem.
            if (F_status_set_fine(status) == F_parameter) {
              status = F_status_set_error(F_number_positive);
            }
          }

          if (F_status_is_error(status) || (zero_only && number) || (!zero_only && (number < 1 || number > 99))) {
            status = F_status_set_fine(status);

            if ((zero_only && number) || (!zero_only && (number < 1 || number > 99)) || status == F_data_not || status == F_number || status == F_number_overflow || status == F_number_negative || status == F_number_positive) {
              if (global.main->error.verbosity != f_console_verbosity_quiet_e) {

                // get the current line number within the settings item.
                cache->action.line_item = line_item;
                f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

                cache->action.line_action = ++cache->action.line_item;

                controller_lock_print(global.main->error.to, global.thread);

                fl_print_format("%c%[%SRule setting has an invalid number '%]", global.main->error.to.stream, f_string_eol_s[0], global.main->error.context, global.main->error.prefix, global.main->error.context);
                fl_print_format("%[%/Q%]", global.main->error.to.stream, global.main->error.notable, cache->buffer_item, cache->content_actions.array[i].array[1], global.main->error.notable);

                if (zero_only) {
                  fl_print_format("%[', only%] ", global.main->error.to.stream, global.main->error.context, global.main->error.context);
                  fl_print_format("%[0%]%[ is", global.main->error.to.stream, global.main->error.notable, global.main->error.notable, global.main->error.context);
                }
                else {
                  fl_print_format("%[', only the whole numbers inclusively between%] ", global.main->error.to.stream, global.main->error.context, global.main->error.context);
                  fl_print_format("%[1%] %[and%] ", global.main->error.to.stream, global.main->error.notable, global.main->error.notable, global.main->error.context, global.main->error.context);
                  fl_print_format("%[99%] %[are", global.main->error.to.stream, global.main->error.notable, global.main->error.notable, global.main->error.context);
                }

                fl_print_format(" allowed for the designated scheduler.%]%c", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s[0]);

                controller_rule_print_error_cache(global.main->error, cache->action, F_false);

                controller_unlock_print_flush(global.main->error.to, global.thread);
              }

              if (F_status_is_error_not(status_return)) {
                status_return = F_status_set_error(F_valid_not);
              }
            }
            else {
              controller_rule_print_error(global.thread, global.main->error, cache->action, status, "fl_conversion_string_to_number_signed", F_true, F_false);
              status = F_status_set_error(status);

              if (F_status_is_error_not(status_return)) {
                status_return = status;
              }
            }

            continue;
          }

          rule->scheduler.priority = number;
        }

        rule->has |= controller_rule_has_scheduler_d;

        controller_rule_setting_read_print_values(global, controller_scheduler_s, i, cache);

        continue;
      }

      if (type == controller_rule_setting_type_timeout_e) {
        if (cache->content_actions.array[i].used != 2) {
          controller_rule_setting_read_print_error(global.main->error, "requires exactly two Content", i, line_item, global.thread, cache);

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        uint8_t timeout_code = 0;

        if (fl_string_dynamic_partial_compare_string(controller_kill_s, cache->buffer_item, controller_kill_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          timeout_code = controller_rule_timeout_code_kill_d;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_start_s, cache->buffer_item, controller_start_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          timeout_code = controller_rule_timeout_code_start_d;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_stop_s, cache->buffer_item, controller_stop_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          timeout_code = controller_rule_timeout_code_stop_d;
        }
        else {
          if (global.main->error.verbosity != f_console_verbosity_quiet_e) {

            // Get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

            cache->action.line_action = ++cache->action.line_item;

            controller_lock_print(global.main->error.to, global.thread);

            fl_print_format("%c%[%SRule setting's first value has '%]", global.main->error.to.stream, f_string_eol_s[0], global.main->error.context, global.main->error.prefix, global.main->error.context);
            fl_print_format("%[%/Q%]", global.main->error.to.stream, global.main->error.notable, cache->buffer_item, cache->content_actions.array[i].array[0], global.main->error.notable);
            fl_print_format("%[' but only supports %s, %s, and %s.%]%c", global.main->error.to.stream, global.main->error.context, controller_kill_s, controller_start_s, controller_stop_s, global.main->error.context, f_string_eol_s[0]);

            controller_rule_print_error_cache(global.main->error, cache->action, F_false);

            controller_unlock_print_flush(global.main->error.to, global.thread);
          }

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        f_number_unsigned_t number = 0;

        status = fl_conversion_string_to_number_unsigned(cache->buffer_item.string, cache->content_actions.array[i].array[1], &number);

        if (F_status_set_fine(status) == F_number_positive) {
          status = fl_conversion_string_to_number_unsigned(cache->buffer_item.string, controller_range_after_number_sign(cache->buffer_item, cache->content_actions.array[i].array[1]), &number);

          // Restore error on parameter problem.
          if (F_status_set_fine(status) == F_parameter) {
            status = F_status_set_error(F_number_positive);
          }
        }

        if (F_status_is_error(status)) {
          status = F_status_set_fine(status);

          if (status == F_number_overflow) {
            controller_rule_setting_read_print_error_with_range(global.main->error, " has an unsupported number", cache->content_actions.array[i].array[1], ", the number is too large for this system", i, line_item, global.thread, cache);
          }
          else if (status == F_data_not || status == F_number || status == F_number_underflow || status == F_number_negative || status == F_number_positive || status == F_number_decimal) {
            controller_rule_setting_read_print_error_with_range(global.main->error, " has an invalid number", cache->content_actions.array[i].array[1], ", only positive whole numbers are allowed", i, line_item, global.thread, cache);
          }
          else {

            // Get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

            cache->action.line_action = ++cache->action.line_item;

            controller_rule_print_error(global.thread, global.main->error, cache->action, status, "fl_conversion_string_to_number_signed", F_true, F_false);
          }

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }
        }
        else {
          if (timeout_code == controller_rule_timeout_code_kill_d) {
            rule->timeout_kill = number;
          }
          else if (timeout_code == controller_rule_timeout_code_start_d) {
            rule->timeout_start = number;
          }
          else {
            rule->timeout_stop = number;
          }

          if (global.main->error.verbosity == f_console_verbosity_debug_e || (global.main->error.verbosity == f_console_verbosity_verbose_e && global.main->parameters[controller_parameter_simulate_e].result == f_console_result_found_e)) {
            f_string_t name_sub = controller_stop_s;

            if (timeout_code == controller_rule_timeout_code_kill_d) {
              name_sub = controller_kill_s;
            }
            else if (timeout_code == controller_rule_timeout_code_start_d) {
              name_sub = controller_start_s;
            }

            cache->action.generic.used = 0;

            status = controller_dynamic_rip_nulless_terminated(cache->buffer_item, cache->content_actions.array[i].array[1], &cache->action.generic);

            if (F_status_is_error(status)) {
              controller_print_error(global.thread, global.main->error, F_status_set_fine(status), "controller_dynamic_rip_nulless_terminated", F_true);

              break;
            }

            controller_rule_setting_read_print_value(global, controller_timeout_s, name_sub, cache->action.generic, 0);
          }
        }

        continue;
      }

      if (type == controller_rule_setting_type_capability_e || type == controller_rule_setting_type_nice_e || type == controller_rule_setting_type_user_e) {
        if (cache->content_actions.array[i].used != 1 || type == controller_rule_setting_type_capability_e && rule->capability || type == controller_rule_setting_type_group_e && (rule->has & controller_rule_has_group_d) || type == controller_rule_setting_type_nice_e && (rule->has & controller_rule_has_nice_d) || type == controller_rule_setting_type_user_e && (rule->has & controller_rule_has_user_d)) {
          controller_rule_setting_read_print_error(global.main->error, "requires exactly one Content", i, line_item, global.thread, cache);

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        if (type == controller_rule_setting_type_capability_e) {
          cache->action.generic.used = 0;

          status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[0], &cache->action.generic);

          if (F_status_is_error(status)) {

            // Get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

            cache->action.line_action = ++cache->action.line_item;

            controller_lock_print(global.main->error.to, global.thread);

            controller_rule_print_error(global.thread, global.main->error, cache->action, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, F_false);

            controller_rule_print_error_cache(global.main->error, cache->action, F_false);

            controller_unlock_print_flush(global.main->error.to, global.thread);

            if (F_status_set_fine(status) == F_memory_not) {
              status_return = status;
              break;
            }

            if (F_status_is_error_not(status_return)) {
              status_return = F_status_set_error(F_valid_not);
            }
          }

          status = f_string_dynamic_terminate_after(&cache->action.generic);

          if (F_status_is_error(status)) {

            // Get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

            cache->action.line_action = ++cache->action.line_item;

            controller_lock_print(global.main->error.to, global.thread);

            controller_rule_print_error(global.thread, global.main->error, cache->action, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true, F_false);

            controller_rule_print_error_cache(global.main->error, cache->action, F_false);

            controller_unlock_print_flush(global.main->error.to, global.thread);

            if (F_status_set_fine(status) == F_memory_not) {
              status_return = status;
              break;
            }

            if (F_status_is_error_not(status_return)) {
              status_return = F_status_set_error(F_valid_not);
            }
          }

          status = f_capability_from_text(cache->action.generic.string, &rule->capability);

          if (F_status_is_error(status) && F_status_set_fine(status) != F_supported_not) {
            if (F_status_set_fine(status) == F_memory_not) {

              // Get the current line number within the settings item.
              cache->action.line_item = line_item;
              f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

              cache->action.line_action = ++cache->action.line_item;

              controller_lock_print(global.main->error.to, global.thread);

              controller_rule_print_error(global.thread, global.main->error, cache->action, F_status_set_fine(status), "f_capability_from_text", F_true, F_false);

              controller_rule_print_error_cache(global.main->error, cache->action, F_false);

              controller_unlock_print_flush(global.main->error.to, global.thread);

              status_return = status;
              break;
            }

            controller_rule_setting_read_print_error(global.main->error, "failed to process the capabilities", i, line_item, global.thread, cache);

            if (F_status_is_error_not(status_return)) {
              status_return = F_status_set_error(F_valid_not);
            }

            continue;
          }

          controller_rule_setting_read_print_value(global, controller_capability_s, 0, cache->action.generic, 0);
        }
        else if (type == controller_rule_setting_type_nice_e) {
          f_number_signed_t number = 0;

          status = fl_conversion_string_to_number_signed(cache->buffer_item.string, cache->content_actions.array[i].array[0], &number);

          if (F_status_set_fine(status) == F_number_positive) {
            status = fl_conversion_string_to_number_signed(cache->buffer_item.string, controller_range_after_number_sign(cache->buffer_item, cache->content_actions.array[i].array[0]), &number);

            // Restore error on parameter problem.
            if (F_status_set_fine(status) == F_parameter) {
              status = F_status_set_error(F_number_positive);
            }
          }

          if (F_status_is_error(status) || number < -20 || number > 19) {
            status = F_status_set_fine(status);

            if (number < -20 || number > 19 || status == F_data_not || status == F_number || status == F_number_overflow || status == F_number_underflow || status == F_number_decimal) {
              if (global.main->error.verbosity != f_console_verbosity_quiet_e) {

                // Get the current line number within the settings item.
                cache->action.line_item = line_item;
                f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

                cache->action.line_action = ++cache->action.line_item;

                controller_lock_print(global.main->error.to, global.thread);

                fl_print_format("%c%[%SRule setting has an invalid number '%]", global.main->error.to.stream, f_string_eol_s[0], global.main->error.context, global.main->error.prefix, global.main->error.context);
                fl_print_format("%[%/Q%]", global.main->error.to.stream, global.main->error.notable, cache->buffer_item, cache->content_actions.array[i].array[0], global.main->error.notable);
                fl_print_format("%[', only the whole numbers inclusively between%] ", global.main->error.to.stream, global.main->error.context, global.main->error.context);
                fl_print_format("%[-20%]", global.main->error.to.stream, global.main->error.notable, global.main->error.notable);
                fl_print_format(" %[and%] ", global.main->error.to.stream, global.main->error.context, global.main->error.context);
                fl_print_format("%[19%]", global.main->error.to.stream, global.main->error.notable, global.main->error.notable);
                fl_print_format(" %[are allowed.%]%c", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s[0]);

                controller_rule_print_error_cache(global.main->error, cache->action, F_false);

                controller_unlock_print_flush(global.main->error.to, global.thread);
              }

              if (F_status_is_error_not(status_return)) {
                status_return = F_status_set_error(F_valid_not);
              }
            }
            else {
              controller_rule_print_error(global.thread, global.main->error, cache->action, status, "fl_conversion_string_to_number_signed", F_true, F_false);
              status = F_status_set_error(status);

              if (F_status_is_error_not(status_return)) {
                status_return = status;
              }
            }
          }
          else {
            rule->nice = number;
            rule->has |= controller_rule_has_nice_d;

            if (global.main->parameters[controller_parameter_simulate_e].result == f_console_result_found_e || global.main->error.verbosity == f_console_verbosity_verbose_e) {
              cache->action.generic.used = 0;

              status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[0], &cache->action.generic);

              if (F_status_is_error_not(status)) {
                status = f_string_dynamic_terminate_after(&cache->action.generic);
              }

              if (F_status_is_error(status)) {

                // Get the current line number within the settings item.
                cache->action.line_item = line_item;
                f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

                cache->action.line_action = ++cache->action.line_item;

                controller_lock_print(global.main->error.to, global.thread);

                controller_rule_print_error(global.thread, global.main->error, cache->action, F_status_set_fine(status), cache->action.generic.used ? "f_string_dynamic_partial_append_nulless" : "f_string_dynamic_terminate_after", F_true, F_false);

                controller_rule_print_error_cache(global.main->error, cache->action, F_false);

                controller_unlock_print_flush(global.main->error.to, global.thread);

                if (F_status_set_fine(status) == F_memory_not) {
                  status_return = status;
                  break;
                }

                if (F_status_is_error_not(status_return)) {
                  status_return = F_status_set_error(F_valid_not);
                }
              }

              if (F_status_is_error_not(status)) {
                controller_rule_setting_read_print_value(global, controller_nice_s, 0, cache->action.generic, 0);
              }
            }
          }
        }
        else if (type == controller_rule_setting_type_user_e) {
          uid_t number = 0;

          status = controller_get_id_user(cache->buffer_item, cache->content_actions.array[i].array[0], cache, &number);

          if (F_status_is_error(status)) {
            status = F_status_set_fine(status);

            if (status == F_exist_not) {
              controller_rule_setting_read_print_error_with_range(global.main->error, " has an invalid user", cache->content_actions.array[i].array[0], ", because no user was found by that name", i, line_item, global.thread, cache);
            }
            else if (status == F_number_too_large) {
              controller_rule_setting_read_print_error_with_range(global.main->error, " has an invalid user", cache->content_actions.array[i].array[0], ", because the given ID is too large", i, line_item, global.thread, cache);
            }
            else if (status == F_number) {
              controller_rule_setting_read_print_error_with_range(global.main->error, " has an invalid user", cache->content_actions.array[i].array[0], ", because the given ID is not a valid supported number", i, line_item, global.thread, cache);
            }
            else {

              // Get the current line number within the settings item.
              cache->action.line_item = line_item;
              f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

              cache->action.line_action = ++cache->action.line_item;

              controller_rule_print_error(global.thread, global.main->error, cache->action, status, "controller_get_id_user", F_true, F_false);

              controller_rule_item_print_error(global.thread, global.main->error, cache->action, F_false, F_status_set_fine(status));
            }

            if (F_status_is_error_not(status_return)) {
              status_return = F_status_set_error(status);
            }
          }
          else {
            rule->user = number;
            rule->has |= controller_rule_has_user_d;

            if (global.main->error.verbosity == f_console_verbosity_debug_e || (global.main->error.verbosity == f_console_verbosity_verbose_e && global.main->parameters[controller_parameter_simulate_e].result == f_console_result_found_e)) {
              cache->action.generic.used = 0;

              status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[0], &cache->action.generic);

              if (F_status_is_error_not(status)) {
                status = f_string_dynamic_terminate_after(&cache->action.generic);
              }

              controller_rule_setting_read_print_value(global, controller_user_s, 0, cache->action.generic, 0);
            }
          }
        }

        continue;
      }

      if (type == controller_rule_setting_type_group_e) {
        if (!cache->content_actions.array[i].used) {
          controller_rule_setting_read_print_error(global.main->error, "requires one or more Content", i, line_item, global.thread, cache);

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        gid_t number = 0;

        rule->groups.used = 0;

        for (j = 0; j < cache->content_actions.array[i].used; ++j) {

          macro_f_int32s_t_increase_by(status, rule->groups, controller_common_allocation_small_d)

          if (F_status_is_error(status)) {
            controller_rule_print_error(global.thread, global.main->error, cache->action, F_status_set_fine(status), "macro_f_array_lengths_t_increase_by", F_true, F_false);

            if (F_status_set_fine(status) == F_memory_not) {
              status_return = status;
              break;
            }

            if (F_status_is_error_not(status_return)) {
              status_return = status;
            }

            // Get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

            cache->action.line_action = ++cache->action.line_item;

            controller_rule_item_print_error(global.thread, global.main->error, cache->action, F_false, F_status_set_fine(status));

            continue;
          }

          status = controller_get_id_group(cache->buffer_item, cache->content_actions.array[i].array[j], cache, &number);

          if (F_status_is_error(status)) {
            status = F_status_set_fine(status);

            if (status == F_exist_not) {
              controller_rule_setting_read_print_error_with_range(global.main->error, " has an invalid group", cache->content_actions.array[i].array[j], ", because no group was found by that name", i, line_item, global.thread, cache);
            }
            else if (status == F_number_too_large) {
              controller_rule_setting_read_print_error_with_range(global.main->error, " has an invalid group", cache->content_actions.array[i].array[j], ", because the given ID is too large", i, line_item, global.thread, cache);
            }
            else if (status == F_number) {
              controller_rule_setting_read_print_error_with_range(global.main->error, " has an invalid group", cache->content_actions.array[i].array[j], ", because the given ID is not a valid supported number", i, line_item, global.thread, cache);
            }
            else {

              // get the current line number within the settings item.
              cache->action.line_item = line_item;
              f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

              cache->action.line_action = ++cache->action.line_item;

              controller_rule_print_error(global.thread, global.main->error, cache->action, status, "f_account_group_id_by_name", F_true, F_false);

              controller_rule_item_print_error(global.thread, global.main->error, cache->action, F_false, F_status_set_fine(status));
            }

            if (F_status_is_error_not(status_return)) {
              status_return = F_status_set_error(status);
            }
          }
          else {
            if (rule->has & controller_rule_has_group_d) {
              rule->groups.array[rule->groups.used++] = number;
            }
            else {
              rule->group = number;
              rule->has |= controller_rule_has_group_d;
            }
          }
        } // for

        controller_rule_setting_read_print_values(global, controller_group_s, i, cache);

        continue;
      }

      if (type == controller_rule_setting_type_environment_e) {
        setting_values = &rule->environment;

        for (j = 0; j < cache->content_actions.array[i].used; ++j) {

          status = f_string_dynamics_increase(controller_common_allocation_small_d, setting_values);

          if (F_status_is_error(status)) {
            controller_rule_print_error(global.thread, global.main->error, cache->action, F_status_set_fine(status), "f_string_dynamics_increase", F_true, F_false);

            if (F_status_set_fine(status) == F_memory_not) {
              status_return = status;
              break;
            }

            if (F_status_is_error_not(status_return)) {
              status_return = status;
            }

            // Get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

            cache->action.line_action = ++cache->action.line_item;

            controller_rule_item_print_error(global.thread, global.main->error, cache->action, F_false, F_status_set_fine(status));

            continue;
          }

          setting_values->array[setting_values->used].used = 0;

          status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[j], &setting_values->array[setting_values->used]);

          if (F_status_is_error(status)) {
            controller_rule_print_error(global.thread, global.main->error, cache->action, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, F_false);
          }
          else {
            status = f_string_dynamic_terminate_after(&setting_values->array[setting_values->used]);

            if (F_status_is_error(status)) {
              controller_rule_print_error(global.thread, global.main->error, cache->action, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true, F_false);
            }
          }

          if (F_status_is_error(status)) {
            setting_values->array[setting_values->used].used = 0;

            if (F_status_set_fine(status) == F_memory_not) {
              status_return = status;
              break;
            }

            if (F_status_is_error_not(status_return)) {
              status_return = status;
            }

            // Get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

            cache->action.line_action = ++cache->action.line_item;

            controller_rule_item_print_error(global.thread, global.main->error, cache->action, F_false, F_status_set_fine(status));

            continue;
          }

          status = controller_validate_environment_name(setting_values->array[setting_values->used]);

          if (status == F_false || F_status_set_fine(status) == F_complete_not_utf) {

            // Get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

            cache->action.line_action = ++cache->action.line_item;

            if (status == F_false) {
              if (global.main->error.verbosity != f_console_verbosity_quiet_e) {
                controller_lock_print(global.main->error.to, global.thread);

                fl_print_format("%c%[%SRule setting has an invalid environment variable name '%]", global.main->error.to.stream, f_string_eol_s[0], global.main->error.context, global.main->error.prefix, global.main->error.context);
                fl_print_format("%[%Q%]", global.main->error.to.stream, global.main->error.notable, setting_values->array[setting_values->used], global.main->error.notable);
                fl_print_format("%['.%]%c", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s[0]);

                controller_rule_print_error_cache(global.main->error, cache->action, F_false);

                controller_unlock_print_flush(global.main->error.to, global.thread);
              }

              if (F_status_is_error_not(status_return)) {
                status_return = F_status_set_error(F_valid_not);
              }
            }
            else {

              // This function should only return F_complete_not_utf on error.
              controller_rule_print_error(global.thread, global.main->error, cache->action, F_complete_not_utf, "controller_validate_environment_name", F_true, F_false);

              if (F_status_is_error_not(status_return)) {
                status_return = status;
              }
            }

            setting_values->array[setting_values->used].used = 0;

            controller_rule_item_print_error(global.thread, global.main->error, cache->action, F_false, F_status_set_fine(status));

            continue;
          }

          ++setting_values->used;
        } // for

        rule->has |= controller_rule_has_environment_d;

        if (cache->content_actions.array[i].used) {
          controller_rule_setting_read_print_values(global, controller_environment_s, i, cache);
        }
        else {
          if (global.main->error.verbosity == f_console_verbosity_debug_e || (global.main->error.verbosity == f_console_verbosity_verbose_e && global.main->parameters[controller_parameter_simulate_e].result == f_console_result_found_e)) {
            controller_lock_print(global.main->output.to, global.thread);

            fl_print_format("%cProcessing rule item action '%[%s%]' setting value to an empty set.%c", global.main->output.to.stream, f_string_eol_s[0], global.main->context.set.title, controller_environment_s, global.main->context.set.title, f_string_eol_s[0]);

            controller_unlock_print_flush(global.main->output.to, global.thread);
          }
        }

        continue;
      }

      // The "on" Rule Setting.
      if (cache->content_actions.array[i].used != 4) {
        controller_rule_setting_read_print_error(global.main->error, "requires exactly four Content", i, line_item, global.thread, cache);

        if (F_status_is_error_not(status_return)) {
          status_return = F_status_set_error(F_valid_not);
        }

        continue;
      }

      if (fl_string_dynamic_partial_compare_string(controller_freeze_s, cache->buffer_item, controller_freeze_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
        action = controller_rule_action_type_freeze_e;
      }
      else if (fl_string_dynamic_partial_compare_string(controller_kill_s, cache->buffer_item, controller_kill_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
        action = controller_rule_action_type_kill_e;
      }
      else if (fl_string_dynamic_partial_compare_string(controller_pause_s, cache->buffer_item, controller_pause_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
        action = controller_rule_action_type_pause_e;
      }
      else if (fl_string_dynamic_partial_compare_string(controller_reload_s, cache->buffer_item, controller_reload_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
        action = controller_rule_action_type_reload_e;
      }
      else if (fl_string_dynamic_partial_compare_string(controller_restart_s, cache->buffer_item, controller_restart_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
        action = controller_rule_action_type_restart_e;
      }
      else if (fl_string_dynamic_partial_compare_string(controller_resume_s, cache->buffer_item, controller_resume_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
        action = controller_rule_action_type_resume_e;
      }
      else if (fl_string_dynamic_partial_compare_string(controller_start_s, cache->buffer_item, controller_start_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
        action = controller_rule_action_type_start_e;
      }
      else if (fl_string_dynamic_partial_compare_string(controller_stop_s, cache->buffer_item, controller_stop_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
        action = controller_rule_action_type_stop_e;
      }
      else if (fl_string_dynamic_partial_compare_string(controller_thaw_s, cache->buffer_item, controller_thaw_s_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
        action = controller_rule_action_type_thaw_e;
      }
      else {
        if (global.main->error.verbosity != f_console_verbosity_quiet_e) {

          // Get the current line number within the settings item.
          cache->action.line_item = line_item;
          f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

          cache->action.line_action = ++cache->action.line_item;

          f_thread_mutex_lock(&global.thread->lock.print);

          controller_lock_print(global.main->error.to, global.thread);

          fl_print_format("%c%[%SRule setting's second value has '%]", global.main->error.to.stream, f_string_eol_s[0], global.main->error.context, global.main->error.prefix, global.main->error.context);
          fl_print_format("%[%/Q%]", global.main->error.to.stream, global.main->error.notable, cache->buffer_item, cache->content_actions.array[i].array[1], global.main->error.notable);
          fl_print_format("%[' but only supports %s, %s, %s, %s, %s", global.main->error.to.stream, global.main->error.context, controller_freeze_s, controller_kill_s, controller_pause_s, controller_reload_s, controller_restart_s);
          fl_print_format("%s, %s, %s, and %s.%]%c", global.main->error.to.stream, controller_resume_s, controller_start_s, controller_stop_s, controller_thaw_s, global.main->error.context, f_string_eol_s[0]);

          controller_rule_print_error_cache(global.main->error, cache->action, F_false);

          controller_unlock_print_flush(global.main->error.to, global.thread);
        }

        if (F_status_is_error_not(status_return)) {
          status_return = F_status_set_error(F_valid_not);
        }

        continue;
      }

      for (j = 0; j < rule->ons.used; ++j) {
        if (rule->ons.array[j].action == action) break;
      } // for

      if (j == rule->ons.used) {
        status = controller_rule_ons_increase(&rule->ons);
      }

      if (F_status_is_error(status)) {
        controller_rule_print_error(global.thread, global.main->error, cache->action, F_status_set_fine(status), "controller_rule_ons_increase", F_true, F_false);
      }
      else {
        if (fl_string_dynamic_partial_compare_string(controller_need_s, cache->buffer_item, controller_need_s_length, cache->content_actions.array[i].array[1]) == F_equal_to) {
          setting_values = &rule->ons.array[j].need;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_want_s, cache->buffer_item, controller_want_s_length, cache->content_actions.array[i].array[1]) == F_equal_to) {
          setting_values = &rule->ons.array[j].want;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_wish_s, cache->buffer_item, controller_wish_s_length, cache->content_actions.array[i].array[1]) == F_equal_to) {
          setting_values = &rule->ons.array[j].wish;
        }
        else {
          if (global.main->error.verbosity != f_console_verbosity_quiet_e) {

            // Get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

            cache->action.line_action = ++cache->action.line_item;

            controller_lock_print(global.main->error.to, global.thread);

            fl_print_format("%c%[%SRule setting's second value has '%]", global.main->error.to.stream, f_string_eol_s[0], global.main->error.context, global.main->error.prefix, global.main->error.context);
            fl_print_format("%[%/Q%]", global.main->error.to.stream, global.main->error.notable, cache->buffer_item, cache->content_actions.array[i].array[1], global.main->error.notable);
            fl_print_format("%[' but only supports %s, %s, and %s.%]%c", global.main->error.to.stream, global.main->error.context, controller_need_s, controller_want_s, controller_wish_s, global.main->error.context, f_string_eol_s[0]);

            controller_rule_print_error_cache(global.main->error, cache->action, F_false);

            controller_unlock_print_flush(global.main->error.to, global.thread);
          }

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        status = f_string_dynamics_increase_by(controller_common_allocation_small_d, setting_values);

        if (F_status_is_error(status)) {
          controller_rule_print_error(global.thread, global.main->error, cache->action, F_status_set_fine(status), "f_string_dynamics_increase_by", F_true, F_false);
        }
      }

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_memory_not) {
          status_return = status;
          break;
        }

        if (F_status_is_error_not(status_return)) {
          status_return = status;
        }

        // Get the current line number within the settings item.
        cache->action.line_item = line_item;
        f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

        cache->action.line_action = ++cache->action.line_item;

        controller_rule_item_print_error(global.thread, global.main->error, cache->action, F_false, F_status_set_fine(status));

        continue;
      }

      status = controller_rule_id_construct(global, cache->buffer_item, cache->content_actions.array[i].array[2], cache->content_actions.array[i].array[3], &setting_values->array[setting_values->used]);

      if (F_status_is_error(status)) {
        setting_values->array[setting_values->used].used = 0;

        if (F_status_set_fine(status) == F_memory_not) {
          status_return = status;
          break;
        }

        if (F_status_is_error_not(status_return)) {
          status_return = status;
        }

        // Get the current line number within the settings item.
        cache->action.line_item = line_item;
        f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

        cache->action.line_action = ++cache->action.line_item;

        controller_rule_item_print_error(global.thread, global.main->error, cache->action, F_false, F_status_set_fine(status));

        continue;
      }

      cache->buffer_path.used = 0;

      status = f_file_name_base(setting_values->array[setting_values->used].string, setting_values->array[setting_values->used + 1].used, &cache->buffer_path);

      if (F_status_is_error(status)) {
        setting_values->array[setting_values->used].used = 0;

        controller_rule_print_error(global.thread, global.main->error, cache->action, F_status_set_fine(status), "f_file_name_base", F_true, F_false);

        if (F_status_set_fine(status) == F_memory_not) {
          status_return = status;
          break;
        }

        if (F_status_is_error_not(status_return)) {
          status_return = status;
        }

        continue;
      }

      if (fl_string_dynamic_partial_compare_string(cache->buffer_item.string, cache->buffer_path, cache->buffer_item.used, cache->content_actions.array[i].array[1]) == F_equal_to_not) {

        if (global.main->error.verbosity != f_console_verbosity_quiet_e) {
          controller_lock_print(global.main->error.to, global.thread);

          fl_print_format("%c%[%SThe rule item action third parameter '%]", global.main->error.to.stream, f_string_eol_s[0], global.main->error.context, global.main->error.prefix, global.main->error.context);
          fl_print_format("%[%/Q%]", global.main->error.to.stream, global.main->error.notable, cache->buffer_item, cache->content_actions.array[i].array[2], global.main->error.notable);
          fl_print_format("%[' must be a base path name, such as %un '.%]", global.main->error.to.stream, global.main->error.context, cache->buffer_path.used, global.main->error.context);
          fl_print_format("%[%Q%]", global.main->error.to.stream, cache->buffer_path, global.main->error.notable);
          fl_print_format("%['.%]%c", global.main->error.to.stream, global.main->error.context, global.main->error.context, f_string_eol_s[0]);

          controller_unlock_print_flush(global.main->error.to, global.thread);
        }

        setting_values->array[setting_values->used].used = 0;

        continue;
      }

      rule->ons.array[j].action = action;

      ++setting_values->used;

      if (j == rule->ons.used) {
        ++rule->ons.used;
      }

      if (global.main->error.verbosity == f_console_verbosity_debug_e || (global.main->error.verbosity == f_console_verbosity_verbose_e && global.main->parameters[controller_parameter_simulate_e].result == f_console_result_found_e)) {
        controller_lock_print(global.main->output.to, global.thread);

        fl_print_format("%cProcessing rule item action '%[%S%]', adding ", global.main->output.to.stream, f_string_eol_s[0], global.main->context.set.title, controller_on_s, global.main->context.set.title);
        fl_print_format("'%[%/Q%]' of ", global.main->output.to.stream, global.main->context.set.notable, cache->buffer_item, cache->content_actions.array[i].array[1], global.main->context.set.notable);
        fl_print_format("'%[%/Q%]/", global.main->output.to.stream, global.main->context.set.important, cache->buffer_item, cache->content_actions.array[i].array[2], global.main->context.set.important);
        fl_print_format("%[%/Q%]'.%c", global.main->output.to.stream, global.main->context.set.important, cache->buffer_item, cache->content_actions.array[i].array[3], global.main->context.set.important, f_string_eol_s[0]);

        controller_unlock_print_flush(global.main->output.to, global.thread);
      }
    } // for

    // Restore the current name item and line number, which there should already be enough allocated space for.
    memcpy(cache->action.name_item.string, name_item, length_name_item);

    cache->action.name_item.string[length_name_item] = 0;
    cache->action.name_item.used = length_name_item;

    cache->action.line_item = line_item;

    return status_return;
  }
#endif // _di_controller_rule_setting_read_

#ifndef _di_controller_rule_validate_
  void controller_rule_validate(const controller_global_t global, const controller_rule_t rule, const uint8_t action, const uint8_t options, controller_cache_t * const cache) {

    const controller_main_t *main = global.main;

    switch (action) {
      case controller_rule_action_type_freeze_e:
      case controller_rule_action_type_kill_e:
      case controller_rule_action_type_pause_e:
      case controller_rule_action_type_reload_e:
      case controller_rule_action_type_restart_e:
      case controller_rule_action_type_resume_e:
      case controller_rule_action_type_start_e:
      case controller_rule_action_type_stop_e:
      case controller_rule_action_type_thaw_e:
        break;

      default:
        if (main->error.verbosity != f_console_verbosity_quiet_e) {
          controller_lock_print(main->error.to, global.thread);

          fl_print_format("%c%[%SUnsupported action type '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix ? main->error.prefix : f_string_empty_s, main->error.context);
          fl_print_format("%[%q%]", main->error.to.stream, main->error.notable, controller_rule_action_type_name(action), main->error.notable);
          fl_print_format("%[' while attempting to validate rule execution.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

          controller_rule_print_error_cache(main->error, cache->action, F_true);

          controller_unlock_print_flush(main->error.to, global.thread);
        }

        return;
    }

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    // find at least one of the requested action.
    {
      bool missing = F_true;

      for (; i < rule.items.used; ++i) {

        for (j = 0; j < rule.items.array[i].actions.used; ++j) {

          if (!action || rule.items.array[i].actions.array[j].type == action) {
            missing = F_false;
            break;
          }
        } // for
      } // for

      if (missing) {
        controller_lock_print(main->output.to, global.thread);

        if (rule.items.used) {
          fl_print_format("%cRule '", main->output.to.stream, f_string_eol_s[0]);
          fl_print_format("%[%Q%]' has no '", main->output.to.stream, main->context.set.title, rule.name, main->context.set.title);
          fl_print_format("%[%q%]' action to execute and would '", main->output.to.stream, main->context.set.title, controller_rule_action_type_name(action), main->context.set.title);
          fl_print_format("%[%s%]' because it is '", main->output.to.stream, main->context.set.important, options & controller_process_option_require_d ? controller_fail_s : controller_succeed_s, main->context.set.important);
          fl_print_format("%[%s%]'.%c", main->output.to.stream, main->context.set.important, options & controller_process_option_require_d ? controller_required_s : controller_optional_s, main->context.set.important, f_string_eol_s[0]);
        }
        else {
          fl_print_format("%cRule '", main->output.to.stream, f_string_eol_s[0]);
          fl_print_format("%[%Q%]' has no known '", main->output.to.stream, main->context.set.title, rule.name, main->context.set.title);
          fl_print_format("%[%s %s%]' (such as ", main->output.to.stream, main->context.set.title, controller_rule_s, controller_type_s, main->context.set.title);
          fl_print_format("'%[%s%]', ", main->output.to.stream, main->context.set.title, controller_command_s, main->context.set.title);
          fl_print_format("'%[%s%]', ", main->output.to.stream, main->context.set.title, controller_service_s, main->context.set.title);
          fl_print_format("'%[%s%]', or ", main->output.to.stream, main->context.set.title, controller_script_s, main->context.set.title);
          fl_print_format("'%[%s%]'", main->output.to.stream, main->context.set.title, controller_utility_s, main->context.set.title);
          fl_print_format(") and would '%[%s%]' because it is '", main->output.to.stream, main->context.set.important, options & controller_process_option_require_d ? controller_fail_s : controller_succeed_s, main->context.set.important);
          fl_print_format("%[%s%]'.%c", main->output.to.stream, main->context.set.important, options & controller_process_option_require_d ? controller_required_s : controller_optional_s, main->context.set.important, f_string_eol_s[0]);
        }

        controller_unlock_print_flush(main->output.to, global.thread);
      }
    }

    controller_lock_print(main->output.to, global.thread);

    fl_print_format("%cRule %[%Q%] {%c", main->output.to.stream, f_string_eol_s[0], main->context.set.title, rule.alias, main->context.set.title, f_string_eol_s[0]);

    // name.
    fl_print_format("  %[%s%] %Q%c", main->output.to.stream, main->context.set.important, controller_name_s, main->context.set.important, rule.name, f_string_eol_s[0]);

    // capability.
    fl_print_format("  %[%s%] ", main->output.to.stream, main->context.set.important, controller_capability_s, main->context.set.important);

    if (f_capability_supported()) {
      if (rule.capability) {
        cache->action.generic.used = 0;

        if (F_status_is_error_not(f_capability_to_text(rule.capability, &cache->action.generic))) {
          f_print_dynamic_safely(cache->action.generic, main->output.to.stream);
        }
      }

      f_print_terminated(f_string_eol_s, main->output.to.stream);
    }
    else {
      fl_print_format("%[(unsupported)%]%c", main->output.to.stream, main->context.set.warning, main->context.set.warning, f_string_eol_s[0]);
    }

    // control group.
    fl_print_format("  %[%s%]", main->output.to.stream, main->context.set.important, controller_cgroup_s, main->context.set.important);

    if (rule.has & controller_rule_has_cgroup_d) {
      fl_print_format(" %s", main->output.to.stream, rule.cgroup.as_new ? controller_new_s : controller_existing_s);

      for (i = 0; i < rule.cgroup.groups.used; ++i) {

        if (rule.cgroup.groups.array[i].used) {
          fl_print_format(" %Q", main->output.to.stream, rule.cgroup.groups.array[i]);
        }
      } // for
    }

    f_print_terminated(f_string_eol_s, main->output.to.stream);

    // how.
    fl_print_format("  %[%s%] %s%c", main->output.to.stream, main->context.set.important, controller_how_s, main->context.set.important, options & controller_process_option_asynchronous_d ? controller_asynchronous_s : controller_synchronous_s, f_string_eol_s[0]);

    // nice.
    fl_print_format("  %[%s%]", main->output.to.stream, main->context.set.important, controller_nice_s, main->context.set.important);

    if (rule.has & controller_rule_has_nice_d) {
      fl_print_format(" %i", main->output.to.stream, rule.nice);
    }

    f_print_terminated(f_string_eol_s, main->output.to.stream);

    // scheduler.
    fl_print_format("  %[%s%]", main->output.to.stream, main->context.set.important, controller_scheduler_s, main->context.set.important);

    if (rule.has & controller_rule_has_scheduler_d) {
      f_string_t policy = "";

      if (rule.scheduler.policy == SCHED_BATCH) {
        policy = controller_batch_s;
      }
      else if (rule.scheduler.policy == SCHED_DEADLINE) {
        policy = controller_deadline_s;
      }
      else if (rule.scheduler.policy == SCHED_FIFO) {
        policy = controller_fifo_s;
      }
      else if (rule.scheduler.policy == SCHED_IDLE) {
        policy = controller_idle_s;
      }
      else if (rule.scheduler.policy == SCHED_OTHER) {
        policy = controller_other_s;
      }
      else if (rule.scheduler.policy == SCHED_RR) {
        policy = controller_round_robin_s;
      }

      fl_print_format(" %s %i", main->output.to.stream, policy, rule.scheduler.priority);
    }

    f_print_terminated(f_string_eol_s, main->output.to.stream);

    // script.
    fl_print_format("  %[%s%] %Q%c", main->output.to.stream, main->context.set.important, controller_script_s, main->context.set.important, rule.script, f_string_eol_s[0]);

    // user.
    fl_print_format("  %[%s%]", main->output.to.stream, main->context.set.important, controller_user_s, main->context.set.important);

    if (rule.has & controller_rule_has_user_d) {
      fl_print_format(" %i", main->output.to.stream, rule.user);
    }

    f_print_terminated(f_string_eol_s, main->output.to.stream);

    // wait.
    fl_print_format("  %[%s%] %s%c", main->output.to.stream, main->context.set.important, controller_wait_s, main->context.set.important, options & controller_process_option_wait_d ? controller_yes_s : controller_no_s, f_string_eol_s[0]);

    // affinity.
    fl_print_format("  %[%s%] {%c", main->output.to.stream, main->context.set.important, controller_affinity_s, main->context.set.important, f_string_eol_s[0]);

    for (i = 0; i < rule.affinity.used; ++i) {
      fl_print_format("    %i%c", main->output.to.stream, rule.affinity.array[i], f_string_eol_s[0]);
    } // for

    // define.
    fl_print_format("  }%c  %[%s%] {%c", main->output.to.stream, f_string_eol_s[0], main->context.set.important, controller_define_s, main->context.set.important, f_string_eol_s[0]);

    for (i = 0; i < rule.define.used; ++i) {

      if (rule.define.array[i].name.used && rule.define.array[i].value.used) {
        fl_print_format("    %Q %[=%] %Q%c", main->output.to.stream, rule.define.array[i].name, main->context.set.important, main->context.set.important, rule.define.array[i].value, f_string_eol_s[0]);
      }
    } // for

    // environment.
    fl_print_format("  }%c  %[%s%] {%c", main->output.to.stream, f_string_eol_s[0], main->context.set.important, controller_environment_s, main->context.set.important, f_string_eol_s[0]);

    for (i = 0; i < rule.environment.used; ++i) {

      if (rule.environment.array[i].used) {
        fl_print_format("    %Q%c", main->output.to.stream, rule.environment.array[i], f_string_eol_s[0]);
      }
    } // for

    fl_print_format("  }%c  %[%s%] {%c", main->output.to.stream, f_string_eol_s[0], main->context.set.important, controller_parameter_s, main->context.set.important, f_string_eol_s[0]);

    // parameter.
    for (i = 0; i < rule.parameter.used; ++i) {

      if (rule.parameter.array[i].name.used && rule.parameter.array[i].value.used) {
        fl_print_format("    %Q %[=%] %Q%c", main->output.to.stream, rule.parameter.array[i].name, main->context.set.important, main->context.set.important, rule.parameter.array[i].value, f_string_eol_s[0]);
      }
    } // for

    // group.
    fl_print_format("  }%c  %[%s%] {%c", main->output.to.stream, f_string_eol_s[0], main->context.set.important, controller_group_s, main->context.set.important, f_string_eol_s[0]);

    if (rule.has & controller_rule_has_group_d) {
      fl_print_format("    %i%c", main->output.to.stream, rule.group, f_string_eol_s[0]);

      for (i = 0; i < rule.groups.used; ++i) {
        fl_print_format("    %i%c", main->output.to.stream, rule.groups.array[i], f_string_eol_s[0]);
      } // for
    }

    // limit.
    fl_print_format("  }%c  %[%s%] {%c", main->output.to.stream, f_string_eol_s[0], main->context.set.important, controller_limit_s, main->context.set.important, f_string_eol_s[0]);

    for (i = 0; i < rule.limits.used; ++i) {
      fl_print_format("    %Q %[=%] %un %un%c", main->output.to.stream, controller_rule_setting_limit_type_name(rule.limits.array[i].type), main->context.set.important, main->context.set.important, rule.limits.array[i].value.rlim_cur, rule.limits.array[i].value.rlim_max, f_string_eol_s[0]);
    } // for

    // on.
    fl_print_format("  }%c  %[%s%] {%c", main->output.to.stream, f_string_eol_s[0], main->context.set.important, controller_on_s, main->context.set.important, f_string_eol_s[0]);

    for (i = 0; i < rule.ons.used; ++i) {

      fl_print_format("    %[%s%] {%c", main->output.to.stream, main->context.set.important, controller_action_s, main->context.set.important, f_string_eol_s[0]);

      {
        f_string_t action = "";

        if (rule.ons.array[i].action == controller_rule_action_type_freeze_e) {
          action = controller_freeze_s;
        }
        else if (rule.ons.array[i].action == controller_rule_action_type_kill_e) {
          action = controller_kill_s;
        }
        else if (rule.ons.array[i].action == controller_rule_action_type_pause_e) {
          action = controller_pause_s;
        }
        else if (rule.ons.array[i].action == controller_rule_action_type_reload_e) {
          action = controller_reload_s;
        }
        else if (rule.ons.array[i].action == controller_rule_action_type_restart_e) {
          action = controller_restart_s;
        }
        else if (rule.ons.array[i].action == controller_rule_action_type_resume_e) {
          action = controller_resume_s;
        }
        else if (rule.ons.array[i].action == controller_rule_action_type_start_e) {
          action = controller_start_s;
        }
        else if (rule.ons.array[i].action == controller_rule_action_type_stop_e) {
          action = controller_stop_s;
        }
        else if (rule.ons.array[i].action == controller_rule_action_type_thaw_e) {
          action = controller_thaw_s;
        }

        fl_print_format("      %[%s%] %s%c", main->output.to.stream, main->context.set.important, controller_type_s, main->context.set.important, action, f_string_eol_s[0]);
      }

      fl_print_format("      %[%s%] {%c", main->output.to.stream, main->context.set.important, controller_need_s, main->context.set.important, f_string_eol_s[0]);

      for (j = 0; j < rule.ons.array[i].need.used; ++j) {

        if (rule.ons.array[i].need.array[j].used) {
          fl_print_format("        %Q%c", main->output.to.stream, rule.ons.array[i].need.array[j], f_string_eol_s[0]);
        }
      } // for

      fl_print_format("      }%c      %[%s%] {%c", main->output.to.stream, f_string_eol_s[0], main->context.set.important, controller_want_s, main->context.set.important, f_string_eol_s[0]);

      for (j = 0; j < rule.ons.array[i].want.used; ++j) {

        if (rule.ons.array[i].want.array[j].used) {
          fl_print_format("        %Q%c", main->output.to.stream, rule.ons.array[i].want.array[j], f_string_eol_s[0]);
        }
      } // for

      fl_print_format("      }%c      %[%s%] {%c", main->output.to.stream, f_string_eol_s[0], main->context.set.important, controller_wish_s, main->context.set.important, f_string_eol_s[0]);

      for (j = 0; j < rule.ons.array[i].wish.used; ++j) {

        if (rule.ons.array[i].wish.array[j].used) {
          fl_print_format("        %Q%c", main->output.to.stream, rule.ons.array[i].wish.array[j], f_string_eol_s[0]);
        }
      } // for

      fl_print_format("      }%c    }%c", main->output.to.stream, f_string_eol_s[0], f_string_eol_s[0]);
    } // for

    fl_print_format("  }%c", main->output.to.stream, f_string_eol_s[0]);

    // items.
    if (rule.items.used) {
      controller_rule_action_t *action = 0;
      controller_rule_item_t *item = 0;
      controller_rule_rerun_item_t *rerun_item = 0;
      f_string_dynamic_t *parameter = 0;

      f_array_length_t j = 0;
      f_array_length_t k = 0;

      for (i = 0; i < rule.items.used; ++i) {

        item = &rule.items.array[i];

        fl_print_format("  %[%s%] {%c", main->output.to.stream, main->context.set.important, controller_item_s, main->context.set.important, f_string_eol_s[0]);

        // type.
        fl_print_format("    %[%s%] %Q%c", main->output.to.stream, main->context.set.important, controller_type_s, main->context.set.important, controller_rule_item_type_name(item->type), f_string_eol_s[0]);

        // pid_file.
        fl_print_format("    %[%s%]", main->output.to.stream, main->context.set.important, controller_pid_file_s, main->context.set.important);
        if (item->pid_file.used) {
          fl_print_format(" %Q", main->output.to.stream, item->pid_file);
        }
        f_print_terminated(f_string_eol_s, main->output.to.stream);

        // with.
        fl_print_format("    %[%s%]", main->output.to.stream, main->context.set.important, controller_with_s, main->context.set.important);
        if (item->with & controller_with_full_path_d) {
          fl_print_format(" %s", main->output.to.stream, controller_full_path_s);
        }
        if (item->with & controller_with_session_new_d) {
          fl_print_format(" %s", main->output.to.stream, controller_session_new_s);
        }
        if (item->with & controller_with_session_same_d) {
          fl_print_format(" %s", main->output.to.stream, controller_session_same_s);
        }
        f_print_terminated(f_string_eol_s, main->output.to.stream);

        // actions.
        for (j = 0; j < item->actions.used; ++j) {

          action = &item->actions.array[j];

          fl_print_format("    %[%s%] {%c", main->output.to.stream, main->context.set.important, controller_action_s, main->context.set.important, f_string_eol_s[0]);
          fl_print_format("      %[%s%] %q%c", main->output.to.stream, main->context.set.important, controller_type_s, main->context.set.important, controller_rule_action_type_name(action->type), f_string_eol_s[0]);

          if (item->type == controller_rule_item_type_script_e || item->type == controller_rule_item_type_utility_e) {
            fl_print_format("      %[%s%] {%c", main->output.to.stream, main->context.set.important, controller_parameter_s, main->context.set.important, f_string_eol_s[0]);

            parameter = &action->parameters.array[0];

            if (parameter->used) {
              f_print_terminated("        ", main->output.to.stream);

              for (k = 0; k < parameter->used; ++k) {

                if (parameter->string[k] == f_fss_eol_s[0]) {
                  if (k + 1 < parameter->used) {
                    f_print_terminated(f_string_eol_s, main->output.to.stream);
                    f_print_terminated("        ", main->output.to.stream);
                  }
                }
                else {
                  // @fixme change this to handle UTF-8 characters (cannot use f_print_character_safely() as it is not UTF-8 safe as-is).
                  f_print_character_safely(parameter->string[k], main->output.to.stream);
                }
              } // for

              f_print_terminated(f_string_eol_s, main->output.to.stream);
            }

            fl_print_format("      }%c", main->output.to.stream, f_string_eol_s[0]);
          }
          else {
            for (k = 0; k < action->parameters.used; ++k) {
              fl_print_format("      %[%s%] %Q%c", main->output.to.stream, main->context.set.important, controller_parameter_s, main->context.set.important, action->parameters.array[k], f_string_eol_s[0]);
            } // for
          }

          fl_print_format("    }%c", main->output.to.stream, f_string_eol_s[0]);
        } // for

        // rerun.
        fl_print_format("    %[%s%] {%c", main->output.to.stream, main->context.set.important, controller_rerun_s, main->context.set.important, f_string_eol_s[0]);
        for (j = 0; j < controller_rule_action_type_execute__enum_size_e; ++j) {

          for (k = 0; k < 2; ++k) {
            if (!k && (item->reruns[j].is & controller_rule_rerun_is_failure_d)) {
              rerun_item = &item->reruns[j].failure;
            }
            else if (k && (item->reruns[j].is & controller_rule_rerun_is_success_d)) {
              rerun_item = &item->reruns[j].success;
            }
            else {
              rerun_item = 0;
              continue;
            }

            fl_print_format("      %[", main->output.to.stream, main->context.set.important);
            switch (j) {
              case controller_rule_action_type_execute_freeze_e:
                f_print_terminated(controller_freeze_s, main->output.to.stream);
                break;

              case controller_rule_action_type_execute_kill_e:
                f_print_terminated(controller_kill_s, main->output.to.stream);
                break;

              case controller_rule_action_type_execute_pause_e:
                f_print_terminated(controller_pause_s, main->output.to.stream);
                break;

              case controller_rule_action_type_execute_reload_e:
                f_print_terminated(controller_reload_s, main->output.to.stream);
                break;

              case controller_rule_action_type_execute_restart_e:
                f_print_terminated(controller_restart_s, main->output.to.stream);
                break;

              case controller_rule_action_type_execute_resume_e:
                f_print_terminated(controller_resume_s, main->output.to.stream);
                break;

              case controller_rule_action_type_execute_start_e:
                f_print_terminated(controller_start_s, main->output.to.stream);
                break;

              case controller_rule_action_type_execute_stop_e:
                f_print_terminated(controller_stop_s, main->output.to.stream);
                break;

              case controller_rule_action_type_execute_thaw_e:
                f_print_terminated(controller_thaw_s, main->output.to.stream);
                break;

              default:
                break;
            }

            fl_print_format("%] %s", main->output.to.stream, main->context.set.important, k ? controller_success_s : controller_failure_s);
            fl_print_format(" %s %ul %s %ul", main->output.to.stream, controller_delay_s, rerun_item->delay, controller_max_s, rerun_item->max);

            if (!k && (item->reruns[j].is & controller_rule_rerun_is_failure_reset_d) || k && (item->reruns[j].is & controller_rule_rerun_is_success_reset_d)) {
              fl_print_format(" %s", main->output.to.stream, controller_reset_s);
            }

            f_print_terminated(f_string_eol_s, main->output.to.stream);
          } // for
        } // for
        fl_print_format("    }%c", main->output.to.stream, f_string_eol_s[0]);

        fl_print_format("  }%c", main->output.to.stream, f_string_eol_s[0]);
      } // for
    }

    fl_print_format("}%c", main->output.to.stream, f_string_eol_s[0]);

    controller_unlock_print_flush(main->output.to, global.thread);
  }
#endif // _di_controller_rule_validate_

#ifndef _di_controller_rule_wait_all_
  f_status_t controller_rule_wait_all(const controller_global_t global, const bool is_normal, const bool required, controller_process_t * const caller) {

    f_status_t status_lock = F_none;

    if (caller) {
      status_lock = controller_lock_read_process(caller, global.thread, &global.thread->lock.process);
    }
    else {
      status_lock = controller_lock_read(is_normal, global.thread, &global.thread->lock.process);
    }

    if (F_status_is_error(status_lock)) {
      controller_lock_print_error_critical(global.main->error, F_status_set_fine(status_lock), F_true, global.thread);

      return status_lock;
    }

    if (!global.thread->processs.used) {
      f_thread_unlock(&global.thread->lock.process);

      return F_data_not;
    }

    f_status_t status = F_none;

    bool required_not_run = F_false;
    bool skip = F_false;

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    // build a list of what to wait for so that anything new after this point will not be waited for.
    const f_array_length_t process_total = global.thread->processs.used;
    controller_process_t *process_list[process_total];

    for (; i < process_total; ++i) {
      process_list[i] = global.thread->processs.array[i];
    } // for

    f_thread_unlock(&global.thread->lock.process);

    for (i = 0; i < process_total; ++i) {

      if (caller) {
        if (!controller_thread_is_enabled_process(caller, global.thread)) break;
      }
      else {
        if (!controller_thread_is_enabled(is_normal, global.thread)) break;
      }

      // re-establish global process read lock to wait for or protect from the cleanup thread while checking the read process.
      if (caller) {
        status_lock = controller_lock_read_process(caller, global.thread, &global.thread->lock.process);
      }
      else {
        status_lock = controller_lock_read(is_normal, global.thread, &global.thread->lock.process);
      }

      if (F_status_is_error(status_lock)) break;

      if (!process_list[i]) {
        f_thread_unlock(&global.thread->lock.process);

        continue;
      }

      if (caller) {
        status_lock = controller_lock_read_process(caller, global.thread, &process_list[i]->active);
      }
      else {
        status_lock = controller_lock_read(is_normal, global.thread, &process_list[i]->active);
      }

      if (F_status_is_error(status_lock)) {
        f_thread_unlock(&global.thread->lock.process);

        break;
      }

      // once the active lock is obtained, then the main process read lock can be safely released.
      f_thread_unlock(&global.thread->lock.process);

      if (caller) {
        if (caller) {
          status_lock = controller_lock_read_process(caller, global.thread, &global.thread->lock.rule);
        }
        else {
          status_lock = controller_lock_read(is_normal, global.thread, &global.thread->lock.rule);
        }

        if (F_status_is_error(status_lock)) {
          f_thread_unlock(&process_list[i]->active);

          break;
        }

        if (fl_string_dynamic_compare(caller->rule.alias, process_list[i]->rule.alias) == F_equal_to) {
          f_thread_unlock(&global.thread->lock.rule);
          f_thread_unlock(&process_list[i]->active);

          continue;
        }

        skip = F_false;

        for (j = 0; j < caller->stack.used; ++j) {

          if (caller) {
            if (!controller_thread_is_enabled_process(caller, global.thread)) break;
          }
          else {
            if (!controller_thread_is_enabled(is_normal, global.thread)) break;
          }

          if (global.thread->processs.array[caller->stack.array[j]] && fl_string_dynamic_compare(process_list[i]->rule.alias, global.thread->processs.array[caller->stack.array[j]]->rule.alias) == F_equal_to) {
            skip = F_true;
          }

          if (skip) break;
        } // for

        f_thread_unlock(&global.thread->lock.rule);

        if (skip) {
          f_thread_unlock(&process_list[i]->active);

          continue;
        }
      }

      if (caller) {
        status_lock = controller_lock_read_process(caller, global.thread, &process_list[i]->lock);
      }
      else {
        status_lock = controller_lock_read(is_normal, global.thread, &process_list[i]->lock);
      }

      if (F_status_is_error(status_lock)) {
        f_thread_unlock(&process_list[i]->active);

        break;
      }

      if (required) {
        if (!(process_list[i]->options & controller_process_option_require_d)) {
          f_thread_unlock(&process_list[i]->lock);
          f_thread_unlock(&process_list[i]->active);

          continue;
        }
      }

      if (!process_list[i]->state || process_list[i]->state == controller_process_state_idle_e || process_list[i]->state == controller_process_state_done_e) {

        if (process_list[i]->state == controller_process_state_done_e) {
          f_thread_unlock(&process_list[i]->lock);

          if (caller) {
            status_lock = controller_lock_write_process(process_list[i], global.thread, &process_list[i]->lock);
          }
          else {
            status_lock = controller_lock_write(is_normal, global.thread, &process_list[i]->lock);
          }

          if (F_status_is_error(status_lock)) {
            controller_lock_print_error_critical(global.main->error, F_status_set_fine(status_lock), F_false, global.thread);

            f_thread_unlock(&process_list[i]->active);

            return status_lock;
          }

          if (process_list[i]->state == controller_process_state_done_e) {
            f_thread_unlock(&process_list[i]->active);

            if (f_thread_lock_write_try(&process_list[i]->active) == F_none) {

              controller_thread_join(&process_list[i]->id_thread);

              process_list[i]->state = controller_process_state_idle_e;

              f_thread_unlock(&process_list[i]->active);

              f_thread_mutex_lock(&process_list[i]->wait_lock);
              f_thread_condition_signal_all(&process_list[i]->wait);
              f_thread_mutex_unlock(&process_list[i]->wait_lock);
            }

            if (caller) {
              status_lock = controller_lock_read_process(caller, global.thread, &process_list[i]->active);
            }
            else {
              status_lock = controller_lock_read(is_normal, global.thread, &process_list[i]->active);
            }

            if (F_status_is_error(status_lock)) {
              f_thread_unlock(&process_list[i]->lock);

              break;
            }
          }

          f_thread_unlock(&process_list[i]->lock);

          if (caller) {
            status_lock = controller_lock_read_process(caller, global.thread, &process_list[i]->lock);
          }
          else {
            status_lock = controller_lock_read(is_normal, global.thread, &process_list[i]->lock);
          }

          if (F_status_is_error(status_lock)) break;
        }

        if (process_list[i]->options & controller_process_option_require_d) {
          if (controller_rule_status_is_error(process_list[i]->action, process_list[i]->rule)) {
            status = F_status_set_error(F_require);

            f_thread_unlock(&process_list[i]->lock);
            f_thread_unlock(&process_list[i]->active);

            break;
          }
          else if (controller_rule_status_is_available(process_list[i]->action, process_list[i]->rule)) {
            required_not_run = F_true;
          }
        }

        f_thread_unlock(&process_list[i]->lock);
        f_thread_unlock(&process_list[i]->active);

        if (F_status_set_fine(status) == F_require) break;

        continue;
      }

      if (!controller_rule_status_is_error(process_list[i]->action, process_list[i]->rule) && (process_list[i]->state == controller_process_state_active_e || process_list[i]->state == controller_process_state_busy_e)) {
        f_thread_unlock(&process_list[i]->lock);

        status = controller_process_wait(global, process_list[i]);

        if (F_status_set_fine(status) == F_interrupt) {
          f_thread_unlock(&process_list[i]->active);

          break;
        }

        if (caller) {
          status_lock = controller_lock_read_process(caller, global.thread, &process_list[i]->lock);
        }
        else {
          status_lock = controller_lock_read(is_normal, global.thread, &process_list[i]->lock);
        }

        if (F_status_is_error(status_lock)) {
          f_thread_unlock(&process_list[i]->active);

          break;
        }

        if ((process_list[i]->options & controller_process_option_require_d)) {
          f_thread_unlock(&process_list[i]->lock);

          if (controller_rule_status_is_error(process_list[i]->action, process_list[i]->rule)) {
            status = F_status_set_error(F_require);

            f_thread_unlock(&process_list[i]->active);
            break;
          }
        }
        else {
          f_thread_unlock(&process_list[i]->lock);
        }
      }
      else {
        f_thread_unlock(&process_list[i]->lock);
      }

      f_thread_unlock(&process_list[i]->active);

      if (F_status_set_fine(status) == F_interrupt || F_status_set_fine(status) == F_require) break;
    } // for

    if (F_status_is_error(status_lock)) {
      controller_lock_print_error_critical(global.main->error, F_status_set_fine(status_lock), F_true, global.thread);

      return status_lock;
    }

    if (caller) {
      if (!controller_thread_is_enabled_process(caller, global.thread)) {
        return F_status_set_error(F_interrupt);
      }
    }
    else {
      if (!controller_thread_is_enabled(is_normal, global.thread)) {
        return F_status_set_error(F_interrupt);
      }
    }

    if (F_status_set_fine(status) == F_require) {
      return status;
    }

    if (required_not_run) {
      return F_require;
    }

    return F_none;
  }
#endif // _di_controller_rule_wait_all_

#ifndef _di_controller_rule_wait_all_process_type_
  f_status_t controller_rule_wait_all_process_type(const controller_global_t global, const uint8_t type, const bool required, controller_process_t * const caller) {

    return controller_rule_wait_all(global, type != controller_process_type_exit_e, required, caller);
  }
#endif // _di_controller_rule_wait_all_process_type_

#ifdef __cplusplus
} // extern "C"
#endif
