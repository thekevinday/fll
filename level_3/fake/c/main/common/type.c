#include "../fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_data_delete_
  void fake_build_data_delete(fake_build_data_t * const build_data) {

    if (!build_data) return;

    fake_build_setting_delete(&build_data->setting);

    f_memory_arrays_resize(0, sizeof(f_string_map_t), (void **) &build_data->environment.array, &build_data->environment.used, &build_data->environment.size, &f_string_maps_delete_callback);
  }
#endif // _di_fake_build_data_delete_

#ifndef _di_fake_build_setting_delete_
  void fake_build_setting_delete(fake_build_setting_t * const build_setting) {

    if (!build_setting) return;

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_setting->build_compiler.string, &build_setting->build_compiler.used, &build_setting->build_compiler.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_setting->build_indexer.string, &build_setting->build_indexer.used, &build_setting->build_indexer.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_setting->build_name.string, &build_setting->build_name.used, &build_setting->build_name.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_setting->build_sources_object.string, &build_setting->build_sources_object.used, &build_setting->build_sources_object.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_setting->build_sources_object_shared.string, &build_setting->build_sources_object_shared.used, &build_setting->build_sources_object_shared.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_setting->build_sources_object_static.string, &build_setting->build_sources_object_static.used, &build_setting->build_sources_object_static.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_setting->path_headers.string, &build_setting->path_headers.used, &build_setting->path_headers.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_setting->path_language.string, &build_setting->path_language.used, &build_setting->path_language.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_setting->path_library_script.string, &build_setting->path_library_script.used, &build_setting->path_library_script.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_setting->path_library_shared.string, &build_setting->path_library_shared.used, &build_setting->path_library_shared.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_setting->path_library_static.string, &build_setting->path_library_static.used, &build_setting->path_library_static.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_setting->path_object_script.string, &build_setting->path_object_script.used, &build_setting->path_object_script.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_setting->path_object_shared.string, &build_setting->path_object_shared.used, &build_setting->path_object_shared.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_setting->path_object_static.string, &build_setting->path_object_static.used, &build_setting->path_object_static.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_setting->path_program_script.string, &build_setting->path_program_script.used, &build_setting->path_program_script.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_setting->path_program_shared.string, &build_setting->path_program_shared.used, &build_setting->path_program_shared.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_setting->path_program_static.string, &build_setting->path_program_static.used, &build_setting->path_program_static.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_setting->path_sources.string, &build_setting->path_sources.used, &build_setting->path_sources.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_setting->path_sources_object.string, &build_setting->path_sources_object.used, &build_setting->path_sources_object.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_setting->process_post.string, &build_setting->process_post.used, &build_setting->process_post.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_setting->process_pre.string, &build_setting->process_pre.used, &build_setting->process_pre.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_setting->version_major.string, &build_setting->version_major.used, &build_setting->version_major.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_setting->version_major_prefix.string, &build_setting->version_major_prefix.used, &build_setting->version_major_prefix.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_setting->version_micro.string, &build_setting->version_micro.used, &build_setting->version_micro.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_setting->version_micro_prefix.string, &build_setting->version_micro_prefix.used, &build_setting->version_micro_prefix.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_setting->version_minor.string, &build_setting->version_minor.used, &build_setting->version_minor.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_setting->version_minor_prefix.string, &build_setting->version_minor_prefix.used, &build_setting->version_minor_prefix.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_setting->version_nano.string, &build_setting->version_nano.used, &build_setting->version_nano.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_setting->version_nano_prefix.string, &build_setting->version_nano_prefix.used, &build_setting->version_nano_prefix.size);

    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->build_indexer_arguments.array, &build_setting->build_indexer_arguments.used, &build_setting->build_indexer_arguments.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->build_libraries.array, &build_setting->build_libraries.used, &build_setting->build_libraries.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->build_libraries_shared.array, &build_setting->build_libraries_shared.used, &build_setting->build_libraries_shared.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->build_libraries_static.array, &build_setting->build_libraries_static.used, &build_setting->build_libraries_static.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->build_objects_library.array, &build_setting->build_objects_library.used, &build_setting->build_objects_library.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->build_objects_library_shared.array, &build_setting->build_objects_library_shared.used, &build_setting->build_objects_library_shared.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->build_objects_library_static.array, &build_setting->build_objects_library_static.used, &build_setting->build_objects_library_static.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->build_objects_program.array, &build_setting->build_objects_program.used, &build_setting->build_objects_program.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->build_objects_program_shared.array, &build_setting->build_objects_program_shared.used, &build_setting->build_objects_program_shared.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->build_objects_program_static.array, &build_setting->build_objects_program_static.used, &build_setting->build_objects_program_static.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->build_sources_documentation.array, &build_setting->build_sources_documentation.used, &build_setting->build_sources_documentation.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->build_sources_headers.array, &build_setting->build_sources_headers.used, &build_setting->build_sources_headers.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->build_sources_headers_shared.array, &build_setting->build_sources_headers_shared.used, &build_setting->build_sources_headers_shared.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->build_sources_headers_static.array, &build_setting->build_sources_headers_static.used, &build_setting->build_sources_headers_static.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->build_sources_library.array, &build_setting->build_sources_library.used, &build_setting->build_sources_library.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->build_sources_library_shared.array, &build_setting->build_sources_library_shared.used, &build_setting->build_sources_library_shared.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->build_sources_library_static.array, &build_setting->build_sources_library_static.used, &build_setting->build_sources_library_static.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->build_sources_program.array, &build_setting->build_sources_program.used, &build_setting->build_sources_program.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->build_sources_program_shared.array, &build_setting->build_sources_program_shared.used, &build_setting->build_sources_program_shared.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->build_sources_program_static.array, &build_setting->build_sources_program_static.used, &build_setting->build_sources_program_static.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->build_sources_script.array, &build_setting->build_sources_script.used, &build_setting->build_sources_script.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->build_sources_setting.array, &build_setting->build_sources_setting.used, &build_setting->build_sources_setting.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->defines.array, &build_setting->defines.used, &build_setting->defines.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->defines_library.array, &build_setting->defines_library.used, &build_setting->defines_library.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->defines_library_shared.array, &build_setting->defines_library_shared.used, &build_setting->defines_library_shared.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->defines_library_static.array, &build_setting->defines_library_static.used, &build_setting->defines_library_static.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->defines_object.array, &build_setting->defines_object.used, &build_setting->defines_object.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->defines_object_shared.array, &build_setting->defines_object_shared.used, &build_setting->defines_object_shared.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->defines_object_static.array, &build_setting->defines_object_static.used, &build_setting->defines_object_static.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->defines_program.array, &build_setting->defines_program.used, &build_setting->defines_program.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->defines_program_shared.array, &build_setting->defines_program_shared.used, &build_setting->defines_program_shared.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->defines_program_static.array, &build_setting->defines_program_static.used, &build_setting->defines_program_static.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->defines_shared.array, &build_setting->defines_shared.used, &build_setting->defines_shared.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->defines_static.array, &build_setting->defines_static.used, &build_setting->defines_static.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->environment.array, &build_setting->environment.used, &build_setting->environment.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->flags.array, &build_setting->flags.used, &build_setting->flags.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->flags_library.array, &build_setting->flags_library.used, &build_setting->flags_library.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->flags_library_shared.array, &build_setting->flags_library_shared.used, &build_setting->flags_library_shared.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->flags_library_static.array, &build_setting->flags_library_static.used, &build_setting->flags_library_static.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->flags_object.array, &build_setting->flags_object.used, &build_setting->flags_object.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->flags_object_shared.array, &build_setting->flags_object_shared.used, &build_setting->flags_object_shared.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->flags_object_static.array, &build_setting->flags_object_static.used, &build_setting->flags_object_static.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->flags_program.array, &build_setting->flags_program.used, &build_setting->flags_program.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->flags_program_shared.array, &build_setting->flags_program_shared.used, &build_setting->flags_program_shared.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->flags_program_static.array, &build_setting->flags_program_static.used, &build_setting->flags_program_static.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->flags_shared.array, &build_setting->flags_shared.used, &build_setting->flags_shared.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->flags_static.array, &build_setting->flags_static.used, &build_setting->flags_static.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->modes.array, &build_setting->modes.used, &build_setting->modes.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &build_setting->modes_default.array, &build_setting->modes_default.used, &build_setting->modes_default.size, &f_string_dynamics_delete_callback);
  }
#endif // _di_fake_build_setting_delete_

#ifndef _di_fake_build_stage_delete_
  void fake_build_stage_delete(fake_build_stage_t * const build_stage) {

    if (!build_stage) return;

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_stage->file_library_script.string, &build_stage->file_library_script.used, &build_stage->file_library_script.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_stage->file_library_shared.string, &build_stage->file_library_shared.used, &build_stage->file_library_shared.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_stage->file_library_static.string, &build_stage->file_library_static.used, &build_stage->file_library_static.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_stage->file_object_script.string, &build_stage->file_object_script.used, &build_stage->file_object_script.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_stage->file_object_shared.string, &build_stage->file_object_shared.used, &build_stage->file_object_shared.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_stage->file_object_static.string, &build_stage->file_object_static.used, &build_stage->file_object_static.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_stage->file_objects_static.string, &build_stage->file_objects_static.used, &build_stage->file_objects_static.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_stage->file_process_post.string, &build_stage->file_process_post.used, &build_stage->file_process_post.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_stage->file_process_pre.string, &build_stage->file_process_pre.used, &build_stage->file_process_pre.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_stage->file_program_script.string, &build_stage->file_program_script.used, &build_stage->file_program_script.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_stage->file_program_shared.string, &build_stage->file_program_shared.used, &build_stage->file_program_shared.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_stage->file_program_static.string, &build_stage->file_program_static.used, &build_stage->file_program_static.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_stage->file_skeleton.string, &build_stage->file_skeleton.used, &build_stage->file_skeleton.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_stage->file_sources_documentation.string, &build_stage->file_sources_documentation.used, &build_stage->file_sources_documentation.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_stage->file_sources_headers.string, &build_stage->file_sources_headers.used, &build_stage->file_sources_headers.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_stage->file_sources_script.string, &build_stage->file_sources_script.used, &build_stage->file_sources_script.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &build_stage->file_sources_settings.string, &build_stage->file_sources_settings.used, &build_stage->file_sources_settings.size);
  }
#endif // _di_fake_build_stage_delete_

#ifndef _di_fake_data_delete_
  void fake_data_delete(fake_data_t * const data) {

    if (!data) return;

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->path_build.string, &data->path_build.used, &data->path_build.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->path_build_documentation.string, &data->path_build_documentation.used, &data->path_build_documentation.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->path_build_documents.string, &data->path_build_documents.used, &data->path_build_documents.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->path_build_includes.string, &data->path_build_includes.used, &data->path_build_includes.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->path_build_libraries.string, &data->path_build_libraries.used, &data->path_build_libraries.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->path_build_libraries_script.string, &data->path_build_libraries_script.used, &data->path_build_libraries_script.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->path_build_libraries_shared.string, &data->path_build_libraries_shared.used, &data->path_build_libraries_shared.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->path_build_libraries_static.string, &data->path_build_libraries_static.used, &data->path_build_libraries_static.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->path_build_objects.string, &data->path_build_objects.used, &data->path_build_objects.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->path_build_objects_script.string, &data->path_build_objects_script.used, &data->path_build_objects_script.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->path_build_objects_shared.string, &data->path_build_objects_shared.used, &data->path_build_objects_shared.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->path_build_objects_static.string, &data->path_build_objects_static.used, &data->path_build_objects_static.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->path_build_programs.string, &data->path_build_programs.used, &data->path_build_programs.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->path_build_programs_script.string, &data->path_build_programs_script.used, &data->path_build_programs_script.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->path_build_programs_shared.string, &data->path_build_programs_shared.used, &data->path_build_programs_shared.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->path_build_programs_static.string, &data->path_build_programs_static.used, &data->path_build_programs_static.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->path_build_settings.string, &data->path_build_settings.used, &data->path_build_settings.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->path_build_stage.string, &data->path_build_stage.used, &data->path_build_stage.size);

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->path_data_build.string, &data->path_data_build.used, &data->path_data_build.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->path_data_documentation.string, &data->path_data_documentation.used, &data->path_data_documentation.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->path_data_settings.string, &data->path_data_settings.used, &data->path_data_settings.size);

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->path_documents.string, &data->path_documents.used, &data->path_documents.size);

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->path_licenses.string, &data->path_licenses.used, &data->path_licenses.size);

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->path_work_includes.string, &data->path_work_includes.used, &data->path_work_includes.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->path_work_libraries.string, &data->path_work_libraries.used, &data->path_work_libraries.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->path_work_libraries_script.string, &data->path_work_libraries_script.used, &data->path_work_libraries_script.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->path_work_libraries_shared.string, &data->path_work_libraries_shared.used, &data->path_work_libraries_shared.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->path_work_libraries_static.string, &data->path_work_libraries_static.used, &data->path_work_libraries_static.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->path_work_programs.string, &data->path_work_programs.used, &data->path_work_programs.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->path_work_programs_script.string, &data->path_work_programs_script.used, &data->path_work_programs_script.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->path_work_programs_shared.string, &data->path_work_programs_shared.used, &data->path_work_programs_shared.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->path_work_programs_static.string, &data->path_work_programs_static.used, &data->path_work_programs_static.size);

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->file_data_build_defines.string, &data->file_data_build_defines.used, &data->file_data_build_defines.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->file_data_build_dependencies.string, &data->file_data_build_dependencies.used, &data->file_data_build_dependencies.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->file_data_build_process_post.string, &data->file_data_build_process_post.used, &data->file_data_build_process_post.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->file_data_build_process_pre.string, &data->file_data_build_process_pre.used, &data->file_data_build_process_pre.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->file_data_build_fakefile.string, &data->file_data_build_fakefile.used, &data->file_data_build_fakefile.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->file_data_build_settings.string, &data->file_data_build_settings.used, &data->file_data_build_settings.size);

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &data->file_documents_readme.string, &data->file_documents_readme.used, &data->file_documents_readme.size);
  }
#endif // _di_fake_data_delete_

#ifndef _di_fake_main_delete_
  void fake_main_delete(fake_main_t * const main) {

    if (!main) return;

    fll_program_data_delete(&main->program);
    fake_setting_delete(&main->setting);

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &main->buffer.string, &main->buffer.used, &main->buffer.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &main->cache_1.string, &main->cache_1.used, &main->cache_1.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &main->cache_2.string, &main->cache_2.used, &main->cache_2.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &main->cache_argument.string, &main->cache_argument.used, &main->cache_argument.size);

    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &main->cache_arguments.array, &main->cache_arguments.used, &main->cache_arguments.size, &f_string_dynamics_delete_callback);

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &main->cache_map.name.string, &main->cache_map.name.used, &main->cache_map.name.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &main->cache_map.value.string, &main->cache_map.value.used, &main->cache_map.value.size);

    f_iki_data_delete(&main->cache_iki);

    f_directory_recurse_do_delete(&main->cache_recurse_do);
  }
#endif // _di_fake_main_delete_

#ifndef _di_fake_make_data_delete_
  void fake_make_data_delete(fake_make_data_t * const data_make) {

    if (!data_make) return;

    fake_build_setting_delete(&data_make->setting_build);
    fake_make_setting_delete(&data_make->setting_make);

    f_memory_arrays_resize(0, sizeof(f_string_map_t), (void **) &data_make->environment.array, &data_make->environment.used, &data_make->environment.size, &f_string_maps_delete_callback);

    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter.build.array, &data_make->parameter.build.used, &data_make->parameter.build.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter.color.array, &data_make->parameter.color.used, &data_make->parameter.color.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter.data.array, &data_make->parameter.data.used, &data_make->parameter.data.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter.define.array, &data_make->parameter.define.used, &data_make->parameter.define.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter.documents.array, &data_make->parameter.documents.used, &data_make->parameter.documents.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter.fakefile.array, &data_make->parameter.fakefile.used, &data_make->parameter.fakefile.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter.licenses.array, &data_make->parameter.licenses.used, &data_make->parameter.licenses.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter.mode.array, &data_make->parameter.mode.used, &data_make->parameter.mode.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter.process.array, &data_make->parameter.process.used, &data_make->parameter.process.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter.settings.array, &data_make->parameter.settings.used, &data_make->parameter.settings.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter.sources.array, &data_make->parameter.sources.used, &data_make->parameter.sources.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter.verbosity.array, &data_make->parameter.verbosity.used, &data_make->parameter.verbosity.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter.work.array, &data_make->parameter.work.used, &data_make->parameter.work.size, &f_string_dynamics_delete_callback);

    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter_option.build.array, &data_make->parameter_option.build.used, &data_make->parameter_option.build.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter_option.color.array, &data_make->parameter_option.color.used, &data_make->parameter_option.color.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter_option.data.array, &data_make->parameter_option.data.used, &data_make->parameter_option.data.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter_option.define.array, &data_make->parameter_option.define.used, &data_make->parameter_option.define.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter_option.documents.array, &data_make->parameter_option.documents.used, &data_make->parameter_option.documents.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter_option.fakefile.array, &data_make->parameter_option.fakefile.used, &data_make->parameter_option.fakefile.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter_option.licenses.array, &data_make->parameter_option.licenses.used, &data_make->parameter_option.licenses.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter_option.mode.array, &data_make->parameter_option.mode.used, &data_make->parameter_option.mode.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter_option.process.array, &data_make->parameter_option.process.used, &data_make->parameter_option.process.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter_option.settings.array, &data_make->parameter_option.settings.used, &data_make->parameter_option.settings.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter_option.sources.array, &data_make->parameter_option.sources.used, &data_make->parameter_option.sources.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter_option.verbosity.array, &data_make->parameter_option.verbosity.used, &data_make->parameter_option.verbosity.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter_option.work.array, &data_make->parameter_option.work.used, &data_make->parameter_option.work.size, &f_string_dynamics_delete_callback);

    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter_value.build.array, &data_make->parameter_value.build.used, &data_make->parameter_value.build.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter_value.color.array, &data_make->parameter_value.color.used, &data_make->parameter_value.color.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter_value.data.array, &data_make->parameter_value.data.used, &data_make->parameter_value.data.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter_value.define.array, &data_make->parameter_value.define.used, &data_make->parameter_value.define.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter_value.documents.array, &data_make->parameter_value.documents.used, &data_make->parameter_value.documents.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter_value.fakefile.array, &data_make->parameter_value.fakefile.used, &data_make->parameter_value.fakefile.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter_value.licenses.array, &data_make->parameter_value.licenses.used, &data_make->parameter_value.licenses.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter_value.mode.array, &data_make->parameter_value.mode.used, &data_make->parameter_value.mode.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter_value.process.array, &data_make->parameter_value.process.used, &data_make->parameter_value.process.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter_value.settings.array, &data_make->parameter_value.settings.used, &data_make->parameter_value.settings.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter_value.sources.array, &data_make->parameter_value.sources.used, &data_make->parameter_value.sources.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter_value.verbosity.array, &data_make->parameter_value.verbosity.used, &data_make->parameter_value.verbosity.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->parameter_value.work.array, &data_make->parameter_value.work.used, &data_make->parameter_value.work.size, &f_string_dynamics_delete_callback);

    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &data_make->path.stack.array, &data_make->path.stack.used, &data_make->path.stack.size, &f_string_dynamics_delete_callback);

    f_memory_arrays_resize(0, sizeof(f_fss_named_t), (void **) &data_make->fakefile.array, &data_make->fakefile.used, &data_make->fakefile.size, &f_fss_nameds_delete_callback);
  }
#endif // _di_fake_make_data_delete_

#ifndef _di_fake_make_setting_delete_
  void fake_make_setting_delete(fake_make_setting_t * const setting_make) {

    f_memory_arrays_resize(0, sizeof(f_string_map_multi_t), (void **) &setting_make->parameter.array, &setting_make->parameter.used, &setting_make->parameter.size, &f_string_map_multis_delete_callback);
  }
#endif // _di_fake_make_setting_delete_

#ifndef _di_fake_setting_delete_
  void fake_setting_delete(fake_setting_t * const setting) {

    if (!setting) return;

    f_memory_array_resize(0, sizeof(f_char_t), (void **) &setting->build.string, &setting->build.used, &setting->build.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &setting->data.string, &setting->data.used, &setting->data.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &setting->documents.string, &setting->documents.used, &setting->documents.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &setting->fakefile.string, &setting->fakefile.used, &setting->fakefile.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &setting->licenses.string, &setting->licenses.used, &setting->licenses.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &setting->process.string, &setting->process.used, &setting->process.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &setting->settings.string, &setting->settings.used, &setting->settings.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &setting->sources.string, &setting->sources.used, &setting->sources.size);
    f_memory_array_resize(0, sizeof(f_char_t), (void **) &setting->work.string, &setting->work.used, &setting->work.size);

    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &setting->defines.array, &setting->defines.used, &setting->defines.size, &f_string_dynamics_delete_callback);
    f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &setting->modes.array, &setting->modes.used, &setting->modes.size, &f_string_dynamics_delete_callback);

    f_memory_array_resize(0, sizeof(uint8_t), (void **) &setting->operations.array, &setting->operations.used, &setting->operations.size);
  }
#endif // _di_fake_setting_delete_

#ifdef __cplusplus
} // extern "C"
#endif
