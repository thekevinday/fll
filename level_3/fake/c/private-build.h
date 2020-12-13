/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_build_h
#define _PRIVATE_build_h

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_setting_t_
  typedef struct {
    uint8_t build_language;

    uint8_t version_target;

    bool build_script;
    bool build_shared;
    bool build_static;

    bool path_standard;
    bool path_headers_preserve;

    bool search_exclusive;
    bool search_shared;
    bool search_static;

    f_string_dynamic_t build_compiler;
    f_string_dynamic_t build_indexer;
    f_string_dynamic_t path_headers;
    f_string_dynamic_t path_language;
    f_string_dynamic_t path_library_script;
    f_string_dynamic_t path_library_shared;
    f_string_dynamic_t path_library_static;
    f_string_dynamic_t path_program_script;
    f_string_dynamic_t path_program_shared;
    f_string_dynamic_t path_program_static;
    f_string_dynamic_t path_sources;
    f_string_dynamic_t process_post;
    f_string_dynamic_t process_pre;
    f_string_dynamic_t project_name;
    f_string_dynamic_t version_major;
    f_string_dynamic_t version_micro;
    f_string_dynamic_t version_minor;

    f_string_dynamics_t build_libraries;
    f_string_dynamics_t build_sources_headers;
    f_string_dynamics_t build_sources_library;
    f_string_dynamics_t build_sources_program;
    f_string_dynamics_t build_sources_setting;
    f_string_dynamics_t build_sources_script;
    f_string_dynamics_t defines_all;
    f_string_dynamics_t defines_shared;
    f_string_dynamics_t defines_static;
    f_string_dynamics_t environment;
    f_string_dynamics_t flags_all;
    f_string_dynamics_t flags_library;
    f_string_dynamics_t flags_program;
    f_string_dynamics_t flags_shared;
    f_string_dynamics_t flags_static;
    f_string_dynamics_t modes;
    f_string_dynamics_t modes_default;
  } fake_build_setting_t;

  #define fake_build_setting_t_initialize { \
    0, \
    0, \
    F_true, \
    F_true, \
    F_true, \
    F_true, \
    F_true, \
    F_true, \
    F_true, \
    F_true, \
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
    f_string_dynamics_t_initialize, \
    f_string_dynamics_t_initialize, \
    f_string_dynamics_t_initialize, \
    f_string_dynamics_t_initialize, \
    f_string_dynamics_t_initialize, \
    f_string_dynamics_t_initialize, \
    f_string_dynamics_t_initialize, \
    f_string_dynamics_t_initialize, \
    f_string_dynamics_t_initialize, \
    f_string_dynamics_t_initialize, \
    f_string_dynamics_t_initialize, \
    f_string_dynamics_t_initialize, \
    f_string_dynamics_t_initialize, \
    f_string_dynamics_t_initialize, \
    f_string_dynamics_t_initialize, \
    f_string_dynamics_t_initialize, \
    f_string_dynamics_t_initialize, \
  }

  #define fake_macro_build_setting_t_delete_simple(setting) \
    f_macro_string_dynamic_t_delete_simple(setting.build_compiler) \
    f_macro_string_dynamic_t_delete_simple(setting.build_indexer) \
    f_macro_string_dynamic_t_delete_simple(setting.path_headers) \
    f_macro_string_dynamic_t_delete_simple(setting.path_language) \
    f_macro_string_dynamic_t_delete_simple(setting.path_library_script) \
    f_macro_string_dynamic_t_delete_simple(setting.path_library_shared) \
    f_macro_string_dynamic_t_delete_simple(setting.path_library_static) \
    f_macro_string_dynamic_t_delete_simple(setting.path_program_script) \
    f_macro_string_dynamic_t_delete_simple(setting.path_program_shared) \
    f_macro_string_dynamic_t_delete_simple(setting.path_program_static) \
    f_macro_string_dynamic_t_delete_simple(setting.path_sources) \
    f_macro_string_dynamic_t_delete_simple(setting.process_post) \
    f_macro_string_dynamic_t_delete_simple(setting.process_pre) \
    f_macro_string_dynamic_t_delete_simple(setting.project_name) \
    f_macro_string_dynamic_t_delete_simple(setting.version_major) \
    f_macro_string_dynamic_t_delete_simple(setting.version_micro) \
    f_macro_string_dynamic_t_delete_simple(setting.version_minor) \
    f_macro_string_dynamics_t_delete_simple(setting.build_libraries) \
    f_macro_string_dynamics_t_delete_simple(setting.build_sources_headers) \
    f_macro_string_dynamics_t_delete_simple(setting.build_sources_library) \
    f_macro_string_dynamics_t_delete_simple(setting.build_sources_program) \
    f_macro_string_dynamics_t_delete_simple(setting.build_sources_setting) \
    f_macro_string_dynamics_t_delete_simple(setting.build_sources_script) \
    f_macro_string_dynamics_t_delete_simple(setting.defines_all) \
    f_macro_string_dynamics_t_delete_simple(setting.defines_shared) \
    f_macro_string_dynamics_t_delete_simple(setting.defines_static) \
    f_macro_string_dynamics_t_delete_simple(setting.environment) \
    f_macro_string_dynamics_t_delete_simple(setting.flags_all) \
    f_macro_string_dynamics_t_delete_simple(setting.flags_library) \
    f_macro_string_dynamics_t_delete_simple(setting.flags_program) \
    f_macro_string_dynamics_t_delete_simple(setting.flags_shared) \
    f_macro_string_dynamics_t_delete_simple(setting.flags_static) \
    f_macro_string_dynamics_t_delete_simple(setting.modes) \
    f_macro_string_dynamics_t_delete_simple(setting.modes_default)

  #define fake_build_setting_name_build_compiler         "build_compiler"
  #define fake_build_setting_name_build_language         "build_language"
  #define fake_build_setting_name_build_libraries        "build_libraries"
  #define fake_build_setting_name_build_indexer          "build_indexer"
  #define fake_build_setting_name_build_script           "build_script"
  #define fake_build_setting_name_build_shared           "build_shared"
  #define fake_build_setting_name_build_sources_headers  "build_sources_headers"
  #define fake_build_setting_name_build_sources_library  "build_sources_library"
  #define fake_build_setting_name_build_sources_program  "build_sources_program"
  #define fake_build_setting_name_build_sources_settings "build_sources_setting"
  #define fake_build_setting_name_build_sources_script   "build_sources_script"
  #define fake_build_setting_name_build_static           "build_static"
  #define fake_build_setting_name_defines_all            "defines_all"
  #define fake_build_setting_name_defines_shared         "defines_shared"
  #define fake_build_setting_name_defines_static         "defines_static"
  #define fake_build_setting_name_environment            "environment"
  #define fake_build_setting_name_flags_all              "flags_all"
  #define fake_build_setting_name_flags_library          "flags_library"
  #define fake_build_setting_name_flags_program          "flags_program"
  #define fake_build_setting_name_flags_shared           "flags_shared"
  #define fake_build_setting_name_flags_static           "flags_static"
  #define fake_build_setting_name_modes                  "modes"
  #define fake_build_setting_name_modes_default          "modes_default"
  #define fake_build_setting_name_path_headers           "path_headers"
  #define fake_build_setting_name_path_headers_preserve  "path_headers_preserve"
  #define fake_build_setting_name_path_language          "path_language"
  #define fake_build_setting_name_path_library_script    "path_library_script"
  #define fake_build_setting_name_path_library_shared    "path_library_shared"
  #define fake_build_setting_name_path_library_static    "path_library_static"
  #define fake_build_setting_name_path_program_script    "path_program_script"
  #define fake_build_setting_name_path_program_shared    "path_program_shared"
  #define fake_build_setting_name_path_program_static    "path_program_static"
  #define fake_build_setting_name_path_sources           "path_sources"
  #define fake_build_setting_name_path_standard          "path_standard"
  #define fake_build_setting_name_process_post           "process_post"
  #define fake_build_setting_name_process_pre            "process_pre"
  #define fake_build_setting_name_project_name           "project_name"
  #define fake_build_setting_name_search_exclusive       "search_exclusive"
  #define fake_build_setting_name_search_shared          "search_shared"
  #define fake_build_setting_name_search_static          "search_static"
  #define fake_build_setting_name_version_major          "version_major"
  #define fake_build_setting_name_version_micro          "version_micro"
  #define fake_build_setting_name_version_minor          "version_minor"
  #define fake_build_setting_name_version_target         "version_target"

  #define fake_build_setting_name_build_compiler_length         14
  #define fake_build_setting_name_build_language_length         14
  #define fake_build_setting_name_build_libraries_length        15
  #define fake_build_setting_name_build_indexer_length          13
  #define fake_build_setting_name_build_script_length           12
  #define fake_build_setting_name_build_shared_length           12
  #define fake_build_setting_name_build_sources_headers_length  21
  #define fake_build_setting_name_build_sources_library_length  21
  #define fake_build_setting_name_build_sources_program_length  21
  #define fake_build_setting_name_build_sources_settings_length 22
  #define fake_build_setting_name_build_sources_script_length   20
  #define fake_build_setting_name_build_static_length           12
  #define fake_build_setting_name_environment_length            11
  #define fake_build_setting_name_defines_all_length            11
  #define fake_build_setting_name_defines_shared_length         14
  #define fake_build_setting_name_defines_static_length         14
  #define fake_build_setting_name_flags_all_length              9
  #define fake_build_setting_name_flags_library_length          13
  #define fake_build_setting_name_flags_program_length          13
  #define fake_build_setting_name_flags_shared_length           12
  #define fake_build_setting_name_flags_static_length           12
  #define fake_build_setting_name_modes_length                  5
  #define fake_build_setting_name_modes_default_length          13
  #define fake_build_setting_name_path_headers_length           12
  #define fake_build_setting_name_path_headers_preserve_length  21
  #define fake_build_setting_name_path_language_length          13
  #define fake_build_setting_name_path_library_script_length    19
  #define fake_build_setting_name_path_library_shared_length    19
  #define fake_build_setting_name_path_library_static_length    19
  #define fake_build_setting_name_path_program_script_length    19
  #define fake_build_setting_name_path_program_shared_length    19
  #define fake_build_setting_name_path_program_static_length    19
  #define fake_build_setting_name_path_sources_length           12
  #define fake_build_setting_name_path_standard_length          13
  #define fake_build_setting_name_process_post_length           12
  #define fake_build_setting_name_process_pre_length            11
  #define fake_build_setting_name_project_name_length           12
  #define fake_build_setting_name_search_exclusive_length       16
  #define fake_build_setting_name_search_shared_length          13
  #define fake_build_setting_name_search_static_length          13
  #define fake_build_setting_name_version_major_length          13
  #define fake_build_setting_name_version_micro_length          13
  #define fake_build_setting_name_version_minor_length          13
  #define fake_build_setting_name_version_target_length         14

  #define fake_build_setting_total 44

  #define fake_build_setting_default_version "0"

  #define fake_build_setting_default_version_length 1
