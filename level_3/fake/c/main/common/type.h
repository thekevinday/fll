/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides common type functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_common_type_h
#define _fake_common_type_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A structure for managing the operation and if-condition states.
 *
 * block:              The process block state.
 * block_result:       The result of the block.
 * condition:          The current if-condition type.
 * condition_result:   The result of the currently processed condition.
 * operation:          The current operation type.
 * operation_previous: The previous operation type.
 * success:            Current state is considered success when F_true and failure when F_false.
 * success_block:      Current block state is considered success when F_true and failure when F_false.
 */
#ifndef _di_fake_state_process_t_
  typedef struct {
    uint8_t block;
    uint8_t block_result;
    uint8_t condition;
    uint8_t condition_result;
    uint8_t operation;
    uint8_t operation_previous;
    uint8_t success;
    uint8_t success_block;
  } fake_state_process_t;

  #define fake_state_process_t_initialize { \
    0, \
    0, \
    0, \
    0, \
    0, \
    0, \
    F_true, \
    F_true, \
  }
#endif // _di_fake_state_process_t_

/**
 * The fake main program settings.
 *
 * This is passed to the program-specific main entry point to designate program settings.
 * These program settings are often processed from the program arguments (often called the command line arguments).
 *
 * flag: Flags passed to the main function.
 *
 * state:  The state data used when processing the FSS data.
 *
 * line_first: A string expected to represent either "\n" or NULL to allow for easy handling of when to print first new line or not.
 * line_last:  A string expected to represent either "\n" or NULL to allow for easy handling of when to print last new line or not.
 *
 * build:    The build directory.
 * data:     The data directory.
 * fakefile: The fakefile file path.
 * process:  The process name.
 * settings: The settings file path.
 * sources:  The sources directory.
 * work:     The work directory.

 * defines: The define data.
 * modes:   The mode data.
 *
 * operations: The operations, in the order in which they are given.
 */
#ifndef _di_fake_setting_t_
  typedef struct {
    uint32_t flag;

    f_state_t state;

    f_string_static_t line_first;
    f_string_static_t line_last;

    f_string_dynamic_t build;
    f_string_dynamic_t data;
    f_string_dynamic_t documents;
    f_string_dynamic_t fakefile;
    f_string_dynamic_t licenses;
    f_string_dynamic_t process;
    f_string_dynamic_t settings;
    f_string_dynamic_t sources;
    f_string_dynamic_t work;

    f_string_dynamics_t defines;
    f_string_dynamics_t modes;

    f_uint8s_t operations;
  } fake_setting_t;

  #define fake_setting_t_initialize \
    { \
      fake_main_flag_print_first_e, \
      f_state_t_initialize, \
      f_string_static_t_initialize, \
      f_string_static_t_initialize, \
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
      f_uint8s_t_initialize, \
    }
#endif // _di_fake_setting_t_

/**
 * The program data.
 *
 * operation: A code representing the currrent operation.
 *
 * main:    The main program data.
 * setting: The settings data.
 *
 * path_build:                  The build path.
 * path_build_documentation:    The build documentation path.
 * path_build_documents:        The build documents path.
 * path_build_includes:         The build includes path.
 * path_build_libraries:        The build libraries path.
 * path_build_libraries_script: The build libraries_script path.
 * path_build_libraries_shared: The build libraries_shared path.
 * path_build_libraries_static: The build libraries_static path.
 * path_build_objects:          The build objects path.
 * path_build_objects_script:   The build objects_script path.
 * path_build_objects_shared:   The build objects_shared path.
 * path_build_objects_static:   The build objects_static path.
 * path_build_programs:         The build programs path.
 * path_build_programs_script:  The build programs_script path.
 * path_build_programs_shared:  The build programs_shared path.
 * path_build_programs_static:  The build programs_static path.
 * path_build_settings:         The build settings path.
 * path_build_stage:            The build stage path.
 *
 * path_data_build:         The build data path.
 * path_data_documentation: The documentation data path.
 * path_data_settings:      The settings data path.
 *
 * path_documents: The documents path.
 * path_licenses:  The licenses path.
 * path_sources:   The sources path.
 *
 * path_work_includes:         The includes work path.
 * path_work_libraries:        The libraries work path.
 * path_work_libraries_script: The libraries_script work path.
 * path_work_libraries_shared: The libraries_shared work path.
 * path_work_libraries_static: The libraries_static work path.
 * path_work_programs:         The programs work path.
 * path_work_programs_script:  The programs_script work path.
 * path_work_programs_shared:  The programs_shared work path.
 * path_work_programs_static:  The programs_static work path.
 *
 * file_data_build_defines:      The defines build file data.
 * file_data_build_dependencies: The dependencies build file data.
 * file_data_build_fakefile:     The fakefile build file data.
 * file_data_build_process_post: The process_post_s build file data.
 * file_data_build_process_pre:  The process_pre_s build file data.
 * file_data_build_settings:     The settings build file data.
 *
 * file_documents_readme: The documents readme file data.
 */
