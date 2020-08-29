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

  #define fake_make_section_stack_max 8192 // maximum stack call depth.
#endif // _di_fake_make_section_

#ifndef _di_fake_make_setting_
  typedef struct {
    bool load_build;

    uint8_t fail;

    f_string_map_multis parameter;
  } fake_make_setting;

  #define fake_make_setting_initialize { \
    0, \
    0, \
    f_string_map_multis_initialize, \
  }

  #define fake_macro_make_setting_delete_simple(setting) \
    f_macro_string_map_multis_delete_simple(setting.parameter)

  #define fake_make_setting_compiler    "compiler"
  #define fake_make_setting_define      "define"
  #define fake_make_setting_environment "environment"
  #define fake_make_setting_fail        "fail"
  #define fake_make_setting_linker      "linker"
  #define fake_make_setting_load_build  "load_build"
  #define fake_make_setting_parameter   "parameter"
  #define fake_make_setting_return      "return"

  #define fake_make_setting_compiler_length    8
  #define fake_make_setting_define_length      6
  #define fake_make_setting_environment_length 11
  #define fake_make_setting_fail_length        4
  #define fake_make_setting_linker_length      6
  #define fake_make_setting_load_build_length  10
  #define fake_make_setting_parameter_length   9
  #define fake_make_setting_return_length      6
#endif // _di_fake_make_setting_

