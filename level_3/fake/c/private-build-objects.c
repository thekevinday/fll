#include "fake.h"
#include "private-common.h"
#include "private-fake.h"
#include "private-build.h"
#include "private-build-objects.h"
#include "private-make.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_objects_static_
  int fake_build_objects_static(fake_main_t * const main, const fake_build_data_t data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t *status) {

    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true || *status == F_child) return main->child;
    if (!data_build.setting.build_sources_library.used) return 0;

    if (main->output.verbosity != f_console_verbosity_quiet_e) {
      fll_print_format("%r%[Compiling static objects.%]%r", main->output.to.stream, f_string_eol_s, main->context.set.important, main->context.set.important, f_string_eol_s);
    }

    f_string_dynamic_t file_name = f_string_dynamic_t_initialize;
    f_string_dynamic_t destination_path = f_string_dynamic_t_initialize;
    f_string_dynamics_t arguments = f_string_dynamics_t_initialize;
    f_array_length_t source_length = 0;
    f_array_length_t destination_length = 0;

    const f_string_static_t *path_sources = &main->path_sources;

    int result = main->child;

    if (data_build.setting.path_standard) {
      path_sources = &main->path_sources_c;

      if (data_build.setting.build_language == fake_build_language_type_cpp_e) {
        path_sources = &main->path_sources_cpp;
      }
    }
    else if (main->parameters.array[fake_parameter_path_sources_e].result != f_console_result_additional_e) {
      path_sources = &data_build.setting.path_sources;
    }

    const f_string_dynamics_t *sources[2] = {
      &data_build.setting.build_sources_library,
      &data_build.setting.build_sources_library_static,
    };

    f_array_length_t i = 0;
    f_array_length_t j = 0;
    uint8_t k = 0;

    for (i = 0; i < 2; ++i) {

      for (j = 0; j < sources[i]->used; ++j) {

        file_name.used = 0;
        destination_path.used = 0;

        source_length = path_sources->used + sources[i]->array[j].used;

        char source[source_length + 1];

        memcpy(source, path_sources->string, path_sources->used);
        memcpy(source + path_sources->used, sources[i]->array[j].string, sources[i]->array[j].used);
        source[source_length] = 0;

        *status = fake_build_get_file_name_without_extension(main, sources[i]->array[j], &file_name);

        if (F_status_is_error(*status)) {
          fll_error_print(main->error, F_status_set_fine(*status), "fake_build_get_file_name_without_extension", F_true);

          break;
        }

        *status = f_file_name_directory(sources[i]->array[j].string, sources[i]->array[j].used, &destination_path);

        if (F_status_is_error(*status)) {
          fll_error_print(main->error, F_status_set_fine(*status), "f_file_name_directory", F_true);

          break;
        }

        if (destination_path.used) {
          *status = f_string_dynamic_prepend(main->path_build_objects, &destination_path);

          if (F_status_is_error(*status)) {
            fll_error_print(main->error, F_status_set_fine(*status), "f_string_dynamic_prepend", F_true);

            break;
          }

          *status = f_string_dynamic_append_assure(f_path_separator_s, &destination_path);

          if (F_status_is_error(*status)) {
            fll_error_print(main->error, F_status_set_fine(*status), "f_string_dynamic_append_assure", F_true);
            break;
          }

          *status = f_string_dynamic_terminate_after(&destination_path);

          if (F_status_is_error(*status)) {
            fll_error_print(main->error, F_status_set_fine(*status), "f_string_dynamic_terminate_after", F_true);

            break;
          }

          *status = f_directory_exists(destination_path.string);

          if (*status == F_false) {
            if (main->error.verbosity != f_console_verbosity_quiet_e) {
              flockfile(main->error.to.stream);

              fl_print_format("%r%[%QThe path '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
              fl_print_format("%[%Q%]", main->error.to.stream, main->error.notable, destination_path, main->error.notable);
              fl_print_format("%[' exists but is not a directory.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

              funlockfile(main->error.to.stream);
            }

            *status = F_status_set_error(F_failure);

            break;
          }
          else if (*status == F_file_found_not) {
            *status = f_directory_create(destination_path.string, mode.directory);

            if (F_status_is_error(*status)) {
              if (F_status_set_fine(*status) == F_file_found_not) {
                flockfile(main->error.to.stream);

                fl_print_format("%r%[%QThe path '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
                fl_print_format("%[%Q%]", main->error.to.stream, main->error.notable, destination_path, main->error.notable);
                fl_print_format("%[' could not be created, a parent directory does not exist.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

                funlockfile(main->error.to.stream);
              }
              else {
                fll_error_file_print(main->error, F_status_set_fine(*status), "f_directory_create", F_true, destination_path, f_file_operation_create_s, fll_error_file_type_directory_e);
              }

              break;
            }

            if (main->error.verbosity == f_console_verbosity_verbose_e) {
              fll_print_format("Directory '%Q' created.%r", main->output.to.stream, destination_path, f_string_eol_s);
            }
          }
          else if (F_status_is_error(*status)) {
            fll_error_file_print(main->error, F_status_set_fine(*status), "f_directory_exists", F_true, destination_path, f_file_operation_create_s, fll_error_file_type_directory_e);

            break;
          }

          destination_length = destination_path.used + file_name.used + fake_build_parameter_object_name_suffix_s.used;
        }
        else {
          destination_length = main->path_build_objects.used + file_name.used + fake_build_parameter_object_name_suffix_s.used;
        }

        char destination[destination_length + 1];

        if (destination_path.used) {
          memcpy(destination, destination_path.string, destination_path.used);
          memcpy(destination + destination_path.used, file_name.string, file_name.used);
          memcpy(destination + destination_path.used + file_name.used, fake_build_parameter_object_name_suffix_s, fake_build_parameter_object_name_suffix_s.used);
        }
        else {
          memcpy(destination, main->path_build_objects.string, main->path_build_objects.used);
          memcpy(destination + main->path_build_objects.used, file_name.string, file_name.used);
          memcpy(destination + main->path_build_objects.used + file_name.used, fake_build_parameter_object_name_suffix_s, fake_build_parameter_object_name_suffix_s.used);
        }

        destination[destination_length] = 0;

        const f_string_static_t values[] = {
          macro_f_string_static_t_initialize(source, 0, source_length),
          fake_build_parameter_object_compile_s,
          fake_build_parameter_object_static_s,
          fake_build_parameter_object_output_s,
          macro_f_string_static_t_initialize(destination, 0, destination_length),
        };

        for (uint8_t k = 0; k < 5; ++k) {

          if (!lengths[k]) continue;

          *status = fll_execute_arguments_add(values[k], &arguments);
          if (F_status_is_error(*status)) break;
        } // for

        fake_build_arguments_standard_add(main, data_build, F_false, F_true, &arguments, status);

        if (F_status_is_error(*status)) {
          fll_error_print(main->error, F_status_set_fine(*status), "fll_execute_arguments_add", F_true);

          break;
        }

        result = fake_execute(main, data_build.environment, data_build.setting.build_compiler, arguments, status);

        macro_f_string_dynamics_t_delete_simple(arguments);

        if (F_status_is_error(*status) || *status == F_child) break;
      } // for

      if (F_status_is_error(*status) || *status == F_child) break;
    } // for

    f_string_dynamic_resize(0, &file_name);
    f_string_dynamic_resize(0, &destination_path);
    f_string_dynamics_resize(0, &arguments);

    if (F_status_is_error_not(*status) && *status != F_child) {
      fake_build_touch(main, file_stage, status);
    }

    return result;
  }
#endif // _di_fake_build_objects_static_

#ifdef __cplusplus
} // extern "C"
#endif
