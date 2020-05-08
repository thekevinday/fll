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
 * It does provide the built binaries and scripts in a consistent location for other programs to operate on.
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
 *
 * The "data/" directory contains all file data, such as firmware or files commonly found under /usr/share in a standard GNU Linux system.
 * The "data/" direcory may also contain build-time data.
 * The "documents/" directory contains all documentation after any build-time processing.
 * The "libraries/" and "programs/" directories contains the sub-directories "script/", "shared/", and "static/".
 * The "libraries/" directory will contain compiled libraries or library-like scripts in their respective sub-directories.
 * The "objects/" directory will contain any compile object files.
 * The "progams/" directory will contain compiled programs or program-like scripts in their respective sub-directories.
 * The "settings/" directory contains all configuration data, such as files commonly found under /etc in a standard GNU Linux system.
 *
 * @todo this will eventually support fakefile, which is akin to makefile.
 *       All of the setting data will be loaded and available for a fakefile.
 *
 * @todo update the below documentation and clean it up (this is the build settings documentation).
 *
 * "build_compiler"
 *
 * "build_libraries"
 *
 * "build_linker"
 *
 * "build_shared"
 *
 * "build_sources_headers"
 * "build_sources_library"
 * "build_sources_program"
 * "build_sources_settings"
 * "build_sources_shell"
 *
 * "build_static"
 *
 * "defines_all"
 * "defines_shared"
 * "defines_static"
 *
 * "flags_all"
 * "flags_library"
 * "flags_program"
 * "flags_shared"
 * "flags_static"
 *
 * "path_language"
 *
 * "process_pre"
 * - This represents the name of a script to run (either a path to the script by prepending '/' or './', or the name a script found via PATH environment variable).
 * - This script will receive three types of parameters, if relevant (1: the operation name, will always be present) (2: -m mode, such that "mode" is the mode value) (3: -d defines, such that "defines" is the combine defines).
 * - This script is run before the operation, for each operation.
 * - This script also accepts the color mode parameters as "+n" for no color and "+l" for light color.
 * - The path of the script, when using './' is relative to the 'data/build/settings/' directory.
 *
 * "process_post"
 * - Identical to "pre_process", except that this script is run after the operation, for each operation.
 * - Also (always) receives a parameter: "-r result, such that "result" is the numeric value representing the return status of the operation.
 *
 * "project_level" This needs to be changed (maybe "build_includes_path"), such that the value is "level_1" instead of "1', for example. There needs to be additional include sub-directory support for header directories.
 * "project_name"
 *
 * "version_major"
 * "version_micro"
 * "version_minor"
 *
 * The data/ is intended to contain additional data, the following are special use or reserved:
 *   "data/build/": The build related settings are stored here, such as process_pre.sh or the settings configuration "data/build/settings".
 *   "data/settings/": Any configuration settings files, like those found under "/etc/".
 *   "data/common/": Any common data files, like those found under "/usr/share/".
 *   "data/documents/": Any documentation data files, like those found under "/usr/share/man/".
 */
#ifndef _fake_h

// libc includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// fll-0 includes
#include <level_0/console.h>
#include <level_0/file.h>
#include <level_0/status.h>
#include <level_0/string.h>
#include <level_0/type.h>

// fll-1 includes
#include <level_1/color.h>
#include <level_1/console.h>
#include <level_1/file.h>
#include <level_1/string.h>

// fll-2 includes
#include <level_2/execute.h>
#include <level_2/fss.h>
#include <level_2/fss_basic.h>
#include <level_2/program.h>

// Temporary include, remove this.
#include <level_1/serialized.h>

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

#ifndef _di_fake_defaults_
  #define fake_default_path_build                 "build/"
  #define fake_default_path_build_documents       "build/documents/"
  #define fake_default_path_build_includes        "build/includes/"
  #define fake_default_path_build_libaries        "build/libaries/"
  #define fake_default_path_build_libaries_script "build/libaries/script/"
  #define fake_default_path_build_libaries_shared "build/libaries/shared/"
  #define fake_default_path_build_libaries_static "build/libaries/static/"
  #define fake_default_path_build_objects         "build/objects/"
  #define fake_default_path_build_process         "build/process/"
  #define fake_default_path_build_programs        "build/programs/"
  #define fake_default_path_build_programs_script "build/programs/script/"
  #define fake_default_path_build_programs_shared "build/programs/shared/"
  #define fake_default_path_build_programs_static "build/programs/static/"
  #define fake_default_path_build_settings        "build/settings/"
  #define fake_default_path_work                  ""

  #define fake_default_path_build_length                 6
  #define fake_default_path_build_documents_length       16
  #define fake_default_path_build_includes_length        15
  #define fake_default_path_build_libaries_length        15
  #define fake_default_path_build_libaries_script_length 22
  #define fake_default_path_build_libaries_shared_length 22
  #define fake_default_path_build_libaries_static_length 22
  #define fake_default_path_build_objects_length         14
  #define fake_default_path_build_process_length         14
  #define fake_default_path_build_programs_length        15
  #define fake_default_path_build_programs_script_length 22
  #define fake_default_path_build_programs_shared_length 22
  #define fake_default_path_build_programs_static_length 22
  #define fake_default_path_build_settings_length        15
  #define fake_default_path_work_length                  0

  #define fake_default_defines  ""
  #define fake_default_mode     ""
  #define fake_default_process  ""
  #define fake_default_settings "settings"

  #define fake_default_defines_length  0
  #define fake_default_mode_length     0
  #define fake_default_process_length  0
  #define fake_default_settings_length 8

  #define fake_default_path_source_build     "data/build/"
  #define fake_default_path_source_codes     "sources/"
  #define fake_default_path_source_common    "data/common/"
  #define fake_default_path_source_data      "data/"
  #define fake_default_path_source_documents "data/documents/"
  #define fake_default_path_source_licenses  "licenses/"
  #define fake_default_path_source_settings  "data/build/"

  #define fake_default_path_source_build_length     11
  #define fake_default_path_source_codes_length     8
  #define fake_default_path_source_common_length    12
  #define fake_default_path_source_data_length      5
  #define fake_default_path_source_documents_length 15
  #define fake_default_path_source_licenses_length  9
  #define fake_default_path_source_settings_length  11

  #define fake_default_language_c     "c/"
  #define fake_default_language_cpp   "c++/"
  #define fake_default_language_shell "shell/"

  #define fake_default_language_c_length     2
  #define fake_default_language_cpp_length   4
  #define fake_default_language_shell_length 6
#endif // _di_fake_defaults_

#ifndef _di_settings_data_
  typedef struct {
    f_string_dynamic build_compiler;
    f_string_dynamic build_libraries;
    f_string_dynamic build_linker;
    f_string_dynamic build_shared;
    f_string_dynamic build_sources_headers;
    f_string_dynamic build_sources_library;
    f_string_dynamic build_sources_program;
    f_string_dynamic build_sources_settings;
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
    f_string_dynamic process_post;
    f_string_dynamic process_pre;
    f_string_dynamic project_level;
    f_string_dynamic project_name;
    f_string_dynamic version_major;
    f_string_dynamic version_micro;
    f_string_dynamic version_minor;
  } fake_settings_data;

  #define fake_settings_data_initialize { f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize, f_string_dynamic_initialize }

  #define fake_macro_settings_build_clear(settings_data) \
    f_macro_string_dynamic_clear(settings_data.build_compiler) \
    f_macro_string_dynamic_clear(settings_data.build_libraries) \
    f_macro_string_dynamic_clear(settings_data.build_linker) \
    f_macro_string_dynamic_clear(settings_data.build_shared) \
    f_macro_string_dynamic_clear(settings_data.build_sources_headers) \
    f_macro_string_dynamic_clear(settings_data.build_sources_library) \
    f_macro_string_dynamic_clear(settings_data.build_sources_program) \
    f_macro_string_dynamic_clear(settings_data.build_sources_settings) \
    f_macro_string_dynamic_clear(settings_data.build_sources_shell) \
    f_macro_string_dynamic_clear(settings_data.build_static) \
    f_macro_string_dynamic_clear(settings_data.defines_all) \
    f_macro_string_dynamic_clear(settings_data.defines_shared) \
    f_macro_string_dynamic_clear(settings_data.defines_static) \
    f_macro_string_dynamic_clear(settings_data.flags_all) \
    f_macro_string_dynamic_clear(settings_data.flags_library) \
    f_macro_string_dynamic_clear(settings_data.flags_program) \
    f_macro_string_dynamic_clear(settings_data.flags_shared) \
    f_macro_string_dynamic_clear(settings_data.flags_static) \
    f_macro_string_dynamic_clear(settings_data.path_language) \
    f_macro_string_dynamic_clear(settings_data.process_post) \
    f_macro_string_dynamic_clear(settings_data.process_pre) \
    f_macro_string_dynamic_clear(settings_data.project_level) \
    f_macro_string_dynamic_clear(settings_data.project_name) \
    f_macro_string_dynamic_clear(settings_data.version_major) \
    f_macro_string_dynamic_clear(settings_data.version_micro) \
    f_macro_string_dynamic_clear(settings_data.version_minor)

  #define fake_macro_settings_data_delete(status, settings_data) \
    f_macro_string_dynamic_delete(status, settings_data.build_compiler) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings_data.build_libraries) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings_data.build_linker) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings_data.build_shared) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings_data.build_sources_headers) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings_data.build_sources_library) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings_data.build_sources_program) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings_data.build_sources_settings) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings_data.build_sources_shell) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings_data.build_static) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings_data.defines_all) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings_data.defines_shared) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings_data.defines_static) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings_data.flags_all) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings_data.flags_library) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings_data.flags_program) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings_data.flags_shared) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings_data.flags_static) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings_data.path_language) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings_data.process_post) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings_data.process_pre) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings_data.project_level) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings_data.project_name) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings_data.version_major) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings_data.version_micro) \
    if (status == f_none) f_macro_string_dynamic_delete(status, settings_data.version_minor)

  #define fake_macro_settings_data_destroy(status, settings_data, length) \
    f_macro_string_dynamic_delete(status, settings_data.build_compiler) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings_data.build_libraries) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings_data.build_linker) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings_data.build_shared) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings_data.build_sources_headers) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings_data.build_sources_library) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings_data.build_sources_program) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings_data.build_sources_settings) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings_data.build_sources_shell) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings_data.build_static) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings_data.defines_all) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings_data.defines_shared) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings_data.defines_static) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings_data.flags_all) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings_data.flags_library) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings_data.flags_program) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings_data.flags_shared) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings_data.flags_static) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings_data.path_language) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings_data.process_post) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings_data.process_pre) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings_data.project_level) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings_data.project_name) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings_data.version_major) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings_data.version_micro) \
    if (status == f_none) f_macro_string_dynamic_destroy(status, settings_data.version_minor)

  #define fake_macro_settings_data_delete_simple(settings_data) \
    f_macro_string_dynamic_delete_simple(settings_data.build_compiler) \
    f_macro_string_dynamic_delete_simple(settings_data.build_libraries) \
    f_macro_string_dynamic_delete_simple(settings_data.build_linker) \
    f_macro_string_dynamic_delete_simple(settings_data.build_shared) \
    f_macro_string_dynamic_delete_simple(settings_data.build_sources_headers) \
    f_macro_string_dynamic_delete_simple(settings_data.build_sources_library) \
    f_macro_string_dynamic_delete_simple(settings_data.build_sources_program) \
    f_macro_string_dynamic_delete_simple(settings_data.build_sources_settings) \
    f_macro_string_dynamic_delete_simple(settings_data.build_sources_shell) \
    f_macro_string_dynamic_delete_simple(settings_data.build_static) \
    f_macro_string_dynamic_delete_simple(settings_data.defines_all) \
    f_macro_string_dynamic_delete_simple(settings_data.defines_shared) \
    f_macro_string_dynamic_delete_simple(settings_data.defines_static) \
    f_macro_string_dynamic_delete_simple(settings_data.flags_all) \
    f_macro_string_dynamic_delete_simple(settings_data.flags_library) \
    f_macro_string_dynamic_delete_simple(settings_data.flags_program) \
    f_macro_string_dynamic_delete_simple(settings_data.flags_shared) \
    f_macro_string_dynamic_delete_simple(settings_data.flags_static) \
    f_macro_string_dynamic_delete_simple(settings_data.path_language) \
    f_macro_string_dynamic_delete_simple(settings_data.process_post) \
    f_macro_string_dynamic_delete_simple(settings_data.process_pre) \
    f_macro_string_dynamic_delete_simple(settings_data.project_level) \
    f_macro_string_dynamic_delete_simple(settings_data.project_name) \
    f_macro_string_dynamic_delete_simple(settings_data.version_major) \
    f_macro_string_dynamic_delete_simple(settings_data.version_micro) \
    f_macro_string_dynamic_delete_simple(settings_data.version_minor)

  #define fake_macro_settings_data_destroy_simple(settings_data, length) \
    f_macro_string_dynamic_destroy_simple(settings_data.build_compiler) \
    f_macro_string_dynamic_destroy_simple(settings_data.build_libraries) \
    f_macro_string_dynamic_destroy_simple(settings_data.build_linker) \
    f_macro_string_dynamic_destroy_simple(settings_data.build_shared) \
    f_macro_string_dynamic_destroy_simple(settings_data.build_sources_headers) \
    f_macro_string_dynamic_destroy_simple(settings_data.build_sources_library) \
    f_macro_string_dynamic_destroy_simple(settings_data.build_sources_program) \
    f_macro_string_dynamic_destroy_simple(settings_data.build_sources_settings) \
    f_macro_string_dynamic_destroy_simple(settings_data.build_sources_shell) \
    f_macro_string_dynamic_destroy_simple(settings_data.build_static) \
    f_macro_string_dynamic_destroy_simple(settings_data.defines_all) \
    f_macro_string_dynamic_destroy_simple(settings_data.defines_shared) \
    f_macro_string_dynamic_destroy_simple(settings_data.defines_static) \
    f_macro_string_dynamic_destroy_simple(settings_data.flags_all) \
    f_macro_string_dynamic_destroy_simple(settings_data.flags_library) \
    f_macro_string_dynamic_destroy_simple(settings_data.flags_program) \
    f_macro_string_dynamic_destroy_simple(settings_data.flags_shared) \
    f_macro_string_dynamic_destroy_simple(settings_data.flags_static) \
    f_macro_string_dynamic_destroy_simple(settings_data.path_language) \
    f_macro_string_dynamic_destroy_simple(settings_data.process_post) \
    f_macro_string_dynamic_destroy_simple(settings_data.process_pre) \
    f_macro_string_dynamic_destroy_simple(settings_data.project_level) \
    f_macro_string_dynamic_destroy_simple(settings_data.project_name) \
    f_macro_string_dynamic_destroy_simple(settings_data.version_major) \
    f_macro_string_dynamic_destroy_simple(settings_data.version_micro) \
    f_macro_string_dynamic_destroy_simple(settings_data.version_minor)

  #define fake_settings_name_build_compiler         "build_compiler"
  #define fake_settings_name_build_libraries        "build_libraries"
  #define fake_settings_name_build_linker           "build_linker"
  #define fake_settings_name_build_shared           "build_shared"
  #define fake_settings_name_build_sources_headers  "build_sources_headers"
  #define fake_settings_name_build_sources_library  "build_sources_library"
  #define fake_settings_name_build_sources_program  "build_sources_program"
  #define fake_settings_name_build_sources_settings "build_sources_settings"
  #define fake_settings_name_build_sources_shell    "build_sources_shell"
  #define fake_settings_name_build_static           "build_static"
  #define fake_settings_name_defines_all            "defines_all"
  #define fake_settings_name_defines_shared         "defines_shared"
  #define fake_settings_name_defines_static         "defines_static"
  #define fake_settings_name_flags_all              "flags_all"
  #define fake_settings_name_flags_library          "flags_library"
  #define fake_settings_name_flags_program          "flags_program"
  #define fake_settings_name_flags_shared           "flags_shared"
  #define fake_settings_name_flags_static           "flags_static"
  #define fake_settings_name_path_language          "path_language"
  #define fake_settings_name_process_post           "process_post"
  #define fake_settings_name_process_pre            "process_pre"
  #define fake_settings_name_project_level          "project_level"
  #define fake_settings_name_project_name           "project_name"
  #define fake_settings_name_version_major          "version_major"
  #define fake_settings_name_version_micro          "version_micro"
  #define fake_settings_name_version_minor          "version_minor"

  #define fake_settings_name_build_compiler_length         14
  #define fake_settings_name_build_libraries_length        15
  #define fake_settings_name_build_linker_length           12
  #define fake_settings_name_build_shared_length           12
  #define fake_settings_name_build_sources_headers_length  21
  #define fake_settings_name_build_sources_library_length  21
  #define fake_settings_name_build_sources_program_length  21
  #define fake_settings_name_build_sources_settings_length 22
  #define fake_settings_name_build_sources_shell_length    19
  #define fake_settings_name_build_static_length           12
  #define fake_settings_name_defines_all_length            11
  #define fake_settings_name_defines_shared_length         14
  #define fake_settings_name_defines_static_length         14
  #define fake_settings_name_flags_all_length              9
  #define fake_settings_name_flags_library_length          13
  #define fake_settings_name_flags_program_length          13
  #define fake_settings_name_flags_shared_length           12
  #define fake_settings_name_flags_static_length           12
  #define fake_settings_name_path_language_length          13
  #define fake_settings_name_process_post_length           12
  #define fake_settings_name_process_pre_length            11
  #define fake_settings_name_project_level_length          13
  #define fake_settings_name_project_name_length           12
  #define fake_settings_name_version_major_length          13
  #define fake_settings_name_version_micro_length          13
  #define fake_settings_name_version_minor_length          13

  #define fake_settings_total 26
#endif // _di_settings_data_

#ifndef _di_fake_build_language_
  enum {
    fake_build_language_c = 1,
    fake_build_language_cpp,
    fake_build_language_shell,
  };

  #define fake_build_language_c     "c"
  #define fake_build_language_cpp   "c++"
  #define fake_build_language_shell "shell"
#endif // _di_fake_build_language_

#ifndef _di_fake_defines_
  enum {
    fake_operation_build = 1,
    fake_operation_clean,
    fake_operation_make,
    fake_operation_skeleton,
  };

  #define fake_operations_total      4
  #define fake_operations_initialize { 0, 0, 0, 0 }

  #define fake_short_defines  "d"
  #define fake_short_mode     "m"
  #define fake_short_process  "p"
  #define fake_short_settings "s"

  #define fake_short_defines_length  1
  #define fake_short_mode_length     1
  #define fake_short_process_length  1
  #define fake_short_settings_length 1

  #define fake_short_path_build "b"
  #define fake_short_path_work  "w"

  #define fake_short_path_build_length 1
  #define fake_short_path_work_length  1

  #define fake_short_path_source_build     "B"
  #define fake_short_path_source_common    "O"
  #define fake_short_path_source_data      "D"
  #define fake_short_path_source_documents "M"
  #define fake_short_path_source_codes     "C"
  #define fake_short_path_source_licenses  "L"
  #define fake_short_path_source_settings  "S"

  #define fake_short_path_source_build_length     1
  #define fake_short_path_source_common_length    1
  #define fake_short_path_source_data_length      1
  #define fake_short_path_source_documents_length 1
  #define fake_short_path_source_codes_length     1
  #define fake_short_path_source_licenses_length  1
  #define fake_short_path_source_settings_length  1

  #define fake_long_defines  "defines"
  #define fake_long_mode     "mode"
  #define fake_long_process  "process"
  #define fake_long_settings "settings"

  #define fake_long_defines_length  7
  #define fake_long_mode_length     4
  #define fake_long_process_length  7
  #define fake_long_settings_length 8

  #define fake_long_path_build "build"
  #define fake_long_path_work  "work"

  #define fake_long_path_build_length 5
  #define fake_long_path_work_length  4

  #define fake_long_path_source_build     "source_build"
  #define fake_long_path_source_common    "source_common"
  #define fake_long_path_source_data      "source_data"
  #define fake_long_path_source_documents "source_documents"
  #define fake_long_path_source_codes     "source_codes"
  #define fake_long_path_source_licenses  "source_licenses"
  #define fake_long_path_source_settings  "source_settings"

  #define fake_long_path_source_build_length     12
  #define fake_long_path_source_common_length    13
  #define fake_long_path_source_data_length      11
  #define fake_long_path_source_documents_length 16
  #define fake_long_path_source_codes_length     12
  #define fake_long_path_source_licenses_length  15
  #define fake_long_path_source_settings_length  15

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
    fake_parameter_no_color,
    fake_parameter_version,

    fake_parameter_defines,
    fake_parameter_mode,
    fake_parameter_process,
    fake_parameter_settings,

    fake_parameter_path_build,
    fake_parameter_path_work,

    fake_parameter_path_source_build,
    fake_parameter_path_source_common,
    fake_parameter_path_source_data,
    fake_parameter_path_source_documents,
    fake_parameter_path_source_codes,
    fake_parameter_path_source_licenses,
    fake_parameter_path_source_settings,

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

  #define fake_console_parameter_initialize \
    { \
      f_console_parameter_initialize(f_console_standard_short_help, f_console_standard_long_help, 0, 0, f_console_type_normal), \
      f_console_parameter_initialize(f_console_standard_short_light, f_console_standard_long_light, 0, 0, f_console_type_inverse), \
      f_console_parameter_initialize(f_console_standard_short_dark, f_console_standard_long_dark, 0, 0, f_console_type_inverse), \
      f_console_parameter_initialize(f_console_standard_short_no_color, f_console_standard_long_no_color, 0, 0, f_console_type_inverse), \
      f_console_parameter_initialize(f_console_standard_short_version, f_console_standard_long_version, 0, 0, f_console_type_inverse), \
      f_console_parameter_initialize(fake_short_defines, fake_long_defines, 0, 1, f_console_type_normal), \
      f_console_parameter_initialize(fake_short_mode, fake_long_mode, 0, 1, f_console_type_normal), \
      f_console_parameter_initialize(fake_short_process, fake_long_process, 0, 1, f_console_type_normal), \
      f_console_parameter_initialize(fake_short_settings, fake_long_settings, 0, 1, f_console_type_normal), \
      f_console_parameter_initialize(fake_short_path_build, fake_long_path_build, 0, 1, f_console_type_normal), \
      f_console_parameter_initialize(fake_short_path_work, fake_long_path_work, 0, 1, f_console_type_normal), \
      f_console_parameter_initialize(fake_short_path_source_build, fake_long_path_source_build, 0, 1, f_console_type_normal), \
      f_console_parameter_initialize(fake_short_path_source_common, fake_long_path_source_common, 0, 1, f_console_type_normal), \
      f_console_parameter_initialize(fake_short_path_source_data, fake_long_path_source_data, 0, 1, f_console_type_normal), \
      f_console_parameter_initialize(fake_short_path_source_documents, fake_long_path_source_documents, 0, 1, f_console_type_normal), \
      f_console_parameter_initialize(fake_short_path_source_codes, fake_long_path_source_codes, 0, 1, f_console_type_normal), \
      f_console_parameter_initialize(fake_short_path_source_licenses, fake_long_path_source_licenses, 0, 1, f_console_type_normal), \
      f_console_parameter_initialize(fake_short_path_source_settings, fake_long_path_source_settings, 0, 1, f_console_type_normal), \
      f_console_parameter_initialize(0, fake_long_documents_disabled, 0, 0, f_console_type_normal), \
      f_console_parameter_initialize(0, fake_long_documents_enabled, 0, 0, f_console_type_normal), \
      f_console_parameter_initialize(0, fake_long_shared_disabled, 0, 0, f_console_type_normal), \
      f_console_parameter_initialize(0, fake_long_shared_enabled, 0, 0, f_console_type_normal), \
      f_console_parameter_initialize(0, fake_long_static_disabled, 0, 0, f_console_type_normal), \
      f_console_parameter_initialize(0, fake_long_static_enabled, 0, 0, f_console_type_normal), \
      f_console_parameter_initialize(0, 0, fake_other_operation_build, 0, f_console_type_other), \
      f_console_parameter_initialize(0, 0, fake_other_operation_clean, 0, f_console_type_other), \
      f_console_parameter_initialize(0, 0, fake_other_operation_make, 0, f_console_type_other), \
      f_console_parameter_initialize(0, 0, fake_other_operation_skeleton, 0, f_console_type_other), \
    }

  #define fake_total_parameters 28
#endif // _di_fake_defines_

#ifndef _di_fake_data_
  typedef struct {
    f_console_parameter parameters[fake_total_parameters];

    f_string_lengths remaining;
    bool process_pipe;

    uint8_t operation;

    f_string_dynamic defines;
    f_string_dynamics mode;
    f_string_dynamic process;
    f_string_dynamic settings;


    f_string_dynamic path_build;
    f_string_dynamic path_work;

    f_string_dynamic path_source_build;
    f_string_dynamic path_source_common;
    f_string_dynamic path_source_data;
    f_string_dynamic path_source_documents;
    f_string_dynamic path_source_codes;
    f_string_dynamic path_source_licenses;
    f_string_dynamic path_source_settings;

    fake_settings_data settings_data;

    fl_color_context context;
  } fake_data;

  #define fake_data_initialize \
    { \
      fake_console_parameter_initialize, \
      f_string_lengths_initialize, \
      f_false, \
      0, \
      f_string_dynamic_initialize, \
      f_string_dynamics_initialize, \
      f_string_dynamic_initialize, \
      f_string_dynamic_initialize, \
      f_string_dynamic_initialize, \
      f_string_dynamic_initialize, \
      f_string_dynamic_initialize, \
      f_string_dynamic_initialize, \
      f_string_dynamic_initialize, \
      f_string_dynamic_initialize, \
      f_string_dynamic_initialize, \
      f_string_dynamic_initialize, \
      f_string_dynamic_initialize, \
      fake_settings_data_initialize, \
      fl_color_context_initialize, \
    }
#endif // _di_fake_data_

/**
 * Print help to standard output.
 *
 * @param context
 *   The color context settings.
 *
 * @return
 *   f_none on success.
 */
#ifndef _di_fake_print_help_
  extern f_return_status fake_print_help(const fl_color_context context);
#endif // _di_fake_print_help_

/**
 * Execute main program.
 *
 * Be sure to call fake_delete_data() after executing this.
 *
 * @param arguments
 *   The parameters passed to the process.
 * @param data
 *   The program data.
 *
 * @return
 *   f_none on success.
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see fake_delete_data()
 */
#ifndef _di_fake_main_
  extern f_return_status fake_main(const f_console_arguments arguments, fake_data *data);
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
 *   f_none on success.
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see fake_main()
 */
#ifndef _di_fake_delete_data_
  extern f_return_status fake_delete_data(fake_data *data);
#endif // _di_fake_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_h
