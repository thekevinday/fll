#include "fss_basic_read.h"
#include "private-common.h"
#include "private-print.h"
#include "private-read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_basic_read_delimit_object_is_
  f_status_t fss_basic_read_delimit_object_is(fss_basic_read_data_t * const data, const f_array_length_t depth) {

    switch (data->delimit_mode) {
      case fss_basic_read_delimit_mode_none_e:
      case fss_basic_read_delimit_mode_content_e:
      case fss_basic_read_delimit_mode_content_greater_e:
      case fss_basic_read_delimit_mode_content_lesser_e:
        return F_false;

      case fss_basic_read_delimit_mode_all_e:
      case fss_basic_read_delimit_mode_content_object_e:
      case fss_basic_read_delimit_mode_content_greater_object_e:
      case fss_basic_read_delimit_mode_content_lesser_object_e:
      case fss_basic_read_delimit_mode_object_e:
        return F_true;

      default:
        break;
    }

    return depth == data->delimit_depth || data->delimit_mode == fss_basic_read_delimit_mode_content_lesser_e;
  }
#endif // _di_fss_basic_read_delimit_object_is_

#ifndef _di_fss_basic_read_depth_process_
  f_status_t fss_basic_read_depth_process(fll_program_data_t * const main, fss_basic_read_data_t * const data) {

    f_status_t status = F_none;

    {
      f_array_length_t depth_size = 1;

      if (main->parameters.array[fss_basic_read_parameter_depth_e].result & f_console_result_value_e) {
        depth_size = main->parameters.array[fss_basic_read_parameter_depth_e].values.used;
      }

      if (depth_size > data->depths.size) {
        status = fss_basic_read_depths_resize(depth_size, &data->depths);

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "fss_basic_read_depths_resize", fll_error_file_flag_fallback_e);

          return status;
        }
      }

      data->depths.used = depth_size;
    }

    f_array_length_t position_depth = 0;
    f_array_length_t position_at = 0;
    f_array_length_t position_name = 0;

    for (f_array_length_t i = 0; i < data->depths.used; ++i) {

      if (!((++main->signal_check) % fss_basic_read_signal_check_d)) {
        if (fll_program_standard_signal_received(&main->program)) {
          fll_program_print_signal_received(main->warning, main->signal_received);

          return F_status_set_error(F_interrupt);
        }

        main->signal_check = 0;
      }

      data->depths.array[i].depth = 0;
      data->depths.array[i].index_at = 0;
      data->depths.array[i].index_name = 0;
      data->depths.array[i].value_at = 0;

      macro_f_string_dynamic_t_clear(data->depths.array[i].value_name);

      if (!main->parameters.array[fss_basic_read_parameter_depth_e].values.used) {
        position_depth = 0;
      }
      else {
        position_depth = main->parameters.array[fss_basic_read_parameter_depth_e].values.array[i];

        status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, data->argv[position_depth], &data->depths.array[i].depth);

        if (F_status_is_error(status)) {
          fll_error_parameter_integer_print(main->error, F_status_set_fine(status), "fl_conversion_dynamic_to_unsigned_detect", F_true, fss_basic_read_long_depth_s, data->argv[position_depth]);

          return status;
        }
      }

      if (main->parameters.array[fss_basic_read_parameter_at_e].result & f_console_result_value_e) {
        for (; position_at < main->parameters.array[fss_basic_read_parameter_at_e].values.used; ++position_at) {

          if (main->parameters.array[fss_basic_read_parameter_at_e].values.array[position_at] < position_depth) {
            continue;
          }

          if (i + 1 < data->depths.used && main->parameters.array[fss_basic_read_parameter_at_e].values.array[position_at] > main->parameters.array[fss_basic_read_parameter_depth_e].values.array[i + 1]) {
            break;
          }

          data->depths.array[i].index_at = main->parameters.array[fss_basic_read_parameter_at_e].values.array[position_at];

          status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, data->argv[data->depths.array[i].index_at], &data->depths.array[i].value_at);

          if (F_status_is_error(status)) {
            fll_error_parameter_integer_print(main->error, F_status_set_fine(status), "fl_conversion_dynamic_to_unsigned_detect", F_true, fss_basic_read_long_at_s, data->argv[data->depths.array[i].index_at]);

            return status;
          }
        } // for
      }

      if (main->parameters.array[fss_basic_read_parameter_name_e].result & f_console_result_value_e) {
        for (; position_name < main->parameters.array[fss_basic_read_parameter_name_e].values.used; position_name++) {

          if (main->parameters.array[fss_basic_read_parameter_name_e].values.array[position_name] < position_depth) {
            continue;
          }

          if (i + 1 < data->depths.used && main->parameters.array[fss_basic_read_parameter_name_e].values.array[position_name] > main->parameters.array[fss_basic_read_parameter_depth_e].values.array[i + 1]) {
            break;
          }

          data->depths.array[i].index_name = main->parameters.array[fss_basic_read_parameter_name_e].values.array[position_name];

          if (main->parameters.array[fss_basic_read_parameter_trim_e].result & f_console_result_found_e) {
            status = f_rip_dynamic(data->argv[data->depths.array[i].index_name], &data->depths.array[i].value_name);
          }
          else {
            status = f_string_dynamic_append(data->argv[data->depths.array[i].index_name], &data->depths.array[i].value_name);
          }

          if (F_status_is_error(status)) {
            fll_error_print(main->error, F_status_set_fine(status), (main->parameters.array[fss_basic_read_parameter_trim_e].result & f_console_result_found_e) ? "f_rip_dynamic" : "f_string_dynamic_append", fll_error_file_flag_fallback_e);

            return status;
          }
        } // for
      }
    } // for

    for (f_array_length_t i = 0; i < data->depths.used; ++i) {

      for (f_array_length_t j = i + 1; j < data->depths.used; ++j) {

        if (!((++main->signal_check) % fss_basic_read_signal_check_d)) {
          if (fll_program_standard_signal_received(&main->program)) {
            fll_program_print_signal_received(main->warning, main->signal_received);

            return F_status_set_error(F_interrupt);
          }

          main->signal_check = 0;
        }

        if (data->depths.array[i].depth == data->depths.array[j].depth) {
          if (main->error.verbosity > f_console_verbosity_quiet_e) {
            f_file_stream_lock(main->error.to);

            fl_print_format("%r%[%QThe value '%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%ul%]", main->error.to, main->error.notable, data->depths.array[i].depth, main->error.notable);
            fl_print_format("%[' may only be specified once for the parameter '%]", main->error.to, main->error.context, main->error.context);
            fl_print_format("%[%r%r%]", main->error.to, main->error.notable, f_console_symbol_long_normal_s, fss_basic_read_long_depth_s, main->error.notable);
            fl_print_format("%['.%]%r", main->error.to, main->error.context, main->error.context, f_string_eol_s);

            f_file_stream_unlock(main->error.to);
          }

          return F_status_set_error(F_parameter);
        }

        if (data->depths.array[i].depth > data->depths.array[j].depth) {
          if (main->error.verbosity > f_console_verbosity_quiet_e) {
            f_file_stream_lock(main->error.to);

            fl_print_format("%r%[%QThe parameter '%]", main->error.to, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%r%r%]", main->error.to, main->error.notable, f_console_symbol_long_normal_s, fss_basic_read_long_depth_s, main->error.notable);
            fl_print_format("%[' may not have the value '%]", main->error.to, main->error.context, main->error.context);
            fl_print_format("%[%ul%]", main->error.to, main->error.notable, data->depths.array[i].depth, main->error.notable);
            fl_print_format("%[' before the value '%]", main->error.to, main->error.context, main->error.context);
            fl_print_format("%[%ul%]", main->error.to, main->error.notable, data->depths.array[j].depth, main->error.notable);
            fl_print_format("%['.%]%r", main->error.to, main->error.context, main->error.context, f_string_eol_s);

            f_file_stream_unlock(main->error.to);
          }

          return F_status_set_error(F_parameter);
        }
      } // for
    } // for

    return F_none;
  }
