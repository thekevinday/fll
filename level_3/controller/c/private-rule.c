#include "controller.h"
#include "private-rule.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_rule_actions_read_
  f_return_status controller_rule_actions_read(const controller_data_t data, const bool multiple, f_string_static_t *buffer, controller_rule_cache_t *cache, controller_rule_item_t *item, controller_rule_actions_t *actions) {
    f_status_t status = F_none;

    f_fss_objects_t objects = f_fss_objects_t_initialize;
    f_fss_contents_t contents = f_fss_contents_t_initialize;

    f_string_range_t range = cache->range_action;

    if (multiple) {
      // @todo
      //fll_fss_extended_list_read();
    }
    else {
      status = f_fss_seek_to_eol(*buffer, range);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "f_fss_seek_to_eol", F_true);
        controller_rule_error_print(data.error, *cache);
      }

      range.stop = range.start;
      range.start = cache->range_action.start;

      // @fixme I just noticed an inconsistency in the naming, should it be quoted_objects and delimit_objects or instead objects_quoted, and objects_delimit?
      // @fixme also, I think that the buffer in the fll_fss read functions no longer need to be pointers (it should be possible to make them constants now).
      status = fll_fss_extended_read(buffer, &range, &objects, &contents, &quoted_objects, &quoted_contents, &delimit_objects, &delimit_contents);
      // @todo
    }

    if (!content.used) {
      if (data.warning.verbosity == f_console_verbosity_debug) {
        fprintf(data.warning.to.stream, "%c", f_string_eol[0]);

        if (actions) {
          fprintf(data.warning.to.stream, "%s%sUnknown action, nothing to do.%s%c", data.warning.context.before->string, data.warning.prefix ? data.warning.prefix : "", data.warning.context.after->string, f_string_eol[0]);
        }
        else {
          fprintf(data.warning.to.stream, "%s%sAction is empty, nothing to do.%s%c", data.warning.context.before->string, data.warning.prefix ? data.warning.prefix : "", data.warning.context.after->string, f_string_eol[0]);
        }

        controller_rule_error_print(data.error, *cache);
      }

      return F_data_not;
    }

    action->type = type;
    action->line = line;
    action->content.used = 0;

    // @todo now that the type and intent are known, the content may be loaded.
    // @todo a "script" type uses basic and a "service" type uses extended because the script is passed to bash whereas the service is directly called.
    // @todo additional line-by-line processing needs to be performed for multi-line services OR services should not support multiple lines.
        /*
        comments.used = 0;
        status = fl_fss_extended_list_content_read(content, &range, &child_content, &delimits, &comments);

        if (F_status_is_error(status)) {
          fll_error_file_print(data->error, F_status_set_fine(status), "fl_fss_extended_list_content_read", F_true, file_name.string, "process", fll_error_file_type_file);
          controller_rule_error_print(data.error, *cache);
          break;
        }

        if (status == FL_fss_found_content) {
          type = controller_rule_item_type_multiple;
        }
        */
          /*
          status = fl_fss_basic_content_read(content, &range, &child_content, &delimits);

          if (F_status_is_error(status)) {
            fll_error_file_print(data->error, F_status_set_fine(status), "fl_fss_basic_content_read", F_true, file_name.string, "process", fll_error_file_type_file);
            controller_rule_error_print(data.error, *cache);
            break;
          }

          if (status == FL_fss_found_content) {
            type = controller_rule_action_type_basic;
          }*/

    return status;
  }
#endif // _di_controller_rule_actions_read_

