#include "fake.h"
#include "private-common.h"
#include "private-fake.h"
#include "private-build.h"
#include "private-clean.h"
#include "private-make.h"
#include "private-make-operate.h"
#include "private-make-operate_process.h"
#include "private-make-operate_process_type.h"
#include "private-print.h"
#include "private-skeleton.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fake_make_operate_process_
  int fake_make_operate_process(fake_make_data_t * const data_make, const f_string_range_t section_name, const f_string_dynamics_t arguments, const bool success, fake_state_process_t * const state_process, f_array_lengths_t * const section_stack, f_status_t * const status) {

    if (*status == F_child) return data_make->main->child;

    if (state_process->block) {
      if (state_process->block == fake_state_process_block_if_e) {
        if (state_process->operation == fake_make_operation_type_or_e) {

          // For cases of "or", if the previous condition is true, then don't bother because "true || X" is always true.
          if (state_process->block_result == fake_condition_result_true_e) {
            state_process->condition_result = state_process->block_result;

            return 0;
          }
        }
        else {

          // For all other cases, if the previous condition is false, then it is always false because "false && X" is always false.
          if (state_process->block_result == fake_condition_result_false_e) {
            state_process->condition_result = state_process->block_result;

            return 0;
          }
        }
      }
      else if (state_process->block == fake_state_process_block_if_skip_e) {
        if (!(state_process->operation == fake_make_operation_type_and_e || state_process->operation == fake_make_operation_type_or_e)) {
          state_process->condition_result = state_process->block_result;

          return 0;
        }
      }
      else if (state_process->block == fake_state_process_block_else_e) {
        if (state_process->operation != fake_make_operation_type_if_e) {
          if (state_process->block_result == fake_condition_result_false_e) {
            state_process->condition_result = state_process->block_result;

            return 0;
          }
        }
      }
    }

    if (state_process->operation == fake_make_operation_type_index_e) {
      const f_status_t result = fake_execute(data_make->main, data_make->environment, data_make->setting_build.build_indexer, arguments, status);

      if (F_status_is_error(*status)) {
        fll_error_print(data_make->error, F_status_set_fine(*status), "fake_execute", F_true);
      }

      if (*status == F_child) {
        return result;
      }

      *status = fake_make_operate_process_return(data_make, result);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_break_e) {
      if (!arguments.used || fl_string_dynamic_compare(fake_make_operation_argument_success_s, arguments.array[0]) == F_equal_to) {
        *status = F_signal_abort;
      }
      else if (fl_string_dynamic_compare(fake_make_operation_argument_failure_s, arguments.array[0]) == F_equal_to) {
        *status = F_status_set_error(F_signal_abort);
      }
      else {
        return 0;
      }

      if (data_make->main->error.verbosity == f_console_verbosity_verbose_e) {
        flockfile(data_make->main->output.to.stream);

        fl_print_format("%rBreaking as '", data_make->main->output.to.stream, f_string_eol_s);
        fl_print_format("%[%Q%]", data_make->main->output.to.stream, data_make->main->context.set.notable, arguments.used ? arguments.array[0] : fake_make_operation_argument_success_s, data_make->main->context.set.notable);
        fl_print_format("'.%r", data_make->main->output.to.stream, f_string_eol_s);

        funlockfile(data_make->main->output.to.stream);
      }

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_build_e) {
      *status = fake_build_operate(data_make->main, arguments.used ? arguments.array[0] : f_string_empty_s);

      if (F_status_set_fine(*status) == F_interrupt) {
        return 0;
      }

      *status = fake_make_operate_process_return(data_make, F_status_is_error(*status) ? 1 : 0);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_clean_e) {
      *status = fake_clean_operate(data_make->main);

      if (F_status_set_fine(*status) == F_interrupt) {
        return 0;
      }

      *status = fake_make_operate_process_return(data_make, F_status_is_error(*status) ? 1 : 0);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_clone_e) {
      *status = fake_make_operate_process_type_copy(data_make, arguments, F_true);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_compile_e) {
      const int result = fake_execute(data_make->main, data_make->environment, data_make->setting_build.build_compiler, arguments, status);

      if (F_status_is_error(*status)) {
        fll_error_print(data_make->error, F_status_set_fine(*status), "fake_execute", F_true);
      }

      if (*status == F_child) {
        return result;
      }

      *status = fake_make_operate_process_return(data_make, result);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_copy_e) {
      *status = fake_make_operate_process_type_copy(data_make, arguments, F_false);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_define_e) {

      if (arguments.used > 1) {
        *status = f_environment_set(arguments.array[0], arguments.array[1], F_true);
      }
      else {
        *status = f_environment_set(arguments.array[0], f_string_empty_s, F_true);
      }

      if (F_status_is_error(*status)) {
        fll_error_print(data_make->error, F_status_set_fine(*status), "f_environment_set", F_true);
      }
      else if (data_make->main->error.verbosity == f_console_verbosity_verbose_e) {
        fll_print_format("%rDefined environment variable '%[%Q%]'.%r", data_make->main->output.to.stream, f_string_eol_s, data_make->main->context.set.notable, arguments.array[0], data_make->main->context.set.notable, f_string_eol_s);
      }

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_delete_e) {
      *status = fake_make_operate_process_type_deletes(data_make, arguments, F_false);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_deletes_e) {
      *status = fake_make_operate_process_type_deletes(data_make, arguments, F_true);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_else_e) {

      // There is nothing to do.
      return 0;
    }

    if (state_process->operation == fake_make_operation_type_exit_e) {
      if (!arguments.used || fl_string_dynamic_compare(fake_make_operation_argument_success_s, arguments.array[0]) == F_equal_to) {
        *status = F_signal_quit;
      }
      else if (fl_string_dynamic_compare(fake_make_operation_argument_failure_s, arguments.array[0]) == F_equal_to) {
        *status = F_status_set_error(F_signal_quit);

        // Forcing exit forces fail mode.
        data_make->setting_make.fail = fake_make_operation_fail_type_exit_e;
        data_make->error.prefix = fl_print_error_s;
        data_make->error.suffix = f_string_empty_s;
        data_make->error.context = data_make->main->context.set.error;
        data_make->error.notable = data_make->main->context.set.notable;
        data_make->error.to.stream = F_type_error_d;
        data_make->error.to.id = F_type_descriptor_error_d;
        data_make->error.set = &data_make->main->context.set;
      }
      else {
        return 0;
      }

      if (data_make->main->error.verbosity == f_console_verbosity_verbose_e) {
        fll_print_format("%rExiting as '%[%Q%]'.%r", data_make->main->output.to.stream, f_string_eol_s, data_make->main->context.set.notable, arguments.used ? arguments.array[0] : fake_make_operation_argument_success_s, data_make->main->context.set.notable, f_string_eol_s);
      }

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_fail_e) {
      fake_make_operate_process_type_fail(data_make, arguments);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_group_e) {
      *status = fake_make_operate_process_type_groups(data_make, arguments, F_false);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_groups_e) {
      *status = fake_make_operate_process_type_groups(data_make, arguments, F_true);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_if_e || state_process->operation == fake_make_operation_type_and_e || state_process->operation == fake_make_operation_type_or_e) {
      if (state_process->condition == fake_make_operation_if_type_if_success_e) {
        if (success) {
          state_process->condition_result = fake_condition_result_true_e;
        }
        else {
          state_process->condition_result = fake_condition_result_false_e;
        }
      }
      else if (state_process->condition == fake_make_operation_if_type_if_defined_e) {
        fake_make_operate_process_type_if_defined(data_make, arguments, F_false, state_process);
      }
      else if (state_process->condition == fake_make_operation_if_type_if_exists_e) {
        *status = fake_make_operate_process_type_if_exists(data_make, arguments, F_false, state_process);
      }
      else if (state_process->condition == fake_make_operation_if_type_if_failure_e) {
        if (success) {
          state_process->condition_result = fake_condition_result_false_e;
        }
        else {
          state_process->condition_result = fake_condition_result_true_e;
        }
      }
      else if (state_process->condition == fake_make_operation_if_type_if_group_e) {
        *status = fake_make_operate_process_type_if_group(data_make, arguments, F_false, state_process);
      }
      else if (state_process->condition == fake_make_operation_if_type_if_is_e) {
        *status = fake_make_operate_process_type_if_is(data_make, arguments, F_false, state_process);
      }
      else if (state_process->condition == fake_make_operation_if_type_if_mode_e) {
        *status = fake_make_operate_process_type_if_mode(data_make, arguments, F_false, state_process);
      }
      else if (state_process->condition == fake_make_operation_if_type_if_not_defined_e) {
        fake_make_operate_process_type_if_defined(data_make, arguments, F_true, state_process);
      }
      else if (state_process->condition == fake_make_operation_if_type_if_equal_e) {
        state_process->condition_result = fake_condition_result_true_e;

        for (f_array_length_t i = 2; i < arguments.used; ++i) {

          if (fl_string_dynamic_compare(arguments.array[1], arguments.array[i]) == F_equal_to_not) {
            state_process->condition_result = fake_condition_result_false_e;

            break;
          }
        } // for
      }
      else if (state_process->condition == fake_make_operation_if_type_if_equal_not_e) {
        state_process->condition_result = fake_condition_result_true_e;

        f_array_length_t i = 1;
        f_array_length_t j = 0;

        for (; i < arguments.used; ++i) {

          for (j = i + 1; j < arguments.used; ++j) {

            if (fl_string_dynamic_compare(arguments.array[i], arguments.array[j]) == F_equal_to) {
              state_process->condition_result = fake_condition_result_false_e;
              i = arguments.used;

              break;
            }
          } // for
        } // for
      }
      else if (state_process->condition == fake_make_operation_if_type_if_greater_e || state_process->condition == fake_make_operation_if_type_if_greater_equal_e || state_process->condition == fake_make_operation_if_type_if_less_e || state_process->condition == fake_make_operation_if_type_if_less_equal_e) {
        *status = fake_make_operate_process_type_if_greater_if_lesser(data_make, arguments, state_process);
      }
      else if (state_process->condition == fake_make_operation_if_type_if_not_exists_e) {
        *status = fake_make_operate_process_type_if_exists(data_make, arguments, F_true, state_process);
      }
      else if (state_process->condition == fake_make_operation_if_type_if_not_group_e) {
        *status = fake_make_operate_process_type_if_group(data_make, arguments, F_true, state_process);
      }
      else if (state_process->condition == fake_make_operation_if_type_if_not_is_e) {
        *status = fake_make_operate_process_type_if_is(data_make, arguments, F_true, state_process);
      }
      else if (state_process->condition == fake_make_operation_if_type_if_not_mode_e) {
        *status = fake_make_operate_process_type_if_mode(data_make, arguments, F_true, state_process);
      }
      else if (state_process->condition == fake_make_operation_if_type_if_not_owner_e) {
        *status = fake_make_operate_process_type_if_owner(data_make, arguments, F_true, state_process);
      }
      else if (state_process->condition == fake_make_operation_if_type_if_owner_e) {
        *status = fake_make_operate_process_type_if_owner(data_make, arguments, F_false, state_process);
      }

      // When inside an else block that is already set to false, then all if conditions inside are always considered false.
      if (state_process->block == fake_state_process_block_else_e && state_process->block_result == fake_condition_result_false_e) {
        return 0;
      }

      // When inside an if block designated to be skipped, then all if conditions inside are always considered false.
      if (state_process->block == fake_state_process_block_if_skip_e) {
        return 0;
      }

      if (state_process->block) {
        if (state_process->operation == fake_make_operation_type_or_e) {
          if (state_process->block_result == fake_condition_result_true_e || state_process->condition_result == fake_condition_result_true_e) {
            state_process->condition_result = fake_condition_result_true_e;
          }
          else {
            state_process->condition_result = fake_condition_result_false_e;
          }
        }
        else if (state_process->block_result == fake_condition_result_true_e && state_process->condition_result == fake_condition_result_true_e) {
          state_process->condition_result = fake_condition_result_true_e;
        }
        else {
          state_process->condition_result = fake_condition_result_false_e;
        }
      }

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_link_e) {
      *status = f_file_link(arguments.array[0], arguments.array[1]);

      if (F_status_is_error(*status)) {
        fll_error_file_print(data_make->error, F_status_set_fine(*status), "f_file_link", F_true, arguments.array[1], f_file_operation_link_s, fll_error_file_type_file_e);
      }
      else if (data_make->main->error.verbosity == f_console_verbosity_verbose_e) {
        flockfile(data_make->main->output.to.stream);

        fl_print_format("Created symbolic link from '%[%Q%]", data_make->main->output.to.stream, data_make->main->context.set.notable, arguments.array[1], data_make->main->context.set.notable);
        fl_print_format("' to %[%Q%].%r", data_make->main->output.to.stream, data_make->main->context.set.notable, arguments.array[0], data_make->main->context.set.notable, f_string_eol_s);

        funlockfile(data_make->main->output.to.stream);
      }

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_mode_e) {
      *status = fake_make_operate_process_type_modes(data_make, arguments, F_false);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_modes_e) {
      *status = fake_make_operate_process_type_modes(data_make, arguments, F_true);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_move_e) {
      *status = fake_make_operate_process_type_move(data_make, arguments);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_operate_e) {
      f_array_length_t id_section = 0;

      for (; id_section < data_make->fakefile.used; ++id_section) {

        if (fl_string_dynamic_partial_compare_string(arguments.array[0].string, data_make->buffer, arguments.array[0].used, data_make->fakefile.array[id_section].name) == F_equal_to) {
          break;
        }
      } // for

      if (id_section == data_make->fakefile.used) {
        return 0;
      }

      const int result = fake_make_operate_section(data_make, id_section, section_stack, status);

      // Ensure that a break only happens within its active state_process->operation stack.
      if (*status == F_signal_abort) {
        *status = F_none;
      }
      else if (F_status_set_fine(*status) == F_signal_abort) {
        *status = F_status_set_error(F_failure);
      }

      return result;
    }

    if (state_process->operation == fake_make_operation_type_owner_e) {
      *status = fake_make_operate_process_type_owners(data_make, arguments, F_false);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_owners_e) {
      *status = fake_make_operate_process_type_owners(data_make, arguments, F_true);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_parameter_e) {
      *status = fake_make_operate_process_type_parameter(data_make, arguments);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_pop_e) {
      *status = fake_make_operate_process_type_pop(data_make, arguments);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_print_e) {
      flockfile(data_make->main->output.to.stream);

      for (f_array_length_t i = 0; i < arguments.used; ++i) {

        f_print_dynamic(arguments.array[i], data_make->main->output.to.stream);

        if (i + 1 < arguments.used) {
          f_print_dynamic_raw(f_string_space_s, data_make->main->output.to.stream);
        }
      } // for

      f_print_dynamic_raw(f_string_space_s, data_make->main->output.to.stream);
      f_print_dynamic_raw(f_string_eol_s, data_make->main->output.to.stream);

      funlockfile(data_make->main->output.to.stream);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_run_e) {
      *status = fake_make_operate_process_run(data_make, arguments, F_false);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_shell_e) {
      *status = fake_make_operate_process_run(data_make, arguments, F_true);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_skeleton_e) {
      *status = fake_skeleton_operate(data_make->main);

      if (F_status_set_fine(*status) == F_interrupt) {
        return 0;
      }

      *status = fake_make_operate_process_return(data_make, F_status_is_error(*status) ? 1 : 0);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_to_e) {
      *status = fake_make_operate_process_type_to(data_make, arguments);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_top_e) {
      *status = fake_make_operate_process_type_top(data_make, arguments);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_touch_e) {
      *status = fake_make_operate_process_type_touch(data_make, arguments);
    }

    return 0;
  }
