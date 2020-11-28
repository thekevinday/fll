#include "controller.h"
#include "private-entry.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_entry_actions_increase_by_
  f_return_status controller_entry_actions_increase_by(const f_array_length_t amount, controller_entry_actions_t *actions) {
    f_status_t status = F_none;
    f_string_length_t size = actions->size + amount;

    if (size > f_array_length_t_size) {
      if (actions->size == f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      size = actions->size;
      status = F_array_too_large;
    }

    const f_status_t status_resize = f_memory_resize((void **) & actions->array, sizeof(controller_entry_action_t), actions->size, size);
    if (F_status_is_error(status_resize)) return status_resize;

    actions->size = size;
    return status;
  }
#endif // _di_controller_entry_actions_increase_by_

#ifndef _di_controller_entry_actions_read_
  f_return_status controller_entry_actions_read(const controller_data_t data, const controller_setting_t setting, const f_string_range_t content_range, controller_entry_cache_t *cache, controller_entry_actions_t *actions) {
    f_status_t status = F_none;
    f_status_t status_action = F_none;

    actions->used = 0;
    cache->object_actions.used = 0;
    cache->content_actions.used = 0;

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
      action->line = cache->line_action;
      action->timeout = 0;
      action->status = F_unknown;
      action->parameters.used = 0;

      status = f_fss_count_lines(cache->buffer_file, cache->object_actions.array[i].start, &cache->line_action);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "f_fss_count_lines", F_true);
        break;
      }

      status = fl_string_dynamic_rip_nulless(cache->buffer_item, cache->object_actions.array[i], &cache->name_action);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_rip_nulless", F_true);
        break;
      }

      status = fl_string_dynamic_terminate_after(&cache->name_action);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_terminate_after", F_true);
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
          fprintf(data.warning.to.stream, "%c", f_string_eol[0]);
          fprintf(data.warning.to.stream, "%s%sUnknown entry item type.%s%c", data.warning.context.before->string, data.warning.prefix ? data.warning.prefix : "", data.warning.context.after->string, f_string_eol[0]);

          controller_entry_error_print(data.warning, *cache);
        }

        continue;
      }

      if (action->type == controller_entry_action_type_consider || action->type == controller_entry_action_type_rule) {
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
      else {
        // for: controller_entry_action_type_ready.
        allocate = 0;
        at_least = 0;
        at_most = 0;
      }

      if (cache->content_actions.array[i].used < at_least || cache->content_actions.array[i].used > at_most) {
        action->status = F_status_set_error(F_parameter);

        if (data.error.verbosity != f_console_verbosity_quiet) {
          fprintf(data.error.to.stream, "%c", f_string_eol[0]);
          fprintf(data.error.to.stream, "%s%sThe entry item action '", data.error.context.before->string, data.error.prefix ? data.error.prefix : "");
          fprintf(data.error.to.stream, "%s%s%s%s", data.error.context.after->string, data.error.notable.before->string, cache->name_action.string, data.error.notable.after->string);
          fprintf(data.error.to.stream, "%s' requires ", data.error.context.before->string);

          if (action->type == controller_entry_action_type_failsafe || action->type == controller_entry_action_type_item) {
            fprintf(data.error.to.stream, "%s%s%llu%s", data.error.context.after->string, data.error.notable.before->string, cache->line_action, data.error.notable.after->string);
            fprintf(data.error.to.stream, "%s or more parameters.%s%c", data.error.context.before->string, data.error.context.after->string, f_string_eol[0]);
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
            fprintf(data.error.to.stream, "%s parameters.%s%c", data.error.context.before->string, data.error.context.after->string, f_string_eol[0]);
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

            if (F_status_is_error_not(status_action)) {
              status_action = status;
            }

            break;
          }

          action->parameters.used++;
        } // for

        if (F_status_is_error(status)) break;

        // @todo validate if "timeout" paramter #1 is one of start, stop, or kill and parameter #2 is valid number.
        // @todo validate if "consider" or "rule" parameters are valid (valid file path), (valid file basename), (then one of asynchronous, require, and/or wait).
        // @todo: after entries are processed, check to see if "item" or "failsafe" reference existent items.
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
  void controller_entry_error_print(const fll_error_print_t output, const controller_entry_cache_t cache) {

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
        fprintf(output.to.stream, "entry item '");
        fprintf(output.to.stream, "%s%s%s%s", output.context.after->string, output.notable.before->string, cache.name_item.string, output.notable.after->string);
        fprintf(output.to.stream, "%s' on line ", output.context.before->string);
        fprintf(output.to.stream, "%s%s%llu%s", output.context.after->string, output.notable.before->string, cache.line_list, output.notable.after->string);
        fprintf(output.to.stream, "%s for ", output.context.before->string);
      }

      fprintf(output.to.stream, "file '");
      fprintf(output.to.stream, "%s%s%s%s", output.context.after->string, output.notable.before->string, cache.name_file.string, output.notable.after->string);
      fprintf(output.to.stream, "%s'.%s%c", output.context.before->string, output.context.after->string, f_string_eol[0]);
    }
  }
#endif // _di_controller_entry_error_print_

#ifndef _di_controller_entry_items_increase_by_
  f_return_status controller_entry_items_increase_by(const f_array_length_t amount, controller_entry_items_t *items) {
    f_status_t status = F_none;
    f_string_length_t size = items->size + amount;

    if (size > f_array_length_t_size) {
      if (items->size == f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      size = items->size;
      status = F_array_too_large;
    }

    const f_status_t status_resize = f_memory_resize((void **) & items->array, sizeof(controller_entry_items_t), items->size, size);
    if (F_status_is_error(status_resize)) return status_resize;

    items->size = size;
    return status;
  }
#endif // _di_controller_entry_items_increase_by_

#ifndef _di_controller_entry_read_
  f_return_status controller_entry_read(const controller_data_t data, const controller_setting_t setting, const f_string_static_t entry_name, controller_entry_cache_t *cache, controller_entry_t *entry) {
    f_status_t status = F_none;

    entry->status = F_unknown;
    entry->items.used = 0;

    cache->line_action = 0;
    cache->line_list = 0;

    cache->range_list.start = 1;
    cache->range_list.stop = 0;

    cache->comments.used = 0;
    cache->delimits.used = 0;

    cache->content_action.used = 0;
    cache->content_actions.used = 0;
    cache->content_items.used = 0;

    cache->object_actions.used = 0;
    cache->object_items.used = 0;

    cache->buffer_file.used = 0;
    cache->buffer_item.used = 0;

    cache->name_file.used = 0;
    cache->name_action.used = 0;
    cache->name_item.used = 0;

    status = controller_file_load(data, setting, controller_string_rules, entry_name, controller_string_rule, controller_string_rules_length, controller_string_rule_length, &cache->buffer_file, &cache->name_file);

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
          fprintf(data.error.to.stream, "%c", f_string_eol[0]);
          fprintf(data.error.to.stream, "%s%sThe entry file is empty.%s%c", data.error.context.before->string, data.error.prefix ? data.error.prefix : "", data.error.context.after->string, f_string_eol[0]);
        }

        status = F_status_set_error(F_data_not);
      }
    }

    if (F_status_is_error_not(status) && cache->object_actions.used) {
      status = controller_entry_items_increase_by(cache->object_items.used, &entry->items);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "controller_entry_items_increase_by", F_true);
      }
      else {
        // 0x1 = main found, 0x2 = found existing.
        uint8_t code = 0;

        controller_entry_item_t *item = 0;
        f_string_range_t *range = 0;
        f_string_length_t j = 0;

        for (f_array_length_t i = 0; i < cache->object_items.used; ++i) {

          if (code & 0x2) {
            code -= 0x2;
          }

          range = 0;

          cache->line_action = 0;
          cache->line_list = 0;

          cache->range_list = cache->object_items.array[i];

          cache->comments.used = 0;
          cache->delimits.used = 0;

          cache->content_action.used = 0;
          cache->content_actions.used = 0;

          cache->object_actions.used = 0;

          cache->buffer_file.used = 0;
          cache->buffer_item.used = 0;

          cache->name_action.used = 0;
          cache->name_item.used = 0;

          status = controller_entry_items_increase_by(controller_default_allocation_step, &entry->items);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "controller_entry_items_increase_by", F_true);
            break;
          }

          status = fl_string_dynamic_partial_append_nulless(cache->buffer_file, cache->object_items.array[i], &cache->name_item);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_partial_append_nulless", F_true);
            break;
          }

          status = fl_string_dynamic_terminate(&cache->name_item);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_terminate", F_true);
            break;
          }

          status = f_fss_count_lines(cache->buffer_file, cache->object_items.array[i].start, &cache->line_list);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "f_fss_count_lines", F_true);
            break;
          }

          for (j = code & 0x1 ? 1 : 0; j < entry->items.used; ++j) {

            if (fl_string_dynamic_compare(entry->items.array[j].name, cache->name_item) == F_equal_to) {
              if (data.warning.verbosity != f_console_verbosity_quiet) {
                fprintf(data.warning.to.stream, "%c", f_string_eol[0]);
                fprintf(data.warning.to.stream, "%s%sIgnoring duplicate entry item '", data.warning.context.before->string, data.warning.prefix ? data.warning.prefix : "");
                fprintf(data.warning.to.stream, "%s%s%s%s", data.warning.context.after->string, data.warning.notable.before->string, cache->name_file.string, data.warning.notable.after->string);
                fprintf(data.warning.to.stream, "%s'.%s%c", data.warning.context.before->string, data.warning.context.after->string, f_string_eol[0]);

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

            item = &entry->items.array[0];

            if (!entry->items.used) {
              entry->items.used = 1;
            }
          }
          else if (entry->items.used) {
            item = &entry->items.array[entry->items.used++];
          }
          else {

            // skip position 0, which is reserved for "main".
            item = &entry->items.array[1];

            entry->items.used = 2;
          }

          item->line = cache->line_list;

          status = fl_string_dynamic_append(cache->name_item, &item->name);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_append", F_true);
            break;
          }

          status = fl_string_dynamic_terminate(&item->name);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_terminate", F_true);
            break;
          }

          status = controller_entry_actions_read(data, setting, *range, cache, &item->actions);

          if (F_status_is_error(status)) {
            controller_entry_error_print(data.error, *cache);

            if (F_status_set_fine(status) == F_memory_not || F_status_set_fine(status) == F_memory_allocation || F_status_set_fine(status) == F_memory_reallocation) {
              break;
            }
          }
        } // for

        if (F_status_is_error_not(status) && code & 0x1) {
          if (data.error.verbosity != f_console_verbosity_quiet) {
            fprintf(data.error.to.stream, "%c", f_string_eol[0]);
            fprintf(data.error.to.stream, "The required list '");
            fprintf(data.error.to.stream, "%s%s%s%s", data.error.context.after->string, data.error.notable.before->string, controller_string_main, data.error.notable.after->string);
            fprintf(data.error.to.stream, "%s' was not found.%s%c", data.error.context.before->string, data.error.context.after->string, f_string_eol[0]);
          }

          status = F_status_set_error(F_found_not);
        }
      }
    }

    if (F_status_is_error(status)) {
      status = F_status_set_fine(status);

      controller_entry_error_print(data.error, *cache);

      if (status == F_memory_not || status == F_memory_allocation || status == F_memory_reallocation) {
        entry->status = F_memory;
      }
      else if (status == F_file_open_max || status == F_space_not || status == F_busy) {
        entry->status = F_resource;
      }
      else if (status == F_access_denied || status == F_filesystem_quota_block || status == F_prohibited || status == F_input_output) {
        entry->status = F_access;
      }
      else if (status == F_interrupted) {
        entry->status = F_interrupted;
      }
      else {
        entry->status = F_invalid;
      }

      return F_false;
    }

    entry->status = F_none;
    return F_true;
  }
#endif // _di_controller_entry_read_

#ifdef __cplusplus
} // extern "C"
#endif
