#include <level_3/fss_basic_read.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_basic_read_print_help_
  f_return_status fss_basic_read_print_help(const fss_basic_read_data data) {
    fll_program_print_help_header(data.context, fss_basic_read_name_long, fss_basic_read_version);

    fll_program_print_help_option(data.context, f_console_standard_short_help, f_console_standard_long_help, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Print this help message.");
    fll_program_print_help_option(data.context, f_console_standard_short_light, f_console_standard_long_light, f_console_symbol_short_disable, f_console_symbol_long_disable, "   Output using colors that show up better on light backgrounds.");
    fll_program_print_help_option(data.context, f_console_standard_short_dark, f_console_standard_long_dark, f_console_symbol_short_disable, f_console_symbol_long_disable, "    Output using colors that show up better on dark backgrounds.");
    fll_program_print_help_option(data.context, f_console_standard_short_no_color, f_console_standard_long_no_color, f_console_symbol_short_disable, f_console_symbol_long_disable, "Do not output in color.");
    fll_program_print_help_option(data.context, f_console_standard_short_version, f_console_standard_long_version, f_console_symbol_short_disable, f_console_symbol_long_disable, " Print only the version number.");

    printf("%c", f_string_eol);

    fll_program_print_help_option(data.context, fss_basic_read_short_name, fss_basic_read_long_name, f_console_symbol_short_enable, f_console_symbol_long_enable, "    Find and print content from this object name.");
    fll_program_print_help_option(data.context, fss_basic_read_short_count, fss_basic_read_long_count, f_console_symbol_short_enable, f_console_symbol_long_enable, "   Find a specific occurrence of the object.");
    fll_program_print_help_option(data.context, fss_basic_read_short_total, fss_basic_read_long_total, f_console_symbol_short_enable, f_console_symbol_long_enable, "   Print the total number of objects in this file.");
    fll_program_print_help_option(data.context, fss_basic_read_short_object, fss_basic_read_long_object, f_console_symbol_short_enable, f_console_symbol_long_enable, "  Print the object instead of the content.");

    fll_program_print_help_usage(data.context, fss_basic_read_name, "filename(s)");

    return f_none;
  }
#endif // _di_fss_basic_read_print_help_

#ifndef _di_fss_basic_read_main_
  f_return_status fss_basic_read_main_process_file(const f_array_length argc, const f_string argv[], fss_basic_read_data *data, const f_string filename, const f_string_length target) f_gcc_attribute_visibility_internal;

  f_return_status fss_basic_read_main(const f_array_length argc, const f_string argv[], fss_basic_read_data *data) {
    f_status status = fll_program_process_parameters(argc, argv, data->parameters, fss_basic_read_total_parameters, fss_basic_read_parameter_no_color, fss_basic_read_parameter_light, fss_basic_read_parameter_dark, &data->remaining, &data->context);

    if (f_status_is_error(status)) {
      fss_basic_read_delete_data(data);
      return f_status_set_error(status);
    }

    f_status status2 = f_none;
    status = f_none;

    // execute parameter results
    if (data->parameters[fss_basic_read_parameter_help].result == f_console_result_found) {
      fss_basic_read_print_help(*data);
    }
    else if (data->parameters[fss_basic_read_parameter_version].result == f_console_result_found) {
      fll_program_print_version(fss_basic_read_version);
    }
    else if (data->remaining.used > 0 || data->process_pipe) {
      f_string_length counter = 0;
      f_string_length target  = 0;
      f_string_length original_size = data->file_position.total_elements;

      if (data->parameters[fss_basic_read_parameter_count].result == f_console_result_additional) {
        target = (f_string_length) atoll(argv[data->parameters[fss_basic_read_parameter_count].additional.array[0]]);
      }

      if (data->process_pipe) {
        f_file file = f_file_initialize;

        file.address = f_pipe;

        status = fl_file_read_fifo(file, &data->buffer);

        if (f_status_is_error(status)) {
          status = f_status_set_fine(status);

          if (status == f_invalid_parameter) {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: Invalid parameter when calling fl_file_read()");
          }
          else if (status == f_overflow) {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Integer overflow while trying to buffer the file '%s'", "-");
          }
          else if (status == f_file_not_open) {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: The file '%s' is no longer open", "-");
          }
          else if (status == f_file_seek_error) {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: A seek error occurred while accessing the file '%s'", "-");
          }
          else if (status == f_file_read_error) {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: A read error occurred while accessing the file '%s'", "-");
          }
          else if (status == f_allocation_error || status == f_reallocation_error) {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: unable to allocate memory");
          }
          else {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling fl_file_read()", f_status_set_error(status));
          }

          fss_basic_read_delete_data(data);
          return f_status_set_error(status);
        }

        status = fss_basic_read_main_process_file(argc, argv, data, "-", target);

        if (f_status_is_error(status)) {
          return status;
        }

        // clear buffers before continuing
        f_macro_fss_contents_delete(status2, data->contents);
        f_macro_fss_objects_delete(status2, data->objects);
        f_macro_string_dynamic_delete(status2, data->buffer);
      }

      if (data->remaining.used > 0) {
        for (; counter < data->remaining.used; counter++) {
          f_file file = f_file_initialize;

          status = f_file_open(&file, argv[data->remaining.array[counter]]);

          data->file_position.total_elements = original_size;

          if (f_status_is_error(status)) {
            status = f_status_set_fine(status);

            if (status == f_invalid_parameter) {
              fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: Invalid parameter when calling f_file_open()");
            }
            else if (status == f_file_not_found) {
              fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Unable to find the file '%s'", argv[data->remaining.array[counter]]);
            }
            else if (status == f_file_open_error) {
              fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Unable to open the file '%s'", argv[data->remaining.array[counter]]);
            }
            else if (status == f_file_descriptor_error) {
              fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: File descriptor error while trying to open the file '%s'", argv[data->remaining.array[counter]]);
            }
            else {
              fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling f_file_open()", f_status_set_error(status));
            }

            fss_basic_read_delete_data(data);
            return f_status_set_error(status);
          }

          if (data->file_position.total_elements == 0) {
            fseek(file.address, 0, SEEK_END);

            data->file_position.total_elements = ftell(file.address);

            // skip past empty files
            if (data->file_position.total_elements == 0) {
              f_file_close(&file);
              continue;
            }

            fseek(file.address, 0, SEEK_SET);
          }

          status = fl_file_read(file, data->file_position, &data->buffer);

          f_file_close(&file);

          if (f_status_is_error(status)) {
            status = f_status_set_fine(status);

            if (status == f_invalid_parameter) {
              fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: Invalid parameter when calling fl_file_read()");
            }
            else if (status == f_overflow) {
              fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Integer overflow while trying to buffer the file '%s'", argv[data->remaining.array[counter]]);
            }
            else if (status == f_file_not_open) {
              fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: The file '%s' is no longer open", argv[data->remaining.array[counter]]);
            }
            else if (status == f_file_seek_error) {
              fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: A seek error occurred while accessing the file '%s'", argv[data->remaining.array[counter]]);
            }
            else if (status == f_file_read_error) {
              fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: A read error occurred while accessing the file '%s'", argv[data->remaining.array[counter]]);
            }
            else if (status == f_allocation_error || status == f_reallocation_error) {
              fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: unable to allocate memory");
            }
            else {
              fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling fl_file_read()", f_status_set_error(status));
            }

            fss_basic_read_delete_data(data);
            return f_status_set_error(status);
          }

          status = fss_basic_read_main_process_file(argc, argv, data, argv[data->remaining.array[counter]], target);

          if (f_status_is_error(status)) {
            return status;
          }

          // clear buffers before repeating the loop
          f_macro_fss_contents_delete(status2, data->contents);
          f_macro_fss_objects_delete(status2, data->objects);
          f_macro_string_dynamic_delete(status2, data->buffer);
        } // for
      }
    }
    else {
      fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: you failed to specify one or more files");
      status = f_status_set_error(f_invalid_parameter);
    }

    fss_basic_read_delete_data(data);
    return status;
  }

  f_return_status fss_basic_read_main_process_file(const f_array_length argc, const f_string argv[], fss_basic_read_data *data, const f_string filename, const f_string_length target) {
    f_status status = f_none;
    f_status status2 = f_none;

    f_string_length current = 0;
    f_string_length found = 0;

    {
      f_string_location input = f_string_location_initialize;

      input.start = 0;
      input.stop  = data->buffer.used - 1;

      status = fll_fss_basic_read(&data->buffer, &input, &data->objects, &data->contents);

      if (f_status_is_error(status)) {
        status = f_status_set_fine(status);

        if (status == f_invalid_parameter) {
          fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: Invalid parameter when calling fll_fss_basic_list_read() for the file '%s'", filename);
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
          fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling fll_fss_basic_list_read() for the file '%s'", f_status_set_error(status), filename);
        }

        fss_basic_read_delete_data(data);
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

    // now that the file has been read, process the objects and contents
    if (data->parameters[fss_basic_read_parameter_total].result == f_console_result_found && data->parameters[fss_basic_read_parameter_name].result == f_console_result_none) {
      fprintf(f_standard_output, "%u\n", (unsigned int) data->objects.used);
    }
    else {
      current = 0;

      if (data->parameters[fss_basic_read_parameter_name].result == f_console_result_none) {
        if (data->parameters[fss_basic_read_parameter_object].result == f_console_result_none) {
          for (; current < data->objects.used; current++) {
            if (data->parameters[fss_basic_read_parameter_count].result == f_console_result_none || (data->parameters[fss_basic_read_parameter_count].result == f_console_result_additional && found == target)) {
              if (data->contents.array[current].used > 0) {
                f_print_string_dynamic_partial(f_standard_output, data->buffer, data->contents.array[current].array[0]);
                fprintf(f_standard_output, "\n");
              }
              else {
                // for all objects with no data, print a newline
                fprintf(f_standard_output, "\n");
              }
            }

            if (data->parameters[fss_basic_read_parameter_count].result == f_console_result_additional) {
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
            if (data->parameters[fss_basic_read_parameter_count].result == f_console_result_none || (data->parameters[fss_basic_read_parameter_count].result == f_console_result_additional && found == target)) {
              f_print_string_dynamic_partial(f_standard_output, data->buffer, data->objects.array[current]);
              fprintf(f_standard_output, "\n");
            }

            if (data->parameters[fss_basic_read_parameter_count].result == f_console_result_additional) {
              if (found == target) {
                break;
              }
              else {
                found++;
              }
            }
          } // for
        }
      }
      else {
        current = 0;

        f_string_length total = 0;
        f_string_length name_length = 0;
        f_string_length argv_length = 0;

        if (data->parameters[fss_basic_read_parameter_name].result == f_console_result_additional) {
          argv_length = strlen(argv[data->parameters[fss_basic_read_parameter_name].additional.array[0]]);

          if (data->parameters[fss_basic_read_parameter_object].result == f_console_result_none) {
            for (; current < data->objects.used; current++) {
              name_length = data->objects.array[current].stop - data->objects.array[current].start + 1;

              if (name_length == argv_length) {
                if (fl_string_compare(data->buffer.string + data->objects.array[current].start, argv[data->parameters[fss_basic_read_parameter_name].additional.array[0]], name_length, argv_length) == f_equal_to) {

                  if (data->parameters[fss_basic_read_parameter_count].result == f_console_result_none || (data->parameters[fss_basic_read_parameter_count].result == f_console_result_additional && found == target)) {
                    if (data->parameters[fss_basic_read_parameter_total].result == f_console_result_found) {
                      total++;
                    }
                    else {
                      if (data->contents.array[current].used > 0) {
                        f_print_string_dynamic_partial(f_standard_output, data->buffer, data->contents.array[current].array[0]);
                        fprintf(f_standard_output, "\n");
                      }
                      else {
                        // for all objects with no data, print a newline
                        fprintf(f_standard_output, "\n");
                      }
                    }
                  }

                  if (data->parameters[fss_basic_read_parameter_count].result == f_console_result_additional) {
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

            if (data->parameters[fss_basic_read_parameter_total].result == f_console_result_found && data->parameters[fss_basic_read_parameter_count].result == f_console_result_none) {
              fprintf(f_standard_output, f_string_length_printf "\n", total);
            }
          }
          else {
            // when and because the object parameter is specified, the name parameter refers to the content instead of the object
            // therefore, make the search on the content and display the object
            for (; current < data->contents.used; current++) {
              if (data->contents.array[current].used > 0) {
                name_length = data->contents.array[current].array[0].stop - data->contents.array[current].array[0].start + 1;

                if (name_length == argv_length) {
                  if (fl_string_compare(data->buffer.string + data->contents.array[current].array[0].start, argv[data->parameters[fss_basic_read_parameter_name].additional.array[0]], name_length, argv_length) == f_equal_to) {
                    if (data->parameters[fss_basic_read_parameter_count].result == f_console_result_none || (data->parameters[fss_basic_read_parameter_count].result == f_console_result_additional && found == target)) {
                      f_print_string_dynamic_partial(f_standard_output, data->buffer, data->objects.array[current]);
                      fprintf(f_standard_output, "\n");
                    }

                    if (data->parameters[fss_basic_read_parameter_count].result == f_console_result_additional) {
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
#endif // _di_fss_basic_read_main_

#ifndef _di_fss_basic_read_delete_data_
  f_return_status fss_basic_read_delete_data(fss_basic_read_data *data) {
    f_status status = f_none;
    f_string_length i = 0;

    while (i < fss_basic_read_total_parameters) {
      f_macro_string_lengths_delete(status, data->parameters[i].additional);
      i++;
    } // while

    f_macro_fss_contents_delete(status, data->contents);
    f_macro_fss_objects_delete(status, data->objects);
    f_macro_string_dynamic_delete(status, data->buffer);
    f_macro_string_lengths_delete(status, data->remaining);

    fl_macro_color_context_delete(status, data->context);

    return f_none;
  }
#endif // _di_fss_basic_read_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif
