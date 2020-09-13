/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.5
 * Licenses: lgplv2.1
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
 * - build/
 *   - data/
 *   - documents/
 *   - includes/
 *   - libraries/
 *     - script/
 *     - shared/
 *     - static/
 *   - objects/
 *   - programs/
 *     - script/
 *     - shared/
 *     - static/
 *   - settings/
 *   - stage/
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

// libc includes
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// fll-0 includes
#include <level_0/type.h>
#include <level_0/status.h>
#include <level_0/type_array.h>
#include <level_0/memory.h>
#include <level_0/signal.h>
#include <level_0/string.h>
#include <level_0/utf.h>
#include <level_0/account.h>
#include <level_0/console.h>
#include <level_0/directory.h>
#include <level_0/environment.h>
#include <level_0/file.h>
#include <level_0/iki.h>
#include <level_0/path.h>

// fll-1 includes
#include <level_1/color.h>
#include <level_1/console.h>
#include <level_1/conversion.h>
#include <level_1/directory.h>
#include <level_1/iki.h>
#include <level_1/string.h>

// fll-2 includes
#include <level_2/execute.h>
#include <level_2/file.h>
#include <level_2/fss.h>
#include <level_2/fss_basic_list.h>
#include <level_2/fss_extended.h>
#include <level_2/path.h>
#include <level_2/program.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_version_
  #define fake_major_version "0"
  #define fake_minor_version "5"
  #define fake_micro_version "0"
  #define fake_version fake_major_version "." fake_minor_version "." fake_micro_version
#endif // _di_fake_version_

#ifndef _di_fake_name_
  #define fake_name      "fake"
  #define fake_name_long "Featureless Make"
#endif // _di_fake_name_

#ifndef _di_fake_default_allocation_step_
  // Set to at least 4 to provide a UTF-8 friendly allocation step.
  #define fake_default_allocation_step 4
#endif // _di_fake_default_allocation_step_

/**
 * The build operation utilizes pre-defined path structures.
 * These structures are hard-coded by their individual pieces to be constructed later on.
 */
#ifndef _di_fake_path_
  #define fake_path_part_bash      "bash"      f_path_separator
  #define fake_path_part_build     "build"     f_path_separator
  #define fake_path_part_c         "c"         f_path_separator
  #define fake_path_part_cpp       "c++"       f_path_separator
  #define fake_path_part_data      "data"      f_path_separator
  #define fake_path_part_documents "documents" f_path_separator
  #define fake_path_part_includes  "includes"  f_path_separator
  #define fake_path_part_libraries "libraries" f_path_separator
  #define fake_path_part_licenses  "licenses"  f_path_separator
  #define fake_path_part_objects   "objects"   f_path_separator
  #define fake_path_part_process   "process"   f_path_separator
  #define fake_path_part_programs  "programs"  f_path_separator
  #define fake_path_part_script    "script"    f_path_separator
  #define fake_path_part_settings  "settings"  f_path_separator
  #define fake_path_part_shared    "shared"    f_path_separator
  #define fake_path_part_stage     "stage"     f_path_separator
  #define fake_path_part_static    "static"    f_path_separator

  #define fake_path_part_bash_length      5
  #define fake_path_part_build_length     6
  #define fake_path_part_c_length         2
  #define fake_path_part_cpp_length       4
  #define fake_path_part_data_length      5
  #define fake_path_part_documents_length 10
  #define fake_path_part_includes_length  9
  #define fake_path_part_libraries_length 10
  #define fake_path_part_licenses_length  9
  #define fake_path_part_objects_length   8
  #define fake_path_part_process_length   8
  #define fake_path_part_programs_length  9
  #define fake_path_part_script_length    7
  #define fake_path_part_settings_length  9
  #define fake_path_part_shared_length    7
  #define fake_path_part_stage_length     6
  #define fake_path_part_static_length    7
#endif // _di_fake_path_

#ifndef _di_fake_file_
  #define fake_file_defines      "defines"
  #define fake_file_dependencies "dependencies"
  #define fake_file_readme       "readme"

  #define fake_file_defines_length      7
  #define fake_file_dependencies_length 12
  #define fake_file_readme_length       6
#endif // _di_fake_file_

/**
 * Provide default settings.
 */