// @todo "operate" should use a call stack, but do not allow recursive calls (check to see if named operation is already on the call stack).
#ifndef _di_fake_make_operation_
  #define fake_make_operation_archive  "archive"
  #define fake_make_operation_build    "build"
  #define fake_make_operation_break    "break"
  #define fake_make_operation_clean    "clean"
  #define fake_make_operation_compile  "compile"
  #define fake_make_operation_define   "define"
  #define fake_make_operation_delete   "delete"
  #define fake_make_operation_deletes  "deletes"
  #define fake_make_operation_else     "else"
  #define fake_make_operation_exit     "exit"
  #define fake_make_operation_fail     "fail"
  #define fake_make_operation_group    "group"
  #define fake_make_operation_groups   "groups"
  #define fake_make_operation_if       "if"
  #define fake_make_operation_link     "link"
  #define fake_make_operation_mode     "mode"
  #define fake_make_operation_modes    "modes"
  #define fake_make_operation_operate  "operate"
  #define fake_make_operation_owner    "owner"
  #define fake_make_operation_owners   "owners"
  #define fake_make_operation_pop      "pop"
  #define fake_make_operation_print    "print"
  #define fake_make_operation_run      "run"
  #define fake_make_operation_shell    "shell"
  #define fake_make_operation_skeleton "skeleton"
  #define fake_make_operation_to       "to"
  #define fake_make_operation_top      "top"
  #define fake_make_operation_touch    "touch"

  #define fake_make_operation_archive_length  7
  #define fake_make_operation_break_length    5
  #define fake_make_operation_build_length    5
  #define fake_make_operation_clean_length    5
  #define fake_make_operation_compile_length  7
  #define fake_make_operation_define_length   6
  #define fake_make_operation_delete_length   6
  #define fake_make_operation_deletes_length  7
  #define fake_make_operation_else_length     4
  #define fake_make_operation_exit_length     4
  #define fake_make_operation_fail_length     4
  #define fake_make_operation_group_length    5
  #define fake_make_operation_groups_length   6
  #define fake_make_operation_if_length       2
  #define fake_make_operation_link_length     4
  #define fake_make_operation_mode_length     4
  #define fake_make_operation_modes_length    5
  #define fake_make_operation_operate_length  7
  #define fake_make_operation_owner_length    5
  #define fake_make_operation_owners_length   6
  #define fake_make_operation_pop_length      3
  #define fake_make_operation_print_length    5
  #define fake_make_operation_run_length      3
  #define fake_make_operation_shell_length    5
  #define fake_make_operation_skeleton_length 8
  #define fake_make_operation_to_length       2
  #define fake_make_operation_top_length      3
  #define fake_make_operation_touch_length    5

  enum {
    fake_make_operation_type_archive = 1,
    fake_make_operation_type_break,
    fake_make_operation_type_build,
    fake_make_operation_type_clean,
    fake_make_operation_type_compile,
    fake_make_operation_type_define,
    fake_make_operation_type_delete,
    fake_make_operation_type_deletes,
    fake_make_operation_type_else,
    fake_make_operation_type_exit,
    fake_make_operation_type_fail,
    fake_make_operation_type_group,
    fake_make_operation_type_groups,
    fake_make_operation_type_if,
    fake_make_operation_type_link,
    fake_make_operation_type_mode,
    fake_make_operation_type_modes,
    fake_make_operation_type_operate,
    fake_make_operation_type_owner,
    fake_make_operation_type_owners,
    fake_make_operation_type_pop,
    fake_make_operation_type_print,
    fake_make_operation_type_run,
    fake_make_operation_type_shell,
    fake_make_operation_type_skeleton,
    fake_make_operation_type_to,
    fake_make_operation_type_top,
    fake_make_operation_type_touch,
  };

  #define fake_make_operation_total 28

  #define fake_make_operation_argument_failure   "failure"
  #define fake_make_operation_argument_file      "file"
  #define fake_make_operation_argument_directory "directory"
  #define fake_make_operation_argument_error     "error"
  #define fake_make_operation_argument_exit      "exit"
  #define fake_make_operation_argument_ignore    "ignore"
  #define fake_make_operation_argument_point     "point"
  #define fake_make_operation_argument_recursive "recursive"
  #define fake_make_operation_argument_success   "success"
  #define fake_make_operation_argument_target    "target"
  #define fake_make_operation_argument_warn      "warn"

  #define fake_make_operation_argument_failure_length   7
  #define fake_make_operation_argument_file_length      4
  #define fake_make_operation_argument_directory_length 9
  #define fake_make_operation_argument_error_length     5
  #define fake_make_operation_argument_exit_length      4
  #define fake_make_operation_argument_ignore_length    6
  #define fake_make_operation_argument_point_length     5
  #define fake_make_operation_argument_recursive_length 9
  #define fake_make_operation_argument_success_length   7
  #define fake_make_operation_argument_target_length    6
  #define fake_make_operation_argument_warn_length      4

  #define fake_make_operation_argument_if_defined       "defined"
  #define fake_make_operation_argument_if_equal         "=="
  #define fake_make_operation_argument_if_equal_not     "<>"
  #define fake_make_operation_argument_if_exists        "exists"
  #define fake_make_operation_argument_if_failure       "failure"
  #define fake_make_operation_argument_if_greater       ">"
  #define fake_make_operation_argument_if_greater_equal ">="
  #define fake_make_operation_argument_if_group         "group"
  #define fake_make_operation_argument_if_is            "is"
  #define fake_make_operation_argument_if_is_for        "for"
  #define fake_make_operation_argument_if_less          "<"
  #define fake_make_operation_argument_if_less_equal    "<="
  #define fake_make_operation_argument_if_mode          "mode"
  #define fake_make_operation_argument_if_owner         "owner"
  #define fake_make_operation_argument_if_success       "success"

  #define fake_make_operation_argument_if_defined_length       7
  #define fake_make_operation_argument_if_equal_length         2
  #define fake_make_operation_argument_if_equal_not_length     2
  #define fake_make_operation_argument_if_exists_length        6
  #define fake_make_operation_argument_if_failure_length       7
  #define fake_make_operation_argument_if_greater_length       1
  #define fake_make_operation_argument_if_greater_equal_length 2
  #define fake_make_operation_argument_if_group_length         5
  #define fake_make_operation_argument_if_is_length            2
  #define fake_make_operation_argument_if_is_for_length        3
  #define fake_make_operation_argument_if_less_length          1
  #define fake_make_operation_argument_if_less_equal_length    2
  #define fake_make_operation_argument_if_mode_length          4
  #define fake_make_operation_argument_if_owner_length         5
  #define fake_make_operation_argument_if_success_length       7

  enum {
    fake_make_operation_if_type_else_false = 1,
    fake_make_operation_if_type_else_false_next,
    fake_make_operation_if_type_else_true,
    fake_make_operation_if_type_else_true_next,
    fake_make_operation_if_type_false,
    fake_make_operation_if_type_false_next,
    fake_make_operation_if_type_if_defined,
    fake_make_operation_if_type_if_equal,
    fake_make_operation_if_type_if_equal_not,
    fake_make_operation_if_type_if_exists,
    fake_make_operation_if_type_if_failure,
    fake_make_operation_if_type_if_greater,
    fake_make_operation_if_type_if_greater_equal,
    fake_make_operation_if_type_if_group,
    fake_make_operation_if_type_if_is,
    fake_make_operation_if_type_if_less,
    fake_make_operation_if_type_if_less_equal,
    fake_make_operation_if_type_if_mode,
    fake_make_operation_if_type_if_owner,
    fake_make_operation_if_type_if_success,
    fake_make_operation_if_type_true,
    fake_make_operation_if_type_true_next,
  };

  enum {
    fake_make_operation_fail_type_exit = 1,
    fake_make_operation_fail_type_warn,
    fake_make_operation_fail_type_ignore,
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
  #define fake_make_parameter_variable_return   "return"
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
  #define fake_make_file_parameter_variable_return_length   6
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
    f_string_dynamics_initialize, \
    f_string_dynamics_initialize, \
    f_string_dynamics_initialize, \
    f_string_dynamics_initialize, \
    f_string_dynamics_initialize, \
    f_string_dynamics_initialize, \
    f_string_dynamics_initialize, \
    f_string_dynamics_initialize, \
    f_string_dynamics_initialize, \
    f_string_dynamics_initialize, \
    f_string_dynamics_initialize, \
    f_string_dynamics_initialize, \
    f_string_dynamics_initialize, \
  }

  #define fake_macro_make_parameter_delete_simple(parameter) \
    f_macro_string_dynamics_delete_simple(parameter.build) \
    f_macro_string_dynamics_delete_simple(parameter.dark) \
    f_macro_string_dynamics_delete_simple(parameter.data) \
    f_macro_string_dynamics_delete_simple(parameter.define) \
    f_macro_string_dynamics_delete_simple(parameter.light) \
    f_macro_string_dynamics_delete_simple(parameter.mode) \
    f_macro_string_dynamics_delete_simple(parameter.no_color) \
    f_macro_string_dynamics_delete_simple(parameter.process) \
    f_macro_string_dynamics_delete_simple(parameter.quiet) \
    f_macro_string_dynamics_delete_simple(parameter.settings) \
    f_macro_string_dynamics_delete_simple(parameter.sources) \
    f_macro_string_dynamics_delete_simple(parameter.verbose) \
    f_macro_string_dynamics_delete_simple(parameter.work)
#endif // _di_fake_make_parameter_

#ifndef _di_fake_make_path_
  typedef struct {
    int top;
    int current;

    f_string_dynamics stack;
  } fake_make_path;

  #define fake_make_path_initialize { \
    0, \
    0, \
    f_string_dynamics_initialize, \
  }

  #define fake_macro_make_path_delete_simple(path) \
    f_macro_string_dynamics_delete_simple(path.stack)
#endif // _di_fake_make_path_

#ifndef _di_fake_make_print_
  typedef struct {
    const char *prefix;
    f_string_static context;

    FILE *to;
  } fake_make_print;

  #define fake_make_print_initialize { \
    0, \
    f_string_static_initialize, \
    0, \
  }

  #define fake_macro_make_print_initialize(prefix, context, to) { prefix, context, to }

  #define fake_make_print_error   "ERROR"
  #define fake_make_print_warning "WARNING"

  #define fake_make_print_error_length   5
  #define fake_make_print_warning_length 7
#endif // _di_fake_make_print_

#ifndef _di_fake_make_data_
  typedef struct {
    fake_build_setting setting_build;
    fake_make_setting setting_make;

    fake_environment environment;

    fake_make_parameter parameter;
    fake_make_path path;
    fake_make_print print;

    f_fss_nameds fakefile;

    f_string_dynamic buffer;
    f_string_dynamic path_cache;

    f_array_length main;
  } fake_make_data;

  #define fake_make_data_initialize { \
    fake_build_setting_initialize, \
    fake_make_setting_initialize, \
    fake_environment_initialize, \
    fake_make_parameter_initialize, \
    fake_make_path_initialize, \
    fake_make_print_initialize, \
    f_fss_nameds_initialize, \
    f_string_dynamic_initialize, \
    f_string_dynamic_initialize, \
    0, \
  }

  #define fake_macro_make_data_delete_simple(data) \
    fake_macro_build_setting_delete_simple(data.setting_build) \
    fake_macro_make_setting_delete_simple(data.setting_make) \
    fake_macro_environment_delete_simple(data.environment) \
    fake_macro_make_parameter_delete_simple(data.parameter) \
    fake_macro_make_path_delete_simple(data.path) \
    f_macro_fss_nameds_delete_simple(data.fakefile) \
    f_macro_string_dynamic_delete_simple(data.buffer) \
    f_macro_string_dynamic_delete_simple(data.path_cache)
#endif // _di_fake_make_data_

/**
 * Assure that a path is within the project root path.
 *
 * @param data
 *   The program data.
 * @param path
 *   file path to get the real path of.
 * @param data_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 *   The data_make.path_cache will be updated to reflect the full path to this file.
 *
 * @return
 *   F_true if inside the project.
 *   F_false (with error bit) if path exists outside of the root project path.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_assure_inside_project_
  extern f_return_status fake_make_assure_inside_project(const fake_data data, const f_string_static path, fake_make_data *data_make) f_gcc_attribute_visibility_internal;
#endif // _di_fake_make_assure_inside_project_

/**
 * Get the group id from either a string representing the number or a string representing the name.
 *
 * @param data
 *   The program data.
 * @param print
 *   The error/warning print data.
 * @param buffer
 *   The string containing the name or number.
 * @param id
 *   The detected group id.
 *
 * @return
 *   F_none on success.
 *   F_exist_not if there is no group by the given name.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_get_id_group_
  f_return_status fake_make_get_id_group(const fake_data data, const fake_make_print print, const f_string_static buffer, gid_t *id) f_gcc_attribute_visibility_internal;
#endif // _di_fake_make_get_id_group_

/**
 * Get the mode id from either a string representing the number or a string representing the mode.
 *
 * @param data
 *   The program data.
 * @param print
 *   The error/warning print data.
 * @param buffer
 *   The string containing the name or number.
 * @param mode
 *   The determined mode.
 *   This uses bitwise data.
 * @param replace
 *   The determined modes that are to be replaced, such as: f_file_mode_replace_owner.
 *   This uses bitwise data.
 *
 * @return
 *   F_none on success.
 *   F_exist_not if there is no mode by the given name.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_get_id_mode_
  f_return_status fake_make_get_id_mode(const fake_data data, const fake_make_print print, const f_string_static buffer, f_file_mode *mode, uint8_t *replace) f_gcc_attribute_visibility_internal;
#endif // _di_fake_make_get_id_mode_

/**
 * Get the user id from either a string representing the number or a string representing the name.
 *
 * @param data
 *   The program data.
 * @param print
 *   The error/warning print data.
 * @param buffer
 *   The string containing the name or number.
 * @param id
 *   The detected user id.
 *
 * @return
 *   F_none on success.
 *   F_exist_not if there is no user by the given name.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_get_id_owner_
  f_return_status fake_make_get_id_owner(const fake_data data, const fake_make_print print, const f_string_static buffer, uid_t *id) f_gcc_attribute_visibility_internal;
#endif // _di_fake_make_get_id_owner_

/**
 * Find the fake file, load it, validate it, and process it.
 *
 * This will process any additional files as necessary, such as the build settings file.
 *
 * @param data
 *   The program data.
 * @param data_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param status
 *   The return status.
 *
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see fake_build_load_setting()
 */