#endif // _di_fake_build_setting_t_

#ifndef _di_fake_build_stage_t_
  typedef struct {
    f_string_dynamic_t file_libraries_script;
    f_string_dynamic_t file_libraries_shared;
    f_string_dynamic_t file_libraries_static;
    f_string_dynamic_t file_objects_static;
    f_string_dynamic_t file_process_post;
    f_string_dynamic_t file_process_pre;
    f_string_dynamic_t file_programs_script;
    f_string_dynamic_t file_programs_shared;
    f_string_dynamic_t file_programs_static;
    f_string_dynamic_t file_skeleton;
    f_string_dynamic_t file_sources_headers;
    f_string_dynamic_t file_sources_script;
    f_string_dynamic_t file_sources_settings;
  } fake_build_stage_t;

  #define fake_build_stage_t_initialize { \
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
  }

  #define fake_build_stage_total 13

  #define fake_macro_build_stage_t_delete_simple(stage) \
    f_macro_string_dynamic_t_delete_simple(stage.file_libraries_script) \
    f_macro_string_dynamic_t_delete_simple(stage.file_libraries_shared) \
    f_macro_string_dynamic_t_delete_simple(stage.file_libraries_static) \
    f_macro_string_dynamic_t_delete_simple(stage.file_objects_static) \
    f_macro_string_dynamic_t_delete_simple(stage.file_process_post) \
    f_macro_string_dynamic_t_delete_simple(stage.file_process_pre) \
    f_macro_string_dynamic_t_delete_simple(stage.file_programs_script) \
    f_macro_string_dynamic_t_delete_simple(stage.file_programs_shared) \
    f_macro_string_dynamic_t_delete_simple(stage.file_programs_static) \
    f_macro_string_dynamic_t_delete_simple(stage.file_skeleton) \
    f_macro_string_dynamic_t_delete_simple(stage.file_sources_headers) \
    f_macro_string_dynamic_t_delete_simple(stage.file_sources_script) \
    f_macro_string_dynamic_t_delete_simple(stage.file_sources_settings)

  #define fake_build_stage_built            ".built"
  #define fake_build_stage_libraries_script "libraries_script"
  #define fake_build_stage_libraries_shared "libraries_shared"
  #define fake_build_stage_libraries_static "libraries_static"
  #define fake_build_stage_objects_static   "objects_static"
  #define fake_build_stage_process_post     "process_post"
  #define fake_build_stage_process_pre      "process_pre"
  #define fake_build_stage_programs_script  "programs_script"
  #define fake_build_stage_programs_shared  "programs_shared"
  #define fake_build_stage_programs_static  "programs_static"
  #define fake_build_stage_separate         "-"
  #define fake_build_stage_skeleton         "skeleton"
  #define fake_build_stage_sources_headers  "sources_headers"
  #define fake_build_stage_sources_script   "sources_script"
  #define fake_build_stage_sources_settings "sources_settings"

  #define fake_build_stage_built_length            6
  #define fake_build_stage_libraries_script_length 16
  #define fake_build_stage_libraries_shared_length 16
  #define fake_build_stage_libraries_static_length 16
  #define fake_build_stage_objects_static_length   14
  #define fake_build_stage_process_post_length     12
  #define fake_build_stage_process_pre_length      11
  #define fake_build_stage_programs_script_length  15
  #define fake_build_stage_programs_shared_length  15
  #define fake_build_stage_programs_static_length  15
  #define fake_build_stage_separate_length         1
  #define fake_build_stage_skeleton_length         8
  #define fake_build_stage_sources_headers_length  15
  #define fake_build_stage_sources_script_length   14
  #define fake_build_stage_sources_settings_length 16
