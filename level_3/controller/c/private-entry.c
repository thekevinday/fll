#include "controller.h"
#include "private-common.h"
#include "private-controller.h"
#include "private-entry.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_entry_action_type_name_
  f_string_static_t controller_entry_action_type_name(const uint8_t type) {

    f_string_static_t buffer = f_string_static_t_initialize;

    switch (type) {
      case controller_entry_action_type_consider:
        buffer.string = controller_string_consider;
        buffer.used = controller_string_consider_length;
        break;

      case controller_entry_action_type_failsafe:
        buffer.string = controller_string_failsafe;
        buffer.used = controller_string_failsafe_length;
        break;

      case controller_entry_action_type_item:
        buffer.string = controller_string_item;
        buffer.used = controller_string_item_length;
        break;

      case controller_entry_action_type_ready:
        buffer.string = controller_string_ready;
        buffer.used = controller_string_ready_length;
        break;

      case controller_entry_action_type_rule:
        buffer.string = controller_string_rule;
        buffer.used = controller_string_rule_length;
        break;

      case controller_entry_action_type_timeout:
        buffer.string = controller_string_timeout;
        buffer.used = controller_string_timeout_length;
        break;
    }

    buffer.size = buffer.used;

    return buffer;
  }
#endif // _di_controller_entry_action_type_name_

