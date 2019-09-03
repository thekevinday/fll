#include <level_1/console.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_process_parameters_
  f_return_status fl_process_parameters(const f_array_length argc, const f_string argv[], f_console_parameter parameters[], const f_array_length total_parameters, f_string_lengths *remaining) {
    #ifndef _di_level_1_parameter_checking_
      if (remaining == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = f_none;
    f_console_id result = 0;
    f_bool found = f_false;

    f_array_length location = 1; // Parameter 0 represents the program name so skip it.
    f_string_length sub_location = 0;
    f_string_length increment_by = 0;
    f_string_length string_length = 0;
    f_array_length parameter_counter = 0;

    f_u_short console_short = f_console_none;
    f_u_short console_long = f_console_none;
    f_u_short console_type = f_console_type_normal;

    f_string_lengths needs_additional = f_string_lengths_initialize;

    // loop through and read all parameters
    while (location < argc) {
      f_console_identify(argv[location], &result);

      string_length = strnlen(argv[location], f_console_max_size);

      // process the current parameter
      if (result == f_console_short_enable || result == f_console_short_disable) {
        increment_by = 1;
        sub_location = 1;
      }
      else if (result == f_console_long_enable || result == f_console_long_disable) {
        increment_by = string_length;
        sub_location = 2;
      }
      else {
        increment_by = string_length;
        sub_location = 0;
      }

      // Handle the normal commands.
      if (result == f_console_short_enable || result == f_console_long_enable) {
        console_short = f_console_short_enable;
        console_long = f_console_long_enable;
        console_type = f_console_type_normal;
      }
      else if (result == f_console_short_disable || result == f_console_long_disable) {
        console_short = f_console_short_disable;
        console_long = f_console_long_disable;
        console_type = f_console_type_inverse;
      }
      else {
        console_short = f_console_none;
      }

      // Additional parameters must always follow what requests them.
      if (needs_additional.used > 0) {
        parameter_counter = needs_additional.array[0];

        if (parameters[parameter_counter].additional.used >= parameters[parameter_counter].additional.size) {
          f_status allocation_status = f_none;

          f_macro_string_lengths_resize(allocation_status, parameters[parameter_counter].additional, parameters[parameter_counter].additional.size + f_console_default_allocation_step);

          if (f_status_is_error(allocation_status)) {
            f_macro_string_lengths_delete(status, needs_additional);
            return f_status_set_error(allocation_status);
          }
        }

        parameters[parameter_counter].result = f_console_result_additional;
        parameters[parameter_counter].additional.array[parameters[parameter_counter].additional.used] = location;
        parameters[parameter_counter].additional.used++;

        needs_additional.used--;

        // Pop the matched parameter off of the top of the needs_additional array.
        for (f_string_length i = 0; i < needs_additional.used; i++) {
          needs_additional.array[i] = needs_additional.array[i + 1];
        } // for
      }
      else if (console_short > f_console_none) {
        // The sub_location is used on a per increment basis (such as 'tar -xcf', the '-' would have an increment of 1, therefore x, c, and f would all be three separate parameters).
        while (sub_location < string_length) {
          for (parameter_counter = 0; parameter_counter < total_parameters; parameter_counter++) {
            if (parameters[parameter_counter].type != console_type) {
              continue;
            }

            if (result == console_short) {
              if (parameters[parameter_counter].symbol_short == 0) {
                continue;
              }

              if (strncmp(&argv[location][sub_location], parameters[parameter_counter].symbol_short, increment_by + 1) != 0) {
                continue;
              }
            }
            else if (result == console_long) {
              if (parameters[parameter_counter].symbol_long == 0) {
                continue;
              }

              if (strncmp(&argv[location][sub_location], parameters[parameter_counter].symbol_long, increment_by + 1) != 0) {
                continue;
              }
            }
            else {
              continue;
            }

            parameters[parameter_counter].result = f_console_result_found;
            parameters[parameter_counter].location = location;
            parameters[parameter_counter].location_sub = 0;
            parameters[parameter_counter].total++;

            if (result == console_short) {
              parameters[parameter_counter].location_sub = sub_location;
            }

            if (parameters[parameter_counter].has_additional) {
              if (needs_additional.used + parameters[parameter_counter].has_additional > needs_additional.size) {
                f_status allocation_status = f_none;

                f_macro_string_lengths_resize(allocation_status, needs_additional, needs_additional.used + parameters[parameter_counter].has_additional);

                if (f_status_is_error(allocation_status)) {
                  f_macro_string_lengths_delete(status, needs_additional);
                  return f_status_set_error(allocation_status);
                }
              }

              for (f_array_length additional = 0; additional < parameters[parameter_counter].has_additional; additional++) {
                needs_additional.array[needs_additional.used] = parameter_counter;
                needs_additional.used++;
              } // for
            }

            break;
          } // for

          sub_location += increment_by;
        } // while
      }
      else {
        found = f_false;

        for (parameter_counter = 0; parameter_counter < total_parameters; parameter_counter++) {
          if (parameters[parameter_counter].type != f_console_type_other) {
            continue;
          }

          if (parameters[parameter_counter].symbol_other == 0) {
            continue;
          }

          if (strncmp(argv[location], parameters[parameter_counter].symbol_other, string_length + 1) != 0) {
            continue;
          }

          parameters[parameter_counter].result = f_console_result_found;
          parameters[parameter_counter].location = location;
          parameters[parameter_counter].location_sub = 0;
          parameters[parameter_counter].total++;

          if (parameters[parameter_counter].has_additional) {
            if (needs_additional.used + parameters[parameter_counter].has_additional > needs_additional.size) {
              f_status allocation_status = f_none;

              f_macro_string_lengths_resize(allocation_status, needs_additional, needs_additional.used + parameters[parameter_counter].has_additional);

              if (f_status_is_error(allocation_status)) {
                f_macro_string_lengths_delete(status, needs_additional);
                return f_status_set_error(allocation_status);
              }
            }

            for (f_array_length additional = 0; additional < parameters[parameter_counter].has_additional; additional++) {
              needs_additional.array[needs_additional.used] = parameter_counter;
              needs_additional.used++;
            } // for
          }

          found = f_true;
          break;
        } // for

        if (!found) {
          // populate list of remaining parameters not associated with anything.
          if (remaining->used >= remaining->size) {
            f_status allocation_status = f_none;

            f_macro_string_lengths_resize(allocation_status, (*remaining), remaining->size + f_console_default_allocation_step);

            if (f_status_is_error(allocation_status)) {
              f_macro_string_lengths_delete(status, needs_additional);
              return f_status_set_error(allocation_status);
            }
          }

          remaining->array[remaining->used] = location;
          remaining->used++;
        }
      }

      location++;
    } // while

    if (needs_additional.used > 0) {
      status = f_no_data;
    }
    else {
      status = f_none;
    }

    {
      f_status allocation_status = f_none;
      f_macro_string_lengths_delete(allocation_status, needs_additional);
    }

    return status;
  }
#endif // _di_fl_process_parameters_

#ifdef __cplusplus
} // extern "C"
#endif