#endif // _di_fake_build_stage_t_

#ifndef _di_fake_build_data_t_
  typedef struct {
    fake_build_setting_t setting;
    fake_environment_t environment;
  } fake_build_data_t;

  #define fake_build_data_t_initialize { \
    fake_build_setting_t_initialize, \
    fake_environment_t_initialize, \
  }

  #define fake_macro_build_data_delete_simple(build) \
    fake_macro_build_setting_t_delete_simple(build.setting) \
    fake_macro_environment_t_delete_simple(build.environment)
#endif // _di_fake_build_data_t_

#ifndef _di_fake_build_parameter_
  #define fake_build_parameter_library_include            "-I"
  #define fake_build_parameter_library_link_file          "-l"
  #define fake_build_parameter_library_link_path          "-L"
  #define fake_build_parameter_library_name_prefix        "lib"
  #define fake_build_parameter_library_name_suffix_shared ".so"
  #define fake_build_parameter_library_name_suffix_static ".a"
  #define fake_build_parameter_library_output             "-o"
  #define fake_build_parameter_library_separator          "."
  #define fake_build_parameter_library_shared             "-shared"
  #define fake_build_parameter_library_static             "-static"
  #define fake_build_parameter_library_shared_prefix      "-Wl,-soname,"

  #define fake_build_parameter_library_include_length            2
  #define fake_build_parameter_library_link_file_length          2
  #define fake_build_parameter_library_link_path_length          2
  #define fake_build_parameter_library_name_prefix_length        3
  #define fake_build_parameter_library_name_suffix_shared_length 3
  #define fake_build_parameter_library_name_suffix_static_length 2
  #define fake_build_parameter_library_output_length             2
  #define fake_build_parameter_library_separator_length          1
  #define fake_build_parameter_library_shared_length             7
  #define fake_build_parameter_library_static_length             7
  #define fake_build_parameter_library_shared_prefix_length      12

  #define fake_build_parameter_object_compile     "-c"
  #define fake_build_parameter_object_name_suffix ".o"
  #define fake_build_parameter_object_output      "-o"
  #define fake_build_parameter_object_static      "-static"

  #define fake_build_parameter_object_compile_length     2
  #define fake_build_parameter_object_name_suffix_length 2
  #define fake_build_parameter_object_output_length      2
  #define fake_build_parameter_object_static_length      7

  #define fake_build_parameter_object_link_arguments "rcs"

  #define fake_build_parameter_object_link_arguments_length 3
