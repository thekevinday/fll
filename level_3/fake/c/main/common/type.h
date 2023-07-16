/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides common type structures.
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
 * Properties:
 *   - block:              The process block state.
 *   - block_result:       The result of the block.
 *   - condition:          The current if-condition type.
 *   - condition_result:   The result of the currently processed condition.
 *   - operation:          The current operation type.
 *   - operation_previous: The previous operation type.
 *   - success:            Current state is considered success when F_true and failure when F_false.
 *   - success_block:      Current block state is considered success when F_true and failure when F_false.
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
 * Properties:
 *   - flag: Flags passed to the main function.
 *
 *   - status_signal: A status used eclusively by the threaded signal handler.
 *   - state:         The state data used when processing the FSS data.
 *
 *   - build:    The build directory.
 *   - data:     The data directory.
 *   - fakefile: The fakefile file path.
 *   - process:  The process name.
 *   - settings: The settings file path.
 *   - sources:  The sources directory.
 *   - work:     The work directory.

 *   - defines: The define data.
 *   - modes:   The mode data.
 *
 *   - operations: The operations, in the order in which they are given.
 */
#ifndef _di_fake_setting_t_
  typedef struct {
    uint32_t flag;

    f_status_t status_signal;
    f_state_t state;

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
      0, \
      F_none, \
      f_state_t_initialize, \
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
 * The main program data as a single structure.
 *
 * program: The main program data.
 * setting: The settings data.
 *
 * Properties:
 *   - buffer:           A string buffer cache often used for files and often held longe than other caches.
 *   - cache_1:          A string cache.
 *   - cache_2:          A string cache.
 *   - cache_argument:   A string cache for some argument.
 *   - cache_argument:   A string cache for some path.
 *   - cache_arguments:  An array of strings cache for arguments.
 *   - cache_map:        A string map cache.
 *   - cache_iki:        IKI data cache.
 *   - cache_recurse_do: A cache for the directory recursion do function.
 */
#ifndef _di_fake_main_t_
  typedef struct {
    fll_program_data_t program;
    fake_setting_t setting;

    f_string_dynamic_t buffer;
    f_string_dynamic_t cache_1;
    f_string_dynamic_t cache_2;
    f_string_dynamic_t cache_argument;
    f_string_dynamics_t cache_arguments;
    f_string_map_t cache_map;
    f_iki_data_t cache_iki;
    f_directory_recurse_do_t cache_recurse_do;
  } fake_main_t;

  #define fake_main_t_initialize \
    { \
      fll_program_data_t_initialize, \
      fake_setting_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamics_t_initialize, \
      f_string_map_t_initialize, \
      f_iki_data_t_initialize, \
      f_directory_recurse_do_t_initialize, \
    }
#endif // _di_fake_main_t_

/**
 * The program data.
 *
 * Properties:
 *   - operation: A code representing the currrent operation.
 *
 *   - path_build:                  The build path.
 *   - path_build_documentation:    The build documentation path.
 *   - path_build_documents:        The build documents path.
 *   - path_build_includes:         The build includes path.
 *   - path_build_libraries:        The build libraries path.
 *   - path_build_libraries_script: The build libraries_script path.
 *   - path_build_libraries_shared: The build libraries_shared path.
 *   - path_build_libraries_static: The build libraries_static path.
 *   - path_build_objects:          The build objects path.
 *   - path_build_objects_script:   The build objects_script path.
 *   - path_build_objects_shared:   The build objects_shared path.
 *   - path_build_objects_static:   The build objects_static path.
 *   - path_build_programs:         The build programs path.
 *   - path_build_programs_script:  The build programs_script path.
 *   - path_build_programs_shared:  The build programs_shared path.
 *   - path_build_programs_static:  The build programs_static path.
 *   - path_build_settings:         The build settings path.
 *   - path_build_stage:            The build stage path.
 *
 *   - path_data_build:         The build data path.
 *   - path_data_documentation: The documentation data path.
 *   - path_data_settings:      The settings data path.
 *
 *   - path_documents: The documents path.
 *   - path_licenses:  The licenses path.
 *   - path_sources:   The sources path.
 *
 *   - path_work_includes:         The includes work path.
 *   - path_work_libraries:        The libraries work path.
 *   - path_work_libraries_script: The libraries_script work path.
 *   - path_work_libraries_shared: The libraries_shared work path.
 *   - path_work_libraries_static: The libraries_static work path.
 *   - path_work_programs:         The programs work path.
 *   - path_work_programs_script:  The programs_script work path.
 *   - path_work_programs_shared:  The programs_shared work path.
 *   - path_work_programs_static:  The programs_static work path.
 *
 *   - file_data_build_defines:      The defines build file data.
 *   - file_data_build_dependencies: The dependencies build file data.
 *   - file_data_build_fakefile:     The fakefile build file data.
 *   - file_data_build_process_post: The process_post_s build file data.
 *   - file_data_build_process_pre:  The process_pre_s build file data.
 *   - file_data_build_settings:     The settings build file data.
 *
 *   - file_documents_readme: The documents readme file data.
 *
 *   - main: The program and settings data.
 */
#ifndef _di_fake_data_t_
  typedef struct {
    uint8_t operation;

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

    fake_main_t *main;
  } fake_data_t;

  #define fake_data_t_initialize \
    { \
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
      0, \
    }
#endif // _di_fake_data_t_

/**
 * The program data for local operations so that custom data can be passed to functions.
 *
 * Properties:
 *   - main:     The program and settings data.
 *   - custom_1: Custom data that both the caller and the called function know to expect.
 *   - custom_2: Custom data that both the caller and the called function know to expect.
 */
#ifndef _di_fake_local_t_
  typedef struct {
    fake_main_t *main;
    void *custom_1;
    void *custom_2;
  } fake_local_t;

  #define fake_local_t_initialize \
    { \
      0, \
      0, \
      0, \
    }

  #define macro_fake_local_t_initialize_1(main, custom_1, custom_2) \
    { \
      main, \
      custom_1, \
      custom_2, \
    }
#endif // _di_fake_local_t_

/**
 * Build settings data.
 *
 * Properties:
 *   - flag: Flags from data_build_setting_* (Not strictly part of the build settings file).
 *
 *   - build_language: The build_language setting.
 *
 *   - version_file:   The version_file setting.
 *   - version_target: The version_target setting.
 *
 *   - build_script: The build_script setting.
 *   - build_shared: The build_shared setting.
 *   - build_static: The build_static setting.
 *
 *   - has_path_standard:     The has_path_standard setting.
 *   - preserve_path_headers: The preserve_path_headers setting.
 *
 *   - search_exclusive: The search_exclusive setting.
 *   - search_shared:    The search_shared setting.
 *   - search_static:    The search_static setting.
 *
 *   - build_compiler:              The build_compiler setting.
 *   - build_indexer:               The build_indexer setting.
 *   - build_name:                  The build_name setting.
 *   - build_sources_object:        The build_sources_object setting.
 *   - build_sources_object_shared: The build_sources_object_shared setting.
 *   - build_sources_object_static: The build_sources_object_static setting.
 *   - path_headers:                The path_headers setting.
 *   - path_language:               The path_language setting.
 *   - path_library_script:         The path_library_script setting.
 *   - path_library_shared:         The path_library_shared setting.
 *   - path_library_static:         The path_library_static setting.
 *   - path_object_script:          The path_object_script setting.
 *   - path_object_shared:          The path_object_shared setting.
 *   - path_object_static:          The path_object_static setting.
 *   - path_program_script:         The path_program_script setting.
 *   - path_program_shared:         The path_program_shared setting.
 *   - path_program_static:         The path_program_static setting.
 *   - path_sources:                The path_sources setting.
 *   - path_sources_object:         The path_sources_object setting.
 *   - process_post:                The process_post setting.
 *   - process_pre:                 The process_pre setting.
 *   - version_major:               The version_major setting.
 *   - version_major_prefix:        The version_major_prefix setting.
 *   - version_micro:               The version_micro setting.
 *   - version_micro_prefix:        The version_micro_prefix setting.
 *   - version_minor:               The version_minor setting.
 *   - version_minor_prefix:        The version_minor_prefix setting.
 *   - version_nano:                The version_nano setting.
 *   - version_nano_prefix:         The version_nano_prefix setting.
 *
 *   - build_indexer_arguments:      The build_indexer_arguments setting.
 *   - build_libraries:              The build_libraries setting.
 *   - build_libraries_shared:       The build_libraries_shared setting.
 *   - build_libraries_static:       The build_libraries_static setting.
 *   - build_objects_library:        The build_objects_library setting.
 *   - build_objects_library_shared: The build_objects_library_shared setting.
 *   - build_objects_library_static: The build_objects_library_static setting.
 *   - build_objects_program:        The build_objects_program setting.
 *   - build_objects_program_shared: The build_objects_program_shared setting.
 *   - build_objects_program_static: The build_objects_program_static setting.
 *   - build_sources_documentation:  The build_sources_documentation setting.
 *   - build_sources_headers:        The build_sources_headers setting.
 *   - build_sources_headers_shared: The build_sources_headers_shared setting.
 *   - build_sources_headers_static: The build_sources_headers_static setting.
 *   - build_sources_library:        The build_sources_library setting.
 *   - build_sources_library_shared: The build_sources_library_shared setting.
 *   - build_sources_library_static: The build_sources_library_static setting.
 *   - build_sources_program:        The build_sources_program setting.
 *   - build_sources_program_shared: The build_sources_program_shared setting.
 *   - build_sources_program_static: The build_sources_program_static setting.
 *   - build_sources_script:         The build_sources_script setting.
 *   - build_sources_setting:        The build_sources_setting setting.
 *   - defines:                      The defines setting.
 *   - defines_library:              The defines_library setting.
 *   - defines_library_shared:       The defines_library_shared setting.
 *   - defines_library_static:       The defines_library_static setting.
 *   - defines_object:               The defines_object setting.
 *   - defines_object_shared:        The defines_object_shared setting.
 *   - defines_object_static:        The defines_object_static setting.
 *   - defines_program:              The defines_program setting.
 *   - defines_program_shared:       The defines_program_shared setting.
 *   - defines_program_static:       The defines_program_static setting.
 *   - defines_shared:               The defines_shared setting.
 *   - defines_static:               The defines_static setting.
 *   - environment:                  The environment setting.
 *   - flags:                        The flags setting.
 *   - flags_library:                The flags_library setting.
 *   - flags_library_shared:         The flags_library_shared setting.
 *   - flags_library_static:         The flags_library_static setting.
 *   - flags_object:                 The flags_object setting.
 *   - flags_object_shared:          The flags_object_shared setting.
 *   - flags_object_static:          The flags_object_static setting.
 *   - flags_program:                The flags_program setting.
 *   - flags_program_shared:         The flags_program_shared setting.
 *   - flags_program_static:         The flags_program_static setting.
 *   - flags_shared:                 The flags_shared setting.
 *   - flags_static:                 The flags_static setting.
 *   - modes:                        The modes setting.
 *   - modes_default:                The modes_default setting.
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

  #define fake_build_setting_total_d 89
#endif // _di_fake_build_setting_t_

/**
 * The build stage data.
 *
 * Properties:
 *   - file_library_script:        The script library files.
 *   - file_library_shared:        The shared library files.
 *   - file_library_static:        The static library files.
 *   - file_object_script:         The script object files.
 *   - file_object_shared:         The shared object files.
 *   - file_object_static:         The static object files.
 *   - file_objects_static:        The static objects files.
 *   - file_process_post:          The post-process files.
 *   - file_process_pre:           The pre-process files.
 *   - file_program_script:        The script program files.
 *   - file_program_shared:        The shared program files.
 *   - file_program_static:        The static program files.
 *   - file_skeleton:              The skeleton files.
 *   - file_sources_documentation: The documentation source files.
 *   - file_sources_headers:       The header source files.
 *   - file_sources_script:        The script source files.
 *   - file_sources_settings:      The setting source files.
 */
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
#endif // _di_fake_build_stage_t_

/**
 * The build data.
 *
 * Properties:
 *   - setting:     The build settings.
 *   - environment: The environment variables.
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
#endif // _di_fake_build_data_t_

/**
 * The make settings.
 *
 * Properties:
 *   - load_build: Designate loading the build settings.
 *   - fail:       Holds the fail state.
 *   - parameter:  The parameters array map.
 */
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
#endif // _di_fake_make_setting_t_

/**
 * The make parameters.
 *
 * Properties:
 *   - build:     The build parameters.
 *   - color:     The color parameters.
 *   - data:      The data parameters.
 *   - define:    The define parameters.
 *   - documents: The document parameters.
 *   - fakefile:  The fakefile parameters.
 *   - licenses:  The license parameters.
 *   - mode:      The mode parameters.
 *   - process:   The process parameters.
 *   - settings:  The setting parameters.
 *   - sources:   The source parameters.
 *   - verbosity: The verbosity parameters.
 *   - work:      The work parameters.
 */
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
#endif // _di_fake_make_parameter_t_

/**
 * The make path.
 *
 * Properties:
 *   - top:   The top-most directory.
 *   - stack: The stack representing the directory paths.
 */
#ifndef _di_fake_make_path_t_
  typedef struct {
    f_file_t top;

    f_string_dynamics_t stack;
  } fake_make_path_t;

  #define fake_make_path_t_initialize { \
    f_file_t_initialize, \
    f_string_dynamics_t_initialize, \
  }
