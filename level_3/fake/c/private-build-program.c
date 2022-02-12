#include "fake.h"
#include "private-common.h"
#include "private-fake.h"
#include "private-build.h"
#include "private-build-program.h"
#include "private-make.h"
#include "private-print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_program_script_
  int fake_build_program_script(fake_main_t * const main, const fake_build_data_t data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t *status) {

    if (F_status_is_error(*status) || f_file_exists(file_stage) == F_true || *status == F_child) return main->child;

    fake_build_touch(main, file_stage, status);

    return 0;
  }
#endif // _di_fake_build_program_script_

#ifndef _di_fake_build_program_shared_
  int fake_build_program_shared(fake_main_t * const main, const fake_build_data_t data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t *status) {

    if (F_status_is_error(*status) || f_file_exists(file_stage) == F_true || *status == F_child) return main->child;
    if (!data_build.setting.build_sources_program.used) return 0;

    if (main->output.verbosity != f_console_verbosity_quiet_e) {
      fll_print_format("%r%[Compiling shared program.%]%r", main->output.to.stream, f_string_eol_s, main->context.set.important, main->context.set.important, f_string_eol_s);
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
      else if (main->parameters.array[fake_parameter_path_sources_e].result != f_console_result_additional_e) {
        path_sources = &data_build.setting.path_sources;
      }

      f_string_static_t source = f_string_static_t_initialize;

      const f_string_dynamics_t *sources[2] = {
        &data_build.setting.build_sources_program,
        &data_build.setting.build_sources_program_shared,
      };

      f_array_length_t i = 0;
      f_array_length_t j = 0;

      for (; i < 2; ++i) {

        for (j = 0; j < sources[i]->used; ++j) {

          source.used = path_sources->used + sources[i]->array[j].used;

          char source_string[source.used + 1];
          source.string = source_string;
          source_string[source.used] = 0;

          memcpy(source_string, path_sources->string, path_sources->used);
          memcpy(source_string + path_sources->used, sources[i]->array[j].string, sources[i]->array[j].used);

          *status = fll_execute_arguments_add(source, &arguments);
          if (F_status_is_error(*status)) break;
        } // for

        if (F_status_is_error(*status)) break;
      } // for
    }

    if (F_status_is_error_not(*status)) {
      f_string_static_t parameter_file_name_path = f_string_static_t_initialize;
      parameter_file_name_path.used = main->path_build_programs_shared.used + data_build.setting.build_name.used;

      char parameter_file_name_path_string[parameter_file_name_path.used + 1];
      parameter_file_name_path.string = parameter_file_name_path_string;
      parameter_file_name_path_string[parameter_file_name_path.used] = 0;

      memcpy(parameter_file_name_path_string, main->path_build_programs_shared.string, main->path_build_programs_shared.used);
      memcpy(parameter_file_name_path_string + main->path_build_programs_shared.used, data_build.setting.build_name.string, data_build.setting.build_name.used);

      const f_string_static_t values[] = {
        fake_build_parameter_library_output_s,
        parameter_file_name_path,
      };

      for (uint8_t i = 0; i < 2; ++i) {

        if (!values[i].used) continue;

        *status = fll_execute_arguments_add(values[i], &arguments);
        if (F_status_is_error(*status)) break;
      } // for
    }

    // If project-specific library sources exist, then the -lbuild_name needs to be added to the arguments.
    if (F_status_is_error_not(*status) && data_build.setting.build_sources_library.used) {
      f_string_static_t link_project_library = f_string_static_t_initialize;
      link_project_library.used = fake_build_parameter_library_link_file_s.used + data_build.setting.build_name.used;

      char link_project_library_string[link_project_library.used + 1];
      link_project_library.string = link_project_library_string;
      link_project_library_string[link_project_library.used] = 0;

      memcpy(link_project_library_string, fake_build_parameter_library_link_file_s.string, fake_build_parameter_library_link_file_s.used);
      memcpy(link_project_library_string + fake_build_parameter_library_link_file_s.used, data_build.setting.build_name.string, data_build.setting.build_name.used);

      *status = fll_execute_arguments_add(link_project_library, &arguments);
    }

    fake_build_arguments_standard_add(main, data_build, F_true, F_false, &arguments, status);

    if (F_status_is_error(*status)) {
      fll_error_print(main->error, F_status_set_fine(*status), "fll_execute_arguments_add", F_true);

      macro_f_string_dynamics_t_delete_simple(arguments);

      return 0;
    }

    int result = fake_execute(main, data_build.environment, data_build.setting.build_compiler, arguments, status);

    macro_f_string_dynamics_t_delete_simple(arguments);

    if (F_status_is_error_not(*status) && *status != F_child) {
      fake_build_touch(main, file_stage, status);
    }

    return result;
  }
#endif // _di_fake_build_program_shared_

#ifndef _di_fake_build_program_static_
  int fake_build_program_static(fake_main_t * const main, const fake_build_data_t data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t *status) {

    if (F_status_is_error(*status) || f_file_exists(file_stage) == F_true || *status == F_child) return main->child;
    if (!data_build.setting.build_sources_program.used) return 0;

    if (main->output.verbosity != f_console_verbosity_quiet_e) {
      fll_print_format("%r%[Compiling static program.%]%r", main->output.to.stream, f_string_eol_s, main->context.set.important, main->context.set.important, f_string_eol_s);
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
      else if (main->parameters.array[fake_parameter_path_sources_e].result != f_console_result_additional_e) {
        path_sources = &data_build.setting.path_sources;
      }

      f_string_static_t source = f_string_static_t_initialize;

      const f_string_dynamics_t *sources[2] = {
        &data_build.setting.build_sources_program,
        &data_build.setting.build_sources_program_static,
      };

      f_array_length_t i = 0;
      f_array_length_t j = 0;

      for (; i < 2; ++i) {

        for (j = 0; j < sources[i]->used; ++j) {

          if (!sources[i]->array[j].used) continue;

          source.used = path_sources->used + sources[i]->array[j].used;

          char source_string[source.used + 1];
          source.string = source_string;
          source_string[source.used] = 0;

          memcpy(source_string, path_sources->string, path_sources->used);
          memcpy(source_string + path_sources->used, sources[i]->array[j].string, sources[i]->array[j].used);

          *status = fll_execute_arguments_add(source, &arguments);
          if (F_status_is_error(*status)) break;
        } // for

        if (F_status_is_error(*status)) break;
      } // for
    }

    if (F_status_is_error_not(*status)) {
      f_string_static_t source_library = f_string_static_t_initialize;
      source_library.used = main->path_build_libraries_static.used + fake_build_parameter_library_name_prefix_s.used + data_build.setting.build_name.used + fake_build_parameter_library_name_suffix_static_s.used;

      char source_library_string[source_library.used + 1];
      source_library.string = source_library_string;
      source_library_string[source_library.used] = 0;
      source_library.used = 0;

      // Only include the library if there are sources that would result in it being built.
      if (data_build.setting.build_sources_library.used) {
        memcpy(source_library_string, main->path_build_libraries_static.string, main->path_build_libraries_static.used);
        source_library.used += main->path_build_libraries_static.used;

        memcpy(source_library_string + source_library.used, fake_build_parameter_library_name_prefix_s.string, fake_build_parameter_library_name_prefix_s.used);
        source_library.used += fake_build_parameter_library_name_prefix_s.used;

        memcpy(source_library_string + source_library.used, data_build.setting.build_name.string, data_build.setting.build_name.used);
        source_library.used += data_build.setting.build_name.used;

        memcpy(source_library_string + source_library.used, fake_build_parameter_library_name_suffix_static_s.string, fake_build_parameter_library_name_suffix_static_s.used);
        source_library.used += fake_build_parameter_library_name_suffix_static_s.used;
      }

      f_string_static_t parameter_file_name_path = f_string_static_t_initialize;
      parameter_file_name_path.used = main->path_build_programs_static.used + data_build.setting.build_name.used;

      char parameter_file_name_path_string[parameter_file_name_path.used + 1];
      parameter_file_name_path.string = parameter_file_name_path_string;
      parameter_file_name_path_string[parameter_file_name_path.used] = 0;

      memcpy(parameter_file_name_path_string, main->path_build_programs_static.string, main->path_build_programs_static.used);
      memcpy(parameter_file_name_path_string + main->path_build_programs_static.used, data_build.setting.build_name.string, data_build.setting.build_name.used);

      const f_string_static_t values[] = {
        source_library,
        fake_build_parameter_library_static_s,
        fake_build_parameter_library_output_s,
        parameter_file_name_path,
      };

      for (uint8_t i = 0; i < 4; ++i) {

        if (!values[i].used) continue;

        *status = fll_execute_arguments_add(values[i], &arguments);
        if (F_status_is_error(*status)) break;
      } // for
    }

    fake_build_arguments_standard_add(main, data_build, F_false, F_false, &arguments, status);

    if (F_status_is_error(*status)) {
      fll_error_print(main->error, F_status_set_fine(*status), "fll_execute_arguments_add", F_true);

      macro_f_string_dynamics_t_delete_simple(arguments);

      return 0;
    }

    int result = fake_execute(main, data_build.environment, data_build.setting.build_compiler, arguments, status);

    macro_f_string_dynamics_t_delete_simple(arguments);

    if (F_status_is_error_not(*status) && *status != F_child) {
      fake_build_touch(main, file_stage, status);
    }

    return result;
  }
#endif // _di_fake_build_program_static_

#ifdef __cplusplus
} // extern "C"
#endif
