#include "fss_extended_write.h"
#include "private-fss_extended_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_extended_write_error_parameter_at_least_once_print_
  void fss_extended_write_error_parameter_at_least_once(const fss_extended_write_data_t data) {

    if (data.error.verbosity == f_console_verbosity_quiet) {
      return;
    }

    fprintf(data.error.to.stream, "%c", f_string_eol[0]);
    fl_color_print(data.error.to.stream, data.context.set.error, "%sMust specify the '", fll_error_print_error);
    fl_color_print(data.error.to.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable, fss_extended_write_long_object);
    fl_color_print(data.error.to.stream, data.context.set.error, "' parameter at least once and the '");
    fl_color_print(data.error.to.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable, fss_extended_write_long_content);
    fl_color_print(data.error.to.stream, data.context.set.error, "' parameter one or more times when not specifying the ");
    fl_color_print(data.error.to.stream, data.context.set.notable, "%s%s", f_console_symbol_long_enable, fss_extended_write_long_partial);
    fl_color_print(data.error.to.stream, data.context.set.error, "' parameter.%c", f_string_eol[0]);
  }
#endif // _di_fss_extended_write_error_parameter_at_least_once_print_

#ifndef _di_fss_extended_write_error_parameter_value_missing_print_
  void fss_extended_write_error_parameter_value_missing_print(const fss_extended_write_data_t data, const f_string_t symbol, const f_string_t parameter) {

    if (data.error.verbosity == f_console_verbosity_quiet) {
      return;
    }

    fprintf(data.error.to.stream, "%c", f_string_eol[0]);
    fl_color_print(data.error.to.stream, data.context.set.error, "%sThe parameter '", fll_error_print_error);
    fl_color_print(data.error.to.stream, data.context.set.notable, "%s%s", symbol, parameter);
    fl_color_print(data.error.to.stream, data.context.set.error, "' was specified, but no value was given.%c", f_string_eol[0]);
  }
#endif // _di_fss_extended_write_error_parameter_value_missing_print_

#ifndef _di_fss_extended_write_error_parameter_unsupported_eol_print_
  void fss_extended_write_error_parameter_unsupported_eol_print(const fss_extended_write_data_t data) {

    if (data.error.verbosity == f_console_verbosity_quiet) {
      return;
    }

    fprintf(data.error.to.stream, "%c", f_string_eol[0]);
    fl_color_print(data.error.to.stream, data.context.set.error, "%sThis standard does not support end of line character '", fll_error_print_error);
    fl_color_print(data.error.to.stream, data.context.set.notable, "\\n");
    fl_color_print(data.error.to.stream, data.context.set.error, "'.%c", f_string_eol[0]);
  }
#endif // _di_fss_extended_write_error_parameter_unsupported_eol_print_

#ifndef _di_fss_extended_write_process_
  f_return_status fss_extended_write_process(const fss_extended_write_data_t data, const f_file_t output, const f_fss_quote_t quote, const f_string_static_t *object, const f_string_statics_t *contents, f_string_dynamic_t *buffer) {
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

      status = fl_fss_extended_object_write(*object, quote, contents && contents->used ? f_fss_complete_full : f_fss_complete_partial, &range, buffer);

      if (F_status_set_fine(status) == F_none_eol) {
        fss_extended_write_error_parameter_unsupported_eol_print(data);

        return F_status_set_error(F_unsupported);
      }

      if (F_status_is_error(status)) {
        fll_error_print(data.error, F_status_set_fine(status), "fl_fss_extended_object_write", F_true);
        return F_status_set_error(status);
      }
    }

    if (contents) {
      if (contents->used) {
        for (f_array_length_t i = 0; i < contents->used; i++) {

          if (contents->array[i].used) {
            range.start = 0;
            range.stop = contents->array[i].used - 1;
          }
          else {
            range.start = 1;
            range.stop = 0;
          }

          status = fl_fss_extended_content_write(contents->array[i], quote, i + 1 < contents->used ? f_fss_complete_next : f_fss_complete_end, &range, buffer);

          if (F_status_set_fine(status) == F_none_eol) {
            fss_extended_write_error_parameter_unsupported_eol_print(data);

            return F_status_set_error(F_unsupported);
          }

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "fl_fss_extended_content_write", F_true);
            return F_status_set_error(status);
          }
        } // for
      }
      else {
        // objects in this standard do not have EOL, so add an EOL for printing purposes when there is no desired content.
        status = fl_string_append(f_string_eol, 1, buffer);

        if (F_status_is_error(status)) {
          fll_error_print(data.error, F_status_set_fine(status), "fl_string_append", F_true);
          return status;
        }
      }
    }

    f_print_dynamic(output.stream, *buffer);

    buffer->used = 0;
    return status;
  }
