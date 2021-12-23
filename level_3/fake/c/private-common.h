/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_common_h
#define _PRIVATE_common_h

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_setting_t_
  typedef struct {
    uint8_t build_language;

    uint8_t version_file;
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
    f_string_dynamic_t version_major_prefix;
    f_string_dynamic_t version_micro;
    f_string_dynamic_t version_micro_prefix;
    f_string_dynamic_t version_minor;
    f_string_dynamic_t version_minor_prefix;
    f_string_dynamic_t version_nano;
    f_string_dynamic_t version_nano_prefix;

    f_string_dynamics_t build_indexer_arguments;
    f_string_dynamics_t build_libraries;
    f_string_dynamics_t build_libraries_shared;
    f_string_dynamics_t build_libraries_static;
    f_string_dynamics_t build_sources_headers;
    f_string_dynamics_t build_sources_headers_shared;
    f_string_dynamics_t build_sources_headers_static;
    f_string_dynamics_t build_sources_library;
    f_string_dynamics_t build_sources_library_shared;
    f_string_dynamics_t build_sources_library_static;
    f_string_dynamics_t build_sources_program;
    f_string_dynamics_t build_sources_program_shared;
    f_string_dynamics_t build_sources_program_static;
    f_string_dynamics_t build_sources_script;
    f_string_dynamics_t build_sources_setting;
    f_string_dynamics_t defines;
    f_string_dynamics_t defines_library;
    f_string_dynamics_t defines_library_shared;
    f_string_dynamics_t defines_library_static;
    f_string_dynamics_t defines_program;
    f_string_dynamics_t defines_program_shared;
    f_string_dynamics_t defines_program_static;
    f_string_dynamics_t defines_shared;
    f_string_dynamics_t defines_static;
    f_string_dynamics_t environment;
    f_string_dynamics_t flags;
    f_string_dynamics_t flags_library;
    f_string_dynamics_t flags_library_shared;
    f_string_dynamics_t flags_library_static;
    f_string_dynamics_t flags_program;
    f_string_dynamics_t flags_program_shared;
    f_string_dynamics_t flags_program_static;
    f_string_dynamics_t flags_shared;
    f_string_dynamics_t flags_static;
    f_string_dynamics_t modes;
    f_string_dynamics_t modes_default;
  } fake_build_setting_t;

  #define fake_build_setting_t_initialize { \
    0, \
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
    f_string_dynamics_t_initialize, \
    f_string_dynamics_t_initialize, \
  }

  #define macro_fake_build_setting_t_delete_simple(setting) \
    macro_f_string_dynamic_t_delete_simple(setting.build_compiler) \
    macro_f_string_dynamic_t_delete_simple(setting.build_indexer) \
    macro_f_string_dynamic_t_delete_simple(setting.path_headers) \
    macro_f_string_dynamic_t_delete_simple(setting.path_language) \
    macro_f_string_dynamic_t_delete_simple(setting.path_library_script) \
    macro_f_string_dynamic_t_delete_simple(setting.path_library_shared) \
    macro_f_string_dynamic_t_delete_simple(setting.path_library_static) \
    macro_f_string_dynamic_t_delete_simple(setting.path_program_script) \
    macro_f_string_dynamic_t_delete_simple(setting.path_program_shared) \
    macro_f_string_dynamic_t_delete_simple(setting.path_program_static) \
    macro_f_string_dynamic_t_delete_simple(setting.path_sources) \
    macro_f_string_dynamic_t_delete_simple(setting.process_post) \
    macro_f_string_dynamic_t_delete_simple(setting.process_pre) \
    macro_f_string_dynamic_t_delete_simple(setting.project_name) \
    macro_f_string_dynamic_t_delete_simple(setting.version_major) \
    macro_f_string_dynamic_t_delete_simple(setting.version_major_prefix) \
    macro_f_string_dynamic_t_delete_simple(setting.version_micro) \
    macro_f_string_dynamic_t_delete_simple(setting.version_micro_prefix) \
    macro_f_string_dynamic_t_delete_simple(setting.version_minor) \
    macro_f_string_dynamic_t_delete_simple(setting.version_minor_prefix) \
    macro_f_string_dynamic_t_delete_simple(setting.version_nano) \
    macro_f_string_dynamic_t_delete_simple(setting.version_nano_prefix) \
    macro_f_string_dynamics_t_delete_simple(setting.build_indexer_arguments) \
    macro_f_string_dynamics_t_delete_simple(setting.build_libraries) \
    macro_f_string_dynamics_t_delete_simple(setting.build_libraries_shared) \
    macro_f_string_dynamics_t_delete_simple(setting.build_libraries_static) \
    macro_f_string_dynamics_t_delete_simple(setting.build_sources_headers) \
    macro_f_string_dynamics_t_delete_simple(setting.build_sources_headers_shared) \
    macro_f_string_dynamics_t_delete_simple(setting.build_sources_headers_static) \
    macro_f_string_dynamics_t_delete_simple(setting.build_sources_library) \
    macro_f_string_dynamics_t_delete_simple(setting.build_sources_library_shared) \
    macro_f_string_dynamics_t_delete_simple(setting.build_sources_library_static) \
    macro_f_string_dynamics_t_delete_simple(setting.build_sources_program) \
    macro_f_string_dynamics_t_delete_simple(setting.build_sources_program_shared) \
    macro_f_string_dynamics_t_delete_simple(setting.build_sources_program_static) \
    macro_f_string_dynamics_t_delete_simple(setting.build_sources_script) \
    macro_f_string_dynamics_t_delete_simple(setting.build_sources_setting) \
    macro_f_string_dynamics_t_delete_simple(setting.defines) \
    macro_f_string_dynamics_t_delete_simple(setting.defines_library) \
    macro_f_string_dynamics_t_delete_simple(setting.defines_library_shared) \
    macro_f_string_dynamics_t_delete_simple(setting.defines_library_static) \
    macro_f_string_dynamics_t_delete_simple(setting.defines_program) \
    macro_f_string_dynamics_t_delete_simple(setting.defines_program_shared) \
    macro_f_string_dynamics_t_delete_simple(setting.defines_program_static) \
    macro_f_string_dynamics_t_delete_simple(setting.defines_shared) \
    macro_f_string_dynamics_t_delete_simple(setting.defines_static) \
    macro_f_string_dynamics_t_delete_simple(setting.environment) \
    macro_f_string_dynamics_t_delete_simple(setting.flags) \
    macro_f_string_dynamics_t_delete_simple(setting.flags_library) \
    macro_f_string_dynamics_t_delete_simple(setting.flags_library_shared) \
    macro_f_string_dynamics_t_delete_simple(setting.flags_library_static) \
    macro_f_string_dynamics_t_delete_simple(setting.flags_program) \
    macro_f_string_dynamics_t_delete_simple(setting.flags_program_shared) \
    macro_f_string_dynamics_t_delete_simple(setting.flags_program_static) \
    macro_f_string_dynamics_t_delete_simple(setting.flags_shared) \
    macro_f_string_dynamics_t_delete_simple(setting.flags_static) \
    macro_f_string_dynamics_t_delete_simple(setting.modes) \
    macro_f_string_dynamics_t_delete_simple(setting.modes_default)

  #define FAKE_build_setting_name_build_compiler_s               "build_compiler"
  #define FAKE_build_setting_name_build_language_s               "build_language"
  #define FAKE_build_setting_name_build_libraries_s              "build_libraries"
  #define FAKE_build_setting_name_build_libraries_shared_s       "build_libraries_shared"
  #define FAKE_build_setting_name_build_libraries_static_s       "build_libraries_static"
  #define FAKE_build_setting_name_build_indexer_s                "build_indexer"
  #define FAKE_build_setting_name_build_indexer_arguments_s      "build_indexer_arguments"
  #define FAKE_build_setting_name_build_script_s                 "build_script"
  #define FAKE_build_setting_name_build_shared_s                 "build_shared"
  #define FAKE_build_setting_name_build_sources_headers_s        "build_sources_headers"
  #define FAKE_build_setting_name_build_sources_headers_shared_s "build_sources_headers_shared"
  #define FAKE_build_setting_name_build_sources_headers_static_s "build_sources_headers_static"
  #define FAKE_build_setting_name_build_sources_library_s        "build_sources_library"
  #define FAKE_build_setting_name_build_sources_library_shared_s "build_sources_library_shared"
  #define FAKE_build_setting_name_build_sources_library_static_s "build_sources_library_static"
  #define FAKE_build_setting_name_build_sources_program_s        "build_sources_program"
  #define FAKE_build_setting_name_build_sources_program_shared_s "build_sources_program_shared"
  #define FAKE_build_setting_name_build_sources_program_static_s "build_sources_program_static"
  #define FAKE_build_setting_name_build_sources_script_s         "build_sources_script"
  #define FAKE_build_setting_name_build_sources_settings_s       "build_sources_setting"
  #define FAKE_build_setting_name_build_static_s                 "build_static"
  #define FAKE_build_setting_name_defines_s                      "defines"
  #define FAKE_build_setting_name_defines_library_s              "defines_library"
  #define FAKE_build_setting_name_defines_library_shared_s       "defines_library_shared"
  #define FAKE_build_setting_name_defines_library_static_s       "defines_library_static"
  #define FAKE_build_setting_name_defines_program_s              "defines_program"
  #define FAKE_build_setting_name_defines_program_shared_s       "defines_program_shared"
  #define FAKE_build_setting_name_defines_program_static_s       "defines_program_static"
  #define FAKE_build_setting_name_defines_shared_s               "defines_shared"
  #define FAKE_build_setting_name_defines_static_s               "defines_static"
  #define FAKE_build_setting_name_environment_s                  "environment"
  #define FAKE_build_setting_name_flags_s                        "flags"
  #define FAKE_build_setting_name_flags_library_s                "flags_library"
  #define FAKE_build_setting_name_flags_library_shared_s         "flags_library_shared"
  #define FAKE_build_setting_name_flags_library_static_s         "flags_library_static"
  #define FAKE_build_setting_name_flags_program_s                "flags_program"
  #define FAKE_build_setting_name_flags_program_shared_s         "flags_program_shared"
  #define FAKE_build_setting_name_flags_program_static_s         "flags_program_static"
  #define FAKE_build_setting_name_flags_shared_s                 "flags_shared"
  #define FAKE_build_setting_name_flags_static_s                 "flags_static"
  #define FAKE_build_setting_name_modes_s                        "modes"
  #define FAKE_build_setting_name_modes_default_s                "modes_default"
  #define FAKE_build_setting_name_path_headers_s                 "path_headers"
  #define FAKE_build_setting_name_path_headers_preserve_s        "path_headers_preserve"
  #define FAKE_build_setting_name_path_language_s                "path_language"
  #define FAKE_build_setting_name_path_library_script_s          "path_library_script"
  #define FAKE_build_setting_name_path_library_shared_s          "path_library_shared"
  #define FAKE_build_setting_name_path_library_static_s          "path_library_static"
  #define FAKE_build_setting_name_path_program_script_s          "path_program_script"
  #define FAKE_build_setting_name_path_program_shared_s          "path_program_shared"
  #define FAKE_build_setting_name_path_program_static_s          "path_program_static"
  #define FAKE_build_setting_name_path_sources_s                 "path_sources"
  #define FAKE_build_setting_name_path_standard_s                "path_standard"
  #define FAKE_build_setting_name_process_post_s                 "process_post"
  #define FAKE_build_setting_name_process_pre_s                  "process_pre"
  #define FAKE_build_setting_name_project_name_s                 "project_name"
  #define FAKE_build_setting_name_search_exclusive_s             "search_exclusive"
  #define FAKE_build_setting_name_search_shared_s                "search_shared"
  #define FAKE_build_setting_name_search_static_s                "search_static"
  #define FAKE_build_setting_name_version_file_s                 "version_file"
  #define FAKE_build_setting_name_version_major_s                "version_major"
  #define FAKE_build_setting_name_version_major_prefix_s         "version_major_prefix"
  #define FAKE_build_setting_name_version_micro_s                "version_micro"
  #define FAKE_build_setting_name_version_micro_prefix_s         "version_micro_prefix"
  #define FAKE_build_setting_name_version_minor_s                "version_minor"
  #define FAKE_build_setting_name_version_minor_prefix_s         "version_minor_prefix"
  #define FAKE_build_setting_name_version_nano_s                 "version_nano"
  #define FAKE_build_setting_name_version_nano_prefix_s          "version_nano_prefix"
  #define FAKE_build_setting_name_version_target_s               "version_target"

  #define fake_build_setting_name_build_compiler_s_length               14
  #define fake_build_setting_name_build_language_s_length               14
  #define fake_build_setting_name_build_libraries_s_length              15
  #define fake_build_setting_name_build_libraries_shared_s_length       22
  #define fake_build_setting_name_build_libraries_static_s_length       22
  #define fake_build_setting_name_build_indexer_s_length                13
  #define fake_build_setting_name_build_indexer_arguments_s_length      23
  #define fake_build_setting_name_build_script_s_length                 12
  #define fake_build_setting_name_build_shared_s_length                 12
  #define fake_build_setting_name_build_sources_headers_s_length        21
  #define fake_build_setting_name_build_sources_headers_shared_s_length 28
  #define fake_build_setting_name_build_sources_headers_static_s_length 28
  #define fake_build_setting_name_build_sources_library_s_length        21
  #define fake_build_setting_name_build_sources_library_shared_s_length 28
  #define fake_build_setting_name_build_sources_library_static_s_length 28
  #define fake_build_setting_name_build_sources_program_s_length        21
  #define fake_build_setting_name_build_sources_program_shared_s_length 28
  #define fake_build_setting_name_build_sources_program_static_s_length 28
  #define fake_build_setting_name_build_sources_script_s_length         20
  #define fake_build_setting_name_build_sources_settings_s_length       22
  #define fake_build_setting_name_build_static_s_length                 12
  #define fake_build_setting_name_environment_length_s                  11
  #define fake_build_setting_name_defines_s_length                      7
  #define fake_build_setting_name_defines_library_s_length              15
  #define fake_build_setting_name_defines_library_shared_s_length       22
  #define fake_build_setting_name_defines_library_static_s_length       22
  #define fake_build_setting_name_defines_program_s_length              15
  #define fake_build_setting_name_defines_program_shared_s_length       22
  #define fake_build_setting_name_defines_program_static_s_length       22
  #define fake_build_setting_name_defines_shared_s_length               14
  #define fake_build_setting_name_defines_static_s_length               14
  #define fake_build_setting_name_flags_s_length                        5
  #define fake_build_setting_name_flags_library_s_length                13
  #define fake_build_setting_name_flags_library_shared_s_length         20
  #define fake_build_setting_name_flags_library_static_s_length         20
  #define fake_build_setting_name_flags_program_s_length                13
  #define fake_build_setting_name_flags_program_shared_s_length         20
  #define fake_build_setting_name_flags_program_static_s_length         20
  #define fake_build_setting_name_flags_shared_s_length                 12
  #define fake_build_setting_name_flags_static_s_length                 12
  #define fake_build_setting_name_modes_s_length                        5
  #define fake_build_setting_name_modes_default_s_length                13
  #define fake_build_setting_name_path_headers_s_length                 12
  #define fake_build_setting_name_path_headers_preserve_s_length        21
  #define fake_build_setting_name_path_language_s_length                13
  #define fake_build_setting_name_path_library_script_s_length          19
  #define fake_build_setting_name_path_library_shared_s_length          19
  #define fake_build_setting_name_path_library_static_s_length          19
  #define fake_build_setting_name_path_program_script_s_length          19
  #define fake_build_setting_name_path_program_shared_s_length          19
  #define fake_build_setting_name_path_program_static_s_length          19
  #define fake_build_setting_name_path_sources_s_length                 12
  #define fake_build_setting_name_path_standard_s_length                13
  #define fake_build_setting_name_process_post_s_length                 12
  #define fake_build_setting_name_process_pre_s_length                  11
  #define fake_build_setting_name_project_name_s_length                 12
  #define fake_build_setting_name_search_exclusive_s_length             16
  #define fake_build_setting_name_search_shared_s_length                13
  #define fake_build_setting_name_search_static_s_length                13
  #define fake_build_setting_name_version_file_s_length                 12
  #define fake_build_setting_name_version_major_s_length                13
  #define fake_build_setting_name_version_major_prefix_s_length         20
  #define fake_build_setting_name_version_micro_s_length                13
  #define fake_build_setting_name_version_micro_prefix_s_length         20
  #define fake_build_setting_name_version_minor_s_length                13
  #define fake_build_setting_name_version_minor_prefix_s_length         20
  #define fake_build_setting_name_version_nano_s_length                 12
  #define fake_build_setting_name_version_nano_prefix_s_length          19
  #define fake_build_setting_name_version_target_s_length               14

  extern const f_string_t fake_build_setting_name_build_compiler_s;
  extern const f_string_t fake_build_setting_name_build_language_s;
  extern const f_string_t fake_build_setting_name_build_libraries_s;
  extern const f_string_t fake_build_setting_name_build_libraries_shared_s;
  extern const f_string_t fake_build_setting_name_build_libraries_static_s;
  extern const f_string_t fake_build_setting_name_build_indexer_s;
  extern const f_string_t fake_build_setting_name_build_indexer_arguments_s;
  extern const f_string_t fake_build_setting_name_build_script_s;
  extern const f_string_t fake_build_setting_name_build_shared_s;
  extern const f_string_t fake_build_setting_name_build_sources_headers_s;
  extern const f_string_t fake_build_setting_name_build_sources_headers_shared_s;
  extern const f_string_t fake_build_setting_name_build_sources_headers_static_s;
  extern const f_string_t fake_build_setting_name_build_sources_library_s;
  extern const f_string_t fake_build_setting_name_build_sources_library_shared_s;
  extern const f_string_t fake_build_setting_name_build_sources_library_static_s;
  extern const f_string_t fake_build_setting_name_build_sources_program_s;
  extern const f_string_t fake_build_setting_name_build_sources_program_shared_s;
  extern const f_string_t fake_build_setting_name_build_sources_program_static_s;
  extern const f_string_t fake_build_setting_name_build_sources_script_s;
  extern const f_string_t fake_build_setting_name_build_sources_settings_s;
  extern const f_string_t fake_build_setting_name_build_static_s;
  extern const f_string_t fake_build_setting_name_defines_s;
  extern const f_string_t fake_build_setting_name_defines_library_s;
  extern const f_string_t fake_build_setting_name_defines_library_shared_s;
  extern const f_string_t fake_build_setting_name_defines_library_static_s;
  extern const f_string_t fake_build_setting_name_defines_program_s;
  extern const f_string_t fake_build_setting_name_defines_program_shared_s;
  extern const f_string_t fake_build_setting_name_defines_program_static_s;
  extern const f_string_t fake_build_setting_name_defines_shared_s;
  extern const f_string_t fake_build_setting_name_defines_static_s;
  extern const f_string_t fake_build_setting_name_environment_s;
  extern const f_string_t fake_build_setting_name_flags_s;
  extern const f_string_t fake_build_setting_name_flags_library_s;
  extern const f_string_t fake_build_setting_name_flags_library_shared_s;
  extern const f_string_t fake_build_setting_name_flags_library_static_s;
  extern const f_string_t fake_build_setting_name_flags_program_s;
  extern const f_string_t fake_build_setting_name_flags_program_shared_s;
  extern const f_string_t fake_build_setting_name_flags_program_static_s;
  extern const f_string_t fake_build_setting_name_flags_shared_s;
  extern const f_string_t fake_build_setting_name_flags_static_s;
  extern const f_string_t fake_build_setting_name_modes_s;
  extern const f_string_t fake_build_setting_name_modes_default_s;
  extern const f_string_t fake_build_setting_name_path_headers_s;
  extern const f_string_t fake_build_setting_name_path_headers_preserve_s;
  extern const f_string_t fake_build_setting_name_path_language_s;
  extern const f_string_t fake_build_setting_name_path_library_script_s;
  extern const f_string_t fake_build_setting_name_path_library_shared_s;
  extern const f_string_t fake_build_setting_name_path_library_static_s;
  extern const f_string_t fake_build_setting_name_path_program_script_s;
  extern const f_string_t fake_build_setting_name_path_program_shared_s;
  extern const f_string_t fake_build_setting_name_path_program_static_s;
  extern const f_string_t fake_build_setting_name_path_sources_s;
  extern const f_string_t fake_build_setting_name_path_standard_s;
  extern const f_string_t fake_build_setting_name_process_post_s;
  extern const f_string_t fake_build_setting_name_process_pre_s;
  extern const f_string_t fake_build_setting_name_project_name_s;
  extern const f_string_t fake_build_setting_name_search_exclusive_s;
  extern const f_string_t fake_build_setting_name_search_shared_s;
  extern const f_string_t fake_build_setting_name_search_static_s;
  extern const f_string_t fake_build_setting_name_version_file_s;
  extern const f_string_t fake_build_setting_name_version_major_s;
  extern const f_string_t fake_build_setting_name_version_major_prefix_s;
  extern const f_string_t fake_build_setting_name_version_micro_s;
  extern const f_string_t fake_build_setting_name_version_micro_prefix_s;
  extern const f_string_t fake_build_setting_name_version_minor_s;
  extern const f_string_t fake_build_setting_name_version_minor_prefix_s;
  extern const f_string_t fake_build_setting_name_version_nano_s;
  extern const f_string_t fake_build_setting_name_version_nano_prefix_s;
  extern const f_string_t fake_build_setting_name_version_target_s;

  #define fake_build_setting_total_d 69

  #define FAKE_build_setting_default_version_s        "0"
  #define FAKE_build_setting_default_version_prefix_s "."

  #define fake_build_setting_default_version_s_length        1
  #define fake_build_setting_default_version_prefix_s_length 1

  extern const f_string_t fake_build_setting_default_version_s;
  extern const f_string_t fake_build_setting_default_version_prefix_s;
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

  #define fake_build_stage_total_d 13

  #define macro_fake_build_stage_t_delete_simple(stage) \
    macro_f_string_dynamic_t_delete_simple(stage.file_libraries_script) \
    macro_f_string_dynamic_t_delete_simple(stage.file_libraries_shared) \
    macro_f_string_dynamic_t_delete_simple(stage.file_libraries_static) \
    macro_f_string_dynamic_t_delete_simple(stage.file_objects_static) \
    macro_f_string_dynamic_t_delete_simple(stage.file_process_post) \
    macro_f_string_dynamic_t_delete_simple(stage.file_process_pre) \
    macro_f_string_dynamic_t_delete_simple(stage.file_programs_script) \
    macro_f_string_dynamic_t_delete_simple(stage.file_programs_shared) \
    macro_f_string_dynamic_t_delete_simple(stage.file_programs_static) \
    macro_f_string_dynamic_t_delete_simple(stage.file_skeleton) \
    macro_f_string_dynamic_t_delete_simple(stage.file_sources_headers) \
    macro_f_string_dynamic_t_delete_simple(stage.file_sources_script) \
    macro_f_string_dynamic_t_delete_simple(stage.file_sources_settings)

  #define FAKE_build_stage_built_s            ".built"
  #define FAKE_build_stage_libraries_script_s "libraries_script"
  #define FAKE_build_stage_libraries_shared_s "libraries_shared"
  #define FAKE_build_stage_libraries_static_s "libraries_static"
  #define FAKE_build_stage_objects_static_s   "objects_static"
  #define FAKE_build_stage_process_post_s     "process_post"
  #define FAKE_build_stage_process_pre_s      "process_pre"
  #define FAKE_build_stage_programs_script_s  "programs_script"
  #define FAKE_build_stage_programs_shared_s  "programs_shared"
  #define FAKE_build_stage_programs_static_s  "programs_static"
  #define FAKE_build_stage_separate_s         "-"
  #define FAKE_build_stage_skeleton_s         "skeleton"
  #define FAKE_build_stage_sources_headers_s  "sources_headers"
  #define FAKE_build_stage_sources_script_s   "sources_script"
  #define FAKE_build_stage_sources_settings_s "sources_settings"

  #define fake_build_stage_built_s_length            6
  #define fake_build_stage_libraries_script_s_length 16
  #define fake_build_stage_libraries_shared_s_length 16
  #define fake_build_stage_libraries_static_s_length 16
  #define fake_build_stage_objects_static_s_length   14
  #define fake_build_stage_process_post_s_length     12
  #define fake_build_stage_process_pre_s_length      11
  #define fake_build_stage_programs_script_s_length  15
  #define fake_build_stage_programs_shared_s_length  15
  #define fake_build_stage_programs_static_s_length  15
  #define fake_build_stage_separate_s_length         1
  #define fake_build_stage_skeleton_s_length         8
  #define fake_build_stage_sources_headers_s_length  15
  #define fake_build_stage_sources_script_s_length   14
  #define fake_build_stage_sources_settings_s_length 16

  extern const f_string_t fake_build_stage_built_s;
  extern const f_string_t fake_build_stage_libraries_script_s;
  extern const f_string_t fake_build_stage_libraries_shared_s;
  extern const f_string_t fake_build_stage_libraries_static_s;
  extern const f_string_t fake_build_stage_objects_static_s;
  extern const f_string_t fake_build_stage_process_post_s;
  extern const f_string_t fake_build_stage_process_pre_s;
  extern const f_string_t fake_build_stage_programs_script_s;
  extern const f_string_t fake_build_stage_programs_shared_s;
  extern const f_string_t fake_build_stage_programs_static_s;
  extern const f_string_t fake_build_stage_separate_s;
  extern const f_string_t fake_build_stage_skeleton_s;
  extern const f_string_t fake_build_stage_sources_headers_s;
  extern const f_string_t fake_build_stage_sources_script_s;
  extern const f_string_t fake_build_stage_sources_settings_s;
