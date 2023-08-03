#include "program.h"
#include "private-program.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_program_parameter_process_context_
  f_status_t fll_program_parameter_process_context(const f_uint16s_t choices, const uint8_t modes[], const bool right, fll_program_data_t * const main) {
    #ifndef _di_level_2_parameter_checking_
      if (!main) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    return private_fll_program_parameter_process_context(choices, modes, right, main);
  }
#endif // _di_fll_program_parameter_process_context_

#ifndef _di_fll_program_parameter_process_context_standard_
  f_status_t fll_program_parameter_process_context_standard(const bool right, fll_program_data_t * const main) {
    #ifndef _di_level_2_parameter_checking_
      if (!main) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    uint16_t array[3] = { f_console_standard_parameter_no_color_e, f_console_standard_parameter_light_e, f_console_standard_parameter_dark_e };
    const f_uint16s_t choices = macro_f_uint16s_t_initialize_1(array, 0, 3);
    const uint8_t modes[3] = { f_color_mode_not_e, f_color_mode_light_e, f_color_mode_dark_e };

    return private_fll_program_parameter_process_context(choices, modes, right, main);
  }
#endif // _di_fll_program_parameter_process_context_standard_

#ifndef _di_fll_program_parameter_process_empty_
  f_status_t fll_program_parameter_process_empty(f_color_context_t * const context, f_color_set_t * const sets[]) {
    #ifndef _di_level_2_parameter_checking_
      if (!context) return F_status_set_error(F_parameter);
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

    f_number_unsigned_t choice = 0;

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

#ifndef _di_fll_program_parameter_process_verbosity_standard_
  f_status_t fll_program_parameter_process_verbosity_standard(const bool right, fll_program_data_t * const main) {
    #ifndef _di_level_2_parameter_checking_
      if (!main) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    uint16_t array[5] = { f_console_standard_parameter_verbosity_quiet_e, f_console_standard_parameter_verbosity_error_e, f_console_standard_parameter_verbosity_verbose_e, f_console_standard_parameter_verbosity_debug_e, f_console_standard_parameter_verbosity_normal_e };
    const f_uint16s_t choices = macro_f_uint16s_t_initialize_1(array, 0, 5);

    const uint8_t verbosity[5] = { f_console_verbosity_quiet_e, f_console_verbosity_error_e, f_console_verbosity_verbose_e, f_console_verbosity_debug_e, f_console_verbosity_normal_e };


    f_number_unsigned_t choice = 0;

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
#endif // _di_fll_program_parameter_process_verbosity_standard_

#ifndef _di_fll_program_parameter_additional_append_
  f_status_t fll_program_parameter_additional_append(const f_string_static_t * const arguments, const f_number_unsigneds_t values, f_string_dynamics_t * const destination) {
    #ifndef _di_level_2_parameter_checking_
      if (!arguments || !destination) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_none;
    const f_number_unsigned_t start = destination->used;

    for (f_number_unsigned_t i = 0; i < values.used; ++i) {

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
  f_status_t fll_program_parameter_additional_mash(const f_string_static_t glue, const f_string_static_t * const arguments, const f_number_unsigneds_t values, f_string_dynamic_t * const destination) {
    #ifndef _di_level_2_parameter_checking_
      if (!arguments || !destination) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_none;
    const f_number_unsigned_t start = destination->used;

    for (f_number_unsigned_t i = 0; i < values.used; ++i) {

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
  f_status_t fll_program_parameter_additional_rip(const f_string_static_t * const arguments, const f_number_unsigneds_t values, f_string_dynamics_t * const destination) {
    #ifndef _di_level_2_parameter_checking_
      if (!arguments || !destination) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_none;
    const f_number_unsigned_t start = destination->used;

    for (f_number_unsigned_t i = 0; i < values.used; ++i) {

      if (arguments[values.array[i]].used) {
        status = f_string_dynamics_increase(F_memory_default_allocation_small_d, destination);
        if (F_status_is_error(status)) break;

        destination->array[destination->used].used = 0;

        status = f_rip_dynamic(arguments[values.array[i]], &destination->array[destination->used]);
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
  f_status_t fll_program_parameter_additional_rip_mash(const f_string_static_t glue, const f_string_static_t * const arguments, const f_number_unsigneds_t values, f_string_dynamic_t * const destination) {
    #ifndef _di_level_2_parameter_checking_
      if (!arguments || !destination) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_status_t status = F_none;
    const f_number_unsigned_t start = destination->used;
    f_string_dynamic_t ripped = f_string_dynamic_t_initialize;

    for (f_number_unsigned_t i = 0; i < values.used; ++i) {

      if (arguments[values.array[i]].used) {
        ripped.used = 0;

        status = f_rip_dynamic(arguments[values.array[i]], &ripped);
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
  f_status_t fll_program_standard_set_down(fll_program_data_t * const program) {
    #ifndef _di_level_2_parameter_checking_
      if (!program) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    // The fclose() calls have undefined behavior when closing an already closed file.
    // Avoid this by explicitly checking every permutation to make sure each descriptor is not a duplicate descriptor.
    // 0x1 = message stream, 0x2 = output stream, 0x4 = error stream, 0x8 = warning stream, 0x10 = debug stream.
    // 0x20 = message descriptor, 0x40 = output descriptor, 0x80 = error descriptor, 0x100 = warning descriptor, 0x200 = debug descriptor.
    uint16_t flag = 0;

    if (program->message.to.stream) {
      if (program->message.to.stream != F_type_error_d && program->message.to.stream != F_type_input_d && program->message.to.stream != F_type_output_d) {
        f_file_stream_flush(program->message.to);

        flag |= 0x1;
      }
    }

    if (program->message.to.id == -1) {
      if (program->message.to.id != F_type_descriptor_error_d && program->message.to.id != F_type_descriptor_input_d && program->message.to.id != F_type_descriptor_output_d) {
        f_file_flush(program->message.to);

        flag |= 0x20;
      }
    }

    if (program->output.to.stream) {
      if (program->output.to.stream != program->message.to.stream) {
        if (program->output.to.stream != F_type_error_d && program->output.to.stream != F_type_input_d && program->output.to.stream != F_type_output_d) {
          f_file_stream_flush(program->output.to);

          flag |= 0x2;
        }
      }
    }

    if (program->error.to.id != -1) {
      if (program->output.to.id != program->message.to.id) {
        if (program->output.to.id != F_type_descriptor_error_d && program->output.to.id != F_type_descriptor_input_d && program->output.to.id != F_type_descriptor_output_d) {
          f_file_flush(program->output.to);

          flag |= 0x40;
        }
      }
    }

    if (program->error.to.stream) {
      if (program->error.to.stream != program->message.to.stream && program->error.to.stream != program->output.to.stream) {
        if (program->error.to.stream != F_type_error_d && program->error.to.stream != F_type_input_d && program->error.to.stream != F_type_output_d) {
          f_file_stream_flush(program->error.to);

          flag |= 0x4;
        }
      }
    }

    if (program->error.to.id != -1) {
      if (program->error.to.id != program->message.to.id && program->error.to.id != program->output.to.id) {
        if (program->error.to.id != F_type_descriptor_error_d && program->error.to.id != F_type_descriptor_input_d && program->error.to.id != F_type_descriptor_output_d) {
          f_file_flush(program->error.to);

          flag |= 0x80;
        }
      }
    }

    if (program->warning.to.stream) {
      if (program->warning.to.stream != program->message.to.stream && program->warning.to.stream != program->output.to.stream && program->warning.to.stream != program->error.to.stream) {
        if (program->warning.to.stream != F_type_error_d && program->warning.to.stream != F_type_input_d && program->warning.to.stream != F_type_output_d) {
          f_file_stream_flush(program->warning.to);

          flag |= 0x8;
        }
      }
    }

    if (program->warning.to.id != -1) {
      if (program->warning.to.id != program->message.to.id && program->warning.to.id != program->output.to.id && program->warning.to.id != program->error.to.id) {
        if (program->warning.to.id != F_type_descriptor_error_d && program->warning.to.id != F_type_descriptor_input_d && program->warning.to.id != F_type_descriptor_output_d) {
          f_file_flush(program->warning.to);

          flag |= 0x100;
        }
      }
    }


    if (program->debug.to.stream) {
      if (program->debug.to.stream != program->message.to.stream && program->debug.to.stream != program->output.to.stream && program->debug.to.stream != program->error.to.stream && program->debug.to.stream != program->warning.to.stream) {
        if (program->debug.to.stream != F_type_error_d && program->debug.to.stream != F_type_input_d && program->debug.to.stream != F_type_output_d) {
          f_file_stream_flush(program->debug.to);

          flag |= 0x10;
        }
      }
    }

    if (program->debug.to.id != -1) {
      if (program->debug.to.id != program->message.to.id && program->debug.to.id != program->output.to.id && program->debug.to.id != program->error.to.id && program->debug.to.id != program->warning.to.id) {
        if (program->debug.to.id != F_type_descriptor_error_d && program->debug.to.id != F_type_descriptor_input_d && program->debug.to.id != F_type_descriptor_output_d) {
          f_file_flush(program->debug.to);

          flag |= 0x200;
        }
      }
    }

    if (flag & 0x1) {
      f_file_stream_close(&program->message.to);
    }

    if (flag & 0x2) {
      f_file_stream_close(&program->output.to);
    }

    if (flag & 0x4) {
      f_file_stream_close(&program->error.to);
    }

    if (flag & 0x8) {
      f_file_stream_close(&program->warning.to);
    }

    if (flag & 0x10) {
      f_file_stream_close(&program->debug.to);
    }

    if (flag & 0x20) {
      f_file_close(&program->message.to);
    }

    if (flag & 0x40) {
      f_file_close(&program->output.to);
    }

    if (flag & 0x80) {
      f_file_close(&program->error.to);
    }

    if (flag & 0x100) {
      f_file_close(&program->warning.to);
    }

    if (flag & 0x200) {
      f_file_close(&program->debug.to);
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

    const f_status_t status = f_signal_close(&program->signal);
    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fll_program_standard_set_down_

#ifndef _di_fll_program_standard_set_up_
  f_status_t fll_program_standard_set_up(fll_program_data_t * const program) {
    #ifndef _di_level_2_parameter_checking_
      if (!program) return F_status_set_error(F_parameter);
    #endif // _di_level_2_parameter_checking_

    f_signal_set_empty(&program->signal.set);
    f_signal_set_add(F_signal_abort, &program->signal.set);
    f_signal_set_add(F_signal_broken_pipe, &program->signal.set);
    f_signal_set_add(F_signal_hangup, &program->signal.set);
    f_signal_set_add(F_signal_interrupt, &program->signal.set);
    f_signal_set_add(F_signal_quit, &program->signal.set);
    f_signal_set_add(F_signal_termination, &program->signal.set);

    f_status_t status = f_signal_mask(SIG_BLOCK, &program->signal.set, 0);
    if (F_status_is_error(status)) return status;

    status = f_signal_open(&program->signal);

    // If there is an error opening a signal descriptor, then do not handle signals.
    if (F_status_is_error(status)) {
      f_signal_mask(SIG_UNBLOCK, &program->signal.set, 0);
      f_signal_close(&program->signal);

      return status;
    }

    // Unblock all other signals.
    memset(&program->signal.set, 0, sizeof(sigset_t));

    f_signal_set_fill(&program->signal.set);
    f_signal_set_delete(F_signal_abort, &program->signal.set);
    f_signal_set_delete(F_signal_broken_pipe, &program->signal.set);
    f_signal_set_delete(F_signal_hangup, &program->signal.set);
    f_signal_set_delete(F_signal_interrupt, &program->signal.set);
    f_signal_set_delete(F_signal_quit, &program->signal.set);
    f_signal_set_delete(F_signal_termination, &program->signal.set);

    status = f_signal_mask(SIG_UNBLOCK, &program->signal.set, 0);
    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fll_program_standard_set_up_

#ifndef _di_fll_program_standard_signal_received_
  uint32_t fll_program_standard_signal_received(fll_program_data_t * const program) {
    #ifndef _di_level_2_parameter_checking_
      if (!program) return 0;
    #endif // _di_level_2_parameter_checking_

    return private_fll_program_standard_signal_received(program);
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

    fll_program_data_t * const program = (fll_program_data_t *) state->custom;

    program->signal_received = private_fll_program_standard_signal_received(program);

    if (program->signal_received == F_signal_abort || program->signal_received == F_signal_broken_pipe || program->signal_received == F_signal_hangup || program->signal_received == F_signal_interrupt || program->signal_received == F_signal_quit || program->signal_received == F_signal_termination) {
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
