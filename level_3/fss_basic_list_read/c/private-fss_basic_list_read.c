#include <level_3/fss_basic_list_read.h>
#include "private-fss_basic_list_read.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fss_basic_list_read_print_file_error_
  void fss_basic_list_read_print_file_error(const fl_color_context context, const f_string function_name, const f_string file_name, const f_status status) {

    if (status == f_invalid_parameter) {
      fl_color_print(f_standard_error, context.error, context.reset, "INTERNAL ERROR: Invalid parameter when calling ");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s()", function_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, ".");
    }
    else if (status == f_overflow) {
      fl_color_print(f_standard_error, context.error, context.reset, "ERROR: Integer overflow while trying to buffer the file '");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
    }
    else if (status == f_file_not_open) {
      fl_color_print(f_standard_error, context.error, context.reset, "INTERNAL ERROR: The file '");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "' is no longer open.");
    }
    else if (status == f_file_seek_error) {
      fl_color_print(f_standard_error, context.error, context.reset, "ERROR: A seek error occurred while accessing the file '");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
    }
    else if (status == f_file_read_error) {
      fl_color_print(f_standard_error, context.error, context.reset, "ERROR: A read error occurred while accessing the file '");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
    }
    else if (status == f_file_not_found) {
      fl_color_print(f_standard_error, context.error, context.reset, "ERROR: Unable to find the file '");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
    }
    else if (status == f_file_open_error) {
      fl_color_print(f_standard_error, context.error, context.reset, "ERROR: Unable to open the file '");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
    }
    else if (status == f_file_descriptor_error) {
      fl_color_print(f_standard_error, context.error, context.reset, "ERROR: File descriptor error while trying to open the file '");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
    }
    else if (status == f_overflow) {
      fl_color_print(f_standard_error, context.error, context.reset, "ERROR: Integer overflow while trying to buffer the file '");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s", file_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, "'.");
    }
    else if (status == f_allocation_error || status == f_reallocation_error) {
      fl_color_print_line(f_standard_error, context.error, context.reset, "CRITICAL ERROR: Unable to allocate memory.");
    }
    else {
      fl_color_print(f_standard_error, context.error, context.reset, "INTERNAL ERROR: An unhandled error (");
      fl_color_print(f_standard_error, context.notable, context.reset, "%u", status);
      fl_color_print(f_standard_error, context.error, context.reset, ") has occured while calling ");
      fl_color_print(f_standard_error, context.notable, context.reset, "%s()", function_name);
      fl_color_print_line(f_standard_error, context.error, context.reset, ".");
    }
  }
#endif // _di_fss_basic_list_read_print_file_error_

