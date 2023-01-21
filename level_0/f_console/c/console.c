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
  f_status_t f_console_identify(const f_string_t input, f_console_result_t * const result) {
    #ifndef _di_level_0_parameter_checking_
      if (!result) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_console_identify(input, result);
  }
#endif // _di_f_console_identify_

#ifndef _di_f_console_parameter_prioritize_left_
  f_status_t f_console_parameter_prioritize_left(const f_console_parameters_t parameters, const f_uint16s_t choices, f_array_length_t * const decision) {
    #ifndef _di_level_0_parameter_checking_
      if (!decision) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!choices.used) return F_data_not;
    if (!parameters.used) return F_data_not;

    f_array_length_t location = 0;
    f_array_length_t location_sub = 0;
    f_array_length_t priority = 0;

    for (f_array_length_t i = 0; i < choices.used; ++i) {

      if (choices.array[i] > parameters.used) return F_status_set_error(F_parameter);

      if (parameters.array[choices.array[i]].result & f_console_result_found_e) {
        if (!location || parameters.array[choices.array[i]].location < location) {
          location = parameters.array[choices.array[i]].location;
          location_sub = parameters.array[choices.array[i]].location_sub;
          priority = i;
        }
        else if (parameters.array[choices.array[i]].location == location && parameters.array[choices.array[i]].location_sub < location_sub) {
          location_sub = parameters.array[choices.array[i]].location_sub;
          priority = i;
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
  f_status_t f_console_parameter_prioritize_right(const f_console_parameters_t parameters, const f_uint16s_t choices, f_array_length_t * const decision) {
    #ifndef _di_level_0_parameter_checking_
      if (!decision) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!choices.used) return F_data_not;
    if (!parameters.used) return F_data_not;

    f_array_length_t location = 0;
    f_array_length_t location_sub = 0;
    f_array_length_t priority = 0;

    for (f_array_length_t i = 0; i < choices.used; ++i) {

      if (choices.array[i] > parameters.used) return F_status_set_error(F_parameter);

      if (parameters.array[choices.array[i]].result & f_console_result_found_e) {
        if (!location || parameters.array[choices.array[i]].location > location) {
          location = parameters.array[choices.array[i]].location;
          location_sub = parameters.array[choices.array[i]].location_sub;
          priority = i;
        }
        else if (parameters.array[choices.array[i]].location == location && parameters.array[choices.array[i]].location_sub > location_sub) {
          location_sub = parameters.array[choices.array[i]].location_sub;
          priority = i;
        }
      }
    } // for

    // The first parameter location (argc = 0) is the program name, therefore if the location is 0, then no matches were found.
    if (!location) return F_data_not;

    *decision = priority;

    return F_none;
  }
#endif // _di_f_console_parameter_prioritize_right_

#ifndef _di_f_console_parameter_process_
  f_status_t f_console_parameter_process(const f_console_arguments_t arguments, f_console_parameters_t * const parameters, void * const data) {
    #ifndef _di_level_0_parameter_checking_
      if (!parameters) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    parameters->arguments.used = 0;

    if (!arguments.argc || !arguments.argv || !arguments.argv[0]) return F_data_not;

    f_console_parameter_state_t state = f_console_parameter_state_t_initialize;

    state.status = f_string_dynamics_increase_by(arguments.argc, &parameters->arguments);
    if (F_status_is_error(state.status)) return state.status;

    // Parameter 0 represents the program name so skip it.
    state.location = 1;

    // Append the program name parameter as a static string.
    parameters->arguments.array[parameters->arguments.used].string = arguments.argv[0];
    parameters->arguments.array[parameters->arguments.used].used = strnlen(arguments.argv[0], F_console_parameter_size_d);
    parameters->arguments.array[parameters->arguments.used++].size = 0;

    uint8_t width = 0;
    f_utf_char_t character_utf_argument = 0;
    f_utf_char_t character_utf_symbol = 0;
    f_array_length_t i;
    f_array_length_t values;
    f_number_unsigned_t width_max = 0;

    while (state.location < arguments.argc && arguments.argv[state.location]) {

      parameters->arguments.array[parameters->arguments.used].string = arguments.argv[state.location];
      parameters->arguments.array[parameters->arguments.used].used = strnlen(arguments.argv[state.location], F_console_parameter_size_d);
      parameters->arguments.array[parameters->arguments.used++].size = 0;

      // Additional parameters must always follow what requests them.
      if (state.value_need.used) {
        if (parameters->callback) {
          state.type = f_console_parameter_state_type_value_need_e;

          parameters->callback(arguments, (void * const) parameters, &state, data);

          if (F_status_is_error(state.status)) {
            f_array_lengths_resize(0, &state.value_need);

            return state.status;
          }

          if (state.status == F_break) break;
          if (state.status == F_continue) continue;
        }
        else {
          state.status = F_process;
        }

        if (state.status == F_process) {
          i = state.value_need.array[0];

          state.status = f_array_lengths_increase(F_memory_default_allocation_small_d, &parameters->array[i].values);
          if (F_status_is_error(state.status)) break;

          parameters->array[i].result |= f_console_result_value_e;
          parameters->array[i].values.array[parameters->array[i].values.used++] = state.location;

          --state.value_need.used;

          // Pop the matched parameter off of the top of the state.value_need array.
          for (i = 0; i < state.value_need.used; ++i) {
            state.value_need.array[i] = state.value_need.array[i + 1];
          } // for
        }

        ++state.location;
        state.status = F_none;

        continue;
      }

      if (parameters->callback) {
        state.type = f_console_parameter_state_type_identify_e;

        parameters->callback(arguments, (void * const) parameters, &state, data);

        if (F_status_is_error(state.status)) {
          f_array_lengths_resize(0, &state.value_need);

          return state.status;
        }

        if (state.status == F_break) break;
        if (state.status == F_continue) continue;
      }
      else {
        state.status = F_process;
      }

      if (state.status == F_process) {
        private_f_console_identify(arguments.argv[state.location], &state.result);

        // Process the current parameter.
        if (state.result & f_console_result_short_e) {
          state.increment_by = 1;
          state.location_sub = 1;
        }
        else if (state.result & f_console_result_long_e) {
          state.increment_by = parameters->arguments.array[state.location].used;
          state.location_sub = 2;
        }
        else {
          state.increment_by = parameters->arguments.array[state.location].used;
          state.location_sub = 0;
        }

        state.found = F_false;
      }

      state.status = F_none;

      if (state.result & (f_console_result_short_e | f_console_result_long_e)) {

        // The state.location_sub is used on a per increment basis.
        while (state.location_sub < parameters->arguments.array[state.location].used) {

          for (i = 0; i < parameters->used; ++i) {

            if (parameters->array[i].flag & f_console_flag_disable_e) continue;
            if ((state.result & f_console_result_normal_e) && !(parameters->array[i].flag & f_console_flag_normal_e)) continue;
            if ((state.result & f_console_result_inverse_e) && !(parameters->array[i].flag & f_console_flag_inverse_e)) continue;

            // For sublocation processing of 'tar -xcf', the '-' would have an increment of 1, therefore x, c, and f would all be three separate parameters)
            if (state.result & f_console_result_short_e) {
              if (!parameters->array[i].symbol_short) continue;

              width = macro_f_utf_byte_width_is(arguments.argv[state.location][state.location_sub]);
              if (width) state.increment_by = width;

              if (arguments.argv[state.location][state.location_sub] != *parameters->array[i].symbol_short) continue;

              if (width) {
                character_utf_argument = 0;
                character_utf_symbol = 0;
                width_max = parameters->arguments.array[state.location].used - state.location_sub;

                state.status = f_utf_char_to_character(arguments.argv[state.location] + state.location_sub, width_max, &character_utf_argument);
                if (F_status_is_error(state.status)) break;

                width_max = strlen(parameters->array[i].symbol_short);

                state.status = f_utf_char_to_character((f_string_t) parameters->array[i].symbol_short, width_max, &character_utf_symbol);
                if (F_status_is_error(state.status)) break;

                if (character_utf_argument != character_utf_symbol) continue;
              }
            }
            else if (state.result & f_console_result_long_e) {
              if (!parameters->array[i].symbol_long) continue;
              if (strncmp(&arguments.argv[state.location][state.location_sub], parameters->array[i].symbol_long, state.increment_by + 1)) continue;
            }
            else {
              continue;
            }

            state.status = F_none;

            if (parameters->callback) {
              state.type = f_console_parameter_state_type_match_normal_e;

              parameters->callback(arguments, (void * const) parameters, &state, data);

              if (F_status_is_error(state.status)) {
                f_array_lengths_resize(0, &state.value_need);

                return state.status;
              }

              if (state.status == F_break) break;

              if (state.status == F_continue) {
                if (state.depth) break;

                continue;
              }
            }
            else {
              state.status = F_process;
            }

            if (state.status == F_process) {
              state.status = f_array_lengths_increase(F_memory_default_allocation_small_d, &parameters->array[i].locations);
              if (F_status_is_error(state.status)) break;

              state.status = f_array_lengths_increase(F_memory_default_allocation_small_d, &parameters->array[i].locations_sub);
              if (F_status_is_error(state.status)) break;

              state.found = F_true;

              parameters->array[i].locations.array[parameters->array[i].locations.used++] = state.location;

              parameters->array[i].result = state.result | (parameters->array[i].result & f_console_result_value_e);
              parameters->array[i].location = state.location;
              parameters->array[i].location_sub = 0;

              if (state.result & f_console_result_short_e) {
                parameters->array[i].location_sub = state.location_sub;
                parameters->array[i].locations_sub.array[parameters->array[i].locations_sub.used++] = state.location_sub;
              }
              else {
                parameters->array[i].locations_sub.array[parameters->array[i].locations_sub.used++] = 0;
              }

              if (parameters->array[i].values_total) {
                state.status = f_array_lengths_increase_by(parameters->array[i].values_total, &state.value_need);
                if (F_status_is_error(state.status)) break;

                for (values = 0; values < parameters->array[i].values_total; ++values) {
                  state.value_need.array[state.value_need.used++] = i;
                } // for
              }
            }

            state.status = F_none;

            break;
          } // for

          if (F_status_is_error(state.status)) break;

          if (state.status == F_break || state.status == F_continue) {
            if (state.depth) {
              --state.depth;

              if (state.status == F_break) break;

              continue;
            }
          }

          state.location_sub += state.increment_by;
        } // while

        if (F_status_is_error(state.status)) break;

        if (state.status == F_break || state.status == F_continue) {
          if (state.depth) {
            --state.depth;

            if (state.status == F_break) break;

            continue;
          }
        }

        state.status = F_none;
      }
      else {
        if (parameters->callback) {
          state.type = f_console_parameter_state_type_match_remaining_e;

          parameters->callback(arguments, (void * const) parameters, &state, data);

          if (F_status_is_error(state.status)) {
            f_array_lengths_resize(0, &state.value_need);

            return state.status;
          }

          if (state.status == F_break) break;
          if (state.status == F_continue) continue;
        }
        else {
          state.status = F_process;
        }

        if (state.status == F_process) {
          for (i = 0; i < parameters->used; ++i) {

            if (parameters->array[i].flag & f_console_flag_disable_e) continue;
            if (!(parameters->array[i].flag & f_console_result_alone_e)) continue;
            if (!parameters->array[i].symbol_simple) continue;

            if (strncmp(arguments.argv[state.location], parameters->array[i].symbol_simple, parameters->arguments.array[state.location].used + 1) != 0) continue;

            state.status = f_array_lengths_increase(F_memory_default_allocation_small_d, &parameters->array[i].locations);
            if (F_status_is_error(state.status)) break;

            state.status = f_array_lengths_increase(F_memory_default_allocation_small_d, &parameters->array[i].locations_sub);
            if (F_status_is_error(state.status)) break;

            parameters->array[i].locations.array[parameters->array[i].locations.used++] = state.location;
            parameters->array[i].locations_sub.array[parameters->array[i].locations_sub.used++] = 0;

            parameters->array[i].result = state.result | (parameters->array[i].result & f_console_result_value_e);
            parameters->array[i].location = state.location;
            parameters->array[i].location_sub = 0;

            if (parameters->array[i].values_total) {
              if (state.value_need.used + parameters->array[i].values_total > state.value_need.size) {
                state.status = f_array_lengths_resize(state.value_need.used + parameters->array[i].values_total, &state.value_need);
                if (F_status_is_error(state.status)) break;
              }

              for (values = 0; values < parameters->array[i].values_total; ++values) {
                state.value_need.array[state.value_need.used++] = i;
              } // for
            }

            state.found = F_true;

            break;
          } // for

          if (F_status_is_error(state.status)) break;
        }

        state.status = F_none;
      }

      if (state.found) {
        ++state.location;
      }
      else {
        if (parameters->callback) {
          state.type = f_console_parameter_state_type_match_not_e;

          parameters->callback(arguments, (void * const) parameters, &state, data);

          if (F_status_is_error(state.status)) break;
          if (state.status == F_break) break;
          if (state.status == F_continue) continue;
        }
        else {
          state.status = F_process;
        }

        if (state.status == F_process) {

          // Populate list of remaining parameters->array that are not associated with anything.
          state.status = f_array_lengths_increase(F_memory_default_allocation_small_d, &parameters->remaining);
          if (F_status_is_error(state.status)) break;

          parameters->remaining.array[parameters->remaining.used++] = state.location++;
        }

        state.status = F_none;
      }
    } // while

    if (F_status_is_error_not(state.status)) {
      if (parameters->callback) {
        state.type = f_console_parameter_state_type_wrap_up_e;

        parameters->callback(arguments, (void * const) parameters, &state, data);

        if (F_status_is_error(state.status)) {
          f_array_lengths_resize(0, &state.value_need);

          return state.status;
        }
      }
      else {
        state.status = F_process;
      }

      if (state.status == F_process) {

        // Make sure the entire parameters arguments array is populated.
        for (; state.location < arguments.argc && arguments.argv[state.location]; ++state.location) {

          parameters->arguments.array[parameters->arguments.used].string = arguments.argv[state.location];
          parameters->arguments.array[parameters->arguments.used].used = strnlen(arguments.argv[state.location], F_console_parameter_size_d);
          parameters->arguments.array[parameters->arguments.used++].size = 0;
        } // for

        if (F_status_is_error_not(state.status)) {
          state.status = state.value_need.used ? F_complete_not : F_none;
        }
      }
    }

    f_array_lengths_resize(0, &state.value_need);

    return state.status;
  }
#endif // _di_f_console_parameter_process_

#ifdef __cplusplus
} // extern "C"
#endif
