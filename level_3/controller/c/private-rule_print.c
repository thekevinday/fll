#include "controller.h"
#include "private-common.h"
#include "private-rule_print.h"
#include "private-lock_print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_rule_print_error_
  void controller_rule_print_error(const fl_print_t print, const controller_cache_action_t cache, const f_status_t status, const f_string_t function, const bool fallback, const bool item, controller_thread_t *thread) {

    if (print.verbosity == f_console_verbosity_quiet) return;
    if (status == F_interrupt) return;

    // fll_error_print() automatically locks, so manually handle only the mutex locking and flushing rather than calling controller_lock_print().
    f_thread_mutex_lock(&thread->lock.print);

    fll_error_print(print, status, function, fallback);

    flockfile(print.to.stream);

    controller_rule_print_error_cache(print, cache, item);

    controller_unlock_print_flush(print.to, thread);
  }
#endif // _di_controller_rule_print_error_

#ifndef _di_controller_rule_print_error_cache_
  void controller_rule_print_error_cache(const fl_print_t print, const controller_cache_action_t cache, const bool item) {

    if (print.verbosity == f_console_verbosity_quiet) return;

    fl_print_format("%c%[%SWhile processing ", print.to.stream, f_string_eol_s[0], print.context, print.prefix);

    if (cache.name_action.used) {
      fl_print_format("%s '%]", print.to.stream, item ? controller_action_s : controller_value_s, print.context);
      fl_print_format("%[%Q%]", print.to.stream, print.notable, cache.name_action, print.notable);
      fl_print_format("%[' on line%] ", print.to.stream, print.context, print.context);
      fl_print_format("%[%un%]", print.to.stream, print.notable, cache.line_action, print.notable);
      fl_print_format("%[ for ", print.to.stream, print.context);
    }

    if (cache.name_item.used) {
      fl_print_format("rule %s '%]", print.to.stream, item ? controller_item_s : controller_setting_s, print.context);
      fl_print_format("%[%Q%]", print.to.stream, print.notable, cache.name_item, print.notable);
      fl_print_format("%[' on line%] ", print.to.stream, print.context, print.context);
      fl_print_format("%[%un%]", print.to.stream, print.notable, cache.line_item, print.notable);
      fl_print_format("%[ for ", print.to.stream, print.context);
    }

    if (cache.name_file.used) {
      fl_print_format("rule file '%]%[%Q%]%['", print.to.stream, print.context, print.notable, cache.name_file, print.notable, print.context);
    }

    fl_print_format(".%]%c", print.to.stream, print.context, f_string_eol_s[0]);
  }
#endif // _di_controller_rule_print_error_cache_

#ifndef _di_controller_rule_item_print_error_
  void controller_rule_item_print_error(const fl_print_t print, const controller_cache_action_t cache, const bool item, const f_status_t status, controller_thread_t *thread) {

    if (print.verbosity == f_console_verbosity_quiet) return;
    if (status == F_interrupt) return;

    // fll_error_print() automatically locks, so manually handle only the mutex locking and flushing rather than calling controller_lock_print().
    f_thread_mutex_lock(&thread->lock.print);

    controller_rule_print_error_cache(print, cache, item);

    flockfile(print.to.stream);

    controller_unlock_print_flush(print.to, thread);
  }
#endif // _di_controller_rule_item_print_error_

