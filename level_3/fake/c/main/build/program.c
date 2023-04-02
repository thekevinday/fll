#include "../fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_program_script_
  int fake_build_program_script(fake_data_t * const data, fake_build_data_t * const data_build, const f_mode_t mode, const f_string_static_t file_stage) {

    if (!data || !data->main || !data_build) return 0;
    if (data->main->setting.state.status == F_child) return data->main->program.child;
    if (F_status_is_error(data->main->setting.state.status) || f_file_exists(file_stage, F_true) == F_true) return 0;

    fake_build_touch(data, file_stage);

    return 0;
  }
#endif // _di_fake_build_program_script_

#ifndef _di_fake_build_program_shared_
  int fake_build_program_shared(fake_data_t * const data, fake_build_data_t * const data_build, const f_mode_t mode, const f_string_static_t file_stage) {

    if (!data || !data->main || !data_build) return 0;
    if (data->main->setting.state.status == F_child) return data->main->program.child;
    if (F_status_is_error(data->main->setting.state.status) || f_file_exists(file_stage, F_true) == F_true) return 0;
    if (!data_build->setting.build_sources_program.used && !data_build->setting.build_sources_program_shared.used) return 0;

    fake_build_print_compile_program_shared(&data->main->program.message);

    fake_string_dynamics_reset(&data->main->cache_arguments);

    fake_build_objects_add(data, data_build, &data->path_build_objects_shared, &data_build->setting.build_objects_program, &data_build->setting.build_objects_program_shared);

    if (F_status_is_error(data->main->setting.state.status)) {
      fake_print_error(&data->main->program.error, macro_fake_f(fake_build_objects_add));

      return 0;
    }

    fake_build_sources_add(data, data_build, &data_build->setting.build_sources_program, &data_build->setting.build_sources_program_shared);

    if (F_status_is_error(data->main->setting.state.status)) {
      fake_print_error(&data->main->program.error, macro_fake_f(fake_build_sources_add));

      return 0;
    }

    if (F_status_is_error_not(data->main->setting.state.status)) {
      fake_string_dynamic_reset(&data->main->cache_argument);

      data->main->setting.state.status = f_string_dynamic_append_nulless(data->path_build_programs_shared, &data->main->cache_argument);

      if (F_status_is_error_not(data->main->setting.state.status)) {
        data->main->setting.state.status = f_string_dynamic_append_nulless(data_build->setting.build_name, &data->main->cache_argument);
      }

      if (F_status_is_error(data->main->setting.state.status)) {
        fake_print_error(&data->main->program.error, macro_fake_f(f_string_dynamic_append_nulless));

        return 0;
      }

      const f_string_static_t values[] = {
        fake_build_parameter_library_output_s,
        data->main->cache_argument,
      };

      for (uint8_t i = 0; i < 2; ++i) {

        if (!values[i].used) continue;

        data->main->setting.state.status = fll_execute_arguments_add(values[i], &data->main->cache_arguments);
        if (F_status_is_error(data->main->setting.state.status)) break;
      } // for
    }

    // If project-specific library sources exist, then the -lbuild_name needs to be added to the arguments.
    if (F_status_is_error_not(data->main->setting.state.status) && data_build->setting.build_sources_library.used) {
      fake_string_dynamic_reset(&data->main->cache_argument);

      data->main->setting.state.status = f_string_dynamic_append_nulless(fake_build_parameter_library_link_file_s, &data->main->cache_argument);

      if (F_status_is_error_not(data->main->setting.state.status)) {
        data->main->setting.state.status = f_string_dynamic_append_nulless(data_build->setting.build_name, &data->main->cache_argument);
      }

      if (F_status_is_error(data->main->setting.state.status)) {
        fake_print_error(&data->main->program.error, macro_fake_f(f_string_dynamic_append_nulless));

        return 0;
      }

      data->main->setting.state.status = fll_execute_arguments_add(data->main->cache_argument, &data->main->cache_arguments);
    }

    fake_build_arguments_standard_add(data, data_build, F_true, fake_build_type_program_e);

    if (F_status_is_error(data->main->setting.state.status)) {
      fake_print_error(&data->main->program.error, macro_fake_f(fll_execute_arguments_add));

      return 0;
    }

    const int result = fake_execute(data, data_build->environment, data_build->setting.build_compiler);

    if (F_status_is_error_not(data->main->setting.state.status) && data->main->setting.state.status != F_child) {
      fake_build_touch(data, file_stage);
    }

    return result;
  }
#endif // _di_fake_build_program_shared_

#ifndef _di_fake_build_program_static_
  int fake_build_program_static(fake_data_t * const data, fake_build_data_t * const data_build, const f_mode_t mode, const f_string_static_t file_stage) {

    if (!data || !data->main || !data_build) return 0;
    if (data->main->setting.state.status == F_child) return data->main->program.child;
    if (F_status_is_error(data->main->setting.state.status) || f_file_exists(file_stage, F_true) == F_true) return 0;
    if (!data_build->setting.build_sources_program.used && !data_build->setting.build_sources_program_static.used) return 0;

    fake_build_print_compile_program_static(&data->main->program.message);

    fake_string_dynamics_reset(&data->main->cache_arguments);

    fake_build_objects_add(data, data_build, &data->path_build_objects_static, &data_build->setting.build_objects_program, &data_build->setting.build_objects_program_static);

    if (F_status_is_error(data->main->setting.state.status)) {
      fake_print_error(&data->main->program.error, macro_fake_f(fake_build_objects_add));

      return 0;
    }

    fake_build_sources_add(data, data_build, &data_build->setting.build_sources_program, &data_build->setting.build_sources_program_static);

    if (F_status_is_error(data->main->setting.state.status)) {
      fake_print_error(&data->main->program.error, macro_fake_f(fake_build_sources_add));

      return 0;
    }

    if (F_status_is_error_not(data->main->setting.state.status)) {
      f_string_static_t source_library = f_string_static_t_initialize;
      source_library.used = data->path_build_libraries_static.used + fake_build_parameter_library_name_prefix_s.used + data_build->setting.build_name.used + fake_build_parameter_library_name_suffix_static_s.used;

      f_char_t source_library_string[source_library.used + 1];
      source_library.string = source_library_string;
      source_library_string[source_library.used] = 0;
      source_library.used = 0;

      // Only include the library if there are sources that would result in it being built.
      if (data_build->setting.build_sources_library.used) {
        memcpy(source_library_string, data->path_build_libraries_static.string, sizeof(f_char_t) * data->path_build_libraries_static.used);
        source_library.used += data->path_build_libraries_static.used;

        memcpy(source_library_string + source_library.used, fake_build_parameter_library_name_prefix_s.string, sizeof(f_char_t) * fake_build_parameter_library_name_prefix_s.used);
        source_library.used += fake_build_parameter_library_name_prefix_s.used;

        memcpy(source_library_string + source_library.used, data_build->setting.build_name.string, sizeof(f_char_t) * data_build->setting.build_name.used);
        source_library.used += data_build->setting.build_name.used;

        memcpy(source_library_string + source_library.used, fake_build_parameter_library_name_suffix_static_s.string, sizeof(f_char_t) * fake_build_parameter_library_name_suffix_static_s.used);
        source_library.used += fake_build_parameter_library_name_suffix_static_s.used;
      }

      f_string_static_t parameter_file_name_path = f_string_static_t_initialize;
      parameter_file_name_path.used = data->path_build_programs_static.used + data_build->setting.build_name.used;

      f_char_t parameter_file_name_path_string[parameter_file_name_path.used + 1];
      parameter_file_name_path.string = parameter_file_name_path_string;
      parameter_file_name_path_string[parameter_file_name_path.used] = 0;

      memcpy(parameter_file_name_path_string, data->path_build_programs_static.string, sizeof(f_char_t) * data->path_build_programs_static.used);
      memcpy(parameter_file_name_path_string + data->path_build_programs_static.used, data_build->setting.build_name.string, sizeof(f_char_t) * data_build->setting.build_name.used);

      const f_string_static_t values[] = {
        source_library,
        fake_build_parameter_library_static_s,
        fake_build_parameter_library_output_s,
        parameter_file_name_path,
      };

      for (uint8_t i = 0; i < 4; ++i) {

        if (!values[i].used) continue;

        data->main->setting.state.status = fll_execute_arguments_add(values[i], &data->main->cache_arguments);
        if (F_status_is_error(data->main->setting.state.status)) break;
      } // for
    }

    fake_build_arguments_standard_add(data, data_build, F_false, fake_build_type_program_e);

    if (F_status_is_error(data->main->setting.state.status)) {
      fake_print_error(&data->main->program.error, macro_fake_f(fll_execute_arguments_add));

      return 0;
    }

    int result = fake_execute(data, data_build->environment, data_build->setting.build_compiler);

    if (F_status_is_error_not(data->main->setting.state.status) && data->main->setting.state.status != F_child) {
      fake_build_touch(data, file_stage);
    }

    return result;
  }
#endif // _di_fake_build_program_static_

#ifdef __cplusplus
} // extern "C"
#endif
