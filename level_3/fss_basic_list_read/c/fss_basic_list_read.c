#include <level_3/fss_basic_list_read.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_basic_list_read_print_help_
  f_return_status fss_basic_list_read_print_help(const fss_basic_list_read_data data) {
    printf("\n");
    fl_color_print(f_standard_output, data.context.title, data.context.reset, " %s", fss_basic_list_read_name_long);

    printf("\n");
    fl_color_print(f_standard_output, data.context.notable, data.context.reset, "  Version %s", fss_basic_list_read_version);


    printf("\n\n");
    fl_color_print(f_standard_output, data.context.important, data.context.reset, " Available Options: ");

    printf("\n  %s", f_console_symbol_short_enable);
    fl_color_print(f_standard_output, data.context.standout, data.context.reset, f_console_standard_short_help);

    printf(", %s", f_console_symbol_long_enable);
    fl_color_print(f_standard_output, data.context.standout, data.context.reset, f_console_standard_long_help);
    printf("      Print this help message");

    printf("\n  %s", f_console_symbol_short_disable);
    fl_color_print(f_standard_output, data.context.standout, data.context.reset, f_console_standard_short_light);

    printf(", %s", f_console_symbol_long_disable);
    fl_color_print(f_standard_output, data.context.standout, data.context.reset, f_console_standard_long_light);
    printf("     Output using colors that show up better on light backgrounds");

    printf("\n  %s", f_console_symbol_short_disable);
    fl_color_print(f_standard_output, data.context.standout, data.context.reset, f_console_standard_short_no_color);

    printf(", %s", f_console_symbol_long_disable);
    fl_color_print(f_standard_output, data.context.standout, data.context.reset, f_console_standard_long_no_color);
    printf("  Do not output in color");

    printf("\n  %s", f_console_symbol_short_disable);
    fl_color_print(f_standard_output, data.context.standout, data.context.reset, f_console_standard_short_version);

    printf(", %s", f_console_symbol_long_disable);
    fl_color_print(f_standard_output, data.context.standout, data.context.reset, f_console_standard_long_version);
    printf("   Print only the version number");


    printf("\n\n  %s", f_console_symbol_short_enable);
    fl_color_print(f_standard_output, data.context.standout, data.context.reset, fss_basic_list_read_short_name);

    printf(", %s", f_console_symbol_long_enable);
    fl_color_print(f_standard_output, data.context.standout, data.context.reset, fss_basic_list_read_long_name);
    printf("      Find and print content from this object name");

    printf("\n  %s", f_console_symbol_short_enable);
    fl_color_print(f_standard_output, data.context.standout, data.context.reset, fss_basic_list_read_short_count);

    printf(", %s", f_console_symbol_long_enable);
    fl_color_print(f_standard_output, data.context.standout, data.context.reset, fss_basic_list_read_long_count);
    printf("     Find a specific occurrence of the object");

    printf("\n  %s", f_console_symbol_short_enable);
    fl_color_print(f_standard_output, data.context.standout, data.context.reset, fss_basic_list_read_short_total);

    printf(", %s", f_console_symbol_long_enable);
    fl_color_print(f_standard_output, data.context.standout, data.context.reset, fss_basic_list_read_long_total);
    printf("     Print the total number of objects in this file");

    printf("\n  %s", f_console_symbol_short_enable);
    fl_color_print(f_standard_output, data.context.standout, data.context.reset, fss_basic_list_read_short_object);

    printf(", %s", f_console_symbol_long_enable);
    fl_color_print(f_standard_output, data.context.standout, data.context.reset, fss_basic_list_read_long_object);
    printf("    Print the object instead of the content");

    printf("\n  %s", f_console_symbol_short_enable);
    fl_color_print(f_standard_output, data.context.standout, data.context.reset, fss_basic_list_read_short_size);

    printf(", %s", f_console_symbol_long_enable);
    fl_color_print(f_standard_output, data.context.standout, data.context.reset, fss_basic_list_read_long_size);
    printf("      Print total lines in the given content");

    printf("\n  %s", f_console_symbol_short_enable);
    fl_color_print(f_standard_output, data.context.standout, data.context.reset, fss_basic_list_read_short_line);

    printf(", %s", f_console_symbol_long_enable);
    fl_color_print(f_standard_output, data.context.standout, data.context.reset, fss_basic_list_read_long_line);
    printf("      Print only the content at the given line");


    printf("\n\n");
    fl_color_print(f_standard_output, data.context.important, data.context.reset, " Usage: ");

    printf("\n  ");
    fl_color_print(f_standard_output, data.context.standout, data.context.reset, fss_basic_list_read_name);

    printf("  ");
    fl_color_print(f_standard_output, data.context.notable, data.context.reset, "[");

    printf(" options ");
    fl_color_print(f_standard_output, data.context.notable, data.context.reset, "]");

    printf("  ");
    fl_color_print(f_standard_output, data.context.notable, data.context.reset, "[");

    printf(" filename(s) ");
    fl_color_print(f_standard_output, data.context.notable, data.context.reset, "]");


    printf("\n\n");

    return f_none;
  }
#endif // _di_fss_basic_list_read_print_help_

#ifndef _di_fss_basic_list_read_main_
  f_return_status fss_basic_list_read_main_process_file(const f_array_length argc, const f_string argv[], fss_basic_list_read_data *data, const f_string filename, const f_string_length target) __attribute__((visibility ("internal")));

  f_return_status fss_basic_list_read_main(const f_array_length argc, const f_string argv[], fss_basic_list_read_data *data) {
    f_status status = f_none;
    f_status status2 = f_none;

    status = fl_process_parameters(argc, argv, data->parameters, fss_basic_list_read_total_parameters, &data->remaining);

    // load colors when not told to show no colors
    if (data->parameters[fss_basic_list_read_parameter_no_color].result == f_console_result_none) {
      fl_new_color_context(status2, data->context);

      if (f_status_is_error(status2)) {
        fprintf(f_standard_error, "Critical Error: unable to allocate memory\n");
        fss_basic_list_read_delete_data(data);
        return status2;
      }
      else {
        fll_colors_load_context(&data->context, data->parameters[fss_basic_list_read_parameter_light].result == f_console_result_found);
      }
    }

    if (f_status_is_error(status)) {
      status = f_status_set_fine(status);

      if (status == f_no_data) {
        fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: One of the parameters you passed requires an additional parameter that you did not pass.");
        // TODO: there is a way to identify which parameter is incorrect
        //       to do this, one must look for any "has_additional" and then see if the "additional" location is set to 0
        //       nothing can be 0 as that represents the program name, unless argv[] is improperly created
      }
      else if (status == f_allocation_error || status == f_reallocation_error) {
        fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: unable to allocate memory");
      }
      else if (status == f_invalid_parameter) {
        fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: Invalid parameter when calling fl_process_parameters()");
      }
      else {
        fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling fl_process_parameters()", f_status_set_error(status));
      }

      fss_basic_list_read_delete_data(data);
      return f_status_set_error(status);
    }

    // execute parameter results
    if (data->parameters[fss_basic_list_read_parameter_help].result == f_console_result_found) {
      fss_basic_list_read_print_help(*data);
    }
    else if (data->parameters[fss_basic_list_read_parameter_version].result == f_console_result_found) {
      fl_program_print_version(fss_basic_list_read_version);
    }
    else if (data->remaining.used > 0 || data->process_pipe) {
      f_string_length counter = 0;
      f_string_length target  = 0;
      f_string_length original_size = data->file_position.total_elements;

      if (data->parameters[fss_basic_list_read_parameter_count].result == f_console_result_additional) {
        target = (f_string_length) atoll(argv[data->parameters[fss_basic_list_read_parameter_count].additional.array[0]]);
      }

      if (data->process_pipe) {
        f_file file = f_file_initialize;

        file.file = f_pipe;

        status = fl_file_read_fifo(file, &data->buffer);

        if (f_status_is_error(status)) {
          status = f_status_set_fine(status);

          if (status == f_invalid_parameter) {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: Invalid parameter when calling f_file_open()");
          }
          else if (status == f_file_not_found) {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Unable to find the file '%s'", "-");
          }
          else if (status == f_file_open_error) {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Unable to open the file '%s'", "-");
          }
          else if (status == f_file_descriptor_error) {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: File descriptor error while trying to open the file '%s'", "-");
          }
          else {
            fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling f_file_open()", f_status_set_error(status));
          }

          fss_basic_list_read_delete_data(data);
          return status;
        }

        status = fss_basic_list_read_main_process_file(argc, argv, data, "-", target);

        if (f_status_is_error(status)) {
          return status;
        }

        // clear buffers before continuing
        f_delete_fss_contents(status2, data->contents);
        f_delete_fss_objects(status2, data->objects);
        f_delete_dynamic_string(status2, data->buffer);
      }

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

          fss_basic_list_read_delete_data(data);
          return f_status_set_error(status);
        }

        if (data->file_position.total_elements == 0) {
          fseek(file.file, 0, SEEK_END);

          data->file_position.total_elements = ftell(file.file);

          // skip past empty files
          if (data->file_position.total_elements == 0) {
            f_file_close(&file);
            continue;
          }

          fseek(file.file, 0, SEEK_SET);
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

          fss_basic_list_read_delete_data(data);
          return f_status_set_error(status);
        }

        status = fss_basic_list_read_main_process_file(argc, argv, data, argv[data->remaining.array[counter]], target);

        if (f_status_is_error(status)) {
          return status;
        }

        // clear buffers before repeating the loop
        f_delete_fss_contents(status2, data->contents);
        f_delete_fss_objects(status2, data->objects);
        f_delete_dynamic_string(status2, data->buffer);
      } // for
    }
    else {
      fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ERROR: you failed to specify one or more files");
      status = f_status_set_error(f_invalid_parameter);
    }

    fss_basic_list_read_delete_data(data);
    return status;
  }

  f_return_status fss_basic_list_read_main_process_file(const f_array_length argc, const f_string argv[], fss_basic_list_read_data *data, const f_string filename, const f_string_length target) {
    f_status status = f_none;
    f_status status2 = f_none;

    f_string_length current = 0;
    f_string_length found = 0;

    {
      f_string_location input = f_string_location_initialize;

      input.start = 0;
      input.stop  = data->buffer.used - 1;

      status = fll_fss_basic_list_read(&data->buffer, &input, &data->objects, &data->contents);

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

        fss_basic_list_read_delete_data(data);
        return f_status_set_error(status);
      }
      else if (status == f_no_data_on_stop || status == f_no_data_on_eos) {
        // clear buffers, then attempt the next file
        f_delete_fss_contents(status2, data->contents);
        f_delete_fss_objects(status2, data->objects);
        f_delete_dynamic_string(status2, data->buffer);

        return f_status_set_warning(status);
      }
    }

    // now that all of the files have been read, process the objects and contents
    if (data->parameters[fss_basic_list_read_parameter_total].result == f_console_result_found && data->parameters[fss_basic_list_read_parameter_name].result == f_console_result_none) {
      fprintf(f_standard_output, "%u\n", (unsigned int) data->objects.used);
    }
    else {
      current = 0;

      if (data->parameters[fss_basic_list_read_parameter_name].result == f_console_result_none) {
        if (data->parameters[fss_basic_list_read_parameter_object].result == f_console_result_none) {
          for (; current < data->objects.used; current++) {
            if (data->parameters[fss_basic_list_read_parameter_count].result == f_console_result_none || (data->parameters[fss_basic_list_read_parameter_count].result == f_console_result_additional && found == target)) {

              if (data->parameters[fss_basic_list_read_parameter_size].result == f_console_result_found) {
                if (data->contents.array[current].used > 0) {
                  f_string_length counter = data->contents.array[current].array[0].start;
                  f_string_length size    = 0;

                  for (; counter <= data->contents.array[current].array[0].stop; counter++) {
                    if (data->buffer.string[counter] == f_eol) size++;
                  } // for

                  // the last newline is never present
                  size++;

                  fprintf(f_standard_output, "%u\n", (unsigned int) size);
                }
                else {
                  fprintf(f_standard_output, "0\n");
                }
              }
              else if (data->parameters[fss_basic_list_read_parameter_line].result == f_console_result_additional) {
                if (data->contents.array[current].used > 0) {
                  f_string_length counter = data->contents.array[current].array[0].start;
                  f_string_length position = 0;
                  f_string_length target = (f_string_length) atoll(argv[data->parameters[fss_basic_list_read_parameter_line].additional.array[0]]);
                  f_string_location range = f_string_location_initialize;

                  // use an invalid range to communicate range not found
                  range.start = 1;
                  range.stop  = 0;

                  for (; counter <= data->contents.array[current].array[0].stop; counter++) {
                    if (position == target) {
                      range.start = counter;

                      // explicit use of < instead of <= is done here so that the range.stop will always be accurate
                      for (; counter < data->contents.array[current].array[0].stop; counter++) {
                        if (data->buffer.string[counter] == f_eol) {
                          break;
                        }
                      } // for

                      range.stop = counter;
                      break;
                    }

                    if (data->buffer.string[counter] == f_eol) {
                      position++;
                    }
                  } // for

                  if (range.start <= range.stop) {
                    f_print_partial_dynamic_string(f_standard_output, data->buffer, range);
                  }
                }
              }
              else {
                if (data->contents.array[current].used > 0) {
                  f_print_partial_dynamic_string(f_standard_output, data->buffer, data->contents.array[current].array[0]);
                  fprintf(f_standard_output, "\n");
                }
              }
            }

            if (data->parameters[fss_basic_list_read_parameter_count].result == f_console_result_additional) {
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
            if (data->parameters[fss_basic_list_read_parameter_count].result == f_console_result_none || (data->parameters[fss_basic_list_read_parameter_count].result == f_console_result_additional && found == target)) {
              f_print_partial_dynamic_string(f_standard_output, data->buffer, data->objects.array[current]);
              fprintf(f_standard_output, "\n");
            }

            if (data->parameters[fss_basic_list_read_parameter_count].result == f_console_result_additional) {
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

        if (data->parameters[fss_basic_list_read_parameter_name].result == f_console_result_additional) {
          argv_length = strlen(argv[data->parameters[fss_basic_list_read_parameter_name].additional.array[0]]);

          if (data->parameters[fss_basic_list_read_parameter_object].result == f_console_result_none) {
            for (; current < data->objects.used; current++) {
              name_length = data->objects.array[current].stop - data->objects.array[current].start + 1;

              if (name_length == argv_length) {
                if (fl_compare_strings(data->buffer.string + data->objects.array[current].start, argv[data->parameters[fss_basic_list_read_parameter_name].additional.array[0]], name_length, argv_length) == f_equal_to) {

                  if (data->parameters[fss_basic_list_read_parameter_size].result == f_console_result_found) {
                    if (data->contents.array[current].used > 0) {
                      f_string_length counter = data->contents.array[current].array[0].start;
                      f_string_length size    = 0;

                      for (; counter <= data->contents.array[current].array[0].stop; counter++) {
                        if (data->buffer.string[counter] == f_eol) size++;
                      } // for

                      // the last newline is never present
                      size++;

                      fprintf(f_standard_output, "%u\n", (unsigned int) size);
                    }
                    else {
                      fprintf(f_standard_output, "0\n");
                    }
                  }
                  else if (data->parameters[fss_basic_list_read_parameter_line].result == f_console_result_additional) {
                    if (data->contents.array[current].used > 0) {
                      f_string_length counter = data->contents.array[current].array[0].start;
                      f_string_length position = 0;
                      f_string_length target = (f_string_length) atoll(argv[data->parameters[fss_basic_list_read_parameter_line].additional.array[0]]);
                      f_string_location range = f_string_location_initialize;

                      // use an invalid range to communicate range not found
                      range.start = 1;
                      range.stop = 0;

                      for (; counter <= data->contents.array[current].array[0].stop; counter++) {
                        if (position == target) {
                          range.start = counter;

                          // explicit use of < instead of <= is done here so that the range.stop will always be accurate
                          for (; counter < data->contents.array[current].array[0].stop; counter++) {
                            if (data->buffer.string[counter] == f_eol) {
                              break;
                            }
                          } // for

                          range.stop = counter;
                          break;
                        }

                        if (data->buffer.string[counter] == f_eol) {
                          position++;
                        }
                      } // for

                      if (range.start <= range.stop) {
                        f_print_partial_dynamic_string(f_standard_output, data->buffer, range);
                      }
                    }
                  }
                  else {
                    if (data->parameters[fss_basic_list_read_parameter_count].result == f_console_result_none || (data->parameters[fss_basic_list_read_parameter_count].result == f_console_result_additional && found == target)) {
                      if (data->parameters[fss_basic_list_read_parameter_total].result == f_console_result_found) {
                        total++;
                      }
                      else {
                        if (data->contents.array[current].used > 0) {
                          f_print_partial_dynamic_string(f_standard_output, data->buffer, data->contents.array[current].array[0]);
                          fprintf(f_standard_output, "\n");
                        }
                      }
                    }
                  }

                  if (data->parameters[fss_basic_list_read_parameter_count].result == f_console_result_additional) {
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

            if (data->parameters[fss_basic_list_read_parameter_total].result == f_console_result_found && data->parameters[fss_basic_list_read_parameter_count].result == f_console_result_none) {
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
                  if (fl_compare_strings(data->buffer.string + data->contents.array[current].array[0].start, argv[data->parameters[fss_basic_list_read_parameter_name].additional.array[0]], name_length, argv_length) == f_equal_to) {
                    if (data->parameters[fss_basic_list_read_parameter_count].result == f_console_result_none || (data->parameters[fss_basic_list_read_parameter_count].result == f_console_result_additional && found == target)) {
                      f_print_partial_dynamic_string(f_standard_output, data->buffer, data->objects.array[current]);
                      fprintf(f_standard_output, "\n");
                    }

                    if (data->parameters[fss_basic_list_read_parameter_count].result == f_console_result_additional) {
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
#endif // _di_fss_basic_list_read_main_

#ifndef _di_fss_basic_list_read_delete_data_
  f_return_status fss_basic_list_read_delete_data(fss_basic_list_read_data *data) {
    f_status status = f_none;
    f_string_length i = 0;

    while (i < fss_basic_list_read_total_parameters) {
      f_delete_string_lengths(status, data->parameters[i].additional);
      i++;
    } // while

    f_delete_fss_contents(status, data->contents);
    f_delete_fss_objects(status, data->objects);
    f_delete_dynamic_string(status, data->buffer);
    f_delete_string_lengths(status, data->remaining);

    fl_delete_color_context(status, data->context);

    return f_none;
  }
#endif // _di_fss_basic_list_read_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif
