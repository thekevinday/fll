#include "fss_extended_read.h"
#include "private-common.h"
#include "private-fss_extended_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_extended_read_delimit_object_is_
  f_status_t fss_extended_read_delimit_object_is(const f_array_length_t depth, fss_extended_read_data_t * const data) {

    switch (data->delimit_mode) {
      case fss_extended_read_delimit_mode_none:
      case fss_extended_read_delimit_mode_content:
      case fss_extended_read_delimit_mode_content_greater:
      case fss_extended_read_delimit_mode_content_lesser:
        return F_false;

      case fss_extended_read_delimit_mode_all:
      case fss_extended_read_delimit_mode_content_object:
      case fss_extended_read_delimit_mode_content_greater_object:
      case fss_extended_read_delimit_mode_content_lesser_object:
      case fss_extended_read_delimit_mode_object:
        return F_true;

      default:
        break;
    }

    return depth == data->delimit_depth || data->delimit_mode == fss_extended_read_delimit_mode_content_lesser;
  }
#endif // _di_fss_extended_read_delimit_object_is_

#ifndef _di_fss_extended_read_delimit_content_is_
  f_status_t fss_extended_read_delimit_content_is(const f_array_length_t depth, fss_extended_read_data_t * const data) {

    switch (data->delimit_mode) {
      case fss_extended_read_delimit_mode_none:
      case fss_extended_read_delimit_mode_object:
        return F_false;

      case fss_extended_read_delimit_mode_all:
        return F_true;

      default:
        break;
    }

    if (depth < data->delimit_depth) {
      return data->delimit_mode == fss_extended_read_delimit_mode_content_lesser || data->delimit_mode == fss_extended_read_delimit_mode_content_lesser_object;
    }

    if (depth > data->delimit_depth) {
      return data->delimit_mode == fss_extended_read_delimit_mode_content_greater || data->delimit_mode == fss_extended_read_delimit_mode_content_greater_object;
    }

    return depth == data->delimit_depth;
  }
#endif // _di_fss_extended_read_delimit_content_is_

#ifndef _di_fss_extended_read_depth_process_
  f_status_t fss_extended_read_depth_process(f_console_arguments_t * const arguments, fss_extended_read_main_t * const main, fss_extended_read_data_t *data) {

    f_status_t status = F_none;

    {
      f_array_length_t depth_size = 1;

      if (main->parameters[fss_extended_read_parameter_depth].result == f_console_result_additional) {
        depth_size = main->parameters[fss_extended_read_parameter_depth].values.used;
      }

      if (depth_size > data->depths.size) {
        status = fss_extended_read_depths_resize(depth_size, &data->depths);

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "fss_extended_read_depths_resize", F_true);

          return status;
        }
      }

      data->depths.used = depth_size;
    }

    f_array_length_t position_depth = 0;
    f_array_length_t position_at = 0;
    f_array_length_t position_name = 0;

    for (f_array_length_t i = 0; i < data->depths.used; ++i) {

      data->depths.array[i].depth = 0;
      data->depths.array[i].index_at = 0;
      data->depths.array[i].index_name = 0;
      data->depths.array[i].value_at = 0;

      macro_f_string_dynamic_t_clear(data->depths.array[i].value_name);

      if (!main->parameters[fss_extended_read_parameter_depth].values.used) {
        position_depth = 0;
      }
      else {
        position_depth = main->parameters[fss_extended_read_parameter_depth].values.array[i];

        const f_string_range_t range = macro_f_string_range_t_initialize(strlen(arguments->argv[position_depth]));

        status = fl_conversion_string_to_number_unsigned(arguments->argv[position_depth], range, &data->depths.array[i].depth);

        if (F_status_is_error(status)) {
          fll_error_parameter_integer_print(main->error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, fss_extended_read_long_depth, arguments->argv[position_depth]);

          return status;
        }
      }

      if (main->parameters[fss_extended_read_parameter_at].result == f_console_result_additional) {
        for (; position_at < main->parameters[fss_extended_read_parameter_at].values.used; ++position_at) {

          if (main->parameters[fss_extended_read_parameter_at].values.array[position_at] < position_depth) {
            continue;
          }

          if (i + 1 < data->depths.used && main->parameters[fss_extended_read_parameter_at].values.array[position_at] > main->parameters[fss_extended_read_parameter_depth].values.array[i + 1]) {
            break;
          }

          data->depths.array[i].index_at = main->parameters[fss_extended_read_parameter_at].values.array[position_at];

          const f_string_range_t range = macro_f_string_range_t_initialize(strlen(arguments->argv[data->depths.array[i].index_at]));

          status = fl_conversion_string_to_number_unsigned(arguments->argv[data->depths.array[i].index_at], range, &data->depths.array[i].value_at);

          if (F_status_is_error(status)) {
            fll_error_parameter_integer_print(main->error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, fss_extended_read_long_at, arguments->argv[data->depths.array[i].index_at]);

            return status;
          }
        } // for
      }

      if (main->parameters[fss_extended_read_parameter_name].result == f_console_result_additional) {
        for (; position_name < main->parameters[fss_extended_read_parameter_name].values.used; position_name++) {

          if (main->parameters[fss_extended_read_parameter_name].values.array[position_name] < position_depth) {
            continue;
          }

          if (i + 1 < data->depths.used && main->parameters[fss_extended_read_parameter_name].values.array[position_name] > main->parameters[fss_extended_read_parameter_depth].values.array[i + 1]) {
            break;
          }

          data->depths.array[i].index_name = main->parameters[fss_extended_read_parameter_name].values.array[position_name];

          if (main->parameters[fss_extended_read_parameter_trim].result == f_console_result_found) {
            status = fl_string_rip(arguments->argv[data->depths.array[i].index_name], strlen(arguments->argv[data->depths.array[i].index_name]), &data->depths.array[i].value_name);
          }
          else {
            status = f_string_append(arguments->argv[data->depths.array[i].index_name], strlen(arguments->argv[data->depths.array[i].index_name]), &data->depths.array[i].value_name);
          }

          if (F_status_is_error(status)) {
            fll_error_print(main->error, F_status_set_fine(status), main->parameters[fss_extended_read_parameter_trim].result == f_console_result_found ? "fl_string_rip" : "f_string_append", F_true);

            return status;
          }
        } // for
      }
    } // for

    for (f_array_length_t i = 0; i < data->depths.used; ++i) {

      for (f_array_length_t j = i + 1; j < data->depths.used; ++j) {

        if (data->depths.array[i].depth == data->depths.array[j].depth) {
          if (main->error.verbosity != f_console_verbosity_quiet) {
            flockfile(main->error.to.stream);

            fl_print_format("%c%[%sThe value '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%ul%]", main->error.to.stream, main->error.notable, data->depths.array[i].depth, main->error.notable);
            fl_print_format("%[' may only be specified once for the parameter '%]", main->error.to.stream, main->error.context, main->error.context);
            fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_extended_read_long_depth, main->error.notable);
            fl_print_format("%['.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

            funlockfile(main->error.to.stream);
          }

          return F_status_set_error(F_parameter);
        }
        else if (data->depths.array[i].depth > data->depths.array[j].depth) {
          if (main->error.verbosity != f_console_verbosity_quiet) {
            flockfile(main->error.to.stream);

            fl_print_format("%c%[%sThe parameter '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
            fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_extended_read_long_depth, main->error.notable);
            fl_print_format("%[' may not have the value '%]", main->error.to.stream, main->error.context, main->error.context);
            fl_print_format("%[%ul%]", main->error.to.stream, main->error.notable, data->depths.array[i].depth, main->error.notable);
            fl_print_format("%[' before the value '%]", main->error.to.stream, main->error.context, main->error.context);
            fl_print_format("%[%ul%]", main->error.to.stream, main->error.notable, data->depths.array[j].depth, main->error.notable);
            fl_print_format("%['.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

            funlockfile(main->error.to.stream);
          }

          return F_status_set_error(F_parameter);
        }
      } // for
    } // for

    return F_none;
  }
#endif // _di_fss_extended_read_depth_process_

#ifndef _di_fss_extended_read_file_identify_
  f_string_t fss_extended_read_file_identify(const f_array_length_t at, const fss_extended_read_files_t files) {

    for (f_array_length_t i = 0; i < files.used; ++i) {

      if (at >= files.array[i].range.start && at <= files.array[i].range.stop) {
        return files.array[i].name;
      }
    } // for

    return "";
  }
#endif // _di_fss_extended_read_file_identify_

#ifndef _di_fss_extended_read_load_
  f_status_t fss_extended_read_load(fss_extended_read_main_t * const main, fss_extended_read_data_t *data) {

    f_state_t state = macro_f_state_t_initialize(fss_extended_read_common_allocation_large, fss_extended_read_common_allocation_small, 0, 0, 0, 0, 0);
    f_string_range_t input = macro_f_string_range_t_initialize(data->buffer.used);

    data->delimits_object.used = 0;
    data->delimits_content.used = 0;
    data->quotes_object.used = 0;
    data->quotes_content.used = 0;

    const f_status_t status = fll_fss_extended_read(data->buffer, state, &input, &data->objects, &data->contents, &data->quotes_object, &data->quotes_content, &data->delimits_object, &data->delimits_content);

    if (F_status_is_error(status)) {
      const f_string_t file_name = fss_extended_read_file_identify(input.start, data->files);

      fll_error_file_print(main->error, F_status_set_fine(status), "fll_fss_extended_read", F_true, file_name ? file_name : "-", "process", fll_error_file_type_file);

      return status;
    }
    else if (status == F_data_not_stop || status == F_data_not_eos) {
      if (data->option & fss_extended_read_data_option_total) {
        fss_extended_read_print_zero(main);

        return F_none;
      }

      return F_status_set_warning(status);
    }

    return F_none;
  }
#endif // _di_fss_extended_read_load_

#ifndef _di_fss_extended_read_load_number_
  f_status_t fss_extended_read_load_number(const f_array_length_t parameter, const f_string_t name, f_console_arguments_t * const arguments, fss_extended_read_main_t * const main, f_number_unsigned_t *number) {

    if (main->parameters[parameter].result == f_console_result_additional) {
      const f_array_length_t index = main->parameters[parameter].values.array[main->parameters[parameter].values.used - 1];
      const f_string_range_t range = macro_f_string_range_t_initialize(strnlen(arguments->argv[index], f_console_parameter_size));

      const f_status_t status = fl_conversion_string_to_number_unsigned(arguments->argv[index], range, number);

      if (F_status_is_error(status)) {
        fll_error_parameter_integer_print(main->error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, name, arguments->argv[index]);

        return status;
      }

      return F_true;
    }

    return F_false;
  }
#endif // _di_fss_extended_read_load_number_

#ifndef _di_fss_extended_read_print_at_
  void fss_extended_read_print_at(const f_array_length_t at, const f_fss_delimits_t delimits_object, const f_fss_delimits_t delimits_content, fss_extended_read_main_t * const main, fss_extended_read_data_t * const data) {

    if (at >= data->contents.used) {
      return;
    }

    flockfile(main->output.to.stream);

    if ((data->option & fss_extended_read_data_option_object) || (data->option & fss_extended_read_data_option_content) && (data->contents.array[at].used || (data->option & fss_extended_read_data_option_empty))) {
      if (data->option & fss_extended_read_data_option_object) {
        if (data->option & fss_extended_read_data_option_trim) {
          if ((data->option & fss_extended_read_data_option_raw) && data->quotes_object.array[at]) {
            f_print_character_safely(data->quotes_object.array[at] == f_fss_quote_type_single ? f_fss_quote_single_s[0] : f_fss_quote_double_s[0], main->output.to.stream);
          }

          fl_print_trim_except_dynamic_partial(data->buffer, data->objects.array[at], delimits_object, main->output.to.stream);

          if ((data->option & fss_extended_read_data_option_raw) && data->quotes_object.array[at]) {
            f_print_character_safely(data->quotes_object.array[at] == f_fss_quote_type_single ? f_fss_quote_single_s[0] : f_fss_quote_double_s[0], main->output.to.stream);
          }
        }
        else {
          if ((data->option & fss_extended_read_data_option_raw) && data->quotes_object.array[at]) {
            f_print_character_safely(data->quotes_object.array[at] == f_fss_quote_type_single ? f_fss_quote_single_s[0] : f_fss_quote_double_s[0], main->output.to.stream);
          }

          f_print_except_dynamic_partial(data->buffer, data->objects.array[at], delimits_object, main->output.to.stream);

          if ((data->option & fss_extended_read_data_option_raw) && data->quotes_object.array[at]) {
            f_print_character_safely(data->quotes_object.array[at] == f_fss_quote_type_single ? f_fss_quote_single_s[0] : f_fss_quote_double_s[0], main->output.to.stream);
          }
        }

        if (data->option & fss_extended_read_data_option_content) {
          fss_extended_read_print_object_end(main);
        }
      }

      bool content_printed = F_false;

      if ((data->option & fss_extended_read_data_option_content) && data->contents.array[at].used) {
        if (data->option & fss_extended_read_data_option_select) {
          if (data->select < data->contents.array[at].used) {
            content_printed = F_true;

            if ((data->option & fss_extended_read_data_option_raw) && data->quotes_content.array[at].array[data->select]) {
              f_print_character_safely(data->quotes_content.array[at].array[data->select] == f_fss_quote_type_single ? f_fss_quote_single_s[0] : f_fss_quote_double_s[0], main->output.to.stream);
            }

            f_print_except_dynamic_partial(data->buffer, data->contents.array[at].array[data->select], delimits_content, main->output.to.stream);

            if ((data->option & fss_extended_read_data_option_raw) && data->quotes_content.array[at].array[data->select]) {
              f_print_character_safely(data->quotes_content.array[at].array[data->select] == f_fss_quote_type_single ? f_fss_quote_single_s[0] : f_fss_quote_double_s[0], main->output.to.stream);
            }
          }
        }
        else {
          for (f_array_length_t i = 0; i < data->contents.array[at].used; ++i) {

            if (data->contents.array[at].array[i].start > data->contents.array[at].array[i].stop) {
              continue;
            }

            content_printed = F_true;

            if ((data->option & fss_extended_read_data_option_raw) && data->quotes_content.array[at].array[i]) {
              f_print_character_safely(data->quotes_content.array[at].array[i] == f_fss_quote_type_single ? f_fss_quote_single_s[0] : f_fss_quote_double_s[0], main->output.to.stream);
            }

            f_print_except_dynamic_partial(data->buffer, data->contents.array[at].array[i], delimits_content, main->output.to.stream);

            if ((data->option & fss_extended_read_data_option_raw) && data->quotes_content.array[at].array[i]) {
              f_print_character_safely(data->quotes_content.array[at].array[i] == f_fss_quote_type_single ? f_fss_quote_single_s[0] : f_fss_quote_double_s[0], main->output.to.stream);
            }

            if (i + 1 < data->contents.array[at].used && data->contents.array[at].array[i + 1].start <= data->contents.array[at].array[i + 1].stop) {
              fss_extended_read_print_content_end(main);
            }
          } // for
        }
      }

      if ((data->option & fss_extended_read_data_option_object) || (data->option & fss_extended_read_data_option_content) && (content_printed || (data->option & fss_extended_read_data_option_empty))) {
        fss_extended_read_print_set_end(main);
      }

      funlockfile(main->output.to.stream);
    }
  }
#endif // _di_fss_extended_read_print_at_

#ifndef _di_fss_extended_read_print_at_total_
  f_status_t fss_extended_read_print_at_total(const f_array_length_t at, fss_extended_read_main_t * const main, fss_extended_read_data_t *data) {

    if (data->option & fss_extended_read_data_option_select) {
      if (data->option & fss_extended_read_data_option_object) {
        flockfile(main->output.to.stream);

        fss_extended_read_print_one(main);

        funlockfile(main->output.to.stream);

        return F_success;
      }

      if (data->select < data->contents.array[at].used) {
        if (data->contents.array[at].array[data->select].start <= data->contents.array[at].array[data->select].stop || (data->option & fss_extended_read_data_option_empty)) {
          flockfile(main->output.to.stream);

          fss_extended_read_print_one(main);

          funlockfile(main->output.to.stream);

          return F_success;
        }
      }
    }
    else if ((data->option & fss_extended_read_data_option_object) || (data->option & fss_extended_read_data_option_empty)) {
      flockfile(main->output.to.stream);

      fss_extended_read_print_one(main);

      funlockfile(main->output.to.stream);

      return F_success;
    }
    else if (data->contents.array[at].used) {
      for (f_array_length_t j = 0; j < data->contents.array[at].used; ++j) {

        if (data->contents.array[at].array[j].start <= data->contents.array[at].array[j].stop) {
          flockfile(main->output.to.stream);

          fss_extended_read_print_one(main);

          funlockfile(main->output.to.stream);

          return F_success;
        }
      } // for
    }

    return F_none;
  }
#endif // _di_fss_extended_read_print_at_total_

#ifndef _di_fss_extended_read_print_content_end_
  void fss_extended_read_print_content_end(fss_extended_read_main_t * const main) {

    if (main->parameters[fss_extended_read_parameter_pipe].result == f_console_result_found) {
      f_print_character(fss_extended_read_pipe_content_start, main->output.to.stream);
    }
    else {
      f_print_character(f_fss_space, main->output.to.stream);
    }
  }
#endif // _di_fss_extended_read_print_content_end_

#ifndef _di_fss_extended_read_print_object_end_
  void fss_extended_read_print_object_end(fss_extended_read_main_t * const main) {

    if (main->parameters[fss_extended_read_parameter_pipe].result == f_console_result_found) {
      f_print_character(fss_extended_read_pipe_content_end, main->output.to.stream);
    }
    else {
      f_print_character(f_fss_space, main->output.to.stream);
    }
  }
#endif // _di_fss_extended_read_print_object_end_

#ifndef _di_fss_extended_read_print_one_
  void fss_extended_read_print_one(fss_extended_read_main_t * const main) {
    f_print_character(f_string_ascii_1_s[0], main->output.to.stream);
    f_print_character(f_string_eol_s[0], main->output.to.stream);
  }
#endif // _di_fss_extended_read_print_one_

#ifndef _di_fss_extended_read_print_set_end_
  void fss_extended_read_print_set_end(fss_extended_read_main_t * const main) {

    if (main->parameters[fss_extended_read_parameter_pipe].result == f_console_result_found) {
      f_print_character(fss_extended_read_pipe_content_end, main->output.to.stream);
    }
    else {
      f_print_character(f_fss_eol, main->output.to.stream);
    }
  }
#endif // _di_fss_extended_read_print_set_end_

#ifndef _di_fss_extended_read_print_zero_
  void fss_extended_read_print_zero(fss_extended_read_main_t * const main) {
    f_print_character(f_string_ascii_0_s[0], main->output.to.stream);
    f_print_character(f_string_eol_s[0], main->output.to.stream);
  }
#endif // _di_fss_extended_read_print_zero_

#ifndef _di_fss_extended_read_process_
  f_status_t fss_extended_read_process(f_console_arguments_t * const arguments, fss_extended_read_main_t * const main, fss_extended_read_data_t *data) {

    f_status_t status = fss_extended_read_process_option(arguments, main, data);
    if (F_status_is_error(status)) return status;

    status = fss_extended_read_load(main, data);
    if (F_status_is_error(status)) return status;

    bool names[data->objects.used];

    status = fss_extended_read_process_name(data, names);
    if (F_status_is_error(status)) return status;

    if (data->depths.array[0].index_at) {
      return fss_extended_read_process_at(main, data, names);
    }

    if (data->option & fss_extended_read_data_option_columns) {
      return fss_extended_read_process_columns(main, data, names);
    }

    if (data->option & fss_extended_read_data_option_total) {
      return fss_extended_read_process_total(main, data, names);
    }

    if (data->option & fss_extended_read_data_option_line) {
      return fss_extended_read_process_line(main, data, names);
    }

    f_array_lengths_t except_none = f_array_lengths_t_initialize;
    f_array_lengths_t *delimits_object = fss_extended_read_delimit_object_is(0, data) ? &data->delimits_object : &except_none;
    f_array_lengths_t *delimits_content = fss_extended_read_delimit_content_is((data->option & fss_extended_read_data_option_select) ? data->select : 0, data) ? &data->delimits_content : &except_none;

    if (data->option & fss_extended_read_data_option_raw) {
      delimits_object = &except_none;
      delimits_content = &except_none;
    }

    for (f_array_length_t i = 0; i < data->contents.used; ++i) {

      if (!names[i]) continue;

      fss_extended_read_print_at(i, *delimits_object, *delimits_content, main, data);
    } // for

    return F_none;
  }
#endif // _di_fss_extended_read_process_

#ifndef _di_fss_extended_read_process_at_
  f_status_t fss_extended_read_process_at(fss_extended_read_main_t * const main, fss_extended_read_data_t *data, bool names[]) {

    if (data->depths.array[0].value_at >= data->objects.used) {
      if (data->option & (fss_extended_read_data_option_columns | fss_extended_read_data_option_total)) {
        flockfile(main->output.to.stream);

        fss_extended_read_print_zero(main);

        funlockfile(main->output.to.stream);
      }

      return F_none;
    }

    // This standard only has one line per Content; therefore, any line value greater than 0 equates to no line to print.
    if (data->option & fss_extended_read_data_option_line) {
      if (data->line) {
        if (data->option & fss_extended_read_data_option_total) {
          flockfile(main->output.to.stream);

          fss_extended_read_print_zero(main);

          funlockfile(main->output.to.stream);
        }

        return F_none;
      }
    }

    f_array_lengths_t except_none = f_array_lengths_t_initialize;
    f_array_lengths_t *delimits_object = fss_extended_read_delimit_object_is(0, data) ? &data->delimits_object : &except_none;
    f_array_lengths_t *delimits_content = fss_extended_read_delimit_content_is((data->option & fss_extended_read_data_option_select) ? data->select : 0, data) ? &data->delimits_content : &except_none;

    if (data->option & fss_extended_read_data_option_raw) {
      delimits_object = &except_none;
      delimits_content = &except_none;
    }

    f_array_length_t at = 0;

    for (f_array_length_t i = 0; i < data->objects.used; ++i) {

      if (!names[i]) continue;

      if (at == data->depths.array[0].value_at) {
        if (data->option & fss_extended_read_data_option_line) {

          // This standard only supports one line per Object so when using "--at", the only valid line is line 0.
          if (data->line) break;

          if (data->option & fss_extended_read_data_option_total) {
            if (fss_extended_read_print_at_total(i, main, data) == F_none) {
              break;
            }
          }
          else {
            if ((data->option & fss_extended_read_data_option_raw) && data->quotes_object.array[at]) {
              f_print_character_safely(data->quotes_object.array[at] == f_fss_quote_type_single ? f_fss_quote_single_s[0] : f_fss_quote_double_s[0], main->output.to.stream);
            }

            fss_extended_read_print_at(i, *delimits_object, *delimits_content, main, data);

            if ((data->option & fss_extended_read_data_option_raw) && data->quotes_object.array[at]) {
              f_print_character_safely(data->quotes_object.array[at] == f_fss_quote_type_single ? f_fss_quote_single_s[0] : f_fss_quote_double_s[0], main->output.to.stream);
            }
          }
        }
        else if (data->option & fss_extended_read_data_option_columns) {
          fll_print_format("%ul%c", main->output.to.stream, data->contents.array[i].used, f_string_eol_s[0]);
        }
        else if (data->option & fss_extended_read_data_option_total) {
          if (fss_extended_read_print_at_total(i, main, data) == F_none) {
            break;
          }
        }
        else {
          if ((data->option & fss_extended_read_data_option_raw) && data->quotes_content.array[at].array[i]) {
            f_print_character_safely(data->quotes_content.array[at].array[i] == f_fss_quote_type_single ? f_fss_quote_single_s[0] : f_fss_quote_double_s[0], main->output.to.stream);
          }

          fss_extended_read_print_at(i, *delimits_object, *delimits_content, main, data);

          if ((data->option & fss_extended_read_data_option_raw) && data->quotes_content.array[at].array[i]) {
            f_print_character_safely(data->quotes_content.array[at].array[i] == f_fss_quote_type_single ? f_fss_quote_single_s[0] : f_fss_quote_double_s[0], main->output.to.stream);
          }
        }

        return F_none;
      }

      ++at;
    } // for

    if (data->option & fss_extended_read_data_option_total) {
      flockfile(main->output.to.stream);

      fss_extended_read_print_zero(main);

      funlockfile(main->output.to.stream);
    }

    return F_none;
  }
