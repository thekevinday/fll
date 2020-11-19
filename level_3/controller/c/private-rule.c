#include "controller.h"
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
    f_status_t status = F_none;
    f_string_length_t size = actions->size + amount;

    if (size > f_array_length_t_size) {
      if (actions->size == f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      size = actions->size;
      status = F_array_too_large;
    }

    const f_status_t status_resize = f_memory_resize((void **) & actions->array, sizeof(controller_rule_actions_t), actions->size, size);
    if (F_status_is_error(status_resize)) return status_resize;

    actions->size = size;
    return status;
  }
#endif // _di_controller_rule_actions_increase_by_

#ifndef _di_controller_rule_actions_read_
  f_return_status controller_rule_actions_read(const controller_data_t data, f_string_static_t *buffer, controller_rule_cache_t *cache, controller_rule_item_t *item, controller_rule_actions_t *actions, f_string_range_t *range) {
    f_status_t status = F_none;

    actions->used = 0;

    // "script" types use the entire content and can be directly passed through.
    if (item->type == controller_rule_item_type_script) {
      status = controller_rule_actions_increase_by(1, actions);

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

          status = fl_string_dynamic_partial_append_nulless(*buffer, cache->range_action, &actions->array[0].parameters.array[0]);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_append_nulless", F_true);
          }
        }
      }

      if (F_status_is_error(status)) {
        controller_rule_error_print(data.error, *cache);
      }

      return status;
    }

    if (actions->type == controller_rule_action_type_extended_list) {
      cache->comments.used = 0;
      cache->content.used = 0;
      cache->contents.used = 0;
      cache->delimits.used = 0;
      cache->objects.used = 0;

      status = fl_fss_extended_list_content_read(*buffer, range, &cache->content, &cache->delimits, &cache->comments);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "fl_fss_extended_list_content_read", F_true);
      }
      else if (status == FL_fss_found_content) {
        status = fll_fss_extended_read(*buffer, &cache->content.array[0], &cache->objects, &cache->contents, 0, 0, &cache->delimits, 0);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "fll_fss_extended_read", F_true);
        }
        else {
          f_array_length_t i = 0;
          f_array_length_t j = 0;

          for (; i < cache->objects.used; ++i) {

            status = f_fss_count_lines(*buffer, cache->objects.array[i].start, &actions->array[actions->used].line);

            if (F_status_is_error(status)) {
              fll_error_print(data.error, F_status_set_fine(status), "f_fss_count_lines", F_true);
              break;
            }

            actions->array[actions->used].line += item->line;
            actions->array[actions->used].parameters.used = 0;

            status = fl_string_dynamics_increase(&actions->array[actions->used].parameters);

            if (F_status_is_error(status)) {
              fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamics_increase", F_true);
              break;
            }

            status = controller_rule_action_read(data, *buffer, &cache->objects.array[i], &cache->contents.array[i], &actions->array[actions->used]);

            if (F_status_is_error(status)) {
              fll_error_print(data.error, F_status_set_fine(status), "controller_rule_action_read", F_true);
            }

            actions->used++;
          } // for
        }
      }
      else {
        status = F_data_not;
      }
    }
    else {
      cache->content.used = 0;
      cache->delimits.used = 0;

      status = fl_fss_extended_content_read(*buffer, range, &cache->content, 0, &cache->delimits);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "fll_fss_extended_content_read", F_true);
      }
      else if (status == FL_fss_found_content) {
        status = fl_fss_apply_delimit(cache->delimits, buffer);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "fl_fss_apply_delimit", F_true);
        }
        else {
          status = controller_rule_actions_increase_by(1, actions);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "controller_rule_actions_increase_by", F_true);
          }
          else {
            status = f_fss_count_lines(*buffer, range->start, &actions->array[0].line);

            if (F_status_is_error(status)) {
              fll_error_print(data.error, F_status_set_fine(status), "f_fss_count_lines", F_true);
            }
            else {
              actions->array[0].line += item->line;
              actions->array[0].parameters.used = 0;

              status = controller_rule_action_read(data, *buffer, 0, &cache->content, &actions->array[0]);

              if (F_status_is_error(status)) {
                fll_error_print(data.error, F_status_set_fine(status), "controller_rule_action_read", F_true);
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

    if (F_status_is_error(status)) {
      controller_rule_error_print(data.error, *cache);
    }
    else if (status == F_data_not) {
      if (data.warning.verbosity == f_console_verbosity_debug) {
        fprintf(data.warning.to.stream, "%c", f_string_eol[0]);
        fprintf(data.warning.to.stream, "%s%sAction is empty, nothing to do.%s%c", data.warning.context.before->string, data.warning.prefix ? data.warning.prefix : "", data.warning.context.after->string, f_string_eol[0]);

        controller_rule_error_print(data.warning, *cache);
      }
    }

    return status;
  }
#endif // _di_controller_rule_actions_read_

#ifndef _di_controller_rule_error_print_
  void controller_rule_error_print(const fll_error_print_t output, const controller_rule_cache_t cache) {

    if (output.verbosity != f_console_verbosity_quiet) {
      fprintf(output.to.stream, "%s%sWhile processing ", output.context.before->string, output.prefix ? output.prefix : "");

      if (cache.name_action.used) {
        fprintf(output.to.stream, "action '");
        fprintf(output.to.stream, "%s%s%s%s", output.context.after->string, output.notable.before->string, cache.name_action.string, output.notable.after->string);
        fprintf(output.to.stream, "%s' on line ", output.context.before->string);
        fprintf(output.to.stream, "%s%s%llu%s", output.context.after->string, output.notable.before->string, cache.line_action, output.notable.after->string);
        fprintf(output.to.stream, "%s for ", output.context.before->string);
      }

      if (cache.name_item.used) {
        fprintf(output.to.stream, "item '");
        fprintf(output.to.stream, "%s%s%s%s", output.context.after->string, output.notable.before->string, cache.name_item.string, output.notable.after->string);
        fprintf(output.to.stream, "%s' on line ", output.context.before->string);
        fprintf(output.to.stream, "%s%s%llu%s", output.context.after->string, output.notable.before->string, cache.line_item, output.notable.after->string);
        fprintf(output.to.stream, "%s for ", output.context.before->string);
      }

      fprintf(output.to.stream, "file '");
      fprintf(output.to.stream, "%s%s%s%s", output.context.after->string, output.notable.before->string, cache.name_file.string, output.notable.after->string);
      fprintf(output.to.stream, "%s'.%s%c", output.context.before->string, output.context.after->string, f_string_eol[0]);
    }
  }
#endif // _di_controller_rule_error_print_

#ifndef _di_controller_rule_item_read_
  f_return_status controller_rule_item_read(const controller_data_t data, f_string_static_t *buffer, controller_rule_cache_t *cache, controller_rule_item_t *item) {
    f_status_t status = F_none;

    f_string_range_t range = f_macro_string_range_t_initialize(buffer->used);
    f_fss_quote_t quote = 0;

    controller_rule_actions_t *actions = 0;

    bool multiple = F_false;

    for (range.start = 0; range.start < buffer->used && range.start <= range.stop; cache->delimits.used = 0, cache->comments.used = 0) {

      status = fl_fss_extended_list_object_read(*buffer, &range, &cache->range_action, &cache->delimits);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "fl_fss_extended_list_object_read", F_true);
        break;
      }

      if (range.start >= range.stop || range.start >= buffer->used) {
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
        status = fl_fss_basic_object_read(*buffer, &range, &cache->range_action, &quote, &cache->delimits);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "fl_fss_basic_object_read", F_true);
          break;
        }
      }

      if (status == FL_fss_found_object_content_not || range.start >= range.stop || range.start >= buffer->used) {
        // object ended without any content.
        break;
      }

      if (status == FL_fss_found_object) {
        status = fl_fss_apply_delimit(cache->delimits, buffer);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "fl_fss_apply_delimit", F_true);
          break;
        }

        status = f_fss_count_lines(*buffer, cache->range_action.start, &cache->line_action);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "f_fss_count_lines", F_true);
          break;
        }

        cache->line_action += item->line;
        cache->name_action.used = 0;

        status = fl_string_dynamic_rip_nulless(*buffer, cache->range_action, &cache->name_action);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_rip_nulless", F_true);
          break;
        }

        status = fl_string_dynamic_terminate_after(&cache->name_action);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_terminate_after", F_true);
          break;
        }

        actions = 0;

        if (fl_string_dynamic_compare_string(controller_string_create, cache->name_action, controller_string_create_length) == F_equal_to) {
          actions = &item->create;
          actions->intent = controller_rule_action_intent_create;
        }
        else if (fl_string_dynamic_compare_string(controller_string_group, cache->name_action, controller_string_group_length) == F_equal_to) {
          actions = &item->group;
          actions->intent = controller_rule_action_intent_group;
        }
        else if (fl_string_dynamic_compare_string(controller_string_restart, cache->name_action, controller_string_restart_length) == F_equal_to) {
          actions = &item->restart;
          actions->intent = controller_rule_action_intent_restart;
        }
        else if (fl_string_dynamic_compare_string(controller_string_reload, cache->name_action, controller_string_reload_length) == F_equal_to) {
          actions = &item->reload;
          actions->intent = controller_rule_action_intent_reload;
        }
        else if (fl_string_dynamic_compare_string(controller_string_start, cache->name_action, controller_string_start_length) == F_equal_to) {
          actions = &item->start;
          actions->intent = controller_rule_action_intent_start;
        }
        else if (fl_string_dynamic_compare_string(controller_string_stop, cache->name_action, controller_string_stop_length) == F_equal_to) {
          actions = &item->stop;
          actions->intent = controller_rule_action_intent_stop;
        }
        else if (fl_string_dynamic_compare_string(controller_string_use, cache->name_action, controller_string_use_length) == F_equal_to) {
          actions = &item->use;
          actions->intent = controller_rule_action_intent_use;
        }
        else if (fl_string_dynamic_compare_string(controller_string_user, cache->name_action, controller_string_user_length) == F_equal_to) {
          actions = &item->user;
          actions->intent = controller_rule_action_intent_user;
        }
        else {
          if (data.warning.verbosity == f_console_verbosity_debug) {
            fprintf(data.warning.to.stream, "%c", f_string_eol[0]);
            fprintf(data.warning.to.stream, "%s%sUnknown action type.%s%c", data.warning.context.before->string, data.warning.prefix ? data.warning.prefix : "", data.warning.context.after->string, f_string_eol[0]);

            controller_rule_error_print(data.warning, *cache);
          }

          continue;
        }

        if (multiple) {
          if (actions->intent == controller_rule_action_intent_create || actions->intent == controller_rule_action_intent_group || actions->intent == controller_rule_action_intent_use || actions->intent == controller_rule_action_intent_user) {
            if (data.error.verbosity != f_console_verbosity_quiet) {
              fprintf(data.error.to.stream, "%c", f_string_eol[0]);
              fprintf(data.error.to.stream, "%s%sFSS Extended List is not allowed for this item action type.%s%c", data.error.context.before->string, data.error.prefix ? data.error.prefix : "", data.error.context.after->string, f_string_eol[0]);
            }

            status = F_status_set_error(F_unsupported);
            break;
          }

          actions->type = controller_rule_action_type_extended_list;
        }
        else {
          actions->type = controller_rule_action_type_extended;
        }

        status = controller_rule_actions_read(data, buffer, cache, item, actions, &range);
        if (F_status_is_error(status)) break;
      }
    } // for

    if (F_status_is_error(status)) {
      controller_rule_error_print(data.error, *cache);
    }

    return status;
  }
