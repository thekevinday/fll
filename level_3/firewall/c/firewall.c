/* FLL - Level 3
 * Project:       Firewall
 * Version:       0.3.x
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 */
#include <level_3/firewall.h>
#include "private-firewall.h"

#ifdef __cplusplus
extern "C"{
#endif

// version printed may be used by scripts, so this will only print the version number and a newline, no extra information or colors
#ifndef _di_firewall_print_version_
  f_return_status firewall_print_version(const firewall_data data) {
    printf("%s\n", firewall_version);

    return f_none;
  }
#endif // _firewall_print_version_

#ifndef _di_firewall_print_help_
  f_return_status firewall_print_help(const firewall_data data) {
    printf("\n");
    fl_print_color(f_standard_output, data.context.title, data.context.reset, " %s", firewall_name_long);

    printf("\n");
    fl_print_color(f_standard_output, data.context.notable, data.context.reset, "  Version %s", firewall_version);

    printf("\n\n");
    fl_print_color(f_standard_output, data.context.important, data.context.reset, " Available Options: ");

    printf("\n  %s", f_console_symbol_short_enable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, f_console_standard_short_help);

    printf(", %s", f_console_symbol_long_enable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, f_console_standard_long_help);
    printf("      Print this help message");

    printf("\n  %s", f_console_symbol_short_disable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, f_console_standard_short_light);

    printf(", %s", f_console_symbol_long_disable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, f_console_standard_long_light);
    printf("     Output using colors that show up better on light backgrounds");

    printf("\n  %s", f_console_symbol_short_disable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, f_console_standard_short_no_color);

    printf(", %s", f_console_symbol_long_disable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, f_console_standard_long_no_color);
    printf("  Do not output in color");

    printf("\n  %s", f_console_symbol_short_enable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, f_console_standard_short_version);

    printf(", %s", f_console_symbol_long_enable);
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, f_console_standard_long_version);
    printf("   Print only the version number");

    printf("\n\n");
    fl_print_color(f_standard_output, data.context.important, data.context.reset, " Available Commands: ");

    printf("\n  ");
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, firewall_command_start);
    printf("    Turn on the firewall");

    printf("\n  ");
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, firewall_command_stop);
    printf("     Turn off the firewall");

    printf("\n  ");
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, firewall_command_restart);
    printf("  Turn off and then turn on the firewall");

    printf("\n  ");
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, firewall_command_lock);
    printf("     Prevent all communication");

    printf("\n  ");
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, firewall_command_show);
    printf("     Show active firewall settings");

    printf("\n\n");
    fl_print_color(f_standard_output, data.context.important, data.context.reset, " Usage: ");

    printf("\n  ");
    fl_print_color(f_standard_output, data.context.standout, data.context.reset, firewall_name);

    printf("  ");
    fl_print_color(f_standard_output, data.context.notable, data.context.reset, "[");

    printf(" options ");
    fl_print_color(f_standard_output, data.context.notable, data.context.reset, "]");

    printf("  ");
    fl_print_color(f_standard_output, data.context.notable, data.context.reset, "[");

    printf(" command ");
    fl_print_color(f_standard_output, data.context.notable, data.context.reset, "]");

    printf("\n\n");

    return f_none;
  }
#endif // _di_firewall_print_help_

