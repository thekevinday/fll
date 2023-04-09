#include "../fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_data_delete_
  void fake_build_data_delete(fake_build_data_t * const build_data) {

    if (!build_data) return;

    fake_build_setting_delete(&build_data->setting);
    f_string_maps_resize(0, &build_data->environment);
  }
#endif // _di_fake_build_data_delete_

#ifndef _di_fake_build_setting_delete_
  void fake_build_setting_delete(fake_build_setting_t * const build_setting) {

    if (!build_setting) return;

    f_string_dynamic_resize(0, &build_setting->build_compiler);
    f_string_dynamic_resize(0, &build_setting->build_indexer);
    f_string_dynamic_resize(0, &build_setting->build_name);
    f_string_dynamic_resize(0, &build_setting->build_sources_object);
    f_string_dynamic_resize(0, &build_setting->build_sources_object_shared);
    f_string_dynamic_resize(0, &build_setting->build_sources_object_static);
    f_string_dynamic_resize(0, &build_setting->path_headers);
    f_string_dynamic_resize(0, &build_setting->path_language);
    f_string_dynamic_resize(0, &build_setting->path_library_script);
    f_string_dynamic_resize(0, &build_setting->path_library_shared);
    f_string_dynamic_resize(0, &build_setting->path_library_static);
    f_string_dynamic_resize(0, &build_setting->path_object_script);
    f_string_dynamic_resize(0, &build_setting->path_object_shared);
    f_string_dynamic_resize(0, &build_setting->path_object_static);
    f_string_dynamic_resize(0, &build_setting->path_program_script);
    f_string_dynamic_resize(0, &build_setting->path_program_shared);
    f_string_dynamic_resize(0, &build_setting->path_program_static);
    f_string_dynamic_resize(0, &build_setting->path_sources);
    f_string_dynamic_resize(0, &build_setting->path_sources_object);
    f_string_dynamic_resize(0, &build_setting->process_post);
    f_string_dynamic_resize(0, &build_setting->process_pre);
    f_string_dynamic_resize(0, &build_setting->version_major);
    f_string_dynamic_resize(0, &build_setting->version_major_prefix);
    f_string_dynamic_resize(0, &build_setting->version_micro);
    f_string_dynamic_resize(0, &build_setting->version_micro_prefix);
    f_string_dynamic_resize(0, &build_setting->version_minor);
    f_string_dynamic_resize(0, &build_setting->version_minor_prefix);
    f_string_dynamic_resize(0, &build_setting->version_nano);
    f_string_dynamic_resize(0, &build_setting->version_nano_prefix);

    f_string_dynamics_resize(0, &build_setting->build_indexer_arguments);
    f_string_dynamics_resize(0, &build_setting->build_libraries);
    f_string_dynamics_resize(0, &build_setting->build_libraries_shared);
    f_string_dynamics_resize(0, &build_setting->build_libraries_static);
    f_string_dynamics_resize(0, &build_setting->build_objects_library);
    f_string_dynamics_resize(0, &build_setting->build_objects_library_shared);
    f_string_dynamics_resize(0, &build_setting->build_objects_library_static);
    f_string_dynamics_resize(0, &build_setting->build_objects_program);
    f_string_dynamics_resize(0, &build_setting->build_objects_program_shared);
    f_string_dynamics_resize(0, &build_setting->build_objects_program_static);
    f_string_dynamics_resize(0, &build_setting->build_sources_documentation);
    f_string_dynamics_resize(0, &build_setting->build_sources_headers);
    f_string_dynamics_resize(0, &build_setting->build_sources_headers_shared);
    f_string_dynamics_resize(0, &build_setting->build_sources_headers_static);
    f_string_dynamics_resize(0, &build_setting->build_sources_library);
    f_string_dynamics_resize(0, &build_setting->build_sources_library_shared);
    f_string_dynamics_resize(0, &build_setting->build_sources_library_static);
    f_string_dynamics_resize(0, &build_setting->build_sources_program);
    f_string_dynamics_resize(0, &build_setting->build_sources_program_shared);
    f_string_dynamics_resize(0, &build_setting->build_sources_program_static);
    f_string_dynamics_resize(0, &build_setting->build_sources_script);
    f_string_dynamics_resize(0, &build_setting->build_sources_setting);
    f_string_dynamics_resize(0, &build_setting->defines);
    f_string_dynamics_resize(0, &build_setting->defines_library);
    f_string_dynamics_resize(0, &build_setting->defines_library_shared);
    f_string_dynamics_resize(0, &build_setting->defines_library_static);
    f_string_dynamics_resize(0, &build_setting->defines_object);
    f_string_dynamics_resize(0, &build_setting->defines_object_shared);
    f_string_dynamics_resize(0, &build_setting->defines_object_static);
    f_string_dynamics_resize(0, &build_setting->defines_program);
    f_string_dynamics_resize(0, &build_setting->defines_program_shared);
    f_string_dynamics_resize(0, &build_setting->defines_program_static);
    f_string_dynamics_resize(0, &build_setting->defines_shared);
    f_string_dynamics_resize(0, &build_setting->defines_static);
    f_string_dynamics_resize(0, &build_setting->environment);
    f_string_dynamics_resize(0, &build_setting->flags);
    f_string_dynamics_resize(0, &build_setting->flags_library);
    f_string_dynamics_resize(0, &build_setting->flags_library_shared);
    f_string_dynamics_resize(0, &build_setting->flags_library_static);
    f_string_dynamics_resize(0, &build_setting->flags_object);
    f_string_dynamics_resize(0, &build_setting->flags_object_shared);
    f_string_dynamics_resize(0, &build_setting->flags_object_static);
    f_string_dynamics_resize(0, &build_setting->flags_program);
    f_string_dynamics_resize(0, &build_setting->flags_program_shared);
    f_string_dynamics_resize(0, &build_setting->flags_program_static);
    f_string_dynamics_resize(0, &build_setting->flags_shared);
    f_string_dynamics_resize(0, &build_setting->flags_static);
    f_string_dynamics_resize(0, &build_setting->modes);
    f_string_dynamics_resize(0, &build_setting->modes_default);
  }
#endif // _di_fake_build_setting_delete_

#ifndef _di_fake_build_stage_delete_
  void fake_build_stage_delete(fake_build_stage_t * const build_stage) {

    if (!build_stage) return;

    f_string_dynamic_resize(0, &build_stage->file_library_script);
    f_string_dynamic_resize(0, &build_stage->file_library_shared);
    f_string_dynamic_resize(0, &build_stage->file_library_static);
    f_string_dynamic_resize(0, &build_stage->file_object_script);
    f_string_dynamic_resize(0, &build_stage->file_object_shared);
    f_string_dynamic_resize(0, &build_stage->file_object_static);
    f_string_dynamic_resize(0, &build_stage->file_objects_static);
    f_string_dynamic_resize(0, &build_stage->file_process_post);
    f_string_dynamic_resize(0, &build_stage->file_process_pre);
    f_string_dynamic_resize(0, &build_stage->file_program_script);
    f_string_dynamic_resize(0, &build_stage->file_program_shared);
    f_string_dynamic_resize(0, &build_stage->file_program_static);
    f_string_dynamic_resize(0, &build_stage->file_skeleton);
    f_string_dynamic_resize(0, &build_stage->file_sources_documentation);
    f_string_dynamic_resize(0, &build_stage->file_sources_headers);
    f_string_dynamic_resize(0, &build_stage->file_sources_script);
    f_string_dynamic_resize(0, &build_stage->file_sources_settings);
  }
#endif // _di_fake_build_stage_delete_

#ifndef _di_fake_data_delete_
  void fake_data_delete(fake_data_t * const data) {

    if (!data) return;

    f_string_dynamic_resize(0, &data->path_build);
    f_string_dynamic_resize(0, &data->path_build_documentation);
    f_string_dynamic_resize(0, &data->path_build_documents);
    f_string_dynamic_resize(0, &data->path_build_includes);
    f_string_dynamic_resize(0, &data->path_build_libraries);
    f_string_dynamic_resize(0, &data->path_build_libraries_script);
    f_string_dynamic_resize(0, &data->path_build_libraries_shared);
    f_string_dynamic_resize(0, &data->path_build_libraries_static);
    f_string_dynamic_resize(0, &data->path_build_objects);
    f_string_dynamic_resize(0, &data->path_build_objects_script);
    f_string_dynamic_resize(0, &data->path_build_objects_shared);
    f_string_dynamic_resize(0, &data->path_build_objects_static);
    f_string_dynamic_resize(0, &data->path_build_programs);
    f_string_dynamic_resize(0, &data->path_build_programs_script);
    f_string_dynamic_resize(0, &data->path_build_programs_shared);
    f_string_dynamic_resize(0, &data->path_build_programs_static);
    f_string_dynamic_resize(0, &data->path_build_settings);
    f_string_dynamic_resize(0, &data->path_build_stage);

    f_string_dynamic_resize(0, &data->path_data_build);
    f_string_dynamic_resize(0, &data->path_data_documentation);
    f_string_dynamic_resize(0, &data->path_data_settings);

    f_string_dynamic_resize(0, &data->path_documents);

    f_string_dynamic_resize(0, &data->path_licenses);

    f_string_dynamic_resize(0, &data->path_work_includes);
    f_string_dynamic_resize(0, &data->path_work_libraries);
    f_string_dynamic_resize(0, &data->path_work_libraries_script);
    f_string_dynamic_resize(0, &data->path_work_libraries_shared);
    f_string_dynamic_resize(0, &data->path_work_libraries_static);
    f_string_dynamic_resize(0, &data->path_work_programs);
    f_string_dynamic_resize(0, &data->path_work_programs_script);
    f_string_dynamic_resize(0, &data->path_work_programs_shared);
    f_string_dynamic_resize(0, &data->path_work_programs_static);

    f_string_dynamic_resize(0, &data->file_data_build_defines);
    f_string_dynamic_resize(0, &data->file_data_build_dependencies);
    f_string_dynamic_resize(0, &data->file_data_build_process_post);
    f_string_dynamic_resize(0, &data->file_data_build_process_pre);
    f_string_dynamic_resize(0, &data->file_data_build_fakefile);
    f_string_dynamic_resize(0, &data->file_data_build_settings);

    f_string_dynamic_resize(0, &data->file_documents_readme);
  }
#endif // _di_fake_data_delete_

#ifndef _di_fake_main_data_delete_
  void fake_main_delete(fake_main_t * const main) {

    if (!main) return;

    fll_program_data_delete(&main->program);
    fake_setting_delete(&main->setting);

    f_string_dynamic_resize(0, &main->buffer);
    f_string_dynamic_resize(0, &main->cache_1);
    f_string_dynamic_resize(0, &main->cache_2);
    f_string_dynamic_resize(0, &main->cache_argument);
    f_string_dynamics_resize(0, &main->cache_arguments);

    f_string_dynamic_resize(0, &main->cache_map.name);
    f_string_dynamic_resize(0, &main->cache_map.value);

    f_iki_data_delete(&main->cache_iki);
  }
#endif // _di_fake_main_data_delete_

#ifndef _di_fake_make_data_delete_
  void fake_make_data_delete(fake_make_data_t * const data_make) {

    if (!data_make) return;

    fake_build_setting_delete(&data_make->setting_build);
    fake_make_setting_delete(&data_make->setting_make);

    f_string_maps_resize(0, &data_make->environment);

    f_string_dynamics_resize(0, &data_make->parameter.build);
    f_string_dynamics_resize(0, &data_make->parameter.color);
    f_string_dynamics_resize(0, &data_make->parameter.data);
    f_string_dynamics_resize(0, &data_make->parameter.define);
    f_string_dynamics_resize(0, &data_make->parameter.documents);
    f_string_dynamics_resize(0, &data_make->parameter.fakefile);
    f_string_dynamics_resize(0, &data_make->parameter.licenses);
    f_string_dynamics_resize(0, &data_make->parameter.mode);
    f_string_dynamics_resize(0, &data_make->parameter.process);
    f_string_dynamics_resize(0, &data_make->parameter.settings);
    f_string_dynamics_resize(0, &data_make->parameter.sources);
    f_string_dynamics_resize(0, &data_make->parameter.verbosity);
    f_string_dynamics_resize(0, &data_make->parameter.work);

    f_string_dynamics_resize(0, &data_make->parameter_option.build);
    f_string_dynamics_resize(0, &data_make->parameter_option.color);
    f_string_dynamics_resize(0, &data_make->parameter_option.data);
    f_string_dynamics_resize(0, &data_make->parameter_option.define);
    f_string_dynamics_resize(0, &data_make->parameter_option.documents);
    f_string_dynamics_resize(0, &data_make->parameter_option.fakefile);
    f_string_dynamics_resize(0, &data_make->parameter_option.licenses);
    f_string_dynamics_resize(0, &data_make->parameter_option.mode);
    f_string_dynamics_resize(0, &data_make->parameter_option.process);
    f_string_dynamics_resize(0, &data_make->parameter_option.settings);
    f_string_dynamics_resize(0, &data_make->parameter_option.sources);
    f_string_dynamics_resize(0, &data_make->parameter_option.verbosity);
    f_string_dynamics_resize(0, &data_make->parameter_option.work);

    f_string_dynamics_resize(0, &data_make->parameter_value.build);
    f_string_dynamics_resize(0, &data_make->parameter_value.color);
    f_string_dynamics_resize(0, &data_make->parameter_value.data);
    f_string_dynamics_resize(0, &data_make->parameter_value.define);
    f_string_dynamics_resize(0, &data_make->parameter_value.documents);
    f_string_dynamics_resize(0, &data_make->parameter_value.fakefile);
    f_string_dynamics_resize(0, &data_make->parameter_value.licenses);
    f_string_dynamics_resize(0, &data_make->parameter_value.mode);
    f_string_dynamics_resize(0, &data_make->parameter_value.process);
    f_string_dynamics_resize(0, &data_make->parameter_value.settings);
    f_string_dynamics_resize(0, &data_make->parameter_value.sources);
    f_string_dynamics_resize(0, &data_make->parameter_value.verbosity);
    f_string_dynamics_resize(0, &data_make->parameter_value.work);

    f_string_dynamics_resize(0, &data_make->path.stack);

    f_fss_nameds_resize(0, &data_make->fakefile);
  }
#endif // _di_fake_make_data_delete_

#ifndef _di_fake_make_setting_delete_
  void fake_make_setting_delete(fake_make_setting_t * const setting_make) {

    f_string_map_multis_resize(0, &setting_make->parameter);
  }
#endif // _di_fake_make_setting_delete_

#ifndef _di_fake_setting_delete_
  void fake_setting_delete(fake_setting_t * const setting) {

    if (!setting) return;

    f_string_dynamic_resize(0, &setting->build);
    f_string_dynamic_resize(0, &setting->data);
    f_string_dynamic_resize(0, &setting->documents);
    f_string_dynamic_resize(0, &setting->fakefile);
    f_string_dynamic_resize(0, &setting->licenses);
    f_string_dynamic_resize(0, &setting->process);
    f_string_dynamic_resize(0, &setting->settings);
    f_string_dynamic_resize(0, &setting->sources);
    f_string_dynamic_resize(0, &setting->work);

    f_string_dynamics_resize(0, &setting->defines);
    f_string_dynamics_resize(0, &setting->modes);

    f_uint8s_resize(0, &setting->operations);
  }
#endif // _di_fake_setting_delete_

#ifdef __cplusplus
} // extern "C"
#endif
