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

#ifndef _di_fake_build_settings_
  typedef struct {
    f_string_dynamic build_compiler;
    f_string_dynamic build_libraries;
    f_string_dynamic build_linker;
    f_string_dynamic build_shared;
    f_string_dynamic build_sources_headers;
    f_string_dynamic build_sources_library;
    f_string_dynamic build_sources_program;
    f_string_dynamic build_sources_setting;
    f_string_dynamic build_sources_shell;
    f_string_dynamic build_static;
    f_string_dynamic defines_all;
    f_string_dynamic defines_shared;
    f_string_dynamic defines_static;
    f_string_dynamic flags_all;
    f_string_dynamic flags_library;
    f_string_dynamic flags_program;
    f_string_dynamic flags_shared;
    f_string_dynamic flags_static;
    f_string_dynamic path_language;
    f_string_dynamic path_headers;
    f_string_dynamic path_library_shared;
    f_string_dynamic path_library_static;
    f_string_dynamic path_program_shared;
    f_string_dynamic path_program_static;
    f_string_dynamic process_post;
    f_string_dynamic process_pre;
    f_string_dynamic project_level;
    f_string_dynamic project_name;
    f_string_dynamic version_major;
    f_string_dynamic version_micro;
    f_string_dynamic version_minor;
  } fake_build_settings;

  #define fake_build_settings_initialize { f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize }

  #define fake_macro_settings_build_clear(settings) \
    f_macro_string_dynamic_clear(settings.build_compiler) \
    f_macro_string_dynamic_clear(settings.build_libraries) \
    f_macro_string_dynamic_clear(settings.build_linker) \
    f_macro_string_dynamic_clear(settings.build_shared) \
    f_macro_string_dynamic_clear(settings.build_sources_headers) \
    f_macro_string_dynamic_clear(settings.build_sources_library) \
    f_macro_string_dynamic_clear(settings.build_sources_program) \
    f_macro_string_dynamic_clear(settings.build_sources_setting) \
    f_macro_string_dynamic_clear(settings.build_sources_shell) \
    f_macro_string_dynamic_clear(settings.build_static) \
    f_macro_string_dynamic_clear(settings.defines_all) \
    f_macro_string_dynamic_clear(settings.defines_shared) \
    f_macro_string_dynamic_clear(settings.defines_static) \
    f_macro_string_dynamic_clear(settings.flags_all) \
    f_macro_string_dynamic_clear(settings.flags_library) \
    f_macro_string_dynamic_clear(settings.flags_program) \
    f_macro_string_dynamic_clear(settings.flags_shared) \
    f_macro_string_dynamic_clear(settings.flags_static) \
    f_macro_string_dynamic_clear(settings.path_language) \
    f_macro_string_dynamic_clear(settings.path_headers) \
    f_macro_string_dynamic_clear(settings.path_libary_shared) \
    f_macro_string_dynamic_clear(settings.path_library_static) \
    f_macro_string_dynamic_clear(settings.path_program_shared) \
    f_macro_string_dynamic_clear(settings.path_program_static) \
    f_macro_string_dynamic_clear(settings.process_post) \
    f_macro_string_dynamic_clear(settings.process_pre) \
    f_macro_string_dynamic_clear(settings.project_level) \
    f_macro_string_dynamic_clear(settings.project_name) \
    f_macro_string_dynamic_clear(settings.version_major) \
    f_macro_string_dynamic_clear(settings.version_micro) \
    f_macro_string_dynamic_clear(settings.version_minor)

  #define fake_macro_build_settings_delete(status, settings) \
    f_macro_string_dynamic_delete(status, settings.build_compiler) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings.build_libraries) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings.build_linker) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings.build_shared) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings.build_sources_headers) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings.build_sources_library) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings.build_sources_program) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings.build_sources_setting) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings.build_sources_shell) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings.build_static) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings.defines_all) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings.defines_shared) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings.defines_static) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings.flags_all) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings.flags_library) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings.flags_program) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings.flags_shared) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings.flags_static) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings.path_language) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings.path_headers) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings.path_library_shared) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings.path_library_static) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings.path_library_shared) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings.path_library_static) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings.process_post) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings.process_pre) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings.project_level) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings.project_name) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings.version_major) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings.version_micro) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings.version_minor)

  #define fake_macro_build_settings_destroy(status, settings, length) \
    f_macro_string_dynamic_delete(status, settings.build_compiler) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings.build_libraries) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings.build_linker) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings.build_shared) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings.build_sources_headers) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings.build_sources_library) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings.build_sources_program) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings.build_sources_setting) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings.build_sources_shell) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings.build_static) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings.defines_all) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings.defines_shared) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings.defines_static) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings.flags_all) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings.flags_library) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings.flags_program) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings.flags_shared) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings.flags_static) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings.path_language) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings.path_headers) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings.path_library_shared) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings.path_library_static) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings.path_program_shared) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings.path_program_static) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings.process_post) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings.process_pre) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings.project_level) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings.project_name) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings.version_major) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings.version_micro) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings.version_minor)

  #define fake_macro_build_settings_delete_simple(settings) \
    f_macro_string_dynamic_delete_simple(settings.build_compiler) \
    f_macro_string_dynamic_delete_simple(settings.build_libraries) \
    f_macro_string_dynamic_delete_simple(settings.build_linker) \
    f_macro_string_dynamic_delete_simple(settings.build_shared) \
    f_macro_string_dynamic_delete_simple(settings.build_sources_headers) \
    f_macro_string_dynamic_delete_simple(settings.build_sources_library) \
    f_macro_string_dynamic_delete_simple(settings.build_sources_program) \
    f_macro_string_dynamic_delete_simple(settings.build_sources_setting) \
    f_macro_string_dynamic_delete_simple(settings.build_sources_shell) \
    f_macro_string_dynamic_delete_simple(settings.build_static) \
    f_macro_string_dynamic_delete_simple(settings.defines_all) \
    f_macro_string_dynamic_delete_simple(settings.defines_shared) \
    f_macro_string_dynamic_delete_simple(settings.defines_static) \
    f_macro_string_dynamic_delete_simple(settings.flags_all) \
    f_macro_string_dynamic_delete_simple(settings.flags_library) \
    f_macro_string_dynamic_delete_simple(settings.flags_program) \
    f_macro_string_dynamic_delete_simple(settings.flags_shared) \
    f_macro_string_dynamic_delete_simple(settings.flags_static) \
    f_macro_string_dynamic_delete_simple(settings.path_language) \
    f_macro_string_dynamic_delete_simple(settings.path_headers) \
    f_macro_string_dynamic_delete_simple(settings.path_library_shared) \
    f_macro_string_dynamic_delete_simple(settings.path_library_static) \
    f_macro_string_dynamic_delete_simple(settings.path_program_shared) \
    f_macro_string_dynamic_delete_simple(settings.path_program_static) \
    f_macro_string_dynamic_delete_simple(settings.process_post) \
    f_macro_string_dynamic_delete_simple(settings.process_pre) \
    f_macro_string_dynamic_delete_simple(settings.project_level) \
    f_macro_string_dynamic_delete_simple(settings.project_name) \
    f_macro_string_dynamic_delete_simple(settings.version_major) \
    f_macro_string_dynamic_delete_simple(settings.version_micro) \
    f_macro_string_dynamic_delete_simple(settings.version_minor)

  #define fake_macro_build_settings_destroy_simple(settings, length) \
    f_macro_string_dynamic_destroy_simple(settings.build_compiler) \
    f_macro_string_dynamic_destroy_simple(settings.build_libraries) \
    f_macro_string_dynamic_destroy_simple(settings.build_linker) \
    f_macro_string_dynamic_destroy_simple(settings.build_shared) \
    f_macro_string_dynamic_destroy_simple(settings.build_sources_headers) \
    f_macro_string_dynamic_destroy_simple(settings.build_sources_library) \
    f_macro_string_dynamic_destroy_simple(settings.build_sources_program) \
    f_macro_string_dynamic_destroy_simple(settings.build_sources_setting) \
    f_macro_string_dynamic_destroy_simple(settings.build_sources_shell) \
    f_macro_string_dynamic_destroy_simple(settings.build_static) \
    f_macro_string_dynamic_destroy_simple(settings.defines_all) \
    f_macro_string_dynamic_destroy_simple(settings.defines_shared) \
    f_macro_string_dynamic_destroy_simple(settings.defines_static) \
    f_macro_string_dynamic_destroy_simple(settings.flags_all) \
    f_macro_string_dynamic_destroy_simple(settings.flags_library) \
    f_macro_string_dynamic_destroy_simple(settings.flags_program) \
    f_macro_string_dynamic_destroy_simple(settings.flags_shared) \
    f_macro_string_dynamic_destroy_simple(settings.flags_static) \
    f_macro_string_dynamic_destroy_simple(settings.path_language) \
    f_macro_string_dynamic_destroy_simple(settings.path_headers) \
    f_macro_string_dynamic_destroy_simple(settings.path_library_shared) \
    f_macro_string_dynamic_destroy_simple(settings.path_library_static) \
    f_macro_string_dynamic_destroy_simple(settings.path_program_shared) \
    f_macro_string_dynamic_destroy_simple(settings.path_program_static) \
    f_macro_string_dynamic_destroy_simple(settings.process_post) \
    f_macro_string_dynamic_destroy_simple(settings.process_pre) \
    f_macro_string_dynamic_destroy_simple(settings.project_level) \
    f_macro_string_dynamic_destroy_simple(settings.project_name) \
    f_macro_string_dynamic_destroy_simple(settings.version_major) \
    f_macro_string_dynamic_destroy_simple(settings.version_micro) \
    f_macro_string_dynamic_destroy_simple(settings.version_minor)

  #define fake_build_settings_name_build_compiler         "build_compiler"
  #define fake_build_settings_name_build_libraries        "build_libraries"
  #define fake_build_settings_name_build_linker           "build_linker"
  #define fake_build_settings_name_build_shared           "build_shared"
  #define fake_build_settings_name_build_sources_headers  "build_sources_headers"
  #define fake_build_settings_name_build_sources_library  "build_sources_library"
  #define fake_build_settings_name_build_sources_program  "build_sources_program"
  #define fake_build_settings_name_build_sources_settings "build_sources_setting"
  #define fake_build_settings_name_build_sources_shell    "build_sources_shell"
  #define fake_build_settings_name_build_static           "build_static"
  #define fake_build_settings_name_defines_all            "defines_all"
  #define fake_build_settings_name_defines_shared         "defines_shared"
  #define fake_build_settings_name_defines_static         "defines_static"
  #define fake_build_settings_name_flags_all              "flags_all"
  #define fake_build_settings_name_flags_library          "flags_library"
  #define fake_build_settings_name_flags_program          "flags_program"
  #define fake_build_settings_name_flags_shared           "flags_shared"
  #define fake_build_settings_name_flags_static           "flags_static"
  #define fake_build_settings_name_path_language          "path_language"
  #define fake_build_settings_name_path_headers           "path_headers"
  #define fake_build_settings_name_path_library_shared    "path_library_shared"
  #define fake_build_settings_name_path_library_static    "path_library_static"
  #define fake_build_settings_name_path_program_shared    "path_program_shared"
  #define fake_build_settings_name_path_program_static    "path_program_static"
  #define fake_build_settings_name_process_post           "process_post"
  #define fake_build_settings_name_process_pre            "process_pre"
  #define fake_build_settings_name_project_level          "project_level"
  #define fake_build_settings_name_project_name           "project_name"
  #define fake_build_settings_name_version_major          "version_major"
  #define fake_build_settings_name_version_micro          "version_micro"
  #define fake_build_settings_name_version_minor          "version_minor"

  #define fake_build_settings_name_build_compiler_length         14
  #define fake_build_settings_name_build_libraries_length        15
  #define fake_build_settings_name_build_linker_length           12
  #define fake_build_settings_name_build_shared_length           12
  #define fake_build_settings_name_build_sources_headers_length  21
  #define fake_build_settings_name_build_sources_library_length  21
  #define fake_build_settings_name_build_sources_program_length  21
  #define fake_build_settings_name_build_sources_settings_length 22
  #define fake_build_settings_name_build_sources_shell_length    19
  #define fake_build_settings_name_build_static_length           12
  #define fake_build_settings_name_defines_all_length            11
  #define fake_build_settings_name_defines_shared_length         14
  #define fake_build_settings_name_defines_static_length         14
  #define fake_build_settings_name_flags_all_length              9
  #define fake_build_settings_name_flags_library_length          13
  #define fake_build_settings_name_flags_program_length          13
  #define fake_build_settings_name_flags_shared_length           12
  #define fake_build_settings_name_flags_static_length           12
  #define fake_build_settings_name_path_language_length          13
  #define fake_build_settings_name_path_headers_length           12
  #define fake_build_settings_name_path_library_shared_length    19
  #define fake_build_settings_name_path_library_static_length    19
  #define fake_build_settings_name_path_program_shared_length    19
  #define fake_build_settings_name_path_program_static_length    19
  #define fake_build_settings_name_process_post_length           12
  #define fake_build_settings_name_process_pre_length            11
  #define fake_build_settings_name_project_level_length          13
  #define fake_build_settings_name_project_name_length           12
  #define fake_build_settings_name_version_major_length          13
  #define fake_build_settings_name_version_micro_length          13
  #define fake_build_settings_name_version_minor_length          13

  #define fake_build_settings_total 31
