#include "byte_dump.h"
#include "private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_byte_dump_program_version_d_
  const f_string_static_t byte_dump_program_version_s = macro_f_string_static_t_initialize(BYTE_DUMP_program_version_s, 0, BYTE_DUMP_program_version_s_length);
#endif // _di_byte_dump_program_version_d_

#ifndef _di_byte_dump_program_name_s_
  const f_string_static_t byte_dump_program_name_s = macro_f_string_static_t_initialize(BYTE_DUMP_program_name_s, 0, BYTE_DUMP_program_name_s_length);
  const f_string_static_t byte_dump_program_name_long_s = macro_f_string_static_t_initialize(BYTE_DUMP_program_name_long_s, 0, BYTE_DUMP_program_name_long_s_length);
#endif // _di_byte_dump_program_name_s_

#ifndef _di_byte_dump_print_s_
  const f_string_static_t byte_dump_print_strings_hexidecimal_s = macro_f_string_static_t_initialize(BYTE_DUMP_print_strings_hexidecimal_s, 0, BYTE_DUMP_print_strings_hexidecimal_s_length);
  const f_string_static_t byte_dump_print_strings_duodecimal_s = macro_f_string_static_t_initialize(BYTE_DUMP_print_strings_duodecimal_s, 0, BYTE_DUMP_print_strings_duodecimal_s_length);
  const f_string_static_t byte_dump_print_strings_octal_s = macro_f_string_static_t_initialize(BYTE_DUMP_print_strings_octal_s, 0, BYTE_DUMP_print_strings_octal_s_length);
  const f_string_static_t byte_dump_print_strings_binary_s = macro_f_string_static_t_initialize(BYTE_DUMP_print_strings_binary_s, 0, BYTE_DUMP_print_strings_binary_s_length);
  const f_string_static_t byte_dump_print_strings_decimal_s = macro_f_string_static_t_initialize(BYTE_DUMP_print_strings_decimal_s, 0, BYTE_DUMP_print_strings_decimal_s_length);
#endif // _di_byte_dump_print_s_

#ifndef _di_byte_dump_s_
  const f_string_static_t byte_dump_character_wall_s = macro_f_string_static_t_initialize(BYTE_DUMP_character_wall_s, 0, BYTE_DUMP_character_wall_s_length);
  const f_string_static_t byte_dump_character_placeholder_s = macro_f_string_static_t_initialize(BYTE_DUMP_character_placeholder_s, 0, BYTE_DUMP_character_placeholder_s_length);
  const f_string_static_t byte_dump_character_incomplete_s = macro_f_string_static_t_initialize(BYTE_DUMP_character_incomplete_s, 0, BYTE_DUMP_character_incomplete_s_length);
  const f_string_static_t byte_dump_character_unused_s = macro_f_string_static_t_initialize(BYTE_DUMP_character_unused_s, 0, BYTE_DUMP_character_unused_s_length);
#endif // _di_byte_dump_s_

#ifndef _di_byte_dump_parameter_d_
  const f_string_static_t byte_dump_short_binary_s = macro_f_string_static_t_initialize(BYTE_DUMP_short_binary_s, 0, BYTE_DUMP_short_binary_s_length);
  const f_string_static_t byte_dump_short_decimal_s = macro_f_string_static_t_initialize(BYTE_DUMP_short_decimal_s, 0, BYTE_DUMP_short_decimal_s_length);
  const f_string_static_t byte_dump_short_duodecimal_s = macro_f_string_static_t_initialize(BYTE_DUMP_short_duodecimal_s, 0, BYTE_DUMP_short_duodecimal_s_length);
  const f_string_static_t byte_dump_short_hexidecimal_s = macro_f_string_static_t_initialize(BYTE_DUMP_short_hexidecimal_s, 0, BYTE_DUMP_short_hexidecimal_s_length);
  const f_string_static_t byte_dump_short_octal_s = macro_f_string_static_t_initialize(BYTE_DUMP_short_octal_s, 0, BYTE_DUMP_short_octal_s_length);
  const f_string_static_t byte_dump_short_unicode_s = macro_f_string_static_t_initialize(BYTE_DUMP_short_unicode_s, 0, BYTE_DUMP_short_unicode_s_length);

  const f_string_static_t byte_dump_short_first_s = macro_f_string_static_t_initialize(BYTE_DUMP_short_first_s, 0, BYTE_DUMP_short_first_s_length);
  const f_string_static_t byte_dump_short_last_s = macro_f_string_static_t_initialize(BYTE_DUMP_short_last_s, 0, BYTE_DUMP_short_last_s_length);

  const f_string_static_t byte_dump_short_narrow_s = macro_f_string_static_t_initialize(BYTE_DUMP_short_narrow_s, 0, BYTE_DUMP_short_narrow_s_length);
  const f_string_static_t byte_dump_short_placeholder_s = macro_f_string_static_t_initialize(BYTE_DUMP_short_placeholder_s, 0, BYTE_DUMP_short_placeholder_s_length);
  const f_string_static_t byte_dump_short_text_s = macro_f_string_static_t_initialize(BYTE_DUMP_short_text_s, 0, BYTE_DUMP_short_text_s_length);
  const f_string_static_t byte_dump_short_wide_s = macro_f_string_static_t_initialize(BYTE_DUMP_short_wide_s, 0, BYTE_DUMP_short_wide_s_length);
  const f_string_static_t byte_dump_short_width_s = macro_f_string_static_t_initialize(BYTE_DUMP_short_width_s, 0, BYTE_DUMP_short_width_s_length);

  const f_string_static_t byte_dump_long_binary_s = macro_f_string_static_t_initialize(BYTE_DUMP_long_binary_s, 0, BYTE_DUMP_long_binary_s_length);
  const f_string_static_t byte_dump_long_decimal_s = macro_f_string_static_t_initialize(BYTE_DUMP_long_decimal_s, 0, BYTE_DUMP_long_decimal_s_length);
  const f_string_static_t byte_dump_long_duodecimal_s = macro_f_string_static_t_initialize(BYTE_DUMP_long_duodecimal_s, 0, BYTE_DUMP_long_duodecimal_s_length);
  const f_string_static_t byte_dump_long_hexidecimal_s = macro_f_string_static_t_initialize(BYTE_DUMP_long_hexidecimal_s, 0, BYTE_DUMP_long_hexidecimal_s_length);
  const f_string_static_t byte_dump_long_octal_s = macro_f_string_static_t_initialize(BYTE_DUMP_long_octal_s, 0, BYTE_DUMP_long_octal_s_length);
  const f_string_static_t byte_dump_long_unicode_s = macro_f_string_static_t_initialize(BYTE_DUMP_long_unicode_s, 0, BYTE_DUMP_long_unicode_s_length);

  const f_string_static_t byte_dump_long_first_s = macro_f_string_static_t_initialize(BYTE_DUMP_long_first_s, 0, BYTE_DUMP_long_first_s_length);
  const f_string_static_t byte_dump_long_last_s = macro_f_string_static_t_initialize(BYTE_DUMP_long_last_s, 0, BYTE_DUMP_long_last_s_length);

  const f_string_static_t byte_dump_long_narrow_s = macro_f_string_static_t_initialize(BYTE_DUMP_long_narrow_s, 0, BYTE_DUMP_long_narrow_s_length);
  const f_string_static_t byte_dump_long_placeholder_s = macro_f_string_static_t_initialize(BYTE_DUMP_long_placeholder_s, 0, BYTE_DUMP_long_placeholder_s_length);
  const f_string_static_t byte_dump_long_text_s = macro_f_string_static_t_initialize(BYTE_DUMP_long_text_s, 0, BYTE_DUMP_long_text_s_length);
  const f_string_static_t byte_dump_long_wide_s = macro_f_string_static_t_initialize(BYTE_DUMP_long_wide_s, 0, BYTE_DUMP_long_wide_s_length);
  const f_string_static_t byte_dump_long_width_s = macro_f_string_static_t_initialize(BYTE_DUMP_long_width_s, 0, BYTE_DUMP_long_width_s_length);

  const f_string_static_t byte_dump_long_normal_s = macro_f_string_static_t_initialize(BYTE_DUMP_long_normal_s, 0, BYTE_DUMP_long_normal_s_length);
  const f_string_static_t byte_dump_long_simple_s = macro_f_string_static_t_initialize(BYTE_DUMP_long_simple_s, 0, BYTE_DUMP_long_simple_s_length);
  const f_string_static_t byte_dump_long_classic_s = macro_f_string_static_t_initialize(BYTE_DUMP_long_classic_s, 0, BYTE_DUMP_long_classic_s_length);
#endif // _di_byte_dump_parameter_d_

#ifndef _di_byte_dump_setting_delete_
  f_status_t byte_dump_setting_delete(byte_dump_setting_t * const setting) {

    if (!setting) return F_status_set_error(F_parameter);

    return F_none;
  }
#endif // _di_byte_dump_setting_delete_