#ifndef _di_controller_rule_item_print_error_execute_
  void controller_rule_item_print_error_execute(const bool script_is, const f_string_t name, const f_status_t status, controller_process_t * const process) {

    if (((controller_main_t *) process->main_data)->error.verbosity != f_console_verbosity_quiet) {
      fl_print_t * const print = &((controller_main_t *) process->main_data)->error;

      controller_lock_print(print->to, (controller_thread_t *) process->main_thread);

      fl_print_format("%c%[%SThe %s '%]", print->to.stream, f_string_eol_s[0], print->context, print->prefix, script_is ? controller_script_s : controller_program_s, print->context);
      fl_print_format("%[%S%]", print->to.stream, print->notable, name, print->notable);

      if (status == F_control_group || status == F_limit || status == F_processor || status == F_schedule) {
        fl_print_format("%[' failed due to a failure to setup the '%]%[", print->to.stream, print->context, print->context, print->notable);

        if (status == F_control_group) {
          f_print_terminated(controller_control_group_s, print->to.stream);
        }
        else if (status == F_limit) {
          f_print_terminated(controller_limit_s, print->to.stream);
        }
        else if (status == F_processor) {
          f_print_terminated(controller_processor_s, print->to.stream);
        }
        else if (status == F_schedule) {
          f_print_terminated(controller_scheduler_s, print->to.stream);
        }

        fl_print_format("%]%['.%]%c", print->to.stream, print->notable, print->context, print->context, f_string_eol_s[0]);
      }
      else if (WIFEXITED(process->result) ? WEXITSTATUS(process->result) : 0) {
        const uint8_t code = WIFEXITED(process->result) ? WEXITSTATUS(process->result) : 0;

        if (code == F_execute_access) {
          fl_print_format("%[' access denied.%]%c", print->to.stream, print->context, print->context, f_string_eol_s[0]);
        }
        else if (code == F_execute_bad) {
          fl_print_format("%[' cannot execute, unsupported format.%]%c", print->to.stream, print->context, print->context, f_string_eol_s[0]);
        }
        else if (code == F_execute_buffer) {
          fl_print_format("%[' invalid memory access in arguments buffer.%]%c", print->to.stream, print->context, print->context, f_string_eol_s[0]);
        }
        else if (code == F_execute_busy) {
          fl_print_format("%[' required resources are unavailable, too busy.%]%c", print->to.stream, print->context, print->context, f_string_eol_s[0]);
        }
        else if (code == F_execute_capability) {
          fl_print_format("%[' failed to setup capabilities.%]%c", print->to.stream, print->context, print->context, f_string_eol_s[0]);
        }
        else if (code == F_execute_control_group) {
          fl_print_format("%[' failed to setup control group.%]%c", print->to.stream, print->context, print->context, f_string_eol_s[0]);
        }
        else if (code == F_execute_child) {
          fl_print_format("%[' failed to setup child process.%]%c", print->to.stream, print->context, print->context, f_string_eol_s[0]);
        }
        else if (code == F_execute_directory_not) {
          fl_print_format("%[' invalid path, part of the path is not a valid directory.%]%c", print->to.stream, print->context, print->context, f_string_eol_s[0]);
        }
        else if (code == F_execute_failure) {
          fl_print_format("%[' failed during execution.%]%c", print->to.stream, print->context, print->context, f_string_eol_s[0]);
        }
        else if (code == F_execute_file_found_not) {
          fl_print_format("%[' could not be executed, unable to find file.%]%c", print->to.stream, print->context, print->context, f_string_eol_s[0]);
        }
        else if (code == F_execute_file_type_directory) {
          fl_print_format("%[' ELF interpreter is a directory.%]%c", print->to.stream, print->context, print->context, f_string_eol_s[0]);
        }
        else if (code == F_execute_fork_not) {
          fl_print_format("%[' fork failure.%]%c", print->to.stream, print->context, print->context, f_string_eol_s[0]);
        }
        else if (code == F_execute_format_not) {
          fl_print_format("%[' could not be executed because the program has an invalid ELF header.%]%c", print->to.stream, print->context, print->context, f_string_eol_s[0]);
        }
        else if (code == F_execute_group) {
          fl_print_format("%[' failed to setup group.%]%c", print->to.stream, print->context, print->context, f_string_eol_s[0]);
        }
        else if (code == F_execute_input_output) {
          fl_print_format("%[' I/O failure.%]%c", print->to.stream, print->context, print->context, f_string_eol_s[0]);
        }
        else if (code == F_execute_limit) {
          fl_print_format("%[' failed to setup resource limits.%]%c", print->to.stream, print->context, print->context, f_string_eol_s[0]);
        }
        else if (code == F_execute_loop) {
          fl_print_format("%[' max recursion reached.%]%c", print->to.stream, print->context, print->context, f_string_eol_s[0]);
        }
        else if (code == F_execute_memory_not) {
          fl_print_format("%[' out of memory.%]%c", print->to.stream, print->context, print->context, f_string_eol_s[0]);
        }
        else if (code == F_execute_name_not) {
          fl_print_format("%[' file name or path is too long.%]%c", print->to.stream, print->context, print->context, f_string_eol_s[0]);
        }
        else if (code == F_execute_nice) {
          fl_print_format("%[' failed to setup niceness.%]%c", print->to.stream, print->context, print->context, f_string_eol_s[0]);
        }
        else if (code == F_execute_parameter) {
          fl_print_format("%[' invalid parameter.%]%c", print->to.stream, print->context, print->context, f_string_eol_s[0]);
        }
        else if (code == F_execute_pipe) {
          fl_print_format("%[' pipe failed.%]%c", print->to.stream, print->context, print->context, f_string_eol_s[0]);
        }
        else if (code == F_execute_processor) {
          fl_print_format("%[' failed to setup processor affinity.%]%c", print->to.stream, print->context, print->context, f_string_eol_s[0]);
        }
        else if (code == F_execute_prohibited) {
          fl_print_format("%[' access prohibited.%]%c", print->to.stream, print->context, print->context, f_string_eol_s[0]);
        }
        else if (code == F_execute_resource_not) {
          fl_print_format("%[' resource limit reached.%]%c", print->to.stream, print->context, print->context, f_string_eol_s[0]);
        }
        else if (code == F_execute_schedule) {
          fl_print_format("%[' failed to setup scheduler.%]%c", print->to.stream, print->context, print->context, f_string_eol_s[0]);
        }
        else if (code == F_execute_terminal) {
          fl_print_format("%[' failed while processing the terminal.%]%c", print->to.stream, print->context, print->context, f_string_eol_s[0]);
        }
        else if (code == F_execute_terminal_known_not) {
          fl_print_format("%[' cannot process terminal, unknown terminal control command.%]%c", print->to.stream, print->context, print->context, f_string_eol_s[0]);
        }
        else if (code == F_execute_terminal_not) {
          fl_print_format("%[' cannot process terminal, not a known terminal.%]%c", print->to.stream, print->context, print->context, f_string_eol_s[0]);
        }
        else if (code == F_execute_terminal_prohibited) {
          fl_print_format("%[' insufficient permissions to process the terminal.%]%c", print->to.stream, print->context, print->context, f_string_eol_s[0]);
        }
        else if (code == F_execute_terminal_valid_not) {
          fl_print_format("%[' invalid parameter while processing the terminal.%]%c", print->to.stream, print->context, print->context, f_string_eol_s[0]);
        }
        else if (code == F_execute_too_large) {
          fl_print_format("%[' too many arguments or arguments are too large.%]%c", print->to.stream, print->context, print->context, f_string_eol_s[0]);
        }
        else if (code == F_execute_user) {
          fl_print_format("%[' failed to setup user.%]%c", print->to.stream, print->context, print->context, f_string_eol_s[0]);
        }
        else if (code == F_execute_valid_not) {
          fl_print_format("%[' unknown ELF interpreter format.%]%c", print->to.stream, print->context, print->context, f_string_eol_s[0]);
        }
        else {
          fl_print_format("%[' failed with the execute error code %]", print->to.stream, print->context, print->context);
          fl_print_format("%[%i%]", print->to.stream, print->notable, code, print->notable);
          fl_print_format("%[.%]%c", print->to.stream, print->context, print->context, f_string_eol_s[0]);
        }
      }
      else {
        fl_print_format("%[' failed.%]%c", print->to.stream, print->context, print->context, f_string_eol_s[0]);
      }

      controller_unlock_print_flush(print->to, (controller_thread_t *) process->main_thread);
    }
  }
