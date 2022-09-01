#include "utf8.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_utf8_program_version_
  const f_string_static_t utf8_program_version_s = macro_f_string_static_t_initialize(UTF8_program_version_s, 0, UTF8_program_version_s_length);
#endif // _di_utf8_program_version_

#ifndef _di_utf8_program_name_
  const f_string_static_t utf8_program_name_s = macro_f_string_static_t_initialize(UTF8_program_name_s, 0, UTF8_program_name_s_length);
  const f_string_static_t utf8_program_name_long_s = macro_f_string_static_t_initialize(UTF8_program_name_long_s, 0, UTF8_program_name_long_s_length);
#endif // _di_utf8_program_name_

#ifndef _di_utf8_program_help_parameters_
  const f_string_static_t utf8_program_help_parameters_s = macro_f_string_static_t_initialize(UTF8_program_help_parameters_s, 0, UTF8_program_help_parameters_s_length);
#endif // _di_utf8_program_help_parameters_

#ifndef _di_utf8_defines_
  const f_string_static_t utf8_string_combining_is_s = macro_f_string_static_t_initialize(UTF8_string_combining_is_s, 0, UTF8_string_combining_is_s_length);
  const f_string_static_t utf8_string_combining_not_s = macro_f_string_static_t_initialize(UTF8_string_combining_not_s, 0, UTF8_string_combining_not_s_length);
  const f_string_static_t utf8_string_unknown_s = macro_f_string_static_t_initialize(UTF8_string_unknown_s, 0, UTF8_string_unknown_s_length);

  const f_string_static_t utf8_string_from_s = macro_f_string_static_t_initialize(UTF8_string_from_s, 0, UTF8_string_from_s_length);
  const f_string_static_t utf8_string_to_s = macro_f_string_static_t_initialize(UTF8_string_to_s, 0, UTF8_string_to_s_length);

  const f_string_static_t utf8_string_prepend_padding_s = macro_f_string_static_t_initialize(UTF8_string_prepend_padding_s, 0, UTF8_string_prepend_padding_s_length);

  const f_string_static_t utf8_string_valid_not_s = macro_f_string_static_t_initialize(UTF8_string_valid_not_s, 0, UTF8_string_valid_not_s_length);

  const f_string_static_t utf8_string_verified_valid_s = macro_f_string_static_t_initialize(UTF8_string_verified_valid_s, 0, UTF8_string_verified_valid_s_length);
  const f_string_static_t utf8_string_verified_valid_not_s = macro_f_string_static_t_initialize(UTF8_string_verified_valid_not_s, 0, UTF8_string_verified_valid_not_s_length);

  const f_string_static_t utf8_string_width_0_s = macro_f_string_static_t_initialize(UTF8_string_width_0_s, 0, UTF8_string_width_0_s_length);
  const f_string_static_t utf8_string_width_1_s = macro_f_string_static_t_initialize(UTF8_string_width_1_s, 0, UTF8_string_width_1_s_length);
  const f_string_static_t utf8_string_width_2_s = macro_f_string_static_t_initialize(UTF8_string_width_2_s, 0, UTF8_string_width_2_s_length);
  const f_string_static_t utf8_string_width_3_s = macro_f_string_static_t_initialize(UTF8_string_width_3_s, 0, UTF8_string_width_3_s_length);
  const f_string_static_t utf8_string_width_4_s = macro_f_string_static_t_initialize(UTF8_string_width_4_s, 0, UTF8_string_width_4_s_length);
#endif // _di_utf8_defines_

