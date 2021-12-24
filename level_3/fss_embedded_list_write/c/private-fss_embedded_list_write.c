#include "fss_embedded_list_write.h"
#include "private-common.h"
#include "private-fss_embedded_list_write.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_embedded_list_write_error_parameter_same_times_print_
  void fss_embedded_list_write_error_parameter_same_times_print(fss_embedded_list_write_main_t * const main) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) {
      return;
    }

    flockfile(main->error.to.stream);

    fl_print_format("%c%[%sMust specify the '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
    fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_embedded_list_write_long_object_s, main->error.notable);
    fl_print_format("%[' parameter and the '%]", main->error.to.stream, main->error.context, main->error.prefix, main->error.context);
    fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_embedded_list_write_long_content_s, main->error.notable);
    fl_print_format("%[' parameter the same number of times when not specifying the '%]", main->error.to.stream, main->error.context, main->error.prefix, main->error.context);
    fl_print_format("%[%s%s%]", main->error.to.stream, main->error.notable, f_console_symbol_long_enable_s, fss_embedded_list_write_long_partial_s, main->error.notable);
    fl_print_format("%[' parameter.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

    funlockfile(main->error.to.stream);
  }
#endif // _di_fss_embedded_list_write_error_parameter_same_times_print_

#ifndef _di_fss_embedded_list_write_error_parameter_unsupported_eol_print_
  void fss_embedded_list_write_error_parameter_unsupported_eol_print(fss_embedded_list_write_main_t * const main) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) {
      return;
    }

    flockfile(main->error.to.stream);

    fl_print_format("%c%[%sThis standard does not support end of line character '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
    fl_print_format("%[\\n%]", main->error.to.stream, main->error.notable, main->error.notable);
    fl_print_format("%[' in objects.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

    funlockfile(main->error.to.stream);
  }
#endif // _di_fss_embedded_list_write_error_parameter_unsupported_eol_print_

#ifndef _di_fss_embedded_list_write_error_parameter_value_missing_print_
  void fss_embedded_list_write_error_parameter_value_missing_print(fss_embedded_list_write_main_t * const main, const f_string_t symbol, const f_string_t parameter) {

    if (main->error.verbosity == f_console_verbosity_quiet_e) {
      return;
    }

    flockfile(main->error.to.stream);

    fl_print_format("%c%[%sThe parameter '%]", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context);
    fl_print_format("%[%S%S%]", main->error.to.stream, main->error.notable, symbol, parameter, main->error.notable);
    fl_print_format("%[' is specified, but no value is given.%]%c", main->error.to.stream, main->error.context, main->error.context, f_string_eol_s[0]);

    funlockfile(main->error.to.stream);
  }
#endif // _di_fss_embedded_list_write_error_parameter_value_missing_print_

#ifndef _di_fss_embedded_list_write_process_
  f_status_t fss_embedded_list_write_process(fss_embedded_list_write_main_t * const main, const f_file_t output, const f_fss_quote_t quote, const f_string_static_t *object, const f_string_static_t *content, const f_string_ranges_t *ignore, f_string_dynamic_t *buffer) {

    f_status_t status = F_none;
    f_state_t state = macro_f_state_t_initialize(fss_embedded_list_write_common_allocation_large_d, fss_embedded_list_write_common_allocation_small_d, 0, 0, 0, 0, 0);
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

      if (content) {
        if (main->parameters[fss_embedded_list_write_parameter_trim_e].result == f_console_result_found_e) {
          complete = f_fss_complete_full_trim_e;
        }
        else {
          complete = f_fss_complete_full_e;
        }
      }

      status = fl_fss_embedded_list_object_write(*object, complete, state, &range, buffer);

      if (F_status_set_fine(status) == F_none_eol) {
        fss_embedded_list_write_error_parameter_unsupported_eol_print(main);

        return F_status_set_error(F_supported_not);
      }

      if (F_status_is_error(status)) {
        fll_error_print(main->error, F_status_set_fine(status), "fl_fss_embedded_list_object_write", F_true);

        return status;
      }
    }

    if (content && content->used) {
      range.start = 0;
      range.stop = content->used - 1;

      status = fl_fss_embedded_list_content_write(*content, object ? f_fss_complete_full_e : f_fss_complete_none_e, &main->prepend, ignore, state, &range, buffer);

      if (F_status_is_error(status)) {
        fll_error_print(main->error, F_status_set_fine(status), "fl_fss_embedded_list_content_write", F_true);

        return status;
      }
    }

    if (!object || !content) {
      status = f_string_append(f_string_eol_s, 1, buffer);

      if (F_status_is_error(status)) {
        fll_error_print(main->error, F_status_set_fine(status), "f_string_append", F_true);

        return status;
      }
    }

    fll_print_dynamic(*buffer, output.stream);

    buffer->used = 0;
    return status;
  }