#endif // _di_fake_build_stage_t_

#ifndef _di_fake_build_data_t_
  typedef struct {
    fake_build_setting_t setting;
    f_string_maps_t environment;
  } fake_build_data_t;

  #define fake_build_data_t_initialize { \
    fake_build_setting_t_initialize, \
    f_string_maps_t_initialize, \
  }

  #define macro_fake_build_main_delete_simple(build) \
    macro_fake_build_setting_t_delete_simple(build.setting) \
    macro_f_string_maps_t_delete_simple(build.environment);
#endif // _di_fake_build_data_t_

#ifndef _di_fake_build_parameter_
  #define FAKE_build_parameter_library_include_s            "-I"
  #define FAKE_build_parameter_library_link_file_s          "-l"
  #define FAKE_build_parameter_library_link_path_s          "-L"
  #define FAKE_build_parameter_library_name_prefix_s        "lib"
  #define FAKE_build_parameter_library_name_suffix_shared_s ".so"
  #define FAKE_build_parameter_library_name_suffix_static_s ".a"
  #define FAKE_build_parameter_library_output_s             "-o"
  #define FAKE_build_parameter_library_shared_s             "-shared"
  #define FAKE_build_parameter_library_static_s             "-static"
  #define FAKE_build_parameter_library_shared_prefix_s      "-Wl,-soname,"

  #define fake_build_parameter_library_include_s_length            2
  #define fake_build_parameter_library_link_file_s_length          2
  #define fake_build_parameter_library_link_path_s_length          2
  #define fake_build_parameter_library_name_prefix_s_length        3
  #define fake_build_parameter_library_name_suffix_shared_s_length 3
  #define fake_build_parameter_library_name_suffix_static_s_length 2
  #define fake_build_parameter_library_output_s_length             2
  #define fake_build_parameter_library_shared_s_length             7
  #define fake_build_parameter_library_static_s_length             7
  #define fake_build_parameter_library_shared_prefix_s_length      12

  extern const f_string_t fake_build_parameter_library_include_s;
  extern const f_string_t fake_build_parameter_library_link_file_s;
  extern const f_string_t fake_build_parameter_library_link_path_s;
  extern const f_string_t fake_build_parameter_library_name_prefix_s;
  extern const f_string_t fake_build_parameter_library_name_suffix_shared_s;
  extern const f_string_t fake_build_parameter_library_name_suffix_static_s;
  extern const f_string_t fake_build_parameter_library_output_s;
  extern const f_string_t fake_build_parameter_library_shared_s;
  extern const f_string_t fake_build_parameter_library_static_s;
  extern const f_string_t fake_build_parameter_library_shared_prefix_s;

  #define FAKE_build_parameter_object_compile_s     "-c"
  #define FAKE_build_parameter_object_name_suffix_s ".o"
  #define FAKE_build_parameter_object_output_s      "-o"
  #define FAKE_build_parameter_object_static_s      "-static"

  #define fake_build_parameter_object_compile_s_length     2
  #define fake_build_parameter_object_name_suffix_s_length 2
  #define fake_build_parameter_object_output_s_length      2
  #define fake_build_parameter_object_static_s_length      7

  extern const f_string_t fake_build_parameter_object_compile_s;
  extern const f_string_t fake_build_parameter_object_name_suffix_s;
  extern const f_string_t fake_build_parameter_object_output_s;
  extern const f_string_t fake_build_parameter_object_static_s;
