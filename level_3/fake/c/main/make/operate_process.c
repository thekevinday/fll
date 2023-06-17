#include "../fake.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_make_operate_process_
  int fake_make_operate_process(fake_make_data_t * const data_make, const f_string_range_t section_name, fake_state_process_t * const state_process, f_number_unsigneds_t * const section_stack) {

    if (!data_make || !data_make->main || !state_process || !section_stack) return 0;
    if (data_make->main->setting.state.status == F_child) return data_make->main->program.child;

    if (state_process->operation == fake_make_operation_type_break_e) {
      fake_make_operate_process_type_break(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_build_e) {
      fake_make_operate_process_type_build(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_clean_e) {
      fake_make_operate_process_type_clean(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_clone_e) {
      fake_make_operate_process_type_copy(data_make, F_true);
    }
    else if (state_process->operation == fake_make_operation_type_compile_e) {
      return fake_make_operate_process_type_compile(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_copy_e) {
      fake_make_operate_process_type_copy(data_make, F_false);
    }
    else if (state_process->operation == fake_make_operation_type_define_e) {
      fake_make_operate_process_type_define(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_delete_e) {
      fake_make_operate_process_type_deletes(data_make, F_false);
    }
    else if (state_process->operation == fake_make_operation_type_deletes_e) {
      fake_make_operate_process_type_deletes(data_make, F_true);
    }
    else if (state_process->operation == fake_make_operation_type_else_e) {
      // There is nothing to do.
    }
    else if (state_process->operation == fake_make_operation_type_exit_e) {
      fake_make_operate_process_type_exit(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_fail_e) {
      fake_make_operate_process_type_fail(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_group_e) {
      fake_make_operate_process_type_groups(data_make, F_false);
    }
    else if (state_process->operation == fake_make_operation_type_groups_e) {
      fake_make_operate_process_type_groups(data_make, F_true);
    }
    else if (state_process->operation == fake_make_operation_type_if_e || state_process->operation == fake_make_operation_type_and_e || state_process->operation == fake_make_operation_type_or_e) {
      fake_make_operate_process_type_condition(data_make, state_process);
    }
    else if (state_process->operation == fake_make_operation_type_index_e) {
      return fake_make_operate_process_type_index(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_link_e) {
      fake_make_operate_process_type_link(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_mode_e) {
      fake_make_operate_process_type_modes(data_make, F_false);
    }
    else if (state_process->operation == fake_make_operation_type_modes_e) {
      fake_make_operate_process_type_modes(data_make, F_true);
    }
    else if (state_process->operation == fake_make_operation_type_move_e) {
      fake_make_operate_process_type_move(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_operate_e) {
      return fake_make_operate_process_type_operate(data_make, section_stack);
    }
    else if (state_process->operation == fake_make_operation_type_owner_e) {
      fake_make_operate_process_type_owners(data_make, F_false);
    }
    else if (state_process->operation == fake_make_operation_type_owners_e) {
      fake_make_operate_process_type_owners(data_make, F_true);
    }
    else if (state_process->operation == fake_make_operation_type_parameter_e) {
      fake_make_operate_process_type_parameter(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_pop_e) {
      fake_make_operate_process_type_pop(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_print_e) {
      fake_make_operate_process_type_print(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_run_e) {
      fake_make_operate_process_run(data_make, F_false);
    }
    else if (state_process->operation == fake_make_operation_type_shell_e) {
      fake_make_operate_process_run(data_make, F_true);
    }
    else if (state_process->operation == fake_make_operation_type_skeleton_e) {
      fake_make_operate_process_type_skeleton(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_to_e) {
      fake_make_operate_process_type_to(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_top_e) {
      fake_make_operate_process_type_top(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_touch_e) {
      fake_make_operate_process_type_touch(data_make);
    }
    else if (state_process->operation == fake_make_operation_type_write_e) {
      fake_make_operate_process_type_write(data_make);
    }

    return 0;
  }
#endif // _di_fake_make_operate_process_

#ifndef _di_fake_make_operate_process_buffer_escape_
  void fake_make_operate_process_buffer_escape(fake_make_data_t * const data_make, const f_string_static_t source, f_string_dynamic_t * const destination) {

    if (!data_make || !data_make->main || !destination) return;

    if (!source.used) {
      data_make->main->setting.state.status = F_data_not;

      return;
    }

    fake_main_t * const main = data_make->main;

    main->setting.state.status = f_string_dynamic_increase_by(source.used, destination);
    if (F_status_is_error(main->setting.state.status)) return;

    for (f_number_unsigned_t i = 0; i < source.used; ++i) {

      // NULL characters are from delimited characters and must be skipped.
      if (!source.string[i]) continue;

      if (source.string[i] == f_string_ascii_slash_backward_s.string[0]) {

        // A slash by itself at the end of the string is invalid.
        if (++i >= source.used) break;

        main->setting.state.status = f_string_dynamic_increase_by(F_memory_default_allocation_small_d, destination);
        if (F_status_is_error(main->setting.state.status)) return;

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
            f_string_static_t buffer = macro_f_string_static_t_initialize_1(buffer_string, 0, 2);

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

              main->setting.state.status = f_utf_unicode_string_to(buffer.string, buffer.used, &codepoint);

              if (F_status_is_error(main->setting.state.status)) {
                if (!(main->setting.state.status == F_failure || main->setting.state.status == F_utf_not || main->setting.state.status == F_complete_not_utf || main->setting.state.status == F_utf_fragment || main->setting.state.status == F_valid_not)) {
                  break;
                }
              }
              else {

                // Reserve 4-bytes (the max size of a Unicode UTF-8 sequence).
                main->setting.state.status = f_string_dynamic_increase_by(4, destination);
                if (F_status_is_error(main->setting.state.status)) return;

                if (!codepoint) {
                  destination->string[destination->used++] = f_string_null_s.string[0];
                }
                else {
                  {
                    f_string_t address = destination->string + destination->used;

                    main->setting.state.status = f_utf_unicode_from(codepoint, 4, &address);
                  }

                  if (F_status_is_error(main->setting.state.status)) {
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
        main->setting.state.status = f_string_dynamic_increase_by(F_memory_default_allocation_small_d, destination);
        if (F_status_is_error(main->setting.state.status)) return;

        destination->string[destination->used++] = source.string[i];
      }
    } // for

    if (F_status_is_error(main->setting.state.status)) return;

    main->setting.state.status = F_none;
  }
#endif // _di_fake_make_operate_process_buffer_escape_

#ifndef _di_fake_make_operate_process_execute_
  void fake_make_operate_process_execute(fake_make_data_t * const data_make, const f_string_static_t program, const f_string_statics_t arguments, const bool as_shell) {

    if (!data_make || !data_make->main) return;

    if (!program.used && !arguments.used) {
      data_make->main->setting.state.status = F_data_not;

      return;
    }

    fake_main_t * const main = data_make->main;

    if (fll_program_standard_signal_received(&main->program)) {
      fll_program_print_signal_received(&main->program.warning, main->program.signal_received);

      main->setting.state.status = F_status_set_error(F_interrupt);

      return;
    }

    // Reset the environment.
    for (f_number_unsigned_t i = 0; i < data_make->environment.used; ++i) {

      data_make->environment.array[i].name.used = 0;
      data_make->environment.array[i].value.used = 0;
    } // for

    data_make->environment.used = 0;

    if (data_make->setting_build.flag & data_build_setting_flag_has_environment_e) {
      main->setting.state.status = fl_environment_load_names(data_make->setting_build.environment, &data_make->environment);

      if (F_status_is_error(main->setting.state.status)) {
        fake_print_error(&main->program.error, macro_fake_f(fl_environment_load_names));

        return;
      }
    }
    else {
      main->setting.state.status = f_environment_get_all(&data_make->environment);

      if (F_status_is_error(main->setting.state.status)) {
        fake_print_error(&main->program.error, macro_fake_f(f_environment_get_all));

        return;
      }
    }

    fake_make_print_verbose_operate_program(&main->program.message, program, arguments);

    // Child processes should receive all signals, without blocking.
    f_signal_how_t signals = f_signal_how_t_initialize;
    f_signal_set_empty(&signals.block);
    f_signal_set_fill(&signals.block_not);

    fl_execute_parameter_t parameter = macro_fl_execute_parameter_t_initialize_1(as_shell ? 0 : FL_execute_parameter_option_path_d, 0, &data_make->environment, &signals, 0);

    int return_code = 0;

    main->setting.state.status = fll_execute_program(program, arguments, &parameter, 0, (void *) &return_code);

    if (fll_program_standard_signal_received(&main->program)) {
      fll_program_print_signal_received(&main->program.warning, main->program.signal_received);

      main->setting.state.status = F_status_set_error(F_interrupt);

      return;
    }

    if (F_status_is_error(main->setting.state.status)) {
      if (F_status_set_fine(main->setting.state.status) == F_interrupt) return;

      if (F_status_set_fine(main->setting.state.status) == F_file_found_not) {
        fake_make_print_error_program_not_found(&main->program.error, program);
      }
      else if (F_status_set_fine(main->setting.state.status) != F_failure) {
        fake_print_error(&main->program.error, macro_fake_f(fll_execute_program));
      }
    }

    fake_make_operate_process_return(data_make, return_code);

    return;
  }
#endif // _di_fake_make_operate_process_execute_

#ifndef _di_fake_make_operate_process_return_
  void fake_make_operate_process_return(fake_make_data_t * const data_make, const int return_code) {

    if (!data_make || !data_make->main) return;

    fake_main_t * const main = data_make->main;

    const f_status_t status_original = main->setting.state.status;

    data_make->setting_make.parameter.array[0].value.array[0].used = 0;

    if (return_code) {
      f_string_dynamic_t number = f_string_dynamic_t_initialize;

      main->setting.state.status = f_conversion_number_signed_to_string(WEXITSTATUS(return_code), f_conversion_data_base_10_c, &number);

      if (F_status_is_error(main->setting.state.status)) {
        fake_print_error(&main->program.error, macro_fake_f(f_conversion_number_signed_to_string));

        f_string_dynamic_resize(0, &number);

        return;
      }

      main->setting.state.status = f_string_dynamic_append(number, &data_make->setting_make.parameter.array[0].value.array[0]);

      f_string_dynamic_resize(0, &number);

      if (F_status_is_error(main->setting.state.status)) {
        fake_print_error(&main->program.error, macro_fake_f(f_string_dynamic_append));

        return;
      }

      fake_make_print_error_program_failed(&main->program.error, return_code);

      main->setting.state.status = (data_make->setting_make.fail == fake_make_operation_fail_exit_e) ? F_status_set_error(F_failure) : F_failure;

      return;
    }

    if (F_status_is_error(status_original)) {
      main->setting.state.status = f_string_dynamic_append(f_string_ascii_1_s, &data_make->setting_make.parameter.array[0].value.array[0]);
    }
    else {
      main->setting.state.status = f_string_dynamic_append(f_string_ascii_0_s, &data_make->setting_make.parameter.array[0].value.array[0]);
    }

    if (F_status_is_error(main->setting.state.status)) {
      fll_error_print(&data_make->error, F_status_set_fine(main->setting.state.status), macro_fake_f(f_string_dynamic_append), F_true);
    }
    else {
      main->setting.state.status = F_none;
    }
  }
#endif // _di_fake_make_operate_process_return_

#ifndef _di_fake_make_operate_process_run_
  void fake_make_operate_process_run(fake_make_data_t * const data_make, const bool as_shell) {

    if (!data_make || !data_make->main) return;

    if (!data_make->main->cache_arguments.used) {
      data_make->main->setting.state.status = F_data_not;

      return;
    }

    f_string_statics_t args = f_string_statics_t_initialize;

    if (data_make->main->cache_arguments.used > 1) {
      args.array = data_make->main->cache_arguments.array + 1;
      args.used = data_make->main->cache_arguments.used - 1;
      args.size = 0;
    }

    fake_make_operate_process_execute(data_make, data_make->main->cache_arguments.used ? data_make->main->cache_arguments.array[0] : f_string_empty_s, args, as_shell);
  }
#endif // _di_fake_make_operate_process_run_

#ifdef __cplusplus
} // extern "C"
#endif