#endif // _di_controller_rule_item_read_

#ifndef _di_controller_rule_items_increase_by_
  f_return_status controller_rule_items_increase_by(const f_array_length_t amount, controller_rule_items_t *items) {
    f_status_t status = F_none;
    f_string_length_t size = items->size + amount;

    if (size > f_array_length_t_size) {
      if (items->size == f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      size = items->size;
      status = F_array_too_large;
    }

    const f_status_t status_resize = f_memory_resize((void **) & items->array, sizeof(controller_rule_items_t), items->size, size);
    if (F_status_is_error(status_resize)) return status_resize;

    items->size = size;
    return status;
  }
#endif // _di_controller_rule_items_increase_by_

#ifndef _di_controller_rule_read_
  f_return_status controller_rule_read(const controller_data_t data, controller_rule_cache_t *cache, controller_rule_items_t *items) {
    f_status_t status = F_none;
    f_string_dynamic_t buffer = f_string_dynamic_t_initialize;

    items->used = 0;

    {
      f_file_t file = f_file_t_initialize;

      status = f_file_stream_open(cache->name_file.string, 0, &file);

      if (F_status_is_error(status)) {
        fll_error_file_print(data.error, F_status_set_fine(status), "f_file_stream_open", F_true, cache->name_file.string, "open", fll_error_file_type_file);
      }
      else {
        status = f_file_stream_read(file, 1, &buffer);

        if (F_status_is_error(status)) {
          fll_error_file_print(data.error, F_status_set_fine(status), "f_file_stream_read", F_true, cache->name_file.string, "read", fll_error_file_type_file);
        }
      }

      f_file_stream_close(F_true, &file);

      if (F_status_is_error(status)) {
        f_macro_string_dynamic_t_delete_simple(buffer);
        return F_false;
      }
    }

    // @todo add these to the cache without conflicting with the actions use of objects and contents.
    f_fss_objects_t objects = f_fss_objects_t_initialize;
    f_fss_contents_t contents = f_fss_contents_t_initialize;

    if (buffer.used) {
      f_string_range_t range = f_macro_string_range_t_initialize(buffer.used);

      cache->delimits.used = 0;
      cache->comments.used = 0;

      status = fll_fss_basic_list_read(buffer, &range, &objects, &contents, &cache->delimits, 0, &cache->comments);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "fll_fss_basic_list_read", F_true);
      }
      else {
        status = fl_fss_apply_delimit(cache->delimits, &buffer);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "fl_fss_apply_delimit", F_true);
        }
      }
    }

    if (F_status_is_error_not(status) && objects.used) {
      status = controller_rule_items_increase_by(objects.used, items);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "controller_rule_items_increase_by", F_true);
      }
      else {
        f_string_dynamic_t content = f_string_dynamic_t_initialize;

        for (f_array_length_t i = 0; i < objects.used; ++i) {

          cache->line_item = 0;
          cache->line_action = 0;

          cache->range_item = objects.array[i];
          cache->range_action.start = 1;
          cache->range_action.stop = 0;

          cache->comments.used = 0;
          cache->content.used = 0;
          cache->contents.used = 0;
          cache->delimits.used = 0;
          cache->objects.used = 0;

          cache->name_file.used = 0;
          cache->name_item.used = 0;
          cache->name_action.used = 0;

          status = f_fss_count_lines(buffer, cache->range_item.start, &cache->line_item);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "f_fss_count_lines", F_true);
            break;
          }

          items->array[items->used].line = cache->line_item;

          status = fl_string_dynamic_rip_nulless(buffer, cache->range_item, &cache->name_item);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_rip_nulless", F_true);
            break;
          }

          status = fl_string_dynamic_terminate_after(&cache->name_item);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_terminate_after", F_true);
            break;
          }

          content.used = 0;
          status = fl_string_dynamic_partial_append(buffer, contents.array[i].array[0], &content);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_partial_append", F_true);
            break;
          }

          if (fl_string_dynamic_compare_string(controller_string_settings, cache->name_item, controller_string_settings_length) == F_equal_to) {
            items->array[items->used].type = 0;
          }
          else if (fl_string_dynamic_compare_string(controller_string_command, cache->name_item, controller_string_command_length) == F_equal_to) {
            items->array[items->used].type = controller_rule_item_type_command;
          }
          else if (fl_string_dynamic_compare_string(controller_string_script, cache->name_item, controller_string_script_length) == F_equal_to) {
            items->array[items->used].type = controller_rule_item_type_script;
          }
          else if (fl_string_dynamic_compare_string(controller_string_service, cache->name_item, controller_string_service_length) == F_equal_to) {
            items->array[items->used].type = controller_rule_item_type_service;
          }
          else {
            if (data.warning.verbosity == f_console_verbosity_debug) {
              fprintf(data.warning.to.stream, "%c", f_string_eol[0]);
              fprintf(data.warning.to.stream, "%s%sUnknown item type.%s%c", data.warning.context.before->string, data.warning.prefix ? data.warning.prefix : "", data.warning.context.after->string, f_string_eol[0]);

              controller_rule_error_print(data.warning, *cache);
            }

            continue;
          }

          if (items->array[items->used].type) {
            status = controller_rule_item_read(data, &content, cache, &items->array[items->used]);
            if (F_status_is_error(status)) break;

            items->used++;
          }
          else {
            // @todo handle rule settings population.
          }
        } // for

        f_macro_string_dynamic_t_delete_simple(content);
      }
    }

    f_macro_fss_objects_t_delete_simple(objects);
    f_macro_fss_contents_t_delete_simple(contents);
    f_macro_string_dynamic_t_delete_simple(buffer);

    if (F_status_is_error(status)) {
      controller_rule_error_print(data.error, *cache);
    }

    return status;
  }
#endif // _di_controller_rule_read_

#ifdef __cplusplus
} // extern "C"
#endif