#endif // _di_fake_build_parameter_

/**
 * Provide common/generic definitions.
 *
 * fake_common_allocation_*:
 *   - large: An allocation step used for buffers that are anticipated to have large buffers.
 *   - small: An allocation step used for buffers that are anticipated to have small buffers.
 *
 * fake_common_setting_bool_*:
 *   - yes: A representation of yes or true.
 *   - no:  A representation of no or false.
 */
#ifndef _di_fake_common_
  #define fake_common_allocation_large_d 256
  #define fake_common_allocation_small_d 16

  #define FAKE_common_setting_bool_yes_s "yes"
  #define FAKE_common_setting_bool_no_s  "no"

  #define fake_common_setting_bool_yes_s_length 3
  #define fake_common_setting_bool_no_s_length  2

  extern const f_string_t fake_common_setting_bool_yes_s;
  extern const f_string_t fake_common_setting_bool_no_s;

  #define fake_common_initial_buffer_max_d 131072 // 128k max default initial buffer size.
#endif // _di_fake_common_

/**
 * Provide common/generic definitions.
 *
 * fake_make_section_*:
 *   - main:     The main section.
 *   - settings: The settings section.
 */
#ifndef _di_fake_make_section_
  #define FAKE_make_section_main_s     "main"
  #define FAKE_make_section_settings_s "settings"

  #define fake_make_section_main_s_length     4
  #define fake_make_section_settings_s_length 8

  extern const f_string_t fake_make_section_main_s;
  extern const f_string_t fake_make_section_settings_s;

  #define fake_make_section_stack_max_d 8192 // maximum stack call depth.
