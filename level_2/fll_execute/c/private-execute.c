#include "execute.h"
#include "private-execute.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fll_execute_arguments_add_) || !defined(_di_fll_execute_arguments_add_set_) || !defined(_di_fll_execute_arguments_dynamic_add_) || !defined(_di_fll_execute_arguments_dynamic_add_set_)
  f_return_status private_fll_execute_arguments_add(const f_string_t source, const f_string_length_t length, f_string_dynamics_t *arguments) {

    f_status_t status = fl_string_dynamics_increase(arguments);
    if (F_status_is_error(status)) return status;

    f_string_dynamic_t argument = f_string_dynamic_t_initialize;

    if (length) {
      status = fl_string_append(source, length, &argument);

      if (F_status_is_error(status)) {
        fl_string_dynamic_delete(&argument);
        return status;
      }
    }

    status = fl_string_dynamic_terminate(&argument);

    if (F_status_is_error(status)) {
      fl_string_dynamic_delete(&argument);
      return status;
    }

    arguments->array[arguments->used].string = argument.string;
    arguments->array[arguments->used].used = argument.used;
    arguments->array[arguments->used].size = argument.size;
    arguments->used++;

    return F_none;
  }
#endif // !defined(_di_fll_execute_arguments_add_) || !defined(_di_fll_execute_arguments_add_set_) || !defined(_di_fll_execute_arguments_dynamic_add_) || !defined(_di_fll_execute_arguments_dynamic_add_set_)

#if !defined(_di_fll_execute_arguments_add_parameter_) || !defined(_di_fll_execute_arguments_add_parameter_set_) || !defined(_di_fll_execute_arguments_dynamic_add_parameter_) || !defined(_di_fll_execute_arguments_dynamic_add_parameter_set_)
  f_return_status private_fll_execute_arguments_add_parameter(const f_string_t prefix, const f_string_length_t prefix_length, const f_string_t name, const f_string_length_t name_length, const f_string_t value, const f_string_length_t value_length, f_string_dynamics_t *arguments) {

    f_status_t status = fl_string_dynamics_increase(arguments);
    if (F_status_is_error(status)) return status;

    f_string_dynamic_t argument = f_string_dynamic_t_initialize;

    if (prefix_length) {
      status = fl_string_append(prefix, prefix_length, &argument);

      if (F_status_is_error(status)) {
        fl_string_dynamic_delete(&argument);

        return status;
      }
    }

    if (name_length) {
      status = fl_string_append(name, name_length, &argument);

      if (F_status_is_error(status)) {
        fl_string_dynamic_delete(&argument);

        return status;
      }
    }

    status = fl_string_dynamic_terminate(&argument);

    if (F_status_is_error(status)) {
      fl_string_dynamic_delete(&argument);

      return status;
    }

    arguments->array[arguments->used].string = argument.string;
    arguments->array[arguments->used].used = argument.used;
    arguments->array[arguments->used].size = argument.size;
    arguments->used++;

    f_macro_string_dynamic_t_clear(argument);

    if (value_length) {
      status = fl_string_append(value, value_length, &argument);

      if (F_status_is_error(status)) {
        fl_string_dynamic_delete(&argument);

        return status;
      }
    }

    status = fl_string_dynamic_terminate(&argument);

    if (F_status_is_error(status)) {
      fl_string_dynamic_delete(&argument);

      return status;
    }

    status = fl_string_dynamics_increase(arguments);

    if (F_status_is_error(status)) {
      fl_string_dynamic_delete(&argument);

      return status;
    }

    arguments->array[arguments->used].string = argument.string;
    arguments->array[arguments->used].used = argument.used;
    arguments->array[arguments->used].size = argument.size;
    arguments->used++;

    return F_none;
  }
#endif // !defined(_di_fll_execute_arguments_add_parameter_) || !defined(_di_fll_execute_arguments_add_parameter_set_) || !defined(_di_fll_execute_arguments_dynamic_add_parameter_) || !defined(_di_fll_execute_arguments_dynamic_add_parameter_set_)

