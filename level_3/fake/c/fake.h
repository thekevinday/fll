/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * The Feautureless Make System (aka fake) used as a package build tool.
 *
 * This program is intented only to build source code into binaries.
 * It specifically does not install, test, or package some project.
 * It does provide the built binaries and scripts in a consistent range for other programs to operate on.
 *
 * This currently only supports a few select languages.
 * Additional languages can be provided via explicit operations.
 *
 * The built sources are placed in the build directory with the following structure:
 *   - build/
 *     - data/
 *     - documents/
 *     - includes/
 *     - libraries/
 *       - script/
 *       - shared/
 *       - static/
 *     - objects/
 *     - programs/
 *       - script/
 *       - shared/
 *       - static/
 *     - settings/
 *     - stage/
 *
 * The "data/" directory contains all file data, such as firmware or files commonly found under /usr/share in a standard GNU Linux system.
 * The "documents/" directory contains all documentation after any build-time processing.
 * The "libraries/" and "programs/" directories contains the sub-directories "script/", "shared/", and "static/".
 * The "libraries/" directory will contain compiled libraries or library-like scripts in their respective sub-directories.
 * The "objects/" directory will contain any compile object files.
 * The "progams/" directory will contain compiled programs or program-like scripts in their respective sub-directories.
 * The "settings/" directory contains all configuration data, such as files commonly found under /etc in a standard GNU Linux system.
 * The "stage/" directory will contain build-time data.
 */
#ifndef _fake_h

// libc includes.
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// fll-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/type_array.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>
#include <fll/level_0/account.h>
#include <fll/level_0/color.h>
#include <fll/level_0/console.h>
#include <fll/level_0/directory.h>
#include <fll/level_0/environment.h>
#include <fll/level_0/execute.h>
#include <fll/level_0/file.h>
#include <fll/level_0/iki.h>
#include <fll/level_0/path.h>
#include <fll/level_0/print.h>
#include <fll/level_0/signal.h>

// fll-1 includes
#include <fll/level_1/console.h>
#include <fll/level_1/conversion.h>
#include <fll/level_1/directory.h>
#include <fll/level_1/environment.h>
#include <fll/level_1/iki.h>
#include <fll/level_1/print.h>
#include <fll/level_1/string.h>

// fll-2 includes
#include <fll/level_2/error.h>
#include <fll/level_2/execute.h>
#include <fll/level_2/file.h>
#include <fll/level_2/fss.h>
#include <fll/level_2/fss_basic_list.h>
#include <fll/level_2/fss_extended.h>
#include <fll/level_2/path.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_program_version_
  #define fake_program_version_major_s F_string_ascii_0_s
  #define fake_program_version_minor_s F_string_ascii_5_s
  #define fake_program_version_micro_s F_string_ascii_8_s

  #ifndef fake_program_version_nano_prefix_s
    #define fake_program_version_nano_prefix_s
  #endif

  #ifndef fake_program_version_nano_s
    #define fake_program_version_nano_s
  #endif

  #define fake_program_version_s fake_program_version_major_s F_string_ascii_period_s fake_program_version_minor_s F_string_ascii_period_s fake_program_version_micro_s fake_program_version_nano_prefix_s fake_program_version_nano_s
#endif // _di_fake_program_version_

#ifndef _di_fake_program_name_
  #define fake_program_name_s      "fake"
  #define fake_program_name_long_s "Featureless Make"
#endif // _di_fake_program_name_

#ifndef _di_fake_default_allocation_step_
  // Set to at least 4 to provide a UTF-8 friendly allocation step.
  #define fake_default_allocation_small_d 4
  #define fake_default_allocation_large_d 64
#endif // _di_fake_default_allocation_step_

/**
 * The build operation utilizes pre-defined path structures.
 * These structures are hard-coded by their individual pieces to be constructed later on.
 */
#ifndef _di_fake_path_
  #define fake_path_part_bash_s      "bash"      F_path_separator_s
  #define fake_path_part_build_s     "build"     F_path_separator_s
  #define fake_path_part_c_s         "c"         F_path_separator_s
  #define fake_path_part_cpp_s       "c++"       F_path_separator_s
  #define fake_path_part_data_s      "data"      F_path_separator_s
  #define fake_path_part_documents_s "documents" F_path_separator_s
  #define fake_path_part_includes_s  "includes"  F_path_separator_s
  #define fake_path_part_libraries_s "libraries" F_path_separator_s
  #define fake_path_part_licenses_s  "licenses"  F_path_separator_s
  #define fake_path_part_objects_s   "objects"   F_path_separator_s
  #define fake_path_part_process_s   "process"   F_path_separator_s
  #define fake_path_part_programs_s  "programs"  F_path_separator_s
  #define fake_path_part_script_s    "script"    F_path_separator_s
  #define fake_path_part_settings_s  "settings"  F_path_separator_s
  #define fake_path_part_shared_s    "shared"    F_path_separator_s
  #define fake_path_part_stage_s     "stage"     F_path_separator_s
  #define fake_path_part_static_s    "static"    F_path_separator_s

  #define fake_path_part_bash_s_length      5
  #define fake_path_part_build_s_length     6
  #define fake_path_part_c_s_length         2
  #define fake_path_part_cpp_s_length       4
  #define fake_path_part_data_s_length      5
  #define fake_path_part_documents_s_length 10
  #define fake_path_part_includes_s_length  9
  #define fake_path_part_libraries_s_length 10
  #define fake_path_part_licenses_s_length  9
  #define fake_path_part_objects_s_length   8
  #define fake_path_part_process_s_length   8
  #define fake_path_part_programs_s_length  9
  #define fake_path_part_script_s_length    7
  #define fake_path_part_settings_s_length  9
  #define fake_path_part_shared_s_length    7
  #define fake_path_part_stage_s_length     6
  #define fake_path_part_static_s_length    7
#endif // _di_fake_path_

#ifndef _di_fake_file_
  #define fake_file_defines_s      "defines"
  #define fake_file_dependencies_s "dependencies"
  #define fake_file_readme_s       "readme"

  #define fake_file_defines_s_length      7
  #define fake_file_dependencies_s_length 12
  #define fake_file_readme_s_length       6
#endif // _di_fake_file_

/**
 * Provide default settings.
 */
#ifndef _di_fake_defaults_
  #define fake_default_path_build_s   "build"   F_path_separator_s
  #define fake_default_path_data_s    "data"    F_path_separator_s
  #define fake_default_path_sources_s "sources" F_path_separator_s
  #define fake_default_path_work_s    ""

  #define fake_default_path_build_s_length   6
  #define fake_default_path_data_s_length    5
  #define fake_default_path_sources_s_length 8
  #define fake_default_path_work_s_length    0

  #define fake_default_define_s   ""
  #define fake_default_fakefile_s "fakefile"
  #define fake_default_mode_s     ""
  #define fake_default_process_s  ""
  #define fake_default_settings_s "settings"

  #define fake_default_define_s_length   0
  #define fake_default_fakefile_s_length 8
  #define fake_default_mode_s_length     0
  #define fake_default_process_s_length  0
  #define fake_default_settings_s_length 8
#endif // _di_fake_defaults_

#ifndef _di_fake_build_language_
  enum {
    fake_build_language_type_bash_e = 1,
    fake_build_language_type_c_e,
    fake_build_language_type_cpp_e,
  };

  #define fake_build_language_bash_s "bash"
  #define fake_build_language_c_s    "c"
  #define fake_build_language_cpp_s  "c++"

  #define fake_build_language_bash_s_length 4
  #define fake_build_language_c_s_length    1
  #define fake_build_language_cpp_s_length  3
#endif // _di_fake_build_language_

#ifndef _di_fake_build_version_
  enum {
    fake_build_version_type_major_e = 1,
    fake_build_version_type_minor_e,
    fake_build_version_type_micro_e,
    fake_build_version_type_nano_e,
  };

  #define fake_build_version_major_s "major"
  #define fake_build_version_minor_s "minor"
  #define fake_build_version_micro_s "micro"
  #define fake_build_version_nano_s  "nano"

  #define fake_build_version_major_s_length 5
  #define fake_build_version_minor_s_length 5
  #define fake_build_version_micro_s_length 5
  #define fake_build_version_nano_s_length  4
#endif // _di_fake_build_version_

#ifndef _di_fake_defines_
  enum {
    fake_operation_build_e = 1,
    fake_operation_clean_e,
    fake_operation_make_e,
    fake_operation_skeleton_e,
  };

  #define fake_signal_check_d       10000
  #define fake_signal_check_tiny_d  4
  #define fake_signal_check_short_d 16

  #define fake_operations_total_d    4
  #define fake_operations_initialize { 0, 0, 0, 0 }

  #define fake_short_define_s   "d"
  #define fake_short_fakefile_s "f"
  #define fake_short_mode_s     "m"
  #define fake_short_process_s  "p"
  #define fake_short_settings_s "s"

  #define fake_short_define_s_length   1
  #define fake_short_fakefile_s_length 1
  #define fake_short_mode_s_length     1
  #define fake_short_process_s_length  1
  #define fake_short_settings_s_length 1

  #define fake_short_path_build_s   "b"
  #define fake_short_path_data_s    "D"
  #define fake_short_path_sources_s "S"
  #define fake_short_path_work_s    "w"

  #define fake_short_path_build_s_length   1
  #define fake_short_path_data_s_length    1
  #define fake_short_path_sources_s_length 1
  #define fake_short_path_work_s_length    1

  #define fake_long_define_s   "define"
  #define fake_long_fakefile_s "fakefile"
  #define fake_long_mode_s     "mode"
  #define fake_long_process_s  "process"
  #define fake_long_settings_s "settings"

  #define fake_long_define_s_length   6
  #define fake_long_fakefile_s_length 8
  #define fake_long_mode_s_length     4
  #define fake_long_process_s_length  7
  #define fake_long_settings_s_length 8

  #define fake_long_path_build_s   "build"
  #define fake_long_path_data_s    "data"
  #define fake_long_path_sources_s "sources"
  #define fake_long_path_work_s    "work"

  #define fake_long_path_build_s_length   5
  #define fake_long_path_data_s_length    4
  #define fake_long_path_sources_s_length 7
  #define fake_long_path_work_s_length    4

  // these special parameters are provided in such a way that they mimic the traditional ./configure script.
  #define fake_long_documents_disabled_s "disable-doc"
  #define fake_long_documents_enabled_s  "enable-doc"
  #define fake_long_shared_disabled_s    "disable-shared"
  #define fake_long_shared_enabled_s     "enable-shared"
  #define fake_long_static_disabled_s    "disable-static"
  #define fake_long_static_enabled_s     "enable-static"

  #define fake_long_documents_disabled_s_length 11
  #define fake_long_documents_enabled_s_length  10
  #define fake_long_shared_disabled_s_length    14
  #define fake_long_shared_enabled_s_length     13
  #define fake_long_static_disabled_s_length    14
  #define fake_long_static_enabled_s_length     13

  #define fake_other_operation_build_s    "build"
  #define fake_other_operation_clean_s    "clean"
  #define fake_other_operation_make_s     "make"
  #define fake_other_operation_skeleton_s "skeleton"

  #define fake_other_operation_build_s_length    5
  #define fake_other_operation_clean_s_length    5
  #define fake_other_operation_make_s_length     4
  #define fake_other_operation_skeleton_s_length 8

  enum {
    fake_parameter_help_e,
    fake_parameter_light_e,
    fake_parameter_dark_e,
    fake_parameter_no_color_e,
    fake_parameter_verbosity_quiet_e,
    fake_parameter_verbosity_normal_e,
    fake_parameter_verbosity_verbose_e,
    fake_parameter_verbosity_debug_e,
    fake_parameter_version_e,

    fake_parameter_define_e,
    fake_parameter_fakefile_e,
    fake_parameter_mode_e,
    fake_parameter_process_e,
    fake_parameter_settings_e,

    fake_parameter_path_build_e,
    fake_parameter_path_data_e,
    fake_parameter_path_sources_e,
    fake_parameter_path_work_e,

    fake_parameter_documents_disabled_e,
    fake_parameter_documents_enabled_e,
    fake_parameter_shared_disabled_e,
    fake_parameter_shared_enabled_e,
    fake_parameter_static_disabled_e,
    fake_parameter_static_enabled_e,

    fake_parameter_operation_build_e,
    fake_parameter_operation_clean_e,
    fake_parameter_operation_make_e,
    fake_parameter_operation_skeleton_e,
  };

  #define fake_console_parameter_t_initialize \
    { \
      macro_f_console_parameter_t_initialize(f_console_standard_short_help_s.string, f_console_standard_long_help_s.string, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_light_s.string, f_console_standard_long_light_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_dark_s.string, f_console_standard_long_dark_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_no_color_s.string, f_console_standard_long_no_color_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_quiet_s.string, f_console_standard_long_quiet_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_normal_s.string, f_console_standard_long_normal_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_verbose_s.string, f_console_standard_long_verbose_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_debug_s.string, f_console_standard_long_debug_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(f_console_standard_short_version_s.string, f_console_standard_long_version_s.string, 0, 0, f_console_type_inverse_e), \
      macro_f_console_parameter_t_initialize(fake_short_define_s, fake_long_define_s, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fake_short_fakefile_s, fake_long_fakefile_s, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fake_short_mode_s, fake_long_mode_s, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fake_short_process_s, fake_long_process_s, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fake_short_settings_s, fake_long_settings_s, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fake_short_path_build_s, fake_long_path_build_s, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fake_short_path_data_s, fake_long_path_data_s, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fake_short_path_sources_s, fake_long_path_sources_s, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(fake_short_path_work_s, fake_long_path_work_s, 0, 1, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(0, fake_long_documents_disabled_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(0, fake_long_documents_enabled_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(0, fake_long_shared_disabled_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(0, fake_long_shared_enabled_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(0, fake_long_static_disabled_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(0, fake_long_static_enabled_s, 0, 0, f_console_type_normal_e), \
      macro_f_console_parameter_t_initialize(0, 0, fake_other_operation_build_s, 0, f_console_type_other_e), \
      macro_f_console_parameter_t_initialize(0, 0, fake_other_operation_clean_s, 0, f_console_type_other_e), \
      macro_f_console_parameter_t_initialize(0, 0, fake_other_operation_make_s, 0, f_console_type_other_e), \
      macro_f_console_parameter_t_initialize(0, 0, fake_other_operation_skeleton_s, 0, f_console_type_other_e), \
    }

  #define fake_total_parameters_d 28
#endif // _di_fake_defines_

#ifndef _di_fake_main_t_
  typedef struct {
    f_console_parameter_t parameters[fake_total_parameters_d];

    f_array_lengths_t remaining;
    bool process_pipe;

    fl_print_t output;
    fl_print_t error;
    fl_print_t warning;

    f_signal_t signal;

    uint8_t operation;
    uint16_t signal_check;

    mode_t umask;
    int child;

    f_string_dynamics_t define;
    f_string_dynamic_t fakefile;
    f_string_dynamics_t mode;
    f_string_dynamic_t process;
    f_string_dynamic_t settings;

    f_string_dynamic_t path_build;
    f_string_dynamic_t path_build_documents;
    f_string_dynamic_t path_build_includes;
    f_string_dynamic_t path_build_libraries;
    f_string_dynamic_t path_build_libraries_script;
    f_string_dynamic_t path_build_libraries_shared;
    f_string_dynamic_t path_build_libraries_static;
    f_string_dynamic_t path_build_objects;
    f_string_dynamic_t path_build_programs;
    f_string_dynamic_t path_build_programs_script;
    f_string_dynamic_t path_build_programs_shared;
    f_string_dynamic_t path_build_programs_static;
    f_string_dynamic_t path_build_settings;
    f_string_dynamic_t path_build_stage;

    f_string_dynamic_t path_data;
    f_string_dynamic_t path_data_build;
    f_string_dynamic_t path_data_settings;

    f_string_dynamic_t path_documents;

    f_string_dynamic_t path_licenses;

    f_string_dynamic_t path_sources;
    f_string_dynamic_t path_sources_bash;
    f_string_dynamic_t path_sources_c;
    f_string_dynamic_t path_sources_cpp;
    f_string_dynamic_t path_sources_script;

    f_string_dynamic_t path_work;
    f_string_dynamic_t path_work_includes;
    f_string_dynamic_t path_work_libraries;
    f_string_dynamic_t path_work_libraries_script;
    f_string_dynamic_t path_work_libraries_shared;
    f_string_dynamic_t path_work_libraries_static;
    f_string_dynamic_t path_work_programs;
    f_string_dynamic_t path_work_programs_script;
    f_string_dynamic_t path_work_programs_shared;
    f_string_dynamic_t path_work_programs_static;

    f_string_dynamic_t file_data_build_defines;
    f_string_dynamic_t file_data_build_dependencies;
    f_string_dynamic_t file_data_build_fakefile;
    f_string_dynamic_t file_data_build_settings;

    f_string_dynamic_t file_documents_readme;

    f_color_context_t context;
  } fake_main_t;

  #define fake_main_t_initialize \
    { \
      fake_console_parameter_t_initialize, \
      f_array_lengths_t_initialize, \
      F_false, \
      fl_print_t_initialize, \
      macro_fl_print_t_initialize_error(), \
      macro_fl_print_t_initialize_warning(), \
      f_signal_t_initialize, \
      0, \
      0, \
      0, \
      0, \
      f_string_dynamics_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamics_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_color_context_t_initialize, \
    }
#endif // _di_fake_main_t_

/**
 * Print help.
 *
 * @param file
 *   The file to print to.
 * @param context
 *   The color context settings.
 *
 * @return
 *   F_none on success.
 */
#ifndef _di_fake_print_help_
  extern f_status_t fake_print_help(const f_file_t file, const f_color_context_t context);
#endif // _di_fake_print_help_

/**
 * Execute main program.
 *
 * Be sure to call fake_main_delete() after executing this.
 *
 * If main.signal is non-zero, then this blocks and handles the following signals:
 *   - F_signal_abort
 *   - F_signal_broken_pipe
 *   - F_signal_hangup
 *   - F_signal_interrupt
 *   - F_signal_quit
 *   - F_signal_termination
 *
 * @param main
 *   The main program data.
 * @param arguments
 *   The parameters passed to the process.
 *
 * @return
 *   F_none on success.
 *   F_child if this is a child process returning.
 *
 *   F_interrupt (with error bit) on receiving a terminate process signal, such as an interrupt signal.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see fake_main_delete()
 */
#ifndef _di_fake_main_
  extern f_status_t fake_main(fake_main_t * const main, const f_console_arguments_t *arguments);
#endif // _di_fake_main_

/**
 * Deallocate main.
 *
 * Be sure to call this after executing fake_main().
 *
 * @param main
 *   The main program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see fake_main()
 */
#ifndef _di_fake_main_delete_
  extern f_status_t fake_main_delete(fake_main_t * const main);
#endif // _di_fake_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_h
