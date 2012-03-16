/* FLL - Level 1
 * Project:       Console
 * Version:       0.3.x
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 */
#include <level_1/console.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_fl_process_parameters_
  f_return_status fl_process_parameters(const f_array_length argc, const f_string argv[], f_console_parameter parameters[], const f_array_length total_parameters, f_string_lengths *remaining) {
    #ifndef _di_level_1_parameter_checking_
      if (remaining == f_null) return f_invalid_parameter;
    #endif // _di_level_1_parameter_checking_

    f_status     status = f_status_initialize;
    f_console_id result = 0;
    f_bool       found  = f_false;

    f_array_length location          = 1; // parameter 0 represents the program name so skip it
    f_string_length sub_location     = 0;
    f_string_length increments       = 0;
    f_string_length string_length    = 0;
    f_array_length parameter_counter = 0;

    f_string_lengths extra_initiator = f_string_lengths_initialize;


    // loop through and read all parameters
    while (location < argc) {
      f_console_identify(argv[location], &result);

      string_length = strnlen(argv[location], f_console_max_size);

      // process the current parameter
      if (result == f_console_short_enable || result == f_console_short_disable) {
        increments   = 1;
        sub_location = 1;
      } else if (result == f_console_long_enable || result == f_console_long_disable) {
        increments   = string_length;
        sub_location = 2;
      } else if (result == f_console_extra_enable || result == f_console_extra_disable) {
        increments   = string_length;
        sub_location = 3;
      } else {
        increments   = 1;
        sub_location = 0;
      }

      // Now handle the normal commands
      if (argv[location][0] == f_console_symbol_enable) {
        while (sub_location < string_length) {
          for (parameter_counter = 0; parameter_counter < total_parameters; parameter_counter++) {
            if (parameters[parameter_counter].type == f_console_type_normal) {
              if (parameters[parameter_counter].symbol_short != 0 && parameters[parameter_counter].symbol_long != 0) {
                if (f_console_is_enable(result, &argv[location][sub_location], parameters[parameter_counter].symbol_short, parameters[parameter_counter].symbol_long, string_length + 1)) {
                  parameters[parameter_counter].result = f_console_result_found;

                  if (parameters[parameter_counter].has_additional) {
                    if (extra_initiator.used >= extra_initiator.size) {
                      f_status allocation_status = f_status_initialize;

                      f_resize_string_lengths(allocation_status, extra_initiator, extra_initiator.size + f_console_default_allocation_step);
                      if (f_macro_test_for_allocation_errors(allocation_status)) {
                        f_delete_string_lengths(status, extra_initiator);
                        return allocation_status;
                      }
                    }

                    extra_initiator.array[extra_initiator.used] = parameter_counter;
                    extra_initiator.used++;
                  }
                }
              }

              if (parameters[parameter_counter].symbol_extra != 0) {
                if (f_console_is_extra_enable(result, &argv[location][sub_location], parameters[parameter_counter].symbol_extra, string_length + 1)) {
                  parameters[parameter_counter].result = f_console_result_found;

                  if (parameters[parameter_counter].has_additional) {
                    if (extra_initiator.used >= extra_initiator.size) {
                      f_status allocation_status = f_status_initialize;

                      f_resize_string_lengths(allocation_status, extra_initiator, extra_initiator.size + f_console_default_allocation_step);
                      if (f_macro_test_for_allocation_errors(allocation_status)) {
                        f_delete_string_lengths(status, extra_initiator);
                        return allocation_status;
                      }
                    }

                    extra_initiator.array[extra_initiator.used] = parameter_counter;
                    extra_initiator.used++;
                  }
                }
              }
            }
          } // for()

          sub_location += increments;
        } // while

      // now handle the inverse commands
      } else if (argv[location][0] == f_console_symbol_disable) {
        while (sub_location < string_length) {
          for (parameter_counter = 0; parameter_counter < total_parameters; parameter_counter++) {
            if (parameters[parameter_counter].type == f_console_type_inverse) {
              if (parameters[parameter_counter].symbol_short != 0 && parameters[parameter_counter].symbol_long != 0) {
                if (f_console_is_disable(result, &argv[location][sub_location], parameters[parameter_counter].symbol_short, parameters[parameter_counter].symbol_long, string_length + 1)) {
                  parameters[parameter_counter].result = f_console_result_found;

                  if (parameters[parameter_counter].has_additional) {
                    if (extra_initiator.used >= extra_initiator.size) {
                      f_status allocation_status = f_status_initialize;

                      f_resize_string_lengths(allocation_status, extra_initiator, extra_initiator.size + f_console_default_allocation_step);
                      if (f_macro_test_for_allocation_errors(allocation_status)) {
                        f_delete_string_lengths(status, extra_initiator);
                        return allocation_status;
                      }
                    }

                    extra_initiator.array[extra_initiator.used] = parameter_counter;
                    extra_initiator.used++;
                  }
                }
              }

              if (parameters[parameter_counter].symbol_extra != 0) {
                if (f_console_is_extra_disable(result, &argv[location][sub_location], parameters[parameter_counter].symbol_extra, string_length + 1)) {
                  parameters[parameter_counter].result = f_console_result_found;

                  if (parameters[parameter_counter].has_additional) {
                    if (extra_initiator.used >= extra_initiator.size) {
                      f_status allocation_status = f_status_initialize;

                      f_resize_string_lengths(allocation_status, extra_initiator, extra_initiator.size + f_console_default_allocation_step);
                      if (f_macro_test_for_allocation_errors(allocation_status)) {
                        f_delete_string_lengths(status, extra_initiator);
                        return allocation_status;
                      }
                    }

                    extra_initiator.array[extra_initiator.used] = parameter_counter;
                    extra_initiator.used++;
                  }
                }
              }
            }
          } // for()

          sub_location += increments;
        } // while
      } else {
        // use found to determine if the remaining parameter should be populated
        found = f_false;

        for (parameter_counter = 0; parameter_counter < total_parameters; parameter_counter++) {
          if (parameters[parameter_counter].type == f_console_type_other) {
            if (parameters[parameter_counter].length > 0 && parameters[parameter_counter].symbol_other != 0) {
              if (strncmp(argv[location], parameters[parameter_counter].symbol_other, parameters[parameter_counter].length + 1) == 0) {
                parameters[parameter_counter].result = f_console_result_found;

                // when "other" is supplied, the extra will be recycled to represent the location of the "other" such that ordering can be determined by the caller
                parameters[parameter_counter].additional = location;

                found = f_true;
                break;
              }
            }
          }
        } // for()

        if (!found) {
          if (extra_initiator.used > 0) {
            parameters[extra_initiator.array[0]].result     = f_console_result_additional;
            parameters[extra_initiator.array[0]].additional = location;

            extra_initiator.used--;

            f_string_length i = 0;

            for (; i < extra_initiator.used; i++) {
              extra_initiator.array[i] = extra_initiator.array[i + 1];
            }
          } else {
            if (remaining->used >= remaining->size) {
              f_status allocation_status = f_status_initialize;

              f_resize_string_lengths(allocation_status, (*remaining), remaining->size + f_console_default_allocation_step);

              if (f_macro_test_for_allocation_errors(allocation_status)) {
                f_delete_string_lengths(status, extra_initiator);
                return allocation_status;
              }
            }

            remaining->array[remaining->used] = location;
            remaining->used++;
          }
        }
      }

      ++location;
    } // while

    if (extra_initiator.used > 0) {
      status = f_no_data;
    } else {
      status = f_none;
    }

    {
      f_status allocation_status = f_status_initialize;
      f_delete_string_lengths(allocation_status, extra_initiator);
    }

    return status;
  }
#endif // _di_fl_process_parameters_

#ifdef __cplusplus
} // extern "C"
#endif