#if !defined(_di_fll_execute_program_)
  f_return_status private_fll_execute_as_child(const fl_execute_as_t as, fl_execute_parameter_t * const parameter, int *result) {

    if (as.nice) {
      errno = 0;

      if (nice(*as.nice) == -1 && errno == -1) {
        *result = -1;

        if (parameter && parameter->option & fl_execute_parameter_option_exit) {
          exit(*result);
        }

        return F_status_set_error(F_nice);
      }
    }

    if (as.capability) {
      const f_status_t status = f_capability_process_set(as.capability);

      if (F_status_is_error(status) && F_status_set_fine(status) != F_supported_not) {
        *result = -1;

        if (parameter && parameter->option & fl_execute_parameter_option_exit) {
          exit(*result);
        }

        return F_status_set_error(F_capability);
      }
    }

    if (as.id_groups) {
      if (setgroups(as.id_groups->used, as.id_groups->array) == -1) {
        *result = -1;

        if (parameter && parameter->option & fl_execute_parameter_option_exit) {
          exit(*result);
        }

        return F_status_set_error(F_group);
      }
    }

    if (as.id_group) {
      if (setgid(*as.id_group) == -1) {
        *result = -1;

        if (parameter && parameter->option & fl_execute_parameter_option_exit) {
          exit(*result);
        }

        return F_status_set_error(F_group);
      }
    }

    if (as.id_user) {
      if (setuid(*as.id_user) == -1) {
        *result = -1;

        if (parameter && parameter->option & fl_execute_parameter_option_exit) {
          exit(*result);
        }

        return F_status_set_error(F_user);
      }
    }

    return F_none;
  }
#endif // !defined(_di_fll_execute_program_)

#if !defined(_di_fll_execute_program_)
  f_return_status private_fll_execute_as_parent(const fl_execute_as_t as, const pid_t id_child, fl_execute_parameter_t * const parameter, char *result) {

    if (as.scheduler) {
      struct sched_param parameter_schedule;
      parameter_schedule.sched_priority = as.scheduler->priority;

      errno = 0;

      if (sched_setscheduler(id_child, as.scheduler->policy, &parameter_schedule) == -1) {
        result[0] = '1';

        return F_status_set_error(F_schedule);
      }
    }

    if (as.control_group) {
      if (F_status_is_error(fl_control_group_apply(*as.control_group, id_child))) {
        result[0] = '1';

        return F_status_set_error(F_control_group);
      }
    }

    return F_none;
  }
#endif // !defined(_di_fll_execute_program_)