#endif // _di_fake_make_section_

#ifndef _di_fake_make_setting_t_
  typedef struct {
    bool load_build;

    uint8_t fail;

    f_string_map_multis_t parameter;
  } fake_make_setting_t;

  #define fake_make_setting_t_initialize { \
    0, \
    0, \
    f_string_map_multis_t_initialize, \
  }

  #define macro_fake_make_setting_t_delete_simple(setting) \
    macro_f_string_map_multis_t_delete_simple(setting.parameter)

  #define FAKE_make_setting_compiler_s          "compiler"
  #define FAKE_make_setting_define_s            "define"
  #define FAKE_make_setting_environment_s       "environment"
  #define FAKE_make_setting_fail_s              "fail"
  #define FAKE_make_setting_indexer_s           "indexer"
  #define FAKE_make_setting_indexer_arguments_s "indexer_arguments"
  #define FAKE_make_setting_load_build_s        "load_build"
  #define FAKE_make_setting_parameter_s         "parameter"
  #define FAKE_make_setting_return_s            "return"

  #define fake_make_setting_compiler_s_length          8
  #define fake_make_setting_define_s_length            6
  #define fake_make_setting_environment_s_length       11
  #define fake_make_setting_fail_s_length              4
  #define fake_make_setting_indexer_s_length           7
  #define fake_make_setting_indexer_arguments_s_length 17
  #define fake_make_setting_load_build_s_length        10
  #define fake_make_setting_parameter_s_length         9
  #define fake_make_setting_return_s_length            6

  extern const f_string_t fake_make_setting_compiler_s;
  extern const f_string_t fake_make_setting_define_s;
  extern const f_string_t fake_make_setting_environment_s;
  extern const f_string_t fake_make_setting_fail_s;
  extern const f_string_t fake_make_setting_indexer_s;
  extern const f_string_t fake_make_setting_indexer_arguments_s;
  extern const f_string_t fake_make_setting_load_build_s;
  extern const f_string_t fake_make_setting_parameter_s;
  extern const f_string_t fake_make_setting_return_s;
