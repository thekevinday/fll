#include "fss_basic_list_read.h"
#include "private-common.h"
#include "private-print.h"
#include "private-read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_basic_list_read_delimit_content_is_
  f_status_t fss_basic_list_read_delimit_content_is(const f_array_length_t depth, fss_basic_list_read_data_t * const data) {

    if (data->delimit_mode == fss_basic_list_read_delimit_mode_none_e) {
      return F_false;
    }

    if (data->delimit_mode == fss_basic_list_read_delimit_mode_all_e) {
      return F_true;
    }

    if (depth < data->delimit_depth) {
      return data->delimit_mode == fss_basic_list_read_delimit_mode_content_lesser_e;
    }

    if (depth == data->delimit_depth) {
      return F_true;
    }

    return data->delimit_mode == fss_basic_list_read_delimit_mode_content_greater_e;
  }
#endif // _di_fss_basic_list_read_delimit_content_is_

#ifndef _di_fss_basic_list_read_delimit_object_is_
  f_status_t fss_basic_list_read_delimit_object_is(const f_array_length_t depth, fss_basic_list_read_data_t * const data) {

    switch (data->delimit_mode) {
      case fss_basic_list_read_delimit_mode_none_e:
      case fss_basic_list_read_delimit_mode_content_e:
      case fss_basic_list_read_delimit_mode_content_greater_e:
      case fss_basic_list_read_delimit_mode_content_lesser_e:
        return F_false;

      case fss_basic_list_read_delimit_mode_all_e:
      case fss_basic_list_read_delimit_mode_content_object_e:
      case fss_basic_list_read_delimit_mode_content_greater_object_e:
      case fss_basic_list_read_delimit_mode_content_lesser_object_e:
      case fss_basic_list_read_delimit_mode_object_e:
        return F_true;

      default:
        break;
    }

    return depth == data->delimit_depth || data->delimit_mode == fss_basic_list_read_delimit_mode_content_lesser_e;
  }
#endif // _di_fss_basic_list_read_delimit_object_is_

