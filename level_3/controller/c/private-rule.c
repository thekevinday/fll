#include "controller.h"
#include "private-common.h"
#include "private-controller.h"
#include "private-rule.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_rule_action_read_
  f_return_status controller_rule_action_read(const controller_data_t data, const f_string_static_t buffer, f_fss_object_t *object, f_fss_content_t *content, controller_rule_action_t *action) {
    f_status_t status = F_none;

    if (object && object->start <= object->start) {
      status = fl_string_dynamics_increase(&action->parameters);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamics_increase", F_true);
        return status;
      }

      action->parameters.array[0].used = 0;

      status = fl_string_dynamic_partial_append_nulless(buffer, *object, &action->parameters.array[0]);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_partial_append_nulless", F_true);
        return status;
      }

      action->parameters.used++;
    }

    if (content && content->used) {
      for (f_array_length_t i = 0; i < content->used; ++i) {

        if (content->array[i].start > content->array[i].start) continue;

        action->parameters.array[action->parameters.used].used = 0;

        status = fl_string_dynamic_partial_append_nulless(buffer, content->array[i], &action->parameters.array[action->parameters.used]);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_partial_append_nulless", F_true);
          return status;
        }

        action->parameters.used++;
      } // for
    }

    return F_none;
  }
#endif // _di_controller_rule_action_read_

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

#ifndef _di_controller_rule_actions_read_
  f_return_status controller_rule_actions_read(const controller_data_t data, controller_cache_t *cache, controller_rule_item_t *item, controller_rule_actions_t *actions, f_string_range_t *range) {
    f_status_t status = F_none;

    actions->used = 0;

    // "script" types use the entire content and can be directly passed through.
    if (item->type == controller_rule_item_type_script) {
      status = controller_rule_actions_increase_by(controller_default_allocation_step, actions);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "controller_rule_actions_increase_by", F_true);
      }
      else {
        actions->array[0].parameters.used = 0;

        status = fl_string_dynamics_increase(&actions->array[0].parameters);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamics_increase", F_true);
        }
        else {
          actions->array[0].line = cache->line_action;

          status = fl_string_dynamic_partial_append_nulless(cache->buffer_item, cache->range_action, &actions->array[0].parameters.array[0]);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_append_nulless", F_true);
          }
        }
      }

      return status;
    }

    if (actions->method == controller_rule_action_method_extended_list) {
      cache->comments.used = 0;
      cache->delimits.used = 0;
      cache->content_actions.used = 0;
      cache->object_actions.used = 0;

      status = fl_fss_extended_list_content_read(cache->buffer_item, range, &cache->content_action, &cache->delimits, &cache->comments);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "fl_fss_extended_list_content_read", F_true);
      }
      else if (status == FL_fss_found_content) {
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

              status = f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &actions->array[actions->used].line);

              if (F_status_is_error(status)) {
                fll_error_print(data.error, F_status_set_fine(status), "f_fss_count_lines", F_true);
                break;
              }

              actions->array[actions->used].line += item->line;
              actions->array[actions->used].parameters.used = 0;
              actions->array[actions->used].status = F_known_not;

              status = fl_string_dynamics_increase(&actions->array[actions->used].parameters);

              if (F_status_is_error(status)) {
                fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamics_increase", F_true);

                actions->array[actions->used].status = controller_status_simplify(F_status_set_fine(status));
                break;
              }

              status = controller_rule_action_read(data, cache->buffer_item, &cache->object_actions.array[i], &cache->content_actions.array[i], &actions->array[actions->used]);

              actions->array[actions->used].status = controller_status_simplify(F_status_set_fine(status));
              actions->used++;
            } // for
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
          status = controller_rule_actions_increase_by(controller_default_allocation_step, actions);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "controller_rule_actions_increase_by", F_true);
          }
          else {
            status = f_fss_count_lines(cache->buffer_item, range->start, &actions->array[0].line);

            if (F_status_is_error(status)) {
              fll_error_print(data.error, F_status_set_fine(status), "f_fss_count_lines", F_true);
            }
            else {
              actions->array[0].line += item->line;
              actions->array[0].parameters.used = 0;
              actions->array[0].status = F_known_not;

              status = controller_rule_action_read(data, cache->buffer_item, 0, &cache->content_action, &actions->array[0]);

              if (F_status_is_error(status)) {
                fll_error_print(data.error, F_status_set_fine(status), "controller_rule_action_read", F_true);

                actions->array[0].status = controller_status_simplify(F_status_set_fine(status));
              }
              else {
                actions->array[0].status = status;
              }

              actions->used = 1;
            }
          }
        }
      }
      else {
        status = F_data_not;
      }
    }

    if (F_status_is_error_not(status) && status == F_data_not) {
      if (data.warning.verbosity == f_console_verbosity_debug) {
        fprintf(data.warning.to.stream, "%c", f_string_eol[0]);
        fprintf(data.warning.to.stream, "%s%sAction is empty, nothing to do.%s%c", data.warning.context.before->string, data.warning.prefix ? data.warning.prefix : "", data.warning.context.after->string, f_string_eol[0]);

        controller_rule_error_print(data.warning, *cache, F_true);
      }
    }

    return status;
  }