#endif // _di_fake_make_setting_t_

#ifndef _di_fake_make_operation_
  #define FAKE_make_operation_and_s       "and"
  #define FAKE_make_operation_break_s     "break"
  #define FAKE_make_operation_build_s     "build"
  #define FAKE_make_operation_clean_s     "clean"
  #define FAKE_make_operation_clone_s     "clone"
  #define FAKE_make_operation_compile_s   "compile"
  #define FAKE_make_operation_copy_s      "copy"
  #define FAKE_make_operation_define_s    "define"
  #define FAKE_make_operation_delete_s    "delete"
  #define FAKE_make_operation_deletes_s   "deletes"
  #define FAKE_make_operation_else_s      "else"
  #define FAKE_make_operation_exit_s      "exit"
  #define FAKE_make_operation_fail_s      "fail"
  #define FAKE_make_operation_group_s     "group"
  #define FAKE_make_operation_groups_s    "groups"
  #define FAKE_make_operation_if_s        "if"
  #define FAKE_make_operation_index_s     "index"
  #define FAKE_make_operation_link_s      "link"
  #define FAKE_make_operation_mode_s      "mode"
  #define FAKE_make_operation_modes_s     "modes"
  #define FAKE_make_operation_move_s      "move"
  #define FAKE_make_operation_operate_s   "operate"
  #define FAKE_make_operation_or_s        "or"
  #define FAKE_make_operation_owner_s     "owner"
  #define FAKE_make_operation_owners_s    "owners"
  #define FAKE_make_operation_parameter_s "parameter"
  #define FAKE_make_operation_pop_s       "pop"
  #define FAKE_make_operation_print_s     "print"
  #define FAKE_make_operation_run_s       "run"
  #define FAKE_make_operation_shell_s     "shell"
  #define FAKE_make_operation_skeleton_s  "skeleton"
  #define FAKE_make_operation_to_s        "to"
  #define FAKE_make_operation_top_s       "top"
  #define FAKE_make_operation_touch_s     "touch"

  #define fake_make_operation_and_s_length       3
  #define fake_make_operation_break_s_length     5
  #define fake_make_operation_build_s_length     5
  #define fake_make_operation_clean_s_length     5
  #define fake_make_operation_clone_s_length     5
  #define fake_make_operation_compile_s_length   7
  #define fake_make_operation_copy_s_length      4
  #define fake_make_operation_define_s_length    6
  #define fake_make_operation_delete_s_length    6
  #define fake_make_operation_deletes_s_length   7
  #define fake_make_operation_else_s_length      4
  #define fake_make_operation_exit_s_length      4
  #define fake_make_operation_fail_s_length      4
  #define fake_make_operation_group_s_length     5
  #define fake_make_operation_groups_s_length    6
  #define fake_make_operation_if_s_length        2
  #define fake_make_operation_index_s_length     5
  #define fake_make_operation_link_s_length      4
  #define fake_make_operation_mode_s_length      4
  #define fake_make_operation_modes_s_length     5
  #define fake_make_operation_move_s_length      4
  #define fake_make_operation_operate_s_length   7
  #define fake_make_operation_or_s_length        2
  #define fake_make_operation_owner_s_length     5
  #define fake_make_operation_owners_s_length    6
  #define fake_make_operation_parameter_s_length 9
  #define fake_make_operation_pop_s_length       3
  #define fake_make_operation_print_s_length     5
  #define fake_make_operation_run_s_length       3
  #define fake_make_operation_shell_s_length     5
  #define fake_make_operation_skeleton_s_length  8
  #define fake_make_operation_to_s_length        2
  #define fake_make_operation_top_s_length       3
  #define fake_make_operation_touch_s_length     5

  extern const f_string_t fake_make_operation_and_s;
  extern const f_string_t fake_make_operation_break_s;
  extern const f_string_t fake_make_operation_build_s;
  extern const f_string_t fake_make_operation_clean_s;
  extern const f_string_t fake_make_operation_clone_s;
  extern const f_string_t fake_make_operation_compile_s;
  extern const f_string_t fake_make_operation_copy_s;
  extern const f_string_t fake_make_operation_define_s;
  extern const f_string_t fake_make_operation_delete_s;
  extern const f_string_t fake_make_operation_deletes_s;
  extern const f_string_t fake_make_operation_else_s;
  extern const f_string_t fake_make_operation_exit_s;
  extern const f_string_t fake_make_operation_fail_s;
  extern const f_string_t fake_make_operation_group_s;
  extern const f_string_t fake_make_operation_groups_s;
  extern const f_string_t fake_make_operation_if_s;
  extern const f_string_t fake_make_operation_index_s;
  extern const f_string_t fake_make_operation_link_s;
  extern const f_string_t fake_make_operation_mode_s;
  extern const f_string_t fake_make_operation_modes_s;
  extern const f_string_t fake_make_operation_move_s;
  extern const f_string_t fake_make_operation_operate_s;
  extern const f_string_t fake_make_operation_or_s;
  extern const f_string_t fake_make_operation_owner_s;
  extern const f_string_t fake_make_operation_owners_s;
  extern const f_string_t fake_make_operation_parameter_s;
  extern const f_string_t fake_make_operation_pop_s;
  extern const f_string_t fake_make_operation_print_s;
  extern const f_string_t fake_make_operation_run_s;
  extern const f_string_t fake_make_operation_shell_s;
  extern const f_string_t fake_make_operation_skeleton_s;
  extern const f_string_t fake_make_operation_to_s;
  extern const f_string_t fake_make_operation_top_s;
  extern const f_string_t fake_make_operation_touch_s;

  enum {
    fake_make_operation_type_and = 1,
    fake_make_operation_type_break,
    fake_make_operation_type_build,
    fake_make_operation_type_clean,
    fake_make_operation_type_clone,
    fake_make_operation_type_compile,
    fake_make_operation_type_copy,
    fake_make_operation_type_define,
    fake_make_operation_type_delete,
    fake_make_operation_type_deletes,
    fake_make_operation_type_else,
    fake_make_operation_type_exit,
    fake_make_operation_type_fail,
    fake_make_operation_type_group,
    fake_make_operation_type_groups,
    fake_make_operation_type_if,
    fake_make_operation_type_index,
    fake_make_operation_type_link,
    fake_make_operation_type_mode,
    fake_make_operation_type_modes,
    fake_make_operation_type_move,
    fake_make_operation_type_operate,
    fake_make_operation_type_or,
    fake_make_operation_type_owner,
    fake_make_operation_type_owners,
    fake_make_operation_type_parameter,
    fake_make_operation_type_pop,
    fake_make_operation_type_print,
    fake_make_operation_type_run,
    fake_make_operation_type_shell,
    fake_make_operation_type_skeleton,
    fake_make_operation_type_to,
    fake_make_operation_type_top,
    fake_make_operation_type_touch,
  };

  #define fake_make_operation_total_d 34

  #define FAKE_make_operation_argument_environment_s "environment"
  #define FAKE_make_operation_argument_failure_s     "failure"
  #define FAKE_make_operation_argument_file_s        "file"
  #define FAKE_make_operation_argument_directory_s   "directory"
  #define FAKE_make_operation_argument_error_s       "error"
  #define FAKE_make_operation_argument_exit_s        "exit"
  #define FAKE_make_operation_argument_has_s         "has"
  #define FAKE_make_operation_argument_ignore_s      "ignore"
  #define FAKE_make_operation_argument_is_s          "is"
  #define FAKE_make_operation_argument_parameter_s   "parameter"
  #define FAKE_make_operation_argument_point_s       "point"
  #define FAKE_make_operation_argument_recursive_s   "recursive"
  #define FAKE_make_operation_argument_success_s     "success"
  #define FAKE_make_operation_argument_target_s      "target"
  #define FAKE_make_operation_argument_warn_s        "warn"

  #define fake_make_operation_argument_environment_s_length 11
  #define fake_make_operation_argument_failure_s_length     7
  #define fake_make_operation_argument_file_s_length        4
  #define fake_make_operation_argument_directory_s_length   9
  #define fake_make_operation_argument_error_s_length       5
  #define fake_make_operation_argument_exit_s_length        4
  #define fake_make_operation_argument_has_s_length         3
  #define fake_make_operation_argument_ignore_s_length      6
  #define fake_make_operation_argument_is_s_length          2
  #define fake_make_operation_argument_parameter_s_length   9
  #define fake_make_operation_argument_point_s_length       5
  #define fake_make_operation_argument_recursive_s_length   9
  #define fake_make_operation_argument_success_s_length     7
  #define fake_make_operation_argument_target_s_length      6
  #define fake_make_operation_argument_warn_s_length        4

  extern const f_string_t fake_make_operation_argument_environment_s;
  extern const f_string_t fake_make_operation_argument_failure_s;
  extern const f_string_t fake_make_operation_argument_file_s;
  extern const f_string_t fake_make_operation_argument_directory_s;
  extern const f_string_t fake_make_operation_argument_error_s;
  extern const f_string_t fake_make_operation_argument_exit_s;
  extern const f_string_t fake_make_operation_argument_has_s;
  extern const f_string_t fake_make_operation_argument_ignore_s;
  extern const f_string_t fake_make_operation_argument_is_s;
  extern const f_string_t fake_make_operation_argument_parameter_s;
  extern const f_string_t fake_make_operation_argument_point_s;
  extern const f_string_t fake_make_operation_argument_recursive_s;
  extern const f_string_t fake_make_operation_argument_success_s;
  extern const f_string_t fake_make_operation_argument_target_s;
  extern const f_string_t fake_make_operation_argument_warn_s;

  #define FAKE_make_operation_argument_if_defined_s       "defined"
  #define FAKE_make_operation_argument_if_equal_s         "=="
  #define FAKE_make_operation_argument_if_equal_not_s     "<>"
  #define FAKE_make_operation_argument_if_exists_s        "exists"
  #define FAKE_make_operation_argument_if_failure_s       "failure"
  #define FAKE_make_operation_argument_if_greater_s       ">"
  #define FAKE_make_operation_argument_if_greater_equal_s ">="
  #define FAKE_make_operation_argument_if_group_s         "group"
  #define FAKE_make_operation_argument_if_is_s            "is"
  #define FAKE_make_operation_argument_if_is_for_s        "for"
  #define FAKE_make_operation_argument_if_less_s          "<"
  #define FAKE_make_operation_argument_if_less_equal_s    "<="
  #define FAKE_make_operation_argument_if_mode_s          "mode"
  #define FAKE_make_operation_argument_if_not_s           "not"
  #define FAKE_make_operation_argument_if_owner_s         "owner"
  #define FAKE_make_operation_argument_if_success_s       "success"

  #define fake_make_operation_argument_if_defined_s_length       7
  #define fake_make_operation_argument_if_equal_s_length         2
  #define fake_make_operation_argument_if_equal_not_s_length     2
  #define fake_make_operation_argument_if_exists_s_length        6
  #define fake_make_operation_argument_if_failure_s_length       7
  #define fake_make_operation_argument_if_greater_s_length       1
  #define fake_make_operation_argument_if_greater_equal_s_length 2
  #define fake_make_operation_argument_if_group_s_length         5
  #define fake_make_operation_argument_if_is_s_length            2
  #define fake_make_operation_argument_if_is_for_s_length        3
  #define fake_make_operation_argument_if_less_s_length          1
  #define fake_make_operation_argument_if_less_equal_s_length    2
  #define fake_make_operation_argument_if_mode_s_length          4
  #define fake_make_operation_argument_if_not_s_length           3
  #define fake_make_operation_argument_if_owner_s_length         5
  #define fake_make_operation_argument_if_success_s_length       7

  extern const f_string_t fake_make_operation_argument_if_defined_s;
  extern const f_string_t fake_make_operation_argument_if_equal_s;
  extern const f_string_t fake_make_operation_argument_if_equal_not_s;
  extern const f_string_t fake_make_operation_argument_if_exists_s;
  extern const f_string_t fake_make_operation_argument_if_failure_s;
  extern const f_string_t fake_make_operation_argument_if_greater_s;
  extern const f_string_t fake_make_operation_argument_if_greater_equal_s;
  extern const f_string_t fake_make_operation_argument_if_group_s;
  extern const f_string_t fake_make_operation_argument_if_is_s;
  extern const f_string_t fake_make_operation_argument_if_is_for_s;
  extern const f_string_t fake_make_operation_argument_if_less_s;
  extern const f_string_t fake_make_operation_argument_if_less_equal_s;
  extern const f_string_t fake_make_operation_argument_if_mode_s;
  extern const f_string_t fake_make_operation_argument_if_not_s;
  extern const f_string_t fake_make_operation_argument_if_owner_s;
  extern const f_string_t fake_make_operation_argument_if_success_s;

  enum {
    fake_make_operation_if_type_done = 1,
    fake_make_operation_if_type_else,
    fake_make_operation_if_type_if,
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
    fake_make_operation_if_type_if_not,
    fake_make_operation_if_type_if_not_defined,
    fake_make_operation_if_type_if_not_exists,
    fake_make_operation_if_type_if_not_group,
    fake_make_operation_if_type_if_not_is,
    fake_make_operation_if_type_if_not_mode,
    fake_make_operation_if_type_if_not_owner,
    fake_make_operation_if_type_if_owner,
    fake_make_operation_if_type_if_success,
  };

  enum {
    fake_make_operation_fail_type_exit = 1,
    fake_make_operation_fail_type_warn,
    fake_make_operation_fail_type_ignore,
  };

  #define fake_make_operation_recursion_depth_max_d 65535