#if !defined(_di_fll_execute_program_)
  f_return_status private_fll_execute_fork(const f_string_t program, const f_string_t fixed_arguments[], fl_execute_parameter_t * const parameter, fl_execute_as_t * const as, int *result) {

    int descriptors[2] = { -1, -1 };

    if (as) {
      if (pipe(descriptors) == -1) {
        return F_status_set_error(F_pipe);
      }
    }

    const pid_t id_process = fork();

    if (id_process < 0) {
      if (as) {
        close(descriptors[0]);
        close(descriptors[1]);
      }

      return F_status_set_error(F_fork);
    }

    if (id_process) {

      if (as) {

        // close the read pipe for the parent.
        close(descriptors[0]);

        // have the parent perform all appropriate access controls and then send either '0' for no error or '1' for error to the child.
        {
          char string_result[2] = { '0', 0 };

          const f_file_t file = f_macro_file_t_initialize2(0, descriptors[1], f_file_flag_write_only);

          f_string_static_t result = f_string_static_t_initialize;

          result.string = string_result;
          result.used = 1;
          result.size = 2;

          const f_status_t status = private_fll_execute_as_parent(*as, id_process, parameter, string_result);

          // inform the child that it can now safely begin (or exit).
          if (F_status_is_error(f_file_write(file, result, 0))) {
            string_result[0] = '1';
          }

          // close the write pipe for the parent when finished writing.
          close(descriptors[1]);

          if (F_status_is_error(status)) {
            return status;
          }
        }
      }

      // have the parent wait for the child process to finish.
      waitpid(id_process, result, WUNTRACED | WCONTINUED);

      // this must explicitly check for 0 (as opposed to checking (!result)).
      if (result != 0) {
        if (WIFEXITED(*result)) {
          return F_none;
        }

        return F_status_set_error(F_failure);
      }

      return F_none;
    }

    if (as) {

      // close the write pipe for the child.
      close(descriptors[1]);

      char string_response[2] = { 0, 0 };

      f_string_static_t response = f_string_static_t_initialize;

      response.string = string_response;
      response.used = 0;
      response.size = 2;

      const f_file_t file = f_macro_file_t_initialize(0, descriptors[0], f_file_flag_read_only, 1, 1);

      f_file_read_block(file, &response);

      if (!response.used || response.string[0] == '1') {
        close(descriptors[0]);

        if (result) {
          *result = -1;
        }

        if (parameter && parameter->option & fl_execute_parameter_option_exit) {
          exit(-1);
        }

        return F_child;
      }
    }

    if (parameter && parameter->signals) {
      #ifdef _di_pthread_support_

        f_signal_mask(SIG_BLOCK, &parameter->signals->block, 0);
        f_signal_mask(SIG_UNBLOCK, &parameter->signals->block_not, 0);

      #else // _di_pthread_support_

        if (parameter->option & fl_execute_parameter_option_threadsafe) {
          f_thread_signal_mask(SIG_BLOCK, &parameter->signals->block, 0);
          f_thread_signal_mask(SIG_UNBLOCK, &parameter->signals->block_not, 0);
        }
        else {
          f_signal_mask(SIG_BLOCK, &parameter->signals->block, 0);
          f_signal_mask(SIG_UNBLOCK, &parameter->signals->block_not, 0);
        }

      #endif // _di_pthread_support_
    }

    if (parameter && parameter->environment) {
      clearenv();

      for (f_array_length_t i = 0; i < parameter->environment->used; i++) {
        f_environment_set_dynamic(parameter->environment->array[i].name, parameter->environment->array[i].value, F_true);
      } // for
    }

    if (as) {

      // close the write pipe for the child when done.
      close(descriptors[0]);

      const f_status_t status = private_fll_execute_as_child(*as, parameter, result);

      if (F_status_is_error(status)) {
        return status;
      }
    }

    const int code = parameter && (parameter->option & fl_execute_parameter_option_path) ? execv(program, fixed_arguments) : execvp(program, fixed_arguments);

    if (result) {
      *result = code;
    }

    if (parameter && parameter->option & fl_execute_parameter_option_exit) {
      exit(code);
    }

    return F_child;
  }
#endif // !defined(_di_fll_execute_program_)

