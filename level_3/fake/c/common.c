#include "fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_program_version_
  const f_string_static_t fake_program_version_s = macro_f_string_static_t_initialize(FAKE_program_version_s, 0, FAKE_program_version_s_length);
#endif // _di_fake_program_version_

#ifndef _di_fake_program_name_
  const f_string_static_t fake_program_name_s = macro_f_string_static_t_initialize(FAKE_program_name_s, 0, FAKE_program_name_s_length);
  const f_string_static_t fake_program_name_long_s = macro_f_string_static_t_initialize(FAKE_program_name_long_s, 0, FAKE_program_name_long_s_length);
#endif // _di_fake_program_name_

#ifndef _di_fake_program_help_parameters_
  const f_string_static_t fake_program_help_parameters_s = macro_f_string_static_t_initialize(FAKE_program_help_parameters_s, 0, FAKE_program_help_parameters_s_length);
#endif // _di_fake_program_help_parameters_

/**
 * The build operation utilizes pre-defined path structures.
 * These structures are hard-coded by their individual pieces to be constructed later on.
 */
#ifndef _di_fake_path_
  const f_string_static_t fake_path_part_bash_s = macro_f_string_static_t_initialize(FAKE_path_part_bash_s, 0, FAKE_path_part_bash_s_length);
  const f_string_static_t fake_path_part_build_s = macro_f_string_static_t_initialize(FAKE_path_part_build_s, 0, FAKE_path_part_build_s_length);
  const f_string_static_t fake_path_part_c_s = macro_f_string_static_t_initialize(FAKE_path_part_c_s, 0, FAKE_path_part_c_s_length);
  const f_string_static_t fake_path_part_cpp_s = macro_f_string_static_t_initialize(FAKE_path_part_cpp_s, 0, FAKE_path_part_cpp_s_length);
  const f_string_static_t fake_path_part_data_s = macro_f_string_static_t_initialize(FAKE_path_part_data_s, 0, FAKE_path_part_data_s_length);
  const f_string_static_t fake_path_part_documents_s = macro_f_string_static_t_initialize(FAKE_path_part_documents_s, 0, FAKE_path_part_documents_s_length);
  const f_string_static_t fake_path_part_includes_s = macro_f_string_static_t_initialize(FAKE_path_part_includes_s, 0, FAKE_path_part_includes_s_length);
  const f_string_static_t fake_path_part_libraries_s = macro_f_string_static_t_initialize(FAKE_path_part_libraries_s, 0, FAKE_path_part_libraries_s_length);
  const f_string_static_t fake_path_part_licenses_s = macro_f_string_static_t_initialize(FAKE_path_part_licenses_s, 0, FAKE_path_part_licenses_s_length);
  const f_string_static_t fake_path_part_objects_s = macro_f_string_static_t_initialize(FAKE_path_part_objects_s, 0, FAKE_path_part_objects_s_length);
  const f_string_static_t fake_path_part_process_s = macro_f_string_static_t_initialize(FAKE_path_part_process_s, 0, FAKE_path_part_process_s_length);
  const f_string_static_t fake_path_part_programs_s = macro_f_string_static_t_initialize(FAKE_path_part_programs_s, 0, FAKE_path_part_programs_s_length);
  const f_string_static_t fake_path_part_script_s = macro_f_string_static_t_initialize(FAKE_path_part_script_s, 0, FAKE_path_part_script_s_length);
  const f_string_static_t fake_path_part_settings_s = macro_f_string_static_t_initialize(FAKE_path_part_settings_s, 0, FAKE_path_part_settings_s_length);
  const f_string_static_t fake_path_part_shared_s = macro_f_string_static_t_initialize(FAKE_path_part_shared_s, 0, FAKE_path_part_shared_s_length);
  const f_string_static_t fake_path_part_stage_s = macro_f_string_static_t_initialize(FAKE_path_part_stage_s, 0, FAKE_path_part_stage_s_length);
  const f_string_static_t fake_path_part_static_s = macro_f_string_static_t_initialize(FAKE_path_part_static_s, 0, FAKE_path_part_static_s_length);
#endif // _di_fake_path_

#ifndef _di_fake_file_
  const f_string_static_t fake_file_defines_s = macro_f_string_static_t_initialize(FAKE_file_defines_s, 0, FAKE_file_defines_s_length);
  const f_string_static_t fake_file_dependencies_s = macro_f_string_static_t_initialize(FAKE_file_dependencies_s, 0, FAKE_file_dependencies_s_length);
  const f_string_static_t fake_file_process_pre_s = macro_f_string_static_t_initialize(FAKE_file_process_pre_s, 0, FAKE_file_process_pre_s_length);
  const f_string_static_t fake_file_process_post_s = macro_f_string_static_t_initialize(FAKE_file_process_post_s, 0, FAKE_file_process_post_s_length);
  const f_string_static_t fake_file_readme_s = macro_f_string_static_t_initialize(FAKE_file_readme_s, 0, FAKE_file_readme_s_length);
#endif // _di_fake_file_

/**
 * Provide default settings.
 */
#ifndef _di_fake_defaults_
  const f_string_static_t fake_default_path_build_s = macro_f_string_static_t_initialize(FAKE_default_path_build_s, 0, FAKE_default_path_build_s_length);
  const f_string_static_t fake_default_path_data_s = macro_f_string_static_t_initialize(FAKE_default_path_data_s, 0, FAKE_default_path_data_s_length);
  const f_string_static_t fake_default_path_sources_s = macro_f_string_static_t_initialize(FAKE_default_path_sources_s, 0, FAKE_default_path_sources_s_length);
  const f_string_static_t fake_default_path_work_s = macro_f_string_static_t_initialize(FAKE_default_path_work_s, 0, FAKE_default_path_work_s_length);

  const f_string_static_t fake_default_define_s = macro_f_string_static_t_initialize(FAKE_default_define_s, 0, FAKE_default_define_s_length);
  const f_string_static_t fake_default_fakefile_s = macro_f_string_static_t_initialize(FAKE_default_fakefile_s, 0, FAKE_default_fakefile_s_length);
  const f_string_static_t fake_default_mode_s = macro_f_string_static_t_initialize(FAKE_default_mode_s, 0, FAKE_default_mode_s_length);
  const f_string_static_t fake_default_process_s = macro_f_string_static_t_initialize(FAKE_default_process_s, 0, FAKE_default_process_s_length);
  const f_string_static_t fake_default_settings_s = macro_f_string_static_t_initialize(FAKE_default_settings_s, 0, FAKE_default_settings_s_length);
#endif // _di_fake_defaults_

#ifndef _di_fake_build_language_
  const f_string_static_t fake_build_language_bash_s = macro_f_string_static_t_initialize(FAKE_build_language_bash_s, 0, FAKE_build_language_bash_s_length);
  const f_string_static_t fake_build_language_c_s = macro_f_string_static_t_initialize(FAKE_build_language_c_s, 0, FAKE_build_language_c_s_length);
  const f_string_static_t fake_build_language_cpp_s = macro_f_string_static_t_initialize(FAKE_build_language_cpp_s, 0, FAKE_build_language_cpp_s_length);
#endif // _di_fake_build_language_

#ifndef _di_fake_build_version_
  const f_string_static_t fake_build_version_major_s = macro_f_string_static_t_initialize(FAKE_build_version_major_s, 0, FAKE_build_version_major_s_length);
  const f_string_static_t fake_build_version_minor_s = macro_f_string_static_t_initialize(FAKE_build_version_minor_s, 0, FAKE_build_version_minor_s_length);
  const f_string_static_t fake_build_version_micro_s = macro_f_string_static_t_initialize(FAKE_build_version_micro_s, 0, FAKE_build_version_micro_s_length);
  const f_string_static_t fake_build_version_nano_s = macro_f_string_static_t_initialize(FAKE_build_version_nano_s, 0, FAKE_build_version_nano_s_length);
#endif // _di_fake_build_version_

#ifndef _di_fake_parameters_
  const f_string_static_t fake_short_define_s = macro_f_string_static_t_initialize(FAKE_short_define_s, 0, FAKE_short_define_s_length);
  const f_string_static_t fake_short_fakefile_s = macro_f_string_static_t_initialize(FAKE_short_fakefile_s, 0, FAKE_short_fakefile_s_length);
  const f_string_static_t fake_short_mode_s = macro_f_string_static_t_initialize(FAKE_short_mode_s, 0, FAKE_short_mode_s_length);
  const f_string_static_t fake_short_process_s = macro_f_string_static_t_initialize(FAKE_short_process_s, 0, FAKE_short_process_s_length);
  const f_string_static_t fake_short_settings_s = macro_f_string_static_t_initialize(FAKE_short_settings_s, 0, FAKE_short_settings_s_length);

  const f_string_static_t fake_short_path_build_s = macro_f_string_static_t_initialize(FAKE_short_path_build_s, 0, FAKE_short_path_build_s_length);
  const f_string_static_t fake_short_path_data_s = macro_f_string_static_t_initialize(FAKE_short_path_data_s, 0, FAKE_short_path_data_s_length);
  const f_string_static_t fake_short_path_sources_s = macro_f_string_static_t_initialize(FAKE_short_path_sources_s, 0, FAKE_short_path_sources_s_length);
  const f_string_static_t fake_short_path_work_s = macro_f_string_static_t_initialize(FAKE_short_path_work_s, 0, FAKE_short_path_work_s_length);

  const f_string_static_t fake_long_define_s = macro_f_string_static_t_initialize(FAKE_long_define_s, 0, FAKE_long_define_s_length);
  const f_string_static_t fake_long_fakefile_s = macro_f_string_static_t_initialize(FAKE_long_fakefile_s, 0, FAKE_long_fakefile_s_length);
  const f_string_static_t fake_long_mode_s = macro_f_string_static_t_initialize(FAKE_long_mode_s, 0, FAKE_long_mode_s_length);
  const f_string_static_t fake_long_process_s = macro_f_string_static_t_initialize(FAKE_long_process_s, 0, FAKE_long_process_s_length);
  const f_string_static_t fake_long_settings_s = macro_f_string_static_t_initialize(FAKE_long_settings_s, 0, FAKE_long_settings_s_length);

  const f_string_static_t fake_long_path_build_s = macro_f_string_static_t_initialize(FAKE_long_path_build_s, 0, FAKE_long_path_build_s_length);
  const f_string_static_t fake_long_path_data_s = macro_f_string_static_t_initialize(FAKE_long_path_data_s, 0, FAKE_long_path_data_s_length);
  const f_string_static_t fake_long_path_sources_s = macro_f_string_static_t_initialize(FAKE_long_path_sources_s, 0, FAKE_long_path_sources_s_length);
  const f_string_static_t fake_long_path_work_s = macro_f_string_static_t_initialize(FAKE_long_path_work_s, 0, FAKE_long_path_work_s_length);

  const f_string_static_t fake_long_documents_disabled_s = macro_f_string_static_t_initialize(FAKE_long_documents_disabled_s, 0, FAKE_long_documents_disabled_s_length);
  const f_string_static_t fake_long_documents_enabled_s = macro_f_string_static_t_initialize(FAKE_long_documents_enabled_s, 0, FAKE_long_documents_enabled_s_length);
  const f_string_static_t fake_long_shared_disabled_s = macro_f_string_static_t_initialize(FAKE_long_shared_disabled_s, 0, FAKE_long_shared_disabled_s_length);
  const f_string_static_t fake_long_shared_enabled_s = macro_f_string_static_t_initialize(FAKE_long_shared_enabled_s, 0, FAKE_long_shared_enabled_s_length);
  const f_string_static_t fake_long_static_disabled_s = macro_f_string_static_t_initialize(FAKE_long_static_disabled_s, 0, FAKE_long_static_disabled_s_length);
  const f_string_static_t fake_long_static_enabled_s = macro_f_string_static_t_initialize(FAKE_long_static_enabled_s, 0, FAKE_long_static_enabled_s_length);

  const f_string_static_t fake_other_operation_build_s = macro_f_string_static_t_initialize(FAKE_other_operation_build_s, 0, FAKE_other_operation_build_s_length);
  const f_string_static_t fake_other_operation_clean_s = macro_f_string_static_t_initialize(FAKE_other_operation_clean_s, 0, FAKE_other_operation_clean_s_length);
  const f_string_static_t fake_other_operation_make_s = macro_f_string_static_t_initialize(FAKE_other_operation_make_s, 0, FAKE_other_operation_make_s_length);
  const f_string_static_t fake_other_operation_skeleton_s = macro_f_string_static_t_initialize(FAKE_other_operation_skeleton_s, 0, FAKE_other_operation_skeleton_s_length);
#endif // _di_fake_parameters_

#ifndef _di_fake_main_delete_
  f_status_t fake_main_delete(fake_main_t * const main) {

    f_console_parameters_delete(&main->parameters);

    f_string_dynamics_resize(0, &main->define);
    f_string_dynamic_resize(0, &main->fakefile);
    f_string_dynamics_resize(0, &main->mode);
    f_string_dynamic_resize(0, &main->process);
    f_string_dynamic_resize(0, &main->settings);

    f_string_dynamic_resize(0, &main->path_build);
    f_string_dynamic_resize(0, &main->path_build_documents);
    f_string_dynamic_resize(0, &main->path_build_includes);
    f_string_dynamic_resize(0, &main->path_build_libraries);
    f_string_dynamic_resize(0, &main->path_build_libraries_script);
    f_string_dynamic_resize(0, &main->path_build_libraries_shared);
    f_string_dynamic_resize(0, &main->path_build_libraries_static);
    f_string_dynamic_resize(0, &main->path_build_objects);
    f_string_dynamic_resize(0, &main->path_build_programs);
    f_string_dynamic_resize(0, &main->path_build_programs_script);
    f_string_dynamic_resize(0, &main->path_build_programs_shared);
    f_string_dynamic_resize(0, &main->path_build_programs_static);
    f_string_dynamic_resize(0, &main->path_build_settings);
    f_string_dynamic_resize(0, &main->path_build_stage);
    f_string_dynamic_resize(0, &main->path_work);

    f_string_dynamic_resize(0, &main->path_data);
    f_string_dynamic_resize(0, &main->path_data_build);

    f_string_dynamic_resize(0, &main->path_data_settings);

    f_string_dynamic_resize(0, &main->path_documents);

    f_string_dynamic_resize(0, &main->path_licenses);

    f_string_dynamic_resize(0, &main->path_sources);
    f_string_dynamic_resize(0, &main->path_sources_bash);
    f_string_dynamic_resize(0, &main->path_sources_c);
    f_string_dynamic_resize(0, &main->path_sources_cpp);
    f_string_dynamic_resize(0, &main->path_sources_script);

    f_string_dynamic_resize(0, &main->path_work);
    f_string_dynamic_resize(0, &main->path_work_includes);
    f_string_dynamic_resize(0, &main->path_work_libraries);
    f_string_dynamic_resize(0, &main->path_work_libraries_script);
    f_string_dynamic_resize(0, &main->path_work_libraries_shared);
    f_string_dynamic_resize(0, &main->path_work_libraries_static);
    f_string_dynamic_resize(0, &main->path_work_programs);
    f_string_dynamic_resize(0, &main->path_work_programs_script);
    f_string_dynamic_resize(0, &main->path_work_programs_shared);
    f_string_dynamic_resize(0, &main->path_work_programs_static);

    f_string_dynamic_resize(0, &main->file_data_build_defines);
    f_string_dynamic_resize(0, &main->file_data_build_dependencies);
    f_string_dynamic_resize(0, &main->file_data_build_process_post_s);
    f_string_dynamic_resize(0, &main->file_data_build_process_pre_s);
    f_string_dynamic_resize(0, &main->file_data_build_fakefile);
    f_string_dynamic_resize(0, &main->file_data_build_settings);

    f_string_dynamic_resize(0, &main->file_documents_readme);

    macro_f_color_context_t_delete_simple(main->context);

    return F_none;
  }
#endif // _di_fake_main_delete_

#ifdef __cplusplus
} // extern "C"
#endif
