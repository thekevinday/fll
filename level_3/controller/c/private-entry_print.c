#include "controller.h"
#include "private-common.h"
#include "private-entry_print.h"
#include "private-lock_print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_entry_action_parameters_print_
  void controller_entry_action_parameters_print(FILE * const stream, const controller_entry_action_t action) {

    for (f_array_length_t index = 0; ;) {

      f_print_dynamic_safely(action.parameters.array[index], stream);

      ++index;

      if (index == action.parameters.used) break;

      f_print_terminated(f_string_space_s, stream);
    } // for
  }
#endif // _di_controller_entry_action_parameters_print_

#ifndef _di_controller_entry_preprocess_print_simulate_setting_value_
  void controller_entry_preprocess_print_simulate_setting_value(const bool is_entry, const controller_global_t global, const f_string_t name, const f_string_t name_sub, const f_string_static_t value, const f_string_t suffix) {

    if (global.main->error.verbosity != f_console_verbosity_debug && !(global.main->error.verbosity == f_console_verbosity_verbose && global.main->parameters[controller_parameter_simulate].result == f_console_result_found)) {
      return;
    }

    controller_lock_print(global.main->output.to, global.thread);

    fl_print_format("%cProcessing %s item action '", global.main->output.to.stream, f_string_eol_s[0], is_entry ? controller_entry_s : controller_exit_s);

    fl_print_format("%[%S%]' setting ", global.main->output.to.stream, global.main->context.set.title, name, global.main->context.set.title);

    if (name_sub) {
      fl_print_format("'%[%S%]'", global.main->output.to.stream, global.main->context.set.notable, name_sub, global.main->context.set.notable);
    }
    else {
      fl_print_format("value", global.main->output.to.stream);
    }

    fl_print_format(" to '%[%Q%]", global.main->output.to.stream, global.main->context.set.important, value, global.main->context.set.important);

    fl_print_format("'%S.%c", global.main->output.to.stream, suffix, f_string_eol_s[0]);

    controller_unlock_print_flush(global.main->output.to, global.thread);
  }
#endif // _di_controller_entry_preprocess_print_simulate_setting_value_

#ifndef _di_controller_entry_print_error_
  void controller_entry_print_error(const bool is_entry, const fl_print_t print, const controller_cache_action_t cache, const f_status_t status, const f_string_t function, const bool fallback, controller_thread_t *thread) {

    if (print.verbosity == f_console_verbosity_quiet) return;
    if (status == F_interrupt) return;

    // fll_error_print() automatically locks, so manually handle only the mutex locking and flushing rather than calling controller_lock_print().
    f_thread_mutex_lock(&thread->lock.print);

    fll_error_print(print, status, function, fallback);

    flockfile(print.to.stream);

    controller_entry_print_error_cache(is_entry, print, cache);

    controller_unlock_print_flush(print.to, thread);
  }
#endif // _di_controller_entry_print_error_

#ifndef _di_controller_entry_print_error_cache_
  void controller_entry_print_error_cache(const bool is_entry, const fl_print_t output, const controller_cache_action_t cache) {

    fl_print_format("%c%[%SWhile processing ", output.to.stream, f_string_eol_s[0], output.context, output.prefix);

    if (cache.name_action.used) {
      fl_print_format("action '%]", output.to.stream, output.context);
      fl_print_format("%[%Q%]", output.to.stream, output.notable, cache.name_action, output.notable);
      fl_print_format("%[' on line%] ", output.to.stream, output.context, output.context);
      fl_print_format("%[%un%]", output.to.stream, output.notable, cache.line_action, output.notable);
      fl_print_format("%[ for ", output.to.stream, output.context);
    }

    if (cache.name_item.used) {
      fl_print_format("%s item '%]", output.to.stream, is_entry ? controller_entry_s : controller_exit_s, output.context);
      fl_print_format("%[%Q%]", output.to.stream, output.notable, cache.name_item, output.notable);
      fl_print_format("%[' on line%] ", output.to.stream, output.context, output.context);
      fl_print_format("%[%un%]", output.to.stream, output.notable, cache.line_item, output.notable);
      fl_print_format("%[ for ", output.to.stream, output.context);
    }

    if (cache.name_file.used) {
      fl_print_format("%s file '%]", output.to.stream, is_entry ? controller_entry_s : controller_exit_s, output.context);
      fl_print_format("%[%Q%]%['", output.to.stream, output.notable, cache.name_file, output.notable, output.context);
    }

    fl_print_format(".%]%c", output.to.stream, output.context, f_string_eol_s[0]);
  }
#endif // _di_controller_entry_print_error_cache_

#ifndef _di_controller_entry_settings_read_print_setting_requires_exactly_
  void controller_entry_settings_read_print_setting_requires_exactly(const bool is_entry, const controller_global_t global, const controller_cache_t cache, const f_number_unsigned_t total) {

    if (global.main->error.verbosity == f_console_verbosity_quiet) return;

    controller_lock_print(global.main->error.to, global.thread);

    fl_print_format("%c%[%SThe %s item setting '%]", global.main->error.to.stream, f_string_eol_s[0], global.main->error.context, global.main->error.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->error.context);
    fl_print_format("%[%Q%]", global.main->error.to.stream, global.main->error.notable, cache.action.name_action, global.main->error.notable);
    fl_print_format("%[' requires exactly %]", global.main->error.to.stream, global.main->error.context, global.main->error.context);
    fl_print_format("%[%un%]", global.main->error.to.stream, global.main->error.notable, total, global.main->error.notable);
    fl_print_format("%[' %s.%]%c", global.main->error.to.stream, global.main->error.context, total > 1 ? controller_parameters_s : controller_parameter_s, global.main->error.context, f_string_eol_s[0]);

    controller_entry_print_error_cache(is_entry, global.main->error, cache.action);

    controller_unlock_print_flush(global.main->error.to, global.thread);
  }
#endif // _di_controller_entry_settings_read_print_setting_requires_exactly_

#ifndef _di_controller_entry_settings_read_print_setting_unknown_action_
  void controller_entry_settings_read_print_setting_unknown_action(const bool is_entry, const controller_global_t global, const controller_cache_t cache) {

    if (global.main->warning.verbosity != f_console_verbosity_debug) return;

    controller_lock_print(global.main->warning.to, global.thread);

    fl_print_format("%c%[%SUnknown %s item setting '%]", global.main->warning.to.stream, f_string_eol_s[0], global.main->warning.context, global.main->warning.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->warning.context);
    fl_print_format("%[%Q%]", global.main->warning.to.stream, global.main->warning.notable, cache.action.name_action, global.main->warning.notable);
    fl_print_format("%['.%]%c", global.main->warning.to.stream, global.main->warning.context, global.main->warning.context, f_string_eol_s[0]);

    controller_entry_print_error_cache(is_entry, global.main->warning, cache.action);

    controller_unlock_print_flush(global.main->warning.to, global.thread);
  }
#endif // _di_controller_entry_settings_read_print_setting_unknown_action_

#ifndef _di_controller_entry_settings_read_print_setting_unknown_action_value_
  void controller_entry_settings_read_print_setting_unknown_action_value(const bool is_entry, const controller_global_t global, const controller_cache_t cache, const f_array_length_t index) {

    if (global.main->warning.verbosity != f_console_verbosity_debug) return;

    controller_lock_print(global.main->warning.to, global.thread);

    fl_print_format("%c%[%SThe %s item setting '%]", global.main->warning.to.stream, f_string_eol_s[0], global.main->warning.context, global.main->warning.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->warning.context);
    fl_print_format("%[%Q%]", global.main->warning.to.stream, global.main->warning.notable, cache.action.name_action, global.main->warning.notable);
    fl_print_format("%[' has an unknown value '%]", global.main->warning.to.stream, f_string_eol_s[0], global.main->warning.context, global.main->warning.prefix, is_entry ? controller_entry_s : controller_exit_s, global.main->warning.context);
    fl_print_format("%[%Q%]", global.main->warning.to.stream, global.main->warning.notable, cache.content_actions.array[index].array[0], global.main->warning.notable);
    fl_print_format("%['.%]%c", global.main->warning.to.stream, global.main->warning.context, global.main->warning.context, f_string_eol_s[0]);

    controller_entry_print_error_cache(is_entry, global.main->warning, cache.action);

    controller_unlock_print_flush(global.main->warning.to, global.thread);
  }
#endif // _di_controller_entry_settings_read_print_setting_unknown_action_value_

#ifdef __cplusplus
} // extern "C"
#endif
