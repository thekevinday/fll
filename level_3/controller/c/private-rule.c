#include "controller.h"
#include "private-common.h"
#include "private-controller.h"
#include "private-rule.h"
#include "private-entry.h"
#include "private-thread.h"

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
  f_status_t controller_rule_parameters_read(const controller_main_t main, const f_string_static_t buffer, f_fss_object_t *object, f_fss_content_t *content, f_string_dynamics_t *parameters) {

    f_status_t status = F_none;

    parameters->used = 0;

    if (object && object->start <= object->start) {

      status = f_string_dynamics_increase(parameters);

      if (F_status_is_error(status)) {
        controller_error_print(main.data->error, F_status_set_fine(status), "f_string_dynamics_increase", F_true, main.thread);

        return status;
      }

      parameters->array[parameters->used].used = 0;

      status = f_string_dynamic_partial_append_nulless(buffer, *object, &parameters->array[0]);

      if (F_status_is_error(status)) {
        controller_error_print(main.data->error, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, main.thread);

        return status;
      }

      status = f_string_dynamic_terminate_after(&parameters->array[0]);

      if (F_status_is_error(status)) {
        controller_error_print(main.data->error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true, main.thread);

        return status;
      }

      parameters->used++;
    }

    if (content && content->used) {

      for (f_array_length_t i = 0; i < content->used; ++i) {

        if (content->array[i].start > content->array[i].start) continue;

        status = f_string_dynamics_increase(parameters);

        if (F_status_is_error(status)) {
          controller_error_print(main.data->error, F_status_set_fine(status), "f_string_dynamics_increase", F_true, main.thread);

          return status;
        }

        parameters->array[parameters->used].used = 0;

        status = f_string_dynamic_partial_append_nulless(buffer, content->array[i], &parameters->array[parameters->used]);

        if (F_status_is_error(status)) {
          controller_error_print(main.data->error, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, main.thread);

          return status;
        }

        status = f_string_dynamic_terminate_after(&parameters->array[parameters->used]);

        if (F_status_is_error(status)) {
          controller_error_print(main.data->error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true, main.thread);

          return status;
        }

        ++parameters->used;
      } // for
    }

    return F_none;
  }
#endif // _di_controller_rule_parameters_read_

#ifndef _di_controller_rule_action_type_name_
  f_string_static_t controller_rule_action_type_name(const uint8_t type) {

    f_string_static_t buffer = f_string_static_t_initialize;

    switch (type) {
      case controller_rule_action_type_group:
        buffer.string = controller_string_group_s;
        buffer.used = controller_string_group_length;
        break;

      case controller_rule_action_type_kill:
        buffer.string = controller_string_kill_s;
        buffer.used = controller_string_kill_length;
        break;

      case controller_rule_action_type_pid_file:
        buffer.string = controller_string_pid_file_s;
        buffer.used = controller_string_pid_file_length;
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

      case controller_rule_action_type_user:
        buffer.string = controller_string_user_s;
        buffer.used = controller_string_user_length;
        break;

      case controller_rule_action_type_with:
        buffer.string = controller_string_with_s;
        buffer.used = controller_string_with_length;
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

      const f_status_t status = f_memory_resize(actions->size, actions->used + amount, sizeof(controller_rule_action_t), (void **) & actions->array);

      if (F_status_is_error_not(status)) {
        actions->size = actions->used + amount;
      }

      return status;
    }

    return F_data_not;
  }
#endif // _di_controller_rule_actions_increase_by_

#ifndef _di_controller_rule_action_read_
  f_status_t controller_rule_action_read(const controller_main_t main, const uint8_t type, const uint8_t method, controller_cache_t *cache, controller_rule_item_t *item, controller_rule_actions_t *actions, f_string_range_t *range) {

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
        controller_error_print(main.data->error, F_status_set_fine(status), "fl_fss_extended_list_content_read", F_true, main.thread);
      }
      else if (status == FL_fss_found_content) {
        status = fl_fss_apply_delimit(cache->delimits, &cache->buffer_item);

        if (F_status_is_error(status)) {
          controller_error_print(main.data->error, F_status_set_fine(status), "fl_fss_apply_delimit", F_true, main.thread);
        }
        else {

          // "script" and "utility" types use the entire content and can be directly passed through.
          if (item->type == controller_rule_item_type_script || item->type == controller_rule_item_type_utility) {
            actions->array[actions->used].parameters.used = 0;

            status = f_string_dynamics_increase(&actions->array[actions->used].parameters);

            if (F_status_is_error(status)) {
              controller_error_print(main.data->error, F_status_set_fine(status), "f_string_dynamics_increase", F_true, main.thread);
            }
            else {

              actions->array[actions->used].type = type;
              actions->array[actions->used].line = cache->action.line_action;
              actions->array[actions->used].parameters.used = 0;
              actions->array[actions->used].status = F_known_not;

              status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_action.array[0], &actions->array[actions->used].parameters.array[0]);

              if (F_status_is_error(status)) {
                controller_error_print(main.data->error, F_status_set_fine(status), "f_string_dynamic_append_nulless", F_true, main.thread);
              }

              status = f_string_dynamic_terminate_after(&actions->array[actions->used].parameters.array[0]);

              if (F_status_is_error(status)) {
                controller_error_print(main.data->error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true, main.thread);
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
            controller_error_print(main.data->error, F_status_set_fine(status), "fll_fss_extended_read", F_true, main.thread);
          }
          else {

            status = fl_fss_apply_delimit(cache->delimits, &cache->buffer_item);

            if (F_status_is_error(status)) {
              controller_error_print(main.data->error, F_status_set_fine(status), "fl_fss_apply_delimit", F_true, main.thread);
            }
            else {

              f_array_length_t i = 0;
              f_array_length_t j = 0;

              for (; i < cache->object_actions.used; ++i) {
                status = controller_rule_actions_increase_by(controller_default_allocation_step, actions);

                if (F_status_is_error(status)) {
                  controller_error_print(main.data->error, F_status_set_fine(status), "controller_rule_actions_increase_by", F_true, main.thread);
                  break;
                }

                status = f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &actions->array[actions->used].line);

                if (F_status_is_error(status)) {
                  controller_error_print(main.data->error, F_status_set_fine(status), "f_fss_count_lines", F_true, main.thread);
                  break;
                }

                actions->array[actions->used].type = type;
                actions->array[actions->used].line += ++item->line;
                actions->array[actions->used].parameters.used = 0;
                actions->array[actions->used].status = F_known_not;

                status = f_string_dynamics_increase(&actions->array[actions->used].parameters);

                if (F_status_is_error(status)) {
                  controller_error_print(main.data->error, F_status_set_fine(status), "f_string_dynamics_increase", F_true, main.thread);

                  actions->array[actions->used].status = controller_status_simplify_error(F_status_set_fine(status));
                  break;
                }

                status = controller_rule_parameters_read(main, cache->buffer_item, &cache->object_actions.array[i], &cache->content_actions.array[i], &actions->array[actions->used].parameters);

                actions->array[actions->used].status = controller_status_simplify_error(F_status_set_fine(status));
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
        controller_error_print(main.data->error, F_status_set_fine(status), "fll_fss_extended_content_read", F_true, main.thread);
      }
      else if (status == FL_fss_found_content) {
        status = fl_fss_apply_delimit(cache->delimits, &cache->buffer_item);

        if (F_status_is_error(status)) {
          controller_error_print(main.data->error, F_status_set_fine(status), "fl_fss_apply_delimit", F_true, main.thread);
        }
        else if (item->type == controller_rule_item_type_script || item->type == controller_rule_item_type_utility) {
          status = f_string_dynamics_increase(&actions->array[actions->used].parameters);

          if (F_status_is_error(status)) {
            controller_error_print(main.data->error, F_status_set_fine(status), "f_string_dynamics_increase", F_true, main.thread);
          }
          else {

            // "script" types use the entire content as a single string piped to the script, so merge all arguments together.
            actions->array[actions->used].type = type;
            actions->array[actions->used].line = cache->action.line_action;
            actions->array[actions->used].parameters.used = 0;
            actions->array[actions->used].status = F_known_not;

            for (f_array_length_t i = 0; i < cache->content_action.used; ++i) {
              status = f_string_dynamic_partial_mash_nulless(f_string_space_s, f_string_space_length, cache->buffer_item, cache->content_action.array[i], &actions->array[actions->used].parameters.array[0]);
              if (F_status_is_error(status)) break;
            } // for

            if (F_status_is_error_not(status)) {
              status = f_string_dynamic_terminate_after(&actions->array[actions->used].parameters.array[0]);

              if (F_status_is_error(status)) {
                controller_error_print(main.data->error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true, main.thread);
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
            controller_error_print(main.data->error, F_status_set_fine(status), "f_fss_count_lines", F_true, main.thread);
          }
          else {

            actions->array[actions->used].type = type;
            actions->array[actions->used].line += ++item->line;
            actions->array[actions->used].parameters.used = 0;
            actions->array[actions->used].status = F_known_not;

            status = controller_rule_parameters_read(main, cache->buffer_item, 0, &cache->content_action, &actions->array[actions->used].parameters);

            if (F_status_is_error(status)) {
              controller_error_print(main.data->error, F_status_set_fine(status), "controller_rule_parameters_read", F_true, main.thread);

              actions->array[actions->used].status = controller_status_simplify_error(F_status_set_fine(status));
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
      if (main.data->warning.verbosity == f_console_verbosity_debug) {
        f_thread_mutex_lock(&main.thread->lock.print);

        fprintf(main.data->warning.to.stream, "%c", f_string_eol_s[0]);
        fprintf(main.data->warning.to.stream, "%s%sAction is empty, nothing to do.%s%c", main.data->warning.context.before->string, main.data->warning.prefix ? main.data->warning.prefix : f_string_empty_s, main.data->warning.context.after->string, f_string_eol_s[0]);

        controller_rule_error_print_cache(main.data->warning, cache->action, F_true);

        controller_print_unlock_flush(main.data->warning.to.stream, &main.thread->lock.print);
      }
    }

    return status;
  }
#endif // _di_controller_rule_action_read_

#ifndef _di_controller_rule_copy_
  f_status_t controller_rule_copy(const controller_rule_t source, controller_rule_t *destination) {

    f_status_t status = F_none;

    // delete the third party structures.
    f_macro_control_group_t_delete_simple(destination->control_group)
    f_capability_delete(&destination->capability);

    destination->status = source.status;

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
    destination->need.used = 0;
    destination->want.used = 0;
    destination->wish.used = 0;

    destination->affinity.used = 0;
    destination->groups.used = 0;
    destination->limits.used = 0;
    destination->scheduler.policy = source.scheduler.policy;
    destination->scheduler.priority = source.scheduler.priority;

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

    if (source.need.used) {
      status = f_string_dynamics_append(source.need, &destination->need);
      if (F_status_is_error(status)) return status;
    }

    if (source.want.used) {
      status = f_string_dynamics_append(source.want, &destination->want);
      if (F_status_is_error(status)) return status;
    }

    if (source.wish.used) {
      status = f_string_dynamics_append(source.wish, &destination->wish);
      if (F_status_is_error(status)) return status;
    }

    if (source.affinity.used) {
      status = f_type_int32s_append(source.affinity, &destination->affinity);
      if (F_status_is_error(status)) return status;
    }

    if (source.capability) {
      status = f_capability_copy(source.capability, &destination->capability);
      if (F_status_is_error(status)) return status;
    }

    status = f_control_group_copy(source.control_group, &destination->control_group);
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
        item_destination->line = item_source->line;

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

#ifndef _di_controller_rule_error_print_
  void controller_rule_error_print(const fll_error_print_t print, const controller_cache_action_t cache, const f_status_t status, const f_string_t function, const bool fallback, const bool item, controller_thread_t *thread) {

    if (print.verbosity != f_console_verbosity_quiet) {
      f_thread_mutex_lock(&thread->lock.print);

      fll_error_print(print, status, function, fallback);
      controller_rule_error_print_cache(print, cache, item);

      controller_print_unlock_flush(print.to.stream, &thread->lock.print);
    }
  }
#endif // _di_controller_rule_error_print_

#ifndef _di_controller_rule_error_print_cache_
  void controller_rule_error_print_cache(const fll_error_print_t output, const controller_cache_action_t cache, const bool item) {

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
        fprintf(output.to.stream, "rule file '");
        fprintf(output.to.stream, "%s%s", output.context.after->string, output.notable.before->string);
        f_print_dynamic(output.to.stream, cache.name_file);
        fprintf(output.to.stream, "%s'.%s%c", output.context.before->string, output.context.after->string, f_string_eol_s[0]);
      }
    }
  }
#endif // _di_controller_rule_error_print_cache_

#ifndef _di_controller_rule_item_error_print_
  void controller_rule_item_error_print(const fll_error_print_t output, const controller_cache_action_t cache, const bool item, controller_thread_t *thread) {

    if (output.verbosity != f_console_verbosity_quiet) {
      f_thread_mutex_lock(&thread->lock.print);

      controller_rule_error_print_cache(output, cache, item);

      controller_print_unlock_flush(output.to.stream, &thread->lock.print);
    }
  }
#endif // _di_controller_rule_item_error_print_

#ifndef _di_controller_rule_item_error_print_execute_
  void controller_rule_item_error_print_execute(const fll_error_print_t print, const bool script_is, const f_string_t name, const int code, const f_status_t status) {

    if (print.verbosity != f_console_verbosity_quiet) {
      fprintf(print.to.stream, "%c", f_string_eol_s[0]);
      fprintf(print.to.stream, "%s%sThe %s '", print.context.before->string, print.prefix ? print.prefix : f_string_empty_s, script_is ? controller_string_script_s : controller_string_program_s);
      fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, name ? name : f_string_empty_s, print.notable.after->string);

      if (status == F_control_group || status == F_limit || status == F_processor || status == F_schedule) {
        fprintf(print.to.stream, "%s' failed due to a failure to setup the '", print.context.before->string);
        fprintf(print.to.stream, "%s%s", print.context.after->string, print.notable.before->string);

        if (status == F_control_group) {
          fprintf(print.to.stream, "%s", controller_string_control_group_s);
        }
        else if (status == F_limit) {
          fprintf(print.to.stream, "%s", controller_string_limit_s);
        }
        else if (status == F_processor) {
          fprintf(print.to.stream, "%s", controller_string_processor_s);
        }
        else if (status == F_schedule) {
          fprintf(print.to.stream, "%s", controller_string_scheduler_s);
        }

        fprintf(print.to.stream, "%s", print.notable.after->string);
        fprintf(print.to.stream, "%s'.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);
      }
      else if (code) {
        fprintf(print.to.stream, "%s' failed with the exit code '", print.context.before->string);
        fprintf(print.to.stream, "%s%s%i%s", print.context.after->string, print.notable.before->string, code, print.notable.after->string);
        fprintf(print.to.stream, "%s'.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);
      }
      else {
        fprintf(print.to.stream, "%s' failed.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);
      }
    }
  }
#endif // _di_controller_rule_item_error_print_execute_

#ifndef _di_controller_rule_item_error_print_execute_not_found_
  void controller_rule_item_error_print_execute_not_found(const fll_error_print_t print, const bool script_is, const f_string_t name) {

    if (print.verbosity != f_console_verbosity_quiet) {
      fprintf(print.to.stream, "%c", f_string_eol_s[0]);
      fprintf(print.to.stream, "%s%sThe %s '", print.context.before->string, print.prefix ? print.prefix : f_string_empty_s, script_is ? controller_string_script_s : controller_string_program_s);
      fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, name ? name : f_string_empty_s, print.notable.after->string);
      fprintf(print.to.stream, "%s' could not be executed because it was not found.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);
    }
  }
#endif // _di_controller_rule_item_error_print_execute_not_found_

#ifndef _di_controller_rule_item_error_print_need_want_wish_
  void controller_rule_item_error_print_need_want_wish(const fll_error_print_t print, const f_string_t need_want_wish, const f_string_t value, const f_string_t why) {

    if (print.verbosity != f_console_verbosity_quiet) {
      fprintf(print.to.stream, "%c", f_string_eol_s[0]);
      fprintf(print.to.stream, "%s%sThe %s rule '", print.context.before->string, print.prefix ? print.prefix : f_string_empty_s, need_want_wish);
      fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, value, print.notable.after->string);
      fprintf(print.to.stream, "%s' %s.%s%c", print.context.before->string, why, print.context.after->string, f_string_eol_s[0]);
    }
  }
#endif // _di_controller_rule_item_error_print_need_want_wish_

#ifndef _di_controller_rule_item_error_print_rule_not_loaded_
  void controller_rule_item_error_print_rule_not_loaded(const fll_error_print_t print, const f_string_t alias) {

    if (print.verbosity != f_console_verbosity_quiet) {
      fprintf(print.to.stream, "%c", f_string_eol_s[0]);
      fprintf(print.to.stream, "%s%sThe rule '", print.context.before->string, print.prefix ? print.prefix : f_string_empty_s);
      fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, alias, print.notable.after->string);
      fprintf(print.to.stream, "%s' is no longer loaded.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);
    }
  }
#endif // _di_controller_rule_item_error_print_rule_not_loaded_

#ifndef _di_controller_rule_action_error_missing_pid_
  void controller_rule_action_error_missing_pid(const fll_error_print_t print, const f_string_t alias) {

    if (print.verbosity != f_console_verbosity_quiet) {
      fprintf(print.to.stream, "%c", f_string_eol_s[0]);
      fprintf(print.to.stream, "%s%sThe rule '", print.context.before->string, print.prefix ? print.prefix : f_string_empty_s);
      fprintf(print.to.stream, "%s%s%s%s", print.context.after->string, print.notable.before->string, alias, print.notable.after->string);
      fprintf(print.to.stream, "%s' is not designating a pid file.%s%c", print.context.before->string, print.context.after->string, f_string_eol_s[0]);
    }
  }
#endif // _di_controller_rule_action_error_missing_pid_

#ifndef _di_controller_rule_execute_
  f_status_t controller_rule_execute(const uint8_t action, const uint8_t options, const controller_main_t main, controller_process_t *process) {

    f_status_t status = F_none;
    f_status_t success = F_false;

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    f_array_length_t k = 0;

    f_string_dynamic_t *pid_file = 0;

    uint8_t with = 0;

    // child processes should receive all signals and handle the signals as they see fit.
    f_signal_how_t signals = f_signal_how_t_initialize;
    f_signal_set_empty(&signals.block);
    f_signal_set_fill(&signals.block_not);

    f_string_maps_t environment = f_string_maps_t_initialize;

    const f_string_dynamics_t arguments_none = f_string_dynamics_t_initialize;

    controller_execute_set_t execute_set = controller_macro_execute_set_t_initialize(0, 0, &environment, &signals, 0, fl_execute_as_t_initialize);

    if (process->rule.affinity.used) {
      execute_set.as.affinity = &process->rule.affinity;
    }

    if (process->rule.capability) {
      execute_set.as.capability = process->rule.capability;
    }

    if (process->rule.has & controller_rule_has_control_group) {
      execute_set.as.control_group = &process->rule.control_group;

      // make sure all required cgroup directories exist.
      if (process->rule.status == F_known_not) {
        status = fll_control_group_prepare(process->rule.control_group);

        if (F_status_is_error(status)) {
          controller_error_file_print(main.data->error, F_status_set_fine(status), "fll_control_group_prepare", F_true, process->rule.control_group.path.string, "prepare control groups for", fll_error_file_type_directory, main.thread);

          return status;
        }
      }
    }

    if (process->rule.has & controller_rule_has_group) {
      execute_set.as.id_group = &process->rule.group;

      if (process->rule.groups.used) {
        execute_set.as.id_groups = &process->rule.groups;
      }
    }

    if (process->rule.limits.used) {
      execute_set.as.limits = &process->rule.limits;
    }

    if (process->rule.has & controller_rule_has_scheduler) {
      execute_set.as.scheduler = &process->rule.scheduler;
    }

    if (process->rule.has & controller_rule_has_nice) {
      execute_set.as.nice = &process->rule.nice;
    }

    if (process->rule.has & controller_rule_has_user) {
      execute_set.as.id_user = &process->rule.user;
    }

    status = fl_environment_load_names(process->rule.environment, &environment);

    if (F_status_is_error(status)) {
      controller_error_print(main.data->error, F_status_set_fine(status), "fl_environment_load_names", F_true, main.thread);

      return status;
    }

    for (i = 0; i < process->rule.items.used && controller_thread_is_enabled_process(process, main.thread); ++i) {

      if (process->rule.items.array[i].type == controller_rule_item_type_setting) continue;

      with = 0;

      for (j = 0; j < process->rule.items.array[i].actions.used; ++j) {

        if (process->rule.items.array[i].actions.array[j].type == controller_rule_action_type_with) {
          for (k = 0; k < process->rule.items.array[i].actions.array[j].parameters.used; ++k) {

            if (fl_string_dynamic_compare_string(controller_string_full_path_s, process->rule.items.array[i].actions.array[j].parameters.array[k], controller_string_full_path_length) == F_equal_to) {
              with |= controller_with_full_path;
            }
          } // for
        }
      } // for

      for (j = 0; j < process->rule.items.array[i].actions.used; ++j) {

        if (!controller_thread_is_enabled_process(process, main.thread)) {
          status = F_signal;

          break;
        }

        if (process->rule.items.array[i].actions.array[j].type != action) continue;

        execute_set.parameter.data = 0;
        execute_set.parameter.option = fl_execute_parameter_option_threadsafe | fl_execute_parameter_option_return;

        if (with & controller_with_full_path) {
          execute_set.parameter.option |= fl_execute_parameter_option_path;
        }

        if (process->rule.items.array[i].type == controller_rule_item_type_command) {
          status = controller_rule_execute_foreground(process->rule.items.array[i].type, process->rule.items.array[i].actions.array[j], 0, process->rule.items.array[i].actions.array[j].parameters, options, main, &execute_set, process);

          if (status == F_child || status == F_signal || F_status_set_fine(status) == F_lock) break;

          if (F_status_is_error(status)) {
            process->rule.items.array[i].actions.array[j].status = F_status_set_error(F_failure);

            if (!(options & controller_process_option_simulate)) break;

            success = F_status_set_error(F_failure);
          }
          else if (success == F_false || success == F_ignore) {
            success = F_true;
          }
        }
        else if (process->rule.items.array[i].type == controller_rule_item_type_script) {
          execute_set.parameter.data = &process->rule.items.array[i].actions.array[j].parameters.array[0];

          status = controller_rule_execute_foreground(process->rule.items.array[i].type, process->rule.items.array[i].actions.array[j], process->rule.script.used ? process->rule.script.string : controller_default_program_script, arguments_none, options, main, &execute_set, process);

          if (status == F_child || status == F_signal || F_status_set_fine(status) == F_lock) break;

          if (F_status_is_error(status)) {
            process->rule.items.array[i].actions.array[j].status = F_status_set_error(F_failure);

            if (!(options & controller_process_option_simulate)) break;

            success = F_status_set_error(F_failure);
          }
          else if (success == F_false || success == F_ignore) {
            success = F_true;
          }
        }
        else if (process->rule.items.array[i].type == controller_rule_item_type_service) {
          pid_file = 0;

          for (k = 0; k < process->rule.items.array[i].actions.used; ++k) {

            if (process->rule.items.array[i].actions.array[k].type != controller_rule_action_type_pid_file) {
              continue;
            }

            if (!process->rule.items.array[i].actions.array[k].parameters.used) {
              continue;
            }

            pid_file = &process->rule.items.array[i].actions.array[k].parameters.array[0];
          } // for

          if (pid_file) {
            status = controller_rule_execute_pid_with(*pid_file, process->rule.items.array[i].type, process->rule.items.array[i].actions.array[j], 0, process->rule.items.array[i].actions.array[j].parameters, options, with, main, &execute_set, process);

            if (status == F_child || status == F_signal || F_status_set_fine(status) == F_lock) break;

            if (F_status_is_error(status)) {
              process->rule.items.array[i].actions.array[j].status = F_status_set_error(F_failure);

              if (!(options & controller_process_option_simulate)) break;

              success = F_status_set_error(F_failure);
            }
            else if (success == F_false || success == F_ignore) {
              success = F_true;
            }
          }
          else {
            success = F_status_set_error(F_failure);

            // @todo make this more specific.
            controller_rule_action_error_missing_pid(main.data->error, process->rule.alias.string);
          }
        }
        else if (process->rule.items.array[i].type == controller_rule_item_type_utility) {
          pid_file = 0;

          for (k = 0; k < process->rule.items.array[i].actions.used; ++k) {

            if (process->rule.items.array[i].actions.array[k].type != controller_rule_action_type_pid_file) {
              continue;
            }

            if (!process->rule.items.array[i].actions.array[k].parameters.used) {
              continue;
            }

            pid_file = &process->rule.items.array[i].actions.array[k].parameters.array[0];
          } // for

          if (pid_file) {
            execute_set.parameter.data = &process->rule.items.array[i].actions.array[j].parameters.array[0];

            status = controller_rule_execute_pid_with(*pid_file, process->rule.items.array[i].type, process->rule.items.array[i].actions.array[j], process->rule.script.used ? process->rule.script.string : controller_default_program_script, arguments_none, options, with, main, &execute_set, process);

            if (status == F_child || status == F_signal || F_status_set_fine(status) == F_lock) break;

            if (F_status_is_error(status)) {
              process->rule.items.array[i].actions.array[j].status = F_status_set_error(F_failure);

              if (!(options & controller_process_option_simulate)) break;

              success = F_status_set_error(F_failure);
            }
            else if (success == F_false || success == F_ignore) {
              success = F_true;
            }
          }
          else {
            success = F_status_set_error(F_failure);

            // @todo make this more specific.
            controller_rule_action_error_missing_pid(main.data->error, process->rule.alias.string);
          }
        }
        else {
          if (main.data->warning.verbosity == f_console_verbosity_debug) {
            f_thread_mutex_lock(&main.thread->lock.print);

            fprintf(main.data->warning.to.stream, "%c", f_string_eol_s[0]);
            fprintf(main.data->warning.to.stream, "%s%sAction type is unknown, ignoring.%s%c", main.data->warning.context.before->string, main.data->warning.prefix ? main.data->warning.prefix : f_string_empty_s, main.data->warning.context.after->string, f_string_eol_s[0]);

            controller_rule_error_print_cache(main.data->warning, process->cache.action, F_true);

            controller_print_unlock_flush(main.data->warning.to.stream, &main.thread->lock.print);
          }

          if (success == F_false) {
            success = F_ignore;
          }

          continue;
        }
      } // for

      if (status == F_child || status == F_signal || F_status_is_error(status) && !(options & controller_process_option_simulate)) {
         break;
       }
    } // for

    f_macro_string_maps_t_delete_simple(environment);

    // lock failed, attempt to re-establish lock before returning.
    if (F_status_set_fine(status) == F_lock) {
      status = controller_lock_read(process, main.thread, &process->lock);

      if (status == F_signal || F_status_is_error(status)) {
        return F_status_set_error(F_lock);
      }

      success = F_false;
    }

    if (!controller_thread_is_enabled_process(process, main.thread)) {
      return F_signal;
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
  f_status_t controller_rule_execute_foreground(const uint8_t type, const controller_rule_action_t action, const f_string_t program, const f_string_dynamics_t arguments, const uint8_t options, const controller_main_t main, controller_execute_set_t * const execute_set, controller_process_t *process) {

    f_status_t status = F_none;
    f_status_t status_lock = F_none;

    int result = 0;
    pid_t id_child = 0;

    if (options & controller_process_option_simulate) {
      if (main.data->error.verbosity != f_console_verbosity_quiet) {
        f_thread_mutex_lock(&main.thread->lock.print);

        fprintf(main.data->output.stream, "%c", f_string_eol_s[0]);
        fprintf(main.data->output.stream, "Simulating execution of '");
        fprintf(main.data->output.stream, "%s%s%s", main.data->context.title.string, program ? program : arguments.used && arguments.array[0].used ? arguments.array[0].string : f_string_empty_s, main.data->context.reset.string);
        fprintf(main.data->output.stream, "' with the arguments: '%s", main.data->context.important.string);

        for (f_array_length_t i = program ? 0 : 1; i < arguments.used; ++i) {
          fprintf(main.data->output.stream, "%s%s", (program && i || !program && i > 1) ? f_string_space_s : "", arguments.array[i].string);
        } // for

        fprintf(main.data->output.stream, "%s' from '", main.data->context.reset.string);
        fprintf(main.data->output.stream, "%s%s%s", main.data->context.notable.string, process->rule.name.used ? process->rule.name.string : f_string_empty_s, main.data->context.reset.string);
        fprintf(main.data->output.stream, "%s'.%c", main.data->context.reset.string, f_string_eol_s[0]);

        controller_print_unlock_flush(main.data->output.stream, &main.thread->lock.print);
      }

      // sleep for less than a second to better show simulation of synchronous vs asynchronous.
      usleep(controller_thread_simulation_timeout);

      const f_string_static_t simulated_program = f_macro_string_static_t_initialize(f_string_empty_s, 0);
      const f_string_statics_t simulated_arguments = f_string_statics_t_initialize;
      fl_execute_parameter_t simulated_parameter = fl_macro_execute_parameter_t_initialize(execute_set->parameter.option, execute_set->parameter.wait, execute_set->parameter.environment, execute_set->parameter.signals, &simulated_program);

      status = fll_execute_program(controller_default_program_script, simulated_arguments, &simulated_parameter, &execute_set->as, simulated_parameter.option & fl_execute_parameter_option_return ? (void *) &id_child : (void *) &result);
    }
    else {
      status = fll_execute_program(program, arguments, &execute_set->parameter, &execute_set->as, execute_set->parameter.option & fl_execute_parameter_option_return ? (void *) &id_child : (void *) &result);
    }

    if (status == F_parent) {
      result = 0;

      f_thread_unlock(&process->lock);

      status_lock = controller_lock_write_process(process, main.thread, &process->lock);

      if (status_lock == F_signal || F_status_is_error(status_lock)) {
        controller_lock_error_critical_print(main.data->error, F_status_set_fine(status_lock), F_false, main.thread);

        if (status_lock != F_signal) {
          status = controller_lock_read_process(process, main.thread, &process->lock);

          if (status == F_none) {
            return status_lock;
          }
        }

        return F_status_set_error(F_lock);
      }

      // assign the child process id to allow for the cancel process to send appropriate termination signals to the child process.
      process->child = id_child;

      f_thread_unlock(&process->lock);

      status_lock = controller_lock_read_process(process, main.thread, &process->lock);

      if (status_lock == F_signal || F_status_is_error(status_lock)) {
        controller_lock_error_critical_print(main.data->error, F_status_set_fine(status_lock), F_true, main.thread);
      }

      if (status_lock != F_signal) {

        // have the parent wait for the child process to finish.
        waitpid(id_child, &result, 0);
      }

      if (status_lock == F_signal || !controller_thread_is_enabled_process(process, main.thread)) {
        if (status_lock == F_none) {
          return F_signal;
        }

        return F_status_set_error(F_lock);
      }

      if (status_lock == F_none) {
        f_thread_unlock(&process->lock);
      }

      status_lock = controller_lock_write_process(process, main.thread, &process->lock);

      if (status_lock == F_signal || F_status_is_error(status_lock)) {
        controller_lock_error_critical_print(main.data->error, F_status_set_fine(status_lock), F_false, main.thread);

        if (status_lock != F_signal) {
          status = controller_lock_read_process(process, main.thread, &process->lock);

          if (status == F_none) {
            return status_lock;
          }
        }

        return F_status_set_error(F_lock);
      }

      // remove the pid now that waidpid() has returned.
      process->child = 0;

      f_thread_unlock(&process->lock);

      status_lock = controller_lock_read_process(process, main.thread, &process->lock);

      if (status_lock == F_signal || F_status_is_error(status_lock)) {
        controller_lock_error_critical_print(main.data->error, F_status_set_fine(status_lock), F_true, main.thread);

        return F_status_set_error(F_lock);
      }

      // this must explicitly check for 0 (as opposed to checking (!result)).
      if (!WIFEXITED(result)) {
        status = F_status_set_error(F_failure);
      }
      else {
        status = F_none;
      }
    }
    else {
      if (!controller_thread_is_enabled_process(process, main.thread)) {
        return F_signal;
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

    if (status == F_child || status == F_signal) {
      return status;
    }

    if (result != 0) {
      status = F_status_set_error(F_failure);
    }

    if (F_status_is_error(status)) {
      status = F_status_set_fine(status);

      f_thread_mutex_lock(&main.thread->lock.print);

      if (status == F_control_group || status == F_failure || status == F_limit || status == F_processor || status == F_schedule) {
        controller_rule_item_error_print_execute(main.data->error, type == controller_rule_item_type_script, program ? program : arguments.used ? arguments.array[0].string : f_string_empty_s, result, status);
      }
      else if (status == F_file_found_not) {
        controller_rule_item_error_print_execute_not_found(main.data->error, F_false, program);
      }
      else {
        controller_error_print(main.data->error, F_status_set_fine(status), "fll_execute_program", F_true, main.thread);
      }

      controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);

      status = F_status_set_error(status);
    }

    return status;
  }
#endif // _di_controller_rule_execute_foreground_

#ifndef _di_controller_rule_execute_pid_with_
  f_status_t controller_rule_execute_pid_with(const f_string_dynamic_t pid_file, const uint8_t type, const controller_rule_action_t action, const f_string_t program, const f_string_dynamics_t arguments, const uint8_t options, const uint8_t with, const controller_main_t main, controller_execute_set_t * const execute_set, controller_process_t *process) {

    f_status_t status = F_none;
    f_status_t status_lock = F_none;

    int result = 0;
    pid_t id_child = 0;

    process->path_pid.used = 0;

    status = f_file_exists(pid_file.string);

    if (F_status_is_error(status)) {
      fll_error_file_print(main.data->error, F_status_set_fine(status), "f_file_exists", F_true, pid_file.string, "find", fll_error_file_type_file);

      return status;
    }

    if (status == F_true) {
      fll_error_file_print(main.data->error, F_file_found, "f_file_exists", F_true, pid_file.string, "create PID", fll_error_file_type_file);

      return F_status_set_error(F_file_found);
    }

    status = controller_string_dynamic_append_terminated(pid_file, &process->path_pid);

    if (F_status_is_error(status)) {
      fll_error_print(main.data->error, F_status_set_fine(status), "controller_string_dynamic_append_terminated", F_true);

      return status;
    }

    if (options & controller_process_option_simulate) {

      if (main.data->error.verbosity != f_console_verbosity_quiet) {
        f_thread_mutex_lock(&main.thread->lock.print);

        fprintf(main.data->output.stream, "%c", f_string_eol_s[0]);
        fprintf(main.data->output.stream, "Simulating execution of '");
        fprintf(main.data->output.stream, "%s%s%s", main.data->context.title.string, program ? program : arguments.used && arguments.array[0].used ? arguments.array[0].string : f_string_empty_s, main.data->context.reset.string);
        fprintf(main.data->output.stream, "' with the arguments: '%s", main.data->context.important.string);

        for (f_array_length_t i = program ? 0 : 1; i < arguments.used; ++i) {
          fprintf(main.data->output.stream, "%s%s", (program && i || !program && i > 1) ? f_string_space_s : "", arguments.array[i].string);
        } // for

        fprintf(main.data->output.stream, "%s' from '", main.data->context.reset.string);
        fprintf(main.data->output.stream, "%s%s%s", main.data->context.notable.string, process->rule.name.used ? process->rule.name.string : f_string_empty_s, main.data->context.reset.string);
        fprintf(main.data->output.stream, "%s'.%c", main.data->context.reset.string, f_string_eol_s[0]);

        controller_print_unlock_flush(main.data->output.stream, &main.thread->lock.print);
      }

      // sleep for less than a second to better show simulation of synchronous vs asynchronous.
      usleep(controller_thread_simulation_timeout);

      const f_string_static_t simulated_program = f_macro_string_static_t_initialize(f_string_empty_s, 0);
      const f_string_statics_t simulated_arguments = f_string_statics_t_initialize;
      fl_execute_parameter_t simulated_parameter = fl_macro_execute_parameter_t_initialize(execute_set->parameter.option, execute_set->parameter.wait, execute_set->parameter.environment, execute_set->parameter.signals, &simulated_program);

      status = fll_execute_program(controller_default_program_script, simulated_arguments, &simulated_parameter, &execute_set->as, simulated_parameter.option & fl_execute_parameter_option_return ? (void *) &id_child : (void *) &result);
    }
    else {
      status = fll_execute_program(program, arguments, &execute_set->parameter, &execute_set->as, execute_set->parameter.option & fl_execute_parameter_option_return ? (void *) &id_child : (void *) &result);
    }

    if (status == F_parent) {
      result = 0;

      f_thread_unlock(&process->lock);

      status_lock = controller_lock_write_process(process, main.thread, &process->lock);

      if (status_lock == F_signal || F_status_is_error(status_lock)) {
        controller_lock_error_critical_print(main.data->error, F_status_set_fine(status_lock), F_false, main.thread);

        if (status_lock != F_signal) {
          status = controller_lock_read_process(process, main.thread, &process->lock);

          if (status == F_none) {
            return status_lock;
          }
        }

        return F_status_set_error(F_lock);
      }

      // assign the child process id to allow for the cancel process to send appropriate termination signals to the child process.
      process->child = id_child;

      f_thread_unlock(&process->lock);

      status_lock = controller_lock_read_process(process, main.thread, &process->lock);

      if (status_lock == F_signal || F_status_is_error(status_lock)) {
        controller_lock_error_critical_print(main.data->error, F_status_set_fine(status_lock), F_true, main.thread);
      }

      if (status_lock != F_signal) {

        // the child process should perform the change into background, therefore it is safe to wait for the child to exit (another process is spawned).
        waitpid(id_child, &result, 0);
      }

      if (!controller_thread_is_enabled_process(process, main.thread)) {
        if (status_lock == F_none) {
          return F_signal;
        }

        return F_signal;
      }

      if (status_lock == F_none) {
        f_thread_unlock(&process->lock);
      }

      status_lock = controller_lock_write_process(process, main.thread, &process->lock);

      if (status_lock == F_signal || F_status_is_error(status_lock)) {
        controller_lock_error_critical_print(main.data->error, F_status_set_fine(status_lock), F_false, main.thread);

        if (status_lock != F_signal) {
          status = controller_lock_read_process(process, main.thread, &process->lock);

          if (status == F_none) {
            return status_lock;
          }
        }

        return F_status_set_error(F_lock);
      }

      // remove the pid now that waidpid() has returned.
      process->child = 0;

      f_thread_unlock(&process->lock);

      status_lock = controller_lock_read_process(process, main.thread, &process->lock);

      if (status_lock == F_signal || F_status_is_error(status_lock)) {
        controller_lock_error_critical_print(main.data->error, F_status_set_fine(status_lock), F_true, main.thread);

        return F_status_set_error(F_lock);
      }

      // this must explicitly check for 0 (as opposed to checking (!result)).
      // @todo expand this to provide user more control over what is or is not an error to designate as a failure.
      if (!WIFEXITED(result)) {
        status = F_status_set_error(F_failure);
      }
      else {
        status = F_none;
      }
    }
    else {
      if (!controller_thread_is_enabled_process(process, main.thread)) {
        return F_signal;
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

    if (status == F_child || status == F_signal) {
      return status;
    }

    if (result != 0) {
      status = F_status_set_error(F_failure);
    }

    if (F_status_is_error(status)) {
      status = F_status_set_fine(status);

      f_thread_mutex_lock(&main.thread->lock.print);

      if (status == F_control_group || status == F_failure || status == F_limit || status == F_processor || status == F_schedule) {
        controller_rule_item_error_print_execute(main.data->error, type == controller_rule_item_type_utility, program ? program : arguments.used ? arguments.array[0].string : f_string_empty_s, result, status);
      }
      else if (status == F_file_found_not) {
        controller_rule_item_error_print_execute_not_found(main.data->error, F_false, program);
      }
      else {
        controller_error_print(main.data->error, F_status_set_fine(status), "fll_execute_program", F_true, main.thread);
      }

      controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);

      return F_status_set_error(status);
    }

    return status;
  }
#endif // _di_controller_rule_execute_pid_with_

#ifndef _di_controller_rule_id_construct_
  f_status_t controller_rule_id_construct(const controller_main_t main, const f_string_static_t source, const f_string_range_t directory, const f_string_range_t basename, f_string_dynamic_t *alias) {

    f_status_t status = F_none;

    alias->used = 0;

    status = f_string_dynamic_partial_append_nulless(source, directory, alias);

    if (F_status_is_error(status)) {
      controller_error_print(main.data->error, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, main.thread);

      return status;
    }

    status = f_string_append(f_path_separator_s, f_path_separator_length, alias);

    if (F_status_is_error(status)) {
      controller_error_print(main.data->error, F_status_set_fine(status), "f_string_append", F_true, main.thread);

      return status;
    }

    status = f_string_dynamic_partial_append_nulless(source, basename, alias);

    if (F_status_is_error(status)) {
      controller_error_print(main.data->error, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, main.thread);

      return status;
    }

    status = f_string_dynamic_terminate_after(alias);

    if (F_status_is_error(status)) {
      controller_error_print(main.data->error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true, main.thread);
    }

    return status;
  }
#endif // _di_controller_rule_id_construct_

#ifndef _di_controller_rule_item_read_
  f_status_t controller_rule_item_read(const controller_main_t main, controller_cache_t *cache, controller_rule_item_t *item) {

    f_status_t status = F_none;

    f_string_range_t range = f_macro_string_range_t_initialize(cache->buffer_item.used);
    f_array_length_t last = 0;

    uint8_t type = 0;
    uint8_t method = 0;
    bool multiple = F_false;

    item->actions.used = 0;

    for (; range.start < cache->buffer_item.used && range.start <= range.stop; last = range.start, cache->delimits.used = 0, cache->comments.used = 0) {

      status = fl_fss_extended_list_object_read(cache->buffer_item, &range, &cache->range_action, &cache->delimits);

      if (F_status_is_error(status)) {
        controller_error_print(main.data->error, F_status_set_fine(status), "fl_fss_extended_list_object_read", F_true, main.thread);
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
          controller_error_print(main.data->error, F_status_set_fine(status), "fl_fss_extended_object_read", F_true, main.thread);
          break;
        }

        // Nothing of importance here, so continue onto the next line.
        // @todo present an error if this line is anything but whitespace.
        if (status != FL_fss_found_object) continue;
      }

      status = fl_fss_apply_delimit(cache->delimits, &cache->buffer_item);

      if (F_status_is_error(status)) {
        controller_error_print(main.data->error, F_status_set_fine(status), "fl_fss_apply_delimit", F_true, main.thread);
        break;
      }

      status = f_fss_count_lines(cache->buffer_item, cache->range_action.start, &cache->action.line_action);

      if (F_status_is_error(status)) {
        controller_error_print(main.data->error, F_status_set_fine(status), "f_fss_count_lines", F_true, main.thread);
        break;
      }

      cache->action.line_action += ++item->line;
      cache->action.name_action.used = 0;

      status = controller_string_dynamic_rip_nulless_terminated(cache->buffer_item, cache->range_action, &cache->action.name_action);

      if (F_status_is_error(status)) {
        controller_error_print(main.data->error, F_status_set_fine(status), "controller_string_dynamic_rip_nulless_terminated", F_true, main.thread);
        break;
      }

      if (fl_string_dynamic_compare_string(controller_string_group_s, cache->action.name_action, controller_string_group_length) == F_equal_to) {
        type = controller_rule_action_type_group;
      }
      else if (fl_string_dynamic_compare_string(controller_string_kill_s, cache->action.name_action, controller_string_kill_length) == F_equal_to) {
        type = controller_rule_action_type_kill;
      }
      else if (fl_string_dynamic_compare_string(controller_string_pause_s, cache->action.name_action, controller_string_pause_length) == F_equal_to) {
        type = controller_rule_action_type_pause;
      }
      else if (fl_string_dynamic_compare_string(controller_string_pid_file_s, cache->action.name_action, controller_string_pid_file_length) == F_equal_to) {
        type = controller_rule_action_type_pid_file;
      }
      else if (fl_string_dynamic_compare_string(controller_string_restart_s, cache->action.name_action, controller_string_restart_length) == F_equal_to) {
        type = controller_rule_action_type_restart;
      }
      else if (fl_string_dynamic_compare_string(controller_string_resume_s, cache->action.name_action, controller_string_resume_length) == F_equal_to) {
        type = controller_rule_action_type_resume;
      }
      else if (fl_string_dynamic_compare_string(controller_string_reload_s, cache->action.name_action, controller_string_reload_length) == F_equal_to) {
        type = controller_rule_action_type_reload;
      }
      else if (fl_string_dynamic_compare_string(controller_string_start_s, cache->action.name_action, controller_string_start_length) == F_equal_to) {
        type = controller_rule_action_type_start;
      }
      else if (fl_string_dynamic_compare_string(controller_string_stop_s, cache->action.name_action, controller_string_stop_length) == F_equal_to) {
        type = controller_rule_action_type_stop;
      }
      else if (fl_string_dynamic_compare_string(controller_string_user_s, cache->action.name_action, controller_string_user_length) == F_equal_to) {
        type = controller_rule_action_type_user;
      }
      else if (fl_string_dynamic_compare_string(controller_string_with_s, cache->action.name_action, controller_string_with_length) == F_equal_to) {
        type = controller_rule_action_type_with;
      }
      else {
        if (main.data->warning.verbosity == f_console_verbosity_debug) {
          f_thread_mutex_lock(&main.thread->lock.print);

          fprintf(main.data->warning.to.stream, "%c", f_string_eol_s[0]);
          fprintf(main.data->warning.to.stream, "%s%sUnknown rule item action '", main.data->warning.context.before->string, main.data->warning.prefix ? main.data->warning.prefix : f_string_empty_s);
          fprintf(main.data->warning.to.stream, "%s%s", main.data->warning.context.after->string, main.data->warning.notable.before->string);
          f_print_dynamic(main.data->warning.to.stream, cache->action.name_action);
          fprintf(main.data->warning.to.stream, "%s", main.data->warning.notable.after->string);
          fprintf(main.data->warning.to.stream, "%s'.%s%c", main.data->warning.context.before->string, main.data->warning.context.after->string, f_string_eol_s[0]);

          controller_rule_error_print_cache(main.data->warning, cache->action, F_true);

          controller_print_unlock_flush(main.data->warning.to.stream, &main.thread->lock.print);
        }

        continue;
      }

      if (multiple) {
        if (type == controller_rule_action_type_group || type == controller_rule_action_type_pid_file || type == controller_rule_action_type_user) {

          if (main.data->error.verbosity != f_console_verbosity_quiet) {
            f_thread_mutex_lock(&main.thread->lock.print);

            fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
            fprintf(main.data->error.to.stream, "%s%sFSS Extended List is not allowed for the rule item action '", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s);
            fprintf(main.data->error.to.stream, "%s%s", main.data->error.context.after->string, main.data->error.notable.before->string);
            f_print_dynamic(main.data->error.to.stream, cache->action.name_action);
            fprintf(main.data->error.to.stream, "%s", main.data->error.notable.after->string);
            fprintf(main.data->error.to.stream, "%s'.%s%c", main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);

            controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);
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
        controller_error_print(main.data->error, F_status_set_fine(status), "controller_rule_actions_increase_by", F_true, main.thread);
        break;
      }

      status = controller_rule_action_read(main, type, method, cache, item, &item->actions, &range);
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

      case controller_rule_item_type_utility:
        buffer.string = controller_string_utility_s;
        buffer.used = controller_string_utility_length;
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

#ifndef _di_controller_rule_process_
  f_status_t controller_rule_process(const controller_main_t main, controller_process_t *process) {

    switch (process->action) {
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
        if (main.data->error.verbosity != f_console_verbosity_quiet) {
          f_thread_mutex_lock(&main.thread->lock.print);

          fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
          fprintf(main.data->error.to.stream, "%s%sUnsupported action type '", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s);
          fprintf(main.data->error.to.stream, "%s%s%s%s", main.data->error.context.after->string, main.data->error.notable.before->string, controller_rule_action_type_name(process->action), main.data->error.notable.after->string);
          fprintf(main.data->error.to.stream, "%s' while attempting to execute rule.%s%c", main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);

          controller_rule_error_print_cache(main.data->error, process->cache.action, F_true);

          controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);
        }

        return F_status_set_error(F_parameter);
    }

    f_status_t status = F_none;
    f_status_t status_lock = F_none;

    process->cache.action.name_action.used = 0;
    process->cache.action.name_item.used = 0;
    process->cache.action.name_file.used = 0;

    status = f_string_append(controller_string_rules_s, controller_string_rules_length, &process->cache.action.name_file);

    if (F_status_is_error_not(status)) {
      status = f_string_append(f_path_separator_s, f_path_separator_length, &process->cache.action.name_file);
    }

    if (F_status_is_error(status)) {
      controller_rule_error_print(main.data->error, process->cache.action, F_status_set_fine(status), "f_string_append", F_true, F_true, main.thread);

      return status;
    }

    status = f_string_dynamic_append(process->rule.alias, &process->cache.action.name_file);

    if (F_status_is_error(status)) {
      controller_rule_error_print(main.data->error, process->cache.action, F_status_set_fine(status), "f_string_dynamic_append", F_true, F_true, main.thread);

      return status;
    }

    status = f_string_append(f_path_extension_separator, f_path_extension_separator_length, &process->cache.action.name_file);

    if (F_status_is_error_not(status)) {
      status = f_string_append(controller_string_rule_s, controller_string_rule_length, &process->cache.action.name_file);
    }

    if (F_status_is_error(status)) {
      controller_rule_error_print(main.data->error, process->cache.action, F_status_set_fine(status), "f_string_append", F_true, F_true, main.thread);

      return status;
    }

    status = f_string_dynamic_terminate_after(&process->cache.action.name_file);

    if (F_status_is_error(status)) {
      controller_rule_error_print(main.data->error, process->cache.action, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true, F_true, main.thread);

      return status;
    }

    if ((process->options & controller_process_option_simulate) && main.data->parameters[controller_parameter_validate].result == f_console_result_found) {
      controller_rule_validate(process->rule, process->action, process->options, main, &process->cache);
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

      f_string_dynamics_t * const dynamics[] = {
        &process->rule.need,
        &process->rule.want,
        &process->rule.wish,
      };

      const f_string_t strings[] = {
        "needed",
        "wanted",
        "wished for",
      };

      // i==0 is need, i==1 is want, i==2 is wish.
      // loop through all dependencies: wait for depedency, execute dependency, fail due to missing required dependency, or skip unrequired missing dependencies.
      for (; i < 3 && controller_thread_is_enabled_process(process, main.thread); ++i) {

        for (j = 0; j < dynamics[i]->used && controller_thread_is_enabled_process(process, main.thread); ++j) {

          id_dependency = 0;
          dependency = 0;
          found = F_false;

          status_lock = controller_lock_read_process(process, main.thread, &main.thread->lock.process);

          if (status_lock == F_signal || F_status_is_error(status_lock)) {
            controller_lock_error_critical_print(main.data->error, F_status_set_fine(status_lock), F_true, main.thread);
          }
          else {
            status = controller_find_process(dynamics[i]->array[j], main.thread->processs, &id_dependency);
          }

          if (status == F_true) {
            found = F_true;

            dependency = main.thread->processs.array[id_dependency];

            status_lock = controller_lock_read_process(process, main.thread, &dependency->active);

            if (status_lock == F_signal || F_status_is_error(status_lock)) {
              controller_lock_error_critical_print(main.data->error, F_status_set_fine(status_lock), F_true, main.thread);

              status = F_false;
              dependency = 0;

              f_thread_unlock(&main.thread->lock.process);
            }
            else {
              f_thread_unlock(&main.thread->lock.process);

              status_lock = controller_lock_read_process(process, main.thread, &main.thread->lock.rule);

              if (status_lock == F_signal || F_status_is_error(status_lock)) {
                controller_lock_error_critical_print(main.data->error, F_status_set_fine(status_lock), F_true, main.thread);

                status = F_false;
              }
              else {
                status = controller_rule_find(dynamics[i]->array[j], main.setting->rules, &id_rule);

                f_thread_unlock(&main.thread->lock.rule);
              }
            }
          }
          else {
            f_thread_unlock(&main.thread->lock.process);
          }

          if (status != F_true) {
            found = F_false;
            id_rule = 0;

            if (i == 0) {
              f_thread_mutex_lock(&main.thread->lock.print);

              controller_rule_item_error_print_need_want_wish(main.data->error, strings[i], dynamics[i]->array[j].string, "was not found");
              controller_rule_error_print_cache(main.data->error, process->cache.action, F_true);

              controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);

              status = F_status_set_error(F_found_not);

              if (!(process->options & controller_process_option_simulate)) {
                if (dependency) {
                  f_thread_unlock(&dependency->active);
                }

                break;
              }
            }
            else {
              if (main.data->warning.verbosity == f_console_verbosity_debug) {
                f_thread_mutex_lock(&main.thread->lock.print);

                controller_rule_item_error_print_need_want_wish(main.data->warning, strings[i], dynamics[i]->array[j].string, "was not found");
                controller_rule_error_print_cache(main.data->warning, process->cache.action, F_true);

                controller_print_unlock_flush(main.data->warning.to.stream, &main.thread->lock.print);
              }
            }
          }
          else if (found) {
            status_lock = controller_lock_read_process(process, main.thread, &main.thread->lock.rule);

            if (status_lock == F_signal || F_status_is_error(status_lock)) {
              controller_lock_error_critical_print(main.data->error, F_status_set_fine(status_lock), F_true, main.thread);

              found = F_false;
              status = status_lock;
            }
          }

          if (found) {

            // the dependency may have write locks, which needs to be avoided, so copy the alias from the rule.
            char alias_other_buffer[main.setting->rules.array[id_rule].alias.used + 1];

            memcpy(alias_other_buffer, main.setting->rules.array[id_rule].alias.string, sizeof(char) * main.setting->rules.array[id_rule].alias.used);
            alias_other_buffer[main.setting->rules.array[id_rule].alias.used] = 0;

            const f_string_static_t alias_other = f_macro_string_static_t_initialize(alias_other_buffer, main.setting->rules.array[id_rule].alias.used);

            f_thread_unlock(&main.thread->lock.rule);

            status_lock = controller_lock_read_process(process, main.thread, &dependency->lock);

            if (status_lock == F_signal || F_status_is_error(status_lock)) {
              controller_lock_error_critical_print(main.data->error, F_status_set_fine(status_lock), F_true, main.thread);

              status = status_lock;
            }
            else if (dependency->state == controller_process_state_active || dependency->state == controller_process_state_busy) {
              f_thread_unlock(&dependency->lock);

              status = controller_process_wait(main, dependency);

              if (F_status_is_error(status) && !(process->options & controller_process_option_simulate)) break;

              status = dependency->rule.status;
            }
            else {
              status_lock = controller_lock_read_process(process, main.thread, &main.thread->lock.rule);

              if (status_lock == F_signal || F_status_is_error(status_lock)) {
                controller_lock_error_critical_print(main.data->error, F_status_set_fine(status_lock), F_true, main.thread);

                f_thread_unlock(&dependency->lock);

                status = status_lock;
              }
              else if (main.setting->rules.array[id_rule].status == F_known_not) {
                f_thread_unlock(&main.thread->lock.rule);
                f_thread_unlock(&dependency->lock);

                options_process = 0;

                if (main.data->parameters[controller_parameter_test].result == f_console_result_found) {
                  options_process |= controller_process_option_simulate;
                }

                if (main.data->parameters[controller_parameter_validate].result == f_console_result_found) {
                  options_process |= controller_process_option_validate;
                }

                // synchronously execute dependency.
                status = controller_rule_process_begin(0, alias_other, process->action, options_process, process->type, process->stack, main, dependency->cache);

                if (status == F_child || status == F_signal) {
                  f_thread_unlock(&dependency->active);

                  break;
                }

                if (F_status_is_error(status)) {
                  if (i == 0 || i == 1 || F_status_set_fine(status) == F_memory_not) {
                    f_thread_mutex_lock(&main.thread->lock.print);

                    controller_rule_item_error_print_need_want_wish(main.data->error, strings[i], alias_other_buffer, "failed during execution");
                    controller_rule_error_print_cache(main.data->error, process->cache.action, F_true);

                    controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);

                    if (!(dependency->options & controller_process_option_simulate) || F_status_set_fine(status) == F_memory_not) {
                      f_thread_unlock(&dependency->active);

                      break;
                    }
                  }
                  else {
                    if (main.data->warning.verbosity == f_console_verbosity_debug) {
                      f_thread_mutex_lock(&main.thread->lock.print);

                      controller_rule_item_error_print_need_want_wish(main.data->warning, strings[i], alias_other_buffer, "failed during execution");
                      controller_rule_error_print_cache(main.data->warning, process->cache.action, F_true);

                      controller_print_unlock_flush(main.data->warning.to.stream, &main.thread->lock.print);
                    }
                  }
                }
              }
              else {
                status = main.setting->rules.array[id_rule].status;

                f_thread_unlock(&main.thread->lock.rule);
                f_thread_unlock(&dependency->lock);
              }
            }

            if (!controller_thread_is_enabled_process(process, main.thread)) {
              f_thread_unlock(&dependency->active);

              break;
            }

            if (status_lock != F_signal && F_status_is_error_not(status_lock)) {
              status_lock = controller_lock_read_process(process, main.thread, &main.thread->lock.rule);

              if (status_lock == F_signal || F_status_is_error(status_lock)) {
                controller_lock_error_critical_print(main.data->error, F_status_set_fine(status_lock), F_false, main.thread);
              }
            }

            if (status_lock == F_signal || F_status_is_error(status_lock)) {
              if (F_status_is_error(status_lock)) {
                controller_rule_item_error_print_need_want_wish(main.data->error, strings[i], alias_other_buffer, "due to lock failure");
              }

              status = status_lock;
            }
            else if (F_status_is_error(main.setting->rules.array[id_rule].status)) {
              f_thread_unlock(&main.thread->lock.rule);

              if (i == 0 || i == 1) {
                f_thread_mutex_lock(&main.thread->lock.print);

                controller_rule_item_error_print_need_want_wish(main.data->error, strings[i], alias_other_buffer, "is in a failed state");

                status = F_status_set_error(F_found_not);
                controller_rule_error_print_cache(main.data->error, process->cache.action, F_true);

                controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);

                if (!(dependency->options & controller_process_option_simulate)) {
                  f_thread_unlock(&dependency->active);

                  break;
                }
              }
              else {
                if (main.data->warning.verbosity == f_console_verbosity_debug) {
                  f_thread_mutex_lock(&main.thread->lock.print);

                  controller_rule_item_error_print_need_want_wish(main.data->warning, strings[i], alias_other_buffer, "is in a failed state");
                  controller_rule_error_print_cache(main.data->warning, process->cache.action, F_true);

                  controller_print_unlock_flush(main.data->warning.to.stream, &main.thread->lock.print);
                }
              }
            }
            else {
              f_thread_unlock(&main.thread->lock.rule);
            }
          }

          if (dependency) {
            f_thread_unlock(&dependency->active);
          }
        } // for

        if (status == F_child || status == F_signal) break;

        if (F_status_is_error(status) && !(process->options & controller_process_option_simulate)) break;
      } // for
    }

    if (status == F_child || status == F_signal) {
      return status;
    }

    if (!controller_thread_is_enabled_process(process, main.thread)) {
      return F_signal;
    }

    if ((process->options & controller_process_option_wait) && F_status_is_error_not(status)) {
      status_lock = controller_rule_wait_all_process_type(process->type, main, F_false, process);

      if (status_lock == F_signal) {
        return F_signal;
      }
    }

    if (!(process->options & controller_process_option_validate) && F_status_is_error_not(status)) {

      // find at least one of the requested action when the rule is required.
      if (process->options & controller_process_option_require) {
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
          if (main.data->error.verbosity != f_console_verbosity_quiet) {
            f_thread_mutex_lock(&main.thread->lock.print);

            fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
            fprintf(main.data->error.to.stream, "%s%sThe rule '", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s);
            fprintf(main.data->error.to.stream, "%s%s%s%s", main.data->error.context.after->string, main.data->error.notable.before->string, process->rule.name.used ? process->rule.name.string : f_string_empty_s, main.data->error.notable.after->string);
            fprintf(main.data->error.to.stream, "%s' has no '", main.data->error.context.before->string);
            fprintf(main.data->error.to.stream, "%s%s%s%s", main.data->error.context.after->string, main.data->error.notable.before->string, controller_rule_action_type_name(process->action).string, main.data->error.notable.after->string);
            fprintf(main.data->error.to.stream, "%s' action to execute.%s%c", main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);

            controller_rule_error_print_cache(main.data->error, process->cache.action, F_true);

            controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);
          }

          status = F_status_set_error(F_parameter);
        }
      }

      if (F_status_is_error_not(status)) {
        status = controller_rule_execute(process->action, process->options, main, process);

        if (status == F_child || status == F_signal || status == F_status_set_error(F_lock)) {
          return status;
        }

        if (!controller_thread_is_enabled_process(process, main.thread)) {
          return F_signal;
        }

        if (F_status_is_error(status)) {
          controller_rule_item_error_print(main.data->error, process->cache.action, F_true, main.thread);
        }
      }
    }

    f_array_length_t id_rule = 0;

    f_thread_unlock(&process->lock);

    status_lock = controller_lock_write_process(process, main.thread, &process->lock);

    if (status_lock == F_signal || F_status_is_error(status_lock)) {
      controller_lock_error_critical_print(main.data->error, F_status_set_fine(status_lock), F_false, main.thread);

      if (status_lock != F_signal) {
        status = controller_lock_read_process(process, main.thread, &process->lock);

        if (status != F_signal && F_status_is_error_not(status)) {
          return status_lock;
        }
      }

      return F_status_set_error(F_lock);
    }

    if (F_status_is_error(status)) {
      process->rule.status = controller_status_simplify_error(F_status_set_fine(status));
    }
    else {
      process->rule.status = status;
    }

    status_lock = controller_lock_write_process(process, main.thread, &main.thread->lock.rule);

    if (status_lock == F_signal || F_status_is_error(status_lock)) {
      controller_lock_error_critical_print(main.data->error, F_status_set_fine(status_lock), F_false, main.thread);

      f_thread_unlock(&process->lock);

      status = controller_lock_read_process(process, main.thread, &process->lock);

      if (status != F_signal && F_status_is_error_not(status)) {
        return status_lock;
      }

      return F_status_set_error(F_lock);
    }

    if (controller_rule_find(process->rule.alias, main.setting->rules, &id_rule) == F_true) {
      controller_rule_t *rule = &main.setting->rules.array[id_rule];

      rule->status = process->rule.status;

      f_array_length_t j = 0;

      controller_rule_item_t *rule_item = 0;
      controller_rule_action_t *rule_action = 0;

      // @todo implement a "version" counter and detect if the rule version is different before attempting update.
      // copy all rule item action statuses from the rule process to the rule.
      for (i = 0; i < rule->items.used; ++i) {

        rule_item = &rule->items.array[i];

        for (j = 0; j < rule_item->actions.used; ++j) {
          rule_item->actions.array[j].status = process->rule.items.array[i].actions.array[j].status;
        } // for
      } // for
    }

    f_thread_unlock(&main.thread->lock.rule);
    f_thread_unlock(&process->lock);

    status_lock = controller_lock_read_process(process, main.thread, &process->lock);

    if (status_lock == F_signal || F_status_is_error(status_lock)) {
      controller_lock_error_critical_print(main.data->error, F_status_set_fine(status_lock), F_true, main.thread);

      return F_status_set_error(F_lock);
    }

    return process->rule.status;
  }
#endif // _di_controller_rule_process_

#ifndef _di_controller_rule_process_begin_
  f_status_t controller_rule_process_begin(const uint8_t options_force, const f_string_static_t alias_rule, const uint8_t action, const uint8_t options, const uint8_t type, const f_array_lengths_t stack, const controller_main_t main, const controller_cache_t cache) {

    if (!controller_thread_is_enabled_process_type(type, main.thread)) {
      return F_signal;
    }

    f_status_t status = F_none;

    controller_process_t *process = 0;

    status = controller_lock_read_process_type(type, main.thread, &main.thread->lock.process);

    if (status == F_signal || F_status_is_error(status)) {
      controller_lock_error_critical_print(main.data->error, F_status_set_fine(status), F_true, main.thread);

      return status;
    }

    {
      f_array_length_t at = 0;

      if (controller_find_process(alias_rule, main.thread->processs, &at) != F_true) {
        status = F_status_set_error(F_found_not);
      }

      if (F_status_is_error(status)) {
        f_thread_unlock(&main.thread->lock.process);

        if (main.data->error.verbosity != f_console_verbosity_quiet) {
          f_thread_mutex_lock(&main.thread->lock.print);

          controller_rule_item_error_print_rule_not_loaded(main.data->error, alias_rule.string);
          controller_rule_error_print_cache(main.data->error, cache.action, F_false);

          controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);
        }

        return status;
      }

      process = main.thread->processs.array[at];

      status = controller_lock_read_process_type(type, main.thread, &process->active);

      if (status == F_signal || F_status_is_error(status)) {
        controller_lock_error_critical_print(main.data->error, F_status_set_fine(status), F_true, main.thread);
        controller_rule_item_error_print(main.data->error, cache.action, F_false, main.thread);

        f_thread_unlock(&main.thread->lock.process);

        return status;
      }

      status = controller_lock_write_process(process, main.thread, &process->lock);

      if (status == F_signal || F_status_is_error(status)) {
        controller_lock_error_critical_print(main.data->error, F_status_set_fine(status), F_false, main.thread);

        f_thread_unlock(&process->active);
        f_thread_unlock(&main.thread->lock.process);

        return status;
      }

      // once a write lock on the process is achieved, it is safe to unlock the main process read lock.
      f_thread_unlock(&main.thread->lock.process);

      // if the process is already running, then there is nothing to do.
      if (process->state == controller_process_state_active || process->state == controller_process_state_busy) {
        f_thread_unlock(&process->lock);
        f_thread_unlock(&process->active);

        return F_busy;
      }

      // the thread is done, so close the thread.
      if (process->state == controller_process_state_done) {
        controller_thread_join(&process->id_thread);
      }

      process->id = at;
    }

    f_thread_unlock(&process->lock);

    status = controller_lock_write_process(process, main.thread, &process->lock);

    if (status == F_signal || F_status_is_error(status)) {
      controller_lock_error_critical_print(main.data->error, F_status_set_fine(status), F_false, main.thread);

      f_thread_unlock(&process->active);

      return status;
    }

    process->state = controller_process_state_active;
    process->action = action;
    process->options = options;
    process->type = type;

    f_macro_time_spec_t_clear(process->cache.timestamp)
    f_macro_string_range_t_clear(process->cache.range_action)

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

    process->main_data = (void *) main.data;
    process->main_setting = (void *) main.setting;
    process->main_thread = (void *) main.thread;

    if (F_status_is_error_not(status) && stack.used) {
      if (process->stack.size < stack.used) {
        status = f_type_array_lengths_resize(stack.used, &process->stack);
      }

      if (F_status_is_error(status)) {
        controller_entry_error_print(main.data->error, cache.action, F_status_set_fine(status), "f_type_array_lengths_resize", F_true, main.thread);
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
        controller_entry_error_print(main.data->error, cache.action, F_status_set_fine(status), "f_string_dynamic_append", F_true, main.thread);
      }
    }

    f_thread_unlock(&process->lock);

    if (F_status_is_error_not(status)) {
      if (process->action && (options_force & controller_process_option_asynchronous)) {
        status = f_thread_create(0, &process->id_thread, controller_thread_process, (void *) process);

        if (F_status_is_error(status)) {
          controller_entry_error_print(main.data->error, cache.action, F_status_set_fine(status), "f_thread_create", F_true, main.thread);
        }
      }
      else {
        status = controller_rule_process_do(options_force, process);

        if (status == F_child || status == F_signal) {
          f_thread_unlock(&process->active);

          return status;
        }
      }
    }

    if (!action || F_status_is_error(status) && (process->state == controller_process_state_active || process->state == controller_process_state_busy)) {
      status = controller_lock_write_process(process, main.thread, &process->lock);

      if (status == F_signal || F_status_is_error(status)) {
        controller_lock_error_critical_print(main.data->error, F_status_set_fine(status), F_false, main.thread);

        f_thread_unlock(&process->active);

        return status;
      }

      if (!action || (options_force & controller_process_option_asynchronous)) {
        process->state = controller_process_state_done;
      }
      else {
        process->state = controller_process_state_idle;
      }

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
  f_status_t controller_rule_process_do(const uint8_t options_force, controller_process_t *process) {

    f_status_t status_lock = F_none;

    controller_main_t main = controller_macro_main_t_initialize((controller_data_t *) process->main_data, (controller_setting_t *) process->main_setting, (controller_thread_t *) process->main_thread);

    // the process and active locks shall be held for the duration of this processing (aside from switching between read to/from write).
    if (options_force & controller_process_option_asynchronous) {
      status_lock = controller_lock_read_process(process, main.thread, &process->active);

      if (status_lock == F_signal || F_status_is_error(status_lock)) {
        controller_lock_error_critical_print(main.data->error, F_status_set_fine(status_lock), F_true, main.thread);

        return status_lock;
      }
    }

    status_lock = controller_lock_read_process(process, main.thread, &process->lock);

    if (status_lock == F_signal || F_status_is_error(status_lock)) {
      controller_lock_error_critical_print(main.data->error, F_status_set_fine(status_lock), F_true, main.thread);

      if (options_force & controller_process_option_asynchronous) {
        f_thread_unlock(&process->active);
      }

      return status_lock;
    }

    f_status_t status = F_none;

    f_array_length_t id_rule = 0;

    const f_array_length_t used_original_stack = process->stack.used;

    status_lock = controller_lock_read_process(process, main.thread, &main.thread->lock.rule);

    if (status_lock == F_signal || F_status_is_error(status_lock)) {
      controller_lock_error_critical_print(main.data->error, F_status_set_fine(status_lock), F_true, main.thread);

      f_thread_unlock(&process->lock);

      if (options_force & controller_process_option_asynchronous) {
        f_thread_unlock(&process->active);
      }

      return status_lock;
    }

    if (controller_rule_find(process->rule.alias, main.setting->rules, &id_rule) == F_true) {
      f_thread_unlock(&process->lock);

      status_lock = controller_lock_write_process(process, main.thread, &process->lock);

      if (status_lock == F_signal || F_status_is_error(status_lock)) {
        controller_lock_error_critical_print(main.data->error, F_status_set_fine(status_lock), F_false, main.thread);

        f_thread_unlock(&main.thread->lock.rule);

        if (options_force & controller_process_option_asynchronous) {
          f_thread_unlock(&process->active);
        }

        return status_lock;
      }

      controller_rule_delete_simple(&process->rule);

      status = controller_rule_copy(main.setting->rules.array[id_rule], &process->rule);

      f_thread_unlock(&process->lock);

      status_lock = controller_lock_read_process(process, main.thread, &process->lock);

      if (status_lock == F_signal || F_status_is_error(status_lock)) {
        controller_lock_error_critical_print(main.data->error, F_status_set_fine(status_lock), F_true, main.thread);

        f_thread_unlock(&main.thread->lock.rule);

        if (options_force & controller_process_option_asynchronous) {
          f_thread_unlock(&process->active);
        }

        return status_lock;
      }

      f_thread_unlock(&main.thread->lock.rule);

      if (F_status_is_error(status)) {
        controller_entry_error_print(main.data->error, process->cache.action, F_status_set_fine(status), "controller_rule_copy", F_true, main.thread);
      }
      else if (!process->action) {

        // this is a "consider" Action, so do not actually execute the rule.
        f_thread_unlock(&process->lock);

        if (options_force & controller_process_option_asynchronous) {
          f_thread_unlock(&process->active);
        }

        return F_process_not;
      }
      else {
        for (f_array_length_t i = 0; i < process->stack.used && controller_thread_is_enabled_process(process, main.thread); ++i) {

          if (process->stack.array[i] == id_rule) {
            if (main.data->error.verbosity != f_console_verbosity_quiet) {
              f_thread_mutex_lock(&main.thread->lock.print);

              fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
              fprintf(main.data->error.to.stream, "%s%sThe rule '", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s);
              fprintf(main.data->error.to.stream, "%s%s%s%s", main.data->error.context.after->string, main.data->error.notable.before->string, process->rule.alias.string, main.data->error.notable.after->string);
              fprintf(main.data->error.to.stream, "%s' is already on the execution dependency stack, this recursion is prohibited.%s%c", main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);

              controller_rule_error_print_cache(main.data->error, process->cache.action, F_true);

              controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);
            }

            // never continue on circular recursion errors even in simulate mode.
            status = F_status_set_error(F_recurse);

            break;
          }
        } // for

        if (!controller_thread_is_enabled_process(process, main.thread)) {
          f_thread_unlock(&process->lock);

          if (options_force & controller_process_option_asynchronous) {
            f_thread_unlock(&process->active);
          }

          return F_signal;
        }

        if (F_status_is_error_not(status)) {
          status = f_type_array_lengths_increase(&process->stack);

          if (F_status_is_error(status)) {
            controller_entry_error_print(main.data->error, process->cache.action, F_status_set_fine(status), "f_type_array_lengths_increase", F_true, main.thread);
          }
          else {
            f_thread_unlock(&process->lock);

            status_lock = controller_lock_write_process(process, main.thread, &process->lock);

            if (status_lock == F_signal || F_status_is_error(status_lock)) {
              controller_lock_error_critical_print(main.data->error, F_status_set_fine(status_lock), F_false, main.thread);

              if (options_force & controller_process_option_asynchronous) {
                f_thread_unlock(&process->active);
              }

              return status_lock;
            }

            process->stack.array[process->stack.used++] = id_rule;

            f_thread_unlock(&process->lock);

            status_lock = controller_lock_read_process(process, main.thread, &process->lock);

            if (status_lock == F_signal || F_status_is_error(status_lock)) {
              controller_lock_error_critical_print(main.data->error, F_status_set_fine(status_lock), F_true, main.thread);

              if (options_force & controller_process_option_asynchronous) {
                f_thread_unlock(&process->active);
              }

              return status_lock;
            }
          }
        }
      }

      if (F_status_is_error_not(status)) {
        status = controller_rule_process(main, process);
      }
    }
    else {
      f_thread_unlock(&main.thread->lock.rule);

      status = F_status_set_error(F_found_not);

      if (main.data->error.verbosity != f_console_verbosity_quiet) {
        f_thread_mutex_lock(&main.thread->lock.print);

        controller_rule_item_error_print_rule_not_loaded(main.data->error, process->rule.alias.string);
        controller_rule_error_print_cache(main.data->error, process->cache.action, F_false);

        controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);
      }
    }

    if (status == F_child) {
      f_thread_unlock(&process->lock);

      if (options_force & controller_process_option_asynchronous) {
        f_thread_unlock(&process->active);
      }

      return status;
    }

    status_lock = controller_lock_write_process(process, main.thread, &main.thread->lock.rule);

    if (status_lock == F_signal || F_status_is_error(status_lock)) {
      controller_lock_error_critical_print(main.data->error, F_status_set_fine(status_lock), F_false, main.thread);

      if (F_status_set_fine(status) != F_lock) {
        f_thread_unlock(&process->lock);
      }

      if (options_force & controller_process_option_asynchronous) {
        f_thread_unlock(&process->active);
      }

      return status_lock;
    }

    if (controller_rule_find(process->rule.alias, main.setting->rules, &id_rule) == F_true) {
      if (F_status_set_fine(status) == F_lock) {
        main.setting->rules.array[id_rule].status = F_status_set_error(F_failure);
      }
      else {
        main.setting->rules.array[id_rule].status = status;
      }
    }

    f_thread_unlock(&main.thread->lock.rule);

    if (F_status_set_fine(status) != F_lock) {
      f_thread_unlock(&process->lock);
    }

    if (status == F_signal || F_status_set_fine(status) == F_lock && !controller_thread_is_enabled_process(process, main.thread)) {
      if (options_force & controller_process_option_asynchronous) {
        f_thread_unlock(&process->active);
      }

      return F_signal;
    }

    status_lock = controller_lock_write_process(process, main.thread, &process->lock);

    if (status_lock == F_signal || F_status_is_error(status_lock)) {
      controller_lock_error_critical_print(main.data->error, F_status_set_fine(status_lock), F_false, main.thread);

      if (options_force & controller_process_option_asynchronous) {
        f_thread_unlock(&process->active);
      }

      return status_lock;
    }

    if (options_force & controller_process_option_asynchronous) {
      process->state = controller_process_state_done;
    }
    else {
      process->state = controller_process_state_idle;
    }

    process->stack.used = used_original_stack;

    // inform all things waiting that the process has finished running.
    f_thread_mutex_lock(&process->wait_lock);
    f_thread_condition_signal_all(&process->wait);
    f_thread_mutex_unlock(&process->wait_lock);

    f_thread_unlock(&process->lock);

    if (options_force & controller_process_option_asynchronous) {
      f_thread_unlock(&process->active);
    }

    if (controller_thread_is_enabled_process(process, main.thread)) {
      return status;
    }

    return F_signal;
  }
#endif // _di_controller_rule_process_do_

#ifndef _di_controller_rule_read_
  f_status_t controller_rule_read(const bool is_normal, const f_string_static_t rule_id, controller_main_t main, controller_cache_t *cache, controller_rule_t *rule) {
    f_status_t status = F_none;

    bool for_item = F_true;

    rule->status = F_known_not;

    // @todo: timeouts may be passed from entry, consider to or not to initialize in a more consistent manner.
    //rule->timeout_kill = 2;
    //rule->timeout_start = 2;
    //rule->timeout_stop = 2;

    rule->has = 0;
    rule->group = 0;
    rule->user = 0;
    rule->nice = 0;

    f_macro_time_spec_t_clear(rule->timestamp);

    rule->alias.used = 0;
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

    status = f_string_dynamic_append_nulless(rule_id, &rule->alias);

    if (F_status_is_error(status)) {
      controller_error_print(main.data->error, F_status_set_fine(status), "f_string_dynamic_append_nulless", F_true, main.thread);
    }
    else {

      status = f_string_dynamic_terminate_after(&rule->alias);

      if (F_status_is_error(status)) {
        controller_error_print(main.data->error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true, main.thread);
      }
      else {
        status = controller_file_load(F_true, controller_string_rules_s, rule->alias, controller_string_rule_s, controller_string_rules_length, controller_string_rule_length, main, cache);
      }
    }

    if (F_status_is_error_not(status)) {
      rule->timestamp = cache->timestamp;

      if (cache->buffer_file.used) {
        f_string_range_t range = f_macro_string_range_t_initialize(cache->buffer_file.used);

        status = fll_fss_basic_list_read(cache->buffer_file, &range, &cache->object_items, &cache->content_items, &cache->delimits, 0, &cache->comments);

        if (F_status_is_error(status)) {
          controller_error_print(main.data->error, F_status_set_fine(status), "fll_fss_basic_list_read", F_true, main.thread);
        }
        else {
          status = fl_fss_apply_delimit(cache->delimits, &cache->buffer_file);

          if (F_status_is_error(status)) {
            controller_error_print(main.data->error, F_status_set_fine(status), "fl_fss_apply_delimit", F_true, main.thread);
          }
        }
      }
    }

    if (F_status_is_error_not(status) && cache->object_items.used) {
      status = controller_rule_items_increase_by(cache->object_items.used, &rule->items);

      if (F_status_is_error(status)) {
        controller_error_print(main.data->error, F_status_set_fine(status), "controller_rule_items_increase_by", F_true, main.thread);
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
            controller_error_print(main.data->error, F_status_set_fine(status), "f_fss_count_lines", F_true, main.thread);
            break;
          }

          rule->items.array[rule->items.used].line = ++cache->action.line_item;

          status = controller_string_dynamic_rip_nulless_terminated(cache->buffer_file, cache->object_items.array[i], &cache->action.name_item);

          if (F_status_is_error(status)) {
            controller_error_print(main.data->error, F_status_set_fine(status), "controller_string_dynamic_rip_nulless_terminated", F_true, main.thread);
            break;
          }

          if (fl_string_dynamic_compare_string(controller_string_setting_s, cache->action.name_item, controller_string_setting_length) == F_equal_to) {
            rule->items.array[rule->items.used].type = 0;
          }
          else if (fl_string_dynamic_compare_string(controller_string_command_s, cache->action.name_item, controller_string_command_length) == F_equal_to) {
            rule->items.array[rule->items.used].type = controller_rule_item_type_command;
          }
          else if (fl_string_dynamic_compare_string(controller_string_script_s, cache->action.name_item, controller_string_script_length) == F_equal_to) {
            rule->items.array[rule->items.used].type = controller_rule_item_type_script;
          }
          else if (fl_string_dynamic_compare_string(controller_string_service_s, cache->action.name_item, controller_string_service_length) == F_equal_to) {
            rule->items.array[rule->items.used].type = controller_rule_item_type_service;
          }
          else if (fl_string_dynamic_compare_string(controller_string_utility_s, cache->action.name_item, controller_string_utility_length) == F_equal_to) {
            rule->items.array[rule->items.used].type = controller_rule_item_type_utility;
          }
          else {
            if (main.data->warning.verbosity == f_console_verbosity_debug) {
              f_thread_mutex_lock(&main.thread->lock.print);

              fprintf(main.data->warning.to.stream, "%c", f_string_eol_s[0]);
              fprintf(main.data->warning.to.stream, "%s%sUnknown rule item '", main.data->warning.context.before->string, main.data->warning.prefix ? main.data->warning.prefix : f_string_empty_s);
              fprintf(main.data->warning.to.stream, "%s%s", main.data->warning.context.after->string, main.data->warning.notable.before->string);
              f_print_dynamic(main.data->warning.to.stream, cache->action.name_item);
              fprintf(main.data->warning.to.stream, "%s", main.data->warning.notable.after->string);
              fprintf(main.data->warning.to.stream, "%s'.%s%c", main.data->warning.context.before->string, main.data->warning.context.after->string, f_string_eol_s[0]);

              controller_rule_error_print_cache(main.data->warning, cache->action, F_true);

              f_thread_mutex_lock(&main.thread->lock.print);
            }

            continue;
          }

          status = f_string_dynamic_partial_append(cache->buffer_file, cache->content_items.array[i].array[0], &cache->buffer_item);

          if (F_status_is_error(status)) {
            controller_error_print(main.data->error, F_status_set_fine(status), "f_string_dynamic_partial_append", F_true, main.thread);
            break;
          }

          status = f_string_dynamic_terminate_after(&cache->buffer_item);

          if (F_status_is_error(status)) {
            controller_error_print(main.data->error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true, main.thread);
            break;
          }

          if (rule->items.array[rule->items.used].type) {
            status = controller_rule_item_read(main, cache, &rule->items.array[rule->items.used]);
            if (F_status_is_error(status)) break;

            rule->items.used++;
          }
          else {
            for_item = F_false;

            status = controller_rule_setting_read(main, *main.setting, cache, rule);

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
      controller_rule_item_error_print(main.data->error, cache->action, for_item, main.thread);

      rule->status = controller_status_simplify_error(F_status_set_fine(status));
      return rule->status;
    }

    return F_none;
  }
#endif // _di_controller_rule_read_

#ifndef _di_controller_rule_setting_read_
  f_status_t controller_rule_setting_read(const controller_main_t main, const controller_setting_t setting, controller_cache_t *cache, controller_rule_t *rule) {

    f_status_t status = F_none;
    f_status_t status_return = F_none;

    f_string_range_t range = f_macro_string_range_t_initialize(cache->buffer_item.used);
    f_string_range_t range2 = f_string_range_t_initialize;

    status = fll_fss_extended_read(cache->buffer_item, &range, &cache->object_actions, &cache->content_actions, 0, 0, &cache->delimits, 0);

    if (F_status_is_error(status)) {
      controller_rule_error_print(main.data->error, cache->action, F_status_set_fine(status), "fll_fss_extended_read", F_true, F_false, main.thread);

      return status;
    }

    f_array_length_t path_original_length = 0;
    f_string_dynamic_t *setting_value = 0;
    f_string_dynamics_t *setting_values = 0;
    f_string_maps_t *setting_maps = 0;

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    uint8_t type = 0;

    // save the current name item and line number to restore on return.
    const f_array_length_t line_item = cache->action.line_item;
    const f_array_length_t length_name_item = cache->action.name_item.used;

    char name_item[length_name_item];
    name_item[length_name_item] = 0;

    memcpy(name_item, cache->action.name_item.string, length_name_item);

    for (; i < cache->content_actions.used; ++i, type = 0) {

      // name_action is used to store all setting values for a single setting.
      cache->action.name_action.used = 0;

      // name_item is used to store the setting name.
      cache->action.name_item.used = 0;

      status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->object_actions.array[i], &cache->action.name_item);

      if (F_status_is_error(status)) {
        controller_rule_error_print(main.data->error, cache->action, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, F_false, main.thread);
      }
      else {
        status = f_string_dynamic_terminate_after(&cache->action.name_item);

        if (F_status_is_error(status)) {
          controller_rule_error_print(main.data->error, cache->action, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true, F_false, main.thread);
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
        cache->action.line_item = line_item;
        f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

        cache->action.line_action = ++cache->action.line_item;

        controller_rule_item_error_print(main.data->error, cache->action, F_false, main.thread);

        continue;
      }

      if (fl_string_dynamic_compare_string(controller_string_affinity_s, cache->action.name_item, controller_string_affinity_length) == F_equal_to) {
        type = controller_rule_setting_type_affinity;
      }
      else if (fl_string_dynamic_compare_string(controller_string_capability_s, cache->action.name_item, controller_string_capability_length) == F_equal_to) {
        type = controller_rule_setting_type_capability;
      }
      else if (fl_string_dynamic_compare_string(controller_string_control_group_s, cache->action.name_item, controller_string_control_group_length) == F_equal_to) {
        type = controller_rule_setting_type_control_group;
      }
      else if (fl_string_dynamic_compare_string(controller_string_define_s, cache->action.name_item, controller_string_define_length) == F_equal_to) {
        type = controller_rule_setting_type_define;
      }
      else if (fl_string_dynamic_compare_string(controller_string_environment_s, cache->action.name_item, controller_string_environment_length) == F_equal_to) {
        type = controller_rule_setting_type_environment;
      }
      else if (fl_string_dynamic_compare_string(controller_string_group_s, cache->action.name_item, controller_string_group_length) == F_equal_to) {
        type = controller_rule_setting_type_group;
      }
      else if (fl_string_dynamic_compare_string(controller_string_limit_s, cache->action.name_item, controller_string_limit_length) == F_equal_to) {
        type = controller_rule_setting_type_limit;
      }
      else if (fl_string_dynamic_compare_string(controller_string_name_s, cache->action.name_item, controller_string_name_length) == F_equal_to) {
        type = controller_rule_setting_type_name;
      }
      else if (fl_string_dynamic_compare_string(controller_string_need_s, cache->action.name_item, controller_string_need_length) == F_equal_to) {
        type = controller_rule_setting_type_need;
      }
      else if (fl_string_dynamic_compare_string(controller_string_nice_s, cache->action.name_item, controller_string_nice_length) == F_equal_to) {
        type = controller_rule_setting_type_nice;
      }
      else if (fl_string_dynamic_compare_string(controller_string_parameter_s, cache->action.name_item, controller_string_parameter_length) == F_equal_to) {
        type = controller_rule_setting_type_parameter;
      }
      else if (fl_string_dynamic_compare_string(controller_string_path_s, cache->action.name_item, controller_string_path_length) == F_equal_to) {
        type = controller_rule_setting_type_path;
      }
      else if (fl_string_dynamic_compare_string(controller_string_scheduler_s, cache->action.name_item, controller_string_scheduler_length) == F_equal_to) {
        type = controller_rule_setting_type_scheduler;
      }
      else if (fl_string_dynamic_compare_string(controller_string_script_s, cache->action.name_item, controller_string_script_length) == F_equal_to) {
        type = controller_rule_setting_type_script;
      }
      else if (fl_string_dynamic_compare_string(controller_string_user_s, cache->action.name_item, controller_string_user_length) == F_equal_to) {
        type = controller_rule_setting_type_user;
      }
      else if (fl_string_dynamic_compare_string(controller_string_want_s, cache->action.name_item, controller_string_want_length) == F_equal_to) {
        type = controller_rule_setting_type_want;
      }
      else if (fl_string_dynamic_compare_string(controller_string_wish_s, cache->action.name_item, controller_string_wish_length) == F_equal_to) {
        type = controller_rule_setting_type_wish;
      }
      else {
        if (main.data->warning.verbosity == f_console_verbosity_debug) {
          f_thread_mutex_lock(&main.thread->lock.print);

          fprintf(main.data->warning.to.stream, "%c", f_string_eol_s[0]);
          fprintf(main.data->warning.to.stream, "%s%sUnknown rule setting '", main.data->warning.context.before->string, main.data->warning.prefix ? main.data->warning.prefix : f_string_empty_s);
          fprintf(main.data->warning.to.stream, "%s%s", main.data->warning.context.after->string, main.data->warning.notable.before->string);
          f_print_dynamic(main.data->warning.to.stream, cache->action.name_item);
          fprintf(main.data->warning.to.stream, "%s", main.data->warning.notable.after->string);
          fprintf(main.data->warning.to.stream, "%s'.%s%c", main.data->warning.context.before->string, main.data->warning.context.after->string, f_string_eol_s[0]);

          // get the current line number within the settings item.
          cache->action.line_item = line_item;
          f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

          cache->action.line_action = ++cache->action.line_item;

          controller_rule_error_print_cache(main.data->warning, cache->action, F_false);

          controller_print_unlock_flush(main.data->warning.to.stream, &main.thread->lock.print);
        }

        continue;
      }

      if (!cache->content_actions.array[i].used) {
        if (main.data->warning.verbosity == f_console_verbosity_debug) {
          f_thread_mutex_lock(&main.thread->lock.print);

          fprintf(main.data->warning.to.stream, "%c", f_string_eol_s[0]);
          fprintf(main.data->warning.to.stream, "%s%sEmpty rule setting.%s%c", main.data->warning.context.before->string, main.data->warning.prefix ? main.data->warning.prefix : f_string_empty_s, main.data->warning.context.after->string, f_string_eol_s[0]);

          // get the current line number within the settings item.
          cache->action.line_item = line_item;
          f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

          cache->action.line_action = ++cache->action.line_item;

          controller_rule_error_print_cache(main.data->warning, cache->action, F_false);

          controller_print_unlock_flush(main.data->warning.to.stream, &main.thread->lock.print);
        }

        continue;
      }

      range2.start = cache->content_actions.array[i].array[0].start;
      range2.stop = cache->content_actions.array[i].array[cache->content_actions.array[i].used - 1].stop;

      status = f_string_dynamic_partial_append_nulless(cache->buffer_item, range2, &cache->action.name_action);

      if (F_status_is_error(status)) {
        controller_rule_error_print(main.data->error, cache->action, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, F_false, main.thread);
      }
      else {
        status = f_string_dynamic_terminate_after(&cache->action.name_action);

        if (F_status_is_error(status)) {
          controller_rule_error_print(main.data->error, cache->action, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true, F_false, main.thread);
        }
      }

      if (F_status_is_error(status)) {

        // get the current line number within the settings item.
        cache->action.line_item = line_item;
        f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

        cache->action.line_action = ++cache->action.line_item;

        controller_rule_item_error_print(main.data->error, cache->action, F_false, main.thread);

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
          if (main.data->error.verbosity != f_console_verbosity_quiet) {

            // get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

            cache->action.line_action = ++cache->action.line_item;

            f_thread_mutex_lock(&main.thread->lock.print);

            fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
            fprintf(main.data->error.to.stream, "%s%sRule setting requires one or more Content.%s%c", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s, main.data->error.context.after->string, f_string_eol_s[0]);

            controller_rule_error_print_cache(main.data->error, cache->action, F_false);

            controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);
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
            controller_rule_error_print(main.data->error, cache->action, F_status_set_fine(status), "f_macro_int32s_t_resize", F_true, F_false, main.thread);
            break;
          }

          status = fl_conversion_string_to_number_signed(cache->buffer_item.string, cache->content_actions.array[i].array[j], &number);

          if (F_status_is_error(status)) {
            status = F_status_set_fine(status);

            if (status == F_data_not || status == F_number || status == F_number_overflow || status == F_number_underflow) {
              if (main.data->error.verbosity != f_console_verbosity_quiet) {

                if (status == F_number_overflow || status == F_number_underflow) {
                  f_thread_mutex_lock(&main.thread->lock.print);

                  fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
                  fprintf(main.data->error.to.stream, "%s%sRule setting has an unsupported number '", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s);
                  fprintf(main.data->error.to.stream, "%s%s", main.data->error.context.after->string, main.data->error.notable.before->string);
                  f_print_dynamic_partial(main.data->error.to.stream, cache->buffer_item, cache->content_actions.array[i].array[j]);
                  fprintf(main.data->error.to.stream, "%s%s', the number is too large for this system.%s%c", main.data->error.notable.after->string, main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);

                  controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);
                }
                else {
                  f_thread_mutex_lock(&main.thread->lock.print);

                  fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
                  fprintf(main.data->error.to.stream, "%s%sRule setting has an invalid number '", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s);
                  fprintf(main.data->error.to.stream, "%s%s", main.data->error.context.after->string, main.data->error.notable.before->string);
                  f_print_dynamic_partial(main.data->error.to.stream, cache->buffer_item, cache->content_actions.array[i].array[j]);
                  fprintf(main.data->error.to.stream, "%s%s', only whole numbers are allowed for an affinity value.%s%c", main.data->error.notable.after->string, main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);

                  controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);
                }

                // get the current line number within the settings item.
                cache->action.line_item = line_item;
                f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

                cache->action.line_action = ++cache->action.line_item;

                controller_rule_item_error_print(main.data->error, cache->action, F_false, main.thread);
              }

              status = F_status_set_error(F_valid_not);

              if (F_status_is_error_not(status_return)) {
                status_return = status;
              }
            }
            else {
              controller_rule_error_print(main.data->error, cache->action, F_status_set_fine(status), "fl_conversion_string_to_number_signed", F_true, F_false, main.thread);

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
          if (main.data->error.verbosity != f_console_verbosity_quiet) {

            // get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

            cache->action.line_action = ++cache->action.line_item;

            f_thread_mutex_lock(&main.thread->lock.print);

            fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
            fprintf(main.data->error.to.stream, "%s%sRule setting requires exactly two Content.%s%c", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s, main.data->error.context.after->string, f_string_eol_s[0]);

            controller_rule_error_print_cache(main.data->error, cache->action, F_false);

            controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);
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
          controller_rule_error_print(main.data->error, cache->action, F_status_set_fine(status), "f_string_maps_increase", F_true, F_false, main.thread);

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

          controller_rule_item_error_print(main.data->error, cache->action, F_false, main.thread);

          continue;
        }

        setting_maps->array[setting_maps->used].name.used = 0;
        setting_maps->array[setting_maps->used].value.used = 0;

        status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[0], &setting_maps->array[setting_maps->used].name);

        if (F_status_is_error(status)) {
          controller_rule_error_print(main.data->error, cache->action, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, F_false, main.thread);

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

          controller_rule_item_error_print(main.data->error, cache->action, F_false, main.thread);

          continue;
        }

        status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[1], &setting_maps->array[setting_maps->used].value);

        if (F_status_is_error(status)) {
          controller_rule_error_print(main.data->error, cache->action, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, F_false, main.thread);
        }
        else {
          status = f_string_dynamic_terminate_after(&setting_maps->array[setting_maps->used].value);

          if (F_status_is_error(status)) {
            controller_rule_error_print(main.data->error, cache->action, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true, F_false, main.thread);
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
          cache->action.line_item = line_item;
          f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

          cache->action.line_action = ++cache->action.line_item;

          controller_rule_item_error_print(main.data->error, cache->action, F_false, main.thread);

          continue;
        }

        setting_maps->used++;
        continue;
      }

      if (type == controller_rule_setting_type_control_group) {

        if (cache->content_actions.array[i].used < 2 || rule->has & controller_rule_has_control_group) {
          if (main.data->error.verbosity != f_console_verbosity_quiet) {
            f_thread_mutex_lock(&main.thread->lock.print);

            fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
            fprintf(main.data->error.to.stream, "%s%sRule setting requires two or more Content.%s%c", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s, main.data->error.context.after->string, f_string_eol_s[0]);

            // get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

            cache->action.line_action = ++cache->action.line_item;

            controller_rule_error_print_cache(main.data->error, cache->action, F_false);

            controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);
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
          if (main.data->error.verbosity != f_console_verbosity_quiet) {
            f_thread_mutex_lock(&main.thread->lock.print);

            fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
            fprintf(main.data->error.to.stream, "%s%sRule setting has an unknown option '", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s);
            fprintf(main.data->error.to.stream, "%s%s", main.data->error.context.after->string, main.data->error.notable.before->string);
            f_print_dynamic_partial(main.data->error.to.stream, cache->buffer_item, cache->content_actions.array[i].array[0]);
            fprintf(main.data->error.to.stream, "%s%s'.%s%c", main.data->error.notable.after->string, main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);

            // get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

            cache->action.line_action = ++cache->action.line_item;

            controller_rule_error_print_cache(main.data->error, cache->action, F_false);

            controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);
          }

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        rule->control_group.path.used = 0;

        status = f_string_dynamic_append(main.setting->path_control, &rule->control_group.path);

        if (F_status_is_error(status)) {
          controller_rule_error_print(main.data->error, cache->action, F_status_set_fine(status), "f_string_dynamic_append", F_true, F_false, main.thread);
        }
        else {
          rule->control_group.groups.used = 0;

          for (j = 1; j < cache->content_actions.array[i].used; ++j) {

            status = f_string_dynamics_increase(&rule->control_group.groups);

            if (F_status_is_error(status)) {
              controller_rule_error_print(main.data->error, cache->action, F_status_set_fine(status), "f_string_dynamics_increase", F_true, F_false, main.thread);
              break;
            }

            rule->control_group.groups.array[rule->control_group.groups.used].used = 0;

            status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[j], &rule->control_group.groups.array[rule->control_group.groups.used]);

            if (F_status_is_error(status)) {
              controller_rule_error_print(main.data->error, cache->action, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, F_false, main.thread);
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
          cache->action.line_item = line_item;
          f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

          cache->action.line_action = ++cache->action.line_item;

          controller_rule_item_error_print(main.data->error, cache->action, F_false, main.thread);

          continue;
        }

        rule->has |= controller_rule_has_control_group;

        continue;
      }

      if (type == controller_rule_setting_type_limit) {
        if (cache->content_actions.array[i].used != 3) {

          if (main.data->error.verbosity != f_console_verbosity_quiet) {
            f_thread_mutex_lock(&main.thread->lock.print);

            fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
            fprintf(main.data->error.to.stream, "%s%sRule setting requires three Content.%s%c", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s, main.data->error.context.after->string, f_string_eol_s[0]);

            // get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

            cache->action.line_action = ++cache->action.line_item;

            controller_rule_error_print_cache(main.data->error, cache->action, F_false);

            controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);
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
          if (main.data->error.verbosity == f_console_verbosity_debug) {
            f_thread_mutex_lock(&main.thread->lock.print);

            fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
            fprintf(main.data->error.to.stream, "%s%sUnknown resource limit type '", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s);
            fprintf(main.data->error.to.stream, "%s%s", main.data->error.context.after->string, main.data->error.notable.before->string);
            f_print_dynamic(main.data->error.to.stream, cache->action.name_action);
            fprintf(main.data->error.to.stream, "%s", main.data->error.notable.after->string);
            fprintf(main.data->error.to.stream, "%s'.%s%c", main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);

            // get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

            cache->action.line_action = ++cache->action.line_item;

            controller_rule_error_print_cache(main.data->error, cache->action, F_true);

            controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);
          }

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        for (j = 0; j < rule->limits.used; ++j) {

          if (type == rule->limits.array[j].type) {
            if (main.data->error.verbosity != f_console_verbosity_quiet) {
              f_thread_mutex_lock(&main.thread->lock.print);

              fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
              fprintf(main.data->error.to.stream, "%s%sThe resource limit type is already specified.%s%c", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s, main.data->error.context.after->string, f_string_eol_s[0]);
              fprintf(main.data->error.to.stream, "%s%s", main.data->error.context.after->string, main.data->error.notable.before->string);

              // get the current line number within the settings item.
              cache->action.line_item = line_item;
              f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

              cache->action.line_action = ++cache->action.line_item;

              controller_rule_error_print_cache(main.data->error, cache->action, F_false);

              controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);
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
          controller_rule_error_print(main.data->error, cache->action, F_status_set_fine(status), "f_limit_sets_increase", F_true, F_false, main.thread);

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

          controller_rule_item_error_print(main.data->error, cache->action, F_false, main.thread);

          continue;
        }

        f_number_signed_t number = 0;

        for (j = 1; j < 3; ++j, number = 0) {

          status = fl_conversion_string_to_number_signed(cache->buffer_item.string, cache->content_actions.array[i].array[j], &number);

          if (F_status_is_error(status)) {
            status = F_status_set_fine(status);

            if (status == F_data_not || status == F_number || status == F_number_overflow || status == F_number_underflow) {

              if (main.data->error.verbosity != f_console_verbosity_quiet) {
                f_thread_mutex_lock(&main.thread->lock.print);

                if (status == F_number_overflow || status == F_number_underflow) {
                  fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
                  fprintf(main.data->error.to.stream, "%s%sRule setting has an unsupported number '", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s);
                  fprintf(main.data->error.to.stream, "%s%s", main.data->error.context.after->string, main.data->error.notable.before->string);
                  f_print_dynamic_partial(main.data->error.to.stream, cache->buffer_item, cache->content_actions.array[i].array[j]);
                  fprintf(main.data->error.to.stream, "%s%s', the number is too large for this system.%s%c", main.data->error.notable.after->string, main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);
                }
                else {
                  fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
                  fprintf(main.data->error.to.stream, "%s%sRule setting has an invalid number '", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s);
                  fprintf(main.data->error.to.stream, "%s%s", main.data->error.context.after->string, main.data->error.notable.before->string);
                  f_print_dynamic_partial(main.data->error.to.stream, cache->buffer_item, cache->content_actions.array[i].array[j]);
                  fprintf(main.data->error.to.stream, "%s%s', only whole numbers are allowed for a resource limit value.%s%c", main.data->error.notable.after->string, main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);
                }

                // get the current line number within the settings item.
                cache->action.line_item = line_item;
                f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

                cache->action.line_action = ++cache->action.line_item;

                controller_rule_error_print_cache(main.data->error, cache->action, F_false);

                controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);
              }

              status = F_status_set_error(F_valid_not);

              if (F_status_is_error_not(status_return)) {
                status_return = status;
              }
            }
            else {
              controller_rule_error_print(main.data->error, cache->action, F_status_set_fine(status), "fl_conversion_string_to_number_signed", F_true, F_false, main.thread);

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
          if (main.data->error.verbosity != f_console_verbosity_quiet) {
            f_thread_mutex_lock(&main.thread->lock.print);

            fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
            fprintf(main.data->error.to.stream, "%s%sRule setting requires exactly one Content.%s%c", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s, main.data->error.context.after->string, f_string_eol_s[0]);

            // get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

            cache->action.line_action = ++cache->action.line_item;

            controller_rule_error_print_cache(main.data->error, cache->action, F_false);

            controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);
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
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

            cache->action.line_action = ++cache->action.line_item;

            controller_rule_item_error_print(main.data->error, cache->action, F_false, main.thread);

            continue;
          }

          if (type == controller_rule_setting_type_name || type == controller_rule_setting_type_script) {
            status = controller_validate_has_graph(*setting_value);

            if (status == F_false || F_status_set_fine(status) == F_complete_not_utf) {

              if (status == F_false) {
                if (main.data->error.verbosity != f_console_verbosity_quiet) {
                  f_thread_mutex_lock(&main.thread->lock.print);

                  fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
                  fprintf(main.data->error.to.stream, "%s%sRule setting has an invalid name '", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s);
                  fprintf(main.data->error.to.stream, "%s%s", main.data->error.context.after->string, main.data->error.notable.before->string);
                  f_print_dynamic(main.data->error.to.stream, *setting_value);
                  fprintf(main.data->error.to.stream, "%s", main.data->error.notable.after->string);
                  fprintf(main.data->error.to.stream, "%s', there must be at least 1 graph character.%s%c", main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);

                  // get the current line number within the settings item.
                  cache->action.line_item = line_item;
                  f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

                  cache->action.line_action = ++cache->action.line_item;

                  controller_rule_error_print_cache(main.data->error, cache->action, F_false);

                  controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);
                }

                if (F_status_is_error_not(status_return)) {
                  status_return = F_status_set_error(F_valid_not);
                }
              }
              else {
                f_thread_mutex_lock(&main.thread->lock.print);

                // this function should only return F_complete_not_utf on error.
                controller_rule_error_print(main.data->error, cache->action, F_complete_not_utf, "controller_validate_has_graph", F_true, F_false, main.thread);

                controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);

                if (F_status_is_error_not(status_return)) {
                  status_return = status;
                }
              }

              setting_value->used = 0;

              // get the current line number within the settings item.
              cache->action.line_item = line_item;
              f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

              cache->action.line_action = ++cache->action.line_item;

              controller_rule_item_error_print(main.data->error, cache->action, F_false, main.thread);

              continue;
            }
          }
        }
        else if (type == controller_rule_setting_type_path) {
          status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[0], setting_value);

          if (F_status_is_error(status)) {
            controller_rule_error_print(main.data->error, cache->action, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, F_false, main.thread);
          }
          else {
            status = f_string_dynamic_terminate_after(setting_value);

            if (F_status_is_error(status)) {
              controller_rule_error_print(main.data->error, cache->action, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true, F_false, main.thread);
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

            controller_rule_item_error_print(main.data->error, cache->action, F_false, main.thread);

            continue;
          }
        }

        continue;
      }

      if (type == controller_rule_setting_type_scheduler) {

        if (cache->content_actions.array[i].used < 1 || cache->content_actions.array[i].used > 2 || rule->has & controller_rule_has_scheduler) {
          if (main.data->error.verbosity != f_console_verbosity_quiet) {
            f_thread_mutex_lock(&main.thread->lock.print);

            fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
            fprintf(main.data->error.to.stream, "%s%sRule setting requires either one or two Content.%s%c", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s, main.data->error.context.after->string, f_string_eol_s[0]);

            // get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

            cache->action.line_action = ++cache->action.line_item;

            controller_rule_error_print_cache(main.data->error, cache->action, F_false);

            controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);
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
          if (main.data->error.verbosity != f_console_verbosity_quiet) {
            f_thread_mutex_lock(&main.thread->lock.print);

            fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
            fprintf(main.data->error.to.stream, "%s%sRule setting has an unknown scheduler '", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s);
            fprintf(main.data->error.to.stream, "%s%s", main.data->error.context.after->string, main.data->error.notable.before->string);
            f_print_dynamic_partial(main.data->error.to.stream, cache->buffer_item, cache->content_actions.array[i].array[0]);
            fprintf(main.data->error.to.stream, "%s%s'.%s%c", main.data->error.notable.after->string, main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);

            // get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

            cache->action.line_action = ++cache->action.line_item;

            controller_rule_error_print_cache(main.data->error, cache->action, F_false);

            controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);
          }

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        if (cache->content_actions.array[i].used > 1) {
          const bool zero_only = rule->scheduler.policy == SCHED_BATCH || rule->scheduler.policy == SCHED_IDLE || rule->scheduler.policy == SCHED_OTHER;

          f_number_signed_t number = 0;

          status = fl_conversion_string_to_number_signed(cache->buffer_item.string, cache->content_actions.array[i].array[1], &number);

          if (F_status_is_error(status) || (zero_only && number) || (!zero_only && (number < 1 || number > 99))) {
            status = F_status_set_fine(status);

            if ((zero_only && number) || (!zero_only && (number < 1 || number > 99)) || status == F_data_not || status == F_number || status == F_number_overflow) {

              if (main.data->error.verbosity != f_console_verbosity_quiet) {
                f_thread_mutex_lock(&main.thread->lock.print);

                fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
                fprintf(main.data->error.to.stream, "%s%sRule setting has an invalid number '", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s);
                fprintf(main.data->error.to.stream, "%s%s", main.data->error.context.after->string, main.data->error.notable.before->string);
                f_print_dynamic_partial(main.data->error.to.stream, cache->buffer_item, cache->content_actions.array[i].array[1]);

                if (zero_only) {
                  fprintf(main.data->error.to.stream, "%s%s', only ", main.data->error.notable.after->string, main.data->error.context.before->string);
                  fprintf(main.data->error.to.stream, "%s%s0%s", main.data->error.context.after->string, main.data->error.notable.before->string, main.data->error.notable.after->string);
                  fprintf(main.data->error.to.stream, "%s is", main.data->error.context.before->string);
                }
                else {
                  fprintf(main.data->error.to.stream, "%s%s', only the whole numbers inclusively between ", main.data->error.notable.after->string, main.data->error.context.before->string);
                  fprintf(main.data->error.to.stream, "%s%s1%s", main.data->error.context.after->string, main.data->error.notable.before->string, main.data->error.notable.after->string);
                  fprintf(main.data->error.to.stream, "%s and ", main.data->error.context.before->string);
                  fprintf(main.data->error.to.stream, "%s%s99%s", main.data->error.context.after->string, main.data->error.notable.before->string, main.data->error.notable.after->string);
                  fprintf(main.data->error.to.stream, "%s are", main.data->error.context.before->string);
                }

                fprintf(main.data->error.to.stream, " allowed for the designated scheduler.%s%c", main.data->error.context.after->string, f_string_eol_s[0]);

                // get the current line number within the settings item.
                cache->action.line_item = line_item;
                f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

                cache->action.line_action = ++cache->action.line_item;

                controller_rule_error_print_cache(main.data->error, cache->action, F_false);

                controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);
              }

              if (F_status_is_error_not(status_return)) {
                status_return = F_status_set_error(F_valid_not);
              }
            }
            else {
              controller_rule_error_print(main.data->error, cache->action, status, "fl_conversion_string_to_number_signed", F_true, F_false, main.thread);
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

          if (main.data->error.verbosity != f_console_verbosity_quiet) {
            f_thread_mutex_lock(&main.thread->lock.print);

            fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
            fprintf(main.data->error.to.stream, "%s%sRule setting requires exactly one Content.%s%c", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s, main.data->error.context.after->string, f_string_eol_s[0]);

            // get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

            cache->action.line_action = ++cache->action.line_item;

            controller_rule_error_print_cache(main.data->error, cache->action, F_false);

            controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);
          }

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        if (type == controller_rule_setting_type_capability) {
          cache->action.generic.used = 0;

          status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[0], &cache->action.generic);

          if (F_status_is_error(status)) {
            f_thread_mutex_lock(&main.thread->lock.print);

            controller_rule_error_print(main.data->error, cache->action, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, F_false, main.thread);

            // get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

            cache->action.line_action = ++cache->action.line_item;

            controller_rule_error_print_cache(main.data->error, cache->action, F_false);

            controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);

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
            f_thread_mutex_lock(&main.thread->lock.print);

            controller_rule_error_print(main.data->error, cache->action, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true, F_false, main.thread);

            // get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

            cache->action.line_action = ++cache->action.line_item;

            controller_rule_error_print_cache(main.data->error, cache->action, F_false);

            controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);

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
              f_thread_mutex_lock(&main.thread->lock.print);

              controller_rule_error_print(main.data->error, cache->action, F_status_set_fine(status), "f_capability_from_text", F_true, F_false, main.thread);

              // get the current line number within the settings item.
              cache->action.line_item = line_item;
              f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

              cache->action.line_action = ++cache->action.line_item;

              controller_rule_error_print_cache(main.data->error, cache->action, F_false);

              controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);

              status_return = status;
              break;
            }

            if (main.data->error.verbosity != f_console_verbosity_quiet) {
              f_thread_mutex_lock(&main.thread->lock.print);

              fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
              fprintf(main.data->error.to.stream, "%s%sRule setting failed to process the capabilities.%s%c", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s, main.data->error.context.after->string, f_string_eol_s[0]);

              // get the current line number within the settings item.
              cache->action.line_item = line_item;
              f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

              cache->action.line_action = ++cache->action.line_item;

              controller_rule_error_print_cache(main.data->error, cache->action, F_false);

              controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);
            }

            if (F_status_is_error_not(status_return)) {
              status_return = F_status_set_error(F_valid_not);
            }

            continue;
          }
        }
        else if (type == controller_rule_setting_type_nice) {
          f_number_signed_t number = 0;

          status = fl_conversion_string_to_number_signed(cache->buffer_item.string, cache->content_actions.array[i].array[0], &number);

          if (F_status_is_error(status) || number < -20 || number > 19) {
            status = F_status_set_fine(status);

            if (number < -20 || number > 19 || status == F_data_not || status == F_number || status == F_number_overflow || status == F_number_underflow) {

              if (main.data->error.verbosity != f_console_verbosity_quiet) {
                f_thread_mutex_lock(&main.thread->lock.print);

                fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
                fprintf(main.data->error.to.stream, "%s%sRule setting has an invalid number '", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s);
                fprintf(main.data->error.to.stream, "%s%s", main.data->error.context.after->string, main.data->error.notable.before->string);
                f_print_dynamic_partial(main.data->error.to.stream, cache->buffer_item, cache->content_actions.array[i].array[0]);
                fprintf(main.data->error.to.stream, "%s%s', only the whole numbers inclusively between ", main.data->error.notable.after->string, main.data->error.context.before->string);
                fprintf(main.data->error.to.stream, "%s%s-20%s", main.data->error.context.after->string, main.data->error.notable.before->string, main.data->error.notable.after->string);
                fprintf(main.data->error.to.stream, "%s and ", main.data->error.context.before->string);
                fprintf(main.data->error.to.stream, "%s%s19%s", main.data->error.context.after->string, main.data->error.notable.before->string, main.data->error.notable.after->string);
                fprintf(main.data->error.to.stream, "%s are allowed.%s%c", main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);

                // get the current line number within the settings item.
                cache->action.line_item = line_item;
                f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

                cache->action.line_action = ++cache->action.line_item;

                controller_rule_error_print_cache(main.data->error, cache->action, F_false);

                controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);
              }

              if (F_status_is_error_not(status_return)) {
                status_return = F_status_set_error(F_valid_not);
              }
            }
            else {
              controller_rule_error_print(main.data->error, cache->action, status, "fl_conversion_string_to_number_signed", F_true, F_false, main.thread);
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
              if (main.data->error.verbosity != f_console_verbosity_quiet) {
                f_thread_mutex_lock(&main.thread->lock.print);

                fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
                fprintf(main.data->error.to.stream, "%s%sRule setting has an invalid user '", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s);
                fprintf(main.data->error.to.stream, "%s%s", main.data->error.context.after->string, main.data->error.notable.before->string);
                f_print_dynamic_partial(main.data->error.to.stream, cache->buffer_item, cache->content_actions.array[i].array[0]);
                fprintf(main.data->error.to.stream, "%s", main.data->error.notable.after->string);
                fprintf(main.data->error.to.stream, "%s' because no user was found by that name.%s%c", main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);

                controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);
              }
            }
            else if (status == F_number_too_large) {
              if (main.data->error.verbosity != f_console_verbosity_quiet) {
                f_thread_mutex_lock(&main.thread->lock.print);

                fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
                fprintf(main.data->error.to.stream, "%s%sRule setting has an invalid user '", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s);
                fprintf(main.data->error.to.stream, "%s%s", main.data->error.context.after->string, main.data->error.notable.before->string);
                f_print_dynamic_partial(main.data->error.to.stream, cache->buffer_item, cache->content_actions.array[i].array[0]);
                fprintf(main.data->error.to.stream, "%s", main.data->error.notable.after->string);
                fprintf(main.data->error.to.stream, "%s' because the given ID is too large.%s%c", main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);

                controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);
              }
            }
            else if (status == F_number) {
              if (main.data->error.verbosity != f_console_verbosity_quiet) {
                f_thread_mutex_lock(&main.thread->lock.print);

                fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
                fprintf(main.data->error.to.stream, "%s%sRule setting has an invalid user '", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s);
                fprintf(main.data->error.to.stream, "%s%s", main.data->error.context.after->string, main.data->error.notable.before->string);
                f_print_dynamic_partial(main.data->error.to.stream, cache->buffer_item, cache->content_actions.array[i].array[0]);
                fprintf(main.data->error.to.stream, "%s", main.data->error.notable.after->string);
                fprintf(main.data->error.to.stream, "%s' because the given ID is not a valid supported number.%s%c", main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);

                controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);
              }
            }
            else {
              controller_rule_error_print(main.data->error, cache->action, status, "f_account_id_user_by_name", F_true, F_false, main.thread);
            }

            // get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

            cache->action.line_action = ++cache->action.line_item;

            controller_rule_item_error_print(main.data->error, cache->action, F_false, main.thread);

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
          if (main.data->error.verbosity != f_console_verbosity_quiet) {
            f_thread_mutex_lock(&main.thread->lock.print);

            fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
            fprintf(main.data->error.to.stream, "%s%sRule setting requires one or more Content.%s%c", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s, main.data->error.context.after->string, f_string_eol_s[0]);

            // get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

            cache->action.line_action = ++cache->action.line_item;

            controller_rule_error_print_cache(main.data->error, cache->action, F_false);

            controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);
          }

          if (F_status_is_error_not(status_return)) {
            status_return = F_status_set_error(F_valid_not);
          }

          continue;
        }

        gid_t number = 0;

        rule->groups.used = 0;

        for (j = 0; j < cache->content_actions.array[i].used; ++j) {

          f_macro_array_lengths_t_increase_by(status, rule->groups, controller_default_allocation_step)

          if (F_status_is_error(status)) {
            controller_rule_error_print(main.data->error, cache->action, F_status_set_fine(status), "f_macro_array_lengths_t_increase_by", F_true, F_false, main.thread);

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

            controller_rule_item_error_print(main.data->error, cache->action, F_false, main.thread);

            continue;
          }

          status = controller_get_id_group(cache->buffer_item, cache->content_actions.array[i].array[j], cache, &number);

          if (F_status_is_error(status)) {
            status = F_status_set_fine(status);

            if (status == F_exist_not) {
              if (main.data->error.verbosity != f_console_verbosity_quiet) {
                f_thread_mutex_lock(&main.thread->lock.print);

                fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
                fprintf(main.data->error.to.stream, "%s%sRule setting has an invalid group '", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s);
                fprintf(main.data->error.to.stream, "%s%s", main.data->error.context.after->string, main.data->error.notable.before->string);
                f_print_dynamic_partial(main.data->error.to.stream, cache->buffer_item, cache->content_actions.array[i].array[j]);
                fprintf(main.data->error.to.stream, "%s", main.data->error.notable.after->string);
                fprintf(main.data->error.to.stream, "%s' because no group was found by that name.%s%c", main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);

                controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);
              }
            }
            else if (status == F_number_too_large) {
              if (main.data->error.verbosity != f_console_verbosity_quiet) {
                f_thread_mutex_lock(&main.thread->lock.print);

                fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
                fprintf(main.data->error.to.stream, "%s%sRule setting has an invalid group '", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s);
                fprintf(main.data->error.to.stream, "%s%s", main.data->error.context.after->string, main.data->error.notable.before->string);
                f_print_dynamic_partial(main.data->error.to.stream, cache->buffer_item, cache->content_actions.array[i].array[j]);
                fprintf(main.data->error.to.stream, "%s", main.data->error.notable.after->string);
                fprintf(main.data->error.to.stream, "%s' because the given ID is too large.%s%c", main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);

                controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);
              }
            }
            else if (status == F_number) {
              if (main.data->error.verbosity != f_console_verbosity_quiet) {
                f_thread_mutex_lock(&main.thread->lock.print);

                fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
                fprintf(main.data->error.to.stream, "%s%sRule setting has an invalid group '", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s);
                fprintf(main.data->error.to.stream, "%s%s", main.data->error.context.after->string, main.data->error.notable.before->string);
                f_print_dynamic_partial(main.data->error.to.stream, cache->buffer_item, cache->content_actions.array[i].array[j]);
                fprintf(main.data->error.to.stream, "%s", main.data->error.notable.after->string);
                fprintf(main.data->error.to.stream, "%s' because the given ID is not a valid supported number.%s%c", main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);

                controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);
              }
            }
            else {
              controller_rule_error_print(main.data->error, cache->action, status, "f_account_id_group_by_name", F_true, F_false, main.thread);
            }

            // get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

            cache->action.line_action = ++cache->action.line_item;

            controller_rule_item_error_print(main.data->error, cache->action, F_false, main.thread);

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
            controller_rule_error_print(main.data->error, cache->action, F_status_set_fine(status), "f_string_dynamics_increase", F_true, F_false, main.thread);

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

            controller_rule_item_error_print(main.data->error, cache->action, F_false, main.thread);

            continue;
          }

          setting_values->array[setting_values->used].used = 0;

          status = f_string_dynamic_partial_append_nulless(cache->buffer_item, cache->content_actions.array[i].array[j], &setting_values->array[setting_values->used]);

          if (F_status_is_error(status)) {
            controller_rule_error_print(main.data->error, cache->action, F_status_set_fine(status), "f_string_dynamic_partial_append_nulless", F_true, F_false, main.thread);
          }
          else {
            status = f_string_dynamic_terminate_after(&setting_values->array[setting_values->used]);

            if (F_status_is_error(status)) {
              controller_rule_error_print(main.data->error, cache->action, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true, F_false, main.thread);
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
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

            cache->action.line_action = ++cache->action.line_item;

            controller_rule_item_error_print(main.data->error, cache->action, F_false, main.thread);

            continue;
          }

          status = controller_validate_environment_name(setting_values->array[setting_values->used]);

          if (status == F_false || F_status_set_fine(status) == F_complete_not_utf) {
            if (status == F_false) {

              if (main.data->error.verbosity != f_console_verbosity_quiet) {
                f_thread_mutex_lock(&main.thread->lock.print);

                fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
                fprintf(main.data->error.to.stream, "%s%sRule setting has an invalid environment variable name '", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s);
                fprintf(main.data->error.to.stream, "%s%s%s%s", main.data->error.context.after->string, main.data->error.notable.before->string, setting_values->array[setting_values->used].string, main.data->error.notable.after->string);
                fprintf(main.data->error.to.stream, "%s'.%s%c", main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);

                // get the current line number within the settings item.
                cache->action.line_item = line_item;
                f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

                cache->action.line_action = ++cache->action.line_item;

                controller_rule_error_print_cache(main.data->error, cache->action, F_false);

                controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);
              }

              if (F_status_is_error_not(status_return)) {
                status_return = F_status_set_error(F_valid_not);
              }
            }
            else {

              // this function should only return F_complete_not_utf on error.
              controller_rule_error_print(main.data->error, cache->action, F_complete_not_utf, "controller_validate_environment_name", F_true, F_false, main.thread);

              if (F_status_is_error_not(status_return)) {
                status_return = status;
              }
            }

            setting_values->array[setting_values->used].used = 0;

            // get the current line number within the settings item.
            cache->action.line_item = line_item;
            f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

            cache->action.line_action = ++cache->action.line_item;

            controller_rule_item_error_print(main.data->error, cache->action, F_false, main.thread);

            continue;
          }

          setting_values->used++;
        } // for

        continue;
      }

      if (cache->content_actions.array[i].used != 2) {

        if (main.data->error.verbosity != f_console_verbosity_quiet) {
          f_thread_mutex_lock(&main.thread->lock.print);

          fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
          fprintf(main.data->error.to.stream, "%s%sRule setting requires exactly two Content.%s%c", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s, main.data->error.context.after->string, f_string_eol_s[0]);

          // get the current line number within the settings item.
          cache->action.line_item = line_item;
          f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

          cache->action.line_action = ++cache->action.line_item;

          controller_rule_error_print_cache(main.data->error, cache->action, F_false);

          controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);
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
        controller_rule_error_print(main.data->error, cache->action, F_status_set_fine(status), "f_string_dynamics_increase_by", F_true, F_false, main.thread);

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

        controller_rule_item_error_print(main.data->error, cache->action, F_false, main.thread);

        continue;
      }

      status = controller_rule_id_construct(main, cache->buffer_item, cache->content_actions.array[i].array[0], cache->content_actions.array[i].array[1], &setting_values->array[setting_values->used]);

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
        cache->action.line_item = line_item;
        f_fss_count_lines(cache->buffer_item, cache->object_actions.array[i].start, &cache->action.line_item);

        cache->action.line_action = ++cache->action.line_item;

        controller_rule_item_error_print(main.data->error, cache->action, F_false, main.thread);

        continue;
      }

      cache->buffer_path.used = 0;

      status = f_file_name_base(setting_values->array[setting_values->used].string, setting_values->array[setting_values->used + 1].used, &cache->buffer_path);

      if (F_status_is_error(status)) {
        setting_values->array[setting_values->used].used = 0;

        controller_rule_error_print(main.data->error, cache->action, F_status_set_fine(status), "f_file_name_base", F_true, F_false, main.thread);

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

        if (main.data->error.verbosity != f_console_verbosity_quiet) {
          f_thread_mutex_lock(&main.thread->lock.print);

          fprintf(main.data->error.to.stream, "%c", f_string_eol_s[0]);
          fprintf(main.data->error.to.stream, "%s%sThe rule item action second parameter '", main.data->error.context.before->string, main.data->error.prefix ? main.data->error.prefix : f_string_empty_s);
          fprintf(main.data->error.to.stream, "%s%s", main.data->error.context.after->string, main.data->error.notable.before->string);
          f_print_dynamic_partial(main.data->error.to.stream, cache->buffer_item, cache->content_actions.array[i].array[1]);
          fprintf(main.data->error.to.stream, "%s", main.data->error.notable.after->string);
          fprintf(main.data->error.to.stream, "%s' must be a base path name, such as %llu '", main.data->error.context.before->string, cache->buffer_path.used);
          fprintf(main.data->error.to.stream, "%s%s", main.data->error.context.after->string, main.data->error.notable.before->string);
          f_print_dynamic(main.data->error.to.stream, cache->buffer_path);
          fprintf(main.data->error.to.stream, "%s", main.data->error.notable.after->string);
          fprintf(main.data->error.to.stream, "%s'.%s%c", main.data->error.context.before->string, main.data->error.context.after->string, f_string_eol_s[0]);

          controller_print_unlock_flush(main.data->error.to.stream, &main.thread->lock.print);
        }

        setting_values->array[setting_values->used].used = 0;

        continue;
      }

      setting_values->used++;
    } // for

    // resore the current name item and line number, which there should already be enough allocated space for.
    memcpy(cache->action.name_item.string, name_item, length_name_item);

    cache->action.name_item.string[length_name_item] = 0;
    cache->action.name_item.used = length_name_item;

    cache->action.line_item = line_item;

    return status_return;
  }