#endif // _di_fss_basic_read_depth_process_

#ifndef _di_fss_basic_read_file_identify_
  f_string_static_t fss_basic_read_file_identify(const f_array_length_t at, const fss_basic_read_files_t files) {

    for (f_array_length_t i = 0; i < files.used; ++i) {

      if (at >= files.array[i].range.start && at <= files.array[i].range.stop) {
        return files.array[i].name;
      }
    } // for

    // When stopped after the end of the buffer, the last file in the list is the correct file.
    if (at > files.array[files.used - 1].range.stop) {
      return files.array[files.used - 1].name;
    }

    return f_string_empty_s;
  }
#endif // _di_fss_basic_read_file_identify_

#ifndef _di_fss_basic_read_load_
  f_status_t fss_basic_read_load(fll_program_data_t * const main, fss_basic_read_data_t * const data) {

    f_state_t state = macro_f_state_t_initialize_1(fss_basic_read_common_allocation_large_d, fss_basic_read_common_allocation_small_d, 0, 0, &fll_program_standard_signal_handle, 0, (void *) main, 0);
    f_string_range_t input = macro_f_string_range_t_initialize2(data->buffer.used);

    data->delimits.used = 0;
    data->quotes.used = 0;

    const f_status_t status = fll_fss_basic_read(data->buffer, state, &input, &data->objects, &data->contents, &data->quotes, &data->delimits, 0);

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_interrupt) {
        fll_program_print_signal_received(main->warning, main->signal_received);

        return status;
      }

      const f_string_static_t file_name = fss_basic_read_file_identify(input.start, data->files);

      fll_error_file_print(main->error, F_status_set_fine(status), "fll_fss_basic_read", fll_error_file_flag_fallback_e, file_name, f_file_operation_process_s, fll_error_file_type_file_e);

      return status;
    }

    if (status == F_data_not_stop || status == F_data_not_eos) {
      if (data->option & fss_basic_read_data_option_total_d) return F_none;

      return F_status_set_warning(status);
    }

    return F_none;
  }
