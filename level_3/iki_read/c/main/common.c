#include "iki_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_read_setting_delete_
  f_status_t iki_read_setting_delete(iki_read_setting_t * const setting) {

    if (!setting) return F_status_set_error(F_parameter);

    f_string_dynamic_resize(0, &setting->buffer);
    f_string_dynamics_resize(0, &setting->names);
    f_string_dynamics_resize(0, &setting->files);

    f_string_maps_resize(0, &setting->replace);
    f_string_triples_resize(0, &setting->reassign);
    f_string_triples_resize(0, &setting->substitute);
    f_string_triples_resize(0, &setting->wrap);

    f_iki_data_delete(&setting->data);

    return F_none;
  }
#endif // _di_iki_read_setting_delete_

#ifndef _di_iki_read_setting_load_
  void iki_read_setting_load(const f_console_arguments_t arguments, iki_read_main_t * const main) {

    if (!main) return;

    main->setting.state.step_small = iki_read_allocation_console_d;

    f_console_parameter_process(arguments, &main->program.parameters, &main->setting.state, 0);

    main->setting.state.step_small = iki_read_allocation_small_d;

    // Identify and pocess first/last parameters.
    if (main->program.parameters.array[iki_read_parameter_line_first_no_e].result & f_console_result_found_e) {
      main->setting.flag -= main->setting.flag & iki_read_main_flag_print_first_e;
    }
    else {
      main->setting.flag |= iki_read_main_flag_print_first_e;
    }

    if (main->program.parameters.array[iki_read_parameter_line_last_no_e].result & f_console_result_found_e) {
      main->setting.flag -= main->setting.flag & iki_read_main_flag_print_last_e;
    }
    else {
      main->setting.flag |= iki_read_main_flag_print_last_e;
    }

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & iki_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      iki_read_print_error(&main->program.error, macro_iki_read_f(f_console_parameter_process));

      return;
    }

    {
      f_uint16s_t choices = f_uint16s_t_initialize;

      // Identify and prioritize "color context" parameters.
      {
        uint16_t choices_array[3] = { iki_read_parameter_no_color_e, iki_read_parameter_light_e, iki_read_parameter_dark_e };
        choices.array = choices_array;
        choices.used = 3;

        const uint8_t modes[3] = { f_color_mode_not_e, f_color_mode_light_e, f_color_mode_dark_e };

        main->setting.state.status = fll_program_parameter_process_context(choices, modes, F_true, &main->program);

        if (F_status_is_error(main->setting.state.status)) {
          if ((main->setting.flag & iki_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          iki_read_print_error(&main->program.error, macro_iki_read_f(fll_program_parameter_process_context));

          return;
        }
      }

      // Identify and prioritize "verbosity" parameters.
      {
        uint16_t choices_array[5] = { iki_read_parameter_verbosity_quiet_e, iki_read_parameter_verbosity_error_e, iki_read_parameter_verbosity_verbose_e, iki_read_parameter_verbosity_debug_e, iki_read_parameter_verbosity_normal_e };
        choices.array = choices_array;
        choices.used = 5;

        const uint8_t verbosity[5] = { f_console_verbosity_quiet_e, f_console_verbosity_error_e, f_console_verbosity_verbose_e, f_console_verbosity_debug_e, f_console_verbosity_normal_e };

        main->setting.state.status = fll_program_parameter_process_verbosity(choices, verbosity, F_true, &main->program);

        if (F_status_is_error(main->setting.state.status)) {
          if ((main->setting.flag & iki_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          iki_read_print_error(&main->program.error, macro_iki_read_f(fll_program_parameter_process_verbosity));

          return;
        }
      }

      if (main->program.parameters.array[iki_read_parameter_help_e].result & f_console_result_found_e) {
        main->setting.flag |= iki_read_main_flag_help_e;

        return;
      }

      if (main->program.parameters.array[iki_read_parameter_version_e].result & f_console_result_found_e) {
        main->setting.flag |= iki_read_main_flag_version_e;

        return;
      }

      if (main->program.parameters.array[iki_read_parameter_copyright_e].result & f_console_result_found_e) {
        main->setting.flag |= iki_read_main_flag_copyright_e;

        return;
      }
    }

    if (!(main->program.parameters.remaining.used || (main->program.pipe & fll_program_data_pipe_input_e))) {
      main->setting.state.status = F_status_set_error(F_parameter);

      if ((main->setting.flag & iki_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      fll_program_print_error_missing_file(&main->program.error);

      return;
    }

    if (main->program.parameters.array[iki_read_parameter_at_e].result & f_console_result_value_e) {
      if (main->program.parameters.array[iki_read_parameter_whole_e].result & f_console_result_found_e) {
        main->setting.state.status = F_status_set_error(F_parameter);

        if ((main->setting.flag & iki_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        fll_program_print_error_parameter_cannot_use_with(&main->program.error, f_console_symbol_long_normal_s, f_console_symbol_long_normal_s, iki_read_long_at_s, iki_read_long_whole_s);

        return;
      }

      const f_array_length_t index = main->program.parameters.array[iki_read_parameter_at_e].values.array[main->program.parameters.array[iki_read_parameter_at_e].values.used - 1];

      main->setting.at = 0;

      main->setting.state.status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, main->program.parameters.arguments.array[index], &main->setting.at);

      if (F_status_is_error(main->setting.state.status)) {
        main->setting.state.status = F_status_set_error(F_parameter);

        if ((main->setting.flag & iki_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        fll_program_print_error_parameter_integer_not(&main->program.error, f_console_symbol_long_normal_s, iki_read_long_at_s, main->program.parameters.arguments.array[index]);

        return;
      }

      main->setting.flag |= iki_read_main_flag_at_e;
    }
    else if (main->program.parameters.array[iki_read_parameter_at_e].result & f_console_result_found_e) {
      main->setting.state.status = F_status_set_error(F_parameter);

      if ((main->setting.flag & iki_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      fll_program_print_error_parameter_missing_value(&main->program.error, f_console_symbol_long_normal_s, iki_read_long_at_s);

      return;
    }

    if (main->program.parameters.array[iki_read_parameter_line_e].result & f_console_result_value_e) {
      const f_array_length_t index = main->program.parameters.array[iki_read_parameter_line_e].values.array[main->program.parameters.array[iki_read_parameter_line_e].values.used - 1];

      main->setting.line = 0;

      main->setting.state.status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, main->program.parameters.arguments.array[index], &main->setting.line);

      if (F_status_is_error(main->setting.state.status)) {
        main->setting.state.status = F_status_set_error(F_parameter);

        if ((main->setting.flag & iki_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        fll_program_print_error_parameter_integer_not(&main->program.error, f_console_symbol_long_normal_s, iki_read_long_line_s, main->program.parameters.arguments.array[index]);

        return;
      }

      main->setting.flag |= iki_read_main_flag_line_e;
    }
    else if (main->program.parameters.array[iki_read_parameter_line_e].result & f_console_result_found_e) {
      main->setting.state.status = F_status_set_error(F_parameter);

      if ((main->setting.flag & iki_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      fll_program_print_error_parameter_missing_value(&main->program.error, f_console_symbol_long_normal_s, iki_read_long_line_s);

      return;
    }

    if (main->program.parameters.array[iki_read_parameter_name_e].result & f_console_result_value_e) {
      main->setting.names.used = 0;

      main->setting.state.status = f_string_dynamics_increase_by(main->program.parameters.array[iki_read_parameter_name_e].values.used, &main->setting.names);

      if (F_status_is_error(main->setting.state.status)) {
        if ((main->setting.flag & iki_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        iki_read_print_error(&main->program.error, macro_iki_read_f(f_string_dynamics_increase_by));

        return;
      }

      // Distinctly append all names.
      f_array_length_t i = 0;
      f_array_length_t j = 0;
      f_array_lengths_t *values = &main->program.parameters.array[iki_read_parameter_name_e].values;

      for (; i < values->used; ++i) {

        for (j = 0; j < main->setting.names.used; ++j) {
          if (fl_string_dynamic_compare(main->program.parameters.arguments.array[values->array[i]], main->setting.names.array[j]) == F_equal_to) break;
        } // for

        if (j < main->setting.names.used) continue;

        main->setting.names.array[main->setting.names.used].used = 0;

        if (main->program.parameters.arguments.array[values->array[i]].used) {
          main->setting.state.status = f_string_dynamics_append(main->program.parameters.arguments.array[values->array[i]], &main->setting.names);
          if (F_status_is_error(main->setting.state.status)) break;
        }
        else {
          main->setting.state.status = f_string_dynamics_append(f_string_empty_s, &main->setting.names);
          if (F_status_is_error(main->setting.state.status)) break;
        }
      } // for

      if (F_status_is_error(main->setting.state.status)) {
        if ((main->setting.flag & iki_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        iki_read_print_error(&main->program.error, macro_iki_read_f(f_string_dynamics_append));

        return;
      }

      main->setting.flag |= iki_read_main_flag_name_e;
    }
    else if (main->program.parameters.array[iki_read_parameter_name_e].result & f_console_result_found_e) {
      main->setting.state.status = F_status_set_error(F_parameter);

      if ((main->setting.flag & iki_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      fll_program_print_error_parameter_missing_value(&main->program.error, f_console_symbol_long_normal_s, iki_read_long_name_s);

      return;
    }

    if (main->program.parameters.array[iki_read_parameter_replace_e].result != f_console_result_none_e) {
      if ((main->program.parameters.array[iki_read_parameter_replace_e].result & f_console_result_found_e) || main->program.parameters.array[iki_read_parameter_replace_e].values.used % 2 != 0) {
        main->setting.state.status = F_status_set_error(F_parameter);

        if ((main->setting.flag & iki_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        fll_program_print_error_parameter_missing_value_requires_amount(&main->program.error, f_console_symbol_long_normal_s, iki_read_long_replace_s, iki_read_string_two_s);

        return;
      }

      main->setting.replace.used = 0;

      main->setting.state.status = f_string_maps_increase_by(main->program.parameters.array[iki_read_parameter_replace_e].values.used / 2, &main->setting.replace);

      if (F_status_is_error(main->setting.state.status)) {
        if ((main->setting.flag & iki_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        iki_read_print_error(&main->program.error, macro_iki_read_f(f_string_maps_increase_by));

        return;
      }

      f_array_length_t at = 0;
      f_array_length_t index = 0;
      f_array_length_t i = 0;
      f_array_length_t j = 0;

      for (; i < main->program.parameters.array[iki_read_parameter_replace_e].values.used; ++i) {

        index = main->program.parameters.array[iki_read_parameter_replace_e].values.array[i];

        // Replace any existing value so that each name exists only once.
        for (j = 0; j < main->setting.replace.used; ++j) {

          if (fl_string_dynamic_compare(main->program.parameters.arguments.array[index], main->setting.replace.array[j].name) == F_equal_to) {
            break;
          }
        } // for

        at = j;

        // Static strings are being used, so if a dynamic string exists (size > 0), then de-allocate it.
        if (main->setting.replace.array[at].name.size) {
          main->setting.state.status = f_string_dynamic_resize(0, &main->setting.replace.array[at].name);
        }

        if (F_status_is_error_not(main->setting.state.status) && main->setting.replace.array[at].value.size) {
          main->setting.state.status = f_string_dynamic_resize(0, &main->setting.replace.array[at].value);
        }

        if (F_status_is_error(main->setting.state.status)) {
          if ((main->setting.flag & iki_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          iki_read_print_error(&main->program.error, macro_iki_read_f(f_string_dynamic_resize));

          return;
        }

        main->setting.replace.array[at].name.string = main->program.parameters.arguments.array[index].string;
        main->setting.replace.array[at].name.used = main->program.parameters.arguments.array[index].used;
        main->setting.replace.array[at].name.size = 0;

        index = main->program.parameters.array[iki_read_parameter_replace_e].values.array[++i];

        main->setting.replace.array[at].value.string = main->program.parameters.arguments.array[index].string;
        main->setting.replace.array[at].value.used = main->program.parameters.arguments.array[index].used;
        main->setting.replace.array[at].value.size = 0;

        if (at == main->setting.replace.used) {
          ++main->setting.replace.used;
        }
      } // for

      main->setting.flag |= iki_read_main_flag_replace_e;
    }

    if (iki_read_setting_load_parameter_substitution(main, main->program.parameters.array[iki_read_parameter_reassign_e], iki_read_long_reassign_s, &main->setting.reassign)) {
      main->setting.flag |= iki_read_main_flag_reassign_e;
    }

    if (F_status_is_error(main->setting.state.status)) return;

    if (iki_read_setting_load_parameter_substitution(main, main->program.parameters.array[iki_read_parameter_substitute_e], iki_read_long_substitute_s, &main->setting.substitute)) {
      main->setting.flag |= iki_read_main_flag_substitute_e;
    }

    if (F_status_is_error(main->setting.state.status)) return;

    if (main->program.parameters.array[iki_read_parameter_wrap_e].result != f_console_result_none_e) {
      if ((main->program.parameters.array[iki_read_parameter_wrap_e].result & f_console_result_found_e) || main->program.parameters.array[iki_read_parameter_wrap_e].values.used % 3 != 0) {
        main->setting.state.status = F_status_set_error(F_parameter);

        if ((main->setting.flag & iki_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        fll_program_print_error_parameter_missing_value_requires_amount(&main->program.error, f_console_symbol_long_normal_s, iki_read_long_wrap_s, iki_read_string_three_s);

        return;
      }

      main->setting.wrap.used = 0;

      main->setting.state.status = f_string_triples_increase_by(main->program.parameters.array[iki_read_parameter_wrap_e].values.used / 3, &main->setting.wrap);

      if (F_status_is_error(main->setting.state.status)) {
        if ((main->setting.flag & iki_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        iki_read_print_error(&main->program.error, macro_iki_read_f(f_string_triples_increase_by));

        return;
      }

      f_array_length_t at = 0;
      f_array_length_t index = 0;
      f_array_length_t i = 0;
      f_array_length_t j = 0;

      for (; i < main->program.parameters.array[iki_read_parameter_wrap_e].values.used; ++i) {

        index = main->program.parameters.array[iki_read_parameter_wrap_e].values.array[i];

        // Replace any existing values so that each name exists only once.
        for (j = 0; j < main->setting.wrap.used; ++j) {

          if (fl_string_dynamic_compare(main->program.parameters.arguments.array[index], main->setting.wrap.array[j].a) == F_equal_to) {
            break;
          }
        } // for

        at = j;

        // Static strings are being used, so if a dynamic string exists (size > 0), then de-allocate it.
        if (main->setting.wrap.array[at].a.size) {
          main->setting.state.status = f_string_dynamic_resize(0, &main->setting.wrap.array[at].a);
        }

        if (F_status_is_error_not(main->setting.state.status) && main->setting.wrap.array[at].b.size) {
          main->setting.state.status = f_string_dynamic_resize(0, &main->setting.wrap.array[at].b);
        }

        if (F_status_is_error_not(main->setting.state.status) && main->setting.wrap.array[at].c.size) {
          main->setting.state.status = f_string_dynamic_resize(0, &main->setting.wrap.array[at].c);
        }

        if (F_status_is_error(main->setting.state.status)) {
          if ((main->setting.flag & iki_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          iki_read_print_error(&main->program.error, macro_iki_read_f(f_string_dynamic_resize));

          return;
        }

        main->setting.wrap.array[at].a.string = main->program.parameters.arguments.array[index].string;
        main->setting.wrap.array[at].a.used = main->program.parameters.arguments.array[index].used;
        main->setting.wrap.array[at].a.size = 0;

        index = main->program.parameters.array[iki_read_parameter_wrap_e].values.array[++i];

        main->setting.wrap.array[at].b.string = main->program.parameters.arguments.array[index].string;
        main->setting.wrap.array[at].b.used = main->program.parameters.arguments.array[index].used;
        main->setting.wrap.array[at].b.size = 0;

        index = main->program.parameters.array[iki_read_parameter_wrap_e].values.array[++i];

        main->setting.wrap.array[at].c.string = main->program.parameters.arguments.array[index].string;
        main->setting.wrap.array[at].c.used = main->program.parameters.arguments.array[index].used;
        main->setting.wrap.array[at].c.size = 0;

        if (at == main->setting.wrap.used) {
          ++main->setting.wrap.used;
        }
      } // for

      main->setting.flag |= iki_read_main_flag_wrap_e;
    }

    if (main->program.parameters.array[iki_read_parameter_literal_e].result & f_console_result_found_e) {
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

        if (main->program.parameters.array[ids[i]].result & f_console_result_found_e) {
          main->setting.state.status = F_status_set_error(F_parameter);

          if ((main->setting.flag & iki_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          fll_program_print_error_parameter_cannot_use_with(&main->program.error, f_console_symbol_long_normal_s, f_console_symbol_long_normal_s, iki_read_long_literal_s, names[i]);

          return;
        }
      } // for

      main->setting.flag |= iki_read_main_flag_literal_e;
    }
    else if (main->program.parameters.array[iki_read_parameter_object_e].result & f_console_result_found_e) {
      const uint8_t ids[2] = {
        iki_read_parameter_content_e,
        iki_read_parameter_total_e,
      };

      const f_string_static_t names[2] = {
        iki_read_long_content_s,
        iki_read_long_total_s,
      };

      for (uint8_t i = 0; i < 2; ++i) {

        if (main->program.parameters.array[ids[i]].result & f_console_result_found_e) {
          main->setting.state.status = F_status_set_error(F_parameter);

          if ((main->setting.flag & iki_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          fll_program_print_error_parameter_cannot_use_with(&main->program.error, f_console_symbol_long_normal_s, f_console_symbol_long_normal_s, iki_read_long_object_s, names[i]);

          return;
        }
      } // for

      main->setting.flag |= iki_read_main_flag_object_e;
    }
    else if (main->program.parameters.array[iki_read_parameter_content_e].result & f_console_result_found_e) {
      if (main->program.parameters.array[iki_read_parameter_total_e].result & f_console_result_found_e) {
        main->setting.state.status = F_status_set_error(F_parameter);

        if ((main->setting.flag & iki_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        fll_program_print_error_parameter_cannot_use_with(&main->program.error, f_console_symbol_long_normal_s, f_console_symbol_long_normal_s, iki_read_long_content_s, iki_read_long_total_s);

        return;
      }

      main->setting.flag |= iki_read_main_flag_content_e;
    }
    else if (main->program.parameters.array[iki_read_parameter_total_e].result & f_console_result_found_e) {
      if (main->program.parameters.array[iki_read_parameter_whole_e].result & f_console_result_found_e) {
        main->setting.state.status = F_status_set_error(F_parameter);

        if ((main->setting.flag & iki_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        fll_program_print_error_parameter_cannot_use_with(&main->program.error, f_console_symbol_long_normal_s, f_console_symbol_long_normal_s, iki_read_long_total_s, iki_read_long_wrap_s);

        return;
      }

      main->setting.flag |= iki_read_main_flag_total_e;
    }
    else {

      // This is the default behavior.
      main->setting.flag |= iki_read_main_flag_content_e;
    }

    if (main->program.parameters.array[iki_read_parameter_whole_e].result & f_console_result_found_e) {
      main->setting.flag |= iki_read_main_flag_whole_e;
    }

    if (main->program.parameters.remaining.used) {
      main->setting.files.used = 0;

      main->setting.state.status = f_string_dynamics_resize(main->program.parameters.remaining.used, &main->setting.files);

      if (F_status_is_error(main->setting.state.status)) {
        if ((main->setting.flag & iki_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        iki_read_print_error(&main->program.error, macro_iki_read_f(f_string_dynamics_resize));

        return;
      }

      f_array_length_t index = 0;

      for (f_array_length_t i = 0; i < main->program.parameters.remaining.used; ++i, ++main->setting.files.used) {

        // Static strings are being used, so if a dynamic string exists (size > 0), then de-allocate it.
        if (main->setting.files.array[main->setting.files.used].size) {
          main->setting.state.status = f_string_dynamic_resize(0, &main->setting.files.array[main->setting.files.used]);

          if (F_status_is_error(main->setting.state.status)) {
            if ((main->setting.flag & iki_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
              fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
            }

            iki_read_print_error(&main->program.error, macro_iki_read_f(f_string_dynamic_resize));

            return;
          }
        }

        index = main->program.parameters.remaining.array[i];

        main->setting.files.array[main->setting.files.used].string = main->program.parameters.arguments.array[index].string;
        main->setting.files.array[main->setting.files.used].used = main->program.parameters.arguments.array[index].used;
        main->setting.files.array[main->setting.files.used].size = 0;

        main->setting.state.status = f_file_exists(main->setting.files.array[main->setting.files.used], F_true);

        if (F_status_is_error(main->setting.state.status)) {
          if ((main->setting.flag & iki_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          fll_error_file_print(&main->program.error, F_status_set_fine(main->setting.state.status), macro_iki_read_f(f_file_exists), fll_error_file_flag_fallback_e, main->setting.files.array[main->setting.files.used], f_file_operation_verify_s, fll_error_file_type_file_e);

          return;
        }
      } // for
    }
  }
#endif // _di_iki_read_setting_load_

#ifndef _di_iki_read_setting_load_parameter_substitution_
  f_status_t iki_read_setting_load_parameter_substitution(iki_read_main_t * const main, const f_console_parameter_t parameter, const f_string_static_t name, f_string_triples_t *triple) {

    if (!(parameter.result & f_console_result_found_e)) return F_false;

    if ((parameter.result & f_console_result_found_e) || parameter.values.used % 3 != 0) {
      main->setting.state.status = F_status_set_error(F_parameter);

      if ((main->setting.flag & iki_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      fll_program_print_error_parameter_missing_value_requires_amount(&main->program.error, f_console_symbol_long_normal_s, name, iki_read_string_three_s);

      return F_false;
    }

    triple->used = 0;

    main->setting.state.status = f_string_triples_increase_by(parameter.values.used / 3, triple);

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & iki_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      iki_read_print_error(&main->program.error, macro_iki_read_f(f_string_triples_increase_by));

      return F_false;
    }

    f_array_length_t at = 0;
    f_array_length_t index = 0;
    f_array_length_t i = 0;
    f_array_length_t j = 0;

    for (; i < parameter.values.used; ++i) {

      index = parameter.values.array[i];

      // Replace any existing values so that each name and value pair exists only once.
      for (j = 0; j < triple->used; ++j) {

        if (fl_string_dynamic_compare(main->program.parameters.arguments.array[index], triple->array[j].a) == F_equal_to) {
          if (fl_string_dynamic_compare(main->program.parameters.arguments.array[parameter.values.array[i + 1]], triple->array[j].b) == F_equal_to) {
            break;
          }
        }
      } // for

      at = j;

      // Static strings are being used, so if a dynamic string exists (size > 0), then de-allocate it.
      if (triple->array[at].a.size) {
        main->setting.state.status = f_string_dynamic_resize(0, &triple->array[at].a);
      }

      if (F_status_is_error_not(main->setting.state.status) && triple->array[at].b.size) {
        main->setting.state.status = f_string_dynamic_resize(0, &triple->array[at].b);
      }

      if (F_status_is_error_not(main->setting.state.status) && triple->array[at].c.size) {
        main->setting.state.status = f_string_dynamic_resize(0, &triple->array[at].c);
      }

      if (F_status_is_error(main->setting.state.status)) {
        if ((main->setting.flag & iki_read_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        iki_read_print_error(&main->program.error, macro_iki_read_f(f_string_dynamic_resize));

        return F_false;
      }

      triple->array[at].a.string = main->program.parameters.arguments.array[index].string;
      triple->array[at].a.used = main->program.parameters.arguments.array[index].used;
      triple->array[at].a.size = 0;

      index = parameter.values.array[++i];

      triple->array[at].b.string = main->program.parameters.arguments.array[index].string;
      triple->array[at].b.used = main->program.parameters.arguments.array[index].used;
      triple->array[at].b.size = 0;

      index = parameter.values.array[++i];

      triple->array[at].c.string = main->program.parameters.arguments.array[index].string;
      triple->array[at].c.used = main->program.parameters.arguments.array[index].used;
      triple->array[at].c.size = 0;

      if (at == triple->used) {
        ++triple->used;
      }
    } // for

    return F_true;
  }
#endif // _di_iki_read_setting_load_parameter_substitution_

#ifndef _di_iki_read_setting_unload_
  f_status_t iki_read_setting_unload(iki_read_main_t * const main) {

    if (!main) return F_status_set_error(F_parameter);

    iki_read_setting_delete(&main->setting);

    return F_none;
  }
#endif // _di_iki_read_setting_unload_

#ifdef __cplusplus
} // extern "C"
#endif