#ifndef _di_controller_entry_actions_increase_by_
  f_return_status controller_entry_actions_increase_by(const f_array_length_t amount, controller_entry_actions_t *actions) {

    if (actions->used + amount > actions->size) {
      if (actions->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      const f_status_t status = f_memory_resize((void **) & actions->array, sizeof(controller_entry_action_t), actions->size, actions->used + amount);

      if (F_status_is_error_not(status)) {
        actions->size = actions->used + amount;
      }

      return status;
    }

    return F_none;
  }
#endif // _di_controller_entry_actions_increase_by_

#ifndef _di_controller_entry_actions_read_
  f_return_status controller_entry_actions_read(const controller_data_t data, const controller_setting_t setting, const f_string_range_t content_range, controller_cache_t *cache, controller_entry_actions_t *actions) {
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
      fll_error_print(data.error, F_status_set_fine(status), "fll_fss_extended_read", F_true);

      return status;
    }

    status = fl_fss_apply_delimit(cache->delimits, &cache->buffer_file);

    if (F_status_is_error(status)) {
      fll_error_print(data.error, F_status_set_fine(status), "fl_fss_apply_delimit", F_true);

      return status;
    }

    cache->delimits.used = 0;

    status = controller_entry_actions_increase_by(cache->object_actions.used, actions);

    if (F_status_is_error(status)) {
      fll_error_print(data.error, F_status_set_fine(status), "controller_entry_actions_increase_by", F_true);

      return status;
    }

    controller_entry_action_t *action = 0;

    f_array_length_t allocate = 0;
    f_array_length_t at_least = 0;
    f_array_length_t at_most = 0;

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    for (; i < cache->object_actions.used; ++i) {

      cache->line_action = 0;
      cache->name_action.used = 0;

      action = &actions->array[actions->used];
      action->type = 0;
      action->code = 0;
      action->line = 0;
      action->number = 0;
      action->status = F_known_not;
      action->parameters.used = 0;

      status = f_fss_count_lines(cache->buffer_file, cache->object_actions.array[i].start, &cache->line_action);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "f_fss_count_lines", F_true);
        break;
      }

      action->line = ++cache->line_action;

      status = controller_string_dynamic_rip_nulless_terminated(cache->buffer_file, cache->object_actions.array[i], &cache->name_action);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "controller_string_dynamic_rip_nulless_terminated", F_true);
        break;
      }

      if (fl_string_dynamic_compare_string(controller_string_consider, cache->name_action, controller_string_consider_length) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_consider;
      }
      else if (fl_string_dynamic_compare_string(controller_string_failsafe, cache->name_action, controller_string_failsafe_length) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_failsafe;
      }
      else if (fl_string_dynamic_compare_string(controller_string_item, cache->name_action, controller_string_item_length) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_item;
      }
      else if (fl_string_dynamic_compare_string(controller_string_ready, cache->name_action, controller_string_ready_length) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_ready;
      }
      else if (fl_string_dynamic_compare_string(controller_string_rule, cache->name_action, controller_string_rule_length) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_rule;
      }
      else if (fl_string_dynamic_compare_string(controller_string_timeout, cache->name_action, controller_string_timeout_length) == F_equal_to) {
        actions->array[actions->used].type = controller_entry_action_type_timeout;
      }
      else {
        if (data.warning.verbosity == f_console_verbosity_debug) {
          fprintf(data.warning.to.stream, "%s%sUnknown entry item action '", data.warning.context.before->string, data.warning.prefix ? data.warning.prefix : f_string_empty_s);
          fprintf(data.warning.to.stream, "%s%s", data.warning.context.after->string, data.warning.notable.before->string);
          f_print_dynamic(data.warning.to.stream, cache->name_action);
          fprintf(data.warning.to.stream, "%s", data.warning.notable.after->string);
          fprintf(data.warning.to.stream, "%s'.%s%c", data.warning.context.before->string, data.warning.context.after->string, f_string_eol_s[0]);

          controller_entry_error_print(data.warning, *cache);
        }

        continue;
      }

      if (action->type == controller_entry_action_type_consider || action->type == controller_entry_action_type_rule) {
        allocate = cache->content_actions.array[i].used;
        at_least = 2;
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
      else {
        // for: controller_entry_action_type_ready.
        allocate = 0;
        at_least = 0;
        at_most = 0;
      }

      if (cache->content_actions.array[i].used < at_least || cache->content_actions.array[i].used > at_most) {
        action->status = F_status_set_error(F_parameter);

        if (data.error.verbosity != f_console_verbosity_quiet) {
          fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
          fprintf(data.error.to.stream, "%s%sThe entry item action '", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s);
          fprintf(data.error.to.stream, "%s%s%s%s", data.error.context.after->string, data.error.notable.before->string, cache->name_action.string, data.error.notable.after->string);
          fprintf(data.error.to.stream, "%s' requires ", data.error.context.before->string);

          if (action->type == controller_entry_action_type_failsafe || action->type == controller_entry_action_type_item) {
            fprintf(data.error.to.stream, "%s%s%llu%s", data.error.context.after->string, data.error.notable.before->string, cache->line_action, data.error.notable.after->string);
            fprintf(data.error.to.stream, "%s or more parameters.%s%c", data.error.context.before->string, data.error.context.after->string, f_string_eol_s[0]);
          }
          else {
            uint8_t parameters = 0;

            if (action->type == controller_entry_action_type_failsafe || action->type == controller_entry_action_type_item) {
              parameters = 1;
            }
            else if (action->type == controller_entry_action_type_timeout) {
              parameters = 2;
            }

            fprintf(data.error.to.stream, "exactly ", data.error.context.before->string);
            fprintf(data.error.to.stream, "%s%s%u%s", data.error.context.after->string, parameters, data.error.notable.after->string);
            fprintf(data.error.to.stream, "%s parameters.%s%c", data.error.context.before->string, data.error.context.after->string, f_string_eol_s[0]);
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
        status = fl_string_dynamics_increase_by(allocate, &action->parameters);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamics_increase_by", F_true);

          action->status = status;

          if (F_status_is_error_not(status_action)) {
            status_action = status;
          }

          break;
        }

        for (j = 0; j < allocate; ++j) {

          action->parameters.array[j].used = 0;

          status = fl_string_dynamic_partial_append_nulless(cache->buffer_file, cache->content_actions.array[i].array[j], &action->parameters.array[j]);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_partial_append_nulless", F_true);

            action->status = status;

            if (F_status_is_error_not(status_action)) {
              status_action = status;
            }

            break;
          }

          action->parameters.used++;
        } // for

        if (F_status_is_error_not(action->status)) {
          if (action->type == controller_entry_action_type_consider || action->type == controller_entry_action_type_rule) {
            if (action->parameters.array[0].used) {

              // force the path to be canonical (removing all '../' parts).
              status = fll_path_canonical(action->parameters.array[0].string, &cache->buffer_path);

              if (F_status_is_error(status)) {
                fll_error_print(data.error, F_status_set_fine(status), "fll_path_canonical", F_true);

                action->status = status;

                if (F_status_set_fine(status) == F_memory_not || F_status_set_fine(status) == F_memory_allocation || F_status_set_fine(status) == F_memory_reallocation) {
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

              if (data.error.verbosity != f_console_verbosity_quiet) {
                fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
                fprintf(data.error.to.stream, "%s%sThe entry item action must not have an empty string for a path (the first parameter).%s%c", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s, data.error.context.after->string, f_string_eol_s[0]);
              }
            }

            if (action->parameters.array[1].used) {
              cache->buffer_path.used = 0;

              status = f_file_name_base(action->parameters.array[1].string, action->parameters.array[1].used, &cache->buffer_path);

              if (F_status_is_error(status)) {
                fll_error_print(data.error, F_status_set_fine(status), "f_file_name_base", F_true);

                if (F_status_set_fine(status) == F_memory_not || F_status_set_fine(status) == F_memory_allocation || F_status_set_fine(status) == F_memory_reallocation) {
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

                  if (data.error.verbosity != f_console_verbosity_quiet) {
                    status = fl_string_dynamic_terminate_after(&cache->buffer_path);

                    if (F_status_is_error(status)) {
                      fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_terminate_after", F_true);

                      action->status = status;

                      if (F_status_set_fine(status) == F_memory_not || F_status_set_fine(status) == F_memory_allocation || F_status_set_fine(status) == F_memory_reallocation) {
                        status_action = status;
                      }

                      break;
                    }

                    fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
                    fprintf(data.error.to.stream, "%s%sThe entry item action second parameter '", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s);
                    fprintf(data.error.to.stream, "%s%s%s%s", data.error.context.after->string, data.error.notable.before->string, action->parameters.array[1].string, data.error.notable.after->string);
                    fprintf(data.error.to.stream, "%s' must be a base path name, such as '", data.error.context.before->string);
                    fprintf(data.error.to.stream, "%s%s%s%s", data.error.context.after->string, data.error.notable.before->string, cache->buffer_path.string, data.error.notable.after->string);
                    fprintf(data.error.to.stream, "%s'.%s%c", data.error.context.before->string, data.error.context.after->string, f_string_eol_s[0]);
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

              if (data.error.verbosity != f_console_verbosity_quiet) {
                fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
                fprintf(data.error.to.stream, "%s%sThe entry item action must not have an empty string for a rule name (the second parameter).%s%c", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s, data.error.context.after->string, f_string_eol_s[0]);
              }
            }

            for (j = 2; j < action->parameters.used; ++j) {

              if (fl_string_dynamic_compare_string(controller_string_asynchronous, action->parameters.array[j], controller_string_asynchronous_length) == F_equal_to) {
                action->code = controller_entry_rule_code_asynchronous;
              }
              else if (fl_string_dynamic_compare_string(controller_string_require, action->parameters.array[j], controller_string_require_length) == F_equal_to) {
                action->code = controller_entry_rule_code_require;
              }
              else if (fl_string_dynamic_compare_string(controller_string_wait, action->parameters.array[j], controller_string_wait_length) == F_equal_to) {
                action->code = controller_entry_rule_code_wait;
              }
              else {
                if (action->status == F_none) {
                  action->status = F_status_set_error(F_supported_not);

                  if (F_status_is_error_not(status_action)) {
                    status_action = action->status;
                  }
                }

                if (data.error.verbosity != f_console_verbosity_quiet) {
                  fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
                  fprintf(data.error.to.stream, "%s%sThe entry item action third parameter (and beyond) must be one of '", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s);
                  fprintf(data.error.to.stream, "%s%s%s%s", data.error.context.after->string, data.error.notable.before->string, controller_string_asynchronous, data.error.notable.after->string);
                  fprintf(data.error.to.stream, "%s', '", data.error.context.before->string);
                  fprintf(data.error.to.stream, "%s%s%s%s", data.error.context.after->string, data.error.notable.before->string, controller_string_require, data.error.notable.after->string);
                  fprintf(data.error.to.stream, "%s', or '", data.error.context.before->string);
                  fprintf(data.error.to.stream, "%s%s%s%s", data.error.context.after->string, data.error.notable.before->string, controller_string_wait, data.error.notable.after->string);
                  fprintf(data.error.to.stream, "%s' but instead has '", data.error.context.before->string);
                  fprintf(data.error.to.stream, "%s%s%s%s", data.error.context.after->string, data.error.notable.before->string, action->parameters.array[j].string, data.error.notable.after->string);
                  fprintf(data.error.to.stream, "%s'.%s%c", data.error.context.before->string, data.error.context.after->string, f_string_eol_s[0]);
                }
              }
            } // for
          }
          else if (action->type == controller_entry_action_type_failsafe || action->type == controller_entry_action_type_item) {
            if (fl_string_dynamic_compare_string(controller_string_main, action->parameters.array[0], controller_string_main_length) == F_equal_to) {
              action->status = F_status_set_error(F_supported_not);

              if (F_status_is_error_not(status_action)) {
                status_action = action->status;
              }

              if (data.error.verbosity != f_console_verbosity_quiet) {
                fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
                fprintf(data.error.to.stream, "%s%sThe entry item action may not specify the reserved item '", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s);
                fprintf(data.error.to.stream, "%s%s%s%s", data.error.context.after->string, data.error.notable.before->string, controller_string_main, data.error.notable.after->string);
                fprintf(data.error.to.stream, "%s'.%s%c", data.error.context.before->string, data.error.context.after->string, f_string_eol_s[0]);
              }
            }
          }
          else if (action->type == controller_entry_action_type_timeout) {

            if (fl_string_dynamic_compare_string(controller_string_kill, action->parameters.array[0], controller_string_kill_length) == F_equal_to) {
              action->code = controller_entry_timeout_code_kill;
            }
            else if (fl_string_dynamic_compare_string(controller_string_start, action->parameters.array[0], controller_string_start_length) == F_equal_to) {
              action->code = controller_entry_timeout_code_start;
            }
            else if (fl_string_dynamic_compare_string(controller_string_stop, action->parameters.array[0], controller_string_stop_length) == F_equal_to) {
              action->code = controller_entry_timeout_code_stop;
            }
            else {
              action->status = F_status_set_error(F_supported_not);

              if (F_status_is_error_not(status_action)) {
                status_action = action->status;
              }

              if (data.error.verbosity != f_console_verbosity_quiet) {
                fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
                fprintf(data.error.to.stream, "%s%sThe entry item action must have one of '", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s);
                fprintf(data.error.to.stream, "%s%s%s%s", data.error.context.after->string, data.error.notable.before->string, controller_string_kill, data.error.notable.after->string);
                fprintf(data.error.to.stream, "%s', '", data.error.context.before->string);
                fprintf(data.error.to.stream, "%s%s%s%s", data.error.context.after->string, data.error.notable.before->string, controller_string_start, data.error.notable.after->string);
                fprintf(data.error.to.stream, "%s', or '", data.error.context.before->string);
                fprintf(data.error.to.stream, "%s%s%s%s", data.error.context.after->string, data.error.notable.before->string, controller_string_stop, data.error.notable.after->string);
                fprintf(data.error.to.stream, "%s' but instead has '", data.error.context.before->string);
                fprintf(data.error.to.stream, "%s%s%s%s", data.error.context.after->string, data.error.notable.before->string, action->parameters.array[0].string, data.error.notable.after->string);
                fprintf(data.error.to.stream, "%s'.%s%c", data.error.context.before->string, data.error.context.after->string, f_string_eol_s[0]);
              }
            }

            if (action->status == F_none) {
              const f_string_range_t range = f_macro_string_range_t_initialize(action->parameters.array[1].used);

              status = fl_conversion_string_to_number_unsigned(action->parameters.array[1].string, &action->number, range);

              if (F_status_is_error(status) || status == F_data_not) {
                action->number = 0;

                if (status == F_data_not) {
                  action->status = F_status_set_error(F_number);
                }
                else {
                  action->status = controller_status_simplify(F_status_set_fine(status));
                }

                if (F_status_set_fine(status) == F_memory_not || F_status_set_fine(status) == F_memory_allocation || F_status_set_fine(status) == F_memory_reallocation) {
                  fll_error_print(data.error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true);

                  status_action = status;
                  break;
                }

                if (data.error.verbosity != f_console_verbosity_quiet) {
                  fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
                  fprintf(data.error.to.stream, "%s%sThe entry item action parameter '", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s);
                  fprintf(data.error.to.stream, "%s%s%s%s", data.error.context.after->string, data.error.notable.before->string, action->parameters.array[1].string, data.error.notable.after->string);
                  fprintf(data.error.to.stream, "%s' is not a valid supported number.%s%c", data.error.context.before->string, data.error.context.after->string, f_string_eol_s[0]);
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
  void controller_entry_error_print(const fll_error_print_t output, const controller_cache_t cache) {

    if (output.verbosity != f_console_verbosity_quiet) {
      fprintf(output.to.stream, "%c", f_string_eol_s[0]);
      fprintf(output.to.stream, "%s%sWhile processing ", output.context.before->string, output.prefix ? output.prefix : f_string_empty_s);

      if (cache.name_action.used) {
        fprintf(output.to.stream, "action '");
        fprintf(output.to.stream, "%s%s%s%s", output.context.after->string, output.notable.before->string, cache.name_action.string, output.notable.after->string);
        fprintf(output.to.stream, "%s' on line ", output.context.before->string);
        fprintf(output.to.stream, "%s%s%llu%s", output.context.after->string, output.notable.before->string, cache.line_action, output.notable.after->string);
        fprintf(output.to.stream, "%s for ", output.context.before->string);
      }

      if (cache.name_item.used) {
        fprintf(output.to.stream, "entry item '");
        fprintf(output.to.stream, "%s%s%s%s", output.context.after->string, output.notable.before->string, cache.name_item.string, output.notable.after->string);
        fprintf(output.to.stream, "%s' on line ", output.context.before->string);
        fprintf(output.to.stream, "%s%s%llu%s", output.context.after->string, output.notable.before->string, cache.line_item, output.notable.after->string);
        fprintf(output.to.stream, "%s for ", output.context.before->string);
      }

      if (cache.name_file.used) {
        fprintf(output.to.stream, "file '");
        fprintf(output.to.stream, "%s%s%s%s", output.context.after->string, output.notable.before->string, cache.name_file.string, output.notable.after->string);
        fprintf(output.to.stream, "%s'.%s%c", output.context.before->string, output.context.after->string, f_string_eol_s[0]);
      }
    }
  }
#endif // _di_controller_entry_error_print_

#ifndef _di_controller_entry_items_increase_by_
  f_return_status controller_entry_items_increase_by(const f_array_length_t amount, controller_entry_items_t *items) {

    if (items->used + amount > items->size) {
      if (items->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      const f_status_t status = f_memory_resize((void **) & items->array, sizeof(controller_entry_item_t), items->size, items->used + amount);

      if (F_status_is_error_not(status)) {
        items->size = items->used + amount;
      }

      return status;
    }

    return F_none;
  }
#endif // _di_controller_entry_items_increase_by_

#ifndef _di_controller_entry_read_
  f_return_status controller_entry_read(const controller_data_t data, const controller_setting_t setting, const f_string_static_t entry_name, controller_cache_t *cache, controller_entry_t *entry) {
    f_status_t status = F_none;

    entry->status = F_known_not;
    entry->items.used = 0;

    cache->line_action = 0;
    cache->line_item = 0;

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

    cache->name_file.used = 0;
    cache->name_action.used = 0;
    cache->name_item.used = 0;

    status = controller_file_load(data, setting, controller_string_entries, entry_name, controller_string_entry, controller_string_entries_length, controller_string_entry_length, cache);

    if (F_status_is_error_not(status)) {
      if (cache->buffer_file.used) {
        f_string_range_t range = f_macro_string_range_t_initialize(cache->buffer_file.used);

        status = fll_fss_basic_list_read(cache->buffer_file, &range, &cache->object_items, &cache->content_items, &cache->delimits, 0, &cache->comments);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "fll_fss_basic_list_read", F_true);
        }
        else {
          status = fl_fss_apply_delimit(cache->delimits, &cache->buffer_file);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "fl_fss_apply_delimit", F_true);
          }
        }
      }
      else {
        if (data.error.verbosity != f_console_verbosity_quiet) {
          fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
          fprintf(data.error.to.stream, "%s%sThe entry file is empty.%s%c", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s, data.error.context.after->string, f_string_eol_s[0]);
        }

        status = F_status_set_error(F_data_not);
      }
    }

    if (F_status_is_error_not(status) && cache->object_items.used) {
      status = controller_entry_items_increase_by(cache->object_items.used, &entry->items);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "controller_entry_items_increase_by", F_true);
      }
      else {

        // 0x1 = main found, 0x2 = found existing.
        uint8_t code = 0;

        f_string_range_t *range = 0;

        f_array_length_t at = 0;
        f_array_length_t i = 0;
        f_array_length_t j = 0;

        for (; i < cache->object_items.used; ++i) {

          if (code & 0x2) {
            code -= 0x2;
          }

          at = 0;
          range = 0;

          cache->line_action = 0;
          cache->line_item = 0;

          cache->comments.used = 0;
          cache->delimits.used = 0;

          cache->content_action.used = 0;
          cache->content_actions.used = 0;

          cache->object_actions.used = 0;

          cache->buffer_path.used = 0;

          cache->name_action.used = 0;
          cache->name_item.used = 0;

          status = controller_entry_items_increase_by(controller_default_allocation_step, &entry->items);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "controller_entry_items_increase_by", F_true);
            break;
          }

          status = controller_string_dynamic_partial_append_terminated(cache->buffer_file, cache->object_items.array[i], &cache->name_item);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "controller_string_dynamic_partial_append_terminated", F_true);
            break;
          }

          status = f_fss_count_lines(cache->buffer_file, cache->object_items.array[i].start, &cache->line_item);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "f_fss_count_lines", F_true);
            break;
          }

          cache->line_item++;

          for (j = (code & 0x1) ? 1 : 0; j < entry->items.used; ++j) {

            if (fl_string_dynamic_compare(entry->items.array[j].name, cache->name_item) == F_equal_to) {
              if (data.warning.verbosity == f_console_verbosity_debug) {
                fprintf(data.warning.to.stream, "%c", f_string_eol_s[0]);
                fprintf(data.warning.to.stream, "%s%sIgnoring duplicate entry item '", data.warning.context.before->string, data.warning.prefix ? data.warning.prefix : f_string_empty_s);
                fprintf(data.warning.to.stream, "%s%s%s%s", data.warning.context.after->string, data.warning.notable.before->string, cache->name_file.string, data.warning.notable.after->string);
                fprintf(data.warning.to.stream, "%s'.%s%c", data.warning.context.before->string, data.warning.context.after->string, f_string_eol_s[0]);

                controller_entry_error_print(data.warning, *cache);
              }

              code |= 0x2;
              break;
            }
          } // for

          if (code & 0x2) continue;

          range = &cache->content_items.array[i].array[0];

          if (fl_string_dynamic_compare_string(controller_string_main, cache->name_item, controller_string_main_length) == F_equal_to) {
            code |= 0x1;

            at = 0;

            if (!entry->items.used) {
              entry->items.used = 1;
            }
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

          entry->items.array[at].line = cache->line_item;

          status = controller_string_dynamic_append_terminated(cache->name_item, &entry->items.array[at].name);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "controller_string_dynamic_append_terminated", F_true);
            break;
          }

          status = controller_entry_actions_read(data, setting, *range, cache, &entry->items.array[at].actions);

          if (F_status_is_error(status)) {
            controller_entry_error_print(data.error, *cache);

            if (F_status_set_fine(status) == F_memory_not || F_status_set_fine(status) == F_memory_allocation || F_status_set_fine(status) == F_memory_reallocation) {
              break;
            }
          }
        } // for

        if (F_status_is_error_not(status)) {
          cache->name_action.used = 0;
          cache->name_item.used = 0;

          if (!(code & 0x1)) {
            if (data.error.verbosity != f_console_verbosity_quiet) {
              fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
              fprintf(data.error.to.stream, "%s%sThe required entry item '", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s);
              fprintf(data.error.to.stream, "%s%s%s%s", data.error.context.after->string, data.error.notable.before->string, controller_string_main, data.error.notable.after->string);
              fprintf(data.error.to.stream, "%s' was not found.%s%c", data.error.context.before->string, data.error.context.after->string, f_string_eol_s[0]);
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

                    cache->line_action = action->line;
                    cache->line_item = entry->items.array[i].line;

                    status = controller_string_dynamic_append_terminated(entry->items.array[i].name, &cache->name_item);

                    if (F_status_is_error(status)) {
                      fll_error_print(data.error, F_status_set_fine(status), "controller_string_dynamic_append_terminated", F_true);
                      break;
                    }

                    if (data.error.verbosity != f_console_verbosity_quiet) {
                      fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
                      fprintf(data.error.to.stream, "%s%sThe required entry item '", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s);
                      fprintf(data.error.to.stream, "%s%s%s%s", data.error.context.after->string, data.error.notable.before->string, action->parameters.array[0].string, data.error.notable.after->string);
                      fprintf(data.error.to.stream, "%s' does not exist.%s%c", data.error.context.before->string, data.error.context.after->string, f_string_eol_s[0]);

                      controller_entry_error_print(data.error, *cache);
                    }

                    action->number = 0;
                    action->status = controller_status_simplify(F_found_not);

                    // @fixme review how entry->status is being handled with respect to action->status (here the action failed, should the entire entry fail? at the moment if mode is simulation this prevents simulation from continuing).
                    //entry->status = controller_status_simplify(F_found_not);

                    cache->name_action.used = 0;
                    cache->name_item.used = 0;
                  }
                  else {
                    action->number = k;
                  }
                }
              } // for
            } // for

            // the error is already fully printed and the entry status is already assigned, so immediately exit.
            if (missing & 0x2) {
              // @fixme review how entry->status is being handled with respect to action->status (here the action failed, should the entire entry fail? at the moment if mode is simulation this prevents simulation from continuing).
              //return entry->status;
            }
          }
        }
      }
    }

    if (F_status_is_error(status)) {
      controller_entry_error_print(data.error, *cache);

      entry->status = controller_status_simplify(F_status_set_fine(status));
    }
    else {
      entry->status = F_none;
    }

    return entry->status;
  }
#endif // _di_controller_entry_read_

#ifdef __cplusplus
} // extern "C"
#endif
