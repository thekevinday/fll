#include "program.h"
#include "private-program.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_program_parameter_process_context_
  f_status_t fll_program_parameter_process_context(const f_uint16s_t choices, const uint8_t modes[], const bool right, fll_program_data_t * const main) {

    {
      if (choices.used) {
        f_status_t status = F_none;
        f_array_length_t choice = 0;

        if (right) {
          status = f_console_parameter_prioritize_right(main->parameters, choices, &choice);
        }
        else {
          status = f_console_parameter_prioritize_left(main->parameters, choices, &choice);
        }

        if (F_status_is_error(status)) return status;

        if (status == F_data_not) {
          main->context.mode = modes[choices.used - 1];
        }
        else {
          main->context.mode = modes[choice];
        }

        if (main->context.mode == f_color_mode_dark_e || main->context.mode == f_color_mode_light_e) {
          status = f_color_load_context(main->context.mode, &main->context);
          if (F_status_is_error(status)) return status;
        }
      }
      else {
        main->context.mode = f_color_mode_not_e;
      }
    }

    main->message.set = &main->context.set;
    main->output.set = &main->context.set;
    main->error.set = &main->context.set;
    main->warning.set = &main->context.set;

    if (main->context.set.error.before) {
      main->message.context = f_color_set_empty_s;
      main->message.notable = main->context.set.notable;

      main->output.context = f_color_set_empty_s;
      main->output.notable = main->context.set.notable;

      main->error.context = main->context.set.error;
      main->error.notable = main->context.set.notable;

      main->warning.context = main->context.set.warning;
      main->warning.notable = main->context.set.notable;
    }
    else {
      f_color_set_t *sets[] = { &main->message.context, &main->message.notable, &main->output.context, &main->output.notable, &main->error.context, &main->error.notable, &main->warning.context, &main->warning.notable, 0 };

      private_fll_program_parameter_process_empty(&main->context, sets);
    }

    return F_none;
  }
#endif // _di_fll_program_parameter_process_context_

#ifndef _di_fll_program_parameter_process_empty_
  f_status_t fll_program_parameter_process_empty(f_color_context_t * const context, f_color_set_t * const sets[]) {
    #ifndef _di_level_2_parameter_checking_
      if (!context) return F_status_set_error(F_parameter);
      if (!sets) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    private_fll_program_parameter_process_empty(context, sets);

    return F_none;
  }
#endif // _di_fll_program_parameter_process_empty_

#ifndef _di_fll_program_parameter_process_verbosity_
  f_status_t fll_program_parameter_process_verbosity(const f_uint16s_t choices, const uint8_t verbosity[], const bool right, fll_program_data_t * const main) {
    #ifndef _di_level_2_parameter_checking_
      if (!main) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    if (!choices.used) return F_data_not;

    f_array_length_t choice = 0;

    {
      const f_status_t status = right ? f_console_parameter_prioritize_right(main->parameters, choices, &choice) : f_console_parameter_prioritize_left(main->parameters, choices, &choice);

      if (F_status_is_error(status)) return status;

      if (status == F_data_not) {
        choice = choices.used - 1;
      }
    }

    main->message.verbosity = verbosity[choice];
    main->output.verbosity = main->message.verbosity;
    main->error.verbosity = main->message.verbosity;
    main->warning.verbosity = main->message.verbosity;

    return F_none;
  }
#endif // _di_fll_program_parameter_process_verbosity_

#ifndef _di_fll_program_parameter_additional_append_
  f_status_t fll_program_parameter_additional_append(const f_string_static_t * const arguments, const f_array_lengths_t values, f_string_dynamics_t * const destination) {
    #ifndef _di_level_2_parameter_checking_
      if (!arguments) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_none;
    const f_array_length_t start = destination->used;

    for (f_array_length_t i = 0; i < values.used; ++i) {

      if (arguments[values.array[i]].used) {
        status = f_string_dynamics_increase(F_memory_default_allocation_small_d, destination);
        if (F_status_is_error(status)) break;

        destination->array[destination->used].used = 0;

        status = f_string_dynamic_append(arguments[values.array[i]], &destination->array[destination->used]);
        if (F_status_is_error(status)) break;

        if (status == F_data_not) {
          status = F_none;
        }
        else {
          ++destination->used;
        }
      }
    } // for

    if (F_status_is_error(status)) return status;
    if (start == destination->used) return F_data_not;

    return F_none;
  }
#endif // _di_fll_program_parameter_additional_append_