#ifndef _di_byte_dump_setting_load_
  void byte_dump_setting_load(const f_console_arguments_t arguments, fll_program_data_t * const main, byte_dump_setting_t * const setting) {

    if (!main || !setting) return;

    setting->state.step_small = byte_dump_allocation_console_d;

    f_console_parameter_process(arguments, &main->parameters, &setting->state, 0);

    setting->state.step_small = byte_dump_allocation_small_d;

    if (F_status_is_error(setting->state.status)) {
      byte_dump_print_line_first_locked(setting, main->error);
      fll_error_print(main->error, F_status_set_fine(setting->state.status), "f_console_parameter_process", fll_error_file_flag_fallback_e);
      byte_dump_print_line_last_locked(setting, main->error);

      return;
    }

    {
      f_array_length_t choice = 0;
      f_uint16s_t choices = f_uint16s_t_initialize;

      // Identify and prioritize "color context" parameters.
      {
        uint16_t choices_array[3] = { byte_dump_parameter_no_color_e, byte_dump_parameter_light_e, byte_dump_parameter_dark_e };
        choices.array = choices_array;
        choices.used = 3;

        const uint8_t modes[3] = { f_color_mode_not_e, f_color_mode_light_e, f_color_mode_dark_e };

        setting->state.status = fll_program_parameter_process_context(choices, modes, F_true, main);

        if (F_status_is_error(setting->state.status)) {
          byte_dump_print_line_first_locked(setting, main->error);
          fll_error_print(main->error, F_status_set_fine(setting->state.status), "fll_program_parameter_process_context", fll_error_file_flag_fallback_e);
          byte_dump_print_line_last_locked(setting, main->error);

          return;
        }
      }

      if (main->parameters.array[byte_dump_parameter_line_first_no_e].result & f_console_result_found_e) {
        setting->line_first = f_string_empty_s;
      }
      else {
        setting->line_first = f_string_eol_s;
      }

      if (main->parameters.array[byte_dump_parameter_line_last_no_e].result & f_console_result_found_e) {
        setting->line_last = f_string_empty_s;
      }
      else {
        setting->line_last = f_string_eol_s;
      }

      // Identify and prioritize "verbosity" parameters.
      {
        uint16_t choices_array[5] = { byte_dump_parameter_verbosity_quiet_e, byte_dump_parameter_verbosity_error_e, byte_dump_parameter_verbosity_verbose_e, byte_dump_parameter_verbosity_debug_e, byte_dump_parameter_verbosity_normal_e };
        choices.array = choices_array;
        choices.used = 5;

        const uint8_t verbosity[5] = { f_console_verbosity_quiet_e, f_console_verbosity_error_e, f_console_verbosity_verbose_e, f_console_verbosity_debug_e, f_console_verbosity_normal_e };

        setting->state.status = fll_program_parameter_process_verbosity(choices, verbosity, F_true, main);

        if (F_status_is_error(setting->state.status)) {
          byte_dump_print_line_first_locked(setting, main->error);
          fll_error_print(main->error, F_status_set_fine(setting->state.status), "fll_program_parameter_process_verbosity", fll_error_file_flag_fallback_e);
          byte_dump_print_line_last_locked(setting, main->error);

          return;
        }
      }
    }

    main->output.to.id = F_type_descriptor_output_d;
    main->output.to.stream = F_type_output_d;
    main->output.to.flag = F_file_flag_create_d | F_file_flag_write_only_d | F_file_flag_append_d;

    if (main->parameters.array[byte_dump_parameter_help_e].result & f_console_result_found_e) {
      setting->flag |= byte_dump_main_flag_help_e;

      return;
    }

    if (main->parameters.array[byte_dump_parameter_version_e].result & f_console_result_found_e) {
      setting->flag |= byte_dump_main_flag_version_e;

      return;
    }

    f_string_static_t * const args = main->parameters.arguments.array;

    if (main->parameters.array[byte_dump_parameter_strip_invalid_e].result & f_console_result_found_e) {
      setting->flag |= byte_dump_main_flag_strip_invalid_e;
    }
  }
#endif // _di_byte_dump_setting_load_

#ifndef _di_byte_dump_setting_unload_
  f_status_t byte_dump_setting_unload(fll_program_data_t * const main, byte_dump_setting_t * const setting) {

    if (!main || !setting) return F_status_set_error(F_parameter);

    byte_dump_setting_delete(setting);

    return F_none;
  }
#endif // _di_byte_dump_setting_unload_

#ifdef __cplusplus
} // extern "C"
#endif
