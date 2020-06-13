/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_make_h
#define _PRIVATE_make_h

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_make_section_
  #define fake_make_section_main     "main"
  #define fake_make_section_settings "settings"

  #define fake_make_section_main_length     4
  #define fake_make_section_settings_length 8
#endif // _di_fake_make_section_

// @todo safety checks that ensures operations on files only happen inside the project directory, represented by "top".
#ifndef _di_fake_make_setting_
  #define fake_make_setting_define     "define"     // @todo 'define' means define this as an environment variable on run, only a single argument is supported. (consider a second parameter such as 'if_missing' or 'if_exists' to define this only if it is not already defined.)
  #define fake_make_setting_load_build "load_build" // @todo ("yes"/"no") as in use the build settings file, write code to import that first and match all settings from that into this.

  #define fake_make_setting_define_length     6
  #define fake_make_setting_load_build_length 10
#endif // _di_fake_make_setting_

// @todo "operate" should use a call stack, but do not allow recursive calls (check to see if named operation is already on the call stack).
#ifndef _di_fake_make_operation_
  #define fake_make_operation_archive  "archive"  // run the ar linker (all arguments are passed as arguments, except for reserved parameter words, with $ in front, such as $build_1).
  #define fake_make_operation_build    "build"    // run the fake build operation ($1 = path to settings file, if missing use default, auto-passes verbosity and other Fake parameters.).
  #define fake_make_operation_clean    "clean"    // run the fake clean operation (auto-passes verbosity and other Fake parameters.).
  #define fake_make_operation_compile  "compile"  // run the gcc compiler (all arguments are passed as arguments, except for reserved parameter words, with $ in front, such as $build_1).
  #define fake_make_operation_create   "create"   // create a file or directory ($1 = 'file' or 'directory') ($2 = path to file or directory) ($3 = 'recursive' (optional) for 'directory' only).
  #define fake_make_operation_delete   "delete"   // delete a file or directory ($1 = 'file' or 'directory') ($2 = path to file or directory) ($3 = 'recursive' (optional) for 'directory' only).
  #define fake_make_operation_else     "else"     // execute next line if immediately previous "if" condition fails (if exists file_name.txt, if defined environment_name, if equals "some string or define" "another string or define", if succeed for previous run/shell command succeeding, if fail for previous run/shell command failing).
  #define fake_make_operation_fail     "fail"     // what to do when a command fails, either 'exit', 'warn' or 'ignore'.
  #define fake_make_operation_group    "group"    // change group on file or directory ($1 = path to file or directory).
  #define fake_make_operation_if       "if"       // execute next line if condition succeeds (if exists file_name.txt, if defined environment_name, if equals "some string or define" "another string or define", if succeed for previous run/shell command succeeding, if fail for previous run/shell command failing).
  #define fake_make_operation_link     "link"     // create a symbolic link ($1 = target) ($2 = point). (@todo also don't allow linking outside project directory).
  #define fake_make_operation_mode     "mode"     // change mode of a file or directory ($1 = path to file or directory).
  #define fake_make_operation_operate  "operate"  // enter into a given named operation except for reserved .
  #define fake_make_operation_owner    "owner"    // change owner on file or directory ($1 = path to file or directory).
  #define fake_make_operation_pop      "pop"      // pop the previous directory off the stack, changing to the popped directory.
  #define fake_make_operation_print    "print"    // print to an output or file ($1 = color, out, error, warning) ($2 = if $1 = color, then out, error, warning; else string to print) ($3 = if $1 = color, then string to print).
  #define fake_make_operation_run      "run"      // execute command via PATH ($1 = program name, all other arguments are passed as arguments, except for reserved parameter words, with $ in front, such as $build_1).
  #define fake_make_operation_shell    "shell"    // execute command at path ($1 = path to program/script, all other arguments are passed as arguments, except for reserved parameter words, with $ in front, such as $build_1).
  #define fake_make_operation_skeleton "skeleton" // run the fake skeleton operation (auto-passes verbosity and other Fake parameters.).
  #define fake_make_operation_to       "to"       // change into a given directory, adding it to the directory stack ($1 = directory name).
  #define fake_make_operation_top      "top"      // change to project root, clearing directory stack.
  #define fake_make_operation_touch    "touch"    // perform touch operation on file or directoy ($1 = path to file or directory).

  #define fake_make_operation_archive_length  7
  #define fake_make_operation_build_length    5
  #define fake_make_operation_clean_length    5
  #define fake_make_operation_compile_length  7
  #define fake_make_operation_create_length   6
  #define fake_make_operation_delete_length   6
  #define fake_make_operation_else_length     4
  #define fake_make_operation_fail_length     4
  #define fake_make_operation_group_length    5
  #define fake_make_operation_if_length       2
  #define fake_make_operation_link_length     4
  #define fake_make_operation_mode_length     4
  #define fake_make_operation_operate_length  7
  #define fake_make_operation_owner_length    5
  #define fake_make_operation_pop_length      3
  #define fake_make_operation_print_length    5
  #define fake_make_operation_run_length      3
  #define fake_make_operation_shell_length    5
  #define fake_make_operation_skeleton_length 8
  #define fake_make_operation_to_length       2
  #define fake_make_operation_top_length      3
  #define fake_make_operation_touch_length    5

  enum {
    fake_make_operation_type_archive,
    fake_make_operation_type_build,
    fake_make_operation_type_clean,
    fake_make_operation_type_compile,
    fake_make_operation_type_create,
    fake_make_operation_type_delete,
    fake_make_operation_type_else,
    fake_make_operation_type_fail,
    fake_make_operation_type_group,
    fake_make_operation_type_if,
    fake_make_operation_type_link,
    fake_make_operation_type_mode,
    fake_make_operation_type_operate,
    fake_make_operation_type_owner,
    fake_make_operation_type_pop,
    fake_make_operation_type_print,
    fake_make_operation_type_run,
    fake_make_operation_type_shell,
    fake_make_operation_type_skeleton,
    fake_make_operation_type_to,
    fake_make_operation_type_top,
    fake_make_operation_type_touch,
  };
#endif // _di_fake_make_operation_

// @todo each one of these should be made available to be passed to the program as "$parameter_define[X]" for multi-value (define) or "$parameter_no_color" for single-value (no_color).
#ifndef _di_fake_make_parameter_
  #define fake_make_parameter_variable_build    "build"
  #define fake_make_parameter_variable_dark     "dark"
  #define fake_make_parameter_variable_data     "data"
  #define fake_make_parameter_variable_define   "define"
  #define fake_make_parameter_variable_light    "light"
  #define fake_make_parameter_variable_mode     "mode"
  #define fake_make_parameter_variable_no_color "no_color"
  #define fake_make_parameter_variable_process  "process"
  #define fake_make_parameter_variable_quiet    "quiet"
  #define fake_make_parameter_variable_settings "settings"
  #define fake_make_parameter_variable_sources  "sources"
  #define fake_make_parameter_variable_verbose  "verbose"
  #define fake_make_parameter_variable_work     "work"

  #define fake_make_file_parameter_variable_build_length    5
  #define fake_make_file_parameter_variable_dark_length     5
  #define fake_make_file_parameter_variable_data_length     5
  #define fake_make_file_parameter_variable_define_length   6
  #define fake_make_file_parameter_variable_light_length    5
  #define fake_make_file_parameter_variable_mode_length     4
  #define fake_make_file_parameter_variable_no_color_length 8
  #define fake_make_file_parameter_variable_process_length  7
  #define fake_make_file_parameter_variable_quiet_length    5
  #define fake_make_file_parameter_variable_settings_length 8
  #define fake_make_file_parameter_variable_sources_length  7
  #define fake_make_file_parameter_variable_verbose_length  7
  #define fake_make_file_parameter_variable_work_length     4

  typedef struct {
    f_string_dynamics build;
    f_string_dynamics dark;
    f_string_dynamics data;
    f_string_dynamics define;
    f_string_dynamics light;
    f_string_dynamics mode;
    f_string_dynamics no_color;
    f_string_dynamics process;
    f_string_dynamics quiet;
    f_string_dynamics settings;
    f_string_dynamics sources;
    f_string_dynamics verbose;
    f_string_dynamics work;
  } fake_make_parameter;

  #define fake_make_parameter_initialize { \
    f_string_dynamics_initialize \
    f_string_dynamics_initialize \
    f_string_dynamics_initialize \
    f_string_dynamics_initialize \
    f_string_dynamics_initialize \
    f_string_dynamics_initialize \
    f_string_dynamics_initialize \
    f_string_dynamics_initialize \
    f_string_dynamics_initialize \
    f_string_dynamics_initialize \
    f_string_dynamics_initialize \
    f_string_dynamics_initialize \
    f_string_dynamics_initialize \
  }
#endif // _di_fake_make_parameter_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_make_h