#ifndef _di_fss_basic_list_read_depth_process_
  f_status_t fss_basic_list_read_depth_process(fll_program_data_t * const main, const f_console_arguments_t *arguments, fss_basic_list_read_data_t *data) {

    f_status_t status = F_none;

    {
      f_array_length_t depth_size = 1;

      if (main->parameters.array[fss_basic_list_read_parameter_depth_e].result == f_console_result_additional_e) {
        depth_size = main->parameters.array[fss_basic_list_read_parameter_depth_e].values.used;
      }

      if (depth_size > data->depths.size) {
        status = fss_basic_list_read_depths_resize(depth_size, &data->depths);

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "fss_basic_list_read_depths_resize", F_true);

          return status;
        }
      }

      data->depths.used = depth_size;
    }

    f_array_length_t position_depth = 0;
    f_array_length_t position_at = 0;
    f_array_length_t position_name = 0;
    uint16_t signal_check = 0;

    for (f_array_length_t i = 0; i < data->depths.used; ++i) {

      if (!((++signal_check) % fss_basic_list_read_signal_check_d)) {
        if (fss_basic_list_read_signal_received(main)) {
          return F_status_set_error(F_interrupt);
        }

        signal_check = 0;
      }

      data->depths.array[i].depth = 0;
      data->depths.array[i].index_at = 0;
      data->depths.array[i].index_name = 0;
      data->depths.array[i].value_at = 0;

      macro_f_string_dynamic_t_clear(data->depths.array[i].value_name);

      if (!main->parameters.array[fss_basic_list_read_parameter_depth_e].values.used) {
        position_depth = 0;
      }
      else {
        position_depth = main->parameters.array[fss_basic_list_read_parameter_depth_e].values.array[i];

        const f_string_range_t range = macro_f_string_range_t_initialize(strlen(argv[position_depth]));

        status = fl_conversion_string_to_number_unsigned(argv[position_depth].string, range, &data->depths.array[i].depth);

        if (F_status_is_error(status)) {
          fll_error_parameter_integer_print(main->error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, fss_basic_list_read_long_depth_s, argv[position_depth]);

          return status;
        }
      }

      if (main->parameters.array[fss_basic_list_read_parameter_at_e].result == f_console_result_additional_e) {
        for (; position_at < main->parameters.array[fss_basic_list_read_parameter_at_e].values.used; ++position_at) {

          if (main->parameters.array[fss_basic_list_read_parameter_at_e].values.array[position_at] < position_depth) {
            continue;
          }

          if (i + 1 < data->depths.used && main->parameters.array[fss_basic_list_read_parameter_at_e].values.array[position_at] > main->parameters.array[fss_basic_list_read_parameter_depth_e].values.array[i + 1]) {
            break;
          }

          data->depths.array[i].index_at = main->parameters.array[fss_basic_list_read_parameter_at_e].values.array[position_at];

          const f_string_range_t range = macro_f_string_range_t_initialize(argv[data->depths.array[i].index_at].used);

          status = fl_conversion_string_to_number_unsigned(argv[data->depths.array[i].index_at].string, range, &data->depths.array[i].value_at);

          if (F_status_is_error(status)) {
            fll_error_parameter_integer_print(main->error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, fss_basic_list_read_long_at_s, argv[data->depths.array[i].index_at]);

            return status;
          }
        } // for
      }

      if (main->parameters.array[fss_basic_list_read_parameter_name_e].result == f_console_result_additional_e) {
        for (; position_name < main->parameters.array[fss_basic_list_read_parameter_name_e].values.used; ++position_name) {

          if (main->parameters.array[fss_basic_list_read_parameter_name_e].values.array[position_name] < position_depth) {
            continue;
          }

          if (i + 1 < data->depths.used && main->parameters.array[fss_basic_list_read_parameter_name_e].values.array[position_name] > main->parameters.array[fss_basic_list_read_parameter_depth_e].values.array[i + 1]) {
            break;
          }

          data->depths.array[i].index_name = main->parameters.array[fss_basic_list_read_parameter_name_e].values.array[position_name];

          if (main->parameters.array[fss_basic_list_read_parameter_trim_e].result == f_console_result_found_e) {
            status = fl_string_dynamic_rip(argv[data->depths.array[i].index_name], &data->depths.array[i].value_name);
          }
          else {
            status = f_string_dynamic_append(argv[data->depths.array[i].index_name], &data->depths.array[i].value_name);
          }

          if (F_status_is_error(status)) {
            fll_error_print(main->error, F_status_set_fine(status), main->parameters.array[fss_basic_list_read_parameter_trim_e].result == f_console_result_found_e ? "fl_string_dynamic_rip" : "f_string_dynamic_append", F_true);

            return status;
          }
        } // for
      }
    } // for

    for (f_array_length_t i = 0; i < data->depths.used; ++i) {

      for (f_array_length_t j = i + 1; j < data->depths.used; ++j) {

        if (!((++signal_check) % fss_basic_list_read_signal_check_d)) {
          if (fss_basic_list_read_signal_received(main)) {
            return F_status_set_error(F_interrupt);
          }

          signal_check = 0;
        }

        if (data->depths.array[i].depth == data->depths.array[j].depth) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            flockfile(main->error.to.stream);

            fl_print_format("%r%[%QThe value '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%ul%]", main->error.to.stream, main->error.notable, data->depths.array[i].depth, main->error.notable);
            fl_print_format("%[' may only be specified once for the parameter '%]", main->error.to.stream, main->error.context, main->error.context);
            fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_basic_list_read_long_depth_s, main->error.notable);
            fl_print_format("%['.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

            funlockfile(main->error.to.stream);
          }

          return F_status_set_error(F_parameter);
        }

        if (data->depths.array[i].depth > data->depths.array[j].depth) {
          if (main->error.verbosity != f_console_verbosity_quiet_e) {
            flockfile(main->error.to.stream);

            fl_print_format("%r%[%QThe parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_basic_list_read_long_depth_s, main->error.notable);
            fl_print_format("%[' may not have the value '%]", main->error.to.stream, main->error.context, main->error.context);
            fl_print_format("%[%ul%]", main->error.to.stream, main->error.notable, data->depths.array[i].depth, main->error.notable);
            fl_print_format("%[' before the value '%]", main->error.to.stream, main->error.context, main->error.context);
            fl_print_format("%[%ul%]", main->error.to.stream, main->error.notable, data->depths.array[j].depth, main->error.notable);
            fl_print_format("%['.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

            funlockfile(main->error.to.stream);
          }

          return F_status_set_error(F_parameter);
        }
      } // for
    } // for

    return F_none;
  }
#endif // _di_fss_basic_list_read_depth_process_

#ifndef _di_fss_basic_list_read_file_identify_
  f_string_t fss_basic_list_read_file_identify(const f_array_length_t at, const fss_basic_list_read_files_t files) {

    for (f_array_length_t i = 0; i < files.used; ++i) {

      if (at >= files.array[i].range.start && at <= files.array[i].range.stop) {
        return files.array[i].name;
      }
    } // for

    // When stopped after the end of the buffer, the last file in the list is the correct file.
    if (at > files.array[files.used - 1].range.stop) {
      return files.array[files.used - 1].name;
    }

    return "";
  }
#endif // _di_fss_basic_list_read_file_identify_

#ifndef _di_fss_basic_list_read_load_
  f_status_t fss_basic_list_read_load(fll_program_data_t * const main, fss_basic_list_read_data_t *data) {

    f_state_t state = macro_f_state_t_initialize(fss_basic_list_common_allocation_large_d, fss_basic_list_read_common_allocation_small_d, 0, 0, 0, 0, 0);
    f_string_range_t input = macro_f_string_range_t_initialize(data->buffer.used);

    data->delimits_object.used = 0;
    data->delimits_content.used = 0;

    const f_status_t status = fll_fss_basic_list_read(data->buffer, state, &input, &data->objects, &data->contents, &data->delimits_object, &data->delimits_content, &data->comments);

    if (F_status_is_error(status)) {
      const f_string_t file_name = fss_basic_list_read_file_identify(input.start, data->files);

      fll_error_file_print(main->error, F_status_set_fine(status), "fll_fss_basic_list_read", F_true, file_name, f_file_operation_process_s, fll_error_file_type_file_e);

      return status;
    }

    if (status == F_data_not_stop || status == F_data_not_eos) {
      if (data->option & fss_basic_list_read_data_option_total_d) {
        flockfile(main->output.to.stream);

        fss_basic_list_read_print_zero(main);

        funlockfile(main->output.to.stream);

        return F_none;
      }

      return F_status_set_warning(status);
    }

    return F_none;
  }
#endif // _di_fss_basic_list_read_load_

#ifndef _di_fss_basic_list_read_load_number_
  f_status_t fss_basic_list_read_load_number(fll_program_data_t * const main, const f_array_length_t parameter, const f_string_t name, const f_console_arguments_t *arguments, f_number_unsigned_t *number) {

    if (main->parameters.array[parameter].result == f_console_result_additional_e) {
      const f_array_length_t index = main->parameters.array[parameter].values.array[main->parameters.array[parameter].values.used - 1];
      const f_string_range_t range = macro_f_string_range_t_initialize(main->argv[index].used);

      const f_status_t status = fl_conversion_string_to_number_unsigned(main->argv[index].string, range, number);

      if (F_status_is_error(status)) {
        fll_error_parameter_integer_print(main->error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, name, main->argv[index]);

        return status;
      }

      return F_true;
    }

    return F_false;
  }
#endif // _di_fss_basic_list_read_load_number_

#ifndef _di_fss_basic_list_read_process_
  f_status_t fss_basic_list_read_process(fll_program_data_t * const main, const f_console_arguments_t *arguments, fss_basic_list_read_data_t *data) {

    f_status_t status = fss_basic_list_read_process_option(main, arguments, data);
    if (F_status_is_error(status)) return status;

    // This standard does not support multiple content groups.
    if ((data->option & fss_basic_list_read_data_option_select_d) && data->select) {
      if (main->parameters.array[fss_basic_list_read_parameter_total_e].result == f_console_result_found_e) {
        flockfile(main->output.to.stream);

        fss_basic_list_read_print_zero(main);

        funlockfile(main->output.to.stream);
      }

      return F_none;
    }

    status = fss_basic_list_read_load(main, data);
    if (F_status_is_error(status)) return status;

    bool names[data->objects.used];

    status = fss_basic_list_read_process_name(data, names);
    if (F_status_is_error(status)) return status;

    if (data->depths.array[0].index_at) {
      return fss_basic_list_read_process_at(main, data, names);
    }

    if (data->option & fss_basic_list_read_data_option_columns_d) {
      return fss_basic_list_read_process_columns(main, data, names);
    }

    if (data->option & fss_basic_list_read_data_option_total_d) {
      return fss_basic_list_read_process_total(main, data, names);
    }

    if (data->option & fss_basic_list_read_data_option_line_d) {
      return fss_basic_list_read_process_line(main, data, names);
    }

    f_array_lengths_t except_none = f_array_lengths_t_initialize;
    f_array_lengths_t *delimits_object = fss_basic_list_read_delimit_object_is(0, data) ? &data->delimits_object : &except_none;
    f_array_lengths_t *delimits_content = fss_basic_list_read_delimit_content_is(0, data) ? &data->delimits_content : &except_none;
    uint16_t signal_check = 0;

    if (data->option & fss_basic_list_read_data_option_raw_d) {
      delimits_object = &except_none;
      delimits_content = &except_none;
    }

    for (f_array_length_t i = 0; i < data->contents.used; ++i) {

      if (!names[i]) continue;

      if (!((++signal_check) % fss_basic_list_read_signal_check_d)) {
        if (fss_basic_list_read_signal_received(main)) {
          return F_status_set_error(F_interrupt);
        }

        signal_check = 0;
      }

      fss_basic_list_read_print_at(main, i, *delimits_object, *delimits_content, data);
    } // for

    return F_none;
  }
#endif // _di_fss_basic_list_read_process_

#ifndef _di_fss_basic_list_read_process_at_
  f_status_t fss_basic_list_read_process_at(fll_program_data_t * const main, fss_basic_list_read_data_t *data, bool names[]) {

    if (data->depths.array[0].value_at >= data->objects.used) {
      if (data->option & (fss_basic_list_read_data_option_columns_d | fss_basic_list_read_data_option_total_d)) {
        flockfile(main->output.to.stream);

        fss_basic_list_read_print_zero(main);

        funlockfile(main->output.to.stream);
      }

      return F_none;
    }

    f_array_lengths_t except_none = f_array_lengths_t_initialize;
    f_array_lengths_t *delimits_object = fss_basic_list_read_delimit_object_is(0, data) ? &data->delimits_object : &except_none;
    f_array_lengths_t *delimits_content = fss_basic_list_read_delimit_content_is(0, data) ? &data->delimits_content : &except_none;

    if (data->option & fss_basic_list_read_data_option_raw_d) {
      delimits_object = &except_none;
      delimits_content = &except_none;
    }

    f_array_length_t at = 0;
    f_status_t status = F_none;
    uint16_t signal_check = 0;

    for (f_array_length_t i = 0; i < data->objects.used; ++i) {

      if (!names[i]) continue;

      if (!((++signal_check) % fss_basic_list_read_signal_check_d)) {
        if (fss_basic_list_read_signal_received(main)) {
          return F_status_set_error(F_interrupt);
        }

        signal_check = 0;
      }

      if (at == data->depths.array[0].value_at) {
        if (data->option & fss_basic_list_read_data_option_line_d) {
          f_array_length_t line = 0;

          status = fss_basic_list_read_process_at_line(main, i, *delimits_object, *delimits_content, data, &line);
          if (status == F_success) return F_none;
        }
        else if (data->option & fss_basic_list_read_data_option_columns_d) {
          fll_print_format("%ul%r", main->output.to.stream, data->contents.array[i].used, f_string_eol_s);
        }
        else if (data->option & fss_basic_list_read_data_option_total_d) {
          flockfile(main->output.to.stream);

          if (data->contents.array[i].used) {
            fss_basic_list_read_print_one(main);
          }
          else {
            fss_basic_list_read_print_zero(main);
          }

          funlockfile(main->output.to.stream);
        }
        else {
          fss_basic_list_read_print_at(main, i, *delimits_object, *delimits_content, data);
        }

        return F_none;
      }

      ++at;
    } // for

    if (data->option & fss_basic_list_read_data_option_total_d) {
      flockfile(main->output.to.stream);

      fss_basic_list_read_print_zero(main);

      funlockfile(main->output.to.stream);
    }

    return F_none;
  }
#endif // _di_fss_basic_list_read_process_at_

#ifndef _di_fss_basic_list_read_process_at_line_
  f_status_t fss_basic_list_read_process_at_line(fll_program_data_t * const main, const f_array_length_t at, const f_array_lengths_t delimits_object, const f_array_lengths_t delimits_content, fss_basic_list_read_data_t *data, f_array_length_t *line) {

    if (data->option & fss_basic_list_read_data_option_object_d) {
      if (*line == data->line) {
        flockfile(main->output.to.stream);

        if (data->option & fss_basic_list_read_data_option_total_d) {
          fss_basic_list_read_print_one(main);
        }
        else {
          fss_basic_list_read_print_at_object(main, data, at, delimits_object);
        }

        funlockfile(main->output.to.stream);

        return F_success;
      }

      ++(*line);
    }

    // There is only a single Content column for this standard.
    if (data->option & fss_basic_list_read_data_option_content_d) {
      if (!data->contents.array[at].used) {
        return F_none;
      }

      f_string_range_t range = f_string_range_t_initialize;
      f_array_length_t i = 0;
      uint16_t signal_check = 0;

      range.start = data->contents.array[at].array[0].start;
      range.stop = data->contents.array[at].array[0].stop;

      // This content has no data, do not even check "include empty" because it cannot be counted as a line.
      if (range.start > range.stop) {
        return F_none;
      }

      for (i = range.start; i <= range.stop; ++i) {

        if (!((++signal_check) % fss_basic_list_read_signal_check_d)) {
          if (fss_basic_list_read_signal_received(main)) {
            return F_status_set_error(F_interrupt);
          }

          signal_check = 0;
        }

        if (data->buffer.string[i] == f_string_eol_s.string[0]) {
          if (*line == data->line) {
            range.stop = i;

            flockfile(main->output.to.stream);

            if (data->option & fss_basic_list_read_data_option_total_d) {
              fss_basic_list_read_print_one(main);
            }
            else {
              f_print_except_in_dynamic_partial(data->buffer, range, delimits_content, data->comments, main->output.to.stream);
            }

            funlockfile(main->output.to.stream);

            return F_success;
          }

          range.start = i + 1;

          if (i <= range.stop) {
            ++(*line);
          }
        }
      } // for

      // If Content does not end with a newline, it still must be treated as the last line.
      if (data->buffer.string[range.stop] != f_string_eol_s.string[0]) {
        ++(*line);

        if (*line == data->line) {
          flockfile(main->output.to.stream);

          if (data->option & fss_basic_list_read_data_option_total_d) {
            fss_basic_list_read_print_one(main);
          }
          else {
            range.stop = data->contents.array[at].array[0].stop;

            f_print_except_in_dynamic_partial(data->buffer, range, delimits_content, data->comments, main->output.to.stream);
            f_print_dynamic_raw(f_string_eol_s, main->output.to.stream);
          }

          funlockfile(main->output.to.stream);

          return F_success;
        }
      }
    }

    return F_none;
  }
#endif // _di_fss_basic_list_read_process_at_line_