#endif // _di_fake_make_path_t_

/**
 * The control data.
 *
 * Properties:
 *   - setting_build:    The build settings.
 *   - setting_make:     The make settings.
 *   - environment:      All environment variables allowed to be exposed to the when processing.
 *   - parameter:        A set of parameters available for IKI substitution.
 *   - parameter_option: A set of parameters available for IKI option substitution.
 *   - parameter_value:  A set of parameters available for IKI value substitution.
 *   - path:             The path to the Fakefile.
 *   - fakefile:         The loaded Fakefile.
 *   - buffer:           A buffer used during processing.
 *   - cache_1:          An additional buffer for caching purposes.
 *   - cache_2:          An additional buffer for caching purposes.
 *   - cache_path:       A buffer for path-specific caching.
 *   - cache_arguments:  A cache for expanded arguments.
 *   - cache_iki:        A cache for IKI data.
 *   - id_main:          Index of the "main" Section.
 *   - main:             The program and settings data.
 *   - data:             The Fake make program data.
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

    f_number_unsigned_t id_main;

    fake_main_t *main;
    fake_data_t *data;
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
    0, \
    0, \
    0, \
  }
#endif // _di_fake_make_data_t_

/**
 * Delete the build data.
 *
 * @param build_data
 *   The build data.
 *
 *   This does not alter setting.state.status.
 */
