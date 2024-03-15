#include "../controller.h"
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

#ifndef _di_controller_rule_string_s_
  const f_string_static_t controller_rule_needed_s = macro_f_string_static_t_initialize_1(CONTROLLER_rule_needed_s, 0, CONTROLLER_rule_needed_s_length);
  const f_string_static_t controller_rule_wanted_s = macro_f_string_static_t_initialize_1(CONTROLLER_rule_wanted_s, 0, CONTROLLER_rule_wanted_s_length);
  const f_string_static_t controller_rule_wished_s = macro_f_string_static_t_initialize_1(CONTROLLER_rule_wished_s, 0, CONTROLLER_rule_wished_s_length);
#endif // _di_controller_rule_print_string_s_

#ifndef _di_controller_rule_action_method_name_
  f_string_static_t controller_rule_action_method_name(const uint8_t type) {

    f_string_static_t buffer = f_string_static_t_initialize;

    switch (type) {
      case controller_rule_action_method_extended_e:
        buffer = controller_rule_action_method_string_extended_s;
        break;

      case controller_rule_action_method_extended_list_e:
        buffer = controller_rule_action_method_string_extended_list_s;
        break;
    }

    return buffer;
  }
#endif // _di_controller_rule_action_method_name_

#ifndef _di_controller_rule_find_
  f_status_t controller_rule_find(const f_string_static_t alias, const controller_rules_t rules, f_number_unsigned_t *at) {

    if (!alias.used) return F_okay;
    if (!rules.used) return F_false;

    for (f_number_unsigned_t i = 0; i < rules.used; ++i) {

      if (f_compare_dynamic(alias, rules.array[i].alias) == F_equal_to) {
        if (at) *at = i;

        return F_true;
      }
    } // for

    return F_false;
  }
#endif // _di_controller_rule_find_

#ifndef _di_controller_rule_parameters_read_
  f_status_t controller_rule_parameters_read(const controller_global_t global, const f_string_static_t buffer, f_range_t * const object, f_ranges_t * const content, controller_rule_action_t * const action, f_state_t * const state) {

    f_status_t status = F_okay;

    action->parameters.used = 0;
    action->ikis.used = 0;

    if (object && object->start <= object->stop) {
      if (content) {
        status = f_memory_array_increase_by(content->used + 1, sizeof(f_string_dynamic_t), (void **) &action->parameters.array, &action->parameters.used, &action->parameters.size);
      }
      else {
        status = f_memory_array_increase(controller_common_allocation_small_d, sizeof(f_string_dynamic_t), (void **) &action->parameters.array, &action->parameters.used, &action->parameters.size);
      }

      if (F_status_is_error(status)) {
        controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), content ? "f_memory_array_increase_by" : "f_memory_array_increase", F_true);

        return status;
      }

      if (content) {
        status = f_memory_array_increase_by(content->used + 1, sizeof(f_iki_data_t), (void **) &action->ikis.array, &action->ikis.used, &action->ikis.size);
      }
      else {
        status = f_memory_array_increase(controller_common_allocation_small_d, sizeof(f_iki_data_t), (void **) &action->ikis.array, &action->ikis.used, &action->ikis.size);
      }

      if (F_status_is_error(status)) {
        controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), content ? "f_memory_array_increase_by" : "f_memory_array_increase", F_true);

        return status;
      }

      action->parameters.array[action->parameters.used].used = 0;
      action->ikis.array[action->ikis.used].content.used = 0;
      action->ikis.array[action->ikis.used].delimits.used = 0;
      action->ikis.array[action->ikis.used].variable.used = 0;
      action->ikis.array[action->ikis.used].vocabulary.used = 0;

      status = f_string_dynamic_partial_append_nulless(buffer, *object, &action->parameters.array[0]);

      if (F_status_is_error(status)) {
        controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true);

        return status;
      }

      ++action->parameters.used;
      ++action->ikis.used;
    }

    if (content && content->used) {
      status = f_memory_array_increase_by(content->used, sizeof(f_string_dynamic_t), (void **) &action->parameters.array, &action->parameters.used, &action->parameters.size);

      if (F_status_is_error(status)) {
        controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_memory_array_increase_by", F_true);

        return status;
      }

      status = f_memory_array_increase_by(content->used, sizeof(f_iki_data_t), (void **) &action->ikis.array, &action->ikis.used, &action->ikis.size);

      if (F_status_is_error(status)) {
        controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_memory_array_increase_by", F_true);

        return status;
      }

      f_range_t range = f_range_t_initialize;

      for (f_number_unsigned_t i = 0; i < content->used; ++i) {

        if (content->array[i].start > content->array[i].stop) continue;

        action->parameters.array[action->parameters.used].used = 0;
        action->ikis.array[action->ikis.used].content.used = 0;
        action->ikis.array[action->ikis.used].delimits.used = 0;
        action->ikis.array[action->ikis.used].variable.used = 0;
        action->ikis.array[action->ikis.used].vocabulary.used = 0;

        status = f_string_dynamic_partial_append_nulless(buffer, content->array[i], &action->parameters.array[action->parameters.used]);

        if (F_status_is_error(status)) {
          controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true);

          return status;
        }

        if (action->parameters.array[action->parameters.used].used) {
          range.start = 0;
          range.stop = action->parameters.array[action->parameters.used].used - 1;

          status = fl_iki_read(&action->parameters.array[action->parameters.used], &range, &action->ikis.array[action->ikis.used], state);

          if (F_status_is_error(status)) {
            controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "fl_iki_read", F_true);

            action->parameters.array[action->parameters.used].used = 0;

            return status;
          }
        }

        ++action->parameters.used;
        ++action->ikis.used;
      } // for
    }

    return F_okay;
  }
#endif // _di_controller_rule_parameters_read_

#ifndef _di_controller_rule_action_type_to_action_execute_type_
  uint8_t controller_rule_action_type_to_action_execute_type(const uint8_t type) {

    if (type == controller_rule_action_type_freeze_e) {
      return controller_rule_action_execute_type_freeze_e;
    }

    if (type == controller_rule_action_type_kill_e) {
      return controller_rule_action_execute_type_kill_e;
    }

    if (type == controller_rule_action_type_pause_e) {
      return controller_rule_action_execute_type_pause_e;
    }

    if (type == controller_rule_action_type_reload_e) {
      return controller_rule_action_execute_type_reload_e;
    }

    if (type == controller_rule_action_type_restart_e) {
      return controller_rule_action_execute_type_restart_e;
    }

    if (type == controller_rule_action_type_resume_e) {
      return controller_rule_action_execute_type_resume_e;
    }

    if (type == controller_rule_action_type_start_e) {
      return controller_rule_action_execute_type_start_e;
    }

    if (type == controller_rule_action_type_stop_e) {
      return controller_rule_action_execute_type_stop_e;
    }

    if (type == controller_rule_action_type_thaw_e) {
      return controller_rule_action_execute_type_thaw_e;
    }

    return controller_rule_action_execute_type__enum_size_e;
  }
#endif // _di_controller_rule_action_type_to_action_execute_type_

#ifndef _di_controller_rule_action_read_
  f_status_t controller_rule_action_read(const controller_global_t global, const bool is_normal, const uint8_t type, const uint8_t method, controller_cache_t * const cache, controller_rule_item_t *item, controller_rule_actions_t *actions, f_range_t *range) {

    f_status_t status = F_okay;

    controller_state_interrupt_t custom = macro_controller_state_interrupt_t_initialize_1(is_normal, global.thread);
    f_state_t state = macro_f_state_t_initialize_1(controller_common_allocation_large_d, controller_common_allocation_small_d, F_okay, 0, 0, 0, &controller_thread_signal_state_fss, 0, (void *) &custom, 0);

    f_number_unsigned_t i = 0;

    for (; i < cache->comments.size; ++i) {

      cache->comments.array[i].start = 1;
      cache->comments.array[i].stop = 0;
    } // for

    for (i = 0; i < cache->delimits.size; ++i) {
      cache->delimits.array[i] = 0;
    } // for

    for (i = 0; i < cache->content_action.size; ++i) {

      cache->content_action.array[i].start = 1;
      cache->content_action.array[i].stop = 0;
    } // for

    cache->comments.used = 0;
    cache->delimits.used = 0;
    cache->content_action.used = 0;

    if (method == controller_rule_action_method_extended_list_e) {
      status = fl_fss_extended_list_content_read(cache->buffer_item, state, range, &cache->content_action, &cache->delimits, &cache->comments);

      if (F_status_is_error(status)) {
        controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "fl_fss_extended_list_content_read", F_true);

        return status;
      }

      if (status == F_fss_found_content) {
        status = f_fss_apply_delimit(state, cache->delimits, &cache->buffer_item);

        if (F_status_is_error(status)) {
          controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_fss_apply_delimit", F_true);

          return status;
        }

        // The "script" and "utility" types use the entire content and can be directly passed through at index 0.
        if (item->type == controller_rule_item_type_script_e || item->type == controller_rule_item_type_utility_e) {
          actions->array[actions->used].parameters.used = 0;

          status = f_memory_array_increase(controller_common_allocation_small_d, sizeof(f_string_dynamic_t), (void **) &actions->array[actions->used].parameters.array, &actions->array[actions->used].parameters.used, &actions->array[actions->used].parameters.size);

          if (F_status_is_error(status)) {
            controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_memory_array_increase", F_true);

            return status;
          }

          status = f_memory_array_increase(controller_common_allocation_small_d, sizeof(f_iki_data_t), (void **) &actions->array[actions->used].ikis.array, &actions->array[actions->used].ikis.used, &actions->array[actions->used].ikis.size);

          if (F_status_is_error(status)) {
            controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_memory_array_increase", F_true);

            return status;
          }

          actions->array[actions->used].type = type;
          actions->array[actions->used].line = cache->action.line_action;
          actions->array[actions->used].status = F_known_not;

          status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_action.array[0], &actions->array[actions->used].parameters.array[0]);

          if (F_status_is_error(status)) {
            controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_string_dynamic_append_nulless", F_true);

            actions->array[actions->used++].status = controller_status_simplify_error(F_status_set_fine(status));

            return status;
          }

          if (actions->array[actions->used].parameters.array[0].used) {
            state.step_large = controller_common_allocation_iki_large_d;
            state.step_small = controller_common_allocation_iki_small_d;
            state.interrupt = &controller_thread_signal_state_iki;

            f_range_t range_iki = macro_f_range_t_initialize_2(actions->array[actions->used].parameters.array[0].used);

            status = fl_iki_read(&actions->array[actions->used].parameters.array[0], &range_iki, &actions->array[actions->used].ikis.array[0], state);

            if (F_status_is_error(status)) {
              controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "fl_iki_read", F_true);

              actions->array[actions->used++].status = controller_status_simplify_error(F_status_set_fine(status));

              return status;
            }
          }

          actions->array[actions->used].ikis.used = 1;
          actions->array[actions->used++].parameters.used = 1;

          return status;
        }

        cache->delimits.used = 0;

        // The object_actions and content_actions caches are being used for the purposes of getting the parameters a given the action.
        status = fll_fss_extended_read(cache->buffer_item, state, &cache->content_action.array[0], &cache->object_actions, &cache->content_actions, 0, 0, &cache->delimits, 0);

        if (F_status_is_error(status)) {
          controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "fll_fss_extended_read", F_true);

          return status;
        }

        status = f_fss_apply_delimit(state, cache->delimits, &cache->buffer_item);

        if (F_status_is_error(status)) {
          controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_fss_apply_delimit", F_true);

          return status;
        }

        for (i = 0; i < cache->object_actions.used; ++i) {

          status = controller_rule_actions_increase_by(controller_common_allocation_small_d, actions);

          if (F_status_is_error(status)) {
            controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "controller_rule_actions_increase_by", F_true);

            return status;
          }

          status = f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &actions->array[actions->used].line, &setting->state);

          if (F_status_is_error(status)) {
            controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_fss_count_lines", F_true);

            return status;
          }

          actions->array[actions->used].type = type;
          actions->array[actions->used].line += ++item->line;
          actions->array[actions->used].status = F_known_not;

          status = controller_rule_parameters_read(global, cache->buffer_item, state, &cache->object_actions.array[i], &cache->content_actions.array[i], &actions->array[actions->used]);

          if (F_status_is_error(status)) {
            actions->array[actions->used++].status = controller_status_simplify_error(F_status_set_fine(status));

            return status;
          }

          actions->array[actions->used++].status = status;
        } // for

        range->start = cache->content_action.array[0].start;
      }
      else {
        status = F_data_not;
      }
    }
    else {
      status = fl_fss_extended_content_read(cache->buffer_item, state, range, &cache->content_action, 0, &cache->delimits);

      if (F_status_is_error(status)) {
        controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "fll_fss_extended_content_read", F_true);
      }
      else if (status == F_fss_found_content) {
        status = f_fss_apply_delimit(state, cache->delimits, &cache->buffer_item);

        if (F_status_is_error(status)) {
          controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_fss_apply_delimit", F_true);
        }
        else if (type == controller_rule_action_type_pid_file_e) {
          item->pid_file.used = 0;

          status = f_rip_dynamic_partial(cache->buffer_item, cache->content_action.array[0], &item->pid_file);

          if (F_status_is_error(status)) {
            controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_rip_dynamic_partial", F_true);
          }
        }
        else if (type == controller_rule_action_type_rerun_e) {
          uint8_t type_rerun = 0;

          if (cache->content_action.used) {
            if (f_compare_dynamic_partial_string(controller_freeze_s.string, cache->buffer_item, controller_freeze_s.used, cache->content_action.array[0]) == F_equal_to) {
              type_rerun = controller_rule_action_execute_type_freeze_e;
            }
            if (f_compare_dynamic_partial_string(controller_kill_s.string, cache->buffer_item, controller_kill_s.used, cache->content_action.array[0]) == F_equal_to) {
              type_rerun = controller_rule_action_execute_type_kill_e;
            }
            else if (f_compare_dynamic_partial_string(controller_pause_s.string, cache->buffer_item, controller_pause_s.used, cache->content_action.array[0]) == F_equal_to) {
              type_rerun = controller_rule_action_execute_type_pause_e;
            }
            else if (f_compare_dynamic_partial_string(controller_reload_s.string, cache->buffer_item, controller_reload_s.used, cache->content_action.array[0]) == F_equal_to) {
              type_rerun = controller_rule_action_execute_type_reload_e;
            }
            else if (f_compare_dynamic_partial_string(controller_restart_s.string, cache->buffer_item, controller_restart_s.used, cache->content_action.array[0]) == F_equal_to) {
              type_rerun = controller_rule_action_execute_type_restart_e;
            }
            else if (f_compare_dynamic_partial_string(controller_resume_s.string, cache->buffer_item, controller_resume_s.used, cache->content_action.array[0]) == F_equal_to) {
              type_rerun = controller_rule_action_execute_type_resume_e;
            }
            else if (f_compare_dynamic_partial_string(controller_start_s.string, cache->buffer_item, controller_start_s.used, cache->content_action.array[0]) == F_equal_to) {
              type_rerun = controller_rule_action_execute_type_start_e;
            }
            else if (f_compare_dynamic_partial_string(controller_stop_s.string, cache->buffer_item, controller_stop_s.used, cache->content_action.array[0]) == F_equal_to) {
              type_rerun = controller_rule_action_execute_type_stop_e;
            }
            else if (f_compare_dynamic_partial_string(controller_thaw_s.string, cache->buffer_item, controller_thaw_s.used, cache->content_action.array[0]) == F_equal_to) {
              type_rerun = controller_rule_action_execute_type_thaw_e;
            }
          }

          if (!type_rerun) {
            if (global.main->program.error.verbosity > f_console_verbosity_quiet_e) {
              controller_lock_print(global.main->program.error.to, global.thread);

              fl_print_format("%r%[%QRule item action '%]", global.main->program.error.to, f_string_eol_s, global.main->program.error.context, global.main->program.error.prefix, global.main->program.error.context);
              fl_print_format(f_string_format_r_single_s.string, global.main->program.error.to, global.main->program.error.notable, controller_rerun_s, global.main->program.error.notable);
              fl_print_format("%[' has '%]", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context);
              fl_print_format(f_string_format_Q_range_single_s.string, global.main->program.error.to, global.main->program.error.notable, cache->buffer_item, cache->content_action.array[0], global.main->program.error.notable);
              fl_print_format("%[' as the first value, only the following are allowed: '%]", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context);
              fl_print_format("%[%r%]%[', '%]", global.main->program.error.to, global.main->program.error.notable, controller_freeze_s, global.main->program.error.notable, global.main->program.error.context, global.main->program.error.context);
              fl_print_format("%[%r%]%[', '%]", global.main->program.error.to, global.main->program.error.notable, controller_kill_s, global.main->program.error.notable, global.main->program.error.context, global.main->program.error.context);
              fl_print_format("%[%r%]%[', '%]", global.main->program.error.to, global.main->program.error.notable, controller_pause_s, global.main->program.error.notable, global.main->program.error.context, global.main->program.error.context);
              fl_print_format("%[%r%]%[', '%]", global.main->program.error.to, global.main->program.error.notable, controller_reload_s, global.main->program.error.notable, global.main->program.error.context, global.main->program.error.context);
              fl_print_format("%[%r%]%[', '%]", global.main->program.error.to, global.main->program.error.notable, controller_restart_s, global.main->program.error.notable, global.main->program.error.context, global.main->program.error.context);
              fl_print_format("%[%r%]%[', '%]", global.main->program.error.to, global.main->program.error.notable, controller_resume_s, global.main->program.error.notable, global.main->program.error.context, global.main->program.error.context);
              fl_print_format("%[%r%]%[', '%]", global.main->program.error.to, global.main->program.error.notable, controller_start_s, global.main->program.error.notable, global.main->program.error.context, global.main->program.error.context);
              fl_print_format("%[%r%]%[', or '%]", global.main->program.error.to, global.main->program.error.notable, controller_stop_s, global.main->program.error.notable, global.main->program.error.context, global.main->program.error.context);
              fl_print_format(f_string_format_r_single_s.string, global.main->program.error.to, global.main->program.error.notable, controller_thaw_s, global.main->program.error.notable, global.main->program.error.context);
              fl_print_format(f_string_format_sentence_end_quote_s.string, global.main->program.error.to, global.main->program.error.context, global.main->program.error.context, f_string_eol_s);

              controller_rule_print_error_cache(global.main->program.error, cache->action, F_true);

              controller_unlock_print_flush(global.main->program.error.to, global.thread);
            }

            return F_status_set_error(F_valid_not);
          }

          controller_rule_rerun_item_t *rerun_item = 0;

          if (cache->content_action.used > 1) {
            if (f_compare_dynamic_partial_string(controller_failure_s.string, cache->buffer_item, controller_failure_s.used, cache->content_action.array[1]) == F_equal_to) {
              rerun_item = &item->reruns[type_rerun].failure;
              item->reruns[type_rerun].is |= controller_rule_rerun_is_failure_d;
            }
            else if (f_compare_dynamic_partial_string(controller_success_s.string, cache->buffer_item, controller_success_s.used, cache->content_action.array[1]) == F_equal_to) {
              rerun_item = &item->reruns[type_rerun].success;
              item->reruns[type_rerun].is |= controller_rule_rerun_is_success_d;
            }
          }
          else {
            if (global.main->program.error.verbosity > f_console_verbosity_quiet_e) {
              controller_lock_print(global.main->program.error.to, global.thread);

              fl_print_format("%r%[%QRule item action '%]", global.main->program.error.to, f_string_eol_s, global.main->program.error.context, global.main->program.error.prefix, global.main->program.error.context);
              fl_print_format(f_string_format_r_single_s.string, global.main->program.error.to, global.main->program.error.notable, controller_rerun_s, global.main->program.error.notable);
              fl_print_format("%[' has '%]", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context);
              fl_print_format(f_string_format_Q_range_single_s.string, global.main->program.error.to, global.main->program.error.notable, cache->buffer_item, cache->content_action.array[1], global.main->program.error.notable);
              fl_print_format("%[' as the second value, only the following are allowed: '%]", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context);
              fl_print_format("%[%r%]%[' or '%]", global.main->program.error.to, global.main->program.error.notable, controller_stop_s, global.main->program.error.notable, global.main->program.error.context, global.main->program.error.context);
              fl_print_format(f_string_format_r_single_s.string, global.main->program.error.to, global.main->program.error.notable, controller_thaw_s, global.main->program.error.notable, global.main->program.error.context);
              fl_print_format(f_string_format_sentence_end_quote_s.string, global.main->program.error.to, global.main->program.error.context, global.main->program.error.context, f_string_eol_s);

              controller_rule_print_error_cache(global.main->program.error, cache->action, F_true);

              controller_unlock_print_flush(global.main->program.error.to, global.thread);
            }

            return F_status_set_error(F_valid_not);
          }

          for (i = 2; i < cache->content_action.used; ++i) {

            if (f_compare_dynamic_partial_string(controller_delay_s.string, cache->buffer_item, controller_delay_s.used, cache->content_action.array[i]) == F_equal_to) {
              status = controller_rule_action_read_rerun_number(global, controller_delay_s.string, cache, &i, &rerun_item->delay);
            }
            else if (f_compare_dynamic_partial_string(controller_max_s.string, cache->buffer_item, controller_max_s.used, cache->content_action.array[i]) == F_equal_to) {
              status = controller_rule_action_read_rerun_number(global, controller_max_s.string, cache, &i, &rerun_item->max);
            }
            else if (f_compare_dynamic_partial_string(controller_reset_s.string, cache->buffer_item, controller_reset_s.used, cache->content_action.array[i]) == F_equal_to) {
              item->reruns[type_rerun].is |= rerun_item == &item->reruns[type_rerun].failure ? controller_rule_rerun_is_failure_reset_d : controller_rule_rerun_is_success_reset_d;
            }
            else {
              if (global.main->program.error.verbosity > f_console_verbosity_quiet_e) {
                controller_lock_print(global.main->program.error.to, global.thread);

                fl_print_format("%r%[%QRule item action '%]", global.main->program.error.to, f_string_eol_s, global.main->program.error.context, global.main->program.error.prefix, global.main->program.error.context);
                fl_print_format(f_string_format_r_single_s.string, global.main->program.error.to, global.main->program.error.notable, controller_rerun_s, global.main->program.error.notable);
                fl_print_format("%[' has an unknown value '%]", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context);
                fl_print_format(f_string_format_Q_range_single_s.string, global.main->program.error.to, global.main->program.error.notable, cache->buffer_item, cache->content_action.array[i], global.main->program.error.notable);
                fl_print_format(f_string_format_sentence_end_quote_s.string, global.main->program.error.to, global.main->program.error.context, global.main->program.error.context, f_string_eol_s);

                controller_rule_print_error_cache(global.main->program.error, cache->action, F_true);

                controller_unlock_print_flush(global.main->program.error.to, global.thread);
              }

              return F_status_set_error(F_valid_not);
            }
          } // for
        }
        else if (type == controller_rule_action_type_with_e) {
          for (i = 0; i < cache->content_action.used; ++i) {

            if (f_compare_dynamic_partial_string(controller_full_path_s.string, cache->buffer_item, controller_full_path_s.used, cache->content_action.array[i]) == F_equal_to) {
              item->with |= controller_with_full_path_d;
            }
            else if (f_compare_dynamic_partial_string(controller_session_new_s.string, cache->buffer_item, controller_session_new_s.used, cache->content_action.array[i]) == F_equal_to) {
              item->with |= controller_with_session_new_d;

              // The "session_new" and "session_same" are mutually exclusive.
              item->with &= ~controller_with_session_same_d;
            }
            else if (f_compare_dynamic_partial_string(controller_session_same_s.string, cache->buffer_item, controller_session_same_s.used, cache->content_action.array[i]) == F_equal_to) {
              item->with |= controller_with_session_same_d;

              // The "session_new" and "session_same" are mutually exclusive.
              item->with &= ~controller_with_session_new_d;
            }
            else {
              if (global.main->program.error.verbosity > f_console_verbosity_quiet_e) {
                controller_lock_print(global.main->program.error.to, global.thread);

                fl_print_format("%r%[%QUnknown value '%]", global.main->program.error.to, f_string_eol_s, global.main->program.error.context, global.main->program.error.prefix, global.main->program.error.context);
                fl_print_format(f_string_format_Q_range_single_s.string, global.main->program.error.to, global.main->program.error.notable, cache->buffer_item, cache->content_action.array[i], global.main->program.error.notable);
                fl_print_format("%[' for rule item action '%]%[%r%]", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context, global.main->program.error.notable, controller_with_s, global.main->program.error.notable);
                fl_print_format(f_string_format_sentence_end_quote_s.string, global.main->program.error.to, global.main->program.error.context, global.main->program.error.context, f_string_eol_s);

                controller_rule_print_error_cache(global.main->program.error, cache->action, F_true);

                controller_unlock_print_flush(global.main->program.error.to, global.thread);
              }

              status = F_status_set_error(F_valid_not);

              break;
            }
          } // for
        }
        else if (item->type == controller_rule_item_type_script_e || item->type == controller_rule_item_type_utility_e) {
          status = f_memory_array_increase(controller_common_allocation_small_d, sizeof(f_string_dynamic_t), (void **) &actions->array[actions->used].parameters.array, &actions->array[actions->used].parameters.used, &actions->array[actions->used].parameters.size);

          if (F_status_is_error(status)) {
            controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_memory_array_increase", F_true);

            return status;
          }

          status = f_memory_array_increase(controller_common_allocation_small_d, sizeof(f_iki_data_t), (void **) &actions->array[actions->used].ikis.array, &actions->array[actions->used].ikis.used, &actions->array[actions->used].ikis.size);

          if (F_status_is_error(status)) {
            controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_memory_array_increase", F_true);

            return status;
          }

          // The "script" types use the entire content as a single string piped to the script, so merge all arguments together.
          actions->array[actions->used].type = type;
          actions->array[actions->used].line = cache->action.line_action;
          actions->array[actions->used].status = F_known_not;

          for (i = 0; i < cache->content_action.used; ++i) {

            status = f_string_dynamic_partial_mash_nulless(f_string_space_s, cache->buffer_item, cache->content_action.array[i], &actions->array[actions->used].parameters.array[0]);
            if (F_status_is_error(status)) break;
          } // for

          if (F_status_is_error(status)) {
            controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_string_dynamic_partial_mash_nulless", F_true);

            actions->array[actions->used++].status = controller_status_simplify_error(F_status_set_fine(status));

            return status;
          }

          if (actions->array[actions->used].parameters.array[0].used) {
            state.step_large = controller_common_allocation_iki_large_d;
            state.step_small = controller_common_allocation_iki_small_d;
            state.interrupt = &controller_thread_signal_state_iki;

            f_range_t range_iki = macro_f_range_t_initialize_2(actions->array[actions->used].parameters.array[0].used);

            status = fl_iki_read(&actions->array[actions->used].parameters.array[0], &range_iki, &actions->array[actions->used].ikis.array[0], state);

            if (F_status_is_error(status)) {
              controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "fl_iki_read", F_true);

              actions->array[actions->used++].status = controller_status_simplify_error(F_status_set_fine(status));

              return status;
            }
          }

          actions->array[actions->used].ikis.used = 1;
          actions->array[actions->used++].parameters.used = 1;
        }
        else {
          status = f_fss_count_lines(cache->buffer_item, range->start, &actions->array[actions->used].line, &setting->state);

          if (F_status_is_error(status)) {
            controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_fss_count_lines", F_true);

            return status;
          }

          actions->array[actions->used].type = type;
          actions->array[actions->used].line += ++item->line;
          actions->array[actions->used].status = F_known_not;

          status = controller_rule_parameters_read(global, cache->buffer_item, state, 0, &cache->content_action, &actions->array[actions->used]);

          if (F_status_is_error(status)) {
            actions->array[actions->used++].status = controller_status_simplify_error(F_status_set_fine(status));

            return status;
          }

          actions->array[actions->used++].status = status;
        }
      }
      else {
        status = F_data_not;
      }
    }

    if (F_status_is_error_not(status) && status == F_data_not) {
      if (global.main->program.warning.verbosity == f_console_verbosity_debug_e) {
        controller_lock_print(global.main->program.warning.to, global.thread);

        fl_print_format("%r%[%QAction is empty, nothing to do.%]%r", global.main->program.warning.to, f_string_eol_s, global.main->program.warning.context, global.main->program.warning.prefix, global.main->program.warning.context, f_string_eol_s);

        controller_rule_print_error_cache(global.main->program.warning, cache->action, F_true);

        controller_unlock_print_flush(global.main->program.warning.to, global.thread);
      }
    }

    return status;
  }
#endif // _di_controller_rule_action_read_

#ifndef _di_controller_rule_action_read_rerun_number_
  f_status_t controller_rule_action_read_rerun_number(const controller_global_t global, const f_string_t name, controller_cache_t * const cache, f_number_unsigned_t * const index, f_number_unsigned_t * const number) {

    f_status_t status = F_okay;
    f_number_signed_t parsed = 0;

    if (*index + 1 == cache->content_action.used) {
      status = F_status_set_error(F_valid_not);
    }
    else {
      status = fl_conversion_dynamic_partial_to_signed_detect(fl_conversion_data_base_10_c, cache->buffer_item, cache->content_action.array[++(*index)], &parsed);

      if (F_status_set_fine(status) == F_number_positive) {
        status = fl_conversion_dynamic_partial_to_signed_detect(fl_conversion_data_base_10_c, cache->buffer_item, controller_range_after_number_sign(cache->buffer_item, cache->content_action.array[*index]), &parsed);
      }

      if (status == F_data_not) {
        status = F_status_set_error(F_valid_not);
      }
    }

    if (F_status_is_error(status)) {
      if (global.main->program.error.verbosity > f_console_verbosity_quiet_e) {
        status = F_status_set_fine(status);

        if (status != F_valid_not && status != F_number && status != F_number_decimal && status != F_number_overflow && status != F_number_underflow && status != F_number_negative) {
          controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "fl_conversion_dynamic_partial_to_signed_detect", F_true);
        }
        else {
          controller_lock_print(global.main->program.error.to, global.thread);

          fl_print_format("%r%[%QRule item action '%]", global.main->program.error.to, f_string_eol_s, global.main->program.error.context, global.main->program.error.prefix, global.main->program.error.context);
          fl_print_format(f_string_format_r_single_s.string, global.main->program.error.to, global.main->program.error.notable, controller_rerun_s, global.main->program.error.notable);
          fl_print_format("%[' requires a positive whole number or 0 for the '%]", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context);
          fl_print_format("%[%S%]", global.main->program.error.to, global.main->program.error.notable, name, global.main->program.error.notable);
          fl_print_format("%[' value", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context);

          if (*index + 1 == cache->content_action.used) {
            fl_print_format(", but none were given.%]%r", global.main->program.error.to, global.main->program.error.context, f_string_eol_s);
          }
          else {
            fl_print_format(", but '%]%[%/Q%]", global.main->program.error.to, global.main->program.error.context, global.main->program.error.notable, cache->buffer_item, cache->content_action.array[*index], global.main->program.error.notable);

            if (status == F_number || status == F_number_decimal) {
              fl_print_format("%[' was given.%]%r", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context, f_string_eol_s);
            }
            else if (status == F_number_overflow) {
              fl_print_format("%[' is too large.%]%r", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context, f_string_eol_s);
            }
            else {
              fl_print_format("%[' is negative.%]%r", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context, f_string_eol_s);
            }
          }

          controller_rule_print_error_cache(global.main->program.error, cache->action, F_true);

          controller_unlock_print_flush(global.main->program.error.to, global.thread);
        }
      }

      return status;
    }

    *number = (f_number_unsigned_t) parsed;

    return F_okay;
  }
#endif // _di_controller_rule_action_read_rerun_number_

