#include "fss_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_write_setting_load_
  void fss_write_setting_load(const f_console_arguments_t arguments, fss_write_main_t * const main, void (*callback)(const f_console_arguments_t arguments, fss_write_main_t * const main)) {

    if (!main) return;

    main->setting.state.step_small = fss_write_allocation_console_d;

    f_console_parameter_process(arguments, &main->program.parameters, &main->setting.state, 0);

    main->setting.state.step_small = fss_write_allocation_small_d;

    // Identify and process first/last parameters.
    if (main->program.parameters.array[f_console_standard_parameter_line_first_no_e].result & f_console_result_found_e) {
      main->setting.flag -= main->setting.flag & fss_write_main_flag_print_first_e;
    }
    else {
      main->setting.flag |= fss_write_main_flag_print_first_e;
    }

    if (main->program.parameters.array[f_console_standard_parameter_line_last_no_e].result & f_console_result_found_e) {
      main->setting.flag -= main->setting.flag & fss_write_main_flag_print_last_e;
    }
    else {
      main->setting.flag |= fss_write_main_flag_print_last_e;
    }

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & fss_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      fss_write_print_error(&main->program.error, macro_fss_write_f(f_console_parameter_process));

      return;
    }

    main->setting.state.status = fll_program_parameter_process_context_standard(F_true, &main->program);

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & fss_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      fss_write_print_error(&main->program.error, macro_fss_write_f(fll_program_parameter_process_context_standard));

      return;
    }

    main->setting.state.status = fll_program_parameter_process_verbosity_standard(F_true, &main->program);

    if (F_status_is_error(main->setting.state.status)) {
      if ((main->setting.flag & fss_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      fss_write_print_error(&main->program.error, macro_fss_write_f(fll_program_parameter_process_verbosity_standard));

      return;
    }

    main->program.output.to.id = F_type_descriptor_output_d;
    main->program.output.to.stream = F_type_output_d;
    main->program.output.to.flag = F_file_flag_create_d | F_file_flag_write_only_d | F_file_flag_append_d;

    if (main->program.parameters.array[f_console_standard_parameter_help_e].result & f_console_result_found_e) {
      main->setting.flag |= fss_write_main_flag_help_e;
    }

    if (main->program.parameters.array[f_console_standard_parameter_version_e].result & f_console_result_found_e) {
      main->setting.flag |= fss_write_main_flag_version_e;
    }

    if (main->program.parameters.array[f_console_standard_parameter_copyright_e].result & f_console_result_found_e) {
      main->setting.flag |= fss_write_main_flag_copyright_e;
    }

    if (main->program.pipe & fll_program_data_pipe_input_e) {
      main->setting.flag |= fss_write_main_flag_pipe_e;
    }
    else {
      main->setting.flag -= main->setting.flag & fss_write_main_flag_pipe_e;
    }

    if (callback) {
      callback(arguments, main);
      if (F_status_is_error(main->setting.state.status)) return;

      if (main->setting.state.status == F_done) {
        main->setting.state.status = F_okay;

        return;
      }
    }

    if (main->program.parameters.array[f_console_standard_parameter_help_e].result & f_console_result_found_e) return;
    if (main->program.parameters.array[f_console_standard_parameter_version_e].result & f_console_result_found_e) return;

    if ((main->program.parameters.array[fss_write_parameter_file_e].result & f_console_result_value_e) && main->program.parameters.array[fss_write_parameter_file_e].values.used) {
      if (main->program.parameters.array[fss_write_parameter_file_e].values.used > 1) {
        main->setting.state.status = F_status_set_error(F_parameter);

        if ((main->setting.flag & fss_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        fll_program_print_error_parameter_must_specify_once(&main->program.error, f_console_symbol_long_normal_s, fss_write_long_file_s);

        return;
      }

      const f_number_unsigned_t index = main->program.parameters.array[fss_write_parameter_file_e].values.array[0];

      main->program.output.to.id = -1;
      main->program.output.to.stream = 0;

      main->setting.state.status = f_file_stream_open(main->program.parameters.arguments.array[index], f_string_empty_s, &main->program.output.to);

      if (F_status_is_error(main->setting.state.status)) {
        if ((main->setting.flag & fss_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        fss_write_print_error_file(&main->program.error, macro_fss_write_f(f_file_stream_open), main->program.parameters.arguments.array[index], f_file_operation_open_s, fll_error_file_type_file_e);

        return;
      }

      main->setting.flag |= fss_write_main_flag_file_to_e;
    }
    else if (main->program.parameters.array[fss_write_parameter_file_e].result & f_console_result_found_e) {
      main->setting.state.status = F_status_set_error(F_parameter);

      if ((main->setting.flag & fss_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      fll_program_print_error_parameter_missing_value(&main->program.error, f_console_symbol_long_normal_s, fss_write_long_file_s);

      return;
    }

    if ((main->program.parameters.array[fss_write_parameter_object_e].result & f_console_result_value_e) && main->program.parameters.array[fss_write_parameter_object_e].values.used) {
      f_number_unsigneds_t * const values = &main->program.parameters.array[fss_write_parameter_object_e].values;

      main->setting.objects.used = 0;

      main->setting.state.status = f_string_dynamics_resize(values->used, &main->setting.objects);

      if (F_status_is_error(main->setting.state.status)) {
        if ((main->setting.flag & fss_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        fss_write_print_error(&main->program.error, macro_fss_write_f(f_string_dynamics_resize));

        return;
      }

      // Construct the array without allocating any more memory for the string data by setting this as a static string (used > 0, size = 0).
      for (f_number_unsigned_t index = 0; main->setting.objects.used < values->used; ) {

        index = values->array[main->setting.objects.used];

        main->setting.objects.array[main->setting.objects.used].string = main->program.parameters.arguments.array[index].string;
        main->setting.objects.array[main->setting.objects.used].used = main->program.parameters.arguments.array[index].used;
        main->setting.objects.array[main->setting.objects.used++].size = 0;
      } // for

      main->setting.flag |= fss_write_main_flag_object_e;
    }
    else if (main->program.parameters.array[fss_write_parameter_object_e].result & f_console_result_found_e) {
      main->setting.state.status = F_status_set_error(F_parameter);

      if ((main->setting.flag & fss_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      fll_program_print_error_parameter_missing_value(&main->program.error, f_console_symbol_long_normal_s, fss_write_long_object_s);

      return;
    }

    if ((main->program.parameters.array[fss_write_parameter_content_e].result & f_console_result_value_e) && main->program.parameters.array[fss_write_parameter_content_e].values.used) {

      if (main->setting.flag & fss_write_main_flag_object_e) {
        if (!(main->setting.flag & fss_write_main_flag_content_multiple_e)) {
          if (main->program.parameters.array[fss_write_parameter_content_e].values.used > main->program.parameters.array[fss_write_parameter_object_e].values.used) {
            main->setting.state.status = F_status_set_error(F_support_not);

            if ((main->setting.flag & fss_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
              fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
            }

            fss_write_print_error_one_content_only(&main->program.error);

            return;
          }
        }
      }

      f_number_unsigned_t stub_object_array[1] = { 0 };
      f_number_unsigneds_t stub_object = macro_f_number_unsigneds_t_initialize_1(stub_object_array, 0, 1);

      f_number_unsigneds_t * const values_content = &main->program.parameters.array[fss_write_parameter_content_e].values;
      f_number_unsigneds_t * const values_object = main->program.parameters.array[fss_write_parameter_object_e].values.used
        ? &main->program.parameters.array[fss_write_parameter_object_e].values
        : &stub_object;

      main->setting.contentss.used = 0;

      main->setting.state.status = f_string_dynamicss_increase_by(values_object->used, &main->setting.contentss);

      if (F_status_is_error(main->setting.state.status)) {
        if ((main->setting.flag & fss_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        fss_write_print_error(&main->program.error, macro_fss_write_f(f_string_dynamicss_increase_by));

        return;
      }

      f_number_unsigned_t i = 0; // For Contents.
      f_number_unsigned_t j = 0; // For Objects.
      f_number_unsigned_t k = 0;
      f_number_unsigned_t total = 0;
      f_number_unsigned_t index = 0;

      // Construct the array without allocating any more memory for the string data by setting this as a static string (used > 0, size = 0).
      while (i < values_content->used) {

        // Determine the total Content associated with the given Object.
        for (total = 0; i + total < values_content->used && (j + 1 >= values_object->used || values_content->array[i + total] < values_object->array[j + 1]); ++total) {
          // Do nothing.
        } // for


        if (!total) {
          ++main->setting.contentss.used;

          if (++j < values_object->used) continue;

          break;
        }

        main->setting.state.status = f_string_dynamics_increase_by(total, &main->setting.contentss.array[j]);

        if (F_status_is_error(main->setting.state.status)) {
          if ((main->setting.flag & fss_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          fss_write_print_error(&main->program.error, macro_fss_write_f(f_string_dynamics_increase_by));

          return;
        }

        for (k = 0; k < total; ++k) {

          index = values_content->array[i++];

          main->setting.contentss.array[j].array[main->setting.contentss.array[j].used].string = main->program.parameters.arguments.array[index].string;
          main->setting.contentss.array[j].array[main->setting.contentss.array[j].used].used = main->program.parameters.arguments.array[index].used;
          main->setting.contentss.array[j].array[main->setting.contentss.array[j].used++].size = 0;
        } // for
      } // while

      if (total) {
        ++main->setting.contentss.used;
      }

      main->setting.flag |= fss_write_main_flag_content_e;
    }
    else if (main->program.parameters.array[fss_write_parameter_content_e].result & f_console_result_found_e) {
      main->setting.state.status = F_status_set_error(F_parameter);

      if ((main->setting.flag & fss_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      fll_program_print_error_parameter_missing_value(&main->program.error, f_console_symbol_long_normal_s, fss_write_long_content_s);

      return;
    }

    if ((main->program.parameters.array[fss_write_parameter_prepend_e].result & f_console_result_value_e) && main->program.parameters.array[fss_write_parameter_prepend_e].values.used) {
      const f_number_unsigned_t index = main->program.parameters.array[fss_write_parameter_prepend_e].values.array[main->program.parameters.array[fss_write_parameter_prepend_e].location];

      main->setting.prepend.used = 0;

      main->setting.state.status = f_string_dynamic_append_nulless(main->program.parameters.arguments.array[index], &main->setting.prepend);

      if (F_status_is_error(main->setting.state.status)) {
        if ((main->setting.flag & fss_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        fss_write_print_error(&main->program.error, macro_fss_write_f(f_string_dynamic_append_nulless));

        return;
      }

      if (main->program.parameters.arguments.array[index].used) {
        f_string_range_t range = macro_f_string_range_t_initialize_2(main->program.parameters.arguments.array[index].used);

        for (; range.start < main->program.parameters.arguments.array[index].used; range.start++) {

          if (f_fss_is_space(main->program.parameters.arguments.array[index], range, &main->setting.state) == F_false) {
            if ((main->setting.flag & fss_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
              fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
            }

            if (F_status_is_error(main->setting.state.status)) {
              fss_write_print_error(&main->program.error, macro_fss_write_f(f_fss_is_space));
            }
            else {
              main->setting.state.status = F_status_set_error(F_parameter);

              fss_write_print_error_prepend_only_whitespace(&main->program.error);
            }

            return;
          }
        } // for
      }

      main->setting.flag |= fss_write_main_flag_prepend_e;
    }
    else if (main->program.parameters.array[fss_write_parameter_prepend_e].result & f_console_result_found_e) {
      main->setting.state.status = F_status_set_error(F_parameter);

      if ((main->setting.flag & fss_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      fll_program_print_error_parameter_missing_value(&main->program.error, f_console_symbol_long_normal_s, fss_write_long_prepend_s);

      return;
    }

    if ((main->program.parameters.array[fss_write_parameter_ignore_e].result & f_console_result_value_e) && main->program.parameters.array[fss_write_parameter_ignore_e].values.used) {
      if (main->program.parameters.array[fss_write_parameter_ignore_e].values.used % 2) {
        main->setting.state.status = F_status_set_error(F_parameter);

        if ((main->setting.flag & fss_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
          fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
        }

        fll_program_print_error_parameter_missing_value_requires_amount(&main->program.error, f_console_symbol_long_normal_s, fss_write_long_ignore_s, fss_write_string_two_s);

        return;
      }

      // Only process if the standard designates that the ingore is supported.
      if (main->setting.flag & fss_write_main_flag_ignore_e) {
        f_number_unsigned_t stub_data_array[1] = { 0 };
        f_number_unsigneds_t stub_data = macro_f_number_unsigneds_t_initialize_1(stub_data_array, 0, 1);

        f_number_unsigneds_t * const values_ignore = &main->program.parameters.array[fss_write_parameter_ignore_e].values;
        f_number_unsigneds_t * const values_data = main->program.parameters.array[fss_write_parameter_object_e].values.used
          ? &main->program.parameters.array[fss_write_parameter_object_e].values
          : main->program.parameters.array[fss_write_parameter_content_e].values.used
            ? &main->program.parameters.array[fss_write_parameter_content_e].values
            : &stub_data;

        main->setting.ignoress.used = 0;

        main->setting.state.status = f_string_rangess_increase_by(values_data->used, &main->setting.ignoress);

        if (F_status_is_error(main->setting.state.status)) {
          if ((main->setting.flag & fss_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
            fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
          }

          fss_write_print_error(&main->program.error, macro_fss_write_f(f_string_rangess_increase_by));

          return;
        }

        f_number_unsigned_t i = 0; // For Ignores.
        f_number_unsigned_t j = 0; // For Objects/Contents.
        f_number_unsigned_t k = 0;
        f_number_unsigned_t total = 0;
        f_number_unsigned_t index = 0;

        // Construct the array without allocating any more memory for the string data by setting this as a static string (used > 0, size = 0).
        while (i < values_ignore->used) {

          // Determine the total Ignore associated with the given Object/Content.
          for (total = 0; i + total < values_ignore->used && (j + 1 >= values_data->used || values_ignore->array[i + total] < values_data->array[j + 1]); ++total) {
            // Do nothing.
          } // for

          if (!total) {
            ++main->setting.ignoress.used;

            if (++j < values_data->used) continue;

            break;
          }

          main->setting.state.status = f_string_ranges_increase_by(total, &main->setting.ignoress.array[j]);

          if (F_status_is_error(main->setting.state.status)) {
            if ((main->setting.flag & fss_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
              fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
            }

            fss_write_print_error(&main->program.error, macro_fss_write_f(f_string_ranges_increase_by));

            return;
          }

          for (k = 0; k < total; ++k) {

            index = values_ignore->array[i++];

            main->setting.state.status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, main->program.parameters.arguments.array[index], &main->setting.ignoress.array[j].array[main->setting.ignoress.array[j].used].start);

            if (F_status_is_error(main->setting.state.status)) {
              if ((main->setting.flag & fss_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
                fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
              }

              fll_program_print_error_parameter_integer_not(&main->program.error, f_console_symbol_long_normal_s, fss_write_long_ignore_s, main->program.parameters.arguments.array[index]);

              return;
            }

            index = values_ignore->array[i++];

            main->setting.state.status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, main->program.parameters.arguments.array[index], &main->setting.ignoress.array[j].array[main->setting.ignoress.array[j].used].stop);

            if (F_status_is_error(main->setting.state.status)) {
              if ((main->setting.flag & fss_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
                fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
              }

              fll_program_print_error_parameter_integer_not(&main->program.error, f_console_symbol_long_normal_s, fss_write_long_ignore_s, main->program.parameters.arguments.array[index]);

              return;
            }

            if (main->setting.ignoress.array[j].array[main->setting.ignoress.array[j].used].stop > main->setting.ignoress.array[j].array[main->setting.ignoress.array[j].used].start) {
              main->setting.state.status = F_status_set_error(F_parameter);

              if ((main->setting.flag & fss_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
                fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
              }

              fll_program_print_error_parameter_range_start_before_stop(
                &main->program.error,
                f_console_symbol_long_normal_s,
                fss_write_long_ignore_s,
                main->program.parameters.arguments.array[values_ignore->array[i - 1]],
                main->program.parameters.arguments.array[index]
              );

              return;
            }

            ++main->setting.ignoress.array[j].used;
          } // for
        } // while

        if (total) {
          ++main->setting.ignoress.used;
        }
      }
      else {

        // Still validate the parameters, even if not being used.
        f_number_unsigned_t i = 0;
        f_number_unsigned_t index = 0;
        f_string_range_t number = f_string_range_t_initialize;

        while (i < main->program.parameters.array[fss_write_parameter_ignore_e].values.used) {

          index = main->program.parameters.array[fss_write_parameter_ignore_e].values.array[i++];

          main->setting.state.status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, main->program.parameters.arguments.array[index], &number.start);

          if (F_status_is_error(main->setting.state.status)) {
            if ((main->setting.flag & fss_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
              fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
            }

            fll_program_print_error_parameter_integer_not(&main->program.error, f_console_symbol_long_normal_s, fss_write_long_ignore_s, main->program.parameters.arguments.array[index]);

            return;
          }

          index = main->program.parameters.array[fss_write_parameter_ignore_e].values.array[i++];

          main->setting.state.status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, main->program.parameters.arguments.array[index], &number.stop);

          if (F_status_is_error(main->setting.state.status)) {
            if ((main->setting.flag & fss_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
              fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
            }

            fll_program_print_error_parameter_integer_not(&main->program.error, f_console_symbol_long_normal_s, fss_write_long_ignore_s, main->program.parameters.arguments.array[index]);

            return;
          }

          if (number.start > number.stop) {
            main->setting.state.status = F_status_set_error(F_parameter);

            if ((main->setting.flag & fss_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
              fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
            }

            fll_program_print_error_parameter_range_start_before_stop(
              &main->program.error,
              f_console_symbol_long_normal_s,
              fss_write_long_ignore_s,
              main->program.parameters.arguments.array[main->program.parameters.array[fss_write_parameter_ignore_e].values.array[i - 1]],
              main->program.parameters.arguments.array[index]
            );

            return;
          }
        } // while
      }
    }
    else if (main->program.parameters.array[fss_write_parameter_ignore_e].result & f_console_result_found_e) {
      main->setting.state.status = F_status_set_error(F_parameter);

      if ((main->setting.flag & fss_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
        fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
      }

      fll_program_print_error_parameter_missing_value(&main->program.error, f_console_symbol_long_normal_s, fss_write_long_ignore_s);

      return;
    }
    else {

      // There is no Object or Content, so remove ignores if set.
      if (main->setting.flag & fss_write_main_flag_ignore_e) {
        main->setting.flag -= fss_write_main_flag_ignore_e;
      }
    }

    if (main->program.parameters.array[fss_write_parameter_partial_e].result & f_console_result_found_e) {
      main->setting.flag |= fss_write_main_flag_partial_e;
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

        if (main->program.parameters.array[has[i]].result & f_console_result_found_e) {
          if (main->setting.flag & (fss_write_main_flag_object_e | fss_write_main_flag_content_e)) {
            if (!(main->setting.flag & fss_write_main_flag_partial_e)) {
              main->setting.state.status = F_status_set_error(F_parameter);

              if (main->program.error.verbosity > f_console_verbosity_quiet_e) {
                fll_print_dynamic_raw(f_string_eol_s, main->program.error.to);
              }

              fll_program_print_error_parameter_cannot_use_with_without(
                &main->program.error,
                f_console_symbol_long_normal_s,
                f_console_symbol_long_normal_s,
                f_console_symbol_long_normal_s,
                has_string[i],
                (main->setting.flag & fss_write_main_flag_object_e)
                  ? fss_write_long_object_s
                  : fss_write_long_content_s,
                fss_write_long_partial_s
              );

              return;
            }
          }

          if (main->program.parameters.array[has_cannots[i][0]].result & f_console_result_found_e) {
            main->setting.state.status = F_status_set_error(F_parameter);

            if ((main->setting.flag & fss_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
              fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
            }

            fll_program_print_error_parameter_cannot_use_with(&main->program.error, f_console_symbol_long_normal_s, f_console_symbol_long_normal_s, has_string[i], has_cannots_string[i][0]);

            return;
          }

          if (main->program.parameters.array[has_cannots[i][1]].result & f_console_result_found_e) {
            main->setting.state.status = F_status_set_error(F_parameter);

            if ((main->setting.flag & fss_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
              fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
            }

            fll_program_print_error_parameter_cannot_use_with(&main->program.error, f_console_symbol_long_normal_s, f_console_symbol_long_normal_s, has_string[i], has_cannots_string[i][1]);

            return;
          }

          main->setting.flag |= has_flag[i];
        }
      } // for
    }

    if (main->setting.flag & (fss_write_main_flag_object_e | fss_write_main_flag_content_e)) {
      if (main->setting.flag & fss_write_main_flag_object_e) {
        if (main->setting.flag & fss_write_main_flag_content_multiple_e) {
          if (main->program.parameters.array[fss_write_parameter_object_e].locations_sub.used > main->program.parameters.array[fss_write_parameter_content_e].locations_sub.used && !(main->setting.flag & fss_write_main_flag_partial_e)) {
            main->setting.state.status = F_status_set_error(F_parameter);

            if ((main->setting.flag & fss_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
              fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
            }

            fss_write_print_error_parameter_same_times_at_least(&main->program.error);

            return;
          }
        }

        if ((main->setting.flag & fss_write_main_flag_content_e) && (main->setting.flag & fss_write_main_flag_partial_e)) {
          if (main->program.parameters.array[fss_write_parameter_content_e].result & f_console_result_value_e) {
            main->setting.state.status = F_status_set_error(F_parameter);

            if ((main->setting.flag & fss_write_main_flag_print_first_e) && main->program.message.verbosity > f_console_verbosity_error_e) {
              fll_print_dynamic_raw(f_string_eol_s, main->program.message.to);
            }

            fll_program_print_error_parameter_cannot_use_with_xor(&main->program.error, f_console_symbol_long_normal_s, f_console_symbol_long_normal_s, f_console_symbol_long_normal_s, fss_write_long_partial_s, fss_write_long_object_s, fss_write_long_content_s);

            return;
          }
        }
      }
    }

    main->setting.quote = f_fss_quote_double_s;

    if (main->program.parameters.array[fss_write_parameter_double_e].result & f_console_result_found_e) {
      if (main->program.parameters.array[fss_write_parameter_single_e].result & f_console_result_found_e) {
        if (main->program.parameters.array[fss_write_parameter_double_e].location < main->program.parameters.array[fss_write_parameter_single_e].location) {
          main->setting.quote = f_fss_quote_single_s;

          if (main->program.parameters.array[fss_write_parameter_backtick_e].result & f_console_result_found_e) {
            if (main->program.parameters.array[fss_write_parameter_single_e].location < main->program.parameters.array[fss_write_parameter_backtick_e].location) {
              main->setting.quote = f_fss_quote_backtick_s;
            }
          }
        }
        else if (main->program.parameters.array[fss_write_parameter_backtick_e].result & f_console_result_found_e) {
          if (main->program.parameters.array[fss_write_parameter_double_e].location < main->program.parameters.array[fss_write_parameter_backtick_e].location) {
            main->setting.quote = f_fss_quote_backtick_s;
          }
        }
      }
      else if (main->program.parameters.array[fss_write_parameter_backtick_e].result & f_console_result_found_e) {
        if (main->program.parameters.array[fss_write_parameter_double_e].location < main->program.parameters.array[fss_write_parameter_backtick_e].location) {
          main->setting.quote = f_fss_quote_backtick_s;
        }
      }
    }
    else if (main->program.parameters.array[fss_write_parameter_single_e].result & f_console_result_found_e) {
      main->setting.quote = f_fss_quote_single_s;

      if (main->program.parameters.array[fss_write_parameter_backtick_e].result & f_console_result_found_e) {
        if (main->program.parameters.array[fss_write_parameter_single_e].location < main->program.parameters.array[fss_write_parameter_backtick_e].location) {
          main->setting.quote = f_fss_quote_backtick_s;
        }
      }
    }
    else if (main->program.parameters.array[fss_write_parameter_backtick_e].result & f_console_result_found_e) {
      main->setting.quote = f_fss_quote_backtick_s;
    }

    if (main->program.parameters.array[fss_write_parameter_trim_e].result & f_console_result_found_e) {
      main->setting.flag |= fss_write_main_flag_trim_e;
    }

    if (!(main->setting.flag & (fll_program_data_pipe_input_e | fss_write_main_flag_content_e | fss_write_parameter_object_e))) {
      main->setting.state.status = F_data_not;
    }
  }
#endif // _di_fss_write_setting_load_

#ifdef __cplusplus
} // extern "C"
#endif
