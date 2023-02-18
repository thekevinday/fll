#include "fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_print_error_
  f_status_t fake_print_error(fake_setting_t * const setting, const fl_print_t print, const f_status_t status, const f_string_t function) {

    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_print_line_first_locked(setting, print);

    fll_error_print(print, F_status_set_fine(status), function, F_true);

    return F_none;
  }
#endif // _di_fake_print_error_

#ifndef _di_fake_print_error_fallback_
  f_status_t fake_print_error_fallback(fake_setting_t * const setting, const fl_print_t print, const f_status_t status, const f_string_t function) {

    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_print_line_first_locked(setting, print);

    if (fll_error_print(print, F_status_set_fine(status), function, F_false) == F_known_not) return F_false;

    return F_true;
  }
#endif // _di_fake_print_error_fallback_

#ifndef _di_fake_print_error_file_
  f_status_t fake_print_error_file(fake_setting_t * const setting, const fl_print_t print, const f_status_t status, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type) {

    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_print_line_first_locked(setting, print);

    fll_error_file_print(print, F_status_set_fine(status), function, F_true, name, operation, type);

    return F_none;
  }
#endif // _di_fake_print_error_file_

#ifndef _di_fake_print_error_file_fallback_
  f_status_t fake_print_error_file_fallback(fake_setting_t * const setting, const fl_print_t print, const f_status_t status, const f_string_t function, const f_string_static_t name, const f_string_static_t operation, const uint8_t type) {

    if (print.verbosity < f_console_verbosity_error_e) return F_output_not;

    fake_print_line_first_locked(setting, print);

    if (fll_error_file_print(print, F_status_set_fine(status), function, F_false, name, operation, type) == F_known_not) return F_false;

    return F_true;
  }
#endif // _di_fake_print_error_file_fallback_

#ifndef _di_fake_print_error_failure_operation_
  f_status_t fake_print_error_failure_operation(fake_setting_t * const setting, const fl_print_t print, const uint8_t operation) {

    if (!setting || print.verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

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

    if (!setting || print.verbosity < f_console_verbosity_error_e) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%[%QFailed to execute script '%]", print.to, print.context, print.prefix, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, script, print.notable);
    fl_print_format("%['.%]%r", print.to, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_print_error_failure_script_

#ifndef _di_fake_print_error_parameter_not_empty_
  f_status_t fake_print_error_parameter_not_empty(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t symbol, const f_string_static_t name, const f_string_static_t value) {

    if (!setting || print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    if (!F_status_is_error(setting->status)) {
      if (print.verbosity < f_console_verbosity_error_e) return F_output_not;
    }

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%[%QThe '%]", print.to, print.context, print.prefix, print.context);
    fl_print_format("%[%Q%Q%]", print.to, print.notable, symbol, name, print.notable);
    fl_print_format("%[' parameter must not be empty and must not contain only white space.%]%r", print.to, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_print_error_parameter_not_empty_

#ifndef _di_fake_print_error_parameter_not_word_
  f_status_t fake_print_error_parameter_not_word(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t symbol, const f_string_static_t name, const f_string_static_t value) {

    if (!setting || print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    if (!F_status_is_error(setting->status)) {
      if (print.verbosity < f_console_verbosity_error_e) return F_output_not;
    }

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

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

    if (!setting || print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    if (!F_status_is_error(setting->status)) {
      if (print.verbosity < f_console_verbosity_error_e) return F_output_not;
    }

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%[%QThe operation '%]", print.to, print.context, print.prefix, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, operation_1, print.notable);
    fl_print_format("%[' cannot be specified with the operation '%]", print.to, print.context, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, operation_2, print.notable);
    fl_print_format("%['.%]%r", print.to, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_print_error_parameter_operation_not_with_

#ifndef _di_fake_print_help_
  f_status_t fake_print_help(fake_setting_t * const setting, const fl_print_t print) {

    if (!setting) return F_output_not;

    f_file_stream_lock(print.to);

    f_print_dynamic_raw(setting->line_first, print.to);

    fll_program_print_help_header(print, fake_program_name_long_s, fake_program_version_s);

    fll_program_print_help_option_standard(print);

    f_print_dynamic_raw(f_string_eol_s, print.to);

    fll_program_print_help_option(print, fake_short_define_s, fake_long_define_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "  Append an additional define after defines from settings file.");
    fll_program_print_help_option(print, fake_short_fakefile_s, fake_long_fakefile_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "Use this fakefile.");
    fll_program_print_help_option(print, fake_short_mode_s, fake_long_mode_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "    Use this mode when processing the build settings.");
    fll_program_print_help_option(print, fake_short_process_s, fake_long_process_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, " Process name for storing build states.");
    fll_program_print_help_option(print, fake_short_settings_s, fake_long_settings_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "Use this settings file.");

    f_print_dynamic_raw(f_string_eol_s, print.to);

    fll_program_print_help_option(print, fake_short_build_s, fake_long_build_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "    Specify a custom build directory.");
    fll_program_print_help_option(print, fake_short_data_s, fake_long_data_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "     Specify a custom path to the data files.");
    fll_program_print_help_option(print, fake_short_documents_s, fake_long_documents_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "Specify a custom path to the documents files.");
    fll_program_print_help_option(print, fake_short_licenses_s, fake_long_licenses_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, " Specify a custom path to the licenses files.");
    fll_program_print_help_option(print, fake_short_sources_s, fake_long_sources_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "  Specify a custom path to the source files.");
    fll_program_print_help_option(print, fake_short_work_s, fake_long_work_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "     Use includes/libraries/programs from this directory instead of system.");

    fl_print_format("%r%r %[Special Options:%] ", print.to, f_string_eol_s, f_string_eol_s, print.set->important, print.set->important);

    fll_program_print_help_option_long(print, fake_long_documents_disabled_s, f_console_symbol_long_normal_s, "   Forcibly do not build documents files.");
    fll_program_print_help_option_long(print, fake_long_documents_enabled_s, f_console_symbol_long_normal_s, "    Forcibly do build documents files.");
    fll_program_print_help_option_long(print, fake_long_shared_disabled_s, f_console_symbol_long_normal_s, "Forcibly do not build shared files.");
    fll_program_print_help_option_long(print, fake_long_shared_enabled_s, f_console_symbol_long_normal_s, " Forcibly do build shared files.");
    fll_program_print_help_option_long(print, fake_long_static_disabled_s, f_console_symbol_long_normal_s, "Forcibly do not build static files.");
    fll_program_print_help_option_long(print, fake_long_static_enabled_s, f_console_symbol_long_normal_s, " Forcibly do build static files.");

    fl_print_format("%r%r %[Operations:%] ", print.to, f_string_eol_s, f_string_eol_s, print.set->important, print.set->important);

    fll_program_print_help_option_other(print, fake_other_operation_build_s, "   Build or compile the code based on build settings file.");
    fll_program_print_help_option_other(print, fake_other_operation_clean_s, "   Delete all build files.");
    fll_program_print_help_option_other(print, fake_other_operation_make_s, "    Build or compile the code based on fakefile (default).");
    fll_program_print_help_option_other(print, fake_other_operation_skeleton_s, "Build a skeleton directory structure.");

    f_print_dynamic_raw(f_string_eol_s, print.to);
    f_print_dynamic_raw(f_string_eol_s, print.to);

    fll_program_print_help_usage(print, fake_program_name_s, fake_program_help_parameters_s);

    fl_print_format("%r  When performing the %[%r%] operation, the", print.to, f_string_eol_s, print.set->notable, fake_other_operation_build_s, print.set->notable);
    fl_print_format(" %[%r%r%] parameter specifies a name (limited to alpha-numeric, underscore, and dash) to be used in addition to the global.%r", print.to, print.set->notable, f_console_symbol_long_normal_s, fake_long_mode_s, print.set->notable, f_string_eol_s);

    fl_print_format("  For example, when a %[%r%]", print.to, print.set->notable, fake_make_parameter_variable_mode_s, print.set->notable);
    fl_print_format(" of 'fll_monolithic' is specified, build libraries from both 'build_libraries' and 'build_libraries-fll_monolithic' are used (but not 'build_libraries-fll_level').%r%r", print.to, f_string_eol_s, f_string_eol_s);

    fl_print_format("  When specifying the %[%r%] or the %[%r%]", print.to, print.set->notable, fake_make_parameter_variable_fakefile_s, print.set->notable, print.set->notable, fake_make_parameter_variable_settings_s, print.set->notable);
    fl_print_format(" parameters, the project root is seached first and then the build data director is searched when the given file does not contain a directory separator.%r", print.to, f_string_eol_s);

    fl_print_format("  For example, with '%[%r%r my_fakefile%]' the fakefile at", print.to, print.set->notable, f_console_symbol_long_normal_s, fake_long_fakefile_s, print.set->notable);
    fl_print_format(" '%[./my_fakefile%]' is used if found, but if it is not found then", print.to, print.set->notable, print.set->notable);
    fl_print_format(" '%[./%r%rmy_fakefile%]' is used if found.%r", print.to, print.set->notable, fake_default_data_s, fake_default_build_s, print.set->notable, f_string_eol_s);
    fl_print_format("  For example, with '%[%r%r ./my_fakefile%]' the fakefile at", print.to, print.set->notable, f_console_symbol_long_normal_s, fake_long_fakefile_s, print.set->notable);
    fl_print_format(" '%[./my_fakefile%]' is used if found, but if it is not found then no other paths are attempted.%r%r", print.to, print.set->notable, print.set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  When piping data to this program, the piped data is treated as if it were prepended to the %[%r%]", print.to, print.set->notable, fake_make_parameter_variable_fakefile_s, print.set->notable);
    fl_print_format(" or the %[%r%], depending on the operation.%r", print.to, print.set->notable, fake_make_parameter_variable_settings_s, print.set->notable, f_string_eol_s);

    fl_print_format("  A section name from the fakefile that does not conflict with an operation name may be specified when performing the %[%r%] operation.%r", print.to, print.set->notable, fake_other_operation_make_s, print.set->notable, f_string_eol_s);

    f_print_dynamic_raw(setting->line_last, print.to);

    f_file_stream_flush(print.to);
    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_print_help_

#ifndef _di_fake_print_line_first_locked_
  f_status_t fake_print_line_first_locked(fake_setting_t * const setting, const fl_print_t print) {

    if (!setting || print.verbosity < f_console_verbosity_error_e) return F_output_not;

    if (F_status_is_error_not(setting->status)) {
      if (print.verbosity < f_console_verbosity_normal_e) return F_output_not;
    }

    if (setting->flag & fake_main_flag_print_first_e) {
      fll_print_dynamic_raw(setting->line_first, print.to);

      setting->flag -= fake_main_flag_print_first_e;
    }
    else {
      fll_print_dynamic_raw(f_string_eol_s, print.to);
    }

    return F_none;
  }
#endif // _di_fake_print_line_first_locked_

#ifndef _di_fake_print_line_first_unlocked_
  f_status_t fake_print_line_first_unlocked(fake_setting_t * const setting, const fl_print_t print) {

    if (!setting || print.verbosity < f_console_verbosity_error_e) return F_output_not;

    if (F_status_is_error_not(setting->status)) {
      if (print.verbosity < f_console_verbosity_normal_e) return F_output_not;
    }

    if (setting->flag & fake_main_flag_print_first_e) {
      fll_print_dynamic_raw(setting->line_first, print.to);

      setting->flag -= fake_main_flag_print_first_e;
    }
    else {
      fll_print_dynamic_raw(f_string_eol_s, print.to);
    }

    return F_none;
  }
#endif // _di_fake_print_line_first_unlocked_

#ifndef _di_fake_print_line_last_locked_
  f_status_t fake_print_line_last_locked(fake_setting_t * const setting, const fl_print_t print) {

    if (!setting || print.verbosity < f_console_verbosity_error_e) return F_output_not;

    if (F_status_is_error_not(setting->status)) {
      if (print.verbosity < f_console_verbosity_normal_e) return F_output_not;
    }

    fll_print_dynamic_raw(setting->line_last, print.to);

    return F_none;
  }
#endif // _di_fake_print_line_last_locked_

#ifndef _di_fake_print_line_last_unlocked_
  f_status_t fake_print_line_last_unlocked(fake_setting_t * const setting, const fl_print_t print) {

    if (!setting || print.verbosity < f_console_verbosity_error_e) return F_output_not;

    if (F_status_is_error_not(setting->status)) {
      if (print.verbosity < f_console_verbosity_normal_e) return F_output_not;
    }

    f_print_dynamic_raw(setting->line_last, print.to);

    return F_none;
  }
#endif // _di_fake_print_line_last_unlocked_

#ifndef _di_fake_print_operation_all_complete_
  f_status_t fake_print_operation_all_complete(fake_setting_t * const setting, const fl_print_t print) {

    if (!setting || print.verbosity < f_console_verbosity_normal_e) return F_output_not;
    if (F_status_is_error(setting->status)) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("All operations complete.%r", print.to, f_string_eol_s, f_string_eol_s);

    f_file_stream_flush(print.to);
    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_print_operation_all_complete_

#ifndef _di_fake_print_operation_cancelled_
  f_status_t fake_print_operation_cancelled(fake_setting_t * const setting, const fl_print_t print, const uint8_t operation) {

    if (!setting || print.verbosity < f_console_verbosity_normal_e) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%[The operation '%]%[", print.to, print.context, print.context, print.notable);

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

    fl_print_format("%]%[' is cancelled.%]%r", print.to, print.notable, print.context, print.context, f_string_eol_s);

    f_file_stream_flush(print.to);
    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_print_operation_cancelled_

#ifndef _di_fake_print_error_build_operation_file_
  f_status_t fake_print_error_build_operation_file(fake_setting_t * const setting, const fl_print_t print, const f_status_t status, const f_string_t function, const f_string_static_t operation, const f_string_static_t source, const f_string_static_t destination, const f_string_static_t how, const bool fallback) {

    if (F_status_set_fine(status) == F_file_found_not) {
      if (print.verbosity > f_console_verbosity_quiet_e) {
        f_file_stream_lock(print.to);

        fake_print_line_first_unlocked(setting, print);

        fl_print_format("%[%QFailed to find '%]", print.to, print.context, print.prefix, print.context);

        fake_print_error_build_operation_file_message(setting, print, operation, source, destination, how);

        fl_print_format("%['.%]%r", print.to, print.context, print.context, f_string_eol_s);

        f_file_stream_unlock(print.to);
      }

      return F_false;
    }

    if (F_status_set_fine(status) == F_parameter) {
      if (print.verbosity > f_console_verbosity_quiet_e) {
        f_file_stream_lock(print.to);

        fake_print_line_first_unlocked(setting, print);

        fl_print_format("%[%QInvalid parameter when calling '%]", print.to, print.context, print.prefix, print.context);
        fl_print_format("%[%Q%]", print.to, print.notable, function, print.notable);
        fl_print_format("%[() to %Q '%]", print.to, print.context, operation, print.context);

        fake_print_error_build_operation_file_message(setting, print, operation, source, destination, how);

        fl_print_format("%['.%]%r", print.to, print.context, print.context, f_string_eol_s);

        f_file_stream_unlock(print.to);
      }

      return F_false;
    }

    if (F_status_set_fine(status) == F_name) {
      if (print.verbosity > f_console_verbosity_quiet_e) {
        f_file_stream_lock(print.to);

        fake_print_line_first_unlocked(setting, print);

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

    if (F_status_set_fine(status) == F_memory_not) {
      if (print.verbosity > f_console_verbosity_quiet_e) {
        f_file_stream_lock(print.to);

        fake_print_line_first_unlocked(setting, print);

        fl_print_format("%[%QUnable to allocate memory, while trying to %Q '%]", print.to, print.context, print.prefix, operation, print.context);

        fake_print_error_build_operation_file_message(setting, print, operation, source, destination, how);

        fl_print_format("%['.%]%r", print.to, print.context, print.context, f_string_eol_s);

        f_file_stream_unlock(print.to);
      }

      return F_false;
    }

    if (F_status_set_fine(status) == F_number_overflow) {
      if (print.verbosity > f_console_verbosity_quiet_e) {
        f_file_stream_lock(print.to);

        fake_print_line_first_unlocked(setting, print);

        fl_print_format("%[%QOverflow while trying to %Q '%]", print.to, print.context, print.prefix, operation, print.context);

        fake_print_error_build_operation_file_message(setting, print, operation, source, destination, how);

        fl_print_format("%['.%]%r", print.to, print.context, print.context, f_string_eol_s);

        f_file_stream_unlock(print.to);
      }

      return F_false;
    }

    if (F_status_set_fine(status) == F_directory) {
      if (print.verbosity > f_console_verbosity_quiet_e) {
        f_file_stream_lock(print.to);

        fake_print_line_first_unlocked(setting, print);

        fl_print_format("%[%QInvalid directory while trying to %Q '%]", print.to, print.context, print.prefix, operation, print.context);

        fake_print_error_build_operation_file_message(setting, print, operation, source, destination, how);

        fl_print_format("%['.%]%r", print.to, print.context, print.context, f_string_eol_s);

        f_file_stream_unlock(print.to);
      }

      return F_false;
    }

    if (F_status_set_fine(status) == F_access_denied) {
      if (print.verbosity > f_console_verbosity_quiet_e) {
        f_file_stream_lock(print.to);

        fake_print_line_first_unlocked(setting, print);

        fl_print_format("%[%QAccess denied while trying to %Q '%]", print.to, print.context, print.prefix, operation, print.context);

        fake_print_error_build_operation_file_message(setting, print, operation, source, destination, how);

        fl_print_format("%['.%]%r", print.to, print.context, print.context, f_string_eol_s);

        f_file_stream_unlock(print.to);
      }

      return F_false;
    }

    if (F_status_set_fine(status) == F_loop) {
      if (print.verbosity > f_console_verbosity_quiet_e) {
        f_file_stream_lock(print.to);

        fake_print_line_first_unlocked(setting, print);

        fl_print_format("%[%QLoop while trying to %Q '%]", print.to, print.context, print.prefix, operation, print.context);

        fake_print_error_build_operation_file_message(setting, print, operation, source, destination, how);

        fl_print_format("%['.%]%r", print.to, print.context, print.context, f_string_eol_s);

        f_file_stream_unlock(print.to);
      }

      return F_false;
    }

    if (F_status_set_fine(status) == F_prohibited) {
      if (print.verbosity > f_console_verbosity_quiet_e) {
        f_file_stream_lock(print.to);

        fake_print_line_first_unlocked(setting, print);

        fl_print_format("%[%QProhibited by system while trying to %Q '%]", print.to, print.context, print.prefix, operation, print.context);

        fake_print_error_build_operation_file_message(setting, print, operation, source, destination, how);

        fl_print_format("%['.%]%r", print.to, print.context, print.context, f_string_eol_s);

        f_file_stream_unlock(print.to);
      }

      return F_false;
    }

    if (F_status_set_fine(status) == F_directory_found_not) {
      if (print.verbosity > f_console_verbosity_quiet_e) {
        f_file_stream_lock(print.to);

        fake_print_line_first_unlocked(setting, print);

        fl_print_format("%[%QFailed to %Q '%]", print.to, print.context, print.prefix, operation, print.context);

        fake_print_error_build_operation_file_message(setting, print, operation, source, destination, how);

        fl_print_format("%[' due to an invalid directory in the path.%]%r", print.to, print.context, print.context, f_string_eol_s);

        f_file_stream_unlock(print.to);
      }

      return F_false;
    }

    if (F_status_set_fine(status) == F_failure) {
      if (print.verbosity > f_console_verbosity_quiet_e) {
        f_file_stream_lock(print.to);

        fake_print_line_first_unlocked(setting, print);

        fl_print_format("%[%QFailed to %Q '%]", print.to, print.context, print.prefix, operation, print.context);

        fake_print_error_build_operation_file_message(setting, print, operation, source, destination, how);

        fl_print_format("%['.%]%r", print.to, print.context, print.context, f_string_eol_s);

        f_file_stream_unlock(print.to);
      }

      return F_false;
    }

    if (fll_error_print(print, F_status_set_fine(status), function, F_false) == F_known_not && fallback && print.verbosity > f_console_verbosity_quiet_e) {
      f_file_stream_lock(print.to);

      fake_print_line_first_unlocked(setting, print);

      fl_print_format("%[UNKNOWN %Q(%]", print.to, print.context, print.prefix, print.context);
      fl_print_format("%[%ui%]", print.to, print.notable, F_status_set_fine(status), print.notable);
      fl_print_format("%[) occurred while trying to %Q '%]", print.to, print.context, operation, print.context);

      fake_print_error_build_operation_file_message(setting, print, operation, source, destination, how);

      fl_print_format("%['.%]%r", print.to, print.context, print.context, f_string_eol_s);

      f_file_stream_unlock(print.to);
    }

    return F_true;
  }
#endif // _di_fake_print_error_build_operation_file_

#ifndef _di_fake_print_error_build_operation_file_message_
  void fake_print_error_build_operation_file_message(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t operation, const f_string_static_t source, const f_string_static_t destination, const f_string_static_t how) {

    if (source.used) {
      fl_print_format("%[%Q%]", print.to, print.notable, source, print.notable);
    }

    fl_print_format("%[while trying to %Q '%]", print.to, print.context, operation, print.context);

    if (destination.used) {
      fl_print_format("%[' %Q '%]", print.to, print.context, how, print.context);
      fl_print_format("%[%Q%]", print.to, print.notable, destination, print.notable);
    }
    else if (source.used) {
      fl_print_format("%[%Q%]", print.to, print.notable, source, print.notable);
    }
  }
#endif // _di_fake_print_error_build_operation_file_message_

#ifndef _di_fake_print_error_fss
  f_status_t fake_print_error_fss(fake_setting_t * const setting, const fl_print_t print, const f_status_t status, const f_string_t function, const f_string_static_t path_file, const f_string_range_t range, const bool fallback) {

    if (status == F_file_found_not) {
      if (print.verbosity > f_console_verbosity_quiet_e) {
        f_file_stream_lock(print.to);

        fake_print_line_first_unlocked(setting, print);

        fl_print_format("%[%QOccurred on invalid UTF-8 character at stop position (at '%]", print.to, print.context, print.prefix, print.context);
        fl_print_format("%[%un%]", print.to, print.notable, range.start, print.notable);
        fl_print_format("%[ of setting file '%]", print.to, print.context, print.context);
        fl_print_format("%[%Q%]", print.to, print.notable, path_file, print.notable);
        fl_print_format("%[').%]%r", print.to, print.context, print.context, f_string_eol_s);

        f_file_stream_unlock(print.to);
      }

      return F_false;
    }

    if (status == F_complete_not_utf || status == F_complete_not_utf_eos || status == F_complete_not_utf_stop) {
      if (print.verbosity > f_console_verbosity_quiet_e) {
        f_file_stream_lock(print.to);

        fake_print_line_first_unlocked(setting, print);

        fl_print_format("%[%QOccurred on invalid UTF-8 character at %s (at '%]", print.to, print.context, print.prefix, status == F_complete_not_utf_eos ? "end of string" : "stop point of string", print.context);
        fl_print_format("%[%un%]", print.to, print.notable, range.start, print.notable);
        fl_print_format("%[ of setting file '%]", print.to, print.context, print.context);
        fl_print_format("%[%Q%]", print.to, print.notable, path_file, print.notable);
        fl_print_format("%[').%]%r", print.to, print.context, print.context, f_string_eol_s);

        f_file_stream_unlock(print.to);
      }

      return F_false;
    }

    if (status == F_complete_not_utf_stop) {
      if (print.verbosity > f_console_verbosity_quiet_e) {
        f_file_stream_lock(print.to);

        fake_print_line_first_unlocked(setting, print);

        fl_print_format("%[%QOccurred on invalid UTF-8 character at stop point of string (at '%]", print.to, print.context, print.prefix, print.context);
        fl_print_format("%[%un%]", print.to, print.notable, range.start, print.notable);
        fl_print_format("%[ of setting file '%]", print.to, print.context, print.context);
        fl_print_format("%[%Q%]", print.to, print.notable, path_file, print.notable);
        fl_print_format("%[').%]%r", print.to, print.context, print.context, f_string_eol_s);

        f_file_stream_unlock(print.to);
      }

      return F_false;
    }

    if (fll_error_print(print, status, function, F_false) == F_known_not && fallback && print.verbosity > f_console_verbosity_quiet_e) {
      f_file_stream_lock(print.to);

      fake_print_line_first_unlocked(setting, print);

      fl_print_format("%[UNKNOWN %Q(%]", print.to, print.context, print.prefix, print.context);
      fl_print_format("%[%ui%]", print.to, print.notable, status, print.notable);
      fl_print_format("%[) in function '%]", print.to, print.context, print.context);
      fl_print_format("%[%Q%]", print.to, print.notable, function, print.notable);
      fl_print_format("%[().%]%r", print.to, print.context, print.context, f_string_eol_s);

      f_file_stream_unlock(print.to);
    }

    return F_true;
  }
#endif // _di_fake_print_error_fss

#ifndef _di_fake_print_error_parameter_too_many_
  f_status_t fake_print_error_parameter_too_many(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t parameter) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    f_file_stream_lock(print.to);

    fl_print_format("%[%QThe parameter '%]", print.to, print.context, print.prefix, print.context);
    fl_print_format("%[%r%r%]", print.to, print.notable, f_console_symbol_long_normal_s, parameter, print.notable);
    fl_print_format("%[' was specified too many times.%]%r", print.to, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_print_error_parameter_too_many_

#ifndef _di_fake_print_error_requires_more_arguments_
  f_status_t fake_print_error_requires_more_arguments(fake_setting_t * const setting, const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;
    if (!print.to.stream) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%[%QRequires more arguments.%]%r", print.to, print.context, print.prefix, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_print_error_requires_more_arguments_

#ifndef _di_fake_print_error_too_many_arguments_
  f_status_t fake_print_error_too_many_arguments(fake_setting_t * const setting, const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;
    if (!print.to.stream) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fll_print_format("%[%QHas too many arguments.%]%r", print.to, print.context, print.prefix, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_print_error_too_many_arguments_

#ifndef _di_fake_print_error_argument_empty_
  f_status_t fake_print_error_argument_empty(fake_setting_t * const setting, const fl_print_t print, const f_array_length_t index) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;
    if (!print.to.stream) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%[%QThe %]", print.to, f_string_eol_s, print.context, print.prefix, print.context);
    fl_print_format("%[%un%]", print.to, print.notable, index, print.notable);
    fl_print_format("%[ argument must not be an empty string.%]%r", print.to, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_print_error_argument_empty_

#ifndef _di_fake_print_message_section_operation_failed_
  f_status_t fake_print_message_section_operation_failed(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t buffer, const f_string_range_t section_name, const f_string_range_t operation_name) {

    if (print.verbosity == f_console_verbosity_quiet_e || !print.to.stream) return F_output_not;

    f_array_length_t line = 1;
    f_state_t state = f_state_t_initialize;

    f_fss_count_lines(state, buffer, operation_name.start, &line);

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

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
#endif // _di_fake_print_message_section_operation_failed_

#ifndef _di_fake_print_message_section_operation_link_argument_unknown_
  f_status_t fake_print_message_section_operation_link_argument_unknown(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t argument) {

    if (print.verbosity == f_console_verbosity_quiet_e || !print.to.stream) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

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
#endif // _di_fake_print_message_section_operation_link_argument_unknown_

#ifndef _di_fake_print_message_section_operation_link_point_exists_
  f_status_t fake_print_message_section_operation_link_point_exists(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t argument) {

    if (print.verbosity == f_console_verbosity_quiet_e || !print.to.stream) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%[%QThe point file '%]", print.to, print.context, print.prefix, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, argument, print.notable);
    fl_print_format("%[' already exists.%]%r", print.to, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_print_message_section_operation_link_point_exists_

#ifndef _di_fake_print_message_section_operation_link_target_exists_not_
  f_status_t fake_print_message_section_operation_link_target_exists_not(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t argument) {

    if (print.verbosity == f_console_verbosity_quiet_e || !print.to.stream) return F_output_not;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%[%QThe target file '%]", print.to, print.context, print.prefix, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, argument, print.notable);
    fl_print_format("%[' does not exist.%]%r", print.to, print.context, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_print_message_section_operation_link_target_exists_not_

#ifndef _di_fake_print_message_section_operation_path_outside_
  f_status_t fake_print_message_section_operation_path_outside(fake_setting_t * const setting, const fl_print_t print, const f_status_t status, const f_string_t function, const f_string_static_t path) {

    if (print.verbosity == f_console_verbosity_quiet_e || !print.to.stream) return F_output_not;

    if (F_status_set_fine(status) == F_false) {
      f_file_stream_lock(print.to);

      fake_print_line_first_unlocked(setting, print);

      fl_print_format("%[%QThe path '%]", print.to, print.context, print.prefix, print.context);
      fl_print_format("%[%Q%]", print.to, print.notable, path, print.notable);
      fl_print_format("%[' is outside the project root.%]%r", print.to, print.context, print.context, f_string_eol_s);

      f_file_stream_unlock(print.to);
    }
    else {
      fake_print_error_file(setting, print, status, function, path, fake_common_file_path_determine_real_s, fll_error_file_type_file_e);
    }

    return F_none;
  }
#endif // _di_fake_print_message_section_operation_path_outside_

#ifndef _di_fake_print_message_section_operation_path_stack_max_
  f_status_t fake_print_message_section_operation_path_stack_max(fake_setting_t * const setting, const fl_print_t print, const f_status_t status, const f_string_t function, const f_string_static_t path) {

    if (print.verbosity == f_console_verbosity_quiet_e || !print.to.stream) return F_output_not;

    if (status == F_array_too_large) {
      f_file_stream_lock(print.to);

      fake_print_line_first_unlocked(setting, print);

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
      fake_print_error_file(setting, print, status, function, path, fake_common_file_path_change_to_s, fll_error_file_type_directory_e);
    }

    return F_none;
  }
#endif // _di_fake_print_message_section_operation_path_stack_max_

#ifndef _di_fake_print_message_section_operation_stack_max_
  f_status_t fake_print_message_section_operation_stack_max(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t buffer, const f_string_range_t section_name, const f_string_range_t operation_name, const f_array_length_t stack_max) {

    if (print.verbosity == f_console_verbosity_quiet_e || !print.to.stream) return F_output_not;

    f_array_length_t line = 1;
    f_state_t state = f_state_t_initialize;

    f_fss_count_lines(state, buffer, operation_name.start, &line);

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

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
#endif // _di_fake_print_message_section_operation_stack_max_

#ifndef _di_fake_print_message_section_operation_unknown_
  f_status_t fake_print_message_section_operation_unknown(fake_setting_t * const setting, const fl_print_t print, const f_string_static_t buffer, const f_string_range_t section_name, const f_string_range_t operation_name) {

    if (print.verbosity == f_console_verbosity_quiet_e || !print.to.stream) return F_output_not;

    f_array_length_t line = 1;
    f_state_t state = f_state_t_initialize;

    f_fss_count_lines(state, buffer, operation_name.start, &line);

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

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
#endif // _di_fake_print_message_section_operation_unknown_

#ifdef __cplusplus
} // extern "C"
#endif