#ifndef _di_utf8_parameters_
  const f_string_static_t utf8_short_from_bytesequence_s = macro_f_string_static_t_initialize(UTF8_short_from_bytesequence_s, 0, UTF8_short_from_bytesequence_s_length);
  const f_string_static_t utf8_short_from_codepoint_s = macro_f_string_static_t_initialize(UTF8_short_from_codepoint_s, 0, UTF8_short_from_codepoint_s_length);
  const f_string_static_t utf8_short_from_file_s = macro_f_string_static_t_initialize(UTF8_short_from_file_s, 0, UTF8_short_from_file_s_length);

  const f_string_static_t utf8_short_headers_s = macro_f_string_static_t_initialize(UTF8_short_headers_s, 0, UTF8_short_headers_s_length);
  const f_string_static_t utf8_short_separate_s = macro_f_string_static_t_initialize(UTF8_short_separate_s, 0, UTF8_short_separate_s_length);
  const f_string_static_t utf8_short_strip_invalid_s = macro_f_string_static_t_initialize(UTF8_short_strip_invalid_s, 0, UTF8_short_strip_invalid_s_length);
  const f_string_static_t utf8_short_verify_s = macro_f_string_static_t_initialize(UTF8_short_verify_s, 0, UTF8_short_verify_s_length);

  const f_string_static_t utf8_short_to_bytesequence_s = macro_f_string_static_t_initialize(UTF8_short_to_bytesequence_s, 0, UTF8_short_to_bytesequence_s_length);
  const f_string_static_t utf8_short_to_codepoint_s = macro_f_string_static_t_initialize(UTF8_short_to_codepoint_s, 0, UTF8_short_to_codepoint_s_length);
  const f_string_static_t utf8_short_to_combining_s = macro_f_string_static_t_initialize(UTF8_short_to_combining_s, 0, UTF8_short_to_combining_s_length);
  const f_string_static_t utf8_short_to_file_s = macro_f_string_static_t_initialize(UTF8_short_to_file_s, 0, UTF8_short_to_file_s_length);
  const f_string_static_t utf8_short_to_width_s = macro_f_string_static_t_initialize(UTF8_short_to_width_s, 0, UTF8_short_to_width_s_length);

  const f_string_static_t utf8_long_from_bytesequence_s = macro_f_string_static_t_initialize(UTF8_long_from_bytesequence_s, 0, UTF8_long_from_bytesequence_s_length);
  const f_string_static_t utf8_long_from_codepoint_s = macro_f_string_static_t_initialize(UTF8_long_from_codepoint_s, 0, UTF8_long_from_codepoint_s_length);
  const f_string_static_t utf8_long_from_file_s = macro_f_string_static_t_initialize(UTF8_long_from_file_s, 0, UTF8_long_from_file_s_length);

  const f_string_static_t utf8_long_headers_s = macro_f_string_static_t_initialize(UTF8_long_headers_s, 0, UTF8_long_headers_s_length);
  const f_string_static_t utf8_long_separate_s = macro_f_string_static_t_initialize(UTF8_long_separate_s, 0, UTF8_long_separate_s_length);
  const f_string_static_t utf8_long_strip_invalid_s = macro_f_string_static_t_initialize(UTF8_long_strip_invalid_s, 0, UTF8_long_strip_invalid_s_length);
  const f_string_static_t utf8_long_verify_s = macro_f_string_static_t_initialize(UTF8_long_verify_s, 0, UTF8_long_verify_s_length);

  const f_string_static_t utf8_long_to_bytesequence_s = macro_f_string_static_t_initialize(UTF8_long_to_bytesequence_s, 0, UTF8_long_to_bytesequence_s_length);
  const f_string_static_t utf8_long_to_codepoint_s = macro_f_string_static_t_initialize(UTF8_long_to_codepoint_s, 0, UTF8_long_to_codepoint_s_length);
  const f_string_static_t utf8_long_to_combining_s = macro_f_string_static_t_initialize(UTF8_long_to_combining_s, 0, UTF8_long_to_combining_s_length);
  const f_string_static_t utf8_long_to_file_s = macro_f_string_static_t_initialize(UTF8_long_to_file_s, 0, UTF8_long_to_file_s_length);
  const f_string_static_t utf8_long_to_width_s = macro_f_string_static_t_initialize(UTF8_long_to_width_s, 0, UTF8_long_to_width_s_length);
#endif // _di_utf8_parameters_

#ifndef _di_utf8_setting_delete_
  f_status_t utf8_setting_delete(utf8_setting_t * const setting) {

    if (!setting) return F_status_set_error(F_parameter);

    f_string_dynamic_resize(0, &setting->buffer);
    f_string_dynamic_resize(0, &setting->text);

    f_string_dynamics_resize(0, &setting->path_files_from);
    f_string_dynamics_resize(0, &setting->path_files_to);
    f_string_dynamics_resize(0, &setting->remaining);

    return F_none;
  }