#ifndef _di_controller_rule_error_print_
  void controller_rule_error_print(const fll_error_print_t output, const controller_rule_cache_t cache) {

    if (output.verbosity != f_console_verbosity_quiet) {
      fprintf(output.to.stream, "%s%sWhile processing ", output.context.before->string, output.prefix ? output.prefix : "");

      if (cache.name_action) {
        fprintf(output.to.stream, "action '");
        fprintf(output.to.stream, "%s%s%s%s", output.context.after->string, output.notable.before->string, cache.name_action.string, output.notable.after->string);
        fprintf(output.to.stream, "%s' on line ", output.context.before->string);
        fprintf(output.to.stream, "%s%s%llu%s", output.context.after->string, output.notable.before->string, cache.line_action, output.notable.after->string);
        fprintf(output.to.stream, "%s for ", output.context.before->string);
      }

      if (cache.name_item) {
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

    f_fss_delimits_t delimits = f_fss_delimits_t_initialize;
    f_fss_comments_t comments = f_fss_comments_t_initialize;
    f_fss_quote_t quote = f_fss_quote_t_initialize;

    controller_rule_actions_t *actions = 0;

    bool multiple = f_false;

    for (range.start = 0; range.start < buffer->used && range.start <= range.stop; delimits.used = 0, comments.used = 0) {

      status = fl_fss_extended_list_object_read(buffer, &range, &cache->range_action, &delimits);

      if (F_status_is_error(status)) {
        fll_error_print(data->error, F_status_set_fine(status), "fl_fss_extended_list_object_read", F_true);
        break;
      }

      if (range.start >= range.stop || range.start >= buffer->used) {
        if (status == FL_fss_found_object || status == FL_fss_found_object_content_not) {
          if (error.verbosity != f_console_verbosity_quiet) {
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
        multiple = f_false;

        // The current line is not an Extended List object, so the next possibility is a Basic List (and Extended List, both use the same Object structure).
        status = fl_fss_basic_object_read(buffer, &range, &cache->range_action, &quote, &delimits);

        if (F_status_is_error(status)) {
          fll_error_print(data->error, F_status_set_fine(status), "fl_fss_basic_object_read", F_true);
          break;
        }
      }

      if (status == FL_fss_found_object_content_not || range.start >= range.stop || range.start >= buffer->used) {
        // object ended without any content.
        break;
      }

      if (status == FL_fss_found_object) {
        status = fl_fss_apply_delimit(delimits, &data_make->buffer);

        if (F_status_is_error(status)) {
          fll_error_print(data->error, F_status_set_fine(status), "fl_fss_apply_delimit", F_true);
          break;
        }

        status = f_fss_count_lines(buffer, cache->range_action.start, &cache->line_action);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "f_fss_count_lines", F_true);
          break;
        }

        cache->line_action += item->line;

        action_name->used = 0;
        status = fl_string_dynamic_rip_nulless(buffer, cache->range_action, action_name);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_rip_nulless", F_true);
          break;
        }

        status = fl_string_dynamic_terminate_after(action_name);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_terminate_after", F_true);
          break;
        }

        actions = 0;

        if (fl_string_dynamic_compare_string(controller_string_create, *action_name, controller_string_create_length) == f_equal_to) {
          actions = &item->create;
          actions->intent = controller_rule_action_intent_create;
        }
        else if (fl_string_dynamic_compare_string(controller_string_group, *action_name, controller_string_group_length) == f_equal_to) {
          actions = &item->group;
          actions->intent = controller_rule_action_intent_group;
        }
        else if (fl_string_dynamic_compare_string(controller_string_restart, *action_name, controller_string_restart_length) == f_equal_to) {
          actions = &item->restart;
          actions->intent = controller_rule_action_intent_restart;
        }
        else if (fl_string_dynamic_compare_string(controller_string_reload, *action_name, controller_string_reload_length) == f_equal_to) {
          actions = &item->reload;
          actions->intent = controller_rule_action_intent_reload;
        }
        else if (fl_string_dynamic_compare_string(controller_string_start, *action_name, controller_string_start_length) == f_equal_to) {
          actions = &item->start;
          actions->intent = controller_rule_action_intent_start;
        }
        else if (fl_string_dynamic_compare_string(controller_string_stop, *action_name, controller_string_stop_length) == f_equal_to) {
          actions = &item->stop;
          actions->intent = controller_rule_action_intent_stop;
        }
        else if (fl_string_dynamic_compare_string(controller_string_use, *action_name, controller_string_use_length) == f_equal_to) {
          actions = &item->use;
          actions->intent = controller_rule_action_intent_use;
        }
        else if (fl_string_dynamic_compare_string(controller_string_user, *action_name, controller_string_user_length) == f_equal_to) {
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
            if (error.verbosity != f_console_verbosity_quiet) {
              fprintf(data.error.to.stream, "%c", f_string_eol[0]);
              fprintf(data.error.to.stream, "%s%sFSS Extended List is not allowed for this item action type.%s%c", data.error.context.before->string, data.error.prefix ? data.error.prefix : "", data.error.context.after->string, f_string_eol[0]);
            }

            status = F_status_set_error(F_unsupported);
            break;
          }
        }

        status = controller_rule_actions_read(data, multiple, buffer, cache, item, actions);
        if (F_status_is_error(status)) break;
      }
    } // for

    f_macro_fss_delimits_t_delete_simple(delimits);
    f_macro_fss_comments_t_delete_simple(comments);

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

    const f_status_t status_resize = f_memory_resize((void **) & items.array, sizeof(controller_rule_items_t), items.size, size);
    if (F_status_is_error(status_resize)) return status_resize;

    items.size = size;
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

      status = f_file_stream_open(arguments.argv[data->remaining.array[i]], 0, &file);

      if (F_status_is_error(status)) {
        fll_error_file_print(data->error, F_status_set_fine(status), "f_file_stream_open", F_true, cache->name_file.string, "open", fll_error_file_type_file);
      }
      else {
        status = f_file_stream_read(file, 1, &buffer);

        if (F_status_is_error(status)) {
          fll_error_file_print(data->error, F_status_set_fine(status), "f_file_stream_read", F_true, cache->name_file.string, "read", fll_error_file_type_file);
        }
      }

      f_file_stream_close(F_true, &file);

      if (F_status_is_error(status)) {
        f_macro_string_dynamic_t_delete_simple(buffer);
        return F_false;
      }
    }

    f_fss_objects_t objects = f_fss_objects_t_initialize;
    f_fss_contents_t contents = f_fss_contents_t_initialize;

    if (buffer.used) {
      f_string_range_t range = f_macro_string_range_t_initialize(buffer.used);
      f_fss_delimits_t delimits = f_fss_delimits_t_initialize;
      f_fss_comments_t comments = f_fss_comments_t_initialize;

      status = fll_fss_basic_list_read(&data_make->buffer, &range, &objects, &contents, &delimits, 0, &comments);

      if (F_status_is_error(status)) {
        fake_print_error_fss(data, status, "fll_fss_basic_list_read", data.file_data_build_fakefile.string, range, F_true);
      }
      else {
        status = fl_fss_apply_delimit(delimits, &data_make->buffer);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "fl_fss_apply_delimit", F_true);
        }
      }

      f_macro_fss_delimits_t_delete_simple(delimits);
      f_macro_fss_comments_t_delete_simple(comments);
    }

    if (F_status_is_error_not(status) && objects.used) {
      status = controller_rule_items_increase_by(objects.used, items);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "controller_rule_items_increase_by", F_true);
      }
      else {
        f_string_dynamic_t content = f_string_dynamic_t_initialize;

        for (f_array_length_t i = 0; i < objects.used; ++i) {

          cache->name_file.used = 0;
          cache->name_item.used = 0;
          cache->name_action.used = 0;

          cache->line_item = 0;
          cache->line_action = 0;

          cache->range_item = objects.array[i];
          cache->range_action = 0;

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

          if (fl_string_dynamic_compare_string(controller_string_settings, cache->name_item, controller_string_settings_length) == f_equal_to) {
            items->array[items->used].type = 0;
          }
          else if (fl_string_dynamic_compare_string(controller_string_command, cache->name_item, controller_string_command_length) == f_equal_to) {
            items->array[items->used].type = controller_rule_item_type_command;
          }
          else if (fl_string_dynamic_compare_string(controller_string_script, cache->name_item, controller_string_script_length) == f_equal_to) {
            items->array[items->used].type = controller_rule_item_type_script;
          }
          else if (fl_string_dynamic_compare_string(controller_string_service, cache->name_item, controller_string_service_length) == f_equal_to) {
            items->array[items->used].type = controller_rule_item_type_service;
          }
          else {
            if (warning.verbosity == f_console_verbosity_debug) {
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

    return status;
  }
#endif // _di_controller_rule_read_

#ifdef __cplusplus
} // extern "C"
#endif