#ifndef _di_controller_rule_copy_
  f_status_t controller_rule_copy(const controller_rule_t source, controller_rule_t *destination) {

    // Delete the third party structures.
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &destination->cgroup.path.string, &destination->cgroup.path.used, &destination->cgroup.path.size);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &destination->cgroup.groups.array, &destination->cgroup.groups.used, &destination->cgroup.groups.size, &f_string_dynamics_delete_callback);

    f_capability_delete(&destination->capability);

    f_number_unsigned_t i = 0;

    for (; i < controller_rule_action_type__enum_size_e; ++i) {
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
    destination->engine.used = 0;
    destination->engine_arguments.used = 0;
    destination->name.used = 0;
    destination->path.used = 0;

    destination->define.used = 0;
    destination->parameter.used = 0;
    destination->environment.used = 0;

    destination->affinity.used = 0;
    destination->groups.used = 0;
    destination->limits.used = 0;
    destination->scheduler.policy = source.scheduler.policy;
    destination->scheduler.priority = source.scheduler.priority;

    for (i = 0; i < destination->ons.size; ++i) {

      destination->ons.array[i].action = 0;
      destination->ons.array[i].need.used = 0;
      destination->ons.array[i].want.used = 0;
      destination->ons.array[i].wish.used = 0;
    } // for

    for (i = 0; i < destination->engine_arguments.size; ++i) {
      destination->engine_arguments.array[i].used = 0;
    } // for

    destination->ons.used = 0;
    destination->items.used = 0;

    f_status_t status = F_okay;

    status = f_string_dynamic_append(source.alias, &destination->alias);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamic_append(source.engine, &destination->engine);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamic_append(source.name, &destination->name);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamic_append(source.path, &destination->path);
    if (F_status_is_error(status)) return status;

    status = f_string_maps_append_all(source.define, &destination->define);
    if (F_status_is_error(status)) return status;

    status = f_string_maps_append_all(source.parameter, &destination->parameter);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamics_append_all(source.engine_arguments, &destination->engine_arguments);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamics_append_all(source.environment, &destination->environment);
    if (F_status_is_error(status)) return status;

    if (source.ons.used) {
      if (destination->ons.used < source.ons.used) {
        status = controller_rule_ons_resize(source.ons.used, &destination->ons);
        if (F_status_is_error(status)) return status;
      }

      for (i = 0; i < source.ons.used; ++i) {

        destination->ons.array[i].action = source.ons.array[i].action;

        if (source.ons.array[i].need.used) {
          destination->ons.array[i].need.used = 0;

          status = f_string_dynamics_append_all(source.ons.array[i].need, &destination->ons.array[i].need);
          if (F_status_is_error(status)) return status;
        }

        if (source.ons.array[i].want.used) {
          destination->ons.array[i].want.used = 0;

          status = f_string_dynamics_append_all(source.ons.array[i].want, &destination->ons.array[i].want);
          if (F_status_is_error(status)) return status;
        }

        if (source.ons.array[i].wish.used) {
          destination->ons.array[i].wish.used = 0;

          status = f_string_dynamics_append_all(source.ons.array[i].wish, &destination->ons.array[i].wish);
          if (F_status_is_error(status)) return status;
        }
      } // for

      destination->ons.used = source.ons.used;
    }

    status = f_int32s_append_all(source.affinity, &destination->affinity);
    if (F_status_is_error(status)) return status;

    if (source.capability) {
      status = f_capability_copy(source.capability, &destination->capability);
      if (F_status_is_error(status)) return status;
    }

    status = f_control_group_copy(source.cgroup, &destination->cgroup);
    if (F_status_is_error(status)) return status;

    status = f_int32s_append_all(source.groups, &destination->groups);
    if (F_status_is_error(status)) return status;

    destination->limits.used = 0;
    status = f_limit_sets_append_all(source.limits, &destination->limits);
    if (F_status_is_error(status)) return status;

    if (source.items.used) {
      controller_rule_item_t *item_source = 0;
      controller_rule_item_t *item_destination = 0;

      controller_rule_action_t *action_source = 0;
      controller_rule_action_t *action_destination = 0;

      if (source.items.used > destination->items.size) {
        status = controller_rule_items_increase_by(source.items.used - destination->items.size, &destination->items);
        if (F_status_is_error(status)) return status;
      }

      f_number_unsigned_t j = 0;

      for (i = 0; i < source.items.used; ++i) {

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

        for (j = 0; j < controller_rule_action_execute_type__enum_size_e; ++j) {

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
          action_destination->ikis.used = 0;

          status = f_string_dynamics_append_all(action_source->parameters, &action_destination->parameters);
          if (F_status_is_error(status)) return status;

          status = f_iki_datas_append_all(action_source->ikis, &action_destination->ikis);
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
  f_status_t controller_rule_execute(const controller_global_t global, const uint8_t action, const uint8_t options, controller_data_t * const process) {

    f_status_t status = F_okay;
    f_status_t success = F_false;

    f_number_unsigned_t i = 0;
    f_number_unsigned_t j = 0;
    f_number_unsigned_t k = 0;

    // Child processes should receive all signals and handle the signals as they see fit.
    f_signal_how_t signals = f_signal_how_t_initialize;
    f_signal_set_empty(&signals.block);
    f_signal_set_fill(&signals.block_not);

    f_string_maps_t environment = f_string_maps_t_initialize;

    controller_execute_set_t execute_set = macro_controller_execute_set_t_initialize_1(0, 0, &environment, &signals, 0, fl_execute_as_t_initialize);

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
          controller_print_error_file(global.thread, global.main->program.error, F_status_set_fine(status), "fll_control_group_prepare", F_true, process->rule.cgroup.path, controller_rule_print_control_groups_prepare_s, fll_error_file_type_directory_e);

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

    if (process->rule.has & controller_rule_has_environment_d) {
      status = fl_environment_load_names(process->rule.environment, &environment);

      if (F_status_is_error(status)) {
        controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "fl_environment_load_names", F_true);

        return status;
      }

      // When a "define" from the entry/exit is in the "environment", add it to the exported environments (and overwrite any existing environment variable of the same name).
      controller_entry_t *entry = 0;

      if (process->type == controller_data_type_entry_e) {
        entry = &global.setting->entry;
      }
      else if (process->type == controller_data_type_exit_e) {
        entry = &global.setting->exit;
      }

      if (entry) {
        for (i = 0; i < entry->define.used; ++i) {

          for (j = 0; j < process->rule.environment.used; ++j) {

            if (f_compare_dynamic(entry->define.array[i].key, process->rule.environment.array[j]) == F_equal_to) {

              for (k = 0; k < environment.used; ++k) {

                if (f_compare_dynamic(entry->define.array[i].key, environment.array[k].name) == F_equal_to) {

                  environment.array[k].value.used = 0;

                  status = f_string_dynamic_append(entry->define.array[i].value, &environment.array[k].value);

                  if (F_status_is_error(status)) {
                    controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_string_dynamic_append", F_true);

                    return status;
                  }

                  break;
                }
              } // for

              if (k == environment.used) {
                status = f_string_maps_append(entry->define.array[i], &environment);

                if (F_status_is_error(status)) {
                  controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_string_maps_append", F_true);

                  return status;
                }
              }

              break;
            }
          } // for
        } // for
      }

      // When a "define" is in the "environment", add it to the exported environments (and overwrite any existing environment variable of the same name).
      for (i = 0; i < process->rule.define.used; ++i) {

        for (j = 0; j < process->rule.environment.used; ++j) {

          if (f_compare_dynamic(process->rule.define.array[i].key, process->rule.environment.array[j]) == F_equal_to) {

            for (k = 0; k < environment.used; ++k) {

              if (f_compare_dynamic(process->rule.define.array[i].key, environment.array[k].name) == F_equal_to) {

                environment.array[k].value.used = 0;

                status = f_string_dynamic_append(process->rule.define.array[i].value, &environment.array[k].value);

                if (F_status_is_error(status)) {
                  controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_string_dynamic_append", F_true);

                  return status;
                }

                break;
              }
            } // for

            if (k == environment.used) {
              status = f_string_maps_append(process->rule.define.array[i], &environment);

              if (F_status_is_error(status)) {
                controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_string_maps_append", F_true);

                return status;
              }
            }

            break;
          }
        } // for
      } // for
    }
    else {
      controller_entry_t *entry = 0;

      if (process->type == controller_data_type_entry_e) {
        entry = &global.setting->entry;
      }
      else if (process->type == controller_data_type_exit_e) {
        entry = &global.setting->exit;
      }

      // When a custom define is specified, it needs to be exported into the environment.
      if (entry->define.used || process->rule.define.used) {

        // Copy all environment variables over when a custom define is used.
        status = f_environment_get_all(&environment);

        if (F_status_is_error(status)) {
          controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_environment_get_all", F_true);

          return status;
        }

        for (i = 0; i < entry->define.used; ++i) {

          status = f_string_maps_append(entry->define.array[i], &environment);

          if (F_status_is_error(status)) {
            controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_string_maps_append", F_true);

            return status;
          }
        } // for

        for (i = 0; i < process->rule.define.used; ++i) {

          status = f_string_maps_append(process->rule.define.array[i], &environment);

          if (F_status_is_error(status)) {
            controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_string_maps_append", F_true);

            return status;
          }
        } // for
      }
      else {

        // When no custom environment variables are defined, just let the original environment pass through.
        execute_set.parameter.environment = 0;
      }
    }

    for (i = 0; i < process->rule.items.used && controller_thread_is_enabled_process(process, global.thread); ++i) {

      if (process->rule.items.array[i].type == controller_rule_item_type_settings_e) continue;

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
          status = controller_rule_expand(global, process->rule.items.array[i].actions.array[j], process);

          if (F_status_is_error(status)) {
            controller_rule_print_error(global.thread, global.main->program.error, process->cache.action, F_status_set_fine(status), "controller_rule_expand", F_true, F_false);

            break;
          }

          do {
            status = controller_rule_execute_foreground(process->rule.items.array[i].type, f_string_empty_s, process->cache.expanded, options, &execute_set, process);

            if (status == F_child || F_status_set_fine(status) == F_interrupt || F_status_set_fine(status) == F_lock) break;
            if (F_status_is_error(status) && F_status_set_fine(status) != F_failure) break;

          } while (controller_rule_execute_rerun(controller_rule_action_type_to_action_execute_type(action), process, &process->rule.items.array[i]) > 0);

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
          status = controller_rule_expand(global, process->rule.items.array[i].actions.array[j], process);

          if (F_status_is_error(status)) {
            controller_rule_print_error(global.thread, global.main->program.error, process->cache.action, F_status_set_fine(status), "controller_rule_expand", F_true, F_false);

            break;
          }

          if (process->cache.expanded.used) {
            execute_set.parameter.data = &process->cache.expanded.array[0];
          }
          else {
            execute_set.parameter.data = 0;
          }

          do {
            if (process->rule.engine.used) {
              status = controller_rule_execute_foreground(process->rule.items.array[i].type, process->rule.engine, process->rule.engine_arguments, options, &execute_set, process);
            }
            else {
              status = controller_rule_execute_foreground(process->rule.items.array[i].type, *global.main->setting.default_engine, process->rule.engine_arguments, options, &execute_set, process);
            }

            if (status == F_child || F_status_set_fine(status) == F_lock) break;
            if (F_status_is_error(status) && F_status_set_fine(status) != F_failure) break;

          } while (controller_rule_execute_rerun(controller_rule_action_type_to_action_execute_type(action), process, &process->rule.items.array[i]) > 0);

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
          status = controller_rule_expand(global, process->rule.items.array[i].actions.array[j], process);

          if (F_status_is_error(status)) {
            controller_rule_print_error(global.thread, global.main->program.error, process->cache.action, F_status_set_fine(status), "controller_rule_expand", F_true, F_false);

            break;
          }

          if (process->rule.items.array[i].pid_file.used) {
            do {
              status = controller_rule_execute_pid_with(process->rule.items.array[i].pid_file, process->rule.items.array[i].type, f_string_empty_s, process->cache.expanded, options, process->rule.items.array[i].with, &execute_set, process);

              if (status == F_child || F_status_set_fine(status) == F_interrupt || F_status_set_fine(status) == F_lock) break;
              if (F_status_is_error(status) && F_status_set_fine(status) != F_failure) break;

            } while (controller_rule_execute_rerun(controller_rule_action_type_to_action_execute_type(action), process, &process->rule.items.array[i]) > 0);

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

            controller_rule_action_print_error_missing_pid(global.main->program.error, process->rule.alias);
          }
        }
        else if (process->rule.items.array[i].type == controller_rule_item_type_utility_e) {
          if (process->rule.items.array[i].pid_file.used) {
            status = controller_rule_expand(global, process->rule.items.array[i].actions.array[j], process);

            if (F_status_is_error(status)) {
              controller_rule_print_error(global.thread, global.main->program.error, process->cache.action, F_status_set_fine(status), "controller_rule_expand", F_true, F_false);

              break;
            }

            if (process->cache.expanded.used) {
              execute_set.parameter.data = &process->cache.expanded.array[0];
            }
            else {
              execute_set.parameter.data = 0;
            }

            do {
              status = controller_rule_execute_pid_with(process->rule.items.array[i].pid_file, process->rule.items.array[i].type, process->rule.engine.used ? process->rule.engine : *global.main->setting.default_engine, process->rule.engine_arguments, options, process->rule.items.array[i].with, &execute_set, process);

              if (status == F_child || F_status_set_fine(status) == F_interrupt || F_status_set_fine(status) == F_lock) break;
              if (F_status_is_error(status) && F_status_set_fine(status) != F_failure) break;

            } while (controller_rule_execute_rerun(controller_rule_action_type_to_action_execute_type(action), process, &process->rule.items.array[i]) > 0);

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

            controller_rule_action_print_error_missing_pid(global.main->program.error, process->rule.alias);
          }
        }
        else {
          if (global.main->program.warning.verbosity == f_console_verbosity_debug_e) {
            controller_lock_print(global.main->program.warning.to, global.thread);

            fl_print_format("%r%[%QAction type is unknown, ignoring.%]%r", global.main->program.warning.to, f_string_eol_s, global.main->program.warning.context, global.main->program.warning.prefix, global.main->program.warning.context, f_string_eol_s);

            controller_rule_print_error_cache(global.main->program.warning, process->cache.action, F_true);

            controller_unlock_print_flush(global.main->program.warning.to, global.thread);
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
      if (F_status_is_error(status)) return F_status_set_error(F_lock);

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

    return F_okay;
  }
#endif // _di_controller_rule_execute_

#ifndef _di_controller_rule_execute_foreground_
  f_status_t controller_rule_execute_foreground(const uint8_t type, const f_string_static_t program, const f_string_statics_t arguments, const uint8_t options, controller_execute_set_t * const execute_set, controller_data_t * const process) {

    f_status_t status = F_okay;
    f_status_t status_lock = F_okay;

    controller_main_t * const main = (controller_main_t *) process->main_data;
    controller_thread_t * const thread = (controller_thread_t *) process->main_thread;

    f_execute_result_t result = f_execute_result_t_initialize;

    status = controller_pids_increase(&process->childs);

    if (F_status_is_error(status)) {
      controller_print_error(thread, main->program.error, F_status_set_fine(status), "controller_pids_increase", F_true);

      return status;
    }

    pid_t *child = 0;

    {
      f_number_unsigned_t i = 0;

      while (i < process->childs.used && process->childs.array[i]) {
        ++i;
      } // while

      child = &process->childs.array[i];

      if (i == process->childs.used) {
        ++process->childs.used;
      }
    }

    if (options & controller_process_option_simulate_d) {
      if (main->program.output.verbosity != f_console_verbosity_quiet_e) {
        controller_lock_print(main->program.output.to, thread);

        fl_print_format("%rSimulating execution of '%[", main->program.output.to, f_string_eol_s, main->program.context.set.title);

        if (program.used) {
          f_print_dynamic_safely(program, main->program.output.to);
        }
        else {
          f_print_dynamic_safely(arguments.array[0], main->program.output.to);
        }

        fl_print_format("%]' with the arguments: '%[", main->program.output.to, main->program.context.set.title, main->program.context.set.important);

        for (f_number_unsigned_t i = program.used ? 0 : 1; i < arguments.used; ++i) {

          if (program.used && i || !program.used && i > 1) {
            f_print_dynamic_raw(f_string_space_s, main->program.output.to);
          }

          f_print_dynamic_safely(arguments.array[i], main->program.output.to);
        } // for

        fl_print_format("%]' from '", main->program.output.to, main->program.context.set.important);
        fl_print_format("%[%Q%]'.%r", main->program.output.to, main->program.context.set.notable, process->rule.name, main->program.context.set.notable, f_string_eol_s);

        controller_unlock_print_flush(main->program.output.to, thread);
      }

      // Sleep for less than a second to better show simulation of synchronous vs asynchronous.
      {
        const struct timespec delay = controller_time_milliseconds(controller_thread_simulation_timeout_d);

        if (controller_time_sleep_nanoseconds(main, (controller_process_t *) process->main_setting, delay) == -1) {
          status = F_status_set_error(F_interrupt);
        }
      }

      if (F_status_set_fine(status) != F_interrupt) {
        fl_execute_parameter_t simulated_parameter = macro_fl_execute_parameter_t_initialize_1(execute_set->parameter.option, execute_set->parameter.wait, process->rule.has & controller_rule_has_environment_d ? execute_set->parameter.environment : 0, execute_set->parameter.signals, &f_string_empty_s);

        status = fll_execute_program(*main->setting.default_engine, process->rule.engine_arguments, &simulated_parameter, &execute_set->as, (void *) &result);
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
        controller_lock_print_error_critical(&main->program.error, F_status_set_fine(status_lock), F_false, thread);

        if (F_status_set_fine(status_lock) != F_interrupt) {
          status = controller_lock_read_process(process, thread, &process->lock);

          if (status == F_okay) {
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
        controller_lock_print_error_critical(&main->program.error, F_status_set_fine(status_lock), F_true, thread);
      }

      if (F_status_set_fine(status_lock) != F_interrupt) {

        // Have the parent wait for the child process to finish.
        waitpid(id_child, &result.status, 0);
      }

      if (F_status_set_fine(status_lock) == F_interrupt || !controller_thread_is_enabled_process(process, thread)) {
        if (status_lock == F_okay) {
          return F_status_set_error(F_interrupt);
        }

        return F_status_set_error(F_lock);
      }

      if (status_lock == F_okay) {
        f_thread_unlock(&process->lock);
      }

      status_lock = controller_lock_write_process(process, thread, &process->lock);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(&main->program.error, F_status_set_fine(status_lock), F_false, thread);

        if (F_status_set_fine(status_lock) != F_interrupt) {
          status = controller_lock_read_process(process, thread, &process->lock);

          if (status == F_okay) {
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
        controller_lock_print_error_critical(&main->program.error, F_status_set_fine(status_lock), F_true, thread);

        return F_status_set_error(F_lock);
      }

      if (WIFEXITED(result.status) ? WEXITSTATUS(result.status) : 0) {
        status = F_status_set_error(F_failure);
      }
      else {
        status = F_okay;
      }
    }
    else {
      main->program.child = result.status;

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
        controller_rule_item_print_error_execute(type == controller_rule_item_type_script_e, program.used ? program : arguments.array[0], status, process);
      }
      else {
        controller_print_error(thread, main->program.error, F_status_set_fine(status), "fll_execute_program", F_true);
      }

      status = F_status_set_error(status);
    }

    return status;
  }
#endif // _di_controller_rule_execute_foreground_

#ifndef _di_controller_rule_execute_pid_with_
  f_status_t controller_rule_execute_pid_with(const f_string_dynamic_t pid_file, const uint8_t type, const f_string_static_t program, const f_string_statics_t arguments, const uint8_t options, const uint8_t with, controller_execute_set_t * const execute_set, controller_data_t * const process) {

    f_status_t status = F_okay;
    f_status_t status_lock = F_okay;

    controller_main_t * const main = (controller_main_t *) process->main_data;
    controller_thread_t * const thread = (controller_thread_t *) process->main_thread;

    f_execute_result_t result = f_execute_result_t_initialize;

    status = controller_pids_increase(&process->childs);

    if (F_status_is_error(status)) {
      controller_print_error(thread, main->program.error, F_status_set_fine(status), "controller_pids_increase", F_true);

      return status;
    }

    status = f_memory_array_increase(controller_common_allocation_small_d, sizeof(f_string_dynamic_t), (void **) &process->path_pids.array, &process->path_pids.used, &process->path_pids.size);

    if (F_status_is_error(status)) {
      controller_print_error(thread, main->program.error, F_status_set_fine(status), "f_memory_array_increase", F_true);

      return status;
    }

    pid_t *child = 0;
    f_string_dynamic_t *child_pid_file = 0;

    {
      f_number_unsigned_t i = 0;

      while (i < process->childs.used && process->childs.array[i]) {
        ++i;
      } // while

      child = &process->childs.array[i];

      if (i == process->childs.used) {
        ++process->childs.used;
      }

      i = 0;

      while (i < process->path_pids.used && process->path_pids.array[i].used) {
        ++i;
      } // while

      child_pid_file = &process->path_pids.array[i];

      if (i == process->path_pids.used) {
        ++process->path_pids.used;
      }
    }

    status = f_file_exists(pid_file, F_true);

    if (F_status_is_error(status)) {
      controller_print_error_file(thread, main->program.error, F_status_set_fine(status), "f_file_exists", F_true, pid_file, f_file_operation_find_s, fll_error_file_type_file_e);

      return status;
    }

    if (status == F_true) {
      controller_print_error_file(thread, main->program.error, F_file_found, "f_file_exists", F_true, pid_file, f_file_operation_find_s, fll_error_file_type_file_e);

      return F_status_set_error(F_file_found);
    }

    status = f_string_dynamic_append_nulless(pid_file, child_pid_file);

    if (F_status_is_error(status)) {
      controller_print_error(thread, main->program.error, F_status_set_fine(status), "f_string_dynamic_append_nulless", F_true);

      return status;
    }

    if (options & controller_process_option_simulate_d) {
      if (main->program.error.verbosity > f_console_verbosity_error_e) {
        controller_lock_print(main->program.error.to, thread);

        fl_print_format("%rSimulating execution of '%[", main->program.error.to, f_string_eol_s, main->program.context.set.title);

        if (program.used) {
          f_print_dynamic_safely(program, main->program.error.to);
        }
        else {
          f_print_dynamic_safely(arguments.array[0], main->program.error.to);
        }

        fl_print_format("%]' with the arguments: '%[", main->program.error.to, main->program.context.set.title, main->program.context.set.important);

        for (f_number_unsigned_t i = program.used ? 0 : 1; i < arguments.used; ++i) {

          if (program.used && i || !program.used && i > 1) {
            f_print_dynamic_raw(f_string_space_s, main->program.error.to);
          }

          f_print_dynamic_safely(arguments.array[i], main->program.error.to);
        } // for

        fl_print_format("%]' from '", main->program.error.to, main->program.context.set.important);
        fl_print_format("%[%Q%]'.%r", main->program.error.to, main->program.context.set.notable, process->rule.name, main->program.context.set.notable, f_string_eol_s);

        controller_unlock_print_flush(main->program.error.to, thread);
      }

      // Sleep for less than a second to better show simulation of synchronous vs asynchronous.
      {
        const struct timespec delay = controller_time_milliseconds(controller_thread_simulation_timeout_d);

        if (controller_time_sleep_nanoseconds(main, (controller_process_t *) process->main_setting, delay) == -1) {
          status = F_status_set_error(F_interrupt);
        }
      }

      if (F_status_set_fine(status) != F_interrupt) {
        const f_string_statics_t simulated_arguments = f_string_statics_t_initialize;
        fl_execute_parameter_t simulated_parameter = macro_fl_execute_parameter_t_initialize_1(execute_set->parameter.option, execute_set->parameter.wait, process->rule.has & controller_rule_has_environment_d ? execute_set->parameter.environment : 0, execute_set->parameter.signals, &f_string_empty_s);

        status = fll_execute_program(*main->setting.default_engine, simulated_arguments, &simulated_parameter, &execute_set->as, (void *) &result);
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
        controller_lock_print_error_critical(&main->program.error, F_status_set_fine(status_lock), F_false, thread);

        if (F_status_set_fine(status_lock) != F_interrupt) {
          status = controller_lock_read_process(process, thread, &process->lock);

          if (status == F_okay) {
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
        controller_lock_print_error_critical(&main->program.error, F_status_set_fine(status_lock), F_true, thread);
      }

      if (F_status_set_fine(status_lock) != F_interrupt) {

        // The child process should perform the change into background, therefore it is safe to wait for the child to exit (another process is spawned).
        waitpid(id_child, &result.status, 0);
      }

      if (!controller_thread_is_enabled_process(process, thread)) {
        if (status_lock == F_okay) {
          return F_status_set_error(F_interrupt);
        }

        return F_status_set_error(F_lock);
      }

      if (status_lock == F_okay) {
        f_thread_unlock(&process->lock);
      }

      status_lock = controller_lock_write_process(process, thread, &process->lock);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(&main->program.error, F_status_set_fine(status_lock), F_false, thread);

        if (F_status_set_fine(status_lock) != F_interrupt) {
          status = controller_lock_read_process(process, thread, &process->lock);

          if (status == F_okay) {
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
        controller_lock_print_error_critical(&main->program.error, F_status_set_fine(status_lock), F_true, thread);

        return F_status_set_error(F_lock);
      }

      if (WIFEXITED(result.status) ? WEXITSTATUS(result.status) : 0) {
        status = F_status_set_error(F_failure);
      }
      else {
        status = F_okay;
      }
    }
    else {
      main->program.child = result.status;

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
        controller_rule_item_print_error_execute(type == controller_rule_item_type_utility_e, program.used ? program : arguments.array[0], status, process);
      }
      else {
        controller_print_error(thread, main->program.error, F_status_set_fine(status), "fll_execute_program", F_true);
      }

      return F_status_set_error(status);
    }

    return status;
  }
#endif // _di_controller_rule_execute_pid_with_

#ifndef _di_controller_rule_execute_rerun_
  int8_t controller_rule_execute_rerun(const uint8_t action, controller_data_t * const process, controller_rule_item_t * const item) {

    const int result = WIFEXITED(process->result) ? WEXITSTATUS(process->result) : 0;

    if (item->reruns[action].is & (result ? controller_rule_rerun_is_failure_d : controller_rule_rerun_is_success_d)) {
      controller_main_t * const main = (controller_main_t *) process->main_data;
      controller_thread_t * const thread = (controller_thread_t *) process->main_thread;
      controller_rule_rerun_item_t *rerun_item = result ? &item->reruns[action].failure : &item->reruns[action].success;

      if (!controller_thread_is_enabled_process(process, thread)) return -2;

      if (!rerun_item->max || rerun_item->count < rerun_item->max) {
        if (main->program.error.verbosity == f_console_verbosity_debug_e) {
          controller_lock_print(main->program.output.to, thread);

          fl_print_format("%rRe-running '", main->program.output.to, f_string_eol_s);
          fl_print_format("%[%r%]' '", main->program.output.to, main->program.context.set.title, process->rule.alias, main->program.context.set.title);
          fl_print_format("%[%r%]' with a ", main->program.output.to, main->program.context.set.notable, controller_rule_action_execute_type_name(action), main->program.context.set.notable);
          fl_print_format("%[%r%] of ", main->program.output.to, main->program.context.set.notable, controller_delay_s, main->program.context.set.notable);
          fl_print_format("%[%ul%] MegaTime", main->program.output.to, main->program.context.set.notable, rerun_item->delay, main->program.context.set.notable);

          if (rerun_item->max) {
            fl_print_format(" for %[%ul%]", main->program.output.to, main->program.context.set.notable, rerun_item->count, main->program.context.set.notable);
            fl_print_format(" of %[%r%] ", main->program.output.to, main->program.context.set.notable, controller_max_s, main->program.context.set.notable);
            fl_print_format(f_string_format_un_single_s.string, main->program.output.to, main->program.context.set.notable, rerun_item->max, main->program.context.set.notable);
            fl_print_format(".%r", main->program.output.to, f_string_eol_s);
          }
          else {
            fl_print_format(" with no %[%r%].%r", main->program.output.to, main->program.context.set.notable, controller_max_s, main->program.context.set.notable, f_string_eol_s);
          }

          controller_unlock_print_flush(main->program.output.to, thread);
        }

        if (rerun_item->delay) {
          const struct timespec delay = controller_time_milliseconds(rerun_item->delay);

          if (controller_time_sleep_nanoseconds(main, (controller_process_t *) process->main_setting, delay) == -1) {
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

#ifndef _di_controller_rule_expand_
  f_status_t controller_rule_expand(const controller_global_t global, const controller_rule_action_t action, controller_data_t * const process) {

    process->cache.expanded.used = 0;

    if (!action.parameters.used) {
      return F_okay;
    }

    f_status_t status = f_memory_array_increase_by(action.parameters.used, sizeof(f_string_dynamic_t), (void **) &process->cache.expanded.array, &process->cache.expanded.used, &process->cache.expanded.size);
    if (F_status_is_error(status)) return status;

    f_number_unsigned_t i = 0;
    f_number_unsigned_t first = 0;
    f_range_t range = f_range_t_initialize;

    f_iki_data_t *iki_data = 0;
    f_string_dynamic_t *buffer = 0;

    for (; process->cache.expanded.used < action.parameters.used; ++process->cache.expanded.used) {

      buffer = &process->cache.expanded.array[process->cache.expanded.used];
      buffer->used = 0;

      if (action.ikis.array[process->cache.expanded.used].variable.used) {
        iki_data = &action.ikis.array[process->cache.expanded.used];

        // Allocate enough room plus an extra buffer to help reduce reallocations.
        status = f_memory_array_increase_by(action.parameters.array[process->cache.expanded.used].used + controller_common_allocation_large_d, sizeof(f_char_t), (void **) &buffer->string, &buffer->used, &buffer->size);

        // Apply the IKI delimits.
        for (i = 0; i < iki_data->delimits.used; ++i) {
          action.parameters.array[process->cache.expanded.used].string[iki_data->delimits.array[i]] = f_iki_syntax_placeholder_s.string[0];
        } // for

        if (iki_data->variable.used) {
          for (i = 0, first = 0; i < iki_data->variable.used; ++i) {

            // Copy everything up to the start of the IKI variable.
            if (first < iki_data->variable.array[i].start) {
              range.start = first;
              range.stop = iki_data->variable.array[i].start - 1;

              status = f_string_dynamic_partial_append_nulless(action.parameters.array[process->cache.expanded.used], range, buffer);
              if (F_status_is_error(status)) break;
            }

            status = controller_rule_expand_iki(process, action.parameters.array[process->cache.expanded.used], iki_data->vocabulary.array[i], iki_data->content.array[i], buffer);
            if (F_status_is_error(status)) break;

            first = iki_data->variable.array[i].stop + 1;
          } // for

          if (F_status_is_error(status)) break;

          // Copy everything after the last IKI variable to the end of the content.
          if (first < action.parameters.array[process->cache.expanded.used].used) {
            range.start = first;
            range.stop = action.parameters.array[process->cache.expanded.used].used - 1;

            status = f_string_dynamic_partial_append(action.parameters.array[process->cache.expanded.used], range, buffer);
          }
        }
        else {
          status = f_string_dynamic_append_nulless(action.parameters.array[process->cache.expanded.used], buffer);
        }

        // Unapply the IKI delimits.
        for (i = 0; i < iki_data->delimits.used; ++i) {
          action.parameters.array[process->cache.expanded.used].string[iki_data->delimits.array[i]] = f_iki_syntax_slash_s.string[0];
        } // for
      }
      else {
        status = f_string_dynamic_append(action.parameters.array[process->cache.expanded.used], buffer);
      }

      if (F_status_is_error(status)) return status;
    } // for

    return F_okay;
  }
#endif // _di_controller_rule_expand_

#ifndef _di_controller_rule_expand_iki_
  f_status_t controller_rule_expand_iki(controller_data_t * const process, const f_string_static_t source, const f_range_t vocabulary, const f_range_t content, f_string_dynamic_t * const destination) {

    if (vocabulary.start > vocabulary.stop) return F_okay;
    if (content.start > content.stop) return F_okay;

    f_status_t status = F_okay;

    if (f_compare_dynamic_partial_string(controller_define_s.string, source, controller_define_s.used, vocabulary) == F_equal_to) {
      f_number_unsigned_t i = 0;

      // First check to see if the environment variable is overwritten by a "define".
      for (; i < process->rule.define.used; ++i) {

        if (f_compare_dynamic_partial_string(process->rule.define.array[i].key.string, source, process->rule.define.array[i].key.used, content) == F_equal_to) {
          status = f_string_dynamic_append(process->rule.define.array[i].value, destination);
          if (F_status_is_error(status)) return status;

          break;
        }
      } // for

      if (i == process->rule.define.used) {
        controller_entry_t * const entry = process->type == controller_data_type_entry_e ? &((controller_process_t *) process->main_setting)->entry : &((controller_process_t *) process->main_setting)->exit;

        for (i = 0; i < entry->define.used; ++i) {

            if (f_compare_dynamic_partial_string(entry->define.array[i].key.string, source, entry->define.array[i].key.used, content) == F_equal_to) {
            status = f_string_dynamic_append(entry->define.array[i].value, destination);
            if (F_status_is_error(status)) return status;

            break;
          }
        } // for

        if (i == entry->define.used) {
          i = process->rule.define.used;
        }
      }

      if (i == process->rule.define.used) {
        f_string_static_t buffer = f_string_static_t_initialize;
        buffer.used = (content.stop - content.start) + 1;

        f_char_t buffer_string[buffer.used + 1];

        memcpy(buffer_string, source.string + content.start, sizeof(f_char_t) * buffer.used);
        buffer_string[buffer.used] = 0;
        buffer.string = buffer_string;
        process->cache.action.generic.used = 0;

        status = f_environment_get(buffer, &process->cache.action.generic);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamic_append(process->cache.action.generic, destination);
        if (F_status_is_error(status)) return status;
      }
    }
    else if (f_compare_dynamic_partial_string(controller_parameter_s.string, source, controller_parameter_s.used, vocabulary) == F_equal_to) {
      f_number_unsigned_t i = 0;

      for (; i < process->rule.parameter.used; ++i) {

        if (f_compare_dynamic_partial_string(process->rule.parameter.array[i].key.string, source, process->rule.parameter.array[i].key.used, content) == F_equal_to) {
          status = f_string_dynamic_append(process->rule.parameter.array[i].value, destination);
          if (F_status_is_error(status)) return status;

          break;
        }
      } // for

      if (i == process->rule.parameter.used) {
        controller_entry_t * const entry = process->type == controller_data_type_entry_e ? &((controller_process_t *) process->main_setting)->entry : &((controller_process_t *) process->main_setting)->exit;

        for (i = 0; i < entry->parameter.used; ++i) {

            if (f_compare_dynamic_partial_string(entry->parameter.array[i].key.string, source, entry->parameter.array[i].key.used, content) == F_equal_to) {
            status = f_string_dynamic_append(entry->parameter.array[i].value, destination);
            if (F_status_is_error(status)) return status;

            break;
          }
        } // for
      }
    }
    else if (f_compare_dynamic_partial_string(controller_program_s.string, source, controller_program_s.used, vocabulary) == F_equal_to) {
      f_string_static_t * const argv = ((controller_main_t *) process->main_data)->parameters.arguments.array;
      f_console_parameters_t * const parameters = &((controller_main_t *) process->main_data)->parameters;

      const f_string_static_t options[] = {
        f_console_standard_long_light_s,
        f_console_standard_long_dark_s,
        f_console_standard_long_no_color_s,
        f_console_standard_long_quiet_s,
        f_console_standard_long_normal_s,
        f_console_standard_long_verbose_s,
        f_console_standard_long_debug_s,
        controller_long_init_s,
        controller_long_interruptible_s,
        controller_long_daemon_s,
        controller_long_simulate_s,
        controller_long_uninterruptible_s,
        controller_long_validate_s,

        // Option and Value.
        controller_long_cgroup_s,
        controller_long_pid_s,
        controller_long_settings_s,
        controller_long_socket_s,
      };

      const f_string_static_t symbols[] = {
        f_console_symbol_short_inverse_s, // light.
        f_console_symbol_short_inverse_s, // dark.
        f_console_symbol_short_inverse_s, // no_color.
        f_console_symbol_short_inverse_s, // quiet.
        f_console_symbol_short_inverse_s, // normal.
        f_console_symbol_short_inverse_s, // verbose.
        f_console_symbol_short_inverse_s, // debug.
        f_console_symbol_short_normal_s,  // daemon.
        f_console_symbol_short_normal_s,  // init.
        f_console_symbol_short_normal_s,  // interruptible.
        f_console_symbol_short_normal_s,  // simulate.
        f_console_symbol_short_normal_s,  // uninterruptible.
        f_console_symbol_short_normal_s,  // validate.

        // Option and Value.
        f_console_symbol_short_normal_s,  // cgroup.
        f_console_symbol_short_normal_s,  // pid.
        f_console_symbol_short_normal_s,  // settings.
        f_console_symbol_short_normal_s,  // socket.
      };

      const f_string_static_t expands[] = {
        f_console_standard_short_light_s,
        f_console_standard_short_dark_s,
        f_console_standard_short_no_color_s,
        f_console_standard_short_quiet_s,
        f_console_standard_short_normal_s,
        f_console_standard_short_verbose_s,
        f_console_standard_short_debug_s,
        controller_short_init_s,
        controller_short_interruptible_s,
        controller_short_daemon_s,
        controller_short_simulate_s,
        controller_short_uninterruptible_s,
        controller_short_validate_s,

        // Option and Value.
        controller_short_cgroup_s,
        controller_short_pid_s,
        controller_short_settings_s,
        controller_short_socket_s,
      };

      const uint8_t codes[] = {
        f_console_standard_parameter_help_e,
        f_console_standard_parameter_dark_e,
        f_console_standard_parameter_no_color_e,
        f_console_standard_parameter_verbosity_quiet_e,
        f_console_standard_parameter_verbosity_normal_e,
        f_console_standard_parameter_verbosity_verbose_e,
        f_console_standard_parameter_verbosity_debug_e,
        controller_parameter_init_e,
        controller_parameter_interruptible_e,
        controller_parameter_daemon_e,
        controller_parameter_simulate_e,
        controller_parameter_uninterruptible_e,
        controller_parameter_validate_e,

        // Option and Value.
        controller_parameter_cgroup_e,
        controller_parameter_pid_e,
        controller_parameter_settings_e,
        controller_parameter_socket_e,
      };

      // F_false = only with option, F_true with option and value.
      const bool values[] = {
        F_false, // light.
        F_false, // dark.
        F_false, // no_color.
        F_false, // quiet.
        F_false, // normal.
        F_false, // verbose.
        F_false, // debug.
        F_false, // daemon.
        F_false, // init.
        F_false, // interruptible.
        F_false, // simulate.
        F_false, // uninterruptible.
        F_false, // validate.

        // Option and Value.
        F_true, // cgroup.
        F_true, // pid.
        F_true, // settings.
        F_true, // socket.
      };

      for (f_number_unsigned_t i = 0; i < 17; ++i) {

        if (f_compare_dynamic_partial_string(options[i].string, source, options[i].used, content) == F_equal_to) {
          if (values[i]) {
            if (parameters->array[codes[i]].result & f_console_result_value_e) {
              const f_number_unsigned_t index = parameters->array[codes[i]].values.array[parameters->array[codes[i]].values.used - 1];

              status = f_memory_array_increase_by(symbols[i].used + expands[i].used + f_string_ascii_space_s.used + argv[index].used + 1, sizeof(f_char_t), (void **) &destination->string, &destination->used, &destination->size);
              if (F_status_is_error(status)) return status;

              status = f_string_dynamic_append(symbols[i], destination);
              if (F_status_is_error(status)) return status;

              status = f_string_dynamic_append(expands[i], destination);
              if (F_status_is_error(status)) return status;

              status = f_string_dynamic_append(f_string_ascii_space_s, destination);
              if (F_status_is_error(status)) return status;

              status = f_string_dynamic_append(argv[index], destination);
              if (F_status_is_error(status)) return status;
            }
          }
          else {
            if (parameters->array[codes[i]].result & f_console_result_found_e) {
              status = f_memory_array_increase_by(symbols[i].used + expands[i].used + 1, sizeof(f_char_t), (void **) &destination->string, &destination->used, &destination->size);
              if (F_status_is_error(status)) return status;

              status = f_string_dynamic_append(symbols[i], destination);
              if (F_status_is_error(status)) return status;

              status = f_string_dynamic_append(expands[i], destination);
              if (F_status_is_error(status)) return status;
            }
          }

          break;
        }

        {
          f_string_static_t buffer = f_string_static_t_initialize;
          buffer.used = options[i].used + controller_parameter_map_option_s.used;

          f_char_t buffer_string[buffer.used];
          buffer.string = buffer_string;

          memcpy(buffer_string, options[i].string, sizeof(f_char_t) * options[i].used);
          memcpy(buffer_string + options[i].used, controller_parameter_map_option_s.string, sizeof(f_char_t) * controller_parameter_map_option_s.used);

          if (f_compare_dynamic_partial_string(buffer.string, source, buffer.used, content) == F_equal_to) {
            if (values[i] && parameters->array[codes[i]].result & f_console_result_value_e || !values[i] && (parameters->array[codes[i]].result & f_console_result_found_e)) {
              status = f_memory_array_increase_by(symbols[i].used + expands[i].used + 1, sizeof(f_char_t), (void **) &destination->string, &destination->used, &destination->size);
              if (F_status_is_error(status)) return status;

              status = f_string_dynamic_append(symbols[i], destination);
              if (F_status_is_error(status)) return status;

              status = f_string_dynamic_append(expands[i], destination);
              if (F_status_is_error(status)) return status;
            }

            break;
          }
        }

        if (values[i]) {
          f_string_static_t buffer = f_string_static_t_initialize;
          buffer.used = options[i].used + controller_parameter_map_value_s.used;

          f_char_t buffer_string[buffer.used];
          buffer.string = buffer_string;

          memcpy(buffer_string, options[i].string, sizeof(f_char_t) * options[i].used);
          memcpy(buffer_string + options[i].used, controller_parameter_map_value_s.string, sizeof(f_char_t) * controller_parameter_map_value_s.used);

          if (f_compare_dynamic_partial_string(buffer.string, source, buffer.used, content) == F_equal_to) {
            if (parameters->array[codes[i]].result & f_console_result_value_e) {
              const f_number_unsigned_t index = parameters->array[codes[i]].values.array[parameters->array[codes[i]].values.used - 1];

              status = f_string_dynamic_append(argv[index], destination);
              if (F_status_is_error(status)) return status;
            }

            break;
          }
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_controller_rule_expand_iki_

#ifndef _di_controller_rule_id_construct_
  f_status_t controller_rule_id_construct(const controller_global_t global, const f_string_static_t source, const f_range_t directory, const f_range_t basename, f_string_dynamic_t * const alias) {

    f_status_t status = F_okay;

    alias->used = 0;

    status = f_string_dynamic_partial_append_nulless(source, directory, alias);

    if (F_status_is_error(status)) {
      controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true);

      return status;
    }

    status = f_string_dynamic_append(f_path_separator_s, alias);

    if (F_status_is_error(status)) {
      controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_string_dynamic_append", F_true);

      return status;
    }

    status = f_string_dynamic_partial_append_nulless(source, basename, alias);

    if (F_status_is_error(status)) {
      controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true);

      return status;
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

    f_status_t status = F_okay;
    controller_state_interrupt_t custom = macro_controller_state_interrupt_t_initialize_1(is_normal, global.thread);
    f_state_t state = macro_f_state_t_initialize_1(controller_common_allocation_large_d, controller_common_allocation_small_d, F_okay, 0, 0, 0, &controller_thread_signal_state_fss, 0, (void *) &custom, 0);
    f_range_t range = macro_f_range_t_initialize_2(cache->buffer_item.used);
    f_number_unsigned_t last = 0;

    uint8_t type = 0;
    uint8_t method = 0;
    bool multiple = F_false;

    item->actions.used = 0;

    for (; range.start < cache->buffer_item.used && range.start <= range.stop; last = range.start, cache->delimits.used = 0, cache->comments.used = 0) {

      status = fl_fss_extended_list_object_read(cache->buffer_item, state, &range, &cache->range_action, &cache->delimits);

      if (F_status_is_error(status)) {
        controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "fl_fss_extended_list_object_read", F_true);

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
        fl_fss_extended_object_read(cache->buffer_item, &range, &cache->range_action, 0, &cache->delimits, state);

        if (F_status_is_error(status)) {
          controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "fl_fss_extended_object_read", F_true);

          break;
        }

        // Nothing of importance here, so continue onto the next line.
        if (status != F_fss_found_object) continue;
      }

      status = f_fss_apply_delimit(state, cache->delimits, &cache->buffer_item);

      if (F_status_is_error(status)) {
        controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_fss_apply_delimit", F_true);

        break;
      }

      status = f_fss_count_lines(cache->buffer_item, cache->range_action.start, &cache->action.line_action, &setting->state);

      if (F_status_is_error(status)) {
        controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_fss_count_lines", F_true);

        break;
      }

      cache->action.line_action += ++item->line;
      cache->action.name_action.used = 0;

      status = f_rip_dynamic_partial_nulless(cache->buffer_item, cache->range_action, &cache->action.name_action);

      if (F_status_is_error(status)) {
        controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_rip_dynamic_partial_nulless", F_true);

        break;
      }

      if (f_compare_dynamic(controller_freeze_s, cache->action.name_action) == F_equal_to) {
        type = controller_rule_action_type_freeze_e;
      }
      else if (f_compare_dynamic(controller_group_s, cache->action.name_action) == F_equal_to) {
        type = controller_rule_action_type_group_e;
      }
      else if (f_compare_dynamic(controller_kill_s, cache->action.name_action) == F_equal_to) {
        type = controller_rule_action_type_kill_e;
      }
      else if (f_compare_dynamic(controller_pause_s, cache->action.name_action) == F_equal_to) {
        type = controller_rule_action_type_pause_e;
      }
      else if (f_compare_dynamic(controller_pid_file_s, cache->action.name_action) == F_equal_to) {
        type = controller_rule_action_type_pid_file_e;
      }
      else if (f_compare_dynamic(controller_reload_s, cache->action.name_action) == F_equal_to) {
        type = controller_rule_action_type_reload_e;
      }
      else if (f_compare_dynamic(controller_rerun_s, cache->action.name_action) == F_equal_to) {
        type = controller_rule_action_type_rerun_e;
      }
      else if (f_compare_dynamic(controller_restart_s, cache->action.name_action) == F_equal_to) {
        type = controller_rule_action_type_restart_e;
      }
      else if (f_compare_dynamic(controller_resume_s, cache->action.name_action) == F_equal_to) {
        type = controller_rule_action_type_resume_e;
      }
      else if (f_compare_dynamic(controller_start_s, cache->action.name_action) == F_equal_to) {
        type = controller_rule_action_type_start_e;
      }
      else if (f_compare_dynamic(controller_stop_s, cache->action.name_action) == F_equal_to) {
        type = controller_rule_action_type_stop_e;
      }
      else if (f_compare_dynamic(controller_thaw_s, cache->action.name_action) == F_equal_to) {
        type = controller_rule_action_type_thaw_e;
      }
      else if (f_compare_dynamic(controller_user_s, cache->action.name_action) == F_equal_to) {
        type = controller_rule_action_type_user_e;
      }
      else if (f_compare_dynamic(controller_with_s, cache->action.name_action) == F_equal_to) {
        type = controller_rule_action_type_with_e;
      }
      else {
        if (global.main->program.warning.verbosity == f_console_verbosity_debug_e) {
          controller_lock_print(global.main->program.warning.to, global.thread);

          fl_print_format("%r%[%QUnknown rule item action '%]", global.main->program.warning.to, f_string_eol_s, global.main->program.warning.context, global.main->program.warning.prefix, global.main->program.warning.context);
          fl_print_format(f_string_format_Q_single_s.string, global.main->program.warning.to, global.main->program.warning.notable, cache->action.name_action, global.main->program.warning.notable);
          fl_print_format(f_string_format_sentence_end_quote_s.string, global.main->program.warning.to, global.main->program.warning.context, global.main->program.warning.context, f_string_eol_s);

          controller_rule_print_error_cache(global.main->program.warning, cache->action, F_true);

          controller_unlock_print_flush(global.main->program.warning.to, global.thread);
        }

        continue;
      }

      if (multiple) {
        if (type == controller_rule_action_type_group_e || type == controller_rule_action_type_pid_file_e || type == controller_rule_action_type_user_e) {

          if (global.main->program.error.verbosity > f_console_verbosity_quiet_e) {
            controller_lock_print(global.main->program.error.to, global.thread);

            fl_print_format("%r%[%QFSS Extended List is not allowed for the rule item action '%]", global.main->program.error.to, f_string_eol_s, global.main->program.error.context, global.main->program.error.prefix, global.main->program.error.context);
            fl_print_format(f_string_format_Q_single_s.string, global.main->program.error.to, global.main->program.error.notable, cache->action.name_action, global.main->program.error.notable);
            fl_print_format(f_string_format_sentence_end_quote_s.string, global.main->program.error.to, global.main->program.error.context, global.main->program.error.context, f_string_eol_s);

            controller_unlock_print_flush(global.main->program.error.to, global.thread);
          }

          status = F_status_set_error(F_support_not);
          break;
        }

        method = controller_rule_action_method_extended_list_e;
      }
      else {
        method = controller_rule_action_method_extended_e;
      }

      status = controller_rule_actions_increase_by(controller_common_allocation_small_d, &item->actions);

      if (F_status_is_error(status)) {
        controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "controller_rule_actions_increase_by", F_true);

        break;
      }

      status = controller_rule_action_read(global, is_normal, type, method, cache, item, &item->actions, &range);
      if (F_status_is_error(status)) break;
    } // for

    return status;
  }
#endif // _di_controller_rule_item_read_

#ifndef _di_controller_rule_items_increase_by_
  f_status_t controller_rule_items_increase_by(const f_number_unsigned_t amount, controller_rule_items_t * const items) {

    if (amount) {
      if (items->used >= F_number_t_size_unsigned_d) return F_status_set_error(F_array_too_large);

      const f_number_unsigned_t length = items->used + amount;

      if (length > items->size) {
        const f_status_t status = f_memory_resize(items->size, length, sizeof(controller_rule_item_t), (void **) & items->array);

        if (F_status_is_error_not(status)) {
          items->size = items->used + amount;
        }

        return status;
      }
    }

    return F_data_not;
  }
#endif // _di_controller_rule_items_increase_by_

#ifndef _di_controller_rule_process_
  f_status_t controller_rule_process(const controller_global_t global, controller_data_t * const process) {

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
        if (global.main->program.error.verbosity > f_console_verbosity_quiet_e) {
          controller_lock_print(global.main->program.error.to, global.thread);

          fl_print_format("%r%[%QUnsupported action type '%]", global.main->program.error.to, f_string_eol_s, global.main->program.error.context, global.main->program.error.prefix, global.main->program.error.context);
          fl_print_format(f_string_format_r_single_s.string, global.main->program.error.to, global.main->program.error.notable, controller_rule_action_type_name(process->action), global.main->program.error.notable);
          fl_print_format("%[' while attempting to execute rule.%]%r", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context, f_string_eol_s);

          controller_rule_print_error_cache(global.main->program.error, process->cache.action, F_true);

          controller_unlock_print_flush(global.main->program.error.to, global.thread);
        }

        return F_status_set_error(F_parameter);
    }

    f_status_t status = F_okay;
    f_status_t status_lock = F_okay;

    process->cache.action.name_action.used = 0;
    process->cache.action.name_item.used = 0;
    process->cache.action.name_file.used = 0;

    status = f_string_dynamic_append(controller_rules_s, &process->cache.action.name_file);

    if (F_status_is_error_not(status)) {
      status = f_string_dynamic_append(f_path_separator_s, &process->cache.action.name_file);
    }

    if (F_status_is_error(status)) {
      controller_rule_print_error(global.thread, global.main->program.error, process->cache.action, F_status_set_fine(status), "f_string_dynamic_append", F_true, F_true);

      return status;
    }

    status = f_string_dynamic_append(process->rule.alias, &process->cache.action.name_file);

    if (F_status_is_error(status)) {
      controller_rule_print_error(global.thread, global.main->program.error, process->cache.action, F_status_set_fine(status), "f_string_dynamic_append", F_true, F_true);

      return status;
    }

    status = f_string_dynamic_append(f_path_extension_separator_s, &process->cache.action.name_file);

    if (F_status_is_error_not(status)) {
      status = f_string_dynamic_append(controller_rule_s, &process->cache.action.name_file);
    }

    if (F_status_is_error(status)) {
      controller_rule_print_error(global.thread, global.main->program.error, process->cache.action, F_status_set_fine(status), "f_string_dynamic_append", F_true, F_true);

      return status;
    }

    if ((process->options & controller_process_option_simulate_d) && (process->options & controller_process_option_validate_d)) {
      controller_rule_validate(global, process->rule, process->action, process->options, &process->cache);
    }

    f_number_unsigned_t i = 0;

    {
      f_number_unsigned_t j = 0;
      f_number_unsigned_t id_rule = 0;
      f_number_unsigned_t id_dependency = 0;

      bool found = F_false;

      controller_data_t *dependency = 0;

      uint8_t options_process = 0;

      const f_string_static_t strings[3] = {
        controller_rule_needed_s,
        controller_rule_wanted_s,
        controller_rule_wished_s,
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
      // Loop through all dependencies: wait for depedency, execute dependency, fail due to missing required dependency, or skip unrequired missing dependencies.
      for (i = 0; i < 3 && controller_thread_is_enabled_process(process, global.thread); ++i) {

        for (j = 0; j < dynamics[i]->used && controller_thread_is_enabled_process(process, global.thread); ++j) {

          id_dependency = 0;
          dependency = 0;
          found = F_false;

          status_lock = controller_lock_read_process(process, global.thread, &global.thread->lock.process);

          if (F_status_is_error(status_lock)) {
            controller_lock_print_error_critical(global.main->program.error, F_status_set_fine(status_lock), F_true, global.thread);
          }
          else {
            status = controller_process_prepare_process_type(global, process->type, process->action, dynamics[i]->array[j], &id_dependency);

            if (F_status_is_error(status)) {
              if (F_status_set_fine(status) == F_lock) {
                if (!controller_thread_is_enabled_process_type(process->type, global.thread)) {
                  return F_status_set_error(F_interrupt);
                }
              }

              if (global.main->program.error.verbosity > f_console_verbosity_quiet_e) {
                controller_lock_print(global.main->program.error.to, global.thread);

                controller_rule_item_print_error_rule_not_loaded(global.main->program.error, dynamics[i]->array[j]);
                controller_rule_print_error_cache(global.main->program.error, process->cache.action, F_false);

                controller_unlock_print_flush(global.main->program.error.to, global.thread);
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
              controller_lock_print_error_critical(global.main->program.error, F_status_set_fine(status_lock), F_true, global.thread);

              status = F_false;
              dependency = 0;

              f_thread_unlock(&global.thread->lock.process);
            }
            else {
              f_thread_unlock(&global.thread->lock.process);

              status_lock = controller_lock_read_process(process, global.thread, &global.thread->lock.rule);

              if (F_status_is_error(status_lock)) {
                controller_lock_print_error_critical(global.main->program.error, F_status_set_fine(status_lock), F_true, global.thread);

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
              controller_lock_print(global.main->program.error.to, global.thread);

              controller_rule_item_print_error_need_want_wish(global.main->program.error, strings[i], dynamics[i]->array[j], "is not found");
              controller_rule_print_error_cache(global.main->program.error, process->cache.action, F_true);

              controller_unlock_print_flush(global.main->program.error.to, global.thread);

              status = F_status_set_error(F_found_not);

              if (!(process->options & controller_process_option_simulate_d)) {
                if (dependency) {
                  f_thread_unlock(&dependency->active);
                }

                break;
              }
            }
            else {
              if (global.main->program.warning.verbosity == f_console_verbosity_debug_e) {
                controller_lock_print(global.main->program.warning.to, global.thread);

                controller_rule_item_print_error_need_want_wish(global.main->program.warning, strings[i], dynamics[i]->array[j], "is not found");

                controller_rule_print_error_cache(global.main->program.warning, process->cache.action, F_true);

                controller_unlock_print_flush(global.main->program.warning.to, global.thread);
              }
            }
          }
          else if (found) {
            status_lock = controller_lock_read_process(process, global.thread, &global.thread->lock.rule);

            if (F_status_is_error(status_lock)) {
              controller_lock_print_error_critical(global.main->program.error, F_status_set_fine(status_lock), F_true, global.thread);

              found = F_false;
              status = status_lock;
            }
          }

          if (found) {

            // The dependency may have write locks, which needs to be avoided, so copy the alias from the rule.
            f_string_static_t alias_other_buffer = f_string_static_t_initialize;
            alias_other_buffer.used = global.setting->rules.array[id_rule].alias.used;

            f_char_t alias_other_buffer_string[alias_other_buffer.used + 1];
            alias_other_buffer.string = alias_other_buffer_string;

            memcpy(alias_other_buffer_string, global.setting->rules.array[id_rule].alias.string, sizeof(f_char_t) * alias_other_buffer.used);
            alias_other_buffer_string[alias_other_buffer.used] = 0;

            f_thread_unlock(&global.thread->lock.rule);

            status_lock = controller_lock_read_process(process, global.thread, &dependency->lock);

            if (F_status_is_error(status_lock)) {
              controller_lock_print_error_critical(global.main->program.error, F_status_set_fine(status_lock), F_true, global.thread);

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
                controller_lock_print_error_critical(global.main->program.error, F_status_set_fine(status_lock), F_true, global.thread);

                f_thread_unlock(&dependency->lock);

                status = status_lock;
              }
              else if (controller_rule_status_is_available(process->action, global.setting->rules.array[id_rule])) {
                f_thread_unlock(&global.thread->lock.rule);
                f_thread_unlock(&dependency->lock);

                options_process = 0;

                if (global.main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e) {
                  options_process |= controller_process_option_simulate_d;
                }

                if (process->options & controller_process_option_validate_d) {
                  options_process |= controller_process_option_validate_d;
                }

                // Synchronously execute dependency.
                status = controller_rule_process_begin(global, 0, alias_other_buffer, process->action, options_process, process->type, process->stack, dependency->cache);

                if (status == F_child || F_status_set_fine(status) == F_interrupt) {
                  f_thread_unlock(&dependency->active);

                  break;
                }

                if (F_status_is_error(status)) {
                  if (i == 0 || i == 1 || F_status_set_fine(status) == F_memory_not) {
                    controller_lock_print(global.main->program.error.to, global.thread);

                    controller_rule_item_print_error_need_want_wish(global.main->program.error, strings[i], alias_other_buffer, "failed during execution");
                    controller_rule_print_error_cache(global.main->program.error, process->cache.action, F_true);

                    controller_unlock_print_flush(global.main->program.error.to, global.thread);

                    if (!(dependency->options & controller_process_option_simulate_d) || F_status_set_fine(status) == F_memory_not) {
                      f_thread_unlock(&dependency->active);

                      break;
                    }
                  }
                  else {
                    if (global.main->program.warning.verbosity == f_console_verbosity_debug_e) {
                      controller_lock_print(global.main->program.warning.to, global.thread);

                      controller_rule_item_print_error_need_want_wish(global.main->program.warning, strings[i], alias_other_buffer, "failed during execution");

                      controller_rule_print_error_cache(global.main->program.warning, process->cache.action, F_true);

                      controller_unlock_print_flush(global.main->program.warning.to, global.thread);
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
                controller_lock_print_error_critical(global.main->program.error, F_status_set_fine(status_lock), F_false, global.thread);
              }
            }

            if (F_status_is_error(status_lock)) {
              if (F_status_is_error(status_lock)) {
                controller_rule_item_print_error_need_want_wish(global.main->program.error, strings[i], alias_other_buffer, "due to lock failure");
              }

              status = status_lock;
            }
            else if (controller_rule_status_is_error(process->action, global.setting->rules.array[id_rule])) {
              f_thread_unlock(&global.thread->lock.rule);

              if (i == 0 || i == 1) {
                controller_lock_print(global.main->program.error.to, global.thread);

                controller_rule_item_print_error_need_want_wish(global.main->program.error, strings[i], alias_other_buffer, "is in a failed state");

                controller_rule_print_error_cache(global.main->program.error, process->cache.action, F_true);

                controller_unlock_print_flush(global.main->program.error.to, global.thread);

                status = F_status_set_error(F_found_not);

                if (!(dependency->options & controller_process_option_simulate_d)) {
                  f_thread_unlock(&dependency->active);

                  break;
                }
              }
              else {
                if (global.main->program.warning.verbosity == f_console_verbosity_debug_e) {
                  controller_lock_print(global.main->program.warning.to, global.thread);

                  controller_rule_item_print_error_need_want_wish(global.main->program.warning, strings[i], alias_other_buffer, "is in a failed state");

                  controller_rule_print_error_cache(global.main->program.warning, process->cache.action, F_true);

                  controller_unlock_print_flush(global.main->program.warning.to, global.thread);
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

      // Find at least one of the requested action when the rule is required.
      if (process->options & controller_process_option_require_d) {
        bool missing = F_true;

        f_number_unsigned_t j = 0;

        for (i = 0; i < process->rule.items.used; ++i) {

          for (j = 0; j < process->rule.items.array[i].actions.used; ++j) {

            if (process->rule.items.array[i].actions.array[j].type == process->action) {
              missing = F_false;

              break;
            }
          } // for
        } // for

        if (missing) {
          if (global.main->program.error.verbosity > f_console_verbosity_quiet_e) {
            controller_lock_print(global.main->program.error.to, global.thread);

            if (process->rule.items.used) {
              fl_print_format("%r%[%QThe rule '%]", global.main->program.error.to, f_string_eol_s, global.main->program.error.context, global.main->program.error.prefix, global.main->program.error.context);
              fl_print_format(f_string_format_Q_single_s.string, global.main->program.error.to, global.main->program.error.notable, process->rule.name, global.main->program.error.notable);
              fl_print_format("%[' has no '%]", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context);
              fl_print_format(f_string_format_r_single_s.string, global.main->program.error.to, global.main->program.error.notable, controller_rule_action_type_name(process->action), global.main->program.error.notable);
              fl_print_format("%[' action to execute.%]%r", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context, f_string_eol_s);
            }
            else {
              fl_print_format("%r%[%QThe rule '%]", global.main->program.error.to, f_string_eol_s, global.main->program.error.context, global.main->program.error.prefix, global.main->program.error.context);
              fl_print_format(f_string_format_Q_single_s.string, global.main->program.error.to, global.main->program.error.notable, process->rule.name, global.main->program.error.notable);
              fl_print_format("%[ has no known '%]", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context);
              fl_print_format("%[%r %r%]", global.main->program.error.to, global.main->program.error.notable, controller_rule_s, controller_type_s, global.main->program.error.notable);
              fl_print_format("%[' (such as '%]", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context);
              fl_print_format(f_string_format_r_single_s.string, global.main->program.error.to, global.main->program.error.notable, controller_command_s, global.main->program.error.notable);
              fl_print_format("%[', '%]", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context);
              fl_print_format(f_string_format_r_single_s.string, global.main->program.error.to, global.main->program.error.notable, controller_service_s, global.main->program.error.notable);
              fl_print_format("%[', '%]", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context);
              fl_print_format(f_string_format_r_single_s.string, global.main->program.error.to, global.main->program.error.notable, controller_script_s, global.main->program.error.notable);
              fl_print_format("%[', or '%]", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context);
              fl_print_format(f_string_format_r_single_s.string, global.main->program.error.to, global.main->program.error.notable, controller_utility_s, global.main->program.error.notable);
              fl_print_format("%[') to execute.%]%r", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context, f_string_eol_s);
            }

            controller_rule_print_error_cache(global.main->program.error, process->cache.action, F_true);

            controller_unlock_print_flush(global.main->program.error.to, global.thread);
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
          controller_rule_item_print_error(global.thread, global.main->program.error, process->cache.action, F_true, F_status_set_fine(status));
        }
      }
    }

    f_number_unsigned_t id_rule = 0;

    f_thread_unlock(&process->lock);

    status_lock = controller_lock_write_process(process, global.thread, &process->lock);

    if (F_status_is_error(status_lock)) {
      controller_lock_print_error_critical(global.main->program.error, F_status_set_fine(status_lock), F_false, global.thread);

      if (F_status_set_fine(status) != F_interrupt) {
        status = controller_lock_read_process(process, global.thread, &process->lock);
        if (F_status_is_error_not(status)) return status_lock;
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
      controller_lock_print_error_critical(global.main->program.error, F_status_set_fine(status_lock), F_false, global.thread);

      f_thread_unlock(&process->lock);

      status = controller_lock_read_process(process, global.thread, &process->lock);
      if (F_status_is_error_not(status)) return status_lock;

      return F_status_set_error(F_lock);
    }

    // Update the global rule status, which is stored separately from the rule status for this process.
    if (controller_rule_find(process->rule.alias, global.setting->rules, &id_rule) == F_true) {
      controller_rule_t *rule = &global.setting->rules.array[id_rule];

      rule->status[process->action] = process->rule.status[process->action];

      f_number_unsigned_t j = 0;

      controller_rule_item_t *rule_item = 0;

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
      controller_lock_print_error_critical(global.main->program.error, F_status_set_fine(status_lock), F_true, global.thread);

      return F_status_set_error(F_lock);
    }

    return process->rule.status[process->action];
  }
#endif // _di_controller_rule_process_

#ifndef _di_controller_rule_process_begin_
  f_status_t controller_rule_process_begin(const controller_global_t global, const uint8_t options_force, const f_string_static_t alias_rule, const uint8_t action, const uint8_t options, const uint8_t type, const f_number_unsigneds_t stack, const controller_cache_t cache) {

    if (!controller_thread_is_enabled_process_type(type, global.thread)) {
      return F_status_set_error(F_interrupt);
    }

    f_status_t status = F_okay;
    f_status_t status_lock = F_okay;

    controller_data_t *process = 0;

    status = controller_lock_read_process_type(type, global.thread, &global.thread->lock.process);

    if (F_status_is_error(status)) {
      controller_lock_print_error_critical(global.main->program.error, F_status_set_fine(status), F_true, global.thread);

      return status;
    }

    {
      f_number_unsigned_t at = 0;

      status = controller_process_prepare(global, type != controller_data_type_exit_e, action, alias_rule, &at);

      if (F_status_is_error(status)) {
        f_thread_unlock(&global.thread->lock.process);

        if (global.main->program.error.verbosity > f_console_verbosity_quiet_e) {
          controller_lock_print(global.main->program.error.to, global.thread);

          controller_rule_item_print_error_rule_not_loaded(global.main->program.error, alias_rule);
          controller_rule_print_error_cache(global.main->program.error, cache.action, F_false);

          controller_unlock_print_flush(global.main->program.error.to, global.thread);
        }

        return status;
      }

      process = global.thread->processs.array[at];

      status = controller_lock_read_process_type(type, global.thread, &process->active);

      if (F_status_is_error(status)) {
        controller_lock_print_error_critical(global.main->program.error, F_status_set_fine(status), F_true, global.thread);
        controller_rule_item_print_error(global.thread, global.main->program.error, cache.action, F_false, F_status_set_fine(status));

        f_thread_unlock(&global.thread->lock.process);

        return status;
      }

      status_lock = controller_lock_write_process(process, global.thread, &process->lock);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(global.main->program.error, F_status_set_fine(status_lock), F_false, global.thread);

        f_thread_unlock(&process->active);
        f_thread_unlock(&global.thread->lock.process);

        return status_lock;
      }

      // Once a write lock on the process is achieved, it is safe to unlock the global process read lock.
      f_thread_unlock(&global.thread->lock.process);

      // If the process is already running, then there is nothing to do.
      if (process->state == controller_process_state_active_e || process->state == controller_process_state_busy_e) {
        f_thread_unlock(&process->lock);
        f_thread_unlock(&process->active);

        return F_busy;
      }

      // The thread is done, so close the thread.
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
      controller_lock_print_error_critical(global.main->program.error, F_status_set_fine(status_lock), F_false, global.thread);

      f_thread_unlock(&process->active);

      return status_lock;
    }

    process->state = controller_process_state_active_e;
    process->action = action;
    process->options = options;
    process->type = type;

    macro_f_time_spec_t_clear(process->cache.timestamp)
    macro_f_range_t_clear(process->cache.range_action)

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
    process->cache.expanded.used = 0;
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
        status = f_memory_array_resize(stack.used, sizeof(f_number_unsigned_t), (void **) &process->stack.array, &process->stack.used, &process->stack.size);
      }

      if (F_status_is_error(status)) {
        controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_memory_array_resize", F_true);
      }
      else {
        for (f_number_unsigned_t i = 0; i < stack.used; ++i) {
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
        controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_string_dynamic_append", F_true);
      }
    }

    f_thread_unlock(&process->lock);

    if (F_status_is_error_not(status)) {
      if (process->action && (options_force & controller_process_option_asynchronous_d)) {
        if (process->type == controller_data_type_exit_e) {
          status = f_thread_create(0, &process->id_thread, controller_thread_process_other, (void *) process);
        }
        else {
          status = f_thread_create(0, &process->id_thread, controller_thread_process_normal, (void *) process);
        }

        if (F_status_is_error(status)) {
          controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_thread_create", F_true);
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
          controller_lock_print_error_critical(global.main->program.error, F_status_set_fine(status_lock), F_false, global.thread);

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

    return F_okay;
  }
#endif // _di_controller_rule_process_begin_

#ifndef _di_controller_rule_process_do_
  f_status_t controller_rule_process_do(const uint8_t options_force, controller_data_t * const process) {

    f_status_t status_lock = F_okay;

    controller_global_t global = macro_controller_global_t_initialize_1((controller_main_t *) process->main_data, (controller_process_t *) process->main_setting, (controller_thread_t *) process->main_thread);

    // The process and active locks shall be held for the duration of this processing (aside from switching between read to/from write).
    if (options_force & controller_process_option_asynchronous_d) {
      status_lock = controller_lock_read_process(process, global.thread, &process->active);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(global.main->program.error, F_status_set_fine(status_lock), F_true, global.thread);

        return status_lock;
      }
    }

    status_lock = controller_lock_read_process(process, global.thread, &process->lock);

    if (F_status_is_error(status_lock)) {
      controller_lock_print_error_critical(global.main->program.error, F_status_set_fine(status_lock), F_true, global.thread);

      if (options_force & controller_process_option_asynchronous_d) {
        f_thread_unlock(&process->active);
      }

      return status_lock;
    }

    f_status_t status = F_okay;

    f_number_unsigned_t id_rule = 0;

    const f_number_unsigned_t used_original_stack = process->stack.used;

    status_lock = controller_lock_read_process(process, global.thread, &global.thread->lock.rule);

    if (F_status_is_error(status_lock)) {
      controller_lock_print_error_critical(global.main->program.error, F_status_set_fine(status_lock), F_true, global.thread);

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
        controller_lock_print_error_critical(global.main->program.error, F_status_set_fine(status_lock), F_false, global.thread);

        f_thread_unlock(&global.thread->lock.rule);

        if (options_force & controller_process_option_asynchronous_d) {
          f_thread_unlock(&process->active);
        }

        return status_lock;
      }

      controller_rule_delete(&process->rule);

      status = controller_rule_copy(global.setting->rules.array[id_rule], &process->rule);

      f_thread_unlock(&process->lock);

      status_lock = controller_lock_read_process(process, global.thread, &process->lock);

      if (F_status_is_error(status_lock)) {
        controller_lock_print_error_critical(global.main->program.error, F_status_set_fine(status_lock), F_true, global.thread);

        f_thread_unlock(&global.thread->lock.rule);

        if (options_force & controller_process_option_asynchronous_d) {
          f_thread_unlock(&process->active);
        }

        return status_lock;
      }

      f_thread_unlock(&global.thread->lock.rule);

      if (F_status_is_error(status)) {
        controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "controller_rule_copy", F_true);
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
        for (f_number_unsigned_t i = 0; i < process->stack.used && controller_thread_is_enabled_process(process, global.thread); ++i) {

          if (process->stack.array[i] == id_rule) {
            if (global.main->program.error.verbosity > f_console_verbosity_quiet_e) {
              controller_lock_print(global.main->program.error.to, global.thread);

              fl_print_format("%r%[%QThe rule '%]", global.main->program.error.to, f_string_eol_s, global.main->program.error.context, global.main->program.error.prefix, global.main->program.error.context);
              fl_print_format(f_string_format_Q_single_s.string, global.main->program.error.to, global.main->program.error.notable, process->rule.alias, global.main->program.error.notable);
              fl_print_format("%[' is already on the execution dependency stack, this recursion is prohibited.%]%r", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context, f_string_eol_s);

              controller_rule_print_error_cache(global.main->program.error, process->cache.action, F_true);

              controller_unlock_print_flush(global.main->program.error.to, global.thread);
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
          status = f_memory_array_increase(controller_common_allocation_small_d, sizeof(f_number_unsigned_t), (void **) &process->stack.array, &process->stack.used, &process->stack.size);

          if (F_status_is_error(status)) {
            controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_memory_array_increase", F_true);
          }
          else {
            f_thread_unlock(&process->lock);

            status_lock = controller_lock_write_process(process, global.thread, &process->lock);

            if (F_status_is_error(status_lock)) {
              controller_lock_print_error_critical(global.main->program.error, F_status_set_fine(status_lock), F_false, global.thread);

              if (options_force & controller_process_option_asynchronous_d) {
                f_thread_unlock(&process->active);
              }

              return status_lock;
            }

            process->stack.array[process->stack.used++] = id_rule;

            f_thread_unlock(&process->lock);

            status_lock = controller_lock_read_process(process, global.thread, &process->lock);

            if (F_status_is_error(status_lock)) {
              controller_lock_print_error_critical(global.main->program.error, F_status_set_fine(status_lock), F_true, global.thread);

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

      if (global.main->program.error.verbosity > f_console_verbosity_quiet_e) {
        controller_lock_print(global.main->program.error.to, global.thread);

        controller_rule_item_print_error_rule_not_loaded(global.main->program.error, process->rule.alias);
        controller_rule_print_error_cache(global.main->program.error, process->cache.action, F_false);

        controller_unlock_print_flush(global.main->program.error.to, global.thread);
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
      controller_lock_print_error_critical(global.main->program.error, F_status_set_fine(status_lock), F_false, global.thread);

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
      controller_lock_print_error_critical(global.main->program.error, F_status_set_fine(status_lock), F_false, global.thread);

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

    f_status_t status = F_okay;

    bool for_item = F_true;

    rule->timeout_kill = entry->timeout_kill ? entry->timeout_kill : 0;
    rule->timeout_start = entry->timeout_start ? entry->timeout_start : 0;
    rule->timeout_stop = entry->timeout_stop ? entry->timeout_stop : 0;

    rule->has = 0;
    rule->group = 0;
    rule->user = 0;
    rule->nice = 0;

    macro_f_time_spec_t_clear(rule->timestamp);

    rule->alias.used = 0;
    rule->engine.used = 0;
    rule->engine_arguments.used = 0;
    rule->name.used = 0;
    rule->path.used = 0;

    rule->define.used = 0;
    rule->parameter.used = 0;
    rule->environment.used = 0;

    rule->affinity.used = 0;

    if (rule->capability) {
      f_capability_delete(&rule->capability);
      rule->capability = 0;
    }

    rule->cgroup.as_new = F_false;
    rule->cgroup.path.used = 0;
    rule->cgroup.groups.used = 0;

    macro_f_control_group_t_clear(rule->cgroup);

    rule->groups.used = 0;
    rule->limits.used = 0;

    rule->scheduler.policy = 0;
    rule->scheduler.priority = 0;

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

    cache->content_items.used = 0;
    cache->object_items.used = 0;

    cache->action.name_action.used = 0;
    cache->action.name_file.used = 0;
    cache->action.name_item.used = 0;

    {
      f_number_unsigned_t i = 0;
      f_number_unsigned_t j = 0;
      f_number_unsigned_t k = 0;
      f_number_unsigned_t l = 0;

      for (i = 0; i < rule->cgroup.groups.size; ++i) {
        rule->cgroup.groups.array[i].used = 0;
      } // for

      for (; i < controller_rule_action_type__enum_size_e; ++i) {
        rule->status[i] = F_known_not;
      } // for

      for (i = 0; i < cache->content_items.size; ++i) {
        cache->content_items.array[i].used = 0;
      } // for

      for (i = 0; i < rule->engine_arguments.size; ++i) {
        rule->engine_arguments.array[i].used = 0;
      } // for

      for (i = 0; i < rule->ons.size; ++i) {
        rule->ons.array[i].need.used = 0;
        rule->ons.array[i].want.used = 0;
        rule->ons.array[i].wish.used = 0;
      } // for

      for (i = 0; i < rule->items.size; ++i) {

        rule->items.array[i].type = 0;
        rule->items.array[i].with = 0;
        rule->items.array[i].line = 0;
        rule->items.array[i].pid_file.used = 0;
        rule->items.array[i].actions.used = 0;

        for (j = 0; j < controller_rule_action_execute_type__enum_size_e; ++j) {

          rule->items.array[i].reruns[j].is = 0;

          macro_controller_rule_rerun_item_initialize(rule->items.array[i].reruns[j].failure);
          macro_controller_rule_rerun_item_initialize(rule->items.array[i].reruns[j].success);
        } // for

        for (j = 0; j < rule->items.array[i].actions.size; ++j) {

          rule->items.array[i].actions.array[j].type = 0;
          rule->items.array[i].actions.array[j].line = 0;
          rule->items.array[i].actions.array[j].status = F_okay;
          rule->items.array[i].actions.array[j].parameters.used = 0;
          rule->items.array[i].actions.array[j].ikis.used = 0;

          for (k = 0; k < rule->items.array[i].actions.array[j].parameters.size; ++k) {
            rule->items.array[i].actions.array[j].parameters.array[k].used = 0;
          } // for

          for (k = 0; k < rule->items.array[i].actions.array[j].ikis.size; ++k) {

            rule->items.array[i].actions.array[j].ikis.array[k].content.used = 0;
            rule->items.array[i].actions.array[j].ikis.array[k].delimits.used = 0;
            rule->items.array[i].actions.array[j].ikis.array[k].variable.used = 0;
            rule->items.array[i].actions.array[j].ikis.array[k].vocabulary.used = 0;

            for (l = 0; l < rule->items.array[i].actions.array[j].ikis.array[k].content.size; ++l) {

              rule->items.array[i].actions.array[j].ikis.array[k].content.array[l].start = 1;
              rule->items.array[i].actions.array[j].ikis.array[k].content.array[l].stop = 0;
            } // for

            for (l = 0; l < rule->items.array[i].actions.array[j].ikis.array[k].delimits.size; ++l) {
              rule->items.array[i].actions.array[j].ikis.array[k].delimits.array[l] = 0;
            } // for

            for (l = 0; l < rule->items.array[i].actions.array[j].ikis.array[k].variable.size; ++l) {

              rule->items.array[i].actions.array[j].ikis.array[k].variable.array[l].start = 1;
              rule->items.array[i].actions.array[j].ikis.array[k].variable.array[l].stop = 0;
            } // for

            for (l = 0; l < rule->items.array[i].actions.array[j].ikis.array[k].vocabulary.size; ++l) {

              rule->items.array[i].actions.array[j].ikis.array[k].vocabulary.array[l].start = 1;
              rule->items.array[i].actions.array[j].ikis.array[k].vocabulary.array[l].stop = 0;
            } // for
          } // for
        } // for
      } // for
    }

    status = f_string_dynamic_append_nulless(alias, &rule->alias);

    if (F_status_is_error(status)) {
      controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_string_dynamic_append_nulless", F_true);
    }
    else {
      status = controller_file_load(global, F_true, controller_rules_s, rule->alias, controller_rule_s, cache);
    }

    if (F_status_is_error_not(status)) {
      rule->timestamp = cache->timestamp;

      if (cache->buffer_file.used) {
        controller_state_interrupt_t custom = macro_controller_state_interrupt_t_initialize_1(is_normal, global.thread);
        f_state_t state = macro_f_state_t_initialize_1(controller_common_allocation_large_d, controller_common_allocation_small_d, F_okay, 0, 0, 0, &controller_thread_signal_state_fss, 0, (void *) &custom, 0);
        f_range_t range = macro_f_range_t_initialize_2(cache->buffer_file.used);

        status = fll_fss_basic_list_read(cache->buffer_file, state, &range, &cache->object_items, &cache->content_items, &cache->delimits, 0, &cache->comments);

        if (F_status_is_error(status)) {
          controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "fll_fss_basic_list_read", F_true);
        }
        else {
          status = f_fss_apply_delimit(state, cache->delimits, &cache->buffer_file);

          if (F_status_is_error(status)) {
            controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_fss_apply_delimit", F_true);
          }
        }
      }
    }

    if (F_status_is_error_not(status) && cache->object_items.used) {
      status = controller_rule_items_increase_by(cache->object_items.used, &rule->items);

      if (F_status_is_error(status)) {
        controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "controller_rule_items_increase_by", F_true);
      }
      else {
        f_number_unsigned_t i = 0;
        f_number_unsigned_t j = 0;
        f_state_t state = f_state_t_initialize;

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

          status = f_fss_count_lines(cache->buffer_file, cache->object_items.array[i].start, &cache->action.line_item, &global.main->setting.state);

          if (F_status_is_error(status)) {
            controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_fss_count_lines", F_true);

            break;
          }

          rule->items.array[rule->items.used].line = ++cache->action.line_item;

          status = f_rip_dynamic_partial_nulless(cache->buffer_file, cache->object_items.array[i], &cache->action.name_item);

          if (F_status_is_error(status)) {
            controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_rip_dynamic_partial_nulless", F_true);

            break;
          }

          if (f_compare_dynamic(controller_settings_s, cache->action.name_item) == F_equal_to) {
            rule->items.array[rule->items.used].type = 0;
          }
          else if (f_compare_dynamic(controller_command_s, cache->action.name_item) == F_equal_to) {
            rule->items.array[rule->items.used].type = controller_rule_item_type_command_e;
          }
          else if (f_compare_dynamic(controller_script_s, cache->action.name_item) == F_equal_to) {
            rule->items.array[rule->items.used].type = controller_rule_item_type_script_e;
          }
          else if (f_compare_dynamic(controller_service_s, cache->action.name_item) == F_equal_to) {
            rule->items.array[rule->items.used].type = controller_rule_item_type_service_e;
          }
          else if (f_compare_dynamic(controller_utility_s, cache->action.name_item) == F_equal_to) {
            rule->items.array[rule->items.used].type = controller_rule_item_type_utility_e;
          }
          else {
            if (global.main->program.warning.verbosity == f_console_verbosity_debug_e) {
              controller_lock_print(global.main->program.warning.to, global.thread);

              fl_print_format("%r%[%QUnknown rule item '%]", global.main->program.warning.to, f_string_eol_s, global.main->program.warning.context, global.main->program.warning.prefix, global.main->program.warning.context);
              fl_print_format(f_string_format_Q_single_s.string, global.main->program.warning.to, global.main->program.warning.notable, cache->action.name_item, global.main->program.warning.notable);
              fl_print_format(f_string_format_sentence_end_quote_s.string, global.main->program.warning.to, global.main->program.warning.context, global.main->program.warning.context, f_string_eol_s);

              controller_rule_print_error_cache(global.main->program.warning, cache->action, F_true);

              controller_unlock_print_flush(global.main->program.warning.to, global.thread);
            }

            continue;
          }

          status = f_string_dynamic_partial_append(cache->buffer_file, cache->content_items.array[i].array[0], &cache->buffer_item);

          if (F_status_is_error(status)) {
            controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_string_dynamic_partial_append", F_true);

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
              if (F_status_set_fine(status) == F_memory_not) break;
            }
          }
        } // for
      }
    }

    if (F_status_is_error(status)) {
      controller_rule_item_print_error(global.thread, global.main->program.error, cache->action, for_item, F_status_set_fine(status));

      rule->status[0] = controller_status_simplify_error(F_status_set_fine(status));

      return rule->status[0];
    }

    return F_okay;
  }
#endif // _di_controller_rule_read_

#ifndef _di_controller_rule_setting_read_
  f_status_t controller_rule_setting_read(const controller_global_t global, const bool is_normal, const controller_process_t setting, controller_cache_t * const cache, controller_rule_t * const rule) {

    f_status_t status = F_okay;
    f_status_t status_return = F_okay;

    f_range_t range = macro_f_range_t_initialize_2(cache->buffer_item.used);
    f_range_t range2 = f_range_t_initialize;

    controller_state_interrupt_t custom = macro_controller_state_interrupt_t_initialize_1(is_normal, global.thread);
    f_state_t state = macro_f_state_t_initialize_1(controller_common_allocation_large_d, controller_common_allocation_small_d, F_okay, 0, 0, 0, &controller_thread_signal_state_fss, 0, (void *) &custom, 0);

    status = fll_fss_extended_read(cache->buffer_item, state, &range, &cache->object_actions, &cache->content_actions, 0, 0, &cache->delimits, 0);

    if (F_status_is_error(status)) {
      controller_rule_print_error(global.thread, global.main->program.error, cache->action, F_status_set_fine(status), "fll_fss_extended_read", F_true, F_false);

      return status;
    }

    f_string_dynamic_t *setting_value = 0;
    f_string_dynamics_t *setting_values = 0;
    f_string_maps_t *setting_maps = 0;

    f_number_unsigned_t i = 0;
    f_number_unsigned_t j = 0;
    uint8_t type = 0;
    uint8_t action = 0;
    bool empty_disallow = F_true;

    // Save the current name item and line number to restore on return.
    const f_number_unsigned_t line_item = cache->action.line_item;
    const f_number_unsigned_t length_name_item = cache->action.name_item.used;

    f_char_t name_item[length_name_item];
    name_item[length_name_item] = 0;

    memcpy(name_item, cache->action.name_item.string, sizeof(f_char_t) * length_name_item);

    for (; i < cache->content_actions.used; ++i, type = 0) {

      // The name_action is used to store all setting values for a single setting.
      cache->action.name_action.used = 0;

      // The name_item is used to store the setting name.
      cache->action.name_item.used = 0;

      status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->object_actions.array[i], &cache->action.name_item);

      if (F_status_is_error(status)) {
        controller_rule_print_error(global.thread, global.main->program.error, cache->action, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, F_false);

        if (F_status_set_fine(status) == F_memory_not) {
          status_return = status;

          break;
        }

        if (F_status_is_error_not(status_return)) {
          status_return = status;
        }

        // Get the current line number within the settings item.
        cache->action.line_item = line_item;
        f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global.main->setting.state);

        cache->action.line_action = ++cache->action.line_item;

        controller_rule_item_print_error(global.thread, global.main->program.error, cache->action, F_false, F_status_set_fine(status));

        continue;
      }

      empty_disallow = F_true;

      if (f_compare_dynamic(controller_affinity_s, cache->action.name_item) == F_equal_to) {
        type = controller_rule_setting_type_affinity_e;
      }
      else if (f_compare_dynamic(controller_capability_s, cache->action.name_item) == F_equal_to) {
        type = controller_rule_setting_type_capability_e;
      }
      else if (f_compare_dynamic(controller_cgroup_s, cache->action.name_item) == F_equal_to) {
        type = controller_rule_setting_type_cgroup_e;
      }
      else if (f_compare_dynamic(controller_define_s, cache->action.name_item) == F_equal_to) {
        type = controller_rule_setting_type_define_e;
      }
      else if (f_compare_dynamic(controller_engine_s, cache->action.name_item) == F_equal_to) {
        type = controller_rule_setting_type_engine_e;
      }
      else if (f_compare_dynamic(controller_environment_s, cache->action.name_item) == F_equal_to) {
        type = controller_rule_setting_type_environment_e;
        empty_disallow = F_false;
      }
      else if (f_compare_dynamic(controller_group_s, cache->action.name_item) == F_equal_to) {
        type = controller_rule_setting_type_group_e;
      }
      else if (f_compare_dynamic(controller_limit_s, cache->action.name_item) == F_equal_to) {
        type = controller_rule_setting_type_limit_e;
      }
      else if (f_compare_dynamic(controller_name_s, cache->action.name_item) == F_equal_to) {
        type = controller_rule_setting_type_name_e;
      }
      else if (f_compare_dynamic(controller_nice_s, cache->action.name_item) == F_equal_to) {
        type = controller_rule_setting_type_nice_e;
      }
      else if (f_compare_dynamic(controller_on_s, cache->action.name_item) == F_equal_to) {
        type = controller_rule_setting_type_on_e;
      }
      else if (f_compare_dynamic(controller_parameter_s, cache->action.name_item) == F_equal_to) {
        type = controller_rule_setting_type_parameter_e;
      }
      else if (f_compare_dynamic(controller_path_s, cache->action.name_item) == F_equal_to) {
        type = controller_rule_setting_type_path_e;
      }
      else if (f_compare_dynamic(controller_scheduler_s, cache->action.name_item) == F_equal_to) {
        type = controller_rule_setting_type_scheduler_e;
      }
      else if (f_compare_dynamic(controller_timeout_s, cache->action.name_item) == F_equal_to) {
        type = controller_rule_setting_type_timeout_e;
      }
      else if (f_compare_dynamic(controller_user_s, cache->action.name_item) == F_equal_to) {
        type = controller_rule_setting_type_user_e;
      }
      else {
        if (global.main->program.warning.verbosity == f_console_verbosity_debug_e) {

          // Get the current line number within the settings item.
          cache->action.line_item = line_item;
          f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global.main->setting.state);

          cache->action.line_action = ++cache->action.line_item;

          controller_lock_print(global.main->program.warning.to, global.thread);

          fl_print_format("%r%[%QUnknown rule setting '%]", global.main->program.warning.to, f_string_eol_s, global.main->program.warning.context, global.main->program.warning.prefix, global.main->program.warning.context);
          fl_print_format(f_string_format_Q_single_s.string, global.main->program.warning.to, global.main->program.warning.notable, cache->action.name_item, global.main->program.warning.notable);
          fl_print_format(f_string_format_sentence_end_quote_s.string, global.main->program.warning.to, global.main->program.warning.context, global.main->program.warning.context, f_string_eol_s);

          controller_rule_print_error_cache(global.main->program.warning, cache->action, F_false);

          controller_unlock_print_flush(global.main->program.warning.to, global.thread);
        }

        continue;
      }

      if (cache->content_actions.array[i].used) {
        range2.start = cache->content_actions.array[i].array[0].start;
        range2.stop = cache->content_actions.array[i].array[cache->content_actions.array[i].used - 1].stop;

        status = f_string_dynamic_partial_append_nulless(cache->buffer_item, range2, &cache->action.name_action);

        if (F_status_is_error(status)) {
          controller_rule_print_error(global.thread, global.main->program.error, cache->action, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, F_false);

          // Get the current line number within the settings item.
          cache->action.line_item = line_item;
          f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global.main->setting.state);

          cache->action.line_action = ++cache->action.line_item;

          controller_rule_item_print_error(global.thread, global.main->program.error, cache->action, F_false, F_status_set_fine(status));

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
          if (global.main->program.warning.verbosity == f_console_verbosity_debug_e) {

            // Get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global.main->setting.state);

            cache->action.line_action = ++cache->action.line_item;

            controller_lock_print(global.main->program.warning.to, global.thread);

            fl_print_format("%r%[%QEmpty rule setting.%]%r", global.main->program.warning.to, f_string_eol_s, global.main->program.warning.context, global.main->program.warning.prefix, global.main->program.warning.context, f_string_eol_s);

            controller_rule_print_error_cache(global.main->program.warning, cache->action, F_false);

            controller_unlock_print_flush(global.main->program.warning.to, global.thread);
          }

          continue;
        }
      }

      if (type == controller_rule_setting_type_affinity_e) {
        if (!cache->content_actions.array[i].used) {
          controller_rule_setting_read_print_error(global.main->program.error, "requires one or more Content", i, line_item, global.thread, cache);

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        rule->affinity.used = 0;

        f_number_signed_t number = 0;

        for (j = 0; j < cache->content_actions.array[i].used; ++j, number = 0) {

          status = f_int32s_increase(controller_common_allocation_small_d, &rule->affinity);

          if (F_status_is_error(status)) {
            controller_rule_print_error(global.thread, global.main->program.error, cache->action, F_status_set_fine(status), "f_int32s_increase", F_true, F_false);

            break;
          }

          status = fl_conversion_dynamic_partial_to_signed_detect(fl_conversion_data_base_10_c, cache->buffer_item, cache->content_actions.array[i].array[j], &number);

          if (F_status_set_fine(status) == F_number_positive) {
            status = fl_conversion_dynamic_partial_to_signed_detect(fl_conversion_data_base_10_c, cache->buffer_item, controller_range_after_number_sign(cache->buffer_item, cache->content_actions.array[i].array[j]), &number);

            // Restore error on parameter problem.
            if (F_status_set_fine(status) == F_parameter) {
              status = F_status_set_error(F_number_positive);
            }
          }

          if (F_status_is_error(status)) {
            status = F_status_set_fine(status);

            if (status == F_data_not || status == F_number || status == F_number_overflow || status == F_number_underflow || status == F_number_negative || status == F_number_decimal) {
              if (status == F_number_underflow) {
                controller_rule_setting_read_print_error_with_range(global.main->program.error, " has an unsupported number", cache->content_actions.array[i].array[j], ", the number is too small for this system", i, line_item, global.thread, cache);
              }
              else if (status == F_number_overflow || status == F_number_positive) {
                controller_rule_setting_read_print_error_with_range(global.main->program.error, " has an unsupported number", cache->content_actions.array[i].array[j], ", the number is too large for this system", i, line_item, global.thread, cache);
              }
              else {
                controller_rule_setting_read_print_error_with_range(global.main->program.error, " has an invalid number", cache->content_actions.array[i].array[j], ", only whole numbers are allowed for an affinity value", i, line_item, global.thread, cache);
              }

              status = F_status_set_error(F_valid_not);

              if (F_status_is_error_not(status_return)) {
                status_return = status;
              }
            }
            else {
              controller_rule_print_error(global.thread, global.main->program.error, cache->action, F_status_set_fine(status), "fl_conversion_dynamic_partial_to_signed_detect", F_true, F_false);

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
          controller_rule_setting_read_print_error(global.main->program.error, "requires exactly two Content", i, line_item, global.thread, cache);

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

        status = f_memory_array_increase(controller_common_allocation_small_d, sizeof(f_string_map_t), (void **) &setting_maps->array, &setting_maps->used, &setting_maps->size);

        if (F_status_is_error(status)) {
          controller_rule_print_error(global.thread, global.main->program.error, cache->action, F_status_set_fine(status), "f_memory_array_increase", F_true, F_false);

          if (F_status_set_fine(status) == F_memory_not) {
            status_return = status;

            break;
          }

          if (F_status_is_error_not(status_return)) {
            status_return = status;
          }

          // Get the current line number within the settings item.
          cache->action.line_item = line_item;
          f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global.main->setting.state);

          cache->action.line_action = ++cache->action.line_item;

          controller_rule_item_print_error(global.thread, global.main->program.error, cache->action, F_false, F_status_set_fine(status));

          continue;
        }

        setting_maps->array[setting_maps->used].name.used = 0;
        setting_maps->array[setting_maps->used].value.used = 0;

        status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[0], &setting_maps->array[setting_maps->used].name);

        if (F_status_is_error(status)) {
          controller_rule_print_error(global.thread, global.main->program.error, cache->action, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, F_false);

          if (F_status_set_fine(status) == F_memory_not) {
            status_return = status;
            break;
          }

          if (F_status_is_error_not(status_return)) {
            status_return = status;
          }

          // Get the current line number within the settings item.
          cache->action.line_item = line_item;
          f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global.main->setting.state);

          cache->action.line_action = ++cache->action.line_item;

          controller_rule_item_print_error(global.thread, global.main->program.error, cache->action, F_false, F_status_set_fine(status));

          continue;
        }

        status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[1], &setting_maps->array[setting_maps->used].value);

        if (F_status_is_error(status)) {
          controller_rule_print_error(global.thread, global.main->program.error, cache->action, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, F_false);

          if (F_status_set_fine(status) == F_memory_not) {
            status_return = status;

            break;
          }

          if (F_status_is_error_not(status_return)) {
            status_return = status;
          }

          // Get the current line number within the settings item.
          cache->action.line_item = line_item;
          f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global.main->setting.state);

          cache->action.line_action = ++cache->action.line_item;

          controller_rule_item_print_error(global.thread, global.main->program.error, cache->action, F_false, F_status_set_fine(status));

          continue;
        }

        controller_rule_setting_read_print_mapping(global, type == controller_rule_setting_type_define_e ? controller_define_s : controller_parameter_s, setting_maps->array[setting_maps->used]);

        ++setting_maps->used;

        continue;
      }

      if (type == controller_rule_setting_type_cgroup_e) {
        if (cache->content_actions.array[i].used < 2 || rule->has & controller_rule_has_cgroup_d) {
          controller_rule_setting_read_print_error(global.main->program.error, "requires two or more Content", i, line_item, global.thread, cache);

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        if (f_compare_dynamic_partial_string(controller_existing_s.string, cache->buffer_item, controller_existing_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          rule->cgroup.as_new = F_false;
        }
        else if (f_compare_dynamic_partial_string(controller_new_s.string, cache->buffer_item, controller_new_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          rule->cgroup.as_new = F_true;
        }
        else {
          controller_rule_setting_read_print_error_with_range(global.main->program.error, " has an unknown option", cache->content_actions.array[i].array[0], "", i, line_item, global.thread, cache);

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        rule->cgroup.path.used = 0;

        status = f_string_dynamic_append(global.setting->path_cgroup, &rule->cgroup.path);

        if (F_status_is_error(status)) {
          controller_rule_print_error(global.thread, global.main->program.error, cache->action, F_status_set_fine(status), "f_string_dynamic_append", F_true, F_false);
        }
        else {
          rule->cgroup.groups.used = 0;

          for (j = 1; j < cache->content_actions.array[i].used; ++j) {

            status = f_memory_array_increase(controller_common_allocation_small_d, sizeof(f_string_dynamic_t), (void **) &rule->cgroup.groups.array, &rule->cgroup.groups.used, &rule->cgroup.groups.size);

            if (F_status_is_error(status)) {
              controller_rule_print_error(global.thread, global.main->program.error, cache->action, F_status_set_fine(status), "f_memory_array_increase", F_true, F_false);

              break;
            }

            rule->cgroup.groups.array[rule->cgroup.groups.used].used = 0;

            status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[j], &rule->cgroup.groups.array[rule->cgroup.groups.used]);

            if (F_status_is_error(status)) {
              controller_rule_print_error(global.thread, global.main->program.error, cache->action, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, F_false);
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

          // Get the current line number within the settings item.
          cache->action.line_item = line_item;
          f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global.main->setting.state);

          cache->action.line_action = ++cache->action.line_item;

          controller_rule_item_print_error(global.thread, global.main->program.error, cache->action, F_false, F_status_set_fine(status));

          continue;
        }

        rule->has |= controller_rule_has_cgroup_d;

        controller_rule_setting_read_print_values(global, controller_cgroup_s, i, cache);

        continue;
      }

      if (type == controller_rule_setting_type_limit_e) {
        if (cache->content_actions.array[i].used != 3) {
          controller_rule_setting_read_print_error(global.main->program.error, "requires three Content", i, line_item, global.thread, cache);

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        if (f_compare_dynamic_partial_string(controller_as_s.string, cache->buffer_item, controller_as_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_as_e;
        }
        else if (f_compare_dynamic_partial_string(controller_core_s.string, cache->buffer_item, controller_core_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_core_e;
        }
        else if (f_compare_dynamic_partial_string(controller_cpu_s.string, cache->buffer_item, controller_cpu_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_cpu_e;
        }
        else if (f_compare_dynamic_partial_string(controller_data_s.string, cache->buffer_item, controller_data_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_data_e;
        }
        else if (f_compare_dynamic_partial_string(controller_fsize_s.string, cache->buffer_item, controller_fsize_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_fsize_e;
        }
        else if (f_compare_dynamic_partial_string(controller_locks_s.string, cache->buffer_item, controller_locks_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_locks_e;
        }
        else if (f_compare_dynamic_partial_string(controller_memlock_s.string, cache->buffer_item, controller_memlock_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_memlock_e;
        }
        else if (f_compare_dynamic_partial_string(controller_msgqueue_s.string, cache->buffer_item, controller_msgqueue_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_msgqueue_e;
        }
        else if (f_compare_dynamic_partial_string(controller_nice_s.string, cache->buffer_item, controller_nice_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_nice_e;
        }
        else if (f_compare_dynamic_partial_string(controller_nofile_s.string, cache->buffer_item, controller_nofile_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_nofile_e;
        }
        else if (f_compare_dynamic_partial_string(controller_nproc_s.string, cache->buffer_item, controller_nproc_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_nproc_e;
        }
        else if (f_compare_dynamic_partial_string(controller_rss_s.string, cache->buffer_item, controller_rss_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_rss_e;
        }
        else if (f_compare_dynamic_partial_string(controller_rtprio_s.string, cache->buffer_item, controller_rtprio_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_rtprio_e;
        }
        else if (f_compare_dynamic_partial_string(controller_rttime_s.string, cache->buffer_item, controller_rttime_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_rttime_e;
        }
        else if (f_compare_dynamic_partial_string(controller_sigpending_s.string, cache->buffer_item, controller_sigpending_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_sigpending_e;
        }
        else if (f_compare_dynamic_partial_string(controller_stack_s.string, cache->buffer_item, controller_stack_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_stack_e;
        }
        else {
          if (global.main->program.error.verbosity == f_console_verbosity_debug_e) {

            // Get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global.main->setting.state);

            cache->action.line_action = ++cache->action.line_item;

            controller_lock_print(global.main->program.error.to, global.thread);

            fl_print_format("%r%[%QUnknown resource limit type '%]", global.main->program.error.to, f_string_eol_s, global.main->program.error.context, global.main->program.error.prefix, global.main->program.error.context);
            fl_print_format(f_string_format_Q_single_s.string, global.main->program.error.to, global.main->program.error.notable, cache->action.name_action, global.main->program.error.notable);
            fl_print_format(f_string_format_sentence_end_quote_s.string, global.main->program.error.to, global.main->program.error.context, global.main->program.error.context, f_string_eol_s);

            controller_rule_print_error_cache(global.main->program.error, cache->action, F_true);

            controller_unlock_print_flush(global.main->program.error.to, global.thread);
          }

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        for (j = 0; j < rule->limits.used; ++j) {

          if (type == rule->limits.array[j].type) {
            if (global.main->program.error.verbosity > f_console_verbosity_quiet_e) {

              // Get the current line number within the settings item.
              cache->action.line_item = line_item;
              f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global.main->setting.state);

              cache->action.line_action = ++cache->action.line_item;

              controller_lock_print(global.main->program.error.to, global.thread);

              fl_print_format("%r%[%QThe resource limit type is already specified%]%r", global.main->program.error.to, f_string_eol_s, global.main->program.error.context, global.main->program.error.prefix, global.main->program.error.context, f_string_eol_s);

              controller_rule_print_error_cache(global.main->program.error, cache->action, F_false);

              controller_unlock_print_flush(global.main->program.error.to, global.thread);
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
          controller_rule_print_error(global.thread, global.main->program.error, cache->action, F_status_set_fine(status), "f_limit_sets_increase", F_true, F_false);

          if (F_status_set_fine(status) == F_memory_not) {
            status_return = status;

            break;
          }

          if (F_status_is_error_not(status_return)) {
            status_return = status;
          }

          // Get the current line number within the settings item.
          cache->action.line_item = line_item;
          f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global.main->setting.state);

          cache->action.line_action = ++cache->action.line_item;

          controller_rule_item_print_error(global.thread, global.main->program.error, cache->action, F_false, F_status_set_fine(status));

          continue;
        }

        f_number_signed_t number = 0;

        for (j = 1; j < 3; ++j, number = 0) {

          status = fl_conversion_dynamic_partial_to_signed_detect(fl_conversion_data_base_10_c, cache->buffer_item, cache->content_actions.array[i].array[j], &number);

          if (F_status_set_fine(status) == F_number_positive) {
            status = fl_conversion_dynamic_partial_to_signed_detect(fl_conversion_data_base_10_c, cache->buffer_item, controller_range_after_number_sign(cache->buffer_item, cache->content_actions.array[i].array[j]), &number);

            // Restore error on parameter problem.
            if (F_status_set_fine(status) == F_parameter) {
              status = F_status_set_error(F_number_positive);
            }
          }

          if (F_status_is_error(status)) {
            status = F_status_set_fine(status);

            if (status == F_data_not || status == F_number || status == F_number_overflow || status == F_number_underflow || status == F_number_negative || status == F_number_positive || status == F_number_decimal) {
              if (status == F_number_underflow) {
                controller_rule_setting_read_print_error_with_range(global.main->program.error, " has an unsupported number", cache->content_actions.array[i].array[j], ", the number is too small for this system", i, line_item, global.thread, cache);
              }
              else if (status == F_number_overflow) {
                controller_rule_setting_read_print_error_with_range(global.main->program.error, " has an unsupported number", cache->content_actions.array[i].array[j], ", the number is too large for this system", i, line_item, global.thread, cache);
              }
              else {
                controller_rule_setting_read_print_error_with_range(global.main->program.error, " has an unsupported number", cache->content_actions.array[i].array[j], ", only whole numbers are allowed for a resource limit value", i, line_item, global.thread, cache);
              }

              status = F_status_set_error(F_valid_not);

              if (F_status_is_error_not(status_return)) {
                status_return = status;
              }
            }
            else {
              controller_rule_print_error(global.thread, global.main->program.error, cache->action, F_status_set_fine(status), "fl_conversion_dynamic_partial_to_signed_detect", F_true, F_false);

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

      if (type == controller_rule_setting_type_name_e || type == controller_rule_setting_type_path_e || type == controller_rule_setting_type_engine_e) {

        if (type == controller_rule_setting_type_name_e) {
          setting_value = &rule->name;
        }
        else if (type == controller_rule_setting_type_path_e) {
          setting_value = &rule->path;
        }
        else if (type == controller_rule_setting_type_engine_e) {
          setting_value = &rule->engine;
        }

        if (setting_value->used || !cache->content_actions.array[i].used) {
          controller_rule_setting_read_print_error(global.main->program.error, "requires one or more Content", i, line_item, global.thread, cache);

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        if (type == controller_rule_setting_type_name_e || type == controller_rule_setting_type_engine_e) {
          status = f_rip_dynamic_partial_nulless(cache->buffer_item, cache->content_actions.array[i].array[0], setting_value);

          if (type == controller_rule_setting_type_engine_e) {
            rule->engine_arguments.used = 0;

            if (cache->content_actions.array[i].used > 1) {
              status = f_memory_array_increase_by(cache->content_actions.array[i].used - 1, sizeof(f_string_dynamic_t), (void **) &rule->engine_arguments.array, &rule->engine_arguments.used, &rule->engine_arguments.size);

              for (j = 1; F_status_is_error_not(status) && j < cache->content_actions.array[i].used; ++j, ++rule->engine_arguments.used) {

                rule->engine_arguments.array[rule->engine_arguments.used].used = 0;

                status = f_string_dynamic_partial_append(cache->buffer_item, cache->content_actions.array[i].array[j], &rule->engine_arguments.array[rule->engine_arguments.used]);
              } // for
            }
          }

          if (F_status_is_error(status)) {
            setting_value->used = 0;

            if (type == controller_rule_setting_type_engine_e) {
              rule->engine_arguments.used = 0;
            }

            if (F_status_set_fine(status) == F_memory_not) {
              status_return = status;

              break;
            }

            if (F_status_is_error_not(status_return)) {
              status_return = status;
            }

            // Get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global.main->setting.state);

            cache->action.line_action = ++cache->action.line_item;

            controller_rule_item_print_error(global.thread, global.main->program.error, cache->action, F_false, F_status_set_fine(status));

            continue;
          }

          status = controller_validate_has_graph(*setting_value);

          if (status == F_false || F_status_set_fine(status) == F_complete_not_utf) {
            if (global.main->program.error.verbosity > f_console_verbosity_quiet_e) {

              // Get the current line number within the settings item.
              cache->action.line_item = line_item;
              f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global.main->setting.state);

              cache->action.line_action = ++cache->action.line_item;
            }

            if (status == F_false) {
              if (global.main->program.error.verbosity > f_console_verbosity_quiet_e) {
                controller_lock_print(global.main->program.error.to, global.thread);

                fl_print_format("%r%[%QRule setting has an invalid name '%]", global.main->program.error.to, f_string_eol_s, global.main->program.error.context, global.main->program.error.prefix, global.main->program.error.context);
                fl_print_format(f_string_format_Q_single_s.string, global.main->program.error.to, global.main->program.error.notable, *setting_value, global.main->program.error.notable);
                fl_print_format("%[', there must be at least 1 graph character.%]%r", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context, f_string_eol_s);

                controller_rule_print_error_cache(global.main->program.error, cache->action, F_false);

                controller_unlock_print_flush(global.main->program.error.to, global.thread);
              }

              if (F_status_is_error_not(status_return)) {
                status_return = F_status_set_error(F_valid_not);
              }
            }
            else {

              // This function should only return F_complete_not_utf on error.
              controller_rule_print_error(global.thread, global.main->program.error, cache->action, F_complete_not_utf, "controller_validate_has_graph", F_true, F_false);

              if (F_status_is_error_not(status_return)) {
                status_return = status;
              }

              controller_rule_item_print_error(global.thread, global.main->program.error, cache->action, F_false, F_status_set_fine(status));
            }

            setting_value->used = 0;

            continue;
          }

          controller_rule_setting_read_print_value(global, type == controller_rule_setting_type_name_e ? controller_name_s : controller_engine_s, f_string_empty_s, *setting_value, 0);
        }
        else if (type == controller_rule_setting_type_path_e) {
          status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[0], setting_value);

          if (F_status_is_error(status)) {
            controller_rule_print_error(global.thread, global.main->program.error, cache->action, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, F_false);

            if (F_status_set_fine(status) == F_memory_not) {
              status_return = status;

              break;
            }

            if (F_status_is_error_not(status_return)) {
              status_return = status;
            }

            setting_value->used = 0;

            // Get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global.main->setting.state);

            cache->action.line_action = ++cache->action.line_item;

            controller_rule_item_print_error(global.thread, global.main->program.error, cache->action, F_false, F_status_set_fine(status));

            continue;
          }

          controller_rule_setting_read_print_value(global, controller_path_s, f_string_empty_s, *setting_value, 0);
        }

        continue;
      }

      if (type == controller_rule_setting_type_scheduler_e) {
        if (cache->content_actions.array[i].used < 1 || cache->content_actions.array[i].used > 2 || rule->has & controller_rule_has_scheduler_d) {
          controller_rule_setting_read_print_error(global.main->program.error, "requires either one or two Content", i, line_item, global.thread, cache);

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        if (f_compare_dynamic_partial_string(controller_batch_s.string, cache->buffer_item, controller_batch_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          rule->scheduler.policy = SCHED_BATCH;
          rule->scheduler.priority = 0;
        }
        else if (f_compare_dynamic_partial_string(controller_deadline_s.string, cache->buffer_item, controller_deadline_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          rule->scheduler.policy = SCHED_DEADLINE;
          rule->scheduler.priority = 49;
        }
        else if (f_compare_dynamic_partial_string(controller_fifo_s.string, cache->buffer_item, controller_fifo_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          rule->scheduler.policy = SCHED_FIFO;
          rule->scheduler.priority = 49;
        }
        else if (f_compare_dynamic_partial_string(controller_idle_s.string, cache->buffer_item, controller_idle_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          rule->scheduler.policy = SCHED_IDLE;
          rule->scheduler.priority = 0;
        }
        else if (f_compare_dynamic_partial_string(controller_other_s.string, cache->buffer_item, controller_other_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          rule->scheduler.policy = SCHED_OTHER;
          rule->scheduler.priority = 0;
        }
        else if (f_compare_dynamic_partial_string(controller_round_robin_s.string, cache->buffer_item, controller_round_robin_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          rule->scheduler.policy = SCHED_RR;
          rule->scheduler.priority = 49;
        }
        else {
          controller_rule_setting_read_print_error_with_range(global.main->program.error, " has an unknown scheduler", cache->content_actions.array[i].array[0], "", i, line_item, global.thread, cache);

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        if (cache->content_actions.array[i].used > 1) {
          const bool zero_only = rule->scheduler.policy == SCHED_BATCH || rule->scheduler.policy == SCHED_IDLE || rule->scheduler.policy == SCHED_OTHER;

          f_number_signed_t number = 0;

          status = fl_conversion_dynamic_partial_to_signed_detect(fl_conversion_data_base_10_c, cache->buffer_item, cache->content_actions.array[i].array[1], &number);

          if (F_status_set_fine(status) == F_number_positive) {
            status = fl_conversion_dynamic_partial_to_signed_detect(fl_conversion_data_base_10_c, cache->buffer_item, controller_range_after_number_sign(cache->buffer_item, cache->content_actions.array[i].array[1]), &number);

            // Restore error on parameter problem.
            if (F_status_set_fine(status) == F_parameter) {
              status = F_status_set_error(F_number_positive);
            }
          }

          if (F_status_is_error(status) || (zero_only && number) || (!zero_only && (number < 1 || number > 99))) {
            status = F_status_set_fine(status);

            if ((zero_only && number) || (!zero_only && (number < 1 || number > 99)) || status == F_data_not || status == F_number || status == F_number_overflow || status == F_number_negative || status == F_number_positive) {
              if (global.main->program.error.verbosity > f_console_verbosity_quiet_e) {

                // Get the current line number within the settings item.
                cache->action.line_item = line_item;
                f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global.main->setting.state);

                cache->action.line_action = ++cache->action.line_item;

                controller_lock_print(global.main->program.error.to, global.thread);

                fl_print_format("%r%[%QRule setting has an invalid number '%]", global.main->program.error.to, f_string_eol_s, global.main->program.error.context, global.main->program.error.prefix, global.main->program.error.context);
                fl_print_format(f_string_format_Q_range_single_s.string, global.main->program.error.to, global.main->program.error.notable, cache->buffer_item, cache->content_actions.array[i].array[1], global.main->program.error.notable);

                if (zero_only) {
                  fl_print_format("%[', only%] ", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context);
                  fl_print_format("%[0%]%[ is", global.main->program.error.to, global.main->program.error.notable, global.main->program.error.notable, global.main->program.error.context);
                }
                else {
                  fl_print_format("%[', only the whole numbers inclusively between%] ", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context);
                  fl_print_format("%[1%] %[and%] ", global.main->program.error.to, global.main->program.error.notable, global.main->program.error.notable, global.main->program.error.context, global.main->program.error.context);
                  fl_print_format("%[99%] %[are", global.main->program.error.to, global.main->program.error.notable, global.main->program.error.notable, global.main->program.error.context);
                }

                fl_print_format(" allowed for the designated scheduler.%]%r", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context, f_string_eol_s);

                controller_rule_print_error_cache(global.main->program.error, cache->action, F_false);

                controller_unlock_print_flush(global.main->program.error.to, global.thread);
              }

              if (F_status_is_error_not(status_return)) {
                status_return = F_status_set_error(F_valid_not);
              }
            }
            else {
              controller_rule_print_error(global.thread, global.main->program.error, cache->action, status, "fl_conversion_dynamic_partial_to_signed_detect", F_true, F_false);
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
          controller_rule_setting_read_print_error(global.main->program.error, "requires exactly two Content", i, line_item, global.thread, cache);

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        uint8_t timeout_code = 0;

        if (f_compare_dynamic_partial_string(controller_kill_s.string, cache->buffer_item, controller_kill_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          timeout_code = controller_rule_timeout_code_kill_d;
        }
        else if (f_compare_dynamic_partial_string(controller_start_s.string, cache->buffer_item, controller_start_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          timeout_code = controller_rule_timeout_code_start_d;
        }
        else if (f_compare_dynamic_partial_string(controller_stop_s.string, cache->buffer_item, controller_stop_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
          timeout_code = controller_rule_timeout_code_stop_d;
        }
        else {
          if (global.main->program.error.verbosity > f_console_verbosity_quiet_e) {

            // Get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global.main->setting.state);

            cache->action.line_action = ++cache->action.line_item;

            controller_lock_print(global.main->program.error.to, global.thread);

            fl_print_format("%r%[%QRule setting's first value has '%]", global.main->program.error.to, f_string_eol_s, global.main->program.error.context, global.main->program.error.prefix, global.main->program.error.context);
            fl_print_format(f_string_format_Q_range_single_s.string, global.main->program.error.to, global.main->program.error.notable, cache->buffer_item, cache->content_actions.array[i].array[0], global.main->program.error.notable);
            fl_print_format("%[' but only supports %r, %r, and %r.%]%r", global.main->program.error.to, global.main->program.error.context, controller_kill_s, controller_start_s, controller_stop_s, global.main->program.error.context, f_string_eol_s);

            controller_rule_print_error_cache(global.main->program.error, cache->action, F_false);

            controller_unlock_print_flush(global.main->program.error.to, global.thread);
          }

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        f_number_unsigned_t number = 0;

        status = fl_conversion_dynamic_partial_to_unsigned_detect(fl_conversion_data_base_10_c, cache->buffer_item, cache->content_actions.array[i].array[1], &number);

        if (F_status_set_fine(status) == F_number_positive) {
          status = fl_conversion_dynamic_partial_to_unsigned_detect(fl_conversion_data_base_10_c, cache->buffer_item, controller_range_after_number_sign(cache->buffer_item, cache->content_actions.array[i].array[1]), &number);

          // Restore error on parameter problem.
          if (F_status_set_fine(status) == F_parameter) {
            status = F_status_set_error(F_number_positive);
          }
        }

        if (F_status_is_error(status)) {
          status = F_status_set_fine(status);

          if (status == F_number_overflow) {
            controller_rule_setting_read_print_error_with_range(global.main->program.error, " has an unsupported number", cache->content_actions.array[i].array[1], ", the number is too large for this system", i, line_item, global.thread, cache);
          }
          else if (status == F_data_not || status == F_number || status == F_number_underflow || status == F_number_negative || status == F_number_positive || status == F_number_decimal) {
            controller_rule_setting_read_print_error_with_range(global.main->program.error, " has an invalid number", cache->content_actions.array[i].array[1], ", only positive whole numbers are allowed", i, line_item, global.thread, cache);
          }
          else {

            // Get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global.main->setting.state);

            cache->action.line_action = ++cache->action.line_item;

            controller_rule_print_error(global.thread, global.main->program.error, cache->action, status, "fl_conversion_dynamic_partial_to_signed_detect", F_true, F_false);
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

          if (global.main->program.error.verbosity == f_console_verbosity_debug_e || (global.main->program.error.verbosity == f_console_verbosity_verbose_e && (global.main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e))) {
            f_string_static_t name_sub = controller_stop_s;

            if (timeout_code == controller_rule_timeout_code_kill_d) {
              name_sub = controller_kill_s;
            }
            else if (timeout_code == controller_rule_timeout_code_start_d) {
              name_sub = controller_start_s;
            }

            cache->action.generic.used = 0;

            status = f_rip_dynamic_partial_nulless(cache->buffer_item, cache->content_actions.array[i].array[1], &cache->action.generic);

            if (F_status_is_error(status)) {
              controller_print_error(global.thread, global.main->program.error, F_status_set_fine(status), "f_rip_dynamic_partial_nulless", F_true);

              break;
            }

            controller_rule_setting_read_print_value(global, controller_timeout_s, name_sub, cache->action.generic, 0);
          }
        }

        continue;
      }

      if (type == controller_rule_setting_type_capability_e || type == controller_rule_setting_type_nice_e || type == controller_rule_setting_type_user_e) {
        if (cache->content_actions.array[i].used != 1 || type == controller_rule_setting_type_capability_e && rule->capability || type == controller_rule_setting_type_group_e && (rule->has & controller_rule_has_group_d) || type == controller_rule_setting_type_nice_e && (rule->has & controller_rule_has_nice_d) || type == controller_rule_setting_type_user_e && (rule->has & controller_rule_has_user_d)) {
          controller_rule_setting_read_print_error(global.main->program.error, "requires exactly one Content", i, line_item, global.thread, cache);

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
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global.main->setting.state);

            cache->action.line_action = ++cache->action.line_item;

            controller_lock_print(global.main->program.error.to, global.thread);

            controller_rule_print_error(global.thread, global.main->program.error, cache->action, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, F_false);

            controller_rule_print_error_cache(global.main->program.error, cache->action, F_false);

            controller_unlock_print_flush(global.main->program.error.to, global.thread);

            if (F_status_set_fine(status) == F_memory_not) {
              status_return = status;

              break;
            }

            if (F_status_is_error_not(status_return)) {
              status_return = F_status_set_error(F_valid_not);
            }
          }

          status = f_capability_from_text(cache->action.generic, &rule->capability);

          if (F_status_is_error(status) && F_status_set_fine(status) != F_support_not) {
            if (F_status_set_fine(status) == F_memory_not) {

              // Get the current line number within the settings item.
              cache->action.line_item = line_item;
              f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global.main->setting.state);

              cache->action.line_action = ++cache->action.line_item;

              controller_lock_print(global.main->program.error.to, global.thread);

              controller_rule_print_error(global.thread, global.main->program.error, cache->action, F_status_set_fine(status), "f_capability_from_text", F_true, F_false);

              controller_rule_print_error_cache(global.main->program.error, cache->action, F_false);

              controller_unlock_print_flush(global.main->program.error.to, global.thread);

              status_return = status;

              break;
            }

            controller_rule_setting_read_print_error(global.main->program.error, "failed to process the capabilities", i, line_item, global.thread, cache);

            if (F_status_is_error_not(status_return)) {
              status_return = F_status_set_error(F_valid_not);
            }

            continue;
          }

          controller_rule_setting_read_print_value(global, controller_capability_s, f_string_empty_s, cache->action.generic, 0);
        }
        else if (type == controller_rule_setting_type_nice_e) {
          f_number_signed_t number = 0;

          status = fl_conversion_dynamic_partial_to_signed_detect(fl_conversion_data_base_10_c, cache->buffer_item, cache->content_actions.array[i].array[0], &number);

          if (F_status_set_fine(status) == F_number_positive) {
            status = fl_conversion_dynamic_partial_to_signed_detect(fl_conversion_data_base_10_c, cache->buffer_item, controller_range_after_number_sign(cache->buffer_item, cache->content_actions.array[i].array[0]), &number);

            // Restore error on parameter problem.
            if (F_status_set_fine(status) == F_parameter) {
              status = F_status_set_error(F_number_positive);
            }
          }

          if (F_status_is_error(status) || number < -20 || number > 19) {
            status = F_status_set_fine(status);

            if (number < -20 || number > 19 || status == F_data_not || status == F_number || status == F_number_overflow || status == F_number_underflow || status == F_number_decimal) {
              if (global.main->program.error.verbosity > f_console_verbosity_quiet_e) {

                // Get the current line number within the settings item.
                cache->action.line_item = line_item;
                f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global.main->setting.state);

                cache->action.line_action = ++cache->action.line_item;

                controller_lock_print(global.main->program.error.to, global.thread);

                fl_print_format("%r%[%QRule setting has an invalid number '%]", global.main->program.error.to, f_string_eol_s, global.main->program.error.context, global.main->program.error.prefix, global.main->program.error.context);
                fl_print_format(f_string_format_Q_range_single_s.string, global.main->program.error.to, global.main->program.error.notable, cache->buffer_item, cache->content_actions.array[i].array[0], global.main->program.error.notable);
                fl_print_format("%[', only the whole numbers inclusively between%] ", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context);
                fl_print_format("%[-20%]", global.main->program.error.to, global.main->program.error.notable, global.main->program.error.notable);
                fl_print_format(" %[and%] ", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context);
                fl_print_format("%[19%]", global.main->program.error.to, global.main->program.error.notable, global.main->program.error.notable);
                fl_print_format(" %[are allowed.%]%r", global.main->program.error.to, global.main->program.error.context, global.main->program.error.context, f_string_eol_s);

                controller_rule_print_error_cache(global.main->program.error, cache->action, F_false);

                controller_unlock_print_flush(global.main->program.error.to, global.thread);
              }

              if (F_status_is_error_not(status_return)) {
                status_return = F_status_set_error(F_valid_not);
              }
            }
            else {
              controller_rule_print_error(global.thread, global.main->program.error, cache->action, status, "fl_conversion_dynamic_partial_to_signed_detect", F_true, F_false);
              status = F_status_set_error(status);

              if (F_status_is_error_not(status_return)) {
                status_return = status;
              }
            }
          }
          else {
            rule->nice = number;
            rule->has |= controller_rule_has_nice_d;

            if ((global.main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e) || global.main->program.error.verbosity == f_console_verbosity_verbose_e) {
              cache->action.generic.used = 0;

              status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[0], &cache->action.generic);

              if (F_status_is_error(status)) {

                // Get the current line number within the settings item.
                cache->action.line_item = line_item;
                f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global.main->setting.state);

                cache->action.line_action = ++cache->action.line_item;

                controller_lock_print(global.main->program.error.to, global.thread);

                controller_rule_print_error(global.thread, global.main->program.error, cache->action, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, F_false);

                controller_rule_print_error_cache(global.main->program.error, cache->action, F_false);

                controller_unlock_print_flush(global.main->program.error.to, global.thread);

                if (F_status_set_fine(status) == F_memory_not) {
                  status_return = status;

                  break;
                }

                if (F_status_is_error_not(status_return)) {
                  status_return = F_status_set_error(F_valid_not);
                }
              }

              if (F_status_is_error_not(status)) {
                controller_rule_setting_read_print_value(global, controller_nice_s, f_string_empty_s, cache->action.generic, 0);
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
              controller_rule_setting_read_print_error_with_range(global.main->program.error, " has an invalid user", cache->content_actions.array[i].array[0], ", because no user was found by that name", i, line_item, global.thread, cache);
            }
            else if (status == F_number_too_large) {
              controller_rule_setting_read_print_error_with_range(global.main->program.error, " has an invalid user", cache->content_actions.array[i].array[0], ", because the given ID is too large", i, line_item, global.thread, cache);
            }
            else if (status == F_number) {
              controller_rule_setting_read_print_error_with_range(global.main->program.error, " has an invalid user", cache->content_actions.array[i].array[0], ", because the given ID is not a valid supported number", i, line_item, global.thread, cache);
            }
            else {

              // Get the current line number within the settings item.
              cache->action.line_item = line_item;
              f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global.main->setting.state);

              cache->action.line_action = ++cache->action.line_item;

              controller_rule_print_error(global.thread, global.main->program.error, cache->action, status, "controller_get_id_user", F_true, F_false);

              controller_rule_item_print_error(global.thread, global.main->program.error, cache->action, F_false, F_status_set_fine(status));
            }

            if (F_status_is_error_not(status_return)) {
              status_return = F_status_set_error(status);
            }
          }
          else {
            rule->user = number;
            rule->has |= controller_rule_has_user_d;

            if (global.main->program.error.verbosity == f_console_verbosity_debug_e || (global.main->program.error.verbosity == f_console_verbosity_verbose_e && (global.main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e))) {
              cache->action.generic.used = 0;

              status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[0], &cache->action.generic);

              controller_rule_setting_read_print_value(global, controller_user_s, f_string_empty_s, cache->action.generic, 0);
            }
          }
        }

        continue;
      }

      if (type == controller_rule_setting_type_group_e) {
        if (!cache->content_actions.array[i].used) {
          controller_rule_setting_read_print_error(global.main->program.error, "requires one or more Content", i, line_item, global.thread, cache);

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        gid_t number = 0;

        rule->groups.used = 0;

        for (j = 0; j < cache->content_actions.array[i].used; ++j) {

          macro_f_int32s_t_increase_by(status, rule->groups, controller_common_allocation_small_d);

          if (F_status_is_error(status)) {
            controller_rule_print_error(global.thread, global.main->program.error, cache->action, F_status_set_fine(status), "macro_f_number_unsigneds_t_increase_by", F_true, F_false);

            if (F_status_set_fine(status) == F_memory_not) {
              status_return = status;

              break;
            }

            if (F_status_is_error_not(status_return)) {
              status_return = status;
            }

            // Get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global.main->setting.state);

            cache->action.line_action = ++cache->action.line_item;

            controller_rule_item_print_error(global.thread, global.main->program.error, cache->action, F_false, F_status_set_fine(status));

            continue;
          }

          status = controller_get_id_group(cache->buffer_item, cache->content_actions.array[i].array[j], cache, &number);

          if (F_status_is_error(status)) {
            status = F_status_set_fine(status);

            if (status == F_exist_not) {
              controller_rule_setting_read_print_error_with_range(global.main->program.error, " has an invalid group", cache->content_actions.array[i].array[j], ", because no group was found by that name", i, line_item, global.thread, cache);
            }
            else if (status == F_number_too_large) {
              controller_rule_setting_read_print_error_with_range(global.main->program.error, " has an invalid group", cache->content_actions.array[i].array[j], ", because the given ID is too large", i, line_item, global.thread, cache);
            }
            else if (status == F_number) {
              controller_rule_setting_read_print_error_with_range(global.main->program.error, " has an invalid group", cache->content_actions.array[i].array[j], ", because the given ID is not a valid supported number", i, line_item, global.thread, cache);
            }
            else {

              // Get the current line number within the settings item.
              cache->action.line_item = line_item;
              f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global.main->setting.state);

              cache->action.line_action = ++cache->action.line_item;

              controller_rule_print_error(global.thread, global.main->program.error, cache->action, status, "f_account_group_id_by_name", F_true, F_false);

              controller_rule_item_print_error(global.thread, global.main->program.error, cache->action, F_false, F_status_set_fine(status));
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

          status = f_memory_array_increase(controller_common_allocation_small_d, sizeof(f_string_dynamic_t), (void **) &setting_values.array, &setting_values.used, &setting_values.size);

          if (F_status_is_error(status)) {
            controller_rule_print_error(global.thread, global.main->program.error, cache->action, F_status_set_fine(status), "f_memory_array_increase", F_true, F_false);

            if (F_status_set_fine(status) == F_memory_not) {
              status_return = status;

              break;
            }

            if (F_status_is_error_not(status_return)) {
              status_return = status;
            }

            // Get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global.main->setting.state);

            cache->action.line_action = ++cache->action.line_item;

            controller_rule_item_print_error(global.thread, global.main->program.error, cache->action, F_false, F_status_set_fine(status));

            continue;
          }

          setting_values->array[setting_values->used].used = 0;

          status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[j], &setting_values->array[setting_values->used]);

          if (F_status_is_error(status)) {
            controller_rule_print_error(global.thread, global.main->program.error, cache->action, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, F_false);

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
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global.main->setting.state);

            cache->action.line_action = ++cache->action.line_item;

            controller_rule_item_print_error(global.thread, global.main->program.error, cache->action, F_false, F_status_set_fine(status));

            continue;
          }

          status = controller_validate_environment_name(setting_values->array[setting_values->used]);

          if (status == F_false || F_status_set_fine(status) == F_complete_not_utf) {

            // Get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global.main->setting.state);

            cache->action.line_action = ++cache->action.line_item;

            if (status == F_false) {
              if (global.main->program.error.verbosity > f_console_verbosity_quiet_e) {
                controller_lock_print(global.main->program.error.to, global.thread);

                fl_print_format("%r%[%QRule setting has an invalid environment variable name '%]", global.main->program.error.to, f_string_eol_s, global.main->program.error.context, global.main->program.error.prefix, global.main->program.error.context);
                fl_print_format(f_string_format_Q_single_s.string, global.main->program.error.to, global.main->program.error.notable, setting_values->array[setting_values->used], global.main->program.error.notable);
                fl_print_format(f_string_format_sentence_end_quote_s.string, global.main->program.error.to, global.main->program.error.context, global.main->program.error.context, f_string_eol_s);

                controller_rule_print_error_cache(global.main->program.error, cache->action, F_false);

                controller_unlock_print_flush(global.main->program.error.to, global.thread);
              }

              if (F_status_is_error_not(status_return)) {
                status_return = F_status_set_error(F_valid_not);
              }
            }
            else {

              // This function should only return F_complete_not_utf on error.
              controller_rule_print_error(global.thread, global.main->program.error, cache->action, F_complete_not_utf, "controller_validate_environment_name", F_true, F_false);

              if (F_status_is_error_not(status_return)) {
                status_return = status;
              }
            }

            setting_values->array[setting_values->used].used = 0;

            controller_rule_item_print_error(global.thread, global.main->program.error, cache->action, F_false, F_status_set_fine(status));

            continue;
          }

          ++setting_values->used;
        } // for

        rule->has |= controller_rule_has_environment_d;

        if (cache->content_actions.array[i].used) {
          controller_rule_setting_read_print_values(global, controller_environment_s, i, cache);
        }
        else {
          if (global.main->program.error.verbosity == f_console_verbosity_debug_e || (global.main->program.error.verbosity == f_console_verbosity_verbose_e && (global.main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e))) {
            controller_lock_print(global.main->program.output.to, global.thread);

            fl_print_format("%rProcessing rule item action '%[%r%]' setting value to an empty set.%r", global.main->program.output.to, f_string_eol_s, global.main->program.context.set.title, controller_environment_s, global.main->program.context.set.title, f_string_eol_s);

            controller_unlock_print_flush(global.main->program.output.to, global.thread);
          }
        }

        continue;
      }

      // The "on" Rule Setting.
      if (cache->content_actions.array[i].used != 4) {
        controller_rule_setting_read_print_error(global.main->program.error, "requires exactly four Content", i, line_item, global.thread, cache);

        if (F_status_is_error_not(status_return)) {
          status_return = F_status_set_error(F_valid_not);
        }

        continue;
      }

      if (f_compare_dynamic_partial_string(controller_freeze_s.string, cache->buffer_item, controller_freeze_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
        action = controller_rule_action_type_freeze_e;
      }
      else if (f_compare_dynamic_partial_string(controller_kill_s.string, cache->buffer_item, controller_kill_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
        action = controller_rule_action_type_kill_e;
      }
      else if (f_compare_dynamic_partial_string(controller_pause_s.string, cache->buffer_item, controller_pause_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
        action = controller_rule_action_type_pause_e;
      }
      else if (f_compare_dynamic_partial_string(controller_reload_s.string, cache->buffer_item, controller_reload_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
        action = controller_rule_action_type_reload_e;
      }
      else if (f_compare_dynamic_partial_string(controller_restart_s.string, cache->buffer_item, controller_restart_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
        action = controller_rule_action_type_restart_e;
      }
      else if (f_compare_dynamic_partial_string(controller_resume_s.string, cache->buffer_item, controller_resume_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
        action = controller_rule_action_type_resume_e;
      }
      else if (f_compare_dynamic_partial_string(controller_start_s.string, cache->buffer_item, controller_start_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
        action = controller_rule_action_type_start_e;
      }
      else if (f_compare_dynamic_partial_string(controller_stop_s.string, cache->buffer_item, controller_stop_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
        action = controller_rule_action_type_stop_e;
      }
      else if (f_compare_dynamic_partial_string(controller_thaw_s.string, cache->buffer_item, controller_thaw_s.used, cache->content_actions.array[i].array[0]) == F_equal_to) {
        action = controller_rule_action_type_thaw_e;
      }
      else {
        if (global.main->program.error.verbosity > f_console_verbosity_quiet_e) {

          // Get the current line number within the settings item.
          cache->action.line_item = line_item;
          f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global.main->setting.state);

          cache->action.line_action = ++cache->action.line_item;

          f_thread_mutex_lock(&global.thread->lock.print);

          controller_lock_print(global.main->program.error.to, global.thread);

          fl_print_format("%r%[%QRule setting's second value has '%]", global.main->program.error.to, f_string_eol_s, global.main->program.error.context, global.main->program.error.prefix, global.main->program.error.context);
          fl_print_format(f_string_format_Q_range_single_s.string, global.main->program.error.to, global.main->program.error.notable, cache->buffer_item, cache->content_actions.array[i].array[1], global.main->program.error.notable);
          fl_print_format("%[' but only supports %r, %r, %r, %r, %r", global.main->program.error.to, global.main->program.error.context, controller_freeze_s, controller_kill_s, controller_pause_s, controller_reload_s, controller_restart_s);
          fl_print_format("%r, %r, %r, and %r.%]%r", global.main->program.error.to, controller_resume_s, controller_start_s, controller_stop_s, controller_thaw_s, global.main->program.error.context, f_string_eol_s);

          controller_rule_print_error_cache(global.main->program.error, cache->action, F_false);

          controller_unlock_print_flush(global.main->program.error.to, global.thread);
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
        controller_rule_print_error(global.thread, global.main->program.error, cache->action, F_status_set_fine(status), "controller_rule_ons_increase", F_true, F_false);
      }
      else {
        if (f_compare_dynamic_partial_string(controller_need_s.string, cache->buffer_item, controller_need_s.used, cache->content_actions.array[i].array[1]) == F_equal_to) {
          setting_values = &rule->ons.array[j].need;
        }
        else if (f_compare_dynamic_partial_string(controller_want_s.string, cache->buffer_item, controller_want_s.used, cache->content_actions.array[i].array[1]) == F_equal_to) {
          setting_values = &rule->ons.array[j].want;
        }
        else if (f_compare_dynamic_partial_string(controller_wish_s.string, cache->buffer_item, controller_wish_s.used, cache->content_actions.array[i].array[1]) == F_equal_to) {
          setting_values = &rule->ons.array[j].wish;
        }
        else {
          if (global.main->program.error.verbosity > f_console_verbosity_quiet_e) {

            // Get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global.main->setting.state);

            cache->action.line_action = ++cache->action.line_item;

            controller_lock_print(global.main->program.error.to, global.thread);

            fl_print_format("%r%[%QRule setting's second value has '%]", global.main->program.error.to, f_string_eol_s, global.main->program.error.context, global.main->program.error.prefix, global.main->program.error.context);
            fl_print_format(f_string_format_Q_range_single_s.string, global.main->program.error.to, global.main->program.error.notable, cache->buffer_item, cache->content_actions.array[i].array[1], global.main->program.error.notable);
            fl_print_format("%[' but only supports %r, %r, and %r.%]%r", global.main->program.error.to, global.main->program.error.context, controller_need_s, controller_want_s, controller_wish_s, global.main->program.error.context, f_string_eol_s);

            controller_rule_print_error_cache(global.main->program.error, cache->action, F_false);

            controller_unlock_print_flush(global.main->program.error.to, global.thread);
          }

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        status = f_memory_array_increase_by(controller_common_allocation_small_d, sizeof(f_string_dynamic_t), (void **) &setting_values->array, &setting_values->used, &setting_values->size);

        if (F_status_is_error(status)) {
          controller_rule_print_error(global.thread, global.main->program.error, cache->action, F_status_set_fine(status), "f_memory_array_increase_by", F_true, F_false);
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
        f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global.main->setting.state);

        cache->action.line_action = ++cache->action.line_item;

        controller_rule_item_print_error(global.thread, global.main->program.error, cache->action, F_false, F_status_set_fine(status));

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
        f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item, &global.main->setting.state);

        cache->action.line_action = ++cache->action.line_item;

        controller_rule_item_print_error(global.thread, global.main->program.error, cache->action, F_false, F_status_set_fine(status));

        continue;
      }

      cache->buffer_path.used = 0;

      status = f_file_name_base(setting_values->array[setting_values->used], &cache->buffer_path);

      if (F_status_is_error(status)) {
        setting_values->array[setting_values->used].used = 0;

        controller_rule_print_error(global.thread, global.main->program.error, cache->action, F_status_set_fine(status), "f_file_name_base", F_true, F_false);

        if (F_status_set_fine(status) == F_memory_not) {
          status_return = status;

          break;
        }

        if (F_status_is_error_not(status_return)) {
          status_return = status;
        }

        continue;
      }

      rule->ons.array[j].action = action;

      ++setting_values->used;

      if (j == rule->ons.used) {
        ++rule->ons.used;
      }

      if (global.main->program.error.verbosity == f_console_verbosity_debug_e || (global.main->program.error.verbosity == f_console_verbosity_verbose_e && (global.main->program.parameters.array[controller_parameter_simulate_e].result & f_console_result_found_e))) {
        controller_lock_print(global.main->program.output.to, global.thread);

        fl_print_format("%rProcessing rule item action '%[%r%]', adding ", global.main->program.output.to, f_string_eol_s, global.main->program.context.set.title, controller_on_s, global.main->program.context.set.title);
        fl_print_format("'%[%/Q%]' of ", global.main->program.output.to, global.main->program.context.set.notable, cache->buffer_item, cache->content_actions.array[i].array[1], global.main->program.context.set.notable);
        fl_print_format("'%[%/Q%]/", global.main->program.output.to, global.main->program.context.set.important, cache->buffer_item, cache->content_actions.array[i].array[2], global.main->program.context.set.important);
        fl_print_format("%[%/Q%]'.%r", global.main->program.output.to, global.main->program.context.set.important, cache->buffer_item, cache->content_actions.array[i].array[3], global.main->program.context.set.important, f_string_eol_s);

        controller_unlock_print_flush(global.main->program.output.to, global.thread);
      }
    } // for

    // Restore the current name item and line number, which there should already be enough allocated space for.
    memcpy(cache->action.name_item.string, name_item, sizeof(f_char_t) * length_name_item);

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
        if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
          controller_lock_print(main->program.error.to, global.thread);

          fl_print_format("%r%[%QUnsupported action type '%]", main->program.error.to, f_string_eol_s, main->program.error.context, main->program.error.prefix, main->program.error.context);
          fl_print_format(f_string_format_r_single_s.string, main->program.error.to, main->program.error.notable, controller_rule_action_type_name(action), main->program.error.notable);
          fl_print_format("%[' while attempting to validate rule execution.%]%r", main->program.error.to, main->program.error.context, main->program.error.context, f_string_eol_s);

          controller_rule_print_error_cache(main->program.error, cache->action, F_true);

          controller_unlock_print_flush(main->program.error.to, global.thread);
        }

        return;
    }

    f_number_unsigned_t i = 0;
    f_number_unsigned_t j = 0;

    // Find at least one of the requested action.
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
        controller_lock_print(main->program.output.to, global.thread);

        if (rule.items.used) {
          fl_print_format("%rRule '", main->program.output.to, f_string_eol_s);
          fl_print_format("%[%Q%]' has no '", main->program.output.to, main->program.context.set.title, rule.name, main->program.context.set.title);
          fl_print_format("%[%r%]' action to execute and would '", main->program.output.to, main->program.context.set.title, controller_rule_action_type_name(action), main->program.context.set.title);
          fl_print_format("%[%r%]' because it is '", main->program.output.to, main->program.context.set.important, options & controller_process_option_require_d ? controller_fail_s : controller_succeed_s, main->program.context.set.important);
          fl_print_format("%[%r%]'.%r", main->program.output.to, main->program.context.set.important, options & controller_process_option_require_d ? controller_required_s : controller_optional_s, main->program.context.set.important, f_string_eol_s);
        }
        else {
          fl_print_format("%rRule '", main->program.output.to, f_string_eol_s);
          fl_print_format("%[%Q%]' has no known '", main->program.output.to, main->program.context.set.title, rule.name, main->program.context.set.title);
          fl_print_format("%[%r %r%]' (such as ", main->program.output.to, main->program.context.set.title, controller_rule_s, controller_type_s, main->program.context.set.title);
          fl_print_format("'%[%r%]', ", main->program.output.to, main->program.context.set.title, controller_command_s, main->program.context.set.title);
          fl_print_format("'%[%r%]', ", main->program.output.to, main->program.context.set.title, controller_service_s, main->program.context.set.title);
          fl_print_format("'%[%r%]', or ", main->program.output.to, main->program.context.set.title, controller_script_s, main->program.context.set.title);
          fl_print_format("'%[%r%]'", main->program.output.to, main->program.context.set.title, controller_utility_s, main->program.context.set.title);
          fl_print_format(") and would '%[%r%]' because it is '", main->program.output.to, main->program.context.set.important, options & controller_process_option_require_d ? controller_fail_s : controller_succeed_s, main->program.context.set.important);
          fl_print_format("%[%r%]'.%r", main->program.output.to, main->program.context.set.important, options & controller_process_option_require_d ? controller_required_s : controller_optional_s, main->program.context.set.important, f_string_eol_s);
        }

        controller_unlock_print_flush(main->program.output.to, global.thread);
      }
    }

    controller_lock_print(main->program.output.to, global.thread);

    fl_print_format("%rRule %[%Q%] {%r", main->program.output.to, f_string_eol_s, main->program.context.set.title, rule.alias, main->program.context.set.title, f_string_eol_s);

    // Name.
    fl_print_format("  %[%r%] %Q%r", main->program.output.to, main->program.context.set.important, controller_name_s, main->program.context.set.important, rule.name, f_string_eol_s);

    // Capability.
    fl_print_format("  %[%r%] ", main->program.output.to, main->program.context.set.important, controller_capability_s, main->program.context.set.important);

    if (f_capability_supported()) {
      if (rule.capability) {
        cache->action.generic.used = 0;

        if (F_status_is_error_not(f_capability_to_text(rule.capability, &cache->action.generic))) {
          f_print_dynamic_safely(cache->action.generic, main->program.output.to);
        }
      }

      f_print_dynamic_raw(f_string_eol_s, main->program.output.to);
    }
    else {
      fl_print_format("%[(unsupported)%]%r", main->program.output.to, main->program.context.set.warning, main->program.context.set.warning, f_string_eol_s);
    }

    // Control Group.
    fl_print_format("  %[%r%]", main->program.output.to, main->program.context.set.important, controller_cgroup_s, main->program.context.set.important);

    if (rule.has & controller_rule_has_cgroup_d) {
      fl_print_format(" %r", main->program.output.to, rule.cgroup.as_new ? controller_new_s : controller_existing_s);

      for (i = 0; i < rule.cgroup.groups.used; ++i) {

        if (rule.cgroup.groups.array[i].used) {
          fl_print_format(" %Q", main->program.output.to, rule.cgroup.groups.array[i]);
        }
      } // for
    }

    f_print_dynamic_raw(f_string_eol_s, main->program.output.to);

    // How.
    fl_print_format("  %[%r%] %r%r", main->program.output.to, main->program.context.set.important, controller_how_s, main->program.context.set.important, options & controller_process_option_asynchronous_d ? controller_asynchronous_s : controller_synchronous_s, f_string_eol_s);

    // Nice.
    fl_print_format("  %[%r%]", main->program.output.to, main->program.context.set.important, controller_nice_s, main->program.context.set.important);

    if (rule.has & controller_rule_has_nice_d) {
      fl_print_format(" %i", main->program.output.to, rule.nice);
    }

    f_print_dynamic_raw(f_string_eol_s, main->program.output.to);

    // Scheduler.
    fl_print_format("  %[%r%]", main->program.output.to, main->program.context.set.important, controller_scheduler_s, main->program.context.set.important);

    if (rule.has & controller_rule_has_scheduler_d) {
      f_string_static_t policy = f_string_static_t_initialize;

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

      fl_print_format(" %r %i", main->program.output.to, policy, rule.scheduler.priority);
    }

    f_print_dynamic_raw(f_string_eol_s, main->program.output.to);

    // Engine.
    if (rule.engine_arguments.used) {
      fl_print_format("  %[%r%] %Q", main->program.output.to, main->program.context.set.important, controller_engine_s, main->program.context.set.important, rule.engine);

      for (i = 0; i < rule.engine_arguments.used; ++i) {

        if (rule.engine_arguments.array[i].used) {
          fl_print_format(" %Q", main->program.output.to, rule.engine_arguments.array[i]);
        }
      } // for

      fl_print_format("%r", main->program.output.to, f_string_eol_s);
    }
    else {
      fl_print_format("  %[%r%] %Q%r", main->program.output.to, main->program.context.set.important, controller_engine_s, main->program.context.set.important, rule.engine, f_string_eol_s);
    }

    // User.
    fl_print_format("  %[%r%]", main->program.output.to, main->program.context.set.important, controller_user_s, main->program.context.set.important);

    if (rule.has & controller_rule_has_user_d) {
      fl_print_format(" %i", main->program.output.to, rule.user);
    }

    f_print_dynamic_raw(f_string_eol_s, main->program.output.to);

    // Wait.
    fl_print_format("  %[%r%] %r%r", main->program.output.to, main->program.context.set.important, controller_wait_s, main->program.context.set.important, options & controller_process_option_wait_d ? controller_yes_s : controller_no_s, f_string_eol_s);

    // Affinity.
    fl_print_format("  %[%r%] {%r", main->program.output.to, main->program.context.set.important, controller_affinity_s, main->program.context.set.important, f_string_eol_s);

    for (i = 0; i < rule.affinity.used; ++i) {
      fl_print_format("    %i%r", main->program.output.to, rule.affinity.array[i], f_string_eol_s);
    } // for

    // Define.
    fl_print_format("  }%r  %[%r%] {%r", main->program.output.to, f_string_eol_s, main->program.context.set.important, controller_define_s, main->program.context.set.important, f_string_eol_s);

    for (i = 0; i < rule.define.used; ++i) {

      if (rule.define.array[i].key.used && rule.define.array[i].value.used) {
        fl_print_format("    %Q %[=%] %Q%r", main->program.output.to, rule.define.array[i].key, main->program.context.set.important, main->program.context.set.important, rule.define.array[i].value, f_string_eol_s);
      }
    } // for

    // Environment.
    fl_print_format("  }%r  %[%r%] {%r", main->program.output.to, f_string_eol_s, main->program.context.set.important, controller_environment_s, main->program.context.set.important, f_string_eol_s);

    for (i = 0; i < rule.environment.used; ++i) {

      if (rule.environment.array[i].used) {
        fl_print_format("    %Q%r", main->program.output.to, rule.environment.array[i], f_string_eol_s);
      }
    } // for

    fl_print_format("  }%r  %[%r%] {%r", main->program.output.to, f_string_eol_s, main->program.context.set.important, controller_parameter_s, main->program.context.set.important, f_string_eol_s);

    // Parameter.
    for (i = 0; i < rule.parameter.used; ++i) {

      if (rule.parameter.array[i].key.used && rule.parameter.array[i].value.used) {
        fl_print_format("    %Q %[=%] %Q%r", main->program.output.to, rule.parameter.array[i].key, main->program.context.set.important, main->program.context.set.important, rule.parameter.array[i].value, f_string_eol_s);
      }
    } // for

    // Group.
    fl_print_format("  }%r  %[%r%] {%r", main->program.output.to, f_string_eol_s, main->program.context.set.important, controller_group_s, main->program.context.set.important, f_string_eol_s);

    if (rule.has & controller_rule_has_group_d) {
      fl_print_format("    %i%r", main->program.output.to, rule.group, f_string_eol_s);

      for (i = 0; i < rule.groups.used; ++i) {
        fl_print_format("    %i%r", main->program.output.to, rule.groups.array[i], f_string_eol_s);
      } // for
    }

    // Limit.
    fl_print_format("  }%r  %[%r%] {%r", main->program.output.to, f_string_eol_s, main->program.context.set.important, controller_limit_s, main->program.context.set.important, f_string_eol_s);

    for (i = 0; i < rule.limits.used; ++i) {
      fl_print_format("    %Q %[=%] %un %un%r", main->program.output.to, controller_rule_setting_limit_type_name(rule.limits.array[i].type), main->program.context.set.important, main->program.context.set.important, rule.limits.array[i].value.rlim_cur, rule.limits.array[i].value.rlim_max, f_string_eol_s);
    } // for

    // On.
    fl_print_format("  }%r  %[%r%] {%r", main->program.output.to, f_string_eol_s, main->program.context.set.important, controller_on_s, main->program.context.set.important, f_string_eol_s);

    for (i = 0; i < rule.ons.used; ++i) {

      fl_print_format("    %[%r%] {%r", main->program.output.to, main->program.context.set.important, controller_action_s, main->program.context.set.important, f_string_eol_s);

      {
        f_string_static_t action = f_string_static_t_initialize;

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

        fl_print_format("      %[%r%] %r%r", main->program.output.to, main->program.context.set.important, controller_type_s, main->program.context.set.important, action, f_string_eol_s);
      }

      fl_print_format("      %[%r%] {%r", main->program.output.to, main->program.context.set.important, controller_need_s, main->program.context.set.important, f_string_eol_s);

      for (j = 0; j < rule.ons.array[i].need.used; ++j) {

        if (rule.ons.array[i].need.array[j].used) {
          fl_print_format("        %Q%r", main->program.output.to, rule.ons.array[i].need.array[j], f_string_eol_s);
        }
      } // for

      fl_print_format("      }%r      %[%r%] {%r", main->program.output.to, f_string_eol_s, main->program.context.set.important, controller_want_s, main->program.context.set.important, f_string_eol_s);

      for (j = 0; j < rule.ons.array[i].want.used; ++j) {

        if (rule.ons.array[i].want.array[j].used) {
          fl_print_format("        %Q%r", main->program.output.to, rule.ons.array[i].want.array[j], f_string_eol_s);
        }
      } // for

      fl_print_format("      }%r      %[%r%] {%r", main->program.output.to, f_string_eol_s, main->program.context.set.important, controller_wish_s, main->program.context.set.important, f_string_eol_s);

      for (j = 0; j < rule.ons.array[i].wish.used; ++j) {

        if (rule.ons.array[i].wish.array[j].used) {
          fl_print_format("        %Q%r", main->program.output.to, rule.ons.array[i].wish.array[j], f_string_eol_s);
        }
      } // for

      fl_print_format("      }%r    }%r", main->program.output.to, f_string_eol_s, f_string_eol_s);
    } // for

    fl_print_format("  }%r", main->program.output.to, f_string_eol_s);

    // Items.
    if (rule.items.used) {
      controller_rule_action_t *action = 0;
      controller_rule_item_t *item = 0;
      controller_rule_rerun_item_t *rerun_item = 0;

      f_number_unsigned_t j = 0;
      f_number_unsigned_t k = 0;
      f_number_unsigned_t l = 0;

      for (i = 0; i < rule.items.used; ++i) {

        item = &rule.items.array[i];

        fl_print_format("  %[%r%] {%r", main->program.output.to, main->program.context.set.important, controller_item_s, main->program.context.set.important, f_string_eol_s);

        // Type.
        fl_print_format("    %[%r%] %Q%r", main->program.output.to, main->program.context.set.important, controller_type_s, main->program.context.set.important, controller_rule_item_type_name(item->type), f_string_eol_s);

        // Pid file.
        fl_print_format("    %[%r%]", main->program.output.to, main->program.context.set.important, controller_pid_file_s, main->program.context.set.important);
        if (item->pid_file.used) {
          fl_print_format(" %Q", main->program.output.to, item->pid_file);
        }
        f_print_dynamic_raw(f_string_eol_s, main->program.output.to);

        // With.
        fl_print_format("    %[%r%]", main->program.output.to, main->program.context.set.important, controller_with_s, main->program.context.set.important);
        if (item->with & controller_with_full_path_d) {
          fl_print_format(" %r", main->program.output.to, controller_full_path_s);
        }
        if (item->with & controller_with_session_new_d) {
          fl_print_format(" %r", main->program.output.to, controller_session_new_s);
        }
        if (item->with & controller_with_session_same_d) {
          fl_print_format(" %r", main->program.output.to, controller_session_same_s);
        }
        f_print_dynamic_raw(f_string_eol_s, main->program.output.to);

        // Actions.
        for (j = 0; j < item->actions.used; ++j) {

          action = &item->actions.array[j];

          fl_print_format("    %[%r%] {%r", main->program.output.to, main->program.context.set.important, controller_action_s, main->program.context.set.important, f_string_eol_s);
          fl_print_format("      %[%r%] %r%r", main->program.output.to, main->program.context.set.important, controller_type_s, main->program.context.set.important, controller_rule_action_type_name(action->type), f_string_eol_s);

          if (item->type == controller_rule_item_type_script_e || item->type == controller_rule_item_type_utility_e) {
            fl_print_format("      %[%r%] {%r", main->program.output.to, main->program.context.set.important, controller_parameter_s, main->program.context.set.important, f_string_eol_s);

            if (action->parameters.used) {
              if (action->parameters.array[0].used) {
                f_print_terminated("        ", main->program.output.to);

                for (k = 0; k < action->parameters.array[0].used; ++k) {

                  if (action->parameters.array[0].string[k] == f_fss_eol_s.string[0]) {
                    if (k + 1 < action->parameters.array[0].used) {
                      fl_print_format("%r        ", main->program.output.to, f_string_eol_s);
                    }
                  }
                  else {
                    f_print_character_safely(action->parameters.array[0].string[k], main->program.output.to);
                  }
                } // for
              }

              f_print_dynamic_raw(f_string_eol_s, main->program.output.to);
            }

            fl_print_format("      }%r", main->program.output.to, f_string_eol_s);
          }
          else {
            for (k = 0; k < action->parameters.used; ++k) {
              fl_print_format("      %[%r%] %Q%r", main->program.output.to, main->program.context.set.important, controller_parameter_s, main->program.context.set.important, action->parameters.array[k], f_string_eol_s);
            } // for
          }

          if (action->ikis.used) {
            fl_print_format("      %[%r%] {%r", main->program.output.to, main->program.context.set.important, controller_iki_s, main->program.context.set.important, f_string_eol_s);

            for (k = 0; k < action->ikis.used; ++k) {

              for (l = 0; l < action->ikis.array[j].vocabulary.used; ++l) {

                fl_print_format("        %[[%]%ul%[]%]", main->program.output.to, main->program.context.set.important, main->program.context.set.important, k, main->program.context.set.important, main->program.context.set.important);
                fl_print_format(" %/Q %[:%] %/Q%r", main->program.output.to, action->parameters.array[k], action->ikis.array[k].vocabulary.array[l], main->program.context.set.important, main->program.context.set.important, action->parameters.array[k], action->ikis.array[k].content.array[l], f_string_eol_s);
              } // for
            } // for

            fl_print_format("      }%r", main->program.output.to, f_string_eol_s);
          }

          fl_print_format("    }%r", main->program.output.to, f_string_eol_s);
        } // for

        // Rerun.
        fl_print_format("    %[%r%] {%r", main->program.output.to, main->program.context.set.important, controller_rerun_s, main->program.context.set.important, f_string_eol_s);
        for (j = 0; j < controller_rule_action_execute_type__enum_size_e; ++j) {

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

            fl_print_format("      %[", main->program.output.to, main->program.context.set.important);
            switch (j) {
              case controller_rule_action_execute_type_freeze_e:
                f_print_dynamic_raw(controller_freeze_s, main->program.output.to);
                break;

              case controller_rule_action_execute_type_kill_e:
                f_print_dynamic_raw(controller_kill_s, main->program.output.to);
                break;

              case controller_rule_action_execute_type_pause_e:
                f_print_dynamic_raw(controller_pause_s, main->program.output.to);
                break;

              case controller_rule_action_execute_type_reload_e:
                f_print_dynamic_raw(controller_reload_s, main->program.output.to);
                break;

              case controller_rule_action_execute_type_restart_e:
                f_print_dynamic_raw(controller_restart_s, main->program.output.to);
                break;

              case controller_rule_action_execute_type_resume_e:
                f_print_dynamic_raw(controller_resume_s, main->program.output.to);
                break;

              case controller_rule_action_execute_type_start_e:
                f_print_dynamic_raw(controller_start_s, main->program.output.to);
                break;

              case controller_rule_action_execute_type_stop_e:
                f_print_dynamic_raw(controller_stop_s, main->program.output.to);
                break;

              case controller_rule_action_execute_type_thaw_e:
                f_print_dynamic_raw(controller_thaw_s, main->program.output.to);
                break;

              default:
                break;
            }

            fl_print_format("%] %r", main->program.output.to, main->program.context.set.important, k ? controller_success_s : controller_failure_s);
            fl_print_format(" %r %ul %r %ul", main->program.output.to, controller_delay_s, rerun_item->delay, controller_max_s, rerun_item->max);

            if (!k && (item->reruns[j].is & controller_rule_rerun_is_failure_reset_d) || k && (item->reruns[j].is & controller_rule_rerun_is_success_reset_d)) {
              fl_print_format(" %r", main->program.output.to, controller_reset_s);
            }

            f_print_dynamic_raw(f_string_eol_s, main->program.output.to);
          } // for
        } // for
        fl_print_format("    }%r", main->program.output.to, f_string_eol_s);

        fl_print_format("  }%r", main->program.output.to, f_string_eol_s);
      } // for
    }

    fl_print_format("}%r", main->program.output.to, f_string_eol_s);

    controller_unlock_print_flush(main->program.output.to, global.thread);
  }
#endif // _di_controller_rule_validate_

#ifndef _di_controller_rule_wait_all_
  f_status_t controller_rule_wait_all(const controller_global_t global, const bool is_normal, const bool required) {

    f_status_t status_lock = controller_lock_read(is_normal, global.thread, &global.thread->lock.process);

    if (F_status_is_error(status_lock)) {
      controller_lock_print_error_critical(global.main->program.error, F_status_set_fine(status_lock), F_true, global.thread);

      return status_lock;
    }

    if (!global.thread->processs.used) {
      f_thread_unlock(&global.thread->lock.process);

      return F_data_not;
    }

    f_status_t status = F_okay;

    bool required_not_run = F_false;
    bool skip = F_false;

    f_number_unsigned_t i = 0;
    f_number_unsigned_t j = 0;

    // Vuild a list of what to wait for so that anything new after this point will not be waited for.
    const f_number_unsigned_t process_total = global.thread->processs.used;
    controller_data_t *process_list[process_total];

    for (; i < process_total; ++i) {
      process_list[i] = global.thread->processs.array[i];
    } // for

    f_thread_unlock(&global.thread->lock.process);

    for (i = 0; i < process_total; ++i) {

      if (!controller_thread_is_enabled(is_normal, global.thread)) break;

      // Re-establish global process read lock to wait for or protect from the cleanup thread while checking the read process.
      status_lock = controller_lock_read(is_normal, global.thread, &global.thread->lock.process);
      if (F_status_is_error(status_lock)) break;

      if (!process_list[i]) {
        f_thread_unlock(&global.thread->lock.process);

        continue;
      }

      status_lock = controller_lock_read(is_normal, global.thread, &process_list[i]->active);

      if (F_status_is_error(status_lock)) {
        f_thread_unlock(&global.thread->lock.process);

        break;
      }

      // Once the active lock is obtained, then the main process read lock can be safely released.
      f_thread_unlock(&global.thread->lock.process);

      status_lock = controller_lock_read(is_normal, global.thread, &process_list[i]->lock);

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

          status_lock = controller_lock_write(is_normal, global.thread, &process_list[i]->lock);

          if (F_status_is_error(status_lock)) {
            controller_lock_print_error_critical(global.main->program.error, F_status_set_fine(status_lock), F_false, global.thread);

            f_thread_unlock(&process_list[i]->active);

            return status_lock;
          }

          if (process_list[i]->state == controller_process_state_done_e) {
            f_thread_unlock(&process_list[i]->active);

            if (f_thread_lock_write_try(&process_list[i]->active) == F_okay) {
              controller_thread_join(&process_list[i]->id_thread);

              process_list[i]->state = controller_process_state_idle_e;

              f_thread_unlock(&process_list[i]->active);

              f_thread_mutex_lock(&process_list[i]->wait_lock);
              f_thread_condition_signal_all(&process_list[i]->wait);
              f_thread_mutex_unlock(&process_list[i]->wait_lock);
            }

            status_lock = controller_lock_read(is_normal, global.thread, &process_list[i]->active);

            if (F_status_is_error(status_lock)) {
              f_thread_unlock(&process_list[i]->lock);

              break;
            }
          }

          f_thread_unlock(&process_list[i]->lock);

          status_lock = controller_lock_read(is_normal, global.thread, &process_list[i]->lock);
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

        status_lock = controller_lock_read(is_normal, global.thread, &process_list[i]->lock);

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
      controller_lock_print_error_critical(global.main->program.error, F_status_set_fine(status_lock), F_true, global.thread);

      return status_lock;
    }

    if (!controller_thread_is_enabled(is_normal, global.thread)) {
      return F_status_set_error(F_interrupt);
    }

    if (F_status_set_fine(status) == F_require) {
      return status;
    }

    if (required_not_run) {
      return F_require;
    }

    return F_okay;
  }
#endif // _di_controller_rule_wait_all_

#ifndef _di_controller_rule_wait_all_process_type_
  f_status_t controller_rule_wait_all_process_type(const controller_global_t global, const uint8_t type, const bool required) {

    return controller_rule_wait_all(global, type != controller_data_type_exit_e, required);
  }
#endif // _di_controller_rule_wait_all_process_type_

#ifdef __cplusplus
} // extern "C"
#endif
