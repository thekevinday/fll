#include "iki_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_read_program_version_
  const f_string_static_t iki_read_program_version_s = macro_f_string_static_t_initialize(IKI_READ_program_version_s, 0, IKI_READ_program_version_s_length);
#endif // _di_iki_read_program_version_

#ifndef _di_iki_read_program_name_
  const f_string_static_t iki_read_program_name_s = macro_f_string_static_t_initialize(IKI_READ_program_name_s, 0, IKI_READ_program_name_s_length);
  const f_string_static_t iki_read_program_name_long_s = macro_f_string_static_t_initialize(IKI_READ_program_name_long_s, 0, IKI_READ_program_name_long_s_length);
#endif // _di_iki_read_program_name_

#ifndef _di_iki_read_strings_
  const f_string_static_t iki_read_string_two_s = macro_f_string_static_t_initialize(IKI_READ_string_two_s, 0, IKI_READ_string_two_s_length);
  const f_string_static_t iki_read_string_three_s = macro_f_string_static_t_initialize(IKI_READ_string_three_s, 0, IKI_READ_string_three_s_length);
#endif // _di_iki_read_strings_

#ifndef _di_iki_read_parameters_
  const f_string_static_t iki_read_short_at_s = macro_f_string_static_t_initialize(IKI_READ_short_at_s, 0, IKI_READ_short_at_s_length);
  const f_string_static_t iki_read_short_content_s = macro_f_string_static_t_initialize(IKI_READ_short_content_s, 0, IKI_READ_short_content_s_length);
  const f_string_static_t iki_read_short_line_s = macro_f_string_static_t_initialize(IKI_READ_short_line_s, 0, IKI_READ_short_line_s_length);
  const f_string_static_t iki_read_short_literal_s = macro_f_string_static_t_initialize(IKI_READ_short_literal_s, 0, IKI_READ_short_literal_s_length);
  const f_string_static_t iki_read_short_name_s = macro_f_string_static_t_initialize(IKI_READ_short_name_s, 0, IKI_READ_short_name_s_length);
  const f_string_static_t iki_read_short_object_s = macro_f_string_static_t_initialize(IKI_READ_short_object_s, 0, IKI_READ_short_object_s_length);
  const f_string_static_t iki_read_short_replace_s = macro_f_string_static_t_initialize(IKI_READ_short_replace_s, 0, IKI_READ_short_replace_s_length);
  const f_string_static_t iki_read_short_substitute_s = macro_f_string_static_t_initialize(IKI_READ_short_substitute_s, 0, IKI_READ_short_substitute_s_length);
  const f_string_static_t iki_read_short_total_s = macro_f_string_static_t_initialize(IKI_READ_short_total_s, 0, IKI_READ_short_total_s_length);
  const f_string_static_t iki_read_short_whole_s = macro_f_string_static_t_initialize(IKI_READ_short_whole_s, 0, IKI_READ_short_whole_s_length);
  const f_string_static_t iki_read_short_wrap_s = macro_f_string_static_t_initialize(IKI_READ_short_wrap_s, 0, IKI_READ_short_wrap_s_length);

  const f_string_static_t iki_read_long_at_s = macro_f_string_static_t_initialize(IKI_READ_long_at_s, 0, IKI_READ_long_at_s_length);
  const f_string_static_t iki_read_long_content_s = macro_f_string_static_t_initialize(IKI_READ_long_content_s, 0, IKI_READ_long_content_s_length);
  const f_string_static_t iki_read_long_line_s = macro_f_string_static_t_initialize(IKI_READ_long_line_s, 0, IKI_READ_long_line_s_length);
  const f_string_static_t iki_read_long_literal_s = macro_f_string_static_t_initialize(IKI_READ_long_literal_s, 0, IKI_READ_long_literal_s_length);
  const f_string_static_t iki_read_long_name_s = macro_f_string_static_t_initialize(IKI_READ_long_name_s, 0, IKI_READ_long_name_s_length);
  const f_string_static_t iki_read_long_object_s = macro_f_string_static_t_initialize(IKI_READ_long_object_s, 0, IKI_READ_long_object_s_length);
  const f_string_static_t iki_read_long_replace_s = macro_f_string_static_t_initialize(IKI_READ_long_replace_s, 0, IKI_READ_long_replace_s_length);
  const f_string_static_t iki_read_long_substitute_s = macro_f_string_static_t_initialize(IKI_READ_long_substitute_s, 0, IKI_READ_long_substitute_s_length);
  const f_string_static_t iki_read_long_total_s = macro_f_string_static_t_initialize(IKI_READ_long_total_s, 0, IKI_READ_long_total_s_length);
  const f_string_static_t iki_read_long_whole_s = macro_f_string_static_t_initialize(IKI_READ_long_whole_s, 0, IKI_READ_long_whole_s_length);
  const f_string_static_t iki_read_long_wrap_s = macro_f_string_static_t_initialize(IKI_READ_long_wrap_s, 0, IKI_READ_long_wrap_s_length);
