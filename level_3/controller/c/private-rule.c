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
  f_return_status controller_rule_parameters_read(const controller_data_t data, const f_string_static_t buffer, f_fss_object_t *object, f_fss_content_t *content, f_string_dynamics_t *parameters) {
    f_status_t status = F_none;

    parameters->used = 0;

    if (object && object->start <= object->start) {
      status = fl_string_dynamics_increase(parameters);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamics_increase", F_true);
        return status;
      }

      parameters->array[parameters->used].used = 0;

      status = fl_string_dynamic_partial_append_nulless(buffer, *object, &parameters->array[0]);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_partial_append_nulless", F_true);
        return status;
      }

      status = fl_string_dynamic_terminate_after(&parameters->array[0]);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_terminate_after", F_true);
        return status;
      }

      parameters->used++;
    }

    if (content && content->used) {
      for (f_array_length_t i = 0; i < content->used; ++i) {

        if (content->array[i].start > content->array[i].start) continue;

        status = fl_string_dynamics_increase(parameters);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamics_increase", F_true);
          return status;
        }

        parameters->array[parameters->used].used = 0;

        status = fl_string_dynamic_partial_append_nulless(buffer, content->array[i], &parameters->array[parameters->used]);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_partial_append_nulless", F_true);
          return status;
        }

        status = fl_string_dynamic_terminate_after(&parameters->array[parameters->used]);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_terminate_after", F_true);
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
        buffer.string = controller_string_create;
        buffer.used = controller_string_create_length;
        break;

      case controller_rule_action_type_group:
        buffer.string = controller_string_group;
        buffer.used = controller_string_group_length;
        break;

      case controller_rule_action_type_kill:
        buffer.string = controller_string_kill;
        buffer.used = controller_string_kill_length;
        break;

      case controller_rule_action_type_restart:
        buffer.string = controller_string_restart;
        buffer.used = controller_string_restart_length;
        break;

      case controller_rule_action_type_reload:
        buffer.string = controller_string_reload;
        buffer.used = controller_string_reload_length;
        break;

      case controller_rule_action_type_start:
        buffer.string = controller_string_start;
        buffer.used = controller_string_start_length;
        break;

      case controller_rule_action_type_stop:
        buffer.string = controller_string_stop;
        buffer.used = controller_string_stop_length;
        break;

      case controller_rule_action_type_use:
        buffer.string = controller_string_use;
        buffer.used = controller_string_use_length;
        break;

      case controller_rule_action_type_user:
        buffer.string = controller_string_user;
        buffer.used = controller_string_user_length;
        break;
    }

    buffer.size = buffer.used;

    return buffer;
  }
#endif // _di_controller_rule_action_type_name_