#if !defined(_di_fll_execute_program_)
  f_return_status private_fll_execute_fork_data(const f_string_t program, const f_string_t fixed_arguments[], fl_execute_parameter_t * const parameter, fl_execute_as_t * const as, int *result) {

    int descriptors[2] = { -1, -1 };

    if (pipe(descriptors) == -1) {
      return F_status_set_error(F_pipe);
    }

    const pid_t id_process = fork();

    if (id_process < 0) {
      close(descriptors[0]);
      close(descriptors[1]);

      return F_status_set_error(F_fork);
    }

    if (id_process) {

      // close the read pipe for the parent.
      close(descriptors[0]);

      {
        char string_result[2] = { '0', 0 };

        const f_file_t file = f_macro_file_t_initialize2(0, descriptors[1], f_file_flag_write_only);

        f_status_t status = F_none;

        // have the parent perform all appropriate access controls and then send either '0' for no error or '1' for error to the child.
        if (as) {
          f_string_static_t result = f_string_static_t_initialize;

          result.string = string_result;
          result.used = 1;
          result.size = 2;

          status = private_fll_execute_as_parent(*as, id_process, parameter, string_result);

          // inform the child that it can now safely begin (or exit).
          if (F_status_is_error(f_file_write(file, result, 0))) {
            string_result[0] = '1';
          }
        }

        // write all data, if child doesn't read this could block until child closes the pipe.
        if (string_result[0] == '0') {
          f_file_write(file, *parameter->data, 0);
        }

        // close the write pipe for the parent when finished writing.
        close(descriptors[1]);

        if (F_status_is_error(status)) {
          return status;
        }
      }

      // have the parent wait for the child process to finish.
      waitpid(id_process, result, WUNTRACED | WCONTINUED);

      // this must explicitly check for 0 (as opposed to checking (!result)).
      if (result != 0) {
        if (WIFEXITED(*result)) {
          return F_none;
        }

        return F_status_set_error(F_failure);
      }

      return F_none;
    }

    // close the write pipe for the child.
    close(descriptors[1]);

    // wait for parent to tell child to begin.
    if (as) {
      char string_response[2] = { 0, 0 };

      f_string_static_t response = f_string_static_t_initialize;

      response.string = string_response;
      response.used = 0;
      response.size = 2;

      const f_file_t file = f_macro_file_t_initialize(0, descriptors[0], f_file_flag_read_only, 1, 1);

      f_file_read_block(file, &response);

      if (!response.used || response.string[0] == '1') {
        close(descriptors[0]);

        if (result) {
          *result = -1;
        }

        if (parameter && parameter->option & fl_execute_parameter_option_exit) {
          exit(-1);
        }

        return F_child;
      }
    }

    if (parameter && parameter->signals) {
      #ifdef _di_pthread_support_

        f_signal_mask(SIG_BLOCK, &parameter->signals->block, 0);
        f_signal_mask(SIG_UNBLOCK, &parameter->signals->block_not, 0);

      #else // _di_pthread_support_

        if (parameter->option & fl_execute_parameter_option_threadsafe) {
          f_thread_signal_mask(SIG_BLOCK, &parameter->signals->block, 0);
          f_thread_signal_mask(SIG_UNBLOCK, &parameter->signals->block_not, 0);
        }
        else {
          f_signal_mask(SIG_BLOCK, &parameter->signals->block, 0);
          f_signal_mask(SIG_UNBLOCK, &parameter->signals->block_not, 0);
        }

      #endif // _di_pthread_support_
    }

    if (parameter && parameter->environment) {
      clearenv();

      for (f_array_length_t i = 0; i < parameter->environment->used; i++) {
        f_environment_set_dynamic(parameter->environment->array[i].name, parameter->environment->array[i].value, F_true);
      } // for
    }

    dup2(descriptors[0], f_type_descriptor_input);

    if (as) {
      const f_status_t status = private_fll_execute_as_child(*as, parameter, result);

      if (F_status_is_error(status)) {
        return status;
      }
    }

    const int code = parameter && parameter->option & fl_execute_parameter_option_path ? execv(program, fixed_arguments) : execvp(program, fixed_arguments);

    // close the write pipe for the child when done.
    close(descriptors[0]);

    if (result) {
      *result = code;
    }

    if (parameter && parameter->option & fl_execute_parameter_option_exit) {
      exit(code);
    }

    return F_child;
  }
#endif // !defined(_di_fll_execute_program_)

#if !defined(_di_fll_execute_program_)
  void private_fll_execute_path_arguments_fixate(const f_string_t program_path, const f_string_statics_t arguments, const bool fixated_is, const f_string_length_t name_size, char program_name[], f_string_t fixed_arguments[]) {

    memcpy(program_name, program_path, name_size);
    program_name[name_size] = 0;

    if (name_size) {
      fixed_arguments[0] = program_name;
    }
    else {
      fixed_arguments[0] = 0;
    }

    f_string_length_t i = 0;

    if (fixated_is) {
      for (i = 1; i < arguments.used; ++i) {
        fixed_arguments[i] = arguments.array[i].string;
      } // for
    }
    else {
      for (; i < arguments.used; ++i) {
        fixed_arguments[i + 1] = arguments.array[i].string;
      } // for

      i++;
    }

    // insert the required end of array designator.
    fixed_arguments[i] = 0;
  }
#endif // !defined(_di_fll_execute_program_)

#ifdef __cplusplus
} // extern "C"
#endif
