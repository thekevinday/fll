#include "console.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_console_identify_
  f_status_t f_console_identify(const f_string_t input, f_console_id_t *result) {
    #ifndef _di_level_0_parameter_checking_
      if (!result) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_f

    const f_array_length_t length = strnlen(input, 3);

    if (!length) {
      *result = f_console_none;

      return F_data_not;
    }

    if (input[0] == f_console_symbol_short_enable_s[0]) {
      if (length > 1) {
        if (input[1] == f_console_symbol_short_enable_s[0]) {
          if (length > 2) {
            *result = f_console_long_enable;
          }
          else *result = f_console_empty_long_enable;
        }
        else *result = f_console_short_enable;
      }
      else *result = f_console_empty_short_enable;
    }
    else if (input[0] == f_console_symbol_short_disable_s[0]) {
      if (length > 1) {
        if (input[1] == f_console_symbol_short_disable_s[0]) {
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

    return F_none;
  }
#endif // _di_f_console_identify_

#ifndef _di_f_console_parameter_process_
  f_status_t f_console_parameter_process(const f_console_arguments_t arguments, f_console_parameters_t parameters, f_array_lengths_t *remaining) {
    #ifndef _di_level_0_parameter_checking_
      if (!remaining) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_status_t status = F_none;
    f_console_id_t result = 0;
    bool found = F_false;

    unsigned long location = 1; // Parameter 0 represents the program name so skip it.

    f_array_length_t sub_location = 0;
    f_array_length_t increment_by = 0;
    f_array_length_t argument_length = 0;

    f_array_length_t i = 0;
    f_array_length_t values = 0;

    uint8_t console_short = f_console_none;
    uint8_t console_long = f_console_none;
    uint8_t console_type = f_console_type_normal;

    f_array_lengths_t needs_value = f_array_lengths_t_initialize;

    uint8_t width = 0;

    // loop through and read all parameters.
    while (location < arguments.argc) {

      // Additional parameters must always follow what requests them.
      if (needs_value.used > 0) {
        i = needs_value.array[0];

        macro_f_array_lengths_t_increase(status, f_memory_default_allocation_small, parameters.parameter[i].values)

        if (F_status_is_error(status)) {
          macro_f_array_lengths_t_delete_simple(needs_value);

          return status;
        }

        parameters.parameter[i].result = f_console_result_additional;
        parameters.parameter[i].values.array[parameters.parameter[i].values.used++] = location;

        --needs_value.used;

        // Pop the matched parameter off of the top of the needs_value array.
        for (f_array_length_t i = 0; i < needs_value.used; ++i) {
          needs_value.array[i] = needs_value.array[i + 1];
        } // for

        ++location;
        continue;
      }

      f_console_identify(arguments.argv[location], &result);

      argument_length = strnlen(arguments.argv[location], f_console_parameter_size);

      // process the current parameter.
      if (result == f_console_short_enable || result == f_console_short_disable) {
        increment_by = 1;
        sub_location = 1;
      }
      else if (result == f_console_long_enable || result == f_console_long_disable) {
        increment_by = argument_length;
        sub_location = 2;
      }
      else {
        increment_by = argument_length;
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
        while (sub_location < argument_length) {

          for (i = 0; i < parameters.used; ++i) {

            if (parameters.parameter[i].type != console_type) {
              continue;
            }

            if (result == console_short) {
              if (!parameters.parameter[i].symbol_short) continue;

              width = macro_f_utf_byte_width_is(arguments.argv[location][sub_location]);
              if (width > 0) {
                increment_by = width;
              }

              if (arguments.argv[location][sub_location] != *parameters.parameter[i].symbol_short) continue;

              if (width > 0) {
                f_utf_character_t character_argument_utf = 0;
                f_utf_character_t character_console_utf = 0;

                f_number_unsigned_t width_max = argument_length - sub_location;

                status = f_utf_char_to_character(arguments.argv[location] + sub_location, width_max, &character_argument_utf);

                if (F_status_is_error(status)) {
                  macro_f_array_lengths_t_delete_simple(needs_value);

                  return status;
                }

                width_max = strlen(parameters.parameter[i].symbol_short);

                status = f_utf_char_to_character((f_string_t) parameters.parameter[i].symbol_short, width_max, &character_console_utf);

                if (F_status_is_error(status)) {
                  macro_f_array_lengths_t_delete_simple(needs_value);

                  return status;
                }

                if (character_argument_utf != character_console_utf) {
                  continue;
                }
              }
            }
            else if (result == console_long) {
              if (!parameters.parameter[i].symbol_long) {
                continue;
              }

              if (strncmp(&arguments.argv[location][sub_location], parameters.parameter[i].symbol_long, increment_by + 1) != 0) {
                continue;
              }
            }
            else {
              continue;
            }

            macro_f_array_lengths_t_increase(status, f_memory_default_allocation_small, parameters.parameter[i].locations)

            if (F_status_is_error(status)) {
              macro_f_array_lengths_t_delete_simple(needs_value);

              return status;
            }

            macro_f_array_lengths_t_increase(status, f_memory_default_allocation_small, parameters.parameter[i].locations_sub)

            if (F_status_is_error(status)) {
              macro_f_array_lengths_t_delete_simple(needs_value);

              return status;
            }

            parameters.parameter[i].locations.array[parameters.parameter[i].locations.used++] = location;

            parameters.parameter[i].result = f_console_result_found;
            parameters.parameter[i].location = location;
            parameters.parameter[i].location_sub = 0;

            if (result == console_short) {
              parameters.parameter[i].location_sub = sub_location;
              parameters.parameter[i].locations_sub.array[parameters.parameter[i].locations_sub.used++] = sub_location;
            }
            else {
              parameters.parameter[i].locations_sub.array[parameters.parameter[i].locations_sub.used++] = 0;
            }

            if (parameters.parameter[i].has_values) {
              if (needs_value.used + parameters.parameter[i].has_values > needs_value.size) {
                macro_f_array_lengths_t_resize(status, needs_value, needs_value.used + parameters.parameter[i].has_values);

                if (F_status_is_error(status)) {
                  macro_f_array_lengths_t_delete_simple(needs_value);

                  return status;
                }
              }

              for (values = 0; values < parameters.parameter[i].has_values; ++values) {
                needs_value.array[needs_value.used++] = i;
              } // for
            }

            break;
          } // for

          sub_location += increment_by;
        } // while
      }
      else {
        found = F_false;

        for (i = 0; i < parameters.used; ++i) {

          if (parameters.parameter[i].type != f_console_type_other) continue;

          if (!parameters.parameter[i].symbol_other) continue;

          if (strncmp(arguments.argv[location], parameters.parameter[i].symbol_other, argument_length + 1) != 0) continue;

          macro_f_array_lengths_t_increase(status, f_memory_default_allocation_small, parameters.parameter[i].locations)

          if (F_status_is_error(status)) {
            macro_f_array_lengths_t_delete_simple(needs_value);

            return status;
          }

          macro_f_array_lengths_t_increase(status, f_memory_default_allocation_small, parameters.parameter[i].locations_sub)

          if (F_status_is_error(status)) {
            macro_f_array_lengths_t_delete_simple(needs_value);

            return status;
          }

          parameters.parameter[i].locations.array[parameters.parameter[i].locations.used++] = location;
          parameters.parameter[i].locations_sub.array[parameters.parameter[i].locations_sub.used++] = 0;

          parameters.parameter[i].result = f_console_result_found;
          parameters.parameter[i].location = location;
          parameters.parameter[i].location_sub = 0;

          if (parameters.parameter[i].has_values) {
            if (needs_value.used + parameters.parameter[i].has_values > needs_value.size) {
              macro_f_array_lengths_t_resize(status, needs_value, needs_value.used + parameters.parameter[i].has_values);

              if (F_status_is_error(status)) {
                macro_f_array_lengths_t_delete_simple(needs_value);

                return status;
              }
            }

            for (values = 0; values < parameters.parameter[i].has_values; ++values) {
              needs_value.array[needs_value.used++] = i;
            } // for
          }

          found = F_true;
          break;
        } // for

        if (!found) {

          // populate list of remaining parameters.parameter not associated with anything.
          if (remaining->used == remaining->size) {
            macro_f_memory_structure_increment(status, (*remaining), 1, f_memory_default_allocation_small, macro_f_array_lengths_t_resize, F_array_too_large);
            if (F_status_is_error(status)) {
              macro_f_array_lengths_t_delete_simple(needs_value);
              return status;
            }
          }

          remaining->array[remaining->used++] = location;
        }
      }

      ++location;
    } // while

    if (needs_value.used > 0) {
      status = F_data_not;
    }
    else {
      status = F_none;
    }

    macro_f_array_lengths_t_delete_simple(needs_value);

    return status;
  }
#endif // _di_f_console_parameter_process_

#ifndef _di_f_console_parameter_prioritize_left_
  f_status_t f_console_parameter_prioritize_left(const f_console_parameters_t parameters, const f_console_parameter_ids_t choices, f_console_parameter_id_t *decision) {
    #ifndef _di_level_0_parameter_checking_
      if (!decision) return F_status_set_error(F_parameter);
      if (!choices.id) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!choices.used) {
      return F_data_not;
    }

    if (!parameters.used) {
      return F_data_not;
    }

    f_array_length_t location = 0;
    f_array_length_t location_sub = 0;
    f_console_parameter_id_t priority = 0;

    for (f_array_length_t i = 0; i < choices.used; ++i) {

      if (choices.id[i] > parameters.used) {
        return F_status_set_error(F_parameter);
      }

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
    if (!location) {
      return F_data_not;
    }

    *decision = priority;

    return F_none;
  }
#endif // _di_f_console_parameter_prioritize_left_

#ifndef _di_f_console_parameter_prioritize_right_
  f_status_t f_console_parameter_prioritize_right(const f_console_parameters_t parameters, const f_console_parameter_ids_t choices, f_console_parameter_id_t *decision) {
    #ifndef _di_level_0_parameter_checking_
      if (!decision) return F_status_set_error(F_parameter);
      if (!choices.id) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!choices.used) {
      return F_data_not;
    }

    if (!parameters.used) {
      return F_data_not;
    }

    f_array_length_t location = 0;
    f_array_length_t location_sub = 0;
    f_console_parameter_id_t priority = 0;

    for (f_array_length_t i = 0; i < choices.used; ++i) {

      if (choices.id[i] > parameters.used) {
        return F_status_set_error(F_parameter);
      }

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
    if (!location) {
      return F_data_not;
    }

    *decision = priority;

    return F_none;
  }
#endif // _di_f_console_parameter_prioritize_right_

#ifdef __cplusplus
} // extern "C"
#endif
