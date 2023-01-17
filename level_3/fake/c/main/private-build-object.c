#include "fake.h"
#include "private-common.h"
#include "private-fake.h"
#include "private-build.h"
#include "private-build-object.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_object_script_
  int fake_build_object_script(fake_data_t * const data, fake_build_data_t * const data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t * const status) {

    if (F_status_is_error(*status) || f_file_exists(file_stage, F_true) == F_true || *status == F_child) return data->main->child;

    fake_build_touch(data, file_stage, status);

    return 0;
  }
#endif // _di_fake_build_object_script_

#ifndef _di_fake_build_object_shared_
  int fake_build_object_shared(fake_data_t * const data, fake_build_data_t * const data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t * const status) {

    if (F_status_is_error(*status) || f_file_exists(file_stage, F_true) == F_true || *status == F_child) return data->main->child;
    if (!data_build->setting.build_sources_object.used && !data_build->setting.build_sources_object_shared.used) return 0;

    if (data->main->message.verbosity != f_console_verbosity_quiet_e && data->main->message.verbosity != f_console_verbosity_error_e) {
      fll_print_format("%r%[Compiling shared object.%]%r", data->main->message.to, f_string_eol_s, data->main->context.set.important, data->main->context.set.important, f_string_eol_s);
    }

    f_string_dynamics_t arguments = f_string_dynamics_t_initialize;

    *status = fake_build_sources_object_add(data, data_build, &data_build->setting.build_sources_object, &data_build->setting.build_sources_object_shared, &arguments);

    if (F_status_is_error(*status)) {
      fll_error_print(data->main->error, F_status_set_fine(*status), "fake_build_sources_object_add", F_true);

      f_string_dynamics_resize(0, &arguments);

      return 0;
    }

    {
      f_string_static_t parameter_file_name_path = f_string_static_t_initialize;
      parameter_file_name_path.used = data->path_build_objects_shared.used + data_build->setting.build_name.used + fake_build_parameter_object_name_suffix_s.used;

      f_char_t parameter_file_name_path_string[parameter_file_name_path.used + 1];
      parameter_file_name_path.string = parameter_file_name_path_string;
      parameter_file_name_path_string[parameter_file_name_path.used] = 0;

      memcpy(parameter_file_name_path_string, data->path_build_objects_shared.string, sizeof(f_char_t) * data->path_build_objects_shared.used);
      memcpy(parameter_file_name_path_string + data->path_build_objects_shared.used, data_build->setting.build_name.string, sizeof(f_char_t) * data_build->setting.build_name.used);
      memcpy(parameter_file_name_path_string + data->path_build_objects_static.used + data_build->setting.build_name.used, fake_build_parameter_object_name_suffix_s.string, sizeof(f_char_t) * fake_build_parameter_object_name_suffix_s.used);

      const f_string_static_t values[] = {
        fake_build_parameter_object_compile_s,
        fake_build_parameter_object_output_s,
        parameter_file_name_path,
      };

      for (uint8_t i = 0; i < 3; ++i) {

        if (!values[i].used) continue;

        *status = fll_execute_arguments_add(values[i], &arguments);
        if (F_status_is_error(*status)) break;
      } // for
    }

    fake_build_arguments_standard_add(data, data_build, F_true, fake_build_type_object_e, &arguments, status);

    if (F_status_is_error(*status)) {
      fll_error_print(data->main->error, F_status_set_fine(*status), "fake_build_arguments_standard_add", F_true);

      macro_f_string_dynamics_t_delete_simple(arguments);

      return 0;
    }

    int result = fake_execute(data, data_build->environment, data_build->setting.build_compiler, arguments, status);

    macro_f_string_dynamics_t_delete_simple(arguments);

    if (F_status_is_error_not(*status) && *status != F_child) {
      fake_build_touch(data, file_stage, status);
    }

    return result;
  }
#endif // _di_fake_build_object_shared_

#ifndef _di_fake_build_object_static_
  int fake_build_object_static(fake_data_t * const data, fake_build_data_t * const data_build, const f_mode_t mode, const f_string_static_t file_stage, f_status_t * const status) {

    if (F_status_is_error(*status) || f_file_exists(file_stage, F_true) == F_true || *status == F_child) return data->main->child;
    if (!data_build->setting.build_sources_object.used && !data_build->setting.build_sources_object_static.used) return 0;

    if (data->main->message.verbosity != f_console_verbosity_quiet_e && data->main->message.verbosity != f_console_verbosity_error_e) {
      fll_print_format("%r%[Compiling static object.%]%r", data->main->message.to, f_string_eol_s, data->main->context.set.important, data->main->context.set.important, f_string_eol_s);
    }

    f_string_dynamics_t arguments = f_string_dynamics_t_initialize;

    *status = fake_build_sources_object_add(data, data_build, &data_build->setting.build_sources_object, &data_build->setting.build_sources_object_static, &arguments);

    if (F_status_is_error(*status)) {
      fll_error_print(data->main->error, F_status_set_fine(*status), "fake_build_sources_object_add", F_true);

      f_string_dynamics_resize(0, &arguments);

      return 0;
    }

    {
      f_string_static_t parameter_file_name_path = f_string_static_t_initialize;
      parameter_file_name_path.used = data->path_build_objects_static.used + data_build->setting.build_name.used + fake_build_parameter_object_name_suffix_s.used;

      f_char_t parameter_file_name_path_string[parameter_file_name_path.used + 1];
      parameter_file_name_path.string = parameter_file_name_path_string;
      parameter_file_name_path_string[parameter_file_name_path.used] = 0;

      memcpy(parameter_file_name_path_string, data->path_build_objects_static.string, sizeof(f_char_t) * data->path_build_objects_static.used);
      memcpy(parameter_file_name_path_string + data->path_build_objects_static.used, data_build->setting.build_name.string, sizeof(f_char_t) * data_build->setting.build_name.used);
      memcpy(parameter_file_name_path_string + data->path_build_objects_static.used + data_build->setting.build_name.used, fake_build_parameter_object_name_suffix_s.string, sizeof(f_char_t) * fake_build_parameter_object_name_suffix_s.used);

      const f_string_static_t values[] = {
        fake_build_parameter_object_compile_s,
        fake_build_parameter_object_output_s,
        parameter_file_name_path,
      };

      for (uint8_t i = 0; i < 3; ++i) {

        if (!values[i].used) continue;

        *status = fll_execute_arguments_add(values[i], &arguments);
        if (F_status_is_error(*status)) break;
      } // for
    }

    fake_build_arguments_standard_add(data, data_build, F_false, fake_build_type_object_e, &arguments, status);

    if (F_status_is_error(*status)) {
      fll_error_print(data->main->error, F_status_set_fine(*status), "fake_build_arguments_standard_add", F_true);

      macro_f_string_dynamics_t_delete_simple(arguments);

      return 0;
    }

    int result = fake_execute(data, data_build->environment, data_build->setting.build_compiler, arguments, status);

    macro_f_string_dynamics_t_delete_simple(arguments);

    if (F_status_is_error_not(*status) && *status != F_child) {
      fake_build_touch(data, file_stage, status);
    }

    return result;
  }
#endif // _di_fake_build_object_static_

#ifdef __cplusplus
} // extern "C"
#endif