#endif // _di_fake_make_operate_process_

#ifndef _di_fake_make_operate_process_execute_
  f_status_t fake_make_operate_process_execute(fake_make_data_t * const data_make, const f_string_static_t program, const f_string_statics_t arguments, const bool as_shell) {

    if (fake_signal_received(data_make->main)) {
      return F_status_set_error(F_interrupt);
    }

    f_status_t status = F_none;

    // Reset the environment.
    for (f_array_length_t i = 0; i < data_make->environment.used; ++i) {

      data_make->environment.array[i].name.used = 0;
      data_make->environment.array[i].value.used = 0;
    } // for

    data_make->environment.used = 0;

    status = fl_environment_load_names(data_make->setting_build.environment, &data_make->environment);

    if (F_status_is_error(status)) {
      fll_error_print(data_make->error, F_status_set_fine(status), "fl_environment_load_names", F_true);

      return status;
    }

    if (data_make->main->error.verbosity == f_console_verbosity_verbose_e) {
      flockfile(data_make->main->output.to.stream);

      f_print_dynamic_safely(program, data_make->main->output.to.stream);

      for (f_array_length_t i = 0; i < arguments.used; ++i) {

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

    if (fake_signal_received(data_make->main)) {
      return F_status_set_error(F_interrupt);
    }

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_interrupt) {
        return status;
      }

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

    return fake_make_operate_process_return(data_make, return_code);
  }
#endif // _di_fake_make_operate_process_execute_

#ifndef _di_fake_make_operate_process_return_
  f_status_t fake_make_operate_process_return(fake_make_data_t * const data_make, const int return_code) {

    f_status_t status = F_none;

    data_make->setting_make.parameter.array[0].value.array[0].used = 0;

    if (!return_code) {
      if (F_status_is_error(status)) {
        status = f_string_append("1", 1, &data_make->setting_make.parameter.array[0].value.array[0]);
      }
      else {
        status = f_string_append("0", 1, &data_make->setting_make.parameter.array[0].value.array[0]);
      }

      if (F_status_is_error(status)) {
        fll_error_print(data_make->error, F_status_set_fine(status), "f_string_append", F_true);
      }

      return status;
    }

    if (return_code) {
      f_string_dynamic_t number = f_string_dynamic_t_initialize;

      status = f_conversion_number_signed_to_string(WEXITSTATUS(return_code), f_conversion_data_base_10_s, &number);

      if (F_status_is_error(status)) {
        fll_error_print(data_make->error, F_status_set_fine(status), "f_conversion_number_signed_to_string", F_true);

        f_string_dynamic_resize(0, &number);

        return status;
      }

      status = f_string_dynamic_append(number, &data_make->setting_make.parameter.array[0].value.array[0]);

      f_string_dynamic_resize(0, &number);
    }
    else {
      status = f_string_append("0", 1, &data_make->setting_make.parameter.array[0].value.array[0]);
    }

    if (F_status_is_error(status)) {
      fll_error_print(data_make->error, F_status_set_fine(status), "f_string_append", F_true);

      return status;
    }

    if (data_make->error.verbosity != f_console_verbosity_quiet_e && data_make->error.to.stream) {
      flockfile(data_make->error.to.stream);

      fl_print_format("%r%[%QFailed with return code %]", data_make->error.to.stream, f_string_eol_s, data_make->error.context, data_make->error.prefix, data_make->error.context);
      fl_print_format("%[%i%]", data_make->error.to.stream, data_make->error.notable, return_code, data_make->error.notable);
      fl_print_format("%[.%]%r", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s);

      funlockfile(data_make->error.to.stream);
    }

    if (data_make->setting_make.fail == fake_make_operation_fail_type_exit_e) {
      return F_status_set_error(F_failure);
    }

    return F_failure;
  }
#endif // _di_fake_make_operate_process_return_

#ifndef _di_fake_make_operate_process_run_
  f_status_t fake_make_operate_process_run(fake_make_data_t * const data_make, const f_string_statics_t arguments, const bool as_shell) {

    f_string_statics_t args = f_string_statics_t_initialize;

    if (arguments.used > 1) {
      args.array = arguments.array + 1;
      args.used = arguments.used - 1;
      args.size = 0;
    }

    const f_status_t status = fake_make_operate_process_execute(data_make, arguments.array[0], args, as_shell);

    return status;
  }
#endif // _di_fake_make_operate_process_run_

#ifdef __cplusplus
} // extern "C"
#endif
