#include "controller.h"
#include "private-common.h"
#include "private-controller.h"
#include "private-rule.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_rule_action_method_name_
  f_string_static_t controller_rule_action_method_name(const uint8_t type) {

    f_string_static_t buffer = f_string_static_t_initialize;

    switch (type) {
      case controller_rule_action_method_extended:
        buffer.string = controller_rule_action_method_string_extended;
        buffer.used = controller_rule_action_method_string_extended_length;
        break;

      case controller_rule_action_method_extended_list:
        buffer.string = controller_rule_action_method_string_extended_list;
        buffer.used = controller_rule_action_method_string_extended_list_length;
        break;
    }

    buffer.size = buffer.used;

    return buffer;
  }
#endif // _di_controller_rule_action_method_name_

#ifndef _di_controller_rule_parameters_read_
  f_status_t controller_rule_parameters_read(const controller_data_t data, const f_string_static_t buffer, f_fss_object_t *object, f_fss_content_t *content, f_string_dynamics_t *parameters) {
    f_status_t status = F_none;

    parameters->used = 0;

    if (object && object->start <= object->start) {
      status = f_string_dynamics_increase(parameters);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamics_increase", F_true);
        return status;
      }

      parameters->array[parameters->used].used = 0;

      status = f_string_dynamic_partial_append_nulless(buffer, *object, &parameters->array[0]);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true);
        return status;
      }

      status = f_string_dynamic_terminate_after(&parameters->array[0]);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);
        return status;
      }

      parameters->used++;
    }

    if (content && content->used) {
      for (f_array_length_t i = 0; i < content->used; ++i) {

        if (content->array[i].start > content->array[i].start) continue;

        status = f_string_dynamics_increase(parameters);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamics_increase", F_true);
          return status;
        }

        parameters->array[parameters->used].used = 0;

        status = f_string_dynamic_partial_append_nulless(buffer, content->array[i], &parameters->array[parameters->used]);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true);
          return status;
        }

        status = f_string_dynamic_terminate_after(&parameters->array[parameters->used]);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);
          return status;
        }

        parameters->used++;
      } // for
    }

    return F_none;
  }
#endif // _di_controller_rule_parameters_read_

#ifndef _di_controller_rule_action_type_name_
  f_string_static_t controller_rule_action_type_name(const uint8_t type) {

    f_string_static_t buffer = f_string_static_t_initialize;

    switch (type) {
      case controller_rule_action_type_create:
        buffer.string = controller_string_create_s;
        buffer.used = controller_string_create_length;
        break;

      case controller_rule_action_type_group:
        buffer.string = controller_string_group_s;
        buffer.used = controller_string_group_length;
        break;

      case controller_rule_action_type_kill:
        buffer.string = controller_string_kill_s;
        buffer.used = controller_string_kill_length;
        break;

      case controller_rule_action_type_restart:
        buffer.string = controller_string_restart_s;
        buffer.used = controller_string_restart_length;
        break;

      case controller_rule_action_type_reload:
        buffer.string = controller_string_reload_s;
        buffer.used = controller_string_reload_length;
        break;

      case controller_rule_action_type_start:
        buffer.string = controller_string_start_s;
        buffer.used = controller_string_start_length;
        break;

      case controller_rule_action_type_stop:
        buffer.string = controller_string_stop_s;
        buffer.used = controller_string_stop_length;
        break;

      case controller_rule_action_type_use:
        buffer.string = controller_string_use_s;
        buffer.used = controller_string_use_length;
        break;

      case controller_rule_action_type_user:
        buffer.string = controller_string_user_s;
        buffer.used = controller_string_user_length;
        break;
    }

    buffer.size = buffer.used;

    return buffer;
  }
#endif // _di_controller_rule_action_type_name_

#ifndef _di_controller_rule_actions_increase_by_
  f_status_t controller_rule_actions_increase_by(const f_array_length_t amount, controller_rule_actions_t *actions) {

    if (actions->used + amount > actions->size) {
      if (actions->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      const f_status_t status = f_memory_resize((void **) & actions->array, sizeof(controller_rule_action_t), actions->size, actions->used + amount);

      if (F_status_is_error_not(status)) {
        actions->size = actions->used + amount;
      }

      return status;
    }

    return F_none;
  }
#endif // _di_controller_rule_actions_increase_by_

#ifndef _di_controller_rule_action_read_
  f_status_t controller_rule_action_read(const controller_data_t data, const uint8_t type, const uint8_t method, controller_cache_t *cache, controller_rule_item_t *item, controller_rule_actions_t *actions, f_string_range_t *range) {
    f_status_t status = F_none;

    if (method == controller_rule_action_method_extended_list) {
      cache->comments.used = 0;
      cache->delimits.used = 0;
      cache->content_action.used = 0;
      cache->content_actions.used = 0;
      cache->object_actions.used = 0;

      if (actions->size) {
        actions->array[actions->used].parameters.used = 0;
      }

      status = fl_fss_extended_list_content_read(cache->buffer_item, range, &cache->content_action, &cache->delimits, &cache->comments);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "fl_fss_extended_list_content_read", F_true);
      }
      else if (status == FL_fss_found_content) {
        status = fl_fss_apply_delimit(cache->delimits, &cache->buffer_item);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "fl_fss_apply_delimit", F_true);
        }
        else {

          // "script" types use the entire content and can be directly passed through.
          if (item->type == controller_rule_item_type_script) {
            actions->array[actions->used].parameters.used = 0;

            status = f_string_dynamics_increase(&actions->array[actions->used].parameters);

            if (F_status_is_error(status)) {
              fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamics_increase", F_true);
            }
            else {
              actions->array[actions->used].type = type;
              actions->array[actions->used].line = cache->line_action;
              actions->array[actions->used].parameters.used = 0;
              actions->array[actions->used].status = F_known_not;

              status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_action.array[0], &actions->array[actions->used].parameters.array[0]);

              if (F_status_is_error(status)) {
                fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamic_append_nulless", F_true);
              }

              status = f_string_dynamic_terminate_after(&actions->array[actions->used].parameters.array[0]);

              if (F_status_is_error(status)) {
                fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);
              }
              else {
                actions->array[actions->used].parameters.used = 1;
                actions->used++;
              }
            }

            return status;
          }

          // the object_actions and content_actions caches are being used for the purposes of getting the parameters a given the action.
          status = fll_fss_extended_read(cache->buffer_item, &cache->content_action.array[0], &cache->object_actions, &cache->content_actions, 0, 0, &cache->delimits, 0);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "fll_fss_extended_read", F_true);
          }
          else {
            status = fl_fss_apply_delimit(cache->delimits, &cache->buffer_item);

            if (F_status_is_error(status)) {
              fll_error_print(data.error, F_status_set_fine(status), "fl_fss_apply_delimit", F_true);
            }
            else {
              f_array_length_t i = 0;
              f_array_length_t j = 0;

              for (; i < cache->object_actions.used; ++i) {

                status = controller_rule_actions_increase_by(controller_default_allocation_step, actions);

                if (F_status_is_error(status)) {
                  fll_error_print(data.error, F_status_set_fine(status), "controller_rule_actions_increase_by", F_true);
                  break;
                }

                status = f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &actions->array[actions->used].line);

                if (F_status_is_error(status)) {
                  fll_error_print(data.error, F_status_set_fine(status), "f_fss_count_lines", F_true);
                  break;
                }

                actions->array[actions->used].type = type;
                actions->array[actions->used].line += ++item->line;
                actions->array[actions->used].parameters.used = 0;
                actions->array[actions->used].status = F_known_not;

                status = f_string_dynamics_increase(&actions->array[actions->used].parameters);

                if (F_status_is_error(status)) {
                  fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamics_increase", F_true);

                  actions->array[actions->used].status = controller_status_simplify(F_status_set_fine(status));
                  break;
                }

                status = controller_rule_parameters_read(data, cache->buffer_item, &cache->object_actions.array[i], &cache->content_actions.array[i], &actions->array[actions->used].parameters);

                actions->array[actions->used].status = controller_status_simplify(F_status_set_fine(status));
                actions->used++;
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

      status = fl_fss_extended_content_read(cache->buffer_item, range, &cache->content_action, 0, &cache->delimits);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "fll_fss_extended_content_read", F_true);
      }
      else if (status == FL_fss_found_content) {
        status = fl_fss_apply_delimit(cache->delimits, &cache->buffer_item);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "fl_fss_apply_delimit", F_true);
        }
        else if (item->type == controller_rule_item_type_script) {
          status = f_string_dynamics_increase(&actions->array[actions->used].parameters);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamics_increase", F_true);
          }
          else {

            // "script" types use the entire content as a single string piped to the script, so merge all arguments together.
            actions->array[actions->used].type = type;
            actions->array[actions->used].line = cache->line_action;
            actions->array[actions->used].parameters.used = 0;
            actions->array[actions->used].status = F_known_not;

            for (f_array_length_t i = 0; i < cache->content_action.used; ++i) {

              status = f_string_dynamic_partial_mash_nulless(f_string_space_s, f_string_space_length, cache->buffer_item, cache->content_action.array[i], &actions->array[actions->used].parameters.array[0]);
              if (F_status_is_error(status)) break;
            } // for

            if (F_status_is_error_not(status)) {
              status = f_string_dynamic_terminate_after(&actions->array[actions->used].parameters.array[0]);

              if (F_status_is_error(status)) {
                fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);
              }
              else {
                actions->array[actions->used].parameters.used = 1;
                actions->used++;
              }
            }
          }

          return status;
        }
        else {
          status = f_fss_count_lines(cache->buffer_item, range->start, &actions->array[actions->used].line);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "f_fss_count_lines", F_true);
          }
          else {
            actions->array[actions->used].type = type;
            actions->array[actions->used].line += ++item->line;
            actions->array[actions->used].parameters.used = 0;
            actions->array[actions->used].status = F_known_not;

            status = controller_rule_parameters_read(data, cache->buffer_item, 0, &cache->content_action, &actions->array[actions->used].parameters);

            if (F_status_is_error(status)) {
              fll_error_print(data.error, F_status_set_fine(status), "controller_rule_parameters_read", F_true);

              actions->array[actions->used].status = controller_status_simplify(F_status_set_fine(status));
            }
            else {
              actions->array[actions->used].status = status;
            }

            actions->used++;
          }
        }
      }
      else {
        status = F_data_not;
      }
    }

    if (F_status_is_error_not(status) && status == F_data_not) {
      if (data.warning.verbosity == f_console_verbosity_debug) {
        fprintf(data.warning.to.stream, "%c", f_string_eol_s[0]);
        fprintf(data.warning.to.stream, "%s%sAction is empty, nothing to do.%s%c", data.warning.context.before->string, data.warning.prefix ? data.warning.prefix : f_string_empty_s, data.warning.context.after->string, f_string_eol_s[0]);

        controller_rule_error_print(data.warning, *cache, F_true);
      }
    }

    return status;
  }
#endif // _di_controller_rule_action_read_

#ifndef _di_controller_rule_error_print_
  void controller_rule_error_print(const fll_error_print_t output, const controller_cache_t cache, const bool item) {

    if (output.verbosity != f_console_verbosity_quiet) {
      fprintf(output.to.stream, "%c", f_string_eol_s[0]);
      fprintf(output.to.stream, "%s%sWhile processing ", output.context.before->string, output.prefix ? output.prefix : f_string_empty_s);

      if (cache.name_action.used) {
        fprintf(output.to.stream, "%s '", item ? "action" : "value");
        fprintf(output.to.stream, "%s%s", output.context.after->string, output.notable.before->string);
        f_print_dynamic(output.to.stream, cache.name_action);
        fprintf(output.to.stream, "%s%s' on line ", output.notable.after->string, output.context.before->string);
        fprintf(output.to.stream, "%s%s%llu%s", output.context.after->string, output.notable.before->string, cache.line_action, output.notable.after->string);
        fprintf(output.to.stream, "%s for ", output.context.before->string);
      }

      if (cache.name_item.used) {
        fprintf(output.to.stream, "rule %s '", item ? "item" : "setting");
        fprintf(output.to.stream, "%s%s", output.context.after->string, output.notable.before->string);
        f_print_dynamic(output.to.stream, cache.name_item);
        fprintf(output.to.stream, "%s%s' on line ", output.notable.after->string, output.context.before->string);
        fprintf(output.to.stream, "%s%s%llu%s", output.context.after->string, output.notable.before->string, cache.line_item, output.notable.after->string);
        fprintf(output.to.stream, "%s for ", output.context.before->string);
      }

      if (cache.name_file.used) {
        fprintf(output.to.stream, "file '");
        fprintf(output.to.stream, "%s%s", output.context.after->string, output.notable.before->string);
        f_print_dynamic(output.to.stream, cache.name_file);
        fprintf(output.to.stream, "%s'.%s%c", output.context.before->string, output.context.after->string, f_string_eol_s[0]);
      }
    }
  }
#endif // _di_controller_rule_error_print_

#ifndef _di_controller_rule_error_print_execute_
  void controller_rule_error_print_execute(const fll_error_print_t output, const bool script_is, const f_string_t name, const int code, const f_status_t status) {

    if (output.verbosity != f_console_verbosity_quiet) {
      fprintf(output.to.stream, "%c", f_string_eol_s[0]);
      fprintf(output.to.stream, "%s%sThe %s '", output.context.before->string, output.prefix ? output.prefix : f_string_empty_s, script_is ? controller_string_script_s : controller_string_program_s);
      fprintf(output.to.stream, "%s%s%s%s", output.context.after->string, output.notable.before->string, name ? name : f_string_empty_s, output.notable.after->string);

      if (status == F_control_group || status == F_limit || status == F_processor || status == F_schedule) {
        fprintf(output.to.stream, "%s' failed due to a failure to setup the '", output.context.before->string);

        fprintf(output.to.stream, "%s%s", output.context.after->string, output.notable.before->string);
        if (status == F_control_group) {
          fprintf(output.to.stream, "%s", controller_string_control_group_s);
        }
        else if (status == F_limit) {
          fprintf(output.to.stream, "%s", controller_string_limit_s);
        }
        else if (status == F_processor) {
          fprintf(output.to.stream, "%s", controller_string_processor_s);
        }
        else if (status == F_schedule) {
          fprintf(output.to.stream, "%s", controller_string_scheduler_s);
        }
        fprintf(output.to.stream, "%s", output.notable.after->string);
        fprintf(output.to.stream, "%s'.%s%c", output.context.before->string, output.context.after->string, f_string_eol_s[0]);
      }
      else if (code) {
        fprintf(output.to.stream, "%s' failed with the exit code '", output.context.before->string);
        fprintf(output.to.stream, "%s%s%i%s", output.context.after->string, output.notable.before->string, code, output.notable.after->string);
        fprintf(output.to.stream, "%s'.%s%c", output.context.before->string, output.context.after->string, f_string_eol_s[0]);
      }
      else {
        fprintf(output.to.stream, "%s' failed.%s%c", output.context.before->string, output.context.after->string, f_string_eol_s[0]);
      }
    }
  }
#endif // _di_controller_rule_error_print_execute_

