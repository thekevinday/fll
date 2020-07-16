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

// @todo safety checks that ensures operations on files only happen inside the project directory, represented by "top".
#ifndef _di_fake_make_setting_
  typedef struct {
    bool load_build;

    f_string_map_multis define;
    f_string_map_multis parameter;
  } fake_make_setting;

  #define fake_make_setting_initialize { \
    0, \
    f_string_map_multis_initialize, \
    f_string_map_multis_initialize, \
  }

  #define fake_macro_make_setting_delete_simple(setting) \
    f_macro_string_map_multis_delete_simple(setting.define) \
    f_macro_string_map_multis_delete_simple(setting.parameter)

  #define fake_make_setting_define     "define"
  #define fake_make_setting_load_build "load_build"
  #define fake_make_setting_parameter  "parameter"
  #define fake_make_setting_return     "return"

  #define fake_make_setting_define_length     6
  #define fake_make_setting_load_build_length 10
  #define fake_make_setting_parameter_length  9
  #define fake_make_setting_return_length     6

  #define fake_make_setting_total 3
#endif // _di_fake_make_setting_

// @todo "operate" should use a call stack, but do not allow recursive calls (check to see if named operation is already on the call stack).
#ifndef _di_fake_make_operation_
  #define fake_make_operation_archive  "archive"
  #define fake_make_operation_build    "build"
  #define fake_make_operation_clean    "clean"
  #define fake_make_operation_compile  "compile"
  #define fake_make_operation_create   "create"
  #define fake_make_operation_define   "define"
  #define fake_make_operation_delete   "delete"
  #define fake_make_operation_else     "else"
  #define fake_make_operation_fail     "fail"
  #define fake_make_operation_group    "group"
  #define fake_make_operation_if       "if"
  #define fake_make_operation_link     "link"
  #define fake_make_operation_mode     "mode"
  #define fake_make_operation_operate  "operate"
  #define fake_make_operation_owner    "owner"
  #define fake_make_operation_pop      "pop"
  #define fake_make_operation_print    "print"
  #define fake_make_operation_run      "run"
  #define fake_make_operation_shell    "shell"
  #define fake_make_operation_skeleton "skeleton"
  #define fake_make_operation_to       "to"
  #define fake_make_operation_top      "top"
  #define fake_make_operation_touch    "touch"

  #define fake_make_operation_archive_length  7
  #define fake_make_operation_build_length    5
  #define fake_make_operation_clean_length    5
  #define fake_make_operation_compile_length  7
  #define fake_make_operation_create_length   6
  #define fake_make_operation_define_length   6
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
    fake_make_operation_type_archive = 1,
    fake_make_operation_type_build,
    fake_make_operation_type_clean,
    fake_make_operation_type_compile,
    fake_make_operation_type_create,
    fake_make_operation_type_define,
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

  #define fake_make_operation_total 23

  #define fake_make_operation_argument_file      "file"
  #define fake_make_operation_argument_directory "directory"
  #define fake_make_operation_argument_error     "error"
  #define fake_make_operation_argument_ignore    "ignore"
  #define fake_make_operation_argument_point     "point"
  #define fake_make_operation_argument_recursive "recursive"
  #define fake_make_operation_argument_target    "target"
  #define fake_make_operation_argument_warn      "warn"

  #define fake_make_operation_argument_file_length      4
  #define fake_make_operation_argument_directory_length 9
  #define fake_make_operation_argument_error_length     5
  #define fake_make_operation_argument_ignore_length    6
  #define fake_make_operation_argument_point_length     5
  #define fake_make_operation_argument_recursive_length 9
  #define fake_make_operation_argument_target_length    6
  #define fake_make_operation_argument_warn_length      4

  enum {
    fake_make_operation_if_type_if = 1,
    fake_make_operation_if_type_else,
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

#ifndef _di_fake_make_data_
  typedef struct {
    fake_build_setting setting_build;
    fake_make_setting setting_make;

    fake_environment environment;
    fake_make_parameter parameter;

    f_fss_nameds fakefile;
    f_string_dynamic buffer;

    f_array_length main;

    uint8_t fail;
  } fake_make_data;

  #define fake_make_data_initialize { \
    fake_build_setting_initialize, \
    fake_make_setting_initialize, \
    fake_environment_initialize, \
    fake_make_parameter_initialize, \
    f_fss_nameds_initialize, \
    f_string_dynamic_initialize, \
    0, \
    0, \
  }

  #define fake_macro_make_data_delete_simple(data) \
    fake_macro_build_setting_delete_simple(data.setting_build) \
    fake_macro_make_setting_delete_simple(data.setting_make) \
    fake_macro_environment_delete_simple(data.environment) \
    fake_macro_make_parameter_delete_simple(data.parameter) \
    f_macro_fss_nameds_delete_simple(data.fakefile) \
    f_macro_string_dynamic_delete_simple(data.buffer)
#endif // _di_fake_make_data_

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
 * @return
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
 * @param quotedss
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
 * Perform the make operations within the given section.
 *
 * @param data
 *   The program data.
 * @param section_id
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
  void fake_make_operate_section(const fake_data data, const f_array_length section_id, fake_make_data *data_make, f_string_lengths *section_stack, f_status *status) f_gcc_attribute_visibility_internal;
#endif // _di_fake_make_operate_section_

/**
 * Perform a specific make operation within the given section.
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
 * @param status
 *   The return status.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_operate_perform_
  extern void fake_make_operate_perform(const fake_data data, const f_string_range section_name, const f_array_length operation, const f_string_static operation_name, const f_string_dynamics arguments, const uint8_t operation_if, fake_make_data *data_make, f_status *status) f_gcc_attribute_visibility_internal;
#endif // _di_fake_make_operate_perform_

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
#ifndef _di_fake_make_operate_perform_process_return_
  extern void fake_make_operate_perform_process_return(const fake_data data, const f_number_signed return_code, fake_make_data *data_make, f_status *status) f_gcc_attribute_visibility_internal;
#endif // _di_fake_make_operate_perform_process_return_

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
 * @param data_make
 *   All make related setting data, including data from the fakefile and optionally build settings file.
 * @param arguments
 *   The expanded arguments.
 * @param operation_if
 *   The if-condition status for the current operation.
 * @param process
 *   Set to TRUE if this is a process validation, FALSE if this is a pre-process validation.
 *   A pre-process validation does not check for content because content is not yet expanded.
 * @param status
 *   The return status.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_make_operate_validate_
  extern void fake_make_operate_validate(const fake_data data, const f_string_range section_name, const f_array_length operation, const f_string_static operation_name, const fake_make_data data_make, const f_string_dynamics arguments, const uint8_t operation_if, const bool process, f_status *status) f_gcc_attribute_visibility_internal;
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

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_make_h