#endif // _di_controller_rule_setting_read_

#ifndef _di_controller_rule_validate_
  void controller_rule_validate(const controller_rule_t rule, const uint8_t action, const uint8_t options, const controller_main_t main, controller_cache_t *cache) {

    const controller_data_t *data = main.data;

    f_thread_mutex_lock(&main.thread->lock.print);

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
          fprintf(data->error.to.stream, "%s%s%s%s", data->error.context.after->string, data->error.notable.before->string, controller_rule_action_type_name(action).string, data->error.notable.after->string);
          fprintf(data->error.to.stream, "%s' while attempting to validate rule execution.%s%c", data->error.context.before->string, data->error.context.after->string, f_string_eol_s[0]);

          controller_rule_error_print_cache(data->error, cache->action, F_true);
        }

        controller_print_unlock_flush(data->error.to.stream, &main.thread->lock.print);

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
        fprintf(data->output.stream, "%c", f_string_eol_s[0]);
        fprintf(data->output.stream, "Rule '");
        fprintf(data->output.stream, "%s%s%s", data->context.set.title.before->string, rule.name.used ? rule.name.string : f_string_empty_s, data->context.set.title.after->string);
        fprintf(data->output.stream, "' has no '");
        fprintf(data->output.stream, "%s%s%s", data->context.set.important.before->string, controller_rule_action_type_name(action).string, data->context.set.important.after->string);
        fprintf(data->output.stream, "' action to execute and would '");
        fprintf(data->output.stream, "%s%s%s", data->context.set.important.before->string, options & controller_process_option_require ? controller_string_fail_s : controller_string_succeed_s, data->context.set.important.after->string);
        fprintf(data->output.stream, "' because it is '");
        fprintf(data->output.stream, "%s%s%s", data->context.set.important.before->string, options & controller_process_option_require ? controller_string_required_s : controller_string_optional_s, data->context.set.important.after->string);
        fprintf(data->output.stream, "'.%c", f_string_eol_s[0]);
      }
    }

    fprintf(data->output.stream, "%c", f_string_eol_s[0]);
    fprintf(data->output.stream, "Rule %s%s%s {%c", data->context.set.title.before->string, rule.alias.used ? rule.alias.string : f_string_empty_s, data->context.set.title.after->string, f_string_eol_s[0]);
    fprintf(data->output.stream, "  %s%s%s %s%c", data->context.set.important.before->string, controller_string_name_s, data->context.set.important.after->string, rule.name.used ? rule.name.string : f_string_empty_s, f_string_eol_s[0]);
    fprintf(data->output.stream, "  %s%s%s %s%c", data->context.set.important.before->string, controller_string_how_s, data->context.set.important.after->string, options & controller_process_option_asynchronous ? controller_string_asynchronous : controller_string_synchronous_s, f_string_eol_s[0]);
    fprintf(data->output.stream, "  %s%s%s %s%c", data->context.set.important.before->string, controller_string_wait_s, data->context.set.important.after->string, options & controller_process_option_wait ? controller_string_yes : controller_string_no_s, f_string_eol_s[0]);

    if (f_capability_supported()) {
      fprintf(data->output.stream, "  %s%s%s ", data->context.set.important.before->string, controller_string_capability_s, data->context.set.important.after->string);

      if (rule.capability) {
        cache->action.generic.used = 0;

        if (F_status_is_error_not(f_capability_to_text(rule.capability, &cache->action.generic))) {
          fprintf(data->output.stream, "%s", cache->action.generic.string);
        }
      }

      fprintf(data->output.stream, "%c", f_string_eol_s[0]);
    }
    else {
      fprintf(data->output.stream, "  %s%s%s ", data->context.set.important.before->string, controller_string_capability_s, data->context.set.important.after->string, f_string_eol_s[0]);
      fprintf(data->output.stream, "%s(unsupported)%s%c", data->context.set.warning.before->string, data->context.set.warning.after->string, f_string_eol_s[0]);
    }

    fprintf(data->output.stream, "  %s%s%s", data->context.set.important.before->string, controller_string_control_group_s, data->context.set.important.after->string);

    if (rule.has & controller_rule_has_control_group) {
      fprintf(data->output.stream, " %s", rule.control_group.as_new ? controller_string_new_s : controller_string_existing_s);

      for (i = 0; i < rule.control_group.groups.used; ++i) {

        if (rule.control_group.groups.array[i].used) {
          fprintf(data->output.stream, f_string_space_s);
          f_print_dynamic(data->output.stream, rule.control_group.groups.array[i]);
        }
      } // for
    }

    fprintf(data->output.stream, "%c", f_string_eol_s[0]);
    fprintf(data->output.stream, "  %s%s%s", data->context.set.important.before->string, controller_string_nice_s, data->context.set.important.after->string);

    if (rule.has & controller_rule_has_nice) {
      fprintf(data->output.stream, " %i", rule.nice);
    }

    fprintf(data->output.stream, "%c", f_string_eol_s[0]);
    fprintf(data->output.stream, "  %s%s%s", data->context.set.important.before->string, controller_string_scheduler_s, data->context.set.important.after->string);

    if (rule.has & controller_rule_has_scheduler) {
      f_string_t policy = "";

      if (rule.scheduler.policy == SCHED_BATCH) {
        policy = controller_string_batch_s;
      }
      else if (rule.scheduler.policy == SCHED_DEADLINE) {
        policy = controller_string_deadline_s;
      }
      else if (rule.scheduler.policy == SCHED_FIFO) {
        policy = controller_string_fifo_s;
      }
      else if (rule.scheduler.policy == SCHED_IDLE) {
        policy = controller_string_idle_s;
      }
      else if (rule.scheduler.policy == SCHED_OTHER) {
        policy = controller_string_other_s;
      }
      else if (rule.scheduler.policy == SCHED_RR) {
        policy = controller_string_round_robin_s;
      }

      fprintf(data->output.stream, " %s %i", policy, rule.scheduler.priority);
    }

    fprintf(data->output.stream, "%c", f_string_eol_s[0]);
    fprintf(data->output.stream, "  %s%s%s %s%c", data->context.set.important.before->string, controller_string_script_s, data->context.set.important.after->string, rule.script.used ? rule.script.string : f_string_empty_s, f_string_eol_s[0]);
    fprintf(data->output.stream, "  %s%s%s", data->context.set.important.before->string, controller_string_user_s, data->context.set.important.after->string);

    if (rule.has & controller_rule_has_user) {
      fprintf(data->output.stream, " %i", rule.user);
    }

    fprintf(data->output.stream, "%c", f_string_eol_s[0]);
    fprintf(data->output.stream, "  %s%s%s {%c", data->context.set.important.before->string, controller_string_affinity_s, data->context.set.important.after->string, f_string_eol_s[0]);

    for (i = 0; i < rule.affinity.used; ++i) {
      fprintf(data->output.stream, "    %i%c", rule.affinity.array[i], f_string_eol_s[0]);
    } // for

    fprintf(data->output.stream, "  }%c", f_string_eol_s[0]);
    fprintf(data->output.stream, "  %s%s%s {%c", data->context.set.important.before->string, controller_string_define_s, data->context.set.important.after->string, f_string_eol_s[0]);

    for (i = 0; i < rule.define.used; ++i) {

      if (rule.define.array[i].name.used && rule.define.array[i].value.used) {
        fprintf(data->output.stream, "    %s %s=%s %s%c", rule.define.array[i].name.string, data->context.set.important.before->string, data->context.set.important.after->string, rule.define.array[i].value.string, f_string_eol_s[0]);
      }
    } // for

    fprintf(data->output.stream, "  }%c", f_string_eol_s[0]);
    fprintf(data->output.stream, "  %s%s%s {%c", data->context.set.important.before->string, controller_string_environment_s, data->context.set.important.after->string, f_string_eol_s[0]);

    for (i = 0; i < rule.environment.used; ++i) {

      if (rule.environment.array[i].used) {
        fprintf(data->output.stream, "    %s%c", rule.environment.array[i].string, f_string_eol_s[0]);
      }
    } // for

    fprintf(data->output.stream, "  }%c", f_string_eol_s[0]);
    fprintf(data->output.stream, "  %s%s%s {%c", data->context.set.important.before->string, controller_string_group_s, data->context.set.important.after->string, f_string_eol_s[0]);

    if (rule.has & controller_rule_has_group) {
      fprintf(data->output.stream, "    %i%c", rule.group, f_string_eol_s[0]);

      for (i = 0; i < rule.groups.used; ++i) {
        fprintf(data->output.stream, "    %i%c", rule.groups.array[i], f_string_eol_s[0]);
      } // for
    }

    fprintf(data->output.stream, "  }%c", f_string_eol_s[0]);
    fprintf(data->output.stream, "  %s%s%s {%c", data->context.set.important.before->string, controller_string_limit_s, data->context.set.important.after->string, f_string_eol_s[0]);

    for (i = 0; i < rule.limits.used; ++i) {
      fprintf(data->output.stream, "    %s %s=%s %llu %llu%c", controller_rule_setting_limit_type_name(rule.limits.array[i].type).string, data->context.set.important.before->string, data->context.set.important.after->string, rule.limits.array[i].value.rlim_cur, rule.limits.array[i].value.rlim_max, f_string_eol_s[0]);
    } // for

    fprintf(data->output.stream, "  }%c", f_string_eol_s[0]);
    fprintf(data->output.stream, "  %s%s%s {%c", data->context.set.important.before->string, controller_string_need_s, data->context.set.important.after->string, f_string_eol_s[0]);

    for (i = 0; i < rule.need.used; ++i) {

      if (rule.need.array[i].used) {
        fprintf(data->output.stream, "    %s%c", rule.need.array[i].string, f_string_eol_s[0]);
      }
    } // for

    fprintf(data->output.stream, "  }%c", f_string_eol_s[0]);

    fprintf(data->output.stream, "  %s%s%s {%c", data->context.set.important.before->string, controller_string_parameter_s, data->context.set.important.after->string, f_string_eol_s[0]);

    for (i = 0; i < rule.parameter.used; ++i) {

      if (rule.parameter.array[i].name.used && rule.parameter.array[i].value.used) {
        fprintf(data->output.stream, "    %s %s=%s %s%c", rule.parameter.array[i].name.string, data->context.set.important.before->string, data->context.set.important.after->string, rule.parameter.array[i].value.string, f_string_eol_s[0]);
      }
    } // for

    fprintf(data->output.stream, "  }%c", f_string_eol_s[0]);
    fprintf(data->output.stream, "  %s%s%s {%c", data->context.set.important.before->string, controller_string_want_s, data->context.set.important.after->string, f_string_eol_s[0]);

    for (i = 0; i < rule.want.used; ++i) {

      if (rule.want.array[i].used) {
        fprintf(data->output.stream, "    %s%c", rule.want.array[i].string, f_string_eol_s[0]);
      }
    } // for

    fprintf(data->output.stream, "  }%c", f_string_eol_s[0]);
    fprintf(data->output.stream, "  %s%s%s {%c", data->context.set.important.before->string, controller_string_wish_s, data->context.set.important.after->string, f_string_eol_s[0]);

    for (i = 0; i < rule.wish.used; ++i) {

      if (rule.wish.array[i].used) {
        fprintf(data->output.stream, "    %s%c", rule.wish.array[i].string, f_string_eol_s[0]);
      }
    } // for

    fprintf(data->output.stream, "  }%c", f_string_eol_s[0]);

    if (rule.items.used) {
      controller_rule_action_t *action = 0;
      controller_rule_item_t *item = 0;
      f_string_dynamic_t *parameter = 0;

      f_array_length_t j = 0;
      f_array_length_t k = 0;

      for (i = 0; i < rule.items.used; ++i) {

        item = &rule.items.array[i];

        fprintf(data->output.stream, "  %s%s%s {%c", data->context.set.important.before->string, controller_string_item_s, data->context.set.important.after->string, f_string_eol_s[0]);
        fprintf(data->output.stream, "    %s%s%s %s%c", data->context.set.important.before->string, controller_string_type_s, data->context.set.important.after->string, controller_rule_item_type_name(item->type).string, f_string_eol_s[0]);

        for (j = 0; j < item->actions.used; ++j) {

          action = &item->actions.array[j];

          fprintf(data->output.stream, "    %s%s%s {%c", data->context.set.important.before->string, controller_string_action_s, data->context.set.important.after->string, f_string_eol_s[0]);
          fprintf(data->output.stream, "      %s%s%s %s%c", data->context.set.important.before->string, controller_string_type_s, data->context.set.important.after->string, controller_rule_action_type_name(action->type).string, f_string_eol_s[0]);

          if (item->type == controller_rule_item_type_script || item->type == controller_rule_item_type_utility) {
            fprintf(data->output.stream, "      %s%s%s {%c", data->context.set.important.before->string, controller_string_parameter_s, data->context.set.important.after->string, f_string_eol_s[0]);

            parameter = &action->parameters.array[0];

            if (parameter->used) {
              fprintf(data->output.stream, "        ");

              for (k = 0; k < parameter->used; ++k) {

                fprintf(data->output.stream, "%c", parameter->string[k]);

                if (parameter->string[k] == f_fss_eol && k + 1 < parameter->used) {
                  fprintf(data->output.stream, "        ");
                }
              } // for

              fprintf(data->output.stream, "%c", f_string_eol_s[0]);
            }

            fprintf(data->output.stream, "      }%c", f_string_eol_s[0]);
          }
          else {
            for (k = 0; k < action->parameters.used; ++k) {
              fprintf(data->output.stream, "      %s%s%s %s%c", data->context.set.important.before->string, controller_string_parameter_s, data->context.set.important.after->string, action->parameters.array[k].string, f_string_eol_s[0]);
            } // for
          }

          fprintf(data->output.stream, "    }%c", f_string_eol_s[0]);
        } // for

        fprintf(data->output.stream, "  }%c", f_string_eol_s[0]);
      } // for
    }

    fprintf(data->output.stream, "}%c", f_string_eol_s[0]);

    controller_print_unlock_flush(data->output.stream, &main.thread->lock.print);
  }