#endif // _di_iki_read_parameters_

#ifndef _di_iki_read_substitution_t_
  const f_string_static_t iki_read_substitution_after_s = macro_f_string_static_t_initialize(IKI_READ_substitution_after_s, 0, IKI_READ_substitution_after_s_length);
  const f_string_static_t iki_read_substitution_before_s = macro_f_string_static_t_initialize(IKI_READ_substitution_before_s, 0, IKI_READ_substitution_before_s_length);
  const f_string_static_t iki_read_substitution_replace_s = macro_f_string_static_t_initialize(IKI_READ_substitution_replace_s, 0, IKI_READ_substitution_replace_s_length);
  const f_string_static_t iki_read_substitution_vocabulary_s = macro_f_string_static_t_initialize(IKI_READ_substitution_vocabulary_s, 0, IKI_READ_substitution_vocabulary_s_length);
  const f_string_static_t iki_read_substitution_with_s = macro_f_string_static_t_initialize(IKI_READ_substitution_with_s, 0, IKI_READ_substitution_with_s_length);
#endif // _di_iki_read_substitution_t_

#ifndef _di_iki_read_setting_delete_
  f_status_t iki_read_setting_delete(iki_read_setting_t * const setting) {

    if (!setting) return F_status_set_error(F_parameter);

    f_string_dynamic_resize(0, &setting->buffer);
    f_string_dynamics_resize(0, &setting->names);
    f_string_dynamics_resize(0, &setting->files);

    f_string_maps_resize(0, &setting->replace);
    f_string_triples_resize(0, &setting->substitute);
    f_string_triples_resize(0, &setting->wrap);

    f_iki_data_delete(&setting->data);

    return F_none;
  }
#endif // _di_iki_read_setting_delete_