#ifndef _di_fss_basic_list_read_process_columns_
  f_status_t fss_basic_list_read_process_columns(fll_program_data_t * const main, fss_basic_list_read_data_t *data, bool names[]) {

    if (!(data->option & fss_basic_list_read_data_option_content_d)) {
      flockfile(main->output.to.stream);

      fss_basic_list_read_print_zero(main);

      funlockfile(main->output.to.stream);

      return F_none;
    }

    f_array_length_t max = 0;
    uint16_t signal_check = 0;

    for (f_array_length_t at = 0; at < data->contents.used; ++at) {

      if (!names[at]) continue;

      if (!((++signal_check) % fss_basic_list_read_signal_check_d)) {
        if (fss_basic_list_read_signal_received(main)) {
          return F_status_set_error(F_interrupt);
        }

        signal_check = 0;
      }

      if (data->contents.array[at].used > max) {
        max = data->contents.array[at].used;
      }
    } // for

    fll_print_format("%ul%r", main->output.to.stream, max, f_string_eol_s);

    return F_none;
  }
#endif // _di_fss_basic_list_read_process_columns_

#ifndef _di_fss_basic_list_read_process_line_
  f_status_t fss_basic_list_read_process_line(fll_program_data_t * const main, fss_basic_list_read_data_t *data, bool names[]) {

    f_array_lengths_t except_none = f_array_lengths_t_initialize;
    f_array_lengths_t *delimits_object = fss_basic_list_read_delimit_object_is(0, data) ? &data->delimits_object : &except_none;
    f_array_lengths_t *delimits_content = fss_basic_list_read_delimit_content_is(0, data) ? &data->delimits_content : &except_none;

    if (data->option & fss_basic_list_read_data_option_raw_d) {
      delimits_object = &except_none;
      delimits_content = &except_none;
    }

    f_array_length_t line = 0;
    f_status_t status = F_none;
    uint16_t signal_check = 0;

    for (f_array_length_t i = 0; i < data->contents.used; ++i) {

      if (!names[i]) continue;

      if (!((++signal_check) % fss_basic_list_read_signal_check_d)) {
        if (fss_basic_list_read_signal_received(main)) {
          return F_status_set_error(F_interrupt);
        }

        signal_check = 0;
      }

      status = fss_basic_list_read_process_at_line(main, i, *delimits_object, *delimits_content, data, &line);
      if (status == F_success) break;
    } // for

    return F_none;
  }
#endif // _di_fss_basic_list_read_process_line_

#ifndef _di_fss_basic_list_read_process_name_
  f_status_t fss_basic_list_read_process_name(fss_basic_list_read_data_t *data, bool names[]) {

    f_array_lengths_t except_none = f_array_lengths_t_initialize;

    if (data->depths.array[0].index_name) {
      f_array_length_t i = 0;

      memset(names, F_false, sizeof(bool) * data->objects.used);

      // This standard should always tread selected names as trimmed.
      for (i = 0; i < data->objects.used; ++i) {

        if (fl_string_dynamic_partial_compare_except_trim_dynamic(data->depths.array[0].value_name, data->buffer, data->objects.array[i], except_none, data->delimits_object) == F_equal_to) {
          names[i] = F_true;
        }
      } // for
    }
    else {
      memset(names, F_true, sizeof(bool) * data->objects.used);
    }

    return F_none;
  }
#endif // _di_fss_basic_list_read_process_name_