#endif // _di_fake_make_operation_

#ifndef _di_fake_make_parameter_t_
  #define FAKE_make_parameter_variable_build_s     "build"
  #define FAKE_make_parameter_variable_color_s     "color"
  #define FAKE_make_parameter_variable_data_s      "data"
  #define FAKE_make_parameter_variable_define_s    "define"
  #define FAKE_make_parameter_variable_fakefile_s  "fakefile"
  #define FAKE_make_parameter_variable_mode_s      "mode"
  #define FAKE_make_parameter_variable_process_s   "process"
  #define FAKE_make_parameter_variable_return_s    "return"
  #define FAKE_make_parameter_variable_settings_s  "settings"
  #define FAKE_make_parameter_variable_sources_s   "sources"
  #define FAKE_make_parameter_variable_verbosity_s "verbosity"
  #define FAKE_make_parameter_variable_work_s      "work"

  #define fake_make_parameter_iki_option_s ":option"
  #define fake_make_parameter_iki_value_s  ":value"

  #define fake_make_parameter_variable_build_s_length     5
  #define fake_make_parameter_variable_color_s_length     5
  #define fake_make_parameter_variable_data_s_length      4
  #define fake_make_parameter_variable_define_s_length    6
  #define fake_make_parameter_variable_fakefile_s_length  8
  #define fake_make_parameter_variable_mode_s_length      4
  #define fake_make_parameter_variable_process_s_length   7
  #define fake_make_parameter_variable_return_s_length    6
  #define fake_make_parameter_variable_settings_s_length  8
  #define fake_make_parameter_variable_sources_s_length   7
  #define fake_make_parameter_variable_verbosity_s_length 9
  #define fake_make_parameter_variable_work_s_length      4

  #define fake_make_parameter_iki_option_s_length 7
  #define fake_make_parameter_iki_value_s_length  6

  extern const f_string_t fake_make_parameter_variable_build_s;
  extern const f_string_t fake_make_parameter_variable_color_s;
  extern const f_string_t fake_make_parameter_variable_data_s;
  extern const f_string_t fake_make_parameter_variable_define_s;
  extern const f_string_t fake_make_parameter_variable_fakefile_s;
  extern const f_string_t fake_make_parameter_variable_mode_s;
  extern const f_string_t fake_make_parameter_variable_process_s;
  extern const f_string_t fake_make_parameter_variable_return_s;
  extern const f_string_t fake_make_parameter_variable_settings_s;
  extern const f_string_t fake_make_parameter_variable_sources_s;
  extern const f_string_t fake_make_parameter_variable_verbosity_s;
  extern const f_string_t fake_make_parameter_variable_work_s;

  extern const f_string_t fake_make_parameter_variable_option_build_s;
  extern const f_string_t fake_make_parameter_variable_option_color_s;
  extern const f_string_t fake_make_parameter_variable_option_data_s;
  extern const f_string_t fake_make_parameter_variable_option_define_s;
  extern const f_string_t fake_make_parameter_variable_option_fakefile_s;
  extern const f_string_t fake_make_parameter_variable_option_mode_s;
  extern const f_string_t fake_make_parameter_variable_option_process_s;
  extern const f_string_t fake_make_parameter_variable_option_return_s;
  extern const f_string_t fake_make_parameter_variable_option_settings_s;
  extern const f_string_t fake_make_parameter_variable_option_sources_s;
  extern const f_string_t fake_make_parameter_variable_option_verbosity_s;
  extern const f_string_t fake_make_parameter_variable_option_work_s;

  extern const f_string_t fake_make_parameter_variable_value_build_s;
  extern const f_string_t fake_make_parameter_variable_value_color_s;
  extern const f_string_t fake_make_parameter_variable_value_data_s;
  extern const f_string_t fake_make_parameter_variable_value_define_s;
  extern const f_string_t fake_make_parameter_variable_value_fakefile_s;
  extern const f_string_t fake_make_parameter_variable_value_mode_s;
  extern const f_string_t fake_make_parameter_variable_value_process_s;
  extern const f_string_t fake_make_parameter_variable_value_return_s;
  extern const f_string_t fake_make_parameter_variable_value_settings_s;
  extern const f_string_t fake_make_parameter_variable_value_sources_s;
  extern const f_string_t fake_make_parameter_variable_value_verbosity_s;
  extern const f_string_t fake_make_parameter_variable_value_work_s;

  typedef struct {
    f_string_dynamics_t build;
    f_string_dynamics_t color;
    f_string_dynamics_t data;
    f_string_dynamics_t define;
    f_string_dynamics_t fakefile;
    f_string_dynamics_t mode;
    f_string_dynamics_t process;
    f_string_dynamics_t settings;
    f_string_dynamics_t sources;
    f_string_dynamics_t verbosity;
    f_string_dynamics_t work;
  } fake_make_parameter_t;

  #define fake_make_parameter_t_initialize { \
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

  #define macro_fake_make_parameter_delete_simple(parameter) \
    macro_f_string_dynamics_t_delete_simple(parameter.build) \
    macro_f_string_dynamics_t_delete_simple(parameter.color) \
    macro_f_string_dynamics_t_delete_simple(parameter.data) \
    macro_f_string_dynamics_t_delete_simple(parameter.define) \
    macro_f_string_dynamics_t_delete_simple(parameter.fakefile) \
    macro_f_string_dynamics_t_delete_simple(parameter.mode) \
    macro_f_string_dynamics_t_delete_simple(parameter.process) \
    macro_f_string_dynamics_t_delete_simple(parameter.settings) \
    macro_f_string_dynamics_t_delete_simple(parameter.sources) \
    macro_f_string_dynamics_t_delete_simple(parameter.verbosity) \
    macro_f_string_dynamics_t_delete_simple(parameter.work)