#ifndef _di_fll_program_parameter_additional_mash_
  f_status_t fll_program_parameter_additional_mash(const f_string_static_t glue, const f_string_static_t * const arguments, const f_array_lengths_t values, f_string_dynamic_t * const destination) {
    #ifndef _di_level_2_parameter_checking_
      if (!arguments) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_none;
    const f_array_length_t start = destination->used;

    for (f_array_length_t i = 0; i < values.used; ++i) {

      if (arguments[values.array[i]].used) {
        status = f_string_dynamic_mash(glue, arguments[values.array[i]], destination);
        if (F_status_is_error(status)) break;
      }
    } // for

    if (F_status_is_error(status)) return status;
    if (start == destination->used) return F_data_not;

    return F_none;
  }
#endif // _di_fll_program_parameter_additional_mash_

#ifndef _di_fll_program_parameter_additional_rip_
  f_status_t fll_program_parameter_additional_rip(const f_string_static_t * const arguments, const f_array_lengths_t values, f_string_dynamics_t * const destination) {
    #ifndef _di_level_2_parameter_checking_
      if (!arguments) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_none;
    const f_array_length_t start = destination->used;

    for (f_array_length_t i = 0; i < values.used; ++i) {

      if (arguments[values.array[i]].used) {
        status = f_string_dynamics_increase(F_memory_default_allocation_small_d, destination);
        if (F_status_is_error(status)) break;

        destination->array[destination->used].used = 0;

        status = fl_string_dynamic_rip(arguments[values.array[i]], &destination->array[destination->used]);
        if (F_status_is_error(status)) break;

        if (status == F_data_not) {
          status = F_none;
        }
        else {
          ++destination->used;
        }
      }
    } // for

    if (F_status_is_error(status)) return status;
    if (start == destination->used) return F_data_not;

    return F_none;
  }
#endif // _di_fll_program_parameter_additional_rip_

#ifndef _di_fll_program_parameter_additional_rip_mash_
  f_status_t fll_program_parameter_additional_rip_mash(const f_string_static_t glue, const f_string_static_t * const arguments, const f_array_lengths_t values, f_string_dynamic_t * const destination) {
    #ifndef _di_level_2_parameter_checking_
      if (!arguments) return F_status_set_error(F_parameter);
      if (!destination) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_none;
    const f_array_length_t start = destination->used;
    f_string_dynamic_t ripped = f_string_dynamic_t_initialize;

    for (f_array_length_t i = 0; i < values.used; ++i) {

      if (arguments[values.array[i]].used) {
        ripped.used = 0;

        status = fl_string_dynamic_rip(arguments[values.array[i]], &ripped);
        if (F_status_is_error(status)) break;

        if (ripped.used) {
          status = f_string_dynamic_mash(glue, ripped, destination);
          if (F_status_is_error(status)) break;
        }
      }
    } // for

    f_string_dynamic_resize(0, &ripped);

    if (F_status_is_error(status)) return status;
    if (start == destination->used) return F_data_not;

    return F_none;
  }
#endif // _di_fll_program_parameter_additional_rip_mash_