#ifndef _di_fake_make_load_fakefile_
  extern void fake_make_load_fakefile(const fake_data data, fake_make_data *data_make, f_status *status) f_gcc_attribute_visibility_internal;
#endif // _di_fake_make_load_fakefile_

/**
 * Execute the make sections and their respective operations.
 *
 * The first section operated on is the 'main' section.
 * The 'settings' section is only loaded into settings and is never operated on.
 *
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_operate_
  extern f_return_status fake_make_operate(const fake_data data) f_gcc_attribute_visibility_internal;
#endif // _di_fake_make_operate_

/**
 * For a given make section operation, expand the content into an arguments array for that operation.
 *
 * @param data
 *   The program data.
 * @param section_name
 *   The section name.
 * @param operation
 *   The operation being performed.
 * @param operation_name
 *   The operation name.
 * @param content
 *   The content array.
 * @param quoteds
 *   The array of quoted associated with the content.
 * @param data_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param arguments
 *   The expanded arguments.
 * @param status
 *   The return status.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_operate_expand_
  extern void fake_make_operate_expand(const fake_data data, const f_string_range section_name, const f_array_length operation, const f_string_static operation_name, const f_fss_content content, const f_fss_quoteds quoteds, fake_make_data *data_make, f_string_dynamics *arguments, f_status *status) f_gcc_attribute_visibility_internal;
#endif // _di_fake_make_operate_expand_

/**
 * Perform the expand operation, specifically for the environment variables.
 *
 * @param data
 *   The program data.
 * @param quoted
 *   The quoted associated with the content.
 * @param range_name
 *   The range representing the variable content name string within the data_make->buffer.
 * @param data_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param arguments
 *   The expanded arguments.
 *
 * @return
 *   F_true on success and match expanded.
 *   F_false on no matches to expand.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_operate_expand_environment_
  extern f_return_status fake_make_operate_expand_environment(const fake_data data, const f_fss_quoted quoted, const f_string_range range_name, fake_make_data *data_make, f_string_dynamics *arguments) f_gcc_attribute_visibility_internal;
#endif // _di_fake_make_operate_expand_environment_

/**
 * Perform the expand operation, specifically for the build settings.
 *
 * @param data
 *   The program data.
 * @param quoted
 *   The quoted associated with the content.
 * @param range_name
 *   The range representing the variable content name string within the data_make->buffer.
 * @param data_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param arguments
 *   The expanded arguments.
 *
 * @return
 *   F_true on success and match expanded.
 *   F_false on no matches to expand.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_operate_expand_build_
  extern f_return_status fake_make_operate_expand_build(const fake_data data, const f_fss_quoted quoted, const f_string_range range_name, fake_make_data *data_make, f_string_dynamics *arguments) f_gcc_attribute_visibility_internal;
#endif // _di_fake_make_operate_expand_build_

/**
 * Perform the make operations within the given section.
 *
 * @param data
 *   The program data.
 * @param id_section
 *   The array location id within the fakefile of the section to operate on.
 * @param data_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param section_stack
 *   The current operation stack.
 * @param status
 *   The return status.
 *
 *   F_invalid (with error bit set) is returned if any part of the section is invalid, such as an invalid operation name.
 *   F_recurse (with error bit set) is returned if unable to recurse to another operation section (usually max stack depth reached).
 */
#ifndef _di_fake_make_operate_section_
  void fake_make_operate_section(const fake_data data, const f_array_length id_section, fake_make_data *data_make, f_string_lengths *section_stack, f_status *status) f_gcc_attribute_visibility_internal;
#endif // _di_fake_make_operate_section_

/**
 * Perform a specific make operation within the given section.
 *
 * @param data
 *   The program data.
 * @param section_name
 *   The section name.
 * @param operation
 *   The operation type.
 * @param operation_name
 *   The operation name.
 * @param arguments
 *   The expanded arguments.
 * @param success
 *   Whether or not a previous section operation succeeded or failed.
 * @param operation_if
 *   The if-condition status for the current operation.
 * @param data_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param section_stack
 *   The current operation stack.
 * @param status
 *   The return status.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_operate_process_
  extern void fake_make_operate_process(const fake_data data, const f_string_range section_name, const uint8_t operation, const f_string_static operation_name, const f_string_dynamics arguments, const bool success, uint8_t *operation_if, fake_make_data *data_make, f_string_lengths *section_stack, f_status *status) f_gcc_attribute_visibility_internal;
#endif // _di_fake_make_operate_process_

/**
 * Execute either the run operation or the shell operation.
 *
 * @param data
 *   The program data.
 * @param program
 *   The program to be executed.
 * @param arguments
 *   The arguments for the run or shell operation.
 * @param as_shell
 *   When TRUE, this is a shell operation.
 *   When FALSE, this is a run operation.
 * @param data_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 *
 * @return
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_operate_process_execute_
  extern f_return_status fake_make_operate_process_execute(const fake_data data, const f_string_static program, const f_string_statics arguments, const bool as_shell, fake_make_data *data_make) f_gcc_attribute_visibility_internal;
#endif // _di_fake_make_operate_process_execute_

/**
 * Handle the return code, converting it to a number.
 *
 * @param data
 *   The program data.
 * @param data_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param status
 *   The return status.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_operate_process_return_
  extern void fake_make_operate_process_return(const fake_data data, const int return_code, fake_make_data *data_make, f_status *status) f_gcc_attribute_visibility_internal;
#endif // _di_fake_make_operate_process_return_

/**
 * Execute either the run operation or the shell operation.
 *
 * @param data
 *   The program data.
 * @param arguments
 *   The arguments for the run or shell operation.
 * @param as_shell
 *   When TRUE, this is a shell operation.
 *   When FALSE, this is a run operation.
 * @param data_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 *
 * @return
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_operate_process_run_
  extern f_return_status fake_make_operate_process_run(const fake_data data, const f_string_statics arguments, const bool as_shell, fake_make_data *data_make) f_gcc_attribute_visibility_internal;
#endif // _di_fake_make_operate_process_run_

/**
 * For a given make section operation, validate the given operation.
 *
 * This performs pre-operation validations.
 * Additional issues may occure when running operations that are not detected nor detectable by this.
 *
 * @param data
 *   The program data.
 * @param section_name
 *   The section name.
 * @param operation
 *   The operation being performed.
 * @param operation_name
 *   The operation name.
 * @param arguments
 *   The expanded arguments.
 * @param operation_if
 *   The if-condition status for the current operation.
 * @param data_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param section_stack
 *   The current operation stack.
 * @param status
 *   The return status.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_operate_validate_
  extern void fake_make_operate_validate(const fake_data data, const f_string_range section_name, const f_array_length operation, const f_string_static operation_name, const f_string_dynamics arguments, uint8_t *operation_if, fake_make_data *data_make, f_string_lengths *section_stack, f_status *status) f_gcc_attribute_visibility_internal;
#endif // _di_fake_make_operate_validate_

/**
 * Validate that the given define variable name is valid.
 *
 * A valid define variable name mst begin with an alpha-character or an underscore.
 * Every character after that may be alphanumeric or underscore.
 * All other characters, including Unicode characters, are invalid.
 *
 * @param name
 *   The variable name string to validate.
 *
 * @return
 *   F_true on valid.
 *   F_false on invalid.
 *   F_none if there is no string to validate (used = 0).
 */
#ifndef _di_fake_make_operate_validate_define_name_
  extern f_return_status fake_make_operate_validate_define_name(const f_string_static name) f_gcc_attribute_visibility_internal;
#endif // _di_fake_make_operate_validate_define_name_

/**
 * Get a path, relative to the project root.
 *
 * @param data
 *   The program data.
 * @param path
 *   The NULL terminated path to get the relative path of.
 * @param data_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 *   The relative path is stored in data_make.path_cache.
 *
 * @return
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_path_relative_
  extern f_return_status fake_make_path_relative(const fake_data data, const f_string_static path, fake_make_data *data_make) f_gcc_attribute_visibility_internal;
#endif // _di_fake_make_path_relative_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_make_h