#ifndef _di_controller_rule_error_print_execute_not_found_
  void controller_rule_error_print_execute_not_found(const fll_error_print_t output, const bool script_is, const f_string_t name) {

    if (output.verbosity != f_console_verbosity_quiet) {
      fprintf(output.to.stream, "%c", f_string_eol_s[0]);
      fprintf(output.to.stream, "%s%sThe %s '", output.context.before->string, output.prefix ? output.prefix : f_string_empty_s, script_is ? controller_string_script_s : controller_string_program_s);
      fprintf(output.to.stream, "%s%s%s%s", output.context.after->string, output.notable.before->string, name ? name : f_string_empty_s, output.notable.after->string);
      fprintf(output.to.stream, "%s' could not be executed because it was not found.%s%c", output.context.before->string, output.context.after->string, f_string_eol_s[0]);
    }
  }
#endif // _di_controller_rule_error_print_execute_not_found_

#ifndef _di_controller_rule_error_print_need_want_wish_
  void controller_rule_error_print_need_want_wish(const fll_error_print_t output, const f_string_t need_want_wish, const f_string_t value, const f_string_t why) {

    if (output.verbosity != f_console_verbosity_quiet) {
      fprintf(output.to.stream, "%c", f_string_eol_s[0]);
      fprintf(output.to.stream, "%s%sThe %s rule '", output.context.before->string, output.prefix ? output.prefix : f_string_empty_s, need_want_wish);
      fprintf(output.to.stream, "%s%s%s%s", output.context.after->string, output.notable.before->string, value, output.notable.after->string);
      fprintf(output.to.stream, "%s' %s.%s%c", output.context.before->string, why, output.context.after->string, f_string_eol_s[0]);
    }
  }
#endif // _di_controller_rule_error_print_need_want_wish_

#ifndef _di_controller_rule_execute_
  f_status_t controller_rule_execute(const controller_cache_t cache, const f_array_length_t index, const uint8_t type, const bool simulate, controller_data_t *data, controller_setting_t *setting) {
    f_status_t status = F_none;
    f_status_t success = F_false;

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t k = 0;

    controller_rule_t *rule = &setting->rules.array[index];
    controller_rule_item_t *item = 0;
    controller_rule_action_t *action = 0;

    // child processes should receive all signals, without blocking.
    f_signal_how_t signals = f_signal_how_t_initialize;
    f_signal_set_empty(&signals.block);
    f_signal_set_fill(&signals.block_not);

    f_string_maps_t environment = f_string_maps_t_initialize;

    const f_string_dynamics_t arguments_none = f_string_dynamics_t_initialize;
    fl_execute_parameter_t parameter = fl_macro_execute_parameter_t_initialize(0, &environment, &signals, 0);
    fl_execute_as_t as = fl_execute_as_t_initialize;

    if (rule->affinity.used) {
      as.affinity = &rule->affinity;
    }

    if (rule->capability) {
      as.capability = rule->capability;
    }

    if (rule->has & controller_rule_has_control_group) {
      as.control_group = &rule->control_group;

      // make sure all required cgroup directories exist.
      if (rule->status == F_known_not) {
        status = fll_control_group_prepare(rule->control_group);

        if (F_status_is_error(status)) {
          fll_error_print(data->error, F_status_set_fine(status), "fll_control_group_prepare", F_true);

          rule->status = F_status_set_error(F_failure);
          return status;
        }
      }
    }

    if (rule->has & controller_rule_has_group) {
      as.id_group = &rule->group;

      if (rule->groups.used) {
        as.id_groups = &rule->groups;
      }
    }

    if (rule->limits.used) {
      as.limits = &rule->limits;
    }

    if (rule->has & controller_rule_has_scheduler) {
      as.scheduler = &rule->scheduler;
    }

    if (rule->has & controller_rule_has_nice) {
      as.nice = &rule->nice;
    }

    if (rule->has & controller_rule_has_user) {
      as.id_user = &rule->user;
    }

    status = fll_environment_load_names(rule->environment, &environment);

    if (F_status_is_error(status)) {
      fll_error_print(data->error, F_status_set_fine(status), "fll_environment_load_names", F_true);

      rule->status = F_status_set_error(F_failure);
      return status;
    }

    for (i = 0; i < rule->items.used; ++i) {

      if (rule->items.array[i].type == controller_rule_item_type_setting) continue;

      item = &rule->items.array[i];

      for (j = 0; j < item->actions.used; ++j) {

        if (item->actions.array[j].type != type) continue;

        action = &item->actions.array[j];

        parameter.data = 0;
        parameter.option = 0;

        if (item->type == controller_rule_item_type_command) {

          if (strchr(action->parameters.array[0].string, f_path_separator_s[0])) {
            parameter.option |= fl_execute_parameter_option_path;
          }

          status = controller_rule_execute_foreground(item->type, *action, simulate, 0, action->parameters, 0, &parameter, &as, data);

          if (status == F_child) {
            break;
          }

          if (F_status_is_error(status)) {
            action->status = F_status_set_error(F_failure);

            if (!simulate) break;
          }

          success = F_true;
        }
        else if (item->type == controller_rule_item_type_script) {
          parameter.data = &action->parameters.array[0];

          if (rule->script.used && strchr(rule->script.string, f_path_separator_s[0])) {
            parameter.option |= fl_execute_parameter_option_path;
          }

          status = controller_rule_execute_foreground(item->type, *action, simulate, rule->script.used ? rule->script.string : controller_default_program_script, arguments_none, 0, &parameter, &as, data);

          if (status == F_child) {
            break;
          }

          if (F_status_is_error(status)) {
            action->status = F_status_set_error(F_failure);

            if (!simulate) break;
          }

          success = F_true;
        }
        else if (item->type == controller_rule_item_type_service) {

          if (strchr(action->parameters.array[0].string, f_path_separator_s[0])) {
            parameter.option |= fl_execute_parameter_option_path;
          }

          status = controller_rule_execute_pid_with(item->type, *action, simulate, 0, action->parameters, 0, &parameter, &as, data);

          if (F_status_is_error(status)) {
            action->status = F_status_set_error(F_failure);

            if (!simulate) break;
          }

          success = F_true;
        }
        else {

          if (data->warning.verbosity == f_console_verbosity_debug) {
            fprintf(data->warning.to.stream, "%c", f_string_eol_s[0]);
            fprintf(data->warning.to.stream, "%s%sAction type is unknown, ignoring.%s%c", data->warning.context.before->string, data->warning.prefix ? data->warning.prefix : f_string_empty_s, data->warning.context.after->string, f_string_eol_s[0]);

            controller_rule_error_print(data->warning, cache, F_true);
          }

          action->status = F_ignore;

          if (success != F_true) {
            success = F_ignore;
          }

          continue;
        }

        if (status == F_child || status == F_signal) break;
      } // for

      if (status == F_child || status == F_signal || F_status_is_error(status) && !simulate) break;
    } // for

    f_string_maps_delete(&environment);

    if (status == F_child) {
      return status;
    }

    if (F_status_is_error(status) || success == F_false) {
      rule->status = F_status_set_error(F_failure);
    }
    else if (success == F_ignore || success == F_busy) {
      rule->status = success;
    }
    else {
      rule->status = F_none;
    }

    return rule->status;
  }
#endif // _di_controller_rule_execute_

#ifndef _di_controller_rule_execute_pid_with_
  f_status_t controller_rule_execute_pid_with(const uint8_t type, const controller_rule_action_t action, const bool simulate, const f_string_t program, const f_string_dynamics_t arguments, const uint8_t options, fl_execute_parameter_t * const parameter, fl_execute_as_t * const as, controller_data_t *data) {

    f_status_t status = F_none;
    int result = 0;

    // @todo check to see if pid file exists.

    // @todo this needs to support/use an option to designate that the process automatically forks in the background.
    //       in which case fll_execute_program() is called.
    //       otherwise this needs to call an asynchronous execute process.
    //       until then, this controller_rule_execute_pid_with() function is not correct and only represents a process that forks to the background.

    if (simulate) {

      if (data->error.verbosity != f_console_verbosity_quiet) {
        fprintf(data->output.stream, "%c", f_string_eol_s[0]);
        fprintf(data->output.stream, "Simulating execution of '");
        fprintf(data->output.stream, "%s%s%s", data->context.title.string, program ? program : arguments.used && arguments.array[0].used ? arguments.array[0].string : f_string_empty_s, data->context.reset.string);
        fprintf(data->output.stream, "' with the arguments: '%s", data->context.title.string);

        for (f_array_length_t i = program ? 0 : 1; i < arguments.used; ++i) {
          fprintf(data->output.stream, "%s%s", (program && i || !program && i > 1) ? f_string_space_s : "", arguments.array[i].string);
        } // for

        fprintf(data->output.stream, "%s'.%c", data->context.reset.string, f_string_eol_s[0]);
      }

      // sleep for less than a second to better show simulation of synchronous vs asynchronous.
      usleep(200000);

      const f_string_static_t simulated_program = f_macro_string_static_t_initialize(f_string_empty_s, 0);
      const f_string_statics_t simulated_arguments = f_string_statics_t_initialize;
      fl_execute_parameter_t simulated_parameter = fl_macro_execute_parameter_t_initialize(parameter->option, parameter->environment, parameter->signals, &simulated_program);

      status = fll_execute_program(controller_default_program_script, simulated_arguments, &simulated_parameter, as, &result);
    }
    else {
      status = fll_execute_program(program, arguments, parameter, as, &result);
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

    if (status == F_child) {
      data->child = result;

      return F_child;
    }

    if (result != 0) {
      status = F_status_set_error(F_failure);
    }

    if (F_status_is_error(status)) {
      status = F_status_set_fine(status);

      if (status == F_control_group || status == F_failure || status == F_limit || status == F_processor || status == F_schedule) {
        controller_rule_error_print_execute(data->error, type == controller_rule_item_type_script, program ? program : arguments.used ? arguments.array[0].string : f_string_empty_s, result, status);
      }
      else if (status == F_file_found_not) {
        controller_rule_error_print_execute_not_found(data->error, F_false, program);
      }
      else {
        fll_error_print(data->error, status, "fll_execute_program", F_true);
      }

      data->child = 0;

      return F_status_set_error(status);
    }

    // @todo wait for pid file or timeout.

    data->child = 0;

    return status;
  }
#endif // _di_controller_rule_execute_pid_with_

#ifndef _di_controller_rule_execute_foreground_
  f_status_t controller_rule_execute_foreground(const uint8_t type, const controller_rule_action_t action, const bool simulate, const f_string_t program, const f_string_dynamics_t arguments, const uint8_t options, fl_execute_parameter_t * const parameter, fl_execute_as_t * const as, controller_data_t *data) {

    f_status_t status = F_none;
    int result = 0;

    if (simulate) {

      if (data->error.verbosity != f_console_verbosity_quiet) {
        fprintf(data->output.stream, "%c", f_string_eol_s[0]);
        fprintf(data->output.stream, "Simulating execution of '");
        fprintf(data->output.stream, "%s%s%s", data->context.title.string, program ? program : arguments.used && arguments.array[0].used ? arguments.array[0].string : f_string_empty_s, data->context.reset.string);
        fprintf(data->output.stream, "' with the arguments: '%s", data->context.title.string);

        for (f_array_length_t i = program ? 0 : 1; i < arguments.used; ++i) {
          fprintf(data->output.stream, "%s%s", (program && i || !program && i > 1) ? f_string_space_s : "", arguments.array[i].string);
        } // for

        fprintf(data->output.stream, "%s'.%c", data->context.reset.string, f_string_eol_s[0]);
      }

      // sleep for less than a second to better show simulation of synchronous vs asynchronous.
      usleep(200000);

      const f_string_static_t simulated_program = f_macro_string_static_t_initialize(f_string_empty_s, 0);
      const f_string_statics_t simulated_arguments = f_string_statics_t_initialize;
      fl_execute_parameter_t simulated_parameter = fl_macro_execute_parameter_t_initialize(parameter->option, parameter->environment, parameter->signals, &simulated_program);

      status = fll_execute_program(controller_default_program_script, simulated_arguments, &simulated_parameter, as, &result);
    }
    else {
      status = fll_execute_program(program, arguments, parameter, as, &result);
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

    if (status == F_child) {
      data->child = result;

      return F_child;
    }

    if (result != 0) {
      status = F_status_set_error(F_failure);
    }

    if (F_status_is_error(status)) {
      status = F_status_set_fine(status);

      if (status == F_control_group || status == F_failure || status == F_limit || status == F_processor || status == F_schedule) {
        controller_rule_error_print_execute(data->error, type == controller_rule_item_type_script, program ? program : arguments.used ? arguments.array[0].string : f_string_empty_s, result, status);
      }
      else if (status == F_file_found_not) {
        controller_rule_error_print_execute_not_found(data->error, F_false, program);
      }
      else {
        fll_error_print(data->error, status, "fll_execute_program", F_true);
      }

      status = F_status_set_error(status);
    }

    data->child = 0;

    return status;
  }
#endif // _di_controller_rule_execute_foreground_

#ifndef _di_controller_rule_find_loaded_
  f_array_length_t controller_rule_find_loaded(const controller_data_t data, const controller_setting_t setting, const f_string_static_t rule_id) {

    f_array_length_t i = 0;

    for (; i < setting.rules.used; ++i) {
      if (fl_string_dynamic_compare(rule_id, setting.rules.array[i].id) == F_equal_to) break;
    } // for

    return i;
  }
#endif // _di_controller_rule_find_loaded_

#ifndef _di_controller_rule_id_construct_
  f_status_t controller_rule_id_construct(const controller_data_t data, const f_string_static_t source, const f_string_range_t directory, const f_string_range_t basename, f_string_dynamic_t *id) {
    f_status_t status = F_none;

    id->used = 0;

    status = f_string_dynamic_partial_append_nulless(source, directory, id);

    if (F_status_is_error(status)) {
      fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true);
      return status;
    }

    status = f_string_append(f_path_separator_s, f_path_separator_length, id);

    if (F_status_is_error(status)) {
      fll_error_print(data.error, F_status_set_fine(status), "f_string_append", F_true);
      return status;
    }

    status = f_string_dynamic_partial_append_nulless(source, basename, id);

    if (F_status_is_error(status)) {
      fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true);
      return status;
    }

    status = f_string_dynamic_terminate_after(id);

    if (F_status_is_error(status)) {
      fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);
    }

    return status;
  }
#endif // _di_controller_rule_id_construct_

