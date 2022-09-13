#include "iki_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_write_program_version_
  const f_string_static_t iki_write_program_version_s = macro_f_string_static_t_initialize(IKI_WRITE_program_version_s, 0, IKI_WRITE_program_version_s_length);
#endif // _di_iki_write_program_version_

#ifndef _di_iki_write_program_name_
  const f_string_static_t iki_write_program_name_s = macro_f_string_static_t_initialize(IKI_WRITE_program_name_s, 0, IKI_WRITE_program_name_s_length);
  const f_string_static_t iki_write_program_name_long_s = macro_f_string_static_t_initialize(IKI_WRITE_program_name_long_s, 0, IKI_WRITE_program_name_long_s_length);
#endif // _di_iki_write_program_name_

#ifndef _di_iki_write_strings_
  const f_string_static_t iki_write_object_s = macro_f_string_static_t_initialize(IKI_WRITE_object_s, 0, IKI_WRITE_object_s_length);
#endif // _di_iki_write_strings_

#ifndef _di_iki_write_parameters_
  const f_string_static_t iki_write_short_file_s = macro_f_string_static_t_initialize(IKI_WRITE_short_file_s, 0, IKI_WRITE_short_file_s_length);
  const f_string_static_t iki_write_short_content_s = macro_f_string_static_t_initialize(IKI_WRITE_short_content_s, 0, IKI_WRITE_short_content_s_length);
  const f_string_static_t iki_write_short_double_s = macro_f_string_static_t_initialize(IKI_WRITE_short_double_s, 0, IKI_WRITE_short_double_s_length);
  const f_string_static_t iki_write_short_object_s = macro_f_string_static_t_initialize(IKI_WRITE_short_object_s, 0, IKI_WRITE_short_object_s_length);
  const f_string_static_t iki_write_short_single_s = macro_f_string_static_t_initialize(IKI_WRITE_short_single_s, 0, IKI_WRITE_short_single_s_length);

  const f_string_static_t iki_write_long_file_s = macro_f_string_static_t_initialize(IKI_WRITE_long_file_s, 0, IKI_WRITE_long_file_s_length);
  const f_string_static_t iki_write_long_content_s = macro_f_string_static_t_initialize(IKI_WRITE_long_content_s, 0, IKI_WRITE_long_content_s_length);
  const f_string_static_t iki_write_long_double_s = macro_f_string_static_t_initialize(IKI_WRITE_long_double_s, 0, IKI_WRITE_long_double_s_length);
  const f_string_static_t iki_write_long_object_s = macro_f_string_static_t_initialize(IKI_WRITE_long_object_s, 0, IKI_WRITE_long_object_s_length);
  const f_string_static_t iki_write_long_single_s = macro_f_string_static_t_initialize(IKI_WRITE_long_single_s, 0, IKI_WRITE_long_single_s_length);
#endif // _di_iki_write_parameters_

#ifndef _di_iki_write_setting_delete_
  f_status_t iki_write_setting_delete(iki_write_setting_t * const setting) {

    if (!setting) return F_status_set_error(F_parameter);

    f_string_dynamic_resize(0, &setting->escaped);
    f_string_dynamic_resize(0, &setting->buffer);
    f_string_dynamic_resize(0, &setting->object);
    f_string_dynamic_resize(0, &setting->content);

    f_string_dynamics_resize(0, &setting->objects);
    f_string_dynamics_resize(0, &setting->contents);

    return F_none;
  }
#endif // _di_iki_write_setting_delete_

