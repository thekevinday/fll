#include "execute.h"
#include "private-execute.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_fll_execute_arguments_add_) || !defined(_di_fll_execute_arguments_add_set_)
  f_status_t private_fll_execute_arguments_add(const f_string_static_t source, f_string_dynamics_t *arguments) {

    arguments->array[arguments->used].used = 0;

    f_status_t status = f_string_dynamic_increase_by(source.used + 1, &arguments->array[arguments->used]);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamic_append(source, &arguments->array[arguments->used]);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamic_terminate_after(&arguments->array[arguments->used]);
    if (F_status_is_error(status)) return status;

    ++arguments->used;

    return F_none;
  }
#endif // !defined(_di_fll_execute_arguments_add_) || !defined(_di_fll_execute_arguments_add_set_)

#if !defined(_di_fll_execute_arguments_add_parameter_) || !defined(_di_fll_execute_arguments_add_parameter_set_)
  f_status_t private_fll_execute_arguments_add_parameter(const f_string_static_t prefix, const f_string_static_t name, const f_string_static_t value, f_string_dynamics_t *arguments) {

    arguments->array[arguments->used].used = 0;

    f_status_t status = f_string_dynamic_increase_by(prefix.used + name.used + 1, &arguments->array[arguments->used]);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamic_append(prefix, &arguments->array[arguments->used]);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamic_terminate_after(&arguments->array[arguments->used]);
    if (F_status_is_error(status)) return status;

    ++arguments->used;

    status = f_string_dynamics_increase(F_memory_default_allocation_small_d, arguments);
    if (F_status_is_error(status)) return status;

    arguments->array[arguments->used].used = 0;

    status = f_string_dynamic_increase_by(value.used + 1, &arguments->array[arguments->used]);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamic_append(value, &arguments->array[arguments->used]);
    if (F_status_is_error(status)) return status;

    status = f_string_dynamic_terminate_after(&arguments->array[arguments->used]);
    if (F_status_is_error(status)) return status;

    ++arguments->used;

    return F_none;
  }
#endif // !defined(_di_fll_execute_arguments_add_parameter_) || !defined(_di_fll_execute_arguments_add_parameter_set_)

#if !defined(_di_fll_execute_program_)
  f_status_t private_fll_execute_as_child(const fl_execute_as_t as, fl_execute_parameter_t * const parameter, int *result) {

    if (as.nice) {
      errno = 0;

      if (nice(*as.nice) == -1 && errno == -1) {
        if (parameter && parameter->option & FL_execute_parameter_option_exit_d) {
          exit(F_execute_nice);
        }

        *result = F_execute_nice;

        return F_status_set_error(F_nice);
      }
    }

    if (as.capability) {
      const f_status_t status = f_capability_process_set(as.capability);

      if (F_status_is_error(status) && F_status_set_fine(status) != F_supported_not) {
        if (parameter && parameter->option & FL_execute_parameter_option_exit_d) {
          exit(F_execute_capability);
        }

        *result = F_execute_capability;

        return F_status_set_error(F_capability);
      }
    }

    if (as.id_groups) {
      if (setgroups(as.id_groups->used, (const gid_t *) as.id_groups->array) == -1) {

        if (parameter && parameter->option & FL_execute_parameter_option_exit_d) {
          exit(F_execute_group);
        }

        *result = F_execute_group;

        return F_status_set_error(F_group);
      }
    }

    if (as.id_group) {
      if (setgid(*as.id_group) == -1) {
        if (parameter && parameter->option & FL_execute_parameter_option_exit_d) {
          exit(F_execute_group);
        }

        *result = F_execute_group;

        return F_status_set_error(F_group);
      }
    }

    if (as.id_user) {
      if (setuid(*as.id_user) == -1) {
        if (parameter && parameter->option & FL_execute_parameter_option_exit_d) {
          exit(F_execute_user);
        }

        *result = F_execute_user;

        return F_status_set_error(F_user);
      }
    }

    return F_none;
  }
#endif // !defined(_di_fll_execute_program_)

