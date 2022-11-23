#include "fss_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_write_program_version_
  const f_string_static_t fss_write_program_version_s = macro_f_string_static_t_initialize(FSS_WRITE_program_version_s, 0, FSS_WRITE_program_version_s_length);
#endif // _di_fss_write_program_version_

#ifndef _di_fss_write_program_name_
  const f_string_static_t fss_write_program_name_s = macro_f_string_static_t_initialize(FSS_WRITE_program_name_s, 0, FSS_WRITE_program_name_s_length);
  const f_string_static_t fss_write_program_name_long_s = macro_f_string_static_t_initialize(FSS_WRITE_program_name_long_s, 0, FSS_WRITE_program_name_long_s_length);
#endif // _di_fss_write_program_name_

#ifndef _di_fss_write_defines_
  const f_string_static_t fss_write_pipe_content_end_s = macro_f_string_static_t_initialize(FSS_WRITE_pipe_content_end_s, 0, FSS_WRITE_pipe_content_end_s_length);
  const f_string_static_t fss_write_pipe_content_ignore_s = macro_f_string_static_t_initialize(FSS_WRITE_pipe_content_ignore_s, 0, FSS_WRITE_pipe_content_ignore_s_length);
  const f_string_static_t fss_write_pipe_content_start_s = macro_f_string_static_t_initialize(FSS_WRITE_pipe_content_start_s, 0, FSS_WRITE_pipe_content_start_s_length);
#endif // _di_fss_write_defines_

#ifndef _di_fss_write_strings_
  const f_string_static_t fss_write_string_two_s = macro_f_string_static_t_initialize(FSS_WRITE_string_two_s, 0, FSS_WRITE_string_two_s_length);
#endif // _di_fss_write_strings_

#ifndef _di_fss_write_parameters_
  const f_string_static_t fss_write_short_as_s = macro_f_string_static_t_initialize(FSS_WRITE_short_as_s, 0, FSS_WRITE_short_as_s_length);
  const f_string_static_t fss_write_short_content_s = macro_f_string_static_t_initialize(FSS_WRITE_short_content_s, 0, FSS_WRITE_short_content_s_length);
  const f_string_static_t fss_write_short_double_s = macro_f_string_static_t_initialize(FSS_WRITE_short_double_s, 0, FSS_WRITE_short_double_s_length);
  const f_string_static_t fss_write_short_file_s = macro_f_string_static_t_initialize(FSS_WRITE_short_file_s, 0, FSS_WRITE_short_file_s_length);
  const f_string_static_t fss_write_short_ignore_s = macro_f_string_static_t_initialize(FSS_WRITE_short_ignore_s, 0, FSS_WRITE_short_ignore_s_length);
  const f_string_static_t fss_write_short_object_s = macro_f_string_static_t_initialize(FSS_WRITE_short_object_s, 0, FSS_WRITE_short_object_s_length);
  const f_string_static_t fss_write_short_partial_s = macro_f_string_static_t_initialize(FSS_WRITE_short_partial_s, 0, FSS_WRITE_short_partial_s_length);
  const f_string_static_t fss_write_short_prepend_s = macro_f_string_static_t_initialize(FSS_WRITE_short_prepend_s, 0, FSS_WRITE_short_prepend_s_length);
  const f_string_static_t fss_write_short_single_s = macro_f_string_static_t_initialize(FSS_WRITE_short_single_s, 0, FSS_WRITE_short_single_s_length);
  const f_string_static_t fss_write_short_trim_s = macro_f_string_static_t_initialize(FSS_WRITE_short_trim_s, 0, FSS_WRITE_short_trim_s_length);

  const f_string_static_t fss_write_long_as_s = macro_f_string_static_t_initialize(FSS_WRITE_long_as_s, 0, FSS_WRITE_long_as_s_length);
  const f_string_static_t fss_write_long_content_s = macro_f_string_static_t_initialize(FSS_WRITE_long_content_s, 0, FSS_WRITE_long_content_s_length);
  const f_string_static_t fss_write_long_double_s = macro_f_string_static_t_initialize(FSS_WRITE_long_double_s, 0, FSS_WRITE_long_double_s_length);
  const f_string_static_t fss_write_long_file_s = macro_f_string_static_t_initialize(FSS_WRITE_long_file_s, 0, FSS_WRITE_long_file_s_length);
  const f_string_static_t fss_write_long_ignore_s = macro_f_string_static_t_initialize(FSS_WRITE_long_ignore_s, 0, FSS_WRITE_long_ignore_s_length);
  const f_string_static_t fss_write_long_object_s = macro_f_string_static_t_initialize(FSS_WRITE_long_object_s, 0, FSS_WRITE_long_object_s_length);
  const f_string_static_t fss_write_long_partial_s = macro_f_string_static_t_initialize(FSS_WRITE_long_partial_s, 0, FSS_WRITE_long_partial_s_length);
  const f_string_static_t fss_write_long_prepend_s = macro_f_string_static_t_initialize(FSS_WRITE_long_prepend_s, 0, FSS_WRITE_long_prepend_s_length);
  const f_string_static_t fss_write_long_single_s = macro_f_string_static_t_initialize(FSS_WRITE_long_single_s, 0, FSS_WRITE_long_single_s_length);
  const f_string_static_t fss_write_long_trim_s = macro_f_string_static_t_initialize(FSS_WRITE_long_trim_s, 0, FSS_WRITE_long_trim_s_length);