#ifndef _di_iki_write_setting_load_
  void iki_write_setting_load(const f_console_arguments_t arguments, fll_program_data_t * const main, iki_write_setting_t * const setting) {

    if (!main || !setting) return;

    // Load parameters.
    setting->status = f_console_parameter_process(arguments, &main->parameters);

    if (F_status_is_error(setting->status)) {
      iki_write_print_line_first_locked(setting, main->error);
      fll_error_print(main->error, F_status_set_fine(setting->status), "f_console_parameter_process", F_true);
      iki_write_print_line_last_locked(setting, main->error);

      return;
    }

    {
      f_array_length_t choice = 0;
      f_uint16s_t choices = f_uint16s_t_initialize;

      // Identify and prioritize "color context" parameters.
      {
        uint16_t choices_array[3] = { iki_write_parameter_no_color_e, iki_write_parameter_light_e, iki_write_parameter_dark_e };
        choices.array = choices_array;
        choices.used = 3;

        const uint8_t modes[3] = { f_color_mode_color_not_e, f_color_mode_light_e, f_color_mode_dark_e };

        setting->status = fll_program_parameter_process_context(choices, modes, F_true, main);

        if (F_status_is_error(setting->status)) {
          iki_write_print_line_first_locked(setting, main->error);
          fll_error_print(main->error, F_status_set_fine(setting->status), "fll_program_parameter_process_context", F_true);
          iki_write_print_line_last_locked(setting, main->error);

          return;
        }
      }

      if (main->parameters.array[iki_write_parameter_line_first_no_e].result == f_console_result_found_e) {
        setting->line_first = f_string_empty_s;
      }
      else {
        setting->line_first = f_string_eol_s;
      }

      if (main->parameters.array[iki_write_parameter_line_last_no_e].result == f_console_result_found_e) {
        setting->line_last = f_string_empty_s;
      }
      else {
        setting->line_last = f_string_eol_s;
      }

      // Identify and prioritize "verbosity" parameters.
      {
        uint16_t choices_array[5] = { iki_write_parameter_verbosity_quiet_e, iki_write_parameter_verbosity_error_e, iki_write_parameter_verbosity_verbose_e, iki_write_parameter_verbosity_debug_e, iki_write_parameter_verbosity_normal_e };
        choices.array = choices_array;
        choices.used = 5;

        const uint8_t verbosity[5] = { f_console_verbosity_quiet_e, f_console_verbosity_error_e, f_console_verbosity_verbose_e, f_console_verbosity_debug_e, f_console_verbosity_normal_e };

        setting->status = fll_program_parameter_process_verbosity(choices, verbosity, F_true, main);

        if (F_status_is_error(setting->status)) {
          iki_write_print_line_first_locked(setting, main->error);
          fll_error_print(main->error, F_status_set_fine(setting->status), "fll_program_parameter_process_verbosity", F_true);
          iki_write_print_line_last_locked(setting, main->error);

          return;
        }
      }

      if (main->parameters.array[iki_write_parameter_help_e].result == f_console_result_found_e) {
        setting->flag |= iki_write_main_flag_help_e;

        return;
      }

      if (main->parameters.array[iki_write_parameter_version_e].result == f_console_result_found_e) {
        setting->flag |= iki_write_main_flag_version_e;

        return;
      }
    }

    main->output.to.id = F_type_descriptor_output_d;
    main->output.to.stream = F_type_output_d;
    main->output.to.flag = F_file_flag_create_d | F_file_flag_write_only_d | F_file_flag_append_d;

    if (main->parameters.array[iki_write_parameter_file_e].result == f_console_result_additional_e) {
      if (main->parameters.array[iki_write_parameter_file_e].values.used > 1) {
        setting->status = F_status_set_error(F_parameter);

        iki_write_print_line_first_locked(setting, main->error);
        fll_program_print_error_parameter_must_specify_once(main->error, f_console_symbol_long_enable_s, iki_write_long_file_s);
        iki_write_print_line_last_locked(setting, main->error);

        return;
      }

      f_string_static_t * const args = main->parameters.arguments.array;

      const f_array_length_t index = main->parameters.array[iki_write_parameter_file_e].values.array[0];

      main->output.to.id = -1;
      main->output.to.stream = 0;

      setting->status = f_file_stream_open(args[index], f_string_empty_s, &main->output.to);

      if (F_status_is_error(setting->status)) {
        iki_write_print_line_first_locked(setting, main->error);
        fll_error_file_print(main->error, F_status_set_fine(setting->status), "f_file_stream_open", F_true, args[index], f_file_operation_open_s, fll_error_file_type_file_e);
        iki_write_print_line_last_locked(setting, main->error);

        return;
      }

      setting->flag |= iki_write_main_flag_file_to_e;
    }
    else if (main->parameters.array[iki_write_parameter_file_e].result == f_console_result_found_e) {
      setting->status = F_status_set_error(F_parameter);

      iki_write_print_line_first_locked(setting, main->error);
      fll_program_print_error_parameter_missing_value(main->error, f_console_symbol_long_enable_s, iki_write_long_file_s);
      iki_write_print_line_last_locked(setting, main->error);

      return;
    }

    if (main->parameters.array[iki_write_parameter_object_e].result == f_console_result_additional_e) {
      f_array_lengths_t * const values = &main->parameters.array[iki_write_parameter_object_e].values;

      setting->objects.used = 0;

      setting->status = f_string_dynamics_resize(values->used, &setting->objects);

      if (F_status_is_error(setting->status)) {
        iki_write_print_line_first_locked(setting, main->error);
        fll_error_print(main->error, F_status_set_fine(setting->status), "f_string_dynamics_resize", F_true);
        iki_write_print_line_last_locked(setting, main->error);

        return;
      }

      // Construct the array without allocating any more memory by setting this as a static string (used > 0, size = 0).
      for (f_array_length_t index = 0; setting->objects.used < values->used; ) {

        index = values->array[setting->objects.used];

        setting->objects.array[setting->objects.used].string = main->parameters.arguments.array[index].string;
        setting->objects.array[setting->objects.used].used = main->parameters.arguments.array[index].used;
        setting->objects.array[setting->objects.used++].size = 0;
      } // for

      setting->flag |= iki_write_main_flag_object_e;
    }
    else if (main->parameters.array[iki_write_parameter_object_e].result == f_console_result_found_e) {
      setting->status = F_status_set_error(F_parameter);

      iki_write_print_line_first_locked(setting, main->error);
      fll_program_print_error_parameter_missing_value(main->error, f_console_symbol_long_enable_s, iki_write_long_object_s);
      iki_write_print_line_last_locked(setting, main->error);

      return;
    }

    if (main->parameters.array[iki_write_parameter_content_e].result == f_console_result_additional_e) {
      f_array_lengths_t * const values = &main->parameters.array[iki_write_parameter_content_e].values;

      setting->contents.used = 0;

      setting->status = f_string_dynamics_resize(values->used, &setting->contents);

      if (F_status_is_error(setting->status)) {
        iki_write_print_line_first_locked(setting, main->error);
        fll_error_print(main->error, F_status_set_fine(setting->status), "f_string_dynamics_resize", F_true);
        iki_write_print_line_last_locked(setting, main->error);

        return;
      }

      // Construct the array without allocating any more memory by setting this as a static string (used > 0, size = 0).
      for (f_array_length_t index = 0; setting->contents.used < values->used; ) {

        index = values->array[setting->contents.used];

        setting->contents.array[setting->contents.used].string = main->parameters.arguments.array[index].string;
        setting->contents.array[setting->contents.used].used = main->parameters.arguments.array[index].used;
        setting->contents.array[setting->contents.used++].size = 0;
      } // for

      setting->flag |= iki_write_main_flag_content_e;
    }
    else if (main->parameters.array[iki_write_parameter_content_e].result == f_console_result_found_e) {
      setting->status = F_status_set_error(F_parameter);

      iki_write_print_line_first_locked(setting, main->error);
      fll_program_print_error_parameter_missing_value(main->error, f_console_symbol_long_enable_s, iki_write_long_content_s);
      iki_write_print_line_last_locked(setting, main->error);

      return;
    }

    if (!(main->pipe & fll_program_data_pipe_input_e) && !(setting->flag & (iki_write_main_flag_content_e | iki_write_parameter_object_e))) {
      setting->status = F_status_set_error(F_parameter);

      iki_write_print_line_first_locked(setting, main->error);
      iki_write_print_error_main_missing(setting, main->error);
      iki_write_print_line_last_locked(setting, main->error);

      return;
    }

    setting->quote = f_iki_syntax_quote_double_s;

    if (main->parameters.array[iki_write_parameter_double_e].result == f_console_result_found_e) {
      if (main->parameters.array[iki_write_parameter_single_e].result == f_console_result_found_e) {
        if (main->parameters.array[iki_write_parameter_double_e].location < main->parameters.array[iki_write_parameter_single_e].location) {
          setting->quote = f_iki_syntax_quote_single_s;
        }
      }
    }
    else if (main->parameters.array[iki_write_parameter_single_e].result == f_console_result_found_e) {
      setting->quote = f_iki_syntax_quote_single_s;
    }
  }
#endif // _di_iki_write_setting_load_

#ifndef _di_iki_write_setting_unload_
  f_status_t iki_write_setting_unload(fll_program_data_t * const main, iki_write_setting_t * const setting) {

    if (!main || !setting) return F_status_set_error(F_parameter);

    iki_write_setting_delete(setting);

    return F_none;
  }
#endif // _di_iki_write_setting_unload_

#ifdef __cplusplus
} // extern "C"
#endif
