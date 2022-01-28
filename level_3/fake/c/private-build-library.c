#include "fake.h"
#include "private-common.h"
#include "private-fake.h"
#include "private-build.h"
#include "private-build-library.h"
#include "private-make.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_library_script_
  int fake_build_library_script(fake_main_t * const main, const fake_build_data_t data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t *status) {

    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true || *status == F_child) return main->child;

    fake_build_touch(main, file_stage, status);

    return 0;
  }
#endif // _di_fake_build_library_script_

#ifndef _di_fake_build_library_shared_
  int fake_build_library_shared(fake_main_t * const main, const fake_build_data_t data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t *status) {

    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true || *status == F_child) return main->child;
    if (!data_build.setting.build_sources_library.used) return 0;

    if (main->output.verbosity != f_console_verbosity_quiet_e) {
      fll_print_format("%q%[Compiling shared library.%]%q", main->output.to.stream, f_string_eol_s, main->context.set.important, main->context.set.important, f_string_eol_s);
    }

    f_string_dynamics_t arguments = f_string_dynamics_t_initialize;

    {
      const f_string_static_t *path_sources = &main->path_sources;

      if (data_build.setting.path_standard) {
        path_sources = &main->path_sources_c;

        if (data_build.setting.build_language == fake_build_language_type_cpp_e) {
          path_sources = &main->path_sources_cpp;
        }
      }
      else if (main->parameters[fake_parameter_path_sources_e].result != f_console_result_additional_e) {
        path_sources = &data_build.setting.path_sources;
      }

      f_array_length_t i = 0;
      f_array_length_t j = 0;
      f_array_length_t source_length = 0;

      const f_string_dynamics_t *sources[2] = {
        &data_build.setting.build_sources_library,
        &data_build.setting.build_sources_library_shared,
      };

      for (; i < 2; ++i) {

        for (j = 0; j < sources[i]->used; ++j) {

          if (!sources[i]->array[j].used) continue;

          source_length = path_sources->used + sources[i]->array[j].used;

          char source[source_length + 1];

          memcpy(source, path_sources->string, path_sources->used);
          memcpy(source + path_sources->used, sources[i]->array[j].string, sources[i]->array[j].used);
          source[source_length] = 0;

          *status = fll_execute_arguments_add(source, source_length, &arguments);
          if (F_status_is_error(*status)) break;
        } // for

        if (F_status_is_error(*status)) break;
      } // for

      if (F_status_is_error(*status)) {
        fll_error_print(main->error, F_status_set_fine(*status), "fll_execute_arguments_add", F_true);

        macro_f_string_dynamics_t_delete_simple(arguments);
        return 0;
      }
    }

    const f_array_length_t parameter_file_name_length = fake_build_parameter_library_name_prefix_s_length + data_build.setting.project_name.used + fake_build_parameter_library_name_suffix_shared_s_length;
    const f_array_length_t parameter_file_name_major_length = data_build.setting.version_major.used ? parameter_file_name_length + data_build.setting.version_major_prefix.used + data_build.setting.version_major.used : 0;
    const f_array_length_t parameter_file_name_minor_length = data_build.setting.version_minor.used ? parameter_file_name_major_length + data_build.setting.version_minor_prefix.used + data_build.setting.version_minor.used : 0;
    const f_array_length_t parameter_file_name_micro_length = data_build.setting.version_micro.used ? parameter_file_name_minor_length + data_build.setting.version_micro_prefix.used + data_build.setting.version_micro.used : 0;
    const f_array_length_t parameter_file_name_nano_length = data_build.setting.version_nano.used ? parameter_file_name_micro_length + data_build.setting.version_nano_prefix.used + data_build.setting.version_nano.used : 0;

    char parameter_file_name[parameter_file_name_length + 1];
    char parameter_file_name_major[parameter_file_name_major_length + 1];
    char parameter_file_name_minor[parameter_file_name_minor_length + 1];
    char parameter_file_name_micro[parameter_file_name_micro_length + 1];
    char parameter_file_name_nano[parameter_file_name_nano_length + 1];

    parameter_file_name[parameter_file_name_length] = 0;
    parameter_file_name_major[parameter_file_name_major_length] = 0;
    parameter_file_name_minor[parameter_file_name_minor_length] = 0;
    parameter_file_name_micro[parameter_file_name_micro_length] = 0;
    parameter_file_name_nano[parameter_file_name_nano_length] = 0;

    memcpy(parameter_file_name, fake_build_parameter_library_name_prefix_s, fake_build_parameter_library_name_prefix_s_length);

    if (parameter_file_name_major_length) {
      memcpy(parameter_file_name_major, fake_build_parameter_library_name_prefix_s, fake_build_parameter_library_name_prefix_s_length);

      if (parameter_file_name_minor_length) {
        memcpy(parameter_file_name_minor, fake_build_parameter_library_name_prefix_s, fake_build_parameter_library_name_prefix_s_length);

        if (parameter_file_name_micro_length) {
          memcpy(parameter_file_name_micro, fake_build_parameter_library_name_prefix_s, fake_build_parameter_library_name_prefix_s_length);

          if (parameter_file_name_nano_length) {
            memcpy(parameter_file_name_nano, fake_build_parameter_library_name_prefix_s, fake_build_parameter_library_name_prefix_s_length);
          }
        }
      }
    }

    f_array_length_t count = fake_build_parameter_library_name_prefix_s_length;

    memcpy(parameter_file_name + count, data_build.setting.project_name.string, data_build.setting.project_name.used);

    if (parameter_file_name_major_length) {
      memcpy(parameter_file_name_major + count, data_build.setting.project_name.string, data_build.setting.project_name.used);

      if (parameter_file_name_minor_length) {
        memcpy(parameter_file_name_minor + count, data_build.setting.project_name.string, data_build.setting.project_name.used);

        if (parameter_file_name_micro_length) {
          memcpy(parameter_file_name_micro + count, data_build.setting.project_name.string, data_build.setting.project_name.used);

          if (parameter_file_name_nano_length) {
            memcpy(parameter_file_name_nano + count, data_build.setting.project_name.string, data_build.setting.project_name.used);
          }
        }
      }
    }

    count += data_build.setting.project_name.used;

    memcpy(parameter_file_name + count, fake_build_parameter_library_name_suffix_shared_s, fake_build_parameter_library_name_suffix_shared_s_length);

    if (parameter_file_name_major_length) {
      memcpy(parameter_file_name_major + count, fake_build_parameter_library_name_suffix_shared_s, fake_build_parameter_library_name_suffix_shared_s_length);

      if (parameter_file_name_minor_length) {
        memcpy(parameter_file_name_minor + count, fake_build_parameter_library_name_suffix_shared_s, fake_build_parameter_library_name_suffix_shared_s_length);

        if (parameter_file_name_micro_length) {
          memcpy(parameter_file_name_micro + count, fake_build_parameter_library_name_suffix_shared_s, fake_build_parameter_library_name_suffix_shared_s_length);

          if (parameter_file_name_nano_length) {
            memcpy(parameter_file_name_nano + count, fake_build_parameter_library_name_suffix_shared_s, fake_build_parameter_library_name_suffix_shared_s_length);
          }
        }
      }
    }

    if (parameter_file_name_major_length) {
      count += fake_build_parameter_library_name_suffix_shared_s_length;

      if (data_build.setting.version_major_prefix.used) {
        memcpy(parameter_file_name_major + count, data_build.setting.version_major_prefix.string, data_build.setting.version_major_prefix.used);

        if (parameter_file_name_minor_length) {
          memcpy(parameter_file_name_minor + count, data_build.setting.version_major_prefix.string, data_build.setting.version_major_prefix.used);

          if (parameter_file_name_micro_length) {
            memcpy(parameter_file_name_micro + count, data_build.setting.version_major_prefix.string, data_build.setting.version_major_prefix.used);

            if (parameter_file_name_nano_length) {
              memcpy(parameter_file_name_nano + count, data_build.setting.version_major_prefix.string, data_build.setting.version_major_prefix.used);
            }
          }
        }

        count += data_build.setting.version_major_prefix.used;
      }

      memcpy(parameter_file_name_major + count, data_build.setting.version_major.string, data_build.setting.version_major.used);

      if (parameter_file_name_minor_length) {
        memcpy(parameter_file_name_minor + count, data_build.setting.version_major.string, data_build.setting.version_major.used);

        if (parameter_file_name_micro_length) {
          memcpy(parameter_file_name_micro + count, data_build.setting.version_major.string, data_build.setting.version_major.used);

          if (parameter_file_name_nano_length) {
            memcpy(parameter_file_name_nano + count, data_build.setting.version_major.string, data_build.setting.version_major.used);
          }
        }
      }

      if (parameter_file_name_minor_length) {
        count += data_build.setting.version_major.used;

        if (data_build.setting.version_minor_prefix.used) {
          memcpy(parameter_file_name_minor + count, data_build.setting.version_minor_prefix.string, data_build.setting.version_minor_prefix.used);

          if (parameter_file_name_micro_length) {
            memcpy(parameter_file_name_micro + count, data_build.setting.version_minor_prefix.string, data_build.setting.version_minor_prefix.used);

            if (parameter_file_name_nano_length) {
              memcpy(parameter_file_name_nano + count, data_build.setting.version_minor_prefix.string, data_build.setting.version_minor_prefix.used);
            }
          }

          count += data_build.setting.version_minor_prefix.used;
        }

        memcpy(parameter_file_name_minor + count, data_build.setting.version_minor.string, data_build.setting.version_minor.used);

        if (parameter_file_name_micro_length) {
          memcpy(parameter_file_name_micro + count, data_build.setting.version_minor.string, data_build.setting.version_minor.used);

          if (parameter_file_name_nano_length) {
            memcpy(parameter_file_name_nano + count, data_build.setting.version_minor.string, data_build.setting.version_minor.used);
          }
        }

        if (parameter_file_name_micro_length) {
          count += data_build.setting.version_minor.used;

          if (data_build.setting.version_micro_prefix.used) {
            memcpy(parameter_file_name_micro + count, data_build.setting.version_micro_prefix.string, data_build.setting.version_micro_prefix.used);

            if (parameter_file_name_nano_length) {
              memcpy(parameter_file_name_nano + count, data_build.setting.version_micro_prefix.string, data_build.setting.version_micro_prefix.used);
            }

            count += data_build.setting.version_micro_prefix.used;
          }

          memcpy(parameter_file_name_micro + count, data_build.setting.version_micro.string, data_build.setting.version_micro.used);

          if (parameter_file_name_nano_length) {
            memcpy(parameter_file_name_nano + count, data_build.setting.version_micro.string, data_build.setting.version_micro.used);

            count += data_build.setting.version_micro.used;

            if (data_build.setting.version_nano_prefix.used) {
              memcpy(parameter_file_name_nano + count, data_build.setting.version_nano_prefix.string, data_build.setting.version_nano_prefix.used);
              count += data_build.setting.version_nano_prefix.used;
            }

            memcpy(parameter_file_name_nano + count, data_build.setting.version_nano.string, data_build.setting.version_nano.used);
          }
        }
      }
    }

    {
      f_array_length_t parameter_linker_length = fake_build_parameter_library_shared_prefix_s_length;
      f_array_length_t parameter_file_path_length = main->path_build_libraries_shared.used;

      if (data_build.setting.version_file == fake_build_version_type_major_e) {
        parameter_file_path_length += parameter_file_name_major_length;
      }
      else if (data_build.setting.version_file == fake_build_version_type_minor_e) {
        parameter_file_path_length += parameter_file_name_minor_length;
      }
      else if (data_build.setting.version_file == fake_build_version_type_micro_e) {
        parameter_file_path_length += parameter_file_name_micro_length;
      }
      else if (data_build.setting.version_file == fake_build_version_type_nano_e) {
        parameter_file_path_length += parameter_file_name_nano_length;
      }

      if (data_build.setting.version_target == fake_build_version_type_major_e) {
        parameter_linker_length += parameter_file_name_major_length;
      }
      else if (data_build.setting.version_target == fake_build_version_type_minor_e) {
        parameter_linker_length += parameter_file_name_minor_length;
      }
      else if (data_build.setting.version_target == fake_build_version_type_micro_e) {
        parameter_linker_length += parameter_file_name_micro_length;
      }
      else if (data_build.setting.version_target == fake_build_version_type_nano_e) {
        parameter_linker_length += parameter_file_name_nano_length;
      }

      char parameter_linker[parameter_linker_length + 1];
      char parameter_file_path[parameter_file_path_length + 1];

      memcpy(parameter_linker, fake_build_parameter_library_shared_prefix_s, fake_build_parameter_library_shared_prefix_s_length);
      memcpy(parameter_file_path, main->path_build_libraries_shared.string, main->path_build_libraries_shared.used);

      if (data_build.setting.version_file == fake_build_version_type_major_e) {
        memcpy(parameter_file_path + main->path_build_libraries_shared.used, parameter_file_name_major, parameter_file_name_major_length);
      }
      else if (data_build.setting.version_file == fake_build_version_type_minor_e) {
        memcpy(parameter_file_path + main->path_build_libraries_shared.used, parameter_file_name_minor, parameter_file_name_minor_length);
      }
      else if (data_build.setting.version_file == fake_build_version_type_micro_e) {
        memcpy(parameter_file_path + main->path_build_libraries_shared.used, parameter_file_name_micro, parameter_file_name_micro_length);
      }
      else if (data_build.setting.version_file == fake_build_version_type_nano_e) {
        memcpy(parameter_file_path + main->path_build_libraries_shared.used, parameter_file_name_nano, parameter_file_name_nano_length);
      }

      if (data_build.setting.version_target == fake_build_version_type_major_e) {
        memcpy(parameter_linker + fake_build_parameter_library_shared_prefix_s_length, parameter_file_name_major, parameter_file_name_major_length);
      }
      else if (data_build.setting.version_target == fake_build_version_type_minor_e) {
        memcpy(parameter_linker + fake_build_parameter_library_shared_prefix_s_length, parameter_file_name_minor, parameter_file_name_minor_length);
      }
      else if (data_build.setting.version_target == fake_build_version_type_micro_e) {
        memcpy(parameter_linker + fake_build_parameter_library_shared_prefix_s_length, parameter_file_name_micro, parameter_file_name_micro_length);
      }
      else if (data_build.setting.version_target == fake_build_version_type_nano_e) {
        memcpy(parameter_linker + fake_build_parameter_library_shared_prefix_s_length, parameter_file_name_nano, parameter_file_name_nano_length);
      }

      parameter_linker[parameter_linker_length] = 0;
      parameter_file_path[parameter_file_path_length] = 0;

      const f_string_t values[] = {
        fake_build_parameter_library_shared_s,
        parameter_linker,
        fake_build_parameter_library_output_s,
        parameter_file_path,
      };

      const f_array_length_t lengths[] = {
        fake_build_parameter_library_shared_s_length,
        parameter_linker_length,
        fake_build_parameter_library_output_s_length,
        parameter_file_path_length,
      };

      for (uint8_t i = 0; i < 4; ++i) {

        if (!lengths[i]) continue;

        *status = fll_execute_arguments_add(values[i], lengths[i], &arguments);
        if (F_status_is_error(*status)) break;
      } // for

      fake_build_arguments_standard_add(main, data_build, F_true, F_true, &arguments, status);

      if (F_status_is_error(*status)) {
        fll_error_print(main->error, F_status_set_fine(*status), "fll_execute_arguments_add", F_true);

        macro_f_string_dynamics_t_delete_simple(arguments);

        return 0;
      }
    }

    {
      const int result = fake_execute(main, data_build.environment, data_build.setting.build_compiler, arguments, status);

      macro_f_string_dynamics_t_delete_simple(arguments);

      if (F_status_is_error(*status)) return 0;
      if (*status == F_child) return result;
    }

    if (parameter_file_name_major_length) {
      f_array_length_t parameter_file_path_length = main->path_build_libraries_shared.used + parameter_file_name_length;

      char parameter_file_path[parameter_file_path_length + 1];

      memcpy(parameter_file_path, main->path_build_libraries_shared.string, main->path_build_libraries_shared.used);
      memcpy(parameter_file_path + main->path_build_libraries_shared.used, parameter_file_name, parameter_file_name_length);

      parameter_file_path[parameter_file_path_length] = 0;

      *status = f_file_link(parameter_file_name_major, parameter_file_path);

      if (F_status_is_error_not(*status) && main->error.verbosity == f_console_verbosity_verbose_e) {
        fll_print_format("Linked file '%S' to '%S'.%q", main->output.to.stream, parameter_file_path, parameter_file_name_major, f_string_eol_s);
      }
      else if (F_status_is_error(*status)) {
        if (F_status_set_fine(*status) == F_file_found) {
          fll_error_file_print(main->error, F_status_set_fine(*status), "f_file_link", F_true, parameter_file_path, "link", fll_error_file_type_file_e);

          return 0;
        }

        fll_error_file_print(main->error, F_status_set_fine(*status), "f_file_link", F_true, parameter_file_name_major, "link", fll_error_file_type_file_e);

        return 0;
      }
    }

    if (data_build.setting.version_file != fake_build_version_type_major_e && parameter_file_name_major_length) {

      f_array_length_t parameter_file_path_length = main->path_build_libraries_shared.used + parameter_file_name_major_length;

      char parameter_file_path[parameter_file_path_length + 1];

      memcpy(parameter_file_path, main->path_build_libraries_shared.string, main->path_build_libraries_shared.used);
      memcpy(parameter_file_path + main->path_build_libraries_shared.used, parameter_file_name_major, parameter_file_name_major_length);

      parameter_file_path[parameter_file_path_length] = 0;

      *status = f_file_link(parameter_file_name_minor, parameter_file_path);

      if (F_status_is_error_not(*status) && main->error.verbosity == f_console_verbosity_verbose_e) {
        fll_print_format("Linked file '%S' to '%S'.%q", main->output.to.stream, parameter_file_path, parameter_file_name_minor, f_string_eol_s);
      }
      else if (F_status_is_error(*status)) {
        if (F_status_set_fine(*status) == F_file_found) {
          fll_error_file_print(main->error, F_status_set_fine(*status), "f_file_link", F_true, parameter_file_path, "link", fll_error_file_type_file_e);

          return 0;
        }

        fll_error_file_print(main->error, F_status_set_fine(*status), "f_file_link", F_true, parameter_file_name_minor, "link", fll_error_file_type_file_e);

        return 0;
      }

      if (data_build.setting.version_file != fake_build_version_type_minor_e && parameter_file_name_minor_length) {

        f_array_length_t parameter_file_path_length = main->path_build_libraries_shared.used + parameter_file_name_minor_length;

        char parameter_file_path[parameter_file_path_length + 1];

        memcpy(parameter_file_path, main->path_build_libraries_shared.string, main->path_build_libraries_shared.used);
        memcpy(parameter_file_path + main->path_build_libraries_shared.used, parameter_file_name_minor, parameter_file_name_minor_length);

        parameter_file_path[parameter_file_path_length] = 0;

        *status = f_file_link(parameter_file_name_micro, parameter_file_path);

        if (F_status_is_error_not(*status) && main->error.verbosity == f_console_verbosity_verbose_e) {
          fll_print_format("Linked file '%S' to '%S'.%q", main->output.to.stream, parameter_file_path, parameter_file_name_micro, f_string_eol_s);
        }
        else if (F_status_is_error(*status)) {
          if (F_status_set_fine(*status) == F_file_found) {
            fll_error_file_print(main->error, F_status_set_fine(*status), "f_file_link", F_true, parameter_file_path, "link", fll_error_file_type_file_e);

            return 0;
          }

          fll_error_file_print(main->error, F_status_set_fine(*status), "f_file_link", F_true, parameter_file_name_micro, "link", fll_error_file_type_file_e);

          return 0;
        }

        if (data_build.setting.version_file != fake_build_version_type_micro_e && parameter_file_name_micro_length) {

          f_array_length_t parameter_file_path_length = main->path_build_libraries_shared.used + parameter_file_name_micro_length;

          char parameter_file_path[parameter_file_path_length + 1];

          memcpy(parameter_file_path, main->path_build_libraries_shared.string, main->path_build_libraries_shared.used);
          memcpy(parameter_file_path + main->path_build_libraries_shared.used, parameter_file_name_micro, parameter_file_name_micro_length);

          parameter_file_path[parameter_file_path_length] = 0;

          *status = f_file_link(parameter_file_name_nano, parameter_file_path);

          if (F_status_is_error_not(*status) && main->error.verbosity == f_console_verbosity_verbose_e) {
            fll_print_format("Linked file '%S' to '%S'.%q", main->output.to.stream, parameter_file_path, parameter_file_name_nano, f_string_eol_s);
          }
          else if (F_status_is_error(*status)) {
            if (F_status_set_fine(*status) == F_file_found) {
              fll_error_file_print(main->error, F_status_set_fine(*status), "f_file_link", F_true, parameter_file_path, "link", fll_error_file_type_file_e);

              return 0;
            }

            fll_error_file_print(main->error, F_status_set_fine(*status), "f_file_link", F_true, parameter_file_name_nano, "link", fll_error_file_type_file_e);

            return 0;
          }
        }
      }
    }

    fake_build_touch(main, file_stage, status);

    return 0;
  }
#endif // _di_fake_build_library_shared_

#ifndef _di_fake_build_library_static_
  int fake_build_library_static(fake_main_t * const main, const fake_build_data_t data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t *status) {

    if (F_status_is_error(*status) || f_file_exists(file_stage.string) == F_true || *status == F_child) return main->child;
    if (!data_build.setting.build_sources_library.used) return 0;

    if (main->output.verbosity != f_console_verbosity_quiet_e) {
      fll_print_format("%q%[Compiling static library.%]%q", main->output.to.stream, f_string_eol_s, main->context.set.important, main->context.set.important, f_string_eol_s);
    }

    f_string_dynamic_t file_name = f_string_dynamic_t_initialize;
    f_string_dynamic_t source_path = f_string_dynamic_t_initialize;
    f_string_dynamics_t arguments = f_string_dynamics_t_initialize;

    f_array_length_t i = 0;

    for (; i < data_build.setting.build_indexer_arguments.used; ++i) {

      if (!data_build.setting.build_indexer_arguments.array[i].used) continue;

      *status = fll_execute_arguments_add(data_build.setting.build_indexer_arguments.array[i].string, data_build.setting.build_indexer_arguments.array[i].used, &arguments);
      if (F_status_is_error(*status)) break;
    } // for

    if (F_status_is_error_not(*status)) {
      f_array_length_t destination_length = main->path_build_libraries_static.used + fake_build_parameter_library_name_prefix_s_length;
      destination_length += data_build.setting.project_name.used + fake_build_parameter_library_name_suffix_static_s_length;

      char destination[destination_length + 1];

      destination_length = 0;

      memcpy(destination, main->path_build_libraries_static.string, main->path_build_libraries_static.used);
      destination_length += main->path_build_libraries_static.used;

      memcpy(destination + destination_length, fake_build_parameter_library_name_prefix_s, fake_build_parameter_library_name_prefix_s_length);
      destination_length += fake_build_parameter_library_name_prefix_s_length;

      memcpy(destination + destination_length, data_build.setting.project_name.string, data_build.setting.project_name.used);
      destination_length += data_build.setting.project_name.used;

      memcpy(destination + destination_length, fake_build_parameter_library_name_suffix_static_s, fake_build_parameter_library_name_suffix_static_s_length);
      destination_length += fake_build_parameter_library_name_suffix_static_s_length;

      destination[destination_length] = 0;

      *status = fll_execute_arguments_add(destination, destination_length, &arguments);
    }

    if (F_status_is_error_not(*status)) {
      f_array_length_t source_length = 0;
      f_array_length_t j = 0;

      const f_string_dynamics_t *sources[2] = {
        &data_build.setting.build_sources_library,
        &data_build.setting.build_sources_library_static,
      };

      for (i = 0; i < 2; ++i) {

        for (j = 0; j < sources[i]->used; ++j) {

          source_path.used = 0;

          *status = fake_build_get_file_name_without_extension(main, sources[i]->array[j], &file_name);

          if (F_status_is_error(*status)) {
            fll_error_print(main->error, F_status_set_fine(*status), "fake_build_get_file_name_without_extension", F_true);

            break;
          }

          *status = f_file_name_directory(sources[i]->array[j].string, sources[i]->array[j].used, &source_path);

          if (F_status_is_error(*status)) {
            fll_error_print(main->error, F_status_set_fine(*status), "f_file_name_directory", F_true);

            break;
          }

          if (source_path.used) {
            *status = f_string_dynamic_prepend(main->path_build_objects, &source_path);

            if (F_status_is_error(*status)) {
              fll_error_print(main->error, F_status_set_fine(*status), "f_string_dynamic_prepend", F_true);

              break;
            }

            *status = f_string_dynamic_append_assure(f_path_separator_s, &source_path);

            if (F_status_is_error(*status)) {
              fll_error_print(main->error, F_status_set_fine(*status), "f_string_dynamic_append_assure", F_true);

              break;
            }

            *status = f_string_dynamic_terminate_after(&source_path);

            if (F_status_is_error(*status)) {
              fll_error_print(main->error, F_status_set_fine(*status), "f_string_dynamic_terminate_after", F_true);

              break;
            }

            source_length = source_path.used + file_name.used + fake_build_parameter_object_name_suffix_s_length;
          }
          else {
            source_length = main->path_build_objects.used + file_name.used + fake_build_parameter_object_name_suffix_s_length;
          }

          char source[source_length + 1];

          if (source_path.used) {
            memcpy(source, source_path.string, source_path.used);
            memcpy(source + source_path.used, file_name.string, file_name.used);
            memcpy(source + source_path.used + file_name.used, fake_build_parameter_object_name_suffix_s, fake_build_parameter_object_name_suffix_s_length);
          }
          else {
            memcpy(source, main->path_build_objects.string, main->path_build_objects.used);
            memcpy(source + main->path_build_objects.used, file_name.string, file_name.used);
            memcpy(source + main->path_build_objects.used + file_name.used, fake_build_parameter_object_name_suffix_s, fake_build_parameter_object_name_suffix_s_length);
          }

          source[source_length] = 0;

          *status = fll_execute_arguments_add(source, source_length, &arguments);

          if (F_status_is_error(*status)) {
            fll_error_print(main->error, F_status_set_fine(*status), "fll_execute_arguments_add", F_true);

            break;
          }
        } // for
      } // for
    }

    int result = main->child;

    if (F_status_is_error_not(*status)) {
      result = fake_execute(main, data_build.environment, data_build.setting.build_indexer, arguments, status);
    }

    macro_f_string_dynamic_t_delete_simple(file_name);
    macro_f_string_dynamic_t_delete_simple(source_path);
    macro_f_string_dynamics_t_delete_simple(arguments);

    if (F_status_is_error_not(*status) && *status != F_child) {
      fake_build_touch(main, file_stage, status);
    }

    return result;
  }
#endif // _di_fake_build_library_static_

#ifdef __cplusplus
} // extern "C"
#endif
