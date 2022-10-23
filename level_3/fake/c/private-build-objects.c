#include "fake.h"
#include "private-common.h"
#include "private-fake.h"
#include "private-build.h"
#include "private-build-objects.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_objects_static_
  int fake_build_objects_static(fake_data_t * const data, fake_build_data_t * const data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t * const status) {

    if (F_status_is_error(*status) || f_file_exists(file_stage, F_true) == F_true || *status == F_child) return data->main->child;
    if (!data_build->setting.build_sources_library.used) return 0;

    if (data->main->output.verbosity != f_console_verbosity_quiet_e && data->main->output.verbosity != f_console_verbosity_error_e) {
      fll_print_format("%r%[Compiling objects for static library.%]%r", data->main->output.to, f_string_eol_s, data->main->context.set.important, data->main->context.set.important, f_string_eol_s);
    }

    f_string_dynamics_t arguments = f_string_dynamics_t_initialize;

    *status = fake_build_objects_add(data, data_build, &data->path_build_objects_static, &data_build->setting.build_objects_library, &data_build->setting.build_objects_library_static, &arguments);

    if (F_status_is_error(*status)) {
      fll_error_print(data->main->error, F_status_set_fine(*status), "fake_build_objects_add", F_true);

      f_string_dynamics_resize(0, &arguments);

      return 0;
    }

    f_string_dynamic_t file_name = f_string_dynamic_t_initialize;
    f_string_dynamic_t destination_path = f_string_dynamic_t_initialize;
    f_string_static_t destination = f_string_static_t_initialize;
    f_string_static_t source = f_string_static_t_initialize;

    int result = data->main->child;

    const f_string_dynamics_t *sources[2] = {
      &data_build->setting.build_sources_library,
      &data_build->setting.build_sources_library_static,
    };

    f_array_length_t i = 0;
    f_array_length_t j = 0;

    for (i = 0; i < 2; ++i) {

      for (j = 0; j < sources[i]->used; ++j) {

        if (!sources[i]->array[j].used) continue;

        file_name.used = 0;
        destination_path.used = 0;

        fake_build_path_source_length(data, data_build, &data_build->setting.path_sources, &source);

        f_char_t source_string[source.used + sources[i]->array[j].used + 1];
        source.string = source_string;

        fake_build_path_source_string(data, data_build, &data_build->setting.path_sources, &source);

        memcpy(source_string + source.used, sources[i]->array[j].string, sizeof(f_char_t) * sources[i]->array[j].used);
        source.used += sources[i]->array[j].used;
        source.string[source.used] = 0;

        *status = fake_build_get_file_name_without_extension(data, sources[i]->array[j], &file_name);

        if (F_status_is_error(*status)) {
          fll_error_print(data->main->error, F_status_set_fine(*status), "fake_build_get_file_name_without_extension", F_true);

          break;
        }

        *status = f_file_name_directory(sources[i]->array[j], &destination_path);

        if (F_status_is_error(*status)) {
          fll_error_print(data->main->error, F_status_set_fine(*status), "f_file_name_directory", F_true);

          break;
        }

        if (destination_path.used) {
          *status = f_string_dynamic_prepend(data->path_build_objects, &destination_path);

          if (F_status_is_error(*status)) {
            fll_error_print(data->main->error, F_status_set_fine(*status), "f_string_dynamic_prepend", F_true);

            break;
          }

          *status = f_string_dynamic_append_assure(f_path_separator_s, &destination_path);

          if (F_status_is_error(*status)) {
            fll_error_print(data->main->error, F_status_set_fine(*status), "f_string_dynamic_append_assure", F_true);

            break;
          }

          *status = f_directory_exists(destination_path);

          if (*status == F_false) {
            if (data->main->error.verbosity > f_console_verbosity_quiet_e) {
              f_file_stream_lock(data->main->error);

              fl_print_format("%r%[%QThe path '%]", data->main->error.to, f_string_eol_s, data->main->error.context, data->main->error.prefix, data->main->error.context);
              fl_print_format("%[%Q%]", data->main->error.to, data->main->error.notable, destination_path, data->main->error.notable);
              fl_print_format("%[' exists but is not a directory.%]%r", data->main->error.to, data->main->error.context, data->main->error.context, f_string_eol_s);

              f_file_stream_unlock(data->main->error);
            }

            *status = F_status_set_error(F_failure);

            break;
          }

          if (*status == F_file_found_not) {
            *status = f_directory_create(destination_path, mode.directory);

            if (F_status_is_error(*status)) {
              if (F_status_set_fine(*status) == F_file_found_not) {
                f_file_stream_lock(data->main->error);

                fl_print_format("%r%[%QThe path '%]", data->main->error.to, f_string_eol_s, data->main->error.context, data->main->error.prefix, data->main->error.context);
                fl_print_format("%[%Q%]", data->main->error.to, data->main->error.notable, destination_path, data->main->error.notable);
                fl_print_format("%[' could not be created, a parent directory does not exist.%]%r", data->main->error.to, data->main->error.context, data->main->error.context, f_string_eol_s);

                f_file_stream_unlock(data->main->error);
              }
              else {
                fll_error_file_print(data->main->error, F_status_set_fine(*status), "f_directory_create", F_true, destination_path, f_file_operation_create_s, fll_error_file_type_directory_e);
              }

              break;
            }

            if (data->main->error.verbosity >= f_console_verbosity_verbose_e) {
              fll_print_format("Directory '%Q' created.%r", data->main->output.to, destination_path, f_string_eol_s);
            }
          }

          if (F_status_is_error(*status)) {
            fll_error_file_print(data->main->error, F_status_set_fine(*status), "f_directory_exists", F_true, destination_path, f_file_operation_create_s, fll_error_file_type_directory_e);

            break;
          }

          destination.used = destination_path.used + file_name.used + fake_build_parameter_object_name_suffix_s.used;
        }
        else {
          destination.used = data->path_build_objects.used + file_name.used + fake_build_parameter_object_name_suffix_s.used;
        }

        f_char_t destination_string[destination.used + 1];
        destination.string = destination_string;
        destination_string[destination.used] = 0;

        if (destination_path.used) {
          memcpy(destination_string, destination_path.string, sizeof(f_char_t) * destination_path.used);
          memcpy(destination_string + destination_path.used, file_name.string, sizeof(f_char_t) * file_name.used);
          memcpy(destination_string + destination_path.used + file_name.used, fake_build_parameter_object_name_suffix_s.string, sizeof(f_char_t) * fake_build_parameter_object_name_suffix_s.used);
        }
        else {
          memcpy(destination_string, data->path_build_objects.string, sizeof(f_char_t) * data->path_build_objects.used);
          memcpy(destination_string + data->path_build_objects.used, file_name.string, sizeof(f_char_t) * file_name.used);
          memcpy(destination_string + data->path_build_objects.used + file_name.used, fake_build_parameter_object_name_suffix_s.string, sizeof(f_char_t) * fake_build_parameter_object_name_suffix_s.used);
        }

        const f_string_static_t values[] = {
          source,
          fake_build_parameter_object_compile_s,
          fake_build_parameter_object_static_s,
          fake_build_parameter_object_output_s,
          destination,
        };

        for (uint8_t k = 0; k < 5; ++k) {

          if (!values[k].used) continue;

          *status = fll_execute_arguments_add(values[k], &arguments);
          if (F_status_is_error(*status)) break;
        } // for

        fake_build_arguments_standard_add(data, data_build, F_false, fake_build_type_library_e, &arguments, status);

        if (F_status_is_error(*status)) {
          fll_error_print(data->main->error, F_status_set_fine(*status), "fll_execute_arguments_add", F_true);

          break;
        }

        result = fake_execute(data, data_build->environment, data_build->setting.build_compiler, arguments, status);

        macro_f_string_dynamics_t_delete_simple(arguments);

        if (F_status_is_error(*status) || *status == F_child) break;
      } // for

      if (F_status_is_error(*status) || *status == F_child) break;
    } // for

    f_string_dynamic_resize(0, &file_name);
    f_string_dynamic_resize(0, &destination_path);
    f_string_dynamics_resize(0, &arguments);

    if (F_status_is_error_not(*status) && *status != F_child) {
      fake_build_touch(data, file_stage, status);
    }

    return result;
  }
#endif // _di_fake_build_objects_static_

#ifdef __cplusplus
} // extern "C"
#endif