#endif // _di_fake_build_parameter_

/**
 * Add the standard arguments for building a library/program.
 *
 * @param data
 *   The program data.
 * @param data_build
 *   The build data.
 * @param is_shared
 *   Set to TRUE to designate that this is adding for a shared library/program.
 *   Set to FALSE to designate that this is adding for a static library/program.
 * @param is_library
 *   Set to TRUE to designate that this is adding for a library.
 *   Set to FALSE to designate that this is adding for a program.
 * @param arguments
 *   The arguments array to append to.
 * @param status
 *   The return status.
 *
 * @see fll_execute_arguments_add()
 */
#ifndef _di_fake_build_arguments_standard_add_
  extern void fake_build_arguments_standard_add(const fake_data_t data, const fake_build_data_t data_build, const bool is_shared, const bool is_library, f_string_dynamics_t *arguments, f_status_t *status) f_gcc_attribute_visibility_internal;
#endif // _di_fake_build_arguments_standard_add_

/**
 * Copy over the data setting files.
 *
 * @param data
 *   The program data.
 * @param mode
 *   The modes for each file type.
 * @param label
 *   A label used when printing the now copying message.
 * @param source
 *   The specific build path to copy from.
 * @param destination
 *   The specific build path to copy to.
 * @param files
 *   The files to copy from source to destination.
 * @param file_stage
 *   The specific stage file path.
 * @param perserve
 *   When a positive number, this represents the amount of characters at the front of each file to ignore.
 *   Everything after that is preserved, and the directory is created if necessary.
 *
 *   This is always treated as 0 for any file that is a directory type.
 *   Set to 0 to disable.
 *
 *   Example: 'sources/c/level_0/fss.h' with a preseve of 10, would result in the path of 'level_0/fss.h' being preserved.
 *            Whereas a preserve of 0 would result in a path of 'fss.h' being used (the 'level_0/' directory is not preserved).
 * @param status
 *   The return status.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_build_copy_
  extern void fake_build_copy(const fake_data_t data, const f_mode_t mode, const f_string_t label, const f_string_static_t source, const f_string_static_t destination, const f_string_statics_t files, const f_string_static_t file_stage, const f_string_length_t preserve, f_status_t *status) f_gcc_attribute_visibility_internal;
#endif // _di_fake_build_copy_

/**
 * Create all of the base directories inside the build directory.
 *
 * @param data
 *   The program data.
 * @param data_build
 *   The build data.
 * @param mode
 *   The directory mode.
 * @param file_stage
 *   The specific stage file path.
 * @param status
 *   The return status.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_build_skeleton_
  extern void fake_build_skeleton(const fake_data_t data, const fake_build_data_t data_build, const mode_t mode, const f_string_static_t file_stage, f_status_t *status) f_gcc_attribute_visibility_internal;
#endif // _di_fake_build_skeleton_

/**
 * Execute the Pre-Process or Post-pocess build script.
 *
 * @param data
 *   The program data.
 * @param data_build
 *   All build related data.
 * @param process_script
 *   The setting_data file name fo the appropriate process script.
 *   This is expected to be either setting.process_pre or setting.process_post.
 * @param file_stage
 *   The specific stage file path.
 * @param status
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @return
 *   The return code of the execution process.
 *   This generally is only needed when F_child is returned, where this holds the return status of the child process.
 */
