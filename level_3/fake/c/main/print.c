#include "fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_print_context_simple_
  void fake_print_context_simple(fake_setting_t * const setting, const fl_print_t print, const f_string_t message) {

    if (!setting) return;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%[%Q%S.%]%r", print.to, print.context, print.prefix, message, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);
  }
#endif // _di_fake_print_context_simple_

#ifndef _di_fake_print_context_simple_variable_
  void fake_print_context_simple_variable(fake_setting_t * const setting, const fl_print_t print, const f_string_t before, const f_string_static_t variable, const f_string_t after) {

    if (!setting) return;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%[%Q%S'%]", print.to, print.context, print.prefix, before, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, variable, print.notable);
    fl_print_format("%['%S.%]%r", print.to, print.context, after, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);
  }
#endif // _di_fake_print_context_simple_variable_

#ifndef _di_fake_print_context_wrapped_parameter_
  void fake_print_context_wrapped_parameter(fake_setting_t * const setting, const fl_print_t print, const f_string_t before, const f_string_static_t symbol, const f_string_static_t name, const f_string_t after) {

    if (!setting) return;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%[%Q%S'%]", print.to, print.context, print.prefix, before, print.context);
    fl_print_format("%[%Q%Q%]", print.to, print.notable, symbol, name, print.notable);
    fl_print_format("%['%S.%]%r", print.to, print.context, after, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);
  }
#endif // _di_fake_print_context_wrapped_parameter_

#ifndef _di_fake_print_context_wrapped_parameters_
  void fake_print_context_wrapped_parameters(fake_setting_t * const setting, const fl_print_t print, const f_string_t before, const f_string_static_t symbol_1, const f_string_static_t name_1, const f_string_t between_1, const f_string_static_t symbol_2, const f_string_static_t name_2, const f_string_t between_2, const f_string_static_t symbol_3, const f_string_static_t name_3, const f_string_t after) {

    if (!setting) return;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%[%Q%S'%]", print.to, print.context, print.prefix, before, print.context);
    fl_print_format("%[%Q%Q%]", print.to, print.notable, symbol_1, name_1, print.notable);
    fl_print_format("%['%S'%]%r", print.to, print.context, between_1, print.context);
    fl_print_format("%[%Q%Q%]", print.to, print.notable, symbol_2, name_2, print.notable);
    fl_print_format("%['%S'%]%r", print.to, print.context, between_2, print.context);
    fl_print_format("%[%Q%Q%]", print.to, print.notable, symbol_3, name_3, print.notable);
    fl_print_format("%['%S.%]%r", print.to, print.context, after, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);
  }
#endif // _di_fake_print_context_wrapped_parameters_

#ifndef _di_fake_print_context_wrapped_variable_
  void fake_print_context_wrapped_variable(fake_setting_t * const setting, const fl_print_t print, const f_string_t before, const f_string_static_t variable, const f_string_t after) {

    if (!setting) return;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%[%Q%S'%]", print.to, print.context, print.prefix, before, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, variable, print.notable);
    fl_print_format("%['%S.%]%r", print.to, print.context, after, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);
  }
#endif // _di_fake_print_context_wrapped_variable_

#ifndef _di_fake_print_context_wrapped_variables_
  void fake_print_context_wrapped_variables(fake_setting_t * const setting, const fl_print_t print, const f_string_t before, const f_string_static_t first, const f_string_t between, const f_string_static_t second, const f_string_t after) {

    if (!setting) return;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%[%Q%S'%]", print.to, print.context, print.prefix, before, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, first, print.notable);
    fl_print_format("%['%S'%]", print.to, print.context, between, print.context);
    fl_print_format("%[%Q%]", print.to, print.notable, second, print.notable);
    fl_print_format("%['%S.%]%r", print.to, print.context, after, print.context, f_string_eol_s);

    f_file_stream_unlock(print.to);
  }
#endif // _di_fake_print_context_wrapped_variables_

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

#ifndef _di_fake_print_important_simple_
  void fake_print_important_simple(fake_setting_t * const setting, const fl_print_t print, const f_string_t message) {

    const fl_print_t custom = macro_fl_print_t_initialize(print.to, print.verbosity, f_string_empty_s, f_string_empty_s, print.set->important, print.set->notable, print.set);

    fake_print_context_simple(setting, custom, message);
  }
#endif // _di_fake_print_important_simple_

#ifndef _di_fake_print_line_first_locked_
  f_status_t fake_print_line_first_locked(fake_setting_t * const setting, const fl_print_t print) {

    if (!setting) return F_output_not;

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

    if (!setting) return F_output_not;

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

    if (!setting) return F_output_not;

    fll_print_dynamic_raw(setting->line_last, print.to);

    return F_none;
  }
#endif // _di_fake_print_line_last_locked_

#ifndef _di_fake_print_line_last_unlocked_
  f_status_t fake_print_line_last_unlocked(fake_setting_t * const setting, const fl_print_t print) {

    if (!setting) return F_output_not;

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

#ifndef _di_fake_print_simple_
  void fake_print_simple(fake_setting_t * const setting, const fl_print_t print, const f_string_t message) {

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fll_print_format("%S.%r", print.to, message, f_string_eol_s);

    f_file_stream_unlock(print.to);
  }
#endif // _di_fake_print_simple_

#ifndef _di_fake_print_simple_variable_
  void fake_print_simple_variable(fake_setting_t * const setting, const fl_print_t print, const f_string_t message, const f_string_static_t variable) {

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fll_print_format("%S'%[%Q%]'.%r", print.to, message, print.set->notable, variable, print.set->notable, f_string_eol_s);

    f_file_stream_unlock(print.to);
  }
#endif // _di_fake_print_simple_variable_

#ifndef _di_fake_print_wrapped_variable_
  void fake_print_wrapped_variable(fake_setting_t * const setting, const fl_print_t print, const f_string_t before, const f_string_static_t variable, const f_string_t after) {

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fll_print_format("%S'%[%Q%]'%S.%r", print.to, before, print.set->notable, variable, print.set->notable, after, f_string_eol_s);

    f_file_stream_unlock(print.to);
  }
#endif // _di_fake_print_wrapped_variable_

#ifndef _di_fake_print_wrapped_variables_
  void fake_print_wrapped_variables(fake_setting_t * const setting, const fl_print_t print, const f_string_t before, const f_string_static_t first, const f_string_t between, const f_string_static_t second, const f_string_t after) {

    if (!setting) return;

    f_file_stream_lock(print.to);

    fake_print_line_first_unlocked(setting, print);

    fl_print_format("%S'", print.to, before);
    fl_print_format("%[%Q%]", print.to, print.notable, first, print.notable);
    fl_print_format("'%S'", print.to, between);
    fl_print_format("%[%Q%]", print.to, print.notable, second, print.notable);
    fl_print_format("'%S.%r", print.to, after, f_string_eol_s);

    f_file_stream_unlock(print.to);
  }
#endif // _di_fake_print_wrapped_variables_

#ifdef __cplusplus
} // extern "C"
#endif
