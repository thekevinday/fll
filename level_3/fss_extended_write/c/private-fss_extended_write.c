#include "fss_extended_write.h"
#include "private-common.h"
#include "private-fss_extended_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_extended_write_error_parameter_at_least_once_print_
  void fss_extended_write_error_parameter_at_least_once(const fss_extended_write_main_t main) {

    if (main.error.verbosity == f_console_verbosity_quiet) {
      return;
    }

    flockfile(main.error.to.stream);

    fl_print_format("%c%[%sMust specify the '%]", main.error.to.stream, f_string_eol_s[0], main.error.context, main.error.prefix, main.error.context);
    fl_print_format("%[%s%s%]", main.error.to.stream, main.error.notable, f_console_symbol_long_enable_s, fss_extended_write_long_object, main.error.notable);
    fl_print_format("%[' parameter and the '%]", main.error.to.stream, main.error.context, main.error.prefix, main.error.context);
    fl_print_format("%[%s%s%]", main.error.to.stream, main.error.notable, f_console_symbol_long_enable_s, fss_extended_write_long_content, main.error.notable);
    fl_print_format("%[' parameter the same number of times when not specifying the '%]", main.error.to.stream, main.error.context, main.error.prefix, main.error.context);
    fl_print_format("%[%s%s%]", main.error.to.stream, main.error.notable, f_console_symbol_long_enable_s, fss_extended_write_long_partial, main.error.notable);
    fl_print_format("%[' parameter.%]%c", main.error.to.stream, main.error.context, main.error.context, f_string_eol_s[0]);

    funlockfile(main.error.to.stream);
  }
#endif // _di_fss_extended_write_error_parameter_at_least_once_print_

#ifndef _di_fss_extended_write_error_parameter_value_missing_print_
  void fss_extended_write_error_parameter_value_missing_print(const fss_extended_write_main_t main, const f_string_t symbol, const f_string_t parameter) {

    if (main.error.verbosity == f_console_verbosity_quiet) {
      return;
    }

    flockfile(main.error.to.stream);

    fl_print_format("%c%[%sThe parameter '%]", main.error.to.stream, f_string_eol_s[0], main.error.context, main.error.prefix, main.error.context);
    fl_print_format("%[%S%S%]", main.error.to.stream, main.error.notable, symbol, parameter, main.error.notable);
    fl_print_format("%[' was specified, but no value was given.%]%c", main.error.to.stream, main.error.context, main.error.context, f_string_eol_s[0]);

    funlockfile(main.error.to.stream);
  }
#endif // _di_fss_extended_write_error_parameter_value_missing_print_

#ifndef _di_fss_extended_write_error_parameter_unsupported_eol_print_
  void fss_extended_write_error_parameter_unsupported_eol_print(const fss_extended_write_main_t main) {

    if (main.error.verbosity == f_console_verbosity_quiet) {
      return;
    }

    flockfile(main.error.to.stream);

    fl_print_format("%c%[%sThis standard does not support end of line character '%]", main.error.to.stream, f_string_eol_s[0], main.error.context, main.error.prefix, main.error.context);
    fl_print_format("%[\\n%]", main.error.to.stream, main.error.notable, main.error.notable);
    fl_print_format("%[' in objects.%]%c", main.error.to.stream, main.error.context, main.error.context, f_string_eol_s[0]);

    funlockfile(main.error.to.stream);
  }
#endif // _di_fss_extended_write_error_parameter_unsupported_eol_print_

#ifndef _di_fss_extended_write_process_
  f_status_t fss_extended_write_process(const fss_extended_write_main_t main, const f_file_t output, const f_fss_quote_t quote, const f_string_static_t *object, const f_string_statics_t *contents, f_string_dynamic_t *buffer) {

    f_status_t status = F_none;
    f_state_t state = macro_f_state_t_initialize(fss_extended_write_common_allocation_large, fss_extended_write_common_allocation_small, 0, 0, 0, 0, 0);
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

      if (contents && contents->used) {
        if (main.parameters[fss_extended_write_parameter_trim].result == f_console_result_found) {
          complete = f_fss_complete_full_trim;
        }
        else {
          complete = f_fss_complete_full;
        }
      }

      status = fl_fss_extended_object_write_string(*object, quote, complete, state, &range, buffer);

      if (F_status_set_fine(status) == F_none_eol) {
        fss_extended_write_error_parameter_unsupported_eol_print(main);

        return F_status_set_error(F_supported_not);
      }

      if (F_status_is_error(status)) {
        fll_error_print(main.error, F_status_set_fine(status), "fl_fss_extended_object_write_string", F_true);

        return F_status_set_error(status);
      }
    }

    if (contents) {
      if (contents->used) {
        for (f_array_length_t i = 0; i < contents->used; ++i) {

          if (contents->array[i].used) {
            range.start = 0;
            range.stop = contents->array[i].used - 1;
          }
          else {
            range.start = 1;
            range.stop = 0;
          }

          status = fl_fss_extended_content_write_string(contents->array[i], quote, i + 1 < contents->used ? f_fss_complete_next : f_fss_complete_end, state, &range, buffer);

          if (F_status_set_fine(status) == F_none_eol) {
            fss_extended_write_error_parameter_unsupported_eol_print(main);

            return F_status_set_error(F_supported_not);
          }

          if (F_status_is_error(status)) {
            fll_error_print(main.error, F_status_set_fine(status), "fl_fss_extended_content_write_string", F_true);

            return F_status_set_error(status);
          }
        } // for
      }
    }
    else if (!object) {
      status = f_string_append(f_string_eol_s, 1, buffer);

      if (F_status_is_error(status)) {
        fll_error_print(main.error, F_status_set_fine(status), "f_string_append", F_true);

        return status;
      }
    }

    fll_print_dynamic(*buffer, output.stream);

    buffer->used = 0;
    return status;
  }