#endif // _di_controller_rule_item_print_error_execute_

#ifndef _di_controller_rule_action_print_error_missing_pid_
  void controller_rule_action_print_error_missing_pid(const fl_print_t print, const f_string_t alias) {

    if (print.verbosity == f_console_verbosity_quiet) return;

    fl_print_format("%c%[%SThe rule '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, print.context);
    fl_print_format("%[%S%]", print.to.stream, print.notable, alias, print.notable);
    fl_print_format("%[' is not designating a pid file.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);
  }
#endif // _di_controller_rule_action_print_error_missing_pid_

#ifndef _di_controller_rule_item_print_error_need_want_wish_
  void controller_rule_item_print_error_need_want_wish(const fl_print_t print, const f_string_t need_want_wish, const f_string_t value, const f_string_t why) {

    if (print.verbosity == f_console_verbosity_quiet) return;

    fl_print_format("%c%[%SThe %s rule '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, need_want_wish, print.context);
    fl_print_format("%[%S%]", print.to.stream, print.notable, value, print.notable);
    fl_print_format("%[' %S.%]%c", print.to.stream, print.context, why, print.context, f_string_eol_s[0]);
  }
#endif // _di_controller_rule_item_print_error_need_want_wish_

#ifndef _di_controller_rule_item_print_error_rule_not_loaded_
  void controller_rule_item_print_error_rule_not_loaded(const fl_print_t print, const f_string_t alias) {

    if (print.verbosity == f_console_verbosity_quiet) return;

    fl_print_format("%c%[%SThe rule '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, print.context);
    fl_print_format("%[%S%]", print.to.stream, print.notable, alias, print.notable);
    fl_print_format("%[' is no longer loaded.%]%c", print.to.stream, print.context, print.context, f_string_eol_s[0]);
  }
#endif // _di_controller_rule_item_print_error_rule_not_loaded_

#ifndef _di_controller_rule_setting_read_print_error_
  void controller_rule_setting_read_print_error(const fl_print_t print, const f_string_t message, const f_array_length_t index, const f_array_length_t line_item, controller_thread_t *thread, controller_cache_t *cache) {

    if (print.verbosity == f_console_verbosity_quiet) return;

    // get the current line number within the settings item.
    cache->action.line_item = line_item;
    f_fss_count_lines(cache->buffer_item, cache->object_actions.array[index].start, &cache->action.line_item);

    cache->action.line_action = ++cache->action.line_item;

    controller_lock_print(print.to, thread);

    fl_print_format("%c%[%SRule setting %S.%]%c", print.to.stream, f_string_eol_s[0], print.context, print.prefix, message, print.context, f_string_eol_s[0]);

    controller_rule_print_error_cache(print, cache->action, F_false);

    controller_unlock_print_flush(print.to, thread);
  }
#endif // _di_controller_rule_setting_read_print_error_

#ifndef _di_controller_rule_setting_read_print_error_with_range_
  void controller_rule_setting_read_print_error_with_range(const fl_print_t print, const f_string_t before, const f_string_range_t range, const f_string_t after, const f_array_length_t index, const f_array_length_t line_item, controller_thread_t *thread, controller_cache_t *cache) {

    if (print.verbosity == f_console_verbosity_quiet) return;

    // get the current line number within the settings item.
    cache->action.line_item = line_item;
    f_fss_count_lines(cache->buffer_item, cache->object_actions.array[index].start, &cache->action.line_item);

    cache->action.line_action = ++cache->action.line_item;

    controller_lock_print(print.to, thread);

    fl_print_format("%c%[%SRule setting %S '%]", print.to.stream, f_string_eol_s[0], print.context, print.prefix, before, print.context);
    fl_print_format("%[%/Q%]", print.to.stream, print.notable, cache->buffer_item, range, print.notable);
    fl_print_format("%['%S.%]%c", print.to.stream, print.context, after, print.context, f_string_eol_s[0]);

    controller_rule_print_error_cache(print, cache->action, F_false);

    controller_unlock_print_flush(print.to, thread);
  }
#endif // _di_controller_rule_setting_read_print_error_with_range_

#ifndef _di_controller_rule_setting_read_print_value_
  void controller_rule_setting_read_print_value(const controller_global_t global, const f_string_t name, const f_string_t name_sub, const f_string_static_t value, const f_string_t suffix) {

    if (global.main->error.verbosity != f_console_verbosity_debug && !(global.main->error.verbosity == f_console_verbosity_verbose && global.main->parameters[controller_parameter_simulate].result == f_console_result_found)) {
      return;
    }

    controller_lock_print(global.main->output.to, global.thread);

    fl_print_format("%cProcessing rule item action '%[%S%]' setting ", global.main->output.to.stream, f_string_eol_s[0], global.main->context.set.title, name, global.main->context.set.title);

    if (name_sub) {
      fl_print_format("'%[%S%]'", global.main->output.to.stream, global.main->context.set.notable, name_sub, global.main->context.set.notable);
    }
    else {
      f_print_terminated("value", global.main->output.to.stream);
    }

    fl_print_format(" to '%[%Q%]'", global.main->output.to.stream, global.main->context.set.important, value, global.main->context.set.important);
    fl_print_format("%S.%c", global.main->output.to.stream, suffix, f_string_eol_s[0]);

    controller_unlock_print_flush(global.main->output.to, global.thread);
  }
#endif // _di_controller_rule_setting_read_print_value_

#ifndef _di_controller_rule_setting_read_print_values_
  void controller_rule_setting_read_print_values(const controller_global_t global, const f_string_t name, const f_array_length_t index, controller_cache_t *cache) {

    if (global.main->error.verbosity != f_console_verbosity_debug && !(global.main->error.verbosity == f_console_verbosity_verbose && global.main->parameters[controller_parameter_simulate].result == f_console_result_found)) {
      return;
    }

    controller_lock_print(global.main->output.to, global.thread);

    fl_print_format("%cProcessing rule item action '%[%S%]' setting value to", global.main->output.to.stream, f_string_eol_s[0], global.main->context.set.title, name, global.main->context.set.title);

    for (f_array_length_t j = 0; j < cache->content_actions.array[index].used; ++j) {

      fl_print_format(" '%[%/Q%]'", global.main->output.to.stream, global.main->context.set.important, cache->buffer_item, cache->content_actions.array[index].array[j], global.main->context.set.important);

      if (j + 2 == cache->content_actions.array[index].used) {
        if (cache->content_actions.array[index].used > 2) {
          f_print_terminated(",", global.main->output.to.stream);
        }

        f_print_terminated(" and", global.main->output.to.stream);
      }
      else if (j + 1 < cache->content_actions.array[index].used) {
        f_print_terminated(",", global.main->output.to.stream);
      }
    } // for

    fl_print_format(".%c", global.main->output.to.stream, f_string_eol_s[0]);

    controller_unlock_print_flush(global.main->output.to, global.thread);
  }
#endif // _di_controller_rule_setting_read_print_value_

#ifdef __cplusplus
} // extern "C"
#endif