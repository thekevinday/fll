#include "fss_extended_list_write.h"
#include "private-fss_extended_list_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_extended_list_write_error_parameter_same_times_print_
  void fss_extended_list_write_error_parameter_same_times_print(const fss_extended_list_write_data_t data) {

    if (data.error.verbosity == f_console_verbosity_quiet) {
      return;
    }

    fprintf(data.error.to.stream, "%c", f_string_eol[0]);
    fl_color_print(data.error.to.stream, data.context.set.error, "%sMust specify both the '", fll_error_print_error);
    fl_color_print(data.error.to.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable, fss_extended_list_write_long_object);
    fl_color_print(data.error.to.stream, data.context.set.error, "' parameter and the '");
    fl_color_print(data.error.to.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable, fss_extended_list_write_long_content);
    fl_color_print(data.error.to.stream, data.context.set.error, "' parameter the same number of times when not specifying the ");
    fl_color_print(data.error.to.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable, fss_extended_list_write_long_partial);
    fl_color_print(data.error.to.stream, data.context.set.error, "' parameter.%c", f_string_eol[0]);
  }
#endif // _di_fss_extended_list_write_error_parameter_same_times_print_

#ifndef _di_fss_extended_list_write_error_parameter_unsupported_eol_print_
  void fss_extended_list_write_error_parameter_unsupported_eol_print(const fss_extended_list_write_data_t data) {

    if (data.error.verbosity == f_console_verbosity_quiet) {
      return;
    }

    fprintf(data.error.to.stream, "%c", f_string_eol[0]);
    fl_color_print(data.error.to.stream, data.context.set.error, "%sThis standard does not support end of line character '", fll_error_print_error);
    fl_color_print(data.error.to.stream, data.context.set.notable, "\\n");
    fl_color_print(data.error.to.stream, data.context.set.error, "' in objects.%c", f_string_eol[0]);
  }
#endif // _di_fss_extended_list_write_error_parameter_unsupported_eol_print_

#ifndef _di_fss_extended_list_write_error_parameter_value_missing_print_
  void fss_extended_list_write_error_parameter_value_missing_print(const fss_extended_list_write_data_t data, const f_string_t symbol, const f_string_t parameter) {

    if (data.error.verbosity == f_console_verbosity_quiet) {
      return;
    }

    fprintf(data.error.to.stream, "%c", f_string_eol[0]);
    fl_color_print(data.error.to.stream, data.context.set.error, "%sThe parameter '", fll_error_print_error);
    fl_color_print(data.error.to.stream, data.context.set.notable, "%s%s", symbol, parameter);
    fl_color_print(data.error.to.stream, data.context.set.error, "' was specified, but no value was given.%c", f_string_eol[0]);
  }
#endif // _di_fss_extended_list_write_error_parameter_value_missing_print_

#ifndef _di_fss_extended_list_write_process_
  f_return_status fss_extended_list_write_process(const fss_extended_list_write_data_t data, const f_file_t output, const f_fss_quote_t quote, const f_string_static_t *object, const f_string_static_t *content, const f_string_ranges_t *ignore, f_string_dynamic_t *buffer) {
    f_status_t status = F_none;

    f_string_range_t range = f_string_range_t_initialize;

    if (object) {
      uint8_t complete = f_fss_complete_none;

      if (object->used) {
        range.start = 0;
        range.stop = object->used - 1;
      }
      else {
        range.start = 1;
        range.stop = 0;
      }

      if (content) {
        if (data.parameters[fss_extended_list_write_parameter_trim].result == f_console_result_found) {
          complete = f_fss_complete_full_trim;
        }
        else {
          complete = f_fss_complete_full;
        }
      }

      status = fl_fss_extended_list_object_write_string(*object, complete, &range, buffer);

      if (F_status_set_fine(status) == F_none_eol) {
        fss_extended_list_write_error_parameter_unsupported_eol_print(data);

        return F_status_set_error(F_unsupported);
      }

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "fl_fss_extended_list_object_write_string", F_true);
        return status;
      }
    }

    if (content && content->used) {
      range.start = 0;
      range.stop = content->used - 1;

      status = fl_fss_extended_list_content_write_string(*content, object ? f_fss_complete_full : f_fss_complete_none, &data.prepend, ignore, &range, buffer);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "fl_fss_extended_list_content_write_string", F_true);
        return status;
      }
    }

    if (!object || !content) {
      status = fl_string_append(f_string_eol, 1, buffer);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "fl_string_append", F_true);
        return status;
      }
    }

    f_print_dynamic(output.stream, *buffer);

    buffer->used = 0;
    return status;
  }