#ifndef _di_fake_build_execute_process_script_
  extern int fake_build_execute_process_script(const fake_data_t data, const fake_build_data_t data_build, const f_string_static_t process_script, const f_string_static_t file_stage, f_status_t *status) f_gcc_attribute_visibility_internal;
#endif // _di_fake_build_execute_process_script_

/**
 * Get the file name without the extension and without the path parts.
 *
 * @param data
 *   The program data.
 * @param path
 *   The file path to get the file name from.
 * @param name
 *   The processed filename.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_build_get_file_name_without_extension_
  extern f_return_status fake_build_get_file_name_without_extension(const fake_data_t data, const f_string_static_t path, f_string_dynamic_t *name);
#endif // _di_fake_build_get_file_name_without_extension_

/**
 * Build the script libraries.
 *
 * @param data
 *   The program data.
 * @param data_build
 *   All build related data.
 * @param mode
 *   The file mode.
 * @param file_stage
 *   The specific stage file path.
 * @param status
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @return
 *   The return code of the execution process.
 *   This generally is only needed when F_child is returned, where this holds the return status of the child process.
 */
#ifndef _di_fake_build_libraries_script_
  extern int fake_build_libraries_script(const fake_data_t data, const fake_build_data_t data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t *status) f_gcc_attribute_visibility_internal;