#ifndef _di_iki_read_setting_load_
  void iki_read_setting_load(const f_console_arguments_t arguments, fll_program_data_t * const main, iki_read_setting_t * const setting) {

    if (!main || !setting) return;

    // Load parameters.
    setting->status = f_console_parameter_process(arguments, &main->parameters);
    if (F_status_is_error(setting->status)) return;

    {
      f_array_length_t choice = 0;
      f_uint16s_t choices = f_uint16s_t_initialize;

      // Identify and prioritize "color context" parameters.
      {
        uint16_t choices_array[3] = { iki_read_parameter_no_color_e, iki_read_parameter_light_e, iki_read_parameter_dark_e };
        choices.array = choices_array;
        choices.used = 3;

        const uint8_t modes[3] = { f_color_mode_color_not_e, f_color_mode_light_e, f_color_mode_dark_e };

        setting->status = fll_program_parameter_process_context(choices, modes, F_true, main);

        if (F_status_is_error(setting->status)) {
          iki_read_print_line_first_locked(setting, main->error);
          fll_error_print(main->error, F_status_set_fine(setting->status), "fll_program_parameter_process_context", F_true);
          iki_read_print_line_last_locked(setting, main->error);

          return;
        }
      }

      if (main->parameters.array[iki_read_parameter_line_first_no_e].result == f_console_result_found_e) {
        setting->line_first = f_string_empty_s;
      }
      else {
        setting->line_first = f_string_eol_s;
      }

      if (main->parameters.array[iki_read_parameter_line_last_no_e].result == f_console_result_found_e) {
        setting->line_last = f_string_empty_s;
      }
      else {
        setting->line_last = f_string_eol_s;
      }

      // Identify and prioritize "verbosity" parameters.
      {
        uint16_t choices_array[5] = { iki_read_parameter_verbosity_quiet_e, iki_read_parameter_verbosity_error_e, iki_read_parameter_verbosity_verbose_e, iki_read_parameter_verbosity_debug_e, iki_read_parameter_verbosity_normal_e };
        choices.array = choices_array;
        choices.used = 5;

        const uint8_t verbosity[5] = { f_console_verbosity_quiet_e, f_console_verbosity_error_e, f_console_verbosity_verbose_e, f_console_verbosity_debug_e, f_console_verbosity_normal_e };

        setting->status = fll_program_parameter_process_verbosity(choices, verbosity, F_true, main);

        if (F_status_is_error(setting->status)) {
          iki_read_print_line_first_locked(setting, main->error);
          fll_error_print(main->error, F_status_set_fine(setting->status), "fll_program_parameter_process_verbosity", F_true);
          iki_read_print_line_last_locked(setting, main->error);

          return;
        }
      }

      if (main->parameters.array[iki_read_parameter_help_e].result == f_console_result_found_e) {
        setting->flag |= iki_read_main_flag_help_e;

        return;
      }

      if (main->parameters.array[iki_read_parameter_version_e].result == f_console_result_found_e) {
        setting->flag |= iki_read_main_flag_version_e;

        return;
      }
    }

    if (!(main->parameters.remaining.used || (main->pipe & fll_program_data_pipe_input_e))) {
      setting->status = F_status_set_error(F_parameter);

      iki_read_print_line_first_locked(setting, main->error);
      fll_program_print_error_missing_file(main->error);
      iki_read_print_line_last_locked(setting, main->error);

      return;
    }

    if (main->parameters.array[iki_read_parameter_at_e].result == f_console_result_additional_e) {
      if (main->parameters.array[iki_read_parameter_whole_e].result == f_console_result_found_e) {
        setting->status = F_status_set_error(F_parameter);

        iki_read_print_line_first_locked(setting, main->error);
        fll_program_print_error_parameter_cannot_use_with(main->error, f_console_symbol_long_enable_s, f_console_symbol_long_enable_s, iki_read_long_at_s, iki_read_long_whole_s);
        iki_read_print_line_last_locked(setting, main->error);

        return;
      }

      const f_array_length_t index = main->parameters.array[iki_read_parameter_at_e].values.array[main->parameters.array[iki_read_parameter_at_e].values.used - 1];

      setting->at = 0;

      setting->status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, main->parameters.arguments.array[index], &setting->at);

      if (F_status_is_error(setting->status)) {
        setting->status = F_status_set_error(F_parameter);

        iki_read_print_line_first_locked(setting, main->error);
        fll_program_print_error_parameter_integer_not(main->error, f_console_symbol_long_enable_s, iki_read_long_at_s, main->parameters.arguments.array[index]);
        iki_read_print_line_last_locked(setting, main->error);

        return;
      }

      setting->flag |= iki_read_main_flag_at_e;
    }
    else if (main->parameters.array[iki_read_parameter_at_e].result == f_console_result_found_e) {
      setting->status = F_status_set_error(F_parameter);

      iki_read_print_line_first_locked(setting, main->error);
      fll_program_print_error_parameter_missing_value(main->error, f_console_symbol_long_enable_s, iki_read_long_at_s);
      iki_read_print_line_last_locked(setting, main->error);

      return;
    }

    if (main->parameters.array[iki_read_parameter_line_e].result == f_console_result_additional_e) {
      const f_array_length_t index = main->parameters.array[iki_read_parameter_line_e].values.array[main->parameters.array[iki_read_parameter_line_e].values.used - 1];

      setting->line = 0;

      setting->status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, main->parameters.arguments.array[index], &setting->line);

      if (F_status_is_error(setting->status)) {
        setting->status = F_status_set_error(F_parameter);

        iki_read_print_line_first_locked(setting, main->error);
        fll_program_print_error_parameter_integer_not(main->error, f_console_symbol_long_enable_s, iki_read_long_line_s, main->parameters.arguments.array[index]);
        iki_read_print_line_last_locked(setting, main->error);

        return;
      }

      setting->flag |= iki_read_main_flag_line_e;
    }
    else if (main->parameters.array[iki_read_parameter_line_e].result == f_console_result_found_e) {
      setting->status = F_status_set_error(F_parameter);

      iki_read_print_line_first_locked(setting, main->error);
      fll_program_print_error_parameter_missing_value(main->error, f_console_symbol_long_enable_s, iki_read_long_line_s);
      iki_read_print_line_last_locked(setting, main->error);

      return;
    }

    if (main->parameters.array[iki_read_parameter_name_e].result == f_console_result_additional_e) {
      setting->names.used = 0;

      setting->status = f_string_dynamics_increase_by(main->parameters.array[iki_read_parameter_name_e].values.used, &setting->names);

      if (F_status_is_error(setting->status)) {
        iki_read_print_line_first_locked(setting, main->error);
        fll_error_print(main->error, F_status_set_fine(setting->status), "f_string_dynamics_increase_by", F_true);
        iki_read_print_line_last_locked(setting, main->error);

        return;
      }

      // Distinctly append all names.
      f_array_length_t i = 0;
      f_array_length_t j = 0;
      f_array_lengths_t *values = &main->parameters.array[iki_read_parameter_name_e].values;

      for (; i < values->used; ++i) {

        for (j = 0; j < setting->names.used; ++j) {
          if (fl_string_dynamic_compare(main->parameters.arguments.array[values->array[i]], setting->names.array[j]) == F_equal_to) break;
        } // for

        if (j < setting->names.used) continue;

        setting->names.array[setting->names.used].used = 0;

        if (main->parameters.arguments.array[values->array[i]].used) {
          setting->status = f_string_dynamics_append(main->parameters.arguments.array[values->array[i]], &setting->names);
          if (F_status_is_error(setting->status)) break;
        }
        else {
          setting->status = f_string_dynamics_append(f_string_empty_s, &setting->names);
          if (F_status_is_error(setting->status)) break;
        }
      } // for

      if (F_status_is_error(setting->status)) {
        iki_read_print_line_first_locked(setting, main->error);
        fll_error_print(main->error, F_status_set_fine(setting->status), "f_string_dynamics_append", F_true);
        iki_read_print_line_last_locked(setting, main->error);

        return;
      }

      setting->flag |= iki_read_main_flag_name_e;
    }
    else if (main->parameters.array[iki_read_parameter_name_e].result == f_console_result_found_e) {
      setting->status = F_status_set_error(F_parameter);

      iki_read_print_line_first_locked(setting, main->error);
      fll_program_print_error_parameter_missing_value(main->error, f_console_symbol_short_enable_s, iki_read_long_name_s);
      iki_read_print_line_last_locked(setting, main->error);

      return;
    }

    if (main->parameters.array[iki_read_parameter_replace_e].result != f_console_result_none_e) {
      if (main->parameters.array[iki_read_parameter_replace_e].result == f_console_result_found_e || main->parameters.array[iki_read_parameter_replace_e].values.used % 2 != 0) {
        setting->status = F_status_set_error(F_parameter);

        iki_read_print_line_first_locked(setting, main->error);
        fll_program_print_error_parameter_missing_value_requires_amount(main->error, f_console_symbol_short_enable_s, iki_read_long_replace_s, iki_read_string_two_s);
        iki_read_print_line_last_locked(setting, main->error);

        return;
      }

      setting->replace.used = 0;

      setting->status = f_string_maps_increase_by(main->parameters.array[iki_read_parameter_replace_e].values.used / 2, &setting->replace);

      if (F_status_is_error(setting->status)) {
        iki_read_print_line_first_locked(setting, main->error);
        fll_error_print(main->error, F_status_set_fine(setting->status), "f_string_maps_increase_by", F_true);
        iki_read_print_line_last_locked(setting, main->error);

        return;
      }

      f_array_length_t at = 0;
      f_array_length_t index = 0;
      f_array_length_t i = 0;
      f_array_length_t j = 0;

      for (; i < main->parameters.array[iki_read_parameter_replace_e].values.used; ++i) {

        index = main->parameters.array[iki_read_parameter_replace_e].values.array[i];

        // Replace any existing value so that each name exists only once.
        for (j = 0; j < setting->replace.used; ++j) {

          if (fl_string_dynamic_compare(main->parameters.arguments.array[index], setting->replace.array[j].name) == F_equal_to) {
            break;
          }
        } // for

        at = j;

        // Static strings are being used, so if a dynamic string exists (size > 0), then de-allocate it.
        if (setting->replace.array[at].name.size) {
          setting->status = f_string_dynamic_resize(0, &setting->replace.array[at].name);
        }

        if (F_status_is_error_not(setting->status) && setting->replace.array[at].value.size) {
          setting->status = f_string_dynamic_resize(0, &setting->replace.array[at].value);
        }

        if (F_status_is_error(setting->status)) {
          iki_read_print_line_first_locked(setting, main->error);
          fll_error_print(main->error, F_status_set_fine(setting->status), "f_string_dynamic_resize", F_true);
          iki_read_print_line_last_locked(setting, main->error);

          return;
        }

        setting->replace.array[at].name.string = main->parameters.arguments.array[index].string;
        setting->replace.array[at].name.used = main->parameters.arguments.array[index].used;
        setting->replace.array[at].name.size = 0;

        index = main->parameters.array[iki_read_parameter_replace_e].values.array[++i];

        setting->replace.array[at].value.string = main->parameters.arguments.array[index].string;
        setting->replace.array[at].value.used = main->parameters.arguments.array[index].used;
        setting->replace.array[at].value.size = 0;

        if (at == setting->replace.used) {
          ++setting->replace.used;
        }
      } // for

      setting->flag |= iki_read_main_flag_replace_e;
    }

    if (main->parameters.array[iki_read_parameter_substitute_e].result != f_console_result_none_e) {
      if (main->parameters.array[iki_read_parameter_substitute_e].result == f_console_result_found_e || main->parameters.array[iki_read_parameter_substitute_e].values.used % 3 != 0) {
        setting->status = F_status_set_error(F_parameter);

        iki_read_print_line_first_locked(setting, main->error);
        fll_program_print_error_parameter_missing_value_requires_amount(main->error, f_console_symbol_short_enable_s, iki_read_long_substitute_s, iki_read_string_three_s);
        iki_read_print_line_last_locked(setting, main->error);

        return;
      }

      setting->substitute.used = 0;

      setting->status = f_string_triples_increase_by(main->parameters.array[iki_read_parameter_substitute_e].values.used / 3, &setting->substitute);

      if (F_status_is_error(setting->status)) {
        iki_read_print_line_first_locked(setting, main->error);
        fll_error_print(main->error, F_status_set_fine(setting->status), "f_string_triples_increase_by", F_true);
        iki_read_print_line_last_locked(setting, main->error);

        return;
      }

      f_array_length_t at = 0;
      f_array_length_t index = 0;
      f_array_length_t i = 0;
      f_array_length_t j = 0;

      for (; i < main->parameters.array[iki_read_parameter_substitute_e].values.used; ++i) {

        index = main->parameters.array[iki_read_parameter_substitute_e].values.array[i];

        // Replace any existing values so that each name and value pair exists only once.
        for (j = 0; j < setting->substitute.used; ++j) {

          if (fl_string_dynamic_compare(main->parameters.arguments.array[index], setting->substitute.array[j].a) == F_equal_to) {
            if (fl_string_dynamic_compare(main->parameters.arguments.array[main->parameters.array[iki_read_parameter_substitute_e].values.array[i + 1]], setting->substitute.array[j].b) == F_equal_to) {
              break;
            }
          }
        } // for

        at = j;

        // Static strings are being used, so if a dynamic string exists (size > 0), then de-allocate it.
        if (setting->substitute.array[at].a.size) {
          setting->status = f_string_dynamic_resize(0, &setting->substitute.array[at].a);
        }

        if (F_status_is_error_not(setting->status) && setting->substitute.array[at].b.size) {
          setting->status = f_string_dynamic_resize(0, &setting->substitute.array[at].b);
        }

        if (F_status_is_error_not(setting->status) && setting->substitute.array[at].c.size) {
          setting->status = f_string_dynamic_resize(0, &setting->substitute.array[at].c);
        }

        if (F_status_is_error(setting->status)) {
          iki_read_print_line_first_locked(setting, main->error);
          fll_error_print(main->error, F_status_set_fine(setting->status), "f_string_dynamic_resize", F_true);
          iki_read_print_line_last_locked(setting, main->error);

          return;
        }

        setting->substitute.array[at].a.string = main->parameters.arguments.array[index].string;
        setting->substitute.array[at].a.used = main->parameters.arguments.array[index].used;
        setting->substitute.array[at].a.size = 0;

        index = main->parameters.array[iki_read_parameter_substitute_e].values.array[++i];

        setting->substitute.array[at].b.string = main->parameters.arguments.array[index].string;
        setting->substitute.array[at].b.used = main->parameters.arguments.array[index].used;
        setting->substitute.array[at].b.size = 0;

        index = main->parameters.array[iki_read_parameter_substitute_e].values.array[++i];

        setting->substitute.array[at].c.string = main->parameters.arguments.array[index].string;
        setting->substitute.array[at].c.used = main->parameters.arguments.array[index].used;
        setting->substitute.array[at].c.size = 0;

        if (at == setting->substitute.used) {
          ++setting->substitute.used;
        }
      } // for

      setting->flag |= iki_read_main_flag_substitute_e;
    }

    if (main->parameters.array[iki_read_parameter_wrap_e].result != f_console_result_none_e) {
      if (main->parameters.array[iki_read_parameter_wrap_e].result == f_console_result_found_e || main->parameters.array[iki_read_parameter_wrap_e].values.used % 3 != 0) {
        setting->status = F_status_set_error(F_parameter);

        iki_read_print_line_first_locked(setting, main->error);
        fll_program_print_error_parameter_missing_value_requires_amount(main->error, f_console_symbol_short_enable_s, iki_read_long_wrap_s, iki_read_string_three_s);
        iki_read_print_line_last_locked(setting, main->error);

        return;
      }

      setting->wrap.used = 0;

      setting->status = f_string_triples_increase_by(main->parameters.array[iki_read_parameter_wrap_e].values.used / 3, &setting->wrap);

      if (F_status_is_error(setting->status)) {
        iki_read_print_line_first_locked(setting, main->error);
        fll_error_print(main->error, F_status_set_fine(setting->status), "f_string_triples_increase_by", F_true);
        iki_read_print_line_last_locked(setting, main->error);

        return;
      }

      f_array_length_t at = 0;
      f_array_length_t index = 0;
      f_array_length_t i = 0;
      f_array_length_t j = 0;

      for (; i < main->parameters.array[iki_read_parameter_wrap_e].values.used; ++i) {

        index = main->parameters.array[iki_read_parameter_wrap_e].values.array[i];

        // Replace any existing values so that each name exists only once.
        for (j = 0; j < setting->wrap.used; ++j) {

          if (fl_string_dynamic_compare(main->parameters.arguments.array[index], setting->wrap.array[j].a) == F_equal_to) {
            break;
          }
        } // for

        at = j;

        // Static strings are being used, so if a dynamic string exists (size > 0), then de-allocate it.
        if (setting->wrap.array[at].a.size) {
          setting->status = f_string_dynamic_resize(0, &setting->wrap.array[at].a);
        }

        if (F_status_is_error_not(setting->status) && setting->wrap.array[at].b.size) {
          setting->status = f_string_dynamic_resize(0, &setting->wrap.array[at].b);
        }

        if (F_status_is_error_not(setting->status) && setting->wrap.array[at].c.size) {
          setting->status = f_string_dynamic_resize(0, &setting->wrap.array[at].c);
        }

        if (F_status_is_error(setting->status)) {
          iki_read_print_line_first_locked(setting, main->error);
          fll_error_print(main->error, F_status_set_fine(setting->status), "f_string_dynamic_resize", F_true);
          iki_read_print_line_last_locked(setting, main->error);

          return;
        }

        setting->wrap.array[at].a.string = main->parameters.arguments.array[index].string;
        setting->wrap.array[at].a.used = main->parameters.arguments.array[index].used;
        setting->wrap.array[at].a.size = 0;

        index = main->parameters.array[iki_read_parameter_wrap_e].values.array[++i];

        setting->wrap.array[at].b.string = main->parameters.arguments.array[index].string;
        setting->wrap.array[at].b.used = main->parameters.arguments.array[index].used;
        setting->wrap.array[at].b.size = 0;

        index = main->parameters.array[iki_read_parameter_wrap_e].values.array[++i];

        setting->wrap.array[at].c.string = main->parameters.arguments.array[index].string;
        setting->wrap.array[at].c.used = main->parameters.arguments.array[index].used;
        setting->wrap.array[at].c.size = 0;

        if (at == setting->wrap.used) {
          ++setting->wrap.used;
        }
      } // for

      setting->flag |= iki_read_main_flag_wrap_e;
    }

    if (main->parameters.array[iki_read_parameter_literal_e].result == f_console_result_found_e) {
      const uint8_t ids[3] = {
        iki_read_parameter_object_e,
        iki_read_parameter_content_e,
        iki_read_parameter_total_e,
      };

      const f_string_static_t names[3] = {
        iki_read_long_object_s,
        iki_read_long_content_s,
        iki_read_long_total_s,
      };

      for (uint8_t i = 0; i < 3; ++i) {

        if (main->parameters.array[ids[i]].result == f_console_result_found_e) {
          setting->status = F_status_set_error(F_parameter);

          iki_read_print_line_first_locked(setting, main->error);
          fll_program_print_error_parameter_cannot_use_with(main->error, f_console_symbol_long_enable_s, f_console_symbol_long_enable_s, iki_read_long_literal_s, names[i]);
          iki_read_print_line_last_locked(setting, main->error);

          return;
        }
      } // for

      setting->flag |= iki_read_main_flag_literal_e;
    }
    else if (main->parameters.array[iki_read_parameter_object_e].result == f_console_result_found_e) {
      const uint8_t ids[2] = {
        iki_read_parameter_content_e,
        iki_read_parameter_total_e,
      };

      const f_string_static_t names[2] = {
        iki_read_long_content_s,
        iki_read_long_total_s,
      };

      for (uint8_t i = 0; i < 2; ++i) {

        if (main->parameters.array[ids[i]].result == f_console_result_found_e) {
          setting->status = F_status_set_error(F_parameter);

          iki_read_print_line_first_locked(setting, main->error);
          fll_program_print_error_parameter_cannot_use_with(main->error, f_console_symbol_long_enable_s, f_console_symbol_long_enable_s, iki_read_long_object_s, names[i]);
          iki_read_print_line_last_locked(setting, main->error);

          return;
        }
      } // for

      setting->flag |= iki_read_main_flag_object_e;
    }
    else if (main->parameters.array[iki_read_parameter_content_e].result == f_console_result_found_e) {
      if (main->parameters.array[iki_read_parameter_total_e].result == f_console_result_found_e) {
        setting->status = F_status_set_error(F_parameter);

        iki_read_print_line_first_locked(setting, main->error);
        fll_program_print_error_parameter_cannot_use_with(main->error, f_console_symbol_long_enable_s, f_console_symbol_long_enable_s, iki_read_long_content_s, iki_read_long_total_s);
        iki_read_print_line_last_locked(setting, main->error);

        return;
      }

      setting->flag |= iki_read_main_flag_content_e;
    }
    else if (main->parameters.array[iki_read_parameter_total_e].result == f_console_result_found_e) {
      if (main->parameters.array[iki_read_parameter_whole_e].result == f_console_result_found_e) {
        setting->status = F_status_set_error(F_parameter);

        iki_read_print_line_first_locked(setting, main->error);
        fll_program_print_error_parameter_cannot_use_with(main->error, f_console_symbol_long_enable_s, f_console_symbol_long_enable_s, iki_read_long_total_s, iki_read_long_wrap_s);
        iki_read_print_line_last_locked(setting, main->error);

        return;
      }

      setting->flag |= iki_read_main_flag_total_e;
    }
    else {

      // This is the default behavior.
      setting->flag |= iki_read_main_flag_content_e;
    }

    if (main->parameters.array[iki_read_parameter_whole_e].result == f_console_result_found_e) {
      setting->flag |= iki_read_main_flag_whole_e;
    }

    if (main->parameters.remaining.used) {
      setting->files.used = 0;

      setting->status = f_string_dynamics_resize(main->parameters.remaining.used, &setting->files);

      if (F_status_is_error(setting->status)) {
        iki_read_print_line_first_locked(setting, main->error);
        fll_error_print(main->error, F_status_set_fine(setting->status), "f_string_dynamics_resize", F_true);
        iki_read_print_line_last_locked(setting, main->error);

        return;
      }

      f_array_length_t index = 0;

      for (f_array_length_t i = 0; i < main->parameters.remaining.used; ++i, ++setting->files.used) {

        // Static strings are being used, so if a dynamic string exists (size > 0), then de-allocate it.
        if (setting->files.array[setting->files.used].size) {
          setting->status = f_string_dynamic_resize(0, &setting->files.array[setting->files.used]);

          if (F_status_is_error(setting->status)) {
            iki_read_print_line_first_locked(setting, main->error);
            fll_error_print(main->error, F_status_set_fine(setting->status), "f_string_dynamic_resize", F_true);
            iki_read_print_line_last_locked(setting, main->error);

            return;
          }
        }

        index = main->parameters.remaining.array[i];

        setting->files.array[setting->files.used].string = main->parameters.arguments.array[index].string;
        setting->files.array[setting->files.used].used = main->parameters.arguments.array[index].used;
        setting->files.array[setting->files.used].size = 0;

        setting->status = f_file_exists(setting->files.array[setting->files.used], F_true);

        if (F_status_is_error(setting->status)) {
          iki_read_print_line_first_locked(setting, main->error);
          fll_error_file_print(main->error, F_status_set_fine(setting->status), "f_file_exists", F_true, setting->files.array[setting->files.used], f_file_operation_verify_s, fll_error_file_type_file_e);
          iki_read_print_line_last_locked(setting, main->error);

          return;
        }
      } // for
    }
  }
#endif // _di_iki_read_setting_load_

#ifndef _di_iki_read_setting_unload_
  f_status_t iki_read_setting_unload(fll_program_data_t * const main, iki_read_setting_t * const setting) {

    if (!main || !setting) return F_status_set_error(F_parameter);

    iki_read_setting_delete(setting);

    return F_none;
  }
#endif // _di_iki_read_setting_unload_

#ifdef __cplusplus
} // extern "C"
#endif