#ifndef _di_fll_program_standard_set_down_
  f_status_t fll_program_standard_set_down(fll_program_data_t * const main) {
    #ifndef _di_level_2_parameter_checking_
      if (!main) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    // The fclose() calls have undefined behavior when closing an already closed file.
    // Avoid this by explicitly checking every permutation to make sure each descriptor is not a duplicate descriptor.
    // 0x1 = message stream, 0x2 = output stream, 0x4 = error stream, 0x8 = warning stream, 0x10 = debug stream.
    // 0x20 = message descriptor, 0x40 = output descriptor, 0x80 = error descriptor, 0x100 = warning descriptor, 0x200 = debug descriptor.
    uint16_t flag = 0;

    if (main->message.to.stream) {
      if (main->message.to.stream != F_type_error_d && main->message.to.stream != F_type_input_d && main->message.to.stream != F_type_output_d) {
        f_file_stream_flush(main->message.to);

        flag |= 0x1;
      }
    }

    if (main->message.to.id == -1) {
      if (main->message.to.id != F_type_descriptor_error_d && main->message.to.id != F_type_descriptor_input_d && main->message.to.id != F_type_descriptor_output_d) {
        f_file_flush(main->message.to);

        flag |= 0x20;
      }
    }

    if (main->output.to.stream) {
      if (main->output.to.stream != main->message.to.stream) {
        if (main->output.to.stream != F_type_error_d && main->output.to.stream != F_type_input_d && main->output.to.stream != F_type_output_d) {
          f_file_stream_flush(main->output.to);

          flag |= 0x2;
        }
      }
    }

    if (main->error.to.id != -1) {
      if (main->output.to.id != main->message.to.id) {
        if (main->output.to.id != F_type_descriptor_error_d && main->output.to.id != F_type_descriptor_input_d && main->output.to.id != F_type_descriptor_output_d) {
          f_file_flush(main->output.to);

          flag |= 0x40;
        }
      }
    }

    if (main->error.to.stream) {
      if (main->error.to.stream != main->message.to.stream && main->error.to.stream != main->output.to.stream) {
        if (main->error.to.stream != F_type_error_d && main->error.to.stream != F_type_input_d && main->error.to.stream != F_type_output_d) {
          f_file_stream_flush(main->error.to);

          flag |= 0x4;
        }
      }
    }

    if (main->error.to.id != -1) {
      if (main->error.to.id != main->message.to.id && main->error.to.id != main->output.to.id) {
        if (main->error.to.id != F_type_descriptor_error_d && main->error.to.id != F_type_descriptor_input_d && main->error.to.id != F_type_descriptor_output_d) {
          f_file_flush(main->error.to);

          flag |= 0x80;
        }
      }
    }

    if (main->warning.to.stream) {
      if (main->warning.to.stream != main->message.to.stream && main->warning.to.stream != main->output.to.stream && main->warning.to.stream != main->error.to.stream) {
        if (main->warning.to.stream != F_type_error_d && main->warning.to.stream != F_type_input_d && main->warning.to.stream != F_type_output_d) {
          f_file_stream_flush(main->warning.to);

          flag |= 0x8;
        }
      }
    }

    if (main->warning.to.id != -1) {
      if (main->warning.to.id != main->message.to.id && main->warning.to.id != main->output.to.id && main->warning.to.id != main->error.to.id) {
        if (main->warning.to.id != F_type_descriptor_error_d && main->warning.to.id != F_type_descriptor_input_d && main->warning.to.id != F_type_descriptor_output_d) {
          f_file_flush(main->warning.to);

          flag |= 0x100;
        }
      }
    }


    if (main->debug.to.stream) {
      if (main->debug.to.stream != main->message.to.stream && main->debug.to.stream != main->output.to.stream && main->debug.to.stream != main->error.to.stream && main->debug.to.stream != main->warning.to.stream) {
        if (main->debug.to.stream != F_type_error_d && main->debug.to.stream != F_type_input_d && main->debug.to.stream != F_type_output_d) {
          f_file_stream_flush(main->debug.to);

          flag |= 0x10;
        }
      }
    }

    if (main->debug.to.id != -1) {
      if (main->debug.to.id != main->message.to.id && main->debug.to.id != main->output.to.id && main->debug.to.id != main->error.to.id && main->debug.to.id != main->warning.to.id) {
        if (main->debug.to.id != F_type_descriptor_error_d && main->debug.to.id != F_type_descriptor_input_d && main->debug.to.id != F_type_descriptor_output_d) {
          f_file_flush(main->debug.to);

          flag |= 0x200;
        }
      }
    }

    if (flag & 0x1) {
      f_file_stream_close(&main->message.to);
    }

    if (flag & 0x2) {
      f_file_stream_close(&main->output.to);
    }

    if (flag & 0x4) {
      f_file_stream_close(&main->error.to);
    }

    if (flag & 0x8) {
      f_file_stream_close(&main->warning.to);
    }

    if (flag & 0x10) {
      f_file_stream_close(&main->debug.to);
    }

    if (flag & 0x20) {
      f_file_close(&main->message.to);
    }

    if (flag & 0x40) {
      f_file_close(&main->output.to);
    }

    if (flag & 0x80) {
      f_file_close(&main->error.to);
    }

    if (flag & 0x100) {
      f_file_close(&main->warning.to);
    }

    if (flag & 0x200) {
      f_file_close(&main->debug.to);
    }

    // 0x1 = output stream, 0x2 = error stream, 0x4 = input stream.
    // 0x10 = output descriptor, 0x20 = error descriptor, 0x40 = input descriptor.
    flag = 0;

    f_file_t file = f_file_t_initialize;

    if (F_type_output_d) {
      file.stream = F_type_output_d;
      flag |= 0x1;

      f_file_stream_flush(file);
    }
    else {
      if (F_type_descriptor_output_d != -1) {
        file.id = F_type_descriptor_output_d;
        flag |= 0x20;

        f_file_flush(file);
      }
    }

    if (F_type_error_d) {
      file.stream = F_type_error_d;
      flag |= 0x2;

      f_file_stream_flush(file);
    }
    else {
      if (F_type_descriptor_error_d != -1) {
        file.id = F_type_descriptor_output_d;
        flag |= 0x40;

        f_file_flush(file);
      }
    }

    if (F_type_input_d) {
      file.stream = F_type_input_d;
      flag |= 0x4;

      f_file_stream_flush(file);
    }
    else {
      if (F_type_descriptor_input_d != -1) {
        file.id = F_type_descriptor_input_d;
        flag |= 0x80;

        f_file_flush(file);
      }
    }

    if (flag & 0x1) {
      file.stream = F_type_output_d;

      f_file_stream_close(&file);
    }

    if (flag & 0x2) {
      file.stream = F_type_error_d;

      f_file_stream_close(&file);
    }

    if (flag & 0x4) {
      file.stream = F_type_input_d;

      f_file_stream_close(&file);
    }

    if (flag & 0x10) {
      file.id = F_type_descriptor_output_d;

      f_file_close(&file);
    }

    if (flag & 0x20) {
      file.id = F_type_descriptor_error_d;

      f_file_close(&file);
    }

    if (flag & 0x40) {
      file.id = F_type_descriptor_input_d;

      f_file_close(&file);
    }

    const f_status_t status = f_signal_close(&main->signal);
    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fll_program_standard_set_down_

#ifndef _di_fll_program_standard_set_up_
  f_status_t fll_program_standard_set_up(fll_program_data_t * const main) {
    #ifndef _di_level_2_parameter_checking_
      if (!main) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_signal_set_empty(&main->signal.set);
    f_signal_set_add(F_signal_abort, &main->signal.set);
    f_signal_set_add(F_signal_broken_pipe, &main->signal.set);
    f_signal_set_add(F_signal_hangup, &main->signal.set);
    f_signal_set_add(F_signal_interrupt, &main->signal.set);
    f_signal_set_add(F_signal_quit, &main->signal.set);
    f_signal_set_add(F_signal_termination, &main->signal.set);

    f_status_t status = f_signal_mask(SIG_BLOCK, &main->signal.set, 0);
    if (F_status_is_error(status)) return status;

    status = f_signal_open(&main->signal);

    // If there is an error opening a signal descriptor, then do not handle signals.
    if (F_status_is_error(status)) {
      f_signal_mask(SIG_UNBLOCK, &main->signal.set, 0);
      f_signal_close(&main->signal);

      return status;
    }

    // Unblock all other signals.
    memset(&main->signal.set, 0, sizeof(sigset_t));

    f_signal_set_fill(&main->signal.set);
    f_signal_set_delete(F_signal_abort, &main->signal.set);
    f_signal_set_delete(F_signal_broken_pipe, &main->signal.set);
    f_signal_set_delete(F_signal_hangup, &main->signal.set);
    f_signal_set_delete(F_signal_interrupt, &main->signal.set);
    f_signal_set_delete(F_signal_quit, &main->signal.set);
    f_signal_set_delete(F_signal_termination, &main->signal.set);

    status = f_signal_mask(SIG_UNBLOCK, &main->signal.set, 0);
    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fll_program_standard_set_up_

#ifndef _di_fll_program_standard_signal_received_
  uint32_t fll_program_standard_signal_received(fll_program_data_t * const main) {
    #ifndef _di_level_2_parameter_checking_
      if (!main) return 0;
    #endif // _di_level_2_parameter_checking_

    return private_fll_program_standard_signal_received(main);
  }
#endif // _di_fll_program_standard_signal_received_

#ifndef _di_fll_program_standard_signal_handle_
  void fll_program_standard_signal_handle(void * const void_state, void * const internal) {
    #ifndef _di_level_2_parameter_checking_
      if (!void_state) return;
    #endif // _di_level_2_parameter_checking_

    f_state_t * const state = (f_state_t *) void_state;

    if (!state->custom) {
      state->status = F_interrupt_not;

      return;
    }

    fll_program_data_t * const data = (fll_program_data_t *) state->custom;

    data->signal_received = private_fll_program_standard_signal_received(data);

    if (data->signal_received == F_signal_abort || data->signal_received == F_signal_broken_pipe || data->signal_received == F_signal_hangup || data->signal_received == F_signal_interrupt || data->signal_received == F_signal_quit || data->signal_received == F_signal_termination) {
      state->status = F_status_set_error(F_interrupt);
    }
    else {
      state->status = F_interrupt_not;
    }
  }
#endif // _di_fll_program_standard_signal_handle_

#ifdef __cplusplus
} // extern "C"
#endif