#endif // _di_fss_embedded_list_write_process_

#ifndef _di_fss_embedded_list_write_process_pipe_
  f_status_t fss_embedded_list_write_process_pipe(fss_embedded_list_write_main_t * const main, const f_file_t output, const f_fss_quote_t quote, f_string_dynamic_t *buffer, f_string_ranges_t *ignore) {

    f_status_t status = F_none;
    f_status_t status_pipe = F_none;

    f_file_t input = f_file_t_initialize;

    input.id = F_type_descriptor_input_d;
    input.size_read = 2048;

    f_array_length_t total = 0;
    f_array_length_t previous = 0;

    f_string_range_t range = f_string_range_t_initialize;
    f_string_range_t range_ignore = f_string_range_t_initialize;

    f_string_dynamic_t block = f_string_dynamic_t_initialize;
    f_string_dynamic_t object = f_string_dynamic_t_initialize;
    f_string_dynamic_t content = f_string_dynamic_t_initialize;

    // 0x0 = start new object/content set, 0x1 = processing object, 0x2 = processing content, 0x3 = end object/content set.
    uint8_t state = 0;

    for (;;) {

      if (fss_embedded_list_write_signal_received(main)) {
        macro_f_string_dynamic_t_delete_simple(block);
        macro_f_string_dynamic_t_delete_simple(object);
        macro_f_string_dynamic_t_delete_simple(content);

        return F_status_set_error(F_interrupt);
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
          object.used = 0;
          content.used = 0;

          state = 0x1;

          range_ignore.start = 1;
          range_ignore.stop = 0;
        }

        if (object.used + block.used > object.size) {
          status = f_string_dynamic_increase_by(block.used, &object);

          if (F_status_is_error(status)) {
            fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_increase_by", F_true);
            break;
          }
        }

        for (; range.start <= range.stop; ++range.start) {

          if (block.string[range.start] == fss_embedded_list_write_pipe_content_start_s) {
            state = 0x2;
            ++range.start;
            break;
          }

          if (block.string[range.start] == fss_embedded_list_write_pipe_content_end_s) {
            state = 0x3;
            ++range.start;
            break;
          }

          if (block.string[range.start] == fss_embedded_list_write_pipe_content_ignore_s) {
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
              fll_error_print(main->error, F_status_set_fine(status), "f_string_dynamic_increase_by", F_true);
              break;
            }
          }

          for (; range.start <= range.stop; ++range.start) {

            if (block.string[range.start] == fss_embedded_list_write_pipe_content_start_s) {
              if (main->error.verbosity != f_console_verbosity_quiet_e) {
                fll_print_format("%c%[%sThis standard only supports one content per object.%]%c", main->error.to.stream, f_string_eol_s[0], main->error.context, main->error.prefix, main->error.context, f_string_eol_s[0]);
              }

              status = F_status_set_error(F_supported_not);
              break;
            }

            if (block.string[range.start] == fss_embedded_list_write_pipe_content_end_s) {
              state = 0x3;
              ++range.start;
              break;
            }

            if (block.string[range.start] == fss_embedded_list_write_pipe_content_ignore_s) {
              if (ignore) {
                if (range_ignore.start > range_ignore.stop) {
                  range_ignore.start = content.used;
                  range_ignore.stop = content.used;
                }
                else {
                  if (ignore->used + 1 > ignore->size) {
                    if (ignore->size + F_fss_default_allocation_step_d > F_array_length_t_size_d) {
                      if (ignore->size + 1 > F_array_length_t_size_d) {
                        fll_error_print(main->error, F_string_too_large, "fss_embedded_list_write_process_pipe", F_true);

                        status = F_status_set_error(F_string_too_large);
                        break;
                      }

                      macro_f_string_ranges_t_resize(status, (*ignore), ignore->size + 1);
                    }
                    else {
                      macro_f_string_ranges_t_resize(status, (*ignore), ignore->size + F_fss_default_allocation_step_d);
                    }

                    if (F_status_is_error(status)) {
                      fll_error_print(main->error, F_string_too_large, "fss_embedded_list_write_process_pipe", F_true);
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
        status = fss_embedded_list_write_process(main, output, quote, &object, &content, ignore, buffer);
        if (F_status_is_error(status)) break;

        state = 0;
      }
    } // for

    // if the pipe ended before finishing, then attempt to wrap up.
    if (F_status_is_error_not(status) && status_pipe == F_none_eof && state) {
      status = fss_embedded_list_write_process(main, output, quote, &object, &content, ignore, buffer);
    }

    macro_f_string_dynamic_t_delete_simple(block);
    macro_f_string_dynamic_t_delete_simple(object);
    macro_f_string_dynamic_t_delete_simple(content);
    return status;
  }
#endif // _di_fss_embedded_list_write_process_pipe_

#ifndef _di_fss_embedded_list_write_process_parameter_ignore_
  f_status_t fss_embedded_list_write_process_parameter_ignore(fss_embedded_list_write_main_t * const main, const f_console_arguments_t *arguments, const f_array_lengths_t contents, const f_array_length_t location, f_string_ranges_t *ignore) {

    f_status_t status = F_none;

    f_array_length_t i = 0;
    f_array_length_t l = 0;
    f_array_length_t index = 0;

    f_string_range_t range = f_string_range_t_initialize;

    f_number_unsigned_t number = 0;

    range.start = 0;

    for (; i < main->parameters[fss_embedded_list_write_parameter_ignore_e].locations.used; ++i) {

      if (fss_embedded_list_write_signal_received(main)) {
        return F_status_set_error(F_interrupt);
      }

      l = main->parameters[fss_embedded_list_write_parameter_ignore_e].locations.array[i];

      if (l < contents.array[location]) continue;
      if (location + 1 < contents.used && l > contents.array[location + 1]) continue;

      if (ignore->used + 1 > ignore->size) {
        if (ignore->size + F_fss_default_allocation_step_d > F_array_length_t_size_d) {
          if (ignore->size + 1 > F_array_length_t_size_d) {
            fll_error_print(main->error, F_string_too_large, "fss_embedded_list_write_process_parameter_ignore", F_true);
            return F_status_set_error(F_string_too_large);
          }

          macro_f_string_ranges_t_resize(status, (*ignore), ignore->size + 1);
        }
        else {
          macro_f_string_ranges_t_resize(status, (*ignore), ignore->size + F_fss_default_allocation_step_d);
        }

        if (F_status_is_error(status)) {
          fll_error_print(main->error, F_status_set_fine(status), "fss_embedded_list_write_process_parameter_ignore", F_true);

          return status;
        }
      }

      index = main->parameters[fss_embedded_list_write_parameter_ignore_e].values.array[i * 2];

      range.start = 0;
      range.stop = strnlen(arguments->argv[index], f_console_parameter_size) - 1;

      // allow and ignore the positive sign.
      if (range.stop > 0 && arguments->argv[index][0] == '+') {
        range.start = 1;
      }

      status = fl_conversion_string_to_number_unsigned(arguments->argv[index], range, &number);

      if (F_status_is_error(status)) {
        fll_error_parameter_integer_print(main->error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, fss_embedded_list_write_long_ignore_s, arguments->argv[index]);

        return status;
      }

      ignore->array[ignore->used].start = number;

      index = main->parameters[fss_embedded_list_write_parameter_ignore_e].values.array[(i * 2) + 1];

      range.start = 0;
      range.stop = strnlen(arguments->argv[index], f_console_parameter_size) - 1;

      // allow and ignore the positive sign.
      if (range.stop > 0 && arguments->argv[index][0] == '+') {
        range.start = 1;
      }

      status = fl_conversion_string_to_number_unsigned(arguments->argv[index], range, &number);

      if (F_status_is_error(status)) {
        fll_error_parameter_integer_print(main->error, F_status_set_fine(status), "fl_conversion_string_to_number_unsigned", F_true, fss_embedded_list_write_long_ignore_s, arguments->argv[index]);

        return status;
      }

      ignore->array[ignore->used++].stop = number;
    } // for

    return F_none;
  }
#endif // _di_fss_embedded_list_write_process_parameter_ignore_

#ifdef __cplusplus
} // extern "C"
#endif