#endif // _di_fss_extended_write_process_

#ifndef _di_fss_extended_write_process_pipe_
  f_status_t fss_extended_write_process_pipe(const fss_extended_write_main_t main, const f_file_t output, const f_fss_quote_t quote, f_string_dynamic_t *buffer) {

    f_status_t status = F_none;
    f_status_t status_pipe = F_none;

    f_file_t input = f_file_t_initialize;

    input.id = f_type_descriptor_input;
    input.size_read = 2048;

    f_array_length_t i = 0;

    f_array_length_t total = 0;
    f_array_length_t previous = 0;
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
          fll_error_print(main.error, F_status_set_fine(status_pipe), "f_file_read_block", F_true);

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
            for (i = 0; i < contents.used; ++i) {
              contents.array[i].used = 0;
            } // for
          }

          object.used = 0;
          contents.used = 0;

          state = 0x1;
        }

        if (object.used + block.used > object.size) {
          status = f_string_dynamic_increase_by(block.used, &object);

          if (F_status_is_error(status)) {
            fll_error_print(main.error, F_status_set_fine(status), "f_string_dynamic_increase_by", F_true);
            break;
          }
        }

        for (; range.start <= range.stop; ++range.start) {

          if (block.string[range.start] == fss_extended_write_pipe_content_start) {
            state = 0x2;
            ++range.start;
            break;
          }

          if (block.string[range.start] == fss_extended_write_pipe_content_end) {
            state = 0x4;
            ++range.start;
            break;
          }

          if (block.string[range.start] == fss_extended_write_pipe_content_ignore) {
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
        if (contents.used + 1 > contents.size) {
          status = f_string_dynamics_increase_by(f_fss_default_allocation_step, &contents);

          if (F_status_is_error(status)) {
            fll_error_print(main.error, F_status_set_fine(status), "f_string_dynamics_increase_by", F_true);
            break;
          }
        }

        state = 0x3;
        ++contents.used;
      }

      if (state == 0x3) {
        if (range.start <= range.stop) {
          total = (range.stop - range.start) + 1;
        }
        else {
          total = 0;
        }

        if (total) {
          for (; range.start <= range.stop; ++range.start) {

            if (block.string[range.start] == fss_extended_write_pipe_content_start) {
              if (contents.used + 1 > contents.size) {
                status = f_string_dynamics_increase_by(f_fss_default_allocation_step, &contents);

                if (F_status_is_error(status)) {
                  fll_error_print(main.error, F_status_set_fine(status), "f_string_dynamics_increase_by", F_true);
                  break;
                }
              }

              ++contents.used;
              continue;
            }

            if (block.string[range.start] == fss_extended_write_pipe_content_end) {
              state = 0x4;
              ++range.start;
              break;
            }

            if (block.string[range.start] == fss_extended_write_pipe_content_ignore) {

              // this is not used by this program.
              continue;
            }

            if (F_status_set_fine(status) == F_none_eol) {
              fss_extended_write_error_parameter_unsupported_eol_print(main);

              status = F_status_set_error(F_supported_not);
              break;
            }

            if (contents.array[contents.used - 1].used + 1 > contents.array[contents.used - 1].size) {
              status = f_string_dynamic_increase_by(f_fss_default_allocation_step, &contents.array[contents.used - 1]);

              if (F_status_is_error(status)) {
                fll_error_print(main.error, F_status_set_fine(status), "f_string_dynamic_increase_by", F_true);
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
        status = fss_extended_write_process(main, output, quote, &object, &contents, buffer);
        if (F_status_is_error(status)) break;

        state = 0;
      }
    } // for

    // if the pipe ended before finishing, then attempt to wrap up.
    if (F_status_is_error_not(status) && status_pipe == F_none_eof && state) {
      status = fss_extended_write_process(main, output, quote, &object, &contents, buffer);
    }

    macro_f_string_dynamic_t_delete_simple(block);
    macro_f_string_dynamic_t_delete_simple(object);
    macro_f_string_dynamics_t_delete_simple(contents);
    return status;
  }
#endif // _di_fss_extended_write_process_pipe_

#ifdef __cplusplus
} // extern "C"
#endif