#endif // _di_controller_rule_validate_

#ifndef _di_controller_rule_wait_all_
  f_status_t controller_rule_wait_all(const bool is_normal, const controller_main_t main, const bool required, controller_process_t *caller) {

    f_status_t status_lock = F_none;

    if (caller) {
      controller_lock_read_process(caller, main.thread, &main.thread->lock.process);
    }
    else {
      controller_lock_read(is_normal, main.thread, &main.thread->lock.process);
    }

    if (status_lock == F_signal || F_status_is_error(status_lock)) {
      controller_lock_error_critical_print(main.data->error, F_status_set_fine(status_lock), F_true, main.thread);

      return status_lock;
    }

    if (!main.thread->processs.used) {
      f_thread_unlock(&main.thread->lock.process);

      return F_data_not;
    }

    f_status_t status = F_none;

    bool required_not_run = F_false;

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    controller_process_t *process = 0;

    bool skip = F_false;

    for (; i < main.thread->processs.used; ++i) {

      if (caller) {
        if (!controller_thread_is_enabled_process(caller, main.thread)) break;
      }
      else {
        if (!controller_thread_is_enabled(is_normal, main.thread)) break;
      }

      process = main.thread->processs.array[i];

      if (caller) {
        f_thread_unlock(&main.thread->lock.process);

        if (caller) {
          status_lock = controller_lock_read_process(caller, main.thread, &main.thread->lock.rule);
        }
        else {
          status_lock = controller_lock_read(is_normal, main.thread, &main.thread->lock.rule);
        }

        if (status_lock == F_signal || F_status_is_error(status_lock)) break;

        skip = F_false;

        for (j = 0; j < caller->stack.used; ++j) {

          if (caller) {
            if (!controller_thread_is_enabled_process(caller, main.thread)) break;
          }
          else {
            if (!controller_thread_is_enabled(is_normal, main.thread)) break;
          }

          if (main.thread->processs.array[caller->stack.array[j]] && fl_string_dynamic_compare(process->rule.alias, main.thread->processs.array[caller->stack.array[j]]->rule.alias) == F_equal_to) {
            skip = F_true;
          }

          if (skip) break;
        } // for

        f_thread_unlock(&main.thread->lock.rule);

        if (caller) {
          status_lock = controller_lock_read_process(caller, main.thread, &main.thread->lock.process);
        }
        else {
          status_lock = controller_lock_read(is_normal, main.thread, &main.thread->lock.process);
        }

        if (status_lock == F_signal || F_status_is_error(status_lock)) break;
        if (skip) continue;
      }

      if (caller) {
        status_lock = controller_lock_read_process(caller, main.thread, &process->active);
      }
      else {
        status_lock = controller_lock_read(is_normal, main.thread, &process->active);
      }

      if (status_lock == F_signal || F_status_is_error(status_lock)) {
        f_thread_unlock(&main.thread->lock.process);

        break;
      }

      f_thread_unlock(&main.thread->lock.process);

      if (caller) {
        status_lock = controller_lock_read_process(caller, main.thread, &process->lock);
      }
      else {
        status_lock = controller_lock_read(is_normal, main.thread, &process->lock);
      }

      if (status_lock == F_signal || F_status_is_error(status_lock)) {
        f_thread_unlock(&process->active);

        break;
      }

      if (required) {
        if (!(process->options & controller_process_option_require)) {
          f_thread_unlock(&process->lock);
          f_thread_unlock(&process->active);

          if (caller) {
            status_lock = controller_lock_read_process(caller, main.thread, &main.thread->lock.process);
          }
          else {
            status_lock = controller_lock_read(is_normal, main.thread, &main.thread->lock.process);
          }

          if (status_lock == F_signal || F_status_is_error(status_lock)) break;

          continue;
        }
      }

      if (!process->state || process->state == controller_process_state_idle || process->state == controller_process_state_done) {

        if (process->state == controller_process_state_done) {
          f_thread_unlock(&process->lock);

          if (caller) {
            status_lock = controller_lock_write_process(process, main.thread, &process->lock);
          }
          else {
            status_lock = controller_lock_write(is_normal, main.thread, &process->lock);
          }

          if (status_lock == F_signal || F_status_is_error(status_lock)) {
            controller_lock_error_critical_print(main.data->error, F_status_set_fine(status_lock), F_false, main.thread);

            f_thread_unlock(&process->active);

            return status_lock;
          }

          if (process->state == controller_process_state_done) {
            f_thread_unlock(&process->active);

            if (f_thread_lock_write_try(&process->active) == F_none) {

              controller_thread_join(&process->id_thread);

              process->state = controller_process_state_idle;

              f_thread_unlock(&process->active);
            }

            if (caller) {
              status_lock = controller_lock_read_process(caller, main.thread, &process->active);
            }
            else {
              status_lock = controller_lock_read(is_normal, main.thread, &process->active);
            }

            if (status_lock == F_signal || F_status_is_error(status_lock)) {
              f_thread_unlock(&process->lock);

              break;
            }
          }

          f_thread_unlock(&process->lock);

          if (caller) {
            status_lock = controller_lock_read_process(caller, main.thread, &process->lock);
          }
          else {
            status_lock = controller_lock_read(is_normal, main.thread, &process->lock);
          }

          if (status_lock == F_signal || F_status_is_error(status_lock)) break;
        }

        if (required && (process->options & controller_process_option_require)) {
          if (F_status_is_error(process->rule.status)) {
            status = F_status_set_error(F_require);

            f_thread_unlock(&process->lock);
            f_thread_unlock(&process->active);

            if (caller) {
              status_lock = controller_lock_read_process(caller, main.thread, &main.thread->lock.process);
            }
            else {
              status_lock = controller_lock_read(is_normal, main.thread, &main.thread->lock.process);
            }

            break;
          }
          else if (process->rule.status == F_known_not) {
            required_not_run = F_true;
          }
        }

        f_thread_unlock(&process->lock);
        f_thread_unlock(&process->active);

        if (caller) {
          status_lock = controller_lock_read_process(caller, main.thread, &main.thread->lock.process);
        }
        else {
          status_lock = controller_lock_read(is_normal, main.thread, &main.thread->lock.process);
        }

        if (status_lock == F_signal || F_status_is_error(status_lock)) break;
        if (F_status_set_fine(status) == F_require) break;

        continue;
      }

      if (process->rule.status == F_known_not || (process->state == controller_process_state_active || process->state == controller_process_state_busy)) {
        f_thread_unlock(&process->lock);

        status = controller_process_wait(main, process);

        if (status == F_signal) {
          f_thread_unlock(&process->active);

          if (caller) {
            status_lock = controller_lock_read_process(caller, main.thread, &main.thread->lock.process);
          }
          else {
            status_lock = controller_lock_read(is_normal, main.thread, &main.thread->lock.process);
          }

          break;
        }

        if (required) {
          if (caller) {
            status_lock = controller_lock_read_process(caller, main.thread, &process->lock);
          }
          else {
            status_lock = controller_lock_read(is_normal, main.thread, &process->lock);
          }

          if (status_lock == F_signal || F_status_is_error(status_lock)) {
            f_thread_unlock(&process->active);

            break;
          }

          if ((process->options & controller_process_option_require)) {
            f_thread_unlock(&process->lock);

            if (F_status_is_error(process->rule.status)) {
              status = F_status_set_error(F_require);

              f_thread_unlock(&process->active);

              if (caller) {
                status_lock = controller_lock_read_process(caller, main.thread, &main.thread->lock.process);
              }
              else {
                status_lock = controller_lock_read(is_normal, main.thread, &main.thread->lock.process);
              }

              break;
            }
          }
          else {
            f_thread_unlock(&process->lock);
          }
        }
      }
      else {
        f_thread_unlock(&process->lock);
      }

      f_thread_unlock(&process->active);

      if (caller) {
        status_lock = controller_lock_read_process(caller, main.thread, &main.thread->lock.process);
      }
      else {
        status_lock = controller_lock_read(is_normal, main.thread, &main.thread->lock.process);
      }

      if (status_lock == F_signal || F_status_is_error(status_lock)) break;
      if (status == F_signal || F_status_set_fine(status) == F_require) break;
    } // for

    if (status_lock == F_signal || F_status_is_error(status_lock)) {
      controller_lock_error_critical_print(main.data->error, F_status_set_fine(status_lock), F_true, main.thread);

      return status_lock;
    }

    f_thread_unlock(&main.thread->lock.process);

    if (caller) {
      if (!controller_thread_is_enabled_process(caller, main.thread)) {
        return F_signal;
      }
    }
    else {
      if (!controller_thread_is_enabled(is_normal, main.thread)) {
        return F_signal;
      }
    }

    if (status == F_signal || F_status_set_fine(status) == F_require) {
      return status;
    }

    if (required_not_run) {
      return F_require;
    }

    return F_none;
  }
#endif // _di_controller_rule_wait_all_

#ifndef _di_controller_rule_wait_all_process_type_
  f_status_t controller_rule_wait_all_process_type(const uint8_t type, const controller_main_t main, const bool required, controller_process_t *caller) {

    return controller_rule_wait_all(type != controller_process_type_exit, main, required, caller);
  }
#endif // _di_controller_rule_wait_all_process_type_

#ifdef __cplusplus
} // extern "C"
#endif
