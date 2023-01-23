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

    if (!arguments.envp) return F_data_not;

    f_array_length_t total = 0;

    while (arguments.envp[total]) {
      ++total;
    } // while

    if (!total) return F_data_not;

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

    if (!choices.used) return F_data_not;
    if (!parameters.used) return F_data_not;

    f_array_length_t location = 0;
    f_array_length_t location_sub = 0;
    f_console_parameter_id_t priority = 0;

    for (f_array_length_t i = 0; i < choices.used; ++i) {

      if (choices.id[i] > parameters.used) return F_status_set_error(F_parameter);

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
    if (!location) return F_data_not;

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

    if (!choices.used) return F_data_not;
    if (!parameters.used) return F_data_not;

    f_array_length_t location = 0;
    f_array_length_t location_sub = 0;
    f_console_parameter_id_t priority = 0;

    for (f_array_length_t i = 0; i < choices.used; ++i) {

      if (choices.id[i] > parameters.used) return F_status_set_error(F_parameter);

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

    if (!arguments.argc || !arguments.argv || !arguments.argv[0]) return F_data_not;

    f_status_t status = f_string_dynamics_increase_by(arguments.argc, &parameters->arguments);
    if (F_status_is_error(status)) return status;

    f_array_lengths_t needs = f_array_lengths_t_initialize;

    status = f_array_lengths_increase(F_memory_default_allocation_small_d, &needs);
    if (F_status_is_error(status)) return status;

    // Append the program name parameter.
    parameters->arguments.array[parameters->arguments.used].string = arguments.argv[0];
    parameters->arguments.array[parameters->arguments.used].used = strnlen(arguments.argv[0], F_console_parameter_size_d);
    parameters->arguments.array[parameters->arguments.used++].size = 0;

    f_console_id_t result = f_console_id_t_initialize;

    // Parameter 0 represents the program name so skip it.
    unsigned long location = 1;

    f_array_length_t location_sub = 0;
    f_array_length_t i = 0;
    f_array_length_t j = 0;

    f_utf_char_t utf_argument = 0;
    f_utf_char_t utf_console = 0;

    uint8_t width = 0;
    bool found = F_false;

    while (location < arguments.argc && arguments.argv[location]) {

      parameters->arguments.array[parameters->arguments.used].string = arguments.argv[location];
      parameters->arguments.array[parameters->arguments.used].used = strnlen(arguments.argv[location], F_console_parameter_size_d);
      parameters->arguments.array[parameters->arguments.used++].size = 0;

      // Additional parameters must always follow what requests them.
      if (needs.used) {
        i = needs.array[0];

        parameters->array[i].result = f_console_result_additional_e;
        parameters->array[i].values.array[parameters->array[i].values.used++] = location++;

        --needs.used;

        for (i = 0; i < needs.used; ++i) {
          needs.array[i] = needs.array[i + 1];
        } // for

        continue;
      }

      private_f_console_identify(arguments.argv[location], &result);

      found = F_false;

      if (result == f_console_short_enable_e || result == f_console_short_disable_e) {

        // Perform pre-process.
        for (location_sub = 1; location_sub < parameters->arguments.array[location].used; ++location_sub) {

          found = F_false;

          for (i = 0; i < parameters->used; ++i) {

            if (parameters->array[i].type != (result == f_console_short_enable_e ? f_console_type_normal_e : f_console_type_inverse_e)) continue;
            if (!parameters->array[i].symbol_short) continue;
            if (arguments.argv[location][location_sub] != *parameters->array[i].symbol_short) continue;

            width = macro_f_utf_byte_width_is(arguments.argv[location][location_sub]);

            if (width) {
              utf_argument = 0;
              utf_console = 0;

              status = f_utf_char_to_character(arguments.argv[location] + location_sub, parameters->arguments.array[location].used - location_sub, &utf_argument);
              if (F_status_is_error(status)) break;

              status = f_utf_char_to_character((f_string_t) parameters->array[i].symbol_short, strlen(parameters->array[i].symbol_short), &utf_console);
              if (F_status_is_error(status)) break;

              if (utf_argument != utf_console) continue;
            }

            found = F_true;

            break;
          } // for

          if (F_status_is_error(status)) break;
          if (!found) break;
        } // for

        if (F_status_is_error(status)) break;

        // The entire string references valid parameters.
        if (found) {
          location_sub = 1;
          needs.used = 0;

          status = f_array_lengths_increase_by(parameters->arguments.array[location].used, &needs);
          if (F_status_is_error(status)) break;

          // The location_sub is used on a per-increment basis (such as 'tar -xcf', the '-' would have an increment of 1, therefore x, c, and f would all be three separate parameters).
          while (location_sub < parameters->arguments.array[location].used) {

            width = macro_f_utf_byte_width_is(arguments.argv[location][location_sub]);

            if (width) {
              utf_argument = 0;
              utf_console = 0;

              status = f_utf_char_to_character(arguments.argv[location] + location_sub, parameters->arguments.array[location].used - location_sub, &utf_argument);
              if (F_status_is_error(status)) break;

              status = f_utf_char_to_character((f_string_t) parameters->array[i].symbol_short, strlen(parameters->array[i].symbol_short), &utf_console);
              if (F_status_is_error(status)) break;

              if (utf_argument != utf_console) continue;
            }
            else {
              width = 1;
            }

            for (i = 0; i < parameters->used; ++i) {

              if (parameters->array[i].type != (result == f_console_short_enable_e ? f_console_type_normal_e : f_console_type_inverse_e)) continue;
              if (!parameters->array[i].symbol_short) continue;
              if (arguments.argv[location][location_sub] != *parameters->array[i].symbol_short) continue;

              status = f_array_lengths_increase(F_memory_default_allocation_small_d, &parameters->array[i].locations);
              if (F_status_is_error(status)) break;

              status = f_array_lengths_increase(F_memory_default_allocation_small_d, &parameters->array[i].locations_sub);
              if (F_status_is_error(status)) break;

              if (parameters->array[i].location != location) {
                parameters->array[i].locations.array[parameters->array[i].locations.used++] = location;
              }

              parameters->array[i].result = f_console_result_found_e;
              parameters->array[i].location = location;
              parameters->array[i].location_sub = location_sub;
              parameters->array[i].locations_sub.array[parameters->array[i].locations_sub.used++] = location_sub;

              for (j = 0; j < parameters->array[i].values_total; ++j) {
                needs.array[needs.used++] = i;
              } // for

              status = f_array_lengths_increase_by(needs.used, &parameters->array[i].values);
              if (F_status_is_error(status)) break;

              break;
            } // for

            if (F_status_is_error(status)) break;

            location_sub += width;
          } // while
        }
      }
      else {
        if (result == f_console_long_enable_e || result == f_console_long_disable_e) {
          location_sub = 2;
          needs.used = 0;

          for (i = 0; i < parameters->used; ++i) {

            if (parameters->array[i].type != (result == f_console_long_enable_e ? f_console_type_normal_e : f_console_type_inverse_e)) continue;
            if (!parameters->array[i].symbol_long) continue;
            if (strncmp(&arguments.argv[location][location_sub], parameters->array[i].symbol_long, parameters->arguments.array[location].used + 1)) continue;

            found = F_true;

            break;
          } // for
        }
        else {
          for (i = 0; i < parameters->used; ++i) {

            if (parameters->array[i].type != f_console_type_other_e) continue;
            if (!parameters->array[i].symbol_other) continue;
            if (strncmp(arguments.argv[location], parameters->array[i].symbol_other, parameters->arguments.array[location].used + 1)) continue;

            found = F_true;

            break;
          } // for
        }

        if (found) {
          status = f_array_lengths_increase(F_memory_default_allocation_small_d, &parameters->array[i].locations);
          if (F_status_is_error(status)) break;

          status = f_array_lengths_increase(F_memory_default_allocation_small_d, &parameters->array[i].locations_sub);
          if (F_status_is_error(status)) break;

          parameters->array[i].result = f_console_result_found_e;
          parameters->array[i].location = location;
          parameters->array[i].location_sub = 0;
          parameters->array[i].locations.array[parameters->array[i].locations.used++] = location;
          parameters->array[i].locations_sub.array[parameters->array[i].locations_sub.used++] = 0;

          for (j = 0; j < parameters->array[i].values_total; ++j) {
            needs.array[needs.used++] = i;
          } // for

          status = f_array_lengths_increase_by(needs.used, &parameters->array[i].values);
          if (F_status_is_error(status)) break;
        }
      }

      if (F_status_is_error(status)) break;

      // Add the missed parameter to the remaining array.
      if (!found) {
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

    if (F_status_is_error_not(status)) {
      status = needs.used ? F_complete_not : F_none;
    }

    f_array_lengths_resize(0, &needs);

    return status;
  }
#endif // _di_f_console_parameter_process_

#ifdef __cplusplus
} // extern "C"
#endif