#endif // _di_fake_build_libraries_script_

/**
 * Build the shared libraries.
 *
 * @param data
 *   The program data.
 * @param data_build
 *   All build related data.
 * @param mode
 *   The file mode.
 * @param file_stage
 *   The specific stage file path.
 * @param status
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @return
 *   The return code of the execution process.
 *   This generally is only needed when F_child is returned, where this holds the return status of the child process.
 */
#ifndef _di_fake_build_library_shared_
  extern int fake_build_library_shared(const fake_data_t data, const fake_build_data_t data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t *status) f_gcc_attribute_visibility_internal;
#endif // _di_fake_build_library_shared_

/**
 * Build the static libraries.
 *
 * @param data
 *   The program data.
 * @param data_build
 *   All build related data.
 * @param mode
 *   The file mode.
 * @param file_stage
 *   The specific stage file path.
 * @param status
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @return
 *   The return code of the execution process.
 *   This generally is only needed when F_child is returned, where this holds the return status of the child process.
 */
#ifndef _di_fake_build_library_static_
  extern int fake_build_library_static(const fake_data_t data, const fake_build_data_t data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t *status) f_gcc_attribute_visibility_internal;
#endif // _di_fake_build_library_static_

/**
 * Find the build setting file, load it, validate it, and process it.
 *
 * @param data
 *   The program data.
 * @param setting_file
 *   The name of the settings file to use.
 *   If setting_file.used is 0, then the default or program parameter supplied file is used.
 * @param setting
 *   All build related setting data from the build setting file are loaded into this.
 *   These setting will have any specified mode property applied.
 * @param status
 *   The return status.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_build_load_setting_
  extern void fake_build_load_setting(const fake_data_t data, const f_string_static_t setting_file, fake_build_setting_t *setting, f_status_t *status) f_gcc_attribute_visibility_internal;
#endif // _di_fake_build_load_setting_

/**
 * Assign build setting defaults.
 *
 * @param data
 *   The program data.
 * @param path_file
 *   The path to the buffer.
 * @param buffer
 *   The loaded file data.
 * @param setting
 *   All build related setting data from the build setting file are loaded into this.
 *   These setting will have any specified mode property applied.
 * @param status
 *   The return status.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_build_load_setting_defaults_
  extern void fake_build_load_setting_defaults(const fake_data_t data, fake_build_setting_t *setting, f_status_t *status) f_gcc_attribute_visibility_internal;
#endif // _di_fake_build_load_setting_defaults_

/**
 * Load and process the setting buffer.
 *
 * @param data
 *   The program data.
 * @param path_file
 *   The path to the buffer.
 * @param buffer
 *   The loaded file data.
 * @param objects
 *   The object mapping.
 * @param contents
 *   The content mapping.
 * @param setting
 *   All build related setting data from the build setting file are loaded into this.
 *   These setting will have any specified mode property applied.
 * @param status
 *   The return status.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_build_load_setting_process_
  extern void fake_build_load_setting_process(const fake_data_t data, const f_string_t path_file, const f_string_static_t buffer, const f_fss_objects_t objects, const f_fss_contents_t contents, fake_build_setting_t *setting, f_status_t *status) f_gcc_attribute_visibility_internal;
#endif // _di_fake_build_load_setting_process_

/**
 * Load the environment used when executing commands.
 *
 * @param data
 *   The program data.
 * @param data_build
 *   All build related data.
 * @param environment
 *   The environment data.
 * @param status
 *   The return status.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_build_load_environment_
  extern void fake_build_load_environment(const fake_data_t data, const fake_build_data_t data_build, fake_environment_t *environment, f_status_t *status) f_gcc_attribute_visibility_internal;
#endif // _di_fake_build_load_environment_

/**
 * Load the stage file paths.
 *
 * @param data
 *   The program data.
 * @param settings_file
 *   The path to the settings file.
 * @param stage
 *   All stage file paths.
 * @param status
 *   The return status.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_build_load_stage_
  extern void fake_build_load_stage(const fake_data_t data, const f_string_static_t settings_file, fake_build_stage_t *stage, f_status_t *status) f_gcc_attribute_visibility_internal;
#endif // _di_fake_build_load_stage_

/**
 * Build the static objects.
 *
 * @param data
 *   The program data.
 * @param data_build
 *   All build related data.
 * @param mode
 *   The file mode.
 * @param file_stage
 *   The specific stage file path.
 * @param status
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @return
 *   The return code of the execution process.
 *   This generally is only needed when F_child is returned, where this holds the return status of the child process.
 */
