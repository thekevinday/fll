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
  int fake_build_library_script(fake_main_t * const main, fake_build_data_t * const data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t * const status) {

    if (F_status_is_error(*status) || f_file_exists(file_stage) == F_true || *status == F_child) return main->child;

    fake_build_touch(main, file_stage, status);

    return 0;
  }
#endif // _di_fake_build_library_script_

#ifndef _di_fake_build_library_shared_
  int fake_build_library_shared(fake_main_t * const main, fake_build_data_t * const data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t * const status) {

    if (F_status_is_error(*status) || f_file_exists(file_stage) == F_true || *status == F_child) return main->child;
    if (!data_build->setting.build_sources_library.used && !data_build->setting.build_sources_library_shared.used) return 0;

    if (main->output.verbosity != f_console_verbosity_quiet_e) {
      fll_print_format("%r%[Compiling shared library.%]%r", main->output.to.stream, f_string_eol_s, main->context.set.important, main->context.set.important, f_string_eol_s);
    }

    f_string_dynamics_t arguments = f_string_dynamics_t_initialize;

    *status = fake_build_objects_add(main, data_build, &main->path_build_objects_shared, &data_build->setting.build_objects_library, &data_build->setting.build_objects_library_shared, &arguments);

    if (F_status_is_error(*status)) {
      fll_error_print(main->error, F_status_set_fine(*status), "fake_build_objects_add", F_true);

      f_string_dynamics_resize(0, &arguments);

      return 0;
    }

    *status = fake_build_sources_add(main, data_build, &data_build->setting.build_sources_library, &data_build->setting.build_sources_library_shared, &arguments);

    if (F_status_is_error(*status)) {
      fll_error_print(main->error, F_status_set_fine(*status), "fake_build_sources_add", F_true);

      f_string_dynamics_resize(0, &arguments);

      return 0;
    }

    f_string_static_t parameter_file_name = f_string_static_t_initialize;
    f_string_static_t parameter_file_name_major = f_string_static_t_initialize;
    f_string_static_t parameter_file_name_minor = f_string_static_t_initialize;
    f_string_static_t parameter_file_name_micro = f_string_static_t_initialize;
    f_string_static_t parameter_file_name_nano = f_string_static_t_initialize;

    f_array_length_t strings_length = 1;

    parameter_file_name.used = fake_build_parameter_library_name_prefix_s.used + data_build->setting.build_name.used + fake_build_parameter_library_name_suffix_shared_s.used;

    if (data_build->setting.version_major.used) {
      parameter_file_name_major.used = parameter_file_name.used + data_build->setting.version_major_prefix.used + data_build->setting.version_major.used;
      strings_length = 2;

      if (data_build->setting.version_minor.used) {
        parameter_file_name_minor.used = parameter_file_name_major.used + data_build->setting.version_minor_prefix.used + data_build->setting.version_minor.used;
        strings_length = 3;

        if (data_build->setting.version_micro.used) {
          parameter_file_name_micro.used = parameter_file_name_minor.used + data_build->setting.version_micro_prefix.used + data_build->setting.version_micro.used;
          strings_length = 4;

          if (data_build->setting.version_nano.used) {
            parameter_file_name_nano.used =  parameter_file_name_micro.used + data_build->setting.version_nano_prefix.used + data_build->setting.version_nano.used;
            strings_length = 5;
          }
        }
      }
    }

    unsigned char parameter_file_name_string[parameter_file_name.used + 1];
    unsigned char parameter_file_name_major_string[parameter_file_name_major.used + 1];
    unsigned char parameter_file_name_minor_string[parameter_file_name_minor.used + 1];
    unsigned char parameter_file_name_micro_string[parameter_file_name_micro.used + 1];
    unsigned char parameter_file_name_nano_string[parameter_file_name_nano.used + 1];

    parameter_file_name.string = parameter_file_name_string;
    parameter_file_name_major.string = parameter_file_name_major_string;
    parameter_file_name_minor.string = parameter_file_name_minor_string;
    parameter_file_name_micro.string = parameter_file_name_micro_string;
    parameter_file_name_nano.string = parameter_file_name_nano_string;

    parameter_file_name.used = 0;
    parameter_file_name_major.used = 0;
    parameter_file_name_minor.used = 0;
    parameter_file_name_micro.used = 0;
    parameter_file_name_nano.used = 0;

    f_string_static_t *strings[5] = {
      &parameter_file_name,
      &parameter_file_name_major,
      &parameter_file_name_minor,
      &parameter_file_name_micro,
      &parameter_file_name_nano,
    };

    {
      uint8_t i = 0;

      for (; i < strings_length; ++i) {

        memcpy(strings[i]->string, fake_build_parameter_library_name_prefix_s.string, sizeof(unsigned char) * fake_build_parameter_library_name_prefix_s.used);

        strings[i]->used += fake_build_parameter_library_name_prefix_s.used;
      } // for

      for (i = 0; i < strings_length; ++i) {

        memcpy(strings[i]->string + strings[i]->used, data_build->setting.build_name.string, sizeof(unsigned char) * data_build->setting.build_name.used);

        strings[i]->used += data_build->setting.build_name.used;
      } // for

      for (i = 0; i < strings_length; ++i) {

        memcpy(strings[i]->string + strings[i]->used, fake_build_parameter_library_name_suffix_shared_s.string, sizeof(unsigned char) * fake_build_parameter_library_name_suffix_shared_s.used);

        strings[i]->used += fake_build_parameter_library_name_suffix_shared_s.used;
      } // for

      if (data_build->setting.version_major.used) {
        if (data_build->setting.version_major_prefix.used) {
          for (i = 1; i < strings_length; ++i) {

            memcpy(strings[i]->string + strings[i]->used, data_build->setting.version_major_prefix.string, sizeof(unsigned char) * data_build->setting.version_major_prefix.used);

            strings[i]->used += data_build->setting.version_major_prefix.used;
          } // for
        }

        for (i = 1; i < strings_length; ++i) {

          memcpy(strings[i]->string + strings[i]->used, data_build->setting.version_major.string, sizeof(unsigned char) * data_build->setting.version_major.used);

          strings[i]->used += data_build->setting.version_major.used;
        } // for

        if (data_build->setting.version_minor.used) {
          if (data_build->setting.version_minor_prefix.used) {
            for (i = 2; i < strings_length; ++i) {

              memcpy(strings[i]->string + strings[i]->used, data_build->setting.version_minor_prefix.string, sizeof(unsigned char) * data_build->setting.version_minor_prefix.used);

              strings[i]->used += data_build->setting.version_minor_prefix.used;
            } // for
          }

          for (i = 2; i < strings_length; ++i) {

            memcpy(strings[i]->string + strings[i]->used, data_build->setting.version_minor.string, sizeof(unsigned char) * data_build->setting.version_minor.used);

            strings[i]->used += data_build->setting.version_minor.used;
          } // for

          if (data_build->setting.version_micro.used) {
            if (data_build->setting.version_micro_prefix.used) {
              for (i = 3; i < strings_length; ++i) {

                memcpy(strings[i]->string + strings[i]->used, data_build->setting.version_micro_prefix.string, sizeof(unsigned char) * data_build->setting.version_micro_prefix.used);

                strings[i]->used += data_build->setting.version_micro_prefix.used;
              } // for
            }

            for (i = 3; i < strings_length; ++i) {

              memcpy(strings[i]->string + strings[i]->used, data_build->setting.version_micro.string, sizeof(unsigned char) * data_build->setting.version_micro.used);

              strings[i]->used += data_build->setting.version_micro.used;
            } // for

            if (data_build->setting.version_nano.used) {
              if (data_build->setting.version_nano_prefix.used) {
                for (i = 4; i < strings_length; ++i) {

                  memcpy(strings[i]->string + strings[i]->used, data_build->setting.version_nano_prefix.string, sizeof(unsigned char) * data_build->setting.version_nano_prefix.used);

                  strings[i]->used += data_build->setting.version_nano_prefix.used;
                } // for
              }

              for (i = 4; i < strings_length; ++i) {

                memcpy(strings[i]->string + strings[i]->used, data_build->setting.version_nano.string, sizeof(unsigned char) * data_build->setting.version_nano.used);

                strings[i]->used += data_build->setting.version_nano.used;
              } // for
            }
          }
        }
      }

      parameter_file_name_string[parameter_file_name.used] = 0;
      parameter_file_name_major_string[parameter_file_name_major.used] = 0;
      parameter_file_name_minor_string[parameter_file_name_minor.used] = 0;
      parameter_file_name_micro_string[parameter_file_name_micro.used] = 0;
      parameter_file_name_nano_string[parameter_file_name_nano.used] = 0;
    }

    {
      f_string_static_t parameter_file_path = f_string_static_t_initialize;
      f_string_static_t parameter_linker = f_string_static_t_initialize;

      parameter_file_path.used = main->path_build_libraries_shared.used;
      parameter_linker.used = fake_build_parameter_library_shared_prefix_s.used;

      if (data_build->setting.version_file == fake_build_version_type_major_e) {
        parameter_file_path.used += parameter_file_name_major.used;
      }
      else if (data_build->setting.version_file == fake_build_version_type_minor_e) {
        parameter_file_path.used += parameter_file_name_minor.used;
      }
      else if (data_build->setting.version_file == fake_build_version_type_micro_e) {
        parameter_file_path.used += parameter_file_name_micro.used;
      }
      else if (data_build->setting.version_file == fake_build_version_type_nano_e) {
        parameter_file_path.used += parameter_file_name_nano.used;
      }

      if (data_build->setting.version_target == fake_build_version_type_major_e) {
        parameter_linker.used += parameter_file_name_major.used;
      }
      else if (data_build->setting.version_target == fake_build_version_type_minor_e) {
        parameter_linker.used += parameter_file_name_minor.used;
      }
      else if (data_build->setting.version_target == fake_build_version_type_micro_e) {
        parameter_linker.used += parameter_file_name_micro.used;
      }
      else if (data_build->setting.version_target == fake_build_version_type_nano_e) {
        parameter_linker.used += parameter_file_name_nano.used;
      }

      unsigned char parameter_file_path_string[parameter_file_path.used + 1];
      unsigned char parameter_linker_string[parameter_linker.used + 1];

      parameter_file_path.string = parameter_file_path_string;
      parameter_linker.string = parameter_linker_string;

      parameter_file_path_string[parameter_file_path.used] = 0;
      parameter_linker_string[parameter_linker.used] = 0;

      memcpy(parameter_file_path_string, main->path_build_libraries_shared.string, sizeof(unsigned char) * main->path_build_libraries_shared.used);
      memcpy(parameter_linker_string, fake_build_parameter_library_shared_prefix_s.string, sizeof(unsigned char) * fake_build_parameter_library_shared_prefix_s.used);

      if (data_build->setting.version_file == fake_build_version_type_major_e) {
        memcpy(parameter_file_path_string + main->path_build_libraries_shared.used, parameter_file_name_major_string, sizeof(unsigned char) * parameter_file_name_major.used);
      }
      else if (data_build->setting.version_file == fake_build_version_type_minor_e) {
        memcpy(parameter_file_path_string + main->path_build_libraries_shared.used, parameter_file_name_minor_string, sizeof(unsigned char) * parameter_file_name_minor.used);
      }
      else if (data_build->setting.version_file == fake_build_version_type_micro_e) {
        memcpy(parameter_file_path_string + main->path_build_libraries_shared.used, parameter_file_name_micro_string, sizeof(unsigned char) * parameter_file_name_micro.used);
      }
      else if (data_build->setting.version_file == fake_build_version_type_nano_e) {
        memcpy(parameter_file_path_string + main->path_build_libraries_shared.used, parameter_file_name_nano_string, sizeof(unsigned char) * parameter_file_name_nano.used);
      }

      if (data_build->setting.version_target == fake_build_version_type_major_e) {
        memcpy(parameter_linker_string + fake_build_parameter_library_shared_prefix_s.used, parameter_file_name_major_string, sizeof(unsigned char) * parameter_file_name_major.used);
      }
      else if (data_build->setting.version_target == fake_build_version_type_minor_e) {
        memcpy(parameter_linker_string + fake_build_parameter_library_shared_prefix_s.used, parameter_file_name_minor_string, sizeof(unsigned char) * parameter_file_name_minor.used);
      }
      else if (data_build->setting.version_target == fake_build_version_type_micro_e) {
        memcpy(parameter_linker_string + fake_build_parameter_library_shared_prefix_s.used, parameter_file_name_micro_string, sizeof(unsigned char) * parameter_file_name_micro.used);
      }
      else if (data_build->setting.version_target == fake_build_version_type_nano_e) {
        memcpy(parameter_linker_string + fake_build_parameter_library_shared_prefix_s.used, parameter_file_name_nano_string, sizeof(unsigned char) * parameter_file_name_nano.used);
      }

      const f_string_static_t values[] = {
        fake_build_parameter_library_shared_s,
        parameter_linker,
        fake_build_parameter_library_output_s,
        parameter_file_path,
      };

      for (uint8_t i = 0; i < 4; ++i) {

        if (!values[i].used) continue;

        *status = fll_execute_arguments_add(values[i], &arguments);
        if (F_status_is_error(*status)) break;
      } // for

      fake_build_arguments_standard_add(main, data_build, F_true, fake_build_type_library_e, &arguments, status);

      if (F_status_is_error(*status)) {
        fll_error_print(main->error, F_status_set_fine(*status), "fll_execute_arguments_add", F_true);

        f_string_dynamics_resize(0, &arguments);

        return 0;
      }
    }

    {
      const int result = fake_execute(main, data_build->environment, data_build->setting.build_compiler, arguments, status);

      f_string_dynamics_resize(0, &arguments);

      if (F_status_is_error(*status)) return 0;
      if (*status == F_child) return result;
    }

    if (parameter_file_name_major.used) {
      f_string_static_t parameter_file_path = f_string_static_t_initialize;
      parameter_file_path.used = main->path_build_libraries_shared.used + parameter_file_name.used;

      unsigned char parameter_file_path_string[parameter_file_path.used + 1];
      parameter_file_path.string = parameter_file_path_string;
      parameter_file_path_string[parameter_file_path.used] = 0;

      memcpy(parameter_file_path_string, main->path_build_libraries_shared.string, sizeof(unsigned char) * main->path_build_libraries_shared.used);
      memcpy(parameter_file_path_string + main->path_build_libraries_shared.used, parameter_file_name.string, sizeof(unsigned char) * parameter_file_name.used);

      *status = f_file_link(parameter_file_name_major, parameter_file_path);

      if (F_status_is_error_not(*status) && main->error.verbosity >= f_console_verbosity_verbose_e) {
        fll_print_format("Linked file '%Q' to '%Q'.%r", main->output.to.stream, parameter_file_path, parameter_file_name_major, f_string_eol_s);
      }
      else if (F_status_is_error(*status)) {
        if (F_status_set_fine(*status) == F_file_found) {
          fll_error_file_print(main->error, F_status_set_fine(*status), "f_file_link", F_true, parameter_file_path, f_file_operation_link_s, fll_error_file_type_file_e);

          return 0;
        }

        fll_error_file_print(main->error, F_status_set_fine(*status), "f_file_link", F_true, parameter_file_name_major, f_file_operation_link_s, fll_error_file_type_file_e);

        return 0;
      }
    }

    if (data_build->setting.version_file != fake_build_version_type_major_e && parameter_file_name_major.used) {
      f_string_static_t parameter_file_path = f_string_static_t_initialize;

      {
        parameter_file_path.used = main->path_build_libraries_shared.used + parameter_file_name_major.used;

        unsigned char parameter_file_path_string[parameter_file_path.used + 1];
        parameter_file_path.string = parameter_file_path_string;
        parameter_file_path_string[parameter_file_path.used] = 0;

        memcpy(parameter_file_path_string, main->path_build_libraries_shared.string, sizeof(unsigned char) * main->path_build_libraries_shared.used);
        memcpy(parameter_file_path_string + main->path_build_libraries_shared.used, parameter_file_name_major.string, sizeof(unsigned char) * parameter_file_name_major.used);

        *status = f_file_link(parameter_file_name_minor, parameter_file_path);

        if (F_status_is_error_not(*status) && main->error.verbosity >= f_console_verbosity_verbose_e) {
          fll_print_format("Linked file '%Q' to '%Q'.%r", main->output.to.stream, parameter_file_path, parameter_file_name_minor, f_string_eol_s);
        }
        else if (F_status_is_error(*status)) {
          if (F_status_set_fine(*status) == F_file_found) {
            fll_error_file_print(main->error, F_status_set_fine(*status), "f_file_link", F_true, parameter_file_path, f_file_operation_link_s, fll_error_file_type_file_e);

            return 0;
          }

          fll_error_file_print(main->error, F_status_set_fine(*status), "f_file_link", F_true, parameter_file_name_minor, f_file_operation_link_s, fll_error_file_type_file_e);

          return 0;
        }
      }

      if (data_build->setting.version_file != fake_build_version_type_minor_e && parameter_file_name_minor.used) {
        {
          parameter_file_path.used = main->path_build_libraries_shared.used + parameter_file_name_minor.used;

          unsigned char parameter_file_path_string[parameter_file_path.used + 1];
          parameter_file_path.string = parameter_file_path_string;
          parameter_file_path_string[parameter_file_path.used] = 0;

          memcpy(parameter_file_path_string, main->path_build_libraries_shared.string, sizeof(unsigned char) * main->path_build_libraries_shared.used);
          memcpy(parameter_file_path_string + main->path_build_libraries_shared.used, parameter_file_name_minor.string, sizeof(unsigned char) * parameter_file_name_minor.used);

          *status = f_file_link(parameter_file_name_micro, parameter_file_path);

          if (F_status_is_error_not(*status) && main->error.verbosity >= f_console_verbosity_verbose_e) {
            fll_print_format("Linked file '%Q' to '%Q'.%r", main->output.to.stream, parameter_file_path, parameter_file_name_micro, f_string_eol_s);
          }
          else if (F_status_is_error(*status)) {
            if (F_status_set_fine(*status) == F_file_found) {
              fll_error_file_print(main->error, F_status_set_fine(*status), "f_file_link", F_true, parameter_file_path, f_file_operation_link_s, fll_error_file_type_file_e);

              return 0;
            }

            fll_error_file_print(main->error, F_status_set_fine(*status), "f_file_link", F_true, parameter_file_name_micro, f_file_operation_link_s, fll_error_file_type_file_e);

            return 0;
          }
        }

        if (data_build->setting.version_file != fake_build_version_type_micro_e && parameter_file_name_micro.used) {
          parameter_file_path.used = main->path_build_libraries_shared.used + parameter_file_name_micro.used;

          unsigned char parameter_file_path_string[parameter_file_path.used + 1];
          parameter_file_path.string = parameter_file_path_string;
          parameter_file_path_string[parameter_file_path.used] = 0;

          memcpy(parameter_file_path_string, main->path_build_libraries_shared.string, sizeof(unsigned char) * main->path_build_libraries_shared.used);
          memcpy(parameter_file_path_string + main->path_build_libraries_shared.used, parameter_file_name_micro.string, sizeof(unsigned char) * parameter_file_name_micro.used);

          *status = f_file_link(parameter_file_name_nano, parameter_file_path);

          if (F_status_is_error_not(*status) && main->error.verbosity >= f_console_verbosity_verbose_e) {
            fll_print_format("Linked file '%Q' to '%Q'.%r", main->output.to.stream, parameter_file_path, parameter_file_name_nano, f_string_eol_s);
          }
          else if (F_status_is_error(*status)) {
            if (F_status_set_fine(*status) == F_file_found) {
              fll_error_file_print(main->error, F_status_set_fine(*status), "f_file_link", F_true, parameter_file_path, f_file_operation_link_s, fll_error_file_type_file_e);

              return 0;
            }

            fll_error_file_print(main->error, F_status_set_fine(*status), "f_file_link", F_true, parameter_file_name_nano, f_file_operation_link_s, fll_error_file_type_file_e);

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
  int fake_build_library_static(fake_main_t * const main, fake_build_data_t * const data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t * const status) {

    if (F_status_is_error(*status) || f_file_exists(file_stage) == F_true || *status == F_child) return main->child;
    if (!data_build->setting.build_sources_library.used && !data_build->setting.build_sources_library_static.used) return 0;

    if (main->output.verbosity != f_console_verbosity_quiet_e) {
      fll_print_format("%r%[Compiling static library.%]%r", main->output.to.stream, f_string_eol_s, main->context.set.important, main->context.set.important, f_string_eol_s);
    }

    f_string_dynamic_t file_name = f_string_dynamic_t_initialize;
    f_string_dynamic_t source_path = f_string_dynamic_t_initialize;
    f_string_dynamics_t arguments = f_string_dynamics_t_initialize;

    f_array_length_t i = 0;

    for (; i < data_build->setting.build_indexer_arguments.used; ++i) {

      if (!data_build->setting.build_indexer_arguments.array[i].used) continue;

      *status = fll_execute_arguments_add(data_build->setting.build_indexer_arguments.array[i], &arguments);
      if (F_status_is_error(*status)) break;
    } // for

    if (F_status_is_error_not(*status)) {
      f_string_static_t destination = f_string_static_t_initialize;
      destination.used = main->path_build_libraries_static.used + fake_build_parameter_library_name_prefix_s.used;
      destination.used += data_build->setting.build_name.used + fake_build_parameter_library_name_suffix_static_s.used;

      unsigned char destination_string[destination.used + 1];
      destination.string = destination_string;
      destination_string[destination.used] = 0;
      destination.used = 0;

      memcpy(destination_string, main->path_build_libraries_static.string, sizeof(unsigned char) * main->path_build_libraries_static.used);
      destination.used += main->path_build_libraries_static.used;

      memcpy(destination_string + destination.used, fake_build_parameter_library_name_prefix_s.string, sizeof(unsigned char) * fake_build_parameter_library_name_prefix_s.used);
      destination.used += fake_build_parameter_library_name_prefix_s.used;

      memcpy(destination_string + destination.used, data_build->setting.build_name.string, sizeof(unsigned char) * data_build->setting.build_name.used);
      destination.used += data_build->setting.build_name.used;

      memcpy(destination_string + destination.used, fake_build_parameter_library_name_suffix_static_s.string, sizeof(unsigned char) * fake_build_parameter_library_name_suffix_static_s.used);
      destination.used += fake_build_parameter_library_name_suffix_static_s.used;

      *status = fll_execute_arguments_add(destination, &arguments);
    }

    if (F_status_is_error_not(*status)) {
      f_string_static_t source = f_string_static_t_initialize;
      f_array_length_t j = 0;

      const f_string_dynamics_t *sources[2] = {
        &data_build->setting.build_sources_library,
        &data_build->setting.build_sources_library_static,
      };

      for (i = 0; i < 2; ++i) {

        for (j = 0; j < sources[i]->used; ++j) {

          source_path.used = 0;

          *status = fake_build_get_file_name_without_extension(main, sources[i]->array[j], &file_name);

          if (F_status_is_error(*status)) {
            fll_error_print(main->error, F_status_set_fine(*status), "fake_build_get_file_name_without_extension", F_true);

            break;
          }

          *status = f_file_name_directory(sources[i]->array[j], &source_path);

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

            source.used = source_path.used + file_name.used + fake_build_parameter_object_name_suffix_s.used;
          }
          else {
            source.used = main->path_build_objects.used + file_name.used + fake_build_parameter_object_name_suffix_s.used;
          }

          unsigned char source_string[source.used + 1];
          source.string = source_string;
          source_string[source.used] = 0;

          if (source_path.used) {
            memcpy(source_string, source_path.string, sizeof(unsigned char) * source_path.used);
            memcpy(source_string + source_path.used, file_name.string, sizeof(unsigned char) * file_name.used);
            memcpy(source_string + source_path.used + file_name.used, fake_build_parameter_object_name_suffix_s.string, sizeof(unsigned char) * fake_build_parameter_object_name_suffix_s.used);
          }
          else {
            memcpy(source_string, main->path_build_objects.string, sizeof(unsigned char) * main->path_build_objects.used);
            memcpy(source_string + main->path_build_objects.used, file_name.string, sizeof(unsigned char) * file_name.used);
            memcpy(source_string + main->path_build_objects.used + file_name.used, fake_build_parameter_object_name_suffix_s.string, sizeof(unsigned char) * fake_build_parameter_object_name_suffix_s.used);
          }

          *status = fll_execute_arguments_add(source, &arguments);

          if (F_status_is_error(*status)) {
            fll_error_print(main->error, F_status_set_fine(*status), "fll_execute_arguments_add", F_true);

            break;
          }
        } // for
      } // for
    }

    int result = main->child;

    if (F_status_is_error_not(*status)) {
      result = fake_execute(main, data_build->environment, data_build->setting.build_indexer, arguments, status);
    }

    f_string_dynamic_resize(0, &file_name);
    f_string_dynamic_resize(0, &source_path);
    f_string_dynamics_resize(0, &arguments);

    if (F_status_is_error_not(*status) && *status != F_child) {
      fake_build_touch(main, file_stage, status);
    }

    return result;
  }
#endif // _di_fake_build_library_static_

#ifdef __cplusplus
} // extern "C"
#endif
