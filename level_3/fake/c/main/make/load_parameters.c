#include "../fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_make_load_parameters_
  void fake_make_load_parameters(fake_make_data_t * const data_make) {

    if (!data_make || !data_make->main) return;
    if (F_status_is_error(data_make->main->setting.state.status)) return;

    fake_main_t * const main = data_make->main;

    if (main->program.context.mode != f_color_mode_none_e) {
      main->setting.state.status = f_string_dynamics_increase_by(fake_allocation_small_d, &data_make->parameter.color);

      if (F_status_is_error_not(main->setting.state.status)) {
        main->setting.state.status = f_string_dynamics_increase_by(fake_allocation_small_d, &data_make->parameter_option.color);
      }

      if (F_status_is_error(main->setting.state.status)) {
        fake_print_error(&main->program.error, macro_fake_f(f_string_dynamics_increase_by));

        return;
      }

      if (main->program.context.mode == f_color_mode_not_e) {
        if (main->program.parameters.array[f_console_standard_parameter_no_color_e].flag & f_console_flag_normal_e) {
          main->setting.state.status = f_string_dynamic_append(f_console_symbol_short_normal_s, &data_make->parameter.color.array[data_make->parameter.color.used]);
        }
        else if (main->program.parameters.array[f_console_standard_parameter_no_color_e].flag & f_console_flag_normal_e) {
          main->setting.state.status = f_string_dynamic_append(f_console_symbol_short_inverse_s, &data_make->parameter.color.array[data_make->parameter.color.used]);
        }

        if (F_status_is_error_not(main->setting.state.status)) {
          main->setting.state.status = f_string_dynamic_append(f_console_standard_short_no_color_s, &data_make->parameter.color.array[data_make->parameter.color.used]);
        }
      }
      else if (main->program.context.mode == f_color_mode_dark_e) {
        if (main->program.parameters.array[f_console_standard_parameter_dark_e].flag & f_console_flag_normal_e) {
          main->setting.state.status = f_string_dynamic_append(f_console_symbol_short_normal_s, &data_make->parameter.color.array[data_make->parameter.color.used]);
        }
        else if (main->program.parameters.array[f_console_standard_parameter_dark_e].flag & f_console_flag_normal_e) {
          main->setting.state.status = f_string_dynamic_append(f_console_symbol_short_inverse_s, &data_make->parameter.color.array[data_make->parameter.color.used]);
        }

        if (F_status_is_error_not(main->setting.state.status)) {
          main->setting.state.status = f_string_dynamic_append(f_console_standard_short_dark_s, &data_make->parameter.color.array[data_make->parameter.color.used]);
        }
      }
      else {
        if (main->program.parameters.array[f_console_standard_parameter_light_e].flag & f_console_flag_normal_e) {
          main->setting.state.status = f_string_dynamic_append(f_console_symbol_short_normal_s, &data_make->parameter.color.array[data_make->parameter.color.used]);
        }
        else if (main->program.parameters.array[f_console_standard_parameter_light_e].flag & f_console_flag_normal_e) {
          main->setting.state.status = f_string_dynamic_append(f_console_symbol_short_inverse_s, &data_make->parameter.color.array[data_make->parameter.color.used]);
        }

        if (F_status_is_error_not(main->setting.state.status)) {
          main->setting.state.status = f_string_dynamic_append(f_console_standard_short_light_s, &data_make->parameter.color.array[data_make->parameter.color.used]);
        }
      }

      if (F_status_is_error_not(main->setting.state.status)) {
        main->setting.state.status = f_string_dynamic_append(data_make->parameter.color.array[data_make->parameter.color.used], &data_make->parameter_option.color.array[data_make->parameter_option.color.used]);
      }

      if (F_status_is_error(main->setting.state.status)) {
        fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_append));

        return;
      }

      ++data_make->parameter.color.used;
      ++data_make->parameter_option.color.used;
    }

    if (main->program.error.verbosity != f_console_verbosity_normal_e) {
      main->setting.state.status = f_string_dynamics_increase_by(fake_allocation_small_d, &data_make->parameter.verbosity);

      if (F_status_is_error_not(main->setting.state.status)) {
        main->setting.state.status = f_string_dynamics_increase_by(fake_allocation_small_d, &data_make->parameter_option.verbosity);
      }

      if (F_status_is_error(main->setting.state.status)) {
        fake_print_error(&main->program.error, macro_fake_f(f_string_dynamics_increase_by));

        return;
      }

      if (main->program.error.verbosity == f_console_verbosity_quiet_e) {
        if (main->program.parameters.array[f_console_standard_parameter_verbosity_quiet_e].flag & f_console_flag_normal_e) {
          main->setting.state.status = f_string_dynamic_append(f_console_symbol_short_normal_s, &data_make->parameter.verbosity.array[data_make->parameter.verbosity.used]);
        }
        else if (main->program.parameters.array[f_console_standard_parameter_verbosity_quiet_e].flag & f_console_flag_normal_e) {
          main->setting.state.status = f_string_dynamic_append(f_console_symbol_short_inverse_s, &data_make->parameter.verbosity.array[data_make->parameter.verbosity.used]);
        }

        if (F_status_is_error_not(main->setting.state.status)) {
          main->setting.state.status = f_string_dynamic_append(f_console_standard_short_quiet_s, &data_make->parameter.verbosity.array[data_make->parameter.verbosity.used]);
        }
      }
      else if (main->program.error.verbosity == f_console_verbosity_error_e) {
        if (main->program.parameters.array[f_console_standard_parameter_verbosity_error_e].flag & f_console_flag_normal_e) {
          main->setting.state.status = f_string_dynamic_append(f_console_symbol_short_normal_s, &data_make->parameter.verbosity.array[data_make->parameter.verbosity.used]);
        }
        else if (main->program.parameters.array[f_console_standard_parameter_verbosity_error_e].flag & f_console_flag_normal_e) {
          main->setting.state.status = f_string_dynamic_append(f_console_symbol_short_inverse_s, &data_make->parameter.verbosity.array[data_make->parameter.verbosity.used]);
        }

        if (F_status_is_error_not(main->setting.state.status)) {
          main->setting.state.status = f_string_dynamic_append(f_console_standard_short_error_s, &data_make->parameter.verbosity.array[data_make->parameter.verbosity.used]);
        }
      }
      else if (main->program.error.verbosity >= f_console_verbosity_verbose_e) {
        if (main->program.parameters.array[f_console_standard_parameter_verbosity_verbose_e].flag & f_console_flag_normal_e) {
          main->setting.state.status = f_string_dynamic_append(f_console_symbol_short_normal_s, &data_make->parameter.verbosity.array[data_make->parameter.verbosity.used]);
        }
        else if (main->program.parameters.array[f_console_standard_parameter_verbosity_verbose_e].flag & f_console_flag_normal_e) {
          main->setting.state.status = f_string_dynamic_append(f_console_symbol_short_inverse_s, &data_make->parameter.verbosity.array[data_make->parameter.verbosity.used]);
        }

        if (F_status_is_error_not(main->setting.state.status)) {
          main->setting.state.status = f_string_dynamic_append(f_console_standard_short_verbose_s, &data_make->parameter.verbosity.array[data_make->parameter.verbosity.used]);
        }
      }
      else {
        if (main->program.parameters.array[f_console_standard_parameter_verbosity_debug_e].flag & f_console_flag_normal_e) {
          main->setting.state.status = f_string_dynamic_append(f_console_symbol_short_normal_s, &data_make->parameter.verbosity.array[data_make->parameter.verbosity.used]);
        }
        else if (main->program.parameters.array[f_console_standard_parameter_verbosity_debug_e].flag & f_console_flag_normal_e) {
          main->setting.state.status = f_string_dynamic_append(f_console_symbol_short_inverse_s, &data_make->parameter.verbosity.array[data_make->parameter.verbosity.used]);
        }

        if (F_status_is_error_not(main->setting.state.status)) {
          main->setting.state.status = f_string_dynamic_append(f_console_standard_short_debug_s, &data_make->parameter.verbosity.array[data_make->parameter.verbosity.used]);
        }
      }

      if (F_status_is_error_not(main->setting.state.status)) {
        main->setting.state.status = f_string_dynamic_append(data_make->parameter.verbosity.array[data_make->parameter.verbosity.used], &data_make->parameter_option.verbosity.array[data_make->parameter_option.verbosity.used]);
      }

      if (F_status_is_error(main->setting.state.status)) {
        fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_append));

        return;
      }

      ++data_make->parameter.verbosity.used;
      ++data_make->parameter_option.verbosity.used;
    }

    {
      const f_string_static_t parameter[] = {
        fake_short_define_s,
        fake_short_mode_s,
      };

      const f_console_parameter_t *console[] = {
        &main->program.parameters.array[fake_parameter_define_e],
        &main->program.parameters.array[fake_parameter_mode_e],
      };

      const f_string_dynamics_t source[] = {
        data_make->data->main->setting.defines,
        data_make->data->main->setting.modes,
      };

      f_string_dynamics_t * const destination[] = {
        &data_make->parameter.define,
        &data_make->parameter.mode,
      };

      f_string_dynamics_t * const destination_option[] = {
        &data_make->parameter_option.define,
        &data_make->parameter_option.mode,
      };

      f_string_dynamics_t * const destination_value[] = {
        &data_make->parameter_value.define,
        &data_make->parameter_value.mode,
      };

      f_number_unsigned_t j = 0;

      for (uint8_t i = 0; i < 2; ++i) {

        if (!(console[i]->result & f_console_result_found_e)) continue;

        for (j = 0; j < source[i].used; ++j) {

          if (destination[i]->used + 2 > destination[i]->size) {
            main->setting.state.status = f_string_dynamics_increase_by(fake_allocation_small_d, destination[i]);

            if (F_status_is_error(main->setting.state.status)) {
              fake_print_error(&main->program.error, macro_fake_f(f_string_dynamics_increase_by));

              return;
            }
          }

          main->setting.state.status = f_string_dynamics_increase(fake_allocation_small_d, destination_option[i]);

          if (F_status_is_error_not(main->setting.state.status)) {
            main->setting.state.status = f_string_dynamics_increase(fake_allocation_small_d, destination_value[i]);
          }

          if (F_status_is_error(main->setting.state.status)) {
            fake_print_error(&main->program.error, macro_fake_f(f_string_dynamics_increase));

            return;
          }

          if (console[i]->flag & f_console_flag_normal_e) {
            main->setting.state.status = f_string_dynamic_append_nulless(f_console_symbol_short_normal_s, &destination[i]->array[destination[i]->used]);
          }
          else if (console[i]->flag & f_console_flag_inverse_e) {
            main->setting.state.status = f_string_dynamic_append_nulless(f_console_symbol_short_inverse_s, &destination[i]->array[destination[i]->used]);
          }

          if (F_status_is_error_not(main->setting.state.status)) {
            main->setting.state.status = f_string_dynamic_append_nulless(parameter[i], &destination[i]->array[destination[i]->used]);
          }

          if (F_status_is_error_not(main->setting.state.status)) {
            main->setting.state.status = f_string_dynamic_append_nulless(destination[i]->array[destination[i]->used], &destination_option[i]->array[destination_option[i]->used]);
          }

          if (F_status_is_error(main->setting.state.status)) {
            fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_append_nulless));

            return;
          }

          ++destination[i]->used;
          ++destination_option[i]->used;

          main->setting.state.status = f_string_dynamics_increase_by(fake_allocation_small_d, destination[i]);

          if (F_status_is_error(main->setting.state.status)) {
            fake_print_error(&main->program.error, macro_fake_f(f_string_dynamics_increase_by));

            return;
          }

          main->setting.state.status = f_string_dynamic_append_nulless(source[i].array[j], &destination[i]->array[destination[i]->used]);

          if (F_status_is_error_not(main->setting.state.status)) {
            main->setting.state.status = f_string_dynamic_append_nulless(source[i].array[j], &destination_value[i]->array[destination_value[i]->used]);
          }

          if (F_status_is_error(main->setting.state.status)) {
            fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_append_nulless));

            return;
          }

          ++destination[i]->used;
          ++destination_value[i]->used;
        } // for
      } // for
    }

    {
      const f_string_static_t parameter[] = {
        fake_short_build_s,
        fake_short_data_s,
        fake_short_documents_s,
        fake_short_fakefile_s,
        fake_short_licenses_s,
        fake_short_process_s,
        fake_short_settings_s,
        fake_short_sources_s,
        fake_short_work_s,
      };

      const f_console_parameter_t *console[] = {
        &main->program.parameters.array[fake_parameter_build_e],
        &main->program.parameters.array[fake_parameter_data_e],
        &main->program.parameters.array[fake_parameter_documents_e],
        &main->program.parameters.array[fake_parameter_fakefile_e],
        &main->program.parameters.array[fake_parameter_licenses_e],
        &main->program.parameters.array[fake_parameter_process_e],
        &main->program.parameters.array[fake_parameter_settings_e],
        &main->program.parameters.array[fake_parameter_sources_e],
        &main->program.parameters.array[fake_parameter_work_e],
      };

      const f_string_dynamic_t source[] = {
        data_make->data->main->setting.build,
        data_make->data->main->setting.data,
        data_make->data->main->setting.documents,
        data_make->data->main->setting.fakefile,
        data_make->data->main->setting.licenses,
        data_make->data->main->setting.process,
        data_make->data->main->setting.settings,
        data_make->data->main->setting.sources,
        data_make->data->main->setting.work,
      };

      f_string_dynamics_t * const destination[] = {
        &data_make->parameter.build,
        &data_make->parameter.data,
        &data_make->parameter.documents,
        &data_make->parameter.fakefile,
        &data_make->parameter.licenses,
        &data_make->parameter.process,
        &data_make->parameter.settings,
        &data_make->parameter.sources,
        &data_make->parameter.work,
      };

      f_string_dynamics_t * const destination_option[] = {
        &data_make->parameter_option.build,
        &data_make->parameter_option.data,
        &data_make->parameter_option.documents,
        &data_make->parameter_option.fakefile,
        &data_make->parameter_option.licenses,
        &data_make->parameter_option.process,
        &data_make->parameter_option.settings,
        &data_make->parameter_option.sources,
        &data_make->parameter_option.work,
      };

      f_string_dynamics_t * const destination_value[] = {
        &data_make->parameter_value.build,
        &data_make->parameter_value.data,
        &data_make->parameter_value.documents,
        &data_make->parameter_value.fakefile,
        &data_make->parameter_value.licenses,
        &data_make->parameter_value.process,
        &data_make->parameter_value.settings,
        &data_make->parameter_value.sources,
        &data_make->parameter_value.work,
      };

      for (uint8_t i = 0; i < 9; ++i) {

        if (!(console[i]->result & f_console_result_found_e)) continue;

        if (destination[i]->used + 2 > destination[i]->size) {
          main->setting.state.status = f_string_dynamics_increase_by(fake_allocation_small_d, destination[i]);

          if (F_status_is_error(main->setting.state.status)) {
            fake_print_error(&main->program.error, macro_fake_f(f_string_dynamics_increase_by));

            return;
          }
        }

        main->setting.state.status = f_string_dynamics_increase(fake_allocation_small_d, destination_option[i]);

        if (F_status_is_error_not(main->setting.state.status)) {
          main->setting.state.status = f_string_dynamics_increase(fake_allocation_small_d, destination_value[i]);
        }

        if (F_status_is_error(main->setting.state.status)) {
          fake_print_error(&main->program.error, macro_fake_f(f_string_dynamics_increase));

          return;
        }

        if (console[i]->flag & f_console_flag_normal_e) {
          main->setting.state.status = f_string_dynamic_append_nulless(f_console_symbol_short_normal_s, &destination[i]->array[destination[i]->used]);
        }
        else if (console[i]->flag & f_console_flag_inverse_e) {
          main->setting.state.status = f_string_dynamic_append_nulless(f_console_symbol_short_inverse_s, &destination[i]->array[destination[i]->used]);
        }

        if (F_status_is_error_not(main->setting.state.status)) {
          main->setting.state.status = f_string_dynamic_append_nulless(parameter[i], &destination[i]->array[destination[i]->used]);
        }

        if (F_status_is_error_not(main->setting.state.status)) {
          main->setting.state.status = f_string_dynamic_append_nulless(destination[i]->array[destination[i]->used], &destination_option[i]->array[destination_option[i]->used]);
        }

        if (F_status_is_error(main->setting.state.status)) {
          fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_append_nulless));

          return;
        }

        ++destination[i]->used;
        ++destination_option[i]->used;

        main->setting.state.status = f_string_dynamics_increase_by(fake_allocation_small_d, destination[i]);

        if (F_status_is_error(main->setting.state.status)) {
          fake_print_error(&main->program.error, macro_fake_f(f_string_dynamics_increase_by));

          return;
        }

        main->setting.state.status = f_string_dynamic_append_nulless(source[i], &destination[i]->array[destination[i]->used]);

        if (F_status_is_error_not(main->setting.state.status)) {
          main->setting.state.status = f_string_dynamic_append_nulless(source[i], &destination_value[i]->array[destination_value[i]->used]);
        }

        if (F_status_is_error(main->setting.state.status)) {
          fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_append_nulless));

          return;
        }

        ++destination[i]->used;
        ++destination_value[i]->used;
      } // for
    }
  }
#endif // _di_fake_make_load_parameters_

#ifdef __cplusplus
} // extern "C"
#endif