#ifndef _di_fake_build_data_delete_
  extern void fake_build_data_delete(fake_build_data_t * const build_data);
#endif // _di_fake_build_data_delete_

/**
 * Delete the build data.
 *
 * @param build_setting
 *   The build setting.
 *
 *   This does not alter setting.state.status.
 */
#ifndef _di_fake_build_setting_delete_
  extern void fake_build_setting_delete(fake_build_setting_t * const build_setting);
#endif // _di_fake_build_setting_delete_

/**
 * Delete the build data.
 *
 * @param build_stage
 *   The build stage.
 *
 *   This does not alter setting.state.status.
 */
#ifndef _di_fake_build_stage_delete_
  extern void fake_build_stage_delete(fake_build_stage_t * const build_stage);
#endif // _di_fake_build_stage_delete_

/**
 * Deallocate program data.
 *
 * @param data
 *   The program data.
 *
 *   This does not alter data.main.settings.state.status.
 */
#ifndef _di_fake_data_delete_
  extern void fake_data_delete(fake_data_t * const data);
#endif // _di_fake_data_delete_

/**
 * Deallocate make data.
 *
 * @param data_make
 *   The make data.
 *
 *   This does not alter data_make.main.setting.state.status.
 */
#ifndef _di_fake_make_data_delete_
  extern void fake_make_data_delete(fake_make_data_t * const data_make);
#endif // _di_fake_make_data_delete_

/**
 * Deallocate main program data.
 *
 * @param setting_make
 *   The make setting data.
 *
 *   This does not alter data_make.main.setting.state.status.
 */
#ifndef _di_fake_main_delete_
  extern void fake_main_delete(fake_main_t * const main);
#endif // _di_fake_main_delete_

/**
 * Deallocate make setting data.
 *
 * @param setting_make
 *   The make setting data.
 *
 *   This does not alter data_make.main.setting.state.status.
 */
#ifndef _di_fake_make_setting_delete_
  extern void fake_make_setting_delete(fake_make_setting_t * const setting_make);
#endif // _di_fake_make_setting_delete_

/**
 * Delete the program main setting data.
 *
 * @param setting
 *   The program main setting data.
 *
 *   This does not alter setting.state.status.
 */
#ifndef _di_fake_setting_delete_
  extern void fake_setting_delete(fake_setting_t * const setting);
#endif // _di_fake_setting_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_common_type_h
