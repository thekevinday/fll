#include "fss_basic_write.h"
#include "private-fss_basic_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_basic_write_error_parameter_same_times_print_
  void fss_basic_write_error_parameter_same_times_print(const fss_basic_write_data_t data) {

    if (data.error.verbosity == f_console_verbosity_quiet) {
      return;
    }

    fl_color_print(data.error.to.stream, data.context.set.error, "%sMust specify both the '", fll_error_print_error);
    fl_color_print(data.error.to.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_write_long_object);
    fl_color_print(data.error.to.stream, data.context.set.error, "' parameter and the '");
    fl_color_print(data.error.to.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_write_long_content);
    fl_color_print(data.error.to.stream, data.context.set.error, "' parameter the same number of times when not specifying the ");
    fl_color_print(data.error.to.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable, fss_basic_write_long_partial);
    fl_color_print(data.error.to.stream, data.context.set.error, "' parameter.%c", f_string_eol[0]);
  }
#endif // _di_fss_basic_write_error_parameter_same_times_print_

#ifndef _di_fss_basic_write_error_parameter_value_missing_print_
  void fss_basic_write_error_parameter_value_missing_print(const fss_basic_write_data_t data, const f_string_t symbol, const f_string_t parameter) {

    if (data.error.verbosity == f_console_verbosity_quiet) {
      return;
    }

    fl_color_print(data.error.to.stream, data.context.set.error, "%sThe parameter '", fll_error_print_error);
    fl_color_print(data.error.to.stream, data.context.set.notable, "%s%s", symbol, parameter);
    fl_color_print(data.error.to.stream, data.context.set.error, "' was specified, but no value was given.%c", f_string_eol[0]);
  }
#endif // _di_fss_basic_write_error_parameter_value_missing_print_

#ifndef _di_fss_basic_write_process_
  f_return_status fss_basic_write_process(const fss_basic_write_data_t data, const f_file_t output, const f_fss_quote_t quote, const f_string_static_t *object, const f_string_static_t *content, f_string_dynamic_t *buffer) {
    f_status_t status = F_none;

    f_string_range_t range = f_string_range_t_initialize;

    if (object) {
      if (object->used) {
        range.start = 0;
        range.stop = object->used - 1;
      }
      else {
        range.start = 1;
        range.stop = 0;
      }

      status = fl_fss_basic_object_write(*object, quote, content ? f_fss_complete_full : f_fss_complete_partial, &range, buffer);

      if (F_status_set_fine(status) == F_none_eol) {
        fl_color_print(data.error.to.stream, data.context.set.error, "%sThis standard does not support end of line character '", fll_error_print_error);
        fl_color_print(data.error.to.stream, data.context.set.notable, "\\n");
        fl_color_print(data.error.to.stream, data.context.set.error, "'.%c", f_string_eol[0]);

        return F_status_set_error(F_unsupported);
      }

      if (status == F_data_not_stop || status == F_data_not_eos) {
        fl_color_print(data.error.to.stream, data.context.set.error, "%sThis standard requires an object.%c", fll_error_print_error, f_string_eol[0]);
        return F_status_set_error(status);
      }
      else if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "fl_fss_basic_list_object_write", F_true);
        return status;
      }
    }

    if (content) {
      if (content->used) {
        range.start = 0;
        range.stop = content->used - 1;
      }
      else {
        range.start = 1;
        range.stop = 0;
      }

      status = fl_fss_basic_content_write(*content, object ? f_fss_complete_full : f_fss_complete_partial, &range, buffer);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "fl_fss_basic_content_write", F_true);
        return status;
      }
    }
    else {
      // objects in this standard do not have EOL, so add an EOL for printing purposes when there is no desired content.
      status = fl_string_append(f_string_eol, 1, buffer);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "fl_fss_basic_content_write", F_true);
        return status;
      }
    }

    f_print_dynamic(output.stream, *buffer);

    buffer->used = 0;
    return status;
  }
#endif // _di_fss_basic_write_process_

#ifndef _di_fss_basic_write_process_pipe_
  f_return_status fss_basic_write_process_pipe(const fss_basic_write_data_t data, const f_file_t output, const f_fss_quote_t quote, f_string_dynamic_t *buffer) {
    f_status_t status = F_none;
    f_status_t status_pipe = F_none;

    f_file_t input = f_file_t_initialize;

    input.id = f_type_descriptor_input;
    input.size_read = 2048;

    f_string_length_t total = 0;
    f_string_length_t previous = 0;
    f_string_range_t range = f_string_range_t_initialize;

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

        range.start = 0;
        range.stop = block.used - 1;
      }

      if (!state || state == 0x1) {
        if (!state) {
          object.used = 0;
          content.used = 0;

          state = 0x1;
        }

        if (object.used + block.used > object.size) {
          status = fl_string_dynamic_size_increase(block.used, &object);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_size_increase", F_true);
            break;
          }
        }

        for (; range.start <= range.stop; range.start++) {

          if (block.string[range.start] == fss_basic_write_pipe_content_start) {
            state = 0x2;
            range.start++;
            break;
          }

          object.string[object.used++] = block.string[range.start];
        } // for

        if (F_status_is_error(status)) break;

        // if the start of content was not found, then fetch the next block.
        if (state != 0x2) continue;

        // if the end of the current block is reached, fetch the next block.
        if (range.start > range.stop) continue;
      }

      if (state == 0x2) {
        if (block.used && range.start <= range.stop) {
          total = (range.stop - range.start) + 1;
        }
        else {
          total = 0;
        }

        if (total) {
          if (content.used + total > content.size) {
            status = fl_string_dynamic_size_increase(total, &content);

            if (F_status_is_error(status)) {
              fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_size_increase", F_true);
              break;
            }
          }

          for (; range.start <= range.stop; range.start++) {

            if (block.string[range.start] == fss_basic_write_pipe_content_start) {
              fl_color_print(data.error.to.stream, data.context.set.error, "%sThis standard only supports one content per object.%c", fll_error_print_error, f_string_eol[0]);

              status = F_status_set_error(F_unsupported);
              break;
            }
            else if (block.string[range.start] == fss_basic_write_pipe_content_end) {
              state = 0x3;
              range.start++;
              break;
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
        status = fss_basic_write_process(data, output, quote, &object, &content, buffer);
        if (F_status_is_error(status)) break;

        state = 0;
      }
    } // for

    // if the pipe ended before finishing, then attempt to wrap up.
    if (status_pipe == F_none_eof && state) {
      status = fss_basic_write_process(data, output, quote, &object, &content, buffer);
    }

    f_macro_string_dynamic_t_delete_simple(block);
    f_macro_string_dynamic_t_delete_simple(object);
    f_macro_string_dynamic_t_delete_simple(content);
    return status;
  }
#endif // _di_fss_basic_write_process_pipe_

#ifdef __cplusplus
} // extern "C"
#endif