#endif // _di_fss_basic_read_load_

#ifndef _di_fss_basic_read_load_number_
  f_status_t fss_basic_read_load_number(fll_program_data_t * const main, fss_basic_read_data_t * const data, const f_array_length_t parameter, const f_string_static_t name, f_number_unsigned_t *number) {

    if (main->parameters.array[parameter].result & f_console_result_value_e) {
      const f_array_length_t index = main->parameters.array[parameter].values.array[main->parameters.array[parameter].values.used - 1];

      const f_status_t status = fl_conversion_dynamic_to_unsigned_detect(fl_conversion_data_base_10_c, data->argv[index], number);

      if (F_status_is_error(status)) {
        fll_error_parameter_integer_print(main->error, F_status_set_fine(status), "fl_conversion_dynamic_to_unsigned_detect", F_true, name, data->argv[index]);

        return status;
      }

      return F_true;
    }

    return F_false;
  }
#endif // _di_fss_basic_read_load_number_

#ifndef _di_fss_basic_read_process_
  f_status_t fss_basic_read_process(fll_program_data_t * const main, fss_basic_read_data_t * const data) {

    f_status_t status = fss_basic_read_process_option(main, data);
    if (F_status_is_error(status)) return status;

    // This standard does not support multiple content groups.
    if ((data->option & fss_basic_read_data_option_select_d) && data->select) {
      if (main->parameters.array[fss_basic_read_parameter_total_e].result & f_console_result_found_e) {
        f_file_stream_lock(main->output.to);

        fss_basic_read_print_zero(main);

        f_file_stream_unlock(main->output.to);
      }

      return F_none;
    }

    status = fss_basic_read_load(main, data);
    if (F_status_is_error(status)) return status;

    bool names[data->objects.used];

    status = fss_basic_read_process_name(data, names);
    if (F_status_is_error(status)) return status;

    if (data->depths.array[0].index_at) {
      return fss_basic_read_process_at(main, data, names);
    }

    if (data->option & fss_basic_read_data_option_columns_d) {
      return fss_basic_read_process_columns(main, data, names);
    }

    if (data->option & fss_basic_read_data_option_total_d) {
      return fss_basic_read_process_total(main, data, names);
    }

    if (data->option & fss_basic_read_data_option_line_d) {
      return fss_basic_read_process_line(main, data, names);
    }

    f_array_lengths_t except_none = f_array_lengths_t_initialize;
    f_array_lengths_t *delimits = fss_basic_read_delimit_object_is(data, 0) ? &data->delimits : &except_none;

    for (f_array_length_t i = 0; i < data->contents.used; ++i) {

      if (!names[i]) continue;

      fss_basic_read_print_at(main, i, *delimits, except_none, data);
    } // for

    return F_none;
  }
