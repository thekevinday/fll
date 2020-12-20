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
  f_return_status private_fll_execute_fork(const f_string_t program, const f_string_t fixed_arguments[], fl_execute_parameter_t * const parameter, int *result) {

    const pid_t process_id = fork();

    if (process_id < 0) {
      return F_status_set_error(F_fork);
    }

    if (process_id) {

      // have the parent wait for the child process to finish.
      waitpid(process_id, result, WUNTRACED | WCONTINUED);

      // this must explicitly check for 0 (as opposed to checking (!result)).
      if (result != 0) {
        if (WIFEXITED(*result)) {
          return F_none;
        }

        return F_status_set_error(F_failure);
      }

      return F_none;
    }

    if (parameter && parameter->signals) {
      f_signal_set_handle(SIG_BLOCK, &parameter->signals->block);
      f_signal_set_handle(SIG_UNBLOCK, &parameter->signals->block_not);
    }

    if (parameter && parameter->environment) {
      clearenv();

      for (f_array_length_t i = 0; i < parameter->environment->used; i++) {
        f_environment_set_dynamic(parameter->environment->array[i].name, parameter->environment->array[i].value, F_true);
      } // for
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
  f_return_status private_fll_execute_fork_data(const f_string_t program, const f_string_t fixed_arguments[], fl_execute_parameter_t * const parameter, int *result) {

    int descriptors[2] = { -1, -1 };

    if (pipe(descriptors) == -1) {
      return F_status_set_error(F_pipe);
    }

    const pid_t process_id = fork();

    if (process_id < 0) {
      close(descriptors[0]);
      close(descriptors[1]);

      return F_status_set_error(F_fork);
    }

    if (process_id) {

      // close the read pipe for the parent.
      close(descriptors[0]);

      // write all data, if child doesn't read this could block until child closes the pipe.
      {
        const f_file_t file = f_macro_file_t_initialize(0, descriptors[1], f_file_flag_write_only);

        f_file_write(file, *parameter->data, 0);

        // close the write pipe for the parent when finished writing.
        close(descriptors[1]);
      }

      // have the parent wait for the child process to finish.
      waitpid(process_id, result, WUNTRACED | WCONTINUED);

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

    if (parameter && parameter->signals) {
      f_signal_set_handle(SIG_BLOCK, &parameter->signals->block);
      f_signal_set_handle(SIG_UNBLOCK, &parameter->signals->block_not);
    }

    if (parameter && parameter->environment) {
      clearenv();

      for (f_array_length_t i = 0; i < parameter->environment->used; i++) {
        f_environment_set_dynamic(parameter->environment->array[i].name, parameter->environment->array[i].value, F_true);
      } // for
    }

    dup2(descriptors[0], f_type_descriptor_input);

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
  void private_fll_execute_path_arguments_fixate(const f_string_t program_path, const f_string_statics_t arguments, const uint8_t option, const f_string_length_t name_size, char program_name[], f_string_t fixed_arguments[]) {

    if (option & fl_execute_parameter_option_fixated) {

      for (f_string_length_t i = 0; i < arguments.used; i++) {
        fixed_arguments[i] = arguments.array[i].string;
      } // for

      // insert the required end of array designator.
      fixed_arguments[arguments.used] = 0;
    }
    else {
      memcpy(program_name, program_path, name_size);
      program_name[name_size] = 0;

      if (name_size) {
        fixed_arguments[0] = program_name;
      }
      else {
        fixed_arguments[0] = 0;
      }

      for (f_string_length_t i = 0; i < arguments.used; i++) {
        fixed_arguments[i + 1] = arguments.array[i].string;
      } // for
    }

    // insert the required end of array designator.
    fixed_arguments[arguments.used + 1] = 0;
  }
#endif // !defined(_di_fll_execute_program_)

#ifdef __cplusplus
} // extern "C"
#endif
