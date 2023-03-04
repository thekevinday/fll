#include "fss_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_write_setting_delete_
  f_status_t fss_write_setting_delete(fss_write_setting_t * const setting) {

    if (!setting) return F_status_set_error(F_parameter);

    f_string_dynamic_resize(0, &setting->escaped);
    f_string_dynamic_resize(0, &setting->block);
    f_string_dynamic_resize(0, &setting->buffer);
    f_string_dynamic_resize(0, &setting->prepend);

    f_string_rangess_resize(0, &setting->ignoress);
    f_string_dynamics_resize(0, &setting->objects);
    f_string_dynamicss_resize(0, &setting->contentss);

    return F_none;
  }
#endif // _di_fss_write_setting_delete_

#ifndef _di_fss_write_setting_load_
  void fss_write_setting_load(const f_console_arguments_t arguments, fll_program_data_t * const main, fss_write_setting_t * const setting, void (*callback)(const f_console_arguments_t arguments, fll_program_data_t * const main, fss_write_setting_t * const setting)) {

    if (!main || !setting) return;

    setting->state.step_small = fss_write_allocation_console_d;

    f_console_parameter_process(arguments, &main->parameters, &setting->state, 0);

    setting->state.step_small = fss_write_allocation_small_d;

    if (F_status_is_error(setting->state.status)) {
      fss_write_print_error(setting, main->error, macro_fss_write_f(f_console_parameter_process));

      return;
    }

    {
      f_uint16s_t choices = f_uint16s_t_initialize;

      // Identify and prioritize "color context" parameters.
      {
        uint16_t choices_array[3] = { fss_write_parameter_no_color_e, fss_write_parameter_light_e, fss_write_parameter_dark_e };
        choices.array = choices_array;
        choices.used = 3;

        const uint8_t modes[3] = { f_color_mode_not_e, f_color_mode_light_e, f_color_mode_dark_e };

        setting->state.status = fll_program_parameter_process_context(choices, modes, F_true, main);

        if (F_status_is_error(setting->state.status)) {
          fss_write_print_error(setting, main->error, macro_fss_write_f(fll_program_parameter_process_context));

          return;
        }
      }

      if (main->parameters.array[fss_write_parameter_line_first_no_e].result & f_console_result_found_e) {
        setting->line_first = f_string_empty_s;
      }
      else {
        setting->line_first = f_string_eol_s;
      }

      if (main->parameters.array[fss_write_parameter_line_last_no_e].result & f_console_result_found_e) {
        setting->line_last = f_string_empty_s;
      }
      else {
        setting->line_last = f_string_eol_s;
      }

      // Identify and prioritize "verbosity" parameters.
      {
        uint16_t choices_array[5] = { fss_write_parameter_verbosity_quiet_e, fss_write_parameter_verbosity_error_e, fss_write_parameter_verbosity_verbose_e, fss_write_parameter_verbosity_debug_e, fss_write_parameter_verbosity_normal_e };
        choices.array = choices_array;
        choices.used = 5;

        const uint8_t verbosity[5] = { f_console_verbosity_quiet_e, f_console_verbosity_error_e, f_console_verbosity_verbose_e, f_console_verbosity_debug_e, f_console_verbosity_normal_e };

        setting->state.status = fll_program_parameter_process_verbosity(choices, verbosity, F_true, main);

        if (F_status_is_error(setting->state.status)) {
          fss_write_print_error(setting, main->error, macro_fss_write_f(fll_program_parameter_process_verbosity));

          return;
        }
      }
    }

    main->output.to.id = F_type_descriptor_output_d;
    main->output.to.stream = F_type_output_d;
    main->output.to.flag = F_file_flag_create_d | F_file_flag_write_only_d | F_file_flag_append_d;

    if (main->parameters.array[fss_write_parameter_help_e].result & f_console_result_found_e) {
      setting->flag |= fss_write_main_flag_help_e;
    }

    if (main->parameters.array[fss_write_parameter_version_e].result & f_console_result_found_e) {
      setting->flag |= fss_write_main_flag_version_e;
    }

    if (main->parameters.array[fss_write_parameter_copyright_e].result & f_console_result_found_e) {
      setting->flag |= fss_write_main_flag_copyright_e;
    }

    if (callback) {
      callback(arguments, main, setting);
      if (F_status_is_error(setting->state.status)) return;

      if (setting->state.status == F_done) {
        setting->state.status = F_none;

        return;
      }
    }

    if (main->parameters.array[fss_write_parameter_help_e].result & f_console_result_found_e) return;
    if (main->parameters.array[fss_write_parameter_version_e].result & f_console_result_found_e) return;

    if ((main->parameters.array[fss_write_parameter_file_e].result & f_console_result_value_e) && main->parameters.array[fss_write_parameter_file_e].values.used) {
      if (main->parameters.array[fss_write_parameter_file_e].values.used > 1) {
        setting->state.status = F_status_set_error(F_parameter);

        fss_write_print_line_first(setting, main->message);
        fll_program_print_error_parameter_must_specify_once(main->error, f_console_symbol_long_normal_s, fss_write_long_file_s);

        return;
      }

      const f_array_length_t index = main->parameters.array[fss_write_parameter_file_e].values.array[0];

      main->output.to.id = -1;
      main->output.to.stream = 0;

      setting->state.status = f_file_stream_open(main->parameters.arguments.array[index], f_string_empty_s, &main->output.to);

      if (F_status_is_error(setting->state.status)) {
        fss_write_print_error_file(setting, main->error, macro_fss_write_f(f_file_stream_open), main->parameters.arguments.array[index], f_file_operation_open_s, fll_error_file_type_file_e);

        return;
      }

      setting->flag |= fss_write_main_flag_file_to_e;
    }
    else if (main->parameters.array[fss_write_parameter_file_e].result & f_console_result_found_e) {
      setting->state.status = F_status_set_error(F_parameter);

      fss_write_print_line_first(setting, main->message);
      fll_program_print_error_parameter_missing_value(main->error, f_console_symbol_long_normal_s, fss_write_long_file_s);

      return;
    }

    if ((main->parameters.array[fss_write_parameter_object_e].result & f_console_result_value_e) && main->parameters.array[fss_write_parameter_object_e].values.used) {
      f_array_lengths_t * const values = &main->parameters.array[fss_write_parameter_object_e].values;

      setting->objects.used = 0;

      setting->state.status = f_string_dynamics_resize(values->used, &setting->objects);

      if (F_status_is_error(setting->state.status)) {
        fss_write_print_error(setting, main->error, macro_fss_write_f(f_string_dynamics_resize));

        return;
      }

      // Construct the array without allocating any more memory for the string data by setting this as a static string (used > 0, size = 0).
      for (f_array_length_t index = 0; setting->objects.used < values->used; ) {

        index = values->array[setting->objects.used];

        setting->objects.array[setting->objects.used].string = main->parameters.arguments.array[index].string;
        setting->objects.array[setting->objects.used].used = main->parameters.arguments.array[index].used;
        setting->objects.array[setting->objects.used++].size = 0;
      } // for

      setting->flag |= fss_write_main_flag_object_e;
    }
    else if (main->parameters.array[fss_write_parameter_object_e].result & f_console_result_found_e) {
      setting->state.status = F_status_set_error(F_parameter);

      fss_write_print_line_first(setting, main->message);
      fll_program_print_error_parameter_missing_value(main->error, f_console_symbol_long_normal_s, fss_write_long_object_s);

      return;
    }

    if ((main->parameters.array[fss_write_parameter_content_e].result & f_console_result_value_e) && main->parameters.array[fss_write_parameter_content_e].values.used) {

      if (setting->flag & fss_write_main_flag_object_e) {
        if (!(setting->flag & fss_write_main_flag_content_multiple_e)) {
          if (main->parameters.array[fss_write_parameter_content_e].values.used > main->parameters.array[fss_write_parameter_object_e].values.used) {
            setting->state.status = F_status_set_error(F_support_not);

            fss_write_print_line_first(setting, main->message);
            fss_write_print_error_one_content_only(setting, main->error);

            return;
          }
        }
      }

      f_array_length_t stub_object_array[1] = { 0 };
      f_array_lengths_t stub_object = macro_f_array_lengths_t_initialize(stub_object_array, 0, 1);

      f_array_lengths_t * const values_content = &main->parameters.array[fss_write_parameter_content_e].values;
      f_array_lengths_t * const values_object = main->parameters.array[fss_write_parameter_object_e].values.used
        ? &main->parameters.array[fss_write_parameter_object_e].values
        : &stub_object;

      setting->contentss.used = 0;

      setting->state.status = f_string_dynamicss_increase_by(values_object->used, &setting->contentss);

      if (F_status_is_error(setting->state.status)) {
        fss_write_print_error(setting, main->error, macro_fss_write_f(f_string_dynamicss_increase_by));

        return;
      }

      f_array_length_t i = 0; // For Contents.
      f_array_length_t j = 0; // For Objects.
      f_array_length_t k = 0;
      f_array_length_t total = 0;
      f_array_length_t index = 0;

      // Construct the array without allocating any more memory for the string data by setting this as a static string (used > 0, size = 0).
      while (i < values_content->used) {

        // Determine the total Content associated with the given Object.
        for (total = 0; i + total < values_content->used && (j + 1 >= values_object->used || values_content->array[i + total] < values_object->array[j + 1]); ++total) {
          // Do nothing.
        } // for


        if (!total) {
          ++setting->contentss.used;

          if (++j < values_object->used) continue;

          break;
        }

        setting->state.status = f_string_dynamics_increase_by(total, &setting->contentss.array[j]);

        if (F_status_is_error(setting->state.status)) {
          fss_write_print_error(setting, main->error, macro_fss_write_f(f_string_dynamics_increase_by));

          return;
        }

        for (k = 0; k < total; ++k) {

          index = values_content->array[i++];

          setting->contentss.array[j].array[setting->contentss.array[j].used].string = main->parameters.arguments.array[index].string;
          setting->contentss.array[j].array[setting->contentss.array[j].used].used = main->parameters.arguments.array[index].used;
          setting->contentss.array[j].array[setting->contentss.array[j].used++].size = 0;
        } // for
      } // while

      if (total) {
        ++setting->contentss.used;
      }

      setting->flag |= fss_write_main_flag_content_e;
    }
    else if (main->parameters.array[fss_write_parameter_content_e].result & f_console_result_found_e) {
      setting->state.status = F_status_set_error(F_parameter);

      fss_write_print_line_first(setting, main->message);
      fll_program_print_error_parameter_missing_value(main->error, f_console_symbol_long_normal_s, fss_write_long_content_s);

      return;
    }

    if ((main->parameters.array[fss_write_parameter_prepend_e].result & f_console_result_value_e) && main->parameters.array[fss_write_parameter_prepend_e].values.used) {
      const f_array_length_t index = main->parameters.array[fss_write_parameter_prepend_e].values.array[main->parameters.array[fss_write_parameter_prepend_e].values.used - 1];

      setting->prepend.used = 0;

      setting->state.status = f_string_dynamic_append_nulless(main->parameters.arguments.array[index], &setting->prepend);

      if (F_status_is_error(setting->state.status)) {
        fss_write_print_error(setting, main->error, macro_fss_write_f(f_string_dynamic_append_nulless));

        return;
      }

      if (main->parameters.arguments.array[index].used) {
        f_string_range_t range = macro_f_string_range_t_initialize2(main->parameters.arguments.array[index].used);

        for (; range.start < main->parameters.arguments.array[index].used; range.start++) {

          if (f_fss_is_space(main->parameters.arguments.array[index], range, &setting->state) == F_false) {
            if (F_status_is_error(setting->state.status)) {
              fss_write_print_error(setting, main->error, macro_fss_write_f(f_fss_is_space));
            }
            else {
              setting->state.status = F_status_set_error(F_parameter);

              fss_write_print_error_prepend_only_whitespace(setting, main->error);
            }

            return;
          }
        } // for
      }

      setting->flag |= fss_write_main_flag_prepend_e;
    }
    else if (main->parameters.array[fss_write_parameter_prepend_e].result & f_console_result_found_e) {
      setting->state.status = F_status_set_error(F_parameter);

      fss_write_print_line_first(setting, main->message);
      fll_program_print_error_parameter_missing_value(main->error, f_console_symbol_long_normal_s, fss_write_long_prepend_s);

      return;
    }

    if ((main->parameters.array[fss_write_parameter_ignore_e].result & f_console_result_value_e) && main->parameters.array[fss_write_parameter_ignore_e].values.used) {
      if (main->parameters.array[fss_write_parameter_ignore_e].values.used % 2 != 0) {
        setting->state.status = F_status_set_error(F_parameter);

        fss_write_print_line_first(setting, main->message);
        fll_program_print_error_parameter_missing_value_requires_amount(main->error, f_console_symbol_long_normal_s, fss_write_long_ignore_s, fss_write_string_two_s);

        return;
      }

      // Only process if the standard designates that the ingore is supported.
      if (setting->flag & fss_write_main_flag_ignore_e) {
        f_array_length_t stub_data_array[1] = { 0 };
        f_array_lengths_t stub_data = macro_f_array_lengths_t_initialize(stub_data_array, 0, 1);

        f_array_lengths_t * const values_ignore = &main->parameters.array[fss_write_parameter_ignore_e].values;
        f_array_lengths_t * const values_data = main->parameters.array[fss_write_parameter_object_e].values.used
          ? &main->parameters.array[fss_write_parameter_object_e].values
          : main->parameters.array[fss_write_parameter_content_e].values.used
            ? &main->parameters.array[fss_write_parameter_content_e].values
            : &stub_data;

        setting->ignoress.used = 0;

        setting->state.status = f_string_rangess_increase_by(values_data->used, &setting->ignoress);

        if (F_status_is_error(setting->state.status)) {
          fss_write_print_error(setting, main->error, macro_fss_write_f(f_string_rangess_increase_by));

          return;
        }

        f_array_length_t i = 0; // For Ignores.
        f_array_length_t j = 0; // For Objects/Contents.
        f_array_length_t k = 0;
        f_array_length_t total = 0;
        f_array_length_t index = 0;

        // Construct the array without allocating any more memory for the string data by setting this as a static string (used > 0, size = 0).
        while (i < values_ignore->used) {

          // Determine the total Ignore associated with the given Object/Content.
          for (total = 0; i + total < values_ignore->used && (j + 1 >= values_data->used || values_ignore->array[i + total] < values_data->array[j + 1]); ++total) {
            // Do nothing.
          } // for

          if (!total) {
            ++setting->ignoress.used;

            if (++j < values_data->used) continue;

            break;
          }

          setting->state.status = f_string_ranges_increase_by(total, &setting->ignoress.array[j]);

          if (F_status_is_error(setting->state.status)) {
            fss_write_print_error(setting, main->error, macro_fss_write_f(f_string_ranges_increase_by));

            return;
          }

          for (k = 0; k < total; ++k) {

            index = values_ignore->array[i++];

            setting->state.status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, main->parameters.arguments.array[index], &setting->ignoress.array[j].array[setting->ignoress.array[j].used].start);

            if (F_status_is_error(setting->state.status)) {
              fss_write_print_line_first(setting, main->message);
              fll_program_print_error_parameter_integer_not(main->error, f_console_symbol_long_normal_s, fss_write_long_ignore_s, main->parameters.arguments.array[index]);

              return;
            }

            index = values_ignore->array[i++];

            setting->state.status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, main->parameters.arguments.array[index], &setting->ignoress.array[j].array[setting->ignoress.array[j].used].stop);

            if (F_status_is_error(setting->state.status)) {
              fss_write_print_line_first(setting, main->message);
              fll_program_print_error_parameter_integer_not(main->error, f_console_symbol_long_normal_s, fss_write_long_ignore_s, main->parameters.arguments.array[index]);

              return;
            }

            if (setting->ignoress.array[j].array[setting->ignoress.array[j].used].stop > setting->ignoress.array[j].array[setting->ignoress.array[j].used].start) {
              setting->state.status = F_status_set_error(F_parameter);

              fss_write_print_line_first(setting, main->message);
              fll_program_print_error_parameter_range_start_before_stop(
                main->error,
                f_console_symbol_long_normal_s,
                fss_write_long_ignore_s,
                main->parameters.arguments.array[values_ignore->array[i - 1]],
                main->parameters.arguments.array[index]
              );

              return;
            }

            ++setting->ignoress.array[j].used;
          } // for
        } // while

        if (total) {
          ++setting->ignoress.used;
        }
      }
      else {

        // Still validate the parameters, even if not being used.
        f_array_length_t i = 0;
        f_array_length_t index = 0;
        f_string_range_t number = f_string_range_t_initialize;

        while (i < main->parameters.array[fss_write_parameter_ignore_e].values.used) {

          index = main->parameters.array[fss_write_parameter_ignore_e].values.array[i++];

          setting->state.status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, main->parameters.arguments.array[index], &number.start);

          if (F_status_is_error(setting->state.status)) {
            fss_write_print_line_first(setting, main->message);
            fll_program_print_error_parameter_integer_not(main->error, f_console_symbol_long_normal_s, fss_write_long_ignore_s, main->parameters.arguments.array[index]);

            return;
          }

          index = main->parameters.array[fss_write_parameter_ignore_e].values.array[i++];

          setting->state.status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, main->parameters.arguments.array[index], &number.stop);

          if (F_status_is_error(setting->state.status)) {
            fss_write_print_line_first(setting, main->message);
            fll_program_print_error_parameter_integer_not(main->error, f_console_symbol_long_normal_s, fss_write_long_ignore_s, main->parameters.arguments.array[index]);

            return;
          }

          if (number.start > number.stop) {
            setting->state.status = F_status_set_error(F_parameter);

            fss_write_print_line_first(setting, main->message);
            fll_program_print_error_parameter_range_start_before_stop(
              main->error,
              f_console_symbol_long_normal_s,
              fss_write_long_ignore_s,
              main->parameters.arguments.array[main->parameters.array[fss_write_parameter_ignore_e].values.array[i - 1]],
              main->parameters.arguments.array[index]
            );

            return;
          }
        } // while
      }
    }
    else if (main->parameters.array[fss_write_parameter_ignore_e].result & f_console_result_found_e) {
      setting->state.status = F_status_set_error(F_parameter);

      fss_write_print_line_first(setting, main->message);
      fll_program_print_error_parameter_missing_value(main->error, f_console_symbol_long_normal_s, fss_write_long_ignore_s);

      return;
    }
    else {

      // There is no Object or Content, so remove ignores if set.
      if (setting->flag & fss_write_main_flag_ignore_e) {
        setting->flag -= fss_write_main_flag_ignore_e;
      }
    }

    if (main->parameters.array[fss_write_parameter_partial_e].result & f_console_result_found_e) {
      setting->flag |= fss_write_main_flag_partial_e;
    }

    {
      const uint32_t has[] = {
        fss_write_parameter_content_end_e,
        fss_write_parameter_content_next_e,
        fss_write_parameter_object_open_e,
      };

      const uint16_t has_flag[] = {
        fss_write_main_flag_content_end_e,
        fss_write_main_flag_content_next_e,
        fss_write_main_flag_object_open_e,
      };

      const f_string_static_t has_string[] = {
        fss_write_long_content_end_s,
        fss_write_long_content_next_s,
        fss_write_long_object_open_s,
      };

      const uint16_t has_cannots[][2] = {
        { fss_write_parameter_content_next_e, fss_write_parameter_object_open_e },
        { fss_write_parameter_content_end_e, fss_write_parameter_object_open_e },
        { fss_write_parameter_content_end_e, fss_write_parameter_content_next_e },
      };

      const f_string_static_t has_cannots_string[][2] = {
        { fss_write_long_content_next_s, fss_write_long_object_open_s },
        { fss_write_long_content_end_s, fss_write_long_object_open_s },
        { fss_write_long_content_end_s, fss_write_long_content_next_s },
      };

      for (uint8_t i = 0; i < 3; ++i) {

        if (main->parameters.array[has[i]].result & f_console_result_found_e) {
          if (setting->flag & (fss_write_main_flag_object_e | fss_write_main_flag_content_e)) {
            if (!(setting->flag & fss_write_main_flag_partial_e)) {
              setting->state.status = F_status_set_error(F_parameter);

              fss_write_print_line_first(setting, main->message);

              fll_program_print_error_parameter_cannot_use_with_without(
                main->error,
                f_console_symbol_long_normal_s,
                f_console_symbol_long_normal_s,
                f_console_symbol_long_normal_s,
                has_string[i],
                (setting->flag & fss_write_main_flag_object_e)
                  ? fss_write_long_object_s
                  : fss_write_long_content_s,
                fss_write_long_partial_s
              );

              return;
            }
          }

          if (main->parameters.array[has_cannots[i][0]].result & f_console_result_found_e) {
            setting->state.status = F_status_set_error(F_parameter);

            fss_write_print_line_first(setting, main->message);
            fll_program_print_error_parameter_cannot_use_with(main->error, f_console_symbol_long_normal_s, f_console_symbol_long_normal_s, has_string[i], has_cannots_string[i][0]);

            return;
          }

          if (main->parameters.array[has_cannots[i][1]].result & f_console_result_found_e) {
            setting->state.status = F_status_set_error(F_parameter);

            fss_write_print_line_first(setting, main->message);
            fll_program_print_error_parameter_cannot_use_with(main->error, f_console_symbol_long_normal_s, f_console_symbol_long_normal_s, has_string[i], has_cannots_string[i][1]);

            return;
          }

          setting->flag |= has_flag[i];
        }
      } // for
    }

    if (setting->flag & (fss_write_main_flag_object_e | fss_write_main_flag_content_e)) {
      if (setting->flag & fss_write_main_flag_object_e) {
        if (setting->flag & fss_write_main_flag_content_multiple_e) {
          if (main->parameters.array[fss_write_parameter_object_e].locations_sub.used > main->parameters.array[fss_write_parameter_content_e].locations_sub.used && !(setting->flag & fss_write_main_flag_partial_e)) {
            setting->state.status = F_status_set_error(F_parameter);

            fss_write_print_line_first(setting, main->message);
            fss_write_print_error_parameter_same_times_at_least(setting, main->error);

            return;
          }
        }

        if ((setting->flag & fss_write_main_flag_content_e) && (setting->flag & fss_write_main_flag_partial_e)) {
          if (main->parameters.array[fss_write_parameter_content_e].result & f_console_result_value_e) {
            setting->state.status = F_status_set_error(F_parameter);

            fss_write_print_line_first(setting, main->message);
            fll_program_print_error_parameter_cannot_use_with_xor(main->error, f_console_symbol_long_normal_s, f_console_symbol_long_normal_s, f_console_symbol_long_normal_s, fss_write_long_partial_s, fss_write_long_object_s, fss_write_long_content_s);

            return;
          }
        }
      }
    }

    setting->quote = f_fss_quote_double_s;

    if (main->parameters.array[fss_write_parameter_double_e].result & f_console_result_found_e) {
      if (main->parameters.array[fss_write_parameter_single_e].result & f_console_result_found_e) {
        if (main->parameters.array[fss_write_parameter_double_e].location < main->parameters.array[fss_write_parameter_single_e].location) {
          setting->quote = f_fss_quote_single_s;

          if (main->parameters.array[fss_write_parameter_backtick_e].result & f_console_result_found_e) {
            if (main->parameters.array[fss_write_parameter_single_e].location < main->parameters.array[fss_write_parameter_backtick_e].location) {
              setting->quote = f_fss_quote_backtick_s;
            }
          }
        }
        else if (main->parameters.array[fss_write_parameter_backtick_e].result & f_console_result_found_e) {
          if (main->parameters.array[fss_write_parameter_double_e].location < main->parameters.array[fss_write_parameter_backtick_e].location) {
            setting->quote = f_fss_quote_backtick_s;
          }
        }
      }
      else if (main->parameters.array[fss_write_parameter_backtick_e].result & f_console_result_found_e) {
        if (main->parameters.array[fss_write_parameter_double_e].location < main->parameters.array[fss_write_parameter_backtick_e].location) {
          setting->quote = f_fss_quote_backtick_s;
        }
      }
    }
    else if (main->parameters.array[fss_write_parameter_single_e].result & f_console_result_found_e) {
      setting->quote = f_fss_quote_single_s;

      if (main->parameters.array[fss_write_parameter_backtick_e].result & f_console_result_found_e) {
        if (main->parameters.array[fss_write_parameter_single_e].location < main->parameters.array[fss_write_parameter_backtick_e].location) {
          setting->quote = f_fss_quote_backtick_s;
        }
      }
    }
    else if (main->parameters.array[fss_write_parameter_backtick_e].result & f_console_result_found_e) {
      setting->quote = f_fss_quote_backtick_s;
    }

    if (main->parameters.array[fss_write_parameter_trim_e].result & f_console_result_found_e) {
      setting->flag |= fss_write_main_flag_trim_e;
    }

    if (!(setting->flag & (fll_program_data_pipe_input_e | fss_write_main_flag_content_e | fss_write_parameter_object_e))) {
      setting->state.status = F_data_not;
    }
  }
#endif // _di_fss_write_setting_load_

#ifndef _di_fss_write_setting_unload_
  f_status_t fss_write_setting_unload(fll_program_data_t * const main, fss_write_setting_t * const setting) {

    if (!main || !setting) return F_status_set_error(F_parameter);

    fss_write_setting_delete(setting);

    return F_none;
  }
#endif // _di_fss_write_setting_unload_

#ifdef __cplusplus
} // extern "C"
#endif