#ifndef _di_fss_basic_list_read_process_option_
  f_status_t fss_basic_list_read_process_option(fll_program_data_t * const main, const f_console_arguments_t *arguments, fss_basic_list_read_data_t *data) {

    f_status_t status = F_none;

    if (main->parameters.array[fss_basic_list_read_parameter_at_e].result == f_console_result_additional_e) {
      data->option |= fss_basic_list_read_data_option_at_d;
    }

    if (main->parameters.array[fss_basic_list_read_parameter_columns_e].result == f_console_result_found_e) {
      data->option |= fss_basic_list_read_data_option_columns_d;
    }

    if (main->parameters.array[fss_basic_list_read_parameter_content_e].result == f_console_result_found_e) {
      data->option |= fss_basic_list_read_data_option_content_d;
    }

    if (main->parameters.array[fss_basic_list_read_parameter_empty_e].result == f_console_result_found_e) {
      data->option |= fss_basic_list_read_data_option_empty_d;
    }

    if (main->parameters.array[fss_basic_list_read_parameter_line_e].result == f_console_result_additional_e) {
      data->option |= fss_basic_list_read_data_option_line_d;

      status = fss_basic_list_read_load_number(main, fss_basic_list_read_parameter_line_e, fss_basic_list_read_long_line_s, arguments, &data->line);
      if (F_status_is_error(status)) return status;
    }

    if (main->parameters.array[fss_basic_list_read_parameter_name_e].result == f_console_result_additional_e) {
      data->option |= fss_basic_list_read_data_option_name_d;
    }

    if (main->parameters.array[fss_basic_list_read_parameter_object_e].result == f_console_result_found_e) {
      data->option |= fss_basic_list_read_data_option_object_d;
    }

    if (main->parameters.array[fss_basic_list_read_parameter_raw_e].result == f_console_result_found_e) {
      data->option |= fss_basic_list_read_data_option_raw_d;
    }

    if (main->parameters.array[fss_basic_list_read_parameter_select_e].result == f_console_result_additional_e) {
      data->option |= fss_basic_list_read_data_option_select_d;

      status = fss_basic_list_read_load_number(main, fss_basic_list_read_parameter_select_e, fss_basic_list_read_long_select_s, arguments, &data->select);
      if (F_status_is_error(status)) return status;
    }

    if (main->parameters.array[fss_basic_list_read_parameter_total_e].result == f_console_result_found_e) {
      data->option |= fss_basic_list_read_data_option_total_d;
    }

    if (main->parameters.array[fss_basic_list_read_parameter_trim_e].result == f_console_result_found_e) {
      data->option |= fss_basic_list_read_data_option_trim_d;
    }

    // Default to content if neither Object nor Content is explicitly requested.
    if (!(data->option & (fss_basic_list_read_data_option_content_d | fss_basic_list_read_data_option_object_d))) {
      data->option |= fss_basic_list_read_data_option_content_d;
    }

    return F_none;
  }
#endif // _di_fss_basic_list_read_process_option_

#ifndef _di_fss_basic_list_read_process_total_
  f_status_t fss_basic_list_read_process_total(fll_program_data_t * const main, fss_basic_list_read_data_t *data, bool names[]) {

    f_array_length_t total = 0;
    f_string_range_t range = f_string_range_t_initialize;
    f_array_length_t i = 0;
    uint16_t signal_check = 0;

    for (f_array_length_t at = 0; at < data->contents.used; ++at) {

      if (!names[at]) continue;

      if (!((++signal_check) % fss_basic_list_read_signal_check_d)) {
        if (fss_basic_list_read_signal_received(main)) {
          return F_status_set_error(F_interrupt);
        }

        signal_check = 0;
      }

      if (data->option & fss_basic_list_read_data_option_object_d) {
        ++total;
      }

      // There is only a single Content column for this standard.
      if (data->option & fss_basic_list_read_data_option_content_d) {

        if (!data->contents.array[at].used) continue;

        range.start = data->contents.array[at].array[0].start;
        range.stop = data->contents.array[at].array[0].stop;

        // This content has no data, do not even check "include empty" because it cannot be counted as a line.
        if (range.start > range.stop) {
          continue;
        }

        for (i = range.start; i <= range.stop; ++i) {

          if (data->buffer.string[i] == f_string_eol_s.string[0]) {
            range.start = i + 1;

            if (i <= range.stop) {
              ++total;
            }
          }
        } // for

        // If Content does not end with a newline, it still must be treated as the last line.
        if (data->buffer.string[range.stop] != f_string_eol_s.string[0]) {
          ++total;
        }
      }
    } // for

    flockfile(main->output.to.stream);

    if (data->option & fss_basic_list_read_data_option_line_d) {
      if (data->line < total) {
        fss_basic_list_read_print_one(main);
      }
      else {
        fss_basic_list_read_print_zero(main);
      }
    }
    else {
      fl_print_format("%ul%r", main->output.to.stream, total, f_string_eol_s);
    }

    funlockfile(main->output.to.stream);

    return F_none;
  }
#endif // _di_fss_basic_list_read_process_total_

#ifdef __cplusplus
} // extern "C"
#endif
