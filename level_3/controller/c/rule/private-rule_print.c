#include "../controller.h"
#include "../common/private-common.h"
#include "../rule/private-rule_print.h"
#include "../lock/private-lock_print.h"

#ifdef __cplusplus
extern "C" {
#endif
#ifndef _di_controller_rule_print_string_s_
  const f_string_static_t controller_rule_print_control_groups_prepare_s = macro_f_string_static_t_initialize(CONTROLLER_rule_print_control_groups_prepare_s, 0, CONTROLLER_rule_print_control_groups_prepare_s_length);
#endif // _di_controller_rule_print_string_s_

#ifndef _di_controller_rule_print_error_
  void controller_rule_print_error(controller_thread_t * const thread, const fl_print_t print, const controller_cache_action_t cache, const f_status_t status, const char *function, const bool fallback, const bool item) {

    if (print.verbosity == f_console_verbosity_quiet_e) return;
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

    if (print.verbosity == f_console_verbosity_quiet_e) return;

    fl_print_format("%r%[%QWhile processing ", print.to.stream, f_string_eol_s, print.context, print.prefix);

    if (cache.name_action.used) {
      fl_print_format("%r '%]", print.to.stream, item ? controller_action_s : controller_value_s, print.context);
      fl_print_format("%[%Q%]", print.to.stream, print.notable, cache.name_action, print.notable);
      fl_print_format("%[' on line%] ", print.to.stream, print.context, print.context);
      fl_print_format("%[%un%]", print.to.stream, print.notable, cache.line_action, print.notable);
      fl_print_format("%[ for ", print.to.stream, print.context);
    }

    if (cache.name_item.used) {
      fl_print_format("rule %r '%]", print.to.stream, item ? controller_item_s : controller_settings_s, print.context);
      fl_print_format("%[%Q%]", print.to.stream, print.notable, cache.name_item, print.notable);
      fl_print_format("%[' on line%] ", print.to.stream, print.context, print.context);
      fl_print_format("%[%un%]", print.to.stream, print.notable, cache.line_item, print.notable);
      fl_print_format("%[ for ", print.to.stream, print.context);
    }

    if (cache.name_file.used) {
      fl_print_format("rule file '%]%[%Q%]%['", print.to.stream, print.context, print.notable, cache.name_file, print.notable, print.context);
    }

    fl_print_format(".%]%r", print.to.stream, print.context, f_string_eol_s);
  }
#endif // _di_controller_rule_print_error_cache_

#ifndef _di_controller_rule_item_print_error_
  void controller_rule_item_print_error(controller_thread_t * const thread, const fl_print_t print, const controller_cache_action_t cache, const bool item, const f_status_t status) {

    if (print.verbosity == f_console_verbosity_quiet_e) return;
    if (status == F_interrupt) return;

    // fll_error_print() automatically locks, so manually handle only the mutex locking and flushing rather than calling controller_lock_print().
    f_thread_mutex_lock(&thread->lock.print);

    controller_rule_print_error_cache(print, cache, item);

    flockfile(print.to.stream);

    controller_unlock_print_flush(print.to, thread);
  }
#endif // _di_controller_rule_item_print_error_

#ifndef _di_controller_rule_item_print_error_execute_
  void controller_rule_item_print_error_execute(const bool script_is, const f_string_static_t name, const f_status_t status, controller_process_t * const process) {

    if (((controller_main_t *) process->main_data)->error.verbosity != f_console_verbosity_quiet_e) {
      fl_print_t * const print = &((controller_main_t *) process->main_data)->error;

      controller_lock_print(print->to, (controller_thread_t *) process->main_thread);

      fl_print_format("%r%[%QThe %r '%]", print->to.stream, f_string_eol_s, print->context, print->prefix, script_is ? controller_engine_s : controller_program_s, print->context);
      fl_print_format("%[%Q%]", print->to.stream, print->notable, name, print->notable);

      if (status == F_control_group || status == F_limit || status == F_processor || status == F_schedule) {
        fl_print_format("%[' failed to setup the '%]%[", print->to.stream, print->context, print->context, print->notable);

        if (status == F_control_group) {
          f_print_dynamic_raw(controller_cgroup_s, print->to.stream);
        }
        else if (status == F_limit) {
          f_print_dynamic_raw(controller_limit_s, print->to.stream);
        }
        else if (status == F_processor) {
          f_print_dynamic_raw(controller_processor_s, print->to.stream);
        }
        else if (status == F_schedule) {
          f_print_dynamic_raw(controller_scheduler_s, print->to.stream);
        }

        fl_print_format("%]%['.%]%r", print->to.stream, print->notable, print->context, print->context, f_string_eol_s);
      }
      else if (WIFEXITED(process->result) ? WEXITSTATUS(process->result) : 0) {
        const uint8_t code = WIFEXITED(process->result) ? WEXITSTATUS(process->result) : 0;

        if (code == F_execute_access) {
          fl_print_format("%[' failed, access is denied.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_bad) {
          fl_print_format("%[' failed, unsupported format.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_buffer) {
          fl_print_format("%[' invalid memory access in arguments buffer.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_busy) {
          fl_print_format("%[' required resources are unavailable, too busy.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_capability) {
          fl_print_format("%[' failed to setup capabilities.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_control_group) {
          fl_print_format("%[' failed to setup control group.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_child) {
          fl_print_format("%[' failed to setup child process.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_directory_not) {
          fl_print_format("%[' invalid path, part of the path is not a valid directory.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_failure) {
          fl_print_format("%[' failed during execution.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_file_found_not) {
          fl_print_format("%[' failed, unable to find file.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_file_type_directory) {
          fl_print_format("%[' ELF interpreter is a directory.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_fork_not) {
          fl_print_format("%[' fork failure.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_format_not) {
          fl_print_format("%[' could not be executed because the program has an invalid ELF header.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_group) {
          fl_print_format("%[' failed to setup group.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_input_output) {
          fl_print_format("%[' I/O failure.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_limit) {
          fl_print_format("%[' failed to setup resource limits.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_loop) {
          fl_print_format("%[' max recursion reached.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_memory_not) {
          fl_print_format("%[' is out of memory.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_name_not) {
          fl_print_format("%[' file name or path is too long.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_nice) {
          fl_print_format("%[' failed to setup niceness.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_parameter) {
          fl_print_format("%[' failed due to an invalid parameter.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_pipe) {
          fl_print_format("%[' pipe failed.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_processor) {
          fl_print_format("%[' failed to setup processor affinity.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_prohibited) {
          fl_print_format("%[' access prohibited.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_resource_not) {
          fl_print_format("%[' resource limit reached.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_schedule) {
          fl_print_format("%[' failed to setup scheduler.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_terminal) {
          fl_print_format("%[' failed while processing the terminal.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_terminal_known_not) {
          fl_print_format("%[' cannot process terminal, unknown terminal control command.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_terminal_not) {
          fl_print_format("%[' cannot process terminal, not a known terminal.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_terminal_prohibited) {
          fl_print_format("%[' insufficient permissions to process the terminal.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_terminal_valid_not) {
          fl_print_format("%[' invalid parameter while processing the terminal.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_too_large) {
          fl_print_format("%[' too many arguments or arguments are too large.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_user) {
          fl_print_format("%[' failed to setup user.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_valid_not) {
          fl_print_format("%[' unknown ELF interpreter format.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_invoke_not) {
          fl_print_format("%[' cannot execute command.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_found_not) {
          fl_print_format("%[' command not found.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_found_not) {
          fl_print_format("%[' invalid argument to exit().%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_signal_hangup) {
          fl_print_format("%[' hang up signal received.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_signal_interrupt) {
          fl_print_format("%[' interrupt signal received.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_signal_quit) {
          fl_print_format("%[' quit signal received.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_signal_illegal) {
          fl_print_format("%[' illegal signal received.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_signal_trap) {
          fl_print_format("%[' trap signal received.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_signal_abort) {
          fl_print_format("%[' abort signal received.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_signal_bus_error) {
          fl_print_format("%[' bus error signal received.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_signal_floating_point_error) {
          fl_print_format("%[' floating point error signal received.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_signal_kill) {
          fl_print_format("%[' kill signal received.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_signal_user_1) {
          fl_print_format("%[' user 1 signal received.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_signal_segmentation_fault) {
          fl_print_format("%[' segmentation fault signal received.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_signal_user_2) {
          fl_print_format("%[' user 2 signal received.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_signal_broken_pipe) {
          fl_print_format("%[' broken pipe signal received.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_signal_alarm_clock) {
          fl_print_format("%[' alarm clock signal received.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_signal_termination) {
          fl_print_format("%[' terminate signal received.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_signal_stack_fault) {
          fl_print_format("%[' stack fault signal received.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_signal_child) {
          fl_print_format("%[' child signal received.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_signal_continue) {
          fl_print_format("%[' continue signal received.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_signal_stop) {
          fl_print_format("%[' stop signal received.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_signal_keyboard_stop) {
          fl_print_format("%[' keyboard stop signal received.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_signal_tty_in) {
          fl_print_format("%[' TTY in signal received.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_signal_tty_out) {
          fl_print_format("%[' TTY out signal received.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_signal_urgent) {
          fl_print_format("%[' urgent signal received.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_signal_cpu_limit) {
          fl_print_format("%[' CPU limit signal received.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_signal_file_size_limit) {
          fl_print_format("%[' file size signal received.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_signal_virtual_alarm_clock) {
          fl_print_format("%[' virtual alarm clock signal received.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_signal_profile_alarm_clock) {
          fl_print_format("%[' profile alarm clock signal received.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_signal_window_size_change) {
          fl_print_format("%[' window size change signal received.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_signal_pollable_event) {
          fl_print_format("%[' pollable signal received.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_signal_power_failure) {
          fl_print_format("%[' power failure signal received.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else if (code == F_execute_signal_bad_system_call) {
          fl_print_format("%[' bad system call signal received.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
        else {
          fl_print_format("%[' failed with the execute error code %]", print->to.stream, print->context, print->context);
          fl_print_format("%[%i%]", print->to.stream, print->notable, code, print->notable);
          fl_print_format("%[.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
        }
      }
      else {
        fl_print_format("%[' failed.%]%r", print->to.stream, print->context, print->context, f_string_eol_s);
      }

      controller_unlock_print_flush(print->to, (controller_thread_t *) process->main_thread);
    }
  }
#endif // _di_controller_rule_item_print_error_execute_

#ifndef _di_controller_rule_action_print_error_missing_pid_
  void controller_rule_action_print_error_missing_pid(const fl_print_t print, const f_string_static_t alias) {

    if (print.verbosity == f_console_verbosity_quiet_e) return;

    fl_print_format("%r%[%QThe rule '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, print.context);
    fl_print_format("%[%Q%]", print.to.stream, print.notable, alias, print.notable);
    fl_print_format("%[' is not designating a pid file.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);
  }
#endif // _di_controller_rule_action_print_error_missing_pid_

#ifndef _di_controller_rule_item_print_error_need_want_wish_
  void controller_rule_item_print_error_need_want_wish(const fl_print_t print, const f_string_static_t need_want_wish, const f_string_static_t value, const f_string_t why) {

    if (print.verbosity == f_console_verbosity_quiet_e) return;

    fl_print_format("%r%[%QThe %r rule '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, need_want_wish, print.context);
    fl_print_format("%[%Q%]", print.to.stream, print.notable, value, print.notable);
    fl_print_format("%[' %S.%]%r", print.to.stream, print.context, why, print.context, f_string_eol_s);
  }
#endif // _di_controller_rule_item_print_error_need_want_wish_

#ifndef _di_controller_rule_item_print_error_rule_not_loaded_
  void controller_rule_item_print_error_rule_not_loaded(const fl_print_t print, const f_string_static_t alias) {

    if (print.verbosity == f_console_verbosity_quiet_e) return;

    fl_print_format("%r%[%QThe rule '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, print.context);
    fl_print_format("%[%Q%]", print.to.stream, print.notable, alias, print.notable);
    fl_print_format("%[' is no longer loaded.%]%r", print.to.stream, print.context, print.context, f_string_eol_s);
  }
#endif // _di_controller_rule_item_print_error_rule_not_loaded_

#ifndef _di_controller_rule_setting_read_print_error_
  void controller_rule_setting_read_print_error(const fl_print_t print, const f_string_t message, const f_array_length_t index, const f_array_length_t line_item, controller_thread_t * const thread, controller_cache_t * const cache) {

    if (print.verbosity == f_console_verbosity_quiet_e) return;

    f_state_t state = f_state_t_initialize;

    // Get the current line number within the settings item.
    cache->action.line_item = line_item;
    f_fss_count_lines(state, cache->buffer_item, cache->object_actions.array[index].start, &cache->action.line_item);

    cache->action.line_action = ++cache->action.line_item;

    controller_lock_print(print.to, thread);

    fl_print_format("%r%[%QRule setting %S.%]%r", print.to.stream, f_string_eol_s, print.context, print.prefix, message, print.context, f_string_eol_s);

    controller_rule_print_error_cache(print, cache->action, F_false);

    controller_unlock_print_flush(print.to, thread);
  }
#endif // _di_controller_rule_setting_read_print_error_

#ifndef _di_controller_rule_setting_read_print_error_with_range_
  void controller_rule_setting_read_print_error_with_range(const fl_print_t print, const f_string_t before, const f_string_range_t range, const f_string_t after, const f_array_length_t index, const f_array_length_t line_item, controller_thread_t * const thread, controller_cache_t * const cache) {

    if (print.verbosity == f_console_verbosity_quiet_e) return;

    f_state_t state = f_state_t_initialize;

    // Get the current line number within the settings item.
    cache->action.line_item = line_item;
    f_fss_count_lines(state, cache->buffer_item, cache->object_actions.array[index].start, &cache->action.line_item);

    cache->action.line_action = ++cache->action.line_item;

    controller_lock_print(print.to, thread);

    fl_print_format("%r%[%QRule setting%S '%]", print.to.stream, f_string_eol_s, print.context, print.prefix, before, print.context);
    fl_print_format("%[%/Q%]", print.to.stream, print.notable, cache->buffer_item, range, print.notable);
    fl_print_format("%['%S.%]%r", print.to.stream, print.context, after, print.context, f_string_eol_s);

    controller_rule_print_error_cache(print, cache->action, F_false);

    controller_unlock_print_flush(print.to, thread);
  }
#endif // _di_controller_rule_setting_read_print_error_with_range_

#ifndef _di_controller_rule_setting_read_print_mapping_
  void controller_rule_setting_read_print_mapping(const controller_global_t global, const f_string_static_t name, const f_string_map_t map) {

    if (global.main->error.verbosity != f_console_verbosity_debug_e && !(global.main->error.verbosity == f_console_verbosity_verbose_e && global.main->parameters.array[controller_parameter_simulate_e].result == f_console_result_found_e)) {
      return;
    }

    controller_lock_print(global.main->output.to, global.thread);

    fl_print_format("%rProcessing rule item action '%[%Q%]'", global.main->output.to.stream, f_string_eol_s, global.main->context.set.title, name, global.main->context.set.title);
    fl_print_format(" mapping '%[%Q%]'", global.main->output.to.stream, global.main->context.set.important, map.name, global.main->context.set.important);
    fl_print_format(" to value '%[%Q%]'.%r", global.main->output.to.stream, global.main->context.set.important, map.value, global.main->context.set.important, f_string_eol_s);

    controller_unlock_print_flush(global.main->output.to, global.thread);
  }
#endif // _di_controller_rule_setting_read_print_mapping_

#ifndef _di_controller_rule_setting_read_print_value_
  void controller_rule_setting_read_print_value(const controller_global_t global, const f_string_static_t name, const f_string_static_t name_sub, const f_string_static_t value, const f_string_t suffix) {

    if (global.main->error.verbosity != f_console_verbosity_debug_e && !(global.main->error.verbosity == f_console_verbosity_verbose_e && global.main->parameters.array[controller_parameter_simulate_e].result == f_console_result_found_e)) {
      return;
    }

    controller_lock_print(global.main->output.to, global.thread);

    fl_print_format("%rProcessing rule item action '%[%Q%]' setting ", global.main->output.to.stream, f_string_eol_s, global.main->context.set.title, name, global.main->context.set.title);

    if (name_sub.used) {
      fl_print_format("'%[%Q%]'", global.main->output.to.stream, global.main->context.set.notable, name_sub, global.main->context.set.notable);
    }
    else {
      f_print_terminated("value", global.main->output.to.stream);
    }

    fl_print_format(" to '%[%Q%]'", global.main->output.to.stream, global.main->context.set.important, value, global.main->context.set.important);
    fl_print_format("%S.%r", global.main->output.to.stream, suffix, f_string_eol_s);

    controller_unlock_print_flush(global.main->output.to, global.thread);
  }
#endif // _di_controller_rule_setting_read_print_value_

#ifndef _di_controller_rule_setting_read_print_values_
  void controller_rule_setting_read_print_values(const controller_global_t global, const f_string_static_t name, const f_array_length_t index, controller_cache_t * const cache) {

    if (global.main->error.verbosity != f_console_verbosity_debug_e && !(global.main->error.verbosity == f_console_verbosity_verbose_e && global.main->parameters.array[controller_parameter_simulate_e].result == f_console_result_found_e)) {
      return;
    }

    controller_lock_print(global.main->output.to, global.thread);

    fl_print_format("%rProcessing rule item action '%[%Q%]' setting value to", global.main->output.to.stream, f_string_eol_s, global.main->context.set.title, name, global.main->context.set.title);

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

    fl_print_format(".%r", global.main->output.to.stream, f_string_eol_s);

    controller_unlock_print_flush(global.main->output.to, global.thread);
  }
#endif // _di_controller_rule_setting_read_print_value_

#ifdef __cplusplus
} // extern "C"
#endif