#ifndef _di_controller_rule_item_read_
  f_status_t controller_rule_item_read(const controller_data_t data, controller_cache_t *cache, controller_rule_item_t *item) {
    f_status_t status = F_none;

    f_string_range_t range = f_macro_string_range_t_initialize(cache->buffer_item.used);
    f_string_length_t last = 0;

    uint8_t type = 0;
    uint8_t method = 0;
    bool multiple = F_false;

    item->actions.used = 0;

    for (; range.start < cache->buffer_item.used && range.start <= range.stop; last = range.start, cache->delimits.used = 0, cache->comments.used = 0) {

      status = fl_fss_extended_list_object_read(cache->buffer_item, &range, &cache->range_action, &cache->delimits);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "fl_fss_extended_list_object_read", F_true);
        break;
      }

      if (status == FL_fss_found_object) {
        multiple = F_true;
      }
      else {
        range.start = last;
        multiple = F_false;
        cache->delimits.used = 0;

        // The current line is not an Extended List object, so the next possibility is a Basic List (and Extended List, both use the same Object structure).
        status = fl_fss_extended_object_read(cache->buffer_item, &range, &cache->range_action, 0, &cache->delimits);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "fl_fss_extended_object_read", F_true);
          break;
        }

        // Nothing of importance here, so continue onto the next line.
        // @todo present an error if this line is anything but whitespace.
        if (status != FL_fss_found_object) continue;
      }

      status = fl_fss_apply_delimit(cache->delimits, &cache->buffer_item);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "fl_fss_apply_delimit", F_true);
        break;
      }

      status = f_fss_count_lines(cache->buffer_item, cache->range_action.start, &cache->line_action);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "f_fss_count_lines", F_true);
        break;
      }

      cache->line_action += ++item->line;
      cache->name_action.used = 0;

      status = controller_string_dynamic_rip_nulless_terminated(cache->buffer_item, cache->range_action, &cache->name_action);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "controller_string_dynamic_rip_nulless_terminated", F_true);
        break;
      }

      if (fl_string_dynamic_compare_string(controller_string_create_s, cache->name_action, controller_string_create_length) == F_equal_to) {
        type = controller_rule_action_type_create;
      }
      else if (fl_string_dynamic_compare_string(controller_string_group_s, cache->name_action, controller_string_group_length) == F_equal_to) {
        type = controller_rule_action_type_group;
      }
      else if (fl_string_dynamic_compare_string(controller_string_kill_s, cache->name_action, controller_string_kill_length) == F_equal_to) {
        type = controller_rule_action_type_kill;
      }
      else if (fl_string_dynamic_compare_string(controller_string_pause_s, cache->name_action, controller_string_pause_length) == F_equal_to) {
        type = controller_rule_action_type_pause;
      }
      else if (fl_string_dynamic_compare_string(controller_string_restart_s, cache->name_action, controller_string_restart_length) == F_equal_to) {
        type = controller_rule_action_type_restart;
      }
      else if (fl_string_dynamic_compare_string(controller_string_resume_s, cache->name_action, controller_string_resume_length) == F_equal_to) {
        type = controller_rule_action_type_resume;
      }
      else if (fl_string_dynamic_compare_string(controller_string_reload_s, cache->name_action, controller_string_reload_length) == F_equal_to) {
        type = controller_rule_action_type_reload;
      }
      else if (fl_string_dynamic_compare_string(controller_string_start_s, cache->name_action, controller_string_start_length) == F_equal_to) {
        type = controller_rule_action_type_start;
      }
      else if (fl_string_dynamic_compare_string(controller_string_stop_s, cache->name_action, controller_string_stop_length) == F_equal_to) {
        type = controller_rule_action_type_stop;
      }
      else if (fl_string_dynamic_compare_string(controller_string_use_s, cache->name_action, controller_string_use_length) == F_equal_to) {
        type = controller_rule_action_type_use;
      }
      else if (fl_string_dynamic_compare_string(controller_string_user_s, cache->name_action, controller_string_user_length) == F_equal_to) {
        type = controller_rule_action_type_user;
      }
      else {
        if (data.warning.verbosity == f_console_verbosity_debug) {
          fprintf(data.warning.to.stream, "%s%sUnknown rule item action '", data.warning.context.before->string, data.warning.prefix ? data.warning.prefix : f_string_empty_s);
          fprintf(data.warning.to.stream, "%s%s", data.warning.context.after->string, data.warning.notable.before->string);
          f_print_dynamic(data.warning.to.stream, cache->name_action);
          fprintf(data.warning.to.stream, "%s", data.warning.notable.after->string);
          fprintf(data.warning.to.stream, "%s'.%s%c", data.warning.context.before->string, data.warning.context.after->string, f_string_eol_s[0]);

          controller_rule_error_print(data.warning, *cache, F_true);
        }

        continue;
      }

      if (multiple) {
        if (type == controller_rule_action_type_create || type == controller_rule_action_type_group || type == controller_rule_action_type_use || type == controller_rule_action_type_user) {
          if (data.error.verbosity != f_console_verbosity_quiet) {
            fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
            fprintf(data.error.to.stream, "%s%sFSS Extended List is not allowed for the rule item action '", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s);
            fprintf(data.error.to.stream, "%s%s", data.error.context.after->string, data.error.notable.before->string);
            f_print_dynamic(data.error.to.stream, cache->name_action);
            fprintf(data.error.to.stream, "%s", data.error.notable.after->string);
            fprintf(data.error.to.stream, "%s'.%s%c", data.error.context.before->string, data.error.context.after->string, f_string_eol_s[0]);
          }

          status = F_status_set_error(F_supported_not);
          break;
        }

        method = controller_rule_action_method_extended_list;
      }
      else {
        method = controller_rule_action_method_extended;
      }

      status = controller_rule_actions_increase_by(controller_default_allocation_step, &item->actions);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "controller_rule_actions_increase_by", F_true);
        break;
      }

      status = controller_rule_action_read(data, type, method, cache, item, &item->actions, &range);
      if (F_status_is_error(status)) break;
    } // for

    return status;
  }
#endif // _di_controller_rule_item_read_

#ifndef _di_controller_rule_item_type_name_
  f_string_static_t controller_rule_item_type_name(const uint8_t type) {

    f_string_static_t buffer = f_string_static_t_initialize;

    switch (type) {
      case controller_rule_item_type_command:
        buffer.string = controller_string_command_s;
        buffer.used = controller_string_command_length;
        break;

      case controller_rule_item_type_script:
        buffer.string = controller_string_script_s;
        buffer.used = controller_string_script_length;
        break;

      case controller_rule_item_type_service:
        buffer.string = controller_string_service_s;
        buffer.used = controller_string_service_length;
        break;

      case controller_rule_item_type_setting:
        buffer.string = controller_string_setting_s;
        buffer.used = controller_string_setting_length;
        break;
    }

    buffer.size = buffer.used;

    return buffer;
  }
#endif // _di_controller_rule_item_type_name_

#ifndef _di_controller_rule_items_increase_by_
  f_status_t controller_rule_items_increase_by(const f_array_length_t amount, controller_rule_items_t *items) {

    if (items->used + amount > items->size) {
      if (items->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      const f_status_t status = f_memory_resize((void **) & items->array, sizeof(controller_rule_item_t), items->size, items->used + amount);

      if (F_status_is_error_not(status)) {
        items->size = items->used + amount;
      }

      return status;
    }

    return F_none;
  }
#endif // _di_controller_rule_items_increase_by_

#ifndef _di_controller_rule_setting_limit_type_name_
  f_string_static_t controller_rule_setting_limit_type_name(const uint8_t type) {

    f_string_static_t buffer = f_string_static_t_initialize;

    switch (type) {
      case controller_resource_limit_type_as:
        buffer.string = controller_string_as_s;
        buffer.used = controller_string_as_length;
        break;

      case controller_resource_limit_type_core:
        buffer.string = controller_string_core_s;
        buffer.used = controller_string_core_length;
        break;

      case controller_resource_limit_type_cpu:
        buffer.string = controller_string_cpu_s;
        buffer.used = controller_string_cpu_length;
        break;

      case controller_resource_limit_type_data:
        buffer.string = controller_string_data_s;
        buffer.used = controller_string_data_length;
        break;

      case controller_resource_limit_type_fsize:
        buffer.string = controller_string_fsize_s;
        buffer.used = controller_string_fsize_length;
        break;

      case controller_resource_limit_type_locks:
        buffer.string = controller_string_locks_s;
        buffer.used = controller_string_locks_length;
        break;

      case controller_resource_limit_type_memlock:
        buffer.string = controller_string_memlock_s;
        buffer.used = controller_string_memlock_length;
        break;

      case controller_resource_limit_type_msgqueue:
        buffer.string = controller_string_msgqueue_s;
        buffer.used = controller_string_msgqueue_length;
        break;

      case controller_resource_limit_type_nice:
        buffer.string = controller_string_nice_s;
        buffer.used = controller_string_nice_length;
        break;

      case controller_resource_limit_type_nofile:
        buffer.string = controller_string_nofile_s;
        buffer.used = controller_string_nofile_length;
        break;

      case controller_resource_limit_type_nproc:
        buffer.string = controller_string_nproc_s;
        buffer.used = controller_string_nproc_length;
        break;

      case controller_resource_limit_type_rss:
        buffer.string = controller_string_rss_s;
        buffer.used = controller_string_rss_length;
        break;

      case controller_resource_limit_type_rtprio:
        buffer.string = controller_string_rtprio_s;
        buffer.used = controller_string_rtprio_length;
        break;

      case controller_resource_limit_type_rttime:
        buffer.string = controller_string_rttime_s;
        buffer.used = controller_string_rttime_length;
        break;

      case controller_resource_limit_type_sigpending:
        buffer.string = controller_string_sigpending_s;
        buffer.used = controller_string_sigpending_length;
        break;

      case controller_resource_limit_type_stack:
        buffer.string = controller_string_stack_s;
        buffer.used = controller_string_stack_length;
        break;
    }

    buffer.size = buffer.used;

    return buffer;
  }
#endif // _di_controller_rule_setting_limit_type_name_

#ifndef _di_controller_rule_path_
  f_status_t controller_rule_path(const controller_data_t data, const controller_setting_t setting, const f_string_static_t path_directory, const f_string_static_t path_name, f_string_dynamic_t *path) {
    f_status_t status = F_none;

    path->used = 0;

    if (setting.path_setting.used) {
      status = f_string_append(setting.path_setting.string, setting.path_setting.used, path);

      if (F_status_is_error_not(status)) {
        status = f_string_append(f_path_separator_s, f_path_separator_length, path);
      }
    }

    if (F_status_is_error_not(status)) {
      status = f_string_append(controller_string_rules_s, controller_string_rules_length, path);
    }

    if (F_status_is_error_not(status)) {
      status = f_string_append(f_path_separator_s, f_path_separator_length, path);
    }

    if (F_status_is_error_not(status)) {
      status = f_string_append(path_directory.string, path_directory.used, path);
    }

    if (F_status_is_error_not(status)) {
      status = f_string_append(f_path_separator_s, f_path_separator_length, path);
    }

    if (F_status_is_error_not(status)) {
      status = f_string_append(path_name.string, path_name.used, path);
    }

    if (F_status_is_error_not(status)) {
      status = f_string_append(f_path_extension_separator_s, f_path_extension_separator_length, path);
    }

    if (F_status_is_error_not(status)) {
      status = f_string_append(controller_string_rule_s, controller_string_rule_length, path);
    }

    if (F_status_is_error(status)) {
      fll_error_print(data.error, F_status_set_fine(status), "f_string_append", F_true);
      return status;
    }

    status = f_string_dynamic_terminate_after(path);

    if (F_status_is_error(status)) {
      fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);
      return status;
    }

    char path_raw[path->used + 1];

    memcpy(path_raw, path->string, path->used);
    path_raw[path->used] = 0;

    status = fll_path_canonical(path_raw, path);

    if (F_status_is_error(status)) {
      fll_error_print(data.error, F_status_set_fine(status), "fll_path_canonical", F_true);
      return status;
    }

    return F_none;
  }
#endif // _di_controller_rule_path_