#endif // _di_fake_build_settings_

/**
 * Find the build settings file, load it, validate it, and process it.
 *
 * @param data
 *   The program data.
 * @param settings
 *   All build related settings data from the build settings file are loaded into this.
 *   These settings will have any specified mode property applied.
 *
 * @return
 *   f_none on success.
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_build_load_settings_
  extern f_return_status fake_build_load_settings(const fake_data data, fake_build_settings *settings) f_gcc_attribute_visibility_internal;
#endif // _di_fake_build_load_settings_

/**
 * Execute the build operation.
 *
 * @param data
 *   The program data.
 *
 * @return
 *   f_none on success.
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_build_operate_
  extern f_return_status fake_build_operate(const fake_data data) f_gcc_attribute_visibility_internal;
#endif // _di_fake_build_operate_

/**
 * Execute the Pre-Process or Post-pocess build script.
 *
 * @param data
 *   The program data.
 * @param settings
 *   All build related settings data from the build settings file.
 * @param process_script
 *   The setting_data file name fo the appropriate process script.
 *   This is expected to be either settings.process_pre or settings.process_post.
 *
 * @return
 *   f_none on success.
 *   Status codes (with error bit) are returned on any problem.
 */
#ifndef _di_fake_build_execute_process_script_
  extern f_return_status fake_build_execute_process_script(const fake_data data, const fake_build_settings settings, const f_string_static process_script) f_gcc_attribute_visibility_internal;
#endif // _di_fake_build_execute_process_script_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_build_h
