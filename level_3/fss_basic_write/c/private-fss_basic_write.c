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

    fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
    f_color_print(data.error.to.stream, data.context.set.error, "%sMust specify both the '", fll_error_print_error);
    f_color_print(data.error.to.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_write_long_object);
    f_color_print(data.error.to.stream, data.context.set.error, "' parameter and the '");
    f_color_print(data.error.to.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_write_long_content);
    f_color_print(data.error.to.stream, data.context.set.error, "' parameter the same number of times when not specifying the ");
    f_color_print(data.error.to.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable_s, fss_basic_write_long_partial);
    f_color_print(data.error.to.stream, data.context.set.error, "' parameter.%c", f_string_eol_s[0]);
  }
#endif // _di_fss_basic_write_error_parameter_same_times_print_

#ifndef _di_fss_basic_write_error_parameter_value_missing_print_
  void fss_basic_write_error_parameter_value_missing_print(const fss_basic_write_data_t data, const f_string_t symbol, const f_string_t parameter) {

    if (data.error.verbosity == f_console_verbosity_quiet) {
      return;
    }

    fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
    f_color_print(data.error.to.stream, data.context.set.error, "%sThe parameter '", fll_error_print_error);
    f_color_print(data.error.to.stream, data.context.set.notable, "%s%s", symbol, parameter);
    f_color_print(data.error.to.stream, data.context.set.error, "' was specified, but no value was given.%c", f_string_eol_s[0]);
  }
#endif // _di_fss_basic_write_error_parameter_value_missing_print_

#ifndef _di_fss_basic_write_error_parameter_unsupported_eol_print_
  void fss_basic_write_error_parameter_unsupported_eol_print(const fss_basic_write_data_t data) {

    if (data.error.verbosity == f_console_verbosity_quiet) {
      return;
    }

    fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
    f_color_print(data.error.to.stream, data.context.set.error, "%sThis standard does not support end of line character '", fll_error_print_error);
    f_color_print(data.error.to.stream, data.context.set.notable, "\\n");
    f_color_print(data.error.to.stream, data.context.set.error, "'.%c", f_string_eol_s[0]);
  }
#endif // _di_fss_basic_write_error_parameter_unsupported_eol_print_

#ifndef _di_fss_basic_write_process_
  f_status_t fss_basic_write_process(const fss_basic_write_data_t data, const f_file_t output, const f_fss_quote_t quote, const f_string_static_t *object, const f_string_static_t *content, f_string_dynamic_t *buffer) {
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
        if (data.parameters[fss_basic_write_parameter_trim].result == f_console_result_found) {
          complete = f_fss_complete_full_trim;
        }
        else {
          complete = f_fss_complete_full;
        }
      }

      status = fl_fss_basic_object_write_string(*object, quote, complete, &range, buffer);

      if (F_status_set_fine(status) == F_none_eol) {
        fss_basic_write_error_parameter_unsupported_eol_print(data);

        return F_status_set_error(F_supported_not);
      }

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "fl_fss_basic_object_write_string", F_true);
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

      status = fl_fss_basic_content_write_string(*content, object ? f_fss_complete_full : f_fss_complete_none, &range, buffer);

      if (F_status_set_fine(status) == F_none_eol) {
        fss_basic_write_error_parameter_unsupported_eol_print(data);

        return F_status_set_error(F_supported_not);
      }

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "fl_fss_basic_content_write_string", F_true);
        return status;
      }
    }

    if (!object || !content) {
      status = f_string_append(f_string_eol, 1, buffer);

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "f_string_append", F_true);
        return status;
      }
    }

    f_print_dynamic(output.stream, *buffer);

    buffer->used = 0;
    return status;
  }
#endif // _di_fss_basic_write_process_

#ifndef _di_fss_basic_write_process_pipe_
  f_status_t fss_basic_write_process_pipe(const fss_basic_write_data_t data, const f_file_t output, const f_fss_quote_t quote, f_string_dynamic_t *buffer) {
    f_status_t status = F_none;
    f_status_t status_pipe = F_none;

    f_file_t input = f_file_t_initialize;

    input.id = f_type_descriptor_input;
    input.size_read = 2048;

    f_array_length_t total = 0;
    f_array_length_t previous = 0;
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

        if (!block.used) break;

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
          status = f_string_dynamic_increase_by(block.used, &object);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamic_increase_by", F_true);
            break;
          }
        }

        for (; range.start <= range.stop; range.start++) {

          if (block.string[range.start] == fss_basic_write_pipe_content_start) {
            state = 0x2;
            range.start++;
            break;
          }

          if (block.string[range.start] == fss_basic_write_pipe_content_end) {
            state = 0x3;
            range.start++;
            break;
          }

          if (block.string[range.start] == fss_basic_write_pipe_content_ignore) {
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
            status = f_string_dynamic_increase_by(total, &content);

            if (F_status_is_error(status)) {
              fll_error_print(data.error, F_status_set_fine(status), "f_string_dynamic_increase_by", F_true);
              break;
            }
          }

          for (; range.start <= range.stop; range.start++) {

            if (block.string[range.start] == fss_basic_write_pipe_content_start) {
              if (data.error.verbosity != f_console_verbosity_quiet) {
                fprintf(data.error.to.stream, "%c", f_string_eol_s[0]);
                f_color_print(data.error.to.stream, data.context.set.error, "%sThis standard only supports one content per object.%c", fll_error_print_error, f_string_eol_s[0]);
              }

              status = F_status_set_error(F_supported_not);
              break;
            }

            if (block.string[range.start] == fss_basic_write_pipe_content_end) {
              state = 0x3;
              range.start++;
              break;
            }

            if (block.string[range.start] == fss_basic_write_pipe_content_ignore) {
              // this is not used by this program.
              continue;
            }

            if (F_status_set_fine(status) == F_none_eol) {
              fss_basic_write_error_parameter_unsupported_eol_print(data);

              status = F_status_set_error(F_supported_not);
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
    if (F_status_is_error_not(status) && status_pipe == F_none_eof && state) {
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