#ifndef _di_fake_data_t_
  typedef struct {
    uint8_t operation;

    fll_program_data_t *main;
    fake_setting_t *setting;

    f_string_dynamic_t path_build;
    f_string_dynamic_t path_build_documentation;
    f_string_dynamic_t path_build_documents;
    f_string_dynamic_t path_build_includes;
    f_string_dynamic_t path_build_libraries;
    f_string_dynamic_t path_build_libraries_script;
    f_string_dynamic_t path_build_libraries_shared;
    f_string_dynamic_t path_build_libraries_static;
    f_string_dynamic_t path_build_objects;
    f_string_dynamic_t path_build_objects_script;
    f_string_dynamic_t path_build_objects_shared;
    f_string_dynamic_t path_build_objects_static;
    f_string_dynamic_t path_build_programs;
    f_string_dynamic_t path_build_programs_script;
    f_string_dynamic_t path_build_programs_shared;
    f_string_dynamic_t path_build_programs_static;
    f_string_dynamic_t path_build_settings;
    f_string_dynamic_t path_build_stage;

    f_string_dynamic_t path_data_build;
    f_string_dynamic_t path_data_documentation;
    f_string_dynamic_t path_data_settings;

    f_string_dynamic_t path_documents; // @todo: make this a settings configurable parameter, moving it to fake_setting_t.

    f_string_dynamic_t path_licenses; // @todo: make this a settings configurable parameter, moving it to fake_setting_t.

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
    f_string_dynamic_t file_data_build_process_post;
    f_string_dynamic_t file_data_build_process_pre;
    f_string_dynamic_t file_data_build_settings;

    f_string_dynamic_t file_documents_readme;
  } fake_data_t;

  #define fake_data_t_initialize \
    { \
      0, \
      0, \
      0, \
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
    }
#endif // _di_fake_main_t_

