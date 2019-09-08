#include <level_3/fss_extended_read.h>
#include "private-fss_extended_read.h"

#ifndef _di_fss_extended_read_main_process_file_
  f_return_status fss_extended_read_main_process_file(const f_console_arguments arguments, fss_extended_read_data *data, const f_string filename, const f_string_length target, const f_string_length select) {
    f_status status = f_none;
    f_status status2 = f_none;

    f_string_length current = 0;
    f_string_length found = 0;

    {
      f_string_location input = f_string_location_initialize;

      input.start = 0;
      input.stop = data->buffer.used - 1;

      status = fll_fss_extended_read(&data->buffer, &input, &data->objects, &data->contents);

      if (f_status_is_error(status)) {
        status = f_status_set_fine(status);

        if (status == f_invalid_parameter) {
          fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: Invalid parameter when calling fll_fss_extended_read() for the file '%s'", filename);
        }
        else if (status == f_allocation_error || status == f_reallocation_error) {
          fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: unable to allocate memory");
        }
        else if (status == f_incomplete_utf_on_stop) {
          fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ENCODING ERROR: error occured on invalid UTF-8 character at stop position (at %d).", input.start);
        }
        else if (status == f_incomplete_utf_on_eos) {
          fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ENCODING ERROR: error occured on invalid UTF-8 character at end of string (at %d).", input.start);
        }
        else {
          fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling fll_fss_extended_read() for the file '%s'", f_status_set_error(status), filename);
        }

        fss_extended_read_delete_data(data);
        return f_status_set_error(status);
      }
      else if (status == f_no_data_on_stop || status == f_no_data_on_eos) {
        // clear buffers, then attempt the next file
        f_macro_fss_contents_delete(status2, data->contents);
        f_macro_fss_objects_delete(status2, data->objects);
        f_macro_string_dynamic_delete(status2, data->buffer);

        return f_status_set_warning(status);
      }
    }

    // now that all of the files have been read, process the objects and contents
    if (data->parameters[fss_extended_read_parameter_total].result == f_console_result_found && data->parameters[fss_extended_read_parameter_name].result == f_console_result_none) {
      fprintf(f_standard_output, "%u\n", (unsigned int) data->objects.used);
    }
    else {
      current = 0;

      if (data->parameters[fss_extended_read_parameter_name].result == f_console_result_none) {
        if (data->parameters[fss_extended_read_parameter_object].result == f_console_result_none) {
          for (; current < data->objects.used; current++) {
            if (data->parameters[fss_extended_read_parameter_count].result == f_console_result_none || (data->parameters[fss_extended_read_parameter_count].result == f_console_result_additional && found == target)) {
              if (data->contents.array[current].used > select) {
                f_print_string_dynamic_partial(f_standard_output, data->buffer, data->contents.array[current].array[select]);
                fprintf(f_standard_output, "\n");
              }
              else {
                // for all objects with no data, print a newline
                fprintf(f_standard_output, "\n");
              }
            }

            if (data->parameters[fss_extended_read_parameter_count].result == f_console_result_additional) {
              if (found == target) {
                break;
              }
              else {
                found++;
              }
            }
          } // for
        }
        else {
          for (; current < data->objects.used; current++) {
            if (data->parameters[fss_extended_read_parameter_count].result == f_console_result_none || (data->parameters[fss_extended_read_parameter_count].result == f_console_result_additional && found == target)) {
              f_print_string_dynamic_partial(f_standard_output, data->buffer, data->objects.array[current]);
              fprintf(f_standard_output, "\n");
            }

            if (data->parameters[fss_extended_read_parameter_count].result == f_console_result_additional) {
              if (found == target) {
                break;
              }
              else {
                found++;
              }
            }
          } // for
        }
      } else {
        current = 0;

        f_string_length total = 0;
        f_string_length name_length = 0;
        f_string_length argv_length = 0;

        if (data->parameters[fss_extended_read_parameter_name].result == f_console_result_additional) {
          argv_length = strlen(arguments.argv[data->parameters[fss_extended_read_parameter_name].additional.array[0]]);

          if (data->parameters[fss_extended_read_parameter_object].result == f_console_result_none) {
            for (; current < data->objects.used; current++) {
              name_length = data->objects.array[current].stop - data->objects.array[current].start + 1;

              if (name_length == argv_length) {
                if (fl_string_compare(data->buffer.string + data->objects.array[current].start, arguments.argv[data->parameters[fss_extended_read_parameter_name].additional.array[0]], name_length, argv_length) == f_equal_to) {

                  if (data->parameters[fss_extended_read_parameter_count].result == f_console_result_none || (data->parameters[fss_extended_read_parameter_count].result == f_console_result_additional && found == target)) {
                    if (data->parameters[fss_extended_read_parameter_total].result == f_console_result_found) {
                      total++;
                    }
                    else {
                      if (data->contents.array[current].used > select) {
                        f_print_string_dynamic_partial(f_standard_output, data->buffer, data->contents.array[current].array[select]);
                        fprintf(f_standard_output, "\n");
                      }
                      else {
                        // for all objects with no data, print a newline
                        fprintf(f_standard_output, "\n");
                      }
                    }
                  }

                  if (data->parameters[fss_extended_read_parameter_count].result == f_console_result_additional) {
                    if (data->parameters[fss_extended_read_parameter_total].result == f_console_result_found) {
                      total = data->contents.array[current].used;
                    }

                    if (found == target) {
                      break;
                    }
                    else {
                      found++;
                    }
                  }
                }
              }
            } // for

            if (data->parameters[fss_extended_read_parameter_total].result == f_console_result_found) {
              fprintf(f_standard_output, f_string_length_printf "\n", total);
            }
          }
          else {
            // when and because the object parameter is specified, the name parameter refers to the content instead of the object
            // therefore, make the search on the content and display the object
            for (; current < data->contents.used; current++) {
              if (data->contents.array[current].used > select) {
                name_length = data->contents.array[current].array[select].stop - data->contents.array[current].array[select].start + 1;

                if (name_length == argv_length) {
                  if (fl_string_compare(data->buffer.string + data->contents.array[current].array[select].start, arguments.argv[data->parameters[fss_extended_read_parameter_name].additional.array[0]], name_length, argv_length) == f_equal_to) {
                    if (data->parameters[fss_extended_read_parameter_count].result == f_console_result_none || (data->parameters[fss_extended_read_parameter_count].result == f_console_result_additional && found == target)) {
                      f_print_string_dynamic_partial(f_standard_output, data->buffer, data->objects.array[current]);
                      fprintf(f_standard_output, "\n");
                    }

                    if (data->parameters[fss_extended_read_parameter_count].result == f_console_result_additional) {
                      if (found == target) {
                        break;
                      }
                      else {
                        found++;
                      }
                    }
                  }
                }
              }
            } // for
          }
        }
      }
    }

    return f_none;
  }
#endif // _di_fss_extended_read_main_process_file_
