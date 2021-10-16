/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.5
 * Licenses: lgplv2.1
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

    f_string_dynamics_t build_libraries;
    f_string_dynamics_t build_sources_headers;
    f_string_dynamics_t build_sources_library;
    f_string_dynamics_t build_sources_program;
    f_string_dynamics_t build_sources_script;
    f_string_dynamics_t build_sources_setting;
    f_string_dynamics_t defines_all;
    f_string_dynamics_t defines_library;
    f_string_dynamics_t defines_program;
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
  }

  #define macro_fake_build_setting_t_delete_simple(setting) \
    macro_f_string_dynamic_t_delete_simple(setting.build_compiler); \
    macro_f_string_dynamic_t_delete_simple(setting.build_indexer); \
    macro_f_string_dynamic_t_delete_simple(setting.path_headers); \
    macro_f_string_dynamic_t_delete_simple(setting.path_language); \
    macro_f_string_dynamic_t_delete_simple(setting.path_library_script); \
    macro_f_string_dynamic_t_delete_simple(setting.path_library_shared); \
    macro_f_string_dynamic_t_delete_simple(setting.path_library_static); \
    macro_f_string_dynamic_t_delete_simple(setting.path_program_script); \
    macro_f_string_dynamic_t_delete_simple(setting.path_program_shared); \
    macro_f_string_dynamic_t_delete_simple(setting.path_program_static); \
    macro_f_string_dynamic_t_delete_simple(setting.path_sources); \
    macro_f_string_dynamic_t_delete_simple(setting.process_post); \
    macro_f_string_dynamic_t_delete_simple(setting.process_pre); \
    macro_f_string_dynamic_t_delete_simple(setting.project_name); \
    macro_f_string_dynamic_t_delete_simple(setting.version_major); \
    macro_f_string_dynamic_t_delete_simple(setting.version_major_prefix); \
    macro_f_string_dynamic_t_delete_simple(setting.version_micro); \
    macro_f_string_dynamic_t_delete_simple(setting.version_micro_prefix); \
    macro_f_string_dynamic_t_delete_simple(setting.version_minor); \
    macro_f_string_dynamic_t_delete_simple(setting.version_minor_prefix); \
    macro_f_string_dynamic_t_delete_simple(setting.version_nano); \
    macro_f_string_dynamic_t_delete_simple(setting.version_nano_prefix); \
    macro_f_string_dynamics_t_delete_simple(setting.build_libraries); \
    macro_f_string_dynamics_t_delete_simple(setting.build_sources_headers); \
    macro_f_string_dynamics_t_delete_simple(setting.build_sources_library); \
    macro_f_string_dynamics_t_delete_simple(setting.build_sources_program); \
    macro_f_string_dynamics_t_delete_simple(setting.build_sources_script); \
    macro_f_string_dynamics_t_delete_simple(setting.build_sources_setting); \
    macro_f_string_dynamics_t_delete_simple(setting.defines_all); \
    macro_f_string_dynamics_t_delete_simple(setting.defines_library); \
    macro_f_string_dynamics_t_delete_simple(setting.defines_program); \
    macro_f_string_dynamics_t_delete_simple(setting.defines_shared); \
    macro_f_string_dynamics_t_delete_simple(setting.defines_static); \
    macro_f_string_dynamics_t_delete_simple(setting.environment); \
    macro_f_string_dynamics_t_delete_simple(setting.flags_all); \
    macro_f_string_dynamics_t_delete_simple(setting.flags_library); \
    macro_f_string_dynamics_t_delete_simple(setting.flags_program); \
    macro_f_string_dynamics_t_delete_simple(setting.flags_shared); \
    macro_f_string_dynamics_t_delete_simple(setting.flags_static); \
    macro_f_string_dynamics_t_delete_simple(setting.modes); \
    macro_f_string_dynamics_t_delete_simple(setting.modes_default);

  #define fake_build_setting_name_build_compiler         "build_compiler"
  #define fake_build_setting_name_build_language         "build_language"
  #define fake_build_setting_name_build_libraries        "build_libraries"
  #define fake_build_setting_name_build_indexer          "build_indexer"
  #define fake_build_setting_name_build_script           "build_script"
  #define fake_build_setting_name_build_shared           "build_shared"
  #define fake_build_setting_name_build_sources_headers  "build_sources_headers"
  #define fake_build_setting_name_build_sources_library  "build_sources_library"
  #define fake_build_setting_name_build_sources_program  "build_sources_program"
  #define fake_build_setting_name_build_sources_script   "build_sources_script"
  #define fake_build_setting_name_build_sources_settings "build_sources_setting"
  #define fake_build_setting_name_build_static           "build_static"
  #define fake_build_setting_name_defines_all            "defines_all"
  #define fake_build_setting_name_defines_library        "defines_library"
  #define fake_build_setting_name_defines_program        "defines_program"
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
  #define fake_build_setting_name_version_file           "version_file"
  #define fake_build_setting_name_version_major          "version_major"
  #define fake_build_setting_name_version_major_prefix   "version_major_prefix"
  #define fake_build_setting_name_version_micro          "version_micro"
  #define fake_build_setting_name_version_micro_prefix   "version_micro_prefix"
  #define fake_build_setting_name_version_minor          "version_minor"
  #define fake_build_setting_name_version_minor_prefix   "version_minor_prefix"
  #define fake_build_setting_name_version_nano           "version_nano"
  #define fake_build_setting_name_version_nano_prefix    "version_nano_prefix"
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
  #define fake_build_setting_name_build_sources_script_length   20
  #define fake_build_setting_name_build_sources_settings_length 22
  #define fake_build_setting_name_build_static_length           12
  #define fake_build_setting_name_environment_length            11
  #define fake_build_setting_name_defines_all_length            11
  #define fake_build_setting_name_defines_library_length        15
  #define fake_build_setting_name_defines_program_length        15
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
  #define fake_build_setting_name_version_file_length           12
  #define fake_build_setting_name_version_major_length          13
  #define fake_build_setting_name_version_major_prefix_length   20
  #define fake_build_setting_name_version_micro_length          13
  #define fake_build_setting_name_version_micro_prefix_length   20
  #define fake_build_setting_name_version_minor_length          13
  #define fake_build_setting_name_version_minor_prefix_length   20
  #define fake_build_setting_name_version_nano_length           12
  #define fake_build_setting_name_version_nano_prefix_length    19
  #define fake_build_setting_name_version_target_length         14

  #define fake_build_setting_total 52

  #define fake_build_setting_default_version        "0"
  #define fake_build_setting_default_version_prefix "."

  #define fake_build_setting_default_version_length        1
  #define fake_build_setting_default_version_prefix_length 1
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

  #define macro_fake_build_stage_t_delete_simple(stage) \
    macro_f_string_dynamic_t_delete_simple(stage.file_libraries_script); \
    macro_f_string_dynamic_t_delete_simple(stage.file_libraries_shared); \
    macro_f_string_dynamic_t_delete_simple(stage.file_libraries_static); \
    macro_f_string_dynamic_t_delete_simple(stage.file_objects_static); \
    macro_f_string_dynamic_t_delete_simple(stage.file_process_post); \
    macro_f_string_dynamic_t_delete_simple(stage.file_process_pre); \
    macro_f_string_dynamic_t_delete_simple(stage.file_programs_script); \
    macro_f_string_dynamic_t_delete_simple(stage.file_programs_shared); \
    macro_f_string_dynamic_t_delete_simple(stage.file_programs_static); \
    macro_f_string_dynamic_t_delete_simple(stage.file_skeleton); \
    macro_f_string_dynamic_t_delete_simple(stage.file_sources_headers); \
    macro_f_string_dynamic_t_delete_simple(stage.file_sources_script); \
    macro_f_string_dynamic_t_delete_simple(stage.file_sources_settings);

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
  #define fake_build_parameter_library_include            "-I"
  #define fake_build_parameter_library_link_file          "-l"
  #define fake_build_parameter_library_link_path          "-L"
  #define fake_build_parameter_library_name_prefix        "lib"
  #define fake_build_parameter_library_name_suffix_shared ".so"
  #define fake_build_parameter_library_name_suffix_static ".a"
  #define fake_build_parameter_library_output             "-o"
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
 * Provide common/generic definitions.
 *
 * fake_common_allocation_*:
 *   - large: An allocation step used for buffers that are anticipated to have large buffers.
 *   - small: An allocation step used for buffers that are anticipated to have small buffers.
 */
#ifndef _di_fake_common_
  #define fake_common_allocation_large 256
  #define fake_common_allocation_small 16

  #define fake_common_initial_buffer_max 131072 // 128k max default initial buffer size.

  #define fake_common_setting_bool_yes "yes"
  #define fake_common_setting_bool_no  "no"

  #define fake_common_setting_bool_yes_length 3
  #define fake_common_setting_bool_no_length  2
#endif // _di_fake_common_

#ifndef _di_fake_make_section_
  #define fake_make_section_main     "main"
  #define fake_make_section_settings "settings"

  #define fake_make_section_main_length     4
  #define fake_make_section_settings_length 8

  #define fake_make_section_stack_max 8192 // maximum stack call depth.
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
#endif // _di_fake_make_setting_t_

#ifndef _di_fake_make_operation_
  #define fake_make_operation_break    "break"
  #define fake_make_operation_build    "build"
  #define fake_make_operation_clean    "clean"
  #define fake_make_operation_clone    "clone"
  #define fake_make_operation_compile  "compile"
  #define fake_make_operation_copy     "copy"
  #define fake_make_operation_define   "define"
  #define fake_make_operation_delete   "delete"
  #define fake_make_operation_deletes  "deletes"
  #define fake_make_operation_else     "else"
  #define fake_make_operation_exit     "exit"
  #define fake_make_operation_fail     "fail"
  #define fake_make_operation_group    "group"
  #define fake_make_operation_groups   "groups"
  #define fake_make_operation_if       "if"
  #define fake_make_operation_index    "index"
  #define fake_make_operation_link     "link"
  #define fake_make_operation_mode     "mode"
  #define fake_make_operation_modes    "modes"
  #define fake_make_operation_move     "move"
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

  #define fake_make_operation_break_length    5
  #define fake_make_operation_build_length    5
  #define fake_make_operation_clean_length    5
  #define fake_make_operation_clone_length    5
  #define fake_make_operation_compile_length  7
  #define fake_make_operation_copy_length     4
  #define fake_make_operation_define_length   6
  #define fake_make_operation_delete_length   6
  #define fake_make_operation_deletes_length  7
  #define fake_make_operation_else_length     4
  #define fake_make_operation_exit_length     4
  #define fake_make_operation_fail_length     4
  #define fake_make_operation_group_length    5
  #define fake_make_operation_groups_length   6
  #define fake_make_operation_if_length       2
  #define fake_make_operation_index_length    5
  #define fake_make_operation_link_length     4
  #define fake_make_operation_mode_length     4
  #define fake_make_operation_modes_length    5
  #define fake_make_operation_move_length     4
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
    fake_make_operation_type_break = 1,
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

  #define fake_make_operation_total 31

  #define fake_make_operation_argument_environment "environment"
  #define fake_make_operation_argument_failure     "failure"
  #define fake_make_operation_argument_file        "file"
  #define fake_make_operation_argument_directory   "directory"
  #define fake_make_operation_argument_error       "error"
  #define fake_make_operation_argument_exit        "exit"
  #define fake_make_operation_argument_has         "has"
  #define fake_make_operation_argument_ignore      "ignore"
  #define fake_make_operation_argument_is          "is"
  #define fake_make_operation_argument_parameter   "parameter"
  #define fake_make_operation_argument_point       "point"
  #define fake_make_operation_argument_recursive   "recursive"
  #define fake_make_operation_argument_success     "success"
  #define fake_make_operation_argument_target      "target"
  #define fake_make_operation_argument_warn        "warn"

  #define fake_make_operation_argument_environment_length 11
  #define fake_make_operation_argument_failure_length     7
  #define fake_make_operation_argument_file_length        4
  #define fake_make_operation_argument_directory_length   9
  #define fake_make_operation_argument_error_length       5
  #define fake_make_operation_argument_exit_length        4
  #define fake_make_operation_argument_has_length         3
  #define fake_make_operation_argument_ignore_length      6
  #define fake_make_operation_argument_is_length          2
  #define fake_make_operation_argument_parameter_length   9
  #define fake_make_operation_argument_point_length       5
  #define fake_make_operation_argument_recursive_length   9
  #define fake_make_operation_argument_success_length     7
  #define fake_make_operation_argument_target_length      6
  #define fake_make_operation_argument_warn_length        4

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
    fake_make_operation_if_type_else_false_next_always,
    fake_make_operation_if_type_else_true,
    fake_make_operation_if_type_else_true_next,
    fake_make_operation_if_type_false,
    fake_make_operation_if_type_false_always,
    fake_make_operation_if_type_false_always_next,
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

  #define fake_make_operation_recursion_depth_max 65535
#endif // _di_fake_make_operation_

#ifndef _di_fake_make_parameter_t_
  #define fake_make_parameter_variable_build     "build"
  #define fake_make_parameter_variable_color     "color"
  #define fake_make_parameter_variable_data      "data"
  #define fake_make_parameter_variable_define    "define"
  #define fake_make_parameter_variable_fakefile  "fakefile"
  #define fake_make_parameter_variable_mode      "mode"
  #define fake_make_parameter_variable_process   "process"
  #define fake_make_parameter_variable_return    "return"
  #define fake_make_parameter_variable_settings  "settings"
  #define fake_make_parameter_variable_sources   "sources"
  #define fake_make_parameter_variable_verbosity "verbosity"
  #define fake_make_parameter_variable_work      "work"

  #define fake_make_parameter_variable_build_length     5
  #define fake_make_parameter_variable_color_length     5
  #define fake_make_parameter_variable_data_length      4
  #define fake_make_parameter_variable_define_length    6
  #define fake_make_parameter_variable_fakefile_length  8
  #define fake_make_parameter_variable_mode_length      4
  #define fake_make_parameter_variable_process_length   7
  #define fake_make_parameter_variable_return_length    6
  #define fake_make_parameter_variable_settings_length  8
  #define fake_make_parameter_variable_sources_length   7
  #define fake_make_parameter_variable_verbosity_length 9
  #define fake_make_parameter_variable_work_length      4

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
    macro_f_string_dynamics_t_delete_simple(parameter.build); \
    macro_f_string_dynamics_t_delete_simple(parameter.color); \
    macro_f_string_dynamics_t_delete_simple(parameter.data); \
    macro_f_string_dynamics_t_delete_simple(parameter.define); \
    macro_f_string_dynamics_t_delete_simple(parameter.fakefile); \
    macro_f_string_dynamics_t_delete_simple(parameter.mode); \
    macro_f_string_dynamics_t_delete_simple(parameter.process); \
    macro_f_string_dynamics_t_delete_simple(parameter.settings); \
    macro_f_string_dynamics_t_delete_simple(parameter.sources); \
    macro_f_string_dynamics_t_delete_simple(parameter.verbosity); \
    macro_f_string_dynamics_t_delete_simple(parameter.work);
#endif // _di_fake_make_parameter_t_

#ifndef _di_fake_make_path_t_
  typedef struct {
    f_file_t top;
    f_file_t current;

    f_string_dynamics_t stack;
  } fake_make_path_t;

  #define fake_make_path_t_initialize { \
    f_file_t_initialize, \
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
    fake_make_path_t path; // @todo review this, check if path.current is used anymore.

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
    macro_f_string_maps_t_delete_simple(structure.environment); \
    macro_fake_make_parameter_delete_simple(structure.parameter) \
    macro_fake_make_path_delete_simple(structure.path) \
    macro_f_fss_nameds_t_delete_simple(structure.fakefile) \
    macro_f_string_dynamic_t_delete_simple(structure.buffer); \
    macro_f_string_dynamic_t_delete_simple(structure.path_cache);
#endif // _di_fake_make_data_t_

#ifndef _di_fake_skeleton_content_
  #define fake_make_skeleton_content_defines      "# fss-0000\n\n"
  #define fake_make_skeleton_content_dependencies "# fss-0000\n\n"
  #define fake_make_skeleton_content_fakefile     "# fss-0005 iki-0002\n\nsettings:\n  fail exit\n\nmain:\n\n"
  #define fake_make_skeleton_content_settings     "# fss-0001\n\n"

  #define fake_make_skeleton_content_defines_length      12
  #define fake_make_skeleton_content_dependencies_length 12
  #define fake_make_skeleton_content_fakefile_length     51
  #define fake_make_skeleton_content_settings_length     12
#endif // _di_fake_skeleton_content_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_h