#endif // _di_controller_rule_actions_read_

#ifndef _di_controller_rule_error_print_
  void controller_rule_error_print(const fll_error_print_t output, const controller_cache_t cache, const bool item) {

    if (output.verbosity != f_console_verbosity_quiet) {
      fprintf(output.to.stream, "%c", f_string_eol[0]);
      fprintf(output.to.stream, "%s%sWhile processing ", output.context.before->string, output.prefix ? output.prefix : "");

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
        fprintf(output.to.stream, "%s'.%s%c", output.context.before->string, output.context.after->string, f_string_eol[0]);
      }
    }
  }
#endif // _di_controller_rule_error_print_

#ifndef _di_controller_rule_item_read_
  f_return_status controller_rule_item_read(const controller_data_t data, controller_cache_t *cache, controller_rule_item_t *item) {
    f_status_t status = F_none;

    f_string_range_t range = f_macro_string_range_t_initialize(cache->buffer_item.used);

    controller_rule_actions_t *actions = 0;

    bool multiple = F_false;

    for (range.start = 0; range.start < cache->buffer_item.used && range.start <= range.stop; cache->delimits.used = 0, cache->comments.used = 0) {

      status = fl_fss_extended_list_object_read(cache->buffer_item, &range, &cache->range_action, &cache->delimits);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "fl_fss_extended_list_object_read", F_true);
        break;
      }

      if (range.start >= range.stop || range.start >= cache->buffer_item.used) {
        if (status == FL_fss_found_object || status == FL_fss_found_object_content_not) {
          if (data.error.verbosity != f_console_verbosity_quiet) {
            fprintf(data.error.to.stream, "%c", f_string_eol[0]);
            fprintf(data.error.to.stream, "%s%sUnterminated FSS Extended List at end of rule file.%s%c", data.error.context.before->string, data.error.prefix ? data.error.prefix : "", data.error.context.after->string, f_string_eol[0]);
          }

          status = F_status_set_error(FL_fss_found_object_content_not);
        }

        break;
      }

      if (status == FL_fss_found_object) {
        multiple = F_true;
      }
      else {
        multiple = F_false;
        cache->delimits.used = 0;

        // The current line is not an Extended List object, so the next possibility is a Basic List (and Extended List, both use the same Object structure).
        status = fl_fss_extended_object_read(cache->buffer_item, &range, &cache->range_action, 0, &cache->delimits);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "fl_fss_extended_object_read", F_true);
          break;
        }
      }

      if (status == FL_fss_found_object_content_not || range.start >= range.stop || range.start >= cache->buffer_item.used) {
        // object ended without any content.
        break;
      }

      if (status == FL_fss_found_object) {
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

        cache->line_action += item->line;
        cache->name_action.used = 0;

        status = fl_string_dynamic_rip_nulless(cache->buffer_item, cache->range_action, &cache->name_action);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_rip_nulless", F_true);
          break;
        }

        status = fl_string_dynamic_terminate_after(&cache->name_action);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_terminate_after", F_true);
          break;
        }

        if (fl_string_dynamic_compare_string(controller_string_create, cache->name_action, controller_string_create_length) == F_equal_to) {
          item->actions.type = controller_rule_action_type_create;
        }
        else if (fl_string_dynamic_compare_string(controller_string_group, cache->name_action, controller_string_group_length) == F_equal_to) {
          item->actions.type = controller_rule_action_type_group;
        }
        else if (fl_string_dynamic_compare_string(controller_string_kill, cache->name_action, controller_string_kill_length) == F_equal_to) {
          item->actions.type = controller_rule_action_type_kill;
        }
        else if (fl_string_dynamic_compare_string(controller_string_restart, cache->name_action, controller_string_restart_length) == F_equal_to) {
          item->actions.type = controller_rule_action_type_restart;
        }
        else if (fl_string_dynamic_compare_string(controller_string_reload, cache->name_action, controller_string_reload_length) == F_equal_to) {
          item->actions.type = controller_rule_action_type_reload;
        }
        else if (fl_string_dynamic_compare_string(controller_string_start, cache->name_action, controller_string_start_length) == F_equal_to) {
          item->actions.type = controller_rule_action_type_start;
        }
        else if (fl_string_dynamic_compare_string(controller_string_stop, cache->name_action, controller_string_stop_length) == F_equal_to) {
          item->actions.type = controller_rule_action_type_stop;
        }
        else if (fl_string_dynamic_compare_string(controller_string_use, cache->name_action, controller_string_use_length) == F_equal_to) {
          item->actions.type = controller_rule_action_type_use;
        }
        else if (fl_string_dynamic_compare_string(controller_string_user, cache->name_action, controller_string_user_length) == F_equal_to) {
          item->actions.type = controller_rule_action_type_user;
        }
        else {
          if (data.warning.verbosity == f_console_verbosity_debug) {
            fprintf(data.warning.to.stream, "%c", f_string_eol[0]);
            fprintf(data.warning.to.stream, "%s%sUnknown rule item action type.%s%c", data.warning.context.before->string, data.warning.prefix ? data.warning.prefix : "", data.warning.context.after->string, f_string_eol[0]);

            controller_rule_error_print(data.warning, *cache, F_true);
          }

          continue;
        }

        if (multiple) {
          if (item->actions.type == controller_rule_action_type_create || item->actions.type == controller_rule_action_type_group || item->actions.type == controller_rule_action_type_use || item->actions.type == controller_rule_action_type_user) {
            if (data.error.verbosity != f_console_verbosity_quiet) {
              fprintf(data.error.to.stream, "%c", f_string_eol[0]);
              fprintf(data.error.to.stream, "%s%sFSS Extended List is not allowed for this rule item action type.%s%c", data.error.context.before->string, data.error.prefix ? data.error.prefix : "", data.error.context.after->string, f_string_eol[0]);
            }

            status = F_status_set_error(F_supported_not);
            break;
          }

          item->actions.method = controller_rule_action_method_extended_list;
        }
        else {
          item->actions.method = controller_rule_action_method_extended;
        }

        status = controller_rule_actions_read(data, cache, item, &item->actions, &range);
        if (F_status_is_error(status)) break;
      }
    } // for

    return status;
  }
