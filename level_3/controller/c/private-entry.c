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

    f_array_length_t index = 0;

    for (;;) {

      f_print_dynamic(stream, action.parameters.array[index]);

      ++index;

      if (index == action.parameters.used) break;

      fprintf(stream, f_string_space_s);
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
        buffer.string = controller_string_consider_s;
        buffer.used = controller_string_consider_length;
        break;

      case controller_entry_action_type_execute:
        buffer.string = controller_string_execute_s;
        buffer.used = controller_string_execute_length;
        break;

      case controller_entry_action_type_failsafe:
        buffer.string = controller_string_failsafe_s;
        buffer.used = controller_string_failsafe_length;
        break;

      case controller_entry_action_type_freeze:
        buffer.string = controller_string_freeze_s;
        buffer.used = controller_string_freeze_length;
        break;

      case controller_entry_action_type_item:
        buffer.string = controller_string_item_s;
        buffer.used = controller_string_item_length;
        break;

      case controller_entry_action_type_kill:
        buffer.string = controller_string_kill_s;
        buffer.used = controller_string_kill_length;
        break;

      case controller_entry_action_type_pause:
        buffer.string = controller_string_pause_s;
        buffer.used = controller_string_pause_length;
        break;

      case controller_entry_action_type_ready:
        buffer.string = controller_string_ready_s;
        buffer.used = controller_string_ready_length;
        break;

      case controller_entry_action_type_reload:
        buffer.string = controller_string_reload_s;
        buffer.used = controller_string_reload_length;
        break;

      case controller_entry_action_type_restart:
        buffer.string = controller_string_restart_s;
        buffer.used = controller_string_restart_length;
        break;

      case controller_entry_action_type_resume:
        buffer.string = controller_string_resume_s;
        buffer.used = controller_string_resume_length;
        break;

      case controller_entry_action_type_start:
        buffer.string = controller_string_start_s;
        buffer.used = controller_string_start_length;
        break;

      case controller_entry_action_type_stop:
        buffer.string = controller_string_stop_s;
        buffer.used = controller_string_stop_length;
        break;

      case controller_entry_action_type_thaw:
        buffer.string = controller_string_thaw_s;
        buffer.used = controller_string_thaw_length;
        break;

      case controller_entry_action_type_timeout:
        buffer.string = controller_string_timeout_s;
        buffer.used = controller_string_timeout_length;
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
      if (actions->used + amount > f_array_length_t_size) {
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
  f_status_t controller_entry_actions_read(const bool is_entry, const f_string_range_t content_range, controller_main_t main, controller_cache_t *cache, controller_entry_actions_t *actions) {
    f_status_t status = F_none;
    f_status_t status_action = F_none;

    actions->used = 0;

    cache->object_actions.used = cache->object_actions.size;

    while (cache->object_actions.used) {
      cache->object_actions.used--;
      cache->object_actions.array[cache->object_actions.used].start = 1;
      cache->object_actions.array[cache->object_actions.used].stop = 0;
    } // while

    cache->content_actions.used = cache->content_actions.size;

    while (cache->content_actions.used) {
      cache->content_actions.used--;
      cache->content_actions.array[cache->content_actions.used].used = 0;
    } // while

    {
      f_string_range_t range = content_range;

      status = fll_fss_extended_read(cache->buffer_file, &range, &cache->object_actions, &cache->content_actions, 0, 0, &cache->delimits, 0);
    }

    if (F_status_is_error(status)) {
      controller_entry_error_print(is_entry, main.data->error, cache->action, F_status_set_fine(status), "fll_fss_extended_read", F_true, main.thread);

      return status;
    }

    status = fl_fss_apply_delimit(cache->delimits, &cache->buffer_file);

    if (F_status_is_error(status)) {
      controller_entry_error_print(is_entry, main.data->error, cache->action, F_status_set_fine(status), "fl_fss_apply_delimit", F_true, main.thread);

      return status;
    }

    cache->delimits.used = 0;

    status = controller_entry_actions_increase_by(cache->object_actions.used, actions);

    if (F_status_is_error(status)) {
      controller_entry_error_print(is_entry, main.data->error, cache->action, F_status_set_fine(status), "controller_entry_actions_increase_by", F_true, main.thread);

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
        controller_entry_error_print(is_entry, main.data->error, cache->action, F_status_set_fine(status), "f_fss_count_lines", F_true, main.thread);
        break;
      }

      action->line = ++cache->action.line_action;

      status = controller_string_dynamic_rip_nulless_terminated(cache->buffer_file, cache->object_actions.array[i], &cache->action.name_action);

      if (F_status_is_error(status)) {
        controller_entry_error_print(is_entry, main.data->error, cache->action, F_status_set_fine(status), "controller_string_dynamic_rip_nulless_terminated", F_true, main.thread);
        break;
      }

      if (fl_string_dynamic_compare_string(controller_string_consider_s, cache->action.name_action, controller_string_consider_length) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_consider;
      }
      else if (fl_string_dynamic_compare_string(controller_string_execute_s, cache->action.name_action, controller_string_execute_length) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_execute;
      }
      else if (fl_string_dynamic_compare_string(controller_string_failsafe_s, cache->action.name_action, controller_string_failsafe_length) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_failsafe;
      }
      else if (fl_string_dynamic_compare_string(controller_string_freeze_s, cache->action.name_action, controller_string_freeze_length) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_freeze;
      }
      else if (fl_string_dynamic_compare_string(controller_string_item_s, cache->action.name_action, controller_string_item_length) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_item;
      }
      else if (fl_string_dynamic_compare_string(controller_string_kill_s, cache->action.name_action, controller_string_kill_length) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_kill;
      }
      else if (fl_string_dynamic_compare_string(controller_string_pause_s, cache->action.name_action, controller_string_pause_length) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_pause;
      }
      else if (fl_string_dynamic_compare_string(controller_string_ready_s, cache->action.name_action, controller_string_ready_length) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_ready;
      }
      else if (fl_string_dynamic_compare_string(controller_string_reload_s, cache->action.name_action, controller_string_reload_length) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_reload;
      }
      else if (fl_string_dynamic_compare_string(controller_string_restart_s, cache->action.name_action, controller_string_restart_length) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_restart;
      }
      else if (fl_string_dynamic_compare_string(controller_string_resume_s, cache->action.name_action, controller_string_resume_length) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_resume;
      }
      else if (fl_string_dynamic_compare_string(controller_string_start_s, cache->action.name_action, controller_string_start_length) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_start;
      }
      else if (fl_string_dynamic_compare_string(controller_string_stop_s, cache->action.name_action, controller_string_stop_length) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_stop;
      }
      else if (fl_string_dynamic_compare_string(controller_string_thaw_s, cache->action.name_action, controller_string_thaw_length) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_thaw;
      }
      else if (fl_string_dynamic_compare_string(controller_string_timeout_s, cache->action.name_action, controller_string_timeout_length) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_timeout;
      }
      else {
        if (main.data->warning.verbosity == f_console_verbosity_debug) {
          fprintf(main.data->warning.to.stream, "%s%sUnknown %s item action '", main.data->warning.context.before->string, main.data->warning.prefix ? main.data->warning.prefix : f_string_empty_s, is_entry ? controller_string_entry_s : controller_string_exit_s);
          fprintf(main.data->warning.to.stream, "%s%s", main.data->warning.context.after->string, main.data->warning.notable.before->string);
          f_print_dynamic(main.data->warning.to.stream, cache->action.name_action);
          fprintf(main.data->warning.to.stream, "%s", main.data->warning.notable.after->string);
          fprintf(main.data->warning.to.stream, "%s'.%s%c", main.data->warning.context.before->string, main.data->warning.context.after->string, f_string_eol_s[0]);

          controller_entry_error_print_cache(is_entry, main.data->warning, cache->action);
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

        if (main.data->error.verbosity != f_console_verbosity_quiet) {
          fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
          fprintf(main.data->error.to.stream, "%s%sThe %s item action '", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s, is_entry ? controller_string_entry_s : controller_string_exit_s);
          fprintf(main.data->error.to.stream, "%s%s%s%s", main.data->error.context.after->string, main.data->error.notable.before->string, cache->action.name_action.string, main.data->error.notable.after->string);
          fprintf(main.data->error.to.stream, "%s' requires ", main.data->error.context.before->string);

          if (at_least == at_most) {
            fprintf(main.data->error.to.stream, "exactly ", main.data->error.context.before->string);
          }

          fprintf(main.data->error.to.stream, "%s%s%llu%s", main.data->error.context.after->string, main.data->error.notable.before->string, at_least, main.data->error.notable.after->string);

          if (action->type == controller_entry_action_type_consider || controller_entry_action_type_is_rule(action->type)) {
            fprintf(main.data->error.to.stream, "%s or more parameters.%s%c", main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);
          }
          else {
            if (at_least == at_most) {
              fprintf(main.data->error.to.stream, "%s parameters.%s%c", main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);
            }
            else {
              fprintf(main.data->error.to.stream, "%s to ", main.data->error.context.before->string);
              fprintf(main.data->error.to.stream, "%s%s%llu%s", main.data->error.context.after->string, main.data->error.notable.before->string, at_most, main.data->error.notable.after->string);
              fprintf(main.data->error.to.stream, "%s parameters.%s%c", main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);
            }
          }
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
          controller_entry_error_print(is_entry, main.data->error, cache->action, F_status_set_fine(status), "f_string_dynamics_increase_by", F_true, main.thread);

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
            controller_entry_error_print(is_entry, main.data->error, cache->action, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, main.thread);

            action->status = status;

            if (F_status_is_error_not(status_action)) {
              status_action = status;
            }

            break;
          }

          action->parameters.used++;
        } // for

        if (F_status_is_error_not(action->status)) {
          if (action->type == controller_entry_action_type_consider || controller_entry_action_type_is_rule(action->type)) {
            if (action->parameters.array[0].used) {

              // force the path to be canonical (removing all '../' parts).
              status = fll_path_canonical(action->parameters.array[0].string, &cache->buffer_path);

              if (F_status_is_error(status)) {
                controller_entry_error_print(is_entry, main.data->error, cache->action, F_status_set_fine(status), "fll_path_canonical", F_true, main.thread);

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

              if (main.data->error.verbosity != f_console_verbosity_quiet) {
                fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
                fprintf(main.data->error.to.stream, "%s%sThe %s item action must not have an empty string for a path (the first parameter).%s%c", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s, is_entry ? controller_string_entry_s : controller_string_exit_s, main.data->error.context.after->string, f_string_eol_s[0]);
              }
            }

            if (action->parameters.array[1].used) {
              cache->buffer_path.used = 0;

              status = f_file_name_base(action->parameters.array[1].string, action->parameters.array[1].used, &cache->buffer_path);

              if (F_status_is_error(status)) {
                controller_entry_error_print(is_entry, main.data->error, cache->action, F_status_set_fine(status), "f_file_name_base", F_true, main.thread);

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

                  if (main.data->error.verbosity != f_console_verbosity_quiet) {
                    status = f_string_dynamic_terminate_after(&cache->buffer_path);

                    if (F_status_is_error(status)) {
                      controller_entry_error_print(is_entry, main.data->error, cache->action, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true, main.thread);

                      action->status = status;

                      if (F_status_set_fine(status) == F_memory_not) {
                        status_action = status;
                      }

                      break;
                    }

                    fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
                    fprintf(main.data->error.to.stream, "%s%sThe %s item action second parameter '", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s, is_entry ? controller_string_entry_s : controller_string_exit_s);
                    fprintf(main.data->error.to.stream, "%s%s%s%s", main.data->error.context.after->string, main.data->error.notable.before->string, action->parameters.array[1].string, main.data->error.notable.after->string);
                    fprintf(main.data->error.to.stream, "%s' must be a base path name, such as '", main.data->error.context.before->string);
                    fprintf(main.data->error.to.stream, "%s%s%s%s", main.data->error.context.after->string, main.data->error.notable.before->string, cache->buffer_path.string, main.data->error.notable.after->string);
                    fprintf(main.data->error.to.stream, "%s'.%s%c", main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);
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

              if (main.data->error.verbosity != f_console_verbosity_quiet) {
                fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
                fprintf(main.data->error.to.stream, "%s%sThe %s item action must not have an empty string for a rule name (the second parameter).%s%c", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s, is_entry ? controller_string_entry_s : controller_string_exit_s, main.data->error.context.after->string, f_string_eol_s[0]);
              }
            }

            for (j = 2; j < action->parameters.used; ++j) {

              if (fl_string_dynamic_compare_string(controller_string_asynchronous_s, action->parameters.array[j], controller_string_asynchronous_length) == F_equal_to) {
                action->code |= controller_entry_rule_code_asynchronous;
              }
              else if (fl_string_dynamic_compare_string(controller_string_require_s, action->parameters.array[j], controller_string_require_length) == F_equal_to) {
                action->code |= controller_entry_rule_code_require;
              }
              else if (fl_string_dynamic_compare_string(controller_string_wait_s, action->parameters.array[j], controller_string_wait_length) == F_equal_to) {
                action->code |= controller_entry_rule_code_wait;
              }
              else {
                if (action->status == F_none) {
                  action->status = F_status_set_error(F_supported_not);

                  if (F_status_is_error_not(status_action)) {
                    status_action = action->status;
                  }
                }

                if (main.data->error.verbosity != f_console_verbosity_quiet) {
                  fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
                  fprintf(main.data->error.to.stream, "%s%sThe %s item action third parameter (and beyond) must be one of '", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s, is_entry ? controller_string_entry_s : controller_string_exit_s);
                  fprintf(main.data->error.to.stream, "%s%s%s%s", main.data->error.context.after->string, main.data->error.notable.before->string, controller_string_asynchronous_s, main.data->error.notable.after->string);
                  fprintf(main.data->error.to.stream, "%s', '", main.data->error.context.before->string);
                  fprintf(main.data->error.to.stream, "%s%s%s%s", main.data->error.context.after->string, main.data->error.notable.before->string, controller_string_require_s, main.data->error.notable.after->string);
                  fprintf(main.data->error.to.stream, "%s', or '", main.data->error.context.before->string);
                  fprintf(main.data->error.to.stream, "%s%s%s%s", main.data->error.context.after->string, main.data->error.notable.before->string, controller_string_wait_s, main.data->error.notable.after->string);
                  fprintf(main.data->error.to.stream, "%s' but instead has '", main.data->error.context.before->string);
                  fprintf(main.data->error.to.stream, "%s%s%s%s", main.data->error.context.after->string, main.data->error.notable.before->string, action->parameters.array[j].string, main.data->error.notable.after->string);
                  fprintf(main.data->error.to.stream, "%s'.%s%c", main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);
                }
              }
            } // for
          }
          else if (action->type == controller_entry_action_type_failsafe || action->type == controller_entry_action_type_item) {
            if (fl_string_dynamic_compare_string(controller_string_main_s, action->parameters.array[0], controller_string_main_length) == F_equal_to) {
              action->status = F_status_set_error(F_supported_not);

              if (F_status_is_error_not(status_action)) {
                status_action = action->status;
              }

              if (main.data->error.verbosity != f_console_verbosity_quiet) {
                fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
                fprintf(main.data->error.to.stream, "%s%sThe %s item action may not specify the reserved item '", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s, is_entry ? controller_string_entry_s : controller_string_exit_s);
                fprintf(main.data->error.to.stream, "%s%s%s%s", main.data->error.context.after->string, main.data->error.notable.before->string, controller_string_main_s, main.data->error.notable.after->string);
                fprintf(main.data->error.to.stream, "%s'.%s%c", main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);
              }
            }
          }
          else if (action->type == controller_entry_action_type_timeout) {

            if (fl_string_dynamic_compare_string(controller_string_kill_s, action->parameters.array[0], controller_string_kill_length) == F_equal_to) {
              action->code = controller_entry_timeout_code_kill;
            }
            else if (fl_string_dynamic_compare_string(controller_string_start_s, action->parameters.array[0], controller_string_start_length) == F_equal_to) {
              action->code = controller_entry_timeout_code_start;
            }
            else if (fl_string_dynamic_compare_string(controller_string_stop_s, action->parameters.array[0], controller_string_stop_length) == F_equal_to) {
              action->code = controller_entry_timeout_code_stop;
            }
            else {
              action->status = F_status_set_error(F_supported_not);

              if (F_status_is_error_not(status_action)) {
                status_action = action->status;
              }

              if (main.data->error.verbosity != f_console_verbosity_quiet) {
                fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
                fprintf(main.data->error.to.stream, "%s%sThe %s item action must have one of '", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s, is_entry ? controller_string_entry_s : controller_string_exit_s);
                fprintf(main.data->error.to.stream, "%s%s%s%s", main.data->error.context.after->string, main.data->error.notable.before->string, controller_string_kill_s, main.data->error.notable.after->string);
                fprintf(main.data->error.to.stream, "%s', '", main.data->error.context.before->string);
                fprintf(main.data->error.to.stream, "%s%s%s%s", main.data->error.context.after->string, main.data->error.notable.before->string, controller_string_start_s, main.data->error.notable.after->string);
                fprintf(main.data->error.to.stream, "%s', or '", main.data->error.context.before->string);
                fprintf(main.data->error.to.stream, "%s%s%s%s", main.data->error.context.after->string, main.data->error.notable.before->string, controller_string_stop_s, main.data->error.notable.after->string);
                fprintf(main.data->error.to.stream, "%s' but instead has '", main.data->error.context.before->string);
                fprintf(main.data->error.to.stream, "%s%s%s%s", main.data->error.context.after->string, main.data->error.notable.before->string, action->parameters.array[0].string, main.data->error.notable.after->string);
                fprintf(main.data->error.to.stream, "%s'.%s%c", main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);
              }
            }

            if (action->status == F_none) {
              const f_string_range_t range = f_macro_string_range_t_initialize(action->parameters.array[1].used);

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
                  controller_entry_error_print(is_entry, main.data->error, cache->action, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, main.thread);

                  status_action = status;
                  break;
                }

                if (main.data->error.verbosity != f_console_verbosity_quiet) {
                  fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
                  fprintf(main.data->error.to.stream, "%s%sThe %s item action parameter '", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s, is_entry ? controller_string_entry_s : controller_string_exit_s);
                  fprintf(main.data->error.to.stream, "%s%s%s%s", main.data->error.context.after->string, main.data->error.notable.before->string, action->parameters.array[1].string, main.data->error.notable.after->string);
                  fprintf(main.data->error.to.stream, "%s' is not a valid supported number.%s%c", main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);
                }
              }
            }
          }
          else if (action->type == controller_entry_action_type_ready) {
            if (action->parameters.used) {
              if (fl_string_dynamic_compare_string(controller_string_wait_s, action->parameters.array[0], controller_string_wait_length) == F_equal_to) {
                action->code |= controller_entry_rule_code_wait;
              }
              else {
                action->status = F_status_set_error(F_supported_not);

                if (main.data->error.verbosity != f_console_verbosity_quiet) {
                  fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
                  fprintf(main.data->error.to.stream, "%s%sThe %s item action may only have '", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s, is_entry ? controller_string_entry_s : controller_string_exit_s);
                  fprintf(main.data->error.to.stream, "%s%s%s%s", main.data->error.context.after->string, main.data->error.notable.before->string, controller_string_wait_s, main.data->error.notable.after->string);
                  fprintf(main.data->error.to.stream, "%s' but instead has '", main.data->error.context.before->string);
                  fprintf(main.data->error.to.stream, "%s%s%s%s", main.data->error.context.after->string, main.data->error.notable.before->string, action->parameters.array[0].string, main.data->error.notable.after->string);
                  fprintf(main.data->error.to.stream, "%s'.%s%c", main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);
                }
              }
            }
          }
        }
      }

      actions->used++;
    } // for

    if (F_status_is_error(status_action)) {
      return status_action;
    }

    return status;
  }
#endif // _di_controller_entry_actions_read_

#ifndef _di_controller_entry_error_print_
  void controller_entry_error_print(const bool is_entry, const fll_error_print_t print, const controller_cache_action_t cache, const f_status_t status, const f_string_t function, const bool fallback, controller_thread_t *thread) {

    if (print.verbosity != f_console_verbosity_quiet) {
      f_thread_mutex_lock(&thread->lock.print);

      fll_error_print(print, status, function, fallback);
      controller_entry_error_print_cache(is_entry, print, cache);

      controller_print_unlock_flush(print.to.stream, &thread->lock.print);
    }
  }
#endif // _di_controller_entry_error_print_

#ifndef _di_controller_entry_error_print_cache_
  void controller_entry_error_print_cache(const bool is_entry, const fll_error_print_t print, const controller_cache_action_t cache) {

    fprintf(print.to.stream, "%c", f_string_eol_s[0]);
    fprintf(print.to.stream, "%s%sWhile processing ", print.context.before->string, print.prefix ? print.prefix : f_string_empty_s);

    if (cache.name_action.used) {
      fprintf(print.to.stream, "action '");
      fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, cache.name_action.string, print.notable.after->string);
      fprintf(print.to.stream, "%s' on line ", print.context.before->string);
      fprintf(print.to.stream, "%s%s%llu%s", print.context.after->string, print.notable.before->string, cache.line_action, print.notable.after->string);
      fprintf(print.to.stream, "%s for ", print.context.before->string);
    }

    if (cache.name_item.used) {
      fprintf(print.to.stream, "%s item '", is_entry ? controller_string_entry_s : controller_string_exit_s);
      fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, cache.name_item.string, print.notable.after->string);
      fprintf(print.to.stream, "%s' on line ", print.context.before->string);
      fprintf(print.to.stream, "%s%s%llu%s", print.context.after->string, print.notable.before->string, cache.line_item, print.notable.after->string);
      fprintf(print.to.stream, "%s for ", print.context.before->string);
    }

    if (cache.name_file.used) {
      fprintf(print.to.stream, "%s file '", is_entry ? controller_string_entry_s : controller_string_exit_s);
      fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, cache.name_file.string, print.notable.after->string);
      fprintf(print.to.stream, "%s'.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);
    }
  }
