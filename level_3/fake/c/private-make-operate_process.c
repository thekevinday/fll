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
  int fake_make_operate_process(fake_make_data_t * const data_make, const f_string_range_t section_name, const f_string_dynamics_t arguments, const bool success, fake_state_process_t *state_process, f_array_lengths_t *section_stack, f_status_t *status) {

    if (*status == F_child) return data_make->main->child;

    if (state_process->operation == fake_make_operation_type_index) {
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

    if (state_process->operation == fake_make_operation_type_break) {
      if (!arguments.used || fl_string_dynamic_compare_string(fake_make_operation_argument_success_s, arguments.array[0], fake_make_operation_argument_success_s_length) == F_equal_to) {
        *status = F_signal_abort;
      }
      else if (fl_string_dynamic_compare_string(fake_make_operation_argument_failure_s, arguments.array[0], fake_make_operation_argument_failure_s_length) == F_equal_to) {
        *status = F_status_set_error(F_signal_abort);
      }
      else {
        return 0;
      }

      if (data_make->main->error.verbosity == f_console_verbosity_verbose) {
        flockfile(data_make->main->output.to.stream);

        fl_print_format("%cBreaking as '", data_make->main->output.to.stream, f_string_eol_s[0]);
        fl_print_format("%[%S%]", data_make->main->output.to.stream, data_make->main->context.set.notable, arguments.used ? arguments.array[0].string : fake_make_operation_argument_success_s, data_make->main->context.set.notable);
        fl_print_format("'.%c", data_make->main->output.to.stream, f_string_eol_s[0]);

        funlockfile(data_make->main->output.to.stream);
      }

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_build) {
      f_string_static_t stub = f_string_static_t_initialize;

      *status = fake_build_operate(arguments.used ? arguments.array[0] : stub, data_make->main);

      if (F_status_set_fine(*status) == F_interrupt) {
        return 0;
      }

      *status = fake_make_operate_process_return(data_make, F_status_is_error(*status) ? 1 : 0);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_clean) {
      *status = fake_clean_operate(data_make->main);

      if (F_status_set_fine(*status) == F_interrupt) {
        return 0;
      }

      *status = fake_make_operate_process_return(data_make, F_status_is_error(*status) ? 1 : 0);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_clone) {
      *status = fake_make_operate_process_type_copy(data_make, arguments, F_true);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_compile) {
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

    if (state_process->operation == fake_make_operation_type_copy) {
      *status = fake_make_operate_process_type_copy(data_make, arguments, F_false);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_define) {

      if (arguments.used > 1) {
        *status = f_environment_set(arguments.array[0].string, arguments.array[1].string, F_true);
      }
      else {
        *status = f_environment_set(arguments.array[0].string, f_string_empty_s, F_true);
      }

      if (F_status_is_error(*status)) {
        fll_error_print(data_make->error, F_status_set_fine(*status), "f_environment_set", F_true);
      }
      else if (data_make->main->error.verbosity == f_console_verbosity_verbose) {
        fll_print_format("%cDefined environment variable '%[%Q%]'.%c", data_make->main->output.to.stream, f_string_eol_s[0], data_make->main->context.set.notable, arguments.array[0], data_make->main->context.set.notable, f_string_eol_s[0]);
      }

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_delete) {
      *status = fake_make_operate_process_type_deletes(data_make, arguments, F_false);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_deletes) {
      *status = fake_make_operate_process_type_deletes(data_make, arguments, F_true);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_else) {

      // Setup the block so that subsequent operations can know the current block and the result (which is preserved across to the else condition).
      state_process->block = fake_make_operation_if_type_else;

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_exit) {
      if (!arguments.used || fl_string_dynamic_compare_string(fake_make_operation_argument_success_s, arguments.array[0], fake_make_operation_argument_success_s_length) == F_equal_to) {
        *status = F_signal_quit;
      }
      else if (fl_string_dynamic_compare_string(fake_make_operation_argument_failure_s, arguments.array[0], fake_make_operation_argument_failure_s_length) == F_equal_to) {
        *status = F_status_set_error(F_signal_quit);

        // Forcing exit forces fail mode.
        data_make->setting_make.fail = fake_make_operation_fail_type_exit;
        data_make->error.prefix = fl_print_error_s;
        data_make->error.suffix = 0;
        data_make->error.context = data_make->main->context.set.error;
        data_make->error.notable = data_make->main->context.set.notable;
        data_make->error.to.stream = F_type_error_d;
        data_make->error.to.id = F_type_descriptor_error_d;
        data_make->error.set = &data_make->main->context.set;
      }
      else {
        return 0;
      }

      if (data_make->main->error.verbosity == f_console_verbosity_verbose) {
        fll_print_format("%cExiting as '%[%S%]'.%c", data_make->main->output.to.stream, f_string_eol_s[0], data_make->main->context.set.notable, arguments.used ? arguments.array[0].string : fake_make_operation_argument_success_s, data_make->main->context.set.notable, f_string_eol_s[0]);
      }

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_fail) {
      fake_make_operate_process_type_fail(data_make, arguments);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_group) {
      *status = fake_make_operate_process_type_groups(data_make, arguments, F_false);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_groups) {
      *status = fake_make_operate_process_type_groups(data_make, arguments, F_true);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_if || state_process->operation == fake_make_operation_type_and || state_process->operation == fake_make_operation_type_or) {
      if (state_process->condition == fake_make_operation_if_type_if_success) {
        if (success) {
          state_process->condition_result = fake_condition_result_true;
        }
        else {
          state_process->condition_result = fake_condition_result_false;
        }
      }
      else if (state_process->condition == fake_make_operation_if_type_if_defined) {
        fake_make_operate_process_type_if_defined(data_make, arguments, F_false, state_process);
      }
      else if (state_process->condition == fake_make_operation_if_type_if_exists) {
        *status = fake_make_operate_process_type_if_exists(data_make, arguments, F_false, state_process);
      }
      else if (state_process->condition == fake_make_operation_if_type_if_failure) {
        if (success) {
          state_process->condition_result = fake_condition_result_false;
        }
        else {
          state_process->condition_result = fake_condition_result_true;
        }
      }
      else if (state_process->condition == fake_make_operation_if_type_if_group) {
        *status = fake_make_operate_process_type_if_group(data_make, arguments, F_false, state_process);
      }
      else if (state_process->condition == fake_make_operation_if_type_if_is) {
        *status = fake_make_operate_process_type_if_is(data_make, arguments, F_false, state_process);
      }
      else if (state_process->condition == fake_make_operation_if_type_if_mode) {
        *status = fake_make_operate_process_type_if_mode(data_make, arguments, F_false, state_process);
      }
      else if (state_process->condition == fake_make_operation_if_type_if_not_defined) {
        fake_make_operate_process_type_if_defined(data_make, arguments, F_true, state_process);
      }
      else if (state_process->condition == fake_make_operation_if_type_if_equal) {
        state_process->condition_result = fake_condition_result_true;

        for (f_array_length_t i = 2; i < arguments.used; ++i) {

          if (fl_string_dynamic_compare(arguments.array[1], arguments.array[i]) == F_equal_to_not) {
            state_process->condition_result = fake_condition_result_false;

            break;
          }
        } // for
      }
      else if (state_process->condition == fake_make_operation_if_type_if_equal_not) {
        state_process->condition_result = fake_condition_result_true;

        f_array_length_t i = 1;
        f_array_length_t j = 0;

        for (; i < arguments.used; ++i) {

          for (j = i + 1; j < arguments.used; ++j) {

            if (fl_string_dynamic_compare(arguments.array[i], arguments.array[j]) == F_equal_to) {
              state_process->condition_result = fake_condition_result_false;
              i = arguments.used;

              break;
            }
          } // for
        } // for
      }
      else if (state_process->condition == fake_make_operation_if_type_if_greater || state_process->condition == fake_make_operation_if_type_if_greater_equal || state_process->condition == fake_make_operation_if_type_if_less || state_process->condition == fake_make_operation_if_type_if_less_equal) {
        *status = fake_make_operate_process_type_if_greater_if_lesser(data_make, arguments, state_process);
      }
      else if (state_process->condition == fake_make_operation_if_type_if_not_exists) {
        *status = fake_make_operate_process_type_if_exists(data_make, arguments, F_true, state_process);
      }
      else if (state_process->condition == fake_make_operation_if_type_if_not_group) {
        *status = fake_make_operate_process_type_if_group(data_make, arguments, F_true, state_process);
      }
      else if (state_process->condition == fake_make_operation_if_type_if_not_is) {
        *status = fake_make_operate_process_type_if_is(data_make, arguments, F_true, state_process);
      }
      else if (state_process->condition == fake_make_operation_if_type_if_not_mode) {
        *status = fake_make_operate_process_type_if_mode(data_make, arguments, F_true, state_process);
      }
      else if (state_process->condition == fake_make_operation_if_type_if_not_owner) {
        *status = fake_make_operate_process_type_if_owner(data_make, arguments, F_true, state_process);
      }
      else if (state_process->condition == fake_make_operation_if_type_if_owner) {
        *status = fake_make_operate_process_type_if_owner(data_make, arguments, F_false, state_process);
      }

      // Setup the block for subsequent operations.
      state_process->block = fake_make_operation_if_type_if;

      if (state_process->condition_result == fake_condition_result_done || state_process->operation == fake_make_operation_type_if) {
        state_process->block_result = state_process->condition_result;
      }
      else if (state_process->operation == fake_make_operation_type_or) {
        if (state_process->block_result == fake_condition_result_true || state_process->condition_result == fake_condition_result_true) {
          state_process->block_result = fake_condition_result_true;
        }
        else {
          state_process->block_result = fake_condition_result_false;
        }
      }
      else {
        if (state_process->block_result == fake_condition_result_true && state_process->condition_result == fake_condition_result_true) {
          state_process->block_result = fake_condition_result_true;
        }
        else {
          state_process->block_result = fake_condition_result_false;
        }
      }

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_link) {
      *status = f_file_link(arguments.array[0].string, arguments.array[1].string);

      if (F_status_is_error(*status)) {
        fll_error_file_print(data_make->error, F_status_set_fine(*status), "f_file_link", F_true, arguments.array[1].string, "create link", fll_error_file_type_file);
      }
      else if (data_make->main->error.verbosity == f_console_verbosity_verbose) {
        flockfile(data_make->main->output.to.stream);

        fl_print_format("Created symbolic link from '%[%Q%]", data_make->main->output.to.stream, data_make->main->context.set.notable, arguments.array[1], data_make->main->context.set.notable);
        fl_print_format("' to %[%Q%].%c", data_make->main->output.to.stream, data_make->main->context.set.notable, arguments.array[0], data_make->main->context.set.notable, f_string_eol_s[0]);

        funlockfile(data_make->main->output.to.stream);
      }

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_mode) {
      *status = fake_make_operate_process_type_modes(data_make, arguments, F_false);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_modes) {
      *status = fake_make_operate_process_type_modes(data_make, arguments, F_true);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_move) {
      *status = fake_make_operate_process_type_move(data_make, arguments);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_operate) {
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

    if (state_process->operation == fake_make_operation_type_owner) {
      *status = fake_make_operate_process_type_owners(data_make, arguments, F_false);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_owners) {
      *status = fake_make_operate_process_type_owners(data_make, arguments, F_true);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_parameter) {
      *status = fake_make_operate_process_type_parameter(data_make, arguments);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_pop) {
      *status = fake_make_operate_process_type_pop(data_make, arguments);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_print) {
      flockfile(data_make->main->output.to.stream);

      for (f_array_length_t i = 0; i < arguments.used; ++i) {

        f_print_dynamic(arguments.array[i], data_make->main->output.to.stream);

        if (i + 1 < arguments.used) {
          f_print_character(f_string_space_s[0], data_make->main->output.to.stream);
        }
      } // for

      f_print_character(f_string_space_s[0], data_make->main->output.to.stream);
      f_print_character(f_string_eol_s[0], data_make->main->output.to.stream);

      funlockfile(data_make->main->output.to.stream);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_run) {
      *status = fake_make_operate_process_run(data_make, arguments, F_false);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_shell) {
      *status = fake_make_operate_process_run(data_make, arguments, F_true);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_skeleton) {
      *status = fake_skeleton_operate(data_make->main);

      if (F_status_set_fine(*status) == F_interrupt) {
        return 0;
      }

      *status = fake_make_operate_process_return(data_make, F_status_is_error(*status) ? 1 : 0);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_to) {
      *status = fake_make_operate_process_type_to(data_make, arguments);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_top) {
      *status = fake_make_operate_process_type_top(data_make, arguments);

      return 0;
    }

    if (state_process->operation == fake_make_operation_type_touch) {
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

    // reset the environment.
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

    if (data_make->main->error.verbosity == f_console_verbosity_verbose) {
      flockfile(data_make->main->output.to.stream);

      f_print_dynamic_safely(program, data_make->main->output.to.stream);

      for (f_array_length_t i = 0; i < arguments.used; ++i) {

        if (arguments.array[i].used) {
          fll_print_format(" %Q", data_make->main->output.to.stream, arguments.array[i]);
        }
      } // for

      f_print_character(f_string_eol_s[0], data_make->main->output.to.stream);

      funlockfile(data_make->main->output.to.stream);

      // flush to stdout before executing command.
      fflush(data_make->main->output.to.stream);
    }

    int return_code = 0;

    // child processes should receive all signals, without blocking.
    f_signal_how_t signals = f_signal_how_t_initialize;
    f_signal_set_empty(&signals.block);
    f_signal_set_fill(&signals.block_not);

    fl_execute_parameter_t parameter = macro_fl_execute_parameter_t_initialize(as_shell ? 0 : FL_execute_parameter_option_path_d, 0, &data_make->environment, &signals, 0);

    status = fll_execute_program(program.string, arguments, &parameter, 0, (void *) &return_code);

    if (fake_signal_received(data_make->main)) {
      return F_status_set_error(F_interrupt);
    }

    if (F_status_is_error(status)) {
      if (F_status_set_fine(status) == F_interrupt) {
        return status;
      }

      if (F_status_set_fine(status) == F_file_found_not) {
        if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
          flockfile(data_make->error.to.stream);

          fl_print_format("%c%[%SFailed to find program '%]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
          fl_print_format("%[%Q%]", data_make->error.to.stream, data_make->error.notable, program, data_make->error.notable);
          fl_print_format("%[' for executing.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

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

    status = f_string_dynamic_terminate_after(&data_make->setting_make.parameter.array[0].value.array[0]);

    if (F_status_is_error(status)) {
      fll_error_print(data_make->error, F_status_set_fine(status), "f_string_dynamic_terminate_after", F_true);

      return status;
    }

    if (data_make->error.verbosity != f_console_verbosity_quiet && data_make->error.to.stream) {
      flockfile(data_make->error.to.stream);

      fl_print_format("%c%[%SFailed with return code %]", data_make->error.to.stream, f_string_eol_s[0], data_make->error.context, data_make->error.prefix, data_make->error.context);
      fl_print_format("%[%i%]", data_make->error.to.stream, data_make->error.notable, return_code, data_make->error.notable);
      fl_print_format("%[.%]%c", data_make->error.to.stream, data_make->error.context, data_make->error.context, f_string_eol_s[0]);

      funlockfile(data_make->error.to.stream);
    }

    if (data_make->setting_make.fail == fake_make_operation_fail_type_exit) {
      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // _di_fake_make_operate_process_return_

#ifndef _di_fake_make_operate_process_run_
  f_status_t fake_make_operate_process_run(fake_make_data_t * const data_make, const f_string_statics_t arguments, const bool as_shell) {

    const f_string_static_t *program = &arguments.array[0];

    f_status_t status = F_none;
    f_string_dynamics_t args = f_string_dynamics_t_initialize;

    if (arguments.used > 1) {
      status = f_string_dynamics_resize(arguments.used - 1, &args);

      if (F_status_is_error(status)) {
        fll_error_print(data_make->error, F_status_set_fine(status), "f_string_dynamics_resize", F_true);
        return status;
      }

      for (f_array_length_t i = 0; i < args.size; ++i) {

        status = f_string_dynamic_append(arguments.array[i + 1], &args.array[i]);

        if (F_status_is_error(status)) {
          fll_error_print(data_make->error, F_status_set_fine(status), "f_string_dynamic_append", F_true);

          f_string_dynamics_resize(0, &args);

          return status;
        }

        status = f_string_dynamic_terminate(&args.array[i]);

        if (F_status_is_error(status)) {
          fll_error_print(data_make->error, F_status_set_fine(status), "f_string_dynamic_terminate", F_true);

          f_string_dynamics_resize(0, &args);

          return status;
        }

        ++args.used;
      } // for
    }

    status = fake_make_operate_process_execute(data_make, *program, args, as_shell);

    f_string_dynamics_resize(0, &args);

    return status;
  }
#endif // _di_fake_make_operate_process_run_

#ifdef __cplusplus
} // extern "C"
#endif
