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

    f_number_unsigned_t total = 0;

    while (arguments.envp[total]) {
      ++total;
    } // while

    if (!total) return F_data_not;

    {
      const f_status_t status = f_string_maps_increase_by(total, environment);
      if (F_status_is_error(status)) return status;
    }

    for (f_number_unsigned_t i = 0; arguments.envp[i]; ++i) {

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

    return F_okay;
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
  f_status_t f_console_parameter_prioritize_left(const f_console_parameters_t parameters, const f_uint16s_t choices, f_number_unsigned_t * const decision) {
    #ifndef _di_level_0_parameter_checking_
      if (!decision) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!choices.used) return F_data_not;
    if (!parameters.used) return F_data_not;

    f_number_unsigned_t location = 0;
    f_number_unsigned_t location_sub = 0;
    f_number_unsigned_t priority = 0;

    for (f_number_unsigned_t i = 0; i < choices.used; ++i) {

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

    return F_okay;
  }
#endif // _di_f_console_parameter_prioritize_left_

#ifndef _di_f_console_parameter_prioritize_right_
  f_status_t f_console_parameter_prioritize_right(const f_console_parameters_t parameters, const f_uint16s_t choices, f_number_unsigned_t * const decision) {
    #ifndef _di_level_0_parameter_checking_
      if (!decision) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!choices.used) return F_data_not;
    if (!parameters.used) return F_data_not;

    f_number_unsigned_t location = 0;
    f_number_unsigned_t location_sub = 0;
    f_number_unsigned_t priority = 0;

    for (f_number_unsigned_t i = 0; i < choices.used; ++i) {

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

    return F_okay;
  }
#endif // _di_f_console_parameter_prioritize_right_

#ifndef _di_f_console_parameter_process_
  void f_console_parameter_process(const f_console_arguments_t arguments, f_console_parameters_t * const parameters, f_state_t * const state, void * const data) {
    #ifndef _di_level_0_parameter_checking_
      if (!state) return;
      if (!parameters) {
        state->status = F_status_set_error(F_parameter);

        return;
      }
    #endif // _di_level_0_parameter_checking_

    parameters->arguments.used = 0;

    if (!arguments.argc || !arguments.argv || !arguments.argv[0]) {
      state->status = F_data_not;

      return;
    }

    f_console_parameter_state_t process = f_console_parameter_state_t_initialize;

    process.state = state;

    state->status = f_memory_array_increase_by(arguments.argc, sizeof(f_string_dynamic_t), (void **) &parameters->arguments.array, &parameters->arguments.used, &parameters->arguments.size);
    if (F_status_is_error(state->status)) return;

    state->status = f_memory_array_increase(state->step_small, sizeof(f_number_unsigned_t), (void **) &process.needs.array, &process.needs.used, &process.needs.size);
    if (F_status_is_error(state->status)) return;

    // Append the program name parameter as a static string.
    parameters->arguments.array[parameters->arguments.used].string = arguments.argv[0];
    parameters->arguments.array[parameters->arguments.used].used = strnlen(arguments.argv[0], F_console_parameter_size_d);
    parameters->arguments.array[parameters->arguments.used++].size = 0;

    // Parameter 0 represents the program name so skip it.
    process.location = 1;

    f_number_unsigned_t i = 0;
    f_number_unsigned_t j = 0;

    f_utf_char_t utf_argument = 0;
    f_utf_char_t utf_console = 0;

    while (process.location < arguments.argc && arguments.argv[process.location]) {

      if (state->interrupt) {
        state->interrupt((void * const) state, 0);
        if (F_status_set_fine(state->status) == F_interrupt) break;
      }

      parameters->arguments.array[parameters->arguments.used].string = arguments.argv[process.location];
      parameters->arguments.array[parameters->arguments.used].used = strnlen(arguments.argv[process.location], F_console_parameter_size_d);
      parameters->arguments.array[parameters->arguments.used++].size = 0;

      // Additional parameters must always follow what requests them.
      if (process.needs.used) {
        if (parameters->callback) {
          process.type = f_console_parameter_state_type_need_e;
          process.at = process.needs.array[0];

          parameters->callback(arguments, (void * const) parameters, &process, data);
          if (F_status_is_error(state->status)) break;
          if (state->status == F_break) break;
          if (state->status == F_continue) continue;
        }
        else {
          state->status = F_process;
        }

        if (state->status == F_process) {
          i = process.needs.array[0];

          parameters->array[i].result |= f_console_result_value_e;
          parameters->array[i].values.array[parameters->array[i].values.used++] = process.location++;
        }

        --process.needs.used;

        for (i = 0; i < process.needs.used; ++i) {
          process.needs.array[i] = process.needs.array[i + 1];
        } // for

        state->status = F_okay;

        continue;
      }

      if (parameters->callback) {
        process.type = f_console_parameter_state_type_identify_e;
        process.at = 0;

        parameters->callback(arguments, (void * const) parameters, &process, data);
        if (F_status_is_error(state->status)) break;
        if (state->status == F_break) break;
        if (state->status == F_continue) continue;
      }
      else {
        state->status = F_process;
      }

      if (state->status == F_process) {
        state->status = private_f_console_identify(arguments.argv[process.location], &process.result);
        if (F_status_is_error(state->status)) break;
      }

      process.found = F_false;
      state->status = F_okay;

      if (process.result & f_console_result_short_e) {

        // Perform pre-process.
        for (process.location_sub = 1; process.location_sub < parameters->arguments.array[process.location].used; ++process.location_sub) {

          process.found = F_false;

          for (i = 0; i < parameters->used; ++i) {

            if (state->interrupt) {
              state->interrupt((void * const) state, 0);
              if (F_status_set_fine(state->status) == F_interrupt) break;
            }

            if (parameters->array[i].flag & f_console_flag_disable_e) continue;
            if ((process.result & f_console_result_normal_e) && !(parameters->array[i].flag & f_console_flag_normal_e)) continue;
            if ((process.result & f_console_result_inverse_e) && !(parameters->array[i].flag & f_console_flag_inverse_e)) continue;
            if (!parameters->array[i].match_short.used) continue;
            if (!parameters->array[i].match_short.string) continue;
            if (arguments.argv[process.location][process.location_sub] != *parameters->array[i].match_short.string) continue;

            process.width = macro_f_utf_byte_width_is(arguments.argv[process.location][process.location_sub]);

            if (parameters->callback) {
              process.type = f_console_parameter_state_type_short_preprocess_e;
              process.at = i;

              parameters->callback(arguments, (void * const) parameters, &process, data);
              if (F_status_is_error(state->status)) break;

              if (state->status == F_break || state->status == F_continue) {
                if (process.depth) {
                  --process.depth;

                  break;
                }

                state->status = F_okay;

                if (state->status == F_break) break;

                continue;
              }
            }
            else {
              state->status = F_process;
            }

            if (state->status == F_process) {
              if (process.width) {
                utf_argument = 0;
                utf_console = 0;

                state->status = f_utf_char_to_character(arguments.argv[process.location] + process.location_sub, parameters->arguments.array[process.location].used - process.location_sub, &utf_argument);
                if (F_status_is_error(state->status)) break;

                state->status = f_utf_char_to_character(parameters->array[i].match_short.string, parameters->array[i].match_short.used, &utf_console);
                if (F_status_is_error(state->status)) break;

                if (utf_argument != utf_console) continue;
              }
            }

            process.found = F_true;

            break;
          } // for

          if (F_status_is_error(state->status)) break;

          if (state->status == F_break || state->status == F_continue) {
            if (process.depth) {
              --process.depth;

              break;
            }

            state->status = F_okay;

            if (state->status == F_break) break;

            continue;
          }

          if (!process.found) break;
        } // for

        if (F_status_is_error(state->status)) break;

        if (state->status == F_break || state->status == F_continue) {
          process.depth = 0;
          state->status = F_okay;

          if (state->status == F_break) break;

          continue;
        }

        // The entire string references valid parameters.
        if (process.found) {
          process.location_sub = 1;
          process.needs.used = 0;

          state->status = f_memory_array_increase_by(parameters->arguments.array[process.location].used, sizeof(f_number_unsigned_t), (void **) &process.needs.array, &process.needs.used, &process.needs.size);
          if (F_status_is_error(state->status)) break;

          // The process.location_sub is used on a per-increment basis (such as 'tar -xcf', the '-' would have an increment of 1, therefore x, c, and f would all be three separate parameters).
          while (process.location_sub < parameters->arguments.array[process.location].used) {

            process.width = macro_f_utf_byte_width_is(arguments.argv[process.location][process.location_sub]);

            if (process.width) {
              utf_argument = 0;
              utf_console = 0;

              state->status = f_utf_char_to_character(arguments.argv[process.location] + process.location_sub, parameters->arguments.array[process.location].used - process.location_sub, &utf_argument);
              if (F_status_is_error(state->status)) break;

              state->status = f_utf_char_to_character(parameters->array[i].match_short.string, parameters->array[i].match_short.used, &utf_console);
              if (F_status_is_error(state->status)) break;

              if (utf_argument != utf_console) continue;
            }
            else {
              process.width = 1;
            }

            for (i = 0; i < parameters->used; ++i) {

              if (state->interrupt) {
                state->interrupt((void * const) state, 0);
                if (F_status_set_fine(state->status) == F_interrupt) break;
              }

              if (parameters->array[i].flag & f_console_flag_disable_e) continue;
              if ((process.result & f_console_result_normal_e) && !(parameters->array[i].flag & f_console_flag_normal_e)) continue;
              if ((process.result & f_console_result_inverse_e) && !(parameters->array[i].flag & f_console_flag_inverse_e)) continue;
              if (!parameters->array[i].match_short.used) continue;
              if (!parameters->array[i].match_short.string) continue;
              if (arguments.argv[process.location][process.location_sub] != *parameters->array[i].match_short.string) continue;

              if (parameters->callback) {
                process.type = f_console_parameter_state_type_short_e;
                process.at = i;

                parameters->callback(arguments, (void * const) parameters, &process, data);
                if (F_status_is_error(state->status)) break;

                if (state->status == F_break || state->status == F_continue) {
                  if (process.depth) {
                    --process.depth;

                    break;
                  }

                  state->status = F_okay;

                  if (state->status == F_break) break;

                  continue;
                }
              }
              else {
                state->status = F_process;
              }

              if (state->status == F_process) {
                state->status = f_memory_array_increase(state->step_small, sizeof(f_number_unsigned_t), (void **) &parameters->array[i].locations.array, &parameters->array[i].locations.used, &parameters->array[i].locations.size);
                if (F_status_is_error(state->status)) break;

                state->status = f_memory_array_increase(state->step_small, sizeof(f_number_unsigned_t), (void **) &parameters->array[i].locations_sub.array, &parameters->array[i].locations_sub.used, &parameters->array[i].locations_sub.size);
                if (F_status_is_error(state->status)) break;

                if (parameters->array[i].location != process.location) {
                  parameters->array[i].locations.array[parameters->array[i].locations.used++] = process.location;
                }

                parameters->array[i].result |= process.result | f_console_result_found_e;
                parameters->array[i].location = process.location;
                parameters->array[i].location_sub = process.location_sub;
                parameters->array[i].locations_sub.array[parameters->array[i].locations_sub.used++] = process.location_sub;

                for (j = 0; j < parameters->array[i].values_total; ++j) {
                  process.needs.array[process.needs.used++] = i;
                } // for

                state->status = f_memory_array_increase_by(process.needs.used, sizeof(f_number_unsigned_t), (void **) &parameters->array[i].values.array, &parameters->array[i].values.used, &parameters->array[i].values.size);
                if (F_status_is_error(state->status)) break;
              }

              state->status = F_okay;

              break;
            } // for

            if (F_status_is_error(state->status)) break;

            if (state->status == F_break || state->status == F_continue) {
              if (process.depth) {
                --process.depth;

                break;
              }

              state->status = F_okay;

              if (state->status == F_break) break;

              continue;
            }

            process.location_sub += process.width;
          } // while

          if (state->status == F_break || state->status == F_continue) {
            process.depth = 0;
            state->status = F_okay;

            if (state->status == F_break) break;

            continue;
          }
        }
      }
      else {
        if (process.result & f_console_result_long_e) {
          process.location_sub = 2;
          process.needs.used = 0;

          for (i = 0; i < parameters->used; ++i) {

            if (state->interrupt) {
              state->interrupt((void * const) state, 0);
              if (F_status_set_fine(state->status) == F_interrupt) break;
            }

            if (parameters->array[i].flag & f_console_flag_disable_e) continue;
            if ((process.result & f_console_result_normal_e) && !(parameters->array[i].flag & f_console_flag_normal_e)) continue;
            if ((process.result & f_console_result_inverse_e) && !(parameters->array[i].flag & f_console_flag_inverse_e)) continue;
            if (!parameters->array[i].match_long.used) continue;
            if (!parameters->array[i].match_long.string) continue;
            if (strncmp(&arguments.argv[process.location][process.location_sub], parameters->array[i].match_long.string, parameters->array[i].match_long.used + 1)) continue;

            if (parameters->callback) {
              process.type = f_console_parameter_state_type_long_e;
              process.at = i;

              parameters->callback(arguments, (void * const) parameters, &process, data);
              if (F_status_is_error(state->status)) break;

              if (state->status == F_break || state->status == F_continue) {
                if (process.depth) {
                  --process.depth;

                  break;
                }

                state->status = F_okay;

                if (state->status == F_break) break;

                continue;
              }
            }
            else {
              state->status = F_process;
            }

            process.found = F_true;

            break;
          } // for
        }
        else {
          for (i = 0; i < parameters->used; ++i) {

            if (state->interrupt) {
              state->interrupt((void * const) state, 0);
              if (F_status_set_fine(state->status) == F_interrupt) break;
            }

            if (parameters->array[i].flag & f_console_flag_disable_e) continue;
            if (!(parameters->array[i].flag & f_console_flag_simple_e)) continue;
            if (!parameters->array[i].match_simple.used && !parameters->array[i].match_simple.string) continue;
            if (strncmp(arguments.argv[process.location], parameters->array[i].match_simple.string, parameters->array[i].match_simple.used + 1)) continue;

            if (parameters->callback) {
              process.type = f_console_parameter_state_type_simple_e;
              process.at = i;

              parameters->callback(arguments, (void * const) parameters, &process, data);
              if (F_status_is_error(state->status)) break;

              if (state->status == F_break || state->status == F_continue) {
                if (process.depth) {
                  --process.depth;

                  break;
                }

                state->status = F_okay;

                if (state->status == F_break) break;

                continue;
              }
            }
            else {
              state->status = F_process;
            }

            process.found = F_true;

            break;
          } // for
        }

        if (F_status_is_error(state->status)) break;

        if (state->status == F_break || state->status == F_continue) {
          process.depth = 0;
          state->status = F_okay;

          if (state->status == F_break) break;

          continue;
        }

        if (state->status == F_process && process.found && i < parameters->used) {
          state->status = f_memory_array_increase(state->step_small, sizeof(f_number_unsigned_t), (void **) &parameters->array[i].locations.array, &parameters->array[i].locations.used, &parameters->array[i].locations.size);
          if (F_status_is_error(state->status)) break;

          state->status = f_memory_array_increase(state->step_small, sizeof(f_number_unsigned_t), (void **) &parameters->array[i].locations_sub.array, &parameters->array[i].locations_sub.used, &parameters->array[i].locations_sub.size);
          if (F_status_is_error(state->status)) break;

          parameters->array[i].result |= process.result | f_console_result_found_e;
          parameters->array[i].location = process.location;
          parameters->array[i].location_sub = 0;
          parameters->array[i].locations.array[parameters->array[i].locations.used++] = process.location;
          parameters->array[i].locations_sub.array[parameters->array[i].locations_sub.used++] = 0;

          for (j = 0; j < parameters->array[i].values_total; ++j) {
            process.needs.array[process.needs.used++] = i;
          } // for

          state->status = f_memory_array_increase_by(process.needs.used, sizeof(f_number_unsigned_t), (void **) &parameters->array[i].values.array, &parameters->array[i].values.used, &parameters->array[i].values.size);
          if (F_status_is_error(state->status)) break;
        }

        state->status = F_okay;
      }

      if (F_status_is_error(state->status)) break;

      // Add the missed parameter to the remaining array.
      if (!process.found) {
        if (parameters->callback) {
          process.type = f_console_parameter_state_type_miss_e;
          process.at = 0;

          parameters->callback(arguments, (void * const) parameters, &process, data);
          if (F_status_is_error(state->status)) break;
          if (state->status == F_break) break;
          if (state->status == F_continue) continue;
        }
        else {
          state->status = F_process;
        }

        if (state->status == F_process) {
          state->status = f_memory_array_increase(state->step_small, sizeof(f_number_unsigned_t), (void **) &parameters->remaining.array, &parameters->remaining.used, &parameters->remaining.size);
          if (F_status_is_error(state->status)) break;

          parameters->remaining.array[parameters->remaining.used++] = process.location;
        }

        state->status = F_okay;
      }

      ++process.location;
    } // while

    // Make sure the entire parameters arguments array is populated.
    if (parameters->callback) {
      process.type = f_console_parameter_state_type_wrap_up_e;
      process.at = 0;

      parameters->callback(arguments, (void * const) parameters, &process, data);
    }
    else {
      state->status = F_process;
    }

    if (state->status == F_process) {
      state->status = F_okay;

      for (; process.location < arguments.argc && arguments.argv[process.location]; ++process.location) {

        if (state->interrupt) {
          state->interrupt((void * const) state, 0);
          if (F_status_set_fine(state->status) == F_interrupt) break;
        }

        parameters->arguments.array[parameters->arguments.used].string = arguments.argv[process.location];
        parameters->arguments.array[parameters->arguments.used].used = strnlen(arguments.argv[process.location], F_console_parameter_size_d);
        parameters->arguments.array[parameters->arguments.used++].size = 0;
      } // for

      if (F_status_is_error_not(state->status)) {
        state->status = process.needs.used ? F_complete_not : F_okay;
      }
    }

    f_memory_array_resize(0, sizeof(f_number_unsigned_t), (void **) &process.needs.array, &process.needs.used, &process.needs.size);
  }
#endif // _di_f_console_parameter_process_

#ifdef __cplusplus
} // extern "C"
#endif