#ifndef _di_fake_build_objects_static_
  extern int fake_build_objects_static(const fake_data_t data, const fake_build_data_t data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t *status) f_gcc_attribute_visibility_internal;
#endif // _di_fake_build_objects_static_

/**
 * Execute the build operation.
 *
 * @param setting_file
 *   The name of the settings file to use.
 *   If setting_file.used is 0, then the default or program parameter supplied file is used.
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_build_operate_
  extern f_return_status fake_build_operate(const f_string_static_t setting_file, fake_data_t *data) f_gcc_attribute_visibility_internal;
#endif // _di_fake_build_operate_

/**
 * Build the script programs.
 *
 * @param data
 *   The program data.
 * @param data_build
 *   All build related data.
 * @param mode
 *   The file mode.
 * @param file_stage
 *   The specific stage file path.
 * @param status
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @return
 *   The return code of the execution process.
 *   This generally is only needed when F_child is returned, where this holds the return status of the child process.
 */
#ifndef _di_fake_build_programs_script_
  extern int fake_build_programs_script(const fake_data_t data, const fake_build_data_t data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t *status) f_gcc_attribute_visibility_internal;
#endif // _di_fake_build_programs_script_

/**
 * Build the shared programs.
 *
 * @param data
 *   The program data.
 * @param data_build
 *   All build related data.
 * @param mode
 *   The file mode.
 * @param file_stage
 *   The specific stage file path.
 * @param status
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @return
 *   The return code of the execution process.
 *   This generally is only needed when F_child is returned, where this holds the return status of the child process.
 */
#ifndef _di_fake_build_program_shared_
  extern int fake_build_program_shared(const fake_data_t data, const fake_build_data_t data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t *status) f_gcc_attribute_visibility_internal;
#endif // _di_fake_build_program_shared_

/**
 * Build the static programs.
 *
 * @param data
 *   The program data.
 * @param data_build
 *   All build related data.
 * @param mode
 *   The file mode.
 * @param file_stage
 *   The specific stage file path.
 * @param status
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @return
 *   The return code of the execution process.
 *   This generally is only needed when F_child is returned, where this holds the return status of the child process.
 */
#ifndef _di_fake_build_program_static_
  extern int fake_build_program_static(const fake_data_t data, const fake_build_data_t data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t *status) f_gcc_attribute_visibility_internal;
#endif // _di_fake_build_program_static_

/**
 * Touch the given build stage file, but only if there are no current errors in status.
 *
 * @param data
 *   The program data.
 * @param file
 *   The file path to touch.
 * @param status
 *   The return status.
 *
 * @see f_file_touch()
 */
#ifndef _di_fake_build_touch_
  extern void fake_build_touch(const fake_data_t data, const f_string_dynamic_t file, f_status_t *status) f_gcc_attribute_visibility_internal;
#endif // _di_fake_build_touch_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_build_h