#ifndef _di_fake_defaults_
  #define fake_default_path_build   "build"   f_path_separator
  #define fake_default_path_data    "data"    f_path_separator
  #define fake_default_path_sources "sources" f_path_separator
  #define fake_default_path_work    ""

  #define fake_default_path_build_length   6
  #define fake_default_path_data_length    5
  #define fake_default_path_sources_length 8
  #define fake_default_path_work_length    0

  #define fake_default_define   ""
  #define fake_default_fakefile "fakefile"
  #define fake_default_mode     ""
  #define fake_default_process  ""
  #define fake_default_settings "settings"

  #define fake_default_define_length   0
  #define fake_default_fakefile_length 8
  #define fake_default_mode_length     0
  #define fake_default_process_length  0
  #define fake_default_settings_length 8
#endif // _di_fake_defaults_

#ifndef _di_fake_build_language_
  enum {
    fake_build_language_type_bash = 1,
    fake_build_language_type_c,
    fake_build_language_type_cpp,
  };

  #define fake_build_language_bash "bash"
  #define fake_build_language_c    "c"
  #define fake_build_language_cpp  "c++"

  #define fake_build_language_bash_length 4
  #define fake_build_language_c_length    1
  #define fake_build_language_cpp_length  3
#endif // _di_fake_build_language_

#ifndef _di_fake_build_version_
  enum {
    fake_build_version_type_major = 1,
    fake_build_version_type_micro,
    fake_build_version_type_minor,
  };

  #define fake_build_version_major "major"
  #define fake_build_version_micro "micro"
  #define fake_build_version_minor "minor"

  #define fake_build_version_major_length 5
  #define fake_build_version_micro_length 5
  #define fake_build_version_minor_length 5
#endif // _di_fake_build_version_

#ifndef _di_fake_defines_
  enum {
    fake_operation_build = 1,
    fake_operation_clean,
    fake_operation_make,
    fake_operation_skeleton,
  };

  #define fake_operations_total      4
  #define fake_operations_initialize { 0, 0, 0, 0 }

  enum {
    fake_verbosity_quiet = 1,
    fake_verbosity_normal,
    fake_verbosity_verbose,
    fake_verbosity_debug,
  };

  #define fake_short_define   "d"
  #define fake_short_fakefile "f"
  #define fake_short_mode     "m"
  #define fake_short_process  "p"
  #define fake_short_settings "s"

  #define fake_short_define_length   1
  #define fake_short_fakefile_length 1
  #define fake_short_mode_length     1
  #define fake_short_process_length  1
  #define fake_short_settings_length 1

  #define fake_short_path_build   "b"
  #define fake_short_path_data    "D"
  #define fake_short_path_sources "S"
  #define fake_short_path_work    "w"

  #define fake_short_path_build_length   1
  #define fake_short_path_data_length    1
  #define fake_short_path_sources_length 1
  #define fake_short_path_work_length    1

  #define fake_long_define   "define"
  #define fake_long_fakefile "fakefile"
  #define fake_long_mode     "mode"
  #define fake_long_process  "process"
  #define fake_long_settings "settings"

  #define fake_long_define_length   6
  #define fake_long_fakefile_length 8
  #define fake_long_mode_length     4
  #define fake_long_process_length  7
  #define fake_long_settings_length 8

  #define fake_long_path_build   "build"
  #define fake_long_path_data    "data"
  #define fake_long_path_sources "sources"
  #define fake_long_path_work    "work"

  #define fake_long_path_build_length   5
  #define fake_long_path_data_length    4
  #define fake_long_path_sources_length 7
  #define fake_long_path_work_length    4

  // these special parameters are provided in such a way that they mimic the traditional ./configure script.
  #define fake_long_documents_disabled "disable-doc"
  #define fake_long_documents_enabled  "enable-doc"
  #define fake_long_shared_disabled    "disable-shared"
  #define fake_long_shared_enabled     "enable-shared"
  #define fake_long_static_disabled    "disable-static"
  #define fake_long_static_enabled     "enable-static"

  #define fake_long_documents_disabled_length 11
  #define fake_long_documents_enabled_length  10
  #define fake_long_shared_disabled_length    14
  #define fake_long_shared_enabled_length     13
  #define fake_long_static_disabled_length    14
  #define fake_long_static_enabled_length     13

  #define fake_other_operation_build    "build"
  #define fake_other_operation_clean    "clean"
  #define fake_other_operation_make     "make"
  #define fake_other_operation_skeleton "skeleton"

  #define fake_other_operation_build_length    5
  #define fake_other_operation_clean_length    5
  #define fake_other_operation_make_length     4
  #define fake_other_operation_skeleton_length 8

  enum {
    fake_parameter_help,
    fake_parameter_light,
    fake_parameter_dark,
    fake_parameter_debug,
    fake_parameter_no_color,
    fake_parameter_quiet,
    fake_parameter_verbose,
    fake_parameter_version,

    fake_parameter_define,
    fake_parameter_fakefile,
    fake_parameter_mode,
    fake_parameter_process,
    fake_parameter_settings,

    fake_parameter_path_build,
    fake_parameter_path_data,
    fake_parameter_path_sources,
    fake_parameter_path_work,

    fake_parameter_documents_disabled,
    fake_parameter_documents_enabled,
    fake_parameter_shared_disabled,
    fake_parameter_shared_enabled,
    fake_parameter_static_disabled,
    fake_parameter_static_enabled,

    fake_parameter_operation_build,
    fake_parameter_operation_clean,
    fake_parameter_operation_make,
    fake_parameter_operation_skeleton,
  };

  #define fake_console_parameter_t_initialize \
    { \
      f_console_parameter_t_initialize(f_console_standard_short_help, f_console_standard_long_help, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(f_console_standard_short_light, f_console_standard_long_light, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_dark, f_console_standard_long_dark, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_debug, f_console_standard_long_debug, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_no_color, f_console_standard_long_no_color, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_quiet, f_console_standard_long_quiet, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_verbose, f_console_standard_long_verbose, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_version, f_console_standard_long_version, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(fake_short_define, fake_long_define, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(fake_short_fakefile, fake_long_fakefile, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(fake_short_mode, fake_long_mode, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(fake_short_process, fake_long_process, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(fake_short_settings, fake_long_settings, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(fake_short_path_build, fake_long_path_build, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(fake_short_path_data, fake_long_path_data, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(fake_short_path_sources, fake_long_path_sources, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(fake_short_path_work, fake_long_path_work, 0, 1, f_console_type_normal), \
      f_console_parameter_t_initialize(0, fake_long_documents_disabled, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(0, fake_long_documents_enabled, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(0, fake_long_shared_disabled, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(0, fake_long_shared_enabled, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(0, fake_long_static_disabled, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(0, fake_long_static_enabled, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(0, 0, fake_other_operation_build, 0, f_console_type_other), \
      f_console_parameter_t_initialize(0, 0, fake_other_operation_clean, 0, f_console_type_other), \
      f_console_parameter_t_initialize(0, 0, fake_other_operation_make, 0, f_console_type_other), \
      f_console_parameter_t_initialize(0, 0, fake_other_operation_skeleton, 0, f_console_type_other), \
    }

  #define fake_total_parameters 27
#endif // _di_fake_defines_

#ifndef _di_fake_data_t_
  typedef struct {
    f_console_parameter_t parameters[fake_total_parameters];

    f_string_lengths_t remaining;
    bool process_pipe;
    mode_t umask;
    f_signal_t signal;

    uint8_t operation;
    uint8_t verbosity;

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

    fl_color_context_t context;
  } fake_data_t;

  #define fake_data_t_initialize \
    { \
      fake_console_parameter_t_initialize, \
      f_string_lengths_t_initialize, \
      F_false, \
      0, \
      f_signal_t_initialize, \
      0, \
      fake_verbosity_normal, \
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
      fl_color_context_t_initialize, \
    }
#endif // _di_fake_data_t_

/**
 * Print help to standard output.
 *
 * @param context
 *   The color context settings.
 *
 * @return
 *   F_none on success.
 */
#ifndef _di_fake_print_help_
  extern f_return_status fake_print_help(const fl_color_context_t context);
#endif // _di_fake_print_help_

/**
 * Execute main program.
 *
 * Be sure to call fake_delete_data() after executing this.
 *
 * If data.signal is non-zero, then this blocks and handles the following signals:
 * - F_signal_abort
 * - F_signal_hangup
 * - F_signal_interrupt
 * - F_signal_quit
 * - F_signal_termination
 *
 * @param arguments
 *   The parameters passed to the process.
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *   F_status if one of the above signals is received.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see fake_delete_data()
 */
#ifndef _di_fake_main_
  extern f_return_status fake_main(const f_console_arguments_t arguments, fake_data_t *data);
#endif // _di_fake_main_

/**
 * Deallocate data.
 *
 * Be sure to call this after executing fake_main().
 *
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see fake_main()
 */
#ifndef _di_fake_delete_data_
  extern f_return_status fake_delete_data(fake_data_t *data);
#endif // _di_fake_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_h
