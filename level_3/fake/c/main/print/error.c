#include "../fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_print_error_
  f_status_t fake_print_error(fl_print_t * const print, const f_string_t function) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_setting_t * const setting = (fake_setting_t *) print->custom;

    if (setting) {
      fll_error_print(*print, F_status_set_fine(setting->state.status), function, fll_error_file_flag_fallback_e);
    }

    return F_none;
  }
#endif // _di_fake_print_error_

#ifndef _di_fake_print_error_argument_empty_
  f_status_t fake_print_error_argument_empty(fake_setting_t * const setting, const fl_print_t print, const f_array_length_t index) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    fake_print_context_wrapped_number(setting, print, "The ", (f_number_unsigned_t) index, " argument must not be an empty string");

    return F_none;
  }
#endif // _di_fake_print_error_argument_empty_

#ifndef _di_fake_print_error_build_operation_file_
  f_status_t fake_print_error_build_operation_file(fake_setting_t * const setting, const fl_print_t print, const f_string_t function, const f_string_static_t operation, const f_string_static_t source, const f_string_static_t destination, const f_string_static_t how, const bool fallback) {

    if (!setting) return F_status_set_error(F_output_not);

    if (F_status_set_fine(setting->state.status) == F_file_found_not) {
      if (print.verbosity > f_console_verbosity_quiet_e) {
        f_file_stream_lock(print.to);

        fl_print_format("%[%QFailed to find '%]", print.to, print.context, print.prefix, print.context);
        fl_print_format("%[%Q%]", print.to, print.notable, source, print.notable);
        fl_print_format("%[' ", print.to, print.context);

        fake_print_error_build_operation_file_partial(setting, print, operation, source, destination, how);

        fl_print_format(".%]%r", print.to, print.context, f_string_eol_s);

        f_file_stream_unlock(print.to);
      }

      return F_false;
    }

    if (F_status_set_fine(setting->state.status) == F_parameter) {
      if (print.verbosity > f_console_verbosity_quiet_e) {
        f_file_stream_lock(print.to);

        fl_print_format("%[%QInvalid parameter when calling '%]", print.to, print.context, print.prefix, print.context);
        fl_print_format("%[%Q%]", print.to, print.notable, function, print.notable);
        fl_print_format("%[() ", print.to, print.context);

        fake_print_error_build_operation_file_partial(setting, print, operation, source, destination, how);

        fl_print_format(".%]%r", print.to, print.context, f_string_eol_s);

        f_file_stream_unlock(print.to);
      }

      return F_false;
    }

    if (F_status_set_fine(setting->state.status) == F_name) {
      if (print.verbosity > f_console_verbosity_quiet_e) {
        f_file_stream_lock(print.to);

        fl_print_format("%[%QInvalid name for '%]", print.to, print.context, print.prefix, print.context);

        if (source.used) {
          fl_print_format("%[%Q%]", print.to, print.notable, source, print.notable);
        }

        if (destination.used) {
          fl_print_format("%[' or '%]", print.to, print.context, print.context);
          fl_print_format("%[%Q%]", print.to, print.notable, destination, print.notable);
        }

        fl_print_format("%['.%]%r", print.to, print.context, print.context, f_string_eol_s);

        f_file_stream_unlock(print.to);
      }

      return F_false;
    }

    if (F_status_set_fine(setting->state.status) == F_memory_not) {
      if (print.verbosity > f_console_verbosity_quiet_e) {
        fake_print_error_build_operation_file_full(setting, print, "Unable to allocate memory, ", operation, source, destination, how, 0);
      }

      return F_false;
    }

    if (F_status_set_fine(setting->state.status) == F_number_overflow) {
      if (print.verbosity > f_console_verbosity_quiet_e) {
        fake_print_error_build_operation_file_full(setting, print, "Overflow ", operation, source, destination, how, 0);
      }

      return F_false;
    }

    if (F_status_set_fine(setting->state.status) == F_directory) {
      if (print.verbosity > f_console_verbosity_quiet_e) {
        fake_print_error_build_operation_file_full(setting, print, "Invalid directory ", operation, source, destination, how, 0);
      }

      return F_false;
    }

    if (F_status_set_fine(setting->state.status) == F_access_denied) {
      if (print.verbosity > f_console_verbosity_quiet_e) {
        fake_print_error_build_operation_file_full(setting, print, "Access denied ", operation, source, destination, how, 0);
      }

      return F_false;
    }

    if (F_status_set_fine(setting->state.status) == F_loop) {
      if (print.verbosity > f_console_verbosity_quiet_e) {
        fake_print_error_build_operation_file_full(setting, print, "Loop ", operation, source, destination, how, 0);
      }

      return F_false;
    }

    if (F_status_set_fine(setting->state.status) == F_prohibited) {
      if (print.verbosity > f_console_verbosity_quiet_e) {
        fake_print_error_build_operation_file_full(setting, print, "Prohibited by system ", operation, source, destination, how, 0);
      }

      return F_false;
    }

    if (F_status_set_fine(setting->state.status) == F_directory_found_not) {
      fake_print_error_build_operation_file_full(setting, print, "Failed ", operation, source, destination, how, "due to an invalid directory in the path");

      return F_false;
    }

    if (F_status_set_fine(setting->state.status) == F_failure) {
      if (print.verbosity > f_console_verbosity_quiet_e) {
        fake_print_error_build_operation_file_full(setting, print, "Failed ", operation, source, destination, how, 0);
      }

      return F_false;
    }

    if (fll_error_print(print, F_status_set_fine(setting->state.status), function, fll_error_file_flag_none_e) == F_known_not && fallback && print.verbosity > f_console_verbosity_quiet_e) {
      f_file_stream_lock(print.to);

      fl_print_format("%[UNKNOWN %Q(%]", print.to, print.context, print.prefix, print.context);
      fl_print_format("%[%ui%]", print.to, print.notable, F_status_set_fine(setting->state.status), print.notable);
      fl_print_format("%[) occurred ", print.to, print.context);

      fake_print_error_build_operation_file_partial(setting, print, operation, source, destination, how);

      fl_print_format(".%]%r", print.to, print.context, f_string_eol_s);

      f_file_stream_unlock(print.to);
    }

    return F_true;
  }
