#include "../fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_build_object_script_
  int fake_build_object_script(fake_data_t * const data, fake_build_data_t * const data_build, const f_mode_t mode, const f_string_static_t file_stage) {

    if (!data || !data->main || !data_build) return 0;
    if (data->main->setting.state.status == F_child) return data->main->program.child;
    if (F_status_is_error(data->main->setting.state.status) || f_file_exists(file_stage, F_true) == F_true) return 0;

    fake_build_touch(data, file_stage);

    return 0;
  }
#endif // _di_fake_build_object_script_

#ifndef _di_fake_build_object_shared_
  int fake_build_object_shared(fake_data_t * const data, fake_build_data_t * const data_build, const f_mode_t mode, const f_string_static_t file_stage) {

    if (!data || !data->main || !data_build) return 0;
    if (data->main->setting.state.status == F_child) return data->main->program.child;
    if (F_status_is_error(data->main->setting.state.status) || f_file_exists(file_stage, F_true) == F_true) return 0;
    if (!data_build->setting.build_sources_object.used && !data_build->setting.build_sources_object_shared.used) return 0;

    fake_build_print_compile_object_shared(&data->main->program.message);

    fake_string_dynamic_reset(&data->main->cache_argument);
    fake_string_dynamics_reset(&data->main->cache_arguments);

    fake_build_sources_object_add(data, data_build, &data_build->setting.build_sources_object, &data_build->setting.build_sources_object_shared);

    if (F_status_is_error(data->main->setting.state.status)) {
      fake_print_error(&data->main->program.error, macro_fake_f(fake_build_sources_object_add));

      return 0;
    }

    {
      data->main->setting.state.status = f_string_dynamic_append_nulless(data->path_build_objects_shared, &data->main->cache_argument);

      if (F_status_is_error_not(data->main->setting.state.status)) {
        data->main->setting.state.status = f_string_dynamic_append_nulless(data_build->setting.build_name, &data->main->cache_argument);
      }

      if (F_status_is_error_not(data->main->setting.state.status)) {
        data->main->setting.state.status = f_string_dynamic_append_nulless(fake_build_parameter_object_name_suffix_s, &data->main->cache_argument);
      }

      if (F_status_is_error(data->main->setting.state.status)) {
        fake_print_error(&data->main->program.error, macro_fake_f(f_string_dynamic_append_nulless));

        return 0;
      }

      const f_string_static_t values[] = {
        fake_build_parameter_object_compile_s,
        fake_build_parameter_object_output_s,
        data->main->cache_argument,
      };

      for (uint8_t i = 0; i < 3; ++i) {

        if (!values[i].used) continue;

        data->main->setting.state.status = fll_execute_arguments_add(values[i], &data->main->cache_arguments);
        if (F_status_is_error(data->main->setting.state.status)) break;
      } // for
    }

    fake_build_arguments_standard_add(data, data_build, F_true, fake_build_type_object_e);

    if (F_status_is_error(data->main->setting.state.status)) {
      fake_print_error(&data->main->program.error, macro_fake_f(fake_build_arguments_standard_add));

      return 0;
    }

    int result = fake_execute(data, data_build->environment, data_build->setting.build_compiler);

    if (F_status_is_error_not(data->main->setting.state.status) && data->main->setting.state.status != F_child) {
      fake_build_touch(data, file_stage);
    }

    return result;
  }
#endif // _di_fake_build_object_shared_

#ifndef _di_fake_build_object_static_
  int fake_build_object_static(fake_data_t * const data, fake_build_data_t * const data_build, const f_mode_t mode, const f_string_static_t file_stage) {

    if (!data || !data->main || !data_build) return 0;
    if (data->main->setting.state.status == F_child) return data->main->program.child;
    if (F_status_is_error(data->main->setting.state.status) || f_file_exists(file_stage, F_true) == F_true) return 0;
    if (!data_build->setting.build_sources_object.used && !data_build->setting.build_sources_object_static.used) return 0;

    fake_build_print_compile_object_static(&data->main->program.message);

    fake_string_dynamic_reset(&data->main->cache_argument);
    fake_string_dynamics_reset(&data->main->cache_arguments);

    fake_build_sources_object_add(data, data_build, &data_build->setting.build_sources_object, &data_build->setting.build_sources_object_static);

    if (F_status_is_error(data->main->setting.state.status)) {
      fake_print_error(&data->main->program.error, macro_fake_f(fake_build_sources_object_add));

      return 0;
    }

    {
      data->main->setting.state.status = f_string_dynamic_append_nulless(data->path_build_objects_static, &data->main->cache_argument);

      if (F_status_is_error_not(data->main->setting.state.status)) {
        data->main->setting.state.status = f_string_dynamic_append_nulless(data_build->setting.build_name, &data->main->cache_argument);
      }

      if (F_status_is_error_not(data->main->setting.state.status)) {
        data->main->setting.state.status = f_string_dynamic_append_nulless(fake_build_parameter_object_name_suffix_s, &data->main->cache_argument);
      }

      if (F_status_is_error(data->main->setting.state.status)) {
        fake_print_error(&data->main->program.error, macro_fake_f(f_string_dynamic_append_nulless));

        return 0;
      }

      const f_string_static_t values[] = {
        fake_build_parameter_object_compile_s,
        fake_build_parameter_object_output_s,
        data->main->cache_argument,
      };

      for (uint8_t i = 0; i < 3; ++i) {

        if (!values[i].used) continue;

        data->main->setting.state.status = fll_execute_arguments_add(values[i], &data->main->cache_arguments);
        if (F_status_is_error(data->main->setting.state.status)) break;
      } // for
    }

    fake_build_arguments_standard_add(data, data_build, F_false, fake_build_type_object_e);

    if (F_status_is_error(data->main->setting.state.status)) {
      fake_print_error(&data->main->program.error, macro_fake_f(fake_build_arguments_standard_add));

      return 0;
    }

    const int result = fake_execute(data, data_build->environment, data_build->setting.build_compiler);

    if (F_status_is_error_not(data->main->setting.state.status) && data->main->setting.state.status != F_child) {
      fake_build_touch(data, file_stage);
    }

    return result;
  }
#endif // _di_fake_build_object_static_

#ifdef __cplusplus
} // extern "C"
#endif