#endif // _di_utf8_setting_delete_

#ifndef _di_utf8_setting_load_
  void utf8_setting_load(const f_console_arguments_t arguments, fll_program_data_t * const main, utf8_setting_t * const setting) {

    if (!main || !setting) return;

    // Load parameters.
    setting->status = f_console_parameter_process(arguments, &main->parameters);

    if (F_status_is_error(setting->status)) {
      utf8_print_line_first(setting, main->error, F_true);
      fll_error_print(main->error, F_status_set_fine(setting->status), "f_console_parameter_process", F_true);
      utf8_print_line_last(setting, main->error, F_true);

      return;
    }

    {
      f_array_length_t choice = 0;
      f_uint16s_t choices = f_uint16s_t_initialize;

      // Identify and prioritize "color context" parameters.
      {
        uint16_t choices_array[3] = { utf8_parameter_no_color_e, utf8_parameter_light_e, utf8_parameter_dark_e };
        choices.array = choices_array;
        choices.used = 3;

        const uint8_t modes[3] = { f_color_mode_color_not_e, f_color_mode_light_e, f_color_mode_dark_e };

        setting->status = fll_program_parameter_process_context(choices, modes, F_true, main);

        if (F_status_is_error(setting->status)) {
          utf8_print_line_first(setting, main->error, F_true);
          fll_error_print(main->error, F_status_set_fine(setting->status), "fll_program_parameter_process_context", F_true);
          utf8_print_line_last(setting, main->error, F_true);

          return;
        }
      }

      if (main->parameters.array[utf8_parameter_line_first_no_e].result == f_console_result_found_e) {
        setting->line_first = f_string_empty_s;
      }
      else {
        setting->line_first = f_string_eol_s;
      }

      if (main->parameters.array[utf8_parameter_line_last_no_e].result == f_console_result_found_e) {
        setting->line_last = f_string_empty_s;
      }
      else {
        setting->line_last = f_string_eol_s;
      }

      // Identify and prioritize "verbosity" parameters.
      {
        uint16_t choices_array[5] = { utf8_parameter_verbosity_quiet_e, utf8_parameter_verbosity_error_e, utf8_parameter_verbosity_verbose_e, utf8_parameter_verbosity_debug_e, utf8_parameter_verbosity_normal_e };
        choices.array = choices_array;
        choices.used = 5;

        const uint8_t verbosity[5] = { f_console_verbosity_quiet_e, f_console_verbosity_error_e, f_console_verbosity_verbose_e, f_console_verbosity_debug_e, f_console_verbosity_normal_e };

        setting->status = fll_program_parameter_process_verbosity(choices, verbosity, F_true, main);

        if (F_status_is_error(setting->status)) {
          utf8_print_line_first(setting, main->error, F_true);
          fll_error_print(main->error, F_status_set_fine(setting->status), "fll_program_parameter_process_verbosity", F_true);
          utf8_print_line_last(setting, main->error, F_true);

          return;
        }
      }

      if (main->parameters.array[utf8_parameter_help_e].result == f_console_result_found_e) {
        setting->flag |= utf8_main_flag_help_e;

        return;
      }

      if (main->parameters.array[utf8_parameter_version_e].result == f_console_result_found_e) {
        setting->flag |= utf8_main_flag_version_e;

        return;
      }

      // Identify and prioritize "from" mode parameters.
      {
        uint16_t choices_array[2] = { utf8_parameter_from_bytesequence_e, utf8_parameter_from_codepoint_e };
        choices.array = choices_array;
        choices.used = 2;

        setting->status = f_console_parameter_prioritize_right(main->parameters, choices, &choice);

        if (F_status_is_error(setting->status)) {
          utf8_print_line_first(setting, main->error, F_true);
          fll_error_print(main->error, F_status_set_fine(setting->status), "f_console_parameter_prioritize_right", F_true);
          utf8_print_line_last(setting, main->error, F_true);

          return;
        }

        if (choices.array[choice] == utf8_parameter_from_bytesequence_e) {
          if (setting->mode & utf8_mode_from_codepoint_e) {
            setting->mode -= utf8_mode_from_codepoint_e;
          }

          setting->mode |= utf8_mode_from_bytesequence_e;
        }
        else if (choices.array[choice] == utf8_parameter_from_codepoint_e) {
          if (setting->mode & utf8_mode_from_bytesequence_e) {
            setting->mode -= utf8_mode_from_bytesequence_e;
          }

          setting->mode |= utf8_mode_from_codepoint_e;
        }
      }

      // Identify and prioritize "to" mode parameters.
      {
        uint16_t choices_array[4] = { utf8_parameter_to_bytesequence_e, utf8_parameter_to_codepoint_e, utf8_parameter_to_combining_e, utf8_parameter_to_width_e };
        choices.array = choices_array;
        choices.used = 4;
        choice = 1;

        setting->status = f_console_parameter_prioritize_right(main->parameters, choices, &choice);

        if (F_status_is_error(setting->status)) {
          utf8_print_line_first(setting, main->error, F_true);
          fll_error_print(main->error, F_status_set_fine(setting->status), "f_console_parameter_prioritize_right", F_true);
          utf8_print_line_last(setting, main->error, F_true);

          return;
        }

        if (choices.array[choice] == utf8_parameter_to_bytesequence_e) {
          if (setting->mode & utf8_mode_to_codepoint_e) {
            setting->mode -= utf8_mode_to_codepoint_e;
          }

          if (setting->mode & utf8_mode_to_combining_e) {
            setting->mode -= utf8_mode_to_combining_e;
          }

          if (setting->mode & utf8_mode_to_width_e) {
            setting->mode -= utf8_mode_to_width_e;
          }

          setting->mode |= utf8_mode_to_bytesequence_e;
        }
        else if (choices.array[choice] == utf8_parameter_to_codepoint_e) {
          if (setting->mode & utf8_mode_to_bytesequence_e) {
            setting->mode -= utf8_mode_to_bytesequence_e;
          }

          if (setting->mode & utf8_mode_to_combining_e) {
            setting->mode -= utf8_mode_to_combining_e;
          }

          if (setting->mode & utf8_mode_to_width_e) {
            setting->mode -= utf8_mode_to_width_e;
          }

          setting->mode |= utf8_mode_to_codepoint_e;
        }
        else if (choices.array[choice] == utf8_parameter_to_combining_e) {
          if (setting->mode & utf8_mode_to_bytesequence_e) {
            setting->mode -= utf8_mode_to_bytesequence_e;
          }

          if (setting->mode & utf8_mode_to_codepoint_e) {
            setting->mode -= utf8_mode_to_codepoint_e;
          }

          // --to_width may be specified with --to_combining.
          if (main->parameters.array[utf8_parameter_to_width_e].result == f_console_result_found_e) {
            setting->mode |= utf8_mode_to_width_e;
          }

          setting->mode |= utf8_mode_to_combining_e;
        }
        else if (choices.array[choice] == utf8_parameter_to_width_e) {
          if (setting->mode & utf8_mode_to_bytesequence_e) {
            setting->mode -= utf8_mode_to_bytesequence_e;
          }

          if (setting->mode & utf8_mode_to_codepoint_e) {
            setting->mode -= utf8_mode_to_codepoint_e;
          }

          // --to_width may be specified with --to_combining.
          if (main->parameters.array[utf8_parameter_to_combining_e].result == f_console_result_found_e) {
            setting->mode |= utf8_mode_to_combining_e;
          }

          setting->mode |= utf8_mode_to_width_e;
        }
      }
    }

    f_string_static_t * const args = main->parameters.arguments.array;

    if (main->parameters.array[utf8_parameter_to_file_e].result == f_console_result_additional_e) {
      if (main->parameters.array[utf8_parameter_to_file_e].values.used > 1) {
        setting->status = F_status_set_error(F_parameter);

        utf8_print_error_parameter_file_to_too_many(main, setting);
        utf8_print_line_last(setting, main->error, F_true);

        return;
      }

      if (args[main->parameters.array[utf8_parameter_to_file_e].values.array[0]].used) {
        setting->path_files_to.used = 0;

        setting->status = f_string_dynamics_increase_by(1, &setting->path_files_to);

        if (F_status_is_error(setting->status)) {
          utf8_print_line_first(setting, main->error, F_true);
          fll_error_print(main->error, F_status_set_fine(setting->status), "f_string_dynamics_increase_by", F_true);
          utf8_print_line_last(setting, main->error, F_true);

          return;
        }

        setting->path_files_to.array[setting->path_files_to.used].used = 0;

        setting->status = f_string_dynamic_append_nulless(main->parameters.arguments.array[main->parameters.array[utf8_parameter_to_file_e].values.array[0]], &setting->path_files_to.array[0]);

        if (F_status_is_error(setting->status)) {
          utf8_print_line_first(setting, main->error, F_true);
          fll_error_print(main->error, F_status_set_fine(setting->status), "f_string_dynamic_append_nulless", F_true);
          utf8_print_line_last(setting, main->error, F_true);

          return;
        }

        ++setting->path_files_to.used;

        setting->status = f_file_stream_open(args[main->parameters.array[utf8_parameter_to_file_e].values.array[0]], f_file_open_mode_append_s, &main->output.to);

        if (F_status_is_error(setting->status)) {
          utf8_print_line_first(setting, main->error, F_true);
          fll_error_file_print(main->error, F_status_set_fine(setting->status), "f_file_stream_open", F_true, args[main->parameters.array[utf8_parameter_to_file_e].values.array[0]], f_file_operation_open_s, fll_error_file_type_file_e);
          utf8_print_line_last(setting, main->error, F_true);

          return;
        }

        setting->flag |= utf8_main_flag_file_to_e;
      }
      else {
        utf8_print_line_first(setting, main->error, F_true);
        utf8_print_error_parameter_file_name_empty(main, setting, main->parameters.array[utf8_parameter_to_file_e].values.array[0]);
        utf8_print_line_last(setting, main->error, F_true);

        setting->status = F_status_set_error(F_parameter);

        return;
      }
    }
    else if (main->parameters.array[utf8_parameter_to_file_e].result == f_console_result_found_e) {
      setting->status = F_status_set_error(F_parameter);

      utf8_print_line_first(setting, main->error, F_true);
      fll_program_print_error_parameter_missing_value(main->error, f_console_symbol_long_enable_s, utf8_long_to_file_s);
      utf8_print_line_last(setting, main->error, F_true);

      return;
    }
    else {
      main->output.to = main->message.to;

      if (setting->flag & utf8_main_flag_file_to_e) {
        setting->flag -= utf8_main_flag_file_to_e;
      }
    }

    if (main->parameters.array[utf8_parameter_from_file_e].result == f_console_result_additional_e) {
      setting->path_files_from.used = 0;

      setting->status = f_string_dynamics_increase_by(main->parameters.array[utf8_parameter_from_file_e].values.used, &setting->path_files_from);

      if (F_status_is_error(setting->status)) {
        utf8_print_line_first(setting, main->error, F_true);
        fll_error_print(main->error, F_status_set_fine(setting->status), "f_string_dynamics_increase_by", F_true);
        utf8_print_line_last(setting, main->error, F_true);

        return;
      }

      setting->path_files_from.used = main->parameters.array[utf8_parameter_from_file_e].values.used;

      f_array_length_t i = 0;
      f_array_length_t index = 0;

      for (; i < setting->path_files_from.used; ++i) {

        index = main->parameters.array[utf8_parameter_from_file_e].values.array[i];
        setting->path_files_from.array[i].used = 0;

        setting->status = f_string_dynamic_append_nulless(main->parameters.arguments.array[index], &setting->path_files_from.array[i]);

        if (F_status_is_error(setting->status)) {
          utf8_print_line_first(setting, main->error, F_true);
          fll_error_print(main->error, F_status_set_fine(setting->status), "f_string_dynamic_append_nulless", F_true);

          break;
        }

        if (args[index].used) {
          if (f_file_exists(args[index], F_true) != F_true) {
            utf8_print_error_parameter_file_not_found(main, setting, F_true, args[index]);

            if (F_status_is_error_not(setting->status)) {
              setting->status = F_status_set_error(F_file_found_not);
            }
          }
        }
        else {
          utf8_print_error_parameter_file_name_empty(main, setting, index);

          if (F_status_is_error_not(setting->status)) {
            setting->status = F_status_set_error(F_parameter);
          }
        }
      } // for

      if (F_status_is_error(setting->status)) {
        utf8_print_line_last(setting, main->error, F_true);

        return;
      }

      setting->flag |= utf8_main_flag_file_from_e;
    }
    else if (main->parameters.array[utf8_parameter_from_file_e].result == f_console_result_found_e) {
      setting->status = F_status_set_error(F_parameter);

      utf8_print_line_first(setting, main->error, F_true);
      fll_program_print_error_parameter_missing_value(main->error, f_console_symbol_long_enable_s, utf8_long_from_file_s);
      utf8_print_line_last(setting, main->error, F_true);

      return;
    }
    else {
      if (setting->flag & utf8_main_flag_file_from_e) {
        setting->flag -= utf8_main_flag_file_from_e;
      }
    }

    if (main->parameters.remaining.used) {
      setting->remaining.used = 0;

      setting->status = f_string_dynamics_resize(main->parameters.remaining.used, &setting->remaining);

      if (F_status_is_error(setting->status)) {
        utf8_print_line_first(setting, main->error, F_true);
        fll_error_print(main->error, F_status_set_fine(setting->status), "f_string_dynamic_append_nulless", F_true);
        utf8_print_line_last(setting, main->error, F_true);

        return;
      }

      // Construct the array without allocating any more memory by setting this as a static string (used > 0, size = 0).
      for (f_array_length_t index = 0; setting->remaining.used < main->parameters.remaining.used; ) {

        index = main->parameters.remaining.array[setting->remaining.used];

        setting->remaining.array[setting->remaining.used].string = main->parameters.arguments.array[index].string;
        setting->remaining.array[setting->remaining.used].used = main->parameters.arguments.array[index].used;
        setting->remaining.array[setting->remaining.used++].size = 0;
      } // for
    }

    if (main->parameters.array[utf8_parameter_from_file_e].result == f_console_result_none_e && !((main->pipe & fll_program_data_pipe_input_e) || main->parameters.remaining.used)) {
      setting->status = F_status_set_error(F_parameter);

      utf8_print_error_no_from(main, setting);
      utf8_print_line_last(setting, main->error, F_true);

      return;
    }

    if (!(setting->mode & utf8_mode_to_bytesequence_e)) {
      if (main->parameters.array[utf8_parameter_separate_e].result == f_console_result_found_e || main->parameters.array[utf8_parameter_headers_e].result == f_console_result_found_e) {
        setting->prepend = utf8_string_prepend_padding_s;
        setting->append = f_string_eol_s;
      }
      else {
        setting->prepend = f_string_space_s;
      }
    }

    if (main->parameters.array[utf8_parameter_headers_e].result == f_console_result_found_e) {
      setting->flag |= utf8_main_flag_header_e;
    }

    if (main->parameters.array[utf8_parameter_separate_e].result == f_console_result_found_e) {
      setting->flag |= utf8_main_flag_separate_e;
    }

    if (main->parameters.array[utf8_parameter_strip_invalid_e].result == f_console_result_found_e) {
      setting->flag |= utf8_main_flag_strip_invalid_e;
    }

    setting->valid_not = main->message.set->error;
  }
#endif // _di_utf8_setting_load_

#ifndef _di_utf8_setting_unload_
  f_status_t utf8_setting_unload(fll_program_data_t * const main, utf8_setting_t * const setting) {

    if (!main || !setting) return F_status_set_error(F_parameter);

    utf8_setting_delete(setting);

    return F_none;
  }
#endif // _di_utf8_setting_unload_

#ifdef __cplusplus
} // extern "C"
#endif