#ifndef _di_controller_rule_process_
  f_status_t controller_rule_process(const f_array_length_t index, const uint8_t action, const uint8_t options, controller_data_t *data, controller_setting_t *setting, controller_cache_t *cache) {

    switch (action) {
      case controller_rule_action_type_freeze:
      case controller_rule_action_type_kill:
      case controller_rule_action_type_pause:
      case controller_rule_action_type_reload:
      case controller_rule_action_type_restart:
      case controller_rule_action_type_resume:
      case controller_rule_action_type_start:
      case controller_rule_action_type_stop:
      case controller_rule_action_type_thaw:
        break;

      default:

        if (data->error.verbosity != f_console_verbosity_quiet) {
          fprintf(data->error.to.stream, "%c", f_string_eol_s[0]);
          fprintf(data->error.to.stream, "%s%sUnsupported action type '", data->error.context.before->string, data->error.prefix ? data->error.prefix : f_string_empty_s);
          fprintf(data->error.to.stream, "%s%s%s%s", data->error.context.after->string, data->error.notable.before->string, controller_rule_action_type_name(action), data->error.notable.after->string);
          fprintf(data->error.to.stream, "%s' while attempting to execute rule.%s%c", data->error.context.before->string, data->error.context.after->string, f_string_eol_s[0]);

          controller_rule_error_print(data->error, *cache, F_true);
        }

        return F_status_set_error(F_parameter);
    }

    if (index >= setting->rules.used) {
      fll_error_print(data->error, F_parameter, "controller_rule_process", F_true);
      controller_rule_error_print(data->error, *cache, F_true);

      return F_status_set_error(F_parameter);
    }

    f_status_t status = fl_type_array_lengths_increase_by(controller_default_allocation_step, &cache->stack);

    if (F_status_is_error(status)) {
      fll_error_print(data->error, F_status_set_fine(status), "fl_type_array_lengths_increase_by", F_true);
      controller_rule_error_print(data->error, *cache, F_true);

      return status;
    }

    f_array_length_t i = 0;

    for (; i < cache->stack.used; ++i) {

      if (cache->stack.array[i] == index) {
        if (data->error.verbosity != f_console_verbosity_quiet) {
          fprintf(data->error.to.stream, "%c", f_string_eol_s[0]);
          fprintf(data->error.to.stream, "%s%sThe rule '", data->error.context.before->string, data->error.prefix ? data->error.prefix : f_string_empty_s);
          fprintf(data->error.to.stream, "%s%s%s%s", data->error.context.after->string, data->error.notable.before->string, setting->rules.array[i].name.string, data->error.notable.after->string);
          fprintf(data->error.to.stream, "%s' is already on the execution stack, this recursion is prohibited.%s%c", data->error.context.before->string, data->error.context.after->string, f_string_eol_s[0]);

          controller_rule_error_print(data->error, *cache, F_true);
        }

        // never continue on recursion errors even in simulate mode.
        return F_status_set_error(F_recurse);
      }
    }

    cache->name_action.used = 0;
    cache->name_item.used = 0;
    cache->name_file.used = 0;

    status = f_string_append(controller_string_rules_s, controller_string_rules_length, &cache->name_file);

    if (F_status_is_error_not(status)) {
      status = f_string_append(f_path_separator_s, f_path_separator_length, &cache->name_file);
    }

    if (F_status_is_error(status)) {
      fll_error_print(data->error, F_status_set_fine(status), "f_string_append", F_true);
      controller_rule_error_print(data->error, *cache, F_true);

      return status;
    }

    status = f_string_dynamic_append(setting->rules.array[index].id, &cache->name_file);

    if (F_status_is_error(status)) {
      fll_error_print(data->error, F_status_set_fine(status), "f_string_dynamic_append", F_true);
      controller_rule_error_print(data->error, *cache, F_true);

      return status;
    }

    status = f_string_append(f_path_extension_separator, f_path_extension_separator_length, &cache->name_file);

    if (F_status_is_error_not(status)) {
      status = f_string_append(controller_string_rule_s, controller_string_rule_length, &cache->name_file);
    }

    if (F_status_is_error(status)) {
      fll_error_print(data->error, F_status_set_fine(status), "f_string_append", F_true);
      controller_rule_error_print(data->error, *cache, F_true);

      return status;
    }

    status = f_string_dynamic_terminate_after(&cache->name_file);

    if (F_status_is_error(status)) {
      fll_error_print(data->error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);
      controller_rule_error_print(data->error, *cache, F_true);

      return status;
    }

    cache->stack.array[cache->stack.used++] = index;

    controller_rule_t *rule = &setting->rules.array[index];

    if ((options & controller_rule_option_simulate) && data->parameters[controller_parameter_validate].result == f_console_result_found) {
      controller_rule_simulate(*data, index, controller_rule_action_type_start, options, cache, setting);
    }

    {
      f_array_length_t j = 0;
      f_array_length_t k = 0;
      f_array_length_t at = 0;

      f_string_dynamics_t * const dynamics[] = {
        &rule->need,
        &rule->want,
        &rule->wish,
      };

      const f_string_t strings[] = {
        "needed",
        "wanted",
        "wished for",
      };

      for (i = 0; i < 3; ++i) {

        for (j = 0; j < dynamics[i]->used; ++j) {
          at = controller_rule_find_loaded(*data, *setting, dynamics[i]->array[j]);

          if (at == setting->rules.used) {
            if (i == 0) {
              controller_rule_error_print_need_want_wish(data->error, strings[i], dynamics[i]->array[j].string, "was not found");

              status = F_status_set_error(F_found_not);
              controller_rule_error_print(data->error, *cache, F_true);

              if (!(options & controller_rule_option_simulate)) break;
            }
            else {
              if (data->warning.verbosity == f_console_verbosity_debug) {
                controller_rule_error_print_need_want_wish(data->warning, strings[i], dynamics[i]->array[j].string, "was not found");
                controller_rule_error_print(data->warning, *cache, F_true);
              }
            }
          }

          if (F_status_is_error_not(status) && at < setting->rules.used) {

            // @todo: this will also need to support the asynchronous/wait behavior.
            //if (setting->rules.array[at].status == F_busy) { ... if wait then block ... }

            // when the status is unknown, then the rule has not been executed, so attempt to execute it.
            if (setting->rules.array[at].status == F_known_not) {

              status = fl_type_array_lengths_increase_by(controller_default_allocation_step, &cache->stack);

              if (F_status_is_error(status)) {
                fll_error_print(data->error, F_status_set_fine(status), "fl_type_array_lengths_increase_by", F_true);
                controller_rule_error_print(data->error, *cache, F_true);

                // always exit on memory errors, even in simulate mode.
                break;
              }

              // rule execution will re-use the existing cache, so save the current cache.
              const f_array_length_t cache_line_action = cache->line_action;
              const f_array_length_t cache_line_item = cache->line_item;

              const f_string_length_t cache_name_action_used = cache->name_action.used;
              const f_string_length_t cache_name_item_used = cache->name_item.used;
              const f_string_length_t cache_name_file_used = cache->name_file.used;

              char cache_name_action[cache_name_action_used];
              char cache_name_item[cache_name_item_used];
              char cache_name_file[cache_name_file_used];

              memcpy(cache_name_action, cache->name_action.string, cache->name_action.used);
              memcpy(cache_name_item, cache->name_item.string, cache->name_item.used);
              memcpy(cache_name_file, cache->name_file.string, cache->name_file.used);

              // @todo: this should pass or use the asynchronous state.
              status = controller_rule_process(at, action, options, data, setting, cache);

              if (status == F_child || status == F_signal) break;

              // restore cache.
              memcpy(cache->name_action.string, cache_name_action, cache_name_action_used);
              memcpy(cache->name_item.string, cache_name_item, cache_name_item_used);
              memcpy(cache->name_file.string, cache_name_file, cache_name_file_used);

              cache->name_action.string[cache_name_action_used] = 0;
              cache->name_item.string[cache_name_item_used] = 0;

              cache->name_action.used = cache_name_action_used;
              cache->name_item.used = cache_name_item_used;
              cache->name_file.used = cache_name_file_used;

              cache->line_action = cache_line_action;
              cache->line_item = cache_line_item;

              if (F_status_is_error(status)) {
                if (i == 0 || i == 1 || F_status_set_fine(status) == F_memory_not) {

                  controller_rule_error_print_need_want_wish(data->error, strings[i], dynamics[i]->array[j].string, "failed during execution");
                  controller_rule_error_print(data->error, *cache, F_true);

                  if (!(options & controller_rule_option_simulate) || F_status_set_fine(status) == F_memory_not) {
                    break;
                  }
                }
                else {
                  if (data->warning.verbosity == f_console_verbosity_debug) {
                    controller_rule_error_print_need_want_wish(data->warning, strings[i], dynamics[i]->array[j].string, "failed during execution");
                    controller_rule_error_print(data->warning, *cache, F_true);
                  }
                }
              }
            }
            else if (F_status_is_error(setting->rules.array[at].status)) {

              if (i == 0 || i == 1) {
                controller_rule_error_print_need_want_wish(data->error, strings[i], dynamics[i]->array[j].string, "is in a failed state");

                status = F_status_set_error(F_found_not);
                controller_rule_error_print(data->error, *cache, F_true);

                if (!(options & controller_rule_option_simulate)) break;
              }
              else {
                if (data->warning.verbosity == f_console_verbosity_debug) {
                  controller_rule_error_print_need_want_wish(data->warning, strings[i], dynamics[i]->array[j].string, "is in a failed state");
                  controller_rule_error_print(data->warning, *cache, F_true);
                }
              }
            }
          }
        } // for

        if (status == F_child || status == F_signal) break;

        if (F_status_is_error(status) && !(options & controller_rule_option_simulate)) break;
      } // for
    }

    if (!(options & controller_rule_option_validate) && F_status_is_error_not(status)) {

      // find at least one of the requested action when the rule is required.
      if (options & controller_rule_option_require) {
        bool missing = F_true;

        f_array_length_t j = 0;

        for (i = 0; i < rule->items.used; ++i) {

          for (j = 0; j < rule->items.array[i].actions.used; ++j) {

            if (rule->items.array[i].actions.array[j].type == action) {
              missing = F_false;
              break;
            }
          } // for
        } // for

        if (missing) {

          if (data->error.verbosity != f_console_verbosity_quiet) {
            fprintf(data->error.to.stream, "%c", f_string_eol_s[0]);
            fprintf(data->error.to.stream, "%s%sThe rule '", data->error.context.before->string, data->error.prefix ? data->error.prefix : f_string_empty_s);
            fprintf(data->error.to.stream, "%s%s%s%s", data->error.context.after->string, data->error.notable.before->string, rule->name.used ? rule->name.string : f_string_empty_s, data->error.notable.after->string);
            fprintf(data->error.to.stream, "%s' has no '", data->error.context.before->string);
            fprintf(data->error.to.stream, "%s%s%s%s", data->error.context.after->string, data->error.notable.before->string, controller_rule_action_type_name(action).string, data->error.notable.after->string);
            fprintf(data->error.to.stream, "%s' action to execute.%s%c", data->error.context.before->string, data->error.context.after->string, f_string_eol_s[0]);

            controller_rule_error_print(data->error, *cache, F_true);
          }

          status = F_status_set_error(F_parameter);
        }
      }

      if (F_status_is_error_not(status)) {
        status = controller_rule_execute(*cache, index, action, options & controller_rule_option_simulate, data, setting);

        if (F_status_is_error(status)) {
          controller_rule_error_print(data->error, *cache, F_true);
        }

        if (status == F_child) {
          return F_child;
        }
      }
    }

    // remove this rule off the stack.
    cache->stack.used--;

    if (F_status_is_error(status)) {
      return status;
    }

    return F_none;
  }
#endif // _di_controller_rule_process_

#ifndef _di_controller_rule_read_
  f_status_t controller_rule_read(const controller_data_t data, const controller_setting_t setting, const f_string_static_t rule_id, controller_cache_t *cache, controller_rule_t *rule) {
    f_status_t status = F_none;

    bool for_item = F_true;

    rule->status = F_known_not;
    rule->process = 0;

    // @todo: timeouts may be passed from entry, consider to or not to initialize in a more consistent manner.
    //rule->timeout_kill = 2;
    //rule->timeout_start = 2;
    //rule->timeout_stop = 2;

    rule->has = 0;
    rule->group = 0;
    rule->user = 0;
    rule->nice = 0;

    f_macro_time_spec_t_clear(rule->timestamp);

    rule->id.used = 0;
    rule->name.used = 0;
    rule->path.used = 0;
    rule->script.used = 0;

    rule->define.used = 0;
    rule->parameter.used = 0;

    rule->environment.used = 0;
    rule->need.used = 0;
    rule->want.used = 0;
    rule->wish.used = 0;

    rule->affinity.used = 0;

    if (rule->capability) {
      f_capability_delete(&rule->capability);
      rule->capability = 0;
    }

    for (f_array_length_t i = 0; i < rule->control_group.groups.size; ++i) {
      rule->control_group.groups.array[i].used = 0;
    } // for

    rule->control_group.as_new = F_false;
    rule->control_group.path.used = 0;
    rule->control_group.groups.used = 0;

    f_macro_control_group_t_clear(rule->control_group);

    rule->groups.used = 0;
    rule->limits.used = 0;

    rule->scheduler.policy = 0;
    rule->scheduler.priority = 0;

    rule->items.used = 0;

    cache->line_item = 0;
    cache->line_action = 0;

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

    cache->name_action.used = 0;
    cache->name_file.used = 0;
    cache->name_item.used = 0;

    status = f_string_dynamic_append_nulless(rule_id, &rule->id);

    if (F_status_is_error(status)) {
      fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamic_append_nulless", F_true);
    }
    else {
      status = f_string_dynamic_terminate_after(&rule->id);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);
      }
      else {
        status = controller_file_load(data, setting, controller_string_rules_s, rule->id, controller_string_rule_s, controller_string_rules_length, controller_string_rule_length, cache);
      }
    }

    if (F_status_is_error_not(status)) {
      rule->timestamp = cache->timestamp;

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
    }

    if (F_status_is_error_not(status) && cache->object_items.used) {
      status = controller_rule_items_increase_by(cache->object_items.used, &rule->items);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "controller_rule_items_increase_by", F_true);
      }
      else {
        f_array_length_t i = 0;
        f_array_length_t j = 0;

        for (; i < cache->object_items.used; ++i) {

          cache->line_item = 0;
          cache->line_action = 0;

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

          cache->name_action.used = 0;
          cache->name_item.used = 0;

          for_item = F_true;

          status = f_fss_count_lines(cache->buffer_file, cache->object_items.array[i].start, &cache->line_item);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "f_fss_count_lines", F_true);
            break;
          }

          rule->items.array[rule->items.used].line = ++cache->line_item;

          status = controller_string_dynamic_rip_nulless_terminated(cache->buffer_file, cache->object_items.array[i], &cache->name_item);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "controller_string_dynamic_rip_nulless_terminated", F_true);
            break;
          }

          if (fl_string_dynamic_compare_string(controller_string_setting_s, cache->name_item, controller_string_setting_length) == F_equal_to) {
            rule->items.array[rule->items.used].type = 0;
          }
          else if (fl_string_dynamic_compare_string(controller_string_command_s, cache->name_item, controller_string_command_length) == F_equal_to) {
            rule->items.array[rule->items.used].type = controller_rule_item_type_command;
          }
          else if (fl_string_dynamic_compare_string(controller_string_script_s, cache->name_item, controller_string_script_length) == F_equal_to) {
            rule->items.array[rule->items.used].type = controller_rule_item_type_script;
          }
          else if (fl_string_dynamic_compare_string(controller_string_service_s, cache->name_item, controller_string_service_length) == F_equal_to) {
            rule->items.array[rule->items.used].type = controller_rule_item_type_service;
          }
          else {
            if (data.warning.verbosity == f_console_verbosity_debug) {
              fprintf(data.warning.to.stream, "%s%sUnknown rule item '", data.warning.context.before->string, data.warning.prefix ? data.warning.prefix : f_string_empty_s);
              fprintf(data.warning.to.stream, "%s%s", data.warning.context.after->string, data.warning.notable.before->string);
              f_print_dynamic(data.warning.to.stream, cache->name_item);
              fprintf(data.warning.to.stream, "%s", data.warning.notable.after->string);
              fprintf(data.warning.to.stream, "%s'.%s%c", data.warning.context.before->string, data.warning.context.after->string, f_string_eol_s[0]);

              controller_rule_error_print(data.warning, *cache, F_true);
            }

            continue;
          }

          status = f_string_dynamic_partial_append(cache->buffer_file, cache->content_items.array[i].array[0], &cache->buffer_item);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamic_partial_append", F_true);
            break;
          }

          status = f_string_dynamic_terminate_after(&cache->buffer_item);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);
            break;
          }

          if (rule->items.array[rule->items.used].type) {
            status = controller_rule_item_read(data, cache, &rule->items.array[rule->items.used]);
            if (F_status_is_error(status)) break;

            rule->items.used++;
          }
          else {
            for_item = F_false;

            status = controller_rule_setting_read(data, setting, cache, rule);

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
      controller_rule_error_print(data.error, *cache, for_item);

      rule->status = controller_status_simplify(F_status_set_fine(status));
      return F_false;
    }

    return F_true;
  }
#endif // _di_controller_rule_read_

