#include "../fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_objects_static_
  int fake_build_objects_static(fake_data_t * const data, fake_build_data_t * const data_build, const f_mode_t mode, const f_string_static_t file_stage) {

    if (!data || !data->main) return 0;
    if (data->main->setting.state.status == F_child) return data->main->program.child;
    if (F_status_is_error(data->main->setting.state.status) || f_file_exists(file_stage, F_true) == F_true) return 0;
    if (!data_build->setting.build_sources_library.used) return 0;

    fake_build_print_compile_object_static_library(&data->main->program.message);

    fake_string_dynamics_reset(&data->main->cache_arguments);

    fake_build_objects_add(data, data_build, &data->path_build_objects_static, &data_build->setting.build_objects_library, &data_build->setting.build_objects_library_static);

    if (F_status_is_error(data->main->setting.state.status)) {
      fake_print_error(&data->main->program.error, macro_fake_f(fake_build_objects_add));

      return 0;
    }

    int result = data->main->program.child;

    const f_string_dynamics_t *sources[2] = {
      &data_build->setting.build_sources_library,
      &data_build->setting.build_sources_library_static,
    };

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    uint8_t k = 0;

    for (i = 0; i < 2; ++i) {

      for (j = 0; j < sources[i]->used; ++j) {

        if (!sources[i]->array[j].used) continue;

        fake_string_dynamic_reset(&data->main->cache_1);
        fake_string_dynamic_reset(&data->main->cache_2);
        fake_string_dynamic_reset(&data->main->cache_argument);

        fake_build_path_source_string(data, data_build, &data_build->setting.path_sources, &data->main->cache_1);
        if (F_status_is_error(data->main->setting.state.status)) break;

        data->main->setting.state.status = f_string_dynamic_append_nulless(sources[i]->array[j], &data->main->cache_1);

        if (F_status_is_error(data->main->setting.state.status)) {
          fake_print_error(&data->main->program.error, macro_fake_f(f_string_dynamic_append_nulless));

          return 0;
        }

        fake_build_get_file_name_without_extension(data, sources[i]->array[j], &data->main->cache_2);

        if (F_status_is_error(data->main->setting.state.status)) {
          fake_print_error(&data->main->program.error, macro_fake_f(fake_build_get_file_name_without_extension));

          break;
        }

        data->main->setting.state.status = f_file_name_directory(sources[i]->array[j], &data->main->cache_argument);

        if (F_status_is_error(data->main->setting.state.status)) {
          fake_print_error(&data->main->program.error, macro_fake_f(f_file_name_directory));

          break;
        }

        if (data->main->cache_argument.used) {
          data->main->setting.state.status = f_string_dynamic_prepend(data->path_build_objects, &data->main->cache_argument);

          if (F_status_is_error(data->main->setting.state.status)) {
            fake_print_error(&data->main->program.error, macro_fake_f(f_string_dynamic_prepend));

            break;
          }

          data->main->setting.state.status = f_string_dynamic_append_assure(f_path_separator_s, &data->main->cache_argument);

          if (F_status_is_error(data->main->setting.state.status)) {
            fake_print_error(&data->main->program.error, macro_fake_f(f_string_dynamic_append_assure));

            break;
          }

          data->main->setting.state.status = f_directory_exists(data->main->cache_argument);

          if (data->main->setting.state.status == F_false) {
            fake_build_print_error_exist_not_directory(&data->main->program.message, data->main->cache_argument);

            data->main->setting.state.status = F_status_set_error(F_failure);

            break;
          }

          if (data->main->setting.state.status == F_file_found_not) {
            data->main->setting.state.status = f_directory_create(data->main->cache_argument, mode.directory);

            if (F_status_is_error(data->main->setting.state.status)) {
              if (F_status_set_fine(data->main->setting.state.status) == F_file_found_not) {
                fake_build_print_error_cannot_create_due_to_parent(&data->main->program.message, data->main->cache_argument);
              }
              else {
                fake_print_error_file(&data->main->program.error, macro_fake_f(f_directory_create), data->main->cache_argument, f_file_operation_create_s, fll_error_file_type_directory_e);
              }

              break;
            }

            fake_build_print_verbose_create_directory(&data->main->program.message, data->main->cache_argument);
          }

          if (F_status_is_error(data->main->setting.state.status)) {
            fake_print_error_file(&data->main->program.error, macro_fake_f(f_directory_exists), data->main->cache_argument, f_file_operation_create_s, fll_error_file_type_directory_e);

            break;
          }
        }

        if (data->main->cache_argument.used) {
          data->main->setting.state.status = F_none;
        }
        else {
          data->main->setting.state.status = f_string_dynamic_append_nulless(data->path_build_objects, &data->main->cache_argument);
        }

        if (F_status_is_error_not(data->main->setting.state.status)) {
          data->main->setting.state.status = f_string_dynamic_append_nulless(data->main->cache_2, &data->main->cache_argument);
        }

        if (F_status_is_error_not(data->main->setting.state.status)) {
          data->main->setting.state.status = f_string_dynamic_append_nulless(fake_build_parameter_object_name_suffix_s, &data->main->cache_argument);
        }

        if (F_status_is_error(data->main->setting.state.status)) {
          fake_print_error(&data->main->program.error, macro_fake_f(f_string_dynamic_append_nulless));

          return 0;
        }

        const f_string_static_t values[] = {
          data->main->cache_1,
          fake_build_parameter_object_compile_s,
          fake_build_parameter_object_static_s,
          fake_build_parameter_object_output_s,
          data->main->cache_argument,
        };

        for (k = 0; k < 5; ++k) {

          if (!values[k].used) continue;

          data->main->setting.state.status = fll_execute_arguments_add(values[k], &data->main->cache_arguments);
          if (F_status_is_error(data->main->setting.state.status)) break;
        } // for

        fake_build_arguments_standard_add(data, data_build, F_false, fake_build_type_library_e);

        if (F_status_is_error(data->main->setting.state.status)) {
          fake_print_error(&data->main->program.error, macro_fake_f(fll_execute_arguments_add));

          break;
        }

        result = fake_execute(data, data_build->environment, data_build->setting.build_compiler);

        if (F_status_is_error(data->main->setting.state.status) || data->main->setting.state.status == F_child) break;
      } // for

      if (F_status_is_error(data->main->setting.state.status) || data->main->setting.state.status == F_child) break;
    } // for

    if (F_status_is_error_not(data->main->setting.state.status) && data->main->setting.state.status != F_child) {
      fake_build_touch(data, file_stage);
    }

    return result;
  }
#endif // _di_fake_build_objects_static_

#ifdef __cplusplus
} // extern "C"
#endif