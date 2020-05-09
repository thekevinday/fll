#include <level_0/console.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_console_identify_
  f_return_status f_console_identify(const f_string input, f_console_id *result) {
    #ifndef _di_level_0_parameter_checking_
      if (result == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_f

    const f_string_length length = strnlen(input, 3);

    if (length == 0) {
      *result = f_console_none;
      return f_no_data;
    }

    if (input[0] == f_console_symbol_enable) {
      if (length > 1) {
        if (input[1] == f_console_symbol_enable) {
          if (length > 2) {
            *result = f_console_long_enable;
          }
          else *result = f_console_empty_long_enable;
        }
        else *result = f_console_short_enable;
      }
      else *result = f_console_empty_short_enable;
    }
    else if (input[0] == f_console_symbol_disable) {
      if (length > 1) {
        if (input[1] == f_console_symbol_disable) {
          if (length > 2) {
            *result = f_console_long_disable;
          }
          else *result = f_console_empty_long_disable;
        }
        else *result = f_console_short_disable;
      }
      else *result = f_console_empty_short_disable;
    }
    else *result = f_console_none;

    return f_none;
  }
#endif // _di_f_console_identify_

#ifndef _di_f_console_parameter_process_
  f_return_status f_console_parameter_process(const f_console_arguments arguments, f_console_parameters parameters, f_string_lengths *remaining) {
    #ifndef _di_level_0_parameter_checking_
      if (remaining == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status status = f_none;
    f_console_id result = 0;
    bool found = f_false;

    unsigned long location = 1; // Parameter 0 represents the program name so skip it.
    f_string_length sub_location = 0;
    f_string_length increment_by = 0;
    f_string_length string_length = 0;
    f_array_length i = 0;

    uint8_t console_short = f_console_none;
    uint8_t console_long = f_console_none;
    uint8_t console_type = f_console_type_normal;

    f_string_lengths needs_additional = f_string_lengths_initialize;

    uint8_t width = 0;

    // loop through and read all parameters.
    while (location < arguments.argc) {

      // Additional parameters must always follow what requests them.
      if (needs_additional.used > 0) {
        i = needs_additional.array[0];

        if (parameters.parameter[i].additional.used >= parameters.parameter[i].additional.size) {
          f_macro_string_lengths_resize(status, parameters.parameter[i].additional, parameters.parameter[i].additional.size + f_console_default_allocation_step);

          if (f_status_is_error(status)) {
            f_macro_string_lengths_delete_simple(needs_additional);
            return status;
          }
        }

        parameters.parameter[i].result = f_console_result_additional;
        parameters.parameter[i].additional.array[parameters.parameter[i].additional.used] = location;
        parameters.parameter[i].additional.used++;

        needs_additional.used--;

        // Pop the matched parameter off of the top of the needs_additional array.
        for (f_string_length i = 0; i < needs_additional.used; i++) {
          needs_additional.array[i] = needs_additional.array[i + 1];
        } // for

        location++;
        continue;
      }

      f_console_identify(arguments.argv[location], &result);

      string_length = strnlen(arguments.argv[location], f_console_max_size);

      // process the current parameter.
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

      if (console_short != f_console_none) {
        // The sub_location is used on a per increment basis (such as 'tar -xcf', the '-' would have an increment of 1, therefore x, c, and f would all be three separate parameters).
        while (sub_location < string_length) {
          for (i = 0; i < parameters.used; i++) {
            if (parameters.parameter[i].type != console_type) {
              continue;
            }

            if (result == console_short) {
              if (parameters.parameter[i].symbol_short == 0) continue;

              width = f_macro_utf_byte_width_is(arguments.argv[location][sub_location]);
              if (width > 0) {
                increment_by = width;
              }

              if (arguments.argv[location][sub_location] != *parameters.parameter[i].symbol_short) continue;

              if (width > 0) {
                f_utf_character character_argument_utf = 0;
                f_utf_character character_console_utf = 0;

                f_number_unsigned width_max = string_length - sub_location;

                status = f_utf_char_to_character(arguments.argv[location] + sub_location, width_max, &character_argument_utf);

                if (status != f_none) {
                  f_macro_string_lengths_delete_simple(needs_additional);
                  return status;
                }

                width_max = strlen(parameters.parameter[i].symbol_short);

                status = f_utf_char_to_character((f_string) parameters.parameter[i].symbol_short, width_max, &character_console_utf);

                if (status != f_none) {
                  f_macro_string_lengths_delete_simple(needs_additional);
                  return status;
                }

                if (character_argument_utf != character_console_utf) {
                  continue;
                }
              }
            }
            else if (result == console_long) {
              if (parameters.parameter[i].symbol_long == 0) {
                continue;
              }

              if (strncmp(&arguments.argv[location][sub_location], parameters.parameter[i].symbol_long, increment_by + 1) != 0) {
                continue;
              }
            }
            else {
              continue;
            }

            if (parameters.parameter[i].locations.used >= parameters.parameter[i].locations.size) {
              f_macro_string_lengths_resize(status, parameters.parameter[i].locations, parameters.parameter[i].locations.size + f_console_default_allocation_step);

              if (f_status_is_error(status)) {
                f_macro_string_lengths_delete_simple(needs_additional);
                return status;
              }
            }

            parameters.parameter[i].locations.array[parameters.parameter[i].locations.used] = location;
            parameters.parameter[i].locations.used++;

            parameters.parameter[i].result = f_console_result_found;
            parameters.parameter[i].location = location;
            parameters.parameter[i].location_sub = 0;
            parameters.parameter[i].total++;

            if (result == console_short) {
              parameters.parameter[i].location_sub = sub_location;
            }

            if (parameters.parameter[i].has_additional) {
              if (needs_additional.used + parameters.parameter[i].has_additional > needs_additional.size) {
                f_macro_string_lengths_resize(status, needs_additional, needs_additional.used + parameters.parameter[i].has_additional);

                if (f_status_is_error(status)) {
                  f_macro_string_lengths_delete_simple(needs_additional);
                  return status;
                }
              }

              for (f_array_length additional = 0; additional < parameters.parameter[i].has_additional; additional++) {
                needs_additional.array[needs_additional.used] = i;
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

        for (i = 0; i < parameters.used; i++) {
          if (parameters.parameter[i].type != f_console_type_other) continue;

          if (parameters.parameter[i].symbol_other == 0) continue;

          if (strncmp(arguments.argv[location], parameters.parameter[i].symbol_other, string_length + 1) != 0) continue;

          if (parameters.parameter[i].locations.used >= parameters.parameter[i].locations.size) {
            f_macro_string_lengths_resize(status, parameters.parameter[i].locations, parameters.parameter[i].locations.size + f_console_default_allocation_step);

            if (f_status_is_error(status)) {
              f_macro_string_lengths_delete_simple(needs_additional);
              return status;
            }
          }

          parameters.parameter[i].locations.array[parameters.parameter[i].locations.used] = location;
          parameters.parameter[i].locations.used++;

          parameters.parameter[i].result = f_console_result_found;
          parameters.parameter[i].location = location;
          parameters.parameter[i].location_sub = 0;
          parameters.parameter[i].total++;

          if (parameters.parameter[i].has_additional) {
            if (needs_additional.used + parameters.parameter[i].has_additional > needs_additional.size) {
              f_macro_string_lengths_resize(status, needs_additional, needs_additional.used + parameters.parameter[i].has_additional);

              if (f_status_is_error(status)) {
                f_macro_string_lengths_delete_simple(needs_additional);
                return status;
              }
            }

            for (f_array_length additional = 0; additional < parameters.parameter[i].has_additional; additional++) {
              needs_additional.array[needs_additional.used] = i;
              needs_additional.used++;
            } // for
          }

          found = f_true;
          break;
        } // for

        if (!found) {
          // populate list of remaining parameters.parameter not associated with anything.
          if (remaining->used >= remaining->size) {
            f_macro_string_lengths_resize(status, (*remaining), remaining->size + f_console_default_allocation_step);

            if (f_status_is_error(status)) {
              f_macro_string_lengths_delete_simple(needs_additional);
              return status;
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

    f_macro_string_lengths_delete_simple(needs_additional);

    return status;
  }
#endif // _di_f_console_parameter_process_

#ifndef _di_f_console_parameter_prioritize_left_
  f_return_status f_console_parameter_prioritize_left(const f_console_parameters parameters, const f_console_parameter_ids choices, f_console_parameter_id *decision) {
    #ifndef _di_level_0_parameter_checking_
      if (decision == 0) return f_status_set_error(f_invalid_parameter);
      if (choices.id == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    if (choices.used == 0) return f_no_data;
    if (parameters.used == 0) return f_no_data;

    f_array_length location = 0;
    f_array_length location_sub = 0;
    f_console_parameter_id priority = 0;

    for (f_array_length i = 0; i < choices.used; i++) {
      if (choices.id[i] > parameters.used) return f_status_set_error(f_invalid_parameter);

      if (parameters.parameter[choices.id[i]].result == f_console_result_found) {
        if (parameters.parameter[choices.id[i]].location < location) {
          location = parameters.parameter[choices.id[i]].location;
          location_sub = parameters.parameter[choices.id[i]].location_sub;
          priority = choices.id[i];
        }
        else if (parameters.parameter[choices.id[i]].location == location && parameters.parameter[choices.id[i]].location_sub < location_sub) {
          location_sub = parameters.parameter[choices.id[i]].location_sub;
          priority = choices.id[i];
        }
      }
    } // for

    // The first parameter location (argc = 0) is the program name, therefore if the location is 0, then no matches were found.
    if (location == 0) {
      return f_no_data;
    }

    *decision = priority;

    return f_none;
  }
#endif // _di_f_console_parameter_prioritize_left_

#ifndef _di_f_console_parameter_prioritize_right_
  f_return_status f_console_parameter_prioritize_right(const f_console_parameters parameters, const f_console_parameter_ids choices, f_console_parameter_id *decision) {
    #ifndef _di_level_0_parameter_checking_
      if (decision == 0) return f_status_set_error(f_invalid_parameter);
      if (choices.id == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    if (choices.used == 0) return f_no_data;
    if (parameters.used == 0) return f_no_data;

    f_array_length location = 0;
    f_array_length location_sub = 0;
    f_console_parameter_id priority = 0;

    for (f_array_length i = 0; i < choices.used; i++) {
      if (choices.id[i] > parameters.used) return f_status_set_error(f_invalid_parameter);

      if (parameters.parameter[choices.id[i]].result == f_console_result_found) {
        if (parameters.parameter[choices.id[i]].location > location) {
          location = parameters.parameter[choices.id[i]].location;
          location_sub = parameters.parameter[choices.id[i]].location_sub;
          priority = choices.id[i];
        }
        else if (parameters.parameter[choices.id[i]].location == location && parameters.parameter[choices.id[i]].location_sub > location_sub) {
          location_sub = parameters.parameter[choices.id[i]].location_sub;
          priority = choices.id[i];
        }
      }
    } // for

    // The first parameter location (argc = 0) is the program name, therefore if the location is 0, then no matches were found.
    if (location == 0) {
      return f_no_data;
    }

    *decision = priority;

    return f_none;
  }
#endif // _di_f_console_parameter_prioritize_right_

#ifdef __cplusplus
} // extern "C"
#endif