#ifndef _di_firewall_main_
  f_return_status firewall_main(const f_s_int argc, const f_string argv[], firewall_data *data) {
    f_status status            = f_status_initialize;
    f_status allocation_status = f_status_initialize;

    status = fl_process_parameters(argc, argv, data->parameters, firewall_total_parameters, &data->remaining);

    // load colors when not told to show no colors
    if (data->parameters[firewall_parameter_no_color].result == f_console_result_none) {
      fll_new_color_context(allocation_status, data->context);

      if (allocation_status == f_none) {
        fll_colors_load_context(&data->context, data->parameters[firewall_parameter_light].result == f_console_result_found);
      } else {
        fprintf(f_standard_error, "Critical Error: unable to allocate memory\n");
        firewall_delete_data(data);
        return allocation_status;
      }
    }

    if (status != f_none) {
      if (status == f_no_data) {
        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: One of the parameters you passed requires an additional parameter that you did not pass.");
        // TODO: there is a way to identify which parameter is incorrect
        //       to do this, one must look for any "has_additional" and then see if the "additiona" location is set to 0
        //       nothing can be 0 as that represents the program name, unless argv[] is improperly created
      } else if (f_macro_test_for_allocation_errors(status)) {
        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: unable to allocate memory");
      } else if (status == f_invalid_parameter) {
        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: Invalid parameter when calling fl_process_parameters()");
      } else {
        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling fl_process_parameters()", status);
      }

      firewall_delete_data(data);
      return status;
    }

    // execute parameter results
    if (data->parameters[firewall_parameter_help].result == f_console_result_found) {
      firewall_print_help(*data);
    } else if (data->parameters[firewall_parameter_version].result == f_console_result_found) {
      firewall_print_version(*data);
    } else {
      // now determine which command was placed first
      f_bool  found_command = f_false;
      f_u_int command       = 0;

      if (data->parameters[firewall_parameter_command_start].result == f_console_result_found) {
        command       = firewall_parameter_command_start;
        found_command = f_true;
      }

      if (data->parameters[firewall_parameter_command_stop].result == f_console_result_found) {
        if (found_command) {
          if (data->parameters[command].additional.array[0] > data->parameters[firewall_parameter_command_stop].additional.array[0]) {
            command = firewall_parameter_command_stop;
          }
        } else {
          command       = firewall_parameter_command_stop;
          found_command = f_true;
        }
      }

      if (data->parameters[firewall_parameter_command_restart].result == f_console_result_found) {
        if (found_command) {
          if (data->parameters[command].additional.array[0] > data->parameters[firewall_parameter_command_restart].additional.array[0]) {
            command = firewall_parameter_command_restart;
          }
        } else {
          command       = firewall_parameter_command_restart;
          found_command = f_true;
        }
      }

      if (data->parameters[firewall_parameter_command_lock].result == f_console_result_found) {
        if (found_command) {
          if (data->parameters[command].additional.array[0] > data->parameters[firewall_parameter_command_lock].additional.array[0]) {
            command = firewall_parameter_command_lock;
          }
        } else {
          command       = firewall_parameter_command_lock;
          found_command = f_true;
        }
      }

      if (data->parameters[firewall_parameter_command_show].result == f_console_result_found) {
        if (found_command) {
          if (data->parameters[command].additional.array[0] > data->parameters[firewall_parameter_command_show].additional.array[0]) {
            command = firewall_parameter_command_show;
          }
        } else {
          command       = firewall_parameter_command_show;
          found_command = f_true;
        }
      }

      if (found_command) {
        // load the global file
        {
          f_file file = f_file_initialize;

          status = f_file_open(&file, (f_string) network_path firewall_file_default);

          if (status != f_none) {
            if (status == f_invalid_parameter) {
              fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: Invalid parameter when calling f_file_open()");
            } else if (status == f_file_not_found) {
              fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Unable to find the file '%s'", network_path firewall_file_default);
            } else if (status == f_file_open_error) {
              fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Unable to open the file '%s'", network_path firewall_file_default);
            } else if (status == f_file_descriptor_error) {
              fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: File descriptor error while trying to open the file '%s'", network_path firewall_file_default);
            } else {
              fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling f_file_open()", status);
            }

            firewall_delete_data(data);
            return status;
          }

          // TODO: this file size set functionality might be turned into an fl_file (or f_file) function
          if (data->file_position.total_elements == 0) {
            fseek(file.file, 0, SEEK_END);
            data->file_position.total_elements = ftell(file.file);
            fseek(file.file, 0, SEEK_SET);
          }

          status = fl_file_read(file, data->file_position, &data->buffer);

          f_file_close(&file);

          if (status != f_none && status != f_none_on_eof) {
            if (status == f_invalid_parameter) {
              fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: Invalid parameter when calling fl_file_read()");
            } else if (status == f_overflow) {
              fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Integer overflow while trying to buffer the file '%s'", network_path firewall_file_default);
            } else if (status == f_file_not_open) {
              fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: The file '%s' is no longer open", network_path firewall_file_default);
            } else if (status == f_file_seek_error) {
              fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: A seek error occurred while accessing the file '%s'", network_path firewall_file_default);
            } else if (status == f_file_read_error) {
              fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: A read error occurred while accessing the file '%s'", network_path firewall_file_default);
            } else if (f_macro_test_for_allocation_errors(status)) {
              fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: unable to allocate memory");
            } else {
              fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling fl_file_read()", status);
            }

            firewall_delete_data(data);
            return status;
          } else {
            f_string_location input = f_string_location_initialize;

            input.stop = data->buffer.used - 1;

            status = fll_fss_basic_list_read(&data->buffer, &input, &data->objects, &data->contents);
          }

          if (status != f_none && status != f_none_on_eos && status != f_none_on_stop && status != fl_fss_found_object_no_content) {
            if (status == f_invalid_parameter) {
              fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: Invalid parameter when calling fll_fss_basic_list_read() for the file '%s'", network_path firewall_file_default);
            } else if (status == f_no_data_on_eos || status == f_no_data || status == f_no_data_on_stop) {
              fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: No relevant data was found within the file '%s'", network_path firewall_file_default);
            } else if (f_macro_test_for_allocation_errors(status)) {
              fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: unable to allocate memory");
            } else {
              fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling fll_fss_basic_list_read() for the file '%s'", status, network_path firewall_file_default);
            }

            firewall_delete_data(data);
            return status;
          }
        }

        if (command == firewall_parameter_command_show) {
          // Warning: these are hardcoded print commands (I am not certain how I am going to implement external 'show' rules as the default-firewall setting file is the wrong place to put this)
          f_bool show_nat    = f_true;
          f_bool show_mangle = f_true;
          f_bool show_ports  = f_true;

          f_dynamic_strings arguments = f_dynamic_strings_initialize;
          f_s_int           results   = 0;

          if (data->remaining.used > 0) {
            show_nat    = f_false;
            show_mangle = f_false;
            show_ports  = f_false;

            f_string_length counter = f_string_length_initialize;

            for (; counter < data->remaining.used; counter++) {
              if (strncmp("nat", argv[data->remaining.array[counter]], 4) != 0) {
                if (strncmp("mangle",  argv[data->remaining.array[counter]], 7) != 0) {
                  if (strncmp("ports",  argv[data->remaining.array[counter]], 6) != 0) {
                    fl_print_color_line(f_standard_warning, data->context.warning, data->context.reset, "WARNING: '%s' is not a valid show option", argv[data->remaining.array[counter]]);
                  } else {
                    show_ports = f_true;
                  }
                } else {
                  show_mangle = f_true;
                }
              } else {
                show_nat = f_true;
              }
            } // for
          }

          f_resize_dynamic_strings(status, arguments, 7);

          if (f_macro_test_for_allocation_errors(status)) {
            fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: unable to allocate memory");
            firewall_delete_data(data);
            return status;
          }

          if (show_nat) {
            fl_print_color(f_standard_output, data->context.standout, data->context.reset, "=========================== ");
            fl_print_color(f_standard_output, data->context.title, data->context.reset, "NAT");
            fl_print_color_line(f_standard_output, data->context.standout, data->context.reset, " ============================");
            fflush(f_standard_output);

            arguments.used = 7;

            arguments.array[0].string = (f_string) firewall_program_name;
            arguments.array[1].string = (f_string) "-x";
            arguments.array[2].string = (f_string) "-v";
            arguments.array[3].string = (f_string) "-t";
            arguments.array[4].string = (f_string) "nat";
            arguments.array[5].string = (f_string) "--numeric";
            arguments.array[6].string = (f_string) "--list";

            arguments.array[0].used = firewall_program_name_length;
            arguments.array[1].used = 2;
            arguments.array[2].used = 2;
            arguments.array[3].used = 2;
            arguments.array[4].used = 3;
            arguments.array[5].used = 9;
            arguments.array[6].used = 6;

            status = fll_execute_program((f_string) firewall_program_name, arguments, &results);

            fprintf(f_standard_output, "\n");
            fflush(f_standard_output);
          }

          if (status != f_failure && show_mangle) {
            fl_print_color(f_standard_output, data->context.standout, data->context.reset, "========================== ");
            fl_print_color(f_standard_output, data->context.title, data->context.reset, "MANGLE");
            fl_print_color_line(f_standard_output, data->context.standout, data->context.reset, " ==========================");
            fflush(f_standard_output);

            arguments.used = 7;

            arguments.array[0].string = (f_string) firewall_program_name;
            arguments.array[1].string = (f_string) "-x";
            arguments.array[2].string = (f_string) "-v";
            arguments.array[3].string = (f_string) "-t";
            arguments.array[4].string = (f_string) "mangle";
            arguments.array[5].string = (f_string) "--numeric";
            arguments.array[6].string = (f_string) "--list";

            arguments.array[0].used = firewall_program_name_length;
            arguments.array[1].used = 2;
            arguments.array[2].used = 2;
            arguments.array[3].used = 2;
            arguments.array[4].used = 3;
            arguments.array[5].used = 9;
            arguments.array[6].used = 6;

            status = fll_execute_program((f_string) firewall_program_name, arguments, &results);

            fprintf(f_standard_output, "\n");
            fflush(f_standard_output);
          }

          if (status != f_failure && show_ports) {
            fl_print_color(f_standard_output, data->context.standout, data->context.reset, "========================== ");
            fl_print_color(f_standard_output, data->context.title, data->context.reset, "PORTS");
            fl_print_color_line(f_standard_output, data->context.standout, data->context.reset, " ===========================");
            fflush(f_standard_output);

            arguments.used = 5;

            arguments.array[0].string = (f_string) firewall_program_name;
            arguments.array[1].string = (f_string) "-x";
            arguments.array[2].string = (f_string) "-v";
            arguments.array[3].string = (f_string) "--numeric";
            arguments.array[4].string = (f_string) "--list";

            arguments.array[0].used = firewall_program_name_length;
            arguments.array[1].used = 2;
            arguments.array[2].used = 2;
            arguments.array[3].used = 9;
            arguments.array[4].used = 6;

            status = fll_execute_program((f_string) firewall_program_name, arguments, &results);

            fprintf(f_standard_output, "\n");
            fflush(f_standard_output);
          }

          if (status == f_failure) {
            fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Failed to perform requested %s operation:", firewall_program_name);
            fprintf(f_standard_error, "  ");

            f_string_length i = f_string_length_initialize;

            fl_print_color_code(f_standard_error, data->context.error);

            for (; i < arguments.used; i++) {
              fprintf(f_standard_error, "%s ", arguments.array[i].string);
            }

            fl_print_color_code(f_standard_error, data->context.reset);
            fprintf(f_standard_error, "\n");
          } else if (f_macro_test_for_allocation_errors(status)) {
            fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: unable to allocate memory");
          }

          arguments.array[0].string = 0;
          arguments.array[1].string = 0;
          arguments.array[2].string = 0;
          arguments.array[3].string = 0;
          arguments.array[4].string = 0;
          arguments.array[5].string = 0;
          arguments.array[6].string = 0;
          arguments.array[0].used = 0;
          arguments.array[1].used = 0;
          arguments.array[2].used = 0;
          arguments.array[3].used = 0;
          arguments.array[4].used = 0;
          arguments.array[5].used = 0;
          arguments.array[6].used = 0;
          f_delete_dynamic_strings(status, arguments);

          firewall_delete_data(data);
          return f_none;
        }

        // load all network devices
        status = fl_directory_list((f_string) network_devices, &data->devices);

        if (f_macro_test_for_allocation_errors(status)) {
          fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: unable to allocate memory");
          firewall_delete_data(data);
          return status;
        } else if (status == f_no_data) {
          fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: could not find any network devices");
          firewall_delete_data(data);
          return status;
        } else if (status == f_failure) {
          fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: failed to read the device directory '%s'", network_devices);
          firewall_delete_data(data);
          return status;
        }

        // remove "lo" (loopback) from the device listing
        {
          f_string_length counter = f_string_length_initialize;

          for (; counter < data->devices.used; counter++) {
            if (fl_compare_strings((f_string) "lo", data->devices.array[counter].string, 3, data->devices.array[counter].used) == f_equal_to) {
              f_dynamic_string swap_string = data->devices.array[counter];

              data->devices.used--;

              for (; counter < data->devices.used; counter++) {
                data->devices.array[counter] = data->devices.array[counter+1];
              }

              data->devices.array[data->devices.used] = swap_string;
            }
          }
        }

        // if at least one specific device was specified, then only use the specified devices, otherwise use all
        if (data->remaining.used > 0) {
          f_string_length device  = f_string_length_initialize;
          f_string_length counter = f_string_length_initialize;
          f_string_length total   = f_string_length_initialize;
          f_string_length i       = f_string_length_initialize;
          f_bool          matched = f_false;

          for (total = data->devices.used; device < total; device++) {
            matched = f_false;

            for (counter = 0; counter < data->remaining.used; counter++) {
              if (strncmp(data->devices.array[device].string, argv[data->remaining.array[counter]], strlen(argv[data->remaining.array[counter]])) == 0) {
                matched = f_true;
              }
            }

            if (!matched) {
              f_dynamic_string swap_string = data->devices.array[device];

              data->devices.used--;

              for (i = device; i < data->devices.used; i++) {
                data->devices.array[i] = data->devices.array[i+1];
              }

              data->devices.array[data->devices.used] = swap_string;

              total--;
              device--;
            }
          }
        }

        // report and remove all "invalid" devices that are specified in the "remaining" variable
        {
          f_string_length device  = f_string_length_initialize;
          f_string_length counter = f_string_length_initialize;
          f_bool          matched = f_false;

          for (; counter < data->remaining.used; counter++) {
            matched = f_false;

            for (device = 0; device < data->devices.used; device++) {
              if (strncmp(data->devices.array[device].string, argv[data->remaining.array[counter]], strlen(argv[data->remaining.array[counter]])) == 0) {
                matched = f_true;
              }
            }

            if (!matched) {
              fl_print_color_line(f_standard_warning, data->context.warning, data->context.reset, "WARNING: There is no device by the name of '%s'", argv[data->remaining.array[counter]]);
            }
          }

          // cleanup, the 'remaining' parameters are no longer needed
          f_delete_string_locations(status, data->remaining);
        }

        // identify global firewall settings
        f_string_length first = f_string_length_initialize;
        f_string_length last  = f_string_length_initialize;
        f_string_length stop  = f_string_length_initialize;
        f_string_length lock  = f_string_length_initialize;

        f_bool found_first = f_false;
        f_bool found_last  = f_false;
        f_bool found_stop  = f_false;
        f_bool found_lock  = f_false;

        f_string_length length  = f_string_length_initialize;
        f_string_length counter = f_string_length_initialize;

        // identify which position is which
        for (; counter < data->objects.used; counter++) {
          length = data->objects.array[counter].stop - data->objects.array[counter].start + 1;

          if (!found_first && fl_compare_strings((f_string) firewall_group_first, data->buffer.string + data->objects.array[counter].start, firewall_group_first_length, length) == f_equal_to) {
            first = counter;
            found_first = f_true;
          } else if (!found_last && fl_compare_strings((f_string) firewall_group_last, data->buffer.string + data->objects.array[counter].start, firewall_group_last_length, length) == f_equal_to) {
            last = counter;
            found_last = f_true;
          } else if (!found_stop && fl_compare_strings((f_string) firewall_group_stop, data->buffer.string + data->objects.array[counter].start, firewall_group_stop_length, length) == f_equal_to) {
            stop = counter;
            found_stop = f_true;
          } else if (!found_lock && fl_compare_strings((f_string) firewall_group_lock, data->buffer.string + data->objects.array[counter].start, firewall_group_lock_length, length) == f_equal_to) {
            lock = counter;
            found_lock = f_true;
          } else {
            if (data->custom.used >= data->custom.size) {
              f_resize_string_lengths(status, data->custom, data->custom.size + firewall_default_allocation_step);

              if (f_macro_test_for_allocation_errors(status)) {
                fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: unable to allocate memory");
                firewall_delete_data(data);
                return status;
              }
            }

            data->custom.array[data->custom.used] = counter;
            data->custom.used++;
          }
        }

        if (found_first && found_last && found_stop && found_lock) {
          f_string_length error_file = f_string_length_initialize;
          status = f_none;

          f_fss_objects  extended_objects  = f_fss_objects_initialize;
          f_fss_contents extended_contents = f_fss_contents_initialize;

          if (command == firewall_parameter_command_lock) {
            f_string_location input = f_string_location_initialize;

            input.start = data->contents.array[lock].array[0].start;
            input.stop  = data->contents.array[lock].array[0].stop;
            error_file  = lock;

            status = fll_fss_extended_read(&data->buffer, &input, &extended_objects, &extended_contents);

            if (status == f_none || status == f_none_on_stop || status == f_none_on_eos) {
              status = firewall_perform_commands(extended_objects, extended_contents, f_true, 0, data->buffer, *data, f_null);

              if (status != f_none) {
                if (f_macro_test_for_allocation_errors(status)) {
                  fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: unable to allocate memory", status);
                } else if (status == f_failure) {
                  // the error message has already been displayed
                } else {
                  fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling firewall_perform_commands()", status);
                }

                f_delete_fss_objects(allocation_status, extended_objects);
                f_delete_fss_contents(allocation_status, extended_contents);

                firewall_delete_data(data);
                return status;
              }
            }
          } else {
            if (command == firewall_parameter_command_stop || command == firewall_parameter_command_restart) {
              f_string_location input = f_string_location_initialize;

              input.start = data->contents.array[stop].array[0].start;
              input.stop  = data->contents.array[stop].array[0].stop;
              error_file  = stop;

              status = fll_fss_extended_read(&data->buffer, &input, &extended_objects, &extended_contents);

              if (status == f_none || status == f_none_on_stop || status == f_none_on_eos) {
                status = firewall_perform_commands(extended_objects, extended_contents, f_true, 0, data->buffer, *data, f_null);
              }
            }

            if ((status == f_none || status == f_none_on_stop || status == f_none_on_eos) && (command == firewall_parameter_command_start || command == firewall_parameter_command_restart)) {
              f_delete_fss_objects(status, extended_objects);
              f_delete_fss_contents(status, extended_contents);

              f_string_location input = f_string_location_initialize;

              input.start = data->contents.array[first].array[0].start;
              input.stop  = data->contents.array[first].array[0].stop;
              error_file  = first;

              status = fll_fss_extended_read(&data->buffer, &input, &extended_objects, &extended_contents);

              if (status == f_none || status == f_none_on_stop || status == f_none_on_eos) {
                status = firewall_perform_commands(extended_objects, extended_contents, f_true, 0, data->buffer, *data, f_null);

                if (status != f_none) {
                  if (f_macro_test_for_allocation_errors(status)) {
                    fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: unable to allocate memory", status);
                  } else if (status == f_failure) {
                    // the error message has already been displayed
                  } else {
                    fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling firewall_perform_commands()", status);
                  }

                  f_delete_fss_objects(allocation_status, extended_objects);
                  f_delete_fss_contents(allocation_status, extended_contents);

                  firewall_delete_data(data);
                  return status;
                } else {
                  f_delete_fss_objects(status, extended_objects);
                  f_delete_fss_contents(status, extended_contents);

                  f_string_length counter = 0;

                  {
                    f_dynamic_string chain_argument = f_dynamic_string_initialize;

                    while (counter < data->custom.used) {
                      f_dynamic_string custom_chain   = f_dynamic_string_initialize;
                      f_string_length  chain_location = 0;

                      input.start = data->objects.array[data->custom.array[counter]].start;
                      input.stop  = data->objects.array[data->custom.array[counter]].stop;

                      // ensure that the chain exists
                      if (counter < data->custom.used && data->custom.array[counter] < data->objects.used) {
                        f_string_length counter2  = 0;
                        f_string_length max_size  = 0;
                        f_bool          new_chain = f_true;

                        counter2 = input.start;
                        max_size = input.stop - input.start + 1;

                        if (max_size >= custom_chain.size) {
                          f_resize_dynamic_string(status, custom_chain, max_size + firewall_default_allocation_step);

                          if (f_macro_test_for_allocation_errors(status)) {
                            f_status allocation_status = f_status_initialize;

                            f_delete_dynamic_string(allocation_status, custom_chain);
                            f_delete_dynamic_string(allocation_status, chain_argument);
                            f_delete_fss_objects(allocation_status, extended_objects);
                            f_delete_fss_contents(allocation_status, extended_contents);
                            firewall_delete_data(data);
                            return status;
                          }
                        }

                        custom_chain.used = 0;
                        counter2 = input.start;
                        while (counter2 <= input.stop && custom_chain.used <= custom_chain.size) {
                          if (data->buffer.string[counter2] == f_fss_delimit_placeholder) {
                            counter2++;
                            continue;
                          }

                          custom_chain.string[custom_chain.used] = data->buffer.string[counter2];
                          custom_chain.used++;
                          counter2++;
                        } // while

                        if (firewall_chain_create_command_length > chain_argument.size) {
                          f_resize_dynamic_string(status, chain_argument, firewall_chain_create_command_length);

                          if (f_macro_test_for_allocation_errors(status)) {
                            f_status allocation_status = f_status_initialize;

                            f_delete_dynamic_string(allocation_status, custom_chain);
                            f_delete_dynamic_string(allocation_status, chain_argument);
                            f_delete_fss_objects(allocation_status, extended_objects);
                            f_delete_fss_contents(allocation_status, extended_contents);
                            firewall_delete_data(data);
                            return status;
                          }
                        }

                        strncat(chain_argument.string, firewall_chain_create_command, firewall_chain_create_command_length);
                        chain_argument.used = firewall_chain_create_command_length;
                        chain_location = 0;


                        while (chain_location < data->chains.used) {
                          if (fl_compare_dynamic_strings(custom_chain, data->chains.array[chain_location]) == f_equal_to) {
                            f_delete_dynamic_string(allocation_status, custom_chain);

                            new_chain = f_false;
                            break;
                          }

                          chain_location++;
                        } // while

                        if (new_chain) {
                          if (data->chains.used >= data->chains.size) {
                            f_resize_dynamic_strings(status, data->chains, data->chains.size + firewall_default_allocation_step);

                            if (f_macro_test_for_allocation_errors(status)) {
                              f_status allocation_status = f_status_initialize;

                              f_delete_dynamic_string(allocation_status, custom_chain);
                              f_delete_dynamic_string(allocation_status, chain_argument);
                              f_delete_fss_objects(allocation_status, extended_objects);
                              f_delete_fss_contents(allocation_status, extended_contents);
                              firewall_delete_data(data);
                              return status;
                            }
                          }

                          f_s_int           results   = 0;
                          f_dynamic_strings arguments = f_dynamic_strings_initialize;

                          f_resize_dynamic_strings(status, arguments, 3);

                          arguments.array[0].string = (f_string) firewall_chain_create_command;
                          arguments.array[1].string = chain_argument.string;
                          arguments.array[2].string = custom_chain.string;

                          arguments.array[0].used = firewall_chain_create_command_length;
                          arguments.array[1].used = chain_argument.used;
                          arguments.array[2].used = custom_chain.used;

                          arguments.used = 3;
                          arguments.size = 3;

                          if (f_macro_test_for_allocation_errors(status)) {
                            f_status allocation_status = f_status_initialize;

                            arguments.array[0].string = 0;
                            arguments.array[1].string = 0;
                            arguments.array[2].string = 0;

                            arguments.array[0].used = 0;
                            arguments.array[1].used = 0;
                            arguments.array[2].used = 0;

                            f_delete_dynamic_string(allocation_status, custom_chain);
                            f_delete_dynamic_string(allocation_status, chain_argument);
                            f_delete_dynamic_strings(allocation_status, arguments);
                            f_delete_fss_objects(allocation_status, extended_objects);
                            f_delete_fss_contents(allocation_status, extended_contents);
                            firewall_delete_data(data);
                            return status;
                          }

                          status = fll_execute_program((f_string) firewall_program_name, arguments, &results);

                          if (status == f_failure) {
                            f_status allocation_status = f_status_initialize;

                            fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Failed to perform requested %s operation:", firewall_program_name);
                            fprintf(f_standard_error, "  ");

                            f_string_length i = f_string_length_initialize;

                            fl_print_color_code(f_standard_error, data->context.error);

                            for (; i < arguments.used; i++) {
                              fprintf(f_standard_error, "%s ", arguments.array[i].string);
                            }

                            fl_print_color_code(f_standard_error, data->context.reset);
                            fprintf(f_standard_error, "\n");

                            arguments.array[0].string = 0;
                            arguments.array[1].string = 0;
                            arguments.array[2].string = 0;

                            arguments.array[0].used = 0;
                            arguments.array[1].used = 0;
                            arguments.array[2].used = 0;

                            f_delete_dynamic_string(allocation_status, custom_chain);
                            f_delete_dynamic_string(allocation_status, chain_argument);
                            f_delete_dynamic_strings(allocation_status, arguments);
                            f_delete_fss_objects(allocation_status, extended_objects);
                            f_delete_fss_contents(allocation_status, extended_contents);
                            firewall_delete_data(data);
                            return status;
                          } else if (status == f_invalid_parameter) {
                            f_status allocation_status = f_status_initialize;

                            fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: Invalid parameter when calling fl_execute_path()");

                            arguments.array[0].string = 0;
                            arguments.array[1].string = 0;
                            arguments.array[2].string = 0;

                            arguments.array[0].used = 0;
                            arguments.array[1].used = 0;
                            arguments.array[2].used = 0;

                            f_delete_dynamic_string(allocation_status, custom_chain);
                            f_delete_dynamic_string(allocation_status, chain_argument);
                            f_delete_dynamic_strings(allocation_status, arguments);
                            f_delete_fss_objects(allocation_status, extended_objects);
                            f_delete_fss_contents(allocation_status, extended_contents);
                            firewall_delete_data(data);
                            return status;
                          }

                          arguments.array[0].string = 0;
                          arguments.array[1].string = 0;
                          arguments.array[2].string = 0;

                          arguments.array[0].used = 0;
                          arguments.array[1].used = 0;
                          arguments.array[2].used = 0;

                          f_delete_dynamic_strings(status, arguments);

                          data->chains.array[data->chains.used] = custom_chain;
                          custom_chain.string = 0;
                          custom_chain.used = 0;
                          chain_location = data->chains.used;
                          data->chains.used++;
                        }
                      }

                      input.start = data->contents.array[data->custom.array[counter]].array[0].start;
                      input.stop  = data->contents.array[data->custom.array[counter]].array[0].stop;

                      status = fll_fss_extended_read(&data->buffer, &input, &extended_objects, &extended_contents);

                      if (status == f_none || status == f_none_on_stop || status == f_none_on_eos) {
                        status = firewall_perform_commands(extended_objects, extended_contents, f_true, counter, data->buffer, *data, &data->chains.array[chain_location]);

                        if (status != f_none) {
                          if (f_macro_test_for_allocation_errors(status)) {
                            fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: unable to allocate memory", status);
                          } else if (status == f_failure) {
                            // the error message has already been displayed
                          } else {
                            fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling firewall_perform_commands()", status);
                          }
                        }
                      }

                      f_delete_dynamic_string(status, chain_argument);
                      f_delete_fss_objects(status, extended_objects);
                      f_delete_fss_contents(status, extended_contents);

                      counter++;
                    } // while
                  }

                  counter = 0;

                  for (; counter < data->devices.used; counter++) {
                    f_file           file          = f_file_initialize;
                    f_dynamic_string file_path     = f_dynamic_string_initialize;
                    f_dynamic_string buffer        = f_dynamic_string_initialize;
                    f_file_position  file_position = f_file_position_initialize;

                    f_fss_objects  list_objects  = f_fss_objects_initialize;
                    f_fss_contents list_contents = f_fss_objects_initialize;

                    f_resize_dynamic_string(status, file_path, network_path_length + data->devices.array[counter].used + firewall_file_suffix_length + 1);

                    if (status == f_none) {
                      strncat(file_path.string, network_path, network_path_length);
                      strncat(file_path.string + network_path_length, data->devices.array[counter].string, data->devices.array[counter].used);
                      strncat(file_path.string, firewall_file_suffix, firewall_file_suffix_length);
                      file_path.used = file_path.size;
                      file_path.string[file_path.used] = 0;

                      status = f_file_open(&file, file_path.string);
                    }

                    if (status != f_none) {
                      if (status == f_invalid_parameter) {
                        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: Invalid parameter when calling f_file_open()");
                      } else if (status == f_file_not_found) {
                        // If these files do not exist, it is not a problem (they are not required)
                      } else if (status == f_file_open_error) {
                        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Unable to open the file '%s'", file_path.string);
                      } else if (status == f_file_descriptor_error) {
                        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: File descriptor error while trying to open the file '%s'", file_path.string);
                      } else if (f_macro_test_for_allocation_errors(status)) {
                        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: unable to allocate memory", status);

                        f_file_close(&file);
                        f_delete_dynamic_string(allocation_status, file_path);
                        firewall_delete_data(data);
                        return status;
                      } else {
                        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling f_file_open()", status);
                      }

                      f_file_close(&file);
                      f_delete_dynamic_string(allocation_status, file_path);
                      continue;
                    }


                    if (data->file_position.total_elements == 0) {
                      fseek(file.file, 0, SEEK_END);
                      data->file_position.total_elements = ftell(file.file);
                      fseek(file.file, 0, SEEK_SET);
                    }

                    status = fl_file_read(file, file_position, &buffer);

                    f_file_close(&file);

                    if (status != f_none && status != f_none_on_eof) {
                      if (status == f_invalid_parameter) {
                        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: Invalid parameter when calling fl_file_read()");
                      } else if (status == f_overflow) {
                        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Integer overflow while trying to buffer the file '%s'", file_path.string);
                      } else if (status == f_file_not_open) {
                        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: The file '%s' is no longer open", file_path.string);
                      } else if (status == f_file_seek_error) {
                        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: A seek error occurred while accessing the file '%s'", file_path.string);
                      } else if (status == f_file_read_error) {
                        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: A read error occurred while accessing the file '%s'", file_path.string);
                      } else if (f_macro_test_for_allocation_errors(status)) {
                        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: unable to allocate memory", status);

                        f_delete_dynamic_string(allocation_status, buffer);
                        f_delete_dynamic_string(allocation_status, file_path);
                        firewall_delete_data(data);
                        return status;
                      } else {
                        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling fl_file_read()", status);
                      }

                      f_delete_dynamic_string(allocation_status, buffer);
                      f_delete_dynamic_string(allocation_status, file_path);
                      continue;
                    }

                    {
                      f_string_location input = f_string_location_initialize;

                      input.stop = buffer.used - 1;

                      status = fll_fss_basic_list_read(&buffer, &input, &list_objects, &list_contents);
                    }

                    if (status != f_none && status != f_none_on_eos && status != f_none_on_stop && status != fl_fss_found_object_no_content) {
                      if (status == f_invalid_parameter) {
                        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: Invalid parameter when calling fll_fss_basic_list_read() for the file '%s'", file_path.string);
                      } else if (status == f_no_data_on_eos || status == f_no_data || status == f_no_data_on_stop) {
                        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: No relevant data was found within the file '%s'", file_path.string);
                      } else if (f_macro_test_for_allocation_errors(status)) {
                        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: unable to allocate memory", status);
                      } else {
                        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling fll_fss_basic_list_read() for the file '%s'", status, file_path.string);
                      }

                      f_delete_dynamic_string(allocation_status, buffer);
                      f_delete_dynamic_string(allocation_status, file_path);
                      f_delete_fss_objects(allocation_status, list_objects);
                      f_delete_fss_contents(allocation_status, list_contents);
                      firewall_delete_data(data);
                      return status;
                    }

                    {
                      f_string_length buffer_counter = f_string_length_initialize;
                      f_string_length length         = f_string_length_initialize;

                      while (buffer_counter < list_objects.used) {
                        length = list_objects.array[buffer_counter].stop - list_objects.array[buffer_counter].start + 1;

                        if (fl_compare_strings((f_string) firewall_group_main, buffer.string + list_objects.array[buffer_counter].start, firewall_group_main_length, length) == f_equal_to) {
                          f_string_location input = f_string_location_initialize;

                          input.start = list_contents.array[buffer_counter].array[0].start;
                          input.stop  = list_contents.array[buffer_counter].array[0].stop;

                          status = fll_fss_extended_read(&buffer, &input, &extended_objects, &extended_contents);

                          if (status == f_none || status == f_none_on_stop || status == f_none_on_eos) {
                            status = firewall_perform_commands(extended_objects, extended_contents, f_false, counter, buffer, *data, f_null);

                            if (status != f_none) {
                              if (f_macro_test_for_allocation_errors(status)) {
                                fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: unable to allocate memory", status);
                              } else if (status == f_failure) {
                                // the error message has already been displayed
                              } else {
                                fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling firewall_perform_commands()", status);
                              }
                            }
                          } else {
                            if (status == f_invalid_parameter) {
                              fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: Invalid parameter when calling fll_fss_extended_read() for the file '%s'", file_path.string);
                            } else if (status == f_no_data_on_eos || status == f_no_data || status == f_no_data_on_stop) {
                              fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: No relevant data was found within the file '%s'", file_path.string);
                            } else if (f_macro_test_for_allocation_errors(status)) {
                              fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: unable to allocate memory", status);
                            } else {
                              fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling fll_fss_extended_read() for the file '%s'", status, file_path.string);
                            }
                          }
                        } else if (fl_compare_strings((f_string) firewall_group_first, buffer.string + list_objects.array[buffer_counter].start, firewall_group_first_length, length) == f_equal_to) {
                          // skip this, device-specific rules do not support this.
                        } else if (fl_compare_strings((f_string) firewall_group_last, buffer.string + list_objects.array[buffer_counter].start, firewall_group_last_length, length) == f_equal_to) {
                          // skip this, device-specific rules do not support this.
                        } else if (fl_compare_strings((f_string) firewall_group_stop, buffer.string + list_objects.array[buffer_counter].start, firewall_group_stop_length, length) == f_equal_to) {
                          // skip this, device-specific rules do not support this.
                        } else if (fl_compare_strings((f_string) firewall_group_lock, buffer.string + list_objects.array[buffer_counter].start, firewall_group_lock_length, length) == f_equal_to) {
                          // skip this, device-specific rules do not support this.
                        } else {
                          f_delete_fss_objects(allocation_status, extended_objects);
                          f_delete_fss_contents(allocation_status, extended_contents);

                          f_string_location input = f_string_location_initialize;

                          f_dynamic_string custom_chain   = f_dynamic_string_initialize;
                          f_dynamic_string chain_argument = f_dynamic_string_initialize;
                          f_string_length  chain_location = 0;

                          f_string_length counter2  = 0;
                          f_string_length max_size  = 0;
                          f_bool          new_chain = f_true;

                          input.start = list_objects.array[buffer_counter].start;
                          input.stop  = list_objects.array[buffer_counter].stop;

                          if (data->chains.used >= data->chains.size) {
                            f_resize_dynamic_strings(status, data->chains, data->chains.size + firewall_default_allocation_step);

                            if (f_macro_test_for_allocation_errors(status)) {
                              f_status allocation_status = f_status_initialize;

                              f_delete_dynamic_string(allocation_status, custom_chain);
                              f_delete_dynamic_string(allocation_status, chain_argument);
                              f_delete_fss_objects(allocation_status, extended_objects);
                              f_delete_fss_contents(allocation_status, extended_contents);
                              firewall_delete_data(data);
                              return status;
                            }
                          }

                          // ensure that the chain exists
                          counter2 = list_objects.array[buffer_counter].start;
                          max_size = list_objects.array[buffer_counter].stop - list_objects.array[buffer_counter].start + 1;

                          if (max_size >= custom_chain.size) {
                            f_resize_dynamic_string(status, custom_chain, max_size + firewall_default_allocation_step);

                            if (f_macro_test_for_allocation_errors(status)) {
                              f_status allocation_status = f_status_initialize;

                              f_delete_dynamic_string(allocation_status, custom_chain);
                              f_delete_dynamic_string(allocation_status, chain_argument);
                              f_delete_fss_objects(allocation_status, extended_objects);
                              f_delete_fss_contents(allocation_status, extended_contents);
                              f_delete_dynamic_string(allocation_status, buffer);
                              f_delete_dynamic_string(allocation_status, file_path);
                              f_delete_fss_objects(allocation_status, list_objects);
                              f_delete_fss_contents(allocation_status, list_contents);
                              firewall_delete_data(data);
                              return status;
                            }
                          }

                          custom_chain.used = 0;
                          counter2 = input.start;
                          while (counter2 <= input.stop && custom_chain.used <= custom_chain.size) {
                            if (buffer.string[counter2] == f_fss_delimit_placeholder) {
                              counter2++;
                              continue;
                            }

                            custom_chain.string[custom_chain.used] = buffer.string[counter2];
                            custom_chain.used++;
                            counter2++;
                          } // while

                          if (firewall_chain_create_command_length > chain_argument.size) {
                            f_resize_dynamic_string(status, chain_argument, firewall_chain_create_command_length);

                            if (f_macro_test_for_allocation_errors(status)) {
                              f_status allocation_status = f_status_initialize;

                              f_delete_dynamic_string(allocation_status, custom_chain);
                              f_delete_dynamic_string(allocation_status, chain_argument);
                              f_delete_fss_objects(allocation_status, extended_objects);
                              f_delete_fss_contents(allocation_status, extended_contents);
                              f_delete_dynamic_string(allocation_status, buffer);
                              f_delete_dynamic_string(allocation_status, file_path);
                              f_delete_fss_objects(allocation_status, list_objects);
                              f_delete_fss_contents(allocation_status, list_contents);
                              firewall_delete_data(data);
                              return status;
                            }
                          }

                          strncat(chain_argument.string, firewall_chain_create_command, firewall_chain_create_command_length);
                          chain_argument.used = firewall_chain_create_command_length;
                          chain_location = 0;

                          while (chain_location < data->chains.used) {
                            if (fl_compare_dynamic_strings(custom_chain, data->chains.array[chain_location]) == f_equal_to) {
                              f_delete_dynamic_string(allocation_status, custom_chain);

                              new_chain = f_false;
                              break;
                            }

                            chain_location++;
                          } // while

                          if (new_chain) {
                            if (data->chains.used >= data->chains.size) {
                              f_resize_dynamic_strings(status, data->chains, data->chains.size + firewall_default_allocation_step);

                              if (f_macro_test_for_allocation_errors(status)) {
                                f_status allocation_status = f_status_initialize;

                                f_delete_dynamic_string(allocation_status, custom_chain);
                                f_delete_dynamic_string(allocation_status, chain_argument);
                                f_delete_fss_objects(allocation_status, extended_objects);
                                f_delete_fss_contents(allocation_status, extended_contents);
                                f_delete_dynamic_string(allocation_status, buffer);
                                f_delete_dynamic_string(allocation_status, file_path);
                                f_delete_fss_objects(allocation_status, list_objects);
                                f_delete_fss_contents(allocation_status, list_contents);
                                firewall_delete_data(data);
                                return status;
                              }
                            }

                            f_s_int           results   = 0;
                            f_dynamic_strings arguments = f_dynamic_strings_initialize;

                            f_resize_dynamic_strings(status, arguments, 3);

                            arguments.array[0].string = (f_string) firewall_chain_create_command;
                            arguments.array[1].string = chain_argument.string;
                            arguments.array[2].string = custom_chain.string;

                            arguments.array[0].used = firewall_chain_create_command_length;
                            arguments.array[1].used = chain_argument.used;
                            arguments.array[2].used = custom_chain.used;

                            arguments.used = 3;
                            arguments.size = 3;

                            if (f_macro_test_for_allocation_errors(status)) {
                              f_status allocation_status = f_status_initialize;

                              arguments.array[0].string = 0;
                              arguments.array[1].string = 0;
                              arguments.array[2].string = 0;

                              arguments.array[0].used = 0;
                              arguments.array[1].used = 0;
                              arguments.array[2].used = 0;

                              f_delete_dynamic_string(allocation_status, custom_chain);
                              f_delete_dynamic_string(allocation_status, chain_argument);
                              f_delete_dynamic_strings(allocation_status, arguments);
                              f_delete_fss_objects(allocation_status, extended_objects);
                              f_delete_fss_contents(allocation_status, extended_contents);
                              f_delete_dynamic_string(allocation_status, buffer);
                              f_delete_dynamic_string(allocation_status, file_path);
                              f_delete_fss_objects(allocation_status, list_objects);
                              f_delete_fss_contents(allocation_status, list_contents);
                              firewall_delete_data(data);
                              return status;
                            }

                            status = fll_execute_program((f_string) firewall_program_name, arguments, &results);

                            if (status == f_failure) {
                              f_status allocation_status = f_status_initialize;

                              fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: Failed to perform requested %s operation:", firewall_program_name);
                              fprintf(f_standard_error, "  ");

                              f_string_length i = f_string_length_initialize;

                              fl_print_color_code(f_standard_error, data->context.error);

                              for (; i < arguments.used; i++) {
                                fprintf(f_standard_error, "%s ", arguments.array[i].string);
                              }

                              fl_print_color_code(f_standard_error, data->context.reset);
                              fprintf(f_standard_error, "\n");

                              arguments.array[0].string = 0;
                              arguments.array[1].string = 0;
                              arguments.array[2].string = 0;

                              arguments.array[0].used = 0;
                              arguments.array[1].used = 0;
                              arguments.array[2].used = 0;

                              f_delete_dynamic_string(allocation_status, custom_chain);
                              f_delete_dynamic_string(allocation_status, chain_argument);
                              f_delete_dynamic_strings(allocation_status, arguments);
                              f_delete_fss_objects(allocation_status, extended_objects);
                              f_delete_fss_contents(allocation_status, extended_contents);
                              f_delete_dynamic_string(allocation_status, buffer);
                              f_delete_dynamic_string(allocation_status, file_path);
                              f_delete_fss_objects(allocation_status, list_objects);
                              f_delete_fss_contents(allocation_status, list_contents);
                              firewall_delete_data(data);
                              return status;
                            } else if (status == f_invalid_parameter) {
                              f_status allocation_status = f_status_initialize;

                              fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: Invalid parameter when calling fl_execute_path()");

                              arguments.array[0].string = 0;
                              arguments.array[1].string = 0;
                              arguments.array[2].string = 0;

                              arguments.array[0].used = 0;
                              arguments.array[1].used = 0;
                              arguments.array[2].used = 0;

                              f_delete_dynamic_string(allocation_status, custom_chain);
                              f_delete_dynamic_string(allocation_status, chain_argument);
                              f_delete_dynamic_strings(allocation_status, arguments);
                              f_delete_fss_objects(allocation_status, extended_objects);
                              f_delete_fss_contents(allocation_status, extended_contents);
                              f_delete_dynamic_string(allocation_status, buffer);
                              f_delete_dynamic_string(allocation_status, file_path);
                              f_delete_fss_objects(allocation_status, list_objects);
                              f_delete_fss_contents(allocation_status, list_contents);
                              firewall_delete_data(data);
                              return status;
                            }

                            arguments.array[0].string = 0;
                            arguments.array[1].string = 0;
                            arguments.array[2].string = 0;

                            arguments.array[0].used = 0;
                            arguments.array[1].used = 0;
                            arguments.array[2].used = 0;

                            f_delete_dynamic_strings(status, arguments);

                            data->chains.array[data->chains.used] = custom_chain;
                            custom_chain.string = 0;
                            custom_chain.used = 0;
                            chain_location = data->chains.used;
                            data->chains.used++;
                          }

                          input.start = list_contents.array[buffer_counter].array[0].start;
                          input.stop  = list_contents.array[buffer_counter].array[0].stop;

                          status = fll_fss_extended_read(&buffer, &input, &extended_objects, &extended_contents);

                          if (status == f_none || status == f_none_on_stop || status == f_none_on_eos) {
                            status = firewall_perform_commands(extended_objects, extended_contents, f_false, buffer_counter, buffer, *data, &data->chains.array[chain_location]);

                            if (status != f_none) {
                              if (f_macro_test_for_allocation_errors(status)) {
                                fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: unable to allocate memory", status);
                              } else if (status == f_failure) {
                                // the error message has already been displayed
                              } else {
                                fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling firewall_perform_commands()", status);
                              }
                            }
                          }

                          f_delete_dynamic_string(allocation_status, chain_argument);
                          f_delete_fss_objects(allocation_status, extended_objects);
                          f_delete_fss_contents(allocation_status, extended_contents);
                        }

                        buffer_counter++;
                      } // while
                    }

                    f_delete_dynamic_string(allocation_status, buffer);
                    f_delete_dynamic_string(allocation_status, file_path);
                    f_delete_fss_objects(allocation_status, list_objects);
                    f_delete_fss_contents(allocation_status, list_contents);
                    f_delete_fss_objects(allocation_status, extended_objects);
                    f_delete_fss_contents(allocation_status, extended_contents);
                  }

                  input.start = data->contents.array[last].array[0].start;
                  input.stop  = data->contents.array[last].array[0].stop;
                  error_file  = last;

                  status = fll_fss_extended_read(&data->buffer, &input, &extended_objects, &extended_contents);

                  if (status == f_none || status == f_none_on_stop || status == f_none_on_eos) {
                    status = firewall_perform_commands(extended_objects, extended_contents, f_true, 0, data->buffer, *data, f_null);

                    if (status != f_none) {
                      if (f_macro_test_for_allocation_errors(status)) {
                        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: unable to allocate memory", status);
                      } else if (status == f_failure) {
                        // the error message has already been displayed
                      } else {
                        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "INTERNAL ERROR: An unhandled error (%u) has occured while calling firewall_perform_commands()", status);
                      }

                      f_delete_fss_objects(allocation_status, extended_objects);
                      f_delete_fss_contents(allocation_status, extended_contents);

                      firewall_delete_data(data);
                      return status;
                    }
                  }
                }
              }
            }
          }

          if (status != f_none && status != f_none_on_eos && status != f_none_on_stop && status != fl_fss_found_object_no_content) {
            if (status == f_invalid_parameter) {
              fl_print_color_code(f_standard_error, data->context.error);
              fprintf(f_standard_error, "INTERNAL ERROR: Invalid parameter when calling fll_fss_extended_read() for the file '");
              f_print_partial_dynamic_string(f_standard_error, data->buffer, data->contents.array[error_file].array[0]);
              fprintf(f_standard_error, "'");
              fl_print_color_code(f_standard_error, data->context.reset);
              fprintf(f_standard_error, "\n");
            } else if (status == f_no_data_on_eos || status == f_no_data || status == f_no_data_on_stop) {
              if (error_file == first || error_file == last || error_file == stop || error_file == lock) {
                fl_print_color_code(f_standard_error, data->context.error);
                fprintf(f_standard_error, "ERROR: No relevant data was found within the file '");
                f_print_partial_dynamic_string(f_standard_error, data->buffer, data->contents.array[error_file].array[0]);
                fprintf(f_standard_error, "'");
                fl_print_color_code(f_standard_error, data->context.reset);
                fprintf(f_standard_error, "\n");
              }
            } else if (f_macro_test_for_allocation_errors(status)) {
              fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "CRITICAL ERROR: unable to allocate memory", status);
            } else if (status == f_failure) {
              // the error message has already been displayed
            } else {
              fl_print_color_code(f_standard_error, data->context.error);
              fprintf(f_standard_error, "INTERNAL ERROR: An unhandled error (%u) has occured while calling fll_fss_extended_read() for the file '", status);
              f_print_partial_dynamic_string(f_standard_error, data->buffer, data->contents.array[error_file].array[0]);
              fprintf(f_standard_error, "'");
              fl_print_color_code(f_standard_error, data->context.reset);
              fprintf(f_standard_error, "\n");
            }
          }

          f_delete_fss_objects(allocation_status, extended_objects);
          f_delete_fss_contents(allocation_status, extended_contents);
        } else {
          const f_autochar *string = f_null;

          if (!found_first) {
            string = firewall_group_first;
          } else if (!found_last) {
            string = firewall_group_last;
          } else if (!found_stop) {
            string = firewall_group_stop;
          } else if (!found_lock) {
            string = firewall_group_lock;
          }

          fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: The required basic list '%s' was not found inside of the file '%s'", string, network_path firewall_file_default);
        }

        // cleanup
        f_delete_fss_contents(allocation_status, data->contents);
        f_delete_fss_objects(allocation_status, data->objects);
        f_delete_dynamic_string(allocation_status, data->buffer);
      } else {
        fl_print_color_line(f_standard_error, data->context.error, data->context.reset, "ERROR: You did not pass a command");
        status = f_invalid_parameter;
      }
    }

    firewall_delete_data(data);
    return status;
  }
#endif // _di_firewall_main_

#ifndef _di_firewall_delete_data_
  f_return_status firewall_delete_data(firewall_data *data) {
    f_status        status = f_status_initialize;
    f_string_length i      = 0;

    while (i < firewall_total_parameters) {
      f_delete_string_lengths(status, data->parameters[i].additional);
      i++;
    } // while

    f_delete_fss_contents(status, data->contents);
    f_delete_fss_objects(status, data->objects);
    f_delete_string_lengths(status, data->custom);
    f_delete_dynamic_strings(status, data->chains);
    f_delete_dynamic_string(status, data->buffer);
    f_delete_string_lengths(status, data->remaining);
    f_delete_dynamic_strings(status, data->devices);

    fll_delete_color_context(status, data->context);

    return f_none;
  }
#endif // _di_firewall_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif
