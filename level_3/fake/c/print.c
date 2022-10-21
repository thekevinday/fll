#include "fake.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_print_help_
  f_status_t fake_print_help(fake_setting_t * const setting, const fl_print_t print) {

    f_file_stream_lock(print.to);

    f_print_dynamic_raw(setting->line_first, print.to.stream);

    fll_program_print_help_header(print, fake_program_name_long_s, fake_program_version_s);

    fll_program_print_help_option_standard(print);

    f_print_dynamic_raw(f_string_eol_s, print.to.stream);

    fll_program_print_help_option(print, fake_short_define_s, fake_long_define_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "  Append an additional define after defines from settings file.");
    fll_program_print_help_option(print, fake_short_fakefile_s, fake_long_fakefile_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Use this fakefile.");
    fll_program_print_help_option(print, fake_short_mode_s, fake_long_mode_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "    Use this mode when processing the build settings.");
    fll_program_print_help_option(print, fake_short_process_s, fake_long_process_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, " Process name for storing build states.");
    fll_program_print_help_option(print, fake_short_settings_s, fake_long_settings_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Use this settings file.");

    f_print_dynamic_raw(f_string_eol_s, print.to.stream);

    fll_program_print_help_option(print, fake_short_path_build_s, fake_long_path_build_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "  Specify a custom build directory.");
    fll_program_print_help_option(print, fake_short_path_data_s, fake_long_path_data_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Specify a custom path to the data files.");
    fll_program_print_help_option(print, fake_short_path_sources_s, fake_long_path_sources_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "Specify a custom path to the source files.");
    fll_program_print_help_option(print, fake_short_path_work_s, fake_long_path_work_s, f_console_symbol_short_enable_s, f_console_symbol_long_enable_s, "   Use includes/libraries/programs from this directory instead of system.");

    fl_print_format("%r%r %[Special Options:%] ", print.to.stream, f_string_eol_s, f_string_eol_s, print.set->important, print.set->important);

    fll_program_print_help_option_long(print, fake_long_documents_disabled_s, f_console_symbol_long_enable_s, "   Forcibly do not build documents files.");
    fll_program_print_help_option_long(print, fake_long_documents_enabled_s, f_console_symbol_long_enable_s, "    Forcibly do build documents files.");
    fll_program_print_help_option_long(print, fake_long_shared_disabled_s, f_console_symbol_long_enable_s, "Forcibly do not build shared files.");
    fll_program_print_help_option_long(print, fake_long_shared_enabled_s, f_console_symbol_long_enable_s, " Forcibly do build shared files.");
    fll_program_print_help_option_long(print, fake_long_static_disabled_s, f_console_symbol_long_enable_s, "Forcibly do not build static files.");
    fll_program_print_help_option_long(print, fake_long_static_enabled_s, f_console_symbol_long_enable_s, " Forcibly do build static files.");

    fl_print_format("%r%r %[Operations:%] ", print.to.stream, f_string_eol_s, f_string_eol_s, print.set->important, print.set->important);

    fll_program_print_help_option_other(print, fake_other_operation_build_s, "   Build or compile the code based on build settings file.");
    fll_program_print_help_option_other(print, fake_other_operation_clean_s, "   Delete all build files.");
    fll_program_print_help_option_other(print, fake_other_operation_make_s, "    Build or compile the code based on fakefile (default).");
    fll_program_print_help_option_other(print, fake_other_operation_skeleton_s, "Build a skeleton directory structure.");

    f_print_dynamic_raw(f_string_eol_s, print.to.stream);
    f_print_dynamic_raw(f_string_eol_s, print.to.stream);

    fll_program_print_help_usage(print, fake_program_name_s, fake_program_help_parameters_s);

    fl_print_format("%r  When performing the %[%r%] operation, the", print.to.stream, f_string_eol_s, print.set->notable, fake_other_operation_build_s, print.set->notable);
    fl_print_format(" %[%r%r%] parameter specifies a name (limited to alpha-numeric, underscore, and dash) to be used in addition to the global.%r", print.to.stream, print.set->notable, f_console_symbol_long_enable_s, fake_long_mode_s, print.set->notable, f_string_eol_s);

    fl_print_format("  For example, when a %[%r%]", print.to.stream, print.set->notable, fake_make_parameter_variable_mode_s, print.set->notable);
    fl_print_format(" of 'fll_monolithic' is specified, build libraries from both 'build_libraries' and 'build_libraries-fll_monolithic' are used (but not 'build_libraries-fll_level').%r%r", print.to.stream, f_string_eol_s, f_string_eol_s);

    fl_print_format("  When specifying the %[%r%] or the %[%r%]", print.to.stream, print.set->notable, fake_make_parameter_variable_fakefile_s, print.set->notable, print.set->notable, fake_make_parameter_variable_settings_s, print.set->notable);
    fl_print_format(" parameters, the project root is seached first and then the build data director is searched when the given file does not contain a directory separator.%r", print.to.stream, f_string_eol_s);

    fl_print_format("  For example, with '%[%r%r my_fakefile%]' the fakefile at", print.to.stream, print.set->notable, f_console_symbol_long_enable_s, fake_long_fakefile_s, print.set->notable);
    fl_print_format(" '%[./my_fakefile%]' is used if found, but if it is not found then", print.to.stream, print.set->notable, print.set->notable);
    fl_print_format(" '%[./%r%rmy_fakefile%]' is used if found.%r", print.to.stream, print.set->notable, fake_default_path_data_s, fake_default_path_build_s, print.set->notable, f_string_eol_s);
    fl_print_format("  For example, with '%[%r%r ./my_fakefile%]' the fakefile at", print.to.stream, print.set->notable, f_console_symbol_long_enable_s, fake_long_fakefile_s, print.set->notable);
    fl_print_format(" '%[./my_fakefile%]' is used if found, but if it is not found then no other paths are attempted.%r%r", print.to.stream, print.set->notable, print.set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  When piping data to this program, the piped data is treated as if it were prepended to the %[%r%]", print.to.stream, print.set->notable, fake_make_parameter_variable_fakefile_s, print.set->notable);
    fl_print_format("or the %[%r%], depending on the operation.%r", print.to.stream, print.set->notable, fake_make_parameter_variable_settings_s, print.set->notable, f_string_eol_s);

    f_print_dynamic_raw(setting->line_last, print.to.stream);

    f_file_stream_flush(output);
    f_file_stream_unlock(print.to);

    return F_none;
  }
#endif // _di_fake_print_help_

#ifndef _di_fake_print_line_first_locked_
  f_status_t fake_print_line_first_locked(fake_setting_t * const setting, const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    if (!F_status_is_error(setting->status)) {
      if (print.verbosity == f_console_verbosity_error_e) return F_output_not;
    }

    f_print_dynamic_raw(setting->line_first, print.to.stream);

    return F_none;
  }
#endif // _di_fake_print_line_first_locked_

#ifndef _di_fake_print_line_first_unlocked_
  f_status_t fake_print_line_first_unlocked(fake_setting_t * const setting, const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    if (!F_status_is_error(setting->status)) {
      if (print.verbosity == f_console_verbosity_error_e) return F_output_not;
    }

    fll_print_dynamic_raw(setting->line_first, print.to.stream);

    return F_none;
  }
#endif // _di_fake_print_line_first_unlocked_

#ifndef _di_fake_print_line_last_locked_
  f_status_t fake_print_line_last_locked(fake_setting_t * const setting, const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    if (!F_status_is_error(setting->status)) {
      if (print.verbosity == f_console_verbosity_error_e) return F_output_not;
    }

    fll_print_dynamic_raw(setting->line_last, print.to.stream);

    return F_none;
  }
#endif // _di_fake_print_line_last_locked_

#ifndef _di_fake_print_line_last_unlocked_
  f_status_t fake_print_line_last_unlocked(fake_setting_t * const setting, const fl_print_t print) {

    if (print.verbosity == f_console_verbosity_quiet_e) return F_output_not;

    if (!F_status_is_error(setting->status)) {
      if (print.verbosity == f_console_verbosity_error_e) return F_output_not;
    }

    f_print_dynamic_raw(setting->line_last, print.to.stream);

    return F_none;
  }
#endif // _di_fake_print_line_last_unlocked_

#ifdef __cplusplus
} // extern "C"
#endif