#ifndef _di_fss_basic_list_read_main_preprocess_depth_
  f_return_status fss_basic_list_read_main_preprocess_depth(const f_console_arguments arguments, const fss_basic_list_read_data data, fss_basic_list_read_depths *depths) {
    f_status status = f_none;

    // pre-process the depth and depth-sensitive parameters.
    if (data.parameters[fss_basic_list_read_parameter_depth].result == f_console_result_additional) {
      macro_fss_basic_list_read_depths_new(status, (*depths), data.parameters[fss_basic_list_read_parameter_depth].locations.used);
      if (f_status_is_error(status)) {
        f_status status2 = f_none;
        fl_color_print_line(f_standard_error, data.context.error, data.context.reset, "CRITICAL ERROR: Unable to allocate memory.");

        macro_fss_basic_list_read_depths_delete(status2, (*depths));
        return f_status_set_error(f_invalid_parameter);
      }

      f_array_length depth_position = data.parameters[fss_basic_list_read_parameter_depth].additional.array[0];
      f_array_length at_index = 0;
      f_array_length name_index = 0;

      depths->array[0].depth = (f_string_length) atoll(arguments.argv[depth_position]);
      depths->array[0].parameter = 0;
      depths->array[0].position = 0;
      depths->used = 1;

      f_string_length depth_previous = depths->array[0].depth;
      f_string_length depth_current = depths->array[0].depth;

      if (data.parameters[fss_basic_list_read_parameter_at].result == f_console_result_additional) {
        for (; at_index < data.parameters[fss_basic_list_read_parameter_at].additional.used; at_index++) {
          if (data.parameters[fss_basic_list_read_parameter_at].additional.array[at_index] > depth_position) {
            if (data.parameters[fss_basic_list_read_parameter_depth].additional.used > 1) {
              if (data.parameters[fss_basic_list_read_parameter_at].additional.array[at_index] > data.parameters[fss_basic_list_read_parameter_depth].additional.array[1]) {
                break;
              }
            }

            depths->array[0].parameter = fss_basic_list_read_parameter_at;
          }
        } // for
      }

      if (data.parameters[fss_basic_list_read_parameter_name].result == f_console_result_additional) {
        for (; name_index < data.parameters[fss_basic_list_read_parameter_name].additional.used; name_index++) {
          if (data.parameters[fss_basic_list_read_parameter_name].additional.array[name_index] > depth_position) {
            if (data.parameters[fss_basic_list_read_parameter_depth].additional.used > 1) {
              if (data.parameters[fss_basic_list_read_parameter_name].additional.array[name_index] > data.parameters[fss_basic_list_read_parameter_depth].additional.array[1]) {
                break;
              }
            }

            if (depths->array[0].parameter == fss_basic_list_read_parameter_at) {
              fl_color_print_line(f_standard_error, data.context.error, data.context.reset, "ERROR: The '--%s' and '--%s' parameters cannot be specified at the same time (specified for depth '%llu').", fss_basic_list_read_long_at, fss_basic_list_read_long_name, depth_current);
              return f_status_set_error(f_invalid_parameter);
            }

            depths->array[0].parameter = fss_basic_list_read_parameter_name;
          }
        } // for
      }

      for (f_array_length i = 1; i < data.parameters[fss_basic_list_read_parameter_depth].locations.used; i++) {
        depth_position = data.parameters[fss_basic_list_read_parameter_depth].additional.array[i];
        depth_current = (f_string_length) atoll(arguments.argv[depth_position]);

        if (depth_current > depth_previous) {
          fl_color_print_line(f_standard_error, data.context.error, data.context.reset, "ERROR: The depth '%llu' cannot be specified before the depth '%llu'.", depth_previous, depth_current);
          return f_status_set_error(f_invalid_parameter);
        }

        if (depth_current == depth_previous) {
          fl_color_print_line(f_standard_error, data.context.error, data.context.reset, "ERROR: The depth '%llu' cannot be the same as the depth '%llu'.", depth_previous, depth_current);
          return f_status_set_error(f_invalid_parameter);
        }

        if (data.parameters[fss_basic_list_read_parameter_at].result == f_console_result_additional) {
          for (; at_index < data.parameters[fss_basic_list_read_parameter_at].additional.used; at_index++) {
            if (data.parameters[fss_basic_list_read_parameter_at].additional.array[at_index] > depth_position) {
              if (data.parameters[fss_basic_list_read_parameter_depth].additional.used > 1) {
                if (data.parameters[fss_basic_list_read_parameter_at].additional.array[at_index] > data.parameters[fss_basic_list_read_parameter_depth].additional.array[i+1]) {
                  break;
                }
              }

              depths->array[i].parameter = fss_basic_list_read_parameter_at;
              depths->array[i].position = data.parameters[fss_basic_list_read_parameter_at].additional.array[i];
            }
          } // for
        }

        if (data.parameters[fss_basic_list_read_parameter_name].result == f_console_result_additional) {
          for (; name_index < data.parameters[fss_basic_list_read_parameter_name].additional.used; name_index++) {
            if (data.parameters[fss_basic_list_read_parameter_name].additional.array[name_index] > depth_position) {
              if (data.parameters[fss_basic_list_read_parameter_depth].additional.used > 1) {
                if (data.parameters[fss_basic_list_read_parameter_name].additional.array[name_index] > data.parameters[fss_basic_list_read_parameter_depth].additional.array[i+1]) {
                  break;
                }
              }

              if (depths->array[i].parameter == fss_basic_list_read_parameter_at) {
                fl_color_print_line(f_standard_error, data.context.error, data.context.reset, "ERROR: The '--%s' and '--%s' parameters cannot be specified at the same time (specified for depth '%llu').", fss_basic_list_read_long_at, fss_basic_list_read_long_name, depth_current);
                return f_status_set_error(f_invalid_parameter);
              }

              depths->array[i].parameter = fss_basic_list_read_parameter_name;
              depths->array[i].position = data.parameters[fss_basic_list_read_parameter_name].additional.array[i];
            }
          } // for
        }

        depths->array[i].depth = (f_string_length) atoll(arguments.argv[depth_position]);
        depths->used++;
      } // for
    }
    // when no depth parameter is specified, provide a implicit depth of 0 when depth-sensitive parameters are in use.
    else {
      if (data.parameters[fss_basic_list_read_parameter_at].result == f_console_result_additional) {
        if (data.parameters[fss_basic_list_read_parameter_name].result == f_console_result_additional) {
          fl_color_print_line(f_standard_error, data.context.error, data.context.reset, "ERROR: The '%s' and '%s' parameters must not be specified at the same time.", fss_basic_list_read_long_name, fss_basic_list_read_long_object);
          return f_status_set_error(f_invalid_parameter);
        }

        macro_fss_basic_list_read_depths_new(status, (*depths), 1);
        if (f_status_is_error(status)) {
          fl_color_print_line(f_standard_error, data.context.error, data.context.reset, "CRITICAL ERROR: Unable to allocate memory.");
          return f_status_set_error(f_invalid_parameter);
        }

        depths->array[0].depth = (f_string_length) atoll(arguments.argv[data.parameters[fss_basic_list_read_parameter_depth].additional.array[0]]);
        depths->array[0].parameter = fss_basic_list_read_parameter_at;
        depths->array[0].position = 0;
        depths->used = 1;
      }
      else if (data.parameters[fss_basic_list_read_parameter_name].result == f_console_result_additional) {
        macro_fss_basic_list_read_depths_new(status, (*depths), 1);
        if (f_status_is_error(status)) {
          fl_color_print_line(f_standard_error, data.context.error, data.context.reset, "CRITICAL ERROR: Unable to allocate memory.");
          return f_status_set_error(f_invalid_parameter);
        }

        depths->array[0].depth = (f_string_length) atoll(arguments.argv[data.parameters[fss_basic_list_read_parameter_depth].additional.array[0]]);
        depths->array[0].parameter = fss_basic_list_read_parameter_name;
        depths->array[0].position = 0;
        depths->used = 1;
      }
    }

    return f_none;
  }
#endif // _di_fss_basic_list_read_main_preprocess_depth_

#ifndef _di_fss_basic_list_read_main_process_file_
  f_return_status fss_basic_list_read_main_process_file(const f_console_arguments arguments, fss_basic_list_read_data *data, const f_string filename, const f_string_length target) {
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
          fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: Unable to allocate memory");
        }
        else if (status == f_incomplete_utf_on_stop) {
          fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ENCODING ERROR: error occured on invalid UTF-8 character at stop position (at %d).", input.start);
        }
        else if (status == f_incomplete_utf_on_eos) {
          fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "ENCODING ERROR: error occured on invalid UTF-8 character at end of string (at %d).", input.start);
        }
        else {
          fl_color_print_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling fll_fss_basic_list_read() for the file '%s'", status, filename);
        }

        fss_basic_list_read_delete_data(data);
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
    if (data->parameters[fss_basic_list_read_parameter_total].result == f_console_result_found && data->parameters[fss_basic_list_read_parameter_name].result == f_console_result_none) {
      fprintf(f_standard_output, "%llu\n", data->objects.used);
    }
    else {
      current = 0;

      if (data->parameters[fss_basic_list_read_parameter_name].result == f_console_result_none) {
        if (data->parameters[fss_basic_list_read_parameter_object].result == f_console_result_none) {
          for (; current < data->objects.used; current++) {
            if (data->parameters[fss_basic_list_read_parameter_at].result == f_console_result_none || (data->parameters[fss_basic_list_read_parameter_at].result == f_console_result_additional && found == target)) {

              /*if (data->parameters[fss_basic_list_read_parameter_size].result == f_console_result_found) {
                if (data->contents.array[current].used > 0) {
                  f_string_length counter = data->contents.array[current].array[0].start;
                  f_string_length size    = 0;

                  for (; counter <= data->contents.array[current].array[0].stop; counter++) {
                    if (data->buffer.string[counter] == f_string_eol) size++;
                  } // for

                  // the last newline is never present
                  size++;

                  fprintf(f_standard_output, "%u\n", (unsigned int) size);
                }
                else {
                  fprintf(f_standard_output, "0\n");
                }
              }
              else*/ if (data->parameters[fss_basic_list_read_parameter_line].result == f_console_result_additional) {
                if (data->contents.array[current].used > 0) {
                  f_string_length counter = data->contents.array[current].array[0].start;
                  f_string_length position = 0;
                  f_string_length target = (f_string_length) atoll(arguments.argv[data->parameters[fss_basic_list_read_parameter_line].additional.array[0]]);
                  f_string_location range = f_string_location_initialize;

                  // use an invalid range to communicate range not found
                  range.start = 1;
                  range.stop  = 0;

                  for (; counter <= data->contents.array[current].array[0].stop; counter++) {
                    if (position == target) {
                      range.start = counter;

                      // explicit use of < instead of <= is done here so that the range.stop will always be accurate
                      for (; counter < data->contents.array[current].array[0].stop; counter++) {
                        if (data->buffer.string[counter] == f_string_eol) {
                          break;
                        }
                      } // for

                      range.stop = counter;
                      break;
                    }

                    if (data->buffer.string[counter] == f_string_eol) {
                      position++;
                    }
                  } // for

                  if (range.start <= range.stop) {
                    f_print_string_dynamic_partial(f_standard_output, data->buffer, range);
                  }
                }
              }
              else {
                if (data->contents.array[current].used > 0) {
                  f_print_string_dynamic_partial(f_standard_output, data->buffer, data->contents.array[current].array[0]);
                  fprintf(f_standard_output, "\n");
                }
              }
            }

            if (data->parameters[fss_basic_list_read_parameter_at].result == f_console_result_additional) {
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
            if (data->parameters[fss_basic_list_read_parameter_at].result == f_console_result_none || (data->parameters[fss_basic_list_read_parameter_at].result == f_console_result_additional && found == target)) {
              f_print_string_dynamic_partial(f_standard_output, data->buffer, data->objects.array[current]);
              fprintf(f_standard_output, "\n");
            }

            if (data->parameters[fss_basic_list_read_parameter_at].result == f_console_result_additional) {
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
          argv_length = strlen(arguments.argv[data->parameters[fss_basic_list_read_parameter_name].additional.array[0]]);

          if (data->parameters[fss_basic_list_read_parameter_object].result == f_console_result_none) {
            for (; current < data->objects.used; current++) {
              name_length = data->objects.array[current].stop - data->objects.array[current].start + 1;

              if (name_length == argv_length) {
                if (fl_string_compare(data->buffer.string + data->objects.array[current].start, arguments.argv[data->parameters[fss_basic_list_read_parameter_name].additional.array[0]], name_length, argv_length) == f_equal_to) {

                  /*if (data->parameters[fss_basic_list_read_parameter_size].result == f_console_result_found) {
                    if (data->contents.array[current].used > 0) {
                      f_string_length counter = data->contents.array[current].array[0].start;
                      f_string_length size    = 0;

                      for (; counter <= data->contents.array[current].array[0].stop; counter++) {
                        if (data->buffer.string[counter] == f_string_eol) size++;
                      } // for

                      // the last newline is never present
                      size++;

                      fprintf(f_standard_output, "%u\n", (unsigned int) size);
                    }
                    else {
                      fprintf(f_standard_output, "0\n");
                    }
                  }
                  else*/ if (data->parameters[fss_basic_list_read_parameter_line].result == f_console_result_additional) {
                    if (data->contents.array[current].used > 0) {
                      f_string_length counter = data->contents.array[current].array[0].start;
                      f_string_length position = 0;
                      f_string_length target = (f_string_length) atoll(arguments.argv[data->parameters[fss_basic_list_read_parameter_line].additional.array[0]]);
                      f_string_location range = f_string_location_initialize;

                      // use an invalid range to communicate range not found
                      range.start = 1;
                      range.stop = 0;

                      for (; counter <= data->contents.array[current].array[0].stop; counter++) {
                        if (position == target) {
                          range.start = counter;

                          // explicit use of < instead of <= is done here so that the range.stop will always be accurate
                          for (; counter < data->contents.array[current].array[0].stop; counter++) {
                            if (data->buffer.string[counter] == f_string_eol) {
                              break;
                            }
                          } // for

                          range.stop = counter;
                          break;
                        }

                        if (data->buffer.string[counter] == f_string_eol) {
                          position++;
                        }
                      } // for

                      if (range.start <= range.stop) {
                        f_print_string_dynamic_partial(f_standard_output, data->buffer, range);
                      }
                    }
                  }
                  else {
                    if (data->parameters[fss_basic_list_read_parameter_at].result == f_console_result_none || (data->parameters[fss_basic_list_read_parameter_at].result == f_console_result_additional && found == target)) {
                      if (data->parameters[fss_basic_list_read_parameter_total].result == f_console_result_found) {
                        total++;
                      }
                      else {
                        if (data->contents.array[current].used > 0) {
                          f_print_string_dynamic_partial(f_standard_output, data->buffer, data->contents.array[current].array[0]);
                          fprintf(f_standard_output, "\n");
                        }
                      }
                    }
                  }

                  if (data->parameters[fss_basic_list_read_parameter_at].result == f_console_result_additional) {
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

            if (data->parameters[fss_basic_list_read_parameter_total].result == f_console_result_found && data->parameters[fss_basic_list_read_parameter_at].result == f_console_result_none) {
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
                  if (fl_string_compare(data->buffer.string + data->contents.array[current].array[0].start, arguments.argv[data->parameters[fss_basic_list_read_parameter_name].additional.array[0]], name_length, argv_length) == f_equal_to) {
                    if (data->parameters[fss_basic_list_read_parameter_at].result == f_console_result_none || (data->parameters[fss_basic_list_read_parameter_at].result == f_console_result_additional && found == target)) {
                      f_print_string_dynamic_partial(f_standard_output, data->buffer, data->objects.array[current]);
                      fprintf(f_standard_output, "\n");
                    }

                    if (data->parameters[fss_basic_list_read_parameter_at].result == f_console_result_additional) {
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
#endif // _di_fss_basic_list_read_main_process_file_

#ifdef __cplusplus
} // extern "C"
#endif