#endif // _di_fss_extended_read_process_at_

#ifndef _di_fss_extended_read_process_columns_
  f_status_t fss_extended_read_process_columns(fss_extended_read_main_t * const main, fss_extended_read_data_t *data, bool names[]) {

    if (!(data->option & fss_extended_read_data_option_content)) {
      flockfile(main->output.to.stream);

      fss_extended_read_print_zero(main);

      funlockfile(main->output.to.stream);

      return F_none;
    }

    f_array_length_t max = 0;

    for (f_array_length_t at = 0; at < data->contents.used; ++at) {

      if (!names[at]) continue;

      if (data->contents.array[at].used > max) {
        max = data->contents.array[at].used;
      }
    } // for

    fll_print_format("%ul%c", main->output.to.stream, max, f_string_eol_s[0]);

    return F_none;
  }
#endif // _di_fss_extended_read_process_columns_

#ifndef _di_fss_extended_read_process_line_
  f_status_t fss_extended_read_process_line(fss_extended_read_main_t * const main, fss_extended_read_data_t *data, bool names[]) {

    f_array_lengths_t except_none = f_array_lengths_t_initialize;
    f_array_lengths_t *delimits_object = fss_extended_read_delimit_object_is(0, data) ? &data->delimits_object : &except_none;
    f_array_lengths_t *delimits_content = fss_extended_read_delimit_content_is((data->option & fss_extended_read_data_option_select) ? data->select : 0, data) ? &data->delimits_content : &except_none;

    if (data->option & fss_extended_read_data_option_raw) {
      delimits_object = &except_none;
      delimits_content = &except_none;
    }

    f_array_length_t line = 0;

    for (f_array_length_t i = 0; i < data->contents.used; ++i) {

      if (!names[i]) continue;

      if (!(data->option & fss_extended_read_data_option_object) && (data->option & fss_extended_read_data_option_content)) {
        if (!data->contents.array[i].used) {
          if (data->option & fss_extended_read_data_option_empty) {
            if (line == data->line) {
              flockfile(main->output.to.stream);

              fss_extended_read_print_set_end(main);

              funlockfile(main->output.to.stream);

              break;
            }

            ++line;
          }

          continue;
        }
      }

      if (line == data->line) {
        fss_extended_read_print_at(i, *delimits_object, *delimits_content, main, data);

        break;
      }

      ++line;
    } // for

    return F_none;
  }
#endif // _di_fss_extended_read_process_line_

#ifndef _di_fss_extended_read_process_name_
  f_status_t fss_extended_read_process_name(fss_extended_read_data_t *data, bool names[]) {

    f_array_lengths_t except_none = f_array_lengths_t_initialize;

    if (data->depths.array[0].index_name) {
      f_array_length_t i = 0;

      memset(names, F_false, sizeof(bool) * data->objects.used);

      if (data->option & fss_extended_read_data_option_trim) {
        for (i = 0; i < data->objects.used; ++i) {

          if (fl_string_dynamic_partial_compare_except_trim_dynamic(data->depths.array[0].value_name, data->buffer, data->objects.array[i], except_none, data->delimits_object) == F_equal_to) {
            names[i] = F_true;
          }
        } // for
      }
      else {
        for (i = 0; i < data->objects.used; ++i) {

           if (fl_string_dynamic_partial_compare_except_dynamic(data->depths.array[0].value_name, data->buffer, data->objects.array[i], except_none, data->delimits_content) == F_equal_to) {
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
#endif // _di_fss_extended_read_process_name_

#ifndef _di_fss_extended_read_process_option_
  f_status_t fss_extended_read_process_option(f_console_arguments_t * const arguments, fss_extended_read_main_t * const main, fss_extended_read_data_t *data) {

    f_status_t status = F_none;

    if (main->parameters[fss_extended_read_parameter_at].result == f_console_result_additional) {
      data->option |= fss_extended_read_data_option_at;
    }

    if (main->parameters[fss_extended_read_parameter_columns].result == f_console_result_found) {
      data->option |= fss_extended_read_data_option_columns;
    }

    if (main->parameters[fss_extended_read_parameter_content].result == f_console_result_found) {
      data->option |= fss_extended_read_data_option_content;
    }

    if (main->parameters[fss_extended_read_parameter_empty].result == f_console_result_found) {
      data->option |= fss_extended_read_data_option_empty;
    }

    if (main->parameters[fss_extended_read_parameter_line].result == f_console_result_additional) {
      data->option |= fss_extended_read_data_option_line;

      status = fss_extended_read_load_number(fss_extended_read_parameter_line, fss_extended_read_long_line, arguments, main, &data->line);
      if (F_status_is_error(status)) return status;
    }

    if (main->parameters[fss_extended_read_parameter_name].result == f_console_result_additional) {
      data->option |= fss_extended_read_data_option_name;
    }

    if (main->parameters[fss_extended_read_parameter_object].result == f_console_result_found) {
      data->option |= fss_extended_read_data_option_object;
    }

    if (main->parameters[fss_extended_read_parameter_raw].result == f_console_result_found) {
      data->option |= fss_extended_read_data_option_raw;
    }

    if (main->parameters[fss_extended_read_parameter_select].result == f_console_result_additional) {
      data->option |= fss_extended_read_data_option_select;

      status = fss_extended_read_load_number(fss_extended_read_parameter_select, fss_extended_read_long_select, arguments, main, &data->select);
      if (F_status_is_error(status)) return status;
    }

    if (main->parameters[fss_extended_read_parameter_total].result == f_console_result_found) {
      data->option |= fss_extended_read_data_option_total;
    }

    if (main->parameters[fss_extended_read_parameter_trim].result == f_console_result_found) {
      data->option |= fss_extended_read_data_option_trim;
    }

    // Default to content if neither Object nor Content is explicitly requested.
    if (!(data->option & (fss_extended_read_data_option_content | fss_extended_read_data_option_object))) {
      data->option |= fss_extended_read_data_option_content;
    }

    return F_none;
  }
#endif // _di_fss_extended_read_process_option_

#ifndef _di_fss_extended_read_process_total_
  f_status_t fss_extended_read_process_total(fss_extended_read_main_t * const main, fss_extended_read_data_t *data, bool names[]) {

    f_array_length_t total = 0;

    // This standard only has one Content per line, however it has multiple Contents within that line.
    if ((data->option & fss_extended_read_data_option_object) || (data->option & fss_extended_read_data_option_content) && (data->option & fss_extended_read_data_option_empty)) {
      for (f_array_length_t i = 0; i < data->objects.used; ++i) {

        if (!names[i]) continue;

        ++total;
      } // for
    }
    else {
      f_array_length_t i = 0;
      f_array_length_t j = 0;

      for (; i < data->contents.used; ++i) {

        if (!names[i]) continue;
        if (!data->contents.array[i].used) continue;

        if ((data->option & fss_extended_read_data_option_select) && data->contents.array[i].used <= data->select) {
          continue;
        }

        for (j = 0; j < data->contents.array[i].used; ++j) {

          if (data->contents.array[i].array[j].start <= data->contents.array[i].array[j].stop) {
            if (data->option & fss_extended_read_data_option_select) {
              if (j == data->select) {
                ++total;

                break;
              }
            }
            else {
              ++total;

              break;
            }
          }
        } // for
      } // for
    }

    flockfile(main->output.to.stream);

    if (data->option & fss_extended_read_data_option_line) {
      if (data->line < total) {
        fss_extended_read_print_one(main);
      }
      else {
        fss_extended_read_print_zero(main);
      }
    }
    else {
      fl_print_format("%ul%c", main->output.to.stream, total, f_string_eol_s[0]);
    }

    funlockfile(main->output.to.stream);

    return F_none;
  }
#endif // _di_fss_extended_read_process_total_

#ifdef __cplusplus
} // extern "C"
#endif
