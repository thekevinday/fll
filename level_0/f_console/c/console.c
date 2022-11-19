#include "console.h"
#include "private-console.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_console_environment_process_
  f_status_t f_console_environment_process(const f_console_arguments_t arguments, f_string_maps_t * const environment) {
    #ifndef _di_level_0_parameter_checking_
      if (!environment) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_f

    if (!arguments.envp) {
      return F_data_not;
    }

    f_array_length_t total = 0;

    while (arguments.envp[total]) {
      ++total;
    } // while

    if (!total) {
      return F_data_not;
    }

    {
      const f_status_t status = f_string_maps_increase_by(total, environment);
      if (F_status_is_error(status)) return status;
    }

    for (f_array_length_t i = 0; arguments.envp[i]; ++i) {

      for (total = 0; arguments.envp[i][total]; ++total) {
        if (arguments.envp[i][total] == f_string_ascii_equal_s.string[0]) break;
      } // for

      if (total) {
        environment->array[environment->used].name.string = arguments.envp[i];
        environment->array[environment->used].name.used = total;
        environment->array[environment->used].name.size = 0;

        if (arguments.envp[i][++total]) {
          environment->array[environment->used].value.string = arguments.envp[i] + total;
          environment->array[environment->used].value.used = 0;
          environment->array[environment->used].value.size = 0;

          for (; arguments.envp[i][total]; ++total) {
            ++environment->array[environment->used].value.used;
          } // for
        }
        else {
          environment->array[environment->used].value.string = 0;
          environment->array[environment->used].value.used = 0;
          environment->array[environment->used].value.size = 0;
        }

        ++environment->used;
      }
    } // for

    return F_none;
  }
#endif // _di_f_console_environment_process_

#ifndef _di_f_console_identify_
  f_status_t f_console_identify(const f_string_t input, f_console_id_t * const result) {
    #ifndef _di_level_0_parameter_checking_
      if (!result) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_f

    return private_f_console_identify(input, result);
  }
#endif // _di_f_console_identify_

#ifndef _di_f_console_parameter_prioritize_left_
  f_status_t f_console_parameter_prioritize_left(const f_console_parameters_t parameters, const f_console_parameter_ids_t choices, f_console_parameter_id_t * const decision) {
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

      if (parameters.array[choices.id[i]].result == f_console_result_found_e) {
        if (!location || parameters.array[choices.id[i]].location < location) {
          location = parameters.array[choices.id[i]].location;
          location_sub = parameters.array[choices.id[i]].location_sub;
          priority = choices.id[i];
        }
        else if (parameters.array[choices.id[i]].location == location && parameters.array[choices.id[i]].location_sub < location_sub) {
          location_sub = parameters.array[choices.id[i]].location_sub;
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
  f_status_t f_console_parameter_prioritize_right(const f_console_parameters_t parameters, const f_console_parameter_ids_t choices, f_console_parameter_id_t * const decision) {
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

      if (parameters.array[choices.id[i]].result == f_console_result_found_e) {
        if (!location || parameters.array[choices.id[i]].location > location) {
          location = parameters.array[choices.id[i]].location;
          location_sub = parameters.array[choices.id[i]].location_sub;
          priority = choices.id[i];
        }
        else if (parameters.array[choices.id[i]].location == location && parameters.array[choices.id[i]].location_sub > location_sub) {
          location_sub = parameters.array[choices.id[i]].location_sub;
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

#ifndef _di_f_console_parameter_process_
  f_status_t f_console_parameter_process(const f_console_arguments_t arguments, f_console_parameters_t * const parameters) {
    #ifndef _di_level_0_parameter_checking_
      if (!parameters) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    parameters->arguments.used = 0;

    if (!arguments.argc || !arguments.argv || !arguments.argv[0]) {
      return F_data_not;
    }

    f_status_t status = f_string_dynamics_increase_by(arguments.argc, &parameters->arguments);
    if (F_status_is_error(status)) return status;

    // Append the program name parameter.
    parameters->arguments.array[parameters->arguments.used].string = arguments.argv[0];
    parameters->arguments.array[parameters->arguments.used].used = strnlen(arguments.argv[0], F_console_parameter_size_d);
    parameters->arguments.array[parameters->arguments.used++].size = 0;

    f_console_id_t result = 0;
    bool found = F_false;

    // Parameter 0 represents the program name so skip it.
    unsigned long location = 1;

    f_array_length_t sub_location = 0;
    f_array_length_t increment_by = 0;

    f_array_length_t i = 0;
    f_array_length_t values = 0;

    uint8_t console_short = f_console_none_e;
    uint8_t console_long = f_console_none_e;
    uint8_t console_type = f_console_type_normal_e;

    f_array_lengths_t needs_value = f_array_lengths_t_initialize;

    uint8_t width = 0;

    while (location < arguments.argc && arguments.argv[location]) {

      parameters->arguments.array[parameters->arguments.used].string = arguments.argv[location];
      parameters->arguments.array[parameters->arguments.used].used = strnlen(arguments.argv[location], F_console_parameter_size_d);
      parameters->arguments.array[parameters->arguments.used++].size = 0;

      // Additional parameters must always follow what requests them.
      if (needs_value.used > 0) {
        i = needs_value.array[0];

        status = f_array_lengths_increase(F_memory_default_allocation_small_d, &parameters->array[i].values);
        if (F_status_is_error(status)) break;

        parameters->array[i].result = f_console_result_additional_e;
        parameters->array[i].values.array[parameters->array[i].values.used++] = location;

        --needs_value.used;

        // Pop the matched parameter off of the top of the needs_value array.
        for (f_array_length_t i = 0; i < needs_value.used; ++i) {
          needs_value.array[i] = needs_value.array[i + 1];
        } // for

        ++location;

        continue;
      }

      private_f_console_identify(arguments.argv[location], &result);

      // Process the current parameter.
      if (result == f_console_short_enable_e || result == f_console_short_disable_e) {
        increment_by = 1;
        sub_location = 1;
      }
      else if (result == f_console_long_enable_e || result == f_console_long_disable_e) {
        increment_by = parameters->arguments.array[location].used;
        sub_location = 2;
      }
      else {
        increment_by = parameters->arguments.array[location].used;
        sub_location = 0;
      }

      // Handle the normal commands.
      if (result == f_console_short_enable_e || result == f_console_long_enable_e) {
        console_short = f_console_short_enable_e;
        console_long = f_console_long_enable_e;
        console_type = f_console_type_normal_e;
      }
      else if (result == f_console_short_disable_e || result == f_console_long_disable_e) {
        console_short = f_console_short_disable_e;
        console_long = f_console_long_disable_e;
        console_type = f_console_type_inverse_e;
      }
      else {
        console_short = f_console_none_e;
      }

      found = F_false;

      if (console_short != f_console_none_e) {

        // The sub_location is used on a per increment basis (such as 'tar -xcf', the '-' would have an increment of 1, therefore x, c, and f would all be three separate parameters).
        while (sub_location < parameters->arguments.array[location].used) {

          for (i = 0; i < parameters->used; ++i) {

            if (parameters->array[i].type != console_type) continue;

            if (result == console_short) {
              if (!parameters->array[i].symbol_short) continue;

              width = macro_f_utf_byte_width_is(arguments.argv[location][sub_location]);

              if (width > 0) {
                increment_by = width;
              }

              if (arguments.argv[location][sub_location] != *parameters->array[i].symbol_short) continue;

              if (width > 0) {
                f_utf_char_t character_argument_utf = 0;
                f_utf_char_t character_console_utf = 0;

                f_number_unsigned_t width_max = parameters->arguments.array[location].used - sub_location;

                status = f_utf_char_to_character(arguments.argv[location] + sub_location, width_max, &character_argument_utf);
                if (F_status_is_error(status)) break;

                width_max = strlen(parameters->array[i].symbol_short);

                status = f_utf_char_to_character((f_string_t) parameters->array[i].symbol_short, width_max, &character_console_utf);
                if (F_status_is_error(status)) break;

                if (character_argument_utf != character_console_utf) continue;
              }
            }
            else if (result == console_long) {
              if (!parameters->array[i].symbol_long) continue;

              if (strncmp(&arguments.argv[location][sub_location], parameters->array[i].symbol_long, increment_by + 1) != 0) {
                continue;
              }
            }
            else {
              continue;
            }

            status = f_array_lengths_increase(F_memory_default_allocation_small_d, &parameters->array[i].locations);
            if (F_status_is_error(status)) break;

            status = f_array_lengths_increase(F_memory_default_allocation_small_d, &parameters->array[i].locations_sub);
            if (F_status_is_error(status)) break;

            found = F_true;

            parameters->array[i].locations.array[parameters->array[i].locations.used++] = location;

            parameters->array[i].result = f_console_result_found_e;
            parameters->array[i].location = location;
            parameters->array[i].location_sub = 0;

            if (result == console_short) {
              parameters->array[i].location_sub = sub_location;
              parameters->array[i].locations_sub.array[parameters->array[i].locations_sub.used++] = sub_location;
            }
            else {
              parameters->array[i].locations_sub.array[parameters->array[i].locations_sub.used++] = 0;
            }

            if (parameters->array[i].values_total) {
              status = f_array_lengths_increase_by(parameters->array[i].values_total, &needs_value);
              if (F_status_is_error(status)) break;

              for (values = 0; values < parameters->array[i].values_total; ++values) {
                needs_value.array[needs_value.used++] = i;
              } // for
            }

            break;
          } // for

          if (F_status_is_error(status)) break;

          sub_location += increment_by;
        } // while

        if (F_status_is_error(status)) break;
      }
      else {
        for (i = 0; i < parameters->used; ++i) {

          if (parameters->array[i].type != f_console_type_other_e) continue;

          if (!parameters->array[i].symbol_other) continue;

          if (strncmp(arguments.argv[location], parameters->array[i].symbol_other, parameters->arguments.array[location].used + 1) != 0) continue;

          status = f_array_lengths_increase(F_memory_default_allocation_small_d, &parameters->array[i].locations);
          if (F_status_is_error(status)) break;

          status = f_array_lengths_increase(F_memory_default_allocation_small_d, &parameters->array[i].locations_sub);
          if (F_status_is_error(status)) break;

          parameters->array[i].locations.array[parameters->array[i].locations.used++] = location;
          parameters->array[i].locations_sub.array[parameters->array[i].locations_sub.used++] = 0;

          parameters->array[i].result = f_console_result_found_e;
          parameters->array[i].location = location;
          parameters->array[i].location_sub = 0;

          if (parameters->array[i].values_total) {
            if (needs_value.used + parameters->array[i].values_total > needs_value.size) {
              status = f_array_lengths_resize(needs_value.used + parameters->array[i].values_total, &needs_value);
              if (F_status_is_error(status)) break;
            }

            for (values = 0; values < parameters->array[i].values_total; ++values) {
              needs_value.array[needs_value.used++] = i;
            } // for
          }

          found = F_true;

          break;
        } // for

        if (F_status_is_error(status)) break;
      }

      if (!found) {

        // Populate list of remaining parameters->array that are not associated with anything.
        status = f_array_lengths_increase(F_memory_default_allocation_small_d, &parameters->remaining);
        if (F_status_is_error(status)) break;

        parameters->remaining.array[parameters->remaining.used++] = location;
      }

      ++location;
    } // while

    // Make sure the entire parameters arguments array is populated.
    for (; location < arguments.argc && arguments.argv[location]; ++location) {

      parameters->arguments.array[parameters->arguments.used].string = arguments.argv[location];
      parameters->arguments.array[parameters->arguments.used].used = strnlen(arguments.argv[location], F_console_parameter_size_d);
      parameters->arguments.array[parameters->arguments.used++].size = 0;
    } // for

    if (F_status_is_error(status)) {
      f_array_lengths_resize(0, &needs_value);

      return status;
    }

    if (needs_value.used) {
      status = F_complete_not;
    }
    else {
      status = F_none;
    }

    f_array_lengths_resize(0, &needs_value);

    return status;
  }
#endif // _di_f_console_parameter_process_

#ifdef __cplusplus
} // extern "C"
#endif