#endif // _di_fss_extended_write_process_

#ifndef _di_fss_extended_write_process_pipe_
  f_return_status fss_extended_write_process_pipe(const fss_extended_write_data_t data, const f_file_t output, const f_fss_quote_t quote, f_string_dynamic_t *buffer) {
    f_status_t status = F_none;
    f_status_t status_pipe = F_none;

    f_file_t input = f_file_t_initialize;

    input.id = f_type_descriptor_input;
    input.size_read = 2048;

    f_array_length_t i = 0;

    f_string_length_t total = 0;
    f_string_length_t previous = 0;
    f_string_range_t range = f_string_range_t_initialize;

    f_string_dynamic_t block = f_string_dynamic_t_initialize;
    f_string_dynamic_t object = f_string_dynamic_t_initialize;
    f_string_dynamics_t contents = f_string_dynamics_t_initialize;

    // 0x0 = start new object/content set, 0x1 = processing object, 0x2 = new individual content, 0x3 = processing content, 0x4 = end object/content set.
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
          if (contents.used) {
            for (i = 0; i < contents.used; i++) {
              contents.array[i].used = 0;
            } // for
          }

          object.used = 0;
          contents.used = 0;

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

          if (block.string[range.start] == fss_extended_write_pipe_content_start) {
            state = 0x2;
            range.start++;
            break;
          }

          if (block.string[range.start] == fss_extended_write_pipe_content_end) {
            state = 0x4;
            range.start++;
            break;
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
        if (contents.used + 1 > contents.size) {
          status = fl_string_dynamics_size_increase(f_fss_default_allocation_step, &contents);

          if (F_status_is_error(status)) {
            fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamics_size_increase", F_true);
            break;
          }
        }

        state = 0x3;
        contents.used++;
      }

      if (state == 0x3) {
        if (range.start <= range.stop) {
          total = (range.stop - range.start) + 1;
        }
        else {
          total = 0;
        }

        if (total) {
          for (; range.start <= range.stop; range.start++) {

            if (block.string[range.start] == fss_extended_write_pipe_content_start) {
              if (contents.used + 1 > contents.size) {
                status = fl_string_dynamics_size_increase(f_fss_default_allocation_step, &contents);

                if (F_status_is_error(status)) {
                  fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamics_size_increase", F_true);
                  break;
                }
              }

              contents.used++;
              continue;
            }
            else if (block.string[range.start] == fss_extended_write_pipe_content_end) {
              state = 0x4;
              range.start++;
              break;
            }
            else if (F_status_set_fine(status) == F_none_eol) {
              fss_extended_write_error_parameter_unsupported_eol_print(data);

              status = F_status_set_error(F_unsupported);
              break;
            }

            if (contents.array[contents.used - 1].used + 1 > contents.array[contents.used - 1].size) {
              status = fl_string_dynamic_size_increase(f_fss_default_allocation_step, &contents.array[contents.used - 1]);

              if (F_status_is_error(status)) {
                fll_error_print(data.error, F_status_set_fine(status), "fl_string_dynamic_size_increase", F_true);
                break;
              }
            }

            contents.array[contents.used - 1].string[contents.array[contents.used - 1].used++] = block.string[range.start];
          } // for

          if (F_status_is_error(status)) break;
        }
        else {
          state = 0x4;
        }
      }

      if (state == 0x4) {
        status = fss_extended_write_process(data, output, quote, &object, &contents, buffer);
        if (F_status_is_error(status)) break;

        state = 0;
      }
    } // for

    // if the pipe ended before finishing, then attempt to wrap up.
    if (F_status_is_error_not(status) && status_pipe == F_none_eof && state) {
      status = fss_extended_write_process(data, output, quote, &object, &contents, buffer);
    }

    f_macro_string_dynamic_t_delete_simple(block);
    f_macro_string_dynamic_t_delete_simple(object);
    f_macro_string_dynamics_t_delete_simple(contents);
    return status;
  }
#endif // _di_fss_extended_write_process_pipe_

#ifdef __cplusplus
} // extern "C"
#endif
