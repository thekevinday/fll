#include "fake.h"
#include "private-common.h"
#include "private-fake.h"
#include "private-build.h"
#include "private-clean.h"
#include "private-make-operate.h"
#include "private-make-operate_process.h"
#include "private-make-operate_process_type.h"
#include "private-print.h"
#include "private-skeleton.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_make_operate_process_
  int fake_make_operate_process(fake_make_data_t * const data_make, const f_string_range_t section_name, fake_state_process_t * const state_process, f_array_lengths_t * const section_stack, f_status_t * const status) {

    if (*status == F_child) return data_make->data->main->child;

    if (state_process->operation == fake_make_operation_type_break_e) {
      *status = fake_make_operate_process_type_break(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_build_e) {
      *status = fake_make_operate_process_type_build(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_clean_e) {
      *status = fake_make_operate_process_type_clean(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_clone_e) {
      *status = fake_make_operate_process_type_copy(data_make, F_true);
    }
    else if (state_process->operation == fake_make_operation_type_compile_e) {
      return fake_make_operate_process_type_compile(data_make, status);
    }
    else if (state_process->operation == fake_make_operation_type_copy_e) {
      *status = fake_make_operate_process_type_copy(data_make, F_false);
    }
    else if (state_process->operation == fake_make_operation_type_define_e) {
      *status = fake_make_operate_process_type_define(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_delete_e) {
      *status = fake_make_operate_process_type_deletes(data_make, F_false);
    }
    else if (state_process->operation == fake_make_operation_type_deletes_e) {
      *status = fake_make_operate_process_type_deletes(data_make, F_true);
    }
    else if (state_process->operation == fake_make_operation_type_else_e) {
      // There is nothing to do.
    }
    else if (state_process->operation == fake_make_operation_type_exit_e) {
      *status = fake_make_operate_process_type_exit(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_fail_e) {
      fake_make_operate_process_type_fail(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_group_e) {
      *status = fake_make_operate_process_type_groups(data_make, F_false);
    }
    else if (state_process->operation == fake_make_operation_type_groups_e) {
      *status = fake_make_operate_process_type_groups(data_make, F_true);
    }
    else if (state_process->operation == fake_make_operation_type_if_e || state_process->operation == fake_make_operation_type_and_e || state_process->operation == fake_make_operation_type_or_e) {
      *status = fake_make_operate_process_type_condition(data_make, state_process);
    }
    else if (state_process->operation == fake_make_operation_type_index_e) {
      return fake_make_operate_process_type_index(data_make, status);
    }
    else if (state_process->operation == fake_make_operation_type_link_e) {
      *status = fake_make_operate_process_type_link(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_mode_e) {
      *status = fake_make_operate_process_type_modes(data_make, F_false);
    }
    else if (state_process->operation == fake_make_operation_type_modes_e) {
      *status = fake_make_operate_process_type_modes(data_make, F_true);
    }
    else if (state_process->operation == fake_make_operation_type_move_e) {
      *status = fake_make_operate_process_type_move(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_operate_e) {
      return fake_make_operate_process_type_operate(data_make, section_stack, status);
    }
    else if (state_process->operation == fake_make_operation_type_owner_e) {
      *status = fake_make_operate_process_type_owners(data_make, F_false);
    }
    else if (state_process->operation == fake_make_operation_type_owners_e) {
      *status = fake_make_operate_process_type_owners(data_make, F_true);
    }
    else if (state_process->operation == fake_make_operation_type_parameter_e) {
      *status = fake_make_operate_process_type_parameter(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_pop_e) {
      *status = fake_make_operate_process_type_pop(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_print_e) {
      *status = fake_make_operate_process_type_print(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_run_e) {
      *status = fake_make_operate_process_run(data_make, F_false);
    }
    else if (state_process->operation == fake_make_operation_type_shell_e) {
      *status = fake_make_operate_process_run(data_make, F_true);
    }
    else if (state_process->operation == fake_make_operation_type_skeleton_e) {
      *status = fake_make_operate_process_type_skeleton(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_to_e) {
      *status = fake_make_operate_process_type_to(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_top_e) {
      *status = fake_make_operate_process_type_top(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_touch_e) {
      *status = fake_make_operate_process_type_touch(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_write_e) {
      *status = fake_make_operate_process_type_write(data_make);
    }

    return 0;
  }
#endif // _di_fake_make_operate_process_

#ifndef _di_fake_make_operate_process_buffer_escape_
  f_status_t fake_make_operate_process_buffer_escape(fake_make_data_t * const data_make, const f_string_static_t source, f_string_dynamic_t * const destination) {

    if (!source.used) return F_data_not;

    f_status_t status = f_string_dynamic_increase_by(source.used, destination);
    if (F_status_is_error(status)) return status;

    for (f_array_length_t i = 0; i < source.used; ++i) {

      // NULL characters are from delimited characters and must be skipped.
      if (!source.string[i]) continue;

      if (source.string[i] == f_string_ascii_slash_backward_s.string[0]) {

        // A slash by itself at the end of the string is invalid.
        if (++i >= source.used) break;

        status = f_string_dynamic_increase_by(F_memory_default_allocation_small_d, destination);
        if (F_status_is_error(status)) return status;

        if (source.string[i] == f_string_ascii_slash_backward_s.string[0]) {
          destination->string[destination->used++] = f_string_ascii_slash_backward_s.string[0];
        }
        else if (source.string[i] == f_string_ascii_n_s.string[0]) {
          destination->string[destination->used++] = f_string_ascii_feed_line_s.string[0];
        }
        else if (source.string[i] == f_string_ascii_r_s.string[0]) {
          destination->string[destination->used++] = f_string_ascii_return_carriage_s.string[0];
        }
        else if (source.string[i] == f_string_ascii_t_s.string[0]) {
          destination->string[destination->used++] = f_string_ascii_tab_horizontal_s.string[0];
        }
        else if (source.string[i] == f_string_ascii_v_s.string[0]) {
          destination->string[destination->used++] = f_string_ascii_tab_vertical_s.string[0];
        }
        else if (source.string[i] == f_string_ascii_0_s.string[0]) {
          destination->string[destination->used++] = f_string_null_s.string[0];
        }
        else if (source.string[i] == f_string_ascii_exclamation_s.string[0]) {
          // The "\!" designates a do nothing character.
        }
        else if (source.string[i] == f_string_ascii_U_s.string[0]) {

          // At the end of the string before a \U+XXXX sequence is completed is invalid.
          if (++i >= source.used) break;

          if (source.string[i] == f_string_ascii_plus_s.string[0]) {

            // At the end of the string before a \U+XXXX sequence is completed is invalid.
            if (i + 4 >= source.used) break;

            ++i;

            // The max Unicode sequence length is "U+XXXXXX".
            char buffer_string[9] = { f_string_ascii_U_s.string[0], f_string_ascii_plus_s.string[0], 0, 0, 0, 0, 0, 0, 0 };
            f_string_static_t buffer = macro_f_string_static_t_initialize(buffer_string, 0, 2);

            for (uint8_t j = 2; i < source.used && j < 8; ) {

              if (!isdigit(source.string[i])) {
                if (!(source.string[i] == f_string_ascii_A_s.string[0] ||
                      source.string[i] == f_string_ascii_B_s.string[0] ||
                      source.string[i] == f_string_ascii_C_s.string[0] ||
                      source.string[i] == f_string_ascii_D_s.string[0] ||
                      source.string[i] == f_string_ascii_E_s.string[0] ||
                      source.string[i] == f_string_ascii_F_s.string[0])) {

                  if (!(source.string[i] == f_string_ascii_a_s.string[0] ||
                        source.string[i] == f_string_ascii_b_s.string[0] ||
                        source.string[i] == f_string_ascii_c_s.string[0] ||
                        source.string[i] == f_string_ascii_d_s.string[0] ||
                        source.string[i] == f_string_ascii_e_s.string[0] ||
                        source.string[i] == f_string_ascii_f_s.string[0])) {

                    --i;

                    break;
                  }
                }
              }

              buffer_string[j++] = source.string[i++];
              ++buffer.used;
            } // for

            if (buffer.used > 2) {
              uint32_t codepoint = 0;

              status = f_utf_unicode_string_to(buffer.string, buffer.used, &codepoint);

              if (F_status_is_error(status)) {
                status = F_status_set_fine(status);

                if (!(status == F_failure || status == F_utf_not || status == F_complete_not_utf || status == F_utf_fragment || status == F_valid_not)) {
                  status = F_status_set_error(status);

                  break;
                }
              }
              else {

                // Reserve 4-bytes (the max size of a Unicode UTF-8 sequence).
                status = f_string_dynamic_increase_by(4, destination);
                if (F_status_is_error(status)) return status;

                if (!codepoint) {
                  destination->string[destination->used++] = f_string_null_s.string[0];
                }
                else {
                  {
                    f_string_t address = destination->string + destination->used;

                    status = f_utf_unicode_from(codepoint, 4, &address);
                  }

                  if (F_status_is_error(status)) {
                    destination->string[destination->used] = 0;
                  }
                  else {
                    if (codepoint < 0x80) {
                      destination->used += 1;
                    }
                    else if (codepoint < 0x800) {
                      destination->used += 2;
                    }
                    else if (codepoint < 0x10000) {
                      destination->used += 3;
                    }
                    else {
                      destination->used += 4;
                    }
                  }
                }
              }
            }
          }
          else {

            // No plus found, so only the "\U" is considered invalid.
            // This character is to be printed.
            --i;
          }
        }
      }
      else {
        status = f_string_dynamic_increase_by(F_memory_default_allocation_small_d, destination);
        if (F_status_is_error(status)) return status;

        destination->string[destination->used++] = source.string[i];
      }
    } // for

    if (F_status_is_error(status)) return status;

    return F_none;
  }
#endif // _di_fake_make_operate_process_buffer_escape_

#ifndef _di_fake_make_operate_process_execute_
  f_status_t fake_make_operate_process_execute(fake_make_data_t * const data_make, const f_string_static_t program, const f_string_statics_t arguments, const bool as_shell) {

    if (!program.used && !arguments.used) return F_data_not;

    if (fll_program_standard_signal_received(data_make->main)) {
      fake_print_signal_received(data_make->data);

      return F_status_set_error(F_interrupt);
    }

    f_status_t status = F_none;

    // Reset the environment.
    for (f_array_length_t i = 0; i < data_make->environment.used; ++i) {

      data_make->environment.array[i].name.used = 0;
      data_make->environment.array[i].value.used = 0;
    } // for

    data_make->environment.used = 0;

    if (data_make->setting_build.flag & data_build_setting_flag_has_environment_e) {
      status = fl_environment_load_names(data_make->setting_build.environment, &data_make->environment);

      if (F_status_is_error(status)) {
        fll_error_print(data_make->error, F_status_set_fine(status), "fl_environment_load_names", F_true);

        return status;
      }
    }
    else {
      status = f_environment_get_all(&data_make->environment);

      if (F_status_is_error(status)) {
        fll_error_print(data_make->error, F_status_set_fine(status), "f_environment_get_all", F_true);

        return status;
      }
    }

    if (data_make->main->error.verbosity >= f_console_verbosity_verbose_e) {
      flockfile(data_make->main->output.to.stream);

      f_array_length_t i = 0;

      if (program.used) {
        f_print_dynamic_safely(program, data_make->main->output.to.stream);
      }
      else {
        i = 1;

        f_print_dynamic_safely(arguments.array[0], data_make->main->output.to.stream);
      }

      for (; i < arguments.used; ++i) {

        if (arguments.array[i].used) {
          fll_print_format(" %Q", data_make->main->output.to.stream, arguments.array[i]);
        }
      } // for

      f_print_dynamic_raw(f_string_eol_s, data_make->main->output.to.stream);

      funlockfile(data_make->main->output.to.stream);

      // Flush to stdout before executing command.
      fflush(data_make->main->output.to.stream);
    }

    int return_code = 0;

    // child processes should receive all signals, without blocking.
    f_signal_how_t signals = f_signal_how_t_initialize;
    f_signal_set_empty(&signals.block);
    f_signal_set_fill(&signals.block_not);

    fl_execute_parameter_t parameter = macro_fl_execute_parameter_t_initialize(as_shell ? 0 : FL_execute_parameter_option_path_d, 0, &data_make->environment, &signals, 0);

    status = fll_execute_program(program, arguments, &parameter, 0, (void *) &return_code);

    if (fll_program_standard_signal_received(data_make->main)) {
      fake_print_signal_received(data_make->data);

      return F_status_set_error(F_interrupt);
    }

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_interrupt) return status;

      if (F_status_set_fine(status) == F_file_found_not) {
        if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
          flockfile(data_make->error.to.stream);

          fl_print_format("%r%[%QFailed to find program '%]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context);
          fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, program, data_make->error.notable);
          fl_print_format("%[' for executing.%]%r", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s);

          funlockfile(data_make->error.to.stream);
        }
      }
      else if (F_status_set_fine(status) != F_failure) {
        fll_error_print(data_make->error, F_status_set_fine(status), "fll_execute_program", F_true);
      }
    }

    return fake_make_operate_process_return(data_make, return_code, status);
  }
#endif // _di_fake_make_operate_process_execute_

#ifndef _di_fake_make_operate_process_return_
  f_status_t fake_make_operate_process_return(fake_make_data_t * const data_make, const int return_code, const f_status_t status) {

    f_status_t result = F_none;

    data_make->setting_make.parameter.array[0].value.array[0].used = 0;

    if (return_code) {
      f_string_dynamic_t number = f_string_dynamic_t_initialize;

      result = f_conversion_number_signed_to_string(WEXITSTATUS(return_code), f_conversion_data_base_10_c, &number);

      if (F_status_is_error(result)) {
        fll_error_print(data_make->error, F_status_set_fine(result), "f_conversion_number_signed_to_string", F_true);

        f_string_dynamic_resize(0, &number);

        return result;
      }

      result = f_string_dynamic_append(number, &data_make->setting_make.parameter.array[0].value.array[0]);

      f_string_dynamic_resize(0, &number);

      if (F_status_is_error(result)) {
        fll_error_print(data_make->error, F_status_set_fine(result), "f_string_dynamic_append", F_true);

        return result;
      }

      if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
        flockfile(data_make->error.to.stream);

        fl_print_format("%r%[%QFailed with return code %]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context);
        fl_print_format("%[%i%]", data_make->error.to.stream, data_make->error.notable, return_code, data_make->error.notable);
        fl_print_format("%[.%]%r", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s);

        funlockfile(data_make->error.to.stream);
      }

      return data_make->setting_make.fail == fake_make_operation_fail_type_exit_e ? F_status_set_error(F_failure) : F_failure;
    }

    if (F_status_is_error(status)) {
      result = f_string_dynamic_append(f_string_ascii_1_s, &data_make->setting_make.parameter.array[0].value.array[0]);
    }
    else {
      result = f_string_dynamic_append(f_string_ascii_0_s, &data_make->setting_make.parameter.array[0].value.array[0]);
    }

    if (F_status_is_error(result)) {
      fll_error_print(data_make->error, F_status_set_fine(result), "f_string_dynamic_append", F_true);
    }
    else {
      result = F_none;
    }

    return result;
  }
#endif // _di_fake_make_operate_process_return_

#ifndef _di_fake_make_operate_process_run_
  f_status_t fake_make_operate_process_run(fake_make_data_t * const data_make, const bool as_shell) {

    f_string_statics_t args = f_string_statics_t_initialize;

    if (data_make->cache_arguments.used > 1) {
      args.array = data_make->cache_arguments.array + 1;
      args.used = data_make->cache_arguments.used - 1;
      args.size = 0;
    }
    else if (!data_make->cache_arguments.used) {
      return F_data_not;
    }

    return fake_make_operate_process_execute(data_make, data_make->cache_arguments.used ? data_make->cache_arguments.array[0] : f_string_empty_s, args, as_shell);
  }
#endif // _di_fake_make_operate_process_run_

#ifdef __cplusplus
} // extern "C"
#endif