#ifndef _di_controller_rule_actions_increase_by_
  f_return_status controller_rule_actions_increase_by(const f_array_length_t amount, controller_rule_actions_t *actions) {

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
  f_return_status controller_rule_action_read(const controller_data_t data, const uint8_t type, const uint8_t method, controller_cache_t *cache, controller_rule_item_t *item, controller_rule_actions_t *actions, f_string_range_t *range) {
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

        // "script" types use the entire content and can be directly passed through.
        if (item->type == controller_rule_item_type_script) {
          actions->array[actions->used].parameters.used = 0;

          status = fl_string_dynamics_increase(&actions->array[actions->used].parameters);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamics_increase", F_true);
          }
          else {
            actions->array[actions->used].type = type;
            actions->array[actions->used].method = method;
            actions->array[actions->used].line = cache->line_action;

            status = fl_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_action.array[0], &actions->array[actions->used].parameters.array[0]);

            if (F_status_is_error(status)) {
              fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_append_nulless", F_true);
            }

            status = fl_string_dynamic_terminate_after(&actions->array[actions->used].parameters.array[0]);

            if (F_status_is_error(status)) {
              fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_terminate_after", F_true);
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
              actions->array[actions->used].method = method;
              actions->array[actions->used].line += ++item->line;
              actions->array[actions->used].parameters.used = 0;
              actions->array[actions->used].status = F_known_not;

              status = fl_string_dynamics_increase(&actions->array[actions->used].parameters);

              if (F_status_is_error(status)) {
                fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamics_increase", F_true);

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
        else {
          status = f_fss_count_lines(cache->buffer_item, range->start, &actions->array[actions->used].line);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "f_fss_count_lines", F_true);
          }
          else {
            actions->array[actions->used].type = type;
            actions->array[actions->used].method = method;
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
        fprintf(output.to.stream, "%s%s%s%s", output.context.after->string, output.notable.before->string, cache.name_action.string, output.notable.after->string);
        fprintf(output.to.stream, "%s' on line ", output.context.before->string);
        fprintf(output.to.stream, "%s%s%llu%s", output.context.after->string, output.notable.before->string, cache.line_action, output.notable.after->string);
        fprintf(output.to.stream, "%s for ", output.context.before->string);
      }

      if (cache.name_item.used) {
        fprintf(output.to.stream, "rule %s '", item ? "item" : "setting");
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
#endif // _di_controller_rule_error_print_

#ifndef _di_controller_rule_error_print_execute_
  void controller_rule_error_print_execute(const fll_error_print_t output, const bool program_is, const f_string_t name, const int code) {

    if (output.verbosity != f_console_verbosity_quiet) {
      fprintf(output.to.stream, "%c", f_string_eol_s[0]);
      fprintf(output.to.stream, "%s%sThe %s '", output.context.before->string, output.prefix ? output.prefix : f_string_empty_s, program_is ? controller_string_program : controller_string_script);
      fprintf(output.to.stream, "%s%s%s%s", output.context.after->string, output.notable.before->string, name ? name : f_string_empty_s, output.notable.after->string);
      fprintf(output.to.stream, "%s' failed with the exit code '", output.context.before->string);
      fprintf(output.to.stream, "%s%s%d%s", output.context.after->string, output.notable.before->string, code, output.notable.after->string);
      fprintf(output.to.stream, "%s'.%s%c", output.context.before->string, output.context.after->string, f_string_eol_s[0]);
    }
  }
#endif // _di_controller_rule_error_print_execute_

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
  f_return_status controller_rule_execute(const controller_cache_t cache, const f_array_length_t index, const uint8_t type, controller_data_t *data, controller_setting_t *setting) {
    f_status_t status = F_none;

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t k = 0;

    controller_rule_item_t *item = 0;
    controller_rule_action_t *action = 0;

    // child processes should receive all signals, without blocking.
    f_signal_how_t signals = f_signal_how_t_initialize;
    f_signal_set_empty(&signals.block);
    f_signal_set_fill(&signals.block_not);

    f_string_maps_t environment = f_string_maps_t_initialize;

    const f_string_dynamics_t arguments_none = f_string_dynamics_t_initialize;
    fl_execute_parameter_t parameter = fl_macro_execute_parameter_t_initialize(0, &environment, &signals, 0);

    status = fll_environment_load_names(setting->rules.array[index].environment, &environment);

    if (F_status_is_error(status)) {
      fll_error_print(data->error, F_status_set_fine(status), "fll_environment_load_names", F_true);
      return status;
    }

    for (i = 0; i < setting->rules.array[index].items.used; ++i) {

      if (setting->rules.array[index].items.array[i].type == controller_rule_item_type_setting) continue;

      item = &setting->rules.array[index].items.array[i];

      for (j = 0; j < item->actions.used; ++j) {

        if (item->actions.array[j].type != type) continue;

        action = &item->actions.array[j];
        status = F_none;

        parameter.data = 0;
        parameter.option = 0;

        if (item->type == controller_rule_item_type_command) {
          if (action->method == controller_rule_action_method_extended) {
            // @todo
          }
          else {
            // @todo extended list execution.
          }
        }
        else if (item->type == controller_rule_item_type_script) {
          parameter.data = &action->parameters.array[0];

          status = controller_rule_execute_script(*action, 0, arguments_none, &parameter, data);
          if (F_status_is_error(status)) break;
        }
        else if (item->type == controller_rule_item_type_service) {
          if (action->method == controller_rule_action_method_extended) {
            // @todo
          }
          else {
            // @todo extended list execution.
          }
        }
        else {
          // unknown, just ignore for now. (@todo print a warning when in debug mode.)
          continue;
        }

        if (status == F_child || status == F_signal) break;
      } // for

      if (status == F_child || status == F_signal) break;
    } // for

    return status;
  }
#endif // _di_controller_rule_execute_

#ifndef _di_controller_rule_execute_script_
  f_return_status controller_rule_execute_script(const controller_rule_action_t action, const uint8_t options, const f_string_dynamics_t arguments, fl_execute_parameter_t * const parameter, controller_data_t *data) {
    int result = 0;

    // @todo script program (such as: "bash") should be configurable somehow (a new entry setting? a new rule setting? both?).
    f_status_t status = fll_execute_program(controller_string_bash, arguments, parameter, &result);

    if (status == F_child) {
      data->child = result;

      return F_child;
    }

    if (result != 0) {
      controller_rule_error_print_execute(data->error, F_false, controller_string_bash, result);

      status = F_status_set_error(F_failure);
    }
    else if (F_status_is_error(status)) {
      fll_error_print(data->error, F_status_set_fine(status), "fll_execute_program_environment", F_true);
    }

    data->child = 0;

    return status;
  }
#endif // _di_controller_rule_execute_script_

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
  f_return_status controller_rule_id_construct(const controller_data_t data, const f_string_static_t source, const f_string_range_t directory, const f_string_range_t basename, f_string_dynamic_t *id) {
    f_status_t status = F_none;

    id->used = 0;

    status = fl_string_dynamic_partial_append_nulless(source, directory, id);

    if (F_status_is_error(status)) {
      fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_partial_append_nulless", F_true);
      return status;
    }

    status = fl_string_append(f_path_separator_s, f_path_separator_length, id);

    if (F_status_is_error(status)) {
      fll_error_print(data.error, F_status_set_fine(status), "fl_string_append", F_true);
      return status;
    }

    status = fl_string_dynamic_partial_append_nulless(source, basename, id);

    if (F_status_is_error(status)) {
      fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_partial_append_nulless", F_true);
      return status;
    }

    status = fl_string_dynamic_terminate_after(id);

    if (F_status_is_error(status)) {
      fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_terminate_after", F_true);
    }

    return status;
  }
#endif // _di_controller_rule_id_construct_

#ifndef _di_controller_rule_item_read_
  f_return_status controller_rule_item_read(const controller_data_t data, controller_cache_t *cache, controller_rule_item_t *item) {
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

      if (fl_string_dynamic_compare_string(controller_string_create, cache->name_action, controller_string_create_length) == F_equal_to) {
        type = controller_rule_action_type_create;
      }
      else if (fl_string_dynamic_compare_string(controller_string_group, cache->name_action, controller_string_group_length) == F_equal_to) {
        type = controller_rule_action_type_group;
      }
      else if (fl_string_dynamic_compare_string(controller_string_kill, cache->name_action, controller_string_kill_length) == F_equal_to) {
        type = controller_rule_action_type_kill;
      }
      else if (fl_string_dynamic_compare_string(controller_string_restart, cache->name_action, controller_string_restart_length) == F_equal_to) {
        type = controller_rule_action_type_restart;
      }
      else if (fl_string_dynamic_compare_string(controller_string_reload, cache->name_action, controller_string_reload_length) == F_equal_to) {
        type = controller_rule_action_type_reload;
      }
      else if (fl_string_dynamic_compare_string(controller_string_start, cache->name_action, controller_string_start_length) == F_equal_to) {
        type = controller_rule_action_type_start;
      }
      else if (fl_string_dynamic_compare_string(controller_string_stop, cache->name_action, controller_string_stop_length) == F_equal_to) {
        type = controller_rule_action_type_stop;
      }
      else if (fl_string_dynamic_compare_string(controller_string_use, cache->name_action, controller_string_use_length) == F_equal_to) {
        type = controller_rule_action_type_use;
      }
      else if (fl_string_dynamic_compare_string(controller_string_user, cache->name_action, controller_string_user_length) == F_equal_to) {
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
        buffer.string = controller_string_command;
        buffer.used = controller_string_command_length;
        break;

      case controller_rule_item_type_script:
        buffer.string = controller_string_script;
        buffer.used = controller_string_script_length;
        break;

      case controller_rule_item_type_service:
        buffer.string = controller_string_service;
        buffer.used = controller_string_service_length;
        break;

      case controller_rule_item_type_setting:
        buffer.string = controller_string_setting;
        buffer.used = controller_string_setting_length;
        break;
    }

    buffer.size = buffer.used;

    return buffer;
  }
#endif // _di_controller_rule_item_type_name_

#ifndef _di_controller_rule_items_increase_by_
  f_return_status controller_rule_items_increase_by(const f_array_length_t amount, controller_rule_items_t *items) {

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

#ifndef _di_controller_rule_path_
  f_return_status controller_rule_path(const controller_data_t data, const controller_setting_t setting, const f_string_static_t path_directory, const f_string_static_t path_name, f_string_dynamic_t *path) {
    f_status_t status = F_none;

    path->used = 0;

    if (setting.path_setting.used) {
      status = fl_string_append(setting.path_setting.string, setting.path_setting.used, path);

      if (F_status_is_error_not(status)) {
        status = fl_string_append(f_path_separator_s, f_path_separator_length, path);
      }
    }

    if (F_status_is_error_not(status)) {
      status = fl_string_append(controller_string_rules, controller_string_rules_length, path);
    }

    if (F_status_is_error_not(status)) {
      status = fl_string_append(f_path_separator_s, f_path_separator_length, path);
    }

    if (F_status_is_error_not(status)) {
      status = fl_string_append(path_directory.string, path_directory.used, path);
    }

    if (F_status_is_error_not(status)) {
      status = fl_string_append(f_path_separator_s, f_path_separator_length, path);
    }

    if (F_status_is_error_not(status)) {
      status = fl_string_append(path_name.string, path_name.used, path);
    }

    if (F_status_is_error_not(status)) {
      status = fl_string_append(f_path_extension_separator, f_path_extension_separator_length, path);
    }

    if (F_status_is_error_not(status)) {
      status = fl_string_append(controller_string_rule, controller_string_rule_length, path);
    }

    if (F_status_is_error(status)) {
      fll_error_print(data.error, F_status_set_fine(status), "fl_string_append", F_true);
      return status;
    }

    status = fl_string_dynamic_terminate_after(path);

    if (F_status_is_error(status)) {
      fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_terminate_after", F_true);
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
  f_return_status controller_rule_process(const f_array_length_t index, const uint8_t action, const uint8_t options, controller_data_t *data, controller_setting_t *setting, controller_cache_t *cache) {

    switch (action) {
      case controller_rule_action_type_kill:
      case controller_rule_action_type_reload:
      case controller_rule_action_type_restart:
      case controller_rule_action_type_start:
      case controller_rule_action_type_stop:
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

    status = fl_string_append(controller_string_rules, controller_string_rules_length, &cache->name_file);

    if (F_status_is_error_not(status)) {
      status = fl_string_append(f_path_separator_s, f_path_separator_length, &cache->name_file);
    }

    if (F_status_is_error(status)) {
      fll_error_print(data->error, F_status_set_fine(status), "fl_string_append", F_true);
      controller_rule_error_print(data->error, *cache, F_true);

      return status;
    }

    status = fl_string_dynamic_append(setting->rules.array[index].id, &cache->name_file);

    if (F_status_is_error(status)) {
      fll_error_print(data->error, F_status_set_fine(status), "fl_string_dynamic_append", F_true);
      controller_rule_error_print(data->error, *cache, F_true);

      return status;
    }

    status = fl_string_append(f_path_extension_separator, f_path_extension_separator_length, &cache->name_file);

    if (F_status_is_error_not(status)) {
      status = fl_string_append(controller_string_rule, controller_string_rule_length, &cache->name_file);
    }

    if (F_status_is_error(status)) {
      fll_error_print(data->error, F_status_set_fine(status), "fl_string_append", F_true);
      controller_rule_error_print(data->error, *cache, F_true);

      return status;
    }

    status = fl_string_dynamic_terminate_after(&cache->name_file);

    if (F_status_is_error(status)) {
      fll_error_print(data->error, F_status_set_fine(status), "fl_string_dynamic_terminate_after", F_true);
      controller_rule_error_print(data->error, *cache, F_true);

      return status;
    }

    cache->stack.array[cache->stack.used++] = index;

    controller_rule_t *rule = &setting->rules.array[index];

    if ((options & controller_rule_option_simulate) && data->parameters[controller_parameter_validate].result == f_console_result_found) {
      controller_rule_simulate(*data, *cache, index, controller_rule_action_type_start, options, setting);
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
              status = controller_rule_process(at, controller_rule_action_type_start, options, data, setting, cache);

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
                if (i == 0 || i == 1 || F_status_set_fine(status) == F_memory_not || F_status_set_fine(status) == F_memory_allocation || F_status_set_fine(status) == F_memory_reallocation) {

                  controller_rule_error_print_need_want_wish(data->error, strings[i], dynamics[i]->array[j].string, "failed during execution");
                  controller_rule_error_print(data->error, *cache, F_true);

                  if (!(options & controller_rule_option_simulate) || F_status_set_fine(status) == F_memory_not || F_status_set_fine(status) == F_memory_allocation || F_status_set_fine(status) == F_memory_reallocation) {
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

    if (!(options & controller_rule_option_simulate) && F_status_is_error_not(status)) {

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
        status = controller_rule_execute(*cache, index, action, data, setting);

        if (F_status_is_error(status)) {
          fll_error_print(data->error, F_status_set_fine(status), "controller_rule_execute", F_true);
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
  f_return_status controller_rule_read(const controller_data_t data, const controller_setting_t setting, const f_string_static_t rule_id, controller_cache_t *cache, controller_rule_t *rule) {
    f_status_t status = F_none;

    bool for_item = F_true;

    rule->status = F_known_not;

    f_macro_time_spec_t_clear(rule->timestamp);

    rule->id.used = 0;
    rule->name.used = 0;

    rule->define.used = 0;
    rule->parameter.used = 0;

    rule->environment.used = 0;
    rule->need.used = 0;
    rule->want.used = 0;
    rule->wish.used = 0;

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

    status = fl_string_dynamic_append_nulless(rule_id, &rule->id);

    if (F_status_is_error(status)) {
      fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_append_nulless", F_true);
    }
    else {
      status = fl_string_dynamic_terminate_after(&rule->id);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_terminate_after", F_true);
      }
      else {
        status = controller_file_load(data, setting, controller_string_rules, rule->id, controller_string_rule, controller_string_rules_length, controller_string_rule_length, cache);
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

          if (fl_string_dynamic_compare_string(controller_string_setting, cache->name_item, controller_string_setting_length) == F_equal_to) {
            rule->items.array[rule->items.used].type = 0;
          }
          else if (fl_string_dynamic_compare_string(controller_string_command, cache->name_item, controller_string_command_length) == F_equal_to) {
            rule->items.array[rule->items.used].type = controller_rule_item_type_command;
          }
          else if (fl_string_dynamic_compare_string(controller_string_script, cache->name_item, controller_string_script_length) == F_equal_to) {
            rule->items.array[rule->items.used].type = controller_rule_item_type_script;
          }
          else if (fl_string_dynamic_compare_string(controller_string_service, cache->name_item, controller_string_service_length) == F_equal_to) {
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

          status = fl_string_dynamic_partial_append(cache->buffer_file, cache->content_items.array[i].array[0], &cache->buffer_item);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_partial_append", F_true);
            break;
          }

          status = fl_string_dynamic_terminate_after(&cache->buffer_item);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_terminate_after", F_true);
            break;
          }

          if (rule->items.array[rule->items.used].type) {
            status = controller_rule_item_read(data, cache, &rule->items.array[rule->items.used]);
            if (F_status_is_error(status)) break;

            rule->items.used++;
          }
          else {
            for_item = F_false;

            status = controller_rule_setting_read(data, cache, rule);

            if (F_status_is_error(status)) {
              if (F_status_set_fine(status) == F_memory_not || F_status_set_fine(status) == F_memory_allocation || F_status_set_fine(status) == F_memory_reallocation) {
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

    rule->status = F_none;
    return F_true;
  }
#endif // _di_controller_rule_read_

#ifndef _di_controller_rule_setting_read_
  f_return_status controller_rule_setting_read(const controller_data_t data, controller_cache_t *cache, controller_rule_t *rule) {
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

    for (; i < cache->content_actions.used; ++i, type = 0) {

      // name_item is used to store the setting name.
      cache->name_item.used = 0;
      status = fl_string_dynamic_partial_append_nulless(cache->buffer_item, cache->object_actions.array[i], &cache->name_item);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_partial_append_nulless", F_true);
      }
      else {
        status = fl_string_dynamic_terminate_after(&cache->name_item);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_terminate_after", F_true);
        }
      }

      if (F_status_is_error(status)) {
        if (F_status_set_fine(status) == F_memory_not || F_status_set_fine(status) == F_memory_allocation || F_status_set_fine(status) == F_memory_reallocation) {
          return status;
        }

        if (F_status_is_error_not(status_return)) {
          status_return = status;
        }

        controller_rule_error_print(data.error, *cache, F_false);
        continue;
      }

      if (fl_string_dynamic_compare_string(controller_string_control_group, cache->name_item, controller_string_control_group_length) == F_equal_to) {
        type = controller_rule_setting_type_control_group;
      }
      else if (fl_string_dynamic_compare_string(controller_string_define, cache->name_item, controller_string_define_length) == F_equal_to) {
        type = controller_rule_setting_type_define;
      }
      else if (fl_string_dynamic_compare_string(controller_string_environment, cache->name_item, controller_string_environment_length) == F_equal_to) {
        type = controller_rule_setting_type_environment;
      }
      else if (fl_string_dynamic_compare_string(controller_string_name, cache->name_item, controller_string_name_length) == F_equal_to) {
        type = controller_rule_setting_type_name;
      }
      else if (fl_string_dynamic_compare_string(controller_string_need, cache->name_item, controller_string_need_length) == F_equal_to) {
        type = controller_rule_setting_type_need;
      }
      else if (fl_string_dynamic_compare_string(controller_string_parameter, cache->name_item, controller_string_parameter_length) == F_equal_to) {
        type = controller_rule_setting_type_parameter;
      }
      else if (fl_string_dynamic_compare_string(controller_string_path, cache->name_item, controller_string_path_length) == F_equal_to) {
        type = controller_rule_setting_type_path;
      }
      else if (fl_string_dynamic_compare_string(controller_string_want, cache->name_item, controller_string_want_length) == F_equal_to) {
        type = controller_rule_setting_type_want;
      }
      else if (fl_string_dynamic_compare_string(controller_string_wish, cache->name_item, controller_string_wish_length) == F_equal_to) {
        type = controller_rule_setting_type_wish;
      }
      else {
        if (data.warning.verbosity == f_console_verbosity_debug) {
          fprintf(data.warning.to.stream, "%s%sUnknown rule setting '", data.warning.context.before->string, data.warning.prefix ? data.warning.prefix : f_string_empty_s);
          fprintf(data.warning.to.stream, "%s%s", data.warning.context.after->string, data.warning.notable.before->string);
          f_print_dynamic(data.warning.to.stream, cache->name_item);
          fprintf(data.warning.to.stream, "%s", data.warning.notable.after->string);
          fprintf(data.warning.to.stream, "%s'.%s%c", data.warning.context.before->string, data.warning.context.after->string, f_string_eol_s[0]);

          controller_rule_error_print(data.warning, *cache, F_false);
        }

        continue;
      }

      if (!cache->content_actions.array[i].used) {
        if (data.warning.verbosity == f_console_verbosity_debug) {
          fprintf(data.warning.to.stream, "%c", f_string_eol_s[0]);
          fprintf(data.warning.to.stream, "%s%sEmpty rule setting.%s%c", data.warning.context.before->string, data.warning.prefix ? data.warning.prefix : f_string_empty_s, data.warning.context.after->string, f_string_eol_s[0]);

          controller_rule_error_print(data.warning, *cache, F_false);
        }

        continue;
      }

      // name_action is used to store all setting values for a single setting.
      cache->name_action.used = 0;

      range2.start = cache->content_actions.array[i].array[0].start;
      range2.stop = cache->content_actions.array[i].array[cache->content_actions.array[i].used - 1].stop;

      status = fl_string_dynamic_partial_append_nulless(cache->buffer_item, range2, &cache->name_action);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_partial_append_nulless", F_true);
      }
      else {
        status = fl_string_dynamic_terminate_after(&cache->name_action);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_terminate_after", F_true);
        }
      }

      if (F_status_is_error(status)) {
        controller_rule_error_print(data.error, *cache, F_false);

        if (F_status_set_fine(status) == F_memory_not || F_status_set_fine(status) == F_memory_allocation || F_status_set_fine(status) == F_memory_reallocation) {
          return status;
        }

        if (F_status_is_error_not(status_return)) {
          status_return = status;
        }

        controller_rule_error_print(data.error, *cache, F_false);
        continue;
      }

      if (type == controller_rule_setting_type_define || type == controller_rule_setting_type_parameter) {

        if (cache->content_actions.array[i].used != 2) {
          fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
          fprintf(data.error.to.stream, "%s%sRule setting requires exactly two Content.%s%c", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s, data.error.context.after->string, f_string_eol_s[0]);

          controller_rule_error_print(data.error, *cache, F_false);

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

        status = fl_string_maps_increase(setting_maps);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "fl_string_maps_increase", F_true);

          if (F_status_set_fine(status) == F_memory_not || F_status_set_fine(status) == F_memory_allocation || F_status_set_fine(status) == F_memory_reallocation) {
            return status;
          }

          if (F_status_is_error_not(status_return)) {
            status_return = status;
          }

          controller_rule_error_print(data.error, *cache, F_false);
          continue;
        }

        setting_maps->array[setting_maps->used].name.used = 0;
        setting_maps->array[setting_maps->used].value.used = 0;

        status = fl_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[0], &setting_maps->array[setting_maps->used].name);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_partial_append_nulless", F_true);

          if (F_status_set_fine(status) == F_memory_not || F_status_set_fine(status) == F_memory_allocation || F_status_set_fine(status) == F_memory_reallocation) {
            return status;
          }

          if (F_status_is_error_not(status_return)) {
            status_return = status;
          }

          controller_rule_error_print(data.error, *cache, F_false);
          continue;
        }

        status = fl_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[1], &setting_maps->array[setting_maps->used].value);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_partial_append_nulless", F_true);
        }
        else {
          status = fl_string_dynamic_terminate_after(&setting_maps->array[setting_maps->used].value);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_terminate_after", F_true);
          }
        }

        if (F_status_is_error(status)) {
          if (F_status_set_fine(status) == F_memory_not || F_status_set_fine(status) == F_memory_allocation || F_status_set_fine(status) == F_memory_reallocation) {
            return status;
          }

          if (F_status_is_error_not(status_return)) {
            status_return = status;
          }

          controller_rule_error_print(data.error, *cache, F_false);
          continue;
        }

        setting_maps->used++;
        continue;
      }

      if (type == controller_rule_setting_type_control_group || type == controller_rule_setting_type_name || type == controller_rule_setting_type_path) {
        if (type == controller_rule_setting_type_control_group) {
          setting_value = &rule->control_group;
        }
        else if (type == controller_rule_setting_type_name) {
          setting_value = &rule->name;
        }
        else if (type == controller_rule_setting_type_path) {
          setting_value = &rule->path;
        }

        if (setting_value->used || cache->content_actions.array[i].used != 1) {
          fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
          fprintf(data.error.to.stream, "%s%sRule setting requires exactly one Content.%s%c", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s, data.error.context.after->string, f_string_eol_s[0]);

          controller_rule_error_print(data.error, *cache, F_false);

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        setting_value->used = 0;

        if (type == controller_rule_setting_type_control_group || type == controller_rule_setting_type_name) {

          status = controller_string_dynamic_rip_nulless_terminated(cache->buffer_item, cache->content_actions.array[i].array[0], setting_value);

          if (F_status_is_error(status)) {
            setting_value->used = 0;

            if (F_status_set_fine(status) == F_memory_not || F_status_set_fine(status) == F_memory_allocation || F_status_set_fine(status) == F_memory_reallocation) {
              return status;
            }

            if (F_status_is_error_not(status_return)) {
              status_return = status;
            }

            controller_rule_error_print(data.error, *cache, F_false);
            continue;
          }

          status = controller_validate_has_graph(*setting_value);

          if (status == F_false || F_status_set_fine(status) == F_complete_not_utf) {
            if (status == F_false) {
              fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
              fprintf(data.error.to.stream, "%s%sRule setting has an invalid name '", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s);
              fprintf(data.error.to.stream, "%s%s", data.error.context.after->string, data.error.notable.before->string);
              f_print_dynamic(data.error.to.stream, *setting_value);
              fprintf(data.error.to.stream, "%s", data.error.notable.after->string);
              fprintf(data.error.to.stream, "%s', there must be at least 1 graph character.%s%c", data.error.context.before->string, data.error.context.after->string, f_string_eol_s[0]);

              controller_rule_error_print(data.error, *cache, F_false);

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

            controller_rule_error_print(data.error, *cache, F_false);
            continue;
          }
        }
        else if (type == controller_rule_setting_type_path) {
          status = fl_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[0], setting_value);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_partial_append_nulless", F_true);
          }
          else {
            status = fl_string_dynamic_terminate_after(setting_value);

            if (F_status_is_error(status)) {
              fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_terminate_after", F_true);
            }
          }

          if (F_status_is_error(status)) {
            if (F_status_set_fine(status) == F_memory_not || F_status_set_fine(status) == F_memory_allocation || F_status_set_fine(status) == F_memory_reallocation) {
              return status;
            }

            if (F_status_is_error_not(status_return)) {
              status_return = status;
            }

            setting_value->used = 0;

            controller_rule_error_print(data.error, *cache, F_false);
            continue;
          }
        }

        continue;
      }

      if (type == controller_rule_setting_type_environment) {
        setting_values = &rule->environment;

        for (j = 0; j < cache->content_actions.array[i].used; ++j) {

          status = fl_string_dynamics_increase(setting_values);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamics_increase", F_true);

            if (F_status_set_fine(status) == F_memory_not || F_status_set_fine(status) == F_memory_allocation || F_status_set_fine(status) == F_memory_reallocation) {
              return status;
            }

            if (F_status_is_error_not(status_return)) {
              status_return = status;
            }

            controller_rule_error_print(data.error, *cache, F_false);
            continue;
          }

          setting_values->array[setting_values->used].used = 0;

          status = fl_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[j], &setting_values->array[setting_values->used]);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_partial_append_nulless", F_true);
          }
          else {
            status = fl_string_dynamic_terminate_after(&setting_values->array[setting_values->used]);

            if (F_status_is_error(status)) {
              fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_terminate_after", F_true);
            }
          }

          if (F_status_is_error(status)) {
            setting_values->array[setting_values->used].used = 0;

            if (F_status_set_fine(status) == F_memory_not || F_status_set_fine(status) == F_memory_allocation || F_status_set_fine(status) == F_memory_reallocation) {
              return status;
            }

            if (F_status_is_error_not(status_return)) {
              status_return = status;
            }

            controller_rule_error_print(data.error, *cache, F_false);
            continue;
          }

          status = controller_validate_environment_name(setting_values->array[setting_values->used]);

          if (status == F_false || F_status_set_fine(status) == F_complete_not_utf) {
            if (status == F_false) {
              fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
              fprintf(data.error.to.stream, "%s%sRule setting has an invalid environment variable name '", data.error.context.before->string, data.error.prefix ? data.error.prefix : f_string_empty_s);
              fprintf(data.error.to.stream, "%s%s%s%s", data.error.context.after->string, data.error.notable.before->string, setting_values->array[setting_values->used].string, data.error.notable.after->string);
              fprintf(data.error.to.stream, "%s'.%s%c", data.error.context.before->string, data.error.context.after->string, f_string_eol_s[0]);

              controller_rule_error_print(data.error, *cache, F_false);

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

      status = fl_string_dynamics_increase_by(controller_default_allocation_step, setting_values);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamics_increase_by", F_true);

        if (F_status_set_fine(status) == F_memory_not || F_status_set_fine(status) == F_memory_allocation || F_status_set_fine(status) == F_memory_reallocation) {
          return status;
        }

        if (F_status_is_error_not(status_return)) {
          status_return = status;
        }

        controller_rule_error_print(data.error, *cache, F_false);
        continue;
      }

      status = controller_rule_id_construct(data, cache->buffer_item, cache->content_actions.array[i].array[0], cache->content_actions.array[i].array[1], &setting_values->array[setting_values->used]);

      if (F_status_is_error(status)) {
        setting_values->array[setting_values->used].used = 0;

        if (F_status_set_fine(status) == F_memory_not || F_status_set_fine(status) == F_memory_allocation || F_status_set_fine(status) == F_memory_reallocation) {
          return status;
        }

        if (F_status_is_error_not(status_return)) {
          status_return = status;
        }

        controller_rule_error_print(data.error, *cache, F_false);
        continue;
      }

      cache->buffer_path.used = 0;

      status = f_file_name_base(setting_values->array[setting_values->used].string, setting_values->array[setting_values->used + 1].used, &cache->buffer_path);

      if (F_status_is_error(status)) {
        setting_values->array[setting_values->used].used = 0;

        fll_error_print(data.error, F_status_set_fine(status), "f_file_name_base", F_true);

        if (F_status_set_fine(status) == F_memory_not || F_status_set_fine(status) == F_memory_allocation || F_status_set_fine(status) == F_memory_reallocation) {
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

    return status_return;
  }
#endif // _di_controller_rule_setting_read_

#ifndef _di_controller_rule_simulate_
  void controller_rule_simulate(const controller_data_t data, const controller_cache_t cache, const f_array_length_t index, const uint8_t action, const uint8_t options, controller_setting_t *setting) {

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

          controller_rule_error_print(data.error, cache, F_true);
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
        fprintf(data.output.stream, "%s%s%s", data.context.set.important.before->string, options & controller_rule_option_require ? controller_string_fail : controller_string_succeed, data.context.set.important.after->string);
        fprintf(data.output.stream, "' because it is '");
        fprintf(data.output.stream, "%s%s%s", data.context.set.important.before->string, options & controller_rule_option_require ? controller_string_required : controller_string_optional, data.context.set.important.after->string);
        fprintf(data.output.stream, "'.%c", f_string_eol_s[0]);
      }
    }

    fprintf(data.output.stream, "%c", f_string_eol_s[0]);
    fprintf(data.output.stream, "Rule %s%s%s {%c", data.context.set.title.before->string, rule->id.used ? rule->id.string : f_string_empty_s, data.context.set.title.after->string, f_string_eol_s[0]);
    fprintf(data.output.stream, "  %s%s%s %s%c", data.context.set.important.before->string, controller_string_name, data.context.set.important.after->string, rule->name.used ? rule->name.string : f_string_empty_s, f_string_eol_s[0]);
    fprintf(data.output.stream, "  %s%s%s %s%c", data.context.set.important.before->string, controller_string_how, data.context.set.important.after->string, options & controller_rule_option_asynchronous ? controller_string_asynchronous : controller_string_synchronous, f_string_eol_s[0]);
    fprintf(data.output.stream, "  %s%s%s %s%c", data.context.set.important.before->string, controller_string_wait, data.context.set.important.after->string, options & controller_rule_option_wait ? controller_string_yes : controller_string_no, f_string_eol_s[0]);
    fprintf(data.output.stream, "  %s%s%s %s%c", data.context.set.important.before->string, controller_string_control_group, data.context.set.important.after->string, rule->control_group.used ? rule->control_group.string : f_string_empty_s, f_string_eol_s[0]);

    fprintf(data.output.stream, "  %s%s%s {%c", data.context.set.important.before->string, controller_string_define, data.context.set.important.after->string, f_string_eol_s[0]);

    if (rule->define.used) {
      for (i = 0; i < rule->define.used; ++i) {

        if (rule->define.array[i].name.used && rule->define.array[i].value.used) {
          fprintf(data.output.stream, "    %s %s=%s %s%c", rule->define.array[i].name.string, data.context.set.important.before->string, data.context.set.important.after->string, rule->define.array[i].value.string, f_string_eol_s[0]);
        }
      } // for
    }

    fprintf(data.output.stream, "  }%c", f_string_eol_s[0]);

    fprintf(data.output.stream, "  %s%s%s {%c", data.context.set.important.before->string, controller_string_parameter, data.context.set.important.after->string, f_string_eol_s[0]);

    if (rule->parameter.used) {
      for (i = 0; i < rule->parameter.used; ++i) {

        if (rule->parameter.array[i].name.used && rule->parameter.array[i].value.used) {
          fprintf(data.output.stream, "    %s %s=%s %s%c", rule->parameter.array[i].name.string, data.context.set.important.before->string, data.context.set.important.after->string, rule->parameter.array[i].value.string, f_string_eol_s[0]);
        }
      } // for
    }

    fprintf(data.output.stream, "  }%c", f_string_eol_s[0]);

    fprintf(data.output.stream, "  %s%s%s {%c", data.context.set.important.before->string, controller_string_environment, data.context.set.important.after->string, f_string_eol_s[0]);

    if (rule->environment.used) {
      for (i = 0; i < rule->environment.used; ++i) {

        if (rule->environment.array[i].used) {
          fprintf(data.output.stream, "    %s%c", rule->environment.array[i].string, f_string_eol_s[0]);
        }
      } // for
    }

    fprintf(data.output.stream, "  }%c", f_string_eol_s[0]);

    fprintf(data.output.stream, "  %s%s%s {%c", data.context.set.important.before->string, controller_string_need, data.context.set.important.after->string, f_string_eol_s[0]);

    if (rule->need.used) {
      for (i = 0; i < rule->need.used; ++i) {

        if (rule->need.array[i].used) {
          fprintf(data.output.stream, "    %s%c", rule->need.array[i].string, f_string_eol_s[0]);
        }
      } // for
    }

    fprintf(data.output.stream, "  }%c", f_string_eol_s[0]);

    fprintf(data.output.stream, "  %s%s%s {%c", data.context.set.important.before->string, controller_string_want, data.context.set.important.after->string, f_string_eol_s[0]);

    if (rule->want.used) {
      for (i = 0; i < rule->want.used; ++i) {

        if (rule->want.array[i].used) {
          fprintf(data.output.stream, "    %s%c", rule->want.array[i].string, f_string_eol_s[0]);
        }
      } // for
    }

    fprintf(data.output.stream, "  }%c", f_string_eol_s[0]);

    fprintf(data.output.stream, "  %s%s%s {%c", data.context.set.important.before->string, controller_string_wish, data.context.set.important.after->string, f_string_eol_s[0]);

    if (rule->wish.used) {
      for (i = 0; i < rule->wish.used; ++i) {

        if (rule->wish.array[i].used) {
          fprintf(data.output.stream, "    %s%c", rule->wish.array[i].string, f_string_eol_s[0]);
        }
      } // for
    }

    fprintf(data.output.stream, "  }%c", f_string_eol_s[0]);

    if (rule->items.used) {
      controller_rule_action_t *action = 0;
      controller_rule_item_t *item = 0;
      f_string_dynamic_t *parameter = 0;

      f_array_length_t j = 0;
      f_array_length_t k = 0;

      for (i = 0; i < rule->items.used; ++i) {

        item = &rule->items.array[i];

        fprintf(data.output.stream, "  %s%s%s {%c", data.context.set.important.before->string, controller_string_item, data.context.set.important.after->string, f_string_eol_s[0]);

        fprintf(data.output.stream, "    %s%s%s %s%c", data.context.set.important.before->string, controller_string_type, data.context.set.important.after->string, controller_rule_item_type_name(item->type).string, f_string_eol_s[0]);

        for (j = 0; j < item->actions.used; ++j) {

          action = &item->actions.array[j];

          fprintf(data.output.stream, "    %s%s%s {%c", data.context.set.important.before->string, controller_string_action, data.context.set.important.after->string, f_string_eol_s[0]);

          fprintf(data.output.stream, "      %s%s%s %s%c", data.context.set.important.before->string, controller_string_type, data.context.set.important.after->string, controller_rule_action_type_name(action->type).string, f_string_eol_s[0]);
          fprintf(data.output.stream, "      %s%s%s %s%c", data.context.set.important.before->string, controller_string_method, data.context.set.important.after->string, controller_rule_action_method_name(action->method).string, f_string_eol_s[0]);

          if (action->method == controller_rule_action_method_extended_list && item->type == controller_rule_item_type_script) {
            fprintf(data.output.stream, "      %s%s%s {%c", data.context.set.important.before->string, controller_string_parameter, data.context.set.important.after->string, f_string_eol_s[0]);

            parameter = &action->parameters.array[0];

            if (parameter->used) {
              fprintf(data.output.stream, "        ");

              for (k = 0; k < parameter->used; ++k) {

                fprintf(data.output.stream, "%c", parameter->string[k]);

                if (parameter->string[k] == f_fss_eol && k + 1 < parameter->used) {
                  fprintf(data.output.stream, "        ");
                }
              } // for
            }

            fprintf(data.output.stream, "      }%c", f_string_eol_s[0]);
          }
          else {
            for (k = 0; k < action->parameters.used; ++k) {
              fprintf(data.output.stream, "      %s%s%s %s%c", data.context.set.important.before->string, controller_string_parameter, data.context.set.important.after->string, action->parameters.array[k].string, f_string_eol_s[0]);
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
  f_return_status controller_rules_increase(controller_rules_t *rules) {

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