#endif // _di_fss_basic_read_process_

#ifndef _di_fss_basic_read_process_at_
  f_status_t fss_basic_read_process_at(fll_program_data_t * const main, fss_basic_read_data_t * const data, bool names[]) {

    if (data->depths.array[0].value_at >= data->objects.used) {
      if (data->option & (fss_basic_read_data_option_columns_d | fss_basic_read_data_option_total_d)) {
        f_file_stream_lock(main->output.to);

        fss_basic_read_print_zero(main);

        f_file_stream_unlock(main->output.to);
      }

      return F_none;
    }

    // This standard only has one line per Content; therefore, any line value greater than 0 equates to no line to print.
    if (data->option & fss_basic_read_data_option_line_d) {
      if (data->line) {
        if (data->option & fss_basic_read_data_option_total_d) {
          f_file_stream_lock(main->output.to);

          fss_basic_read_print_zero(main);

          f_file_stream_unlock(main->output.to);
        }

        return F_none;
      }
    }

    f_array_lengths_t except_none = f_array_lengths_t_initialize;
    f_array_lengths_t *delimits = fss_basic_read_delimit_object_is(data, 0) ? &data->delimits : &except_none;

    f_array_length_t at = 0;

    for (f_array_length_t i = 0; i < data->objects.used; ++i) {

      if (!names[i]) continue;

      if (!((++main->signal_check) % fss_basic_read_signal_check_d)) {
        if (fll_program_standard_signal_received(&main->program)) {
          fll_program_print_signal_received(main->warning, main->signal_received);

          return F_status_set_error(F_interrupt);
        }

        main->signal_check = 0;
      }

      if (at == data->depths.array[0].value_at) {
        if (data->option & fss_basic_read_data_option_line_d) {

          // This standard only supports one line per Object so when using "--at", the only valid line is line 0.
          if (data->line) break;

          if (data->option & fss_basic_read_data_option_total_d) {
            f_file_stream_lock(main->output.to);

            fss_basic_read_print_one(main);

            f_file_stream_unlock(main->output.to);
          }
          else {
            fss_basic_read_print_at(main, i, *delimits, except_none, data);
          }
        }
        else if (data->option & fss_basic_read_data_option_columns_d) {
          fll_print_format("%ul%r", main->output.to, data->contents.array[i].used, f_string_eol_s);
        }
        else if (data->option & fss_basic_read_data_option_total_d) {
          f_file_stream_lock(main->output.to);

          if (data->contents.array[i].used) {
            fss_basic_read_print_one(main);
          }
          else {
            fss_basic_read_print_zero(main);
          }

          f_file_stream_unlock(main->output.to);
        }
        else {
          fss_basic_read_print_at(main, i, *delimits, except_none, data);
        }

        return F_none;
      }

      ++at;
    } // for

    if (data->option & fss_basic_read_data_option_total_d) {
      f_file_stream_lock(main->output.to);

      fss_basic_read_print_zero(main);

      f_file_stream_unlock(main->output.to);
    }

    return F_none;
  }
#endif // _di_fss_basic_read_process_at_

#ifndef _di_fss_basic_read_process_columns_
  f_status_t fss_basic_read_process_columns(fll_program_data_t * const main, fss_basic_read_data_t * const data, bool names[]) {

    if (!(data->option & fss_basic_read_data_option_content_d)) {
      f_file_stream_lock(main->output.to);

      fss_basic_read_print_zero(main);

      f_file_stream_unlock(main->output.to);

      return F_none;
    }

    f_array_length_t max = 0;

    for (f_array_length_t at = 0; at < data->contents.used; ++at) {

      if (!names[at]) continue;

      if (!((++main->signal_check) % fss_basic_read_signal_check_d)) {
        if (fll_program_standard_signal_received(&main->program)) {
          fll_program_print_signal_received(main->warning, main->signal_received);

          return F_status_set_error(F_interrupt);
        }

        main->signal_check = 0;
      }

      if (data->contents.array[at].used > max) {
        max = data->contents.array[at].used;
      }
    } // for

    fll_print_format("%ul%r", main->output.to, max, f_string_eol_s);

    return F_none;
  }
#endif // _di_fss_basic_read_process_columns_

#ifndef _di_fss_basic_read_process_line_
  f_status_t fss_basic_read_process_line(fll_program_data_t * const main, fss_basic_read_data_t * const data, bool names[]) {

    f_array_lengths_t except_none = f_array_lengths_t_initialize;
    f_array_lengths_t *delimits = fss_basic_read_delimit_object_is(data, 0) ? &data->delimits : &except_none;

    f_array_length_t line = 0;

    for (f_array_length_t i = 0; i < data->contents.used; ++i) {

      if (!names[i]) continue;

      if (!((++main->signal_check) % fss_basic_read_signal_check_d)) {
        if (fll_program_standard_signal_received(&main->program)) {
          fll_program_print_signal_received(main->warning, main->signal_received);

          return F_status_set_error(F_interrupt);
        }

        main->signal_check = 0;
      }

      if (!(data->option & fss_basic_read_data_option_object_d) && (data->option & fss_basic_read_data_option_content_d)) {
        if (!data->contents.array[i].used) {
          if (data->option & fss_basic_read_data_option_empty_d) {
            if (line == data->line) {
              f_file_stream_lock(main->output.to);

              fss_basic_read_print_set_end(main);

              f_file_stream_unlock(main->output.to);

              break;
            }

            ++line;
          }

          continue;
        }
      }

      if (line == data->line) {
        fss_basic_read_print_at(main, i, *delimits, except_none, data);

        break;
      }

      ++line;
    } // for

    return F_none;
  }
#endif // _di_fss_basic_read_process_line_

#ifndef _di_fss_basic_read_process_name_
  f_status_t fss_basic_read_process_name(fss_basic_read_data_t * const data, bool names[]) {

    f_array_lengths_t except_none = f_array_lengths_t_initialize;

    if (data->depths.array[0].index_name) {
      f_array_length_t i = 0;

      memset(names, F_false, sizeof(bool) * data->objects.used);

      if (data->option & fss_basic_read_data_option_trim_d) {
        for (i = 0; i < data->objects.used; ++i) {

          if (f_compare_dynamic_partial_except_trim_dynamic(data->depths.array[0].value_name, data->buffer, data->objects.array[i], except_none, data->delimits) == F_equal_to) {
            names[i] = F_true;
          }
        } // for
      }
      else {
        for (i = 0; i < data->objects.used; ++i) {

           if (f_compare_dynamic_partial_except_dynamic(data->depths.array[0].value_name, data->buffer, data->objects.array[i], except_none, data->delimits) == F_equal_to) {
            names[i] = F_true;
          }
        } // for
      }
    }
    else {
      memset(names, F_true, sizeof(bool) * data->objects.used);
    }

    return F_none;
  }
#endif // _di_fss_basic_read_process_name_

