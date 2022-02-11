#include "fss_extended_write.h"
#include "private-common.h"
#include "private-write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_extended_write_error_parameter_at_least_once_print_
  void fss_extended_write_error_parameter_at_least_once(fll_program_data_t * const main) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) {
      return;
    }

    flockfile(main->error.to.stream);

    fl_print_format("%r%[%QMust specify the '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
    fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_extended_write_long_object_s, main->error.notable);
    fl_print_format("%[' parameter and the '%]", main->error.to.stream, main->error.context, main->error.context);
    fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_extended_write_long_content_s, main->error.notable);
    fl_print_format("%[' parameter the same number of times when not specifying the '%]", main->error.to.stream, main->error.context, main->error.context);
    fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_extended_write_long_partial_s, main->error.notable);
    fl_print_format("%[' parameter.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

    funlockfile(main->error.to.stream);
  }
#endif // _di_fss_extended_write_error_parameter_at_least_once_print_

#ifndef _di_fss_extended_write_error_parameter_value_missing_print_
  void fss_extended_write_error_parameter_value_missing_print(fll_program_data_t * const main, const f_string_static_t symbol, const f_string_static_t parameter) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) {
      return;
    }

    flockfile(main->error.to.stream);

    fl_print_format("%r%[%QThe parameter '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
    fl_print_format("%[%r%r%]", main->error.to.stream, main->error.notable, symbol, parameter, main->error.notable);
    fl_print_format("%[' is specified, but no value is given.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

    funlockfile(main->error.to.stream);
  }
#endif // _di_fss_extended_write_error_parameter_value_missing_print_

#ifndef _di_fss_extended_write_error_parameter_unsupported_eol_print_
  void fss_extended_write_error_parameter_unsupported_eol_print(fll_program_data_t * const main) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) {
      return;
    }

    flockfile(main->error.to.stream);

    fl_print_format("%r%[%QThis standard does not support end of line character '%]", main->error.to.stream, f_string_eol_s, main->error.context, main->error.prefix, main->error.context);
    fl_print_format("%[\\n%]", main->error.to.stream, main->error.notable, main->error.notable);
    fl_print_format("%[' in objects.%]%r", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s);

    funlockfile(main->error.to.stream);
  }
#endif // _di_fss_extended_write_error_parameter_unsupported_eol_print_

#ifndef _di_fss_extended_write_process_
  f_status_t fss_extended_write_process(fll_program_data_t * const main, const f_file_t output, const f_fss_quote_t quote, const f_string_static_t *object, const f_string_statics_t *contents, f_string_dynamic_t *buffer) {

    f_status_t status = F_none;
    f_state_t state = macro_f_state_t_initialize(fss_extended_write_common_allocation_large_d, fss_extended_write_common_allocation_small_d, 0, 0, 0, 0, 0);
    f_string_range_t range = f_string_range_t_initialize;

    if (object) {
      uint8_t complete = f_fss_complete_none_e;

      if (object->used) {
        range.start = 0;
        range.stop = object->used - 1;
      }
      else {
        range.start = 1;
        range.stop = 0;
      }

      if (contents && contents->used) {
        if (main->parameters.array[fss_extended_write_parameter_trim_e].result == f_console_result_found_e) {
          complete = f_fss_complete_full_trim_e;
        }
        else {
          complete = f_fss_complete_full_e;
        }
      }

      status = fl_fss_extended_object_write(*object, quote, complete, state, &range, buffer);

      if (F_status_set_fine(status) == F_none_eol) {
        fss_extended_write_error_parameter_unsupported_eol_print(main);

        return F_status_set_error(F_supported_not);
      }

      if (F_status_is_error(status)) {
        fll_error_print(main->error, F_status_set_fine(status), "fl_fss_extended_object_write", F_true);

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

          status = fl_fss_extended_content_write(contents->array[i], quote, i + 1 < contents->used ? f_fss_complete_next_e : f_fss_complete_end_e, state, &range, buffer);

          if (F_status_set_fine(status) == F_none_eol) {
            fss_extended_write_error_parameter_unsupported_eol_print(main);

            return F_status_set_error(F_supported_not);
          }

          if (F_status_is_error(status)) {
            fll_error_print(main->error, F_status_set_fine(status), "fl_fss_extended_content_write", F_true);

            return F_status_set_error(status);
          }
        } // for
      }
    }
    else if (!object) {
      status = f_string_dynamic_append(f_string_eol_s, buffer);

      if (F_status_is_error(status)) {
        fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_append", F_true);

        return status;
      }
    }

    fll_print_dynamic(*buffer, output.stream);

    buffer->used = 0;

    return status;
  }