#if !defined(_di_fll_execute_program_)
  f_status_t private_fll_execute_as_parent(const fl_execute_as_t as, const pid_t id_child, fl_execute_parameter_t * const parameter, char *result) {

    if (as.affinity && as.affinity->used) {
      cpu_set_t *set = CPU_ALLOC(as.affinity->used);

      if (set == 0) {
        result[0] = '1';

        return F_status_set_error(F_processor);
      }

      size_t size = CPU_ALLOC_SIZE(as.affinity->used);

      CPU_ZERO_S(size, set);

      for (f_array_length_t i = 0; i < as.affinity->used; ++i) {
        CPU_SET_S(as.affinity->array[i], size, set);
      } // for

      const int response = sched_setaffinity(id_child, size, set);

      CPU_FREE(set);

      if (response == -1) {
        result[0] = '1';

        return F_status_set_error(F_processor);
      }
    }

    if (as.control_group) {
      if (F_status_is_error(fl_control_group_apply(*as.control_group, id_child))) {
        result[0] = '1';

        return F_status_set_error(F_control_group);
      }
    }

    if (as.scheduler) {
      struct sched_param parameter_schedule;
      parameter_schedule.sched_priority = as.scheduler->priority;

      errno = 0;

      if (sched_setscheduler(id_child, as.scheduler->policy, &parameter_schedule) == -1) {
        result[0] = '1';

        return F_status_set_error(F_schedule);
      }
    }

    if (as.limits) {
      for (f_array_length_t i = 0; i < as.limits->used; ++i) {

        if (F_status_is_error(f_limit_process(id_child, as.limits->array[i].type, &as.limits->array[i].value, 0))) {
          result[0] = '1';

          return F_status_set_error(F_limit);
        }
      } // for
    }

    return F_none;
  }
#endif // !defined(_di_fll_execute_program_)

#if !defined(_di_fll_execute_program_)
  f_status_t private_fll_execute_fork(const bool direct, const f_string_static_t program, const f_string_t fixed_arguments[], fl_execute_parameter_t * const parameter, fl_execute_as_t * const as, void *result) {

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

        // Close the read pipe for the parent.
        close(descriptors[0]);

        // Have the parent perform all appropriate access controls and then send either '0' for no error or '1' for error to the child.
        {
          char string_result[2] = { '0', 0 };

          const f_file_t file = macro_f_file_t_initialize2(0, descriptors[1], F_file_flag_write_only_d);

          f_string_static_t buffer = f_string_static_t_initialize;

          buffer.string = string_result;
          buffer.used = 1;
          buffer.size = 2;

          const f_status_t status = private_fll_execute_as_parent(*as, id_process, parameter, string_result);

          // Inform the child that it can now safely begin (or exit).
          f_file_write(file, buffer, 0);

          // Close the write pipe for the parent when finished writing.
          close(descriptors[1]);

          if (F_status_is_error(status)) {
            return status;
          }
        }
      }

      if (parameter && parameter->option & FL_execute_parameter_option_return_d) {

        if (result != 0) {
          pid_t *r = (pid_t *) result;
          *r = id_process;
        }

        return F_parent;
      }

      // have the parent wait for the child process to finish.
      waitpid(id_process, (int *) result, parameter ? parameter->wait : 0);

      // This must explicitly check for 0 (as opposed to checking (!result)).
      if (result != 0) {
        if (WIFEXITED(*((int *) result))) {
          return F_none;
        }

        return F_status_set_error(F_failure);
      }

      return F_none;
    }

    if (parameter && parameter->option & FL_execute_parameter_option_session_d) {
      setsid();
    }

    if (as) {

      // Close the write pipe for the child.
      close(descriptors[1]);

      f_string_dynamic_t response = f_string_dynamic_t_initialize;

      const f_file_t file = macro_f_file_t_initialize(0, descriptors[0], F_file_flag_read_only_d, 1, 1);

      f_file_read_block(file, &response);

      if (!response.used || response.string[0] == '1') {
        f_string_dynamic_resize(0, &response);

        close(descriptors[0]);

        if (result) {
          int *r = (int *) result;

          *r = F_execute_failure;
        }

        if (parameter && parameter->option & FL_execute_parameter_option_exit_d) {
          exit(F_execute_failure);
        }

        return F_child;
      }

      f_string_dynamic_resize(0, &response);
    }

    if (parameter && parameter->signals) {
      #ifdef _di_pthread_support_
        f_signal_mask(SIG_BLOCK, &parameter->signals->block, 0);
        f_signal_mask(SIG_UNBLOCK, &parameter->signals->block_not, 0);
      #else // _di_pthread_support_
        if (parameter->option & FL_execute_parameter_option_threadsafe_d) {
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

      for (f_array_length_t i = 0; i < parameter->environment->used; ++i) {
        f_environment_set(parameter->environment->array[i].name, parameter->environment->array[i].value, F_true);
      } // for
    }

    if (as) {

      // Close the write pipe for the child when done.
      close(descriptors[0]);

      const f_status_t status = private_fll_execute_as_child(*as, parameter, (int *) result);
      if (F_status_is_error(status)) return status;
    }

    int code = direct ? execv(program.string, fixed_arguments) : execvp(program.string, fixed_arguments);

    if (code == -1) {
      if (errno == EACCES) code = F_execute_access;
      else if (errno == E2BIG) code = F_execute_too_large;
      else if (errno == EAGAIN) code = F_execute_resource_not;
      else if (errno == EFAULT) code = F_execute_buffer;
      else if (errno == EINVAL) code = F_execute_parameter;
      else if (errno == EIO) code = F_execute_input_output;
      else if (errno == EISDIR) code = F_execute_file_type_directory;
      else if (errno == EIO) code = F_execute_input_output;
      else if (errno == ELIBBAD) code = F_execute_valid_not;
      else if (errno == ELOOP) code = F_execute_loop;
      else if (errno == EMFILE) code = F_execute_resource_not;
      else if (errno == ENAMETOOLONG) code = F_execute_name_not;
      else if (errno == ENFILE) code = F_execute_resource_not;
      else if (errno == ENOENT) code = F_execute_file_found_not;
      else if (errno == ENOEXEC) code = F_execute_bad;
      else if (errno == ENOMEM) code = F_execute_memory_not;
      else if (errno == ENOTDIR) code = F_execute_directory_not;
      else if (errno == EPERM) code = F_execute_prohibited;
      else if (errno == ETXTBSY) code = F_execute_busy;
      else code = F_execute_failure;
    }
    else if (code < 0) {
      code = F_execute_failure;
    }

    if (result) {
      int *r = (int *) result;
      *r = code;
    }

    if (parameter && parameter->option & FL_execute_parameter_option_exit_d) {
      exit(code);
    }

    return F_child;
  }