#endif // _di_controller_entry_error_print_cache_

#ifndef _di_controller_entry_items_increase_by_
  f_status_t controller_entry_items_increase_by(const f_array_length_t amount, controller_entry_items_t *items) {

    if (items->used + amount > items->size) {
      if (items->used + amount > f_array_length_t_size) {
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
  f_status_t controller_entry_read(const bool is_entry, controller_main_t main, controller_cache_t *cache) {

    f_status_t status = F_none;

    controller_entry_t *entry = is_entry ? &main.setting->entry : &main.setting->exit;

    entry->status = F_known_not;
    entry->items.used = 0;

    cache->action.line_action = 0;
    cache->action.line_item = 0;

    f_macro_time_spec_t_clear(cache->timestamp);

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
      status = controller_file_load(F_true, controller_string_entries_s, main.setting->name_entry, controller_string_entry_s, controller_string_entries_length, controller_string_entry_length, main, cache);
    }
    else {
      status = controller_file_load(F_false, controller_string_exits_s, main.setting->name_entry, controller_string_exit_s, controller_string_exits_length, controller_string_exit_length, main, cache);

      if (status == F_file_found_not) {
        return F_file_found_not;
      }
    }

    if (F_status_is_error_not(status)) {
      if (cache->buffer_file.used) {
        f_string_range_t range = f_macro_string_range_t_initialize(cache->buffer_file.used);

        status = fll_fss_basic_list_read(cache->buffer_file, &range, &cache->object_items, &cache->content_items, &cache->delimits, 0, &cache->comments);

        if (F_status_is_error(status)) {
          controller_error_print(main.data->error, F_status_set_fine(status), "fll_fss_basic_list_read", F_true, main.thread);
        }
        else {
          status = fl_fss_apply_delimit(cache->delimits, &cache->buffer_file);

          if (F_status_is_error(status)) {
            controller_entry_error_print(is_entry, main.data->error, cache->action, F_status_set_fine(status), "fl_fss_apply_delimit", F_true, main.thread);
          }
        }
      }
      else {
        if (main.data->error.verbosity != f_console_verbosity_quiet) {
          f_thread_mutex_lock(&main.thread->lock.print);

          fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
          fprintf(main.data->error.to.stream, "%s%sThe %s file is empty.%s%c", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s, is_entry ? controller_string_entry_s : controller_string_exit_s, main.data->error.context.after->string, f_string_eol_s[0]);

          controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);
        }

        status = F_status_set_error(F_data_not);
      }
    }

    if (F_status_is_error_not(status) && cache->object_items.used) {
      status = controller_entry_items_increase_by(cache->object_items.used, &entry->items);

      if (F_status_is_error(status)) {
        controller_entry_error_print(is_entry, main.data->error, cache->action, F_status_set_fine(status), "controller_entry_items_increase_by", F_true, main.thread);
      }
      else {

        // 0x1 = main found, 0x2 = found existing.
        uint8_t code = 0;

        f_string_range_t *range = 0;

        f_array_length_t at = 0;
        f_array_length_t i = 0;
        f_array_length_t j = 0;

        for (; i < cache->object_items.used && controller_thread_is_enabled(is_entry, main.thread); ++i) {

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

          status = controller_entry_items_increase_by(controller_default_allocation_step, &entry->items);

          if (F_status_is_error(status)) {
            controller_entry_error_print(is_entry, main.data->error, cache->action, F_status_set_fine(status), "controller_entry_items_increase_by", F_true, main.thread);
            break;
          }

          status = controller_string_dynamic_partial_append_terminated(cache->buffer_file, cache->object_items.array[i], &cache->action.name_item);

          if (F_status_is_error(status)) {
            controller_entry_error_print(is_entry, main.data->error, cache->action, F_status_set_fine(status), "controller_string_dynamic_partial_append_terminated", F_true, main.thread);
            break;
          }

          status = f_fss_count_lines(cache->buffer_file, cache->object_items.array[i].start, &cache->action.line_item);

          if (F_status_is_error(status)) {
            controller_entry_error_print(is_entry, main.data->error, cache->action, F_status_set_fine(status), "f_fss_count_lines", F_true, main.thread);
            break;
          }

          cache->action.line_item++;

          for (j = (code & 0x1) ? 1 : 0; j < entry->items.used; ++j) {

            if (fl_string_dynamic_compare(entry->items.array[j].name, cache->action.name_item) == F_equal_to) {
              if (main.data->warning.verbosity == f_console_verbosity_debug) {
                f_thread_mutex_lock(&main.thread->lock.print);

                fprintf(main.data->warning.to.stream, "%c", f_string_eol_s[0]);
                fprintf(main.data->warning.to.stream, "%s%sIgnoring duplicate %s item '", main.data->warning.context.before->string, main.data->warning.prefix ? main.data->warning.prefix : f_string_empty_s, is_entry ? controller_string_entry_s : controller_string_exit_s);
                fprintf(main.data->warning.to.stream, "%s%s%s%s", main.data->warning.context.after->string, main.data->warning.notable.before->string, cache->action.name_file.string, main.data->warning.notable.after->string);
                fprintf(main.data->warning.to.stream, "%s'.%s%c", main.data->warning.context.before->string, main.data->warning.context.after->string, f_string_eol_s[0]);

                controller_entry_error_print_cache(is_entry, main.data->warning, cache->action);

                controller_print_unlock_flush(main.data->warning.to.stream, &main.thread->lock.print);
              }

              code |= 0x2;
              break;
            }
          } // for

          if (code & 0x2) continue;

          range = &cache->content_items.array[i].array[0];

          if (fl_string_dynamic_compare_string(controller_string_main_s, cache->action.name_item, controller_string_main_length) == F_equal_to) {
            code |= 0x1;

            at = 0;

            if (!entry->items.used) {
              entry->items.used = 1;
            }
          }
          else if (fl_string_dynamic_compare_string(controller_string_setting_s, cache->action.name_item, controller_string_setting_length) == F_equal_to) {
            status = controller_entry_settings_read(is_entry, *range, main, cache);

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

          status = controller_string_dynamic_append_terminated(cache->action.name_item, &entry->items.array[at].name);

          if (F_status_is_error(status)) {
            controller_error_print(main.data->error, F_status_set_fine(status), "controller_string_dynamic_append_terminated", F_true, main.thread);

            break;
          }

          status = controller_entry_actions_read(is_entry, *range, main, cache, &entry->items.array[at].actions);

          if (F_status_is_error(status)) {
            f_thread_mutex_lock(&main.thread->lock.print);

            controller_entry_error_print_cache(is_entry, main.data->error, cache->action);

            controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);

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
            if (main.data->error.verbosity != f_console_verbosity_quiet) {
              f_thread_mutex_lock(&main.thread->lock.print);

              fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
              fprintf(main.data->error.to.stream, "%s%sThe required %s item '", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s, is_entry ? controller_string_entry_s : controller_string_exit_s);
              fprintf(main.data->error.to.stream, "%s%s%s%s", main.data->error.context.after->string, main.data->error.notable.before->string, controller_string_main_s, main.data->error.notable.after->string);
              fprintf(main.data->error.to.stream, "%s' was not found.%s%c", main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);

              controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);
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

                if (!controller_thread_is_enabled(is_entry, main.thread)) {
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

                    status = controller_string_dynamic_append_terminated(entry->items.array[i].name, &cache->action.name_item);

                    if (F_status_is_error(status)) {
                      controller_error_print(main.data->error, F_status_set_fine(status), "controller_string_dynamic_append_terminated", F_true, main.thread);
                      break;
                    }

                    if (main.data->error.verbosity != f_console_verbosity_quiet) {
                      f_thread_mutex_lock(&main.thread->lock.print);

                      fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
                      fprintf(main.data->error.to.stream, "%s%sThe required %s item '", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s, is_entry ? controller_string_entry_s : controller_string_exit_s);
                      fprintf(main.data->error.to.stream, "%s%s%s%s", main.data->error.context.after->string, main.data->error.notable.before->string, action->parameters.array[0].string, main.data->error.notable.after->string);
                      fprintf(main.data->error.to.stream, "%s' does not exist.%s%c", main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);

                      controller_entry_error_print_cache(is_entry, main.data->error, cache->action);

                      controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);
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
      controller_entry_error_print_cache(is_entry, main.data->error, cache->action);

      entry->status = controller_status_simplify_error(F_status_set_fine(status));
    }
    else {
      entry->status = F_none;
    }

    return entry->status;
  }
#endif // _di_controller_entry_read_

#ifndef _di_controller_entry_settings_read_
  f_status_t controller_entry_settings_read(const bool is_entry, const f_string_range_t content_range, controller_main_t main, controller_cache_t *cache) {
    f_status_t status = F_none;

    {
      f_string_range_t range = content_range;

      status = fll_fss_extended_read(cache->buffer_file, &range, &cache->object_actions, &cache->content_actions, 0, 0, &cache->delimits, 0);
    }

    if (F_status_is_error(status)) {
      controller_entry_error_print(is_entry, main.data->error, cache->action, F_status_set_fine(status), "fll_fss_extended_read", F_true, main.thread);

      return status;
    }

    status = fl_fss_apply_delimit(cache->delimits, &cache->buffer_file);

    if (F_status_is_error(status)) {
      controller_entry_error_print(is_entry, main.data->error, cache->action, F_status_set_fine(status), "fl_fss_apply_delimit", F_true, main.thread);

      return status;
    }

    cache->delimits.used = 0;

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t line = 0;

    for (; i < cache->object_actions.used; ++i) {

      status = f_fss_count_lines(cache->buffer_file, cache->object_actions.array[i].start, &cache->action.line_action);

      if (F_status_is_error(status)) {
        controller_entry_error_print(is_entry, main.data->error, cache->action, F_status_set_fine(status), "f_fss_count_lines", F_true, main.thread);
        break;
      }

      line = ++cache->action.line_action;

      status = controller_string_dynamic_rip_nulless_terminated(cache->buffer_file, cache->object_actions.array[i], &cache->action.name_action);

      if (F_status_is_error(status)) {
        controller_entry_error_print(is_entry, main.data->error, cache->action, F_status_set_fine(status), "controller_string_dynamic_rip_nulless_terminated", F_true, main.thread);
        break;
      }

      if (is_entry && fl_string_dynamic_compare_string(controller_string_mode_s, cache->action.name_action, controller_string_mode_length) == F_equal_to) {
        if (cache->content_actions.array[i].used < 0 || cache->content_actions.array[i].used > 1) {
          if (main.data->error.verbosity != f_console_verbosity_quiet) {
            fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
            fprintf(main.data->error.to.stream, "%s%sThe %s item setting '", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s, is_entry ? controller_string_entry_s : controller_string_exit_s);
            fprintf(main.data->error.to.stream, "%s%s%s%s", main.data->error.context.after->string, main.data->error.notable.before->string, cache->action.name_action.string, main.data->error.notable.after->string);
            fprintf(main.data->error.to.stream, "%s' requires exactly ", main.data->error.context.before->string);
            fprintf(main.data->error.to.stream, "%s%s%llu%s", main.data->error.context.after->string, main.data->error.notable.before->string, 1, main.data->error.notable.after->string);
            fprintf(main.data->error.to.stream, "%s parameter.%s%c", main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);
          }

          continue;
        }

        if (fl_string_dynamic_partial_compare_string(controller_string_service_s, cache->buffer_file, controller_string_service_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          main.setting->mode = controller_setting_mode_service;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_string_program_s, cache->buffer_file, controller_string_program_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          main.setting->mode = controller_setting_mode_program;
        }
        else {
          if (main.data->warning.verbosity == f_console_verbosity_debug) {
            fprintf(main.data->warning.to.stream, "%s%sUnknown %s item setting value '", main.data->warning.context.before->string, main.data->warning.prefix ? main.data->warning.prefix : f_string_empty_s, is_entry ? controller_string_entry_s : controller_string_exit_s);
            fprintf(main.data->warning.to.stream, "%s%s", main.data->warning.context.after->string, main.data->warning.notable.before->string);
            f_print_dynamic_partial(main.data->warning.to.stream, cache->buffer_file, cache->content_actions.array[i].array[0]);
            fprintf(main.data->warning.to.stream, "%s%s for %s item setting '", main.data->warning.notable.after->string, main.data->warning.context.before->string, is_entry ? controller_string_entry_s : controller_string_exit_s);
            fprintf(main.data->warning.to.stream, "%s%s", main.data->warning.context.after->string, main.data->warning.notable.before->string);
            f_print_dynamic(main.data->warning.to.stream, cache->action.name_action);
            fprintf(main.data->warning.to.stream, "%s", main.data->warning.notable.after->string);
            fprintf(main.data->warning.to.stream, "%s'.%s%c", main.data->warning.context.before->string, main.data->warning.context.after->string, f_string_eol_s[0]);

            controller_entry_error_print_cache(is_entry, main.data->warning, cache->action);
          }

          continue;
        }
      }
      else {
        if (main.data->warning.verbosity == f_console_verbosity_debug) {
          fprintf(main.data->warning.to.stream, "%s%sUnknown %s item setting '", main.data->warning.context.before->string, main.data->warning.prefix ? main.data->warning.prefix : f_string_empty_s, is_entry ? controller_string_entry_s : controller_string_exit_s);
          fprintf(main.data->warning.to.stream, "%s%s", main.data->warning.context.after->string, main.data->warning.notable.before->string);
          f_print_dynamic(main.data->warning.to.stream, cache->action.name_action);
          fprintf(main.data->warning.to.stream, "%s", main.data->warning.notable.after->string);
          fprintf(main.data->warning.to.stream, "%s'.%s%c", main.data->warning.context.before->string, main.data->warning.context.after->string, f_string_eol_s[0]);

          controller_entry_error_print_cache(is_entry, main.data->warning, cache->action);
        }

        continue;
      }
    } // for
  }
#endif // _di_controller_entry_settings_read_

#ifdef __cplusplus
} // extern "C"
#endif