#ifndef _di_controller_rule_setting_read_
  f_status_t controller_rule_setting_read(const controller_data_t data, const controller_setting_t setting, controller_cache_t *cache, controller_rule_t *rule) {
    f_status_t status = F_none;
    f_status_t status_return = F_none;

    f_string_range_t range = f_macro_string_range_t_initialize(cache->buffer_item.used);
    f_string_range_t range2 = f_string_range_t_initialize;

    status = fll_fss_extended_read(cache->buffer_item, &range, &cache->object_actions, &cache->content_actions, 0, 0, &cache->delimits, 0);

    if (F_status_is_error(status)) {
      fll_error_print(data.error, F_status_set_fine(status), "fll_fss_extended_read", F_true);
      controller_rule_error_print(data.error, *cache, F_false);

      return status;
    }

    f_string_length_t path_original_length = 0;
    f_string_dynamic_t *setting_value = 0;
    f_string_dynamics_t *setting_values = 0;
    f_string_maps_t *setting_maps = 0;

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    uint8_t type = 0;

    // save the current name item and line number to restore on return.
    const f_array_length_t line_item = cache->line_item;
    const f_array_length_t length_name_item = cache->name_item.used;

    char name_item[length_name_item];
    name_item[length_name_item] = 0;

    memcpy(name_item, cache->name_item.string, length_name_item);

    for (; i < cache->content_actions.used; ++i, type = 0) {

      // name_action is used to store all setting values for a single setting.
      cache->name_action.used = 0;

      // name_item is used to store the setting name.
      cache->name_item.used = 0;

      status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->object_actions.array[i], &cache->name_item);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true);
      }
      else {
        status = f_string_dynamic_terminate_after(&cache->name_item);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);
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

        // get the current line number within the settings item.
        cache->line_item = line_item;
        f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

        cache->line_action = ++cache->line_item;

        controller_rule_error_print(data.error, *cache, F_false);
        continue;
      }

      if (fl_string_dynamic_compare_string(controller_string_affinity_s, cache->name_item, controller_string_affinity_length) == F_equal_to) {
        type = controller_rule_setting_type_affinity;
      }
      else if (fl_string_dynamic_compare_string(controller_string_capability_s, cache->name_item, controller_string_capability_length) == F_equal_to) {
        type = controller_rule_setting_type_capability;
      }
      else if (fl_string_dynamic_compare_string(controller_string_control_group_s, cache->name_item, controller_string_control_group_length) == F_equal_to) {
        type = controller_rule_setting_type_control_group;
      }
      else if (fl_string_dynamic_compare_string(controller_string_define_s, cache->name_item, controller_string_define_length) == F_equal_to) {
        type = controller_rule_setting_type_define;
      }
      else if (fl_string_dynamic_compare_string(controller_string_environment_s, cache->name_item, controller_string_environment_length) == F_equal_to) {
        type = controller_rule_setting_type_environment;
      }
      else if (fl_string_dynamic_compare_string(controller_string_group_s, cache->name_item, controller_string_group_length) == F_equal_to) {
        type = controller_rule_setting_type_group;
      }
      else if (fl_string_dynamic_compare_string(controller_string_limit_s, cache->name_item, controller_string_limit_length) == F_equal_to) {
        type = controller_rule_setting_type_limit;
      }
      else if (fl_string_dynamic_compare_string(controller_string_name_s, cache->name_item, controller_string_name_length) == F_equal_to) {
        type = controller_rule_setting_type_name;
      }
      else if (fl_string_dynamic_compare_string(controller_string_need_s, cache->name_item, controller_string_need_length) == F_equal_to) {
        type = controller_rule_setting_type_need;
      }
      else if (fl_string_dynamic_compare_string(controller_string_nice_s, cache->name_item, controller_string_nice_length) == F_equal_to) {
        type = controller_rule_setting_type_nice;
      }
      else if (fl_string_dynamic_compare_string(controller_string_parameter_s, cache->name_item, controller_string_parameter_length) == F_equal_to) {
        type = controller_rule_setting_type_parameter;
      }
      else if (fl_string_dynamic_compare_string(controller_string_path_s, cache->name_item, controller_string_path_length) == F_equal_to) {
        type = controller_rule_setting_type_path;
      }
      else if (fl_string_dynamic_compare_string(controller_string_scheduler_s, cache->name_item, controller_string_scheduler_length) == F_equal_to) {
        type = controller_rule_setting_type_scheduler;
      }
      else if (fl_string_dynamic_compare_string(controller_string_script_s, cache->name_item, controller_string_script_length) == F_equal_to) {
        type = controller_rule_setting_type_script;
      }
      else if (fl_string_dynamic_compare_string(controller_string_user_s, cache->name_item, controller_string_user_length) == F_equal_to) {
        type = controller_rule_setting_type_user;
      }
      else if (fl_string_dynamic_compare_string(controller_string_want_s, cache->name_item, controller_string_want_length) == F_equal_to) {
        type = controller_rule_setting_type_want;
      }
      else if (fl_string_dynamic_compare_string(controller_string_wish_s, cache->name_item, controller_string_wish_length) == F_equal_to) {
        type = controller_rule_setting_type_wish;
      }
      else {
        if (data.warning.verbosity == f_console_verbosity_debug) {
          fprintf(data.warning.to.stream, "%c", f_string_eol_s[0]);
          fprintf(data.warning.to.stream, "%s%sUnknown rule setting '", data.warning.context.before->string, data.warning.prefix ? data.warning.prefix : f_string_empty_s);
          fprintf(data.warning.to.stream, "%s%s", data.warning.context.after->string, data.warning.notable.before->string);
          f_print_dynamic(data.warning.to.stream, cache->name_item);
          fprintf(data.warning.to.stream, "%s", data.warning.notable.after->string);
          fprintf(data.warning.to.stream, "%s'.%s%c", data.warning.context.before->string, data.warning.context.after->string, f_string_eol_s[0]);

          // get the current line number within the settings item.
          cache->line_item = line_item;
          f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

          cache->line_action = ++cache->line_item;

          controller_rule_error_print(data.warning, *cache, F_false);
        }

        continue;
      }

      if (!cache->content_actions.array[i].used) {
        if (data.warning.verbosity == f_console_verbosity_debug) {
          fprintf(data.warning.to.stream, "%c", f_string_eol_s[0]);
          fprintf(data.warning.to.stream, "%s%sEmpty rule setting.%s%c", data.warning.context.before->string, data.warning.prefix ? data.warning.prefix : f_string_empty_s, data.warning.context.after->string, f_string_eol_s[0]);

          // get the current line number within the settings item.
          cache->line_item = line_item;
          f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

          cache->line_action = ++cache->line_item;

          controller_rule_error_print(data.warning, *cache, F_false);
        }

        continue;
      }

      range2.start = cache->content_actions.array[i].array[0].start;
      range2.stop = cache->content_actions.array[i].array[cache->content_actions.array[i].used - 1].stop;

      status = f_string_dynamic_partial_append_nulless(cache->buffer_item, range2, &cache->name_action);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true);
      }
      else {
        status = f_string_dynamic_terminate_after(&cache->name_action);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);
        }
      }

      if (F_status_is_error(status)) {

        // get the current line number within the settings item.
        cache->line_item = line_item;
        f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

        cache->line_action = ++cache->line_item;

        controller_rule_error_print(data.error, *cache, F_false);

        if (F_status_set_fine(status) == F_memory_not) {
          status_return = status;
          break;
        }

        if (F_status_is_error_not(status_return)) {
          status_return = status;
        }

        continue;
      }

      if (type == controller_rule_setting_type_affinity) {
        // @todo use sched_getaffinity() to get the available cpus and do not add an invalid cpu to the affinity array.

        if (!cache->content_actions.array[i].used) {

          if (data.error.verbosity != f_console_verbosity_quiet) {

            // get the current line number within the settings item.
            cache->line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

            cache->line_action = ++cache->line_item;

            fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
            fprintf(data.error.to.stream, "%s%sRule setting requires one or more Content.%s%c", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s, data.error.context.after->string, f_string_eol_s[0]);

            controller_rule_error_print(data.error, *cache, F_false);
          }

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
            f_array_length_t size = rule->affinity.used + f_memory_default_allocation_step;

            if (size > f_array_length_t_size) {
              if (rule->affinity.used + 1 > f_array_length_t_size) {
                status = F_status_set_error(F_array_too_large);
              }
              else {
                size = f_array_length_t_size;
              }
            }

            if (F_status_is_error_not(status)) {
              f_macro_int32s_t_resize(status, rule->affinity, size);
            }
          }

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "f_macro_int32s_t_resize", F_true);
            break;
          }

          status = fl_conversion_string_to_number_signed(cache->buffer_item.string, &number, cache->content_actions.array[i].array[j]);

          if (F_status_is_error(status)) {
            status = F_status_set_fine(status);

            if (status == F_data_not || status == F_number || status == F_number_overflow || status == F_number_underflow) {

              if (data.error.verbosity != f_console_verbosity_quiet) {
                if (status == F_number_overflow || status == F_number_underflow) {
                  fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
                  fprintf(data.error.to.stream, "%s%sRule setting has an unsupported number '", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s);
                  fprintf(data.error.to.stream, "%s%s", data.error.context.after->string, data.error.notable.before->string);
                  f_print_dynamic_partial(data.error.to.stream, cache->buffer_item, cache->content_actions.array[i].array[j]);
                  fprintf(data.error.to.stream, "%s%s', the number is too large for this system.%s%c", data.error.notable.after->string, data.error.context.before->string, data.error.context.after->string, f_string_eol_s[0]);
                }
                else {
                  fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
                  fprintf(data.error.to.stream, "%s%sRule setting has an invalid number '", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s);
                  fprintf(data.error.to.stream, "%s%s", data.error.context.after->string, data.error.notable.before->string);
                  f_print_dynamic_partial(data.error.to.stream, cache->buffer_item, cache->content_actions.array[i].array[j]);
                  fprintf(data.error.to.stream, "%s%s', only whole numbers are allowed for an affinity value.%s%c", data.error.notable.after->string, data.error.context.before->string, data.error.context.after->string, f_string_eol_s[0]);
                }

                // get the current line number within the settings item.
                cache->line_item = line_item;
                f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

                cache->line_action = ++cache->line_item;

                controller_rule_error_print(data.error, *cache, F_false);
              }

              status = F_status_set_error(F_valid_not);

              if (F_status_is_error_not(status_return)) {
                status_return = status;
              }
            }
            else {
              fll_error_print(data.error, status, "fl_conversion_string_to_number_signed", F_true);

              status = F_status_set_error(status);

              if (F_status_is_error_not(status_return)) {
                status_return = status;
              }
            }

            continue;
          }

          rule->affinity.array[rule->affinity.used++] = number;
        } // for

        continue;
      }

      if (type == controller_rule_setting_type_define || type == controller_rule_setting_type_parameter) {

        if (cache->content_actions.array[i].used != 2) {

          if (data.error.verbosity != f_console_verbosity_quiet) {

            // get the current line number within the settings item.
            cache->line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

            cache->line_action = ++cache->line_item;

            fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
            fprintf(data.error.to.stream, "%s%sRule setting requires exactly two Content.%s%c", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s, data.error.context.after->string, f_string_eol_s[0]);

            controller_rule_error_print(data.error, *cache, F_false);
          }

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        if (type == controller_rule_setting_type_define) {
          setting_maps = &rule->define;
        }
        else if (type == controller_rule_setting_type_parameter) {
          setting_maps = &rule->parameter;
        }

        status = f_string_maps_increase(setting_maps);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "f_string_maps_increase", F_true);

          if (F_status_set_fine(status) == F_memory_not) {
            status_return = status;
            break;
          }

          if (F_status_is_error_not(status_return)) {
            status_return = status;
          }

          // get the current line number within the settings item.
          cache->line_item = line_item;
          f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

          cache->line_action = ++cache->line_item;

          controller_rule_error_print(data.error, *cache, F_false);
          continue;
        }

        setting_maps->array[setting_maps->used].name.used = 0;
        setting_maps->array[setting_maps->used].value.used = 0;

        status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[0], &setting_maps->array[setting_maps->used].name);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true);

          if (F_status_set_fine(status) == F_memory_not) {
            status_return = status;
            break;
          }

          if (F_status_is_error_not(status_return)) {
            status_return = status;
          }

          // get the current line number within the settings item.
          cache->line_item = line_item;
          f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

          cache->line_action = ++cache->line_item;

          controller_rule_error_print(data.error, *cache, F_false);
          continue;
        }

        status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[1], &setting_maps->array[setting_maps->used].value);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true);
        }
        else {
          status = f_string_dynamic_terminate_after(&setting_maps->array[setting_maps->used].value);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);
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

          // get the current line number within the settings item.
          cache->line_item = line_item;
          f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

          cache->line_action = ++cache->line_item;

          controller_rule_error_print(data.error, *cache, F_false);
          continue;
        }

        setting_maps->used++;
        continue;
      }

      if (type == controller_rule_setting_type_control_group) {

        if (cache->content_actions.array[i].used < 2 || rule->has & controller_rule_has_control_group) {

          if (data.error.verbosity != f_console_verbosity_quiet) {
            fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
            fprintf(data.error.to.stream, "%s%sRule setting requires two or more Content.%s%c", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s, data.error.context.after->string, f_string_eol_s[0]);

            // get the current line number within the settings item.
            cache->line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

            cache->line_action = ++cache->line_item;

            controller_rule_error_print(data.error, *cache, F_false);
          }

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        if (fl_string_dynamic_partial_compare_string(controller_string_existing_s, cache->buffer_item, controller_string_existing_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          rule->control_group.as_new = F_false;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_string_new_s, cache->buffer_item, controller_string_new_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          rule->control_group.as_new = F_true;
        }
        else {
          if (data.error.verbosity != f_console_verbosity_quiet) {
            fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
            fprintf(data.error.to.stream, "%s%sRule setting has an unknown option '", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s);
            fprintf(data.error.to.stream, "%s%s", data.error.context.after->string, data.error.notable.before->string);
            f_print_dynamic_partial(data.error.to.stream, cache->buffer_item, cache->content_actions.array[i].array[0]);
            fprintf(data.error.to.stream, "%s%s'.%s%c", data.error.notable.after->string, data.error.context.before->string, data.error.context.after->string, f_string_eol_s[0]);

            // get the current line number within the settings item.
            cache->line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

            cache->line_action = ++cache->line_item;

            controller_rule_error_print(data.error, *cache, F_false);
          }

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        rule->control_group.path.used = 0;

        // @todo path prefix needs to be configurable via a parameter.
        status = f_string_append(f_control_group_path_system_prefix, f_control_group_path_system_prefix_length, &rule->control_group.path);

        if (F_status_is_error_not(status)) {
          status = f_string_append(f_control_group_path_system_default, f_control_group_path_system_default_length, &rule->control_group.path);
        }

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "f_string_append", F_true);
        }
        else {
          rule->control_group.groups.used = 0;

          for (j = 1; j < cache->content_actions.array[i].used; ++j) {

            status = f_string_dynamics_increase(&rule->control_group.groups);

            if (F_status_is_error(status)) {
              fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamics_increase", F_true);
              break;
            }

            rule->control_group.groups.array[rule->control_group.groups.used].used = 0;

            status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[j], &rule->control_group.groups.array[rule->control_group.groups.used]);

            if (F_status_is_error(status)) {
              fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true);
              break;
            }

            rule->control_group.groups.used++;
          } // for
        }

        if (F_status_is_error(status)) {
          if (F_status_set_fine(status) == F_memory_not) {
            status_return = status;
            break;
          }

          rule->control_group.path.used = 0;

          if (F_status_is_error_not(status_return)) {
            status_return = status;
          }

          // get the current line number within the settings item.
          cache->line_item = line_item;
          f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

          cache->line_action = ++cache->line_item;

          controller_rule_error_print(data.error, *cache, F_false);
          continue;
        }

        rule->has |= controller_rule_has_control_group;

        continue;
      }

      if (type == controller_rule_setting_type_limit) {

        if (cache->content_actions.array[i].used != 3) {

          if (data.error.verbosity != f_console_verbosity_quiet) {
            fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
            fprintf(data.error.to.stream, "%s%sRule setting requires three Content.%s%c", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s, data.error.context.after->string, f_string_eol_s[0]);

            // get the current line number within the settings item.
            cache->line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

            cache->line_action = ++cache->line_item;

            controller_rule_error_print(data.error, *cache, F_false);
          }

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        if (fl_string_dynamic_partial_compare_string(controller_string_as_s, cache->buffer_item, controller_string_as_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_as;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_string_core_s, cache->buffer_item, controller_string_core_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_core;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_string_cpu_s, cache->buffer_item, controller_string_cpu_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_cpu;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_string_data_s, cache->buffer_item, controller_string_data_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_data;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_string_fsize_s, cache->buffer_item, controller_string_fsize_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_fsize;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_string_locks_s, cache->buffer_item, controller_string_locks_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_locks;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_string_memlock_s, cache->buffer_item, controller_string_memlock_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_memlock;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_string_msgqueue_s, cache->buffer_item, controller_string_msgqueue_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_msgqueue;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_string_nice_s, cache->buffer_item, controller_string_nice_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_nice;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_string_nofile_s, cache->buffer_item, controller_string_nofile_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_nofile;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_string_nproc_s, cache->buffer_item, controller_string_nproc_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_nproc;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_string_rss_s, cache->buffer_item, controller_string_rss_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_rss;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_string_rtprio_s, cache->buffer_item, controller_string_rtprio_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_rtprio;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_string_rttime_s, cache->buffer_item, controller_string_rttime_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_rttime;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_string_sigpending_s, cache->buffer_item, controller_string_sigpending_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_sigpending;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_string_stack_s, cache->buffer_item, controller_string_stack_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          type = controller_resource_limit_type_stack;
        }
        else {
          if (data.error.verbosity == f_console_verbosity_debug) {
            fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
            fprintf(data.error.to.stream, "%s%sUnknown resource limit type '", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s);
            fprintf(data.error.to.stream, "%s%s", data.error.context.after->string, data.error.notable.before->string);
            f_print_dynamic(data.error.to.stream, cache->name_action);
            fprintf(data.error.to.stream, "%s", data.error.notable.after->string);
            fprintf(data.error.to.stream, "%s'.%s%c", data.error.context.before->string, data.error.context.after->string, f_string_eol_s[0]);

            // get the current line number within the settings item.
            cache->line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

            cache->line_action = ++cache->line_item;

            controller_rule_error_print(data.error, *cache, F_true);
          }

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        for (j = 0; j < rule->limits.used; ++j) {

          if (type == rule->limits.array[j].type) {
            if (data.error.verbosity != f_console_verbosity_quiet) {
              fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
              fprintf(data.error.to.stream, "%s%sThe resource limit type is already specified.%s%c", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s, data.error.context.after->string, f_string_eol_s[0]);
              fprintf(data.error.to.stream, "%s%s", data.error.context.after->string, data.error.notable.before->string);

              // get the current line number within the settings item.
              cache->line_item = line_item;
              f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

              cache->line_action = ++cache->line_item;

              controller_rule_error_print(data.error, *cache, F_false);
            }

            status = F_status_set_error(F_valid_not);

            if (F_status_is_error_not(status_return)) {
              status_return = status;
            }
          }
        } // for

        if (F_status_is_error(status)) continue;

        f_macro_limit_sets_t_increase(status, rule->limits);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "f_limit_sets_increase", F_true);

          if (F_status_set_fine(status) == F_memory_not) {
            status_return = status;
            break;
          }

          if (F_status_is_error_not(status_return)) {
            status_return = status;
          }

          // get the current line number within the settings item.
          cache->line_item = line_item;
          f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

          cache->line_action = ++cache->line_item;

          controller_rule_error_print(data.error, *cache, F_false);
          continue;
        }

        f_number_signed_t number = 0;

        for (j = 1; j < 3; ++j, number = 0) {
          status = fl_conversion_string_to_number_signed(cache->buffer_item.string, &number, cache->content_actions.array[i].array[j]);

          if (F_status_is_error(status)) {
            status = F_status_set_fine(status);

            if (status == F_data_not || status == F_number || status == F_number_overflow || status == F_number_underflow) {

              if (data.error.verbosity != f_console_verbosity_quiet) {
                if (status == F_number_overflow || status == F_number_underflow) {
                  fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
                  fprintf(data.error.to.stream, "%s%sRule setting has an unsupported number '", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s);
                  fprintf(data.error.to.stream, "%s%s", data.error.context.after->string, data.error.notable.before->string);
                  f_print_dynamic_partial(data.error.to.stream, cache->buffer_item, cache->content_actions.array[i].array[j]);
                  fprintf(data.error.to.stream, "%s%s', the number is too large for this system.%s%c", data.error.notable.after->string, data.error.context.before->string, data.error.context.after->string, f_string_eol_s[0]);
                }
                else {
                  fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
                  fprintf(data.error.to.stream, "%s%sRule setting has an invalid number '", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s);
                  fprintf(data.error.to.stream, "%s%s", data.error.context.after->string, data.error.notable.before->string);
                  f_print_dynamic_partial(data.error.to.stream, cache->buffer_item, cache->content_actions.array[i].array[j]);
                  fprintf(data.error.to.stream, "%s%s', only whole numbers are allowed for a resource limit value.%s%c", data.error.notable.after->string, data.error.context.before->string, data.error.context.after->string, f_string_eol_s[0]);
                }

                // get the current line number within the settings item.
                cache->line_item = line_item;
                f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

                cache->line_action = ++cache->line_item;

                controller_rule_error_print(data.error, *cache, F_false);
              }

              status = F_status_set_error(F_valid_not);

              if (F_status_is_error_not(status_return)) {
                status_return = status;
              }
            }
            else {
              fll_error_print(data.error, status, "fl_conversion_string_to_number_signed", F_true);

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

        continue;
      }

      if (type == controller_rule_setting_type_name || type == controller_rule_setting_type_path || type == controller_rule_setting_type_script) {
        if (type == controller_rule_setting_type_name) {
          setting_value = &rule->name;
        }
        else if (type == controller_rule_setting_type_path) {
          setting_value = &rule->path;
        }
        else if (type == controller_rule_setting_type_script) {
          setting_value = &rule->script;
        }

        if (setting_value->used || cache->content_actions.array[i].used != 1) {

          if (data.error.verbosity != f_console_verbosity_quiet) {
            fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
            fprintf(data.error.to.stream, "%s%sRule setting requires exactly one Content.%s%c", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s, data.error.context.after->string, f_string_eol_s[0]);

            // get the current line number within the settings item.
            cache->line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

            cache->line_action = ++cache->line_item;

            controller_rule_error_print(data.error, *cache, F_false);
          }

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        if (type == controller_rule_setting_type_name || type == controller_rule_setting_type_script) {

          status = controller_string_dynamic_rip_nulless_terminated(cache->buffer_item, cache->content_actions.array[i].array[0], setting_value);

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
            cache->line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

            cache->line_action = ++cache->line_item;

            controller_rule_error_print(data.error, *cache, F_false);
            continue;
          }

          if (type == controller_rule_setting_type_name || type == controller_rule_setting_type_script) {
            status = controller_validate_has_graph(*setting_value);

            if (status == F_false || F_status_set_fine(status) == F_complete_not_utf) {
              if (status == F_false) {

                if (data.error.verbosity != f_console_verbosity_quiet) {
                  fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
                  fprintf(data.error.to.stream, "%s%sRule setting has an invalid name '", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s);
                  fprintf(data.error.to.stream, "%s%s", data.error.context.after->string, data.error.notable.before->string);
                  f_print_dynamic(data.error.to.stream, *setting_value);
                  fprintf(data.error.to.stream, "%s", data.error.notable.after->string);
                  fprintf(data.error.to.stream, "%s', there must be at least 1 graph character.%s%c", data.error.context.before->string, data.error.context.after->string, f_string_eol_s[0]);

                  // get the current line number within the settings item.
                  cache->line_item = line_item;
                  f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

                  cache->line_action = ++cache->line_item;

                  controller_rule_error_print(data.error, *cache, F_false);
                }

                if (F_status_is_error_not(status_return)) {
                  status_return = F_status_set_error(F_valid_not);
                }
              }
              else {

                // this function should only return F_complete_not_utf on error.
                fll_error_print(data.error, F_complete_not_utf, "controller_validate_has_graph", F_true);

                if (F_status_is_error_not(status_return)) {
                  status_return = status;
                }
              }

              setting_value->used = 0;

              // get the current line number within the settings item.
              cache->line_item = line_item;
              f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

              cache->line_action = ++cache->line_item;

              controller_rule_error_print(data.error, *cache, F_false);
              continue;
            }
          }
        }
        else if (type == controller_rule_setting_type_path) {
          status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[0], setting_value);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true);
          }
          else {
            status = f_string_dynamic_terminate_after(setting_value);

            if (F_status_is_error(status)) {
              fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);
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
            cache->line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

            cache->line_action = ++cache->line_item;

            controller_rule_error_print(data.error, *cache, F_false);
            continue;
          }
        }

        continue;
      }

      if (type == controller_rule_setting_type_scheduler) {

        if (cache->content_actions.array[i].used < 1 || cache->content_actions.array[i].used > 2 || rule->has & controller_rule_has_scheduler) {

          if (data.error.verbosity != f_console_verbosity_quiet) {
            fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
            fprintf(data.error.to.stream, "%s%sRule setting requires either one or two Content.%s%c", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s, data.error.context.after->string, f_string_eol_s[0]);

            // get the current line number within the settings item.
            cache->line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

            cache->line_action = ++cache->line_item;

            controller_rule_error_print(data.error, *cache, F_false);
          }

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        if (fl_string_dynamic_partial_compare_string(controller_string_batch_s, cache->buffer_item, controller_string_batch_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          rule->scheduler.policy = SCHED_BATCH;
          rule->scheduler.priority = 0;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_string_deadline_s, cache->buffer_item, controller_string_deadline_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          rule->scheduler.policy = SCHED_DEADLINE;
          rule->scheduler.priority = 49;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_string_fifo_s, cache->buffer_item, controller_string_fifo_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          rule->scheduler.policy = SCHED_FIFO;
          rule->scheduler.priority = 49;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_string_idle_s, cache->buffer_item, controller_string_idle_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          rule->scheduler.policy = SCHED_IDLE;
          rule->scheduler.priority = 0;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_string_other_s, cache->buffer_item, controller_string_other_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          rule->scheduler.policy = SCHED_OTHER;
          rule->scheduler.priority = 0;
        }
        else if (fl_string_dynamic_partial_compare_string(controller_string_round_robin_s, cache->buffer_item, controller_string_round_robin_length, cache->content_actions.array[i].array[0]) == F_equal_to) {
          rule->scheduler.policy = SCHED_RR;
          rule->scheduler.priority = 49;
        }
        else {
          if (data.error.verbosity != f_console_verbosity_quiet) {
            fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
            fprintf(data.error.to.stream, "%s%sRule setting has an unknown scheduler '", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s);
            fprintf(data.error.to.stream, "%s%s", data.error.context.after->string, data.error.notable.before->string);
            f_print_dynamic_partial(data.error.to.stream, cache->buffer_item, cache->content_actions.array[i].array[0]);
            fprintf(data.error.to.stream, "%s%s'.%s%c", data.error.notable.after->string, data.error.context.before->string, data.error.context.after->string, f_string_eol_s[0]);

            // get the current line number within the settings item.
            cache->line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

            cache->line_action = ++cache->line_item;

            controller_rule_error_print(data.error, *cache, F_false);
          }

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        if (cache->content_actions.array[i].used > 1) {
          const bool zero_only = rule->scheduler.policy == SCHED_BATCH || rule->scheduler.policy == SCHED_IDLE || rule->scheduler.policy == SCHED_OTHER;

          f_number_signed_t number = 0;

          status = fl_conversion_string_to_number_signed(cache->buffer_item.string, &number, cache->content_actions.array[i].array[1]);

          if (F_status_is_error(status) || (zero_only && number) || (!zero_only && (number < 1 || number > 99))) {
            status = F_status_set_fine(status);

            if ((zero_only && number) || (!zero_only && (number < 1 || number > 99)) || status == F_data_not || status == F_number || status == F_number_overflow) {

              if (data.error.verbosity != f_console_verbosity_quiet) {
                fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
                fprintf(data.error.to.stream, "%s%sRule setting has an invalid number '", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s);
                fprintf(data.error.to.stream, "%s%s", data.error.context.after->string, data.error.notable.before->string);
                f_print_dynamic_partial(data.error.to.stream, cache->buffer_item, cache->content_actions.array[i].array[1]);

                if (zero_only) {
                  fprintf(data.error.to.stream, "%s%s', only ", data.error.notable.after->string, data.error.context.before->string);
                  fprintf(data.error.to.stream, "%s%s0%s", data.error.context.after->string, data.error.notable.before->string, data.error.notable.after->string);
                  fprintf(data.error.to.stream, "%s is", data.error.context.before->string);
                }
                else {
                  fprintf(data.error.to.stream, "%s%s', only the whole numbers inclusively between ", data.error.notable.after->string, data.error.context.before->string);
                  fprintf(data.error.to.stream, "%s%s1%s", data.error.context.after->string, data.error.notable.before->string, data.error.notable.after->string);
                  fprintf(data.error.to.stream, "%s and ", data.error.context.before->string);
                  fprintf(data.error.to.stream, "%s%s99%s", data.error.context.after->string, data.error.notable.before->string, data.error.notable.after->string);
                  fprintf(data.error.to.stream, "%s are", data.error.context.before->string);
                }

                fprintf(data.error.to.stream, " allowed for the designated scheduler.%s%c", data.error.context.after->string, f_string_eol_s[0]);

                // get the current line number within the settings item.
                cache->line_item = line_item;
                f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

                cache->line_action = ++cache->line_item;

                controller_rule_error_print(data.error, *cache, F_false);
              }

              if (F_status_is_error_not(status_return)) {
                status_return = F_status_set_error(F_valid_not);
              }
            }
            else {
              fll_error_print(data.error, status, "fl_conversion_string_to_number_signed", F_true);
              status = F_status_set_error(status);

              if (F_status_is_error_not(status_return)) {
                status_return = status;
              }
            }

            continue;
          }

          rule->scheduler.priority = number;
        }

        rule->has |= controller_rule_has_scheduler;

        continue;
      }

      if (type == controller_rule_setting_type_capability || type == controller_rule_setting_type_nice || type == controller_rule_setting_type_user) {

        if (cache->content_actions.array[i].used != 1 || type == controller_rule_setting_type_capability && rule->capability || type == controller_rule_setting_type_group && (rule->has & controller_rule_has_group) || type == controller_rule_setting_type_nice && (rule->has & controller_rule_has_nice) || type == controller_rule_setting_type_user && (rule->has & controller_rule_has_user)) {

          if (data.error.verbosity != f_console_verbosity_quiet) {
            fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
            fprintf(data.error.to.stream, "%s%sRule setting requires exactly one Content.%s%c", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s, data.error.context.after->string, f_string_eol_s[0]);

            // get the current line number within the settings item.
            cache->line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

            cache->line_action = ++cache->line_item;

            controller_rule_error_print(data.error, *cache, F_false);
          }

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        if (type == controller_rule_setting_type_capability) {
          cache->buffer_other.used = 0;

          status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[0], &cache->buffer_other);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true);

            // get the current line number within the settings item.
            cache->line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

            cache->line_action = ++cache->line_item;

            controller_rule_error_print(data.error, *cache, F_false);

            if (F_status_set_fine(status) == F_memory_not) {
              status_return = status;
              break;
            }

            if (F_status_is_error_not(status_return)) {
              status_return = F_status_set_error(F_valid_not);
            }
          }

          status = f_string_dynamic_terminate_after(&cache->buffer_other);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);

            // get the current line number within the settings item.
            cache->line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

            cache->line_action = ++cache->line_item;

            controller_rule_error_print(data.error, *cache, F_false);

            if (F_status_set_fine(status) == F_memory_not) {
              status_return = status;
              break;
            }

            if (F_status_is_error_not(status_return)) {
              status_return = F_status_set_error(F_valid_not);
            }
          }

          status = f_capability_from_text(cache->buffer_other.string, &rule->capability);

          if (F_status_is_error(status) && F_status_set_fine(status) != F_supported_not) {

            if (F_status_set_fine(status) == F_memory_not) {
              fll_error_print(data.error, F_status_set_fine(status), "f_capability_from_text", F_true);

              // get the current line number within the settings item.
              cache->line_item = line_item;
              f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

              cache->line_action = ++cache->line_item;

              controller_rule_error_print(data.error, *cache, F_false);

              status_return = status;
              break;
            }

            if (data.error.verbosity != f_console_verbosity_quiet) {
              fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
              fprintf(data.error.to.stream, "%s%sRule setting failed to process the capabilities.%s%c", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s, data.error.context.after->string, f_string_eol_s[0]);

              // get the current line number within the settings item.
              cache->line_item = line_item;
              f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

              cache->line_action = ++cache->line_item;

              controller_rule_error_print(data.error, *cache, F_false);
            }

            if (F_status_is_error_not(status_return)) {
              status_return = F_status_set_error(F_valid_not);
            }

            continue;
          }
        }
        else if (type == controller_rule_setting_type_nice) {
          f_number_signed_t number = 0;

          status = fl_conversion_string_to_number_signed(cache->buffer_item.string, &number, cache->content_actions.array[i].array[0]);

          if (F_status_is_error(status) || number < -20 || number > 19) {
            status = F_status_set_fine(status);

            if (number < -20 || number > 19 || status == F_data_not || status == F_number || status == F_number_overflow || status == F_number_underflow) {

              if (data.error.verbosity != f_console_verbosity_quiet) {
                fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
                fprintf(data.error.to.stream, "%s%sRule setting has an invalid number '", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s);
                fprintf(data.error.to.stream, "%s%s", data.error.context.after->string, data.error.notable.before->string);
                f_print_dynamic_partial(data.error.to.stream, cache->buffer_item, cache->content_actions.array[i].array[0]);
                fprintf(data.error.to.stream, "%s%s', only the whole numbers inclusively between ", data.error.notable.after->string, data.error.context.before->string);
                fprintf(data.error.to.stream, "%s%s-20%s", data.error.context.after->string, data.error.notable.before->string, data.error.notable.after->string);
                fprintf(data.error.to.stream, "%s and ", data.error.context.before->string);
                fprintf(data.error.to.stream, "%s%s19%s", data.error.context.after->string, data.error.notable.before->string, data.error.notable.after->string);
                fprintf(data.error.to.stream, "%s are allowed.%s%c", data.error.context.before->string, data.error.context.after->string, f_string_eol_s[0]);

                // get the current line number within the settings item.
                cache->line_item = line_item;
                f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

                cache->line_action = ++cache->line_item;

                controller_rule_error_print(data.error, *cache, F_false);
              }

              if (F_status_is_error_not(status_return)) {
                status_return = F_status_set_error(F_valid_not);
              }
            }
            else {
              fll_error_print(data.error, status, "fl_conversion_string_to_number_signed", F_true);
              status = F_status_set_error(status);

              if (F_status_is_error_not(status_return)) {
                status_return = status;
              }
            }
          }
          else {
            rule->nice = number;
            rule->has |= controller_rule_has_nice;
          }
        }
        else if (type == controller_rule_setting_type_user) {
          uid_t number = 0;

          status = controller_get_id_user(cache->buffer_item, cache->content_actions.array[i].array[0], cache, &number);

          if (F_status_is_error(status)) {
            status = F_status_set_fine(status);

            if (status == F_exist_not) {
              if (data.error.verbosity != f_console_verbosity_quiet) {
                fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
                fprintf(data.error.to.stream, "%s%sRule setting has an invalid user '", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s);
                fprintf(data.error.to.stream, "%s%s", data.error.context.after->string, data.error.notable.before->string);
                f_print_dynamic_partial(data.error.to.stream, cache->buffer_item, cache->content_actions.array[i].array[0]);
                fprintf(data.error.to.stream, "%s", data.error.notable.after->string);
                fprintf(data.error.to.stream, "%s' because no user was found by that name.%s%c", data.error.context.before->string, data.error.context.after->string, f_string_eol_s[0]);
              }
            }
            else if (status == F_number_too_large) {
              if (data.error.verbosity != f_console_verbosity_quiet) {
                fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
                fprintf(data.error.to.stream, "%s%sRule setting has an invalid user '", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s);
                fprintf(data.error.to.stream, "%s%s", data.error.context.after->string, data.error.notable.before->string);
                f_print_dynamic_partial(data.error.to.stream, cache->buffer_item, cache->content_actions.array[i].array[0]);
                fprintf(data.error.to.stream, "%s", data.error.notable.after->string);
                fprintf(data.error.to.stream, "%s' because the given ID is too large.%s%c", data.error.context.before->string, data.error.context.after->string, f_string_eol_s[0]);
              }
            }
            else if (status == F_number) {
              if (data.error.verbosity != f_console_verbosity_quiet) {
                fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
                fprintf(data.error.to.stream, "%s%sRule setting has an invalid user '", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s);
                fprintf(data.error.to.stream, "%s%s", data.error.context.after->string, data.error.notable.before->string);
                f_print_dynamic_partial(data.error.to.stream, cache->buffer_item, cache->content_actions.array[i].array[0]);
                fprintf(data.error.to.stream, "%s", data.error.notable.after->string);
                fprintf(data.error.to.stream, "%s' because the given ID is not a valid supported number.%s%c", data.error.context.before->string, data.error.context.after->string, f_string_eol_s[0]);
              }
            }
            else {
              fll_error_print(data.error, status, "f_account_id_user_by_name", F_true);
            }

            // get the current line number within the settings item.
            cache->line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

            cache->line_action = ++cache->line_item;

            controller_rule_error_print(data.error, *cache, F_false);

            if (F_status_is_error_not(status_return)) {
              status_return = F_status_set_error(status);
            }
          }
          else {
            rule->user = number;
            rule->has |= controller_rule_has_user;
          }
        }

        continue;
      }

      if (type == controller_rule_setting_type_group) {
        if (!cache->content_actions.array[i].used) {
          if (data.error.verbosity != f_console_verbosity_quiet) {
            fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
            fprintf(data.error.to.stream, "%s%sRule setting requires one or more Content.%s%c", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s, data.error.context.after->string, f_string_eol_s[0]);

            // get the current line number within the settings item.
            cache->line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

            cache->line_action = ++cache->line_item;

            controller_rule_error_print(data.error, *cache, F_false);
          }

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        gid_t number = 0;

        rule->groups.used = 0;

        for (j = 0; j < cache->content_actions.array[i].used; ++j) {

          status = fl_type_int32s_increase(&rule->groups);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "fl_type_int32s_increase", F_true);

            if (F_status_set_fine(status) == F_memory_not) {
              status_return = status;
              break;
            }

            if (F_status_is_error_not(status_return)) {
              status_return = status;
            }

            // get the current line number within the settings item.
            cache->line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

            cache->line_action = ++cache->line_item;

            controller_rule_error_print(data.error, *cache, F_false);
            continue;
          }

          status = controller_get_id_group(cache->buffer_item, cache->content_actions.array[i].array[j], cache, &number);

          if (F_status_is_error(status)) {
            status = F_status_set_fine(status);

            if (status == F_exist_not) {
              if (data.error.verbosity != f_console_verbosity_quiet) {
                fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
                fprintf(data.error.to.stream, "%s%sRule setting has an invalid group '", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s);
                fprintf(data.error.to.stream, "%s%s", data.error.context.after->string, data.error.notable.before->string);
                f_print_dynamic_partial(data.error.to.stream, cache->buffer_item, cache->content_actions.array[i].array[j]);
                fprintf(data.error.to.stream, "%s", data.error.notable.after->string);
                fprintf(data.error.to.stream, "%s' because no group was found by that name.%s%c", data.error.context.before->string, data.error.context.after->string, f_string_eol_s[0]);
              }
            }
            else if (status == F_number_too_large) {
              if (data.error.verbosity != f_console_verbosity_quiet) {
                fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
                fprintf(data.error.to.stream, "%s%sRule setting has an invalid group '", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s);
                fprintf(data.error.to.stream, "%s%s", data.error.context.after->string, data.error.notable.before->string);
                f_print_dynamic_partial(data.error.to.stream, cache->buffer_item, cache->content_actions.array[i].array[j]);
                fprintf(data.error.to.stream, "%s", data.error.notable.after->string);
                fprintf(data.error.to.stream, "%s' because the given ID is too large.%s%c", data.error.context.before->string, data.error.context.after->string, f_string_eol_s[0]);
              }
            }
            else if (status == F_number) {
              if (data.error.verbosity != f_console_verbosity_quiet) {
                fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
                fprintf(data.error.to.stream, "%s%sRule setting has an invalid group '", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s);
                fprintf(data.error.to.stream, "%s%s", data.error.context.after->string, data.error.notable.before->string);
                f_print_dynamic_partial(data.error.to.stream, cache->buffer_item, cache->content_actions.array[i].array[j]);
                fprintf(data.error.to.stream, "%s", data.error.notable.after->string);
                fprintf(data.error.to.stream, "%s' because the given ID is not a valid supported number.%s%c", data.error.context.before->string, data.error.context.after->string, f_string_eol_s[0]);
              }
            }
            else {
              fll_error_print(data.error, status, "f_account_id_group_by_name", F_true);
            }

            // get the current line number within the settings item.
            cache->line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

            cache->line_action = ++cache->line_item;

            controller_rule_error_print(data.error, *cache, F_false);

            if (F_status_is_error_not(status_return)) {
              status_return = F_status_set_error(status);
            }
          }
          else {
            if (rule->has & controller_rule_has_group) {
              rule->groups.array[rule->groups.used++] = number;
            }
            else {
              rule->group = number;
              rule->has |= controller_rule_has_group;
            }
          }
        } // for

        continue;
      }

      if (type == controller_rule_setting_type_environment) {
        setting_values = &rule->environment;

        for (j = 0; j < cache->content_actions.array[i].used; ++j) {

          status = f_string_dynamics_increase(setting_values);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamics_increase", F_true);

            if (F_status_set_fine(status) == F_memory_not) {
              status_return = status;
              break;
            }

            if (F_status_is_error_not(status_return)) {
              status_return = status;
            }

            // get the current line number within the settings item.
            cache->line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

            cache->line_action = ++cache->line_item;

            controller_rule_error_print(data.error, *cache, F_false);
            continue;
          }

          setting_values->array[setting_values->used].used = 0;

          status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[j], &setting_values->array[setting_values->used]);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true);
          }
          else {
            status = f_string_dynamic_terminate_after(&setting_values->array[setting_values->used]);

            if (F_status_is_error(status)) {
              fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);
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

            // get the current line number within the settings item.
            cache->line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

            cache->line_action = ++cache->line_item;

            controller_rule_error_print(data.error, *cache, F_false);
            continue;
          }

          status = controller_validate_environment_name(setting_values->array[setting_values->used]);

          if (status == F_false || F_status_set_fine(status) == F_complete_not_utf) {
            if (status == F_false) {

              if (data.error.verbosity != f_console_verbosity_quiet) {
                fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
                fprintf(data.error.to.stream, "%s%sRule setting has an invalid environment variable name '", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s);
                fprintf(data.error.to.stream, "%s%s%s%s", data.error.context.after->string, data.error.notable.before->string, setting_values->array[setting_values->used].string, data.error.notable.after->string);
                fprintf(data.error.to.stream, "%s'.%s%c", data.error.context.before->string, data.error.context.after->string, f_string_eol_s[0]);

                // get the current line number within the settings item.
                cache->line_item = line_item;
                f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

                cache->line_action = ++cache->line_item;

                controller_rule_error_print(data.error, *cache, F_false);
              }

              if (F_status_is_error_not(status_return)) {
                status_return = F_status_set_error(F_valid_not);
              }
            }
            else {

              // this function should only return F_complete_not_utf on error.
              fll_error_print(data.error, F_complete_not_utf, "controller_validate_environment_name", F_true);

              if (F_status_is_error_not(status_return)) {
                status_return = status;
              }
            }

            setting_values->array[setting_values->used].used = 0;

            // get the current line number within the settings item.
            cache->line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

            cache->line_action = ++cache->line_item;

            controller_rule_error_print(data.error, *cache, F_false);
            continue;
          }

          setting_values->used++;
        } // for

        continue;
      }

      if (cache->content_actions.array[i].used != 2) {

        if (data.error.verbosity != f_console_verbosity_quiet) {
          fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
          fprintf(data.error.to.stream, "%s%sRule setting requires exactly two Content.%s%c", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s, data.error.context.after->string, f_string_eol_s[0]);

          // get the current line number within the settings item.
          cache->line_item = line_item;
          f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

          cache->line_action = ++cache->line_item;

          controller_rule_error_print(data.error, *cache, F_false);
        }

        if (F_status_is_error_not(status_return)) {
          status_return = F_status_set_error(F_valid_not);
        }

        continue;
      }

      if (type == controller_rule_setting_type_need) {
        setting_values = &rule->need;
      }
      else if (type == controller_rule_setting_type_want) {
        setting_values = &rule->want;
      }
      else if (type == controller_rule_setting_type_wish) {
        setting_values = &rule->wish;
      }

      status = f_string_dynamics_increase_by(controller_default_allocation_step, setting_values);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamics_increase_by", F_true);

        if (F_status_set_fine(status) == F_memory_not) {
          status_return = status;
          break;
        }

        if (F_status_is_error_not(status_return)) {
          status_return = status;
        }

        // get the current line number within the settings item.
        cache->line_item = line_item;
        f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

        cache->line_action = ++cache->line_item;

        controller_rule_error_print(data.error, *cache, F_false);
        continue;
      }

      status = controller_rule_id_construct(data, cache->buffer_item, cache->content_actions.array[i].array[0], cache->content_actions.array[i].array[1], &setting_values->array[setting_values->used]);

      if (F_status_is_error(status)) {
        setting_values->array[setting_values->used].used = 0;

        if (F_status_set_fine(status) == F_memory_not) {
          status_return = status;
          break;
        }

        if (F_status_is_error_not(status_return)) {
          status_return = status;
        }

        // get the current line number within the settings item.
        cache->line_item = line_item;
        f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->line_item);

        cache->line_action = ++cache->line_item;

        controller_rule_error_print(data.error, *cache, F_false);
        continue;
      }

      cache->buffer_path.used = 0;

      status = f_file_name_base(setting_values->array[setting_values->used].string, setting_values->array[setting_values->used + 1].used, &cache->buffer_path);

      if (F_status_is_error(status)) {
        setting_values->array[setting_values->used].used = 0;

        fll_error_print(data.error, F_status_set_fine(status), "f_file_name_base", F_true);

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

        if (data.error.verbosity != f_console_verbosity_quiet) {
          fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
          fprintf(data.error.to.stream, "%s%sThe rule item action second parameter '", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s);
          fprintf(data.error.to.stream, "%s%s", data.error.context.after->string, data.error.notable.before->string);
          f_print_dynamic_partial(data.error.to.stream, cache->buffer_item, cache->content_actions.array[i].array[1]);
          fprintf(data.error.to.stream, "%s", data.error.notable.after->string);
          fprintf(data.error.to.stream, "%s' must be a base path name, such as %llu '", data.error.context.before->string, cache->buffer_path.used);
          fprintf(data.error.to.stream, "%s%s", data.error.context.after->string, data.error.notable.before->string);
          f_print_dynamic(data.error.to.stream, cache->buffer_path);
          fprintf(data.error.to.stream, "%s", data.error.notable.after->string);
          fprintf(data.error.to.stream, "%s'.%s%c", data.error.context.before->string, data.error.context.after->string, f_string_eol_s[0]);
        }

        setting_values->array[setting_values->used].used = 0;

        continue;
      }

      setting_values->used++;
    } // for

    // resore the current name item and line number, which there should already be enough allocated space for.
    memcpy(cache->name_item.string, name_item, length_name_item);

    cache->name_item.string[length_name_item] = 0;
    cache->name_item.used = length_name_item;

    cache->line_item = line_item;

    return status_return;
  }
#endif // _di_controller_rule_setting_read_

#ifndef _di_controller_rule_simulate_
  void controller_rule_simulate(const controller_data_t data, const f_array_length_t index, const uint8_t action, const uint8_t options, controller_cache_t *cache, controller_setting_t *setting) {

    switch (action) {
      case controller_rule_action_type_kill:
      case controller_rule_action_type_reload:
      case controller_rule_action_type_restart:
      case controller_rule_action_type_start:
      case controller_rule_action_type_stop:
        break;

      default:

        if (data.error.verbosity != f_console_verbosity_quiet) {
          fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
          fprintf(data.error.to.stream, "%s%sUnsupported action type '", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s);
          fprintf(data.error.to.stream, "%s%s%s%s", data.error.context.after->string, data.error.notable.before->string, controller_rule_action_type_name(action).string, data.error.notable.after->string);
          fprintf(data.error.to.stream, "%s' while attempting to simulate rule execution.%s%c", data.error.context.before->string, data.error.context.after->string, f_string_eol_s[0]);

          controller_rule_error_print(data.error, *cache, F_true);
        }

        return;
    }

    controller_rule_t * const rule = &setting->rules.array[index];

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    // find at least one of the requested action.
    {
      bool missing = F_true;

      for (; i < rule->items.used; ++i) {

        for (j = 0; j < rule->items.array[i].actions.used; ++j) {

          if (rule->items.array[i].actions.array[j].type == action) {
            missing = F_false;
            break;
          }
        } // for
      } // for

      if (missing) {
        fprintf(data.output.stream, "%c", f_string_eol_s[0]);
        fprintf(data.output.stream, "Rule '");
        fprintf(data.output.stream, "%s%s%s", data.context.set.title.before->string, rule->name.used ? rule->name.string : f_string_empty_s, data.context.set.title.after->string);
        fprintf(data.output.stream, "' has no '");
        fprintf(data.output.stream, "%s%s%s", data.context.set.important.before->string, controller_rule_action_type_name(action).string, data.context.set.important.after->string);
        fprintf(data.output.stream, "' action to execute and would '");
        fprintf(data.output.stream, "%s%s%s", data.context.set.important.before->string, options & controller_rule_option_require ? controller_string_fail_s : controller_string_succeed_s, data.context.set.important.after->string);
        fprintf(data.output.stream, "' because it is '");
        fprintf(data.output.stream, "%s%s%s", data.context.set.important.before->string, options & controller_rule_option_require ? controller_string_required_s : controller_string_optional_s, data.context.set.important.after->string);
        fprintf(data.output.stream, "'.%c", f_string_eol_s[0]);
      }
    }

    fprintf(data.output.stream, "%c", f_string_eol_s[0]);
    fprintf(data.output.stream, "Rule %s%s%s {%c", data.context.set.title.before->string, rule->id.used ? rule->id.string : f_string_empty_s, data.context.set.title.after->string, f_string_eol_s[0]);
    fprintf(data.output.stream, "  %s%s%s %s%c", data.context.set.important.before->string, controller_string_name_s, data.context.set.important.after->string, rule->name.used ? rule->name.string : f_string_empty_s, f_string_eol_s[0]);
    fprintf(data.output.stream, "  %s%s%s %s%c", data.context.set.important.before->string, controller_string_how_s, data.context.set.important.after->string, options & controller_rule_option_asynchronous ? controller_string_asynchronous : controller_string_synchronous_s, f_string_eol_s[0]);
    fprintf(data.output.stream, "  %s%s%s %s%c", data.context.set.important.before->string, controller_string_wait_s, data.context.set.important.after->string, options & controller_rule_option_wait ? controller_string_yes : controller_string_no_s, f_string_eol_s[0]);

    if (f_capability_supported()) {
      fprintf(data.output.stream, "  %s%s%s ", data.context.set.important.before->string, controller_string_capability_s, data.context.set.important.after->string);

      if (rule->capability) {
        cache->buffer_other.used = 0;

        if (F_status_is_error_not(f_capability_to_text(rule->capability, &cache->buffer_other))) {
          fprintf(data.output.stream, "%s", cache->buffer_other.string);
        }
      }

      fprintf(data.output.stream, "%c", f_string_eol_s[0]);
    }
    else {
      fprintf(data.output.stream, "  %s%s%s ", data.context.set.important.before->string, controller_string_capability_s, data.context.set.important.after->string, f_string_eol_s[0]);
      fprintf(data.output.stream, "%s(unsupported)%s%c", data.context.set.warning.before->string, data.context.set.warning.after->string, f_string_eol_s[0]);
    }

    fprintf(data.output.stream, "  %s%s%s", data.context.set.important.before->string, controller_string_control_group_s, data.context.set.important.after->string);
    if (rule->has & controller_rule_has_control_group) {
      fprintf(data.output.stream, " %s", rule->control_group.as_new ? controller_string_new_s : controller_string_existing_s);

      for (i = 0; i < rule->control_group.groups.used; ++i) {

        if (rule->control_group.groups.array[i].used) {
          fprintf(data.output.stream, f_string_space_s);
          f_print_dynamic(data.output.stream, rule->control_group.groups.array[i]);
        }
      } // for
    }
    fprintf(data.output.stream, "%c", f_string_eol_s[0]);

    fprintf(data.output.stream, "  %s%s%s", data.context.set.important.before->string, controller_string_nice_s, data.context.set.important.after->string);
    if (rule->has & controller_rule_has_nice) {
      fprintf(data.output.stream, " %i", rule->nice);
    }
    fprintf(data.output.stream, "%c", f_string_eol_s[0]);

    fprintf(data.output.stream, "  %s%s%s", data.context.set.important.before->string, controller_string_scheduler_s, data.context.set.important.after->string);
    if (rule->has & controller_rule_has_scheduler) {
      f_string_t policy = "";

      if (rule->scheduler.policy == SCHED_BATCH) {
        policy = controller_string_batch_s;
      }
      else if (rule->scheduler.policy == SCHED_DEADLINE) {
        policy = controller_string_deadline_s;
      }
      else if (rule->scheduler.policy == SCHED_FIFO) {
        policy = controller_string_fifo_s;
      }
      else if (rule->scheduler.policy == SCHED_IDLE) {
        policy = controller_string_idle_s;
      }
      else if (rule->scheduler.policy == SCHED_OTHER) {
        policy = controller_string_other_s;
      }
      else if (rule->scheduler.policy == SCHED_RR) {
        policy = controller_string_round_robin_s;
      }

      fprintf(data.output.stream, " %s %i", policy, rule->scheduler.priority);
    }
    fprintf(data.output.stream, "%c", f_string_eol_s[0]);

    fprintf(data.output.stream, "  %s%s%s %s%c", data.context.set.important.before->string, controller_string_script_s, data.context.set.important.after->string, rule->script.used ? rule->script.string : f_string_empty_s, f_string_eol_s[0]);

    fprintf(data.output.stream, "  %s%s%s", data.context.set.important.before->string, controller_string_user_s, data.context.set.important.after->string);
    if (rule->has & controller_rule_has_user) {
      fprintf(data.output.stream, " %i", rule->user);
    }
    fprintf(data.output.stream, "%c", f_string_eol_s[0]);

    fprintf(data.output.stream, "  %s%s%s {%c", data.context.set.important.before->string, controller_string_affinity_s, data.context.set.important.after->string, f_string_eol_s[0]);

    for (i = 0; i < rule->affinity.used; ++i) {
      fprintf(data.output.stream, "    %i%c", rule->affinity.array[i], f_string_eol_s[0]);
    } // for

    fprintf(data.output.stream, "  }%c", f_string_eol_s[0]);

    fprintf(data.output.stream, "  %s%s%s {%c", data.context.set.important.before->string, controller_string_define_s, data.context.set.important.after->string, f_string_eol_s[0]);

    for (i = 0; i < rule->define.used; ++i) {

      if (rule->define.array[i].name.used && rule->define.array[i].value.used) {
        fprintf(data.output.stream, "    %s %s=%s %s%c", rule->define.array[i].name.string, data.context.set.important.before->string, data.context.set.important.after->string, rule->define.array[i].value.string, f_string_eol_s[0]);
      }
    } // for

    fprintf(data.output.stream, "  }%c", f_string_eol_s[0]);

    fprintf(data.output.stream, "  %s%s%s {%c", data.context.set.important.before->string, controller_string_environment_s, data.context.set.important.after->string, f_string_eol_s[0]);

    for (i = 0; i < rule->environment.used; ++i) {

      if (rule->environment.array[i].used) {
        fprintf(data.output.stream, "    %s%c", rule->environment.array[i].string, f_string_eol_s[0]);
      }
    } // for

    fprintf(data.output.stream, "  }%c", f_string_eol_s[0]);

    fprintf(data.output.stream, "  %s%s%s {%c", data.context.set.important.before->string, controller_string_group_s, data.context.set.important.after->string, f_string_eol_s[0]);

    if (rule->has & controller_rule_has_group) {
      fprintf(data.output.stream, "    %i%c", rule->group, f_string_eol_s[0]);

      for (i = 0; i < rule->groups.used; ++i) {
        fprintf(data.output.stream, "    %i%c", rule->groups.array[i], f_string_eol_s[0]);
      } // for
    }

    fprintf(data.output.stream, "  }%c", f_string_eol_s[0]);

    fprintf(data.output.stream, "  %s%s%s {%c", data.context.set.important.before->string, controller_string_limit_s, data.context.set.important.after->string, f_string_eol_s[0]);

    for (i = 0; i < rule->limits.used; ++i) {

      fprintf(data.output.stream, "    %s %s=%s %llu %llu%c", controller_rule_setting_limit_type_name(rule->limits.array[i].type).string, data.context.set.important.before->string, data.context.set.important.after->string, rule->limits.array[i].value.rlim_cur, rule->limits.array[i].value.rlim_max, f_string_eol_s[0]);
    } // for

    fprintf(data.output.stream, "  }%c", f_string_eol_s[0]);

    fprintf(data.output.stream, "  %s%s%s {%c", data.context.set.important.before->string, controller_string_need_s, data.context.set.important.after->string, f_string_eol_s[0]);

    for (i = 0; i < rule->need.used; ++i) {

      if (rule->need.array[i].used) {
        fprintf(data.output.stream, "    %s%c", rule->need.array[i].string, f_string_eol_s[0]);
      }
    } // for

    fprintf(data.output.stream, "  }%c", f_string_eol_s[0]);

    fprintf(data.output.stream, "  %s%s%s {%c", data.context.set.important.before->string, controller_string_parameter_s, data.context.set.important.after->string, f_string_eol_s[0]);

    for (i = 0; i < rule->parameter.used; ++i) {

      if (rule->parameter.array[i].name.used && rule->parameter.array[i].value.used) {
        fprintf(data.output.stream, "    %s %s=%s %s%c", rule->parameter.array[i].name.string, data.context.set.important.before->string, data.context.set.important.after->string, rule->parameter.array[i].value.string, f_string_eol_s[0]);
      }
    } // for

    fprintf(data.output.stream, "  }%c", f_string_eol_s[0]);

    fprintf(data.output.stream, "  %s%s%s {%c", data.context.set.important.before->string, controller_string_want_s, data.context.set.important.after->string, f_string_eol_s[0]);

    for (i = 0; i < rule->want.used; ++i) {

      if (rule->want.array[i].used) {
        fprintf(data.output.stream, "    %s%c", rule->want.array[i].string, f_string_eol_s[0]);
      }
    } // for

    fprintf(data.output.stream, "  }%c", f_string_eol_s[0]);

    fprintf(data.output.stream, "  %s%s%s {%c", data.context.set.important.before->string, controller_string_wish_s, data.context.set.important.after->string, f_string_eol_s[0]);

    for (i = 0; i < rule->wish.used; ++i) {

      if (rule->wish.array[i].used) {
        fprintf(data.output.stream, "    %s%c", rule->wish.array[i].string, f_string_eol_s[0]);
      }
    } // for

    fprintf(data.output.stream, "  }%c", f_string_eol_s[0]);

    if (rule->items.used) {
      controller_rule_action_t *action = 0;
      controller_rule_item_t *item = 0;
      f_string_dynamic_t *parameter = 0;

      f_array_length_t j = 0;
      f_array_length_t k = 0;

      for (i = 0; i < rule->items.used; ++i) {

        item = &rule->items.array[i];

        fprintf(data.output.stream, "  %s%s%s {%c", data.context.set.important.before->string, controller_string_item_s, data.context.set.important.after->string, f_string_eol_s[0]);

        fprintf(data.output.stream, "    %s%s%s %s%c", data.context.set.important.before->string, controller_string_type_s, data.context.set.important.after->string, controller_rule_item_type_name(item->type).string, f_string_eol_s[0]);

        for (j = 0; j < item->actions.used; ++j) {

          action = &item->actions.array[j];

          fprintf(data.output.stream, "    %s%s%s {%c", data.context.set.important.before->string, controller_string_action_s, data.context.set.important.after->string, f_string_eol_s[0]);

          fprintf(data.output.stream, "      %s%s%s %s%c", data.context.set.important.before->string, controller_string_type_s, data.context.set.important.after->string, controller_rule_action_type_name(action->type).string, f_string_eol_s[0]);

          if (item->type == controller_rule_item_type_script) {
            fprintf(data.output.stream, "      %s%s%s {%c", data.context.set.important.before->string, controller_string_parameter_s, data.context.set.important.after->string, f_string_eol_s[0]);

            parameter = &action->parameters.array[0];

            if (parameter->used) {
              fprintf(data.output.stream, "        ");

              for (k = 0; k < parameter->used; ++k) {

                fprintf(data.output.stream, "%c", parameter->string[k]);

                if (parameter->string[k] == f_fss_eol && k + 1 < parameter->used) {
                  fprintf(data.output.stream, "        ");
                }
              } // for

              fprintf(data.output.stream, "%c", f_string_eol_s[0]);
            }

            fprintf(data.output.stream, "      }%c", f_string_eol_s[0]);
          }
          else {
            for (k = 0; k < action->parameters.used; ++k) {
              fprintf(data.output.stream, "      %s%s%s %s%c", data.context.set.important.before->string, controller_string_parameter_s, data.context.set.important.after->string, action->parameters.array[k].string, f_string_eol_s[0]);
            } // for
          }

          fprintf(data.output.stream, "    }%c", f_string_eol_s[0]);
        } // for

        fprintf(data.output.stream, "  }%c", f_string_eol_s[0]);
      } // for
    }

    fprintf(data.output.stream, "}%c", f_string_eol_s[0]);

    setting->rules.array[index].status = F_complete;
  }
#endif // _di_controller_rule_simulate_

#ifndef _di_controller_rules_increase_
  f_status_t controller_rules_increase(controller_rules_t *rules) {

    if (rules->used + 1 > rules->size) {
      f_array_length_t size = rules->used + controller_default_allocation_step;

      if (size > f_string_length_t_size) {
        if (rules->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      const f_status_t status = f_memory_resize((void **) & rules->array, sizeof(controller_rule_t), rules->size, size);

      if (F_status_is_error_not(status)) {
        rules->size = size;
      }

      return status;
    }

    return F_none;
  }
#endif // _di_controller_rules_increase_

#ifdef __cplusplus
} // extern "C"
#endif