/**
 * Build settings data.
 *
 * flag: Flags from data_build_setting_* (Not strictly part of the build settings file).
 *
 * build_language: The build_language setting.
 *
 * version_file:   The version_file setting.
 * version_target: The version_target setting.
 *
 * build_script: The build_script setting.
 * build_shared: The build_shared setting.
 * build_static: The build_static setting.
 *
 * has_path_standard:     The has_path_standard setting.
 * preserve_path_headers: The preserve_path_headers setting.
 *
 * search_exclusive: The search_exclusive setting.
 * search_shared:    The search_shared setting.
 * search_static:    The search_static setting.
 *
 * build_compiler:              The build_compiler setting.
 * build_indexer:               The build_indexer setting.
 * build_name:                  The build_name setting.
 * build_sources_object:        The build_sources_object setting.
 * build_sources_object_shared: The build_sources_object_shared setting.
 * build_sources_object_static: The build_sources_object_static setting.
 * path_headers:                The path_headers setting.
 * path_language:               The path_language setting.
 * path_library_script:         The path_library_script setting.
 * path_library_shared:         The path_library_shared setting.
 * path_library_static:         The path_library_static setting.
 * path_object_script:          The path_object_script setting.
 * path_object_shared:          The path_object_shared setting.
 * path_object_static:          The path_object_static setting.
 * path_program_script:         The path_program_script setting.
 * path_program_shared:         The path_program_shared setting.
 * path_program_static:         The path_program_static setting.
 * path_sources:                The path_sources setting.
 * path_sources_object:         The path_sources_object setting.
 * process_post:                The process_post setting.
 * process_pre:                 The process_pre setting.
 * version_major:               The version_major setting.
 * version_major_prefix:        The version_major_prefix setting.
 * version_micro:               The version_micro setting.
 * version_micro_prefix:        The version_micro_prefix setting.
 * version_minor:               The version_minor setting.
 * version_minor_prefix:        The version_minor_prefix setting.
 * version_nano:                The version_nano setting.
 * version_nano_prefix:         The version_nano_prefix setting.
 *
 * build_indexer_arguments:      The build_indexer_arguments setting.
 * build_libraries:              The build_libraries setting.
 * build_libraries_shared:       The build_libraries_shared setting.
 * build_libraries_static:       The build_libraries_static setting.
 * build_objects_library:        The build_objects_library setting.
 * build_objects_library_shared: The build_objects_library_shared setting.
 * build_objects_library_static: The build_objects_library_static setting.
 * build_objects_program:        The build_objects_program setting.
 * build_objects_program_shared: The build_objects_program_shared setting.
 * build_objects_program_static: The build_objects_program_static setting.
 * build_sources_documentation:  The build_sources_documentation setting.
 * build_sources_headers:        The build_sources_headers setting.
 * build_sources_headers_shared: The build_sources_headers_shared setting.
 * build_sources_headers_static: The build_sources_headers_static setting.
 * build_sources_library:        The build_sources_library setting.
 * build_sources_library_shared: The build_sources_library_shared setting.
 * build_sources_library_static: The build_sources_library_static setting.
 * build_sources_program:        The build_sources_program setting.
 * build_sources_program_shared: The build_sources_program_shared setting.
 * build_sources_program_static: The build_sources_program_static setting.
 * build_sources_script:         The build_sources_script setting.
 * build_sources_setting:        The build_sources_setting setting.
 * defines:                      The defines setting.
 * defines_library:              The defines_library setting.
 * defines_library_shared:       The defines_library_shared setting.
 * defines_library_static:       The defines_library_static setting.
 * defines_object:               The defines_object setting.
 * defines_object_shared:        The defines_object_shared setting.
 * defines_object_static:        The defines_object_static setting.
 * defines_program:              The defines_program setting.
 * defines_program_shared:       The defines_program_shared setting.
 * defines_program_static:       The defines_program_static setting.
 * defines_shared:               The defines_shared setting.
 * defines_static:               The defines_static setting.
 * environment:                  The environment setting.
 * flags:                        The flags setting.
 * flags_library:                The flags_library setting.
 * flags_library_shared:         The flags_library_shared setting.
 * flags_library_static:         The flags_library_static setting.
 * flags_object:                 The flags_object setting.
 * flags_object_shared:          The flags_object_shared setting.
 * flags_object_static:          The flags_object_static setting.
 * flags_program:                The flags_program setting.
 * flags_program_shared:         The flags_program_shared setting.
 * flags_program_static:         The flags_program_static setting.
 * flags_shared:                 The flags_shared setting.
 * flags_static:                 The flags_static setting.
 * modes:                        The modes setting.
 * modes_default:                The modes_default setting.
 */
#ifndef _di_fake_build_setting_t_
  typedef struct {
    uint8_t flag;

    uint8_t build_language;

    uint8_t version_file;
    uint8_t version_target;

    bool build_script;
    bool build_shared;
    bool build_static;

    bool has_path_standard;
    bool preserve_path_headers;

    bool search_exclusive;
    bool search_shared;
    bool search_static;

    f_string_dynamic_t build_compiler;
    f_string_dynamic_t build_indexer;
    f_string_dynamic_t build_name;
    f_string_dynamic_t build_sources_object;
    f_string_dynamic_t build_sources_object_shared;
    f_string_dynamic_t build_sources_object_static;
    f_string_dynamic_t path_headers;
    f_string_dynamic_t path_language;
    f_string_dynamic_t path_library_script;
    f_string_dynamic_t path_library_shared;
    f_string_dynamic_t path_library_static;
    f_string_dynamic_t path_object_script;
    f_string_dynamic_t path_object_shared;
    f_string_dynamic_t path_object_static;
    f_string_dynamic_t path_program_script;
    f_string_dynamic_t path_program_shared;
    f_string_dynamic_t path_program_static;
    f_string_dynamic_t path_sources;
    f_string_dynamic_t path_sources_object;
    f_string_dynamic_t process_post;
    f_string_dynamic_t process_pre;
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
    f_string_dynamics_t build_objects_library;
    f_string_dynamics_t build_objects_library_shared;
    f_string_dynamics_t build_objects_library_static;
    f_string_dynamics_t build_objects_program;
    f_string_dynamics_t build_objects_program_shared;
    f_string_dynamics_t build_objects_program_static;
    f_string_dynamics_t build_sources_documentation;
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
    f_string_dynamics_t defines_object;
    f_string_dynamics_t defines_object_shared;
    f_string_dynamics_t defines_object_static;
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
    f_string_dynamics_t flags_object;
    f_string_dynamics_t flags_object_shared;
    f_string_dynamics_t flags_object_static;
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
    macro_f_string_dynamic_t_delete_simple(setting.build_name) \
    macro_f_string_dynamic_t_delete_simple(setting.build_sources_object) \
    macro_f_string_dynamic_t_delete_simple(setting.build_sources_object_shared) \
    macro_f_string_dynamic_t_delete_simple(setting.build_sources_object_static) \
    macro_f_string_dynamic_t_delete_simple(setting.path_headers) \
    macro_f_string_dynamic_t_delete_simple(setting.path_language) \
    macro_f_string_dynamic_t_delete_simple(setting.path_library_script) \
    macro_f_string_dynamic_t_delete_simple(setting.path_library_shared) \
    macro_f_string_dynamic_t_delete_simple(setting.path_library_static) \
    macro_f_string_dynamic_t_delete_simple(setting.path_object_script) \
    macro_f_string_dynamic_t_delete_simple(setting.path_object_shared) \
    macro_f_string_dynamic_t_delete_simple(setting.path_object_static) \
    macro_f_string_dynamic_t_delete_simple(setting.path_program_script) \
    macro_f_string_dynamic_t_delete_simple(setting.path_program_shared) \
    macro_f_string_dynamic_t_delete_simple(setting.path_program_static) \
    macro_f_string_dynamic_t_delete_simple(setting.path_sources) \
    macro_f_string_dynamic_t_delete_simple(setting.path_sources_object) \
    macro_f_string_dynamic_t_delete_simple(setting.process_post) \
    macro_f_string_dynamic_t_delete_simple(setting.process_pre) \
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
    macro_f_string_dynamics_t_delete_simple(setting.build_objects_library) \
    macro_f_string_dynamics_t_delete_simple(setting.build_objects_library_shared) \
    macro_f_string_dynamics_t_delete_simple(setting.build_objects_library_static) \
    macro_f_string_dynamics_t_delete_simple(setting.build_objects_program) \
    macro_f_string_dynamics_t_delete_simple(setting.build_objects_program_shared) \
    macro_f_string_dynamics_t_delete_simple(setting.build_objects_program_static) \
    macro_f_string_dynamics_t_delete_simple(setting.build_sources_documentation) \
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
    macro_f_string_dynamics_t_delete_simple(setting.defines_object) \
    macro_f_string_dynamics_t_delete_simple(setting.defines_object_shared) \
    macro_f_string_dynamics_t_delete_simple(setting.defines_object_static) \
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
    macro_f_string_dynamics_t_delete_simple(setting.flags_object) \
    macro_f_string_dynamics_t_delete_simple(setting.flags_object_shared) \
    macro_f_string_dynamics_t_delete_simple(setting.flags_object_static) \
    macro_f_string_dynamics_t_delete_simple(setting.flags_program) \
    macro_f_string_dynamics_t_delete_simple(setting.flags_program_shared) \
    macro_f_string_dynamics_t_delete_simple(setting.flags_program_static) \
    macro_f_string_dynamics_t_delete_simple(setting.flags_shared) \
    macro_f_string_dynamics_t_delete_simple(setting.flags_static) \
    macro_f_string_dynamics_t_delete_simple(setting.modes) \
    macro_f_string_dynamics_t_delete_simple(setting.modes_default)

  #define fake_build_setting_total_d 89
#endif // _di_fake_build_setting_t_

#ifndef _di_fake_build_stage_t_
  typedef struct {
    f_string_dynamic_t file_library_script;
    f_string_dynamic_t file_library_shared;
    f_string_dynamic_t file_library_static;
    f_string_dynamic_t file_object_script;
    f_string_dynamic_t file_object_shared;
    f_string_dynamic_t file_object_static;
    f_string_dynamic_t file_objects_static;
    f_string_dynamic_t file_process_post;
    f_string_dynamic_t file_process_pre;
    f_string_dynamic_t file_program_script;
    f_string_dynamic_t file_program_shared;
    f_string_dynamic_t file_program_static;
    f_string_dynamic_t file_skeleton;
    f_string_dynamic_t file_sources_documentation;
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
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
  }

  #define fake_build_stage_total_d 17

  #define macro_fake_build_stage_t_delete_simple(stage) \
    macro_f_string_dynamic_t_delete_simple(stage.file_library_script) \
    macro_f_string_dynamic_t_delete_simple(stage.file_library_shared) \
    macro_f_string_dynamic_t_delete_simple(stage.file_library_static) \
    macro_f_string_dynamic_t_delete_simple(stage.file_object_script) \
    macro_f_string_dynamic_t_delete_simple(stage.file_object_shared) \
    macro_f_string_dynamic_t_delete_simple(stage.file_object_static) \
    macro_f_string_dynamic_t_delete_simple(stage.file_objects_static) \
    macro_f_string_dynamic_t_delete_simple(stage.file_process_post) \
    macro_f_string_dynamic_t_delete_simple(stage.file_process_pre) \
    macro_f_string_dynamic_t_delete_simple(stage.file_program_script) \
    macro_f_string_dynamic_t_delete_simple(stage.file_program_shared) \
    macro_f_string_dynamic_t_delete_simple(stage.file_program_static) \
    macro_f_string_dynamic_t_delete_simple(stage.file_skeleton) \
    macro_f_string_dynamic_t_delete_simple(stage.file_sources_documentation) \
    macro_f_string_dynamic_t_delete_simple(stage.file_sources_headers) \
    macro_f_string_dynamic_t_delete_simple(stage.file_sources_script) \
    macro_f_string_dynamic_t_delete_simple(stage.file_sources_settings)
#endif // _di_fake_build_stage_t_

/**
 * The build data.
 *
 * setting:     The build settings.
 * environment: The environment variables.
 */
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
#endif // _di_fake_make_setting_t_

#ifndef _di_fake_make_parameter_t_
  typedef struct {
    f_string_dynamics_t build;
    f_string_dynamics_t color;
    f_string_dynamics_t data;
    f_string_dynamics_t define;
    f_string_dynamics_t documents;
    f_string_dynamics_t fakefile;
    f_string_dynamics_t licenses;
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
    f_string_dynamics_t_initialize, \
    f_string_dynamics_t_initialize, \
  }

  #define macro_fake_make_parameter_delete_simple(parameter) \
    macro_f_string_dynamics_t_delete_simple(parameter.build) \
    macro_f_string_dynamics_t_delete_simple(parameter.color) \
    macro_f_string_dynamics_t_delete_simple(parameter.data) \
    macro_f_string_dynamics_t_delete_simple(parameter.define) \
    macro_f_string_dynamics_t_delete_simple(parameter.documents) \
    macro_f_string_dynamics_t_delete_simple(parameter.fakefile) \
    macro_f_string_dynamics_t_delete_simple(parameter.licenses) \
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

/**
 * The control data.
 *
 * setting_build:    The build settings.
 * setting_make:     The make settings.
 * environment:      All environment variables allowed to be exposed to the when processing.
 * parameter:        A set of parameters available for IKI substitution.
 * parameter_option: A set of parameters available for IKI option substitution.
 * parameter_value:  A set of parameters available for IKI value substitution.
 * path:             The path to the Fakefile.
 * error:            The error output print structure.
 * fakefile:         The loaded Fakefile.
 * buffer:           A buffer used during processing.
 * cache_1:          An additional buffer for caching purposes.
 * cache_2:          An additional buffer for caching purposes.
 * cache_path:       A buffer for path-specific caching.
 * cache_arguments:  A cache for expanded arguments.
 * cache_iki:        A cache for IKI data.
 * id_main:          Index of the "main" Section.
 * main:             The main program data.
 * data:             The Fake make program data.
 * setting:          The settings data.
 */
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
    f_string_dynamic_t cache_1;
    f_string_dynamic_t cache_2;
    f_string_dynamic_t cache_path;
    f_string_dynamics_t cache_arguments;
    f_iki_data_t cache_iki;

    f_array_length_t id_main;

    fll_program_data_t *main;
    fake_data_t *data;
    fake_setting_t *setting;
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
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamics_t_initialize, \
    f_iki_data_t_initialize, \
    0, \
    0, \
    0, \
    0, \
  }
#endif // _di_fake_make_data_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_common_type_h