#endif // _di_controller_rule_item_read_

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

#ifndef _di_controller_rule_read_
  f_return_status controller_rule_read(const controller_data_t data, const controller_setting_t setting, const f_string_static_t rule_id, controller_cache_t *cache, controller_rule_t *rule) {
    f_status_t status = F_none;

    bool for_item = F_true;

    rule->status = F_known_not;

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
      status = controller_file_load(data, setting, controller_string_rules, rule->id, controller_string_rule, controller_string_rules_length, controller_string_rule_length, &cache->name_file, &cache->buffer_file);
    }

    if (F_status_is_error_not(status) && cache->buffer_file.used) {
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

    if (F_status_is_error_not(status) && cache->object_items.used) {
      status = controller_rule_items_increase_by(cache->object_items.used, &rule->items);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "controller_rule_items_increase_by", F_true);
      }
      else {
        for (f_array_length_t i = 0; i < cache->object_items.used; ++i) {

          cache->line_item = 0;
          cache->line_action = 0;

          cache->range_action.start = 1;
          cache->range_action.stop = 0;

          cache->comments.used = 0;
          cache->delimits.used = 0;

          cache->content_action.used = 0;
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

          rule->items.array[rule->items.used].line = cache->line_item;

          status = fl_string_dynamic_rip_nulless(cache->buffer_file, cache->object_items.array[i], &cache->name_item);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_rip_nulless", F_true);
            break;
          }

          status = fl_string_dynamic_terminate_after(&cache->name_item);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_terminate_after", F_true);
            break;
          }

          if (fl_string_dynamic_compare_string(controller_string_settings, cache->name_item, controller_string_settings_length) == F_equal_to) {
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
              fprintf(data.warning.to.stream, "%c", f_string_eol[0]);
              fprintf(data.warning.to.stream, "%s%sUnknown rule item type.%s%c", data.warning.context.before->string, data.warning.prefix ? data.warning.prefix : "", data.warning.context.after->string, f_string_eol[0]);

              controller_rule_error_print(data.warning, *cache, F_true);
            }

            continue;
          }

          status = fl_string_dynamic_partial_append(cache->buffer_file, cache->content_items.array[i].array[0], &cache->buffer_item);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_partial_append", F_true);
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
          fprintf(data.warning.to.stream, "%c", f_string_eol[0]);
          fprintf(data.warning.to.stream, "%s%sUnknown rule setting.%s%c", data.warning.context.before->string, data.warning.prefix ? data.warning.prefix : "", data.warning.context.after->string, f_string_eol[0]);

          controller_rule_error_print(data.warning, *cache, F_false);
        }

        continue;
      }

      if (!cache->content_actions.array[i].used) {
        if (data.warning.verbosity == f_console_verbosity_debug) {
          fprintf(data.warning.to.stream, "%c", f_string_eol[0]);
          fprintf(data.warning.to.stream, "%s%sEmpty rule setting.%s%c", data.warning.context.before->string, data.warning.prefix ? data.warning.prefix : "", data.warning.context.after->string, f_string_eol[0]);

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
          fprintf(data.error.to.stream, "%c", f_string_eol[0]);
          fprintf(data.error.to.stream, "%s%sRule setting requires exactly two Content.%s%c", data.error.context.before->string, data.error.prefix ? data.error.prefix : "", data.error.context.after->string, f_string_eol[0]);

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

        setting_maps->array[setting_maps->used].name.used = 0;
        setting_maps->array[setting_maps->used].value.used = 0;

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
          fprintf(data.error.to.stream, "%c", f_string_eol[0]);
          fprintf(data.error.to.stream, "%s%sRule setting requires exactly one Content.%s%c", data.error.context.before->string, data.error.prefix ? data.error.prefix : "", data.error.context.after->string, f_string_eol[0]);

          controller_rule_error_print(data.error, *cache, F_false);

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        setting_value->used = 0;

        if (type == controller_rule_setting_type_control_group || type == controller_rule_setting_type_name) {
          status = fl_string_dynamic_rip_nulless(cache->buffer_item, cache->content_actions.array[i].array[0], setting_value);

          if (F_status_is_error(status)) {
            setting_value->used = 0;

            fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_rip_nulless", F_true);

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
              fprintf(data.error.to.stream, "%c", f_string_eol[0]);
              fprintf(data.error.to.stream, "%s%sRule setting has an invalid name '", data.error.context.before->string, data.error.prefix ? data.error.prefix : "");
              fprintf(data.error.to.stream, "%s%s%s%s", data.error.context.after->string, data.error.notable.before->string, setting_value->string, data.error.notable.after->string);
              fprintf(data.error.to.stream, "%s', there must be at least 1 graph character.%s%c", data.error.context.before->string, data.error.context.after->string, f_string_eol[0]);

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
            setting_values->array[setting_values->used].used = 0;

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

          status = controller_validate_environment_name(setting_values->array[setting_values->used]);

          if (status == F_false || F_status_set_fine(status) == F_complete_not_utf) {
            if (status == F_false) {
              fprintf(data.error.to.stream, "%c", f_string_eol[0]);
              fprintf(data.error.to.stream, "%s%sRule setting has an invalid environment variable name '", data.error.context.before->string, data.error.prefix ? data.error.prefix : "");
              fprintf(data.error.to.stream, "%s%s%s%s", data.error.context.after->string, data.error.notable.before->string, setting_values->array[setting_values->used].string, data.error.notable.after->string);
              fprintf(data.error.to.stream, "%s'.%s%c", data.error.context.before->string, data.error.context.after->string, f_string_eol[0]);

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
        fprintf(data.error.to.stream, "%c", f_string_eol[0]);
        fprintf(data.error.to.stream, "%s%sRule setting requires exactly two Content.%s%c", data.error.context.before->string, data.error.prefix ? data.error.prefix : "", data.error.context.after->string, f_string_eol[0]);

        controller_rule_error_print(data.error, *cache, F_false);

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

      status = fl_string_dynamics_increase_by(2, setting_values);

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

      setting_values->array[setting_values->used].used = 0;
      setting_values->array[setting_values->used + 1].used = 0;

      status = fl_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[0], &setting_values->array[setting_values->used]);

      if (F_status_is_error(status)) {
        setting_values->array[setting_values->used].used = 0;

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

      status = fl_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[1], &setting_values->array[setting_values->used + 1]);

      if (F_status_is_error(status)) {
        setting_values->array[setting_values->used].used = 0;
        setting_values->array[setting_values->used + 1].used = 0;

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

      // force the path to be canonical (removing all '../' parts).
      status = fll_path_canonical(setting_values->array[setting_values->used].string, &setting_values->array[setting_values->used]);

      if (F_status_is_error(status)) {
        setting_values->array[setting_values->used].used = 0;
        setting_values->array[setting_values->used + 1].used = 0;

        fll_error_print(data.error, F_status_set_fine(status), "fll_path_canonical", F_true);

        if (F_status_set_fine(status) == F_memory_not || F_status_set_fine(status) == F_memory_allocation || F_status_set_fine(status) == F_memory_reallocation) {
          status_return = status;
          break;
        }

        if (F_status_is_error_not(status_return)) {
          status_return = status;
        }

        continue;
      }

      cache->buffer_path.used = 0;

      status = f_file_name_base(setting_values->array[setting_values->used + 1].string, setting_values->array[setting_values->used + 1].used, &cache->buffer_path);

      if (F_status_is_error(status)) {
        setting_values->array[setting_values->used].used = 0;
        setting_values->array[setting_values->used + 1].used = 0;

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
      else {
        if (fl_string_dynamic_compare(setting_values->array[setting_values->used + 1], cache->buffer_path) == F_equal_to_not) {

          if (data.error.verbosity != f_console_verbosity_quiet) {
            status = fl_string_dynamic_terminate_after(&cache->buffer_item);

            if (F_status_is_error(status)) {
              setting_values->array[setting_values->used].used = 0;
              setting_values->array[setting_values->used + 1].used = 0;

              fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_terminate_after", F_true);

              if (F_status_set_fine(status) == F_memory_not || F_status_set_fine(status) == F_memory_allocation || F_status_set_fine(status) == F_memory_reallocation) {
                return status;
              }

              if (F_status_is_error_not(status_return)) {
                status_return = status;
              }

              controller_rule_error_print(data.error, *cache, F_false);
              continue;
            }

            fprintf(data.error.to.stream, "%c", f_string_eol[0]);
            fprintf(data.error.to.stream, "%s%sThe rule item action second parameter '", data.error.context.before->string, data.error.prefix ? data.error.prefix : "");
            fprintf(data.error.to.stream, "%s%s%s%s", data.error.context.after->string, data.error.notable.before->string, setting_values->array[setting_values->used + 1].string, data.error.notable.after->string);
            fprintf(data.error.to.stream, "%s' must be a base path name, such as '", data.error.context.before->string);
            fprintf(data.error.to.stream, "%s%s%s%s", data.error.context.after->string, data.error.notable.before->string, cache->buffer_path.string, data.error.notable.after->string);
            fprintf(data.error.to.stream, "%s'.%s%c", data.error.context.before->string, data.error.context.after->string, f_string_eol[0]);
          }

          setting_values->array[setting_values->used].used = 0;
          setting_values->array[setting_values->used + 1].used = 0;

          continue;
        }
      }

      setting_values->used += 2;
    } // for

    return status_return;
  }
#endif // _di_controller_rule_setting_read_

#ifdef __cplusplus
} // extern "C"
#endif