#endif // _di_fss_extended_write_process_

#ifndef _di_fss_extended_write_process_pipe_
  f_status_t fss_extended_write_process_pipe(fll_program_data_t * const main, const f_file_t output, const f_fss_quote_t quote, f_string_dynamic_t *buffer) {

    f_status_t status = F_none;
    f_status_t status_pipe = F_none;

    f_file_t input = f_file_t_initialize;

    input.id = F_type_descriptor_input_d;
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

    for (uint16_t signal_check = 0; ; ) {

      if (!((++signal_check) % fss_extended_write_signal_check_d)) {
        if (fss_extended_write_signal_received(main)) {
          return F_status_set_error(F_interrupt);
        }

        signal_check = 0;
      }

      if (range.start > range.stop) {
        if (status_pipe == F_none_eof) break;

        block.used = 0;

        status_pipe = f_file_read_block(input, &block);

        if (F_status_is_error(status_pipe)) {
          fll_error_print(main->error, F_status_set_fine(status_pipe), "f_file_read_block", F_true);

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
            fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_increase_by", F_true);
            break;
          }
        }

        for (; range.start <= range.stop; ++range.start) {

          if (block.string[range.start] == fss_extended_write_pipe_content_start_s.string[0]) {
            state = 0x2;
            ++range.start;

            break;
          }

          if (block.string[range.start] == fss_extended_write_pipe_content_end_s.string[0]) {
            state = 0x4;
            ++range.start;

            break;
          }

          if (block.string[range.start] == fss_extended_write_pipe_content_ignore_s.string[0]) {

            // This is not used by objects.
            continue;
          }

          object.string[object.used++] = block.string[range.start];
        } // for

        if (F_status_is_error(status)) break;

        // If the start of content was not found, then fetch the next block.
        if (state == 0x1) continue;

        // If the end of the current block is reached, fetch the next block.
        if (range.start > range.stop) continue;
      }

      if (state == 0x2) {
        if (contents.used + 1 > contents.size) {
          status = f_string_dynamics_increase_by(F_fss_default_allocation_step_d, &contents);

          if (F_status_is_error(status)) {
            fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamics_increase_by", F_true);
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

            if (block.string[range.start] == fss_extended_write_pipe_content_start_s.string[0]) {
              if (contents.used + 1 > contents.size) {
                status = f_string_dynamics_increase_by(F_fss_default_allocation_step_d, &contents);

                if (F_status_is_error(status)) {
                  fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamics_increase_by", F_true);

                  break;
                }
              }

              ++contents.used;

              continue;
            }

            if (block.string[range.start] == fss_extended_write_pipe_content_end_s.string[0]) {
              state = 0x4;
              ++range.start;

              break;
            }

            if (block.string[range.start] == fss_extended_write_pipe_content_ignore_s.string[0]) {

              // This is not used by this program.
              continue;
            }

            if (F_status_set_fine(status) == F_none_eol) {
              fss_extended_write_error_parameter_unsupported_eol_print(main);

              status = F_status_set_error(F_supported_not);

              break;
            }

            if (contents.array[contents.used - 1].used + 1 > contents.array[contents.used - 1].size) {
              status = f_string_dynamic_increase_by(F_fss_default_allocation_step_d, &contents.array[contents.used - 1]);

              if (F_status_is_error(status)) {
                fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_increase_by", F_true);

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

    // If the pipe ended before finishing, then attempt to wrap up.
    if (F_status_is_error_not(status) && status_pipe == F_none_eof && state) {
      status = fss_extended_write_process(main, output, quote, &object, &contents, buffer);
    }

    f_string_dynamic_resize(0, &block);
    f_string_dynamic_resize(0, &object);
    f_string_dynamics_resize(0, &contents);

    return status;
  }
#endif // _di_fss_extended_write_process_pipe_

#ifdef __cplusplus
} // extern "C"
#endif