#endif // _di_fake_make_parameter_t_

#ifndef _di_fake_make_path_t_
  typedef struct {
    f_file_t top;

    f_string_dynamics_t stack;
  } fake_make_path_t;

  #define fake_make_path_t_initialize { \
    f_file_t_initialize, \
    f_string_dynamics_t_initialize, \
  }

  #define macro_fake_make_path_delete_simple(path) \
    macro_f_string_dynamics_t_delete_simple(path.stack);
#endif // _di_fake_make_path_t_

#ifndef _di_fake_make_data_t_
  typedef struct {
    fake_build_setting_t setting_build;
    fake_make_setting_t setting_make;

    f_string_maps_t environment;

    fake_make_parameter_t parameter;
    fake_make_parameter_t parameter_option;
    fake_make_parameter_t parameter_value;
    fake_make_path_t path;

    fl_print_t error;

    f_fss_nameds_t fakefile;

    f_string_dynamic_t buffer;
    f_string_dynamic_t path_cache;

    f_array_length_t main;
  } fake_make_data_t;

  #define fake_make_data_t_initialize { \
    fake_build_setting_t_initialize, \
    fake_make_setting_t_initialize, \
    f_string_maps_t_initialize, \
    fake_make_parameter_t_initialize, \
    fake_make_parameter_t_initialize, \
    fake_make_parameter_t_initialize, \
    fake_make_path_t_initialize, \
    fl_print_t_initialize, \
    f_fss_nameds_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    0, \
  }

  #define macro_fake_make_data_t_delete_simple(structure) \
    macro_fake_build_setting_t_delete_simple(structure.setting_build) \
    macro_fake_make_setting_t_delete_simple(structure.setting_make) \
    macro_f_string_maps_t_delete_simple(structure.environment) \
    macro_fake_make_parameter_delete_simple(structure.parameter) \
    macro_fake_make_parameter_delete_simple(structure.parameter_option) \
    macro_fake_make_parameter_delete_simple(structure.parameter_value) \
    macro_fake_make_path_delete_simple(structure.path) \
    macro_f_fss_nameds_t_delete_simple(structure.fakefile) \
    macro_f_string_dynamic_t_delete_simple(structure.buffer) \
    macro_f_string_dynamic_t_delete_simple(structure.path_cache)
#endif // _di_fake_make_data_t_

/**
 * A structure for managing the operation and if-condition states.
 *
 * block:              The operation type representing the block (either "if" or "else").
 * block_result:       The result of the block.
 * condition:          The current if-condition type.
 * condition_result:   The result of the currently processed condition.
 * operation:          The current operation type.
 * operation_previous: The previous operation type.
 */
#ifndef _di_fake_state_process_t_
  typedef struct {
    uint8_t block;
    uint8_t block_result;
    uint8_t condition;
    uint8_t condition_result;
    uint8_t operation;
    uint8_t operation_previous;
  } fake_state_process_t;

  #define fake_state_process_t_initialize { \
    0, \
    0, \
    0, \
    0, \
    0, \
    0, \
  }
#endif // _di_fake_state_process_t_

/**
 * Designate that the if state is true, false, or undefined (none).
 *
 * fake_condition_result_*:
 * - none:  The result of the if-condition is not set.
 * - false: The result of the if-condition is false.
 * - true:  The result of the if-condition is true.
 * - done:  The if-condition is done and should no longer be processed.
 */
#ifndef _di_fake_condition_result_
  enum {
    fake_condition_result_none = 0,
    fake_condition_result_false,
    fake_condition_result_true,
    fake_condition_result_done,
  };
#endif // _di_fake_condition_result_

#ifndef _di_fake_skeleton_content_
  #define FAKE_make_skeleton_content_defines_s      "# fss-0000\n\n"
  #define FAKE_make_skeleton_content_dependencies_s "# fss-0000\n\n"
  #define FAKE_make_skeleton_content_fakefile_s     "# fss-0005 iki-0002\n\nsettings:\n  fail exit\n\nmain:\n\n"
  #define FAKE_make_skeleton_content_settings_s     "# fss-0001\n\n"

  #define fake_make_skeleton_content_defines_s_length      12
  #define fake_make_skeleton_content_dependencies_s_length 12
  #define fake_make_skeleton_content_fakefile_s_length     51
  #define fake_make_skeleton_content_settings_s_length     12

  extern const f_string_t fake_make_skeleton_content_defines_s;
  extern const f_string_t fake_make_skeleton_content_dependencies_s;
  extern const f_string_t fake_make_skeleton_content_fakefile_s;
  extern const f_string_t fake_make_skeleton_content_settings_s;
#endif // _di_fake_skeleton_content_

/**
 * Check to see if a process signal is received.
 *
 * Only signals that are blocked via main.signal will be received.
 *
 * @param main
 *   The main program data.
 *
 * @return
 *   A positive number representing a valid signal on signal received.
 *   F_false on no signal received.
 *
 * @see f_signal_read()
 */
#ifndef _di_fake_signal_received_
  extern f_status_t fake_signal_received(fake_main_t * const main) F_attribute_visibility_internal_d;
#endif // _di_fake_signal_received_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_h