#endif // _di_fss_write_parameters_

#ifndef _di_fss_write_setting_delete_
  f_status_t fss_write_setting_delete(fss_write_setting_t * const setting) {

    if (!setting) return F_status_set_error(F_parameter);

    f_string_dynamic_resize(0, &setting->escaped);
    f_string_dynamic_resize(0, &setting->block);
    f_string_dynamic_resize(0, &setting->buffer);
    f_string_dynamic_resize(0, &setting->object);
    f_string_dynamic_resize(0, &setting->content);
    f_string_dynamic_resize(0, &setting->prepend);

    f_string_ranges_resize(0, &setting->ignores);
    f_string_dynamics_resize(0, &setting->objects);
    f_string_dynamics_resize(0, &setting->contents);

    return F_none;
  }
#endif // _di_fss_write_setting_delete_

#ifndef _di_fss_write_setting_load_
  void fss_write_setting_load(const f_console_arguments_t arguments, fll_program_data_t * const main, fss_write_setting_t * const setting) {

    if (!main || !setting) return;

    setting->flag = 0;

    // Load parameters.
    setting->status = f_console_parameter_process(arguments, &main->parameters);

    if (F_status_is_error(setting->status)) {
      fss_write_print_error(setting, main->error, "f_console_parameter_process");

      return;
    }

    {
      f_array_length_t choice = 0;
      f_uint16s_t choices = f_uint16s_t_initialize;

      // Identify and prioritize "color context" parameters.
      {
        uint16_t choices_array[3] = { fss_write_parameter_no_color_e, fss_write_parameter_light_e, fss_write_parameter_dark_e };
        choices.array = choices_array;
        choices.used = 3;

        const uint8_t modes[3] = { f_color_mode_color_not_e, f_color_mode_light_e, f_color_mode_dark_e };

        setting->status = fll_program_parameter_process_context(choices, modes, F_true, main);

        if (F_status_is_error(setting->status)) {
          fss_write_print_error(setting, main->error, "fll_program_parameter_process_context");

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

        setting->status = fll_program_parameter_process_verbosity(choices, verbosity, F_true, main);

        if (F_status_is_error(setting->status)) {
          fss_write_print_error(setting, main->error, "fll_program_parameter_process_verbosity");

          return;
        }
      }

      if (main->parameters.array[fss_write_parameter_help_e].result & f_console_result_found_e) {
        setting->flag |= fss_write_main_flag_help_e;

        return;
      }

      if (main->parameters.array[fss_write_parameter_version_e].result & f_console_result_found_e) {
        setting->flag |= fss_write_main_flag_version_e;

        return;
      }
    }

    main->output.to.id = F_type_descriptor_output_d;
    main->output.to.stream = F_type_output_d;
    main->output.to.flag = F_file_flag_create_d | F_file_flag_write_only_d | F_file_flag_append_d;

    if (main->parameters.array[fss_write_parameter_file_e].result & f_console_result_value_e && main->parameters.array[fss_write_parameter_file_e].values.used) {
      // @todo check the "-a/--as" and select format or fallback to FSS-0000 Basic (support either digits "0000"/"0001" or simple names "basic"/"basic_list".
    // Fallback only happens if -a/--as is not disabled, otherwise the callback function should be pre-defined.
    }
    else if (main->parameters.array[fss_write_parameter_as_e].result & f_console_result_found_e) {
      setting->status = F_status_set_error(F_parameter);

      fss_write_print_line_first_locked(setting, main->error);
      fll_program_print_error_parameter_missing_value(main->error, f_console_symbol_long_normal_s, fss_write_long_file_s);
      fss_write_print_line_last_locked(setting, main->error);

      return;
    }

    if (main->parameters.array[fss_write_parameter_file_e].result & f_console_result_value_e && main->parameters.array[fss_write_parameter_file_e].values.used) {
      if (main->parameters.array[fss_write_parameter_file_e].values.used > 1) {
        setting->status = F_status_set_error(F_parameter);

        fss_write_print_line_first_locked(setting, main->error);
        fll_program_print_error_parameter_must_specify_once(main->error, f_console_symbol_long_normal_s, fss_write_long_file_s);
        fss_write_print_line_last_locked(setting, main->error);

        return;
      }

      const f_array_length_t index = main->parameters.array[fss_write_parameter_file_e].values.array[0];

      main->output.to.id = -1;
      main->output.to.stream = 0;

      setting->status = f_file_stream_open(main->parameters.arguments.array[index], f_string_empty_s, &main->output.to);

      if (F_status_is_error(setting->status)) {
        fss_write_print_error_file(setting, main->error, "f_file_stream_open", main->parameters.arguments.array[index], f_file_operation_open_s, fll_error_file_type_file_e);

        return;
      }

      setting->flag |= fss_write_main_flag_file_to_e;
    }
    else if (main->parameters.array[fss_write_parameter_file_e].result & f_console_result_found_e) {
      setting->status = F_status_set_error(F_parameter);

      fss_write_print_line_first_locked(setting, main->error);
      fll_program_print_error_parameter_missing_value(main->error, f_console_symbol_long_normal_s, fss_write_long_file_s);
      fss_write_print_line_last_locked(setting, main->error);

      return;
    }

    if (main->parameters.array[fss_write_parameter_object_e].result & f_console_result_value_e && main->parameters.array[fss_write_parameter_object_e].values.used) {
      f_array_lengths_t * const values = &main->parameters.array[fss_write_parameter_object_e].values;

      setting->objects.used = 0;

      setting->status = f_string_dynamics_resize(values->used, &setting->objects);

      if (F_status_is_error(setting->status)) {
        fss_write_print_error(setting, main->error, "f_string_dynamics_resize");

        return;
      }

      // Construct the array without allocating any more memory by setting this as a static string (used > 0, size = 0).
      for (f_array_length_t index = 0; setting->objects.used < values->used; ) {

        index = values->array[setting->objects.used];

        setting->objects.array[setting->objects.used].string = main->parameters.arguments.array[index].string;
        setting->objects.array[setting->objects.used].used = main->parameters.arguments.array[index].used;
        setting->objects.array[setting->objects.used++].size = 0;
      } // for

      setting->flag |= fss_write_main_flag_object_e;
    }
    else if (main->parameters.array[fss_write_parameter_object_e].result & f_console_result_found_e) {
      setting->status = F_status_set_error(F_parameter);

      fss_write_print_line_first_locked(setting, main->error);
      fll_program_print_error_parameter_missing_value(main->error, f_console_symbol_long_normal_s, fss_write_long_object_s);
      fss_write_print_line_last_locked(setting, main->error);

      return;
    }

    if (main->parameters.array[fss_write_parameter_content_e].result & f_console_result_value_e && main->parameters.array[fss_write_parameter_content_e].values.used) {
      f_array_lengths_t * const values = &main->parameters.array[fss_write_parameter_content_e].values;

      setting->contents.used = 0;

      setting->status = f_string_dynamics_resize(values->used, &setting->contents);

      if (F_status_is_error(setting->status)) {
        fss_write_print_error(setting, main->error, "f_string_dynamics_resize");

        return;
      }

      // Construct the array without allocating any more memory by setting this as a static string (used > 0, size = 0).
      for (f_array_length_t index = 0; setting->contents.used < values->used; ) {

        index = values->array[setting->contents.used];

        setting->contents.array[setting->contents.used].string = main->parameters.arguments.array[index].string;
        setting->contents.array[setting->contents.used].used = main->parameters.arguments.array[index].used;
        setting->contents.array[setting->contents.used++].size = 0;
      } // for

      setting->flag |= fss_write_main_flag_content_e;
    }
    else if (main->parameters.array[fss_write_parameter_content_e].result & f_console_result_found_e) {
      setting->status = F_status_set_error(F_parameter);

      fss_write_print_line_first_locked(setting, main->error);
      fll_program_print_error_parameter_missing_value(main->error, f_console_symbol_long_normal_s, fss_write_long_content_s);
      fss_write_print_line_last_locked(setting, main->error);

      return;
    }

    if (main->parameters.array[fss_write_parameter_prepend_e].result & f_console_result_value_e && main->parameters.array[fss_write_parameter_prepend_e].values.used) {
      const f_array_length_t index = main->parameters.array[fss_write_parameter_prepend_e].values.array[main->parameters.array[fss_write_parameter_prepend_e].values.used - 1];

      setting->prepend.used = 0;

      setting->status = f_string_dynamic_append_nulless(main->parameters.arguments.array[index], &setting->prepend);

      if (F_status_is_error(setting->status)) {
        fss_write_print_error(setting, main->error, "f_string_dynamic_append_nulless");

        return;
      }

      if (main->parameters.arguments.array[index].used) {
        f_string_range_t range = macro_f_string_range_t_initialize2(main->parameters.arguments.array[index].used);
        f_state_t state = f_state_t_initialize;

        for (; range.start < main->parameters.arguments.array[index].used; range.start++) {

          setting->status = f_fss_is_space(state, main->parameters.arguments.array[index], range);

          if (F_status_is_error(setting->status)) {
            fss_write_print_error(setting, main->error, "f_fss_is_space");

            return;
          }

          if (setting->status == F_false) {
            setting->status = F_status_set_error(F_parameter);

            fss_write_print_error_prepend_only_whitespace(setting, main->error);

            return;
          }
        } // for
      }

      setting->flag |= fss_write_main_flag_prepend_e;
    }
    else if (main->parameters.array[fss_write_parameter_prepend_e].result & f_console_result_found_e) {
      setting->status = F_status_set_error(F_parameter);

      fss_write_print_line_first_locked(setting, main->error);
      fll_program_print_error_parameter_missing_value(main->error, f_console_symbol_long_normal_s, fss_write_long_prepend_s);
      fss_write_print_line_last_locked(setting, main->error);

      return;
    }

    if (main->parameters.array[fss_write_parameter_ignore_e].result & f_console_result_value_e && main->parameters.array[fss_write_parameter_ignore_e].values.used) {

      if (main->parameters.array[fss_write_parameter_ignore_e].values.used % 2 != 0) {
        setting->status = F_status_set_error(F_parameter);

        fss_write_print_line_first_locked(setting, main->error);
        fll_program_print_error_parameter_missing_value_requires_amount(main->error, f_console_symbol_long_normal_s, fss_write_long_ignore_s, fss_write_string_two_s);
        fss_write_print_line_last_locked(setting, main->error);

        return;
      }

      setting->ignores.used = 0;

      setting->status = f_string_ranges_increase_by(main->parameters.array[fss_write_parameter_ignore_e].values.used / 2, &setting->ignores);

      if (F_status_is_error(setting->status)) {
        fss_write_print_error(setting, main->error, "f_string_ranges_increase_by");

        return;
      }

      f_array_length_t index = 0;

      for (f_array_length_t i = 0; i < main->parameters.array[fss_write_parameter_ignore_e].values.used; i += 2) {

        index = main->parameters.array[fss_write_parameter_ignore_e].values.array[i];

        setting->status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, main->parameters.arguments.array[index], &setting->ignores.array[setting->ignores.used].start);

        if (F_status_is_error(setting->status)) {
          fss_write_print_line_first_locked(setting, main->error);
          fll_program_print_error_parameter_integer_not(main->error, f_console_symbol_long_normal_s, fss_write_long_ignore_s, main->parameters.arguments.array[index]);
          fss_write_print_line_last_locked(setting, main->error);

          return;
        }

        index = main->parameters.array[fss_write_parameter_ignore_e].values.array[i + 1];

        setting->status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, main->parameters.arguments.array[index], &setting->ignores.array[setting->ignores.used].stop);

        if (F_status_is_error(setting->status)) {
          fss_write_print_line_first_locked(setting, main->error);
          fll_program_print_error_parameter_integer_not(main->error, f_console_symbol_long_normal_s, fss_write_long_ignore_s, main->parameters.arguments.array[index]);
          fss_write_print_line_last_locked(setting, main->error);

          return;
        }

        if (setting->ignores.array[setting->ignores.used].stop > setting->ignores.array[setting->ignores.used].start) {
          setting->status = F_status_set_error(F_parameter);

          fss_write_print_line_first_locked(setting, main->error);
          fll_program_print_error_parameter_range_start_before_stop(main->error, f_console_symbol_long_normal_s, fss_write_long_ignore_s, main->parameters.arguments.array[main->parameters.array[fss_write_parameter_ignore_e].values.array[i]], main->parameters.arguments.array[index]);
          fss_write_print_line_last_locked(setting, main->error);

          return;
        }

        ++setting->ignores.used;
      } // for

      setting->flag |= fss_write_main_flag_ignore_e;
    }
    else if (main->parameters.array[fss_write_parameter_ignore_e].result & f_console_result_found_e) {
      setting->status = F_status_set_error(F_parameter);

      fss_write_print_line_first_locked(setting, main->error);
      fll_program_print_error_parameter_missing_value(main->error, f_console_symbol_long_normal_s, fss_write_long_ignore_s);
      fss_write_print_line_last_locked(setting, main->error);

      return;
    }

    if (main->parameters.array[fss_write_parameter_partial_e].result & f_console_result_found_e) {
      setting->flag |= fss_write_main_flag_partial_e;
    }

    if (setting->flag & (fss_write_main_flag_object_e | fss_write_main_flag_content_e)) {
      if (setting->flag & fss_write_main_flag_object_e) {
        if (main->parameters.array[fss_write_parameter_object_e].locations.used != main->parameters.array[fss_write_parameter_object_e].values.used) {
          setting->status = F_status_set_error(F_parameter);

          fss_write_print_line_first_locked(setting, main->error);
          fll_program_print_error_parameter_missing_value(main->error, f_console_symbol_long_normal_s, fss_write_long_object_s);
          fss_write_print_line_last_locked(setting, main->error);

          return;
        }

        if (main->parameters.array[fss_write_parameter_content_e].locations.used != main->parameters.array[fss_write_parameter_content_e].values.used) {
          setting->status = F_status_set_error(F_parameter);

          fss_write_print_line_first_locked(setting, main->error);
          fll_program_print_error_parameter_missing_value(main->error, f_console_symbol_long_normal_s, fss_write_long_content_s);
          fss_write_print_line_last_locked(setting, main->error);

          return;
        }

        if (main->parameters.array[fss_write_parameter_object_e].locations.used != main->parameters.array[fss_write_parameter_content_e].locations.used && !(setting->flag & fss_write_main_flag_partial_e)) {
          setting->status = F_status_set_error(F_parameter);

          fss_write_print_line_first_locked(setting, main->error);
          fll_program_print_error_parameter_both_specified_same_amount_without(main->error, f_console_symbol_long_normal_s, f_console_symbol_long_normal_s, f_console_symbol_long_normal_s, fss_write_long_object_s, fss_write_long_content_s, fss_write_long_partial_s);
          fss_write_print_line_last_locked(setting, main->error);

          return;
        }

        if ((setting->flag & fss_write_main_flag_content_e) && (setting->flag & fss_write_main_flag_partial_e)) {
          if (main->parameters.array[fss_write_parameter_content_e].result & f_console_result_value_e) {
            setting->status = F_status_set_error(F_parameter);

            fss_write_print_line_first_locked(setting, main->error);
            fll_program_print_error_parameter_cannot_use_with_xor(main->error, f_console_symbol_long_normal_s, f_console_symbol_long_normal_s, f_console_symbol_long_normal_s, fss_write_long_partial_s, fss_write_long_object_s, fss_write_long_content_s);
            fss_write_print_line_last_locked(setting, main->error);

            return;
          }
        }

        if (setting->flag & fss_write_main_flag_content_e) {
          f_array_length_t location_object = 0;
          f_array_length_t location_content = 0;
          f_array_length_t location_sub_object = 0;
          f_array_length_t location_sub_content = 0;

          for (f_array_length_t i = 0; i < main->parameters.array[fss_write_parameter_object_e].locations.used; ++i) {

            location_object = main->parameters.array[fss_write_parameter_object_e].locations.array[i];
            location_content = main->parameters.array[fss_write_parameter_content_e].locations.array[i];
            location_sub_object = main->parameters.array[fss_write_parameter_object_e].locations_sub.array[i];
            location_sub_content = main->parameters.array[fss_write_parameter_content_e].locations_sub.array[i];

            if (location_object > location_content || location_object == location_content && location_sub_object > location_sub_content) {
              setting->status = F_status_set_error(F_parameter);

              fss_write_print_line_first_locked(setting, main->error);
              fss_write_print_error_object_not_before_content(setting, main->error);
              fss_write_print_line_last_locked(setting, main->error);

              break;
            }
          } // for
        }
      }
    }

    setting->quote = f_fss_quote_double_s;

    if (main->parameters.array[fss_write_parameter_double_e].result & f_console_result_found_e) {
      if (main->parameters.array[fss_write_parameter_single_e].result & f_console_result_found_e) {
        if (main->parameters.array[fss_write_parameter_double_e].location < main->parameters.array[fss_write_parameter_single_e].location) {
          setting->quote = f_fss_quote_single_s;
        }
      }
    }
    else if (main->parameters.array[fss_write_parameter_single_e].result & f_console_result_found_e) {
      setting->quote = f_fss_quote_single_s;
    }

    if (main->parameters.array[fss_write_parameter_trim_e].result & f_console_result_found_e) {
      setting->flag |= fss_write_main_flag_trim_e;
    }

    if (!(setting->flag & (fll_program_data_pipe_input_e | fss_write_main_flag_content_e | fss_write_parameter_object_e))) {
      setting->status = F_data_not;
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