#endif // !defined(_di_fll_execute_program_)

#if !defined(_di_fll_execute_program_)
  f_status_t private_fll_execute_fork_data(const bool direct, const f_string_static_t program, const f_string_t fixed_arguments[], fl_execute_parameter_t * const parameter, fl_execute_as_t * const as, void *result) {

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

      // Close the read pipe for the parent.
      close(descriptors[0]);

      {
        char string_result[2] = { '0', 0 };

        const f_file_t file = macro_f_file_t_initialize2(0, descriptors[1], F_file_flag_write_only_d);

        f_status_t status = F_none;

        // Have the parent perform all appropriate access controls and then send either '0' for no error or '1' for error to the child.
        if (as) {
          f_string_static_t buffer = f_string_static_t_initialize;

          buffer.string = string_result;
          buffer.used = 1;
          buffer.size = 2;

          status = private_fll_execute_as_parent(*as, id_process, parameter, string_result);

          // Inform the child that it can now safely begin (or exit).
          if (F_status_is_error(f_file_write(file, buffer, 0))) {
            string_result[0] = '1';
          }
        }

        // Write all data, if child doesn't read this could block until child closes the pipe.
        if (string_result[0] == '0') {
          f_file_write(file, *parameter->data, 0);
        }

        // Close the write pipe for the parent when finished writing.
        close(descriptors[1]);

        if (F_status_is_error(status)) {
          return status;
        }
      }

      if (parameter && parameter->option & FL_execute_parameter_option_return_d) {

        if (result != 0) {
          pid_t *r = (pid_t *) result;
          *r = id_process;
        }

        return F_parent;
      }

      // Have the parent wait for the child process to finish.
      waitpid(id_process, (int *) result, parameter->wait);

      // This must explicitly check for 0 (as opposed to checking (!result)).
      if (result != 0) {
        if (WIFEXITED(*((int *) result))) {
          return F_none;
        }

        return F_status_set_error(F_failure);
      }

      return F_none;
    }

    if (parameter && parameter->option & FL_execute_parameter_option_session_d) {
      setsid();
    }

    // Close the write pipe for the child.
    close(descriptors[1]);

    // Wait for parent to tell child to begin.
    if (as) {
      f_string_dynamic_t response = f_string_dynamic_t_initialize;

      const f_file_t file = macro_f_file_t_initialize(0, descriptors[0], F_file_flag_read_only_d, 1, 1);

      f_file_read_block(file, &response);

      if (!response.used || response.string[0] == '1') {
        f_string_dynamic_resize(0, &response);

        close(descriptors[0]);

        if (result) {
          f_status_t *r = (f_status_t *) result;

          *r = F_status_set_error(F_failure);
        }

        if (parameter && parameter->option & FL_execute_parameter_option_exit_d) {
          exit(-1);
        }

        return F_child;
      }

      f_string_dynamic_resize(0, &response);
    }

    if (parameter && parameter->signals) {
      #ifdef _di_pthread_support_
        f_signal_mask(SIG_BLOCK, &parameter->signals->block, 0);
        f_signal_mask(SIG_UNBLOCK, &parameter->signals->block_not, 0);
      #else // _di_pthread_support_
        if (parameter->option & FL_execute_parameter_option_threadsafe_d) {
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

      for (f_array_length_t i = 0; i < parameter->environment->used; ++i) {
        f_environment_set(parameter->environment->array[i].name, parameter->environment->array[i].value, F_true);
      } // for
    }

    dup2(descriptors[0], F_type_descriptor_input_d);

    if (as) {
      const f_status_t status = private_fll_execute_as_child(*as, parameter, (int *) result);
      if (F_status_is_error(status)) return status;
    }

    int code = direct ? execv(program.string, fixed_arguments) : execvp(program.string, fixed_arguments);

    // Close the write pipe for the child when done.
    close(descriptors[0]);

    if (code < 0) {
      if (errno == EACCES) code = F_execute_access;
      else if (errno == E2BIG) code = F_execute_too_large;
      else if (errno == EAGAIN) code = F_execute_resource_not;
      else if (errno == EFAULT) code = F_execute_buffer;
      else if (errno == EINVAL) code = F_execute_parameter;
      else if (errno == EIO) code = F_execute_input_output;
      else if (errno == EISDIR) code = F_execute_file_type_directory;
      else if (errno == EIO) code = F_execute_input_output;
      else if (errno == ELIBBAD) code = F_execute_valid_not;
      else if (errno == ELOOP) code = F_execute_loop;
      else if (errno == EMFILE) code = F_execute_resource_not;
      else if (errno == ENAMETOOLONG) code = F_execute_name_not;
      else if (errno == ENFILE) code = F_execute_resource_not;
      else if (errno == ENOENT) code = F_execute_file_found_not;
      else if (errno == ENOEXEC) code = F_execute_bad;
      else if (errno == ENOMEM) code = F_execute_memory_not;
      else if (errno == ENOTDIR) code = F_execute_directory_not;
      else if (errno == EPERM) code = F_execute_prohibited;
      else if (errno == ETXTBSY) code = F_execute_busy;
      else code = F_execute_failure;
    }
    else if (code < 0) {
      code = F_execute_failure;
    }

    if (result) {
      int *r = (int *) result;
      *r = code;
    }

    if (parameter && parameter->option & FL_execute_parameter_option_exit_d) {
      exit(code);
    }

    return F_child;
  }
#endif // !defined(_di_fll_execute_program_)

#if !defined(_di_fll_execute_program_)
  void private_fll_execute_path_arguments_fixate(const f_string_static_t program_path, const f_string_statics_t arguments, const f_string_t last_slash, const bool fixated_is, f_string_static_t program_name, f_string_t fixed_arguments[]) {

    memset(program_name.string, 0, program_name.used + 1);
    memset(fixed_arguments, 0, sizeof(f_string_t) * (arguments.used + 2));

    memcpy(program_name.string, last_slash ? last_slash + 1 : program_path.string, program_name.used);

    if (program_name.used) {
      fixed_arguments[0] = program_name.string;
    }

    if (fixated_is) {
      for (f_array_length_t i = 1; i < arguments.used; ++i) {
        fixed_arguments[i] = arguments.array[i].string;
      } // for
    }
    else {
      for (f_array_length_t i = 0; i < arguments.used; ++i) {
        fixed_arguments[i + 1] = arguments.array[i].string;
      } // for
    }
  }
#endif // !defined(_di_fll_execute_program_)

#ifdef __cplusplus
} // extern "C"
#endif
