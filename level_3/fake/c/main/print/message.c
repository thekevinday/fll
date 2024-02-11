#include "../fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_print_message_building_
  f_status_t fake_print_message_building(fl_print_t * const print, const f_string_statics_t * const build_arguments, fake_build_setting_t * const setting_build) {

    if (!print || !print->custom || !setting_build) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_normal_e) return F_output_not;

    fake_main_t * const main = (fake_main_t *) print->custom;

    f_file_stream_lock(print->to);

    fl_print_format("%[Building%] ", print->to, print->set->important, print->set->important);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->set->notable, setting_build->build_name, print->set->notable);
    fl_print_format("%[ using '%]", print->to, print->set->important, print->set->important);
    fl_print_format(f_string_format_Q_single_s.string, print->to, print->set->notable, build_arguments && build_arguments->used ? build_arguments->array[0] : main->setting.settings, print->set->notable);

    fl_print_format("%[' with modes '%]", print->to, print->set->important, print->set->important);

    // Custom modes are always used if provided, otherwise fallback to the passed modes or the default modes.
    const f_string_statics_t * const modes = build_arguments && build_arguments->used > 1
      ? build_arguments
      : main->setting.modes.used
        ? &main->setting.modes
        : &setting_build->modes_default;

    for (f_number_unsigned_t i = build_arguments && build_arguments->used > 1 ? 1 : 0; i < modes->used; ) {

      fl_print_format(f_string_format_Q_single_s.string, print->to, print->set->notable, modes->array[i], print->set->notable);

      if (++i < modes->used) {
        fl_print_format("%[', '%]", print->to, print->set->important, print->set->important);
      }
    } // for

    fl_print_format(f_string_format_sentence_end_quote_s.string, print->to, print->set->important, print->set->important, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_fake_print_message_building_

#ifndef _di_fake_print_message_delete_all_files_
  f_status_t fake_print_message_delete_all_files(fl_print_t * const print) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_normal_e) return F_output_not;

    fake_main_t * const main = (fake_main_t *) print->custom;

    fake_print_context_important_simple_variable(print, "Deleting all files within build directory ", main->setting.build, 0);

    return F_okay;
  }
#endif // _di_fake_print_message_delete_all_files_

#ifndef _di_fake_print_message_generating_skeleton_
  f_status_t fake_print_message_generating_skeleton(fl_print_t * const print) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_normal_e) return F_output_not;

    fake_print_context_important_simple(print, "Generating skeleton structure");

    return F_okay;
  }
#endif // _di_fake_print_message_generating_skeleton_

#ifndef _di_fake_print_message_help_
  f_status_t fake_print_message_help(fl_print_t * const print) {

    if (!print) return F_status_set_error(F_output_not);

    f_file_stream_lock(print->to);

    fll_program_print_help_header(print, fake_program_name_long_s, fake_program_version_s);

    fll_program_print_help_option_standard(print);

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fll_program_print_help_option(print, fake_short_define_s, fake_long_define_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "  Append an additional define after defines from settings file.");
    fll_program_print_help_option(print, fake_short_fakefile_s, fake_long_fakefile_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "Use this fakefile.");
    fll_program_print_help_option(print, fake_short_mode_s, fake_long_mode_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "    Use this mode when processing the build settings.");
    fll_program_print_help_option(print, fake_short_process_s, fake_long_process_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, " Process name for storing build states.");
    fll_program_print_help_option(print, fake_short_settings_s, fake_long_settings_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "Use this settings file.");

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fll_program_print_help_option(print, fake_short_build_s, fake_long_build_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "    Specify a custom build directory.");
    fll_program_print_help_option(print, fake_short_data_s, fake_long_data_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "     Specify a custom path to the data files.");
    fll_program_print_help_option(print, fake_short_documents_s, fake_long_documents_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "Specify a custom path to the documents files.");
    fll_program_print_help_option(print, fake_short_licenses_s, fake_long_licenses_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, " Specify a custom path to the licenses files.");
    fll_program_print_help_option(print, fake_short_sources_s, fake_long_sources_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "  Specify a custom path to the source files.");
    fll_program_print_help_option(print, fake_short_under_s, fake_long_under_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "    Specify a custom path the data build files are under.");
    fll_program_print_help_option(print, fake_short_work_s, fake_long_work_s, f_console_symbol_short_normal_s, f_console_symbol_long_normal_s, "     Use includes/libraries/programs from this directory instead of system.");

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fll_program_print_help_special_options(print);

    fll_program_print_help_option_long(print, fake_long_documents_disabled_s, f_console_symbol_long_normal_s, "   Forcibly do not build documents files.");
    fll_program_print_help_option_long(print, fake_long_documents_enabled_s, f_console_symbol_long_normal_s, "    Forcibly do build documents files.");
    fll_program_print_help_option_long(print, fake_long_shared_disabled_s, f_console_symbol_long_normal_s, "Forcibly do not build shared files.");
    fll_program_print_help_option_long(print, fake_long_shared_enabled_s, f_console_symbol_long_normal_s, " Forcibly do build shared files.");
    fll_program_print_help_option_long(print, fake_long_static_disabled_s, f_console_symbol_long_normal_s, "Forcibly do not build static files.");
    fll_program_print_help_option_long(print, fake_long_static_enabled_s, f_console_symbol_long_normal_s, " Forcibly do build static files.");

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fll_program_print_help_operations(print);

    fll_program_print_help_option_other(print, fake_other_operation_build_s, "   Build or compile the code based on build settings file.");
    fll_program_print_help_option_other(print, fake_other_operation_clean_s, "   Delete all build files.");
    fll_program_print_help_option_other(print, fake_other_operation_make_s, "    Build or compile the code based on fakefile (default).");
    fll_program_print_help_option_other(print, fake_other_operation_skeleton_s, "Build a skeleton directory structure.");

    f_print_dynamic_raw(f_string_eol_s, print->to);

    fll_program_print_help_usage(print, fake_program_name_s, fake_program_help_parameters_s);

    fl_print_format("%r  When performing the %[%r%] operation, the", print->to, f_string_eol_s, print->set->notable, fake_other_operation_build_s, print->set->notable);
    fl_print_format(" %[%r%r%] parameter specifies a name (limited to alpha-numeric, underscore, and dash) to be used in addition to the global.%r", print->to, print->set->notable, f_console_symbol_long_normal_s, fake_long_mode_s, print->set->notable, f_string_eol_s);

    fl_print_format("  For example, when a %[%r%]", print->to, print->set->notable, fake_make_parameter_variable_mode_s, print->set->notable);
    fl_print_format(" of 'fll_monolithic' is specified, build libraries from both 'build_libraries' and 'build_libraries-fll_monolithic' are used (but not 'build_libraries-fll_level').%r%r", print->to, f_string_eol_s, f_string_eol_s);

    fl_print_format("  When specifying the %[%r%] or the %[%r%]", print->to, print->set->notable, fake_make_parameter_variable_fakefile_s, print->set->notable, print->set->notable, fake_make_parameter_variable_settings_s, print->set->notable);
    fl_print_format(" parameters, the project root is seached first and then the build data director is searched when the given file does not contain a directory separator.%r", print->to, f_string_eol_s);

    fl_print_format("  For example, with '%[%r%r my_fakefile%]' the fakefile at", print->to, print->set->notable, f_console_symbol_long_normal_s, fake_long_fakefile_s, print->set->notable);
    fl_print_format(" '%[./my_fakefile%]' is used if found, but if it is not found then", print->to, print->set->notable, print->set->notable);
    fl_print_format(" '%[./%r%rmy_fakefile%]' is used if found.%r", print->to, print->set->notable, fake_default_data_s, fake_default_build_s, print->set->notable, f_string_eol_s);
    fl_print_format("  For example, with '%[%r%r ./my_fakefile%]' the fakefile at", print->to, print->set->notable, f_console_symbol_long_normal_s, fake_long_fakefile_s, print->set->notable);
    fl_print_format(" '%[./my_fakefile%]' is used if found, but if it is not found then no other paths are attempted.%r%r", print->to, print->set->notable, print->set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  When piping data to this program, the piped data is treated as if it were prepended to the %[%r%]", print->to, print->set->notable, fake_make_parameter_variable_fakefile_s, print->set->notable);
    fl_print_format(" or the %[%r%], depending on the operation.%r", print->to, print->set->notable, fake_make_parameter_variable_settings_s, print->set->notable, f_string_eol_s);

    fl_print_format("  A section name from the fakefile that does not conflict with an operation name may be specified when performing the %[%r%] operation.%r", print->to, print->set->notable, fake_other_operation_make_s, print->set->notable, f_string_eol_s);

    f_file_stream_flush(print->to);
    f_file_stream_unlock(print->to);

    return F_okay;
  }
#endif // _di_fake_print_message_help_

#ifdef __cplusplus
} // extern "C"
#endif