#endif // _di_fss_extended_list_write_process_

#ifndef _di_fss_extended_list_write_process_pipe_
  f_return_status fss_extended_list_write_process_pipe(const fss_extended_list_write_data_t data, const f_file_t output, const f_fss_quote_t quote, f_string_dynamic_t *buffer, f_string_ranges_t *ignore) {
    f_status_t status = F_none;
    f_status_t status_pipe = F_none;

    f_file_t input = f_file_t_initialize;

    input.id = f_type_descriptor_input;
    input.size_read = 2048;

    f_string_length_t total = 0;
    f_string_length_t previous = 0;

    f_string_range_t range = f_string_range_t_initialize;
    f_string_range_t range_ignore = f_string_range_t_initialize;

    f_string_dynamic_t block = f_string_dynamic_t_initialize;
    f_string_dynamic_t object = f_string_dynamic_t_initialize;
    f_string_dynamic_t content = f_string_dynamic_t_initialize;

    // 0x0 = start new object/content set, 0x1 = processing object, 0x2 = processing content, 0x3 = end object/content set.
    uint8_t state = 0;

    for (;;) {

      if (range.start > range.stop) {
        if (status_pipe == F_none_eof) break;

        block.used = 0;

        status_pipe = f_file_read_block(input, &block);

        if (F_status_is_error(status_pipe)) {
          fll_error_print(data.error, F_status_set_fine(status_pipe), "f_file_read_block", F_true);

          status_pipe = F_status_set_error(F_pipe);
          break;
        }

        if (!block.used) break;

        range.start = 0;
        range.stop = block.used - 1;
      }

      if (!state || state == 0x1) {
        if (!state) {
          object.used = 0;
          content.used = 0;

          state = 0x1;

          range_ignore.start = 1;
          range_ignore.stop = 0;
        }

        if (object.used + block.used > object.size) {
          status = fl_string_dynamic_increase_by(block.used, &object);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_increase_by", F_true);
            break;
          }
        }

        for (; range.start <= range.stop; range.start++) {

          if (block.string[range.start] == fss_extended_list_write_pipe_content_start) {
            state = 0x2;
            range.start++;
            break;
          }

          if (block.string[range.start] == fss_extended_list_write_pipe_content_end) {
            state = 0x3;
            range.start++;
            break;
          }

          if (block.string[range.start] == fss_extended_list_write_pipe_content_ignore) {
            // this is not used by objects.
            continue;
          }

          object.string[object.used++] = block.string[range.start];
        } // for

        if (F_status_is_error(status)) break;

        // if the start of content was not found, then fetch the next block.
        if (state == 0x1) continue;

        // if the end of the current block is reached, fetch the next block.
        if (range.start > range.stop) continue;
      }

      if (state == 0x2) {
        if (range.start <= range.stop) {
          total = (range.stop - range.start) + 1;
        }
        else {
          total = 0;
        }

        if (total) {
          if (content.used + total > content.size) {
            status = fl_string_dynamic_increase_by(total, &content);

            if (F_status_is_error(status)) {
              fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_increase_by", F_true);
              break;
            }
          }

          for (; range.start <= range.stop; range.start++) {

            if (block.string[range.start] == fss_extended_list_write_pipe_content_start) {
              if (data.error.verbosity != f_console_verbosity_quiet) {
                fprintf(data.error.to.stream, "%c", f_string_eol[0]);
                fl_color_print(data.error.to.stream, data.context.set.error, "%sThis standard only supports one content per object.%c", fll_error_print_error, f_string_eol[0]);
              }

              status = F_status_set_error(F_unsupported);
              break;
            }

            if (block.string[range.start] == fss_extended_list_write_pipe_content_end) {
              state = 0x3;
              range.start++;
              break;
            }

            if (block.string[range.start] == fss_extended_list_write_pipe_content_ignore) {
              if (ignore) {
                if (range_ignore.start > range_ignore.stop) {
                  range_ignore.start = content.used;
                  range_ignore.stop = content.used;
                }
                else {
                  if (ignore->used + 1 > ignore->size) {
                    if (ignore->size + f_fss_default_allocation_step > f_array_length_t_size) {
                      if (ignore->size + 1 > f_array_length_t_size) {
                        fll_error_print(data.error, F_string_too_large, "fss_extended_list_write_process_pipe", F_true);

                        status = F_status_set_error(F_string_too_large);
                        break;
                      }

                      f_macro_string_ranges_t_resize(status, (*ignore), ignore->size + 1);
                    }
                    else {
                      f_macro_string_ranges_t_resize(status, (*ignore), ignore->size + f_fss_default_allocation_step);
                    }

                    if (F_status_is_error(status)) {
                      fll_error_print(data.error, F_string_too_large, "fss_extended_list_write_process_pipe", F_true);
                      break;
                    }
                  }

                  ignore->array[ignore->used].start = range_ignore.start;
                  ignore->array[ignore->used++].stop = content.used - 1;

                  range_ignore.start = 1;
                  range_ignore.stop = 0;
                }
              }

              continue;
            }

            content.string[content.used++] = block.string[range.start];
          } // for

          if (F_status_is_error(status)) break;
        }
        else {
          state = 0x3;
        }
      }

      if (state == 0x3) {
        status = fss_extended_list_write_process(data, output, quote, &object, &content, ignore, buffer);
        if (F_status_is_error(status)) break;

        state = 0;
      }
    } // for

    // if the pipe ended before finishing, then attempt to wrap up.
    if (F_status_is_error_not(status) && status_pipe == F_none_eof && state) {
      status = fss_extended_list_write_process(data, output, quote, &object, &content, ignore, buffer);
    }

    f_macro_string_dynamic_t_delete_simple(block);
    f_macro_string_dynamic_t_delete_simple(object);
    f_macro_string_dynamic_t_delete_simple(content);
    return status;
  }
#endif // _di_fss_extended_list_write_process_pipe_

#ifndef _di_fss_extended_list_write_process_parameter_ignore_
  f_return_status fss_extended_list_write_process_parameter_ignore(const f_console_arguments_t arguments, const fss_extended_list_write_data_t data, const f_array_lengths_t contents, const f_array_length_t location, f_string_ranges_t *ignore) {
    f_status_t status = F_none;

    f_array_length_t i = 0;
    f_array_length_t l = 0;
    f_array_length_t index = 0;

    f_string_range_t range = f_string_range_t_initialize;

    f_number_unsigned_t number = 0;

    range.start = 0;

    for (; i < data.parameters[fss_extended_list_write_parameter_ignore].locations.used; i++) {

      l = data.parameters[fss_extended_list_write_parameter_ignore].locations.array[i];

      if (l < contents.array[location]) continue;
      if (location + 1 < contents.used && l > contents.array[location + 1]) continue;

      if (ignore->used + 1 > ignore->size) {
        if (ignore->size + f_fss_default_allocation_step > f_array_length_t_size) {
          if (ignore->size + 1 > f_array_length_t_size) {
            fll_error_print(data.error, F_string_too_large, "fss_extended_list_write_process_parameter_ignore", F_true);
            return F_status_set_error(F_string_too_large);
          }

          f_macro_string_ranges_t_resize(status, (*ignore), ignore->size + 1);
        }
        else {
          f_macro_string_ranges_t_resize(status, (*ignore), ignore->size + f_fss_default_allocation_step);
        }

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "fss_extended_list_write_process_parameter_ignore", F_true);
          return status;
        }
      }

      index = data.parameters[fss_extended_list_write_parameter_ignore].values.array[i * 2];

      range.start = 0;
      range.stop = strnlen(arguments.argv[index], f_console_length_size) - 1;

      // allow and ignore the positive sign.
      if (range.stop > 0 && arguments.argv[index][0] == '+') {
        range.start = 1;
      }

      status = fl_conversion_string_to_number_unsigned(arguments.argv[index], &number, range);

      if (F_status_is_error(status)) {
        fll_error_parameter_integer_print(data.error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, fss_extended_list_write_long_ignore, arguments.argv[index]);
        return status;
      }

      ignore->array[ignore->used].start = number;

      index = data.parameters[fss_extended_list_write_parameter_ignore].values.array[(i * 2) + 1];

      range.start = 0;
      range.stop = strnlen(arguments.argv[index], f_console_length_size) - 1;

      // allow and ignore the positive sign.
      if (range.stop > 0 && arguments.argv[index][0] == '+') {
        range.start = 1;
      }

      status = fl_conversion_string_to_number_unsigned(arguments.argv[index], &number, range);

      if (F_status_is_error(status)) {
        fll_error_parameter_integer_print(data.error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, fss_extended_list_write_long_ignore, arguments.argv[index]);
        return status;
      }

      ignore->array[ignore->used++].stop = number;
    } // for

    return F_none;
  }
#endif // _di_fss_extended_list_write_process_parameter_ignore_

#ifdef __cplusplus
} // extern "C"
#endif