#ifndef _di_fss_basic_read_process_option_
  f_status_t fss_basic_read_process_option(fll_program_data_t * const main, fss_basic_read_data_t * const data) {

    f_status_t status = F_none;

    if (main->parameters.array[fss_basic_read_parameter_at_e].result & f_console_result_value_e) {
      data->option |= fss_basic_read_data_option_at_d;
    }

    if (main->parameters.array[fss_basic_read_parameter_columns_e].result & f_console_result_found_e) {
      data->option |= fss_basic_read_data_option_columns_d;
    }

    if (main->parameters.array[fss_basic_read_parameter_content_e].result & f_console_result_found_e) {
      data->option |= fss_basic_read_data_option_content_d;
    }

    if (main->parameters.array[fss_basic_read_parameter_empty_e].result & f_console_result_found_e) {
      data->option |= fss_basic_read_data_option_empty_d;
    }

    if (main->parameters.array[fss_basic_read_parameter_line_e].result & f_console_result_value_e) {
      data->option |= fss_basic_read_data_option_line_d;

      status = fss_basic_read_load_number(main, data, fss_basic_read_parameter_line_e, fss_basic_read_long_line_s, &data->line);
      if (F_status_is_error(status)) return status;
    }

    if (main->parameters.array[fss_basic_read_parameter_name_e].result & f_console_result_value_e) {
      data->option |= fss_basic_read_data_option_name_d;
    }

    if (main->parameters.array[fss_basic_read_parameter_object_e].result & f_console_result_found_e) {
      data->option |= fss_basic_read_data_option_object_d;
    }

    if (main->parameters.array[fss_basic_read_parameter_original_e].result & f_console_result_found_e) {
      data->option |= fss_basic_read_data_option_original_d;
    }

    if (main->parameters.array[fss_basic_read_parameter_select_e].result & f_console_result_value_e) {
      data->option |= fss_basic_read_data_option_select_d;

      status = fss_basic_read_load_number(main, data, fss_basic_read_parameter_select_e, fss_basic_read_long_select_s, &data->select);
      if (F_status_is_error(status)) return status;
    }

    if (main->parameters.array[fss_basic_read_parameter_total_e].result & f_console_result_found_e) {
      data->option |= fss_basic_read_data_option_total_d;
    }

    if (main->parameters.array[fss_basic_read_parameter_trim_e].result & f_console_result_found_e) {
      data->option |= fss_basic_read_data_option_trim_d;
    }

    // Default to content if neither Object nor Content is explicitly requested.
    if (!(data->option & (fss_basic_read_data_option_content_d | fss_basic_read_data_option_object_d))) {
      data->option |= fss_basic_read_data_option_content_d;
    }

    return F_none;
  }
#endif // _di_fss_basic_read_process_option_

#ifndef _di_fss_basic_read_process_total_
  f_status_t fss_basic_read_process_total(fll_program_data_t * const main, fss_basic_read_data_t * const data, bool names[]) {

    f_array_length_t total = 0;

    for (f_array_length_t i = 0; i < data->objects.used; ++i) {

      if (!names[i]) continue;

      if (!((++main->signal_check) % fss_basic_read_signal_check_d)) {
        if (fll_program_standard_signal_received(&main->program)) {
          fll_program_print_signal_received(main->warning, main->signal_received);

          return F_status_set_error(F_interrupt);
        }

        main->signal_check = 0;
      }

      if (!(data->option & fss_basic_read_data_option_object_d) && data->option & fss_basic_read_data_option_content_d) {
        if (!(data->contents.array[i].used || (data->option & fss_basic_read_data_option_empty_d))) {
          continue;
        }
      }

      ++total;
    } // for

    f_file_stream_lock(main->output.to);

    if (data->option & fss_basic_read_data_option_line_d) {
      if (data->line < total) {
        fss_basic_read_print_one(main);
      }
      else {
        fss_basic_read_print_zero(main);
      }
    }
    else {
      fl_print_format("%ul%r", main->output.to, total, f_string_eol_s);
    }

    f_file_stream_unlock(main->output.to);

    return F_none;
  }
#endif // _di_fss_basic_read_process_total_

#ifdef __cplusplus
} // extern "C"
#endif
