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

#if !defined(_di_fll_execute_path_) || !defined(_di_fll_execute_program_)
  f_return_status private_fll_execute_fork(const f_string_t program_path, const f_string_t fixed_arguments[], const bool program_is, const f_signal_how_t *signals, f_string_static_t * const pipe_data, int *result) {

    int descriptors[2] = { -1, -1 };

    if (pipe_data) {
       if (pipe(descriptors) == -1) {
         return F_status_set_error(F_pipe);
       }
    }

    const pid_t process_id = fork();

    if (process_id < 0) {

      if (pipe_data) {
        close(descriptors[0]);
        close(descriptors[1]);
      }

      return F_status_set_error(F_fork);
    }

    if (process_id) {

      // close the read pipe for the parent.
      close(descriptors[0]);
    }
    else {

      // close the write pipe for the child.
      close(descriptors[1]);

      if (signals) {
        f_signal_set_handle(SIG_BLOCK, &signals->block);
        f_signal_set_handle(SIG_UNBLOCK, &signals->block_not);
      }

      if (pipe_data) {
        dup2(descriptors[0], f_type_descriptor_input);
      }

      const int code = program_is ? execvp(program_path, fixed_arguments) : execv(program_path, fixed_arguments);

      // close the write pipe for the child when done.
      if (pipe_data) {
        close(descriptors[0]);
      }

      if (result) {
        *result = code;
      }

      return F_child;
    }

    // write all data, if child doesn't read this could block until child closes the pipe.
    if (pipe_data) {
      const f_file_t file = f_macro_file_t_initialize(0, descriptors[1], f_file_flag_write_only);

      f_file_write(file, *pipe_data, 0);

      // close the write pipe for the parent when finished writing.
      close(descriptors[1]);
    }

    // have the parent wait for the child process to finish.
    waitpid(process_id, result, WUNTRACED | WCONTINUED);

    if (result != 0) {
      if (WIFEXITED(*result)) {
        return F_none;
      }

      return F_status_set_error(F_failure);
    }

    return F_none;
  }
#endif // !defined(_di_fll_execute_path_) || !defined(_di_fll_execute_program_)

#if !defined(_di_fll_execute_path_environment_) || !defined(_di_fll_execute_program_environment_)
  f_return_status private_fll_execute_fork_environment(const f_string_t program_path, const f_string_t fixed_arguments[], const bool program_is, const f_string_statics_t names, const f_string_statics_t values, const f_signal_how_t *signals, f_string_static_t * const pipe_data, int *result) {

    int descriptors[2] = { -1, -1 };

    if (pipe_data) {
       if (pipe(descriptors) == -1) {
         return F_status_set_error(F_pipe);
       }
    }

    const pid_t process_id = fork();

    if (process_id < 0) {

      if (pipe_data) {
        close(descriptors[0]);
        close(descriptors[1]);
      }

      return F_status_set_error(F_fork);
    }

    if (process_id) {

      // close the read pipe for the parent.
      close(descriptors[0]);
    }
    else {

      // close the write pipe for the child.
      close(descriptors[1]);

      if (signals) {
        f_signal_set_handle(SIG_BLOCK, &signals->block);
        f_signal_set_handle(SIG_UNBLOCK, &signals->block_not);
      }

      clearenv();

      for (f_array_length_t i = 0; i < names.used; i++) {
        f_environment_set_dynamic(names.array[i], values.array[i], F_true);
      } // for

      if (pipe_data) {
        dup2(descriptors[0], f_type_descriptor_input);
      }

      const int code = program_is ? execvp(program_path, fixed_arguments) : execv(program_path, fixed_arguments);

      // close the write pipe for the child when done.
      if (pipe_data) {
        close(descriptors[0]);
      }

      if (result) {
        *result = code;
      }

      return F_child;
    }

    // write all data, if child doesn't read this could block until child closes the pipe.
    if (pipe_data) {
      const f_file_t file = f_macro_file_t_initialize(0, descriptors[1], f_file_flag_write_only);

      f_file_write(file, *pipe_data, 0);

      // close the write pipe for the parent when finished writing.
      close(descriptors[1]);
    }

    // have the parent wait for the child process to finish.
    waitpid(process_id, result, WUNTRACED | WCONTINUED);

    if (result != 0) {
      if (WIFEXITED(*result)) {
        return F_none;
      }

      return F_status_set_error(F_failure);
    }
  }
#endif // !defined(_di_fll_execute_path_environment_) || !defined(_di_fll_execute_program_environment_)

#if !defined(_di_fll_execute_path_) || !defined(_di_fll_execute_path_environment_)
  void private_fll_execute_path_arguments_fixate(const f_string_t program_path, const f_string_statics_t arguments, const f_string_length_t name_size, char program_name[], f_string_t fixed_arguments[]) {

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

    // insert the required end of array designator.
    fixed_arguments[arguments.used + 1] = 0;
  }
#endif // !defined(_di_fll_execute_path_) || !defined(_di_fll_execute_path_environment_)

#ifdef __cplusplus
} // extern "C"
#endif