#endif // _di_fake_print_error_build_operation_file_

#ifndef _di_fake_print_error_build_operation_file_full_
  f_status_t fake_print_error_build_operation_file_full(fake_setting_t * const setting, const fl_print_t print, const f_string_t before, const f_string_static_t operation, const f_string_static_t source, const f_string_static_t destination, const f_string_static_t how, const f_string_t after) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print.to);

    fl_print_format("%[%Q%S", print.to, print.context, print.prefix, before);

    if (source.used) {
      fake_print_error_build_operation_file_partial(setting, print, operation, source, destination, how);
    }
    else {
      fl_print_format("%[", print.to, print.context);
    }

    fl_print_format("%S.%]%r", print.to, print.context, after, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_print_error_build_operation_file_full_

#ifndef _di_fake_print_error_build_operation_file_partial_
  void fake_print_error_build_operation_file_partial(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t operation, const f_string_static_t source, const f_string_static_t destination, const f_string_static_t how) {

    if (!setting) return;
    if (print.verbosity < f_console_verbosity_error_e || !source.used) return;

    fl_print_format("%[while trying to %Q '%]", print.to, print.context, operation, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, source, print.notable);

    if (destination.used) {
      fl_print_format("%[' %Q '%]", print.to, print.context, how, print.context);
      fl_print_format("%[%Q%]", print.to, print.notable, destination, print.notable);
    }

    fl_print_format("%['", print.to, print.context, print.context);
  }
#endif // _di_fake_print_error_build_operation_file_partial_

#ifndef _di_fake_print_error_directory_create_parent_missing_
  f_status_t fake_print_error_directory_create_parent_missing(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_print_context_wrapped_variable(setting, print, "The directory ", path, " could not be created, a parent directory is missing or invalid");

    return F_none;
  }
#endif // _di_fake_print_error_directory_create_parent_missing_

#ifndef _di_fake_print_error_execute_program_not_found_
  f_status_t fake_print_error_execute_program_not_found(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t program) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_print_context_simple_variable(setting, print, "Failed to find program ", program, " for executing");

    return F_none;
  }
#endif // _di_fake_print_error_execute_program_not_found_

#ifndef _di_fake_print_error_failure_operation_
  f_status_t fake_print_error_failure_operation(fake_setting_t * const setting, const fl_print_t print, const uint8_t operation) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print.to);

    fl_print_format("%[%QThe operation '%]%[", print.to, print.context, print.prefix, print.context, print.notable);

    if (operation == fake_operation_build_e) {
      f_print_dynamic(fake_other_operation_build_s, print.to);
    }
    else if (operation == fake_operation_clean_e) {
      f_print_dynamic(fake_other_operation_clean_s, print.to);
    }
    else if (operation == fake_operation_make_e) {
      f_print_dynamic(fake_other_operation_make_s, print.to);
    }
    else if (operation == fake_operation_skeleton_e) {
      f_print_dynamic(fake_other_operation_skeleton_s, print.to);
    }

    fl_print_format("%]%[' failed.%]%r", print.to, print.notable, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_print_error_failure_operation_

#ifndef _di_fake_print_error_failure_script_
  f_status_t fake_print_error_failure_script(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t script) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_print_context_wrapped_variable(setting, print, "Failed to execute script ", script, "");

    return F_none;
  }
#endif // _di_fake_print_error_failure_script_

#ifndef _di_fake_print_error_fallback_
  f_status_t fake_print_error_fallback(fake_setting_t * const setting, const fl_print_t print, const f_string_t function) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    if (fll_error_print(print, F_status_set_fine(setting->state.status), function, fll_error_file_flag_none_e) == F_known_not) return F_false;

    return F_true;
  }
#endif // _di_fake_print_error_fallback_

#ifndef _di_fake_print_error_file_
  f_status_t fake_print_error_file(fake_setting_t * const setting, const fl_print_t print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    fll_error_file_print(print, F_status_set_fine(setting->state.status), function, fll_error_file_flag_fallback_e, name, operation, type);

    return F_none;
  }
#endif // _di_fake_print_error_file_

#ifndef _di_fake_print_error_file_create_parent_missing_
  f_status_t fake_print_error_file_create_parent_missing(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t path) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_print_context_wrapped_variable(setting, print, "The file ", path, " could not be created, a parent directory is missing or invalid");

    return F_none;
  }
#endif // _di_fake_print_error_file_create_parent_missing_

#ifndef _di_fake_print_error_file_simple_
  f_status_t fake_print_error_file_simple(fake_setting_t * const setting, const fl_print_t print, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    fll_error_file_print(print, F_status_set_fine(setting->state.status), function, fll_error_file_flag_simple_e, name, operation, type);

    return F_none;
  }
#endif // _di_fake_print_error_file_simple_

#ifndef _di_fake_print_error_fss_
  f_status_t fake_print_error_fss(fake_setting_t * const setting, const fl_print_t print, const f_string_t function, const f_string_static_t path_file, const f_string_range_t range, const bool fallback) {

    if (!setting) return F_status_set_error(F_output_not);

    if (setting->state.status == F_file_found_not) {
      if (print.verbosity > f_console_verbosity_quiet_e) {
        fake_print_error_fss_message(setting, print, 0, "Occurred on invalid UTF-8 character at stop position (at ", range.start, " of the setting file ", path_file, ")");
      }

      return F_false;
    }

    if (setting->state.status == F_complete_not_utf || setting->state.status == F_complete_not_utf_eos || setting->state.status == F_complete_not_utf_stop) {
      if (print.verbosity > f_console_verbosity_quiet_e) {
        f_file_stream_lock(print.to);

        fl_print_format("%[%QOccurred on invalid UTF-8 character at %s (at '%]", print.to, print.context, print.prefix, setting->state.status == F_complete_not_utf_eos ? "end of string" : "stop point of string", print.context);
        fl_print_format("%[%un%]", print.to, print.notable, range.start, print.notable);
        fl_print_format("%[ of the setting file '%]", print.to, print.context, print.context);
        fl_print_format("%[%Q%]", print.to, print.notable, path_file, print.notable);
        fl_print_format("%[').%]%r", print.to, print.context, print.context, f_string_eol_s);

        f_file_stream_unlock(print.to);
      }

      return F_false;
    }

    if (setting->state.status == F_complete_not_utf_stop) {
      if (print.verbosity > f_console_verbosity_quiet_e) {
        fake_print_error_fss_message(setting, print, 0, "Occurred on invalid UTF-8 character at stop point of string (at ", range.start, " of the setting file ", path_file, ")");
      }

      return F_false;
    }

    if (fll_error_print(print, setting->state.status, function, fll_error_file_flag_none_e) == F_known_not && fallback) {
      if (print.verbosity > f_console_verbosity_quiet_e) {
        f_string_static_t function_s = f_string_static_t_initialize;
        function_s.string = function;
        function_s.used = strlen(function);

        fake_print_error_fss_message(setting, print, "UNKNOWN ", 0, (f_number_unsigned_t) setting->state.status, ") in function ", function_s, "()");
      }
    }

    return F_true;
  }
#endif // _di_fake_print_error_fss_

#ifndef _di_fake_print_error_fss_message_
  f_status_t fake_print_error_fss_message(fake_setting_t * const setting, const fl_print_t print, const f_string_t prefix, const f_string_t before, const f_number_unsigned_t number, const f_string_t middle, const f_string_static_t variable, const f_string_t after) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print.to);

    fl_print_format("%[%S%Q%S(%]", print.to, print.context, prefix, print.prefix, before, print.context);
    fl_print_format("%[%un%]", print.to, print.notable, number, print.notable);
    fl_print_format("%[)%S'%]", print.to, print.context, middle, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, variable, print.notable);
    fl_print_format("%[%S.%]%r", print.to, print.context, after, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_print_error_fss_message_

#ifndef _di_fake_print_error_group_not_found_
  f_status_t fake_print_error_group_not_found(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t group) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_print_context_wrapped_variable(setting, print, "The group ", group, " is not found");

    return F_none;
  }
#endif // _di_fake_print_error_group_not_found_

#ifndef _di_fake_print_error_mode_invalid_
  f_status_t fake_print_error_mode_invalid(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t mode) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_print_context_wrapped_variable(setting, print, "The mode ", mode, " is invalid");

    return F_none;
  }
#endif // _di_fake_print_error_mode_invalid_

#ifndef _di_fake_print_error_number_too_large_
  f_status_t fake_print_error_number_too_large(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t number) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_print_context_wrapped_variable(setting, print, "The number ", number, " is too large");

    return F_none;
  }
#endif // _di_fake_print_error_number_too_large_

#ifndef _di_fake_print_error_operation_failed_
  f_status_t fake_print_error_operation_failed(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t buffer, const f_string_range_t section_name, const f_string_range_t operation_name) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    f_array_length_t line = 1;
    f_state_t state = f_state_t_initialize;

    f_fss_count_lines(buffer, operation_name.start, &line, &setting->state);

    f_file_stream_lock(print.to);

    fl_print_format("%[%QThe section operation '%]", print.to, print.context, print.prefix, print.context);
    fl_print_format("%[%/Q%]", print.to, print.notable, buffer, operation_name, print.notable);
    fl_print_format("%[' from section '%]", print.to, print.context, print.context);
    fl_print_format("%[%/Q%]", print.to, print.notable, buffer, section_name, print.notable);
    fl_print_format("%[' on line%] ", print.to, print.context, print.context);
    fl_print_format("%[%un%]", print.to, print.notable, line, print.notable);
    fl_print_format(" %[failed.%]%r", print.to, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_print_error_operation_failed_

#ifndef _di_fake_print_error_operation_link_argument_unknown_
  f_status_t fake_print_error_operation_link_argument_unknown(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t argument) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print.to);

    fl_print_format("%[%QThe argument '%]", print.to, print.context, print.prefix, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, argument, print.notable);
    fl_print_format("%[' is not not valid and may only be one of either '%]", print.to, print.context, print.context);
    fl_print_format("%[%r%]", print.to, print.notable, fake_make_operation_argument_force_s, print.notable);
    fl_print_format("%[' or '%]", print.to, print.context, print.context);
    fl_print_format("%[%r%]", print.to, print.notable, fake_make_operation_argument_strict_s, print.notable);
    fl_print_format("%['.%]%r", print.to, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_print_error_operation_link_argument_unknown_

#ifndef _di_fake_print_error_operation_link_point_exists_
  f_status_t fake_print_error_operation_link_point_exists(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t argument) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_print_context_wrapped_variable(setting, print, "The point file ", argument, " already exists");

    return F_none;
  }
#endif // _di_fake_print_error_operation_link_point_exists_

#ifndef _di_fake_print_error_operation_link_target_exists_not_
  f_status_t fake_print_error_operation_link_target_exists_not(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t argument) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_print_context_wrapped_variable(setting, print, "The target file ", argument, " does not exist");

    return F_none;
  }
#endif // _di_fake_print_error_operation_link_target_exists_not_

#ifndef _di_fake_print_error_operation_path_outside_
  f_status_t fake_print_error_operation_path_outside(fake_setting_t * const setting, const fl_print_t print, const f_string_t function, const f_string_static_t path) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_verbose_e) return F_output_not;

    if (F_status_set_fine(setting->state.status) == F_false) {
      fake_print_context_wrapped_variable(setting, print, "The path ", path, " is outside the project root");
    }
    else {
      fake_print_error_file(setting, print, function, path, fake_common_file_path_determine_real_s, fll_error_file_type_file_e);
    }

    return F_none;
  }
#endif // _di_fake_print_error_operation_path_outside_

#ifndef _di_fake_print_error_operation_path_stack_max_
  f_status_t fake_print_error_operation_path_stack_max(fake_setting_t * const setting, const fl_print_t print, const f_string_t function, const f_string_static_t path) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    if (setting->state.status == F_array_too_large) {
      f_file_stream_lock(print.to);

      fl_print_format("%[%QMaximum stack size reached while processing path '%]", print.to, print.context, print.prefix, print.context);
      fl_print_format("%[%Q%]", print.to, print.notable, path, print.notable);
      fl_print_format("%['", print.to, print.context);

      if (function) {
        fl_print_format(" while calling%] %[%S%]", print.to, print.context, print.notable, function, print.notable);
        fl_print_format("%[()", print.to, print.context);
      }

      fl_print_format(".%]%r", print.to, print.context, f_string_eol_s);

      f_file_stream_unlock(print.to);
    }
    else {
      fake_print_error_file(setting, print, function, path, fake_common_file_path_change_to_s, fll_error_file_type_directory_e);
    }

    return F_none;
  }
#endif // _di_fake_print_error_operation_path_stack_max_

#ifndef _di_fake_print_error_operation_stack_max_
  f_status_t fake_print_error_operation_stack_max(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t buffer, const f_string_range_t section_name, const f_string_range_t operation_name, const f_array_length_t stack_max) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    f_array_length_t line = 1;
    f_state_t state = f_state_t_initialize;

    f_fss_count_lines(buffer, operation_name.start, &line, &setting->state);

    f_file_stream_lock(print.to);

    fl_print_format("%[%QThe section operation '%]", print.to, print.context, print.prefix, print.context);
    fl_print_format("%[%/Q%]", print.to, print.notable, buffer, operation_name, print.notable);
    fl_print_format("%[' from section '%]", print.to, print.context, buffer, print.context);
    fl_print_format("%[%/Q%]", print.to, print.notable, buffer, section_name, print.notable);
    fl_print_format("%[' on line%] ", print.to, print.context, print.context);
    fl_print_format("%[%ul%]", print.to, print.notable, line, print.notable);
    fl_print_format("%[' cannot be processed because the max stack depth of%] ", print.to, print.context, print.context);
    fl_print_format("%[%ul%]", print.to, print.notable, stack_max, print.notable);
    fl_print_format(" %[has been reached.%]%r", print.to, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_print_error_operation_stack_max_

#ifndef _di_fake_print_error_operation_unknown_
  f_status_t fake_print_error_operation_unknown(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t buffer, const f_string_range_t section_name, const f_string_range_t operation_name) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    f_array_length_t line = 1;
    f_state_t state = f_state_t_initialize;

    f_fss_count_lines(buffer, operation_name.start, &line, &setting->state);

    f_file_stream_lock(print.to);

    fl_print_format("%[%QThe section operation '%]", print.to, print.context, print.prefix, print.context);
    fl_print_format("%[%/Q%]", print.to, print.notable, buffer, operation_name, print.notable);
    fl_print_format("%[' from section '%]", print.to, print.context, buffer, print.context);
    fl_print_format("%[%/Q%]", print.to, print.notable, buffer, section_name, print.notable);
    fl_print_format("%[' on line%] ", print.to, print.context, print.context);
    fl_print_format("%[%ul%]", print.to, print.notable, line, print.notable);
    fl_print_format(" %[is not a known operation name.%]%r", print.to, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_print_error_operation_unknown_

#ifndef _di_fake_print_error_parameter_not_empty_
  f_status_t fake_print_error_parameter_not_empty(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t symbol, const f_string_static_t name, const f_string_static_t value) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    fake_print_context_wrapped_parameter(setting, print, "The ", symbol, name, " parameter must not be empty and must not contain only white space");

    return F_none;
  }
#endif // _di_fake_print_error_parameter_not_empty_

#ifndef _di_fake_print_error_parameter_directory_not_found_path_
  f_status_t fake_print_error_parameter_directory_not_found_path(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t symbol, const f_string_static_t name, const f_string_static_t value) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    fake_print_context_wrapped_parameter_value(setting, print, "The value of the directory parameter ", symbol, name, " has a path of ", value, " that is not found.");

    return F_none;
  }
#endif // _di_fake_print_error_parameter_directory_not_found_path_

#ifndef _di_fake_print_error_parameter_not_word_
  f_status_t fake_print_error_parameter_not_word(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t symbol, const f_string_static_t name, const f_string_static_t value) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    f_file_stream_lock(print.to);

    fl_print_format("%[%QThe '%]", print.to, print.context, print.prefix, print.context);
    fl_print_format("%[%Q%Q%]", print.to, print.notable, symbol, name, print.notable);
    fl_print_format("%[' parameter value '%]", print.to, print.context, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, value, print.notable);
    fl_print_format("%[' contains non-word, non-dash, and non-plus characters.%]%r", print.to, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_print_error_parameter_not_word_

#ifndef _di_fake_print_error_parameter_operation_not_with_
  f_status_t fake_print_error_parameter_operation_not_with(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t operation_1, const f_string_static_t operation_2) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_print_context_wrapped_variables(setting, print, "The operation ", operation_1, " cannot be specified with the operation ", operation_2, 0);

    return F_none;
  }
#endif // _di_fake_print_error_parameter_operation_not_with_

#ifndef _di_fake_print_error_parameter_too_many_
  f_status_t fake_print_error_parameter_too_many(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t symbol, const f_string_static_t parameter) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_print_context_wrapped_parameter(setting, print, "The parameter ", symbol, parameter, " is specified too many times");

    return F_none;
  }
#endif // _di_fake_print_error_parameter_too_many_

#ifndef _di_fake_print_error_requires_more_arguments_
  f_status_t fake_print_error_requires_more_arguments(fake_setting_t * const setting, const fl_print_t print) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_print_context_simple(setting, print, "Requires more arguments");

    return F_none;
  }
#endif // _di_fake_print_error_requires_more_arguments_

#ifndef _di_fake_print_error_too_many_arguments_
  f_status_t fake_print_error_too_many_arguments(fake_setting_t * const setting, const fl_print_t print) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_print_context_simple(setting, print, "Has too many arguments");

    return F_none;
  }
#endif // _di_fake_print_error_too_many_arguments_

#ifndef _di_fake_print_error_user_not_found_
  f_status_t fake_print_error_user_not_found(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t user) {

    if (!setting) return F_status_set_error(F_output_not);
    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_print_context_wrapped_variable(setting, print, "The user ", user, " is not found");

    return F_none;
  }
#endif // _di_fake_print_error_user_not_found_

#ifdef __cplusplus
} // extern "C"
#endif
