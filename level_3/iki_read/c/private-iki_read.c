#include <level_3/iki_read.h>
#include "private-iki_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_iki_read_print_error_
  f_return_status iki_read_print_error(const fl_color_context context, const uint8_t verbosity, const f_status status, const f_string function, const bool fallback) {

    if (status == F_parameter) {
      if (verbosity != iki_read_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "ERROR: Invalid parameter when calling function ");
        fl_color_print(f_type_error, context.notable, context.reset, "%s", function);
        fl_color_print_line(f_type_error, context.error, context.reset, "().");
      }

      return F_none;
    }

    if (status == F_memory_allocation || status == F_memory_reallocation) {
      if (verbosity != iki_read_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "ERROR: Unable to allocate memory in function ");
        fl_color_print(f_type_error, context.notable, context.reset, "%s", function);
        fl_color_print_line(f_type_error, context.error, context.reset, "().");
      }

      return F_none;
    }

    if (status == F_buffer_too_large) {
      if (verbosity != iki_read_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "ERROR: Maximum buffer limit reached while processing ");
        fl_color_print(f_type_error, context.notable, context.reset, "%s", function);
        fl_color_print_line(f_type_error, context.error, context.reset, "().");
      }

      return F_none;
    }

    if (status == F_string_too_large) {
      if (verbosity != iki_read_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "ERROR: Maximum string limit reached while processing ");
        fl_color_print(f_type_error, context.notable, context.reset, "%s", function);
        fl_color_print_line(f_type_error, context.error, context.reset, "().");
      }

      return F_none;
    }

    if (fallback && verbosity != iki_read_verbosity_quiet) {
      fprintf(f_type_error, "%c", f_string_eol[0]);
      fl_color_print(f_type_error, context.error, context.reset, "UNKNOWN ERROR: (");
      fl_color_print(f_type_error, context.notable, context.reset, "%llu", status);
      fl_color_print(f_type_error, context.error, context.reset, ") in function ");
      fl_color_print(f_type_error, context.notable, context.reset, "%s", function);
      fl_color_print_line(f_type_error, context.error, context.reset, "().");
    }

    return F_unknown;
  }
#endif // _di_iki_read_print_error_

#ifndef _di_iki_read_print_error_file_
  bool iki_read_print_error_file(const fl_color_context context, const uint8_t verbosity, const f_status status, const f_string function, const f_string name, const f_string operation, const bool is_file, const bool fallback) {
    const f_string file_or_directory = is_file ? "file" : "directory";

    if (status == F_file_found_not) {
      if (verbosity != iki_read_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "ERROR: failed to find %s '", file_or_directory);
        fl_color_print(f_type_error, context.notable, context.reset, "%s", name);
        fl_color_print_line(f_type_error, context.error, context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_file_found) {
      if (verbosity != iki_read_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "ERROR: the %s '", file_or_directory);
        fl_color_print(f_type_error, context.notable, context.reset, "%s", name);
        fl_color_print_line(f_type_error, context.error, context.reset, "' already exists.");
      }

      return F_false;
    }

    if (status == F_parameter) {
      if (verbosity != iki_read_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "INTERNAL ERROR: Invalid parameter when calling ");
        fl_color_print(f_type_error, context.notable, context.reset, "%s", function);
        fl_color_print(f_type_error, context.error, context.reset, "() for the %s '", file_or_directory);
        fl_color_print(f_type_error, context.notable, context.reset, "%s", name);
        fl_color_print_line(f_type_error, context.error, context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_name) {
      if (verbosity != iki_read_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "ERROR: Invalid %s name '", file_or_directory);
        fl_color_print(f_type_error, context.notable, context.reset, "%s", name);
        fl_color_print_line(f_type_error, context.error, context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_memory_out) {
      if (verbosity != iki_read_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "CRITICAL ERROR: Unable to allocate memory, while trying to %s %s '", operation, file_or_directory);
        fl_color_print(f_type_error, context.notable, context.reset, "%s", name);
        fl_color_print_line(f_type_error, context.error, context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_number_overflow) {
      if (verbosity != iki_read_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "ERROR: Overflow while trying to %s %s '", operation, file_or_directory);
        fl_color_print(f_type_error, context.notable, context.reset, "%s", name);
        fl_color_print_line(f_type_error, context.error, context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_directory) {
      if (verbosity != iki_read_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "ERROR: Invalid directory while trying to %s %s '", operation, file_or_directory);
        fl_color_print(f_type_error, context.notable, context.reset, "%s", name);
        fl_color_print_line(f_type_error, context.error, context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_access_denied) {
      if (verbosity != iki_read_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "ERROR: Access denied while trying to %s %s '", operation, file_or_directory);
        fl_color_print(f_type_error, context.notable, context.reset, "%s", name);
        fl_color_print_line(f_type_error, context.error, context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_loop) {
      if (verbosity != iki_read_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "ERROR: Loop while trying to %s %s '", operation, file_or_directory);
        fl_color_print(f_type_error, context.notable, context.reset, "%s", name);
        fl_color_print_line(f_type_error, context.error, context.reset, "'.");
      }

      return F_false;
    }

    if (status == F_prohibited) {
      if (verbosity != iki_read_verbosity_quiet) {
        fprintf(f_type_error, "%c", f_string_eol[0]);
        fl_color_print(f_type_error, context.error, context.reset, "ERROR: Prohibited by system while trying to %s %s '", operation, file_or_directory);
        fl_color_print(f_type_error, context.notable, context.reset, "%s", name);
        fl_color_print_line(f_type_error, context.error, context.reset, "'.");
      }

      return F_false;
    }

    if (is_file) {
      if (status == F_directory_found_not) {
        if (verbosity != iki_read_verbosity_quiet) {
          fprintf(f_type_error, "%c", f_string_eol[0]);
          fl_color_print(f_type_error, context.error, context.reset, "ERROR: failed to %s %s '", operation, file_or_directory);
          fl_color_print(f_type_error, context.notable, context.reset, "%s", name);
          fl_color_print_line(f_type_error, context.error, context.reset, "' due to an invalid directory in the path.");
        }

        return F_false;
      }
    }
    else {
      if (status == F_directory_found_not) {
        if (verbosity != iki_read_verbosity_quiet) {
          fprintf(f_type_error, "%c", f_string_eol[0]);
          fl_color_print(f_type_error, context.error, context.reset, "ERROR: failed to %s %s '", operation, file_or_directory);
          fl_color_print(f_type_error, context.notable, context.reset, "%s", name);
          fl_color_print_line(f_type_error, context.error, context.reset, "' due to an invalid directory in the path.");
        }

        return F_false;
      }

      if (status == F_failure) {
        if (verbosity != iki_read_verbosity_quiet) {
          fprintf(f_type_error, "%c", f_string_eol[0]);
          fl_color_print(f_type_error, context.error, context.reset, "ERROR: failed to %s %s '", operation, file_or_directory);
          fl_color_print(f_type_error, context.notable, context.reset, "%s", name);
          fl_color_print_line(f_type_error, context.error, context.reset, "'.");
        }

        return F_false;
      }
    }

    if (iki_read_print_error(context, verbosity, status, function, F_false) == F_unknown && fallback && verbosity != iki_read_verbosity_quiet) {
      fprintf(f_type_error, "%c", f_string_eol[0]);
      fl_color_print(f_type_error, context.error, context.reset, "UNKNOWN ERROR: (");
      fl_color_print(f_type_error, context.notable, context.reset, "%llu", status);
      fl_color_print(f_type_error, context.error, context.reset, ") occurred while trying to %s %s '", operation, file_or_directory);
      fl_color_print(f_type_error, context.notable, context.reset, "%s", name);
      fl_color_print_line(f_type_error, context.error, context.reset, "'.");
    }

    return F_true;
  }
#endif // _di_iki_read_print_error_file_

#ifndef _di_iki_read_print_error_number_argument_
  void iki_read_print_error_number_argument(const fl_color_context context, const uint8_t verbosity, const f_status status, const f_string function, const f_string parameter, const f_string argument) {
    if (verbosity == iki_read_verbosity_quiet) return;

    fprintf(f_type_error, "%c", f_string_eol[0]);

    if (status == F_parameter) {
      fl_color_print(f_type_error, context.error, context.reset, "INTERNAL ERROR: Invalid parameter when calling ");
      fl_color_print(f_type_error, context.notable, context.reset, "%s()", function);
      fl_color_print_line(f_type_error, context.error, context.reset, ".");
    }
    else if (status == F_number) {
      fl_color_print(f_type_error, context.error, context.reset, "ERROR: The argument '");
      fl_color_print(f_type_error, context.notable, context.reset, "%s", argument);
      fl_color_print(f_type_error, context.error, context.reset, "' is not a valid number for the parameter '");
      fl_color_print(f_type_error, context.notable, context.reset, "%s%s", f_console_symbol_long_enable, parameter);
      fl_color_print_line(f_type_error, context.error, context.reset, "'.");
    }
    else if (status == F_number_underflow) {
      fl_color_print(f_type_error, context.error, context.reset, "ERROR: The argument '");
      fl_color_print(f_type_error, context.notable, context.reset, "%s", argument);
      fl_color_print(f_type_error, context.error, context.reset, "' is too small for the parameter '");
      fl_color_print(f_type_error, context.notable, context.reset, "%s%s", f_console_symbol_long_enable, parameter);
      fl_color_print_line(f_type_error, context.error, context.reset, "'.");
    }
    else if (status == F_number_overflow) {
      fl_color_print(f_type_error, context.error, context.reset, "ERROR: The argument '");
      fl_color_print(f_type_error, context.notable, context.reset, "%s", argument);
      fl_color_print(f_type_error, context.error, context.reset, "' is too large for the parameter '");
      fl_color_print(f_type_error, context.notable, context.reset, "%s%s", f_console_symbol_long_enable, parameter);
      fl_color_print_line(f_type_error, context.error, context.reset, "'.");
    }
    else if (status == F_number_negative) {
      fl_color_print(f_type_error, context.error, context.reset, "ERROR: The argument '");
      fl_color_print(f_type_error, context.notable, context.reset, "%s", argument);
      fl_color_print(f_type_error, context.error, context.reset, "' is negative, which is not allowed for the parameter '");
      fl_color_print(f_type_error, context.notable, context.reset, "%s%s", f_console_symbol_long_enable, parameter);
      fl_color_print_line(f_type_error, context.error, context.reset, "'.");
    }
    else if (status == F_number_positive) {
      fl_color_print(f_type_error, context.error, context.reset, "ERROR: The argument '");
      fl_color_print(f_type_error, context.notable, context.reset, "%s", argument);
      fl_color_print(f_type_error, context.error, context.reset, "' contains a '");
      fl_color_print(f_type_error, context.notable, context.reset, "+");
      fl_color_print(f_type_error, context.error, context.reset, "', which is not allowed for the parameter '");
      fl_color_print(f_type_error, context.notable, context.reset, "%s%s", f_console_symbol_long_enable, parameter);
      fl_color_print_line(f_type_error, context.error, context.reset, "'.");
    }
    else if (status == F_data_not) {
      fl_color_print(f_type_error, context.error, context.reset, "ERROR: The parameter '");
      fl_color_print(f_type_error, context.notable, context.reset, "%s%s", f_console_symbol_long_enable, parameter);
      fl_color_print_line(f_type_error, context.error, context.reset, "' must not be an empty string.");
    }
    else {
      fl_color_print(f_type_error, context.error, context.reset, "UNKNOWN ERROR: (");
      fl_color_print(f_type_error, context.notable, context.reset, "%llu", status);
      fl_color_print(f_type_error, context.error, context.reset, ") has occurred while calling ");
      fl_color_print(f_type_error, context.notable, context.reset, "%s()", function);
      fl_color_print(f_type_error, context.error, context.reset, "' for the parameter '");
      fl_color_print(f_type_error, context.notable, context.reset, "%s%s", f_console_symbol_long_enable, parameter);
      fl_color_print(f_type_error, context.error, context.reset, "' with the value '");
      fl_color_print(f_type_error, context.notable, context.reset, "%s", argument);
      fl_color_print_line(f_type_error, context.error, context.reset, "'.");
    }
  }
#endif // _di_iki_read_print_error_number_argument_

#ifndef _di_iki_read_process_at_
  f_return_status iki_read_process_at(const f_console_arguments arguments, const f_string file_name, iki_read_data *data, f_string_range *range) {
    if (data->parameters[iki_read_parameter_line].result != f_console_result_additional) return F_false;

    if (data->line < data->buffer.used) {
      f_string_length line = 0;

      range->start = 0;
      if (data->line > 0) {
        for (; line < data->line && range->start < data->buffer.used; range->start++) {
          if (data->buffer.string[range->start] == f_string_eol[0]) line++;
        } // for
      }

      range->stop = range->start;
      for (; range->stop < data->buffer.used; range->stop++) {
        if (data->buffer.string[range->stop] == f_string_eol[0]) break;
      } // for
    }
    else {
      range->start = data->buffer.used + 1;
    }

    return F_true;
  }
#endif // _di_iki_read_process_at_

#ifndef _di_iki_read_process_buffer_
  f_return_status iki_read_process_buffer(const f_console_arguments arguments, const f_string file_name, iki_read_data *data) {
    f_status status = F_none;

    f_iki_variable variable = f_iki_variable_initialize;
    f_iki_vocabulary vocabulary = f_iki_vocabulary_initialize;
    f_iki_content content = f_iki_content_initialize;

    if (data->parameters[iki_read_parameter_whole].result == f_console_result_found) {
      f_string_range buffer_range = f_macro_string_range_initialize(data->buffer.used);

      if (iki_read_process_at(arguments, file_name, data, &buffer_range)) {
        if (buffer_range.start > data->buffer.used) {
          return F_data_not;
        }
      }

      if (data->mode == iki_read_mode_content) {
        status = iki_read_process_buffer_ranges_whole(arguments, file_name, buffer_range, data, &variable, &vocabulary, &content, &content);
      }
      else if (data->mode == iki_read_mode_literal) {
        status = iki_read_process_buffer_ranges_whole(arguments, file_name, buffer_range, data, &variable, &vocabulary, &content, &variable);
      }
      else if (data->mode == iki_read_mode_object) {
        status = iki_read_process_buffer_ranges_whole(arguments, file_name, buffer_range, data, &variable, &vocabulary, &content, &vocabulary);
      }
    }
    else if (data->mode == iki_read_mode_total) {
      status = iki_read_process_buffer_total(arguments, file_name, data, &variable, &vocabulary, &content);
    }
    else {
      f_string_range buffer_range = f_macro_string_range_initialize(data->buffer.used);

      if (iki_read_process_at(arguments, file_name, data, &buffer_range)) {
        if (buffer_range.start > data->buffer.used) {
          return F_data_not;
        }
      }

      if (data->mode == iki_read_mode_content) {
        status = iki_read_process_buffer_ranges(arguments, file_name, data, &buffer_range, &variable, &vocabulary, &content, &content);
      }
      else if (data->mode == iki_read_mode_literal) {
        status = iki_read_process_buffer_ranges(arguments, file_name, data, &buffer_range, &variable, &vocabulary, &content, &variable);
      }
      else if (data->mode == iki_read_mode_object) {
        status = iki_read_process_buffer_ranges(arguments, file_name, data, &buffer_range, &variable, &vocabulary, &content, &vocabulary);
      }
    }

    f_macro_iki_variable_delete_simple(variable);
    f_macro_iki_vocabulary_delete_simple(vocabulary);
    f_macro_iki_content_delete_simple(content);

    return status;
  }
#endif // _di_iki_read_process_buffer_

#ifndef _di_iki_read_process_buffer_ranges_
  f_return_status iki_read_process_buffer_ranges(const f_console_arguments arguments, const f_string file_name, iki_read_data *data, f_string_range *buffer_range, f_iki_variable *variable, f_iki_vocabulary *vocabulary, f_iki_content *content, f_string_ranges *ranges) {
    f_status status = F_none;

    bool unmatched = F_true;

    status = fl_iki_read(&data->buffer, buffer_range, variable, vocabulary, content);
    if (F_status_is_error(status)) {
      iki_read_print_error(data->context, data->verbosity, F_status_set_fine(status), "fl_iki_read", F_true);
      return status;
    }

    if (data->parameters[iki_read_parameter_name].result == f_console_result_additional) {
      f_string_dynamic name = f_string_dynamic_initialize;

      f_array_length index = 0;
      f_array_length i = 0;
      f_array_length j = 0;

      buffer_range->start = 0;

      for (; i < data->parameters[iki_read_parameter_name].additional.used; i++) {
        index = data->parameters[iki_read_parameter_name].additional.array[i];
        name.used = 0;

        status = fl_string_append_nulless(arguments.argv[index], strlen(arguments.argv[index]), &name);
        if (F_status_is_error(status)) {
          iki_read_print_error(data->context, data->verbosity, F_status_set_fine(status), "fl_string_append_nulless", F_true);

          f_macro_string_dynamic_delete_simple(name);
          return status;
        }

        buffer_range->stop = name.used - 1;

        for (j = 0; j < vocabulary->used; j++) {
          status = fl_string_dynamic_partial_compare(name, data->buffer, *buffer_range, vocabulary->array[j]);

          if (status == F_equal_to) {
            unmatched = F_false;

            f_print_string_dynamic_partial(f_type_output, data->buffer, ranges->array[j]);
            printf("%c", f_string_eol[0]);
          }
        } // for
      } // for

      f_macro_string_dynamic_delete_simple(name);

      if (unmatched) return F_data_not;
    }
    else if (ranges->used) {
      for (f_array_length i = 0; i < ranges->used; i++) {
        f_print_string_dynamic_partial(f_type_output, data->buffer, ranges->array[i]);
        printf("%c", f_string_eol[0]);
      } // for
    }
    else {
      return F_data_not;
    }

    return F_none;
  }
#endif // _di_iki_read_process_buffer_ranges_

#ifndef _di_iki_read_process_buffer_ranges_whole_
  f_return_status iki_read_process_buffer_ranges_whole(const f_console_arguments arguments, const f_string file_name, const f_string_range buffer_range, iki_read_data *data, f_iki_variable *variable, f_iki_vocabulary *vocabulary, f_iki_content *content, f_string_ranges *ranges) {
    f_status status = F_none;
    f_string_range range = buffer_range;

    status = fl_iki_read(&data->buffer, &range, variable, vocabulary, content);
    if (F_status_is_error(status)) {
      iki_read_print_error(data->context, data->verbosity, F_status_set_fine(status), "fl_iki_read", F_true);
      return status;
    }

    if (!variable->used) {
      f_print_string_dynamic_partial(f_type_output, data->buffer, buffer_range);
      return F_none;
    }

    f_string_dynamics names = f_string_dynamics_initialize;
    f_string_range name_range = f_string_range_initialize;
    bool name_missed = F_true;

    if (data->parameters[iki_read_parameter_name].result == f_console_result_additional) {
      f_array_length i = 0;
      f_array_length j = 0;
      f_string_length length_argument = 0;

      for (f_array_length index = 0; i < data->parameters[iki_read_parameter_name].additional.used; i++) {
        index = data->parameters[iki_read_parameter_name].additional.array[i];
        length_argument = strnlen(arguments.argv[index], f_console_length_size);

        for (j = 0, name_missed = F_true; j < names.used; j++) {
          status = fl_string_compare(arguments.argv[index], names.array[j].string, length_argument, names.array[j].used);

          if (status == F_equal_to) {
            name_missed = F_false;
            break;
          }
        } // for

        if (name_missed) {
          if (names.used + 1 > names.size) {
            if (names.used + f_iki_default_allocation_step > f_array_length_size) {
              if (names.used + 1 > names.size > f_array_length_size) {
                iki_read_print_error(data->context, data->verbosity, F_buffer_too_large, "iki_read_process_buffer_ranges_whole", F_true);

                f_macro_string_dynamics_delete_simple(names);
                return F_status_set_error(F_buffer_too_large);
              }
              else {
                f_macro_string_dynamics_resize(status, names, names.used + 1);
              }
            }
            else {
              f_macro_string_dynamics_resize(status, names, names.used + f_iki_default_allocation_step);
            }

            if (F_status_is_error(status)) {
              iki_read_print_error(data->context, data->verbosity, F_status_set_fine(status), "iki_read_process_buffer_ranges_whole", F_true);

              f_macro_string_dynamics_delete_simple(names);
              return status;
            }
          }

          status = fl_string_append_nulless(arguments.argv[index], length_argument, &names.array[names.used]);
          if (F_status_is_error(status)) {
            iki_read_print_error(data->context, data->verbosity, F_status_set_fine(status), "fl_string_append_nulless", F_true);

            f_macro_string_dynamics_delete_simple(names);
            return status;
          }

          names.used++;
        }
      } // for
    }

    f_string_length i = buffer_range.start;
    f_array_length j = 0;
    f_array_length k = 0;

    range = buffer_range;
    name_range.start = 0;

    while (i <= range.stop && j < variable->used) {
      if (i < variable->array[j].start) {
        range.stop = variable->array[j].start - 1;

        f_print_string_dynamic_partial(f_type_output, data->buffer, range);

        range.start = variable->array[j].stop + 1;
        range.stop = buffer_range.stop;

        i = variable->array[j].start;
      }

      // @todo handle expansion and substitution.
      if (names.used) {
        name_missed = F_true;

        for (k = 0; k < names.used; k++) {
          name_range.stop = names.array[k].used - 1;

          status = fl_string_dynamic_partial_compare(data->buffer, names.array[k], vocabulary->array[j], name_range);

          if (status == F_equal_to) {
            name_missed = F_false;
            break;
          }
        } // for

        if (name_missed) {
          f_print_string_dynamic_partial(f_type_output, data->buffer, variable->array[j]);
        }
        else {
          f_print_string_dynamic_partial(f_type_output, data->buffer, ranges->array[j]);
        }
      }
      else {
        f_print_string_dynamic_partial(f_type_output, data->buffer, ranges->array[j]);
      }

      i = variable->array[j].stop + 1;
      j++;
    } // while

    if (i <= buffer_range.stop) {
      range.start = i;
      f_print_string_dynamic_partial(f_type_output, data->buffer, range);
    }

    f_macro_string_dynamics_delete_simple(names);
    return F_none;
  }
#endif // _di_iki_read_process_buffer_ranges_whole_

#ifndef _di_iki_read_process_buffer_total_
  f_return_status iki_read_process_buffer_total(const f_console_arguments arguments, const f_string file_name, iki_read_data *data, f_iki_variable *variable, f_iki_vocabulary *vocabulary, f_iki_content *content) {
    f_status status = F_none;
    f_string_range range = f_macro_string_range_initialize(data->buffer.used);

    if (iki_read_process_at(arguments, file_name, data, &range)) {
      if (range.start > data->buffer.used) {
        printf("0\n");
        return F_none;
      }
    }

    status = fl_iki_read(&data->buffer, &range, variable, vocabulary, content);
    if (F_status_is_error(status)) {
      iki_read_print_error(data->context, data->verbosity, F_status_set_fine(status), "fl_iki_read", F_true);
      return status;
    }

    f_array_length total = 0;

    if (data->parameters[iki_read_parameter_name].result == f_console_result_additional) {
      f_string_dynamic name = f_string_dynamic_initialize;

      f_array_length index = 0;
      f_array_length i = 0;
      f_array_length j = 0;

      range.start = 0;

      for (; i < data->parameters[iki_read_parameter_name].additional.used; i++) {
        index = data->parameters[iki_read_parameter_name].additional.array[i];
        name.used = 0;

        status = fl_string_append_nulless(arguments.argv[index], strlen(arguments.argv[index]), &name);
        if (F_status_is_error(status)) {
          iki_read_print_error(data->context, data->verbosity, F_status_set_fine(status), "fl_string_append_nulless", F_true);

          f_macro_string_dynamic_delete_simple(name);
          return status;
        }

        range.stop = name.used - 1;

        for (j = 0; j < vocabulary->used; j++) {
          status = fl_string_dynamic_partial_compare(name, data->buffer, range, vocabulary->array[j]);

          if (status == F_equal_to) total++;
        } // for
      } // for

      f_macro_string_dynamic_delete_simple(name);
    }
    else {
      total = variable->used;
    }

    printf("%llu\n", total);

    return F_none;
  }
#endif // _di_iki_read_process_buffer_total_

#ifdef __cplusplus
} // extern "C"
#endif
